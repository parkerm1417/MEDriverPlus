#include "MsgCtrl.h"

struct Message Test_ = {
		.Direction = Downlink,
		.Length = 4,
		.Data = 0b1010
};

void Setup_MsgCtrl(void){
	Messages[TestMessage] = Test_;

	for(int i=0; i<NumberOfMessages; i++){
		if(Messages[i].Direction == Downlink){
			for(int j=Messages[i].Length - 1; j>=0; j--){
				if((Messages[i].Data >> j) & 1){
					Messages[i].Cycles[Messages[i].Length - j - 1] = DOWNLINK_1_OFF_CYCLES;
					Messages[i].Cycles[Messages[i].Length - j] = DOWNLINK_1_ON_CYCLES;
				}
				else{
					Messages[i].Cycles[Messages[i].Length - j - 1] = DOWNLINK_0_OFF_CYCLES;
					Messages[i].Cycles[Messages[i].Length - j] = DOWNLINK_0_ON_CYCLES;
				}
			}
		}
		else{
			for(int j=0; j<Messages[i].Length; j++){
				Messages[i].Cycles[j*2] = UPLINK_ON_CYCLES;
				Messages[i].Cycles[(j*2) + 1] = UPLINK_OFF_CYCLES;
			}
		}
	}
}

void SendMessage(uint8_t _Message){

	CyclesRemaining = 0;
	DriverIndefinite = false;

}


