/* LCD_PROGRAM*/
/* LCD_PROGRAM.c */
#include <util/delay.h>
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../INCLUDE/HAL/LCD/LCD_PRIVATE.h"
#include "../INCLUDE/HAL/LCD/LCD_CFG.h"

static void LCD_voidSendEnablePulse(void)
{
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(2);
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_LOW);
}

void LCD_voidWriteHalfPort(u8 Copy_u8Value)
{
    MDIO_voidSetPinValue(LCD_DATA_PORT, PIN4, GET_BIT(Copy_u8Value, 0));
    MDIO_voidSetPinValue(LCD_DATA_PORT, PIN5, GET_BIT(Copy_u8Value, 1));
    MDIO_voidSetPinValue(LCD_DATA_PORT, PIN6, GET_BIT(Copy_u8Value, 2));
    MDIO_voidSetPinValue(LCD_DATA_PORT, PIN7, GET_BIT(Copy_u8Value, 3));
}

void LCD_voidWriteCommand(u8 Copy_u8Command)
{
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);

    // إرسال الجزء الأعلى (High Nibble)
    LCD_voidWriteHalfPort(Copy_u8Command >> 4);
    LCD_voidSendEnablePulse();

    // إرسال الجزء الأسفل (Low Nibble)
    LCD_voidWriteHalfPort(Copy_u8Command);
    LCD_voidSendEnablePulse();
}

void LCD_voidWriteChar(u8 Copy_u8Char)
{
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_HIGH);
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);

    // إرسال الجزء الأعلى
    LCD_voidWriteHalfPort(Copy_u8Char >> 4);
    LCD_voidSendEnablePulse();

    // إرسال الجزء الأسفل
    LCD_voidWriteHalfPort(Copy_u8Char);
    LCD_voidSendEnablePulse();
}

void LCD_voidInit(void)
{
    _delay_ms(35);

    // أوامر تهيئة وضع 4-Bit القياسية
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
    MDIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_LOW);

    LCD_voidWriteHalfPort(0b0010); // Function set for 4-bit
    LCD_voidSendEnablePulse();

    LCD_voidWriteCommand(FS_4BIT_2LINES_5x7);
    _delay_ms(1);

    LCD_voidWriteCommand(DIS_ON_NO_CURSER);
    _delay_ms(1);

    LCD_voidWriteCommand(DIS_CLEAR);
    _delay_ms(2);

    LCD_voidWriteCommand(ENTRY_MODE_INCREASE_NO_SHIFT);
}

void LCD_voidWriteString(u8 *Copy_u8Arr)
{
    while(*Copy_u8Arr > 0)
    {
        LCD_voidWriteChar(*Copy_u8Arr++);
    }
}

void LCD_voidClearDisplay(void)
{
    LCD_voidWriteCommand(DIS_CLEAR);
    _delay_ms(2);
}

void LCD_voidGoTo_XY(u8 Copy_u8Line, u8 Copy_u8Position)
{
    if(Copy_u8Line == LINE_1)
    {
        LCD_voidWriteCommand(0x80 + Copy_u8Position);
    }
    else if(Copy_u8Line == LINE_2)
    {
        LCD_voidWriteCommand(0xC0 + Copy_u8Position);
    }
    _delay_ms(1);
}

void LCD_voidWrite_u32Number(u32 Copy_u32Number)
{
    u32 local_u32Number = 1;
    if(Copy_u32Number == 0)
    {
        LCD_voidWriteChar('0');
        return;
    }
    while(Copy_u32Number != 0)
    {
        local_u32Number = ((local_u32Number * 10) + (Copy_u32Number % 10));
        Copy_u32Number /= 10;
    }
    while(local_u32Number != 1)
    {
        LCD_voidWriteChar((local_u32Number % 10) + 48);
        local_u32Number /= 10;
    }
}

void LCD_voidDrawPattern(u8 Copy_u8PatternNumber, u8* Copy_u8PatternArray)
{
    u8 local_u8CGRAMAddress = Copy_u8PatternNumber * 8;
    LCD_voidWriteCommand(local_u8CGRAMAddress | 0x40);

    for (u8 i = 0; i < 8; i++)
    {
        LCD_voidWriteChar(Copy_u8PatternArray[i]);
    }
    LCD_voidWriteCommand(0x80);
}
