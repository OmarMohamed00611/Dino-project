/*
 * GI_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: alata
 */


#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

// MCAL Directives
#include "../INCLUDE/MCAL/GLOBAL_INTERRUPT/GI_INTERFACE.h"
#include "../INCLUDE/MCAL/GLOBAL_INTERRUPT/GI_PRIVATE.h"
#include "../INCLUDE/MCAL/GLOBAL_INTERRUPT/GI_CFG.h"

void MGI_voidEnable(void)
{

    SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
}

void MGI_voidDisable(void)
{

    CLR_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
}
