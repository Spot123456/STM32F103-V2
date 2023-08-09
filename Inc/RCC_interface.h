#ifndef		RCC_INTERFACE_H
#define		RCC_INTERFACE_H

# include "Std_Types.h"

void		RCC_voidSysClkInt(void);

void		RCC_voidEnablePerClk(u8 BusId , u8 PerId);



void		RCC_voidDisablePerClk(u8 BusId , u8 PerId);

void		RCC_voidEnableADC_Prescaler();

#define APB1	0
#define APB2	1
#define AHB		2

#endif
