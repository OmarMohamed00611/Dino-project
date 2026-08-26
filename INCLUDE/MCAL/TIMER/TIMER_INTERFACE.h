/*
 * TIMER_INTERFACE.h
 *
 *  Created on: Aug 25, 2026
 *      Author: alata
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_
#define INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_

// Modes of Timer 8Bits
#define NORMAL_MODE          0
#define PHASE_CORRECT_MODE   1
#define CTC_MODE             2
#define FAST_PWM_MODE        3

// CTC OC0 Pin Modes
#define NORMAL_DIO_PIN       0
#define TOGGLE_CTC           1
#define CLR_CTC              2
#define SET_CTC              3

// Fast PWM OC0 Pin Modes
#define FAST_PWM_NON_INVERTING  2
#define FAST_PWM_INVERTING      3

#endif /* INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_ */
