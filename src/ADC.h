#ifndef __STM32L476G_DISCOVERY_ADC_H
#define __STM32L476G_DISCOVERY_ADC_H

#include "stm32l476xx.h"
#include <stdint.h>

#define ADC_SAMPLE_SIZE 100

void ADC_Init(void);

void ADC_Wakeup(void);
void ADC_Init(void);

void ADC_Pin_Init(void);
void ADC_Common_Configuration(void);

void ADC_Swap_Channel(int channel);

uint32_t ADC_Run(int ADCx);

#endif /* __STM32L476G_DISCOVERY_ADC_H */
