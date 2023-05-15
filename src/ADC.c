#include "ADC.h"

#include "stm32l476xx.h"

#include <stdint.h>

void ADC_Wakeup(void) {
    int wait_time;

    // To start ADC operations, the following sequence should be applied
    // DEEPPWD = 0: ADC not in deep-power down
    // DEEPPWD = 1: ADC in deep-power-down (default reset state)
    if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
        ADC1->CR &= ~ADC_CR_DEEPPWD; // Exit deep power down mode if still in that state
		if ((ADC2->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
				ADC2->CR &= ~ADC_CR_DEEPPWD;
		if ((ADC3->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
				ADC3->CR &= ~ADC_CR_DEEPPWD;
    // Enable the ADC internal voltage regulator
    // Before performing any operation such as launching a calibration or enabling the ADC, the ADC
    // voltage regulator must first be enabled and the software must wait for the regulator start-up
    // time.
    ADC1->CR |= ADC_CR_ADVREGEN;
		ADC2->CR |= ADC_CR_ADVREGEN;
		ADC3->CR |= ADC_CR_ADVREGEN;

    // Wait for ADC voltage regulator start-up time
    // The software must wait for the startup time of the ADC voltage regulator (T_ADCVREG_STUP)
    // before launching a calibration or enabling the ADC.
    // T_ADCVREG_STUP = 20 us
    wait_time = 60 * (80000000 / 1000000);
    while (wait_time != 0) {
        wait_time--;
    }
}

void ADC_Common_Configuration() {
    // [TODO]
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;
	ADC123_COMMON->CCR &= ~(15UL << 18);
	ADC123_COMMON->CCR &= ~(3UL << 16);
	ADC123_COMMON->CCR |= (1UL << 16);
	ADC123_COMMON->CCR &= ~(31UL);
}

void ADC_Pin_Init(void) {
    // [TODO]
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOA->MODER |= GPIO_MODER_MODE0;
	GPIOC->MODER |= GPIO_MODER_MODE0;
	GPIOC->MODER |= GPIO_MODER_MODE1;
	GPIOC->MODER |= GPIO_MODER_MODE2;
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD0);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD1);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD2);
	GPIOA->ASCR |= GPIO_ASCR_ASC0;
	GPIOC->ASCR |= GPIO_ASCR_ASC0;
	GPIOC->ASCR |= GPIO_ASCR_ASC1;
	GPIOC->ASCR |= GPIO_ASCR_ASC2;
	
	
	
}

void ADC_Init(void) {
    // [TODO] Enable & Reset ADC Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	RCC->AHB2RSTR |= RCC_AHB2RSTR_ADCRST;
	RCC->CCIPR |= 3UL << 28;
	RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_ADCRST);
	ADC1->CR &= ~(ADC_CR_ADEN);
	ADC2->CR &= ~(ADC_CR_ADEN);
	ADC3->CR &= ~(ADC_CR_ADEN);
	ADC1->CFGR &= ~(ADC_CFGR_ALIGN);
	ADC2->CFGR &= ~(ADC_CFGR_ALIGN);
	ADC3->CFGR &= ~(ADC_CFGR_ALIGN);
	ADC1->CFGR &= ~(ADC_CFGR_RES);
	ADC2->CFGR &= ~(ADC_CFGR_RES);
	ADC3->CFGR &= ~(ADC_CFGR_RES);
	ADC1->SQR1 &= ~(ADC_SQR1_L);
	ADC2->SQR1 &= ~(ADC_SQR1_L);
	ADC3->SQR1 &= ~(ADC_SQR1_L);
	ADC1->SQR1 &= ~(31UL << 6);
	ADC1->SQR1 |= (5UL << 6);
	ADC2->SQR1 &= ~(31UL << 6);
	ADC2->SQR1 |= (1UL << 6);
	ADC3->SQR1 &= ~(31UL << 6);
	ADC3->SQR1 |= (2UL << 6);
	ADC1->DIFSEL &= ~(1UL << 5);
	ADC2->DIFSEL &= ~(1UL << 1);
	ADC3->DIFSEL &= ~(1UL << 2);
	ADC3->DIFSEL &= ~(1UL << 3);
	ADC1->SMPR1 &= ~(ADC_SMPR1_SMP5);
	ADC1->SMPR1 |= (3UL << 15);
	ADC2->SMPR1 &= ~(ADC_SMPR1_SMP1);
	ADC2->SMPR1 |= (3UL << 3);
	ADC3->SMPR1 &= ~(ADC_SMPR1_SMP2);
	ADC3->SMPR1 &= ~(ADC_SMPR1_SMP3);
	ADC3->SMPR1 |= (3UL << 6);
	ADC3->SMPR1 |= (3UL << 9);
	ADC1->CFGR &= ~(ADC_CFGR_CONT);
	ADC2->CFGR &= ~(ADC_CFGR_CONT);
	ADC3->CFGR &= ~(ADC_CFGR_CONT);
	ADC1->CFGR &= ~(ADC_CFGR_EXTEN);
	ADC2->CFGR &= ~(ADC_CFGR_EXTEN);
	ADC3->CFGR &= ~(ADC_CFGR_EXTEN);
	ADC1->CR |= ADC_CR_ADEN;
	ADC2->CR |= ADC_CR_ADEN;
	ADC3->CR |= ADC_CR_ADEN;
	
	while ((ADC1->ISR & 1UL) == 0) {
	}
	while ((ADC2->ISR & 1UL) == 0) {
	}
	while ((ADC3->ISR & 1UL) == 0) {
	}
	
	


    // Other ADC Initialization
    ADC_Pin_Init();
    ADC_Common_Configuration();
    ADC_Wakeup();

    // [TODO] Other Configuration
}


void ADC_Swap_Channel(int channel) {
	
	if (channel == 2) {
		ADC3->CR &= ~(ADC_CR_ADEN);
		ADC3->SQR1 &= ~(31UL << 6);
		ADC3->SQR1 |= (2UL << 6);
		ADC3->CR |= ADC_CR_ADEN;
		
	}
	else if (channel == 3) {
		
		ADC3->CR &= ~(ADC_CR_ADEN);
		ADC3->SQR1 &= ~(31UL << 6);
		ADC3->SQR1 |= (3UL << 6);
		ADC3->CR |= ADC_CR_ADEN;
		
	}
	while ((ADC3->ISR & 1UL) == 0) {
	}
	
	
	
	
}


uint32_t ADC_Run(int ADCx) {
		uint32_t temp2;
		uint32_t temp3;
		uint32_t temp;
	if (ADCx == 1) {	
		ADC1->CR |= ADC_CR_ADSTART;
		while((ADC1->ISR & ADC_ISR_EOC) == 0) {
		}
		temp = ADC1->DR;
		return temp;
	}
	
	else if (ADCx == 2) {
		ADC2->CR |= ADC_CR_ADSTART;
		while((ADC2->ISR & ADC_ISR_EOC) == 0) {
		}
		temp2 = ADC2->DR;
		return temp2;
	}
	else if (ADCx == 3) {
		ADC3->CR |= ADC_CR_ADSTART;
		while((ADC3->ISR & ADC_ISR_EOC) == 0) {
		}
		temp3 = ADC3->DR;
		return temp3;
	}
}
	
	
