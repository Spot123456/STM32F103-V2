



#include "DMA_interface.h"

#ifndef		NULL
#define		NULL	(void *)0
#endif

static	void	(*DMA1_CallBack)(void)	=	NULL;

void	DMA1_voidChannelInit(u8 channel_no ,u8 from_to,u8 circular_mode)
{
	/*
	Memory to Memory
	priority very high
	Size (Source & Destination) u32
	MINC, PINC enabled
	Direction read from Peripheral
	Transfere Complete Interrupt
	Channel Disable
	*/
	// memory to memory : i.e memory work without being triggered
	// REQ by the peripheral

	// select type of interrupt enable
	#if	Full_Complete_Interrupt == enable
		SET_BIT(DMA1->channel[channel_no].CCRx,1);
	#else
		CLR_BIT(DMA1->channel[channel_no].CRRx,1);

	#endif

	#if		Half_Complete_Interrupt == enable
			SET_BIT(DMA1->channel[channel_no].CCRx,2);

	#elif	Half_Complete_Interrupt == disable
			CLR_BIT(DMA1->channel[channel_no].CCRx,2);

	#endif

	#if		TX_Erorr_Interrupt == enable
		SET_BIT(DMA1->channel[channel_no].CCRx,3);

	#elif	TX_Erorr_Interrupt == disable
		CLR_BIT(DMA1->channel[channel_no].CCRx,3);

	#endif

	// enable the channel
		SET_BIT(DMA1->channel[channel_no].CCRx,0);

		// pinc -> peripheral inc mode
		// Minc ->	Memory	   inc mode
	switch (from_to)
	{

		case Arr_TO_Arr		:
			//Read from Memory
			SET_BIT(DMA1->channel[channel_no].CCRx,4);
			SET_BIT(DMA1->channel[channel_no].CCRx,7); // MINC INC
			SET_BIT(DMA1->channel[channel_no].CCRx,6);	// PINC INC
			SET_BIT(DMA1->channel[channel_no].CCRx,14);	// Memory to memory mode enabled
			break;
		case Peri_TO_Arr	:
			//Read from Peri
			CLR_BIT(DMA1->channel[channel_no].CCRx,4)	;
			SET_BIT(DMA1->channel[channel_no].CCRx,7); // MINC INC
			CLR_BIT(DMA1->channel[channel_no].CCRx,6);	// PINC const
			break;
		case Arr_TO_Peri	:
			//Read from Memory
			SET_BIT(DMA1->channel[channel_no].CCRx,4)	;
			SET_BIT(DMA1->channel[channel_no].CCRx,7); // MINC INC
			CLR_BIT(DMA1->channel[channel_no].CCRx,6);	// PINC const
			break;
		case Peri_TO_Peri	:
			//Read from Peri
			CLR_BIT(DMA1->channel[channel_no].CCRx,4)	;
			CLR_BIT(DMA1->channel[channel_no].CCRx,7); // MINC const
			CLR_BIT(DMA1->channel[channel_no].CCRx,6);	// PINC const
			break;

	}
	switch (circular_mode)
	{
		case disable:	CLR_BIT(DMA1->channel[channel_no].CCRx,5); break;
		case enable:	SET_BIT(DMA1->channel[channel_no].CCRx,5); break;
	}

}

void	DMA1_voidStartChannel(u32 * SrcAdd,u32 * DestAdd,u16 BlockLength,u8 channel_no)
{
	/*		Make Sure that the channel is  disabled */
	CLR_BIT(DMA1->channel[channel_no].CCRx,0);
	
	//source Address
	DMA1->channel[channel_no].CPARx=*SrcAdd;
	DMA1->channel[channel_no].CMARx=*DestAdd;
	//load the data length
	DMA1->channel[channel_no].CNDTRx=BlockLength;
	// enable the DMA to start transfere
	SET_BIT(DMA1->channel[channel_no].CCRx,0);
}

void	DMA1_voidSetCallBack(void (*pf)(void))
{
	if(pf!=NULL)
	{
		DMA1_CallBack=pf;
	}

}


void	DMA1_Channel0_IRQHandler()
{
	// error flag for channel zero only
		if ((GET_BIT(DMA1->ISR,1))==1)
		{
			// event handle
			//the clear the flag

			// clear the flag
			DMA1->IFCR=(1<<3);
		}
		else if ((GET_BIT(DMA1->ISR,2))==1)
		{
			// event handle
			// Erorr half transfer

			// clear the flag
			DMA1->IFCR=(1<<2);
		}
		else if ((GET_BIT(DMA1->ISR,3))==1)
		{
			// event handle
			//Report Error DMA1 transfere error

			// clear the flag
			DMA1->IFCR=(1<<1);
		}
		DMA1_CallBack();

		//Clears the GIF, TEIF, HTIF and TCIF flags in the DMA_ISR register
		DMA1->IFCR=(1<<0);

}





