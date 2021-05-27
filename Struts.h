#ifndef Struts_H
#define Struts_H

#ifdef __cplusplus
 extern "C" {
#endif

/*
    Struts.h : typical serial and ethernet strructures and 
    other data communication objects 
    (anything used within interrupt and gc_event handlers)

    Version : @(#) 1.0
    Copyright (C) 2020 A C P Avaiation Walkerburn Scotland
    
    This is a massive common library and i'll strip this out for just what you need for here
    just comment out the other stuff for now
*/
#include "definitions.h"
#include "SBGC_Command.h"
#include "inttypes.h"
#include <stdint.h>
#include "rion.h"
#include "robot.h"

/* ====== maximum packet sizes ===================== */
#ifndef XS_CMD_MAX_BYTES
#define XS_CMD_MAX_BYTES 50u
#endif
#ifndef RC_CMD_MAX_BYTES1
#define RC_CMD_MAX_BYTES1 64u
#endif
#ifndef ARTNET4_MAX_LEN
#define ARTNET4_MAX_LEN 512U
#endif
#ifndef GEF_EGD_UDP_MAX_LEN
#define GEF_EGD_UDP_MAX_LEN 1450U
#endif

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define STRUTPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define STRUTPACKED __attribute__((packed))                                   /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define STRUTPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define STRUTPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define STRUTPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif


/* =============== comon math objects ================================= */
#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t x;
  float32_t y;
  float32_t z;
} Vectr;
#else
STRUTPACKED(
typedef struct {
  float32_t x;
  float32_t y;
  float32_t z;
}) Vectr;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t x;
  uint32_t y;
} u32point_t;
#else
STRUTPACKED(
typedef struct {
  uint32_t x;
  uint32_t y;
}) u32point_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float64_t i;
  float64_t j;
} xyline_t;
#else
STRUTPACKED(
typedef struct {
  float64_t i;
  float64_t j;
}) xyline_t;
#endif

#if defined(D_FT900)                                                            /* shuffle exchange switch operator */
typedef struct STRUTPACKED {
  xyline_t a;
  xyline_t b;
} ML_weight_t;
#else
STRUTPACKED(
typedef struct {
  xyline_t a;
  xyline_t b;
}) ML_weight_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float64_t x;
  float64_t y;
  float64_t z;
} dVectr;
#else
STRUTPACKED(
typedef struct {
  float64_t x;
  float64_t y;
  float64_t z;
}) dVectr;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  dVectr a;
  dVectr b;
  dVectr c;
} Matrix3f64_t;
#else
STRUTPACKED(
typedef struct {
  dVectr a;
  dVectr b;
  dVectr c;
}) Matrix3f64_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t m[4u][4u];
} mat44;
#else
STRUTPACKED(
typedef struct {
  float32_t m[4u][4u];
}) mat44;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t m[3u][3u];
} mat33;
#else
STRUTPACKED(
typedef struct {
  float32_t m[3u][3u];
}) mat33;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t x;
  float32_t y;
  float32_t z;
  float32_t w;
} quat;
#else
STRUTPACKED(
typedef struct {
  float32_t x;
  float32_t y;
  float32_t z;
  float32_t w;
}) quat;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float64_t x;
  float64_t y;
  float64_t z;
  float64_t w;
} dquat;
#else
STRUTPACKED(
typedef struct {
  float64_t x;
  float64_t y;
  float64_t z;
  float64_t w;
}) dquat;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  dquat a;
  dquat b;
  dquat c;
  dquat d;
} Matrix4d64_t;
#else
STRUTPACKED(
typedef struct {
  dquat a;
  dquat b;
  dquat c;
  dquat d;
}) Matrix4d64_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
//  uint16_t Baud;                                                              //USB port Baud rate in mikroE for pic32 can not set it ??
  unsigned char ReadBuffer[32u];                                                //Packet Read from USB link
  unsigned char WriteBuffer[32u];                                               //Packet Written to USB link
  unsigned char ReadBufTmp[16u];                                                //store for partial with jrt they can all be set to 16 bytes max if needed
  int8_t Bytes_In;                                                              //Length of UART packet
  int8_t Bytes_In_Read2;
  uint16_t Packet_In_Err;
  uint8_t State;                                                                //Status of the Packet Read in (See Definitions)
  uint8_t WriteState;
  uint8_t prevState;
  uint16_t writeTimeOut;
} USBObject_t;
#else
 STRUTPACKED (
typedef struct{
//  uint16_t Baud;                                                              //USB port Baud rate in mikroE for pic32 can not set it ??
  unsigned char ReadBuffer[32u];                                                //Packet Read from USB link
  unsigned char WriteBuffer[32u];                                               //Packet Written to USB link
  unsigned char ReadBufTmp[16u];                                                //store for partial with jrt they can all be set to 16 bytes max if needed
  int8_t Bytes_In;                                                              //Length of UART packet
  int8_t Bytes_In_Read2;
  uint16_t Packet_In_Err;
  uint8_t State;                                                                //Status of the Packet Read in (See Definitions)
  uint8_t WriteState;
  uint8_t prevState;
  uint16_t writeTimeOut;
 }) USBObject_t;                                                                /* general function serial object allows up to 64 bytes for message */
#endif

typedef enum {
   USB_NO_DATA_READ = 0u,                                                       // Node is performing its main functions.
   USB_PACKET_READ_DATA = 1u,                                                   // usb read a data packet
   USB_PACKET_READ_CONFIG = 2u,                                                 // usb read a config reply message
   USB_PARTIAL_READ_DATA = 3u,                                                  // usb partially read a data packet
   USB_PARTIAL_READ_CONFIG = 4u,                                                // usb partially read config reply message
   USB_PACKET_DATA_COMPLETE = 5u,                                               // usb data message has been processed
   USB_PACKET_CONFIG_COMPLETE = 6u,                                             // usb start/stop config message has been processed
   USB_DATA_CORRUPT = 7u                                                        // corrupt message has been collected
} usbModeClass;                                                                 // defines the current mode class for reading USB

typedef enum {
   USB_NO_DATA_WRITE = 0u,                                                      // Node is performing its main functions.
   USB_CONFIG_WRITE_START = 1u,                                                 // usb writes a data packet to start polling with the measurment at the desired frequency
   USB_CONFIG_WRITE_STOP = 2u,                                                  // usb writes a message to stop polling with the data measurement result
   USB_CONFIG_SETUP = 3u,                                                       // copy the composed message to the send buffer
   USB_SEND_FAIL = 4u,                                                          // fail to send reply from usb send function
   USB_SEND_CONFIG_PACKET = 5u,                                                 // send the configuration packet via the usb port
   USB_SENT_CONFIG_PACKET = 6u,                                                 // sent the configuration packet via the usb port wait for confirmation message back
   USB_CONFIG_COMPLETE = 7u                                                     // complete or holding state
} usbWriteClass;                                                                // defines the current mode class for writing USB

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t Baud;                                                                //UART port Baud rate
  uint8_t Enable;                                                               //Enable UART
  unsigned char Buffer[64u];                                                    //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint16_t Index_Was;                                                           //The last index was
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
} SerialObject_t;
#else
 STRUTPACKED (
typedef struct{
  uint16_t Baud;                                                                //UART port Baud rate
  uint8_t Enable;                                                               //Enable UART
  unsigned char Buffer[64u];                                                    //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint16_t Index_Was;                                                           //The last index was
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
 }) SerialObject_t;                                                             /* general function serial object allows up to 64 bytes for message */
#endif

#if defined(NMEA0183_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t Baud;                                                                //UART port Baud rate
  unsigned char Buffer[NMEA0183_MAX_MSG_LEN];                                   //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
} SerialNMEA0183Object_t;
#else
 STRUTPACKED (
typedef struct{
  uint32_t Baud;                                                                //UART port Baud rate
  unsigned char Buffer[NMEA0183_MAX_MSG_LEN];                                   //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
 }) SerialNMEA0183Object_t;
#endif

#endif

#if defined(LWNX_LIDDAR_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t Baud;                                                                //UART port Baud rate
//  unsigned char Buffer[1024U];                                                //Buffer the Packet this is not used here we use the LwNxResponse
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
} SerialLwNxObject_t;
#else
 STRUTPACKED (
typedef struct{
  uint32_t Baud;                                                                //UART port Baud rate
//  unsigned char Buffer[1024U];                                                //Buffer the Packet this is not used here we use the LwNxResponse
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
 }) SerialLwNxObject_t;                                                         /* LwNx receiver up to 1024 bytes can be received in lwResponsePacket no bytes are stored here */
#endif

#endif

#if defined(GEF_EGD_PLC)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint8_t  Enable;                                                              //Enable UART
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char UDP_Buffer[GEF_EGD_UDP_MAX_LEN];                                //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    //how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       //how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthEGDUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint8_t  Enable;                                                              //Enable UART
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char UDP_Buffer[GEF_EGD_UDP_MAX_LEN];                                //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    //how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       //how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthEGDUDPObject_t;
#endif

#endif

#if (defined(SBGC_GIMBAL_HMI) || defined(SBGC_GIMBAL_JOY))

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               //Enable UART
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char UDP_Buffer[SBGC_CMD_MAX_BYTES];                                 //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    //how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       //how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthSBGCUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               //Enable UART
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char UDP_Buffer[SBGC_CMD_MAX_BYTES];                                 //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    //how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       //how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthSBGCUDPObject_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t Baud;                                                                //UART port Baud rate
  uint8_t Enable;                                                               //Enable UART
  unsigned char Buffer[SBGC_CMD_MAX_BYTES];                                     //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint16_t Index_Was;                                                           //The last index was
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
} SerialSBGCObject_t;
#else
 STRUTPACKED (
typedef struct{
  uint32_t Baud;                                                                //UART port Baud rate
  uint8_t Enable;                                                               //Enable UART
  unsigned char Buffer[SBGC_CMD_MAX_BYTES];                                     //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint16_t Index_Was;                                                           //The last index was
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
 }) SerialSBGCObject_t;                                                         /* SimpleBGC receiver up to 255 bytes per message */
#endif

#endif

#if defined(USE_MAVLINK)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char Buffer[MAV_MAX_MSG_LEN];                                        //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t  UDP_Packets_Sent;                                                   //how many packets we have sent.
  uint16_t  UDP_Byte_Sent;                                                      //how many Bytes we have sent.
  uint16_t  Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthMavlinkUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           //Ethernet port packets will come from
  uint16_t Dest_Port;                                                           //Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            //Ethernet Packat acknowledgment port
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  unsigned char Buffer[MAV_MAX_MSG_LEN];                                        //Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            //Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       //Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        //How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       //How many times we has to retry sending a packet
  uint16_t  UDP_Packets_Sent;                                                   //how many packets we have sent.
  uint16_t  UDP_Byte_Sent;                                                      //how many Bytes we have sent.
  uint16_t  Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthMavlinkUDPObject_t;
#endif

typedef enum {
   MAV_TO_ARDUPILOT = 0u,                                                       // send to ardupilot
   MAV_TO_GROUND1 = 1u,                                                         // send to ground control
   MAV_TO_JOY = 2u,                                                             // send to joystick
   MAV_TO_FLIGHT = 3u,                                                          // send to flight controller
   MAV_TO_FIREGS = 4u,                                                          // send to fire ground station
   MAV_NUM_OF_NODES
} mavSinkClass;                                                                 // defines possible current mavlink sinks for receiving messages over UDP

#if defined(SERIAL_MAVLINK)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t Baud;                                                                //UART port Baud rate
  unsigned char Buffer[MAV_MAX_MSG_LEN];                                        //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
} SerialMavObject_t;
#else
 STRUTPACKED (
typedef struct{
  uint32_t Baud;                                                                //UART port Baud rate
  unsigned char Buffer[MAV_MAX_MSG_LEN];                                        //Buffer the Packet
  uint16_t Index;                                                               //Packet Index
  uint8_t Len;                                                                  //Length of UART packet
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint16_t Buffer_Overrun;                                                      // How many timer we had a buffer overrun
  uint16_t Framing_Error;                                                       /* Framing errors  */
  uint16_t Parity_Error;                                                        /* Parity errors */
  uint8_t State;                                                                //Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       //Enable UART Timeoute
  unsigned char Msg_id_recv;                                                    // Message Id received.
 }) SerialMavObject_t;                                                          /* mavlink receiver up to 279 bytes per message */
#endif

#endif

#endif  /* end mavlink */

#if defined(CAMERA_TYPE)
#if (CAMERA_TYPE == XS_CAM)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  unsigned char   Enable;                                                       // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[XS_CMD_MAX_BYTES];                                   // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthXSUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  unsigned char   Enable;                                                       // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[XS_CMD_MAX_BYTES];                                   // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthXSUDPObject_t;
#endif

#endif
#endif

#if defined(RUN_CAM_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[RC_CMD_MAX_BYTES1];                                  // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthRunCUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[RC_CMD_MAX_BYTES1];                                  // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthRunCUDPObject_t;
#endif

#endif

#if defined(CBOR_COMS_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[CoAP_CMD_MAX_BYTES];                                 // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthCoAPUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[CoAP_CMD_MAX_BYTES];                                 // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthCoAPUDPObject_t;
#endif

#endif

#if defined(ART_NET_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t  Index;                                                              // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[ARTNET4_MAX_LEN];                                    // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthArtNetUDPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Ethernet port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t  Index;                                                              // Packet Index
  uint8_t Len;                                                                  // Length of UART packet
  unsigned char UDP_Buffer[ARTNET4_MAX_LEN];                                    // Buffer for incoming UDP packet
  uint8_t UDP_Index;                                                            // Index for incoming UDP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t UDP_Buffer_Len;                                                       // Length of UDP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t UDP_CRC[5u];                                                          // ACK CRC packet
  uint8_t UDP_CRC_Index;
  uint8_t UDP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t UDP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t UDP_Send_Slow_ACK_Timeout;
  uint8_t UDP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t UDP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t UDP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t UDP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthArtNetUDPObject_t;
#endif

#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint16_t Index_Was;                                                           // The last index was
  uint8_t Len;                                                                  // Length of UART packet
  uint8_t TCP_Buffer[TCP_IP_MAX_BYTES];                                         // Buffer for incoming TCP packet
  uint8_t TCP_Index;                                                            // Index for incoming TCP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t TCP_Buffer_Len;                                                       // Length of TCP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t TCP_CRC[5u];                                                          // ACK CRC packet
  uint8_t TCP_CRC_Index;
  uint8_t TCP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t TCP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t TCP_Send_Slow_ACK_Timeout;
  uint8_t TCP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t TCP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t TCP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t TCP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
} EthTCPObject_t;
#else
STRUTPACKED (
typedef struct{
  uint16_t From_Port;                                                           // Ethernet port packets will come from
  uint16_t Dest_Port;                                                           // Etherner port packets will be sent to
  uint16_t ACK_Port;                                                            // Ethernet Packat acknowledgment port
  uint8_t Enable;                                                               // Enable UART
  uint16_t Index;                                                               // Packet Index
  uint16_t Index_Was;                                                           // The last index was
  uint8_t Len;                                                                  // Length of UART packet
  uint8_t TCP_Buffer[TCP_IP_MAX_BYTES];                                         // Buffer for incoming TCP packet
  uint8_t TCP_Index;                                                            // Index for incoming TCP packet  unsigned char   Max_Length;    //Mexumam length of package we expect
  uint8_t TCP_Buffer_Len;                                                       // Length of TCP Packet
  uint8_t RemoteIpAddr[4u];
  uint8_t TCP_CRC[5u];                                                          // ACK CRC packet
  uint8_t TCP_CRC_Index;
  uint8_t TCP_Send_Trys;                                                        // How many times we tried to send the UDP packet
  uint8_t TCP_Send_Slow_ACK;                                                    // How many times did we slow ACK when a UDP packet was sent?
  uint8_t TCP_Send_Slow_ACK_Timeout;
  uint8_t TCP_Send_Fail;                                                        // How many times did we fail to send a UDP packet?
  uint8_t TCP_Send_Retry;                                                       // How many times we has to retry sending a packet
  uint16_t TCP_Packets_Sent;                                                    // how many packets we have sent.
  uint16_t TCP_Byte_Sent;                                                       // how many Bytes we have sent.
  uint16_t Bytes_In;
  uint16_t Packets_In;
  uint8_t Buffer_Overrun;                                                       // How many timer we had a buffer overrun
  uint8_t Buffer_Underrun;                                                      // How many timer we has a buffer underrun
  uint8_t State;                                                                // Status of the Packet (See Definitions)
  uint8_t Timeout_Enable;                                                       // Enable UART Timeoute
  uint8_t Msg_id_recv;                                                          // Message Id received.
 }) EthTCPObject_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint8_t Is;
  uint8_t MacAddr[6u];
  uint8_t IpAddr[4u];
  uint8_t Link_Established;
  uint8_t Link_Alive;
  uint8_t Link_Alive_Was;
  uint16_t Link_Alive_Time;
} Node;
#else
 STRUTPACKED (
 typedef struct{
  uint8_t Is;
  uint8_t MacAddr[6u];
  uint8_t IpAddr[4u];
  uint8_t Link_Established;
  uint8_t Link_Alive;
  uint8_t Link_Alive_Was;
  uint16_t Link_Alive_Time;
})Node;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
 uint8_t Enabled;                                                               // enable heart beat
 uint8_t Count;                                                                 //Clear the heart Beat counter
 uint8_t Step;                                                                  //Process step
 uint8_t Max_Time;                                                              // Maximum time for timeout
 uint8_t Air;                                                                   //Clear heart Beat for air Node
 uint8_t MasGs;                                                                 //Clear heart Beat for Master ground station Node
 uint8_t FirGs;                                                                 //Clear heart Beat for Fire ground station Node
 uint16_t Time;                                                                 //Clear the heart beat timer beat
 uint8_t Air_Time;                                                              //Clear heart Beat for air Node
 uint8_t MasGs_Time;                                                            //Clear heart Beat for Master ground station Node
 uint8_t FirGs_Time;                                                            //Clear heart Beat for Fire ground station Node
} H_B;
#else
 STRUTPACKED (
 typedef struct{
 uint8_t Enabled;                                                               // enable heart beat
 uint8_t Count;                                                                 //Clear the heart Beat counter
 uint8_t Step;                                                                  //Process step
 uint8_t Max_Time;                                                              // Maximum time for timeout
 uint8_t Air;                                                                   //Clear heart Beat for air Node
 uint8_t MasGs;                                                                 //Clear heart Beat for Master ground station Node
 uint8_t FirGs;                                                                 //Clear heart Beat for Fire ground station Node
 uint16_t Time;                                                                 //Clear the heart beat timer beat
 uint8_t Air_Time;                                                              //Clear heart Beat for air Node
 uint8_t MasGs_Time;                                                            //Clear heart Beat for Master ground station Node
 uint8_t FirGs_Time;                                                            //Clear heart Beat for Fire ground station Node
}) H_B;
#endif

#if (defined(GPS_INCLUDED2) || defined(GPS_INCLUDED))

#if defined(D_FT900)
typedef struct STRUTPACKED {
      uint32_t timestamp;                                                       // time from GPS
      uint8_t numOfSatel;                                                       // number of satelites used in solution
      float32_t lat;                                                            // latitude
      float32_t longd;                                                          // longditude
      float32_t altRef;                                                         // Altitude above user datum ellipsoid
      float32_t hAcc;                                                           // Horizontal accuracy estimate.
      float32_t vAcc;                                                           // Vertical accuracy estimate
      float32_t SOG;                                                            // speed over ground
      float32_t COG;                                                            // true course
      float32_t vVel;                                                           // Vertical velocity (positive downwards)
      float32_t SealevelAltitude;                                               // Sea level altitude meters
      float32_t GeoidalHt;                                                      // Geoidal height
      float32_t hdop;                                                           // horizontal dilution of precision
      float32_t vdop;                                                           // vertical dilution of precision
} GPS_Info_t;
#else
 STRUTPACKED (                                                                  // GPS message object
typedef struct {
      uint32_t timestamp;                                                       // time from GPS
      uint8_t numOfSatel;                                                       // number of satelites used in solution
      float32_t lat;                                                            // latitude
      float32_t longd;                                                          // longditude
      float32_t altRef;                                                         // Altitude above user datum ellipsoid
      float32_t hAcc;                                                           // Horizontal accuracy estimate.
      float32_t vAcc;                                                           // Vertical accuracy estimate
      float32_t SOG;                                                            // speed over ground
      float32_t COG;                                                            // true course
      float32_t vVel;                                                           // Vertical velocity (positive downwards)
      float32_t SealevelAltitude;                                               // Sea level altitude meters
      float32_t GeoidalHt;                                                      // Geoidal height
      float32_t hdop;                                                           // horizontal dilution of precision
      float32_t vdop;                                                           // vertical dilution of precision
}) GPS_Info_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
      float32_t latitude;                                                       // latitude
      float32_t longditude;                                                     // longditude
      float32_t altitude;                                                       // Sea level altitude meters
} GPS_Position_t;
#else
 STRUTPACKED (                                                                  // GPS message object
typedef struct {
      float32_t latitude;                                                       // latitude
      float32_t longditude;                                                     // longditude
      float32_t altitude;                                                       // Sea level altitude meters
}) GPS_Position_t;
#endif

#endif /* end GPS */

#if defined(LSM303M_USED)

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint16_t accels[3u];                                                         // accelerations for the 3 axes short
   uint16_t mags[3u];                                                           // magnetometer readings for the 3 axes
   uint16_t temp;                                                               // temperature reading
} lsm303_data_t;
#else
 STRUTPACKED (                                                                  // lsm303 accelerometer / compass
typedef struct {
   uint16_t accels[3u];                                                         // accelerations for the 3 axes short
   uint16_t mags[3u];                                                           // magnetometer readings for the 3 axes
   uint16_t temp;                                                               // temperature reading
}) lsm303_data_t;
#endif

#endif

#if ((defined(GPS_INCLUDED2) || defined(GPS_INCLUDED)) && defined(USE_MAVLINK))

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t min_pitch;
   uint8_t frontTransHdg;                                                       // Front transition heading for VTOL mode
   uint8_t empty2;
   uint8_t yaw_angle;
   GPS_Position_t pos;
} mavTakeOff_t;
#else
 STRUTPACKED (                                                                  // take off variables type for mavlink
typedef struct {
   uint8_t min_pitch;
   uint8_t frontTransHdg;                                                       // Front transition heading for VTOL mode
   uint8_t empty2;
   uint8_t yaw_angle;
   GPS_Position_t pos;
}) mavTakeOff_t;
#endif

typedef enum {MV_CRAFT_NORMAL = 0u, MV_CRAFT_VTOL = 1u, MV_RETURN_BASE=2u, MV_DROP_PAYLOAD=3u, MV_NUM_OF_CRAFT_TYPES = 4u} mav_craft_typ_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t hold_time;
   uint8_t acc_rad;
   uint8_t traj_cont;
   uint8_t yaw_angle;
   GPS_Position_t pos;
} mavNavWaypoint_t;
#else
 STRUTPACKED (                                                                  // mavlink navigate to waypoint
typedef struct {
   uint8_t hold_time;
   uint8_t acc_rad;
   uint8_t traj_cont;
   uint8_t yaw_angle;
   GPS_Position_t pos;
}) mavNavWaypoint_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t logic;
   uint8_t groundSpd;
   uint8_t radius;                                                              //  +ve clockwise -ve anti-clockwise
   uint8_t yaw_angle;
   GPS_Position_t pos;
} mavFollow_t;
#else
 STRUTPACKED (                                                                  // mavlink following object
typedef struct {
   uint8_t logic;
   uint8_t groundSpd;
   uint8_t radius;                                                              //  +ve clockwise -ve anti-clockwise
   uint8_t yaw_angle;
   GPS_Position_t pos;
}) mavFollow_t;
#endif

typedef enum {TAR_KEEP_CUR = 0u, TAR_DIFF_KEEP = 1u, TAR_FIXED_ABOVE = 2u, TAR_NUM_OF_MODES = 3u} mav_alt_targ_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t SysID;                                                               // System ID (of the FOLLOW_TARGET beacon). Send 0 to disable follow-me and return to the default position hold mode.
   uint8_t reserve1;
   uint8_t reserve2;
   mav_alt_targ_e alt_mode;                                                     // Altitude mode: 0: Keep current altitude, 1: keep altitude difference to target, 2: go to a fixed altitude above home.
   uint8_t alt_abv_hm;                                                          //  Altitude above home. (used if mode=2) e.g. alt_mode=TAR_FIXED_ABOVE
   uint8_t reserve3;
   uint8_t time2land;                                                           // Time to land in which the MAV should go to the default position hold mode after a message RX timeout
} mavTarget_t;
#else
 STRUTPACKED (                                                                  // mavlink target object
typedef struct {
   uint8_t SysID;                                                               // System ID (of the FOLLOW_TARGET beacon). Send 0 to disable follow-me and return to the default position hold mode.
   uint8_t reserve1;
   uint8_t reserve2;
   mav_alt_targ_e alt_mode;                                                     // Altitude mode: 0: Keep current altitude, 1: keep altitude difference to target, 2: go to a fixed altitude above home.
   uint8_t alt_abv_hm;                                                          //  Altitude above home. (used if mode=2) e.g. alt_mode=TAR_FIXED_ABOVE
   uint8_t reserve3;
   uint8_t time2land;                                                           // Time to land in which the MAV should go to the default position hold mode after a message RX timeout
}) mavTarget_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t camQ1;                                                               // Camera q1 (where 0 is on the ray from the camera to the tracking device)
   uint8_t camQ2;                                                               // q2
   uint8_t camQ3;                                                               // q3
   uint8_t camQ4;                                                               // q4
   uint8_t altOff;                                                              // altitude offset from target
   uint8_t xOff;                                                                // X from target
   uint8_t yOff;                                                                // Y from target
} mavRepos_t;
#else
 STRUTPACKED (                                                                  // mavlink reposition object
typedef struct {
   uint8_t camQ1;                                                               // Camera q1 (where 0 is on the ray from the camera to the tracking device)
   uint8_t camQ2;                                                               // q2
   uint8_t camQ3;                                                               // q3
   uint8_t camQ4;                                                               // q4
   uint8_t altOff;                                                              // altitude offset from target
   uint8_t xOff;                                                                // X from target
   uint8_t yOff;                                                                // Y from target
}) mavRepos_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t target_alt;
   uint8_t pres_land;
   uint8_t vtol_app_alt;
   uint8_t yaw_angle;
   GPS_Position_t pos;
} mavNavLanding_t;
#else
 STRUTPACKED (                                                                  // mavlink landing object
typedef struct {
   uint8_t target_alt;
   uint8_t pres_land;
   uint8_t vtol_app_alt;
   uint8_t yaw_angle;
   GPS_Position_t pos;
}) mavNavLanding_t;
#endif

typedef enum {ALT_NEURAL = 0u, ALT_CLIMB = 1u, ALT_DESCEND = 2u, ALT_NUM_OF_MODES = 3u} mav_altit_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   mav_altit_e mode;                                                            // 0 = Neutral, command completes when within 5m of this command's altitude,   1 = Climbing, command completes when at or above this command's altitude,   2 = Descending, command completes when at or below this command's altitude
   uint8_t altitude;                                                            // Desired altitude (meters)
} mavNavAltitude_t;
#else
 STRUTPACKED (                                                                  // mavlink altitude object
typedef struct {
   mav_altit_e mode;                                                            // 0 = Neutral, command completes when within 5m of this command's altitude,   1 = Climbing, command completes when at or above this command's altitude,   2 = Descending, command completes when at or below this command's altitude
   uint8_t altitude;                                                            // Desired altitude (meters)
}) mavNavAltitude_t;
#endif

typedef union {                                                                 // union of all mavlink loitering variables
  uint8_t empty1;
  uint8_t num_of_turns;
  uint8_t time_to_loiter;
} mavlink_loiter_union_t;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   mavlink_loiter_union_t type;                                                 // loiter type (loiter unlimit, time, number of turns)
   uint8_t empty2;
   uint8_t radius;
   uint8_t yaw_angle;
   GPS_Position_t pos;
} mavLoitering_t;
#else
 STRUTPACKED (                                                                  // mavlink loitering object
typedef struct {
   mavlink_loiter_union_t type;                                                 // loiter type (loiter unlimit, time, number of turns)
   uint8_t empty2;
   uint8_t radius;
   uint8_t yaw_angle;
   GPS_Position_t pos;
}) mavLoitering_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint64_t time;
   uint8_t hrs;
   uint8_t mins;
   uint8_t secs;
} mavDelay_t;
#else
 STRUTPACKED (                                                                  // mavlink delay object
typedef struct {
   uint64_t time;
   uint8_t hrs;
   uint8_t mins;
   uint8_t secs;
}) mavDelay_t;
#endif

typedef enum {MV_VEH_POINT_CENTER = 0u, MV_HOLD_HEADING = 1u, MV_LEAVE_YAW = 2u, ORB_YAW_NUM_OF_MODES = 3u} mav_orb_yaw_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t orbRadius;                                                           // Radius of the circle. positive: Orbit clockwise. negative: Orbit counter-clockwise.
   uint8_t tangVel;                                                             // Tangential Velocity. NaN: Vehicle configuration default.
   mav_orb_yaw_e orbYawBehave;                                                  // Yaw behavior of the vehicle. 0: vehicle front points to the center (default). 1: Hold last heading. 2: Leave yaw uncontrolled.
   uint8_t dyCentBeacon;                                                        // Reserved (e.g. for dynamic center beacon options)
   GPS_Position_t pos;                                                          // Center point latitude/longditude/altitude (if no MAV_FRAME specified) / X coordinate according to MAV_FRAME. NaN: Use current vehicle position or current center if already orbiting.,
} mavOrbit_t;
#else
 STRUTPACKED (                                                                  // mavlink orbit object
typedef struct {
   uint8_t orbRadius;                                                           // Radius of the circle. positive: Orbit clockwise. negative: Orbit counter-clockwise.
   uint8_t tangVel;                                                             // Tangential Velocity. NaN: Vehicle configuration default.
   mav_orb_yaw_e orbYawBehave;                                                  // Yaw behavior of the vehicle. 0: vehicle front points to the center (default). 1: Hold last heading. 2: Leave yaw uncontrolled.
   uint8_t dyCentBeacon;                                                        // Reserved (e.g. for dynamic center beacon options)
   GPS_Position_t pos;                                                          // Center point latitude/longditude/altitude (if no MAV_FRAME specified) / X coordinate according to MAV_FRAME. NaN: Use current vehicle position or current center if already orbiting.,
}) mavOrbit_t;
#endif

typedef enum {DLY_MV_STATE_MACH = 0u, DLY_MV_CMD_SECS = 1u, DLY_MV_CMD_HRS = 2u, DLY_MV_CMD_MINS = 3u, DLY_MV_CMD_TIMESPEC = 4u, DLY_MV_NUM_OF_MODES = 5u} mav_delay_e;

typedef union {                                                                 // union of all mavlink packets
  mavLoitering_t loiter;                                                        // loiter information
  mavNavLanding_t landing;                                                      // landing information
  mavNavWaypoint_t waypoint;                                                    // waypoint information
  mavTakeOff_t takeoff;                                                         // takeoff inforation
  mavNavAltitude_t altcont;                                                     // altitude information
  mavDelay_t delay;                                                             // delay object parameters
  mavOrbit_t orbit;                                                             // orbit object parameters
  mavFollow_t follow;                                                           // follow object parameters
  mavTarget_t target;                                                           // target object parameters
  mavRepos_t reposn;                                                            // reposition object parameters
} mavlink_packet_union_t;                                                       // union of possible mavlink message payloads

#if defined(D_FT900)
typedef struct STRUTPACKED {
   mavlink_packet_union_t payload;
} mavCmdMsgPayload_t;                                                            // area definition
#else
 STRUTPACKED (                                                                  // mavlink loitering object
typedef struct {
   mavlink_packet_union_t payload;
}) mavCmdMsgPayload_t;
#endif


#endif /* mavlink and gps */

#if defined(GEO_JSON_USED)
//  Define a structure for a square area of field
//
//  lo1(5),la1(2)                            lo2(5),la2(10)                        4 co-ordinate sqaure represents an area and ammount of fertilizer
//                                                                                 required in the field
//  lo3(1),la3(2)                            lo4(1),la4(10)
//
#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint8_t square_id;                                                            // index identifier for square in setpoint lookup table
  unsigned char geoJSONCoord[10u];                                              // geoJSON co-ordinates from the JSON string
  uint8_t geoTyp;                                                               // geoJSON type
//  float32_t remoteSpt1;                                                         // remote recipe setpoint for the PID controlling the inverter spraying
  uint8_t coordChkDisAbl : 1u;                                                  // set false to ignore co-ordinate check
  uint8_t spareBits : 7u;

  float32_t GeoidalHt;                                                          // height for sprayer cone centered as these squares
  float32_t long1;                                                              // longditude co-ordinate point1
  float32_t lat1;                                                               // latititude co-ordinate point1
  float32_t long2;                                                              // longditude co-ordinate point2
  float32_t lat2;                                                               // latititude co-ordinate point2
  float32_t long3;                                                              // longditude co-ordinate point3
  float32_t lat3;                                                               // latititude co-ordinate point3
  float32_t long4;                                                              // longditude co-ordinate point4
  float32_t lat4;                                                               // latititude co-ordinate point4
} geoCoord_Square_t;                                                            // area definition
#else
STRUTPACKED(
typedef struct{
  uint8_t square_id;                                                            // index identifier for square in setpoint lookup table
  unsigned char geoJSONCoord[10u];                                              // geoJSON co-ordinates from the JSON string
  uint8_t geoTyp;                                                               // geoJSON type
//  float32_t remoteSpt1;                                                         // remote recipe setpoint for the PID controlling the inverter spraying
  uint8_t coordChkDisAbl : 1u;                                                  // set false to ignore co-ordinate check
  uint8_t spareBits : 7u;
  
  float32_t GeoidalHt;                                                          // height for sprayer cone centered as these squares
  float32_t long1;                                                              // longditude co-ordinate point1
  float32_t lat1;                                                               // latititude co-ordinate point1
  float32_t long2;                                                              // longditude co-ordinate point2
  float32_t lat2;                                                               // latititude co-ordinate point2
  float32_t long3;                                                              // longditude co-ordinate point3
  float32_t lat3;                                                               // latititude co-ordinate point3
  float32_t long4;                                                              // longditude co-ordinate point4
  float32_t lat4;                                                               // latititude co-ordinate point4
}) geoCoord_Square_t;                                                           // area definition
#endif

typedef enum {OCR_MATCH_2LRFB = 0u, OCR_MATCH_LR = 1u, OCR_MATCH_FB = 2u, OCR_MATCH_2LR_ANYORDER =3u, OCR_MATCH_2LR_TOP1ST =4u, OCR_MATCH_2LR_BOT1ST =5u, OCR_MATCH_2FB_ANYORDER =6u, OCR_MATCH_2FB_TOP1ST =7u, OCR_MATCH_2FB_BOT1ST =8u, OCR_AND_LATLON = 9u, LATLON_ONLY = 9u, MATCH_TACHO_POS = 10u, OCR_MATCH_DOWN = 11u, OCR_MATCH_NUM = 12u} ocr_match_select_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
    ocr_match_select_e numMatchActiv;                                           /* 0 means must match both strings 1 means right/left only 2 means front back only */
    uint16_t tachoMaxRiLe;                                                      /* maximum field distance from start point in Right/Left x axis direction */
    uint16_t tachoMaxFrBa;                                                      /* maximum field distance from start point in Front Back y axis direction */
    unsigned char ocrRiLeMatchStr[ANCR_MAX_MSG];                                /* ocr match string around the field (right or left mounted camera) */
    unsigned char ocrFrBaMatchStr[ANCR_MAX_MSG];                                /* ocr match string around the field (front or back mounted camera) */
    uint16_t tachoRiLe;                                                         /* if you want to use distance as the co-ordinate left/right x axis */
    uint16_t tachoFrBa;                                                         /* if you want to use distance as the co-ordinate front/back y axis */
    geoCoord_Square_t geoCoordSq;                                               /* geo-coordinate square alternative or backup to ocr */
    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
    GaitParams legGait;                                                         /* leg gait to be applied when the two strings above are seen by the cmaera */
    LegGain legGain;                                                            /* leg gain parameters to be used */
    uint16_t stateEng;                                                          /* allow selection of any custom proceedure using this value in a given state engine */
} ocr_match_select_t;                                                           /* automatic characture recognition movement object for unmanned vehicle e.g. sprayer or planter */
#else
STRUTPACKED(                                                                    /* defines quantity of each product for a given analysis of the field */
typedef struct {
    ocr_match_select_e numMatchActiv;                                           /* 0 means must match both strings 1 means right/left only 2 means front back only */
    uint16_t tachoMaxRiLe;                                                      /* maximum field distance from start point in Right/Left x axis direction */
    uint16_t tachoMaxFrBa;                                                      /* maximum field distance from start point in Front Back y axis direction */
    unsigned char ocrRiLeMatchStr[ANCR_MAX_MSG];                                /* ocr match string around the field (right or left mounted camera) */
    unsigned char ocrFrBaMatchStr[ANCR_MAX_MSG];                                /* ocr match string around the field (front or back mounted camera) */
    uint16_t tachoRiLe;                                                         /* if you want to use distance as the co-ordinate left/right x axis */
    uint16_t tachoFrBa;                                                         /* if you want to use distance as the co-ordinate front/back y axis */
    geoCoord_Square_t geoCoordSq;                                               /* geo-coordinate square alternative or backup to ocr */
    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
    GaitParams legGait;                                                         /* leg gait to be applied when the two strings above are seen by the cmaera */
    LegGain legGain;                                                            /* leg gain parameters to be used */
    uint16_t stateEng;                                                          /* allow selection of any custom proceedure using this value in a given state engine */
}) ocr_match_select_t;                                                          /* defines a given setpoint or movement for an automatic characture recognition string (plant tree or change sprayer) */
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t RightStop : 1u;                                                      /* event suggesting we have gone too far right (e.g. tacho or beacon) */
   uint8_t LeftStop : 1u;                                                       /* event suggesting we have gone too far left (e.g. tacho or beacon) */
   uint8_t FwdStop : 1u;                                                        /* event suggesting we have gone too far forward (e.g. tacho or beacon) */
   uint8_t RevStop : 1u;                                                        /* event suggesting we have gone too far back (e.g. tacho or beacon) */
   uint8_t leftRig : 2u;                                                        /* left right or stop tristate */
   uint8_t fwdBack : 2u;                                                        /* forward or back or stop tristate */

   uint8_t turnby90 : 1u;                                                       /* turns it by 90 */
   uint8_t matchLefRig : 1u;                                                    /* left right camera saw match when set true */
   uint8_t matchFwdBack : 1u;                                                   /* forward back saw match when set true */
   uint8_t matchBelow : 1u;                                                     /* match below has been found */
   uint8_t reverse_lr : 1u;
   uint8_t reverse_fb : 1u;
   uint8_t spare : 2u;
} ocr_movement_obj_t;                                                          /* automatic characture recognition movement object for unmanned vehicle e.g. sprayer or planter */
#else
STRUTPACKED(
typedef struct {
   uint8_t RightStop : 1u;                                                      /* event suggesting we have gone too far right (e.g. tacho or beacon) */
   uint8_t LeftStop : 1u;                                                       /* event suggesting we have gone too far left (e.g. tacho or beacon) */
   uint8_t FwdStop : 1u;                                                        /* event suggesting we have gone too far forward (e.g. tacho or beacon) */
   uint8_t RevStop : 1u;                                                        /* event suggesting we have gone too far back (e.g. tacho or beacon) */
   uint8_t leftRig : 2u;                                                        /* left right or stop tristate */
   uint8_t fwdBack : 2u;                                                        /* forward or back or stop tristate */

   uint8_t turnby90 : 1u;                                                       /* turns it by 90 */
   uint8_t matchLefRig : 1u;                                                    /* left right camera saw match when set true */
   uint8_t matchFwdBack : 1u;                                                   /* forward back saw match when set true */
   uint8_t matchBelow : 1u;                                                     /* match below has been found */
   uint8_t reverse_lr : 1u;
   uint8_t reverse_fb : 1u;
   uint8_t spare : 2u;
}) ocr_movement_obj_t;                                                          /* automatic characture recognition movement object for unmanned vehicle e.g. sprayer or planter */
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
    geoCoord_Square_t geoCoord;                                                 /* co-ordinates of each square (photo) in the field */
    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
} field_product_t;                                                              /* defines each field to be sprayed with the product */
#else
STRUTPACKED(                                                                    /* defines quantity of each product for a given analysis of the field */
typedef struct {
    geoCoord_Square_t geoCoord;                                                 /* co-ordinates of each square (photo) in the field */
    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
}) field_product_t;                                                             /* defines each field to be sprayed with the product */
#endif

#define GPS_GEO_WRONG_HEIGHT -1                                                 // the height of the sparyer is not in range
#define GPS_GEO_NO_AREA_MATCH 0                                                 // the current co-ordinates do not match the given area
#endif                                                                          /* end GeoJSON */

#if defined(GPS_POS_SPRAYER)

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t State;
   int64_t InitTm;
   uint64_t Tm;
} sprayVehicleState_t;                                                         // Spray Vehicle state
#else
 STRUTPACKED (
typedef struct {
   uint8_t State;
   int64_t InitTm;
   uint64_t Tm;
}) sprayVehicleState_t;                                                         // Spray Vehicle state
#endif

typedef enum { ARM_MTR_FORWARD=30u, ARM_FWD_TO_END=31u, ARM_FWD_TO_MID=32u, ARM_MTR_BACKWD=33u, ARM_REV_TO_MID=34u, ARM_REV_TO_RETR=35u, ARM_SPR_ACT_MTR_IDLE=36u } spray_arm_state_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t startedSpray : 1u;                                                  /* startedSpray setting */
    uint8_t g_hmiResetESD1 : 1u;                                                /* hmi ESD saved from GUI button press  */
    uint8_t timeOverride : 1u;                                                  /* time override for level sensor */
    uint8_t posSpDrvRem : 1u;                                                   /* pid drive remote local to the drive */
    uint8_t rtflag4 : 1u;                                                       /* spare flags */
    uint8_t rtflag5 : 1u;
    uint8_t rtflag6 : 1u;
    uint8_t rtflag7 : 1u;

    uint8_t AuxDevState;                                                        /* auxillary device state */
    uint8_t DeviceState;                                                        /* device state */
    uint8_t ExtArmStep;                                                         /* external arm step */
    uint8_t g_batchState;                                                       /* batch make up steps */
    uint8_t ExtArmStateReq;                                                     /* extended arm GUI request */
    uint8_t curProduct;                                                         /* current product */

    uint8_t use_auxDevState : 1u;                                               /* set true means we use and want to recall AuxDevState from file */
    uint8_t use_devState : 1u;                                                  /* set true means we use and want to recall DeviceState from file  */
    uint8_t use_extArmStep : 1u;                                                /* set true means we use and want to recall extArmStep from file  */
    uint8_t use_gbatchState : 1u;                                               /* set true means we use and want to recall g_batchState from file  */
    uint8_t use_extArmStateReq : 1u;                                            /* set true means we use and want to recall extArmStateReq from file  */
    uint8_t rtflag8 : 1u;                                                       /* spare flags */
    uint8_t rtflag9 : 1u;
    uint8_t rtflag10 : 1u;

    rionUTCDateTimeField_t timestamp;                                           /* time stamp for the data snapshot in raw internet object notation */
} storedRealTimeData_t;
#else
STRUTPACKED(                                                                    /* recipe and settings for spray sequence */
typedef struct {
    uint8_t startedSpray : 1u;                                                  /* startedSpray setting */
    uint8_t g_hmiResetESD1 : 1u;                                                /* hmi ESD saved from GUI button press  */
    uint8_t timeOverride : 1u;                                                  /* time override for level sensor */
    uint8_t posSpDrvRem : 1u;                                                   /* pid drive remote local to the drive */
    uint8_t rtflag4 : 1u;                                                       /* spare flags */
    uint8_t rtflag5 : 1u;
    uint8_t rtflag6 : 1u;
    uint8_t rtflag7 : 1u;

    uint8_t AuxDevState;                                                        /* auxillary device state */
    uint8_t DeviceState;                                                        /* device state */
    uint8_t ExtArmStep;                                                         /* external arm step */
    uint8_t g_batchState;                                                       /* batch make up steps */
    uint8_t ExtArmStateReq;                                                     /* extended arm GUI request */
    uint8_t curProduct;                                                         /* current product */

    uint8_t use_auxDevState : 1u;                                               /* set true means we use and want to recall AuxDevState from file */
    uint8_t use_devState : 1u;                                                  /* set true means we use and want to recall DeviceState from file  */
    uint8_t use_extArmStep : 1u;                                                /* set true means we use and want to recall extArmStep from file  */
    uint8_t use_gbatchState : 1u;                                               /* set true means we use and want to recall g_batchState from file  */
    uint8_t use_extArmStateReq : 1u;                                            /* set true means we use and want to recall extArmStateReq from file  */
    uint8_t rtflag8 : 1u;                                                       /* spare flags */
    uint8_t rtflag9 : 1u;
    uint8_t rtflag10 : 1u;

    rionUTCDateTimeField_t timestamp;                                           /* time stamp for the data snapshot in raw internet object notation */
}) storedRealTimeData_t;                                                        /* batch sequence No.1 Real Time spooled settings (add the variables you need save to mmc file to this structure) */
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t prodId;                                                             /* product identity */
    unsigned char prodName[12u];                                                /* product name */
    unsigned char prodDesc[32u];                                                /* product description */
    unsigned char prodTk1Nm[12u];                                               /* product name in tank 1 */
    unsigned char prodTk2Nm[12u];                                               /* product name in tank 2 */
    unsigned char prodHp1Nm[12u];                                               /* product name in hopper 1 */
} product_id_t;
#else
STRUTPACKED(                                                                    /* defines each product (spray mixtures) */
typedef struct {
    uint8_t prodId;                                                             /* product identity */
    unsigned char prodName[12u];                                                /* product name */
    unsigned char prodDesc[32u];                                                /* product description */
    unsigned char prodTk1Nm[12u];                                               /* product name in tank 1 */
    unsigned char prodTk2Nm[12u];                                               /* product name in tank 2 */
    unsigned char prodHp1Nm[12u];                                               /* product name in hopper 1 */
}) product_id_t;                                                                /* descriptive information on spray mix and blended liquids/solids (read only information file data) */
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t saveProduct : 1u;                                                    /* hmi command to save product or fields definitions recipe  */
   uint8_t delProduct : 1u;                                                     /* hmi command to delete existing product recipe  */
   uint8_t guiDerivedState : 2u;
//   mmc_data_write_state_e guiDerivedState : 2u;                                 /* derived hmi command to create new product recipe file, save new product recipe, overwrite existing product recipe  */
   uint8_t formatDsk : 1u;                                                      /* format SD card */
   uint8_t tristate : 2u;
   uint8_t spare : 1u;

   uint8_t prodSelect;                                                          /* product number selected to be written */
//   mmc_data_typ_e type : 4u;
   uint8_t type : 4u;
   uint8_t spare2 : 4u;
} gui_spray_data_t;
#else
STRUTPACKED(                                                                   /* defines each Graphical User Interface option for sprayer files */
typedef struct {
   uint8_t saveProduct : 1u;                                                    /* hmi command to save product or fields definitions recipe  */
   uint8_t delProduct : 1u;                                                     /* hmi command to delete existing product recipe  */
   uint8_t guiDerivedState : 2u;
//   mmc_data_write_state_e guiDerivedState : 2u;                                 /* derived hmi command to create new product recipe file, save new product recipe, overwrite existing product recipe  */
   uint8_t formatDsk : 1u;                                                      /* format SD card */
   uint8_t tristate : 2u;
   uint8_t spare : 1u;

   uint8_t prodSelect;                                                          /* product number selected to be written */
//   mmc_data_typ_e type : 4u;
   uint8_t type : 4u;
   uint8_t spare2 : 4u;
}) gui_spray_data_t;
#endif


#endif  /* pos sprayer */

#if defined(BATCH_MIXER)

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t timeOverride : 1u;                                                  /* make the product using time setting without level instrument */
    uint8_t solidMakeUp : 1u;                                                   /* when set true denotes second addition is solids */
    uint8_t xTraStep : 1u;                                                      /* when set true we have 3 stage 2 liquid mix and one solid */
    uint8_t flag1 : 1u;                                                         /* spare recipe flags */
    uint8_t flag2 : 1u;
    uint8_t flag3 : 1u;
    uint8_t flag4 : 1u;
    uint8_t flag5 : 1u;

    float32_t level1SptCorse;                                                   /* level 1 (tank A addition) set-point corse */
    float32_t level1SptFine;                                                    /* level 1 set-point fine */
    float32_t level2SptCorse;                                                   /* level 2 (tank B addition) set-point corse */
    float32_t level2SptFine;                                                    /* level 2 set-point fine */
    float32_t LevelEmpty;                                                       /* LevelEmpty (refill level) */
    uint64_t corse1Time;                                                        /* corse 1 addition time */
    uint64_t fine1Time;                                                         /* fine 1 addition time */
    uint64_t corse2Time;                                                        /* corse 2 addition time */
    uint64_t fine2Time;                                                         /* fine 2 addition time */
    uint64_t solid1Time;                                                        /* time for solid addition */
    uint64_t mixTime;                                                           /* time for mixing before spraying */
    uint64_t dosingTime;
    uint64_t errorTime;                                                         /* how much to add to timed step for error timeout exception (sequence progression without stimulus) */

    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
} batchSeq1Recipe_t;
#else
STRUTPACKED(                                                                    /* recipe and settings for spray sequence */
typedef struct {
    uint8_t timeOverride : 1u;                                                  /* make the product using time setting without level instrument */
    uint8_t solidMakeUp : 1u;                                                   /* when set true denotes second addition is solids */
    uint8_t xTraStep : 1u;                                                      /* when set true we have 3 stage 2 liquid mix and one solid */
    uint8_t flag1 : 1u;                                                         /* spare recipe flags */
    uint8_t flag2 : 1u;
    uint8_t flag3 : 1u;
    uint8_t flag4 : 1u;
    uint8_t flag5 : 1u;

    float32_t level1SptCorse;                                                   /* level 1 (tank A addition) set-point corse */
    float32_t level1SptFine;                                                    /* level 1 set-point fine */
    float32_t level2SptCorse;                                                   /* level 2 (tank B addition) set-point corse */
    float32_t level2SptFine;                                                    /* level 2 set-point fine */
    float32_t LevelEmpty;                                                       /* LevelEmpty (refill level) */
    uint64_t corse1Time;                                                        /* corse 1 addition time */
    uint64_t fine1Time;                                                         /* fine 1 addition time */
    uint64_t corse2Time;                                                        /* corse 2 addition time */
    uint64_t fine2Time;                                                         /* fine 2 addition time */
    uint64_t solid1Time;                                                        /* time for solid addition */
    uint64_t mixTime;                                                           /* time for mixing before spraying */
    uint64_t dosingTime;
    uint64_t errorTime;                                                         /* how much to add to timed step for error timeout exception (sequence progression without stimulus) */

    float32_t arrOfSpraySpt;                                                    /* speed of sprayer inverter taken from codec anaysis of RGB photo */
}) batchSeq1Recipe_t;                                                           // batch sequence No.1 Recipe settings
#endif

typedef enum { BATCH_TK_WAIT_EMPTY=0u, BATCH_TK_OPN_VLV1=1u, BATCH_WAIT_LVL1=2u, BATCH_TK_OPN_VLV2=3u, BATCH_WAIT_LVL2=4u, BATCH_TK_OPN_VLV3=5u, BATCH_WAIT_LVL3=6u, BATCH_TK_OPN_VLV4=7u, BATCH_WAIT_LVL4=8u, BATCH_ST_MIX=9u, BATCH_WT_MIX=10u, BATCH_END_MIX=11u, BATCH_ST_VIB=17u, BATCH_WAIT_SOLID=18u, BATCH_END_SOLID=19u, BATCH_EXT_ARM=20u, BATCH_INIT_RESET=100u, BATCH_HOLD_STATE=101u, BATCH_HOLD_RETURN=102u } batch_steps_e;
#endif  /* batch mixer */

#if (defined(GPS_POS_SPRAYER) && defined(BATCH_MIXER))                          /* if we have a gps position sprayer it has each field related to the product */

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t prodId;                                                             /* product identity */
    batchSeq1Recipe_t recipe;                                                   /* spray mix settings */
    field_product_t field[NO_SPRAY_OF_AREAS];                                   /* definition of how much to spray around the defined fields  (if you have more than just increase NO_SPRAY_OF_AREAS to include this as farm) */
} spray_product_t;
#else
STRUTPACKED(                                                                    /* defines each product (spray mixtures) */
typedef struct {
    uint8_t prodId;                                                             /* product identity */
    batchSeq1Recipe_t recipe;                                                   /* spray mix settings */
    field_product_t field[NO_SPRAY_OF_AREAS];                                   /* definition of how much to spray around the defined fields  (if you have more than just increase NO_SPRAY_OF_AREAS to include this as farm) */
}) spray_product_t;                                                             /* details for making spray products with id records (read/write file & production data) */
#endif

#elif (!defined(GPS_POS_SPRAYER) && defined(BATCH_MIXER))

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t prodId;                                                             /* product identity */
    batchSeq1Recipe_t recipe;                                                   /* spray mix settings */
} spray_product_t;
#else
STRUTPACKED(                                                                    /* defines each product (spray mixtures) */
typedef struct {
    uint8_t prodId;                                                             /* product identity */
    batchSeq1Recipe_t recipe;                                                   /* spray mix settings */
}) spray_product_t;                                                             /* details for making spray products with id records (read/write file & production data) */
#endif

#elif (defined(GPS_POS_SPRAYER) && !defined(BATCH_MIXER))

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t prodId;                                                             /* product identity */
    field_product_t field[NO_SPRAY_OF_AREAS];                                   /* definition of how much to spray around the defined field (if you have more than one make multiple field variables or 2d array) */
} spray_product_t;
#else
STRUTPACKED(                                                                    /* defines each product (spray mixtures) */
typedef struct {
    uint8_t prodId;                                                             /* product identity */
    field_product_t field[NO_SPRAY_OF_AREAS];                                   /* definition of how much to spray around the defined field (if you have more than one make multiple field variables or 2d array) */
}) spray_product_t;
#endif

#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t start1 : 1u;                                                        /* video is recording on channel 1 */
    uint8_t reset1 : 1u;                                                        /* video cumulative record time is reset */
    uint8_t start2 : 1u;                                                        /* same for next channel which is 2 */
    uint8_t reset2 : 1u;
    uint8_t start3 : 1u;
    uint8_t reset3 : 1u;
    uint8_t start4 : 1u;
    uint8_t reset4 : 1u;

    float64_t videoRecCh1;                                                      /* cumulative time we have been recording video */
    float64_t videoRecCh2;
    float64_t videoRecCh3;
    float64_t videoRecCh4;
} videoChannelStatus_t;
#else
STRUTPACKED(                                                                   /* video channel recording status structure */
typedef struct {
    uint8_t start1 : 1u;                                                        /* video is recording on channel 1 */
    uint8_t reset1 : 1u;                                                        /* video cumulative record time is reset */
    uint8_t start2 : 1u;                                                        /* same for next channel which is 2 */
    uint8_t reset2 : 1u;
    uint8_t start3 : 1u;
    uint8_t reset3 : 1u;
    uint8_t start4 : 1u;
    uint8_t reset4 : 1u;

    float64_t videoRecCh1;                                                      /* cumulative time we have been recording video */
    float64_t videoRecCh2;
    float64_t videoRecCh3;
    float64_t videoRecCh4;
}) videoChannelStatus_t;                                                        // video recording state global structure
#endif

typedef enum {
  ENAB_ADC_MAN_SAMP = 0u,                                                       /* enable ADC for manual sampling */
  CHOOSE_ADC_PIN = 1u,                                                          /* choose the ADC pin for manual sampling */
  WAIT_ADC_SAM_TIM = 2u,                                                        /* wait for the ADC sampling time */
  WAIT_FOR_SAMPLE = 3u,                                                         /* wait for the ADC sample complete flag or timeout */
  COLLECT_ADC_RAW = 4u,                                                         /* collect the raw value from the ADC and place into the variable specified to the collection function  */
  COLLECT_ADC_TIMEOUT = 5u,                                                     /* set error on the value collected as we timed out trying to get it  */
  ADC_COLLECT_COMPLETE = 6u,                                                    /* value has been collected wait for caller process to reschedule the handler */
  ENAB_ADC_AUT_SAMP = 7u,                                                       /* enable ADC for auto sampling */
  MAN_SAMPLING_OFF = 8u                                                         /* manual sampling turned off */
} ADCStates_e;                                                                  /* ADC state either auto sample or manual sample */

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t g_count_sam;                                                         // counter of samples
   uint8_t g_count_acc;                                                         // global counter which indicates a new moving average is present
   uint16_t value_in;                                                           // latest input value
   uint32_t mavg_sum;                                                           // summed value for moving average calculation
   uint32_t mavg_value;                                                         // the calculated moving average
   uint32_t mavg_last;                                                          // the previous calculated moving average
} mov_avg_data_t;
#else
STRUTPACKED(
typedef struct {
   uint8_t g_count_sam;                                                         // counter of samples
   uint8_t g_count_acc;                                                         // global counter which indicates a new moving average is present
   uint16_t value_in;                                                           // latest input value
   uint32_t mavg_sum;                                                           // summed value for moving average calculation
   uint32_t mavg_value;                                                         // the calculated moving average
   uint32_t mavg_last;                                                          // the previous calculated moving average
}) mov_avg_data_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   int32_t time2Pulse;                                                          /* time from rising or falling edge pulse to last occurance */
   uint32_t time2PulseLast;                                                     /* tick time reference of the last pulse */
   float32_t rot_speed;                                                         /* speed of rotation */
   float32_t distance;                                                          /* distance travelled or quantity accumulated */
   float32_t accel;                                                             /* acceleration */
   uint64_t rot_count;                                                          /* pulse counter */
   uint64_t rot_count_last;                                                     /* last pulse counter for accel calculation */
} rotat_sens_obj_t;
#else
STRUTPACKED(
typedef struct {
   int32_t time2Pulse;                                                          /* time from rising or falling edge pulse to last occurance */
   uint32_t time2PulseLast;                                                     /* tick time reference of the last pulse */
   float32_t rot_speed;                                                         /* speed of rotation */
   float32_t distance;                                                          /* distance travelled or quantity accumulated */
   float32_t accel;                                                             /* acceleration */
   uint64_t rot_count;                                                          /* pulse counter */
   uint64_t rot_count_last;                                                     /* last pulse counter for accel calculation */
}) rotat_sens_obj_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t missingTeeth : 1u;                                                   /* set true if pattern shows missing teeth */
   uint8_t re1_match : 1u;                                                      /* rising edge interrupt 1 matches */
   uint8_t fe1_match : 1u;                                                      /* falling edge interrupt 1 matches */
   uint8_t re2_match : 1u;                                                      /* rising edge interrupt 2 matches */
   uint8_t fe2_match : 1u;                                                      /* falling edge interrupt 2 matches */
   uint8_t sparepi : 3u;
   uint8_t int_state;
   uint16_t count1Good;                                                         /* count of good measurements */
   uint16_t count2Good;
   float32_t pi_db;                                                             /* value to which each reading should not deviate by set at initialisation */
   float32_t pic_Velocity;                                                      /* pulse integrity corrected velocity */
   float32_t pic_Accel;                                                         /* pulse integrity corrected acceleration */
} pulse_integrity_t;
#else
STRUTPACKED(
typedef struct {
   uint8_t missingTeeth : 1u;                                                   /* set true if pattern shows missing teeth */
   uint8_t re1_match : 1u;                                                      /* rising edge interrupt 1 matches */
   uint8_t fe1_match : 1u;                                                      /* falling edge interrupt 1 matches */
   uint8_t re2_match : 1u;                                                      /* rising edge interrupt 2 matches */
   uint8_t fe2_match : 1u;                                                      /* falling edge interrupt 2 matches */
   uint8_t sparepi : 3u;
   uint8_t int_state;
   uint16_t count1Good;                                                         /* count of good measurements */
   uint16_t count2Good;
   float32_t pi_db;                                                             /* value to which each reading should not deviate by set at initialisation */
   float32_t pic_Velocity;                                                      /* pulse integrity corrected velocity */
   float32_t pic_Accel;                                                         /* pulse integrity corrected acceleration */
}) pulse_integrity_t;
#endif

#if defined(FUTABA303_USED)
typedef enum {PHASE_A = 0, PHASE_B = 1, PHASE_C = 2, PHASE_NONE = 3} bldc_phase_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t rotStat;                                                             /* rotation sequence state machine */
   uint16_t pwm_period;                                                         /* timer val returned from PWM_Init */
   uint16_t pwmVal;                                                             /* scaled speed in timer val units */
   int64_t plsTimeDuration;                                                     /* time in 100ms slices */
   uint64_t plsTimeDurationLast;                                                /* reference start time */
   int64_t waitTime;                                                            /* wait time between each pwm step */
} futaba_s3003_obj_t;
#else
STRUTPACKED(
typedef struct {
   uint8_t rotStat;                                                             /* rotation sequence state machine */
   uint16_t pwm_period;                                                         /* timer val returned from PWM_Init */
   uint16_t pwmVal;                                                             /* scaled speed in timer val units */
   int64_t plsTimeDuration;                                                     /* time in 100ms slices */
   uint64_t plsTimeDurationLast;                                                /* reference start time */
   int64_t waitTime;                                                            /* wait time between each pwm step */
}) futaba_s3003_obj_t;
#endif

#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t v1;                                                                 /* speed heading 50 degrees from GPS */
  float32_t v2;                                                                 /* speed heading 170 degrees from GPS */
  float32_t v3;                                                                 /* speed heading 290 degrees from GPS */
  float64_t TrueAirSpeed;                                                       /* calculated true air speed */
  float64_t WindSpeed;                                                          /* calculated wind speed */
} wind_compens_t;
#else
STRUTPACKED(
typedef struct {
  float32_t v1;                                                                 /* speed heading 50 degrees from GPS */
  float32_t v2;                                                                 /* speed heading 170 degrees from GPS */
  float32_t v3;                                                                 /* speed heading 290 degrees from GPS */
  float64_t TrueAirSpeed;                                                       /* calculated true air speed */
  float64_t WindSpeed;                                                          /* calculated wind speed */
}) wind_compens_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   float32_t ek3DragBCoeffX;                                                    /* ballistic co-eff X */ 
   float32_t ek3DragBCoeffY;                                                    /* ballistic co-eff Y */
   float32_t bluffBodyDragAcc;                                                  /* bluff body drag acceleration */
   float32_t momentumDragAcc;                                                   /* momentum drag acceleration */
   float32_t ek2DragMCoeff;
} drag_coef_t;
#else
STRUTPACKED(
typedef struct {
   float32_t ek3DragBCoeffX;
   float32_t ek3DragBCoeffY;      
   float32_t bluffBodyDragAcc; 
   float32_t momentumDragAcc;
   float32_t ek2DragMCoeff;
}) drag_coef_t;
#endif

#if defined(WEATHER_STAT)
/* ============================== Weather Station =========================== */
#define KES_CMD_LENGTH 8u                                                       /* send data command length */
#define WEATHER_UNIT_IMPERIAL 0u                                                /* define specifications fr the units */
#define WEATHER_UNIT_FROMIMP 1u
#define WEATHER_UNIT_METRIC 2u

#if defined(D_FT900)
typedef struct STRUTPACKED {
    uint8_t setUnits : 3u;                                                      /* set this as big as the number of statex for the units above currently 7 allowed 3 uaed */
    uint8_t spare : 5u;
    float32_t pstatic;                                                          // pressure
    float32_t temp;                                                             // temperature
    float32_t windspeed;                                                        // wind speed
    float32_t winddir_deg;                                                      // wind direction
    float32_t rel_humidity;                                                     // TODO Get the real humidity value from message
} WeatherStat_t;
#else
STRUTPACKED(
typedef struct {
    uint8_t setUnits : 3u;                                                      /* set this as big as the number of statex for the units above currently 7 allowed 3 uaed */
    uint8_t spare : 5u;
    float32_t pstatic;                                                          // pressure
    float32_t temp;                                                             // temperature
    float32_t windspeed;                                                        // wind speed
    float32_t winddir_deg;                                                      // wind direction
    float32_t rel_humidity;                                                     // TODO Get the real humidity value from message
}) WeatherStat_t;
#endif
  // contents of the kestrel S message response in imperial units:
  // DT,  MG,  TR,  WS,  CW,  HW, TP, WC, RH, HI, DP, WB,  BP,  AL, DA
  //  s, Mag, True, mph, mph, mph, F,  F,  %,  F,  F,  F, inHg, ft, ft
  // in metric units:
  //  s,Mag,True,km/h,km/h,km/h,?C,?C,%,?C,?C,?C,hPa,m,m
  //
  // Kestrel Weather Station Sample packet in metric units:
  // S
  // > DT,MG,TR,WS,CW,HW,TP,WC,RH,HI,DP,WB,BP,AL,DA
  // s,Mag,True,km/h,km/h,km/h,?C,?C,%,?C,?C,?C,hPa,m,m
  // 399124138,000,000,0.0,0.0,0.0,22.5,22.5,37.6,21.4,7.3,13.5,931.5,701,1171
  // >
  //
  // where:
  //
  //   DT is the date and time in seconds since 1st January 2000,
  //   AV is air velocity
  //   AF is air flow
  //   MG is the compass magnetic direction
  //   TR is the compass true direction
  //   WS is the wind speed
  //   CW is the crosswind
  //   HW is the headwind
  //   TP is the temperature,
  //   WC is the wind chill,
  //   RH is the relative humidity,
  //   EV is the evaporation rate
  //   CT is the concrete temperature
  //   HR, MO (moisture) are the humidity ratio
  //   HI is the heat index,
  //   DP is the dew point,
  //   WB is the wet bulb
  //   AP is absolute pressure
  //   BP is the pressure,
  //   AL is the altitude,
  //   DA is the density altitude
  //   AD is air density
  //   RA is relative air density
typedef enum {KES_DT = 0, KES_MG, KES_TR, KES_WS, KES_CW, KES_HW, KES_TP, KES_WC, KES_RH, KES_HI, KES_DP, KES_WB, KES_BP, KES_AL, KES_DA, KES_NUM_PARAMS} KestralWeather_e;
#endif

typedef enum {PWM_PRESCALE1 = 1u, PWM_PRESCALE8 = 8u, PWM_PRESCALE64=64u, PWM_PRESCALE256=256u } pwm_preScale_e;
typedef enum {PWM_TIMER2 = 2u, PWM_TIMER3 = 3u } pwm_timer_e;
typedef enum {START=0u, STOP, OPEN, CLOSE, VIBRATE, ROTATE, CUT, CHOP } deviceCmdState_e;
typedef enum {RUN_TIMEOUT=0u, RUNNING, STARTING, STOP_TIMEOUT, STOPPED, STOPPING, VIB_TIMEOUT, VIBRATING, ROT_TIMEOUT, ROTATING, CUT_TIMEOUT, CUTTING, CHOP_TIMEOUT, CHOPPING, OPN_TIMEOUT, OPENED, OPENING, CLS_TIMEOUT, CLOSED, CLOSING } deviceFbState_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
  deviceCmdState_e cmd;                                                         /* HMI request */
  deviceCmdState_e cmdLast;                                                     /* HMI request */
  uint8_t alarm : 1u;                                                           /* alarm state */
  uint8_t fb : 1u;                                                              /* first feed back */
  uint8_t fb2 : 1u;                                                             /* second feedback */
  uint8_t numfb : 2u;                                                           /* number of feedback */
  uint8_t sparebts : 3u;
  int64_t TimeDuration;                                                         /* time to travel to limit */
  uint64_t TimeDurationLast;                                                    /* last stored time event when change of state occurs */
  uint64_t AlmTimeOut;                                                          /* set this to the maximum time it takes to meet the feedback state */
  deviceFbState_e state;                                                        /* state feedback for HMI */
} device_t;                                                                     /* Device with feedback Checking Object */
#else
STRUTPACKED(
typedef struct{
  deviceCmdState_e cmd;                                                         /* HMI request */
  deviceCmdState_e cmdLast;                                                     /* HMI request */
  uint8_t alarm : 1u;                                                           /* alarm state */
  uint8_t fb : 1u;                                                              /* first feed back */
  uint8_t fb2 : 1u;                                                             /* second feedback */
  uint8_t numfb : 2u;                                                           /* number of feedback */
  uint8_t sparebts : 3u;
  int64_t TimeDuration;                                                         /* time to travel to limit */
  uint64_t TimeDurationLast;                                                    /* last stored time event when change of state occurs */
  uint64_t AlmTimeOut;                                                          /* set this to the maximum time it takes to meet the feedback state */
  deviceFbState_e state;                                                        /* state feedback for HMI */
 }) device_t;                                                                   /* Device with feedback Checking Object */
#endif

#if defined(DSHOT_MOTOR)
/* =================== dSHot 600 Motor =================================== */
#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint8_t level0;
  uint8_t duration0;
  uint8_t level1;
  uint8_t duration1;
} dShot_t;
#else
  STRUTPACKED (
typedef struct {
  uint8_t level0;
  uint8_t duration0;
  uint8_t level1;
  uint8_t duration1;
}) dShot_t;
#endif

#define DSHOT_PACKT_SZ 16u
#define DSHOT_MIN 48u
#define DSHOT_MAX 2047u

#if defined(D_FT900)
typedef struct STRUTPACKED {
   dShot_t dshotPacket[DSHOT_PACKT_SZ];
   uint16_t outputValue;
   uint8_t requestTelemetry : 1u;
   uint8_t spare : 7u;
   uint8_t receivedBytes;
   uint8_t pin;
} dShot_motor_t;
#else
  STRUTPACKED (
typedef struct {
   dShot_t dshotPacket[DSHOT_PACKT_SZ];
   uint16_t outputValue;
   uint8_t requestTelemetry : 1u;
   uint8_t spare : 7u;
   uint8_t receivedBytes;
   uint8_t pin;
}) dShot_motor_t;      
#endif
                                                         /* for dShot600 protocol motors */
#endif /* end dShot */

/* ================ Videoray M5 motors ===================================== */
/** @file m5.h
 *  @brief Interface function definitions for Videoray M5 motors.
 *
 *  @author Seth Girvan (Lord)
 *  Ported for PIC32 by ACP Aviation
 */
/*
 * MIT License
 *
 * Copyright (c) 2019 AVBotz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ========================================================================== */
#define VM5_SYNC_REQUEST_0 0xF5U                                                // Per VRCSR doc
#define VM5_SYNC_REQUEST_1 0x5FU                                                //
#define VM5_RESPONSE_NONE 0x00U                                                 /* Per the CSR doc (Per the m5 manual, 0x02 results in the standard thruster response.) */
#define VM5_ADDR_CUSTOM_COMMAND 0xF0U                                           // Per CSR doc and m5 manual

// Default per the m5 manual. Our thrusters actually came with this set to
// 0xFF, but we should have set them all to 0x81.
#define VM5_HEADER_LEN 10u
#define VM5_PROP_CMD_LEN 2u
#define VM5_THRUSTER_GROUP_ID 0x81U
#define VM5_PROPULSION_COMMAND 0xAAU                                            // Per m5 manual
#define VM5_PROPULSION_COMMAND_R_ID 0x00U                                       // we don't want a response
#define VM5_NUM_THRUSTERS 8u
#define VM5_PROPULSION_COMMAND_PACKET_LEN (VM5_PROP_CMD_LEN + (3U * 4U * VM5_NUM_THRUSTERS))       // 0xAA + R_ID + NUM_THRUSTERS * (4 byte float)
#define VM5_PROPULSION_COMMAND_HEADER_CRC ((uint32_t)0xDD8AC40DLU)              // Manually calculated assuming NUM_THRUSTERS == 8. Update if any part of the header changes! (32 bit CRC: ANSI X3.66 per VRCSR doc)
#define VM5_CRC_LEN 4u
#define VM5_CRC_POST_R_ID ((uint32_t)0xEACEB963LU)                              // Manually calculated assuming R_ID == 0 (without final xor mask)
#define VM5_BITS_PER_BYTE 8u
#define VM5_CRC32_POLY ((uint32_t)0xEDB88320LU)                                 // reverse polynomial
#define VM5_BAUD 115200UL

#define VM5THRUSTER_HEADER  {   \
                /* Sync bytes order is regardless of endianness. In thruster.py,
                   SYNC_REQUEST is defined in reverse byte order but serialized in
                 native byte order, resulting in big endian.     */                 \
                VM5_SYNC_REQUEST_0,  \
                VM5_SYNC_REQUEST_1,   \
                VM5_THRUSTER_GROUP_ID, \
                VM5_RESPONSE_NONE,      \
                VM5_ADDR_CUSTOM_COMMAND, \
                VM5_PROPULSION_COMMAND_PACKET_LEN, \
                /* Begin header CRC (little endian)  */ \
                VM5_PROPULSION_COMMAND_HEADER_CRC & 0xFFU,   \
                (VM5_PROPULSION_COMMAND_HEADER_CRC >> 8U) & 0xFFU,  \
                (VM5_PROPULSION_COMMAND_HEADER_CRC >> 16U) & 0xFFU,  \
                VM5_PROPULSION_COMMAND_HEADER_CRC >> 24U             \
        } \
        
#define VM5THRUSTER_PROP_CMD { \
                VM5_PROPULSION_COMMAND,  \
                VM5_PROPULSION_COMMAND_R_ID  } \

typedef enum
{
   VM5_INIT,
   VM5_HEADER,                                                                  /* send the message from here */
   VM5_R_ID,
   VM5_POWER,
   VM5_POWER_ONLY,                                                              /* update only power data from here */
   VM5_CRC,
   VM5_SEND,
   VM5_SENT,                                                                    /* when in this state a poll timer moves us back to the VM5_HEADER state to re-schedule the mesage send */
   VM5_POWER_SET                                                                /* when you are writing to the power structure */
} vm5ThrusterState_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   float32_t power[VM5_NUM_THRUSTERS];                                          // Powers range [-1, 1]
} vm5powerThruster_t;
#else
  STRUTPACKED (
typedef struct {
   float32_t power[VM5_NUM_THRUSTERS];                                          // Powers range [-1, 1]
}) vm5powerThruster_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  vm5ThrusterState_e state;
  vm5powerThruster_t m5[3u];
  unsigned char *Buf;
  uint8_t uartPort;
} vm5_object_t;
#else
  STRUTPACKED (
typedef struct {
  vm5ThrusterState_e state;
  vm5powerThruster_t m5[3u];
  unsigned char *Buf;
  uint8_t uartPort;
}) vm5_object_t;
#endif

#if defined(TILT_SERVO1_USED)

#define SERVO1_RETRY_LIM CPU_TICKS_PER_SECOND*0.5f
#define SERVO1_RESEND_MAX 5u

#define SERVO1_REQ_MOVE 0                                                       /* because its a sub class within the enum */
#define SERVO1_REQ_ANGLE 1
#define SERVO1_REQ_SPEED 2
#define SERVO1_REQ_REP_DLY 3
#define SERVO1_REQ_VOLT 4
#define SERVO1_REQ_TEMPERAT 5
  
typedef enum
{
  SERVO1_REQ_MOVE1 = SERVO1_REQ_MOVE,
  SERVO1_REQ_ANGLE1 = SERVO1_REQ_ANGLE,
  SERVO1_REQ_SPEED1 = SERVO1_REQ_SPEED,
  SERVO1_REQ_REP_DLY1 = SERVO1_REQ_REP_DLY,
  SERVO1_REQ_VOLT1 = SERVO1_REQ_VOLT,
  SERVO1_REQ_TEMPERAT1 = SERVO1_REQ_TEMPERAT,
  SERVO1_MAX_REQ_TYPES
} servo1_request_e;

typedef enum
{
  SERVO1_REQ_MOVE2 = SERVO1_REQ_MOVE,
  SERVO1_REQ_ANGLE2 = SERVO1_REQ_ANGLE,
  SERVO1_REQ_SPEED2 = SERVO1_REQ_SPEED,
  SERVO1_REQ_REP_DLY2 = SERVO1_REQ_REP_DLY,
  SERVO1_REQ_VOLT2 = SERVO1_REQ_VOLT,
  SERVO1_REQ_TEMPERAT2 = SERVO1_REQ_TEMPERAT,
  SERVO1_WAIT_MOVE_REPLY = 7,
  SERVO1_WAIT_ANGLE_REPLY = 8,
  SERVO1_WAIT_SPEED_REPLY = 9,
  SERVO1_WAIT_REP_DLY_REPLY = 10,
  SERVO1_WAIT_VOLT_REPLY = 11,
  SERVO1_WAIT_TEMPERAT_REPLY = 12,
  SERVO1_MOVE_REPLY_RCV = 13,
  SERVO1_ANGLE_REPLY_RCV = 14,
  SERVO1_SPEED_REPLY_RCV = 15,
  SERVO1_REP_DLY_REPLY_RCV = 16,
  SERVO1_VOLT_REPLY_RCV = 17,
  SERVO1_TEMPERAT_REPLY_RCV = 18,
  SERVO1_REQ_DONE = 19
} servo1_state_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t buf[20u];
   uint8_t reqQueue[5u];
   uint8_t state;
   float64_t ang;
   float64_t speed;
   float32_t voltage;
   uint8_t RepDelayTime;
   uint8_t temperatCel;
   int32_t ticksSoFar;
   uint32_t lastTickRef;
   uint8_t reqAngle : 1u;
   uint8_t reqSpeed : 1u;
   uint8_t reqVolt : 1u;
   uint8_t reqTemp : 1u;
   uint8_t reqDly : 1u;
   uint8_t reqMove : 1u;
   uint8_t spare : 2u;
   uint8_t ResendCnt;
   uint8_t noInQ;
} servo1_t;
#else
  STRUTPACKED (
typedef struct {
   uint8_t buf[20u];
   uint8_t reqQueue[5u];
   uint8_t state;
   float64_t ang;
   float64_t speed;
   float32_t voltage;
   uint8_t RepDelayTime;
   uint8_t temperatCel;
   int32_t ticksSoFar;
   uint32_t lastTickRef;
   uint8_t reqAngle : 1u;
   uint8_t reqSpeed : 1u;
   uint8_t reqVolt : 1u;
   uint8_t reqTemp : 1u;
   uint8_t reqDly : 1u;
   uint8_t reqMove : 1u;
   uint8_t spare : 2u;
   uint8_t ResendCnt;
   uint8_t noInQ;
}) servo1_t;
#endif
#endif  /* -- end tilt servo -- */

#if defined(NAVSTIK_USED)
/* bias and linear constant for the caliberation of Accelerometer */
#define navstik_BiasA_x 1.049103f                                                       /*0.511558*/ 
#define navstik_BiasA_y -0.218415f                                                      /*-0.230395*/
#define navstik_BiasA_z 0.070886f                                                       /*-1.758256*/ 

#define navstik_Alpha_A 1.153687f                                                       /*1.031150*/ 
#define navstik_Beta_A 0.988549f                                                        /*0.956985*/ 
#define navstik_Gamma_A 0.961142f                                                       /*0.831406*/

/* bias and linear conastant for the caliberation of Magnetoometer */
#define navstik_BiasH_x 0.042499f
#define navstik_BiasH_y 0.122872f
#define navstik_BiasH_z 0.001617f

#define navstik_Alpha_H 0.845243f
#define navstik_Beta_H 0.853257f
#define navstik_Gamma_H 0.932019f

#define NAVSTIK_NUM_OF_SAMP 50u
#define NAVSTIK_GYRO_ALWAYS_UPD                                                 /* update for every value just get new calib every NAVSTIK_NUM_OF_SAMP otherwise update value only after NAVSTIK_NUM_OF_SAMP */ 

typedef enum
{
 _NAVSTIK_OFST_ACCELX = 10,
 _NAVSTIK_OFST_ACCELY = 19,
 _NAVSTIK_OFST_ACCELZ = 28,
 _NAVSTIK_OFST_GYROX = 37,
 _NAVSTIK_OFST_GYROY = 46,
 _NAVSTIK_OFST_GYROZ = 55,
 _NAVSTIK_OFST_MAGX = 64,
 _NAVSTIK_OFST_MAGY = 73,
 _NAVSTIK_OFST_MAGZ = 82  
} navstickWordOffset_e;

typedef enum
{
 _NAVSTIK_NO_CALIB = 0,
 _NAVSTIK_START_CALIB = 1,
 _NAVSTIK_REMOVING_OFFSET = 2, 
 _NAVSTIK_USE_CALIB = 3
} navstickUseCalib_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   float64_t navstik_ACCELX;
   float64_t navstik_ACCELY;
   float64_t navstik_ACCELZ;
   float64_t navstik_GYROX;
   float64_t navstik_GYROY;
   float64_t navstik_GYROZ;
   float64_t navstik_BiasG_x;
   float64_t navstik_BiasG_y;
   float64_t navstik_BiasG_z;
   uint8_t numOfSam;
   float64_t navstik_GYROX_OFTO;
   float64_t navstik_GYROY_OFTO;
   float64_t navstik_GYROZ_OFTO;   
   float64_t navstik_MAGX;
   float64_t navstik_MAGY;
   float64_t navstik_MAGZ;  
} navstik_object_t;
#else
  STRUTPACKED (
typedef struct {
   float64_t navstik_ACCELX;
   float64_t navstik_ACCELY;
   float64_t navstik_ACCELZ;
   float64_t navstik_GYROX;
   float64_t navstik_GYROY;
   float64_t navstik_GYROZ;
   float64_t navstik_BiasG_x;
   float64_t navstik_BiasG_y;
   float64_t navstik_BiasG_z;
   uint8_t numOfSam;
   float64_t navstik_GYROX_OFTO;
   float64_t navstik_GYROY_OFTO;
   float64_t navstik_GYROZ_OFTO; 
   float64_t navstik_MAGX;
   float64_t navstik_MAGY;
   float64_t navstik_MAGZ; 
}) navstik_object_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
   float64_t roll;
   float64_t pitch;
   float64_t yaw;
   float64_t MAG_Heading; 
   int32_t G_Dt;
   uint32_t lastTick; 
   uint8_t timeInitDone : 1u;
   uint8_t spare : 7u;
} dcm_object_t;
#else
  STRUTPACKED (
typedef struct {
   float64_t roll;
   float64_t pitch;
   float64_t yaw;
   float64_t MAG_Heading;
   int32_t G_Dt;
   uint32_t lastTick;
   uint8_t timeInitDone : 1u;
   uint8_t spare : 7u;
}) dcm_object_t;
#endif


#endif /* navstik */

#if defined(NAVILOCK_USED)

typedef enum
{
  NAVILOCK_REQ_TRACK,
  NAVILOCK_WAIT_REPLY,
  NAVILOCK_REPLY_RCV,
  NAVILOCK_PROCESS_TRACK,
  NAVILOCK_REQ_POINT,  
  NAVILOCK_WAIT_POINT_REPLY,
  NAVILOCK_POINTS_RCV,
  NAVILOCK_PROCESS_POINT,
  NAVILOCK_REQ_SET_TOT_DIST,
  NAVILOCK_WAIT_DIST_SET_REPLY,
  NAVILOCK_SET_TOT_DIST_RCV,
  NAVILOCK_REQ_TOT_DIST,
  NAVILOCK_WAIT_GET_TOT_DIST_REPLY,
  NAVILOCK_GET_TOT_DIST_RCV,
  NAVILOCK_PROCESS_TOT_DIST,
  NAVILOCK_REQ_ERAS_TRAK,
  NAVILOCK_WAIT_ERAS_TRAK_REPLY,
  NAVILOCK_ERAS_TRAK_RCV,
  NAVILOCK_REQ_DONE,
  NAVILOCK_NUM_OF_STATES
} navilock_state_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   uint8_t buf[30u*NAVI_MAX_NO_OF_POINTS];
   uint8_t state;
   int32_t ticksSoFar;
   uint32_t lastTickRef;
   uint8_t readTrak : 1u;
   uint8_t setTotDist : 1u;
   uint8_t getTotDist : 1u;
   uint8_t erasTrak : 1u;
   uint8_t spare : 4u;
   uint8_t ResendCnt;
   uint32_t new_distance;
   uint16_t charIdx;
} navilock_t;
#else
  STRUTPACKED (
typedef struct {
   uint8_t buf[30u*NAVI_MAX_NO_OF_POINTS];
   uint8_t state;
   int32_t ticksSoFar;
   uint32_t lastTickRef;
   uint8_t readTrak : 1u;
   uint8_t setTotDist : 1u;
   uint8_t getTotDist : 1u;
   uint8_t erasTrak : 1u;
   uint8_t spare : 4u;
   uint8_t ResendCnt;
   uint32_t new_distance;
   uint16_t charIdx;
}) navilock_t;
#endif
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint32_t timestamp;
  float32_t pixel_flow_x_integral;
  float32_t pixel_flow_y_integral;
  // quat quaterni;
  uint32_t frame_count_since_last_readout;
  float32_t integration_timespan;
  uint8_t sensor_id;
  uint8_t quality;
  float32_t gyro_x_rate_integral;
  float32_t gyro_y_rate_integral;
  float32_t gyro_z_rate_integral;
  float32_t max_flow_rate;
  float32_t min_ground_distance;
  float32_t max_ground_distance;
} optical_flow_report_t;
#else
STRUTPACKED(                                                                    /* optical flow report */
typedef struct {
  uint32_t timestamp;
  float32_t pixel_flow_x_integral;
  float32_t pixel_flow_y_integral;
  // quat quaterni;
  uint32_t frame_count_since_last_readout;
  float32_t integration_timespan;
  uint8_t sensor_id;
  uint8_t quality;
  float32_t gyro_x_rate_integral;
  float32_t gyro_y_rate_integral;
  float32_t gyro_z_rate_integral;
  float32_t max_flow_rate;
  float32_t min_ground_distance;
  float32_t max_ground_distance;
}) optical_flow_report_t;
#endif

//#if defined(USING_PMLPS)
#if defined(D_FT900)
typedef struct STRUTPACKED {
  uint8_t SQUAL;
  Vectr position;
  float32_t prev_pos[3u];
  quat orientation;
  float32_t pitch;
  float32_t roll;
  float32_t yaw;
  float32_t prev_angle[3u];
  uint32_t lastTimRef;
  uint32_t stamp;
  uint64_t time;
  uint64_t prev_timestamp;
  uint8_t state;
} pmlpsEstimatedPosition_t;
#else
STRUTPACKED(
typedef struct {
  uint8_t SQUAL;
  Vectr position;
  float32_t prev_pos[3u];
  quat orientation;
  float32_t pitch;
  float32_t roll;
  float32_t yaw;
  float32_t prev_angle[3u];
  uint32_t lastTimRef;
  uint32_t stamp;
  uint64_t time;
  uint64_t prev_timestamp;
  uint8_t state;
}) pmlpsEstimatedPosition_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t cam_direction;
  float32_t cam_height;
  float32_t cam_width;
  float32_t fov_horizontal;
  float32_t fov_vertical;
  uint8_t camera_orientation;
} opt_flow_cam_config_t;
#else
STRUTPACKED(
typedef struct {
  float32_t cam_direction;
  float32_t cam_height;
  float32_t cam_width;
  float32_t fov_horizontal;
  float32_t fov_vertical;
  uint8_t camera_orientation;
}) opt_flow_cam_config_t;
#endif
        
#if defined(D_FT900)
typedef struct STRUTPACKED {
  float32_t linear_accel_cov;
  float32_t angular_vel_cov;
  float32_t cov_pose;
  float32_t cov_twist;
  float32_t tracker_confidence;
} opt_flow_coVar_t;
#else
STRUTPACKED(
typedef struct {
  float32_t linear_accel_cov;
  float32_t angular_vel_cov;
  float32_t cov_pose;
  float32_t cov_twist;
  float32_t tracker_confidence;
}) opt_flow_coVar_t;
#endif

/* ----- T265 Intel Realsense Camera --------------------------------------- */
#if defined(D_FT900)
typedef struct STRUTPACKED {
  Vectr translation;
  quat rotation;
  Vectr velocity;
  Vectr euler;
  uint32_t lastTimRef;
  uint32_t stamp;
  uint8_t state;
} T265Pose_t;
#else
STRUTPACKED(
typedef struct {
  Vectr translation;
  quat rotation;
  Vectr velocity;
  Vectr euler;
  uint32_t lastTimRef;
  uint32_t stamp;
  uint8_t state;
}) T265Pose_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
  mat44 H_aeroRef_T265Ref;
  mat44 H_T265body_aeroBody;
  mat44 H_body_camera;
  mat44 V_aeroRef_aeroBody; 
  mat44 H_PrevAeroBody_CurrAeroBody;  
  mat44 inv_aeroRef_T265Ref;
} T265Orientation_t;
#else
STRUTPACKED(
typedef struct {
  mat44 H_aeroRef_T265Ref;
  mat44 H_T265body_aeroBody;
  mat44 H_body_camera;
  mat44 V_aeroRef_aeroBody; 
  mat44 H_PrevAeroBody_CurrAeroBody; 
  mat44 inv_aeroRef_T265Ref;
}) T265Orientation_t;
#endif

typedef enum
{
  FwdPortRight,
  DwnPortRight,
  Fwd45,
  Bck45,
  NumOfCamOri
} T265Cam_Ori_e;
//#endif

#if defined(AVNav_USED)
typedef enum  {
        currentHeading = 0,
        currentDepth,
        currentPower,
        desiredHeading,
        desiredDepth,
        desiredPower,
        dropperState,
        runState,
        missionState,
        lastTask,
        emergencyCode,                                                          /* should be printed but not acted upon; mbed will handle safety */
        STATE_PROP_NUM                                                          /* number of above properties listed */
} VISTASK_STATE_PROPERTY_e;
/*
 * The sub has three kill states: alive, dead, and stopped (via SIGINT)
 */
typedef enum 
{
        R_ALIVE = 0x00,
        R_KILLED = 0x01,
        R_STOPPED = 0x02
} VISTASK_RUN_STATE_e;
/*
 * An enumeration of the tasks that EVA can perform, listed with nonvision tasks first.
 * This is so that the current task can be identified.
 */
typedef enum 
{
        T_NUL = -1,                                                                // used in search to say that nothing has been found; the current task cannot be set to T_NUL
        T_GATE,
        T_SEARCH,
        T_HYDROPHONE,
        T_BUOY,
        T_DROPPER,
        T_LGATE,
        T_PATH,
        T_TORPEDO,
        T_PARTY
} VISTASK_TASK_ID;
#if defined(D_FT900)
typedef struct STRUTPACKED {
  int16_t currentHeading;
  int16_t currentDepth;
  int16_t currentPower;
  int16_t emergencyCode;
  int16_t desiredHeading;
  int16_t desiredDepth;
  int16_t desiredPower;
  int16_t dropperState;
} AVNav_Data_t;
#else
STRUTPACKED(
typedef struct {
  int16_t currentHeading;
  int16_t currentDepth;
  int16_t currentPower;
  int16_t emergencyCode;
  int16_t desiredHeading;
  int16_t desiredDepth;
  int16_t desiredPower;
  int16_t dropperState;
}) AVNav_Data_t;
#endif
#endif /* --- AVNav used --- */

typedef enum
{
    SIG_EXP_FUNC = 0,
    SIG_D_FUNC = 1
} typeOfSigmoid_e;

#if defined(D_FT900)
typedef struct STRUTPACKED {
   float64_t divider;
   float64_t ap;
   float64_t dp;
   float64_t am;
   float64_t dm;
   float64_t d;
   float64_t adjustedBinLocation;
   float64_t peakFreqAdjusted;
} quinn_est_t;
#else
STRUTPACKED(
typedef struct {
   float64_t divider;
   float64_t ap;
   float64_t dp;
   float64_t am;
   float64_t dm;
   float64_t d;
   float64_t adjustedBinLocation;
   float64_t peakFreqAdjusted;
}) quinn_est_t;
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
    int16_t src;
    int16_t dest;
    int16_t weight;
} BF_Edge_t;
#else
STRUTPACKED(
typedef struct
{
    int16_t src;
    int16_t dest;
    int16_t weight;
}) BF_Edge_t;                                                                   // Bellman Ford Edge
#endif

#if defined(D_FT900)
typedef struct STRUTPACKED {
    int16_t V;
    int16_t E;
    BF_Edge_t *edge;
    int16_t dist[];
} BF_Graph_t;
#else
STRUTPACKED(
typedef struct
{
    int16_t V;
    int16_t E;
    BF_Edge_t *edge;
    int16_t dist[];
}) BF_Graph_t;                                                                  // Bellman Ford Graph
#endif

#ifdef __cplusplus
}
#endif

#endif /*Struts_H*/
