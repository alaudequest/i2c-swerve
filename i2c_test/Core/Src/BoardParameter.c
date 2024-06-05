/*
 * BoardParameter.c
 *
 *  Created on: May 29, 2024
 *      Author: ADMIN
 */

#include "BoardParameter.h"
#include "string.h"
I2C_HandleTypeDef *port;
static uint8_t rxBuffer[5] = {0};
static uint8_t txBuffer[5] = {0};

static BoardData brdData;
static uint8_t _TransferDirection;

static void SetValueParam(uint8_t value, uint8_t reg);
static inline uint8_t GetValueParam(uint8_t);
static inline void CheckError() {
	if (!port)
		while (1);
}

static inline void ResetRxBuffer() {
	memset(rxBuffer, 0, sizeof(rxBuffer));
}

static inline void ResetTxBuffer() {
	memset(txBuffer, 0, sizeof(txBuffer));
}

uint8_t* BrdParam_GetAddrRxBuffer() {
	return rxBuffer;
}

uint8_t* BrdParam_GetAddrTxBuffer() {
	return txBuffer;
}

void BrdParam_Init(I2C_HandleTypeDef *hi2c) {
	port = hi2c;
	CheckError();
}

void BrdParam_SetTransferDirection(uint8_t TransferDirection) {
	_TransferDirection = TransferDirection;
}

void BrdParam_HandleReceiveDataCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c->Instance != port->Instance)
		return;

	if (_TransferDirection == I2C_DIRECTION_TRANSMIT) {
		uint8_t reg = rxBuffer[0];
		uint8_t value = rxBuffer[1];
		SetValueParam(value, reg);
		ResetRxBuffer();
	}
	else if (_TransferDirection == I2C_DIRECTION_RECEIVE) {
		uint8_t reg = rxBuffer[0];
		uint8_t value = GetValueParam(reg);
		memcpy(txBuffer, &value, sizeof(value));
		HAL_I2C_Slave_Seq_Transmit_IT(hi2c, txBuffer, sizeof(value), I2C_FIRST_AND_LAST_FRAME);
	}

}

static void SetValueParam(uint8_t value, uint8_t reg) {
	switch (reg) {
	case DEV_REG_TARGET_SPEED:
		brdData.targetSpeed = value;
		break;
	case DEV_REG_TARGET_ANGLE:
		brdData.targetAngle = value;
		break;
	}
}

static inline uint8_t GetValueParam(uint8_t reg) {
	switch (reg) {
	case DEV_REG_TARGET_SPEED:
		return brdData.targetSpeed;
		break;
	case DEV_REG_TARGET_ANGLE:
		return brdData.targetAngle;
		break;
	}
	return 0;
}

