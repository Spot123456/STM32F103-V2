#ifndef		BIT_MATH_H
#define		BIT_MATH_H

#define		SET_BIT(REG,BIT)		(REG|=  (1<<BIT))
#define		CLR_BIT(REG,BIT)		(REG&= ~(1<<BIT))
#define		TOG_BIT(REG,BIT)		(REG^=  (1<<BIT))
#define		GET_BIT(REG,BIT)		((REG>>BIT)&0x01)

//#define		BIT_LOW					((u8)0)




/*
typedef enum
{
	LOW ,
	HIGH ,
}EN_DIO_VAL;


typedef enum
{
	PORTA ,
	PORTB ,
	PORTC ,
}EN_DIO_PORTID;
typedef enum
{ pin0,
	pin1,
	pin2,
	pin3,
	pin4,
	pin5,
	pin6,
	pin7,
	pin8,
	pin9,
	pin10,
	pin11,
	pin12,
	pin13,
	pin14,
	pin15,

}DIO_Pin_ID;
*/

#endif
