#include "MEDriverPlusMain.h"

void Setup(void){
	Setup_BitCtrl();
//	Setup_MsgCtrl();
	DAC_Start(2048);
}

void Loop(void){
    if (BspButtonState == BUTTON_PRESSED)
    {
    	if(DriverState == DriverOn){
    		DriverStop(-1);
    	}
    	else if(DriverState == DriverOff){
    		DriverStart(-1);
    	}
      BspButtonState = BUTTON_RELEASED;
    }
}

