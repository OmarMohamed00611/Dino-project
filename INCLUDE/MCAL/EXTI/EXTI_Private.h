#ifndef INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_
#define INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_

#include "../../LIB/STD_TYPES.h"

#define MCUCR_REG    (*(volatile u8*)0x55)
#define MCUCSR_REG   (*(volatile u8*)0x54)
#define GICR_REG     (*(volatile u8*)0x5B)
#define GIFR_REG     (*(volatile u8*)0x5A)

#define SENSE_MODE_MASK 3

#define EXTI0_SENSE_MODE_BITS 0
#define EXTI1_SENSE_MODE_BITS 2
#define EXTI2_SENSE_MODE_BITS 6

#define EXTI0_ENABLE_BIT 6
#define EXTI1_ENABLE_BIT 7
#define EXTI2_ENABLE_BIT 5

#define EXTI0_FLAG_BIT 6
#define EXTI1_FLAG_BIT 7
#define EXTI2_FLAG_BIT 5

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif

