#include "main.h"
#include "can.h"
#include "Motor.h"
#include "usart.h"
extern CAN_RxHeaderTypeDef RxHeader;
extern uint8_t RxData[8];
extern M3508_Motor motor;
 void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
 {
     if(hcan->Instance == CAN1)
     {
         motor.canRxMsgCallback(RxData);
         std::vector<float> motor_message=motor.Get_motor_message();
         size_t size_motor_message=motor_message.size()*sizeof(float);
         uint8_t* motor_message_uint8=reinterpret_cast<uint8_t*>(motor_message.data());
         HAL_UART_Transmit_DMA(&huart6,motor_message_uint8,size_motor_message);
         HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,&RxHeader, RxData);
    }

}