#include "stdint.h"
#include "stdio.h"

#define ESC 0x1B

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

// ALEKSANDARS FUNKTIONER!-------------------------------------------------------------------

// Clears terminal
void clrscr(){
    printf("%c[2J", ESC);
}

// clears from cursor to end of line
void clreol(){
    printf("%c[K", ESC);
}

// set cursor position
void gotoxy(uint8_t x, uint8_t y){
    printf("%c[%d;%dH", ESC, x, y);
}

// turn on/off underline
void underline(uint8_t on){
    if (on==1){
        printf("%c[04m", ESC);
    }else{
        printf("%c[24m", ESC);
    }
}

// turn on/off blink
void blink(uint8_t on){
    if (on==1){
        printf("%c[05m", ESC);
    }else{
        printf("%c[25m", ESC);
    }
}

// turn on/off reverse
void inverse(uint8_t on){
    if (on==1){
        printf("%c[07m", ESC);
    }else{
        printf("%c[27m", ESC);
    }
}

// test print input to point
void printtest(int x, int y){
    printf("x:%d, y:%d\n", x, y);
}

// draws empty colored box
void box(uint8_t y1, uint8_t x1, uint8_t y2, uint8_t x2, uint8_t color){
    gotoxy(y1, x1);
    int i, j;
    bgcolor(color);
    for(i = x1; i <= x1+x2; i++){
        for(j = y1; j <= y1+y2; j++){
            gotoxy(j,i);
            printf(" ");
        }
    }
    bgcolor(0);
}

// draws window with centered title
void window(uint8_t y1, uint8_t x1, uint8_t y2, uint8_t x2, char * title, uint8_t style){

    int i, j;
    int xsum = x1 + x2;
    int ysum = y1 + y2;
    int len = strlen(title);

    int offset;
    // pass string into char array
    char titlearray[len+1];
    strcpy(titlearray, title);

    int upleft, upright, downleft, downright, horline, verline, jointleft, jointright;

    //box(y1, x1, y2, x2, 6); // Color inside of box

    // Style initialization
    if (style != 1){
        upleft = 218;
        upright = 191;
        downleft = 192;
        downright = 217;
        horline = 196;
        verline = 179;
        jointleft = 180;
        jointright = 195;
    } else {
        upleft = 201;
        upright = 187;
        downleft = 200;
        downright = 188;
        horline = 205;
        verline = 186;
        jointleft = 185;
        jointright = 204;
    }

    // Draw Corners
    gotoxy(y1,x1);
    printf("%c", upleft);

    gotoxy(ysum, x1);
    printf("%c", downleft);

    gotoxy(y1, xsum);
    printf("%c", upright);

    gotoxy(ysum, xsum);
    printf("%c", downright);

    // left side
    for(i = y1+1; i < ysum; i++){
        gotoxy(i, x1);
        printf("%c", verline);
    }
    // right side
    for(i = y1+1; i < ysum; i++){
        gotoxy(i, xsum);
        printf("%c", verline);
    }
    // bottom
    for(i = x1+1; i < xsum; i++){
        gotoxy(ysum, i);
        printf("%c", horline);
    }

    // top
    offset = len/2;

    for(i = x1+1; i <= xsum/2 - offset; i++){ // prints left side
        if (i != xsum/2 - offset){
            gotoxy(y1, i);
            printf("%c", horline);
        }else{
            gotoxy(y1, i);
            printf("%c", jointleft);
        }
    }

    for(i = xsum - 1; i >= xsum/2 + offset; i--){ // prints right side
        if (i != xsum/2 + offset + 1){
            gotoxy(y1, i);
            printf("%c", horline);
        }else{
            gotoxy(y1, i);
            printf("%c", jointright);
        }
    }
    // print title in center
    blink(1);
    inverse(1);
    gotoxy(y1,xsum/2 - offset + 1);
    printf("%s", titlearray);
    blink(0);
    inverse(0);
    gotoxy(ysum+1, x1);

}
// draws empty window
void walls(uint8_t y1, uint8_t x1, uint8_t y2, uint8_t x2, uint8_t style){

    int i, j;
    int xsum = x2-x1;
    int ysum = y2-y1;

    int upleft, upright, downleft, downright, horline, verline, jointleft, jointright;

    // Style initialization
    if (style != 1){
        upleft = 218;
        upright = 191;
        downleft = 192;
        downright = 217;
        horline = 196;
        verline = 179;
    } else {
        upleft = 201;
        upright = 187;
        downleft = 200;
        downright = 188;
        horline = 205;
        verline = 186;
    }

    // Draw Corners
    gotoxy(y1,x1);
    printf("%c", upleft);

    gotoxy(y2, x1);
    printf("%c", downleft);

    gotoxy(y1, x2);
    printf("%c", upright);

    gotoxy(y2, x2);
    printf("%c", downright);

    // left side
    for(i = y1+1; i < y2; i++){
        gotoxy(i, x1);
        printf("%c", verline);
    }
    // right side
    for(i = y1+1; i < y2; i++){
        gotoxy(i, x2);
        printf("%c", verline);
    }
    // top
    for(i = x1+1; i < x2; i++){
        gotoxy(y1, i);
        printf("%c", horline);
    }
    // bottom
    for(i = x1+1; i < x2; i++){
        gotoxy(y2, i);
        printf("%c", horline);
    }
}
// Draw ball
void drawball(y1,x1){
    gotoxy(y1,x1);
    int symbol = 111;
    printf("%c", symbol);
}
// Erase ball
void eraseball(y1,x1){
    gotoxy(y1,x1);
    printf(" ");
}



