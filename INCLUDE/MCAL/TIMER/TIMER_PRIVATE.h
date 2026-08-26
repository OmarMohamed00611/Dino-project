/*
 * TIMER_PRIVATE.h
 *
 *  Created on: Aug 25, 2026
 *      Author: alata
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_
#define INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_

/* Timer0 Hardware Registers */
#define TCCR0   (*(volatile u8 *) 0x53)
#define TCNT0   (*(volatile u8 *) 0x52)
#define OCR0    (*(volatile u8 *) 0x5C)
#define TIMSK   (*(volatile u8 *) 0x59)
#define TIFR    (*(volatile u8 *) 0x58)

/* TCCR0 Bits */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TIMSK Bits (Interrupt Mask Register) */
#define OCIE0   1   // Output Compare Match Interrupt Enable
#define TOIE0   0   // Timer/Counter0 Overflow Interrupt Enable

/* TIFR Bits (Interrupt Flag Register) */
#define OCF0    1   // Output Compare Flag
#define TOV0    0   // Timer/Counter0 Overflow Flag

#ifndef NULL
#define NULL    0
#endif

#endif /* INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_ */
