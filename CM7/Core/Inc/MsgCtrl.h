#ifndef INC_MSGCTRL_H_
#define INC_MSGCTRL_H_

#include "TimingCtrl.h"
#include "stdint.h"
#include "BitCtrl.h"

enum MessageList{
	TestMessage,
	NumberOfMessages
};

enum MessageDirection{
	Downlink,
	Uplink
};

struct Message{
	uint32_t DownLength;
	uint32_t UpLength;
	uint32_t Data;
	uint32_t Cycles[64];
};

extern struct Message Messages[NumberOfMessages];

void Setup_MsgCtrl(void);

void SendMessage(uint8_t _Message);

#endif /* INC_MSGCTRL_H_ */
