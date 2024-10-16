#include "iap.h"
// #include "ch422.h"
// #include "keyscan.h"
// #include "roller.h"

// #include "debug.h"

#include "usb_lib.h"
#include "usb_prop.h"

#define OUT_EP       ENDP1

#define FLASH_Base   0x08002800 // 10K

#define STATE_SCUESS 0x00
#define STATE_ERROR  0x01
#define STATE_FINISH 0x02

uint8_t Fast_Program_Buf[390];

volatile uint8_t JMP_FLAG = 0;

uint8_t HID_Buffer_OUT[64] = {0x00};
uint8_t HID_Buffer_IN[64]  = {0x00};

DataReceive *receive = (DataReceive *)HID_Buffer_OUT;
DataUpload *upload   = (DataUpload *)HID_Buffer_IN;

// const uint8_t bitPosMap[] = {23, 20, 22, 19, 21, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6};

uint32_t activeAddr = FLASH_Base;

uint8_t codeBuffer[390];
uint16_t codeBuffIndex = 0;

void HIDIO_Receive_Handler()
{
  uint16_t i;

  uint8_t state  = STATE_ERROR;
  uint8_t length = receive->length;

  switch (receive->reportID) {
    // Custom HIDIO
    case 0xAA:
      switch (receive->command) {
        case CMD_IAP_RESET: {
          activeAddr    = FLASH_Base;
          codeBuffIndex = 0;

          state = STATE_SCUESS;
          break;
        }
        case CMD_IAP_PROM: {
          for (i = 0; i < length; i++) {
            codeBuffer[codeBuffIndex + i] = receive->data[i];
          }
          codeBuffIndex += length;
          if (codeBuffIndex >= 256) {
            FLASH_Unlock_Fast();
            FLASH_ErasePage_Fast(activeAddr);
            FLASH_ProgramPage_Fast(activeAddr, (uint32_t *)codeBuffer);
            FLASH_Lock_Fast();

            codeBuffIndex -= 256;
            for (i = 0; i < codeBuffIndex; i++) {
              codeBuffer[i] = codeBuffer[256 + i];
            }
            activeAddr += 0x100;
          }
          state = STATE_SCUESS;

          break;
        }
        case CMD_IAP_PROM_END: {
          for (i = 0; i < (256 - codeBuffIndex); i++) { // 此处i需要是u16，否则CodeLen=0会死循环
            Fast_Program_Buf[codeBuffIndex + i] = 0x00;
          }
          if (codeBuffIndex > 0) {
            FLASH_Unlock_Fast();
            FLASH_ErasePage_Fast(activeAddr);
            FLASH_ProgramPage_Fast(activeAddr, (uint32_t *)codeBuffer);
            FLASH_Lock_Fast();
          }

          activeAddr    = FLASH_Base;
          codeBuffIndex = 0;

          state = STATE_SCUESS;
          break;
        }
        case CMD_IAP_VERIFY: {
          state = STATE_SCUESS;
          for (i = 0; i < length; i++) {
            if (receive->data[i] != *(uint8_t *)(activeAddr + i)) {
              state = STATE_ERROR;
              break;
            }
          }
          activeAddr += length;
          break;
        }
        case CMD_IAP_VERIFY_END: {
          state = STATE_SCUESS;
          break;
        }
        case CMD_IAP_EXIT: {
          JMP_FLAG = 1;

          break;
        }
        default: {
          break;
        }
      }
    default: {
      break;
    }
  }

  upload->reportID = 0xAA;
  upload->command  = receive->command;
  upload->length   = 1;
  upload->data[0]  = state;

  HIDIO_Upload();
}

void HIDIO_Upload()
{
  USBD_ENDPx_DataUp(OUT_EP, HID_Buffer_IN, 64);
}