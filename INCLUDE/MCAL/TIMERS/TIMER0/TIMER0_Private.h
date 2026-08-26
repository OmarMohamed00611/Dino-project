#ifndef INCLUDE_MCAL_TIMERS_TIMER0_TIMER0_PRIVATE_H_
#define INCLUDE_MCAL_TIMERS_TIMER0_TIMER0_PRIVATE_H_

#include "../../../LIB/STD_TYPES.h"

#define TCCR0_REG    (*(volatile u8*)0x53)
#define TCNT0_REG    (*(volatile u8*)0x52)
#define OCR0_REG     (*(volatile u8*)0x5C)
#define TIMSK_REG    (*(volatile u8*)0x59)
#define TIFR_REG     (*(volatile u8*)0x58)

#define TIMER0_WGM01_BIT     3
#define TIMER0_COM00_BIT     4
#define TIMER0_COM01_BIT     5
#define TIMER0_WGM00_BIT     6

#define TIMER0_TOIE0_BIT     0
#define TIMER0_OCIE0_BIT     1

#define TIMER0_TOV0_BIT      0
#define TIMER0_OCF0_BIT      1

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif

