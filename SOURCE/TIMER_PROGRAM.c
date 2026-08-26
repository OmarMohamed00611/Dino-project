/*
 * TIMER_PROGRAM.c
 *
 *  Created on: Aug 25, 2026
 *      Author: alata
 */
#include "../INCLUDE/MCAL/TIMER/TIMER_INTERFACE.h"
#include "../INCLUDE/MCAL/TIMER/TIMER_PRIVATE.h"
#include "../INCLUDE/MCAL/TIMER/TIMER_CFG.h"

#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

void MTIMER0_voidInit(void)
{
#if TIMER0_MODE == NORMAL_MODE
    // Set wave generation to normal mode (WGM00 = 0, WGM01 = 0)
    CLR_BIT(TCCR0, 6);
    CLR_BIT(TCCR0, 3);

    // Turn on overflow interrupt
    SET_BIT(TIMSK, 0);
    CLR_BIT(TIMSK, 1);

    // Start timer by setting its clock
    TCCR0 &= 0b11111000;
    TCCR0 |= TIMER0_CLK_CFG;

#elif TIMER0_MODE == CTC_MODE
    // Set wave generation to CTC mode (WGM00 = 0, WGM01 = 1)
    CLR_BIT(TCCR0, 6);
    SET_BIT(TCCR0, 3);

    // Turn on CTC compare match interrupt
    CLR_BIT(TIMSK, 0);
    SET_BIT(TIMSK, 1);

    // Start timer by setting its clock and OC0 Pin mode
    TCCR0 &= 0b11001000; // Clear prescaler and COM bits
    TCCR0 |= (TIMER0_CLK_CFG | (TIMER0_CTC_OC0_PIN_MODE << 4));

#elif TIMER0_MODE == FAST_PWM_MODE
    // Set wave generation to Fast PWM mode (WGM00 = 1, WGM01 = 1)
    SET_BIT(TCCR0, 6);
    SET_BIT(TCCR0, 3);

    // Disable Interrupts (Hardware PWM on OC0 pin doesn't need software interrupts)
    CLR_BIT(TIMSK, 0);
    CLR_BIT(TIMSK, 1);

    // Start timer by setting its clock and OC0 Pin mode (Non-inverting / Inverting)
    TCCR0 &= 0b11001000; // Clear prescaler and COM bits
    TCCR0 |= (TIMER0_CLK_CFG | (TIMER0_PWM_OC0_PIN_MODE << 4));

#endif
}
