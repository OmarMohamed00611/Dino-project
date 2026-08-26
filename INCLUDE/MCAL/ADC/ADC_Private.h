#ifndef INCLUDE_MCAL_ADC_ADC_PRIVATE_H_
#define INCLUDE_MCAL_ADC_ADC_PRIVATE_H_

#include "../../LIB/STD_TYPES.h"

#define ADMUX_REG    (*(volatile u8*)0x27)
#define ADCSRA_REG   (*(volatile u8*)0x26)
#define ADCL_REG     (*(volatile u8*)0x24)
#define ADCH_REG     (*(volatile u8*)0x25)

#define ADEN_BIT     7
#define ADSC_BIT     6
#define ADIF_BIT     4

#define MUX_MASK     0x1F
#define ADMUX_KEEP   0xE0

#endif

