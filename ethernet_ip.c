/* Ethernet IP Example Allen Bradley PowerFlex 525 and Yasakawa MP3300IEC                                                        */
/* ref : Alexsey Timmin James Roth Miquel Valentine                                                                              */
/* https://github.com/nimbuscontrols/EIPScanner/blob/master/examples/vendors/yaskawa/mp3300iec/Yaskawa_AssemblyObjectExample.cpp */
/* https://github.com/loki-os/go-ethernet-ip/blob/master/encapsulation.go                                                        */
/* written by ACP Aviation                                                                                                       */

#include <stdint.h>
#include "definitions.h"
#if defined(ETH_IP_USED)
#include "cpu_endian_defs.h"
#include "ethernet_ip.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void EIPCalculateNextSeed( uint32_t *xor_shift_seed );
uint64_t EIPRandomGenerate( uint8_t *initFlag );
const char* EIP_CipVendorStr( int16_t aVendorId );                              /* vendor code extract when using cip */

int8_t decodeListIdentityEIP( const char*msg, EIPListIdentity_t *listId );
int8_t decodeListInterfaceEIP( const char*msg, EIPListInterface_t *listId );
int8_t decodeListServicesEIP( const char*msg, EIPListServices_t *listId );
int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet );
int8_t decodeMessageRouterResponsetEIP( const char*msg, EIPMessageRouterResponse_t *packet );
int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet );

EIPEncapsulationPacket_t encodeListIdentityEIP( const uint64_t context);
EIPEncapsulationPacket_t encodeListInterfaceEIP( const uint64_t context);
EIPEncapsulationPacket_t encodeListServicesEIP( const uint64_t context);
EIPCommonPacketFormatItem_t encodeCommonPacketFormatItemEIP( const EIPItemID_e Type, uint8_t *dataV);
EIPCommonPacketFormat_t encodeCommonPacketFormatEIP( const EIPCommonPacketFormatItem_t **items2Send );
EIPMessageRouterRequest_t encodeEIPMessageRouterRequestEIP( const uint8_t* path, const uint8_t* dataVals, const uint16_t service );
EIPregisterSessionSpecificData_t encodeRegisterSessionSpecificDataEIP( );
EIPEncapsulationPacket_t encodeRegisterSessionEIP( const uint64_t context );
EIPEncapsulationPacket_t encodeUnRegisterSessionEIP( const uint64_t context, const uint64_t sessHandle );
EIPEncapsulationPacket_t encodeInstructNOPcodeEIP( const int8_t *dataIn );
EIPSendDataSpecificData_t encodeSendDataSpecificDataEIP( const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
EIPEncapsulationPacket_t encodeNewSendRRDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
EIPEncapsulationPacket_t SendRRDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf );
EIPEncapsulationPacket_t encodeNewSendUnitDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send );
EIPEncapsulationPacket_t SendUnitDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf );

int8_t readYaskawaEIP_EPath( const char*msg, Yaskawa_EPath_t *epath );

/** 
 * https://github.com/liftoff-sr/CIPster/blob/master/source/src/utils/xorshiftrandom.cc
 * @brief Pseudo-random number algorithm
 * The algorithm used to create the pseudo-random numbers.
 * Works directly on the file global variable
 **/
/* ----------------------------------------------------------------------------
 *  EIPCalculateNextSeed : calculate the next seed
 *  param : uint32_t *xor_shift_seed
 *        
 *  return : void
 * -------------------------------------------------------------------------- */
void EIPCalculateNextSeed( uint32_t *xor_shift_seed ) 
{
  *xor_shift_seed ^= *xor_shift_seed << 13u;
  *xor_shift_seed ^= *xor_shift_seed >> 17u;
  *xor_shift_seed ^= *xor_shift_seed << 5u;
}

/* ----------------------------------------------------------------------------
 *  EIPRandomGenerate : generate random number 64 bits long
 *  param : uint32_t *xor_shift_seed
 *        
 *  return : void
 * -------------------------------------------------------------------------- */
uint64_t EIPRandomGenerate( uint8_t *initFlag ) 
{
  uint16_t i1;
  uint16_t i2;
  uint16_t i3;
  uint16_t i4;
  uint32_t i5;
  uint32_t i6;
  if (*initFlag == 0)
  {
     srand(((uint16_t)CP0_GET(CP0_COUNT)&0xFFFFu));
     *initFlag = 1;
  }
  i1 = rand();
  i2 = rand();
  i3 = rand();
  i4 = rand();
  i5 = i1 | (((uint32_t)i2) << 16u);
  i6 = i3 | (((uint32_t)i4) << 16u);  
  EIPCalculateNextSeed( &i5 );
  EIPCalculateNextSeed( &i6 ); 
  return (((uint64_t)i5) | (((uint64_t)i6) << 32u)); 
}

/* ----------------------------------------------------------------------------
 *  EIP_CipVendorStr : get a description for the vendor as a string
 *  param : int16_t aVendorId
 *        
 *  return : const char*
 * -------------------------------------------------------------------------- */
const char* EIP_CipVendorStr( int16_t aVendorId )
{
    int16_t i;

    for( i = 0; i < EIP_VENDOR_COUNT; ++i )
    {
        if( gEIP_vendors[i].id == aVendorId )
            return gEIP_vendors[i].name;
    }
}

/* ----------------------------------------------------------------------------
 *  decodeListIdentityEIP : decode list Id message
 *  param : const char*msg, EIPListIdentity_t *listId
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */
int8_t decodeListIdentityEIP( const char*msg, EIPListIdentity_t *listId )
{
    int8_t retn = 1;

    if ((msg == NULL) || (listId == NULL))        
    {
            retn = -1;
    }
    else
    {
        if (sizeof(msg) < sizeof(EIPListIdentity_t))
        {
            retn = -1;
        }
        else
        {
            memcpy((void*) listId,(void*) msg, sizeof(EIPListIdentity_t));
#if defined(ETHIP_HOST_IS_BIG_ENDIAN)
            listId->Item.SinFamily = SWAPINT16(listId->Item.SinFamily);
            listId->Item.SinPort = SWAPINT16(listId->Item.SinPort);
            listId->Item.SinAddr = SWAPINT32(listId->Item.SinAddr);
            listId->Item.SinZero = SWAPINT64(listId->Item.SinZero);
        }
#endif           
     }        
     return retn;
}

/* ----------------------------------------------------------------------------
 *  decodeListInterfaceEIP : decode list interface message
 *  param : const char*msg, EIPListInterface_t *listId 
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */
int8_t decodeListInterfaceEIP( const char*msg, EIPListInterface_t *listId )
{
    int8_t retn = 1;

    if ((msg == NULL) || (listId == NULL))        
    {
            retn = -1;
    }
    else
    {
        if (sizeof(msg) < sizeof(EIPListInterface_t))
        {
            retn = -1;
        }
        else
        {
           memcpy((void*) listId,(void*) msg, sizeof(EIPListInterface_t));  
        } 
    }        
    return retn;
}

/* ----------------------------------------------------------------------------
 *  decodeListServicesEIP : decode list services message
 *  param : const char*msg, EIPListServices_t *listId 
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */
int8_t decodeListServicesEIP( const char*msg, EIPListServices_t *listId )
{
    int8_t retn = 1;

    if ((msg == NULL) || (listId == NULL))        
    {
            retn = -1;
    }
    else
    {
        if (sizeof(msg) < sizeof(EIPListServices_t))
        {
            retn = -1;
        }
        else
        {
           memcpy((void*) listId,(void*) msg, sizeof(EIPListServices_t)); 
        }  
    }        
    return retn;
}

/* ----------------------------------------------------------------------------
 *  decodeCommonPacketFormatEIP : decode common packet format message
 *  param : const char*msg, EIPCommonPacketFormat_t *listId 
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */
int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet )
{
    int8_t retn = 1;

    if ((msg == NULL) || (packet == NULL))        
    {
        retn = -1;
    }
    else
    {
        if (sizeof(msg) < sizeof(EIPCommonPacketFormat_t))
        {
            retn = -1;
        }
        else
        {
           memcpy((void*) packet,(void*) msg, sizeof(EIPCommonPacketFormat_t));   
        }
    }        
    return retn;
}
/* ----------------------------------------------------------------------------
 *  decodeMessageRouterResponseEIP : decode Message Router Response message
 *  param : const char*msg, EIPMessageRouterResponse_t *packet 
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */
int8_t decodeMessageRouterResponsetEIP( const char*msg, EIPMessageRouterResponse_t *packet )
{
    int8_t retn = 1;

    if ((msg == NULL) || (packet == NULL))        
    {
        retn = -1;
    }
    else
    {
        if (sizeof(msg) < sizeof(EIPMessageRouterResponse_t))
        {
            retn = -1;
        }
        else
        {
           memcpy((void*) packet,(void*) msg, sizeof(EIPMessageRouterResponse_t));   
        }
    }        
    return retn;
}
/* ----------------------------------------------------------------------------
 *  encodeListIdentityEIP : encode list identity message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeListIdentityEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListIdentity;
    encapsulationPacket.pHeader.SenderContext = context;
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeListInterfaceEIP : encode list interface message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeListInterfaceEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListInterfaces;
    encapsulationPacket.pHeader.SenderContext = context;
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeListServicesEIP : encode list identity message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeListServicesEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListServices;
    encapsulationPacket.pHeader.SenderContext = context;
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeCommonPacketFormatEIP : encode Common Packet Format message for EIP
 *  param : const EIPItemID_e Type, uint8_t *dataV 
 *        
 *  return : EIPCommonPacketFormatItem_t*
 * -------------------------------------------------------------------------- */
EIPCommonPacketFormatItem_t encodeCommonPacketFormatItemEIP( const EIPItemID_e Type, uint8_t *dataV) 
{
    EIPCommonPacketFormatItem_t encapsulationPacket;    
    encapsulationPacket.TypeID = Type;
    encapsulationPacket.Length = strlen(dataV);
    memcpy((void*)&encapsulationPacket.DataV,(void*)dataV,strlen(dataV));        
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeCommonPacketFormatEIP : encode Common Packet Format message for EIP
 *  param : const EIPCommonPacketFormatItem_t **content  
 *        
 *  return : EIPCommonPacketFormat_t*
 * -------------------------------------------------------------------------- */
EIPCommonPacketFormat_t encodeCommonPacketFormatEIP(const EIPCommonPacketFormatItem_t **items2Send ) 
{
    EIPCommonPacketFormat_t encapsulationPacket;    
    int16_t itemNo;
    encapsulationPacket.ItemCount = ((int16_t)sizeof(items2Send)/sizeof(EIPCommonPacketFormatItem_t));
    for( itemNo = 0; itemNo < encapsulationPacket.ItemCount; ++itemNo )
    {
         memset((void*)&encapsulationPacket.Items[itemNo],0,sizeof(EIPCommonPacketFormatItem_t));
         memcpy((void*)&encapsulationPacket.Items[itemNo],(void*)&items2Send[itemNo],sizeof(EIPCommonPacketFormatItem_t));
    }    
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeEIPMessageRouterRequestEIP : encode Message Router Request for EIP
 *  param : const uint8_t* path, const uint8_t* dataVals, const uint16_t service
 *        
 *  return : EIPMessageRouterRequest_t*
 * -------------------------------------------------------------------------- */
EIPMessageRouterRequest_t encodeEIPMessageRouterRequestEIP(const uint8_t* path, const uint8_t* dataVals, const uint16_t service) 
{
    EIPMessageRouterRequest_t encapsulationPacket;    
    encapsulationPacket.Service = service;
    encapsulationPacket.RequestPathSize = (strlen((char*)path)/2u);
    memcpy((void*)&encapsulationPacket.RequestPath,(void*)path,strlen((char*)path));
    memcpy((void*)&encapsulationPacket.RequestData,(void*)dataVals,strlen((char*)dataVals));
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeRegisterSessionSpecificDataEIP : encode Common Packet Format message for EIP
 *  param : const EIPItemID_e Type, uint8_t *dataV 
 *        
 *  return : EIPCommonPacketFormatItem_t
 * -------------------------------------------------------------------------- */
EIPregisterSessionSpecificData_t encodeRegisterSessionSpecificDataEIP( ) 
{
    EIPregisterSessionSpecificData_t encapsulationPacket;    
    encapsulationPacket.ProtocolVersion = 1;
    encapsulationPacket.OptionsFlags = 0;        
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeRegisterSessionEIP : encode message to register a session
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeRegisterSessionEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    EIPregisterSessionSpecificData_t cmdData;        
    encapsulationPacket.pHeader.EIPCommand = EIPCommandRegisterSession;
    encapsulationPacket.pHeader.Length = 4u;
    encapsulationPacket.pHeader.SenderContext = context;
    cmdData = encodeRegisterSessionSpecificDataEIP( );
    memcpy((void*)&encapsulationPacket.CommandSpecificData,(void*)&cmdData,sizeof(cmdData)); 
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeUnRegisterSessionSpecificDataEIP : encode list interface message
 *  param : const uint64_t context, const uint64_t sessHandle
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeUnRegisterSessionEIP(const uint64_t context, const uint64_t sessHandle) 
{
    EIPEncapsulationPacket_t encapsulationPacket;          
    encapsulationPacket.pHeader.EIPCommand = EIPCommandUnRegisterSession;
    encapsulationPacket.pHeader.Length = 4u;
    encapsulationPacket.pHeader.SenderContext = context;
    encapsulationPacket.pHeader.SessionHandle = sessHandle; 
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeInstructNOPcodeEIP : encode nop code message
 *  param : const int8_t *dataIn 
 *        
 *  return : EIPEncapsulationPacket_t
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeInstructNOPcodeEIP(const int8_t *dataIn) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    encapsulationPacket.pHeader.EIPCommand = EIPCommandNOP;
    encapsulationPacket.pHeader.Length = 4u;
    encapsulationPacket.pHeader.SenderContext = 0;
    memcpy((void*)&encapsulationPacket.CommandSpecificData,(void*)dataIn,sizeof(dataIn)); 
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeSendDataSpecificDataEIP : encode message Send DataS pecific Data
 *  param : const uint64_t context 
 *        
 *  return : EIPSendDataSpecificData_t
 * -------------------------------------------------------------------------- */
EIPSendDataSpecificData_t encodeSendDataSpecificDataEIP( const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send ) 
{
    EIPSendDataSpecificData_t encapsulationPacket; 
    EIPCommonPacketFormat_t cmdData; 	
    encapsulationPacket.InterfaceHandle = 0;
    encapsulationPacket.TimeOut= tim; 
    cmdData = encodeCommonPacketFormatEIP( items2Send );	
    memcpy((void*)&encapsulationPacket.Packet[0u],(void*)&cmdData,sizeof(cmdData));    	
    return encapsulationPacket;
}


/* ----------------------------------------------------------------------------
 *  encodeNewSendRRDataEIP : encode message RR data
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeNewSendRRDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send ) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    EIPSendDataSpecificData_t cmdData;        
    encapsulationPacket.pHeader.EIPCommand = EIPCommandSendRRData;
    encapsulationPacket.pHeader.Length = 4u;
    encapsulationPacket.pHeader.SenderContext = context;
    encapsulationPacket.pHeader.SessionHandle = sessHandle; 
    cmdData = encodeSendDataSpecificDataEIP( tim, items2Send ); 
    memcpy((void*)&encapsulationPacket.CommandSpecificData,(void*)&cmdData,sizeof(cmdData)); 
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  SendRRDataEIP : encode message RR data
 *  param : uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, 
 *          const EIPCommonPacketFormatItem_t **cpf
 * 
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t SendRRDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf ) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    uint64_t ctx = EIPRandomGenerate( initSeed );

    encapsulationPacket = encodeNewSendRRDataEIP(sessHandle, ctx, timeout, cpf );
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeNewSendUnitDataEIP : encode message Unit data
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t encodeNewSendUnitDataEIP( const uint64_t sessHandle, const uint64_t context, const uint16_t tim, const EIPCommonPacketFormatItem_t **items2Send ) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    EIPSendDataSpecificData_t cmdData;        
    encapsulationPacket.pHeader.EIPCommand = EIPCommandSendUnitData;
    encapsulationPacket.pHeader.Length = 4u;
    encapsulationPacket.pHeader.SenderContext = context;
    encapsulationPacket.pHeader.SessionHandle = sessHandle; 
    cmdData = encodeSendDataSpecificDataEIP( tim, items2Send ); 
    memcpy((void*)&encapsulationPacket.CommandSpecificData,(void*)&cmdData,sizeof(cmdData)); 
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  SendUnitDataEIP : encode message RR data
 *  param : uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, 
 *          const EIPCommonPacketFormatItem_t **cpf
 * 
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t SendUnitDataEIP( uint8_t *initSeed, const uint64_t sessHandle, const uint16_t timeout, const EIPCommonPacketFormatItem_t **cpf ) 
{
    EIPEncapsulationPacket_t encapsulationPacket;  
    uint64_t ctx = EIPRandomGenerate( initSeed );

    encapsulationPacket = encodeNewSendUnitDataEIP(sessHandle, ctx, timeout, cpf );
    return encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  readYaskawaEIP_EPath : Yasakawa path message
 *  param : const char*msg, Yaskawa_EPath_t *epath 
 *        
 *  return : int8_t
 * -------------------------------------------------------------------------- */        
int8_t readYaskawaEIP_EPath( const char*msg, Yaskawa_EPath_t *epath )
{
    EIP_Yasakawa_EPathSegmentTypes_CipUsint_e segmentType;
    uint8_t bytId = 0u;
    int8_t retn = 1;

    if (((msg == NULL) || (sizeof(msg) < sizeof(Yaskawa_EPath_t))) || (epath == NULL))        
    {
            retn = -1;
    }
    else
    {
            while (bytId < sizeof(msg)) 
            {
               segmentType = msg[bytId]; 
               switch (segmentType) 
               {
                      case EIP_CLASS_8_BITS:
                      epath->classId.uint8_Eip = msg[bytId+1u];
                      bytId += 2u;
                      break;
                
                      case EIP_CLASS_16_BITS:
                      epath->classId.uint16_Eip = msg[bytId+1u] | (msg[bytId+2u] << 8u);
                      bytId += 3u;
                      break;
                
                      case EIP_INSTANCE_8_BITS:
                      epath->objectId.uint8_Eip = msg[bytId+1u];
                      bytId += 2u;
                      break;

                      case EIP_INSTANCE_16_BITS:
                      epath->objectId.uint16_Eip = msg[bytId+1u] | (msg[bytId+2u] << 8u);
                      bytId += 3u;
                      break;
                  
                      case EIP_ATTRIBUTE_8_BITS:
                      epath->attributeId.uint8_Eip = msg[bytId+1u];
                      bytId += 2u;
                      break;
                  
                      case EIP_ATTRIBUTE_16_BITS:
                      epath->attributeId.uint16_Eip = msg[bytId+1u] | (msg[bytId+2u] << 8u);
                      bytId += 3u;
                      break;
                  
                      default:
                      retn = -1;
                      bytId = sizeof(msg);
                      break;
                   }
             }
        }
        return retn;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end we use ethernat ip */
