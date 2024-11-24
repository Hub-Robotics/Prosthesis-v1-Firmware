/*******************************************************************************
*
* See source file for more information.
*
*******************************************************************************/

#ifndef INC_PROSTHESIS_CONTROL_H_
#define INC_PROSTHESIS_CONTROL_H_

// i can see this in epos4.c??
typedef enum
{
	none,
	readOnly,
	constantMotorTorque100Nmm,
	magneticEncoderBias,
	impedanceControl
} TestPrograms_t;

typedef struct
{
	enum
	{
		left,
		right
	} Side;
	enum
	{
		ankle,
		combined,
		knee
	} Joint;
	uint8_t ankleMotorId;
	uint8_t kneeMotorId;
} Prosthesis_t;

extern uint8_t isProsthesisControlRequired; // ??

void InitProsthesisControl(Prosthesis_t *Options);
void RunProsthesisControl(void);
void RequireTestProgram(TestPrograms_t option);


/*******************************************************************************
 * END
 ******************************************************************************/

#endif /* INC_PROSTHESIS_CONTROL_H_ */
