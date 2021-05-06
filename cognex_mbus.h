#ifndef __cognex_modbus_
#define __cognex_modbus_

/* ------------------------------------------ */
/* cognex modbus interface                    */
/* written by AirCamPro                       */
/* ------------------------------------------ */

#include "mbproto.h"                                                            /* modbus generic library */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define CMODPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define CMODPACKED __attribute__((packed))                                   /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define CMODPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define CMODPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define CMODPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif

//READ HOLDING REGISTERS – 03H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_CONTROL_BLK_START 0u /* 400000-1 (u32) */
#define COGN_MOD_CONTROL_BLK_END 1u /* 400000-1 (u32) */
/* =======================================================================================================================================================================================================
    Control Block
    The Control block contains bit type data. This block consists of the control signals sent from the PLC to the reader. It is used by the PLC to initiate actions and acknowledge certain data transfers
   ======================================================================================================================================================================================================= */
#if defined(D_FT900)
typedef struct CMODPACKED {
    uint8_t TrainCode : 1u;  /* When a bit transitions from 0 -> 1 the associated action is executed */
    uint8_t TrainMatchString : 1u; 
    uint8_t TrainFocus : 1u;
    uint8_t TrainBrightness : 1u;
    uint8_t UnTrain : 1u;
    uint8_t Reserved : 1u;
    uint8_t XecDMCCcmd : 1u;
    uint8_t SetMatchStr : 1u;
} COGN_Modbus_SoftEvent_t;
#else
CMODPACKED(
typedef struct  {
    uint8_t TrainCode : 1u;  /* When a bit transitions from 0 -> 1 the associated action is executed */
    uint8_t TrainMatchString : 1u; 
    uint8_t TrainFocus : 1u;
    uint8_t TrainBrightness : 1u;
    uint8_t UnTrain : 1u;
    uint8_t Reserved : 1u;
    uint8_t XecDMCCcmd : 1u;
    uint8_t SetMatchStr : 1u;
}) COGN_Modbus_SoftEvent_t;     
#endif

typedef union {
    uint8_t SEWord;
    COGN_Modbus_SoftEvent_t SEBits;
} COGN_Modbus_SoftEvents_u;

#if defined(D_FT900)
typedef struct CMODPACKED {
    uint16_t TriggerEnable : 1u;  /* This field is set to enable triggering via the Trigger bit. Clear this field to disable the network triggering mechanism. */
    uint16_t Trigger : 1u;    /* Setting this bit triggers an acquisition. Note that the Trigger Ready bit must be set high before triggering an acquisition. */
    uint16_t BufferResultsEnable : 1u;    /* When this bit is set, each read result (ResultID, ResultCode, ResultLength and ResultData fields) will be held in the Output Block until it is acknowledged. Once acknowledged, the next set of read results will be made available from the buffer. If new read results arrive before the earlier set is acknowledged the new set will be queued in the reader’s buffer */	
    uint16_t ResultsAck : 1u;    /* Set by the PLC to acknowledge that it has received the latest results (ResultID, ResultCode, ResultLength and ResultData fields). When the reader sees this bit transition from 0à1 it clears the ResultsAvailable bit. */
    uint16_t Reserved : 12u;  /* Not currently in use */
    uint8_t SetUserData : 1u; /* Set by the PLC to signal that new UserData is available. After reading the new UserData the reader sets SetUserDataAck to signal that the transfer is complete. */
    uint8_t InitiateStringCmd : 1u; /* Set by the PLC to signal that a new StringCommand is available. After processing the command, the reader sets StringCmdAck to signal that the command result is available. */
    uint8_t Reserved2 : 6u;
    COGN_Modbus_SoftEvents_u SoftEvent;   /* When a bit transitions from 0 -> 1 the associated action is executed. After executing the action the reader sets the corresponding SoftEventAck to signal that the action is complete */
} COGN_Modbus_ControlBlk_t;
#else
CMODPACKED(
typedef struct  {
    uint16_t TriggerEnable : 1u;  /* This field is set to enable triggering via the Trigger bit. Clear this field to disable the network triggering mechanism. */
    uint16_t Trigger : 1u;    /* Setting this bit triggers an acquisition. Note that the Trigger Ready bit must be set high before triggering an acquisition. */
    uint16_t BufferResultsEnable : 1u;    /* When this bit is set, each read result (ResultID, ResultCode, ResultLength and ResultData fields) will be held in the Output Block until it is acknowledged. Once acknowledged, the next set of read results will be made available from the buffer. If new read results arrive before the earlier set is acknowledged the new set will be queued in the reader’s buffer */	
    uint16_t ResultsAck : 1u;    /* Set by the PLC to acknowledge that it has received the latest results (ResultID, ResultCode, ResultLength and ResultData fields). When the reader sees this bit transition from 0à1 it clears the ResultsAvailable bit. */
    uint16_t Reserved : 12u;  /* Not currently in use */
    uint8_t SetUserData : 1u; /* Set by the PLC to signal that new UserData is available. After reading the new UserData the reader sets SetUserDataAck to signal that the transfer is complete. */
    uint8_t InitiateStringCmd : 1u; /* Set by the PLC to signal that a new StringCommand is available. After processing the command, the reader sets StringCmdAck to signal that the command result is available. */
    uint8_t Reserved2 : 6u;
    COGN_Modbus_SoftEvents_u SoftEvent;   /* When a bit transitions from 0 -> 1 the associated action is executed. After executing the action the reader sets the corresponding SoftEventAck to signal that the action is complete */
}) COGN_Modbus_ControlBlk_t;     
#endif

//READ HOLDING REGISTERS – 04H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_STATUS_BLK_START 5000u /* 405000-1 (u32) */
#define COGN_MOD_STATUS_BLK_END 5001u /* 405000-1 (u32) */
/* =======================================================================================================================================================================================================
   Status Block
   The status block contains bit type data. This block consists of the status signals sent from the reader to the PLC. It is used by the reader to signal status and handshake certain data transfers
   ======================================================================================================================================================================================================= */
   
#if defined(D_FT900)
typedef struct CMODPACKED {
    uint16_t TriggerReady : 1u;  /* Indicates when the reader is ready to accept a new Trigger. The reader sets this bit when TriggerEnable has been set and the reader is ready to accept a new trigger */
    uint16_t TriggerAck : 1u;    /* Indicates when the reader recognizes that Trigger has been set. This bit will remain set until the Trigger bit has been cleared */
    uint16_t Aquiring : 1u;    /* Set to indicate that the reader is in the process of acquiring an image */	
    uint16_t MissedAcq : 1u;    /* Indicates that the reader missed a requested acquisition trigger. The bit is cleared when the next acquisition is issued. */
    uint16_t reserved : 4u;  /* Future use */
    uint16_t Decoding : 1u; /* Set to indicate that the reader is in the process of decoding an image */
    uint16_t DecodeCompleteToggle : 1u; /* Indicates new result data is available. Bit toggles state (0 -> 1 or 1 -> 0) each time new result data becomes available */
    uint16_t resultOverrun : 1u; /* Set to indicate that the reader has discarded a set of read results because the PLC has not acknowledged the earlier results. Cleared when the next set of result data is successfully queued in the buffer. This bit only has meaning if result buffering is enabled. */
    uint16_t resultAvail : 1u; /* Set to indicate that new result data is available. Bit will remain set until acknowledged with ResultsAck even if additional new read results become available. */
    uint16_t reserved2 : 3u; /* Future use */
    uint16_t generalFlt : 1u; /* Set to indicate that an Ethernet communications fault has occurred. Currently only used by SoftEvent operations. Bit will remain set until the next successful SoftEvent or until TriggerEnable is set low and then high again */
    uint8_t setUsrDataAck : 1u; /* Set to indicate that the reader has received new UserData. Bit will remain set until the corresponding SetUserData bit is cleared. This forms a logical handshake between the PLC and reader. */
    uint8_t strCmdAck : 1u; /* Set to indicate that the reader has completed processing the latest string command and that the command response is available. Bit will remain set until the corresponding InitiateStringCmd bit is cleared. This forms a logical handshake between the PLC and reader. */
    uint8_t reserved3 : 6u;
    COGN_Modbus_SoftEvents_u SoftEventAck;   /* Set to indicate that the reader has completed the SoftEvent action. Bit will remain set until the corresponding SoftEvent bit is cleared */
} COGN_Modbus_StatusBlk_t;
#else
CMODPACKED(
typedef struct  {
    uint16_t TriggerReady : 1u;  /* Indicates when the reader is ready to accept a new Trigger. The reader sets this bit when TriggerEnable has been set and the reader is ready to accept a new trigger */
    uint16_t TriggerAck : 1u;    /* Indicates when the reader recognizes that Trigger has been set. This bit will remain set until the Trigger bit has been cleared */
    uint16_t Aquiring : 1u;    /* Set to indicate that the reader is in the process of acquiring an image */	
    uint16_t MissedAcq : 1u;    /* Indicates that the reader missed a requested acquisition trigger. The bit is cleared when the next acquisition is issued. */
    uint16_t reserved : 4u;  /* Future use */
    uint16_t Decoding : 1u; /* Set to indicate that the reader is in the process of decoding an image */
    uint16_t DecodeCompleteToggle : 1u; /* Indicates new result data is available. Bit toggles state (0 -> 1 or 1 -> 0) each time new result data becomes available */
    uint16_t resultOverrun : 1u; /* Set to indicate that the reader has discarded a set of read results because the PLC has not acknowledged the earlier results. Cleared when the next set of result data is successfully queued in the buffer. This bit only has meaning if result buffering is enabled. */
    uint16_t resultAvail : 1u; /* Set to indicate that new result data is available. Bit will remain set until acknowledged with ResultsAck even if additional new read results become available. */
    uint16_t reserved2 : 3u; /* Future use */
    uint16_t generalFlt : 1u; /* Set to indicate that an Ethernet communications fault has occurred. Currently only used by SoftEvent operations. Bit will remain set until the next successful SoftEvent or until TriggerEnable is set low and then high again */
    uint8_t setUsrDataAck : 1u; /* Set to indicate that the reader has received new UserData. Bit will remain set until the corresponding SetUserData bit is cleared. This forms a logical handshake between the PLC and reader. */
    uint8_t strCmdAck : 1u; /* Set to indicate that the reader has completed processing the latest string command and that the command response is available. Bit will remain set until the corresponding InitiateStringCmd bit is cleared. This forms a logical handshake between the PLC and reader. */
    uint8_t reserved3 : 6u;
    COGN_Modbus_SoftEvents_u SoftEventAck;   /* Set to indicate that the reader has completed the SoftEvent action. Bit will remain set until the corresponding SoftEvent bit is cleared */
}) COGN_Modbus_StatusBlk_t;     
#endif

//READ HOLDING REGISTERS – 03H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_INPUT_BLK_LEN 2001u /* 402001 (u16) */
#define COGN_MOD_INPUT_BLK_START 2002u /* 402002 (u16) */
#define COGN_MOD_INPUT_BLK_END 4004u /* 404004 (u16) */
/* =======================================================================================================================================================================================================
   Input Data Block
   The Input Data block is sent from the PLC to the reader. The block consists of user defined data that may be used as input to the acquisition/decode operation.
   ======================================================================================================================================================================================================= */

//READ HOLDING REGISTERS – 03H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_OUTPUT_BLK_TRIG 7001u /* 407001 (u16) Trigger identifier. Identifier of the next trigger to be issued. Used to match issued triggers with result data that is received later. This same value will be returned as the ResultID of the corresponding read. */
#define COGN_MOD_OUTPUT_BLK_RES 7002u /* 407002 (u16) Result identifier. This is the value of TriggerID when the corresponding trigger was issued. Used to match up triggers with corresponding result data */
#define COGN_MOD_OUTPUT_BLK_CODE 7003u /* 407003 (u16) Result Code as given by COGN_Modbus_OutResCode_t */
#define COGN_MOD_OUTPUT_BLK_LEN 7004u /* 407004 (u16) Number of bytes of valid data actually in the ResultData field. */
#define COGN_MOD_OUTPUT_BLK_START 7005u /* 407005 (u16) */
#define COGN_MOD_OUTPUT_BLK_END 9004u /* 409004 (u16) */
/* =======================================================================================================================================================================================================
   Output Data Block
   The Output Data block is sent from the reader to the PLC. The block consists primarily of read result data.
   ======================================================================================================================================================================================================= */
#if defined(D_FT900)
typedef struct CMODPACKED {
    uint16_t ReadStatus : 1u;       /* 1=read */
    uint16_t Validate : 1u;        /* 1=valid */
    uint16_t Verified : 1u;
    uint16_t AcqTrigOverrun : 1u;
    uint16_t AcqBufferOverrun : 1u;
    uint16_t Reserved : 11u;
} COGN_Modbus_OutResCode_t;
#else
CMODPACKED(
typedef struct  {
    uint16_t ReadStatus : 1u;       /* 1=read */
    uint16_t Validate : 1u;        /* 1=valid */
    uint16_t Verified : 1u;
    uint16_t AcqTrigOverrun : 1u;
    uint16_t AcqBufferOverrun : 1u;
    uint16_t Reserved : 11u;
}) COGN_Modbus_OutResCode_t;     
#endif   

//READ HOLDING REGISTERS – 03H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_STRCMD_BLK_LEN 1000u /* 401000 (u16) length */
#define COGN_MOD_STRCMD_BLK_START 1001u /* 401001 (u16) */
#define COGN_MOD_STRCMD_BLK_END 1999u /* 401999 (u16) */
/* =======================================================================================================================================================================================================
   String Command Block
   The String Command block is sent from the PLC to the reader. The block is used to transport string based commands (DMCC) to the reader.
   ======================================================================================================================================================================================================= */

//READ HOLDING REGISTERS – 03H
//WRITE SINGLE REGISTER – 06H
#define COGN_MOD_STRRES_BLK_RES 6000u
#define COGN_MOD_STRRES_BLK_LEN 6001u /* 401000 (u16) length */
#define COGN_MOD_STRRES_BLK_START 6002u /* 401001 (u16) */
#define COGN_MOD_STRRES_BLK_END 6999u /* 401999 (u16) */
/* =======================================================================================================================================================================================================
   String Command Result Block
   The String Command Result block is sent from the reader to the PLC. The block is used to transport the response from string based commands (DMCC) to the PLC
   ======================================================================================================================================================================================================= */   
   
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* -- end cognex modbus tcp defines -- */
