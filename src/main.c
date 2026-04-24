/*
 * SimGEKI
 * Copyright (c) 2024 SimDevices, Handle
 */

#include "bsp.h"
#include "usb_lib.h"
#include "iap.h"

// Simple delay using NOP instructions
static void Delay_MS(uint32_t ms)
{
  uint32_t i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 12000; j++) { // Approximate 1ms at 96MHz
      __asm__("nop");
    }
  }
}

void IAP_2_APP(void)
{
  NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  NVIC_DisableIRQ(USBWakeUp_IRQn);

  _SetISTR(0);
  _SetCNTR(CNTR_FRES);
  _SetCNTR(CNTR_FRES | CNTR_PDWN);

  USB_Port_Set(DISABLE, DISABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);

  Delay_MS(100);

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

  Delay_MS(5);

  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
}

int main(void)
{
  SystemInit();
  SystemCoreClockUpdate();

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  Delay_MS(10);

  if (Input_Check() != 0) {
    IAP_2_APP();
    while (1) {}
  }

  Set_USBConfig();
  USB_Interrupts_Config();
  USB_Init();

  while (1) {
    if (JMP_FLAG) {
      IAP_2_APP();
      while (1) {}
    }
  }
}
