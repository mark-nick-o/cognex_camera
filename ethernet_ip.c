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
EIPEncapsulationPacket_t* encodeListIdentityEIP(const uint64_t context);
EIPEncapsulationPacket_t* encodeListInterfaceEIP(const uint64_t context);
EIPEncapsulationPacket_t* encodeListServicesEIP(const uint64_t context);
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

    if (((msg == NULL) || (sizeof(msg) < sizeof(EIPListIdentity_t))) || (listId == NULL))	
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

    if (((msg == NULL) || (sizeof(msg) < sizeof(EIPListInterface_t))) || (listId == NULL))	
    {
	    retn = -1;
    }
    else
    {
	   memcpy((void*) listId,(void*) msg, sizeof(EIPListInterface_t));   
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

    if (((msg == NULL) || (sizeof(msg) < sizeof(EIPListServices_t))) || (listId == NULL))	
    {
	    retn = -1;
    }
    else
    {
	   memcpy((void*) listId,(void*) msg, sizeof(EIPListServices_t));   
    }	
    return retn;
}

/* ----------------------------------------------------------------------------
 *  encodeListIdentityEIP : encode list identity message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t* encodeListIdentityEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListIdentity;
    encapsulationPacket.pHeader.SenderContext = context;
    return &encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeListInterfaceEIP : encode list interface message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t* encodeListInterfaceEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListInterfaces;
    encapsulationPacket.pHeader.SenderContext = context;
    return &encapsulationPacket;
}

/* ----------------------------------------------------------------------------
 *  encodeListServicesEIP : encode list identity message
 *  param : const uint64_t context 
 *        
 *  return : EIPEncapsulationPacket_t*
 * -------------------------------------------------------------------------- */
EIPEncapsulationPacket_t* encodeListServicesEIP(const uint64_t context) 
{
    EIPEncapsulationPacket_t encapsulationPacket;    
    encapsulationPacket.pHeader.EIPCommand = EIPCommandListServices;
    encapsulationPacket.pHeader.SenderContext = context;
    return &encapsulationPacket;
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
