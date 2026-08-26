/*
 * ADC_PRIVATE.h
 *
 *  Created on: Aug 24, 2026
 *      Author: alata
 */

#ifndef INCLUDE_MCAL_ADC_ADC_PRIVATE_H_
#define INCLUDE_MCAL_ADC_ADC_PRIVATE_H_


/* ADC Registers */
#define ADMUX           (*(volatile u8 *) 0x27)
#define ADCSRA          (*(volatile u8 *) 0x26)
#define ADCH            (*(volatile u8 *) 0x25)
#define ADCL            (*(volatile u8 *) 0x24)
#define ADC_DATA_REG    (*(volatile u16*) 0x24) // عشان نقرأ الـ 10 بت مرة واحدة

/* ADMUX Bits */
#define REFS1           7
#define REFS0           6
#define ADLAR           5

/* ADCSRA Bits */
#define ADEN            7
#define ADSC            6
#define ADATE           5
#define ADIF            4
#define ADIE            3
#define ADPS2           2
#define ADPS1           1
#define ADPS0           0

/* Voltage Reference Options */
#define AREF_VREF               1
#define AVCC_VREF               2
#define INTERNAL_2_56_VREF      3

/* Prescaler Options */
#define PRESCALER_DIV_2         1
#define PRESCALER_DIV_4         2
#define PRESCALER_DIV_8         3
#define PRESCALER_DIV_16        4
#define PRESCALER_DIV_32        5
#define PRESCALER_DIV_64        6
#define PRESCALER_DIV_128       7


#endif /* INCLUDE_MCAL_ADC_ADC_PRIVATE_H_ */
