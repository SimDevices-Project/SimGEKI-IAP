#ifndef __HIDIO_H_
#define __HIDIO_H_

#include "bsp.h"
// #include "keyscan.h"

// Need -fshort-enums

typedef enum {
  CMD_IAP_RESET      = 0xA1,
  CMD_IAP_PROM       = 0xA2,
  CMD_IAP_PROM_END   = 0xA3,
  CMD_IAP_VERIFY     = 0xA4,
  CMD_IAP_VERIFY_END = 0xA5,
  CMD_IAP_EXIT       = 0xF0,
} __packed IAPCmd;

typedef struct {
  uint8_t reportID;
  IAPCmd command;
  uint8_t length;
  uint8_t data[61];
} __packed DataUpload;

typedef struct {
  uint8_t reportID;
  IAPCmd command;
  uint8_t length;
  uint8_t data[61];
} __packed DataReceive;

// void HIDIO_Init();
void HIDIO_Receive_Handler();
void HIDIO_Upload();
// void HIDIO_Update();

extern uint8_t HID_Buffer_OUT[64];
extern uint8_t HID_Buffer_IN[64];

extern volatile uint8_t JMP_FLAG;

#endif // !__HIDIO_H_