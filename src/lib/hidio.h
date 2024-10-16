#ifndef __HIDIO_H_
#define __HIDIO_H_

#include "bsp.h"
// #include "keyscan.h"

// Need -fshort-enums

typedef enum {
  NORMAL     = 0x00,
  JAM        = 0x01,
  DISCONNECT = 0x02,
  BUSY       = 0x03,
} __packed CoinCondition;

typedef enum {
  SET_COMM_TIMEOUT   = 0x01,
  SET_SAMPLING_COUNT = 0x02,
  CLEAR_BOARD_STATUS = 0x03,
  SET_GENERAL_OUTPUT = 0x04,
  SET_PWM_OUTPUT     = 0x05,

  SET_ROLLER_OFFSET = 0xA0,
  UPDATE_FIRMWARE   = 0xF1,
} __packed HidioCommand;

typedef struct {
  CoinCondition condition;
  uint8_t count;
} __packed CoinData;

typedef struct {
  uint8_t reportID;
  uint16_t analog[8];
  uint16_t rotary[4];
  CoinData coin[2];
  uint8_t buttons[4];
  uint8_t systemStatus;
  uint8_t usbStatus;
  uint8_t _unused[29];
} __packed DataUpload;

typedef struct {
  uint8_t reportID;
  HidioCommand command;
  uint8_t payload[62];
} __packed DataReceive;

// void HIDIO_Init();
void HIDIO_Receive_Handler();
void HIDIO_Upload();
// void HIDIO_Update();

extern uint8_t HID_Buffer_OUT[64];
extern uint8_t HID_Buffer_IN[64];

#endif // !__HIDIO_H_