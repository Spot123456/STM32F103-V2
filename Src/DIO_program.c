#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"DIO_interface.h"
#include	"DIO_private.h"
//#include	"DIO_config.h"






void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction)
{
	if(port<3 && pin <16)
	{
		if(pin <8)
		{
			switch(port)
			{
			case PORTA:
				GPIOA->GPIOx_CRL&=~((0b1111)<<(pin*4));
				GPIOA->GPIOx_CRL|=((Direction)<<(pin*4));
				break;
			case PORTB:
				GPIOB->GPIOx_CRL&=~((0b1111)<<(pin*4))	;
				GPIOB->GPIOx_CRL|=((Direction)<<(pin*4));
				break;
			case PORTC:
				GPIOC->GPIOx_CRL&=~((0b1111)<<(pin*4));
				GPIOC->GPIOx_CRL|=((Direction)<<(pin*4));
				break;

			default: //error type
				break;

			}

		}

		else if (pin<16)
		{
			pin-=8;
			switch (Direction)
			{
			case PORTA:
				GPIOA->GPIOx_CRH &=~((0b1111)<<(pin*4));
				GPIOA->GPIOx_CRH |=((Direction)<<(pin*4));
				break;

			case PORTB:
				GPIOB->GPIOx_CRH &=~((0b1111)<<(pin*4));
				GPIOB->GPIOx_CRH |=((Direction)<<(pin*4));
				break;

			case PORTC:
				GPIOC->GPIOx_CRH &=~((0b1111)<<(pin*4));
				GPIOC->GPIOx_CRH |=((Direction)<<(pin*4));
				break;

			}
		}
	}
	else {/* return Error*/}

}
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value)
{
	if(port<3 && pin<16)
	{
		if(Value== HIGH)
		{
			switch(port)
			{
			case PORTA: GPIOA->GPIOx_BSRR=(1<<pin); break;
			case PORTB: GPIOB->GPIOx_BSRR=(1<<pin); break;
			case PORTC: GPIOC->GPIOx_BSRR=(1<<pin); break;
			}
		}
		else if(Value== LOW)
		{
			switch(port)
			{
			case PORTA: GPIOA->GPIOx_BRR=(1<<pin); break;
			case PORTB: GPIOB->GPIOx_BRR=(1<<pin); break;
			case PORTC: GPIOC->GPIOx_BRR=(1<<pin); break;
			}
		}
	}
	else {/* return error */ }
	

}

u8 DIO_u8GetPinValue(u8 port, u8 pin)

{
	u8 val=0x55;
	if(port<3 && pin <16)
	{

		switch (port)
		{
		case PORTA :	val= GET_BIT(GPIOA->GPIOx_IDR,pin);	break;
		case PORTB :	val= GET_BIT(GPIOB->GPIOx_IDR,pin);	break;
		case PORTC :	val= GET_BIT(GPIOC->GPIOx_IDR,pin);	break;
		}
	}
	return	val;
}


