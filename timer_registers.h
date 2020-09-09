/**
 * @file	timer_registers.h
 * @author	Looi Kian Seong
 * @date	13-8-2020
 * @brief	This files defines the timer registers for bit field read/write
 *
 */

#ifndef TIMER_REGISTERS_H_
#define TIMER_REGISTERS_H_

#include "stm32f3xx.h"

typedef union {
	__IO uint32_t CR1;
	struct {
		__IO uint32_t CEN		:	1;
		__IO uint32_t UDIS		:	1;
		__IO uint32_t URS		:	1;
		__IO uint32_t OPM		:	1;
		__IO uint32_t DIR		:	1;
		__IO uint32_t CMS		:	2;
		__IO uint32_t ARPE		:	1;
		__IO uint32_t CKD		:	2;
		__IO uint32_t reserved0		:	1;			//must be kept at reset value
		__IO uint32_t UIFREMAP		:	1;
	};
} TIM_CR1_t;

typedef union {
	__IO uint32_t CR2;
	struct {
		__IO uint32_t reserved0		:	3;
		__IO uint32_t CCDS		:	1;
		__IO uint32_t MMS		:	3;
		__IO uint32_t TI1S		:	1;
	};
} TIM_CR2_t;

typedef union {
	__IO uint32_t SMCR;
	struct {
		__IO uint32_t SMS0		:	1;
		__IO uint32_t SMS1		:	1;
		__IO uint32_t SMS2		:	1;
		__IO uint32_t OCCS		:	1;
		__IO uint32_t TS		:	3;
		__IO uint32_t MSM		:	1;
		__IO uint32_t ETF		:	4;
		__IO uint32_t ETPS		:	2;
		__IO uint32_t ECE		:	1;
		__IO uint32_t ETP		:	1;
		__IO uint32_t SMS3		:	1;
	};
} TIM_SMCR_t;

typedef union {
	__IO uint32_t DIER;
	struct {
		__IO uint32_t UIE		:	1;
		__IO uint32_t CC1IE		:	1;
		__IO uint32_t CC2IE		:	1;
		__IO uint32_t CC3IE		:	1;
		__IO uint32_t CC4IE		:	1;
		__IO uint32_t reserved0		:	1;			//must be kept at reset value
		__IO uint32_t TIE		:	1;
		__IO uint32_t reserved1		:	1;			//must be kept at reset value
		__IO uint32_t UDE		:	1;
		__IO uint32_t CC1DE		:	1;
		__IO uint32_t CC2DE		:	1;
		__IO uint32_t CC3DE		:	1;
		__IO uint32_t CC4DE		:	1;
		__IO uint32_t reserved2		:	1;			//must be kept at reset value
		__IO uint32_t TDE		:	1;
	};
} TIM_DIER_t;

typedef union {
	__IO uint32_t SR;
	struct {
		__IO uint32_t UIF		:	1;
		__IO uint32_t CC1IF		:	1;
		__IO uint32_t CC2IF		:	1;
		__IO uint32_t CC3IF		:	1;
		__IO uint32_t CC4IF		:	1;
		__IO uint32_t reserved0		:	1;			//must be kept at reset value
		__IO uint32_t TIF		:	1;
		__IO uint32_t reserved1		:	1;			//must be kept at reset value
		__IO uint32_t reserved2		:	1;			//must be kept at reset value
		__IO uint32_t CC1OF		:	1;
		__IO uint32_t CC2OF		:	1;
		__IO uint32_t CC3OF		:	1;
		__IO uint32_t CC4OF		:	1;
	};
} TIM_SR_t;

typedef union {
	__IO uint32_t EGR;
	struct {
		__IO uint32_t UG		:	1;
		__IO uint32_t CC1G		:	1;
		__IO uint32_t CC2G		:	1;
		__IO uint32_t CC3G		:	1;
		__IO uint32_t CC4G		:	1;
		__IO uint32_t reserved0		:	1;			//must be kept at reset value
		__IO uint32_t TG		:	1;
	};
} TIM_EGR_t;

typedef union {
	__IO uint32_t CCMR1;
	struct {
		__IO uint32_t CC1S		:	2;
		__IO uint32_t OC1FE		:	1;
		__IO uint32_t OC1PE		:	1;
		__IO uint32_t OC1M0_2		:	3;
		__IO uint32_t OC1CE		:	1;
		__IO uint32_t CC2S		:	2;
		__IO uint32_t OC2FE		:	1;
		__IO uint32_t OC2PE		:	1;
		__IO uint32_t OC2M0_2		:	3;
		__IO uint32_t OC2CE		:	1;
		__IO uint32_t OC1M3		:	1;
		__IO uint32_t reserved0		:	7;			//must be kept at reset value
		__IO uint32_t OC2M3		:	1;
	};
	struct {
		__IO uint32_t _CC1S		:	2;
		__IO uint32_t IC1PSC		:	2;
		__IO uint32_t IC1F		:	4;
		__IO uint32_t _CC2S		:	2;
		__IO uint32_t IC2PSC		:	2;
		__IO uint32_t IC2F		:	4;
		__IO uint32_t _OC1M3		:	1;
		__IO uint32_t _reserved0	:	7;			//must be kept at reset value
		__IO uint32_t _OC2M3		:	1;
	};
} TIM_CCMR1_t;

typedef union {
	__IO uint32_t CCMR2;
	struct {
		__IO uint32_t CC3S		:	2;
		__IO uint32_t OC3FE		:	1;
		__IO uint32_t OC3PE		:	1;
		__IO uint32_t OC3M0_2		:	3;
		__IO uint32_t OC3CE		:	1;
		__IO uint32_t CC4S		:	2;
		__IO uint32_t OC4FE		:	1;
		__IO uint32_t OC4PE		:	1;
		__IO uint32_t OC4M0_2		:	3;
		__IO uint32_t OC4CE		:	1;
		__IO uint32_t OC3M3		:	1;
		__IO uint32_t reserved0		:	7;			//must be kept at reset value
		__IO uint32_t OC4M3		:	1;
	};
	struct {
		__IO uint32_t _CC3S		:	2;
		__IO uint32_t IC3PSC		:	2;
		__IO uint32_t IC3F		:	4;
		__IO uint32_t _CC4S		:	2;
		__IO uint32_t IC4PSC		:	2;
		__IO uint32_t IC4F		:	4;
		__IO uint32_t _OC3M3		:	1;
		__IO uint32_t _reserved0	:	7;			//must be kept at reset value
		__IO uint32_t _OC4M3		:	1;
	};
} TIM_CCMR2_t;

typedef union {
	__IO uint32_t CCER;
	struct {
		__IO uint32_t CCER1	:	4;
		__IO uint32_t CCER2	:	4;
		__IO uint32_t CCER3	:	4;
		__IO uint32_t CCER4	:	4;
	};
} TIM_CCER_t;

#endif /* TIMER_REGISTERS_H_ */
