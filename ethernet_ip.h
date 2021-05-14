#ifndef __ethnetIP_
#define __ethnetIP_
/* Ethernet IP Example Allen Bradley PowerFlex 525 and Yasakawa MP3300IEC                                                        */
/* ref : Alexsey Timmin James Roth Miquel Valentine                                                                              */
/* https://github.com/nimbuscontrols/EIPScanner/blob/master/examples/vendors/yaskawa/mp3300iec/Yaskawa_AssemblyObjectExample.cpp */
/* https://github.com/loki-os/go-ethernet-ip/blob/master/encapsulation.go                                                        */
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
  #define EIPPACKED __attribute__((packed))                                 /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
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

typedef	enum {
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

#define ETH_IP_MAX_CMD_LEN 65511u
#define ETH_IP_MAX_PRODNM_LEN 32u
#define ETH_IP_MAX_ITEMDTA_LEN 32u
#define ETH_IP_MAX_LSTSRVC_LEN 16u

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
	uint8_t CommandSpecificData[ETH_IP_MAX_CMD_LEN]; 
} EIPEncapsulationPacket_t;
#else
EIPPACKED(
typedef struct
{
	EIPEncapsulationHeader_t pHeader;
	uint8_t CommandSpecificData[ETH_IP_MAX_CMD_LEN]; 
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
	unsigned char ProductName[ETH_IP_MAX_PRODNM_LEN];
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
	unsigned char ProductName[ETH_IP_MAX_PRODNM_LEN];
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
	unsigned char ProductName[ETH_IP_MAX_PRODNM_LEN];
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
	unsigned char ProductName[ETH_IP_MAX_PRODNM_LEN];
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
	uint8_t ItemData[ETH_IP_MAX_ITEMDTA_LEN];
} EIPListInterfaceItem_t;
#else
EIPPACKED(
typedef struct
{
	uint16_t ItemTypeCode;
	uint16_t ItemLength;
	uint8_t ItemData[ETH_IP_MAX_ITEMDTA_LEN];
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
	uint8_t Name[ETH_IP_MAX_LSTSRVC_LEN];
} EIPListServicesItem_t;
#else
EIPPACKED(
typedef struct
{
	uint16_t ItemTypeCode;
	uint16_t ItemLength;
	uint16_t Version;
	uint16_t Flags;
	uint8_t Name[ETH_IP_MAX_LSTSRVC_LEN];
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

typedef	enum {
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

extern int8_t decodeListIdentityEIP( const char*msg, EIPListIdentity_t *listId );
extern int8_t decodeListInterfaceEIP( const char*msg, EIPListInterface_t *listId );
extern int8_t decodeListServicesEIP( const char*msg, EIPListServices_t *listId );
extern EIPEncapsulationPacket_t* encodeListIdentityEIP(const uint64_t context);
extern EIPEncapsulationPacket_t* encodeListInterfaceEIP(const uint64_t context);
extern EIPEncapsulationPacket_t* encodeListServicesEIP(const uint64_t context);
extern int8_t readYaskawaEIP_EPath( const char*msg, Yaskawa_EPath_t *epath );

#endif /* we use ethernet ip */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end lib */
