#ifndef __ethnetIP_
#define __ethnetIP_
/* Ethernet IP Example Allen Bradley PowerFlex 525 and Yasakawa MP3300IEC                                                        */
/* ref : Alexsey Timmin James Roth Miquel Valentine                                                                              */
/* https://github.com/nimbuscontrols/EIPScanner/blob/master/examples/vendors/yaskawa/mp3300iec/Yaskawa_AssemblyObjectExample.cpp */
/* https://github.com/loki-os/go-ethernet-ip/blob/master/encapsulation.go                                                        */
/* https://github.com/EIPStackGroup/OpENer/blob/master/source/src/enet_encap/encap.c                                             */
/* written by ACP Aviation                                                                                                       */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "definitions.h"
#if defined(ETH_IP_USED)
#include "cpu_endian_defs.h"

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define EIPPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define EIPPACKED __attribute__((packed))                                     /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define EIPPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define EIPPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define EIPPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif

#define ETHIP_HOST_IS_BIG_ENDIAN                                                /* uncomment if you dont need the bytes swaps */

#define YASKAWA_IP_ADDR "192.168.1.2"
#define YASKAWA_PORT 0xAF12ul
#define YASKAWA_VENDOR_ID 0x2cu
#define ASSEMBLY_OBJECT 0x04u
#define YASKAWA_INPUT_ASSEMBLY_111 0x6Fu
#define YASKAWA_OUTPUT_ASSEMBLY_101 0x65u
#define ASSEMBLY_INSTANCE_SIZE 128u
#define DATA_OFFSET 100u

typedef        enum {
   EIP_CLASS_8_BITS = 0x20,
   EIP_CLASS_16_BITS = 0x21,
   EIP_INSTANCE_8_BITS = 0x24,
   EIP_INSTANCE_16_BITS = 0x25,
   EIP_ATTRIBUTE_8_BITS = 0x30,
   EIP_ATTRIBUTE_16_BITS = 0x31,
} EIP_Yasakawa_EPathSegmentTypes_CipUsint_e;

typedef union {
  uint8_t uint8_Eip;
  uint16_t uint16_Eip;
} EIP_Yasakawa_u;

#if defined(D_FT900)
typedef struct EIPPACKED {
   EIP_Yasakawa_u classId;
   EIP_Yasakawa_u objectId;
   EIP_Yasakawa_u attributeId;
   uint16_t size;
} Yaskawa_EPath_t;
#else
EIPPACKED(
typedef struct
{
   EIP_Yasakawa_u classId;
   EIP_Yasakawa_u objectId;
   EIP_Yasakawa_u attributeId;
   uint16_t size;
}) Yaskawa_EPath_t;                                                          // Yasakawa EPath
#endif

#define AB525_MXFLTSZ 100u
#define AB525_MXFLTDSCSZ 200u

typedef enum {
        EIPCommandNOP = 0x00,
        EIPCommandListServices = 0x04,
        EIPCommandListIdentity = 0x63,
        EIPCommandListInterfaces = 0x64,
        EIPCommandRegisterSession = 0x65,
        EIPCommandUnRegisterSession = 0x66,
        EIPCommandSendRRData = 0x6F,
        EIPCommandSendUnitData = 0x70,
        EIPCommandIndicateStatus = 0x72,
        EIPCommandCancel = 0x73
} EIPCommand_e;

typedef enum {                                                                  /** @brief definition of capability flags */
  kCapabilityFlagsCipTcp = 0x0020,
  kCapabilityFlagsCipUdpClass0or1 = 0x0100
} EIPCapabilityFlags_e;

typedef enum {
        ItemIDUCMM = 0x0000,
        ItemIDListIdentityResponse = 0x000C,
        ItemIDConnectionBased = 0x00A1,
        ItemIDConnectedTransportPacket = 0x00B1,
        ItemIDUnconnectedMessage = 0x00B2,
        ItemIDListServicesResponse = 0x0100,
        ItemIDSockaddrInfoO2T = 0x8000,
        ItemIDSockaddrInfoT2O = 0x8001,
        ItemIDSequencedAddressItem = 0x8002
} EIPItemID_e;

/** @brief definition of status codes in encapsulation protocol
 * All other codes are either legacy codes, or reserved for future use
 *  */
typedef enum {
  kEncapsulationProtocolSuccess = 0x0000,
  kEncapsulationProtocolInvalidCommand = 0x0001,
  kEncapsulationProtocolInsufficientMemory = 0x0002,
  kEncapsulationProtocolIncorrectData = 0x0003,
  kEncapsulationProtocolInvalidSessionHandle = 0x0064,
  kEncapsulationProtocolInvalidLength = 0x0065,
  kEncapsulationProtocolUnsupportedProtocol = 0x0069
} EIPEncapsulationProtocolErrorCode_e;

#define ETH_IP_MAX_CMD_LEN 65511u                                               /* use if zero packed */
#define ETH_IP_MAX_PRODNM_LEN 32u
#define ETH_IP_MAX_ITEMDTA_LEN 32u
#define ETH_IP_MAX_LSTSRVC_LEN 16u
#define ETH_IP_MAX_ITEMS 64u                                                    /* not sure what this is TO DO Check this ? */

#if defined(D_FT900)
typedef struct EIPPACKED {
        EIPItemID_e TypeID;
        uint16_t Length;        
        uint8_t DataV[]; 
} EIPCommonPacketFormatItem_t;
#else
EIPPACKED(
typedef struct
{
        EIPItemID_e TypeID;
        uint16_t Length;        
        uint8_t DataV[]; 
}) EIPCommonPacketFormatItem_t;                                                 // Ethernet IP Header
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemCount;        
        EIPCommonPacketFormatItem_t Items[];  
} EIPCommonPacketFormat_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemCount;        
        EIPCommonPacketFormatItem_t Items[]; 
}) EIPCommonPacketFormat_t;                                                     // Ethernet IP Header
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint32_t InterfaceHandle;    
        uint16_t TimeOut;     
        EIPCommonPacketFormat_t Packet[];  
} EIPSendDataSpecificData_t;
#else
EIPPACKED(
typedef struct
{
        uint32_t InterfaceHandle;  
        uint16_t TimeOut;       
        EIPCommonPacketFormat_t Packet[]; 
}) EIPSendDataSpecificData_t;                                                     // Ethernet IP Header
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        EIPCommand_e EIPCommand;
        uint16_t Length;        
        uint32_t SessionHandle; 
        uint32_t Status;        
        uint64_t SenderContext;
        uint32_t Options; 
} EIPEncapsulationHeader_t;
#else
EIPPACKED(
typedef struct
{
        EIPCommand_e EIPCommand;
        uint16_t Length;        
        uint32_t SessionHandle; 
        uint32_t Status;        
        uint64_t SenderContext;
        uint32_t Options; 
}) EIPEncapsulationHeader_t;                                                          // Ethernet IP Header
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        EIPEncapsulationHeader_t pHeader;
        uint8_t CommandSpecificData[]; 
} EIPEncapsulationPacket_t;
#else
EIPPACKED(
typedef struct
{
        EIPEncapsulationHeader_t pHeader;
        uint8_t CommandSpecificData[]; 
}) EIPEncapsulationPacket_t;                                                          // Ethernet IP packet
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t VendorID;     
        uint16_t DeviceType; 
        uint16_t ProductCode; 
        uint8_t Major;   
        uint8_t Minor;  
        uint16_t Status;    
        uint32_t SerialNumber; 
        unsigned char ProductName[];
} EIPDevice_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t VendorID;     
        uint16_t DeviceType; 
        uint16_t ProductCode; 
        uint8_t Major;   
        uint8_t Minor;  
        uint16_t Status;    
        uint32_t SerialNumber; 
        unsigned char ProductName[];
}) EIPDevice_t;                                                                 // Ethernet IP device packet
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemTypeCode;                
        uint16_t ItemLength;                  
        uint16_t EncapsulationProtocolVersion; 
        int16_t SinFamily;                   
        uint16_t SinPort;                    
        uint32_t SinAddr;                    
        uint64_t SinZero;                     
        uint16_t VendorID;                     
        uint16_t DeviceType;                 
        uint16_t ProductCode;            
        uint8_t Major;                   
        uint8_t Minor;                       
        uint16_t Status;                      
        uint32_t SerialNumber;                 
        uint8_t NameLength;                   
        unsigned char ProductName[];
        uint8_t State;
} EIPListIdentityItem_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemTypeCode;                
        uint16_t ItemLength;                  
        uint16_t EncapsulationProtocolVersion; 
        int16_t SinFamily;                                                      /* sin bytes swap endian */              
        uint16_t SinPort;                    
        uint32_t SinAddr;                    
        uint64_t SinZero;                     
        uint16_t VendorID;                     
        uint16_t DeviceType;                 
        uint16_t ProductCode;            
        uint8_t Major;                   
        uint8_t Minor;                       
        uint16_t Status;                      
        uint32_t SerialNumber;                 
        uint8_t NameLength;                   
        unsigned char ProductName[];
        uint8_t State;
}) EIPListIdentityItem_t;                                                         
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemCount;
        EIPListIdentityItem_t Item; 
} EIPListIdentity_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemCount;
        EIPListIdentityItem_t Item; 
}) EIPListIdentity_t;                                                          
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemTypeCode;
        uint16_t ItemLength;
        uint8_t ItemData[];
} EIPListInterfaceItem_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemTypeCode;
        uint16_t ItemLength;
        uint8_t ItemData[];
}) EIPListInterfaceItem_t;                                                          
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemCount;
        EIPListInterfaceItem_t Item; 
} EIPListInterface_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemCount;
        EIPListInterfaceItem_t Item; 
}) EIPListInterface_t;                                                          
#endif        

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemTypeCode;
        uint16_t ItemLength;
        uint16_t Version;
        uint16_t Flags;
        uint8_t Name[];
} EIPListServicesItem_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemTypeCode;
        uint16_t ItemLength;
        uint16_t Version;
        uint16_t Flags;
        uint8_t Name[];
}) EIPListServicesItem_t;                                                          
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ItemCount;
        EIPListServicesItem_t Item; 
} EIPListServices_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ItemCount;
        EIPListServicesItem_t Item; 
}) EIPListServices_t;                                                          
#endif

#define ETH_IP_MAX_REQPATH_LEN 100u                                             /* if strings are packed with zero len */
#define ETH_IP_MAX_REQDATA_LEN 100u
#define ETH_IP_MAX_ADTSTAT_LEN 100u
#define ETH_IP_MAX_RESDATA_LEN 100u

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t Service;         
        uint16_t RequestPathSize; 
        uint8_t RequestPath[];
        uint8_t RequestData[];
} EIPMessageRouterRequest_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t Service;         
        uint16_t RequestPathSize; 
        uint8_t RequestPath[];
        uint8_t RequestData[];
}) EIPMessageRouterRequest_t;                                                          
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ReplyService;          
        uint16_t Reserved;             
        uint16_t GeneralStatus;          
        uint16_t SizeOfAdditionalStatus; 
        uint8_t AdditionalStatus[];
        uint8_t ResponseData[];
} EIPMessageRouterResponse_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ReplyService;          
        uint16_t Reserved;             
        uint16_t GeneralStatus;          
        uint16_t SizeOfAdditionalStatus; 
        uint8_t AdditionalStatus[];
        uint8_t ResponseData[];
}) EIPMessageRouterResponse_t;                                                          
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
        uint16_t ProtocolVersion;          
        uint16_t OptionsFlags;             
} EIPregisterSessionSpecificData_t;
#else
EIPPACKED(
typedef struct
{
        uint16_t ProtocolVersion;          
        uint16_t OptionsFlags;  
}) EIPregisterSessionSpecificData_t;                                                          
#endif

typedef enum 
{
    CTL_OMIT_CLASS              = (1<<0),
    CTL_OMIT_INSTANCE           = (1<<1),
    CTL_OMIT_CONN_PT            = (1<<2),
    CTL_OMIT_ATTRIBUTE          = (1<<3),
    CTL_UNCOMPRESSED_EPATH      = (1<<4),
    CTL_PACKED_EPATH            = (1<<5),

    CTL_OMIT_CONN_PATH          = (1<<6),

    CTL_FORWARD_OPEN            = (1<<7),
    CTL_FORWARD_CLOSE           = (1<<8),
} EIP_CTL_FLAGS_e;                                                              // Control bits for Serializeable::Serialize(), or SerializeCount()'s aCtl
        
//The Following Hardware Configuration is used in this example
// Turck FEN20-4DIP-4DXP
//Unisversal Digital Channels are used as Digital Outputs
// Manual: http://pdb2.turck.de/repo/media/_en/Anlagen/Datei_EDB/edb_6931090_gbr_en.pdf
//IP-Address: 192.168.1.254





/* https://literature.rockwellautomation.com/idc/groups/literature/documents/du/520-du001_-en-e.pdf - page 5 */
#if defined(D_FT900)
typedef struct EIPPACKED {
  int16_t fCode;
  unsigned char faultText[AB525_MXFLTSZ];
  unsigned char faultDescription[AB525_MXFLTDSCSZ];
} AB_PF525_Fault_t;
#else
EIPPACKED(
typedef struct
{
  int16_t fCode;
  unsigned char faultText[AB525_MXFLTSZ];
  unsigned char faultDescription[AB525_MXFLTDSCSZ];
}) AB_PF525_Fault_t;                                                            // Power Flex 525 Fault Codes
#endif

#if defined(D_FT900)
typedef struct EIPPACKED {
    uint8_t faultCode;
    uint8_t dsiPort;
    uint8_t dsiDeviceObject;
    uint8_t faultText;
    uint8_t timerValue;
    uint8_t sValidData : 1u;
    uint8_t isRealTime : 1u;
        uint8_t spareflags : 6u;
} AB_PF525_Data_t;
#else
EIPPACKED(
typedef struct
{
    uint8_t faultCode;
    uint8_t dsiPort;
    uint8_t dsiDeviceObject;
    uint8_t faultText;
    uint8_t timerValue;
    uint8_t sValidData : 1u;
    uint8_t isRealTime : 1u;
    uint8_t spareflags : 6u;
}) AB_PF525_Data_t;                                                             // Power Flex 525 Drive
#endif

typedef        enum {
        AB525_FAULT_1_CODE = 7,
        AB525_FAULT_2_CODE = 8,
        FAB525_FAULT_3_CODE = 9,
        AB525_FAULT_4_CODE = 604,
        AB525_FAULT_5_CODE = 605,
        AB525_FAULT_6_CODE = 606,
        AB525_FAULT_7_CODE = 607,
        AB525_FAULT_8_CODE = 608,
        AB525_FAULT_9_CODE = 609,
        AB525_FAULT_10_CODE = 610,

        /*FAULT_1_TIME_HR = 611,
                FAULT_2_TIME_HR = 612,
                FAULT_3_TIME_HR = 613,
                FAULT_4_TIME_HR = 614,
                FAULT_5_TIME_HR = 615,
                FAULT_6_TIME_HR = 616,
                FAULT_7_TIME_HR = 617,
                FAULT_8_TIME_HR = 618,
                FAULT_9_TIME_HR = 619,
                FAULT_10_TIME_HR = 620,
                FAULT_1_TIME_MIN = 621,
                FAULT_2_TIME_MIN = 622,
                FAULT_3_TIME_MIN = 623,
                FAULT_4_TIME_MIN = 624,
                FAULT_5_TIME_MIN = 625,
                FAULT_6_TIME_MIN = 626,
                FAULT_7_TIME_MIN = 627,
                FAULT_8_TIME_MIN = 628,
                FAULT_9_TIME_MIN = 629,
                FAULT_10_TIME_MIN = 630,*/

        AB525_FAULT_1_FREQ = 631,
        AB525_FAULT_2_FREQ = 632,
        AB525_FAULT_3_FREQ = 633,
        AB525_FAULT_4_FREQ = 634,
        AB525_FAULT_5_FREQ = 635,
        AB525_FAULT_6_FREQ = 636,
        AB525_FAULT_7_FREQ = 637,
        AB525_FAULT_8_FREQ = 638,
        AB525_FAULT_9_FREQ = 639,
        AB525_FAULT_10_FREQ = 640,

        AB525_FAULT_1_CURR = 641,
        AB525_FAULT_2_CURR = 642,
        AB525_FAULT_3_CURR = 643,
        AB525_FAULT_4_CURR = 644,
        AB525_FAULT_5_CURR = 645,
        AB525_FAULT_6_CURR = 646,
        AB525_FAULT_7_CURR = 647,
        AB525_FAULT_8_CURR = 648,
        AB525_FAULT_9_CURR = 649,
        AB525_FAULT_10_CURR = 650,

        AB525_FAULT_1_BUS_VOLTS = 651,
        AB525_FAULT_2_BUS_VOLTS = 652,
        AB525_FAULT_3_BUS_VOLTS = 653,
        AB525_FAULT_4_BUS_VOLTS = 654,
        AB525_FAULT_5_BUS_VOLTS = 655,
        AB525_FAULT_6_BUS_VOLTS = 656,
        AB525_FAULT_7_BUS_VOLTS = 657,
        AB525_FAULT_8_BUS_VOLTS = 658,
        AB525_FAULT_9_BUS_VOLTS = 659,
        AB525_FAULT_10_BUS_VOLTS = 660,

                /*FAULT_1_STATUS = 661,
                FAULT_2_STATUS = 662,
                FAULT_3_STATUS = 663,
                FAULT_4_STATUS = 664,
                FAULT_5_STATUS = 665,
                FAULT_6_STATUS = 666,
                FAULT_7_STATUS = 667,
                FAULT_8_STATUS = 668,
                FAULT_9_STATUS = 669,
                FAULT_10_STATUS = 670,*/
} EIP_ABPF525_Fault_e;

/* ------------ error codes for CIP ----------------------------------------- */
#define EIP_VID(x)      x,
#define EIP_VENDOR_COUNT ((int16_t)(sizeof(gEIP_vendors)/sizeof(gEIP_vendors[0u])))

static const struct VendorRow {                                                 /* Translate Vendor IDs */
    uint16_t  id;
    const char* name;
} gEIP_vendors[] = {
    {   EIP_VID(0)      "Reserved" },
    {   EIP_VID(1)      "Rockwell Automation/Allen-Bradley" },
    {   EIP_VID(2)      "Namco Controls Corp." },
    {   EIP_VID(3)      "Honeywell Inc." },
    {   EIP_VID(4)      "Parker Hannifin Corp. (Veriflo Division)" },
    {   EIP_VID(5)      "Rockwell Automation/Reliance Elec." },
    {   EIP_VID(6)      "Reserved" },
    {   EIP_VID(7)      "SMC Corporation" },
    {   EIP_VID(8)      "Molex Incorporated" },
    {   EIP_VID(9)      "Western Reserve Controls Corp." },
    {   EIP_VID(10)     "Advanced Micro Controls Inc. (AMCI)" },
    {   EIP_VID(11)     "ASCO Pneumatic Controls" },
    {   EIP_VID(12)     "Banner Engineering Corp." },
    {   EIP_VID(13)     "Belden Wire & Cable Company" },
    {   EIP_VID(14)     "Cooper Interconnect" },
    {   EIP_VID(15)     "Reserved" },
    {   EIP_VID(16)     "Daniel Woodhead Co. (Woodhead Connectivity)" },
    {   EIP_VID(17)     "Dearborn Group Inc." },
    {   EIP_VID(18)     "Reserved" },
    {   EIP_VID(19)     "Helm Instrument Company" },
    {   EIP_VID(20)     "Huron Net Works" },
    {   EIP_VID(21)     "Lumberg, Inc." },
    {   EIP_VID(22)     "Online Development Inc.(Automation Value)" },
    {   EIP_VID(23)     "Vorne Industries, Inc." },
    {   EIP_VID(24)     "ODVA Special Reserve" },
    {   EIP_VID(25)     "Reserved" },
    {   EIP_VID(26)     "Festo Corporation" },
    {   EIP_VID(27)     "Reserved" },
    {   EIP_VID(28)     "Reserved" },
    {   EIP_VID(29)     "Reserved" },
    {   EIP_VID(30)     "Unico, Inc." },
    {   EIP_VID(31)     "Ross Controls" },
    {   EIP_VID(32)     "Reserved" },
    {   EIP_VID(33)     "Reserved" },
    {   EIP_VID(34)     "Hohner Corp." },
    {   EIP_VID(35)     "Micro Mo Electronics, Inc." },
    {   EIP_VID(36)     "MKS Instruments, Inc." },
    {   EIP_VID(37)     "Yaskawa Electric America formerly Magnetek Drives" },
    {   EIP_VID(38)     "Reserved" },
    {   EIP_VID(39)     "AVG Automation (Uticor)" },
    {   EIP_VID(40)     "Wago Corporation" },
    {   EIP_VID(41)     "Kinetics (Unit Instruments)" },
    {   EIP_VID(42)     "IMI Norgren Limited" },
    {   EIP_VID(43)     "BALLUFF, Inc." },
    {   EIP_VID(44)     "Yaskawa Electric America, Inc." },
    {   EIP_VID(45)     "Eurotherm Controls Inc" },
    {   EIP_VID(46)     "ABB Industrial Systems" },
    {   EIP_VID(47)     "Omron Corporation" },
    {   EIP_VID(48)     "TURCk, Inc." },
    {   EIP_VID(49)     "Grayhill Inc." },
    {   EIP_VID(50)     "Real Time Automation (C&ID)" },
    {   EIP_VID(51)     "Reserved" },
    {   EIP_VID(52)     "Numatics, Inc." },
    {   EIP_VID(53)     "Lutze, Inc." },
    {   EIP_VID(54)     "Reserved" },
    {   EIP_VID(55)     "Reserved" },
    {   EIP_VID(56)     "Softing GmbH" },
    {   EIP_VID(57)     "Pepperl + Fuchs" },
    {   EIP_VID(58)     "Spectrum Controls, Inc." },
    {   EIP_VID(59)     "D.I.P. Inc. MKS Inst." },
    {   EIP_VID(60)     "Applied Motion Products, Inc." },
    {   EIP_VID(61)     "Sencon Inc." },
    {   EIP_VID(62)     "High Country Tek" },
    {   EIP_VID(63)     "SWAC Automation Consult GmbH" },
    {   EIP_VID(64)     "Clippard Instrument Laboratory" },
    {   EIP_VID(65)     "Reserved" },
    {   EIP_VID(66)     "Reserved" },
    {   EIP_VID(67)     "Reserved" },
    {   EIP_VID(68)     "Eaton Electrical" },
    {   EIP_VID(69)     "Reserved" },
    {   EIP_VID(70)     "Reserved" },
    {   EIP_VID(71)     "Toshiba International Corp." },
    {   EIP_VID(72)     "Control Technology Incorporated" },
    {   EIP_VID(73)     "TCS (NZ) Ltd." },
    {   EIP_VID(74)     "Hitachi, Ltd." },
    {   EIP_VID(75)     "ABB Robotics Products AB" },
    {   EIP_VID(76)     "NKE Corporation" },
    {   EIP_VID(77)     "Rockwell Software, Inc." },
    {   EIP_VID(78)     "Escort Memory Systems (A Datalogic Group Co.)" },
    {   EIP_VID(79)     "Reserved" },
    {   EIP_VID(80)     "Industrial Devices Corporation" },
    {   EIP_VID(81)     "IXXAT Automation GmbH" },
    {   EIP_VID(82)     "Mitsubishi Electric Automation, Inc." },
    {   EIP_VID(83)     "OPTO-22" },
    {   EIP_VID(84)     "Reserved" },
    {   EIP_VID(85)     "Reserved" },
    {   EIP_VID(86)     "Horner Electric" },
    {   EIP_VID(87)     "Burkert Werke GmbH & Co. KG" },
    {   EIP_VID(88)     "Reserved" },
    {   EIP_VID(89)     "Industrial Indexing Systems, Inc." },
    {   EIP_VID(90)     "HMS Industrial Networks AB" },
    {   EIP_VID(91)     "Robicon" },
    {   EIP_VID(92)     "Helix Technology (Granville-Phillips)" },
    {   EIP_VID(93)     "Arlington Laboratory" },
    {   EIP_VID(94)     "Advantech Co. Ltd." },
    {   EIP_VID(95)     "Square D Company" },
    {   EIP_VID(96)     "Digital Electronics Corp." },
    {   EIP_VID(97)     "Danfoss" },
    {   EIP_VID(98)     "Reserved" },
    {   EIP_VID(99)     "Reserved" },
    {   EIP_VID(100)    "Bosch Rexroth Corporation, Pneumatics" },
    {   EIP_VID(101)    "Applied Materials, Inc." },
    {   EIP_VID(102)    "Showa Electric Wire & Cable Co." },
    {   EIP_VID(103)    "Pacific Scientific (API Controls Inc.)" },
    {   EIP_VID(104)    "Sharp Manufacturing Systems Corp." },
    {   EIP_VID(105)    "Olflex Wire & Cable, Inc." },
    {   EIP_VID(106)    "Reserved" },
    {   EIP_VID(107)    "Unitrode" },
    {   EIP_VID(108)    "Beckhoff Automation GmbH" },
    {   EIP_VID(109)    "National Instruments" },
    {   EIP_VID(110)    "Mykrolis Corporations (Millipore)" },
    {   EIP_VID(111)    "International Motion Controls Corp." },
    {   EIP_VID(112)    "Reserved" },
    {   EIP_VID(113)    "SEG Kempen GmbH" },
    {   EIP_VID(114)    "Reserved" },
    {   EIP_VID(115)    "Reserved" },
    {   EIP_VID(116)    "MTS Systems Corp." },
    {   EIP_VID(117)    "Krones, Inc" },
    {   EIP_VID(118)    "Reserved" },
    {   EIP_VID(119)    "EXOR Electronic R & D" },
    {   EIP_VID(120)    "SIEI S.p.A." },
    {   EIP_VID(121)    "KUKA Roboter GmbH" },
    {   EIP_VID(122)    "Reserved" },
    {   EIP_VID(123)    "SEC (Samsung Electronics Co., Ltd)" },
    {   EIP_VID(124)    "Binary Electronics Ltd" },
    {   EIP_VID(125)    "Flexible Machine Controls" },
    {   EIP_VID(126)    "Reserved" },
    {   EIP_VID(127)    "ABB Inc. (Entrelec)" },
    {   EIP_VID(128)    "MAC Valves, Inc." },
    {   EIP_VID(129)    "Auma Actuators Inc" },
    {   EIP_VID(130)    "Toyoda Machine Works, Ltd" },
    {   EIP_VID(131)    "Reserved" },
    {   EIP_VID(132)    "Reserved" },
    {   EIP_VID(133)    "Balogh T.A.G., Corporation" },
    {   EIP_VID(134)    "TR Systemtechnik GmbH" },
    {   EIP_VID(135)    "UNIPULSE Corporation" },
    {   EIP_VID(136)    "Reserved" },
    {   EIP_VID(137)    "Reserved" },
    {   EIP_VID(138)    "Conxall Corporation Inc." },
    {   EIP_VID(139)    "Reserved" },
    {   EIP_VID(140)    "Reserved" },
    {   EIP_VID(141)    "Kuramo Electric Co., Ltd." },
    {   EIP_VID(142)    "Creative Micro Designs" },
    {   EIP_VID(143)    "GE Industrial Systems" },
    {   EIP_VID(144)    "Leybold Vacuum GmbH" },
    {   EIP_VID(145)    "Siemens Energy & Automation/Drives" },
    {   EIP_VID(146)    "Kodensha Ltd" },
    {   EIP_VID(147)    "Motion Engineering, Inc." },
    {   EIP_VID(148)    "Honda Engineering Co., Ltd" },
    {   EIP_VID(149)    "EIM Valve Controls" },
    {   EIP_VID(150)    "Melec Inc." },
    {   EIP_VID(151)    "Sony Manufacturing Systems Corporation" },
    {   EIP_VID(152)    "North American Mfg." },
    {   EIP_VID(153)    "WATLOW" },
    {   EIP_VID(154)    "Japan Radio Co., Ltd" },
    {   EIP_VID(155)    "NADEX Co., Ltd" },
    {   EIP_VID(156)    "Ametek Automation & Process Technologies" },
    {   EIP_VID(157)    "Reserved" },
    {   EIP_VID(158)    "KVASER AB" },
    {   EIP_VID(159)    "IDEC IZUMI Corporation" },
    {   EIP_VID(160)    "Mitsubishi Heavy Industries Ltd" },
    {   EIP_VID(161)    "Mitsubishi Electric Corporation" },
    {   EIP_VID(162)    "Horiba-STEC Inc." },
    {   EIP_VID(163)    "esd electronic system design gmbh" },
    {   EIP_VID(164)    "DAIHEN Corporation" },
    {   EIP_VID(165)    "Tyco Valves & Controls/Keystone" },
    {   EIP_VID(166)    "EBARA Corporation" },
    {   EIP_VID(167)    "Reserved" },
    {   EIP_VID(168)    "Reserved" },
    {   EIP_VID(169)    "Hokuyo Electric Co. Ltd" },
    {   EIP_VID(170)    "Pyramid Solutions, Inc." },
    {   EIP_VID(171)    "Denso Wave Incorporated" },
    {   EIP_VID(172)    "HLS Hard-Line Solutions Inc" },
    {   EIP_VID(173)    "Caterpillar, Inc." },
    {   EIP_VID(174)    "PDL Electronics Ltd." },
    {   EIP_VID(175)    "Reserved" },
    {   EIP_VID(176)    "Red Lion Controls" },
    {   EIP_VID(177)    "ANELVA Corporation" },
    {   EIP_VID(178)    "Toyo Denki Seizo KK" },
    {   EIP_VID(179)    "Sanyo Denki Co., Ltd" },
    {   EIP_VID(180)    "Advanced Energy Japan K.K. (Aera Japan)" },
    {   EIP_VID(181)    "Pilz GmbH & Co" },
    {   EIP_VID(182)    "Marsh Bellofram-Bellofram PCD Division" },
    {   EIP_VID(183)    "Reserved" },
    {   EIP_VID(184)    "M-SYSTEM Co. Ltd" },
    {   EIP_VID(185)    "Nissin Electric Co., Ltd" },
    {   EIP_VID(186)    "Hitachi Metals Ltd." },
    {   EIP_VID(187)    "Oriental Motor Company" },
    {   EIP_VID(188)    "A&D Co., Ltd" },
    {   EIP_VID(189)    "Phasetronics, Inc." },
    {   EIP_VID(190)    "Cummins Engine Company" },
    {   EIP_VID(191)    "Deltron Inc." },
    {   EIP_VID(192)    "Geneer Corporation" },
    {   EIP_VID(193)    "Anatol Automation, Inc." },
    {   EIP_VID(194)    "Reserved" },
    {   EIP_VID(195)    "Reserved" },
    {   EIP_VID(196)    "Medar, Inc." },
    {   EIP_VID(197)    "Comdel Inc." },
    {   EIP_VID(198)    "Advanced Energy Industries, Inc" },
    {   EIP_VID(199)    "Reserved" },
    {   EIP_VID(200)    "DAIDEN Co., Ltd" },
    {   EIP_VID(201)    "CKD Corporation" },
    {   EIP_VID(202)    "Toyo Electric Corporation" },
    {   EIP_VID(203)    "Reserved" },
    {   EIP_VID(204)    "AuCom Electronics Ltd" },
    {   EIP_VID(205)    "Shinko Electric Co., Ltd" },
    {   EIP_VID(206)    "Vector Informatik GmbH" },
    {   EIP_VID(207)    "Reserved" },
    {   EIP_VID(208)    "Moog Inc." },
    {   EIP_VID(209)    "Contemporary Controls" },
    {   EIP_VID(210)    "Tokyo Sokki Kenkyujo Co., Ltd" },
    {   EIP_VID(211)    "Schenck-AccuRate, Inc." },
    {   EIP_VID(212)    "The Oilgear Company" },
    {   EIP_VID(213)    "Reserved" },
    {   EIP_VID(214)    "ASM Japan K.K." },
    {   EIP_VID(215)    "HIRATA Corp." },
    {   EIP_VID(216)    "SUNX Limited" },
    {   EIP_VID(217)    "Meidensha Corp." },
    {   EIP_VID(218)    "NIDEC SANKYO CORPORATION (Sankyo Seiki Mfg. Co., Ltd)" },
    {   EIP_VID(219)    "KAMRO Corp." },
    {   EIP_VID(220)    "Nippon System Development Co., Ltd" },
    {   EIP_VID(221)    "EBARA Technologies Inc." },
    {   EIP_VID(222)    "Reserved" },
    {   EIP_VID(223)    "Reserved" },
    {   EIP_VID(224)    "SG Co., Ltd" },
    {   EIP_VID(225)    "Vaasa Institute of Technology" },
    {   EIP_VID(226)    "MKS Instruments (ENI Technology)" },
    {   EIP_VID(227)    "Tateyama System Laboratory Co., Ltd." },
    {   EIP_VID(228)    "QLOG Corporation" },
    {   EIP_VID(229)    "Matric Limited Inc." },
    {   EIP_VID(230)    "NSD Corporation" },
    {   EIP_VID(231)    "Reserved" },
    {   EIP_VID(232)    "Sumitomo Wiring Systems, Ltd" },
    {   EIP_VID(233)    "Group 3 Technology Ltd" },
    {   EIP_VID(234)    "CTI Cryogenics" },
    {   EIP_VID(235)    "POLSYS CORP" },
    {   EIP_VID(236)    "Ampere Inc." },
    {   EIP_VID(237)    "Reserved" },
    {   EIP_VID(238)    "Simplatroll Ltd" },
    {   EIP_VID(239)    "Reserved" },
    {   EIP_VID(240)    "Reserved" },
    {   EIP_VID(241)    "Leading Edge Design" },
    {   EIP_VID(242)    "Humphrey Products" },
    {   EIP_VID(243)    "Schneider Automation, Inc." },
    {   EIP_VID(244)    "Westlock Controls Corp." },
    {   EIP_VID(245)    "Nihon Weidmuller Co., Ltd" },
    {   EIP_VID(246)    "Brooks Instrument (Div. of Emerson)" },
    {   EIP_VID(247)    "Reserved" },
    {   EIP_VID(248)    " Moeller GmbH" },
    {   EIP_VID(249)    "Varian Vacuum Products" },
    {   EIP_VID(250)    "Yokogawa Electric Corporation" },
    {   EIP_VID(251)    "Electrical Design Daiyu Co., Ltd" },
    {   EIP_VID(252)    "Omron Software Co., Ltd" },
    {   EIP_VID(253)    "BOC Edwards" },
    {   EIP_VID(254)    "Control Technology Corporation" },
    {   EIP_VID(255)    "Bosch Rexroth" },
    {   EIP_VID(256)    "Turck" },
    {   EIP_VID(257)    "Control Techniques PLC" },
    {   EIP_VID(258)    "Hardy Instruments, Inc." },
    {   EIP_VID(259)    "LS Industrial Systems" },
    {   EIP_VID(260)    "E.O.A. Systems Inc." },
    {   EIP_VID(261)    "Reserved" },
    {   EIP_VID(262)    "New Cosmos Electric Co., Ltd." },
    {   EIP_VID(263)    "Sense Eletronica LTDA" },
    {   EIP_VID(264)    "Xycom, Inc." },
    {   EIP_VID(265)    "Baldor Electric" },
    {   EIP_VID(266)    "Reserved" },
    {   EIP_VID(267)    "Patlite Corporation" },
    {   EIP_VID(268)    "Reserved" },
    {   EIP_VID(269)    "Mogami Wire & Cable Corporation" },
    {   EIP_VID(270)    "Welding Technology Corporation (WTC)" },
    {   EIP_VID(271)    "Reserved" },
    {   EIP_VID(272)    "Deutschmann Automation GmbH" },
    {   EIP_VID(273)    "ICP Panel-Tec Inc." },
    {   EIP_VID(274)    "Bray Controls USA" },
    {   EIP_VID(275)    "Reserved" },
    {   EIP_VID(276)    "Status Technologies" },
    {   EIP_VID(277)    "Trio Motion Technology Ltd" },
    {   EIP_VID(278)    "Sherrex Systems Ltd" },
    {   EIP_VID(279)    "Adept Technology, Inc." },
    {   EIP_VID(280)    "Spang Power Electronics" },
    {   EIP_VID(281)    "Reserved" },
    {   EIP_VID(282)    "Acrosser Technology Co., Ltd" },
    {   EIP_VID(283)    "Hilscher GmbH" },
    {   EIP_VID(284)    "IMAX Corporation" },
    {   EIP_VID(285)    "Electronic Innovation, Inc. (Falter Engineering)" },
    {   EIP_VID(286)    "Netlogic Inc." },
    {   EIP_VID(287)    "Bosch Rexroth Corporation, Indramat" },
    {   EIP_VID(288)    "Reserved" },
    {   EIP_VID(289)    "Reserved" },
    {   EIP_VID(290)    "Murata  Machinery Ltd." },
    {   EIP_VID(291)    "MTT Company Ltd." },
    {   EIP_VID(292)    "Kanematsu Semiconductor Corp." },
    {   EIP_VID(293)    "Takebishi Electric Sales Co." },
    {   EIP_VID(294)    "Tokyo Electron Device Ltd" },
    {   EIP_VID(295)    "PFU Limited" },
    {   EIP_VID(296)    "Hakko Automation Co., Ltd." },
    {   EIP_VID(297)    "Advanet Inc." },
    {   EIP_VID(298)    "Tokyo Electron Software Technologies Ltd." },
    {   EIP_VID(299)    "Reserved" },
    {   EIP_VID(300)    "Shinagawa Electric Wire Co., Ltd." },
    {   EIP_VID(301)    "Yokogawa M&C Corporation" },
    {   EIP_VID(302)    "KONAN Electric Co., Ltd." },
    {   EIP_VID(303)    "Binar Elektronik AB" },
    {   EIP_VID(304)    "Furukawa Electric Co." },
    {   EIP_VID(305)    "Cooper Energy Services" },
    {   EIP_VID(306)    "Schleicher GmbH & Co." },
    {   EIP_VID(307)    "Hirose Electric Co., Ltd" },
    {   EIP_VID(308)    "Western Servo Design Inc." },
    {   EIP_VID(309)    "Prosoft Technology" },
    {   EIP_VID(310)    "Reserved" },
    {   EIP_VID(311)    "Towa Shoko Co., Ltd" },
    {   EIP_VID(312)    "Kyopal Co., Ltd" },
    {   EIP_VID(313)    "Extron Co." },
    {   EIP_VID(314)    "Wieland Electric GmbH" },
    {   EIP_VID(315)    "SEW Eurodrive GmbH" },
    {   EIP_VID(316)    "Aera Corporation" },
    {   EIP_VID(317)    "STA Reutlingen" },
    {   EIP_VID(318)    "Reserved" },
    {   EIP_VID(319)    "Fuji Electric Co., Ltd." },
    {   EIP_VID(320)    "Reserved" },
    {   EIP_VID(321)    "Reserved" },
    {   EIP_VID(322)    "ifm efector, inc." },
    {   EIP_VID(323)    "Reserved" },
    {   EIP_VID(324)    "IDEACOD-Hohner Automation S.A." },
    {   EIP_VID(325)    "CommScope Inc." },
    {   EIP_VID(326)    "GE Fanuc Automation North America, Inc." },
    {   EIP_VID(327)    "Matsushita Electric Industrial Co., Ltd" },
    {   EIP_VID(328)    "Okaya Electronics Corporation" },
    {   EIP_VID(329)    "KASHIYAMA Industries, Ltd" },
    {   EIP_VID(330)    "JVC" },
    {   EIP_VID(331)    "Interface Corporation" },
    {   EIP_VID(332)    "Grape Systems Inc." },
    {   EIP_VID(333)    "Reserved" },
    {   EIP_VID(334)    "Reserved" },
    {   EIP_VID(335)    "Toshiba IT & Control Systems Corporation" },
    {   EIP_VID(336)    "Sanyo Machine Works, Ltd." },
    {   EIP_VID(337)    "Vansco Electronics Ltd." },
    {   EIP_VID(338)    "Dart Container Corp." },
    {   EIP_VID(339)    "Livingston & Co., Inc." },
    {   EIP_VID(340)    "Alfa Laval LKM as" },
    {   EIP_VID(341)    "BF ENTRON Ltd. (British Federal)" },
    {   EIP_VID(342)    "Bekaert Engineering NV" },
    {   EIP_VID(343)    "Ferran  Scientific Inc." },
    {   EIP_VID(344)    "KEBA AG" },
    {   EIP_VID(345)    "Endress + Hauser" },
    {   EIP_VID(346)    "Reserved" },
    {   EIP_VID(347)    "ABB ALSTOM Power UK Ltd. (EGT)" },
    {   EIP_VID(348)    "Berger Lahr GmbH" },
    {   EIP_VID(349)    "Reserved" },
    {   EIP_VID(350)    "Federal Signal Corp." },
    {   EIP_VID(351)    "Kawasaki Robotics (USA), Inc." },
    {   EIP_VID(352)    "Bently Nevada Corporation" },
    {   EIP_VID(353)    "Reserved" },
    {   EIP_VID(354)    "FRABA Posital GmbH" },
    {   EIP_VID(355)    "Elsag Bailey, Inc." },
    {   EIP_VID(356)    "Fanuc Robotics America" },
    {   EIP_VID(357)    "Reserved" },
    {   EIP_VID(358)    "Surface Combustion, Inc." },
    {   EIP_VID(359)    "Reserved" },
    {   EIP_VID(360)    "AILES Electronics Ind. Co., Ltd." },
    {   EIP_VID(361)    "Wonderware Corporation" },
    {   EIP_VID(362)    "Particle Measuring Systems, Inc." },
    {   EIP_VID(363)    "Reserved" },
    {   EIP_VID(364)    "Reserved" },
    {   EIP_VID(365)    "BITS Co., Ltd" },
    {   EIP_VID(366)    "Japan Aviation Electronics Industry Ltd" },
    {   EIP_VID(367)    "Keyence Corporation" },
    {   EIP_VID(368)    "Kuroda Precision Industries Ltd." },
    {   EIP_VID(369)    "Mitsubishi Electric Semiconductor Application" },
    {   EIP_VID(370)    "Nippon Seisen Cable, Ltd." },
    {   EIP_VID(371)    "Omron ASO Co., Ltd" },
    {   EIP_VID(372)    "Seiko Seiki Co., Ltd." },
    {   EIP_VID(373)    "Sumitomo Heavy Industries, Ltd." },
    {   EIP_VID(374)    "Tango Computer Service Corporation" },
    {   EIP_VID(375)    "Technology Service, Inc." },
    {   EIP_VID(376)    "Toshiba Information Systems (Japan) Corporation" },
    {   EIP_VID(377)    "TOSHIBA Schneider Inverter Corporation" },
    {   EIP_VID(378)    "Toyooki Kogyo Co., Ltd." },
    {   EIP_VID(379)    "XEBEC" },
    {   EIP_VID(380)    "Madison Cable Corporation" },
    {   EIP_VID(381)    "Hitati Engineering & Services Co., Ltd" },
    {   EIP_VID(382)    "TEM-TECH Lab Co., Ltd" },
    {   EIP_VID(383)    "International Laboratory Corporation" },
    {   EIP_VID(384)    "Dyadic Systems Co., Ltd." },
    {   EIP_VID(385)    "SETO Electronics Industry Co., Ltd" },
    {   EIP_VID(386)    "Tokyo Electron Kyushu Limited" },
    {   EIP_VID(387)    "KEI System Co., Ltd" },
    {   EIP_VID(388)    "Reserved" },
    {   EIP_VID(389)    "Asahi Engineering Co., Ltd" },
    {   EIP_VID(390)    "Contrex Inc." },
    {   EIP_VID(391)    "Paradigm Controls Ltd." },
    {   EIP_VID(392)    "Reserved" },
    {   EIP_VID(393)    "Ohm Electric Co., Ltd." },
    {   EIP_VID(394)    "RKC Instrument Inc." },
    {   EIP_VID(395)    "Suzuki Motor Corporation" },
    {   EIP_VID(396)    "Custom Servo Motors Inc." },
    {   EIP_VID(397)    "PACE Control Systems" },
    {   EIP_VID(398)    "Reserved" },
    {   EIP_VID(399)    "Reserved" },
    {   EIP_VID(400)    "LINTEC Co., Ltd." },
    {   EIP_VID(401)    "Hitachi Cable Ltd." },
    {   EIP_VID(402)    "BUSWARE Direct" },
    {   EIP_VID(403)    "Eaton Electric B.V. (former Holec Holland N.V.)" },
    {   EIP_VID(404)    "VAT Vakuumventile AG" },
    {   EIP_VID(405)    "Scientific Technologies Incorporated" },
    {   EIP_VID(406)    "Alfa Instrumentos Eletronicos Ltda" },
    {   EIP_VID(407)    "TWK Elektronik GmbH" },
    {   EIP_VID(408)    "ABB Welding Systems AB" },
    {   EIP_VID(409)    "BYSTRONIC Maschinen AG" },
    {   EIP_VID(410)    "Kimura Electric Co., Ltd" },
    {   EIP_VID(411)    "Nissei Plastic Industrial Co., Ltd" },
    {   EIP_VID(412)    "Reserved" },
    {   EIP_VID(413)    "Kistler-Morse Corporation" },
    {   EIP_VID(414)    "Proteous Industries Inc." },
    {   EIP_VID(415)    "IDC Corporation" },
    {   EIP_VID(416)    "Nordson Corporation" },
    {   EIP_VID(417)    "Rapistan Systems" },
    {   EIP_VID(418)    "LP-Elektronik GmbH" },
    {   EIP_VID(419)    "GERBI & FASE S.p.A.(Fase Saldatura)" },
    {   EIP_VID(420)    "Phoenix Digital Corporation" },
    {   EIP_VID(421)    "Z-World Engineering" },
    {   EIP_VID(422)    "Honda R&D Co., Ltd." },
    {   EIP_VID(423)    "Bionics Instrument Co., Ltd." },
    {   EIP_VID(424)    "Teknic, Inc." },
    {   EIP_VID(425)    "R.Stahl, Inc." },
    {   EIP_VID(426)    "Reserved" },
    {   EIP_VID(427)    "Ryco Graphic Manufacturing Inc." },
    {   EIP_VID(428)    "Giddings & Lewis, Inc." },
    {   EIP_VID(429)    "Koganei Corporation" },
    {   EIP_VID(430)    "Reserved" },
    {   EIP_VID(431)    "Nichigoh Communication Electric Wire Co., Ltd." },
    {   EIP_VID(432)    "Reserved" },
    {   EIP_VID(433)    "Fujikura Ltd." },
    {   EIP_VID(434)    "AD Link Technology Inc." },
    {   EIP_VID(435)    "StoneL Corporation" },
    {   EIP_VID(436)    "Computer Optical Products, Inc." },
    {   EIP_VID(437)    "CONOS Inc." },
    {   EIP_VID(438)    "Erhardt + Leimer GmbH" },
    {   EIP_VID(439)    "UNIQUE Co. Ltd" },
    {   EIP_VID(440)    "Roboticsware, Inc." },
    {   EIP_VID(441)    "Nachi Fujikoshi Corporation" },
    {   EIP_VID(442)    "Hengstler GmbH" },
    {   EIP_VID(443)    "Reserved" },
    {   EIP_VID(444)    "SUNNY GIKEN Inc." },
    {   EIP_VID(445)    "Lenze Drive Systems GmbH" },
    {   EIP_VID(446)    "CD Systems B.V." },
    {   EIP_VID(447)    "FMT/Aircraft Gate Support Systems AB" },
    {   EIP_VID(448)    "Axiomatic Technologies Corp" },
    {   EIP_VID(449)    "Embedded System Products, Inc." },
    {   EIP_VID(450)    "Reserved" },
    {   EIP_VID(451)    "Mencom Corporation" },
    {   EIP_VID(452)    "Reserved" },
    {   EIP_VID(453)    "Matsushita Welding Systems Co., Ltd." },
    {   EIP_VID(454)    "Dengensha Mfg. Co. Ltd." },
    {   EIP_VID(455)    "Quinn Systems Ltd." },
    {   EIP_VID(456)    "Tellima Technology Ltd" },
    {   EIP_VID(457)    "MDT, Software" },
    {   EIP_VID(458)    "Taiwan Keiso Co., Ltd" },
    {   EIP_VID(459)    "Pinnacle Systems" },
    {   EIP_VID(460)    "Ascom Hasler Mailing Sys" },
    {   EIP_VID(461)    "INSTRUMAR Limited" },
    {   EIP_VID(462)    "Reserved" },
    {   EIP_VID(463)    "Navistar International Transportation Corp" },
    {   EIP_VID(464)    "Huettinger Elektronik GmbH + Co. KG" },
    {   EIP_VID(465)    "OCM Technology Inc." },
    {   EIP_VID(466)    "Professional Supply Inc." },
    {   EIP_VID(467)    "Control Solutions" },
    {   EIP_VID(468)    "Baumer IVO GmbH & Co. KG" },
    {   EIP_VID(469)    "Worcester Controls Corporation" },
    {   EIP_VID(470)    "Pyramid Technical Consultants, Inc." },
    {   EIP_VID(471)    "Reserved" },
    {   EIP_VID(472)    "Apollo Fire Detectors Limited" },
    {   EIP_VID(473)    "Avtron Manufacturing, Inc." },
    {   EIP_VID(474)    "Reserved" },
    {   EIP_VID(475)    "Tokyo Keiso Co., Ltd." },
    {   EIP_VID(476)    "Daishowa Swiki Co., Ltd." },
    {   EIP_VID(477)    "Kojima Instruments Inc." },
    {   EIP_VID(478)    "Shimadzu Corporation" },
    {   EIP_VID(479)    "Tatsuta Electric Wire & Cable Co., Ltd." },
    {   EIP_VID(480)    "MECS Corporation" },
    {   EIP_VID(481)    "Tahara Electric" },
    {   EIP_VID(482)    "Koyo Electronics" },
    {   EIP_VID(483)    "Clever Devices" },
    {   EIP_VID(484)    "GCD Hardware & Software GmbH" },
    {   EIP_VID(485)    "Reserved" },
    {   EIP_VID(486)    "Miller Electric Mfg Co." },
    {   EIP_VID(487)    "GEA Tuchenhagen GmbH" },
    {   EIP_VID(488)    "Riken Keiki Co., LTD" },
    {   EIP_VID(489)    "Keisokugiken Corporation" },
    {   EIP_VID(490)    "Fuji Machine Mfg. Co., Ltd" },
    {   EIP_VID(491)    "Reserved" },
    {   EIP_VID(492)    "Nidec-Shimpo Corp." },
    {   EIP_VID(493)    "UTEC Corporation" },
    {   EIP_VID(494)    "Sanyo Electric Co. Ltd." },
    {   EIP_VID(495)    "Reserved" },
    {   EIP_VID(496)    "Reserved" },
    {   EIP_VID(497)    "Okano Electric Wire Co. Ltd" },
    {   EIP_VID(498)    "Shimaden Co. Ltd." },
    {   EIP_VID(499)    "Teddington Controls Ltd" },
    {   EIP_VID(500)    "Reserved" },
    {   EIP_VID(501)    "VIPA GmbH" },
    {   EIP_VID(502)    "Warwick Manufacturing Group" },
    {   EIP_VID(503)    "Danaher Controls" },
    {   EIP_VID(504)    "Reserved" },
    {   EIP_VID(505)    "Reserved" },
    {   EIP_VID(506)    "American Science & Engineering" },
    {   EIP_VID(507)    "Accutron Controls International Inc." },
    {   EIP_VID(508)    "Norcott Technologies Ltd" },
    {   EIP_VID(509)    "TB Woods, Inc" },
    {   EIP_VID(510)    "Proportion-Air, Inc." },
    {   EIP_VID(511)    "SICK Stegmann GmbH" },
    {   EIP_VID(512)    "Reserved" },
    {   EIP_VID(513)    "Edwards Signaling" },
    {   EIP_VID(514)    "Sumitomo Metal Industries, Ltd" },
    {   EIP_VID(515)    "Cosmo Instruments Co., Ltd." },
    {   EIP_VID(516)    "Denshosha Co., Ltd." },
    {   EIP_VID(517)    "Kaijo Corp." },
    {   EIP_VID(518)    "Michiproducts Co., Ltd." },
    {   EIP_VID(519)    "Miura Corporation" },
    {   EIP_VID(520)    "TG Information Network Co., Ltd." },
    {   EIP_VID(521)    "Fujikin , Inc." },
    {   EIP_VID(522)    "Estic Corp." },
    {   EIP_VID(523)    "GS Hydraulic Sales" },
    {   EIP_VID(524)    "Reserved" },
    {   EIP_VID(525)    "MTE Limited" },
    {   EIP_VID(526)    "Hyde Park Electronics, Inc." },
    {   EIP_VID(527)    "Pfeiffer Vacuum GmbH" },
    {   EIP_VID(528)    "Cyberlogic Technologies" },
    {   EIP_VID(529)    "OKUMA Corporation FA Systems Division" },
    {   EIP_VID(530)    "Reserved" },
    {   EIP_VID(531)    "Hitachi Kokusai Electric Co., Ltd." },
    {   EIP_VID(532)    "SHINKO TECHNOS Co., Ltd." },
    {   EIP_VID(533)    "Itoh Electric Co., Ltd." },
    {   EIP_VID(534)    "Colorado Flow Tech Inc." },
    {   EIP_VID(535)    "Love Controls Division/Dwyer Inst." },
    {   EIP_VID(536)    "Alstom Drives and Controls" },
    {   EIP_VID(537)    "The Foxboro Company" },
    {   EIP_VID(538)    "Tescom Corporation" },
    {   EIP_VID(539)    "Reserved" },
    {   EIP_VID(540)    "Atlas Copco Controls UK" },
    {   EIP_VID(541)    "Reserved" },
    {   EIP_VID(542)    "Autojet Technologies" },
    {   EIP_VID(543)    "Prima Electronics S.p.A." },
    {   EIP_VID(544)    "PMA GmbH" },
    {   EIP_VID(545)    "Shimafuji Electric Co., Ltd" },
    {   EIP_VID(546)    "Oki Electric Industry Co., Ltd" },
    {   EIP_VID(547)    "Kyushu Matsushita Electric Co., Ltd" },
    {   EIP_VID(548)    "Nihon Electric Wire & Cable Co., Ltd" },
    {   EIP_VID(549)    "Tsuken Electric Ind Co., Ltd" },
    {   EIP_VID(550)    "Tamadic Co." },
    {   EIP_VID(551)    "MAATEL SA" },
    {   EIP_VID(552)    "OKUMA America" },
    {   EIP_VID(553)    "Control Techniques PLC-NA" },
    {   EIP_VID(554)    "TPC Wire & Cable" },
    {   EIP_VID(555)    "ATI Industrial Automation" },
    {   EIP_VID(556)    "Microcontrol (Australia) Pty Ltd" },
    {   EIP_VID(557)    "Serra Soldadura, S.A." },
    {   EIP_VID(558)    "Southwest Research Institute" },
    {   EIP_VID(559)    "Cabinplant International" },
    {   EIP_VID(560)    "Sartorius Mechatronics T&H GmbH" },
    {   EIP_VID(561)    "Comau S.p.A. Robotics & Final Assembly Division" },
    {   EIP_VID(562)    "Phoenix Contact" },
    {   EIP_VID(563)    "Yokogawa MAT Corporation" },
    {   EIP_VID(564)    "asahi sangyo co., ltd." },
    {   EIP_VID(565)    "Reserved" },
    {   EIP_VID(566)    "Akita Myotoku Ltd." },
    {   EIP_VID(567)    "OBARA Corp." },
    {   EIP_VID(568)    "Suetron Electronic GmbH" },
    {   EIP_VID(569)    "Reserved" },
    {   EIP_VID(570)    "Serck Controls Limited" },
    {   EIP_VID(571)    "Fairchild Industrial Products Company" },
    {   EIP_VID(572)    "ARO S.A." },
    {   EIP_VID(573)    "M2C GmbH" },
    {   EIP_VID(574)    "Shin Caterpillar Mitsubishi Ltd." },
    {   EIP_VID(575)    "Santest Co., Ltd." },
    {   EIP_VID(576)    "Cosmotechs Co., Ltd." },
    {   EIP_VID(577)    "Hitachi Electric Systems" },
    {   EIP_VID(578)    "Smartscan Ltd" },
    {   EIP_VID(579)    "Woodhead Software & Electronics France" },
    {   EIP_VID(580)    "Athena Controls, Inc." },
    {   EIP_VID(581)    "Syron Engineering & Manufacturing, Inc." },
    {   EIP_VID(582)    "Asahi Optical Co., Ltd." },
    {   EIP_VID(583)    "Sansha Electric Mfg. Co., Ltd." },
    {   EIP_VID(584)    "Nikki Denso Co., Ltd." },
    {   EIP_VID(585)    "Star Micronics, Co., Ltd." },
    {   EIP_VID(586)    "Ecotecnia Socirtat Corp." },
    {   EIP_VID(587)    "AC Technology Corp." },
    {   EIP_VID(588)    "West Instruments Limited" },
    {   EIP_VID(589)    "NTI Limited" },
    {   EIP_VID(590)    "Delta Computer Systems, Inc." },
    {   EIP_VID(591)    "FANUC Ltd." },
    {   EIP_VID(592)    "Hearn-Gu Lee" },
    {   EIP_VID(593)    "ABB Automation Products" },
    {   EIP_VID(594)    "Orion Machinery Co., Ltd." },
    {   EIP_VID(595)    "Reserved" },
    {   EIP_VID(596)    "Wire-Pro, Inc." },
    {   EIP_VID(597)    "Beijing Huakong Technology Co. Ltd." },
    {   EIP_VID(598)    "Yokoyama Shokai Co., Ltd." },
    {   EIP_VID(599)    "Toyogiken Co., Ltd." },
    {   EIP_VID(600)    "Coester Equipamentos Eletronicos Ltda." },
    {   EIP_VID(601)    "Reserved" },
    {   EIP_VID(602)    "Electroplating Engineers of Japan Ltd." },
    {   EIP_VID(603)    "ROBOX S.p.A." },
    {   EIP_VID(604)    "Spraying Systems Company" },
    {   EIP_VID(605)    "Benshaw Inc." },
    {   EIP_VID(606)    "ZPA-DP A.S." },
    {   EIP_VID(607)    "Wired Rite Systems" },
    {   EIP_VID(608)    "Tandis Research, Inc." },
    {   EIP_VID(609)    "SSD Drives GmbH" },
    {   EIP_VID(610)    "ULVAC Japan Ltd." },
    {   EIP_VID(611)    "DYNAX Corporation" },
    {   EIP_VID(612)    "Nor-Cal Products, Inc." },
    {   EIP_VID(613)    "Aros Electronics AB" },
    {   EIP_VID(614)    "Jun-Tech Co., Ltd." },
    {   EIP_VID(615)    "HAN-MI Co. Ltd." },
    {   EIP_VID(616)    "uniNtech (formerly SungGi Internet)" },
    {   EIP_VID(617)    "Hae Pyung Electronics Reserch Institute" },
    {   EIP_VID(618)    "Milwaukee Electronics" },
    {   EIP_VID(619)    "OBERG Industries" },
    {   EIP_VID(620)    "Parker Hannifin/Compumotor Division" },
    {   EIP_VID(621)    "TECHNO DIGITAL CORPORATION" },
    {   EIP_VID(622)    "Network Supply Co., Ltd." },
    {   EIP_VID(623)    "Union Electronics Co., Ltd." },
    {   EIP_VID(624)    "Tritronics Services PM Ltd." },
    {   EIP_VID(625)    "Rockwell Automation-Sprecher+Schuh" },
    {   EIP_VID(626)    "Matsushita Electric Industrial Co., Ltd/Motor Co." },
    {   EIP_VID(627)    "Rolls-Royce Energy Systems, Inc." },
    {   EIP_VID(628)    "JEONGIL INTERCOM CO., LTD" },
    {   EIP_VID(629)    "Interroll Corp." },
    {   EIP_VID(630)    "Hubbell Wiring Device-Kellems (Delaware)" },
    {   EIP_VID(631)    "Intelligent Motion Systems" },
    {   EIP_VID(632)    "Reserved" },
    {   EIP_VID(633)    "INFICON AG" },
    {   EIP_VID(634)    "Hirschmann, Inc." },
    {   EIP_VID(635)    "The Siemon Company" },
    {   EIP_VID(636)    "YAMAHA Motor Co. Ltd." },
    {   EIP_VID(637)    "aska corporation" },
    {   EIP_VID(638)    "Woodhead Connectivity" },
    {   EIP_VID(639)    "Trimble AB" },
    {   EIP_VID(640)    "Murrelektronik GmbH" },
    {   EIP_VID(641)    "Creatrix Labs, Inc." },
    {   EIP_VID(642)    "TopWorx" },
    {   EIP_VID(643)    "Kumho Industrial Co., Ltd." },
    {   EIP_VID(644)    "Wind River Systems, Inc." },
    {   EIP_VID(645)    "Bihl & Wiedemann GmbH" },
    {   EIP_VID(646)    "Harmonic Drive Systems Inc." },
    {   EIP_VID(647)    "Rikei Corporation" },
    {   EIP_VID(648)    "BL Autotec, Ltd." },
    {   EIP_VID(649)    "Hana Information & Technology Co., Ltd." },
    {   EIP_VID(650)    "Seoil Electric Co., Ltd." },
    {   EIP_VID(651)    "Fife Corporation" },
    {   EIP_VID(652)    "Shanghai Electrical Apparatus Research Institute" },
    {   EIP_VID(653)    "Reserved" },
    {   EIP_VID(654)    "Parasense Development Centre" },
    {   EIP_VID(655)    "Reserved" },
    {   EIP_VID(656)    "Reserved" },
    {   EIP_VID(657)    "Six Tau S.p.A." },
    {   EIP_VID(658)    "Aucos GmbH" },
    {   EIP_VID(659)    "Rotork Controls" },
    {   EIP_VID(660)    "Automationdirect.com" },
    {   EIP_VID(661)    "Thermo BLH" },
    {   EIP_VID(662)    "System Controls, Ltd." },
    {   EIP_VID(663)    "Univer S.p.A." },
    {   EIP_VID(664)    "MKS-Tenta Technology" },
    {   EIP_VID(665)    "Lika Electronic SNC" },
    {   EIP_VID(666)    "Mettler-Toledo, Inc." },
    {   EIP_VID(667)    "DXL USA Inc." },
    {   EIP_VID(668)    "Rockwell Automation/Entek IRD Intl." },
    {   EIP_VID(669)    "Nippon Otis Elevator Company" },
    {   EIP_VID(670)    "Sinano Electric, Co., Ltd." },
    {   EIP_VID(671)    "Sony Manufacturing Systems" },
    {   EIP_VID(672)    "Reserved" },
    {   EIP_VID(673)    "Contec Co., Ltd." },
    {   EIP_VID(674)    "Automated Solutions" },
    {   EIP_VID(675)    "Controlweigh" },
    {   EIP_VID(676)    "Reserved" },
    {   EIP_VID(677)    "Fincor Electronics" },
    {   EIP_VID(678)    "Cognex Corporation" },
    {   EIP_VID(679)    "Qualiflow" },
    {   EIP_VID(680)    "Weidmuller, Inc." },
    {   EIP_VID(681)    "Morinaga Milk Industry Co., Ltd." },
    {   EIP_VID(682)    "Takagi Industrial Co., Ltd." },
    {   EIP_VID(683)    "Wittenstein AG" },
    {   EIP_VID(684)    "Sena Technologies, Inc." },
    {   EIP_VID(685)    "Reserved" },
    {   EIP_VID(686)    "APV Products Unna" },
    {   EIP_VID(687)    "Creator Teknisk Utvedkling AB" },
    {   EIP_VID(688)    "Reserved" },
    {   EIP_VID(689)    "Mibu Denki Industrial Co., Ltd." },
    {   EIP_VID(690)    "Takamastsu Machineer Section" },
    {   EIP_VID(691)    "Startco Engineering Ltd." },
    {   EIP_VID(692)    "Reserved" },
    {   EIP_VID(693)    "Holjeron" },
    {   EIP_VID(694)    "ALCATEL High Vacuum Technology" },
    {   EIP_VID(695)    "Taesan LCD Co., Ltd." },
    {   EIP_VID(696)    "POSCON" },
    {   EIP_VID(697)    "VMIC" },
    {   EIP_VID(698)    "Matsushita Electric Works, Ltd." },
    {   EIP_VID(699)    "IAI Corporation" },
    {   EIP_VID(700)    "Horst GmbH" },
    {   EIP_VID(701)    "MicroControl GmbH & Co." },
    {   EIP_VID(702)    "Leine & Linde AB" },
    {   EIP_VID(703)    "Reserved" },
    {   EIP_VID(704)    "EC Elettronica Srl" },
    {   EIP_VID(705)    "VIT Software HB" },
    {   EIP_VID(706)    "Bronkhorst High-Tech B.V." },
    {   EIP_VID(707)    "Optex Co., Ltd." },
    {   EIP_VID(708)    "Yosio Electronic Co." },
    {   EIP_VID(709)    "Terasaki Electric Co., Ltd." },
    {   EIP_VID(710)    "Sodick Co., Ltd." },
    {   EIP_VID(711)    "MTS Systems Corporation-Automation Division" },
    {   EIP_VID(712)    "Mesa Systemtechnik" },
    {   EIP_VID(713)    "SHIN HO SYSTEM Co., Ltd." },
    {   EIP_VID(714)    "Goyo Electronics Co, Ltd." },
    {   EIP_VID(715)    "Loreme" },
    {   EIP_VID(716)    "SAB Brockskes GmbH & Co. KG" },
    {   EIP_VID(717)    "Trumpf Laser GmbH + Co. KG" },
    {   EIP_VID(718)    "Niigata Electronic Instruments Co., Ltd." },
    {   EIP_VID(719)    "Yokogawa Digital Computer Corporation" },
    {   EIP_VID(720)    "O.N. Electronic Co., Ltd." },
    {   EIP_VID(721)    "Industrial Control  Communication, Inc." },
    {   EIP_VID(722)    "ABB, Inc." },
    {   EIP_VID(723)    "ElectroWave USA, Inc." },
    {   EIP_VID(724)    "Industrial Network Controls, LLC" },
    {   EIP_VID(725)    "KDT Systems Co., Ltd." },
    {   EIP_VID(726)    "SEFA Technology Inc." },
    {   EIP_VID(727)    "Nippon POP Rivets and Fasteners Ltd." },
    {   EIP_VID(728)    "Yamato Scale Co., Ltd." },
    {   EIP_VID(729)    "Zener Electric" },
    {   EIP_VID(730)    "GSE Scale Systems" },
    {   EIP_VID(731)    "ISAS (Integrated Switchgear & Sys. Pty Ltd)" },
    {   EIP_VID(732)    "Beta LaserMike Limited" },
    {   EIP_VID(733)    "TOEI Electric Co., Ltd." },
    {   EIP_VID(734)    "Hakko Electronics Co., Ltd" },
    {   EIP_VID(735)    "Reserved" },
    {   EIP_VID(736)    "RFID, Inc." },
    {   EIP_VID(737)    "Adwin Corporation" },
    {   EIP_VID(738)    "Osaka Vacuum, Ltd." },
    {   EIP_VID(739)    "A-Kyung Motion, Inc." },
    {   EIP_VID(740)    "Camozzi S.P. A." },
    {   EIP_VID(741)    "Crevis Co., LTD" },
    {   EIP_VID(742)    "Rice Lake Weighing Systems" },
    {   EIP_VID(743)    "Linux Network Services" },
    {   EIP_VID(744)    "KEB Antriebstechnik GmbH" },
    {   EIP_VID(745)    "Hagiwara Electric Co., Ltd." },
    {   EIP_VID(746)    "Glass Inc. International" },
    {   EIP_VID(747)    "Reserved" },
    {   EIP_VID(748)    "DVT Corporation" },
    {   EIP_VID(749)    "Woodward Governor" },
    {   EIP_VID(750)    "Mosaic Systems, Inc." },
    {   EIP_VID(751)    "Laserline GmbH" },
    {   EIP_VID(752)    "COM-TEC, Inc." },
    {   EIP_VID(753)    "Weed Instrument" },
    {   EIP_VID(754)    "Prof-face European Technology Center" },
    {   EIP_VID(755)    "Fuji Automation Co., Ltd." },
    {   EIP_VID(756)    "Matsutame Co., Ltd." },
    {   EIP_VID(757)    "Hitachi Via Mechanics, Ltd." },
    {   EIP_VID(758)    "Dainippon Screen Mfg. Co. Ltd." },
    {   EIP_VID(759)    "FLS Automation A/S" },
    {   EIP_VID(760)    "ABB Stotz Kontakt GmbH" },
    {   EIP_VID(761)    "Technical Marine Service" },
    {   EIP_VID(762)    "Advanced Automation Associates, Inc." },
    {   EIP_VID(763)    "Baumer Ident GmbH" },
    {   EIP_VID(764)    "Tsubakimoto Chain Co." },
    {   EIP_VID(765)    "Reserved" },
    {   EIP_VID(766)    "Furukawa Co., Ltd." },
    {   EIP_VID(767)    "Active Power" },
    {   EIP_VID(768)    "CSIRO Mining Automation" },
    {   EIP_VID(769)    "Matrix Integrated Systems" },
    {   EIP_VID(770)    "Digitronic Automationsanlagen GmbH" },
    {   EIP_VID(771)    "SICK STEGMANN Inc." },
    {   EIP_VID(772)    "TAE-Antriebstechnik GmbH" },
    {   EIP_VID(773)    "Electronic Solutions" },
    {   EIP_VID(774)    "Rocon L.L.C." },
    {   EIP_VID(775)    "Dijitized Communications Inc." },
    {   EIP_VID(776)    "Asahi Organic Chemicals Industry Co., Ltd." },
    {   EIP_VID(777)    "Hodensha" },
    {   EIP_VID(778)    "Harting, Inc. NA" },
    {   EIP_VID(779)    "Kubler GmbH" },
    {   EIP_VID(780)    "Yamatake Corporation" },
    {   EIP_VID(781)    "JEOL" },
    {   EIP_VID(782)    "Yamatake Industrial Systems Co., Ltd." },
    {   EIP_VID(783)    "HAEHNE Elektronische Messgerate GmbH" },
    {   EIP_VID(784)    "Ci Technologies Pty Ltd (for Pelamos Industries)" },
    {   EIP_VID(785)    "N. SCHLUMBERGER & CIE" },
    {   EIP_VID(786)    "Teijin Seiki Co., Ltd." },
    {   EIP_VID(787)    "DAIKIN Industries, Ltd" },
    {   EIP_VID(788)    "RyuSyo Industrial Co., Ltd." },
    {   EIP_VID(789)    "SAGINOMIYA SEISAKUSHO, INC." },
    {   EIP_VID(790)    "Seishin Engineering Co., Ltd." },
    {   EIP_VID(791)    "Japan Support System Ltd." },
    {   EIP_VID(792)    "Decsys" },
    {   EIP_VID(793)    "Metronix Messgerate u. Elektronik GmbH" },
    {   EIP_VID(794)    "Reserved" },
    {   EIP_VID(795)    "Vaccon Company, Inc." },
    {   EIP_VID(796)    "Siemens Energy & Automation, Inc." },
    {   EIP_VID(797)    "Ten X Technology, Inc." },
    {   EIP_VID(798)    "Tyco Electronics" },
    {   EIP_VID(799)    "Delta Power Electronics Center" },
    {   EIP_VID(800)    "Denker" },
    {   EIP_VID(801)    "Autonics Corporation" },
    {   EIP_VID(802)    "JFE Electronic Engineering Pty. Ltd." },
    {   EIP_VID(803)    "Reserved" },
    {   EIP_VID(804)    "Electro-Sensors, Inc." },
    {   EIP_VID(805)    "Digi International, Inc." },
    {   EIP_VID(806)    "Texas Instruments" },
    {   EIP_VID(807)    "ADTEC Plasma Technology Co., Ltd" },
    {   EIP_VID(808)    "SICK AG" },
    {   EIP_VID(809)    "Ethernet Peripherals, Inc." },
    {   EIP_VID(810)    "Animatics Corporation" },
    {   EIP_VID(811)    "Reserved" },
    {   EIP_VID(812)    "Process Control Corporation" },
    {   EIP_VID(813)    "SystemV. Inc." },
    {   EIP_VID(814)    "Danaher Motion SRL" },
    {   EIP_VID(815)    "SHINKAWA Sensor Technology, Inc." },
    {   EIP_VID(816)    "Tesch GmbH & Co. KG" },
    {   EIP_VID(817)    "Reserved" },
    {   EIP_VID(818)    "Trend Controls Systems Ltd." },
    {   EIP_VID(819)    "Guangzhou ZHIYUAN Electronic Co., Ltd." },
    {   EIP_VID(820)    "Mykrolis Corporation" },
    {   EIP_VID(821)    "Bethlehem Steel Corporation" },
    {   EIP_VID(822)    "KK ICP" },
    {   EIP_VID(823)    "Takemoto Denki Corporation" },
    {   EIP_VID(824)    "The Montalvo Corporation" },
    {   EIP_VID(825)    "Reserved" },
    {   EIP_VID(826)    "LEONI Special Cables GmbH" },
    {   EIP_VID(827)    "Reserved" },
    {   EIP_VID(828)    "ONO SOKKI CO.,LTD." },
    {   EIP_VID(829)    "Rockwell Samsung Automation" },
    {   EIP_VID(830)    "SHINDENGEN ELECTRIC MFG. CO. LTD" },
    {   EIP_VID(831)    "Origin Electric Co. Ltd." },
    {   EIP_VID(832)    "Quest Technical Solutions, Inc." },
    {   EIP_VID(833)    "LS Cable, Ltd." },
    {   EIP_VID(834)    "Enercon-Nord Electronic GmbH" },
    {   EIP_VID(835)    "Northwire Inc." },
    {   EIP_VID(836)    "Engel Elektroantriebe GmbH" },
    {   EIP_VID(837)    "The Stanley Works" },
    {   EIP_VID(838)    "Celesco Transducer Products, Inc." },
    {   EIP_VID(839)    "Chugoku Electric Wire and Cable Co." },
    {   EIP_VID(840)    "Kongsberg Simrad AS" },
    {   EIP_VID(841)    "Panduit Corporation" },
    {   EIP_VID(842)    "Spellman High Voltage Electronics Corp." },
    {   EIP_VID(843)    "Kokusai Electric Alpha Co., Ltd." },
    {   EIP_VID(844)    "Brooks Automation, Inc." },
    {   EIP_VID(845)    "ANYWIRE CORPORATION" },
    {   EIP_VID(846)    "Honda Electronics Co. Ltd" },
    {   EIP_VID(847)    "REO Elektronik AG" },
    {   EIP_VID(848)    "Fusion UV Systems, Inc." },
    {   EIP_VID(849)    "ASI Advanced Semiconductor Instruments GmbH" },
    {   EIP_VID(850)    "Datalogic, Inc." },
    {   EIP_VID(851)    "SoftPLC Corporation" },
    {   EIP_VID(852)    "Dynisco Instruments LLC" },
    {   EIP_VID(853)    "WEG Industrias SA" },
    {   EIP_VID(854)    "Frontline Test Equipment, Inc." },
    {   EIP_VID(855)    "Tamagawa Seiki Co., Ltd." },
    {   EIP_VID(856)    "Multi Computing Co., Ltd." },
    {   EIP_VID(857)    "RVSI" },
    {   EIP_VID(858)    "Commercial Timesharing Inc." },
    {   EIP_VID(859)    "Tennessee Rand Automation LLC" },
    {   EIP_VID(860)    "Wacogiken Co., Ltd" },
    {   EIP_VID(861)    "Reflex Integration Inc." },
    {   EIP_VID(862)    "Siemens AG, A&D PI Flow Instruments" },
    {   EIP_VID(863)    "G. Bachmann Electronic GmbH" },
    {   EIP_VID(864)    "NT International" },
    {   EIP_VID(865)    "Schweitzer Engineering Laboratories" },
    {   EIP_VID(866)    "ATR Industrie-Elektronik GmbH Co." },
    {   EIP_VID(867)    "PLASMATECH Co., Ltd" },
    {   EIP_VID(868)    "Reserved" },
    {   EIP_VID(869)    "GEMU GmbH & Co. KG" },
    {   EIP_VID(870)    "Alcorn McBride Inc." },
    {   EIP_VID(871)    "MORI SEIKI CO., LTD" },
    {   EIP_VID(872)    "NodeTech Systems Ltd" },
    {   EIP_VID(873)    "Emhart Teknologies" },
    {   EIP_VID(874)    "Cervis, Inc." },
    {   EIP_VID(875)    "FieldServer Technologies (Div Sierra Monitor Corp)" },
    {   EIP_VID(876)    "NEDAP Power Supplies" },
    {   EIP_VID(877)    "Nippon Sanso Corporation" },
    {   EIP_VID(878)    "Mitomi Giken Co., Ltd." },
    {   EIP_VID(879)    "PULS GmbH" },
    {   EIP_VID(880)    "Reserved" },
    {   EIP_VID(881)    "Japan Control Engineering Ltd" },
    {   EIP_VID(882)    "Embedded Systems Korea (Former Zues Emtek Co Ltd.)" },
    {   EIP_VID(883)    "Automa SRL" },
    {   EIP_VID(884)    "Harms+Wende GmbH & Co KG" },
    {   EIP_VID(885)    "SAE-STAHL GmbH" },
    {   EIP_VID(886)    "Microwave Data Systems" },
    {   EIP_VID(887)    "Bernecker + Rainer Industrie-Elektronik GmbH" },
    {   EIP_VID(888)    "Hiprom Technologies" },
    {   EIP_VID(889)    "Reserved" },
    {   EIP_VID(890)    "Nitta Corporation" },
    {   EIP_VID(891)    "Kontron Modular Computers GmbH" },
    {   EIP_VID(892)    "Marlin Controls" },
    {   EIP_VID(893)    "ELCIS s.r.l." },
    {   EIP_VID(894)    "Acromag, Inc." },
    {   EIP_VID(895)    "Avery Weigh-Tronix" },
    {   EIP_VID(896)    "Reserved" },
    {   EIP_VID(897)    "Reserved" },
    {   EIP_VID(898)    "Reserved" },
    {   EIP_VID(899)    "Practicon Ltd" },
    {   EIP_VID(900)    "Schunk GmbH & Co. KG" },
    {   EIP_VID(901)    "MYNAH Technologies" },
    {   EIP_VID(902)    "Defontaine Groupe" },
    {   EIP_VID(903)    "Emerson Process Management Power & Water Solutions" },
    {   EIP_VID(904)    "F.A. Elec" },
    {   EIP_VID(905)    "Hottinger Baldwin Messtechnik GmbH" },
    {   EIP_VID(906)    "Coreco Imaging, Inc." },
    {   EIP_VID(907)    "London Electronics Ltd." },
    {   EIP_VID(908)    "HSD SpA" },
    {   EIP_VID(909)    "Comtrol Corporation" },
    {   EIP_VID(910)    "TEAM, S.A. (Tecnica Electronica de Automatismo Y Medida)" },
    {   EIP_VID(911)    "MAN B&W Diesel Ltd. Regulateurs Europa" },
    {   EIP_VID(912)    "Reserved" },
    {   EIP_VID(913)    "Reserved" },
    {   EIP_VID(914)    "Micro Motion, Inc." },
    {   EIP_VID(915)    "Eckelmann AG" },
    {   EIP_VID(916)    "Hanyoung Nux" },
    {   EIP_VID(917)    "Ransburg Industrial Finishing KK" },
    {   EIP_VID(918)    "Kun Hung Electric Co. Ltd." },
    {   EIP_VID(919)    "Brimos wegbebakening b.v." },
    {   EIP_VID(920)    "Nitto Seiki Co., Ltd" },
    {   EIP_VID(921)    "PPT Vision, Inc." },
    {   EIP_VID(922)    "Yamazaki Machinery Works" },
    {   EIP_VID(923)    "SCHMIDT Technology GmbH" },
    {   EIP_VID(924)    "Parker Hannifin SpA (SBC Division)" },
    {   EIP_VID(925)    "HIMA Paul Hildebrandt GmbH" },
    {   EIP_VID(926)    "RivaTek, Inc." },
    {   EIP_VID(927)    "Misumi Corporation" },
    {   EIP_VID(928)    "GE Multilin" },
    {   EIP_VID(929)    "Measurement Computing Corporation" },
    {   EIP_VID(930)    "Jetter AG" },
    {   EIP_VID(931)    "Tokyo Electronics Systems Corporation" },
    {   EIP_VID(932)    "Togami Electric Mfg. Co., Ltd." },
    {   EIP_VID(933)    "HK Systems" },
    {   EIP_VID(934)    "CDA Systems Ltd." },
    {   EIP_VID(935)    "Aerotech Inc." },
    {   EIP_VID(936)    "JVL Industrie Elektronik A/S" },
    {   EIP_VID(937)    "NovaTech Process Solutions LLC" },
    {   EIP_VID(938)    "Reserved" },
    {   EIP_VID(939)    "Cisco Systems" },
    {   EIP_VID(940)    "Grid Connect" },
    {   EIP_VID(941)    "ITW Automotive Finishing" },
    {   EIP_VID(942)    "HanYang System" },
    {   EIP_VID(943)    "ABB K.K. Technical Center" },
    {   EIP_VID(944)    "Taiyo Electric Wire & Cable Co., Ltd." },
    {   EIP_VID(945)    "Reserved" },
    {   EIP_VID(946)    "SEREN IPS INC" },
    {   EIP_VID(947)    "Belden CDT Electronics Division" },
    {   EIP_VID(948)    "ControlNet International" },
    {   EIP_VID(949)    "Gefran S.P.A." },
    {   EIP_VID(950)    "Jokab Safety AB" },
    {   EIP_VID(951)    "SUMITA OPTICAL GLASS, INC." },
    {   EIP_VID(952)    "Biffi Italia srl" },
    {   EIP_VID(953)    "Beck IPC GmbH" },
    {   EIP_VID(954)    "Copley Controls Corporation" },
    {   EIP_VID(955)    "Fagor Automation S. Coop." },
    {   EIP_VID(956)    "DARCOM" },
    {   EIP_VID(957)    "Frick Controls (div. of York International)" },
    {   EIP_VID(958)    "SymCom, Inc." },
    {   EIP_VID(959)    "Infranor" },
    {   EIP_VID(960)    "Kyosan Cable, Ltd." },
    {   EIP_VID(961)    "Varian Vacuum Technologies" },
    {   EIP_VID(962)    "Messung Systems" },
    {   EIP_VID(963)    "Xantrex Technology, Inc." },
    {   EIP_VID(964)    "StarThis Inc." },
    {   EIP_VID(965)    "Chiyoda Co., Ltd." },
    {   EIP_VID(966)    "Flowserve Corporation" },
    {   EIP_VID(967)    "Spyder Controls Corp." },
    {   EIP_VID(968)    "IBA AG" },
    {   EIP_VID(969)    "SHIMOHIRA ELECTRIC MFG.CO.,LTD" },
    {   EIP_VID(970)    "Reserved" },
    {   EIP_VID(971)    "Siemens L&A" },
    {   EIP_VID(972)    "Micro Innovations AG" },
    {   EIP_VID(973)    "Switchgear & Instrumentation" },
    {   EIP_VID(974)    "PRE-TECH CO., LTD." },
    {   EIP_VID(975)    "National Semiconductor" },
    {   EIP_VID(976)    "Invensys Process Systems" },
    {   EIP_VID(977)    "Ametek HDR Power Systems" },
    {   EIP_VID(978)    "Reserved" },
    {   EIP_VID(979)    "TETRA-K Corporation" },
    {   EIP_VID(980)    "C & M Corporation" },
    {   EIP_VID(981)    "Siempelkamp Maschinen" },
    {   EIP_VID(982)    "Reserved" },
    {   EIP_VID(983)    "Daifuku America Corporation" },
    {   EIP_VID(984)    "Electro-Matic Products Inc." },
    {   EIP_VID(985)    "BUSSAN MICROELECTRONICS CORP." },
    {   EIP_VID(986)    "ELAU AG" },
    {   EIP_VID(987)    "Hetronic USA" },
    {   EIP_VID(988)    "NIIGATA POWER SYSTEMS Co., Ltd." },
    {   EIP_VID(989)    "Software Horizons Inc." },
    {   EIP_VID(990)    "B3 Systems, Inc." },
    {   EIP_VID(991)    "Moxa Networking Co., Ltd." },
    {   EIP_VID(992)    "Reserved" },
    {   EIP_VID(993)    "S4 Integration" },
    {   EIP_VID(994)    "Elettro Stemi S.R.L." },
    {   EIP_VID(995)    "AquaSensors" },
    {   EIP_VID(996)    "Ifak System GmbH" },
    {   EIP_VID(997)    "SANKEI MANUFACTURING Co.,LTD." },
    {   EIP_VID(998)    "Emerson Network Power Co., Ltd." },
    {   EIP_VID(999)    "Fairmount Automation, Inc." },
    {   EIP_VID(1000)   "Bird Electronic Corporation" },
    {   EIP_VID(1001)   "Nabtesco Corporation" },
    {   EIP_VID(1002)   "AGM Electronics, Inc." },
    {   EIP_VID(1003)   "ARCX Inc." },
    {   EIP_VID(1004)   "DELTA I/O Co." },
    {   EIP_VID(1005)   "Chun IL Electric Ind. Co." },
    {   EIP_VID(1006)   "N-Tron" },
    {   EIP_VID(1007)   "Nippon Pneumatics/Fludics System CO.,LTD." },
    {   EIP_VID(1008)   "DDK Ltd." },
    {   EIP_VID(1009)   "Seiko Epson Corporation" },
    {   EIP_VID(1010)   "Halstrup-Walcher GmbH" },
    {   EIP_VID(1011)   "ITT" },
    {   EIP_VID(1012)   "Ground Fault Systems bv" },
    {   EIP_VID(1013)   "Scolari Engineering S.p.A." },
    {   EIP_VID(1014)   "Vialis Traffic bv" },
    {   EIP_VID(1015)   "Weidmueller Interface GmbH & Co. KG" },
    {   EIP_VID(1016)   "Shanghai Sibotech Automation Co. Ltd" },
    {   EIP_VID(1017)   "AEG Power Supply Systems GmbH" },
    {   EIP_VID(1018)   "Komatsu Electronics Inc." },
    {   EIP_VID(1019)   "Souriau" },
    {   EIP_VID(1020)   "Baumuller Chicago Corp." },
    {   EIP_VID(1021)   "J. Schmalz GmbH" },
    {   EIP_VID(1022)   "SEN Corporation" },
    {   EIP_VID(1023)   "Korenix Technology Co. Ltd" },
    {   EIP_VID(1024)   "Cooper Power Tools" },
    {   EIP_VID(1025)   "INNOBIS" },
    {   EIP_VID(1026)   "Shinho System" },
    {   EIP_VID(1027)   "Xm Services Ltd." },
    {   EIP_VID(1028)   "KVC Co., Ltd." },
    {   EIP_VID(1029)   "Sanyu Seiki Co., Ltd." },
    {   EIP_VID(1030)   "TuxPLC" },
    {   EIP_VID(1031)   "Northern Network Solutions" },
    {   EIP_VID(1032)   "Converteam GmbH" },
    {   EIP_VID(1033)   "Symbol Technologies" },
    {   EIP_VID(1034)   "S-TEAM Lab" },
    {   EIP_VID(1035)   "Maguire Products, Inc." },
    {   EIP_VID(1036)   "AC&T" },
    {   EIP_VID(1037)   "MITSUBISHI HEAVY INDUSTRIES, LTD. KOBE SHIPYARD & MACHINERY WORKS" },
    {   EIP_VID(1038)   "Hurletron Inc." },
    {   EIP_VID(1039)   "Chunichi Denshi Co., Ltd" },
    {   EIP_VID(1040)   "Cardinal Scale Mfg. Co." },
    {   EIP_VID(1041)   "BTR NETCOM via RIA Connect, Inc." },
    {   EIP_VID(1042)   "Base2" },
    {   EIP_VID(1043)   "ASRC Aerospace" },
    {   EIP_VID(1044)   "Beijing Stone Automation" },
    {   EIP_VID(1045)   "Changshu Switchgear Manufacture Ltd." },
    {   EIP_VID(1046)   "METRONIX Corp." },
    {   EIP_VID(1047)   "WIT" },
    {   EIP_VID(1048)   "ORMEC Systems Corp." },
    {   EIP_VID(1049)   "ASATech (China) Inc." },
    {   EIP_VID(1050)   "Controlled Systems Limited" },
    {   EIP_VID(1051)   "Mitsubishi Heavy Ind. Digital System Co., Ltd. (M.H.I.)" },
    {   EIP_VID(1052)   "Electrogrip" },
    {   EIP_VID(1053)   "TDS Automation" },
    {   EIP_VID(1054)   "T&C Power Conversion, Inc." },
    {   EIP_VID(1055)   "Robostar Co., Ltd" },
    {   EIP_VID(1056)   "Scancon A/S" },
    {   EIP_VID(1057)   "Haas Automation, Inc." },
    {   EIP_VID(1058)   "Eshed Technology" },
    {   EIP_VID(1059)   "Delta Electronic Inc." },
    {   EIP_VID(1060)   "Innovasic Semiconductor" },
    {   EIP_VID(1061)   "SoftDEL Systems Limited" },
    {   EIP_VID(1062)   "FiberFin, Inc." },
    {   EIP_VID(1063)   "Nicollet Technologies Corp." },
    {   EIP_VID(1064)   "B.F. Systems" },
    {   EIP_VID(1065)   "Empire Wire and Supply LLC" },
    {   EIP_VID(1066)   "Reserved" },
    {   EIP_VID(1067)   "Elmo Motion Control LTD" },
    {   EIP_VID(1068)   "Reserved" },
    {   EIP_VID(1069)   "Asahi Keiki Co., Ltd." },
    {   EIP_VID(1070)   "Joy Mining Machinery" },
    {   EIP_VID(1071)   "MPM Engineering Ltd" },
    {   EIP_VID(1072)   "Wolke Inks & Printers GmbH" },
    {   EIP_VID(1073)   "Mitsubishi Electric Engineering Co., Ltd." },
    {   EIP_VID(1074)   "COMET AG" },
    {   EIP_VID(1075)   "Real Time Objects & Systems, LLC" },
    {   EIP_VID(1076)   "MISCO Refractometer" },
    {   EIP_VID(1077)   "JT Engineering Inc." },
    {   EIP_VID(1078)   "Automated Packing Systems" },
    {   EIP_VID(1079)   "Niobrara R&D Corp." },
    {   EIP_VID(1080)   "Garmin Ltd." },
    {   EIP_VID(1081)   "Japan Mobile Platform Co., Ltd" },
    {   EIP_VID(1082)   "Advosol Inc." },
    {   EIP_VID(1083)   "ABB Global Services Limited" },
    {   EIP_VID(1084)   "Sciemetric Instruments Inc." },
    {   EIP_VID(1085)   "Tata Elxsi Ltd." },
    {   EIP_VID(1086)   "TPC Mechatronics, Co., Ltd." },
    {   EIP_VID(1087)   "Cooper Bussmann" },
    {   EIP_VID(1088)   "Trinite Automatisering B.V." },
    {   EIP_VID(1089)   "Peek Traffic B.V." },
    {   EIP_VID(1090)   "Acrison, Inc" },
    {   EIP_VID(1091)   "Applied Robotics, Inc." },
    {   EIP_VID(1092)   "FireBus Systems, Inc." },
    {   EIP_VID(1093)   "Beijing Sevenstar Huachuang Electronics" },
    {   EIP_VID(1094)   "Magnetek" },
    {   EIP_VID(1095)   "Microscan" },
    {   EIP_VID(1096)   "Air Water Inc." },
    {   EIP_VID(1097)   "Sensopart Industriesensorik GmbH" },
    {   EIP_VID(1098)   "Tiefenbach Control Systems GmbH" },
    {   EIP_VID(1099)   "INOXPA S.A" },
    {   EIP_VID(1100)   "Zurich University of Applied Sciences" },
    {   EIP_VID(1101)   "Ethernet Direct" },
    {   EIP_VID(1102)   "GSI-Micro-E Systems" },
    {   EIP_VID(1103)   "S-Net Automation Co., Ltd." },
    {   EIP_VID(1104)   "Power Electronics S.L." },
    {   EIP_VID(1105)   "Renesas Technology Corp." },
    {   EIP_VID(1106)   "NSWCCD-SSES" },
    {   EIP_VID(1107)   "Porter Engineering Ltd." },
    {   EIP_VID(1108)   "Meggitt Airdynamics, Inc." },
    {   EIP_VID(1109)   "Inductive Automation" },
    {   EIP_VID(1110)   "Neural ID" },
    {   EIP_VID(1111)   "EEPod LLC" },
    {   EIP_VID(1112)   "Hitachi Industrial Equipment Systems Co., Ltd." },
    {   EIP_VID(1113)   "Salem Automation" },
    {   EIP_VID(1114)   "port GmbH" },
    {   EIP_VID(1115)   "B & PLUS" },
    {   EIP_VID(1116)   "Graco Inc." },
    {   EIP_VID(1117)   "Altera Corporation" },
    {   EIP_VID(1118)   "Technology Brewing Corporation" },
    {   EIP_VID(1121)   "CSE Servelec" },
    {   EIP_VID(1124)   "Fluke Networks" },
    {   EIP_VID(1125)   "Tetra Pak Packaging Solutions SPA" },
    {   EIP_VID(1126)   "Racine Federated, Inc." },
    {   EIP_VID(1127)   "Pureron Japan Co., Ltd." },
    {   EIP_VID(1130)   "Brother Industries, Ltd." },
    {   EIP_VID(1132)   "Leroy Automation" },
    {   EIP_VID(1134)   "THK CO., LTD." },
    {   EIP_VID(1137)   "TR-Electronic GmbH" },
    {   EIP_VID(1138)   "ASCON S.p.A." },
    {   EIP_VID(1139)   "Toledo do Brasil Industria de Balancas Ltda." },
    {   EIP_VID(1140)   "Bucyrus DBT Europe GmbH" },
    {   EIP_VID(1141)   "Emerson Process Management Valve Automation" },
    {   EIP_VID(1142)   "Alstom Transport" },
    {   EIP_VID(1144)   "Matrox Electronic Systems" },
    {   EIP_VID(1145)   "Littelfuse" },
    {   EIP_VID(1146)   "PLASMART, Inc." },
    {   EIP_VID(1147)   "Miyachi Corporation" },
    {   EIP_VID(1150)   "Promess Incorporated" },
    {   EIP_VID(1151)   "COPA-DATA GmbH" },
    {   EIP_VID(1152)   "Precision Engine Controls Corporation" },
    {   EIP_VID(1153)   "Alga Automacao e controle LTDA" },
    {   EIP_VID(1154)   "U.I. Lapp GmbH" },
    {   EIP_VID(1155)   "ICES" },
    {   EIP_VID(1156)   "Philips Lighting bv" },
    {   EIP_VID(1157)   "Aseptomag AG" },
    {   EIP_VID(1158)   "ARC Informatique" },
    {   EIP_VID(1159)   "Hesmor GmbH" },
    {   EIP_VID(1160)   "Kobe Steel, Ltd." },
    {   EIP_VID(1161)   "FLIR Systems" },
    {   EIP_VID(1162)   "Simcon A/S" },
    {   EIP_VID(1163)   "COPALP" },
    {   EIP_VID(1164)   "Zypcom, Inc." },
    {   EIP_VID(1165)   "Swagelok" },
    {   EIP_VID(1166)   "Elspec" },
    {   EIP_VID(1167)   "ITT Water & Wastewater AB" },
    {   EIP_VID(1168)   "Kunbus GmbH Industrial Communication" },
    {   EIP_VID(1170)   "Performance Controls, Inc." },
    {   EIP_VID(1171)   "ACS Motion Control, Ltd." },
    {   EIP_VID(1173)   "IStar Technology Limited" },
    {   EIP_VID(1174)   "Alicat Scientific, Inc." },
    {   EIP_VID(1176)   "ADFweb.com SRL" },
    {   EIP_VID(1177)   "Tata Consultancy Services Limited" },
    {   EIP_VID(1178)   "CXR Ltd." },
    {   EIP_VID(1179)   "Vishay Nobel AB" },
    {   EIP_VID(1181)   "SolaHD" },
    {   EIP_VID(1182)   "Endress+Hauser" },
    {   EIP_VID(1183)   "Bartec GmbH" },
    {   EIP_VID(1185)   "AccuSentry, Inc." },
    {   EIP_VID(1186)   "Exlar Corporation" },
    {   EIP_VID(1187)   "ILS Technology" },
    {   EIP_VID(1188)   "Control Concepts Inc." },
    {   EIP_VID(1190)   "Procon Engineering Limited" },
    {   EIP_VID(1191)   "Hermary Opto Electronics Inc." },
    {   EIP_VID(1192)   "Q-Lambda" },
    {   EIP_VID(1194)   "VAMP Ltd" },
    {   EIP_VID(1195)   "FlexLink" },
    {   EIP_VID(1196)   "Office FA.com Co., Ltd." },
    {   EIP_VID(1197)   "SPMC (Changzhou) Co. Ltd." },
    {   EIP_VID(1198)   "Anton Paar GmbH" },
    {   EIP_VID(1199)   "Zhuzhou CSR Times Electric Co., Ltd." },
    {   EIP_VID(1200)   "DeStaCo" },
    {   EIP_VID(1201)   "Synrad, Inc" },
    {   EIP_VID(1202)   "Bonfiglioli Vectron GmbH" },
    {   EIP_VID(1203)   "Pivotal Systems" },
    {   EIP_VID(1204)   "TKSCT" },
    {   EIP_VID(1205)   "Randy Nuernberger" },
    {   EIP_VID(1206)   "CENTRALP" },
    {   EIP_VID(1207)   "Tengen Group" },
    {   EIP_VID(1208)   "OES, Inc." },
    {   EIP_VID(1209)   "Actel Corporation" },
    {   EIP_VID(1210)   "Monaghan Engineering, Inc." },
    {   EIP_VID(1211)   "wenglor sensoric gmbh" },
    {   EIP_VID(1212)   "HSA Systems" },
    {   EIP_VID(1213)   "MK Precision Co., Ltd." },
    {   EIP_VID(1214)   "Tappan Wire and Cable" },
    {   EIP_VID(1215)   "Heinzmann GmbH & Co. KG" },
    {   EIP_VID(1216)   "Process Automation International Ltd." },
    {   EIP_VID(1217)   "Secure Crossing" },
    {   EIP_VID(1218)   "SMA Railway Technology GmbH" },
    {   EIP_VID(1219)   "FMS Force Measuring Systems AG" },
    {   EIP_VID(1220)   "ABT Endustri Enerji Sistemleri Sanayi Tic. Ltd. Sti." },
    {   EIP_VID(1221)   "MagneMotion Inc." },
    {   EIP_VID(1222)   "STS Co., Ltd." },
    {   EIP_VID(1223)   "MERAK SIC, SA" },
    {   EIP_VID(1224)   "ABOUNDI, Inc." },
    {   EIP_VID(1225)   "Rosemount Inc." },
    {   EIP_VID(1226)   "GEA FES, Inc." },
    {   EIP_VID(1227)   "TMG Technologie und Engineering GmbH" },
    {   EIP_VID(1228)   "embeX GmbH" },
    {   EIP_VID(1229)   "GH Electrotermia, S.A." },
    {   EIP_VID(1230)   "Tolomatic" },
    {   EIP_VID(1231)   "Dukane" },
    {   EIP_VID(1232)   "Elco (Tian Jin) Electronics Co., Ltd." },
    {   EIP_VID(1233)   "Jacobs Automation" },
    {   EIP_VID(1234)   "Noda Radio Frequency Technologies Co., Ltd." },
    {   EIP_VID(1235)   "MSC Tuttlingen GmbH" },
    {   EIP_VID(1236)   "Hitachi Cable Manchester" },
    {   EIP_VID(1237)   "ACOREL SAS" },
    {   EIP_VID(1238)   "Global Engineering Solutions Co., Ltd." },
    {   EIP_VID(1239)   "ALTE Transportation, S.L." },
    {   EIP_VID(1240)   "Penko Engineering B.V." },

    // missing some here.

    {   EIP_VID(1251)   "Siemens" },
};

static const int16_t g_OpenerEthernetPort = 0xAF12;                             /** @brief Ethernet/IP standard port */

extern void EIPCalculateNextSeed( uint32_t *xor_shift_seed );
extern uint64_t EIPRandomGenerate( uint8_t *initFlag );
extern const char* EIP_CipVendorStr( int16_t aVendorId );

extern int8_t decodeListIdentityEIP( const char*msg, EIPListIdentity_t *listId );
extern int8_t decodeListInterfaceEIP( const char*msg, EIPListInterface_t *listId );
extern int8_t decodeListServicesEIP( const char*msg, EIPListServices_t *listId );
extern int8_t decodeMessageRouterResponsetEIP( const char*msg, EIPMessageRouterResponse_t *packet );
extern int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet );

extern EIPEncapsulationPacket_t encodeListIdentityEIP(const uint64_t context);
extern EIPEncapsulationPacket_t encodeListInterfaceEIP(const uint64_t context);
extern EIPEncapsulationPacket_t encodeListServicesEIP(const uint64_t context);
extern EIPCommonPacketFormatItem_t encodeCommonPacketFormatItemEIP( const EIPItemID_e Type, uint8_t *dataV);
extern EIPCommonPacketFormat_t encodeCommonPacketFormatEIP(const EIPCommonPacketFormatItem_t **items2Send );
extern EIPMessageRouterRequest_t encodeEIPMessageRouterRequestEIP(const uint8_t* path, const uint8_t* dataVals, const uint16_t service);
extern EIPregisterSessionSpecificData_t encodeRegisterSessionSpecificDataEIP( );
extern EIPEncapsulationPacket_t encodeRegisterSessionEIP(const uint64_t context);
extern EIPEncapsulationPacket_t encodeUnRegisterSessionEIP(const uint64_t context, const uint64_t sessHandle);
extern EIPEncapsulationPacket_t encodeInstructNOPcodeEIP(const int8_t *dataIn);
extern EIPSendDataSpecificData_t encodeSendDataSpecificDataEIP( const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
extern EIPEncapsulationPacket_t encodeNewSendRRDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
extern EIPEncapsulationPacket_t SendRRDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf );
extern EIPEncapsulationPacket_t encodeNewSendUnitDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
extern EIPEncapsulationPacket_t SendUnitDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf );
extern int8_t readYaskawaEIP_EPath( const char*msg, Yaskawa_EPath_t *epath );

#endif /* we use ethernet ip */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end lib */
