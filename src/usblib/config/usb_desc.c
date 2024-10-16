/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : USB Descriptors.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "usb_lib.h"
#include "usb_desc.h"

/* USB Device Descriptors */
const uint8_t USBD_DeviceDescriptor[USBD_SIZE_DEVICE_DESC] = {
    USBD_SIZE_DEVICE_DESC,        // bLength
    0x01,                         // bDescriptorType
    0x10, 0x01,                   // bcdUSB
    0x00,                         // bDeviceClass
    0x00,                         // bDeviceSubClass
    0x00,                         // bDeviceProtocol
    DEF_USBD_UEP0_SIZE,           // bMaxPacketSize0
    VENDOR_ID_L, VENDOR_ID_H,     // 厂商ID
    PRODUCT_ID_L, PRODUCT_ID_H,   // 产品ID
    PRODUCT_BCD_L, PRODUCT_BCD_H, // 设备版本号
    0x01,                         // iManufacturer
    0x02,                         // iProduct
    0x00,                         // iSerialNumber
    0x01,                         // bNumConfigurations
};

/* USB Configration Descriptors */
const uint8_t USBD_ConfigDescriptor[USBD_SIZE_CONFIG_DESC] = {
    /* Configuration Descriptor */
    0x09,                                                     // bLength
    0x02,                                                     // bDescriptorType
    USBD_SIZE_CONFIG_DESC & 0xFF, USBD_SIZE_CONFIG_DESC >> 8, // wTotalLength
    0x01,                                                     // bNumInterfaces
    0x01,                                                     // bConfigurationValue
    0x00,                                                     // iConfiguration (String Index)
    0x80,                                                     // bmAttributes: Bus Powered
    0x32,                                                     // MaxPower: 100mA

    /* interface 0 (HID interface) descriptor */
    0x09, // bLength
    0x04, // bDescriptorType (Interface)
    0x00, // bInterfaceNumber 0
    0x00, // bAlternateSetting
    0x02, // bNumEndpoints 2
    0x03, // bInterfaceClass
    0x00, // bInterfaceSubClass
    0x00, // bInterfaceProtocol
    0x00, // iInterface (String Index)

    /* interface 0 HID descriptor */
    0x09,                                                     // bLength
    0x21,                                                     // bDescriptorType
    0x11, 0x01,                                               // bcdHID
    0x00,                                                     // bCountryCode
    0x01,                                                     // bNumDescriptors
    0x22,                                                     // bDescriptorType
    USBD_SIZE_REPORT_DESC & 0xFF, USBD_SIZE_REPORT_DESC >> 8, // wDescriptorLength

    /* interface 0 endpoint descriptor*/
    0x07,       // bLength
    0x05,       // bDescriptorType (Endpoint)
    0x81,       // bEndpointAddress (IN/D2H)
    0x03,       // bmAttributes (Interrupt)
    0x40, 0x00, // wMaxPacketSize 64
    0x01,       // bInterval 1 (unit depends on device speed)

    /* interface 4 endpoint descriptor */
    0x07,       // bLength
    0x05,       // bDescriptorType (Endpoint)
    0x01,       // bEndpointAddress (OUT/H2D)
    0x03,       // bmAttributes (Interrupt)
    0x40, 0x00, // wMaxPacketSize 64
    0x05,       // bInterval 5 (unit depends on device speed)

};

/* USB String Descriptors */
const uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID] = {
    USBD_SIZE_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04};

/* USB Device String Vendor */
const uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR] = {
    USBD_SIZE_STRING_VENDOR,
    USB_STRING_DESCRIPTOR_TYPE,
    'S', 0, 'i', 0, 'm', 0};

/* USB Device String Product */
const uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT] = {
    USBD_SIZE_STRING_PRODUCT,
    USB_STRING_DESCRIPTOR_TYPE,
    'S', 0, 'i', 0, 'm', 0, 'B', 0, 'o', 0, 'o', 0, 't', 0};

/* HID Report Descriptor */
const uint8_t USBD_HidRepDesc[USBD_SIZE_REPORT_DESC] =
    {
        0x05, 0x01,       // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x00,       // Usage (0x00)
        0xA1, 0x01,       // Collection (Application)
        0x09, 0x00,       //   Usage (0x00)
        0x85, 0xAA,       //   Report ID (170  0xAA)
        0xA1, 0x01,       //   Collection (Application)
        0x09, 0x00,       //     Usage (0x00)
        0x26, 0xFF, 0x00, //     Logical Maximum (255)
        0x75, 0x08,       //     Report Size (8)
        0x15, 0x00,       //     Logical Minimum (0)
        0x95, 0x3F,       //     Report Count (63)
        0x81, 0x02,       //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x00,       //     Usage (0x00)
        0x15, 0x00,       //     Logical Minimum (0)
        0x26, 0xFF, 0x00, //     Logical Maximum (255)
        0x75, 0x08,       //     Report Size (8)
        0x95, 0x3F,       //     Report Count (63)
        0x91, 0x02,       //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,             //   End Collection
        0xC0,             // End Collection
};
