#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_CONFIG_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_CONFIG_H_

#include "../../LIB/STD_TYPES.h"

#define KEYPAD_PRESSED    0
#define KEY_NOT_PRESSED   0xFF

#define ROW_NO            4
#define COL_NO            4

#define Flag_DOWN         0
#define Flag_UP           1

#define KEYPAD_PORT       PORTB

typedef enum { KEYPAD_ROW0 = 0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3 } KEYPAD_ROW_PINS;
typedef enum { KEYPAD_COL0 = 4, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3 } KEYPAD_COL_PINS;

#define KEYPAD_ROWS {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3}
#define KEYPAD_COLS {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3}

#define KEYPAD_KEYS {   \
	{'7','8','9','/'},  \
	{'4','5','6','*'},  \
	{'1','2','3','-'},  \
	{'C','0','=','+'}}

#define KEYPAD_DEBOUNCE_DELAY 30

extern u8 Global_u8ArrOfKeyValues[ROW_NO][COL_NO];

#endif

