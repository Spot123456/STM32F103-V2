


#ifndef		NULL
#define		NULL			((void *)0)
#endif
#include "Std_Types.h"
#include "Bit_math.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"





//static	void	(*EXTI0_CallBack)	(void)	= NULL;

static	void (* PF_CallBack)(void)= NULL;

void		EXTI_voidInit(u8 Port,u8 line_num)
{
	// datasheet page 191 ref manual
	// to select the input for extI0 : port a,b,...
	// if PORTA
	//EXTI_voidDisableInt(0);
#ifndef		 AFIO_EXTICR
#define		 AFIO_EXTICR1_ADD	(0x40010000) // this address of GPIO (AFIO)
#define 	 AFIO_EXTICR1 *((u32*)(AFIO_EXTICR1_ADD+0x08))
#define 	 AFIO_EXTICR2 *((u32*)(AFIO_EXTICR1_ADD+0x0C))
#define 	 AFIO_EXTICR3 *((u32*)(AFIO_EXTICR1_ADD+0x10))
#define 	 AFIO_EXTICR4 *((u32*)(AFIO_EXTICR1_ADD+0x14))
#endif

	if(line_num<4)
	{
		switch(Port)
		{
		case	PORTA:	AFIO_EXTICR1&=~(0b1111<<line_num*4);
						AFIO_EXTICR1|=(0<<line_num*4);
						break;

		case	PORTB:	AFIO_EXTICR1&=~(0b1111<<line_num*4);
						AFIO_EXTICR1|=(1<<line_num*4);
						break;

		case	PORTC:	AFIO_EXTICR1&=~(0b1111<<line_num*4);
						AFIO_EXTICR1|=(2<<line_num*4);
						break;
		}

	}
	else if(line_num<8)
	{
	line_num-=4;
		switch(Port)
		{
		case	PORTA:	AFIO_EXTICR2&=~(0b1111<<line_num*4);
						AFIO_EXTICR2|=(0<<line_num*4);
						break;

		case	PORTB:	AFIO_EXTICR2&=~(0b1111<<line_num*4);
						AFIO_EXTICR2|=(1<<line_num*4);
						break;

		case	PORTC:	AFIO_EXTICR2&=~(0b1111<<line_num*4);
						AFIO_EXTICR2|=(2<<line_num*4);
						break;
		}

	}
	else if(line_num<12)
	{
		line_num-=8;
		switch(Port)
		{
		case	PORTA:	AFIO_EXTICR3 &=~(0b1111<<line_num*4);
						AFIO_EXTICR3 |=(0<<line_num*4);
						break;

		case	PORTB:	AFIO_EXTICR3 &=~(0b1111<<line_num*4);
						AFIO_EXTICR3 |=(1<<line_num*4);
						break;

		case	PORTC:	AFIO_EXTICR3 &=~(0b1111<<line_num*4);
						AFIO_EXTICR3 |=(2<<line_num*4);
						break;
		}

	}
	else if(line_num<16)
	{
		line_num-=12;
		switch(Port)
		{
		case	PORTA:	AFIO_EXTICR4 &=~(0b1111<<line_num*4);
						AFIO_EXTICR4 |=(0<<line_num*4);
						break;

		case	PORTB:	AFIO_EXTICR4 &=~(0b1111<<line_num*4);
						AFIO_EXTICR4 |=(1<<line_num*4);
						break;

		case	PORTC:	AFIO_EXTICR4 &=~(0b1111<<line_num*4);
						AFIO_EXTICR4 |=(2<<line_num*4);
						break;
		}

	}
	else{/*worng line input */}
}
void		EXTI_voidEnableInt(u8 line_num)
{
	EXTI->IMR|=(1<<line_num);

}
void		EXTI_voidDisableInt(u8 line_num)
{
	EXTI->IMR&=~(1<<line_num);
}

void		EXTI_voidEnableSWI(u8 line_num)
{
	EXTI->SWIER|=(1<<line_num);
}
void		EXTI_voidChangeSenseMode(u8 line_num, u8 Sense_Mode)
{
	switch (Sense_Mode)
	{

		case	RISING_Edge:	EXTI->RTSR|=(1<<line_num);
								EXTI->FTSR&=~(1<<line_num);
								break;

		case	Faling_Edge:	CLR_BIT(EXTI->RTSR,line_num);
								SET_BIT(EXTI->FTSR,line_num);
								break;

		case	IOC_Edge:		CLR_BIT(EXTI->RTSR,line_num);
								SET_BIT(EXTI->FTSR,line_num);
								break;
	}
	SET_BIT(EXTI -> IMR,line_num);
}

void		EXTI0_voidSetCallBack(void (*Fptr)(void))
{
	if(Fptr != NULL)
	{
		PF_CallBack=Fptr;
	}
}

void	EXTI0_IRQHandler(void)
{
	PF_CallBack();
	/*	Clear the Flag			*/
}


