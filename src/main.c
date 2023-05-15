/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 5A
 */


#include "ADC.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>
#include <stdbool.h>
#include "DAC.h"

//uint32_t ADC1Value;
int current_state = 0;
bool ramp1_done = false;
bool ramp2_done = false;
bool halt = false;
uint32_t PD1;
uint32_t PD2;
uint32_t PD3;
uint32_t PD4;
double V1;
double V2;
double V3;
double V4;
uint32_t DV1 = 10;
uint32_t DV2 = 4;
uint32_t Vmax1 = 3800;
uint32_t Vmax2 = 3800;
double PD1set = 3.0;
double PD2set = 0.0;
double PD3set = 3.0;
double PD4set = 0.0;
uint32_t currentV1 = 0 ;
uint32_t currentV2=0;

//uint32_t second;




int main(void) {
 
	while(1) {

	if (current_state == 0) {
		current_state = 1;
	}
	if (halt == true) {
		current_state = 6;
	}
	
	switch(current_state)
	{
		
		case(1):
			//reset registers zero all variables
		
			RCC->AHB2RSTR |= RCC_AHB2RSTR_ADCRST | RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST;
			RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_ADCRST | RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST);
			current_state = 2;
			continue;
		
		
		
		case(2):
			//enable GPIO high output for drivers
			//enable ADC/GPIO clock, set pins etc
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			System_Clock_Init();
			ADC_Init();
			DAC_Init();
			current_state = 3;
			
			
			
			continue;
		
		case(3):
			//monitor state
			PD1 = ADC_Run(1);
		
		
			V1 = ((double)PD1/4096) * (double)(3.35);
			PD2 = ADC_Run(2);
			V2 = ((double)PD2/4096) * (double)(3.35);
			
			PD3 = ADC_Run(3);
			
			V3 = ((double)PD3/4096) * (double)(3.35);
			ADC_Swap_Channel(3);
			PD4 = ADC_Run(3);
			V4 = ((double)PD4/4096) * (double)(3.35);
			
			ADC_Swap_Channel(2);
		
			for(int i = 0; i < 50000; i++){
			}
			
			if ((V1 <= PD1set) && (V2 >= PD2set) && (V3 <= PD3set) && (V4 >= PD4set)) { //(V1 < PD1set) && (V2 > PD2set) && (V3 < PD3set) && (V4 > PD4set)
				current_state = 4;
			}
			else {
				current_state = 6;
				halt = true;
			}
		
			continue;
		
		
		case(4):
			//ramping state 1
		
		
		
			if (currentV1 >= Vmax1) {
				ramp1_done = true;
				DAC_Write_Value(Vmax1,1);
				
			}
				
		
		if (ramp1_done == true) {
			current_state = 5;
			DAC_Write_Value(Vmax1,1);
			continue;
		}
		
		else {
			DAC_Write_Value(currentV1 + DV1, 1);
			currentV1 = currentV1 + DV1;
			current_state = 3;
			continue;
			
			
		}
			
		
		case(5):
			//ramping state 2
		if (currentV2 >= Vmax2) {
				ramp2_done = true;
				DAC_Write_Value(4096,2);
				
			}
		
		
		
		if (ramp2_done == true) {
			current_state = 3;
			DAC_Write_Value(4096,2);
			continue;
		}
		
		else {
			DAC_Write_Value(currentV2 + DV2, 2);
			currentV2 = currentV2 + DV2;
			current_state = 3;
			continue;
			
		}
		
		
		case(6):
			//fault state, do not leave here
		
			current_state = 6;
			break;
	
	
	
	
	}
	
	
	
	}
	
	
	
	
	
	
  
}
