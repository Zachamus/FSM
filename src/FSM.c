#include "FSM.h"
#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "ADC.h"
#include "SysClock.h"
/*

int current_state = 0;
bool ramp1_done = false;
bool ramp2_done = false;

void FSM(void) {
	
	if (current_state == 0) {
		current_state = 1;
	}
	
	switch(current_state)
	{
		
		case(1):
			//reset registers zero all variables
		
			RCC->AHB2RSTR |= RCC_AHB2RSTR_ADCRST | RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST;
			RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_ADCRST | RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST);
			current_state = 2;
			break;
		
		
		
		case(2):
			//enable GPIO high output for drivers
			//enable ADC/GPIO clock, set pins etc
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			System_Clock_Init();
			ADC_Init();
			
			break;
		
		case(3):
			//monitor state
			break;
		
		
		case(4):
			//ramping state 1
			break;
		
		
		case(5):
			//ramping state 2
			break;
		
		
		case(6):
			//fault state, do not leave here
			break;
	
	
	
	
	
	
	
	
	}
	
	
	
}
*/