/*
 * SimGEKI
 * Copyright (c) 2024 SimDevices, Handle
 */

#include "bsp.h"

#include "usb_lib.h"

#include "debug.h"

#include "iap.h"

void IAP_2_APP(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
  Delay_Ms(30);
  NVIC_EnableIRQ(Software_IRQn);
  NVIC_SetPendingIRQ(Software_IRQn);
}

/*********************************************************************
 * @fn      Input_Check
 *
 * @brief   Check Input state
 *
 * @return  1 - APP
 *          0 - IAP
 */
uint8_t Input_Check(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  Delay_Ms(5);

  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
}

int main(void)
{
  SystemInit();
  SystemCoreClockUpdate();

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  Delay_Init();

  Set_USBConfig();
  USB_Init();
  USB_Interrupts_Config();

  Delay_Ms(20);

  if (Input_Check() != 0) {
    JMP_FLAG = 1;
  }
  while (1) {
    if (JMP_FLAG) {
      IAP_2_APP();
      while (1) {}
    }
  }
}
