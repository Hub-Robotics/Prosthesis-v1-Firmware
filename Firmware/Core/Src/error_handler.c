/*******************************************************************************
*
* TITLE:	Error Handler for Prosthesis v1
* AUTHOR:	Greg Berkeley
* RELEASE:	12/15/2024
*
* NOTES
* 1. Summary of LED status below.
* 		- Green		= no error
* 		- Yellow	= initialization error
* 		- Orange	= EPOS4 abort error
* 		- Red		= EPOS4 fault error
*
*******************************************************************************/

#include "error_handler.h"
#include "main.h"

typedef enum
{
	NoError,
	AnkleEncoderInitError,
	AnkleMotorControllerInitError,
	AnkleMotorControllerFaultError,
	AnkleMotorControllerAbortError,
	AnkleCAN_ControllerInitError,
	KneeEncoderInitError,
	KneeMotorControllerInitError,
	KneeMotorControllerFaultError,
	KneeMotorControllerAbortError,
	KneeCAN_ControllerInitError,
	IMU_InitError
} LED_Code_e;

static LED_Code_e CM_ledCode = NoError;

void ErrorHandler_AS5145B(EncoderIndex_e deviceIndex, AS5145B_Error_e error)
{
	if(deviceIndex == AnkleEncoderIndex)
		CM_ledCode = AnkleEncoderInitError;
	else
		CM_ledCode = KneeEncoderInitError;

	while(1);
}

void ErrorHandler_EPOS4(MotorControllerIndex_e deviceIndex, EPOS4_Error_e error)
{
	if(deviceIndex == AnkleMotorControllerIndex)
	{
		if(error == EPOS4_FaultError)
			CM_ledCode = AnkleMotorControllerFaultError;
		else if(error == EPOS4_AbortError)
			CM_ledCode = AnkleMotorControllerAbortError;
		else
			CM_ledCode = AnkleMotorControllerInitError;
	}
	else
	{
		if(error == EPOS4_FaultError)
			CM_ledCode = KneeMotorControllerFaultError;
		else if(error == EPOS4_AbortError)
			CM_ledCode = KneeMotorControllerAbortError;
		else
			CM_ledCode = KneeMotorControllerInitError;
	}

	while(1);
}

void ErrorHandler_MCP25625(uint8_t deviceIndex, MCP25625_Error_e error)
{
	if(deviceIndex == AnkleCAN_ControllerIndex)
		CM_ledCode = AnkleCAN_ControllerInitError;
	else
		CM_ledCode = KneeCAN_ControllerInitError;

	while(1);
}

void ErrorHandler_MPU925x(MPU925x_Error_e error)
{
	CM_ledCode = IMU_InitError;
	while(1);
}


/*******************************************************************************
* END
*******************************************************************************/