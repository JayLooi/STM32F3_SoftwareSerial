/**
 * @file	SoftwareSerial.h
 * @author	Looi Kian Seong
 * @date	13-8-2020
 * @brief	This files declares function prototypes
 *			for software UART functionalities
 *
 */

#ifndef SOFTWARESERIAL_H_
#define SOFTWARESERIAL_H_

#include "ss_reg_config.h"

#define SS_MAX_TX_BUFF			128
#define SS_MAX_RX_BUFF			128

#if(SS_MAX_TX_BUFF == 128)
	#define	TX_BUFF_SIZE_BIT	7
#elif(SS_MAX_TX_BUFF == 64)
	#define	TX_BUFF_SIZE_BIT	6
#elif(SS_MAX_TX_BUFF == 32)
	#define	TX_BUFF_SIZE_BIT	5
#elif(SS_MAX_TX_BUFF == 16)
	#define	TX_BUFF_SIZE_BIT	4
#else
	#error "Invalid tx buffer size! "
#endif

typedef struct {
	uint8_t pos	:	TX_BUFF_SIZE_BIT;
} tx_uintx_t;

#if(SS_MAX_RX_BUFF == 128)
	#define	RX_BUFF_SIZE_BIT	7
#elif(SS_MAX_RX_BUFF == 64)
	#define	RX_BUFF_SIZE_BIT	6
#elif(SS_MAX_RX_BUFF == 32)
	#define	RX_BUFF_SIZE_BIT	5
#elif(SS_MAX_RX_BUFF == 16)
	#define	RX_BUFF_SIZE_BIT	4
#else
	#error "Invalid rx buffer size! "
#endif

typedef struct {
	uint8_t pos	:	RX_BUFF_SIZE_BIT;
} rx_uintx_t;

void ssInit(uint32_t baudrate);
void ssWriteByte(char byte);
void ssWrite(const char *data);
uint8_t isRxAvailable();
char ssReadByte();
void TIM3_IRQHandler();

#endif /* SOFTWARESERIAL_H_ */
