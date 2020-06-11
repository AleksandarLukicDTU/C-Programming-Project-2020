/*********************************************************************
                              Main.c
**********************************************************************/
#include "stm32f30x_conf.h" // STM32 configuration
#include "30010_io.h" // Input output library for this course
#include "io.h"


/* // Main 1 - opg 1


int main(void)
{
    uart_init(9600); // Initialize USB serial emulation at 9600 baud
    printf("Hello, World!\n"); // Show the world you are alive
    while(1){}
}
*/
/* // Main 2 - opg 1
int16_t power(int16_t a, int16_t exp) {
// calculates a^exp
 int16_t i, r = a;
 for (i = 1; i <= exp-1; i++)
 r *= a;
 return(r);
 while(1){}
}
int main(void)
 {

 int16_t a;
 uart_init( 9600 ); // Initialize USB serial at 9600 baud
 color(6,1);
 printf("\n\n x x^2 x^3 x^4\n");
 for (a = 0; a < 10; a++)
    printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));
 while(1){}
}
*/

/*// Main 3 - opg 2
int main(void)
{
    uart_init(9600); // Initialize USB serial emulation at 9600 baud
    clrscr();
    //gotoxy(5,10);
    //clreol();
    color(15,0);
    int i, j;
    int sum = 0;
    for (i = 0; i <= 10; i++){
        for (j = 0; j <= 3; j++){
            sum++;
            printf("Hello, World no.%d ", sum); // Show the world you are alive
        }
        printf("\n");
    }
    underline(1);
    printf("THE END\nTotal: %d\n", sum);
    underline(2);
    blink(1);
    printtest(9,5);
    blink(2);
    inverse(1);
    printtest(9,5);
    inverse(2);
    //gotoxy(7,10);
    //clreol();
    while(1){}
}
*/
/*// Main 4 - opg 2
int main(void)
{

    uart_init(9600); // Initialize USB serial emulation at 9600 baud
    clrscr();
    fgcolor(6);
    window(1,1,10,31,"Gruppe 6 lolo1",1);
    fgcolor(0);
    fgcolor(6);
    window(12,1,10,41,"Gruppe 6 lolo1",0);
    fgcolor(7);
    //box(1,1,10,31,6);
    // window(1,1,10,30,"Welcome!",0);
    while(1){}
}
*/
// Main 5 - opg 4
/*
int main(void)
{
    int x1 = 1;
    int x2 = 60;
    int y1 = 1;
    int y2 = 20;
    int style = 1;
    int offsetX = (x1 + x2)/2;
    int offsetY = (y1 + y2)/2;

    uart_init(9600); // Initialize USB serial emulation at 9600 baud
    clrscr();

    fgcolor(6);
    walls(y1,x1,y2,x2,style);
    walls(offsetY-1, offsetX-5, offsetY+1, offsetX+5,style);
    hits(offsetY, offsetX-4);
    fgcolor(7);
    while(1){}
}
*/
/*// Main 6 - Opg 4
typedef struct balls{
	int y;
	int x;
	int yvel;
	int xvel;
}balls;

int main(void){
	// Initialization
	// Walls:
	int xmin = 1;	int xmax = 60; int ymin = 1; int ymax = 20;
	int style = 1; int offsetX = (xmin + xmax)/2; int offsetY = (ymin + ymax)/2;
	int count = 0;

	// Ball:
	balls ball;
	ball.y = offsetY;
	ball.x = offsetX;
	ball.yvel = 1 ;
	ball.xvel = 1;

	uart_init(9600); // Initialize USB serial emulation at 9600 baud
	clrscr();
	gotoxy(1,1);
	//drawball(1,1);
	fgcolor(6);

	//walls(ymin, xmin, ymax, xmax, style);
	//walls(offsetY-1, offsetX-5, offsetY+1, offsetX+5, style);
	gotoxy(offsetY, offsetX-4);
	printf("Hits:");

	// Update loop
	while(count < 1000){ // max collisions

		eraseball(ball.y, ball.x); // refresh ball graphics

		// check for collision with outer walls
		if (ball.x == xmin+1 || ball.x == xmax-1 ){
			ball.xvel *= -1;
			count++;
		}
		if (ball.y == ymin+1 || ball.y == ymax-1){
			ball.yvel *= -1;
			count++;
		}

		// move ball according to velocity
		ball.y += ball.yvel;
		ball.x += ball.xvel;

		// check for collision with inner walls
		if(ball.x <= offsetX-5+2 && ball.x >= offsetX+5-2 || ball.y <= offsetY && ball.y >= offsetY){
			//count+=100;
		}else{
			drawball(ball.y, ball.x);
			//walls(offsetY-1, offsetX-5, offsetY+1, offsetX+5, style);
			//gotoxy(offsetY, offsetX-4);
			//printf("Hits:");
		}
		gotoxy(offsetY, offsetX+1);
		printf("%d", count);
	}
	// end message
	gotoxy(offsetY, offsetX-4);
			printf("GAME OVER");
	while(1){}
}
*/
// Main 7 - Opg 5
//void main(){
//
//	uart_init(9600); // Initialize USB serial emulation at 9600 baud
////	printf("Hello, World!");
//	clrscr();
//
//	while(1){
//		readjoystick();
//		setLed(1,1,1);
//	}
//}

void main(){

	uart_init(9600); // Initialize USB serial emulation at 9600 baud
	clrscr();
	//window(1,1,10,30,"Stop Watch",0);

	while(1){
		printTime(5,5);
	}
}
