#ifndef		RCC_CONFIG_H
#define		RCC_CONFIG_H

/*
 * you can config speed between 4 choices
 * 1- RCC_HSE_bypass
 * 2-RCC_HSE_Crystal
 * 3-RCC_HSI
 * 4-RCC_PLL
 * NOTE THAT : if PLL Choise speed and the input of pll
 */


#define HSI			0
#define	HSE			1
#define	PLL			2
#define	SYS_CLK		HSE
#define PLL_MUL		PLL_input_Mul2

#define PLL_HSE		0
#define PLL_HSI		1
#define  PLL_INPUT	PLL_HSE


#define	HCLK		0		//high clk
#define HCLK_DIV2	4		//dev 2
#define HCLK_DIV4	5		//dev 4
#define HCLK_DIV8	6		//dev 8
#define HCLK_DIV16	7		//dev 16

#define APB2_scale	HCLK

#define APB1_scale	HCLK




#endif
