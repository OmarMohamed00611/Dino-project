
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/ADC/ADC_Interface.h"
#include "../INCLUDE/MCAL/ADC/ADC_Private.h"
#include "../INCLUDE/MCAL/ADC/ADC_Config.h"

void ADC_voidInit(void)
{

    ADMUX_REG = (ADC_REFERENCE << 6) | (ADC_ADJUST << 5);

    ADCSRA_REG = (1 << ADEN_BIT) | (ADC_PRESCALER & 0x07);
}

u16 ADC_u16GetDigitalValue(ADC_CHANNELS A_ADCChannel)
{
    u8 L_u8Low;
    u8 L_u8High;

    ADMUX_REG = (ADMUX_REG & ADMUX_KEEP) | (A_ADCChannel & MUX_MASK);

    SET_BIT(ADCSRA_REG, ADSC_BIT);

    while (GET_BIT(ADCSRA_REG, ADIF_BIT) == 0);

    SET_BIT(ADCSRA_REG, ADIF_BIT);

#if (ADC_ADJUST == ADC_RIGHT)
    L_u8Low  = ADCL_REG;
    L_u8High = ADCH_REG;
    return ((u16)L_u8High << 8) | L_u8Low;
#else
    return ADCH_REG;
#endif
}

