
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/DIO/DIO_Interface.h"

#include "../INCLUDE/HAL/KEYPAD/KEYPAD_Config.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_Private.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_Interface.h"

#include <util/delay.h>

u8 Global_u8ArrOfKeyValues[ROW_NO][COL_NO] = KEYPAD_KEYS;

static u8 G_u8ArrOfRows[ROW_NO] = KEYPAD_ROWS;
static u8 G_u8ArrOfCols[COL_NO] = KEYPAD_COLS;

void KEYPAD_voidInit(void)
{
    u8 L_u8Counter;

    for (L_u8Counter = 0; L_u8Counter < ROW_NO; L_u8Counter++)
    {
        DIO_voidSetPinDirection(KEYPAD_PORT, G_u8ArrOfRows[L_u8Counter], DIO_OUTPUT);
        DIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8Counter], DIO_HIGH);
    }

    for (L_u8Counter = 0; L_u8Counter < COL_NO; L_u8Counter++)
    {
        DIO_voidSetPinDirection(KEYPAD_PORT, G_u8ArrOfCols[L_u8Counter], DIO_INPUT);
        DIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrOfCols[L_u8Counter], DIO_HIGH);
    }
}

u8 KEYPAD_u8GetPressedKey(void)
{
    u8 L_u8KeyValue = KEY_NOT_PRESSED;
    u8 L_u8RowCounter;
    u8 L_u8ColCounter;
    u8 L_u8PinValue;
    u8 L_u8Flag = Flag_DOWN;

    for (L_u8RowCounter = 0; L_u8RowCounter < ROW_NO; L_u8RowCounter++)
    {
        DIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8RowCounter], DIO_LOW);
        _delay_ms(1);

        for (L_u8ColCounter = 0; L_u8ColCounter < COL_NO; L_u8ColCounter++)
        {
            L_u8PinValue = DIO_u8GetPinValue(KEYPAD_PORT, G_u8ArrOfCols[L_u8ColCounter]);
            if (L_u8PinValue == KEYPAD_PRESSED)
            {
                _delay_ms(KEYPAD_DEBOUNCE_DELAY);
                L_u8PinValue = DIO_u8GetPinValue(KEYPAD_PORT, G_u8ArrOfCols[L_u8ColCounter]);
                if (L_u8PinValue == KEYPAD_PRESSED)
                {

                    while (DIO_u8GetPinValue(KEYPAD_PORT, G_u8ArrOfCols[L_u8ColCounter]) == KEYPAD_PRESSED);
                    _delay_ms(KEYPAD_DEBOUNCE_DELAY);

                    L_u8KeyValue = Global_u8ArrOfKeyValues[L_u8RowCounter][L_u8ColCounter];
                    L_u8Flag = Flag_UP;
                    break;
                }
            }
        }

        DIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8RowCounter], DIO_HIGH);

        if (L_u8Flag == Flag_UP)
        {
            break;
        }
    }

    if (L_u8Flag == Flag_DOWN)
    {
        _delay_ms(10);
    }

    return L_u8KeyValue;
}

