#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"STK_interface.h"
#include	"STK_private.h"
#include	"STK_config.h"

#ifndef		NULL
#define		NULL		(void *)0
#endif

static	void	(*STK_CallBack)	(void)	=	NULL;
static	u8		STK_u8ModeOfInterval;


void	STK_voidInit()
{
#if	STK_CLK_SRC == STK_AHB_DIV_8
	STK->CTRL= 0x00;
#elif STK_CLK_SRC == STK_AHB
	STK->CTRL=0x04;

#endif

}
void	STK_voidSetBusyWait(u32	Ticks)
{
	// set the time load
	STK->LOAD=Ticks;
	// start timer
	STK->CTRL=0x01;
	// while the count didn't arrived to zero work null op
	while(GET_BIT(STK->CTRL,16)==0)
	{
		asm("NOP");
	}
	// reset counter
	STK->CTRL=0x00;
	// reset the set val & read the remainder
	STK->LOAD=0;
	STK->VAL=0;

}
void	STK_voidSetIntervalSingle(u32	Ticks, void (*Pf)(void))
{
	// set the val
	STK->LOAD= Ticks;
	// enable interrupt
	SET_BIT(STK->CTRL,1);
	// start timer
	SET_BIT(STK->CTRL,0);
	// equal the fun with call back fun
	STK_CallBack=Pf;
	// show the type of interrupt ( mode)
	STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;


}
void	STK_voidSetIntervalPeriodic(u32	Ticks, void (*Pf)(void))
{
	// load the ticks value
	STK->LOAD= Ticks;
	// enable interrupt
	SET_BIT( STK->CTRL ,1 );
	// start timer
	SET_BIT( STK->CTRL ,0 );
	// equal the function with call back fun to call in ISR
	STK_CallBack=Pf;
	// show the mode of timer
	STK_u8ModeOfInterval= STK_PERIOD_INTERVAL;
}
void	STK_voidStopInterval()
{
	// disable interrupt
	CLR_BIT(STK->CTRL,1);
	// stop timer  ( disable )
	ClR_BIT(STK->CTRL,0);
	// set load =0 & val by any number to reset counter (we use 0)
	STK->LOAD=0;
	STK->VAL=0;
}
u32		STK_u32GetElapsedTime()  // the time that finshed from total time
{
	u32 local_counter;
	local_counter= (STK->LOAD)-(STK->VAL);
	return local_counter;
}
u32		STK_u32GetRemainingTime()
{
	u32	Local_counter;
	Local_counter= STK->VAL;
	return Local_counter;
}


void	SysTick_Handler()
{
	u8 Local_u8Temp;
	if(STK_u8ModeOfInterval == STK_SINGLE_INTERVAL)
	{
		/*	Disable The Interrupt			*/
		CLR_BIT(STK -> CTRL , 1);
		/*	Stop the timer					*/
		CLR_BIT(STK -> CTRL , 0);
		STK ->	LOAD	=	0;
		STK ->	VAL		=	0;
	}
	STK_CallBack();
	/*	to clear the timer flag just read it */
		Local_u8Temp	=	GET_BIT(STK -> CTRL,16);

}





