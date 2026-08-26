#ifndef INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_
#define INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

typedef enum{
    EXTI0 = 0,
    EXTI1,
    EXTI2
}EXTI_ID;

typedef enum{
    LOW_LEVEL = 0,
    ON_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
}EXTI_SENSE_MODE;

void EXTI_voidConfig      (EXTI_ID A_EXTI_ID, EXTI_SENSE_MODE A_EXTI_SENSE_MODE);
void EXTI_voidEnable      (EXTI_ID A_EXTI_ID);
void EXTI_voidDisable     (EXTI_ID A_EXTI_ID);
void EXTI_voidClearFlag   (EXTI_ID A_EXTI_ID);
void EXTI_voidSetCallBack (EXTI_ID A_EXTI_ID, void(*ptrToFunc)(void));

#endif

