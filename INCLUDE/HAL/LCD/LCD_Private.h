#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

#include "../../LIB/BIT_MATH.h"

#define LCD_CMD_FUNCTION_SET     CONC_BIT(0, 0, 1, LCD_DL, LCD_N, LCD_F, 0, 0)

#define LCD_CMD_DISPLAY_CTRL     CONC_BIT(0, 0, 0, 0, 1, LCD_D, LCD_C, LCD_B)

#define LCD_CMD_ENTRY_MODE       CONC_BIT(0, 0, 0, 0, 0, 1, LCD_ID, LCD_S)

#define LCD_CMD_CLEAR            0x01
#define LCD_CMD_RETURN_HOME      0x02

#define LCD_CMD_SHIFT_DISPLAY_LEFT   0x18
#define LCD_CMD_SHIFT_DISPLAY_RIGHT  0x1C

#define LCD_DDRAM_ROW1_BASE      0x80
#define LCD_DDRAM_ROW2_BASE      0xC0

#define LCD_CGRAM_BASE           0x40

#endif

