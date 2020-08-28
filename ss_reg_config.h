/**
 * @file	ss_reg_config.h
 * @author	Looi Kian Seong
 * @date	13-8-2020
 * @brief	This files defines the GPIO and Timer3 configurations
 * 			for software UART functionalities
 *
 */

#ifndef SS_REG_CONFIG_H_
#define SS_REG_CONFIG_H_

#include "gpio_registers.h"
#include "timer_registers.h"

#define	F_CPU		SystemCoreClock

extern TIM_SR_t *TIM3_SR;
extern TIM_DIER_t *TIM3_DIER;
extern TIM_CCMR1_t *TIM3_CCMR1;
extern TIM_CCMR2_t *TIM3_CCMR2;
extern TIM_CCER_t *TIM3_CCER;
extern TIM_CR1_t *TIM3_CR1;

#define	RX_DATA			GPIO_C->IDR7

/* GPIOC Config */
#define ENABLE_GPIOC_CLOCK()					RCC->AHBENR |= RCC_AHBENR_GPIOCEN
#define CONFIG_GPIOC6_MODE()					(GPIO_C->MODER6 = 0b10, GPIO_C->OSPEEDR6 = 0b11, GPIO_C->AFRL6 = 0b0010)
#define	CONFIG_GPIOC7_MODE()					(	GPIO_C->MODER7 = 0b10, GPIO_C->OSPEEDR7 = 0b11, \
													GPIO_C->AFRL7 = 0b0010, GPIO_C->PUPDR7 = 0x01		)

#define	FALLING_EDGE		0b0010
#define	RISING_EDGE			0b0000
#define	BOTH_EDGES			0b1010

/* Timer3 Config */
#define ENABLE_TIM3_CLOCK()						RCC->APB1ENR |= RCC_APB1ENR_TIM3EN
#define	CONFIG_TIM3_PSC(prescaler)				TIM3->PSC = ((prescaler) - 1)
#define	CONFIG_TIM3_ARR(ARR_value)				TIM3->ARR = ARR_value
#define	CONFIG_TIM3_CCR1(COMP_value)			TIM3->CCR1 = COMP_value
#define	CONFIG_TIM3_CCR3(COMP_value)			TIM3->CCR3 = COMP_value
#define	CONFIG_TIM3_CC1_DIR()					(TIM3_CCMR1->CC1S = 0, TIM3_CCMR1->OC1M3 = 0)
#define	CONFIG_TIM3_CC2_DIR()					TIM3_CCMR1->CC2S = 1
#define	CONFIG_TIM3_CC3_DIR()					TIM3_CCMR2->CC3S = 0
#define FORCE_OC1REF_HIGH()						TIM3_CCMR1->OC1M0_2 = 0b101
#define	CONFIG_TIM3_CC1_OUT_MODE(BIT_DATA)		TIM3_CCMR1->OC1M0_2 = (2 >> (BIT_DATA))
#define	CONFIG_TIM3_CC2_CAP_TRIGGER(trigger)	TIM3_CCER->CCER2 = ((TIM3_CCER->CCER2 & 0b0001) | trigger)
#define	ENABLE_TIM3_OUTPUT_COMP1()				TIM3_CCER->CCER1 = 1
#define	ENABLE_TIM3_INPUT_CAP2()				TIM3_CCER->CCER2 |= 1
#define ENABLE_TIM3_CC1_INT()					TIM3_DIER->CC1IE = 1
#define ENABLE_TIM3_CC2_INT()					TIM3_DIER->CC2IE = 1
#define ENABLE_TIM3_CC3_INT()					TIM3_DIER->CC3IE = 1
#define	DISABLE_TIM3_OUTPUT_COMP1()				TIM3_CCER->CCER1 = 0
#define	DISABLE_TIM3_INPUT_CAP2()				TIM3_CCER->CCER2 &= 0b1110
#define DISABLE_TIM3_CC1_INT()					TIM3_DIER->CC1IE = 0
#define DISABLE_TIM3_CC2_INT()					TIM3_DIER->CC2IE = 0
#define DISABLE_TIM3_CC3_INT()					TIM3_DIER->CC3IE = 0
#define	ENABLE_TIM3_COUNTER()					TIM3_CR1->CEN = 1
#define	ENABLE_TIM3_INTERRUPT()					NVIC->ISER[0] |= 1 << 29
#define	DISABLE_TIM3_INTERRUPT()				NVIC->ISER[0] &= ~(1 << 29)

#endif /* SS_REG_CONFIG_H_ */
