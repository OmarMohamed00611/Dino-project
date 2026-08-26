#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/DIO/DIO_Interface.h"
#include "../INCLUDE/MCAL/TIMERS/TIMER0/TIMER0_Interface.h"
#include "../INCLUDE/MCAL/GI/GI_Interface.h"

#define OVFS_FOR_HALF_SECOND   1953

void Blink_LED(void)
{
    static u16 L_u16OVFCounter = 0;

    L_u16OVFCounter++;
    if (L_u16OVFCounter >= OVFS_FOR_HALF_SECOND)
    {
        DIO_voidTogglePinValue(PORTB, PIN0);
        L_u16OVFCounter = 0;
    }
}

int main(void)
{
    DIO_voidInit();

    DIO_voidSetPinDirection(PORTB, PIN0, DIO_OUTPUT);
    DIO_voidSetPinValue(PORTB, PIN0, DIO_LOW);

    TIMER0_voidInit();

    TIMER0_voidSetPreloadValue(0);
    TIMER0_voidSetOVFCallback(Blink_LED);

    GI_VoidSetStatus(GI_ON);

    while (1)
    {
    }

    return 0;
}

