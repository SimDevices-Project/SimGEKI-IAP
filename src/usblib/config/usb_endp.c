/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_endp.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : Endpoint routines
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
#include "usb_prop.h"

// #include "cdc.h"

#include "iap.h"

/*********************************************************************
 * @fn      EP1_IN_Callback
 *
 * @brief  Endpoint 1 IN.
 *
 * @return  none
 */
void EP1_IN_Callback(void)
{
}

/*********************************************************************
 * @fn      EP1_OUT_Callback
 *
 * @brief  Endpoint 1 OUT.
 *
 * @return  none
 */
void EP1_OUT_Callback(void)
{
  if (USB_SIL_Read(EP1_OUT, HID_Buffer_OUT) == 64) {
    HIDIO_Receive_Handler();
  }
  SetEPRxValid(ENDP1);
}

/*********************************************************************
 * @fn      USBD_ENDPx_DataUp
 *
 * @brief  USBD ENDPx DataUp Function
 *
 * @param   endp - endpoint num.
 *          *pbuf - A pointer points to data.
 *          len - data length to transmit.
 *
 * @return  data up status.
 */
uint8_t USBD_ENDPx_DataUp(uint8_t endp, uint8_t *pbuf, uint16_t len)
{
  switch (endp) {
    case ENDP1: {
      if (GetEPTxStatus(ENDP1) == EP_TX_VALID) {
        return USB_ERROR;
      }
      USB_SIL_Write(EP1_IN, pbuf, len);
      SetEPTxStatus(ENDP1, EP_TX_VALID);
      break;
    }
    default:
      return USB_ERROR;
  }
  return USB_SUCCESS;
}
