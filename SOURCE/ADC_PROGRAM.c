/*
 * ADC_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: alata
 */



#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"
#include "../INCLUDE/MCAL/ADC/ADC_PRIVATE.h"
#include "../INCLUDE/MCAL/ADC/ADC_CFG.h"

void MADC_voidInit(void)
{
    /* 1. Select Voltage Reference */
    #if ADC_VREF_SELECTION == AREF_VREF
        CLR_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
    #elif ADC_VREF_SELECTION == AVCC_VREF
        SET_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
    #elif ADC_VREF_SELECTION == INTERNAL_2_56_VREF
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
    #endif

    /* 2. Select Data Adjustment (Right Adjust for 10-bit resolution) */
    CLR_BIT(ADMUX, ADLAR);

    /* 3. Select Prescaler */
    ADCSRA &= 0b11111000; // Clear first 3 bits
    ADCSRA |= ADC_PRESCALER_SELECTION; // Set prescaler

    /* 4. Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

u16 MADC_voidGetDigitalValue(ADC_CHANNELS A_ADCChannel)
{
    u16 Local_u16DigitalValue = 0;

    /* 1. Select the Channel (Clear the first 5 bits then insert the channel number) */
    ADMUX &= 0b11100000;
    ADMUX |= A_ADCChannel;

    /* 2. Start Conversion */
    SET_BIT(ADCSRA, ADSC);

    /* 3. Wait until conversion is complete (Polling on ADIF flag) */
    while (GET_BIT(ADCSRA, ADIF) == 0);

    /* 4. Clear the Interrupt Flag (by writing 1 to it) */
    SET_BIT(ADCSRA, ADIF);

    /* 5. Read the Data */
    Local_u16DigitalValue = ADC_DATA_REG;

    return Local_u16DigitalValue;
}
