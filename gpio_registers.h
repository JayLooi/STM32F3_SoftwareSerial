/**
 * @file	gpio_registers.h
 * @author	Looi Kian Seong
 * @date	13-8-2020
 * @brief	This files defines the GPIO registers for bit field read/write
 *
 */

#ifndef GPIO_REGISTERS_H_
#define GPIO_REGISTERS_H_

#include "stm32f3xx.h"

/* Macro functions for creating GPIO register parameters */
#define DECLARE_REG_x_16xBITS(REG_NAME, xBIT, BIT_FIELD)		union {															\
																	__IO uint##xBIT##_t REG_NAME;								\
																	struct {													\
																		__IO uint##xBIT##_t REG_NAME##0		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##1		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##2		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##3		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##4		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##5		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##6		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##7		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##8		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##9		:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##10	:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##11	:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##12	:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##13	:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##14	:	BIT_FIELD;		\
																		__IO uint##xBIT##_t REG_NAME##15	:	BIT_FIELD;		\
																	};															\
																}

#define	DECLARE_8x4_BITS_REG32(REG_NAME)		union {											\
													__IO uint32_t REG_NAME;						\
													struct {									\
														__IO uint32_t REG_NAME##0	:	4;		\
														__IO uint32_t REG_NAME##1	:	4;		\
														__IO uint32_t REG_NAME##2	:	4;		\
														__IO uint32_t REG_NAME##3	:	4;		\
														__IO uint32_t REG_NAME##4	:	4;		\
														__IO uint32_t REG_NAME##5	:	4;		\
														__IO uint32_t REG_NAME##6	:	4;		\
														__IO uint32_t REG_NAME##7	:	4;		\
													};											\
												}

#define	DECLARE_16x1_BITS_REG32(REG_NAME)		DECLARE_REG_x_16xBITS(REG_NAME, 32, 1)
#define	DECLARE_16x2_BITS_REG32(REG_NAME)		DECLARE_REG_x_16xBITS(REG_NAME, 32, 2)
#define DECLARE_16x1_BITS_REG16(REG_NAME)		DECLARE_REG_x_16xBITS(REG_NAME, 16, 1)

/* Define GPIO register union-struct variables */
#define GPIO_MODER		DECLARE_16x2_BITS_REG32(MODER)
#define GPIO_OTYPER		DECLARE_16x1_BITS_REG32(OTYPER)
#define GPIO_OSPEEDR	DECLARE_16x2_BITS_REG32(OSPEEDR)
#define	GPIO_PUPDR		DECLARE_16x2_BITS_REG32(PUPDR)
#define	GPIO_IDR		DECLARE_16x1_BITS_REG32(IDR)
#define	GPIO_ODR		DECLARE_16x1_BITS_REG32(ODR)
#define	GPIO_BSRRL		DECLARE_16x1_BITS_REG16(BSRRL)
#define	GPIO_BSRRH		DECLARE_16x1_BITS_REG16(BSRRH)
//#define	GPIO_LCKR
#define	GPIO_AFRL		DECLARE_8x4_BITS_REG32(AFRL)
#define	GPIO_AFRH		DECLARE_8x4_BITS_REG32(AFRH)
#define	GPIO_BRR		DECLARE_16x1_BITS_REG32(BRR)

typedef struct {
	GPIO_MODER;			/*!< GPIO port mode register,                Address offset: 0x00 */
	GPIO_OTYPER;		/*!< GPIO port output type register,         Address offset: 0x04 */
	GPIO_OSPEEDR;		/*!< GPIO port output speed register,        Address offset: 0x08 */
	GPIO_PUPDR;			/*!< GPIO port pull-up/pull-down register,   Address offset: 0x0C */
	GPIO_IDR;			/*!< GPIO port input data register,          Address offset: 0x10 */
	GPIO_ODR;			/*!< GPIO port output data register,         Address offset: 0x14 */
	GPIO_BSRRL;			/*!< GPIO port bit set/reset low register,   Address offset: 0x18 */
	GPIO_BSRRH;			/*!< GPIO port bit set/reset high register,  Address offset: 0x1A */
	__IO uint32_t LCKR;	/*!< GPIO port configuration lock register,  Address offset: 0x1C */
	GPIO_AFRL;			/*!< GPIO alternate function low registers,  Address offset: 0x20 */
	GPIO_AFRH;			/*!< GPIO alternate function high registers, Address offset: 0x24 */
	GPIO_BRR;			/*!< GPIO bit reset register,                Address offset: 0x28 */
} GPIOx_t;

#define GPIO_A			((GPIOx_t *)GPIOA_BASE)
#define GPIO_B			((GPIOx_t *)GPIOB_BASE)
#define GPIO_C			((GPIOx_t *)GPIOC_BASE)
#define GPIO_D			((GPIOx_t *)GPIOD_BASE)
#define GPIO_E			((GPIOx_t *)GPIOE_BASE)
#define GPIO_F			((GPIOx_t *)GPIOF_BASE)

#endif /* GPIO_REGISTERS_H_ */
