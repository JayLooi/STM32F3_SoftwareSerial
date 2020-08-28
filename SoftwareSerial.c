/**
 * @file	SoftwareSerial.c
 * @author	Looi Kian Seong
 * @date	13-8-2020
 * @brief	This files defines functions for software UART
 *
 */

#include "SoftwareSerial.h"

TIM_SR_t *TIM3_SR = (TIM_SR_t *)(&TIM3->SR);
TIM_DIER_t *TIM3_DIER = (TIM_DIER_t *)(&TIM3->DIER);
TIM_CCMR1_t *TIM3_CCMR1 = (TIM_CCMR1_t *)(&TIM3->CCMR1);
TIM_CCMR2_t *TIM3_CCMR2 = (TIM_CCMR2_t *)(&TIM3->CCMR2);
TIM_CCER_t *TIM3_CCER = (TIM_CCER_t *)(&TIM3->CCER);
TIM_CR1_t *TIM3_CR1 = (TIM_CR1_t *)(&TIM3->CR1);

static volatile uint32_t cnt_per_bit;
static volatile char tx_buff[SS_MAX_TX_BUFF];
static volatile char rx_buff[SS_MAX_RX_BUFF];
static volatile uint8_t pend_tx_byte = 0;
static volatile uint8_t available_rx_byte = 0;
static volatile uint8_t tx_bit = 0;
static volatile uint8_t rx_bit = 0;
static volatile uint8_t is_receiving = 0;
static volatile uint8_t is_rx_buff_available = 0;
static volatile uint8_t rx_data = 0;
static volatile uint8_t tx_data[9];
static volatile char curr_tx_byte;
static uint32_t one_and_half_bit_time;

static volatile tx_uintx_t tx_buff_byte, tx_byte;
static volatile rx_uintx_t curr_rbyte, rx_byte;

#define	MAX_TIM_CNT_PER_BIT			499

/**
 * @brief  Initialise the GPIO and Timer configurations for software UART
 * @param  baudrate: baud rate for software UART communication
 * 						(9600, 19200, 38400, 57600, 74880, 115200)
 * 						to have more stable full-duplex communication,
 * 						avoid using baud rate of 115200
 * @retval None
 */
void ssInit(uint32_t baudrate) {
	tx_buff_byte.pos = tx_byte.pos = curr_rbyte.pos = rx_byte.pos = 0;
	tx_data[8] = 1;
	cnt_per_bit = F_CPU / baudrate;
	uint16_t prescaler = 1;

	while((cnt_per_bit / prescaler) > MAX_TIM_CNT_PER_BIT) {
		prescaler++;
	}
	cnt_per_bit /= prescaler;
	if(cnt_per_bit > MAX_TIM_CNT_PER_BIT)
		return;

	one_and_half_bit_time = cnt_per_bit / 2 + cnt_per_bit;
	ENABLE_GPIOC_CLOCK();
	CONFIG_GPIOC6_MODE();
	CONFIG_GPIOC7_MODE();

	ENABLE_TIM3_CLOCK();
	CONFIG_TIM3_PSC(prescaler);
	FORCE_OC1REF_HIGH();
	CONFIG_TIM3_CC1_OUT_MODE(0);		/* start bit */
	CONFIG_TIM3_CC1_DIR();
	CONFIG_TIM3_CC2_DIR();
	CONFIG_TIM3_CC3_DIR();
	ENABLE_TIM3_INTERRUPT();
	ENABLE_TIM3_CC2_INT();
	CONFIG_TIM3_CC2_CAP_TRIGGER(FALLING_EDGE);
	ENABLE_TIM3_INPUT_CAP2();
	ENABLE_TIM3_COUNTER();
}

/**
 * @brief  Write a byte of data into the transmission buffer
 * @param  byte: data to be transmitted
 * @retval None
 */
void ssWriteByte(char byte) {
	while(pend_tx_byte == SS_MAX_TX_BUFF);
	DISABLE_TIM3_INTERRUPT();
	tx_buff_byte.pos = tx_byte.pos + pend_tx_byte;
	tx_buff[tx_buff_byte.pos] = byte;
	pend_tx_byte++;
	if(!TIM3_DIER->CC1IE) {
		/* Note: avoid looping here to improve the execution speed */
		tx_data[0] = (byte >> 0) & 0x01;
		tx_data[1] = (byte >> 1) & 0x01;
		tx_data[2] = (byte >> 2) & 0x01;
		tx_data[3] = (byte >> 3) & 0x01;
		tx_data[4] = (byte >> 4) & 0x01;
		tx_data[5] = (byte >> 5) & 0x01;
		tx_data[6] = (byte >> 6) & 0x01;
		tx_data[7] = (byte >> 7) & 0x01;
		ENABLE_TIM3_CC1_INT();
		ENABLE_TIM3_OUTPUT_COMP1();
		TIM3->CCR1 = TIM3->CNT + cnt_per_bit;
	}
	ENABLE_TIM3_INTERRUPT();
}

/**
 * @brief  Write a string of 8-bit char into the transmission buffer
 * @param  data: string of 8-bit char
 * @retval None
 */
void ssWrite(const char *data) {
	char byte;
	while((byte = *(data++))) {
		ssWriteByte(byte);
	}
}

/**
 * @brief  Check for the availability of data in reception buffer
 * @param  None
 * @retval Number of data in the buffer
 */
uint8_t isRxAvailable() {
	return available_rx_byte;
}

/**
 * @brief  Read a byte of data from the reception buffer
 * @param  None
 * @retval First available byte of data in the buffer
 */
char ssReadByte() {
	if(available_rx_byte) {
		curr_rbyte.pos = rx_byte.pos - available_rx_byte--;
		return rx_buff[curr_rbyte.pos];
	}

	else
		return -1;
}

/**
 * @brief  Interrupt service routine for data reception and transmission
 * @param  None
 * @retval None
 */
void TIM3_IRQHandler() {
	/* Falling edge (start bit) detection */
	if(TIM3_SR->CC2IF) {
		uint32_t cap_cnt = TIM3->CCR2;
		if(!is_receiving && !RX_DATA) {	/* start bit */
			TIM3->CCR3 = cap_cnt + one_and_half_bit_time;
			TIM3_SR->CC3IF = 0;
			is_receiving = 1;
			is_rx_buff_available = (available_rx_byte < SS_MAX_RX_BUFF);
			ENABLE_TIM3_CC3_INT();
			DISABLE_TIM3_INPUT_CAP2();
			DISABLE_TIM3_CC2_INT();
		}
	}

	/* Reception */
	if(is_receiving && TIM3_SR->CC3IF) {
		TIM3_SR->CC3IF = 0;
		TIM3->CCR3 += cnt_per_bit;
		if(rx_bit < 8) {
			rx_data |= RX_DATA << rx_bit;
			rx_bit++;
		} else {
			if(RX_DATA) {	/* stop bit */
				if(is_rx_buff_available) {
					rx_buff[rx_byte.pos] = rx_data;
					available_rx_byte++;
					rx_byte.pos++;
				}
			} else {		/* framing error */
				//TODO:	Handle framing error
			}

			rx_data = 0;
			is_receiving = 0;
			rx_bit = 0;
			is_rx_buff_available = 0;
			ENABLE_TIM3_INPUT_CAP2();
			ENABLE_TIM3_CC2_INT();
			DISABLE_TIM3_CC3_INT();
		}
	}

	/* Transmission */
	if(pend_tx_byte && TIM3_SR->CC1IF) {
		TIM3_SR->CC1IF = 0;
		TIM3->CCR1 += cnt_per_bit;

		if(tx_bit < 9) {
			CONFIG_TIM3_CC1_OUT_MODE(tx_data[tx_bit++]);
		} else {
			CONFIG_TIM3_CC1_OUT_MODE(0);			/* start bit */
			tx_bit = 0;
			tx_byte.pos++;
			pend_tx_byte--;
			if(!pend_tx_byte) {
				DISABLE_TIM3_CC1_INT();
				DISABLE_TIM3_OUTPUT_COMP1();
				tx_byte.pos = 0;
				tx_buff_byte.pos = 0;
			} else {
				curr_tx_byte = tx_buff[tx_byte.pos];
				/* Note: avoid looping here to improve the execution speed */
				tx_data[0] = (curr_tx_byte >> 0) & 0x01;
				tx_data[1] = (curr_tx_byte >> 1) & 0x01;
				tx_data[2] = (curr_tx_byte >> 2) & 0x01;
				tx_data[3] = (curr_tx_byte >> 3) & 0x01;
				tx_data[4] = (curr_tx_byte >> 4) & 0x01;
				tx_data[5] = (curr_tx_byte >> 5) & 0x01;
				tx_data[6] = (curr_tx_byte >> 6) & 0x01;
				tx_data[7] = (curr_tx_byte >> 7) & 0x01;
			}
		}
	}
}
