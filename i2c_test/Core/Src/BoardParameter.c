/*
 * BoardParameter.c
 *
 *  Created on: May 29, 2024
 *      Author: ADMIN
 */

#include "BoardParameter.h"
I2C_HandleTypeDef *port;
static uint8_t rxBuffer[5] = {0};
static uint8_t txBuffer[5] = {0};

static BoardData brdData;

static inline void CheckError(){
	if(!port) while(1);
}

static inline void ResetBuffer(){

}

void BrdParam_Init(I2C_HandleTypeDef *hi2c){
	port = hi2c;
	CheckError();
}

void BrdParam_HandleListenIRQ(I2C_HandleTypeDef *hi2c, uint8_t reg)
{
	if(hi2c->Instance != port->Instance) return;
	switch(reg){
	case DEV_REG_SPEED_KP:
//		HAL_I2C_Slave_Receive_IT(port, rxBuffer, sizeof(float));
		break;
	}
}


void BrdParam_HandleReceiveData(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance != port->Instance) return;

}
