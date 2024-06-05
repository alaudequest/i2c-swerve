/*
 * BoardParameter.h
 *
 *  Created on: May 29, 2024
 *      Author: ADMIN
 */

#ifndef INC_BOARDPARAMETER_H_
#define INC_BOARDPARAMETER_H_
#include "main.h"
#include "stdbool.h"

typedef enum ModePID {
	MODE_PID_SPEED,
	MODE_PID_ANGLE
} ModePID;

typedef enum SwerveParamRegister {
	DEV_REG_SPEED_KP = 1,
	DEV_REG_SPEED_KI,
	DEV_REG_SPEED_KD,

	DEV_REG_ANGLE_KP,
	DEV_REG_ANGLE_KI,
	DEV_REG_ANGLE_KD,

	DEV_REG_TARGET_SPEED,
	DEV_REG_TARGET_ANGLE,
	DEV_REG_MODE,
} SwerveParamRegister;

typedef struct ParamPID {
	float kp;
	float ki;
	float kd;
} ParamPID;

typedef struct BoardData {
	ParamPID pidPosition;
	ParamPID pidAngle;
	float targetSpeed;
	float targetAngle;
	bool mode;
} BoardData;
void BrdParam_SetTransferDirection(uint8_t TransferDirection);
uint8_t* BrdParam_GetAddrRxBuffer();
uint8_t* BrdParam_GetAddrTxBuffer();
void BrdParam_HandleReceiveDataCallback(I2C_HandleTypeDef *hi2c);

#endif /* INC_BOARDPARAMETER_H_ */
