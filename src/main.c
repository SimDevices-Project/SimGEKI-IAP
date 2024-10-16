/*
 * SimGEKI
 * Copyright (c) 2024 SimDevices, Handle
 */

#include "bsp.h"

#include "usb_lib.h"

#include "debug.h"

int main(void)
{
  SystemInit();
  SystemCoreClockUpdate();

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  Delay_Init();

  Set_USBConfig();
  USB_Init();
  USB_Interrupts_Config();

  Delay_Ms(50);

  while (1) {

  }
}
