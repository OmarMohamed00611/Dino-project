/*
 * TIMER_CFG.h
 *
 *  Created on: Aug 25, 2026
 *      Author: alata
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_CFG_H_
#define INCLUDE_MCAL_TIMER_TIMER_CFG_H_

/*
 * Choose Timer0 Mode:
 * NORMAL_MODE - CTC_MODE - FAST_PWM_MODE - PHASE_CORRECT_MODE
 */
#define TIMER0_MODE  FAST_PWM_MODE

/* Choose Timer0 Clock (Prescaler): e.g., 2 for DIV_8, 3 for DIV_64 */
#define TIMER0_CLK_CFG  2

/* Choose OC0 Pin Mode for CTC: NORMAL_DIO_PIN, TOGGLE_CTC, CLR_CTC, SET_CTC */
#define TIMER0_CTC_OC0_PIN_MODE  NORMAL_DIO_PIN

/* Choose OC0 Pin Mode for Fast PWM: FAST_PWM_NON_INVERTING, FAST_PWM_INVERTING */
#define TIMER0_PWM_OC0_PIN_MODE  FAST_PWM_NON_INVERTING

#endif /* INCLUDE_MCAL_TIMER_TIMER_CFG_H_ */
