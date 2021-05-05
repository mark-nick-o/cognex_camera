#ifndef __slmp_mitsi__
#define __slmp_mitsi__

/* #include <stdlib.h> */
#include "definitions.h" 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ==========================================================
   SLMP Mitsubishi Protocol - Carrier TCP stream or UDP socket
   inspired from code by Masahiro Hasegawa
   written in rust and also c# driver by Luke Chen 
   ========================================================== */
   
#define _MAX_BIT_RW_POINT_ASCII 3584u
#define _MAX_BIT_RW_POINT_BINARY 7168u
#define _MAX_WORD_RW_POINT 960u

#define _BasicFormat "5000"                                                     //ASCII Header(3E)
#define _SubBasicFormat "03FF00"                                                //Request target module I/O number [03FF] + request target module station number [00]

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define SLMPPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define SLMPPACKED __attribute__((packed)) ALIGNED(1)                        /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define SLMPPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define SLMPPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define SLMPPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif
                
typedef enum {
    // Device
    DeviceRead = 0x0401,
    DeviceWrite = 0x1401,
    DeviceReadRandom = 0x0403,
    DeviceWriteRandom = 0x1402,
    EntryMonitorDevice = 0x0801,
    ExecuteMonitor = 0x0802,
    ReadBlock = 0x0406,
    WriteBlock = 0x01406,
    // Label
    ArrayLabelRead = 0x041A,
    ArrayLabelWrite = 0x141A,
    LabelReadRandom = 0x041C,
    LabelWriteRandom = 0x141B,
    // Memory
    MemoryRead = 0x0613,
    MemoryWrite = 0x1613,
    // ExtendUnit
    ExtendUnitRead = 0x0601,
    ExtendUnitWrite = 0x1601,
    // RemoteControl
    RemoteRun = 0x1001,
    RemoteStop = 0x1002,
    RemotePause = 0x1003,
    RemoteLatchClear = 0x1005,
    RemoteReset = 0x1006,
    ReadTypeName = 0x0101,
    NodeIndication = 0x3070,
    // Drive
    ReadDiskState = 0x0205,
    Defrag = 0x1207,
    // RemotePassword
    RemotePasswordLock = 0x1631,
    RemotePasswordUnlock = 0x1630,
    // File
    ReadFileInfo = 0x0201,
    ReadFileInfoWithTitle = 0x0202,
    ReadFileNoInfo = 0x0204,
    ChangeFileInfo = 0x1204,
    FileSearch = 0x0203,
    FileRead = 0x0206,
    FileWrite = 0x1203,
    FileLock = 0x0808,
    FileCopy = 0x1206,
    FileDelete = 0x1205,
    ReadDir = 0x1810,
    SearchDir = 0x1811,
    NewFileA = 0x1202,
    NewFileB = 0x1820,
    DeleteFile = 0x1822,
    CopyFile = 0x1824,
    ChangeFileState = 0x1825,
    ChangeFileDate = 0x1826,
    OpenFile = 0x1827,
    ReadFile = 0x1828,
    WriteFile = 0x1829,
    CloseFile = 0x182A,
    SelfTest = 0x0619,
    ClearErrorCode = 0x1617,
    ClearErrorHistory = 0x1619,
    OnDemand = 0x2101,
    // DataCollection
    Auth = 0x4000,
    KeepAlive = 0x4001,
    GetData = 0x4002,
    Distribute = 0x4003,
    // NodeConnection
    NodeSearch = 0x0E30,
    IPAddressSet = 0x0E31,
    // ParameterSetting
    DeviceInfoCompare = 0x0E32,
    ParameterGet = 0x0E33,
    ParameterUpdate = 0x0E34,
    ParameterSetStart = 0x0E35,
    ParameterSetEnd = 0x0E36,
    ParameterSetCancel = 0x0E3A,
    DeviceIdentificationInfoGet = 0x0E28,
    CommunicationSpeed = 0x3072,
    // NodeMonitoring
    StatusRead = 0x0E44,
    StatusRead2 = 0x0E53,
    ConnectionSettingGet = 0x0E45,
    DataMonitoring = 0x0E29,
    // Other
    CAN = 0x4020,
    IOLInk = 0x5000,
    ModbusTCP = 0x5001,
    ModbusRTU = 0x5002,
    // CCLinkIEFieldDiagnostics
    SelectNodeInfoGet = 0x3119,
    CommunicationTest = 0x3040,
    CableTest = 0x3050,
    // CCLinkIETSNNetworkManagement
    NetworkConfig = 0x0E90,
    MasterConfig = 0x0E91,
    SlaveConfig = 0x0E92,
    CyclicConfig = 0x0E93,
    Notification = 0x0E94,
    // LinkDeviceParameter
    LinkDevicePrmWrite = 0x320A,
    LinkDevicePrmWriteCheckReq = 0x320B,
    LinkDevicePrmWriteCheckResp = 0x320C,
    // EventHistory
    GetEventNum = 0x3060,
    GetEventHistory = 0x3061,
    ClearEventHistory = 0x161A,
    ClockOffsetDataSend = 0x3062,
    // BackupRestore
    GetCommunicationSet = 0x0EB0,
    GetStationSubIDList = 0x0EB1,
    GetDeviceInfo = 0x0EB2,
    StartBackup = 0x0EB3,
    EndBackup = 0x0EB4,
    RequestBackup = 0x0EB5,
    GetBackupPrm = 0x0EB6,
    CheckRestore = 0x0EB7,
    StartRestore = 0x0EB8,
    EndRestore = 0x0EB9,
    SetBackupPrm = 0x0EBA,
    // SlaveStationPrmRestore_
    CheckPrmDelivery = 0x0EBE,
    // StartStopCyclic
    StopOwnStationCyclic = 0x3206,
    StartOwnStationCyclic = 0x3207,
    StopOtherStationCyclic = 0x3208,
    StartOtherStationCyclic = 0x3209,
    //ReservedStation
    RsvStationConfigTemporaryRelease = 0x320D,
    RsvStationConfig = 0x320E,
    // WatchdogCounter
    SetWatchdogCounterInfo = 0x3210,
    WatchdogCounterOffsetConfig = 0x3211
} SLMPCommand_e;

typedef enum {
    SM = 0x91,
    SD = 0xA9,
    X = 0x9C,
    Y = 0x9D,
    M = 0x90,
    L = 0x92,
    F = 0x93,
    V = 0x94,
    B = 0xA0,
    D = 0xA8,
    W = 0xB4,
    TS = 0xC1,
    TC = 0xC0,
    TN = 0xC2,
    LTS = 0x51,
    LTC = 0x50,
    LTN = 0x52,
    STS = 0xC7,
    STC = 0xC6,
    STN = 0xC8,
    LSTS = 0x59,
    LSTC = 0x58,
    LSTN = 0x5A,
    CS = 0xC4,
    CC = 0xC3,
    CN = 0xC5,
    SB = 0xA1,
    SW = 0xB5,
    DX = 0xA2,
    DY = 0xA3,
    Z = 0xCC,
    LZ = 0x62,
    R = 0xAF,
    ZR = 0xB0,
    RD = 0x2C,
    LCS = 0x55,
    LCC = 0x54,
    LCN = 0x56
} SLMPDeviceCode_e;

typedef enum {
    Success = 0x00,
    WrongCommand = 0xC059,
    WrongFormat = 0xC05C,
    WrongLength = 0xC061,
    Busy = 0xCEE0,
    ExceedReqLength = 0xCEE1,
    ExceedRespLength = 0xCEE2,
    ServerNotFound = 0xCF10,
    WrongConfigItem = 0xCF20,
    PrmIDNotFound = 0xCF30,
    NotStartExclusiveWrite = 0xCF31,
    RelayFailure = 0xCF70,
    TimeoutError = 0xCF71,
    CANAppNotPermittedRead = 0xCCC7,
    CANAppWriteOnly = 0xCCC8,
    CANAppReadOnly = 0xCCC9,
    CANAppUndefinedObjectAccess = 0xCCCA,
    CANAppNotPermittedPDOMapping = 0xCCCB,
    CANAppExceedPDOMapping = 0xCCCC,
    CANAppNotExistSubIndex = 0xCCD3,
    CANAppWrongParameter = 0xCCD4,
    CANAppMoreOverParameterRange = 0xCCD5,
    CANAppLessOverParameterRange = 0xCCD6,
    CANAppTransOrStoreError = 0xCCDA,
    CANAppOtherError = 0xCCFF,
    OtherNetworkError = 0xCF00,
    DataFragmentShortage = 0xCF40,
    DataFragmentDup = 0xCF41,
    DataFragmentLost = 0xCF43,
    DataFragmentNotSupport = 0xCF44
} SLMPEndCode_e;

typedef enum {
    SLMP_Not = 0x00,
    SLMP_Clear = 0x01,
    SLMP_AllClear = 0x02
} SLMPClearMode_e;

typedef enum 
{
   SLMP_Binary,
   SLMP_ASCII
} CommunicationMode_e;

typedef enum {
    SLMP_Word = 0000,
    SLMP_Bit = 0001
} SLMPsubCommands_e;
                
#if defined(D_FT900)
typedef struct SLMPPACKED {
    uint16_t f_type;
    uint16_t serial_no;
    uint16_t reserved2;
} SlmpMTHeader_t;
#else
SLMPPACKED(
typedef struct  {
    uint16_t f_type;
    uint16_t serial_no;
    uint16_t reserved2;
}) SlmpMTHeader_t;     
#endif

#if defined(D_FT900)
typedef struct SLMPPACKED {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t end_code;
} SlmpSubHeaderRes_t;
#else
SLMPPACKED(
typedef struct  {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t end_code;
}) SlmpSubHeaderRes_t;                                                           
#endif


#if defined(D_FT900)
typedef struct SLMPPACKED {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t timer;
} SlmpSubHeaderReq_t;
#else
SLMPPACKED(
typedef struct  {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t timer;
}) SlmpSubHeaderReq_t;                                                           
#endif

#if defined(D_FT900)
typedef struct SLMPPACKED {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t reserved3;
} SlmpSubHeaderOd_t;
#else
SLMPPACKED(
typedef struct  {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t dl;
    uint16_t reserved3;
}) SlmpSubHeaderOd_t;                                                           
#endif

#if defined(D_FT900)
typedef struct SLMPPACKED {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t command;
    uint16_t sub_command;
} ErrInfo_t;
#else
SLMPPACKED(
typedef struct  {
    uint8_t net_no;
    uint8_t node_no;
    uint16_t dst_proc_no;
    uint8_t reserved1;
    uint16_t command;
    uint16_t sub_command;
}) ErrInfo_t;                                                           
#endif

#if defined(D_FT900)
typedef struct SLMPPACKED {
    SlmpSubHeaderReq_t slmp_header;
    uint16_t seq_no;
    SLMPCommand_e command;
    uint16_t sub_command;
} SlmpFrameHeader_t;
#else
SLMPPACKED(
typedef struct  {
    SlmpSubHeaderReq_t slmp_header;
    uint16_t seq_no;
    SLMPCommand_e command;
    uint16_t sub_command;
}) SlmpFrameHeader_t;                                                           
#endif

#define SlmpFrameType 0x54u

/*-----------------------------------------------------------------------------
 *  SlmpSetCommand:  Set the command and subcommand 
 *
 *  Parameters: SlmpFrameHeader_t *fh, uint16_t cmd, uint16_t subcmd 
 *              
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
void SlmpSetCommand( SlmpFrameHeader_t *fh, uint16_t cmd, uint16_t subcmd )
{
   fh->command = cmd;
   fh->sub_command = subcmd; 
}

/*-----------------------------------------------------------------------------
 *  Slmp_make_frame_header:  Compose header message 
 *
 *  Parameters: const SlmpFrameHeader_t fh, unsigned char* buf  
 *              
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
int8_t Slmp_make_frame_header( const SlmpFrameHeader_t fh, unsigned char* buf )
{
   int8_t ret = 1;
   
   if (sizeof(buf) < 19u)
   {
      ret = -1;
   }
   else
   {
      buf[0u] = SlmpFrameType;
      buf[1u] = 0x00u;
      buf[2u] = fh.seq_no & 0x0Fu;
      buf[3u] = fh.seq_no >> 8u;
      buf[4u] = 0x00u;
      buf[5u] = 0x00u;
      // Network number
      // Node number
      // Processor number 2byte
      // Multi-drop
      // Data length 2byte
      // Timer 2byte
      memcpy((void*)buf+6u,(void*) &fh.slmp_header, sizeof(SlmpSubHeaderReq_t));
      buf[15u] = fh.command & 0x0Fu;
      buf[16u] = fh.command >> 8u;
      buf[17u] = fh.sub_command & 0x0Fu;
      buf[18u] = fh.sub_command >> 8u;   
   }
   return ret;
}

/// Send SLMP command
///
/// # argument
///
/// * ` connection_info ' - SLMP connection information
/// * ` timeout ' - The timeout time for the SLMP command, in 250ms
/// * 'cmd' - SLMP command
/// * 'sub_command' - subcommand
/// * 'content_data' - supplied data per command
///
/// # Return value
///
/// Serial number corresponding to the command you sent
/*-----------------------------------------------------------------------------
 *  SlmpcreateBuffer:  Compose message 
 *
 *  Parameters: const SlmpFrameHeader_t *fh, unsigned char* sendbuf,  
 *              const unsigned char* data2send 
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
int8_t SlmpcreateBuffer( SlmpFrameHeader_t *fh, unsigned char* sendbuf, const unsigned char* data2send )
{
    int8_t ret = 1;
        
    if (sizeof(sendbuf) >= 18u + sizeof(data2send))
    {        
        fh->seq_no = ++fh->seq_no % UINT16_MAX; 
        if (Slmp_make_frame_header( *fh, sendbuf ) != -1)
        {
            memcpy((void*) sendbuf, (void*) data2send, sizeof(data2send));
        }
        else
        {
            ret = -1;
        }
    }
    else
    {
        ret = -1;
    }
    return ret;         
}

/// Device specification 16bit version at the time of device reading and writing
///
/// # argument
///
/// * 'd_type' - Device type
/// * 'first_addr' - first address
/// * 'count' - points
///
/// # Return value
///
/// Packed bytes
/*-----------------------------------------------------------------------------
 *  Slmp_make_cmd_rw_devices16:  Compose message to read/write PLC (remote controller)
 *
 *  Parameters: SLMPDeviceCode_e d_type, const uint16_t first_addr, const uint16_t count, 
 *              unsigned char * buf 
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
int8_t Slmp_make_cmd_rw_devices16( SLMPDeviceCode_e d_code, const uint16_t first_addr, const uint16_t count, unsigned char * buf) 
{
     int8_t ret = 1;
        
     if (sizeof(buf) >= 6u)
     {
        buf[0u] = d_code;
        buf[1u] = first_addr & 0x0Fu;
        buf[2u] = (first_addr >> 8u);
        buf[3u] = 0x00u;
        buf[4u] = count & 0x0Fu;
        buf[5u] = (count >> 8u);
     }
     else
     {
        ret = -1;
     }
     return ret;
}

/*-----------------------------------------------------------------------------
 *  Slmp_send_remote_run_cmd:  Compose message to stop PLC (remote controller)
 *
 *  Parameters: uint8_t force,  SLMPClearMode_e clear_mode, SlmpFrameHeader_t *fh, 
 *              unsigned char* sendbuf
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
void Slmp_send_remote_run_cmd( uint8_t force,  SLMPClearMode_e clear_mode, SlmpFrameHeader_t *fh, unsigned char* sendbuf ) 
{
    unsigned char buf[4u];
        
    if (force == 0u) 
      buf[0u] = 0x01u;
    else
      buf[0u] = 0x03u;
        
    buf[1u] = 0x00u;
    buf[2u] = clear_mode;
    buf[3u] = 0x00u;
    
    SlmpSetCommand( fh, RemoteRun, 0 );
    SlmpcreateBuffer( fh, sendbuf, &buf );
}

/*-----------------------------------------------------------------------------
 *  Slmp_send_remote_stop_cmd:  Compose message to stop PLC (remote controller)
 *
 *  Parameters: uint8_t force, SlmpFrameHeader_t *fh, unsigned char* sendbuf
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
void Slmp_send_remote_stop_cmd( uint8_t force,  SlmpFrameHeader_t *fh, unsigned char* sendbuf ) 
{ 
   unsigned char buf = 0u;
   SlmpSetCommand( fh, RemoteStop, 0 );
   SlmpcreateBuffer( fh, sendbuf, &buf );
}

/*-----------------------------------------------------------------------------
 *  Slmp_send_remote_pause_cmd:  Compose message to pause PLC (remote controller)
 *
 *  Parameters: uint8_t force, SlmpFrameHeader_t *fh, unsigned char* sendbuf
 *  Return:     (none)
 *----------------------------------------------------------------------------*/
void Slmp_send_remote_pause_cmd( uint8_t force, SlmpFrameHeader_t *fh, unsigned char* sendbuf ) 
{
    unsigned char buf[1u];
        
    if (force == 0u) 
        buf[0u] = 0x01u;
    else
        buf[0u] = 0x03u;
    
    SlmpSetCommand( fh, RemotePause, 0 );
    SlmpcreateBuffer( fh, sendbuf, &buf );
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* -- end lib -- */
