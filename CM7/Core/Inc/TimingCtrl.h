#ifndef INC_TIMINGCTRL_H_
#define INC_TIMINGCTRL_H_

#include "stdint.h"
#include "stdbool.h"

#define DRIVER_FREQ 214000U
#define ADJUSTED_DRIVER_FREQ DRIVER_FREQ-2000

#define DOWNLINK_0_ON_TIME 100U
#define DOWNLINK_0_OFF_TIME 150U

#define DOWNLINK_1_ON_TIME 100U
#define DOWNLINK_1_OFF_TIME 150U

#define UPLINK_ON_TIME 100U
#define UPLINK_OFF_TIME 100U

#define DRIVER_PERIOD 1000000/ADJUSTED_DRIVER_FREQ
#define DOWNLINK_0_ON_CYCLES (DOWNLINK_0_ON_TIME/(DRIVER_PERIOD))
#define DOWNLINK_0_OFF_CYCLES (DOWNLINK_0_OFF_TIME/(DRIVER_PERIOD))
#define DOWNLINK_1_ON_CYCLES (DOWNLINK_1_ON_TIME/(DRIVER_PERIOD))
#define DOWNLINK_1_OFF_CYCLES (DOWNLINK_1_OFF_TIME/(DRIVER_PERIOD))

#define UPLINK_PREP_CYCLES 3U
#define UPLINK_ON_CYCLES (UPLINK_ON_TIME/(DRIVER_PERIOD))
#define UPLINK_OFF_CYCLES (UPLINK_OFF_TIME/(DRIVER_PERIOD))-UPLINK_PREP_CYCLES

extern uint32_t OnCycles;
extern uint32_t OffCycles;
extern uint32_t CyclesRemaining;
extern bool DriverIndefinite;

#endif /* INC_TIMINGCTRL_H_ */
