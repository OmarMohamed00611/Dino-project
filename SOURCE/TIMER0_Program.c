
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/DIO/DIO_Interface.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_Interface.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_Private.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_Config.h"
#include "../INCLUDE/MCAL/TIMERS/TIMER0/TIMER0_Private.h"
#include "../INCLUDE/MCAL/TIMERS/TIMER0/TIMER0_Config.h"
#include "../INCLUDE/MCAL/TIMERS/TIMER0/TIMER0_Interface.h"

static void (*TIMER0_OVF_CALLBACK)(void) = NULL;
static void (*TIMER0_CTC_CALLBACK)(void) = NULL;

void TIMER0_voidInit(void)
{
#if (TIMER0_MODE == NORMAL_MODE)
    CLR_BIT(TCCR0_REG, TIMER0_WGM01_BIT);
    CLR_BIT(TCCR0_REG, TIMER0_WGM00_BIT);
    SET_BIT(TIMSK_REG, TIMER0_TOIE0_BIT);
    CLR_BIT(TIMSK_REG, TIMER0_OCIE0_BIT);
    TCCR0_REG &= 0xF8;
    TCCR0_REG |= TIMER0_CLK_CFG;

#elif (TIMER0_MODE == PHASE_CORRECT_MODE)
    SET_BIT(TCCR0_REG, TIMER0_WGM00_BIT);
    CLR_BIT(TCCR0_REG, TIMER0_WGM01_BIT);
    #if (TIMER0_PWM_MODE == NON_INVERTING_PWM)
        CLR_BIT(TCCR0_REG, TIMER0_COM00_BIT);
        SET_BIT(TCCR0_REG, TIMER0_COM01_BIT);
    #elif (TIMER0_PWM_MODE == INVERTING_PWM)
        SET_BIT(TCCR0_REG, TIMER0_COM00_BIT);
        SET_BIT(TCCR0_REG, TIMER0_COM01_BIT);
    #endif
    TCCR0_REG &= 0xF8;
    TCCR0_REG |= TIMER0_CLK_CFG;

#elif (TIMER0_MODE == CTC_MODE)
    CLR_BIT(TCCR0_REG, TIMER0_WGM00_BIT);
    SET_BIT(TCCR0_REG, TIMER0_WGM01_BIT);
    CLR_BIT(TIMSK_REG, TIMER0_TOIE0_BIT);
    SET_BIT(TIMSK_REG, TIMER0_OCIE0_BIT);
    TCCR0_REG &= 0xF8;
    TCCR0_REG &= ~(0x30);
    TCCR0_REG |= (TIMER0_CLK_CFG | (TIMER0_OC0_MODE << TIMER0_COM00_BIT));

#elif (TIMER0_MODE == FAST_PWM_MODE)
    SET_BIT(TCCR0_REG, TIMER0_WGM01_BIT);
    SET_BIT(TCCR0_REG, TIMER0_WGM00_BIT);
    #if (TIMER0_PWM_MODE == NON_INVERTING_PWM)
        CLR_BIT(TCCR0_REG, TIMER0_COM00_BIT);
        SET_BIT(TCCR0_REG, TIMER0_COM01_BIT);
    #elif (TIMER0_PWM_MODE == INVERTING_PWM)
        SET_BIT(TCCR0_REG, TIMER0_COM00_BIT);
        SET_BIT(TCCR0_REG, TIMER0_COM01_BIT);
    #endif
    TCCR0_REG &= 0xF8;
    TCCR0_REG |= TIMER0_CLK_CFG;

#else
    #error "Wrong selection of TIMER0_MODE"
#endif
}

void TIMER0_voidSetOCR0Value(u8 A_u8OCR0Value)
{
    OCR0_REG = A_u8OCR0Value;
}

void TIMER0_voidSetPreloadValue(u8 A_u8NoOfTicks)
{
    TCNT0_REG = A_u8NoOfTicks;
}

void TIMER0_voidStopTimer(void)
{
    TCCR0_REG &= 0xF8;
}

void TIMER0_voidSetOVFCallback(void (*A_PtrToFunc)(void))
{
    if (A_PtrToFunc != NULL)
    {
        TIMER0_OVF_CALLBACK = A_PtrToFunc;
    }
}

void TIMER0_voidSetCTCCallback(void (*A_PtrToFunc)(void))
{
    if (A_PtrToFunc != NULL)
    {
        TIMER0_CTC_CALLBACK = A_PtrToFunc;
    }
}

void TIMER0_voidSetPWMDutyCycle(u8 Copy_u8DutyCycle)
{
    u8 Local_u8OCR0Value;
    if (Copy_u8DutyCycle <= 100)
    {
#if (TIMER0_PWM_MODE == NON_INVERTING_PWM)
        Local_u8OCR0Value = (u8)(((u32)Copy_u8DutyCycle * 255) / 100);
#elif (TIMER0_PWM_MODE == INVERTING_PWM)
        Local_u8OCR0Value = 255 - (u8)(((u32)Copy_u8DutyCycle * 255) / 100);
#endif
        OCR0_REG = Local_u8OCR0Value;
    }
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (TIMER0_OVF_CALLBACK != NULL)
    {
        TIMER0_OVF_CALLBACK();
    }
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (TIMER0_CTC_CALLBACK != NULL)
    {
        TIMER0_CTC_CALLBACK();
    }
}

