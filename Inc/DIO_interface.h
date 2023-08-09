#ifndef		DIO_INTERFACE_H
#define		DIO_INTERFACE_H
#include "Std_Types.h"
#include "Bit_Math.h"



void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction);
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value);
u8		DIO_u8GetPinValue(u8 port, u8 pin);

//void	DIO_u8GetPortValue(u8 port, u8 Direction);
//void 	DIO_Set_PortVal(u8 port ,u8 Copy_Val);

// output pin value

#define GPIO_PP_10MHZ	0b0001
#define GPIO_PP_2MHZ	0b0010
#define GPIO_PP_50MHZ	0b0011

#define GPIO_OD_10MHZ	0b0101
#define GPIO_OD_2MHZ	0b0110
#define GPIO_OD_50MHZ	0b0111


#define AFIO_PP_10MHZ	0b1001
#define AFIO_PP_2MHZ	0b1010
#define AFIO_PP_50MHZ	0b1011


#define AFIO_OD_10MHZ	0b1101
#define AFIO_OD_2MHZ	0b1110
#define AFIO_OD_50MHZ	0b1111

// direction pins

#define input_analog	ob0000
#define input_floating	0b0100
#define input_pullup	0b1000		//PxODR register must = 0
#define input_pulldown	0b1000		//PxODR register must = 1


#define pin0	0
#define pin1	1
#define pin2	2
#define pin3	3


#define pin4	4
#define pin5	5
#define pin6	6
#define pin7	7


#define pin8	8
#define pin9	9
#define pin10	10
#define pin11	11

#define pin12	12
#define pin13	13
#define pin14	14
#define pin15	15

#define HIGH	1
#define LOW		0


#define	PORTA	0

#define	PORTB	1

#define	PORTC	2



#endif
