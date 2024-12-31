#include "MsgCtrl.h"

struct Message Messages[NumberOfMessages];

struct Message Test_ = {
		.DownLength = 4,
		.Data = 0b0101,
		.UpLength = 2
};

void Setup_MsgCtrl(void){
	Messages[TestMessage] = Test_;

	for(int i=0; i<NumberOfMessages; i++){
		for(int j=0; j<Messages[i].DownLength; j++){
			if((Messages[i].Data >> j) & 1){
				Messages[i].Cycles[(Messages[i].DownLength - j)*2 - 2] = DOWNLINK_1_OFF_CYCLES;
				Messages[i].Cycles[(Messages[i].DownLength - j)*2 - 1] = DOWNLINK_1_ON_CYCLES;
			}
			else{
				Messages[i].Cycles[(Messages[i].DownLength - j)*2 - 2] = DOWNLINK_0_OFF_CYCLES;
				Messages[i].Cycles[(Messages[i].DownLength - j)*2 - 1] = DOWNLINK_0_ON_CYCLES;
			}
		}
		if(Messages[i].UpLength != 0){
			Messages[i].Cycles[Messages[i].DownLength * 2] = UPLINK_PREP_CYCLES;
			for(int j=0; j<Messages[i].UpLength; j++){
				Messages[i].Cycles[(Messages[i].DownLength * 2) + (j*2) + 1] = UPLINK_ON_CYCLES;
				Messages[i].Cycles[(Messages[i].DownLength * 2) + (j*2) + 2] = UPLINK_OFF_CYCLES;
			}
		}
	}
}

void SendMessage(uint8_t _Message){
	MessageName = _Message;
	NewMessage = true;
	CyclesRemaining = 0;
	DriverIndefinite = false;
}


