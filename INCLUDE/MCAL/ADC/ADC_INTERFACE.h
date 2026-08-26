/*
 * ADC_INTERFACE.h
 */


#ifndef INCLUDE_MCAL_ADC_ADC_INTERFACE_H_
#define INCLUDE_MCAL_ADC_ADC_INTERFACE_H_

/*
 * ATmega32 ADC Channels (32 Options: Single Ended & Differential)
 * Naming Convention for Differential: ADC_PositivePin_NegativePin_Gain
 */
typedef enum {
    // Single Ended Channels
    ADC0 = 0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,

    // Differential Channels (Gain 10x & 200x)
    ADC_0_0_10  = 8,
    ADC_1_0_10  = 9,
    ADC_0_0_200 = 10,
    ADC_1_0_200 = 11,
    ADC_2_2_10  = 12,
    ADC_3_2_10  = 13,
    ADC_2_2_200 = 14,
    ADC_3_2_200 = 15,

    // Differential Channels (Gain 1x)
    ADC_0_1_1   = 16,
    ADC_1_1_1   = 17,
    ADC_2_1_1   = 18,
    ADC_3_1_1   = 19,
    ADC_4_1_1   = 20,
    ADC_5_1_1   = 21,
    ADC_6_1_1   = 22,
    ADC_7_1_1   = 23,
    ADC_0_2_1   = 24,
    ADC_1_2_1   = 25,
    ADC_2_2_1   = 26,
    ADC_3_2_1   = 27,
    ADC_4_2_1   = 28,
    ADC_5_2_1   = 29,

    // Special Testing Channels
    ADC_1_2_2   = 30, // 1.22V Reference
    ADC_GND     = 31  // 0V (GND)
} ADC_CHANNELS;

void MADC_voidInit(void);
u16  MADC_voidGetDigitalValue(ADC_CHANNELS A_ADCChannel);

#endif /* INCLUDE_MCAL_ADC_ADC_INTERFACE_H_ */
