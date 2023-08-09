#ifndef		RCC_PRIVATE_H
#define		RCC_PRIVATE_H

#define		RCC_BASE_ADD		(0x40021000)

typedef struct
{
	u32 RCC_CR ;
	u32 RCC_CFGR;
	u32	RCC_CIR;
	u32	RCC_APB2RSTR;
	u32	RCC_APB1RSTR;
	u32	RCC_AHBENR;
	u32	RCC_APB2ENR;
	u32	RCC_APB1ENR;
	u32 RCC_BDCR;
	u32	RCC_CSR;
}ST_RCC;

#define RCC_REG		((ST_RCC*)(RCC_BASE_ADD))

// PLL HSE multiplication factor
#define	PLL_input_Mul2	0
#define	PLL_input_Mul3	1
#define	PLL_input_Mul4	2
#define	PLL_input_Mul5	3
#define	PLL_input_Mul6	4
#define	PLL_input_Mul7	5
#define	PLL_input_Mul8	6
#define	PLL_input_Mul9	7
#define	PLL_input_Mul10	8
#define PLL_input_MUl_Musk	0b1111


#endif
