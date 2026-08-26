#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
#include "KEYPAD_Config.h"

void KEYPAD_voidInit(void);
u8 KEYPAD_u8GetPressedKey(void);

#endif

