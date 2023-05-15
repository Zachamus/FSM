#include "stm32l476xx.h"

static void DAC_Pin_Init(void) {
    // [TODO]
	GPIOA->MODER &= ~(GPIO_MODER_MODE4);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD4);
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

void DAC_Write_Value(uint32_t value, int channel) {
    // [TODO] Write DAC1Ch1 right-aligned 12-bit value
	if (channel == 1) {
		DAC1->DHR12R1 = value;
	}
	
	else if (channel ==2) {
		DAC1->DHR12R2 = value;
	}
	
}

void DAC_Init(void) {
    DAC_Pin_Init();
	RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
	DAC1->CR &= ~(DAC_CR_EN1);
	DAC1->CR &= ~(DAC_CR_EN2);
	DAC1->CR |= DAC_CR_TSEL1;
	DAC1->CR |= DAC_CR_TSEL2;
	DAC1->CR &= ~(DAC_CR_TEN1);
	DAC1->CR &= ~(DAC_CR_TEN2);
	DAC1->MCR &= ~(DAC_MCR_MODE1);
	DAC1->MCR &= ~(DAC_MCR_MODE1);
	DAC1->CR |= DAC_CR_EN1;
	DAC1->CR |= DAC_CR_EN2;
	

    // [TODO] Enable DAC clock

    // [TODO] Enable software trigger mode

    // [TODO] Disable trigger

    // [TODO] DAC1 connected in normal mode to external pin only with buffer enabled

    // [TODO] Enable DAC channel 1

    DAC_Write_Value(0,1);
}
