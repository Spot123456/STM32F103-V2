#ifndef		DIO_PRIVATE_H
#define		DIO_PRIVATE_H

#define		GPIOA_BASE_ADD		(0x40010800)

#define		GPIOB_BASE_ADD		(0x40010C00)

#define		GPIOC_BASE_ADD		(0x40011000)




typedef struct
{
	u32	GPIOx_CRL;
	u32	GPIOx_CRH;
	u32	GPIOx_IDR;
	u32	GPIOx_ODR;
	u32	GPIOx_BSRR;
	u32	GPIOx_BRR;
	u32 GPIOx_LCKR;
}ST_DIO;

#define	GPIOA	((ST_DIO*)(GPIOA_BASE_ADD))

#define	GPIOB	((ST_DIO*)(GPIOB_BASE_ADD))

#define	GPIOC	((ST_DIO*)(GPIOC_BASE_ADD))






#endif
