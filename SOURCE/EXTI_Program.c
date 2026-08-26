
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/EXTI/EXTI_Interface.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_Private.h"
#include "../INCLUDE/MCAL/EXTI/EXTI_Config.h"

void (*EXTI0_Callback)(void) = NULL;
void (*EXTI1_Callback)(void) = NULL;
void (*EXTI2_Callback)(void) = NULL;

void EXTI_voidConfig (EXTI_ID A_EXTI_ID, EXTI_SENSE_MODE A_EXTI_SENSE_MODE)
{
    if((A_EXTI_ID <= EXTI2) && (A_EXTI_SENSE_MODE <= RISING_EDGE))
    {
        switch(A_EXTI_ID)
        {
            case EXTI0:

                MCUCR_REG &= ~(SENSE_MODE_MASK << EXTI0_SENSE_MODE_BITS);
                MCUCR_REG |=  (A_EXTI_SENSE_MODE << EXTI0_SENSE_MODE_BITS);
                break;

            case EXTI1:

                MCUCR_REG &= ~(SENSE_MODE_MASK << EXTI1_SENSE_MODE_BITS);
                MCUCR_REG |=  (A_EXTI_SENSE_MODE << EXTI1_SENSE_MODE_BITS);
                break;

            case EXTI2:

                if (A_EXTI_SENSE_MODE == FALLING_EDGE)
                {
                    CLR_BIT(MCUCSR_REG, EXTI2_SENSE_MODE_BITS);
                }
                else if (A_EXTI_SENSE_MODE == RISING_EDGE)
                {
                    SET_BIT(MCUCSR_REG, EXTI2_SENSE_MODE_BITS);
                }
                else {  }
                break;

            default: break;
        }
    }
}

void EXTI_voidEnable(EXTI_ID A_EXTI_ID)
{
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: SET_BIT(GICR_REG, EXTI0_ENABLE_BIT); break;
            case EXTI1: SET_BIT(GICR_REG, EXTI1_ENABLE_BIT); break;
            case EXTI2: SET_BIT(GICR_REG, EXTI2_ENABLE_BIT); break;
            default: break;
        }
    }
}

void EXTI_voidDisable(EXTI_ID A_EXTI_ID)
{
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: CLR_BIT(GICR_REG, EXTI0_ENABLE_BIT); break;
            case EXTI1: CLR_BIT(GICR_REG, EXTI1_ENABLE_BIT); break;
            case EXTI2: CLR_BIT(GICR_REG, EXTI2_ENABLE_BIT); break;
            default: break;
        }
    }
}

void EXTI_voidClearFlag(EXTI_ID A_EXTI_ID)
{
    if(A_EXTI_ID <= EXTI2)
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: SET_BIT(GIFR_REG, EXTI0_FLAG_BIT); break;
            case EXTI1: SET_BIT(GIFR_REG, EXTI1_FLAG_BIT); break;
            case EXTI2: SET_BIT(GIFR_REG, EXTI2_FLAG_BIT); break;
            default: break;
        }
    }
}

void EXTI_voidSetCallBack (EXTI_ID A_EXTI_ID, void(*ptrToFunc)(void))
{
    if((A_EXTI_ID <= EXTI2) && (ptrToFunc != NULL))
    {
        switch(A_EXTI_ID)
        {
            case EXTI0: EXTI0_Callback = ptrToFunc; break;
            case EXTI1: EXTI1_Callback = ptrToFunc; break;
            case EXTI2: EXTI2_Callback = ptrToFunc; break;
            default: break;
        }
    }
}

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

