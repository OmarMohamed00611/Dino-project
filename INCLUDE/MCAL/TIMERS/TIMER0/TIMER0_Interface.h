#ifndef INCLUDE_MCAL_TIMERS_TIMER0_TIMER0_INTERFACE_H_
#define INCLUDE_MCAL_TIMERS_TIMER0_TIMER0_INTERFACE_H_

#include "../../../LIB/STD_TYPES.h"

#define NORMAL_MODE          0
#define PHASE_CORRECT_MODE   1
#define CTC_MODE             2
#define FAST_PWM_MODE        3

#define NORMAL_DIO_PIN       0
#define TOGGLE_CTC           1
#define CLR_CTC              2
#define SET_CTC              3

#define NON_INVERTING_PWM    0
#define INVERTING_PWM        1

void TIMER0_voidInit(void);
void TIMER0_voidSetOCR0Value(u8 A_u8OCR0Value);
void TIMER0_voidSetPreloadValue(u8 A_u8NoOfTicks);
void TIMER0_voidStopTimer(void);
void TIMER0_voidSetOVFCallback(void (*A_PtrToFunc)(void));
void TIMER0_voidSetCTCCallback(void (*A_PtrToFunc)(void));
void TIMER0_voidSetPWMDutyCycle(u8 Copy_u8DutyCycle);

#endif

