/*
 * KEYPAD_CFG.h
 *
 *  Created on: Aug 22, 2026
 *      Author: alata
 */

#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_


#define KEYPAD_PORT          PORTB

#define KEYPAD_ROW0          PIN0
#define KEYPAD_ROW1          PIN1
#define KEYPAD_ROW2          PIN2
#define KEYPAD_ROW3          PIN3

#define KEYPAD_COL0          PIN4
#define KEYPAD_COL1          PIN5
#define KEYPAD_COL2          PIN6
#define KEYPAD_COL3          PIN7


#define KEYPAD_ROWS          {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3}
#define KEYPAD_COLS          {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3}


#define KEYPAD_DEBOUNCE_DELAY 30


#endif /* INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_ */
