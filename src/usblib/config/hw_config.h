/********************************** (C) COPYRIGHT *******************************
 * File Name          : hw_config.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : Configuration file for USB.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/ 
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "usb_type.h" 

void Set_USBConfig(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Port_Set(FunctionalState NewState, FunctionalState Pin_In_IPU);

#endif /* __HW_CONFIG_H */ 








