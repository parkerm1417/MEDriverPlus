#include "MsgCtrl.h"

struct Message Messages[NumberOfMessages];

struct Message Test_ = {
		.DownLength = 5,
		.Data = 0b01010,
		.UpLength = 2
};

void Setup_MsgCtrl(void){
	Messages[TestMessage] = Test_;
	int idx_ctr = 0;

	for(int i=0; i<NumberOfMessages; i++){
		for(int j=0; j<Messages[i].DownLength; j++){
			if((Messages[i].Data >> j) & 1){
				Messages[i].Cycles[idx_ctr] = DOWNLINK_1_ON_CYCLES;
				Messages[i].OnOff[idx_ctr] = 1;
				idx_ctr++;
			}
			else{
				Messages[i].Cycles[idx_ctr] = DOWNLINK_0_ON_CYCLES;
				Messages[i].OnOff[idx_ctr] = 1;
				idx_ctr++;

				Messages[i].Cycles[idx_ctr] = DOWNLINK_0_OFF_CYCLES;
				Messages[i].OnOff[idx_ctr] = 0;
				idx_ctr++;
			}
		}
		Messages[i].SwitchIndex = idx_ctr;
		if(Messages[i].UpLength != 0){
			Messages[i].Cycles[idx_ctr] = UPLINK_PREP_CYCLES;
			idx_ctr++;
			for(int j=0; j<Messages[i].UpLength; j++){
				Messages[i].Cycles[idx_ctr] = UPLINK_ON_CYCLES;
				Messages[i].OnOff[idx_ctr] = 1;
				idx_ctr++;

				Messages[i].Cycles[idx_ctr] = UPLINK_OFF_CYCLES;
				Messages[i].OnOff[idx_ctr] = 0;
				idx_ctr++;
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


