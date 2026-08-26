#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

typedef enum {
    ROW1 = 1,
    ROW2
} LCD_ROWS;

typedef enum {
    COL1 = 1,
    COL2,
    COL3,
    COL4,
    COL5,
    COL6,
    COL7,
    COL8,
    COL9,
    COL10,
    COL11,
    COL12,
    COL13,
    COL14,
    COL15,
    COL16
} LCD_COLS;

#define PATTERN_0    0x40
#define PATTERN_1    0x48
#define PATTERN_2    0x50
#define PATTERN_3    0x58
#define PATTERN_4    0x60
#define PATTERN_5    0x68
#define PATTERN_6    0x70
#define PATTERN_7    0x78

void LCD_voidInit (void);
void LCD_voidWriteCommand ( u8 Copy_u8Command );
void LCD_voidWriteChar ( u8 Copy_u8Char );
void LCD_voidWriteString ( const u8 *Copy_u8Arr );
void LCD_voidWrite_s32Number ( s32 Copy_s32Number );
void LCD_voidGoTo_XY ( LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position );
void LCD_voidDrawPattern ( u8 Copy_u8Pattern_Number , const u8 *Copy_u8Arr_Pattern );
void LCD_voidWritePattern ( u8 Copy_u8Pattern , LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position );
void LCD_voidClearDisplay (void);
void LCD_voidShiftLeft (void);
void LCD_voidShiftRight (void);
void LCD_voidClearGrid ( LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position );
void LCD_voidClearLine ( LCD_ROWS Copy_u8Line );

#endif

