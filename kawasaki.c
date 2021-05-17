#include "definitions.h"
#include "gc_events.h"
#include "kawasaki.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* =============================================================================

   Written from python
   https://github.com/ethz-asl/kawasaki/tree/master/kawasaki_driver/src/kawasaki_driver
   by ACP Aviation
   
============================================================================= */

uint8_t kawasakiGetJoint(kawasaki_robot_t *rob);
uint8_t kawasakiGetPose(kawasaki_robot_t *rob);
uint8_t kawasakiParseState(const char* msg, kawasaki_robot_t *rob);
void kawasakiRcvSendmsg( const char * rcv, char * send, kawasaki_robot_t *rob );

/* ----------------------------------------------------------------------------
 *  kawasakiGetJoint : get joint info
 *  param : kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiGetJoint(kawasaki_robot_t *rob)
{
    char * spaceDelimField = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found 
    
    spaceDelimField = strtok(&rob->joint_states.string," ");                    // split it by space
    while (spaceDelimField != NULL)
    {
       itemNum = ++itemNum % UINT8_MAX;
       switch(itemNum)
       {
           case 1u:
           rob->joint_states.position.x = atof(spaceDelimField)/1000.0f;
           break;

           case 2u:
           rob->joint_states.position.y = atof(spaceDelimField)/1000.0f;
           break;
		   
           case 3u:
           rob->joint_states.position.z = atof(spaceDelimField)/1000.0f;
           ret = 1U;
           break;
		   
           default:
           break;                                                    
       }
       spaceDelimField = strtok(NULL, " ");                                     /* get the next string in the line */                             
    }
    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiGetPose : get pose info
 *  param : kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiGetPose(kawasaki_robot_t *rob)
{
    char * spaceDelimField = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found 
    
    spaceDelimField = strtok(&rob->pose_states.string," ");                     // split it by space
    while (spaceDelimField != NULL)
    {
       itemNum = ++itemNum % UINT8_MAX;
       switch(itemNum)
       {
           case 1u:
           rob->pose_states.position.x = atof(spaceDelimField)/1000.0f;
           break;

           case 2u:
           rob->pose_states.position.y = atof(spaceDelimField)/1000.0f;
           break;
		   
           case 3u:
           rob->pose_states.position.z = atof(spaceDelimField)/1000.0f;
           break;

           case 4u:
           rob->pose_states.orientation_deg.x = atof(spaceDelimField);
           rob->pose_states.orientation_rad.x = DEGREE_TO_RADIAN(rob->pose_states.orientation_deg.x);
           break;
		   
           case 5u:
           rob->pose_states.orientation_deg.y = atof(spaceDelimField);
           rob->pose_states.orientation_rad.y = DEGREE_TO_RADIAN(rob->pose_states.orientation_deg.y);
	   break;

           case 6u:
           rob->pose_states.orientation_deg.z = atof(spaceDelimField);
           rob->pose_states.orientation_rad.z = DEGREE_TO_RADIAN(rob->pose_states.orientation_deg.z);		   
           if (Quaternion_from_euler(rob->pose_states.orientation_rad.x, rob->pose_states.orientation_rad.y, rob->pose_states.orientation_rad.z, &rob->pose_states.orientationquat)==1)
           {
               ret = 1U;
           }
           break;
		   
           default:
           break;                                                    
       }
       spaceDelimField = strtok(NULL, " ");                                     /* get the next string in the line */                             
    }
    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiParseState : parse state info message
 *  param : char* msg, kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiParseState(const char* msg, kawasaki_robot_t *rob)
{
    char * pch = NULL;
    char * spaceDelimField = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found 
    
    pch = strtok((char*)msg,"\r\n");                                            // split it by delimeter
    while (pch != NULL)
    {
       itemNum = ++itemNum % UINT8_MAX;
       switch(itemNum)
       {
           case KAWA_STATE_MSG_JOINT_VALUES_INDEX:
           strncpy(rob->joint_states.string,pch,KAWA_MAX_JOINT_STATE_REPLY);
           break;

           case KAWA_STATE_MSG_POSE_VALUES_INDEX:
           strncpy(rob->pose_states.string,pch,KAWA_MAX_POSE_STATE_REPLY);
	   ret = 2U;
           break;
		   
           default:
           break;                                                    
       }
       pch = strtok(NULL, "\r\n");                                              /* get the next string in the line */                             
    }
    if ((ret == 2U) && (kawasakiGetJoint(rob) == 1U))
    {
       ret = kawasakiGetPose(rob);
    }
    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiRcvSendmsg : parse state info message
 *  param : const char * rcv, char * send, kawasaki_robot_t *rob
 *        
 *  return : void
 * -------------------------------------------------------------------------- */
void kawasakiRcvSendmsg( const char * rcv, char * send, kawasaki_robot_t *rob )
{
	char stringTemp[KAWA_START_MSG_LEN];
        char buf[KAWA_START_MSG_LEN];
	
	switch(rob->state)
	{
         case 0u:
         break;

         case KAWA_RCV_START:
         KAWA_START_MSG(&buf);
         if (strncmp((char*)rcv,&buf,strlen(&buf))==0)
         {
            rob->state = KAWA_SND_LOGIN;
         }
         break;

         case KAWA_SND_LOGIN:
         strcpy(send,KAWA_LOGIN_USER);
         rob->state = KAWA_RCV_LOGIN;
         break;
		 
         case KAWA_RCV_LOGIN:
         KAWA_LOGIN_REPLY(&stringTemp,rob->socket_number);
         if (strncmp((char*)rcv,&stringTemp,strlen(&stringTemp))==0)
         {
            rob->state = KAWA_SND_GETSTATE;
         }
         break;		

         case KAWA_SND_GETSTATE:
         strcpy(send,KAWA_GET_STATE);
         rob->state = KAWA_RCV_GETSTATE;
         break;	

         case KAWA_RCV_GETSTATE:
         if (strncmp((char*)rcv,KAWA_STATE_STRING_PARTIAL,KAWA_STATE_STRING_PARTIAL_LEN)==0)
         {
            rob->state = KAWA_RCV_POSE;
         }
         break;

         case KAWA_RCV_POSE:
         if (kawasakiParseState(rcv, rob) == 1)
         {
			 
         }
 		 
    }
	
}
