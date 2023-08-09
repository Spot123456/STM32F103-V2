#ifndef	DMA_PRIVATE_H
#define	DMA_PRIVATE_H


#include "Std_Types.h"
#include "Bit_Math.h"

typedef	struct
{
	u32	CCRx;
	u32	CNDTRx;
	u32	CPARx;
	u32	CMARx;
	u32	reserved;
}DMA1_channel;

typedef struct
{
	u32 			ISR;
	u32				IFCR;
	DMA1_channel	channel[7];
}DMA1_Type;



#define 	DMA1			((volatile DMA1_Type*)(0x40020000))


#endif


