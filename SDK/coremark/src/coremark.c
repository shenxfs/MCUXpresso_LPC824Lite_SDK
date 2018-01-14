/*
===============================================================================
 Name        : coremark.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "board.h"
#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
#define TICKRATE_HZ (1000)	/* 1000 ticks per second */

__IO uint32_t ticks = 0;
void SysTick_Handler(void){
	ticks++;
}

void delay_ms(uint32_t ms){
	uint32_t tm;
	tm = ticks;
	tm += ms;
	while (ticks < tm) {
		__WFI();
	}
}
int main(void) {
	Board_Init();
	SystemCoreClockUpdate();
	/* Enable SysTick Timer */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);
	printf("Hello World\n");

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
        Board_LED_Toggle(0);
        delay_ms(500);
    }
    return 0 ;
}
