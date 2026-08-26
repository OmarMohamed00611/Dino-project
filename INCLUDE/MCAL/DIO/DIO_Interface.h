#ifndef INCLUDE_MCAL_DIO_DIO_INTERFACE_H_
#define INCLUDE_MCAL_DIO_DIO_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

typedef enum { PIN0 = 0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7 } DIO_PINS;
typedef enum { PORTA = 0, PORTB, PORTC, PORTD } DIO_PORTS;
typedef enum { DIO_INPUT = 0, DIO_OUTPUT } PIN_DIRECTION;
typedef enum { DIO_LOW = 0, DIO_HIGH } PIN_STATUS;
typedef enum { DIO_FLOATING = 0, DIO_PULLUP } PIN_INPUT_MODE;

void DIO_voidInit(void);
void DIO_voidSetPinDirection(u8 Copy_u8PortNumber, u8 Copy_u8PinNumber, u8 Copy_u8Direction);
void DIO_voidSetPortDirection(u8 Copy_u8PortNumber, u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8PortNumber, u8 Copy_u8PinNumber, u8 Copy_u8Value);
void DIO_voidSetPortValue(u8 Copy_u8PortNumber, u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 Copy_u8PortNumber, u8 Copy_u8PinNumber);
u8 DIO_u8GetPortValue(u8 Copy_u8PortNumber);
void DIO_voidTogglePinValue(u8 Copy_u8PortNumber, u8 Copy_u8PinNumber);
void DIO_voidTogglePortValue(u8 Copy_u8PortNumber);
void DIO_voidConfig_Pull_Up_Pin(u8 Copy_u8PortNumber, u8 Copy_u8PinNumber, u8 Copy_u8PullUpStatus);
void DIO_voidConfig_Pull_Up_Port(u8 Copy_u8PortNumber, u8 Copy_u8PullUpStatus);

#endif

