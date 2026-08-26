/*
 * KEYPAD_PROGRAM.h
 *
 *  Created on: Aug 22, 2026
 *      Author: alata
 */

#include <util/delay.h>
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"

#include "../INCLUDE/HAL/KEYPAD/KEYPAD_CFG.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_PRIVATE.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"

static u8 Global_u8ArrOfKeyValues[ROW_NO][COL_NO] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};
static u8 G_u8ArrofRows[ROW_NO] = KEYPAD_ROWS;
static u8 G_u8ArrofCols[COL_NO] = KEYPAD_COLS;

u8 HKEYPAD_u8GetPressedKey(void)
{
    u8 L_u8KeyValue = KEYPAD_NOT_PRESSED_VAL;
    u8 L_u8RowCounter = 0;
    u8 L_u8ColCounter = 0;
    u8 L_u8PinValue;
    u8 L_u8Flag = FLAG_DOWN;

    for (L_u8RowCounter = 0; L_u8RowCounter < ROW_NO; L_u8RowCounter++)
    {
        MDIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrofRows[L_u8RowCounter], KEYPAD_PRESSED);

        for (L_u8ColCounter = 0; L_u8ColCounter < COL_NO; L_u8ColCounter++)
        {
            L_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT, G_u8ArrofCols[L_u8ColCounter]);

            if (L_u8PinValue == KEYPAD_PRESSED)
            {
                _delay_ms(KEYPAD_DEBOUNCE_DELAY);
                L_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT, G_u8ArrofCols[L_u8ColCounter]);

                if (L_u8PinValue == KEYPAD_PRESSED)
                {
                    while (L_u8PinValue == KEYPAD_PRESSED)
                    {
                        L_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT, G_u8ArrofCols[L_u8ColCounter]);
                    }

                    L_u8KeyValue = Global_u8ArrOfKeyValues[L_u8RowCounter][L_u8ColCounter];
                    L_u8Flag = FLAG_UP;
                    break;
                }
            }
        }


        MDIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrofRows[L_u8RowCounter], KEYPAD_NOT_PRESSED);

        if (L_u8Flag == FLAG_UP)
        {
            break;
        }
    }

    return L_u8KeyValue;
}
