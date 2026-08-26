
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

#include "../INCLUDE/HAL/LCD/LCD_Interface.h"
#include "../INCLUDE/HAL/LCD/LCD_Private.h"
#include "../INCLUDE/HAL/LCD/LCD_Config.h"

void LCD_voidInit (void)
{

    DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT, E_PIN, DIO_OUTPUT);

    _delay_ms(35);

    LCD_voidWriteCommand(LCD_CMD_FUNCTION_SET);
    _delay_us(50);

    LCD_voidWriteCommand(LCD_CMD_DISPLAY_CTRL);
    _delay_us(50);

    LCD_voidWriteCommand(LCD_CMD_CLEAR);
    _delay_ms(2);

    LCD_voidWriteCommand(LCD_CMD_ENTRY_MODE);
    _delay_us(50);
}

void LCD_voidWriteCommand ( u8 Copy_u8Command )
{

    DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, DIO_LOW);

    DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, DIO_LOW);

    DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);

    DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, DIO_HIGH);
    _delay_us(2);
    DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, DIO_LOW);

    _delay_us(50);
}

void LCD_voidWriteChar ( u8 Copy_u8Char )
{

    DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, DIO_HIGH);

    DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, DIO_LOW);

    DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Char);

    DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, DIO_HIGH);
    _delay_us(2);
    DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, DIO_LOW);

    _delay_us(50);
}

void LCD_voidWriteString ( const u8 *Copy_u8Arr )
{
    u8 i = 0;
    while (Copy_u8Arr[i] != '\0')
    {
        LCD_voidWriteChar(Copy_u8Arr[i]);
        i++;
    }
}

void LCD_voidWrite_s32Number ( s32 Copy_s32Number )
{
    u32 Local_u32Number;
    u8 Arr[11];
    u8 i;
    s16 j;

    if (Copy_s32Number == 0) {
        LCD_voidWriteChar('0');
        return;
    }

    if (Copy_s32Number < 0) {
        LCD_voidWriteChar('-');
        Local_u32Number = (u32)(-(s64)Copy_s32Number);
    } else {
        Local_u32Number = (u32)Copy_s32Number;
    }

    i = 0;

    while (Local_u32Number > 0) {
        Arr[i] = (Local_u32Number % 10) + '0';
        Local_u32Number /= 10;
        i++;
    }

    i--;
    for (j = i; j >= 0; j--) {
        LCD_voidWriteChar(Arr[j]);
    }
}

void LCD_voidGoTo_XY ( LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position )
{
    u8 lineIndex, colIndex;

    lineIndex = (u8)Copy_u8Line - 1;
    colIndex  = (u8)Copy_u8Position - 1;

    if (lineIndex > 1 || colIndex > 15) {
        return;
    }

    if (lineIndex == 0) {
        LCD_voidWriteCommand(LCD_DDRAM_ROW1_BASE + colIndex);
    } else {
        LCD_voidWriteCommand(LCD_DDRAM_ROW2_BASE + colIndex);
    }
}

void LCD_voidDrawPattern ( u8 Copy_u8Pattern_Number , const u8 *Copy_u8Arr_Pattern )
{
    u8 i;
    LCD_voidWriteCommand(Copy_u8Pattern_Number);
    for (i = 0; i < 8; i++) {
        LCD_voidWriteChar(Copy_u8Arr_Pattern[i]);
    }
}

void LCD_voidWritePattern ( u8 Copy_u8Pattern , LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position )
{

    u8 Local_u8CharCode = (Copy_u8Pattern - LCD_CGRAM_BASE) / 8;

    LCD_voidGoTo_XY(Copy_u8Line, Copy_u8Position);
    LCD_voidWriteChar(Local_u8CharCode);
}

void LCD_voidClearDisplay (void)
{
    LCD_voidWriteCommand(LCD_CMD_CLEAR);
    _delay_ms(2);
}

void LCD_voidShiftLeft (void)
{
    LCD_voidWriteCommand(LCD_CMD_SHIFT_DISPLAY_LEFT);
    _delay_us(50);
}

void LCD_voidShiftRight (void)
{
    LCD_voidWriteCommand(LCD_CMD_SHIFT_DISPLAY_RIGHT);
    _delay_us(50);
}

void LCD_voidClearGrid ( LCD_ROWS Copy_u8Line , LCD_COLS Copy_u8Position )
{
    LCD_voidGoTo_XY(Copy_u8Line, Copy_u8Position);
    LCD_voidWriteChar(' ');
}

void LCD_voidClearLine ( LCD_ROWS Copy_u8Line )
{
    LCD_COLS col;
    for (col = COL1; col <= COL16; col++) {
        LCD_voidGoTo_XY(Copy_u8Line, col);
        LCD_voidWriteChar(' ');
    }
}

