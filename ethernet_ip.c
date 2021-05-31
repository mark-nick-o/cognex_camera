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

int8_t decodeListIdentityEIP( const char*msg, EIPListIdentity_t *listId );
int8_t decodeListInterfaceEIP( const char*msg, EIPListInterface_t *listId );
int8_t decodeListServicesEIP( const char*msg, EIPListServices_t *listId );
int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet );
int8_t decodeMessageRouterResponsetEIP( const char*msg, EIPMessageRouterResponse_t *packet );
int8_t decodeCommonPacketFormatEIP( const char*msg, EIPCommonPacketFormat_t *packet );

EIPEncapsulationPacket_t encodeListIdentityEIP(const uint64_t context);
EIPEncapsulationPacket_t encodeListInterfaceEIP(const uint64_t context);
EIPEncapsulationPacket_t encodeListServicesEIP(const uint64_t context);
EIPCommonPacketFormatItem_t encodeCommonPacketFormatItemEIP( const EIPItemID_e Type, uint8_t *dataV);
EIPCommonPacketFormat_t encodeCommonPacketFormatEIP(const EIPCommonPacketFormatItem_t **content, const uint16_t itemCount);
EIPMessageRouterRequest_t encodeEIPMessageRouterRequestEIP(const uint8_t* path, const uint8_t* dataVals, const uint16_t service);
EIPregisterSessionSpecificData_t encodeRegisterSessionSpecificDataEIP( );
EIPEncapsulationPacket_t encodeRegisterSessionEIP(const uint64_t context);
EIPEncapsulationPacket_t encodeUnRegisterSessionEIP(const uint64_t context, const uint64_t sessHandle);
EIPEncapsulationPacket_t encodeInstructNOPcodeEIP(const int8_t *dataIn);

int8_t readYaskawaEIP_EPath( const char*msg, Yaskawa_EPath_t *epath );

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
 *  param : const EIPCommonPacketFormatItem_t **content, const uint16_t itemCount 
 *        
 *  return : EIPCommonPacketFormat_t*
 * -------------------------------------------------------------------------- */
EIPCommonPacketFormat_t encodeCommonPacketFormatEIP(const EIPCommonPacketFormatItem_t **content, const uint16_t itemCount) 
{
    EIPCommonPacketFormat_t encapsulationPacket;    
    encapsulationPacket.ItemCount = itemCount;
    memset((void*)&encapsulationPacket.Items[0u],0,sizeof(encapsulationPacket));
    memcpy((void*)&encapsulationPacket.Items[0u],(void*)&content[0u],(itemCount*sizeof(EIPCommonPacketFormatItem_t)));
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
