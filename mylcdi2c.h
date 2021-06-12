/*
 * mylcdi2c.h
 *
 *  Created on: 12 Haz 2021
 *      Author: SUAT
 */

#ifndef INC_MYLCDI2C_H_
#define INC_MYLCDI2C_H_


void mylcdi2c_init(I2C_HandleTypeDef *i2c, uint8_t address);
void mylcdi2c_print(char *str);
void mylcdi2c_command(uint8_t cmd);
void mylcdi2c_write(uint8_t cmd);
void mylcdi2c_setCursor(uint8_t row, uint8_t column);
void mylcdi2c_clear();
#endif /* INC_MYLCDI2C_H_ */
