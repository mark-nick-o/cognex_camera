#include <stdint.h>
#include "Struts.h"
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
uint8_t kawasakiSetPose( kawasaki_robot_t *rob, const dVectr position, const dquat quaternion, char * msg );
uint8_t kawasakiSetPose2( kawasaki_robot_t *rob, const dVectr position, const dquat quaternion, char * msg );
uint8_t kawasakiParseSetFeedback( char* msg, kawasaki_robot_t *rob );
void kawasakiRcvSendmsg( const char * rcv, char * send, kawasaki_robot_t *rob, const dVectr posit, const dquat quat );

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

#ifdef out4now
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
         KAWA_LOGIN_REPLY(&stringTemp,rob->snd_socket_number);
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
#endif
/* ----------------------------------------------------------------------------
 *  kawasakiSetPose : set pose info
 *  param : kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiSetPose( kawasaki_robot_t *rob, const dVectr position, const dquat quaternion, char * msg )
{
    uint8_t ret = 0U;                                                           // number of strings found 

    if ((msg == NULL) || (sizeof(msg) < KAWA_SET_POSE_MSG_SIZE)) return ret;        
        
    rob->pose_states.position.x = (position.x*1000.0f);
    rob->pose_states.position.y = (position.y*1000.0f);
    rob->pose_states.position.z = (position.z*1000.0f);
    if (Quaternion_to_euler( &rob->pose_states.orientation_rad.x, &rob->pose_states.orientation_rad.y, &rob->pose_states.orientation_rad.z, quaternion )==1u)
    {
       rob->pose_states.orientation_deg.x = RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.x); 
       rob->pose_states.orientation_deg.y = RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.y); 
       rob->pose_states.orientation_deg.z = RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.z);            
    } 
    KAWA_SET_POSE_SEND(msg,rob);
    ret = 1U;
            
    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiSetPose2 : set pose info (uses roundup macro 3.3f seems to round up so need)
 *  param : kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiSetPose2( kawasaki_robot_t *rob, const dVectr position, const dquat quaternion, char * msg )
{
    uint8_t ret = 0U;                                                           // return code 

    if ((msg == NULL) || (sizeof(msg) < KAWA_SET_POSE_MSG_SIZE)) return ret;        
        
    rob->pose_states.position.x = ROUND((position.x*1000.0f),3.0f);
    rob->pose_states.position.y = ROUND((position.y*1000.0f),3.0f);
    rob->pose_states.position.z = ROUND((position.z*1000.0f),3.0f);
    if (Quaternion_to_euler( &rob->pose_states.orientation_rad.x, &rob->pose_states.orientation_rad.y, &rob->pose_states.orientation_rad.z, quaternion )==1u)
    {
       rob->pose_states.orientation_deg.x = ROUND((RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.x)),3.0f); 
       rob->pose_states.orientation_deg.y = ROUND((RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.y)),3.0f); 
       rob->pose_states.orientation_deg.z = ROUND((RADIAN_TO_DEGREE(rob->pose_states.orientation_rad.z)),3.0f);            
    } 
    KAWA_SET_POSE_SEND(msg,rob);
    ret = 1u;
            
    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiParseSetFeedback : parse the response from a set position command
 *  param : char* msg, kawasaki_robot_t *rob
 *        
 *  return : uint8_t 1=success
 * -------------------------------------------------------------------------- */
uint8_t kawasakiParseSetFeedback(char* msg, kawasaki_robot_t *rob)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found 
    
    pch = strtok(msg,"\r\n");                                                   // split it by commas
    while (pch != NULL)
    {
       itemNum = ++itemNum % UINT8_MAX;
       switch(itemNum)
       {
           case 1u:
           strncpy(rob->feedbackCmd,pch,strlen(pch));
           strcat(rob->feedbackCmd,"b\n");
           ret = 1U;
           break;

           case KAWA_STATE_MSG_POSE_VALUES_INDEX:
           strncpy(rob->feedbackError,pch,strlen(pch));
           ret = 2U;
           break;
                   
           default:
           break;                                                    
       }
       pch = strtok(NULL, "\r\n");                                              /* get the next string in the line */                             
    }

    return ret;
}

/* ----------------------------------------------------------------------------
 *  kawasakiRcvSendmsg : parse state info message and compose responses
 *                       control of request states done on top level by calling logic
 *                       send / recieve / socket OPEN has been left for caller 
 *                       as machine specific
 *
 *  param : const char * rcv, char * send, kawasaki_robot_t *rob
 *        
 *  return : void
 * -------------------------------------------------------------------------- */
void kawasakiRcvSendmsg( const char * rcv, char * send, kawasaki_robot_t *rob, const dVectr posit, const dquat quat )
{
        char* stringTemp;
        char buf[KAWA_START_MSG_LEN];
        uint8_t ans = 0u;
        
        switch(rob->state)
        {
           case KAWA_IDLE:
           if (rob->socketState == KAWA_SOCKET_CLOSED)
           {
              rob->state = KAWA_OPEN_SOCKET;           
           }
           break;

           case KAWA_OPEN_SOCKET:                                               /*  Open two socket connections and login in as "as". The first socket is for sending commands and the second is for receiving. */
           if (rob->socketState == KAWA_SOCKET_OPEN_SUCESS)
           {
              rob->state = KAWA_SOCKET_LARGE_WAIT;
           }
           break;

           case KAWA_SOCKET_LARGE_WAIT:                                         /* to do */
           rob->state = KAWA_RCV_START;
           break;
                 
           case KAWA_RCV_START:
           KAWA_START_MSG(&buf);
           if (strncmp((char*)rcv,&buf,strlen(&buf))==0)
           {
              rob->state = KAWA_SND_LOGIN;
           }
           break;

           case KAWA_SND_LOGIN:
           stringTemp = strncpy(send,KAWA_LOGIN_USER,sizeof(send));
           rob->state = KAWA_TIMEOUT_LARGE_WAIT;
           break;

           case KAWA_TIMEOUT_LARGE_WAIT:                                        /* to do */
           rob->state = KAWA_RCV_LOGIN;
           break;
                 
           case KAWA_RCV_LOGIN:
           KAWA_LOGIN_REPLY(stringTemp,rob->snd_socket_number);
           if (strncmp((char*)rcv,stringTemp,strlen(stringTemp))==0)
           {
              rob->state = KAWA_LOGIN_MEDIUM_WAIT;
           }
           break;                

           case KAWA_LOGIN_MEDIUM_WAIT:                                         /* to do */
           rob->state = KAWA_SND_GETSTATE;
           break;
                 
           case KAWA_SND_GETSTATE:
           stringTemp = strncpy(send,KAWA_GET_STATE,sizeof(send));
           rob->state = KAWA_GETSTATE_MEDIUM_WAIT;
           break;        

           case KAWA_GETSTATE_MEDIUM_WAIT:                                      /* to do */
           rob->state = KAWA_SND_GETSTATE;
           break;
                 
           case KAWA_RCV_GETSTATE:
           if (strncmp((char*)rcv,KAWA_STATE_STRING_PARTIAL,KAWA_STATE_STRING_PARTIAL_LEN)==0)
           {
              rob->state = KAWA_RCV_POSE;
           }
           break;

           case KAWA_RCV_POSE:
           if (kawasakiParseState(rcv, rob) == 1u)
           {
              rob->state = KAWA_IDLE;                         
           }
           break;

           case KAWA_SND_POSE:
           if (kawasakiSetPose(rob,posit,quat,send) == 1u)
           {
              rob->state = KAWA_TIMEOUT_MEDIUM_WAIT;                         
           }
           break;         
                 
           case KAWA_TIMEOUT_MEDIUM_WAIT:                                       /* to do */
           strncpy((char*) &rob->setCmd, (char*) rcv, strlen((char*)rcv));
           rob->state = KAWA_RCV_SND_POSE;        
           break; 

           case KAWA_RCV_SND_POSE:
           ans = kawasakiParseSetFeedback((char*)rcv, rob);
           if (ans == 1U)
           {
              if (strncmp(&rob->feedbackCmd, &rob->setCmd, strlen(rob->feedbackCmd)) == 0u)
              {
                  rob->state = KAWA_IDLE;                
              }
           }
           else if (ans == 2U)
           {
             if (strncmp(&rob->feedbackCmd, &rob->setCmd, strlen(rob->feedbackCmd)) == 0u)
             {
                if (strncmp(&rob->feedbackError, KAWA_NO_ERROR_FEEDBACK, strlen(KAWA_NO_ERROR_FEEDBACK)) == 0u) 
                {
                    rob->state = KAWA_IDLE;
                }
                else if (strncmp(&rob->feedbackError, KAWA_MOTOR_OFF_ERROR, strlen(KAWA_MOTOR_OFF_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_SET_MTR_OFF;
                }
                else if (strncmp(&rob->feedbackError, KAWA_TEACH_LOCK_ON_ERROR, strlen(KAWA_TEACH_LOCK_ON_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_TEACH_LOCK_ON_ERROR;
                }
                else if (strncmp(&rob->feedbackError, KAWA_ERROR_MODE_ERROR, strlen(KAWA_ERROR_MODE_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_ERROR_MODE_ERROR;
                }        
                else if (strncmp(&rob->feedbackError, KAWA_ALREADY_RUNNING_ERROR, strlen(KAWA_ALREADY_RUNNING_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_ALREADY_RUNNING_ERROR;
                }
                else if (strncmp(&rob->feedbackError, KAWA_CANNOT_REACH_ERROR, strlen(KAWA_CANNOT_REACH_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_CANNOT_REACH_ERROR;
                }
                else if (strncmp(&rob->feedbackError, KAWA_TEACH_MODE_ERROR, strlen(KAWA_TEACH_MODE_ERROR)) == 0u) 
                {
                    rob->state = KAWA_SET_ERROR_TEACH_MODE_ERROR;
                }                                
             }
          }
          break;                
                 
          default:                                                              /* sits here on all alarm states - until acknowledged and moved out */
          break;
    }
        
}
#ifdef __cplusplus
}
#endif
