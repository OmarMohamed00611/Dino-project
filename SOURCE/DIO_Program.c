
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"

#include "../INCLUDE/MCAL/DIO/DIO_Interface.h"
#include "../INCLUDE/MCAL/DIO/DIO_Private.h"
#include "../INCLUDE/MCAL/DIO/DIO_Config.h"

void DIO_voidInit(void)
{

    DDRA_REG = CONC_BIT(PORTA_PIN7_DIRECTION, PORTA_PIN6_DIRECTION,
                        PORTA_PIN5_DIRECTION, PORTA_PIN4_DIRECTION,
                        PORTA_PIN3_DIRECTION, PORTA_PIN2_DIRECTION,
                        PORTA_PIN1_DIRECTION, PORTA_PIN0_DIRECTION);

    DDRB_REG = CONC_BIT(PORTB_PIN7_DIRECTION, PORTB_PIN6_DIRECTION,
                        PORTB_PIN5_DIRECTION, PORTB_PIN4_DIRECTION,
                        PORTB_PIN3_DIRECTION, PORTB_PIN2_DIRECTION,
                        PORTB_PIN1_DIRECTION, PORTB_PIN0_DIRECTION);

    DDRC_REG = CONC_BIT(PORTC_PIN7_DIRECTION, PORTC_PIN6_DIRECTION,
                        PORTC_PIN5_DIRECTION, PORTC_PIN4_DIRECTION,
                        PORTC_PIN3_DIRECTION, PORTC_PIN2_DIRECTION,
                        PORTC_PIN1_DIRECTION, PORTC_PIN0_DIRECTION);

    DDRD_REG = CONC_BIT(PORTD_PIN7_DIRECTION, PORTD_PIN6_DIRECTION,
                        PORTD_PIN5_DIRECTION, PORTD_PIN4_DIRECTION,
                        PORTD_PIN3_DIRECTION, PORTD_PIN2_DIRECTION,
                        PORTD_PIN1_DIRECTION, PORTD_PIN0_DIRECTION);

    PORTA_REG = CONC_BIT(PORTA_PIN7_VALUE, PORTA_PIN6_VALUE,
                         PORTA_PIN5_VALUE, PORTA_PIN4_VALUE,
                         PORTA_PIN3_VALUE, PORTA_PIN2_VALUE,
                         PORTA_PIN1_VALUE, PORTA_PIN0_VALUE);

    PORTB_REG = CONC_BIT(PORTB_PIN7_VALUE, PORTB_PIN6_VALUE,
                         PORTB_PIN5_VALUE, PORTB_PIN4_VALUE,
                         PORTB_PIN3_VALUE, PORTB_PIN2_VALUE,
                         PORTB_PIN1_VALUE, PORTB_PIN0_VALUE);

    PORTC_REG = CONC_BIT(PORTC_PIN7_VALUE, PORTC_PIN6_VALUE,
                         PORTC_PIN5_VALUE, PORTC_PIN4_VALUE,
                         PORTC_PIN3_VALUE, PORTC_PIN2_VALUE,
                         PORTC_PIN1_VALUE, PORTC_PIN0_VALUE);

    PORTD_REG = CONC_BIT(PORTD_PIN7_VALUE, PORTD_PIN6_VALUE,
                         PORTD_PIN5_VALUE, PORTD_PIN4_VALUE,
                         PORTD_PIN3_VALUE, PORTD_PIN2_VALUE,
                         PORTD_PIN1_VALUE, PORTD_PIN0_VALUE);
}

void DIO_voidSetPinDirection(u8 Copy_u8PortNumber,
                             u8 Copy_u8PinNumber,
                             u8 Copy_u8Direction)
{
    if (Copy_u8PortNumber > PORTD || Copy_u8PinNumber > PIN7)
    {
        return;
    }

    if (Copy_u8Direction == DIO_INPUT)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: CLR_BIT(DDRA_REG, Copy_u8PinNumber); break;
            case PORTB: CLR_BIT(DDRB_REG, Copy_u8PinNumber); break;
            case PORTC: CLR_BIT(DDRC_REG, Copy_u8PinNumber); break;
            case PORTD: CLR_BIT(DDRD_REG, Copy_u8PinNumber); break;
        }
    }
    else if (Copy_u8Direction == DIO_OUTPUT)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: SET_BIT(DDRA_REG, Copy_u8PinNumber); break;
            case PORTB: SET_BIT(DDRB_REG, Copy_u8PinNumber); break;
            case PORTC: SET_BIT(DDRC_REG, Copy_u8PinNumber); break;
            case PORTD: SET_BIT(DDRD_REG, Copy_u8PinNumber); break;
        }
    }
}

void DIO_voidSetPortDirection(u8 Copy_u8PortNumber,
                              u8 Copy_u8Direction)
{
    if (Copy_u8PortNumber > PORTD)
    {
        return;
    }

    if (Copy_u8Direction == DIO_INPUT)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: DDRA_REG = 0x00; break;
            case PORTB: DDRB_REG = 0x00; break;
            case PORTC: DDRC_REG = 0x00; break;
            case PORTD: DDRD_REG = 0x00; break;
        }
    }
    else if (Copy_u8Direction == DIO_OUTPUT)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: DDRA_REG = 0xFF; break;
            case PORTB: DDRB_REG = 0xFF; break;
            case PORTC: DDRC_REG = 0xFF; break;
            case PORTD: DDRD_REG = 0xFF; break;
        }
    }
}

void DIO_voidSetPinValue(u8 Copy_u8PortNumber,
                         u8 Copy_u8PinNumber,
                         u8 Copy_u8Value)
{
    if (Copy_u8PortNumber > PORTD || Copy_u8PinNumber > PIN7)
    {
        return;
    }

    if (Copy_u8Value == DIO_LOW)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: CLR_BIT(PORTA_REG, Copy_u8PinNumber); break;
            case PORTB: CLR_BIT(PORTB_REG, Copy_u8PinNumber); break;
            case PORTC: CLR_BIT(PORTC_REG, Copy_u8PinNumber); break;
            case PORTD: CLR_BIT(PORTD_REG, Copy_u8PinNumber); break;
        }
    }
    else if (Copy_u8Value == DIO_HIGH)
    {
        switch (Copy_u8PortNumber)
        {
            case PORTA: SET_BIT(PORTA_REG, Copy_u8PinNumber); break;
            case PORTB: SET_BIT(PORTB_REG, Copy_u8PinNumber); break;
            case PORTC: SET_BIT(PORTC_REG, Copy_u8PinNumber); break;
            case PORTD: SET_BIT(PORTD_REG, Copy_u8PinNumber); break;
        }
    }
}

void DIO_voidSetPortValue(u8 Copy_u8PortNumber,
                          u8 Copy_u8Value)
{
    if (Copy_u8PortNumber > PORTD)
    {
        return;
    }

    switch (Copy_u8PortNumber)
    {
        case PORTA: PORTA_REG = Copy_u8Value; break;
        case PORTB: PORTB_REG = Copy_u8Value; break;
        case PORTC: PORTC_REG = Copy_u8Value; break;
        case PORTD: PORTD_REG = Copy_u8Value; break;
    }
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortNumber,
                     u8 Copy_u8PinNumber)
{
    u8 Local_u8Variable = 0;

    if (Copy_u8PortNumber > PORTD || Copy_u8PinNumber > PIN7)
    {
        return Local_u8Variable;
    }

    switch (Copy_u8PortNumber)
    {
        case PORTA: Local_u8Variable = GET_BIT(PINA_REG, Copy_u8PinNumber); break;
        case PORTB: Local_u8Variable = GET_BIT(PINB_REG, Copy_u8PinNumber); break;
        case PORTC: Local_u8Variable = GET_BIT(PINC_REG, Copy_u8PinNumber); break;
        case PORTD: Local_u8Variable = GET_BIT(PIND_REG, Copy_u8PinNumber); break;
    }

    return Local_u8Variable;
}

u8 DIO_u8GetPortValue(u8 Copy_u8PortNumber)
{
    u8 Local_u8Variable = 0;

    if (Copy_u8PortNumber > PORTD)
    {
        return Local_u8Variable;
    }

    switch (Copy_u8PortNumber)
    {
        case PORTA: Local_u8Variable = PINA_REG; break;
        case PORTB: Local_u8Variable = PINB_REG; break;
        case PORTC: Local_u8Variable = PINC_REG; break;
        case PORTD: Local_u8Variable = PIND_REG; break;
    }

    return Local_u8Variable;
}

void DIO_voidTogglePinValue(u8 Copy_u8PortNumber,
                            u8 Copy_u8PinNumber)
{
    if (Copy_u8PortNumber > PORTD || Copy_u8PinNumber > PIN7)
    {
        return;
    }

    switch (Copy_u8PortNumber)
    {
        case PORTA: TOGGLE_BIT(PORTA_REG, Copy_u8PinNumber); break;
        case PORTB: TOGGLE_BIT(PORTB_REG, Copy_u8PinNumber); break;
        case PORTC: TOGGLE_BIT(PORTC_REG, Copy_u8PinNumber); break;
        case PORTD: TOGGLE_BIT(PORTD_REG, Copy_u8PinNumber); break;
    }
}

void DIO_voidTogglePortValue(u8 Copy_u8PortNumber)
{
    if (Copy_u8PortNumber > PORTD)
    {
        return;
    }

    switch (Copy_u8PortNumber)
    {
        case PORTA: PORTA_REG ^= 0xFF; break;
        case PORTB: PORTB_REG ^= 0xFF; break;
        case PORTC: PORTC_REG ^= 0xFF; break;
        case PORTD: PORTD_REG ^= 0xFF; break;
    }
}

void DIO_voidConfig_Pull_Up_Pin(u8 Copy_u8PortNumber,
                                u8 Copy_u8PinNumber,
                                u8 Copy_u8PullUpStatus)
{
    if (Copy_u8PortNumber > PORTD || Copy_u8PinNumber > PIN7)
    {
        return;
    }

    if (Copy_u8PullUpStatus == DIO_PULLUP)
    {
        DIO_voidSetPinValue(Copy_u8PortNumber, Copy_u8PinNumber, DIO_HIGH);
    }
    else if (Copy_u8PullUpStatus == DIO_FLOATING)
    {
        DIO_voidSetPinValue(Copy_u8PortNumber, Copy_u8PinNumber, DIO_LOW);
    }
}

void DIO_voidConfig_Pull_Up_Port(u8 Copy_u8PortNumber,
                                 u8 Copy_u8PullUpStatus)
{
    if (Copy_u8PortNumber > PORTD)
    {
        return;
    }

    if (Copy_u8PullUpStatus == DIO_PULLUP)
    {
        DIO_voidSetPortValue(Copy_u8PortNumber, DIO_HIGH);
    }
    else if (Copy_u8PullUpStatus == DIO_FLOATING)
    {
        DIO_voidSetPortValue(Copy_u8PortNumber, DIO_LOW);
    }
}

