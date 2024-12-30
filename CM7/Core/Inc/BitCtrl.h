#ifndef INC_BITCTRL_H_
#define INC_BITCTRL_H_

#include "stdint.h"
#include "stdbool.h"
#include "tim.h"
#include "adc.h"
#include "MsgCtrl.h"

enum DriverStates{
	DriverOn,
	DriverOff,
	PrepForUplink
};

extern enum DriverStates DriverState;
extern bool UplinkWhenOff;
extern uint8_t MessageName;

void Setup_BitCtrl(void);

void DriverStart(int32_t _Cycles);

void DriverStop(int32_t _Cycles);

#endif /* INC_BITCTRL_H_ */
