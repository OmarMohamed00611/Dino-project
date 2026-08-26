/*
 * EXTI_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: alata
 */
/*
 * EXTI_PROGRAM.c
 */

#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

// MCAL Directives
#include "../INCLUDE/MCAL/EXTI/EXTI_INTERFACE.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_PRIVATE.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_CFG.h"

// مؤشرات الدوال (Pointers to Functions) لاستدعائها وقت المقاطعة
void (*EXTI0_Callback)(void) = NULL;
void (*EXTI1_Callback)(void) = NULL;
void (*EXTI2_Callback)(void) = NULL;

void MEXTI_voidConfig(EXTI_ID A_EXTI_ID, EXTI_SENSE_MODE A_EXTI_SENSE_MODE)
{
    if((A_EXTI_ID <= EXTI2) && (A_EXTI_SENSE_MODE <= RISING_EDGE))
    {
        switch(A_EXTI_ID)
        {
            case EXTI0:
                MCUCR &= ~(SENSE_MODE_MASK << EXTI0_SENSE_MODE_BITS); // تصفير البتات أولاً
                MCUCR |= (A_EXTI_SENSE_MODE << EXTI0_SENSE_MODE_BITS);
                break;
            case EXTI1:
                MCUCR &= ~(SENSE_MODE_MASK << EXTI1_SENSE_MODE_BITS);
                MCUCR |= (A_EXTI_SENSE_MODE << EXTI1_SENSE_MODE_BITS);
                break;
            case EXTI2:
                // EXTI2 لا تدعم إلا RISING أو FALLING في الـ ATmega32
                switch(A_EXTI_SENSE_MODE)
                {
                    case FALLING_EDGE: CLR_BIT(MCUCSR, EXTI2_SENSE_MODE_BITS); break;
                    case RISING_EDGE:  SET_BIT(MCUCSR, EXTI2_SENSE_MODE_BITS); break;
                    default: break;
                }
                break;
        }
    }
}

void MEXTI_voidEnable(EXTI_ID A_EXTI_ID)
{
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: SET_BIT(GICR, EXTI0_ENABLE_BIT); break;
            case EXTI1: SET_BIT(GICR, EXTI1_ENABLE_BIT); break;
            case EXTI2: SET_BIT(GICR, EXTI2_ENABLE_BIT); break;
        }
    }
}

void MEXTI_voidDisable(EXTI_ID A_EXTI_ID)
{
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: CLR_BIT(GICR, EXTI0_ENABLE_BIT); break;
            case EXTI1: CLR_BIT(GICR, EXTI1_ENABLE_BIT); break;
            case EXTI2: CLR_BIT(GICR, EXTI2_ENABLE_BIT); break;
        }
    }
}

void MEXTI_voidClearFlag(EXTI_ID A_EXTI_ID)
{
    // we clear the flag by setting the flag to 1
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: SET_BIT(GIFR, EXTI0_FLAG_BIT); break;
            case EXTI1: SET_BIT(GIFR, EXTI1_FLAG_BIT); break;
            case EXTI2: SET_BIT(GIFR, EXTI2_FLAG_BIT); break;
        }
    }
}

void MEXTI_voidSetCallBack(EXTI_ID A_EXTI_ID, void(*ptrToFunc)(void))
{
    if((A_EXTI_ID <= EXTI2) && (ptrToFunc != NULL))
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: EXTI0_Callback = ptrToFunc; break;
            case EXTI1: EXTI1_Callback = ptrToFunc; break;
            case EXTI2: EXTI2_Callback = ptrToFunc; break;
        }
    }
}

/* =========================================================
 * Interrupt Service Routines (ISRs)
 * ========================================================= */
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if(EXTI0_Callback != NULL)
    {
        EXTI0_Callback();
    }
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if(EXTI1_Callback != NULL)
    {
        EXTI1_Callback();
    }
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    if(EXTI2_Callback != NULL)
    {
        EXTI2_Callback();
    }
}

