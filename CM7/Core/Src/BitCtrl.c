#include "BitCtrl.h"

enum DriverStates DriverState = DriverOff;
bool UplinkWhenOff = false;
uint8_t MessageName = 0;
bool NewMessage = false;
uint8_t CurrentMessageIndex = 0;

void Setup_BitCtrl(void){
  PWM_Start();
  DriverStop(-1);
}

void DriverStart(int32_t _Cycles){
	BSP_LED_On(LED_GREEN);
	TIM1->BDTR |= TIM_BDTR_AOE;
	DriverState = DriverOn;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);

	if(_Cycles == 0){return;}

	if(_Cycles == -1){
		DriverIndefinite = true;
		return;
	}
	else{
		DriverIndefinite = false;
	}

	CyclesRemaining = _Cycles;
}

void DriverStop(int32_t _Cycles){
	BSP_LED_Off(LED_GREEN);
	TIM1->BDTR &= ~TIM_BDTR_AOE;
	TIM1->BDTR &= ~TIM_BDTR_MOE;
	DriverState = DriverOff;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);

	if(_Cycles == 0){return;}

	if(_Cycles == -1){
		DriverIndefinite = true;
		return;
	}
	else{
		DriverIndefinite = false;
	}

	CyclesRemaining = _Cycles;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(DriverIndefinite){return;}

	if(CyclesRemaining == 0){
		if(!NewMessage){
			CurrentMessageIndex++;
		}
		NewMessage = false;
		if(CurrentMessageIndex == Messages[MessageName].SwitchIndex){
			if(Messages[MessageName].UpLength == 0){
				CurrentMessageIndex = 0;
				UplinkWhenOff = false;
				DriverStop(-1);
				return;
			}
			else{
				UplinkWhenOff = true;
				DriverStart(Messages[MessageName].Cycles[CurrentMessageIndex]);
				return;
			}
		}
		if(CurrentMessageIndex == (Messages[MessageName].SwitchIndex + (Messages[MessageName].UpLength * 2))){
			CurrentMessageIndex = 0;
			UplinkWhenOff = false;
			DriverStop(-1);
			return;
		}
		if(Messages[MessageName].OnOff[CurrentMessageIndex] == 0){
			DriverStop(Messages[MessageName].Cycles[CurrentMessageIndex]);
			if(UplinkWhenOff){
				ADC_Start();
			}
			return;
		}
		else{
			DriverStart(Messages[MessageName].Cycles[CurrentMessageIndex]);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			return;
		}
	}
	CyclesRemaining--;
}
