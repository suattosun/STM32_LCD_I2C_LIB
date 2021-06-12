#include "stm32f4xx_hal.h"

/*
 * mylcdi2c.c
 *
 *  Created on: 12 Haz 2021
 *      Author: SUAT-ARGE
 */
#define CLEARDISPLAY 		0x01
#define RETURNHOME 		0x02
#define ENTRYMODE 		0x04
#define DISPLAYSETTING		0x08
#define CURSORSHIFT 		0x10
#define FUNCTIONSET 		0x20
#define SETCGRAMADD 		0x40
#define SETDDRAMADD 		0x80

#define ENTRYMODE_S 		0x01
#define ENTRYMODE_ID		0x02

#define DISPLAYSETTING_B	0x01
#define DISPLAYSETTING_C	0x02
#define DISPLAYSETTING_D	0x04

#define FUNCTIONSET_F		0x04
#define FUNCTIONSET_N		0x08
#define FUNCTIONSET_DL		0x10
#define RSENABLE		0x01
#define ENENABLE		0x04
#define BGLIGHT			0x08
static I2C_HandleTypeDef *I2CHandler;
uint8_t ADDRESS;

void mylcdi2c_init(I2C_HandleTypeDef *i2c, uint8_t address) {
	I2CHandler = i2c;
	ADDRESS = address;
	HAL_Delay(20);
	mylcdi2c_command(0x30);
	HAL_Delay(5);
	mylcdi2c_command(0x20);
	HAL_Delay(1);
	mylcdi2c_command(20);
	HAL_Delay(2);

	mylcdi2c_command((FUNCTIONSET | FUNCTIONSET_N) );
	mylcdi2c_command(
	(DISPLAYSETTING | DISPLAYSETTING_D) );

	mylcdi2c_command(CLEARDISPLAY);
	HAL_Delay(1);

}

void mylcdi2c_command(uint8_t cmd) {
	uint8_t High = (cmd & 0xF0), Low = ((cmd << 4) & 0xF0);
	uint8_t data[4];
	data[0] = High | ENENABLE | BGLIGHT;
	data[1] = High | BGLIGHT;
	data[2] = Low | ENENABLE | BGLIGHT;
	data[3] = Low | BGLIGHT;
	HAL_I2C_Master_Transmit(I2CHandler, ADDRESS, &data, 4, 100);
}
void mylcdi2c_write(uint8_t cmd) {
	uint8_t High = cmd & 0xF0, Low = (cmd << 4) & 0xF0;
	uint8_t data[4];
	data[0] = High | RSENABLE | ENENABLE | BGLIGHT;
	data[1] = High | RSENABLE | BGLIGHT;
	data[2] = Low | RSENABLE | ENENABLE | BGLIGHT;
	data[3] = Low | RSENABLE | BGLIGHT;

	HAL_I2C_Master_Transmit(I2CHandler, ADDRESS, (uint8_t*) data, 4, 1);
}

void mylcdi2c_print(char *str) {
	for (uint8_t i = 0; str[i] != '\0'; i++) {
		mylcdi2c_write(str[i]);
	}
}
void mylcdi2c_setCursor(uint8_t row, uint8_t column) {
	uint8_t maskData = column;
	if (row == 0) {
		maskData |= 0x80;
	}
	if (row == 1) {
		maskData |= 0xC;
	}
	mylcdi2c_command(maskData << 4);
}
void mylcdi2c_clear() {
	mylcdi2c_command(CLEARDISPLAY );
	HAL_Delay(2);

}
