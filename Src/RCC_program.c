#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"RCC_interface.h"
#include	"RCC_private.h"
#include	"RCC_config.h"


void		RCC_voidSysClkInt(void)
{
	#if SYS_CLK==HSE
	//RCC_REG->RCC_CR|=(1<<18)|(1<<19)
	// enable HSE bypass
	SET_BIT(RCC_REG->RCC_CR,18);
	// enable Clock security system enable
	SET_BIT(RCC_REG->RCC_CR,19);

	// enable HSE
	SET_BIT(RCC_REG->RCC_CR,16);
	// wait 6 clk and read the pin that sure HSE is stable
	while(!GET_BIT(RCC_REG->RCC_CR,17));

	//Set and cleared by software to select SYSCLK source and forced HSI if HSE has Failure
	//SET_BIT(RCC_REG->RCC_CFGR,0);
	//CLR_BIT(RCC_REG->RCC_CFGR,1);

	#elif SYS_CLK==PLL

#if PLL_INPUT == PLL_HSE
	//  HSE oscillator clock selected as PLL input clock
	SET_BIT(RCC_REG->RCC_CFGR,16);

	// div the HSE/2 befor MULTiplication
		SET_BIT(RCC_REG->RCC_CFGR,17);

#elif	PLL_INPUT == PLL_HSI
	CLR_BIT(RCC_REG->RCC_CFGR,16);

#endif

	// mul input HSE for PLL
	//RCC_REG->RCC_CFGR &=~(0b1111<<18) ;  // init state is mul by 2

	RCC_REG->RCC_CFGR |=(PLL_MUL<<18); // other mul


	// enable Clock security system enable
	SET_BIT(RCC_REG->RCC_CR,19);

	//Set and cleared by software to select SYSCLK source and forced HSI if HSE has Failure
	//SET_BIT(RCC_REG->RCC_CFGR,0);
	//CLR_BIT(RCC_REG->RCC_CFGR,1);

	// PLL enable
		SET_BIT(RCC_REG->RCC_CR,24);

	while(!GET_BIT(RCC_REG->RCC_CR,25));



	#elif	SYS_CLK== HSI

	SET_BIT(RCC_REG->RCC_CR,0);
	CLR_BIT(RCC_REG->RCC_CFGR,1);
	CLR_BIT(RCC_REG->RCC_CFGR,0);



	while(!GET_BIT(RCC_REG->RCC_CR,1));


	#endif
}


void		RCC_voidEnablePerClk(u8 BusId , u8 PerId)
{
	if(PerId < 32)
	{
		//control the division factor of the APB2 high-speed clock
		RCC_REG->RCC_CFGR|= (APB2_scale<<11) ;
		//control the division factor of the APB1 low-speed clock
		RCC_REG->RCC_CFGR|= (APB1_scale<<8) ;
		switch(BusId)
		{
		case APB1 :	SET_BIT(RCC_REG->RCC_APB1ENR,PerId)	;	break;
		case APB2 :	SET_BIT(RCC_REG->RCC_APB2ENR,PerId)	;	break;
		case AHB :	SET_BIT(RCC_REG->RCC_AHBENR,PerId)	;	break;
		default   :	//do nothing	;
			break;
		}
	}
}


void		RCC_voidDisablePerClk(u8 BusId , u8 PerId)
{
	if(PerId < 32)
	{
	switch(BusId)
		{
		case APB1 :	CLR_BIT(RCC_REG->RCC_APB1ENR,PerId)	;	break;
		case APB2 :	CLR_BIT(RCC_REG->RCC_APB2ENR,PerId)	;	break;
		case AHB :	CLR_BIT(RCC_REG->RCC_AHBENR,PerId)	;	break;
		default   :	//do nothing	;
			break;
		}
	}
	else {/* return error " out  of range "*/}
}









