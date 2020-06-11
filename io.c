/*
 * io.c
 *
 *  Created on: 10. jun. 2020
 *      Author: Aleksandar Lukic
 */

#include "stm32f30x_conf.h" // STM32 configuration
#include "30010_io.h"

volatile uint16_t millisec, sec, min, hour;

// Opg 5
void setjoystick(){

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PA0 to input (UP)
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PB0 to input (DOWN)
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PB5 to input (CENTER)
	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PC1 to input (LEFT)
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PC0 to input (RIGHT)
	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 5x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 5x02 - Pull-down)
}

uint16_t readjoystick(){
	setjoystick();

	uint16_t up, down, center, left, right, out;

	up = (GPIOA->IDR & (0x0001 << 4)) >> (4); //Read from pin PA4 shifted to bit0

	down = (GPIOB->IDR & (0x0001 << 0)) << (1); //Read from pin PB0 shifted to bit1

	left = (GPIOC->IDR & (0x0001 << 1)) << (1); //Read from pin PC1 shifted to bit2

	right = (GPIOC->IDR & (0x0001 << 0)) << (3); //Read from pin PC0 shifted to bit3

	center = (GPIOB->IDR & (0x0001 << 5)) >> 1; //Read from pin PB5 shifted to bit4

	out = up | down | left | right | center;
	//printf("%d\n", out);
	return out;
}

void setLed(uint16_t b, uint16_t r, uint16_t g){

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	if (b != 0){
	// Set pin PA9 to input (BLUE)
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (9 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 5x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (9 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (9 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 5x02 - Pull-down)
	}

	if (r != 0){
	// Set pin PB4 to input (RED)
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 5x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 5x02 - Pull-down)
	}

	if (g != 0){
	// Set pin PC7 to input (GREEN)
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (7 * 2)); // Set mode register (0x00 –
	//Input, 0x01 - Output, 5x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (7 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (7 * 2)); // Set push/pull register (0x00 -
	//No pull, 0x01 - Pull-up, 5x02 - Pull-down)
	}
}

// Opg 6
void timer(){
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;

	TIM2->CR1 = 0x01; // Configure timer 2
	TIM2->ARR = 0x61A7FF; // Set reload value
	TIM2->PSC = 0x00; // Set prescale value

	TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

	NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void TIM2_IRQHandler(void) {

	millisec++;

	if (millisec = 10){
		sec++;
		millisec = 0;
	}

	if (sec = 60){
		min++;
		sec = 0;
	}

	if (min = 60){
		hour++;
		min = 0;
	}

	TIM2->SR &= ~0x0001; // Clear interrupt bit
}

void printTime(uint8_t x, uint8_t y){
	gotoxy(x,y);
	printf(millisec);
	gotoxy(x+1,y);
	printf(sec);
	gotoxy(x+2,y);
	printf(min);
	gotoxy(x+3,y);
	printf(hour);

}
