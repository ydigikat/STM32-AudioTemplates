/**
 * @file audio.h
 * @author yizakat (yizakat@yizakat.com)
 * @brief Audio support
 * @version 0.1
 * @date 2023-12-31
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef HARDWARE_AUDIO_H_
#define HARDWARE_AUDIO_H_

#include <stdbool.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "pins.h"
#include "board.h"

/* I2S/DMA configuration for this board */
#define I2S_SPI (SPI2)
#define I2S_DMA (DMA1)
#define I2S_DMA_STREAM (LL_DMA_STREAM_4)
#define I2S_DMA_IRQ (DMA1_Stream4_IRQn)
#define I2S_DMA_CLK (LL_AHB1_GRP1_PERIPH_DMA1)
#define I2S_SPI_CLK (LL_APB1_GRP1_PERIPH_SPI2)

/* We want a 1MHz VCO for the I2S PLL, the other dividers are mode specific (see the LUT in audio.c) */
#define I2S_M (LL_RCC_PLLI2SM_DIV_25)

/* Supported audio configurations */
typedef enum
{
	I2S_44_16,
	I2S_48_16,
	I2S_44_32,
	I2S_48_32,
	I2S_44_MCKOE_16,
	I2S_48_MCKOE_16,
	I2S_44_MCKOE_32,
	I2S_48_MCKOE_32,
} audio_mode_t;

typedef struct
{
	audio_mode_t type;
	uint16_t N;
	uint8_t R;
	uint8_t DIV;
	uint8_t ODD;
	uint8_t MCKOE;
	uint8_t bits;
	float fsr;
} audio_config_t;

#define SAMPLE_BLOCK_SIZE 128								/* 128 float samples */
#define AUDIO_BUF_SGL SAMPLE_BLOCK_SIZE * 4 /* 256 16-bit I2S output samples * LR channels */
#define AUDIO_BUF_DBL AUDIO_BUF_SGL * 2			/* Double buffer */

audio_config_t *audio_streaming_run(int16_t sample_buffer[], audio_mode_t audio_config_type);

#endif /* HARDWARE_AUDIO_H_ */
