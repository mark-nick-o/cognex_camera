#include "definitions.h"                                                        // Common data for compiler

#if defined(COGNEX_CAM_USED)

#include <stdint.h>
#include "cognex.h"
#include "telnet_cmd.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -------------------- Command Strings ------------------------------------  */
void COGN_SendTA( char *msg, const uint32_t partID );
uint8_t COGN_ParseTA_AlignmentReply(char* msg);

/* -------------------- SLMP -----------------------------------------------  */
uint8_t COGN_TA_GP_Send( char *msg, const uint32_t partId );
uint8_t COGN_TA_GP_Receive( char *msg, COGN_TA_GP_Rcv_t *rcv );

/* --------------------- GoldenPose ----------------------------------------  */
/* -------------------- Command Strings ------------------------------------  */
void COGN_SendXA( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
void COGN_SendXAS( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
void COGN_SendXALC( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode, COGN_LCResult_e LCresultMode );
void COGN_SendXAMP( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
void COGN_SendSGP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose );
void COGN_SendGCP( char *msg, const uint32_t stepID, const uint32_t coord );
void COGN_SendGCCP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose );

uint8_t COGN_ParseSGP_AlignmentReply(char* msg);
uint8_t COGN_ParseGP_AlignmentReply( char* msg, COGN_pose_t *pose );
uint8_t COGN_ParseGCP_AlignmentReply(char* msg, COGN_GCP_GP_Rcv_t *poseRead);
/* -------------------- SLMP -----------------------------------------------  */
uint8_t COGN_XA_GP_Receive( char *msg, COGN_XA_GP_Rcv_t *rcv );
uint8_t COGN_XA_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
uint8_t COGN_XAS_GP_Receive( char *msg, COGN_XAS_GP_Rcv_t *rcv );
uint8_t COGN_XAS_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
uint8_t COGN_XALC_GP_Receive( char *msg, COGN_XALC_GP_Rcv_t *rcv );
uint8_t COGN_XALC_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, COGN_LCResult_e LCresultMode, const uint32_t partId );
uint8_t COGN_XAMP_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
uint8_t COGN_XAMP_GP_Receive( char *msg, COGN_XAMP_GP_Rcv_t *rcv );
uint8_t COGN_SGP_GP_Send( char *msg, const COGN_pose_t *pose, const uint32_t stepId, COGN_coord_e cord );
uint8_t COGN_SGP_GP_Receive( char *msg, COGN_SGP_GP_Rcv_t *rcv );
uint8_t COGN_GCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord );
uint8_t COGN_GCP_GP_Receive( char *msg, COGN_GCP_GP_Rcv_t *rcv );
uint8_t COGN_GCCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord, const COGN_pose_t pose );
uint8_t COGN_GCCP_GP_Receive( char *msg, COGN_GCCP_GP_Rcv_t *rcv );

void COGN_SendTT( char *msg, const uint32_t partID, const COGN_pose_t pose );
uint8_t COGN_ParseTT_AlignmentReply(char* msg);
uint8_t COGN_TT_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose );
uint8_t COGN_TT_VGR_Receive( const char *msg, COGN_TT_VGR_Rcv_t *rcv );
void COGN_SendTTR( char *msg, const uint32_t partID, const COGN_pose_t pose );
uint8_t COGN_ParseTTR_AlignmentReply(char* msg);
uint8_t COGN_TTR_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose );
uint8_t COGN_TTR_VGR_Receive( const char *msg, COGN_TT_VGR_Rcv_t *rcv );

int8_t COGN_SendXT( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );
uint8_t COGN_ParseXT_AlignmentReply(const char* msg, COGN_pose_t *pose);
uint8_t COGN_XT_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
uint8_t COGN_XT_VGR_Receive( const char *msg, COGN_XT_VGR_Rcv_t *rcv );

uint8_t COGN_XT2_VGR_Receive( const char *msg, COGN_XT2_VGR_Rcv_t *rcv );
uint8_t COGN_XT2_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
uint8_t COGN_ParseXT2_AlignmentReply(const char* msg, COGN_XT2_VGR_Rcv_t *pose);
int8_t COGN_SendXT2( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

uint8_t COGN_XTS_VGR_Receive( const char *msg, COGN_XTS_VGR_Rcv_t *rcv );
uint8_t COGN_XTS_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
uint8_t COGN_ParseXTS_AlignmentReply( const char* msg, COGN_XTS_VGR_Rcv_t *pose );
int8_t COGN_SendXTS( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

uint8_t COGN_XTLC_VGR_Receive( const char *msg, COGN_XTLC_VGR_Rcv_t *rcv );
uint8_t COGN_XTLC_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, COGN_LCResult_e lcRes, const COGN_pose_t *pose );
uint8_t COGN_ParseXTLC_AlignmentReply(const char* msg, COGN_XTLC_VGR_Rcv_t *pose);
int8_t COGN_SendXTLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

void COGN_SendLF( char *msg, const uint32_t stepID, const uint32_t prodID, const COGN_pose_t pose );
uint8_t COGN_ParseLF_AlignmentReply(const char* msg, COGN_LF_MSC_Rcv_t *pose);
uint8_t COGN_LF_MSC_Send( char *msg, const uint32_t stepId, const COGN_pose_t *pose );
uint8_t COGN_LF_MSC_Receive( const char *msg, COGN_LF_MSC_Rcv_t *rcv );

uint8_t COGN_TPR_MSC_Receive( const char *msg, COGN_TPR_MSC_Rcv_t *rcv );
uint8_t COGN_TPR_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t *pose );
uint8_t COGN_ParseTPR_AlignmentReply(const char* msg, COGN_TPR_MSC_Rcv_t *pose);
void COGN_SendTPR( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t pose );

uint8_t COGN_LC_MSC_Receive( const char *msg, COGN_LC_MSC_Rcv_t *rcv );
uint8_t COGN_LC_MSC_Send( char *msg, const uint32_t partID, COGN_LCResult_e resMode );
int16_t COGN_ParseLC_MSC_AlignmentReply(const char* msg, COGN_LC_MSC_Rcv_t *pose);
void COGN_SendLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode );
uint8_t COGN_GP_MSC_Receive( const char *msg, COGN_GP_MSC_Rcv_t *rcv );
uint8_t COGN_GP_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
int16_t COGN_ParseGP_MSC_AlignmentReply(const char* msg, COGN_GP_MSC_Rcv_t *pose);
void COGN_SendGP( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const uint32_t align, const COGN_pose_t pose );

uint8_t COGN_TP_MSC_Receive( const char *msg, COGN_TP_MSC_Rcv_t *rcv );
uint8_t COGN_TP_MSC_Send( char *msg, const uint32_t partID, const uint16_t alignMode );
void COGN_SendTP( char *msg, const uint32_t partID, const uint16_t alignMode );
int16_t COGN_ParseTP_MSC_AlignmentReply(const char* msg, COGN_TP_MSC_Rcv_t *pose);

void COGN_SendCP( char *msg );
int16_t COGN_ParseCP_MSC_AlignmentReply(const char* msg, COGN_CP_MSC_Rcv_t *pose);
uint8_t COGN_CP_MSC_Send( char *msg, const uint16_t rStat );
uint8_t COGN_CP_MSC_Receive( const char *msg, COGN_CP_MSC_Rcv_t *rcv );

void COGN_SendGS( char *msg, const uint8_t cam );
int16_t COGN_ParseGS_SV_AlignmentReply(const char* msg, COGN_GS_SV_Rcv_t *pose);
uint8_t COGN_GS_SV_Send( char *msg, const uint16_t cameraNo );
uint8_t COGN_GS_SV_Receive( const char *msg, COGN_GS_SV_Rcv_t *rcv );

void COGN_SendGV( char *msg, const uint8_t cam );
int16_t COGN_ParseGV_SV_AlignmentReply(const char* msg, COGN_GV_SV_Rcv_t *pose);
uint8_t COGN_GV_SV_Send( char *msg, const uint16_t cameraNo );
uint8_t COGN_GV_SV_Receive( const char *msg, COGN_GV_SV_Rcv_t *rcv );

void COGN_SendPID( char *msg, const uint32_t prodID );
int16_t COGN_ParsePID_SV_AlignmentReply(const char* msg, COGN_PID_SV_Rcv_t *pose);
uint8_t COGN_PID_SV_Send( char *msg, const uint32_t prodID );
uint8_t COGN_PID_SV_Receive( const char *msg, COGN_PID_SV_Rcv_t *rcv );

void COGN_SendTM( char *msg, const uint32_t prodID, const uint8_t trigVal );
int16_t COGN_ParseTM_TRIG_AlignmentReply(const char* msg, COGN_TM_TRIG_Rcv_t *pose);
uint8_t COGN_TM_TRIG_Send( char *msg, const uint32_t prodID, const uint16_t trigVal );
uint8_t COGN_TM_TRIG_Receive( const char *msg, COGN_TM_TRIG_Rcv_t *rcv );

/* Train Alignment Golden Pose --- Train the “Golden Pose” of the target */

/*-----------------------------------------------------------------------------
 *  COGN_SendTA :  wrapper for writing TA to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID
 *  Return: uint8_t The result status 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
void COGN_SendTA( char *msg, const uint32_t partID )
{
   API_GOGN_TA_GP(msg,partID);
}
/*-----------------------------------------------------------------------------
 *  COGN_ParseTA_AlignmentReply:  Parses the TA ascci response
 *      
 *  Parameters: char* msg
 *  Return: uint8_t The result status 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseTA_AlignmentReply(char* msg)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found
    uint8_t commandStatus = 0u;                                                 // command status     
    
    if (!strncmp(msg,"TA",2U))                                                  // message is XA = Golden Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
              case 2u:
              ret = atoi(pch);
              break;
                          
              default:
              break;                                                    
          }
          pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return ret;
}

/* ---------- SLMP data send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TA_GP_Send: send TA message 
 *      
 *  Parameters: char *msg, const uint32_t partId
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TA_GP_Send( char *msg, const uint32_t partId )
{
   COGN_TA_GP_Snd_t snd; 
   size_t len = COGN_TA_SND_OFFST + sizeof(COGN_TA_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.cmdId = COGN_TA_SLMP_CMD;
   snd.partId = partId;  
     
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_TA_SND_OFFST, (void*) &snd, sizeof(COGN_TA_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TA_GP_Receive: receive TA message 
 *      
 *  Parameters: char *msg, COGN_TA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TA_GP_Receive( char *msg, COGN_TA_GP_Rcv_t *rcv )
{
   size_t len = COGN_TA_RCV_OFFST + sizeof(COGN_TA_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TA_RCV_OFFST, sizeof(COGN_TA_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTA :  wrapper for writing XA to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, 
 *  const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendXA( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode )
{
   API_COGN_XA_GP(msg,partID,resultMode,currentPosn,rotateCurrentPosn);
}

/* --------------------- read back function for Golden Pose ----------------- */

/*-----------------------------------------------------------------------------
 *  COGN_ParseGP_AlignmentReply:  
 *      
 *  Parameters: char* msg, COGN_pose_t *pose 
 *  Return: uint8_t -1 (error) or number of fields found in the message
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseGP_AlignmentReply(char* msg, COGN_pose_t *pose)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U;                                                       // number of strings found
    uint8_t commandStatus = 0u;                                                 // command status     
    uint8_t xamp = 0u;
    
    if (!strncmp(msg,"XA",2U))                                                  // message is XA = Golden Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
              case 2u:
              strcpy(method,pch);
              break;
                          
              case 3u:
              commandStatus = atoi(pch);
              if (commandStatus <= 0u)
              {
                 return -1;
              }
              break;
                          
              case 4u:
              if (!strncmp(msg,"XAMP",2U))
              {
                pose->foundPartId = atol(pch);
                xamp = 1u;
              }
              else
              {
                pose->coord.x = atol(pch);
              }
              break;

              case 5u:
              if (xamp == 1u)
              {
                 pose->coord.x = atol(pch);
              }
              else
              {
                 pose->coord.y = atol(pch);
              }
              break;

              case 6u:
              if (xamp == 1u)
              {
                 pose->coord.y = atol(pch);
              }
              else
              {
                 pose->coord.z = atol(pch);
              }
              break;                          

              case 7u:
              if (xamp == 1u)
              {
                 pose->coord.z = atol(pch);
              }
              else
              {
                 pose->rotat.z = atol(pch);
              }
              break;

              case 8u:
              if (xamp == 1u)
              {
                 pose->rotat.z = atol(pch);
              }
              else
              {
                 pose->rotat.y = atol(pch);
              } 
              break;

              case 9u:
              if (xamp == 1u)
              {
                 pose->rotat.y = atol(pch);
              }
              else
              {
                 pose->rotat.x = atol(pch);
              }
              break;

              case 10u:
              if (!strncmp(msg,"XAS",2U))
              {
                  pose->score[0u] = atol(pch);
              }
              else if (!strncmp(msg,"XALC",2U))
              {
                  pose->LCResult = atol(pch);
              }
              else if (xamp == 1u)
              {
                 pose->rotat.x = atol(pch);
              }
              break;

              case 11u:
              if (!strncmp(msg,"XAS",2U))
              {
                  pose->score[1u] = atol(pch);
              }
              else if (!strncmp(msg,"XALC",2U))
              {              
                  pose->LCJudge = atoi(pch);
              }
              break;        

              default:
              break;                          
                          
          }
          pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return itemNum;
}
                      
/* ---------------------- SLMP data send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XA_GP_Send: send XAS message 
 *      
 *  Parameters: char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XA_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId )
{
   COGN_XA_GP_Snd_t snd; 
   size_t len = COGN_XA_SND_OFFST + sizeof(COGN_XA_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.cmdId = COGN_XA_SLMP_CMD;
   snd.partId = partId;
   snd.mode = mode;    
     
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_XA_SND_OFFST, (void*) &snd, sizeof(COGN_XA_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XA_GP_Receive: receive XA message 
 *      
 *  Parameters: char *msg, COGN_XA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XA_GP_Receive( char *msg, COGN_XA_GP_Rcv_t *rcv )
{
   size_t len = COGN_XA_RCV_OFFST + sizeof(COGN_XA_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XA_RCV_OFFST, sizeof(COGN_XA_GP_Rcv_t));
       ret = len;
   }
   return ret;
}


/*-----------------------------------------------------------------------------
 *  COGN_SendXAS :  wrapper for writing XAS to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendXAS( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode )
{
   API_COGN_XAS_GP(msg,partID,resultMode,currentPosn,rotateCurrentPosn);
}
                      
/* ====================== SLMP data send ===================================  */
/*-----------------------------------------------------------------------------
 *  COGN_XAS_GP_Send: send XAS message 
 *      
 *  Parameters: char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XAS_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId )
{
   COGN_XAS_GP_Snd_t snd; 
   size_t len = COGN_XAS_SND_OFFST + sizeof(COGN_XAS_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.cmdId = COGN_XAS_SLMP_CMD;
   snd.partId = partId;
   snd.mode = mode;    
     
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_XAS_SND_OFFST, (void*) &snd, sizeof(COGN_XAS_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XAS_GP_Receive: receive XAS message 
 *      
 *  Parameters: char *msg, COGN_XA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XAS_GP_Receive( char *msg, COGN_XAS_GP_Rcv_t *rcv )
{
   size_t len = COGN_XAS_RCV_OFFST + sizeof(COGN_XAS_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XAS_RCV_OFFST, sizeof(COGN_XAS_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXALC :  wrapper for writing XALC to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, 
 *              const COGN_u32Vectr_t rotateCurrentPosn,  
 *              COGN_GP_Result_e resultMode, COGN_LCResult_e LCresultMode
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendXALC( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode, COGN_LCResult_e LCresultMode )
{
   API_GOGN_XALC_GP(msg,partID,resultMode,LCresultMode,currentPosn,rotateCurrentPosn);
}

/*-----------------------------------------------------------------------------
 *  COGN_XALC_GP_Send: send XALC message 
 *      
 *  Parameters: char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XALC_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, COGN_LCResult_e LCresultMode, const uint32_t partId )
{
   COGN_XALC_GP_Snd_t snd; 
   size_t len = COGN_XALC_SND_OFFST + sizeof(COGN_XALC_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.cmdId = COGN_XALC_SLMP_CMD;
   snd.partId = partId;
   snd.mode = mode;    
   snd.LCMode = LCresultMode;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_XALC_SND_OFFST, (void*) &snd, sizeof(COGN_XALC_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XALC_GP_Receive: receive XA message 
 *      
 *  Parameters: char *msg, COGN_XA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XALC_GP_Receive( char *msg, COGN_XALC_GP_Rcv_t *rcv )
{
   size_t len = COGN_XALC_RCV_OFFST + sizeof(COGN_XALC_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XALC_RCV_OFFST, sizeof(COGN_XALC_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXAMP :  wrapper for writing XAMP to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, 
 *              const COGN_u32Vectr_t rotateCurrentPosn,  
 *              COGN_GP_Result_e resultMode, COGN_LCResult_e LCresultMode
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendXAMP( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode )
{
   API_GOGN_XAMP_GP(msg,partID,resultMode,currentPosn,rotateCurrentPosn);
}

/*-----------------------------------------------------------------------------
 *  COGN_XAMP_GP_Send: send XAMP message 
 *      
 *  Parameters: char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XAMP_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId )
{
   COGN_XAMP_GP_Snd_t snd; 
   size_t len = COGN_XAMP_SND_OFFST + sizeof(COGN_XAMP_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.cmdId = COGN_XAMP_SLMP_CMD;
   snd.partId = partId;
   snd.mode = mode;    
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_XAMP_SND_OFFST, (void*) &snd, sizeof(COGN_XAMP_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XAMP_GP_Receive: receive XA message 
 *      
 *  Parameters: char *msg, COGN_XA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XAMP_GP_Receive( char *msg, COGN_XAMP_GP_Rcv_t *rcv )
{
   size_t len = COGN_XAMP_RCV_OFFST + sizeof(COGN_XAMP_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XAMP_RCV_OFFST, sizeof(COGN_XAMP_GP_Rcv_t));
       ret = len;
   }
   return ret;
}


/*-----------------------------------------------------------------------------
 *  COGN_ParseSGP_AlignmentReply:  Parses the TA ascci response
 *      
 *  Parameters: char* msg
 *  Return: uint8_t The result status 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseSGP_AlignmentReply(char* msg)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found
    uint8_t commandStatus = 0u;                                                 // command status     
    
    if (!strncmp(msg,"SGP",3U))                                                  // message is SGP = set Golden Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
              case 2u:
              ret = atoi(pch);
              break;
                          
              default:
              break;                                                    
          }
          pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendSGP :  wrapper for writing SGP to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose 
 *          
 *              
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendSGP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose )
{
   API_GOGN_SGP_GP(msg,stepID,coord,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_SGP_GP_Send: compose an SGP message 
 *      
 *  Parameters: char *msg, const COGN_pose_t *pose, const uint32_t stepId, COGN_coord_e cord
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_SGP_GP_Send( char *msg, const COGN_pose_t *pose, const uint32_t stepId, COGN_coord_e cord )
{
   COGN_SGP_GP_Snd_t snd; 
   size_t len = COGN_SGP_SND_OFFST + sizeof(COGN_SGP_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.coord = cord;
   snd.Y = pose->coord.y;
   snd.X = pose->coord.x;
   snd.Theta = pose->theta;
   snd.cmdId = COGN_SGP_SLMP_CMD;
   snd.stepId = stepId;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_SGP_SND_OFFST, (void*) &snd, sizeof(COGN_SGP_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SGP_GP_Receive: receive XA message 
 *      
 *  Parameters: char *msg, COGN_XA_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_SGP_GP_Receive( char *msg, COGN_SGP_GP_Rcv_t *rcv )
{
   size_t len = COGN_SGP_RCV_OFFST + sizeof(COGN_SGP_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_SGP_RCV_OFFST, sizeof(COGN_SGP_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendGCP :  wrapper for writing GCP to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t stepID, const uint32_t coord 
 *          
 *              
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendGCP( char *msg, const uint32_t stepID, const uint32_t coord )
{
   API_GOGN_GCP_GP(msg,stepID,coord);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseGCP_AlignmentReply:  Parses the GCP ascci response
 *      
 *  Parameters: char* msg, COGN_GCP_GP_Rcv_t *poseRead
 *  Return: uint8_t The result status 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseGCP_AlignmentReply(char* msg, COGN_GCP_GP_Rcv_t *poseRead)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found
    uint8_t commandStatus = 0u;                                                 // command status     
    
    if ((!strncmp(msg,"GGP",3U)) || (!strncmp(msg,"GCP",3U)))                   // message is GGP = get Golden Pose / get Current Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
              case 2u:
              poseRead->result = atoi(pch);
              break;

              case 3u:
              poseRead->x = atoi(pch);
              break;

              case 4u:
              poseRead->y = atoi(pch);
              break;

              case 5u:
              poseRead->theta = atoi(pch);
              break;
                          
              default:
              break;                                                    
          }
          pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GCP_GP_Send: compose an GCP message 
 *      
 *  Parameters: char *msg, const uint32_t stepId, COGN_coord_e cord
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord )
{
   COGN_GCP_GP_Snd_t snd; 
   size_t len = COGN_GCP_SND_OFFST + sizeof(COGN_GCP_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.coord = cord;
   snd.cmdId = COGN_GCP_SLMP_CMD;
   snd.stepId = stepId;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_GCP_SND_OFFST, (void*) &snd, sizeof(COGN_GCP_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GCP_GP_Receive: receive GCP message 
 *      
 *  Parameters: char *msg, COGN_GCP_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GCP_GP_Receive( char *msg, COGN_GCP_GP_Rcv_t *rcv )
{
   size_t len = COGN_GCP_RCV_OFFST + sizeof(COGN_GCP_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_GCP_RCV_OFFST, sizeof(COGN_GCP_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendGCCP :  wrapper for writing GCP to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose 
 *          
 *              
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendGCCP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose )
{
   API_GOGN_GCCP_GP(msg,stepID,coord,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_GCCP_GP_Send: compose an GCP message 
 *      
 *  Parameters: char *msg, const uint32_t stepId, COGN_coord_e cord
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GCCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord, const COGN_pose_t pose )
{
   COGN_GCCP_GP_Snd_t snd; 
   size_t len = COGN_GCCP_SND_OFFST + sizeof(COGN_GCCP_GP_Snd_t);
   uint8_t ret = -1;
   
   snd.coord = cord;
   snd.cmdId = COGN_GCCP_SLMP_CMD;
   snd.stepId = stepId;
   snd.curPosX = pose.coord.x;
   snd.curPosY = pose.coord.y;
   snd.curPosZ = pose.coord.z;
   snd.rotX = pose.rotat.x;
   snd.rotY = pose.rotat.y;
   snd.rotZ = pose.rotat.z;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_GCCP_SND_OFFST, (void*) &snd, sizeof(COGN_GCCP_GP_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GCCP_GP_Receive: receive GCP message 
 *      
 *  Parameters: char *msg, COGN_GCCP_GP_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GCCP_GP_Receive( char *msg, COGN_GCCP_GP_Rcv_t *rcv )
{
   size_t len = COGN_GCCP_RCV_OFFST + sizeof(COGN_GCCP_GP_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_GCCP_RCV_OFFST, sizeof(COGN_GCCP_GP_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTT :  wrapper for writing TT to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID
 *  Return: uint8_t The result sTTtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
void COGN_SendTT( char *msg, const uint32_t partID, const COGN_pose_t pose )
{
   API_GOGN_TT_VGR(msg,partID,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseTT_AlignmentReply:  Parses the TT ascci response
 *      
 *  Parameters: char* msg
 *  Return: uint8_t The result sTTtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseTT_AlignmentReply(char* msg)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found
    uint8_t commandSTTtus = 0u;                                                 // command sTTtus     
    
    if (!strncmp(msg,"TT",2U))                                                  // message is XA = Golden Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
              {
                case 2u:
                ret = atoi(pch);
                break;
                          
            default:
            break;                                                    
              }
              pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return ret;
}

/* ---------- SLMP TT send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TT_VGR_Send: send TT message 
 *      
 *  Parameters: char *msg, const uint32_t partId, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TT_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose )
{
   COGN_TT_VGR_Snd_t snd; 
   size_t len = COGN_TT_SND_OFFST + sizeof(COGN_TT_VGR_Snd_t);
   uint8_t ret = -1;
   
   snd.cmdId = COGN_TT_SLMP_CMD;
   snd.partId = partId;  
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_TT_SND_OFFST, (void*) &snd, sizeof(COGN_TT_VGR_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TT_VGR_Receive: receive TT message 
 *      
 *  Parameters: const char *msg, COGN_TT_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TT_VGR_Receive( const char *msg, COGN_TT_VGR_Rcv_t *rcv )
{
   size_t len = COGN_TT_RCV_OFFST + sizeof(COGN_TT_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TT_RCV_OFFST, sizeof(COGN_TT_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTTR :  wrapper for writing TTR to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID
 *  Return: uint8_t The result sTTRtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
void COGN_SendTTR( char *msg, const uint32_t partID, const COGN_pose_t pose )
{
   API_GOGN_TTR_VGR(msg,partID,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseTTR_AlignmentReply:  Parses the TTR ascci response
 *      
 *  Parameters: char* msg
 *  Return: uint8_t The result sTTRtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseTTR_AlignmentReply(char* msg)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found
    uint8_t commandSTTRtus = 0u;                                                 // command sTTRtus     
    
    if (!strncmp(msg,"TTR",2U))                                                  // message is XA = Golden Pose
    {
       pch = strtok(msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
              {
                case 2u:
                ret = atoi(pch);
                break;
                          
            default:
            break;                                                    
              }
              pch = strtok(NULL, ",");                                              /* get the next string in the line */                             
       }
    }
    return ret;
}

/* ---------- SLMP TTR send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TTR_VGR_Send: send TTR message 
 *      
 *  Parameters: char *msg, const uint32_t partId, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TTR_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose )
{
   COGN_TTR_VGR_Snd_t snd; 
   size_t len = COGN_TTR_SND_OFFST + sizeof(COGN_TTR_VGR_Snd_t);
   uint8_t ret = -1;
   
   snd.cmdId = COGN_TTR_SLMP_CMD;
   snd.partId = partId;  
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_TTR_SND_OFFST, (void*) &snd, sizeof(COGN_TTR_VGR_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TTR_VGR_Receive: receive TTR message 
 *      
 *  Parameters: char *msg, COGN_TTR_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TTR_VGR_Receive( const char *msg, COGN_TTR_VGR_Rcv_t *rcv )
{
   size_t len = COGN_TTR_RCV_OFFST + sizeof(COGN_TTR_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TTR_RCV_OFFST, sizeof(COGN_TTR_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXT :  wrapper for writing XT to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose
 *  Return: int8_t -1 inavlid parameters
 *----------------------------------------------------------------------------*/
int8_t COGN_SendXT( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose )
{
   int8_t ret = 0;        
   if (( resMode >= COGN_VGR_RET_NUM ) || ( resMode <= 0 )) ret = -1;         
   API_GOGN_XT_VGR(msg,partID,resMode,pose);
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseXT_AlignmentReply:  Parses the XT ascci response
 *      
 *  Parameters: const char* msg, COGN_pose_t *pose
 *  Return: uint8_t The result sXTtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseXT_AlignmentReply(const char* msg, COGN_pose_t *pose)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    
    if (!strncmp((char*)msg,"XT",2U))                                                  // message is XT = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
                case 2u:
                ret = atoi(pch);
                break;

                case 3u:
                pose->coord.x = atol(pch);
                break;

                case 4u:
                pose->coord.y = atol(pch);
                break;

                case 5u:
                pose->coord.z = atol(pch);
                break;

                case 6u:
                pose->rotat.x = atol(pch);
                break;

                case 7u:
                pose->rotat.y = atol(pch);
                break;

                case 8u:
                pose->rotat.z = atol(pch);
                break;
                        
                default:
                break;                                                    
            }
            pch = strtok(NULL, ",");                                            /* get the next string in the line */                             
       }
    }
    return ret;
}

/* ---------- SLMP XT send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XT_VGR_Send: send XT message 
 *      
 *  Parameters: char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XT_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose )
{
   COGN_XT_VGR_Snd_t snd; 
   size_t len = COGN_XT_SND_OFFST + sizeof(COGN_XT_VGR_Snd_t);
   uint8_t ret = -1;
        
   if (( resMode < COGN_VGR_RET_NUM ) && ( resMode > 0 ))    
   {
       snd.cmdId = COGN_XT_SLMP_CMD;
       snd.partId = partId;  
       snd.curPosX = pose->coord.x;
       snd.curPosY = pose->coord.y;
       snd.curPosZ = pose->coord.z;
       snd.rotX = pose->rotat.x;
       snd.rotY = pose->rotat.y;
       snd.rotZ = pose->rotat.z;
       snd.resMode = resMode;
   
       if (sizeof(msg) >= len)
       {
           memcpy((void*) msg+COGN_XT_SND_OFFST, (void*) &snd, sizeof(COGN_XT_VGR_Snd_t));
           ret = len;
       }
   } 
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XT_VGR_Receive: receive XT message 
 *      
 *  Parameters: char *msg, COGN_XT_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XT_VGR_Receive( const char *msg, COGN_XT_VGR_Rcv_t *rcv )
{
   size_t len = COGN_XT_RCV_OFFST + sizeof(COGN_XT_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XT_RCV_OFFST, sizeof(COGN_XT_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXT2 :  wrapper for writing XT2 to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose
 *  Return: int8_t -1 inavlid parameters
 *----------------------------------------------------------------------------*/
int8_t COGN_SendXT2( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose )
{
   int8_t ret = 0;        
   if (( resMode >= COGN_VGR_RET_NUM ) || ( resMode <= 0 )) ret = -1;         
   API_GOGN_XT2_VGR(msg,partID,resMode,pose);
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseXT2_AlignmentReply:  Parses the XT2 ascci response
 *      
 *  Parameters: const char* msg, COGN_XT2_VGR_Rcv_t *pose
 *  Return: uint8_t The result sXT2tus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseXT2_AlignmentReply(const char* msg, COGN_XT2_VGR_Rcv_t *pose)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    
    if (!strncmp((char*)msg,"XT2",2U))                                                  // message is XT2 = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
              {
                case 2u:
                pose->result1 = atoi(pch);
                break;

                case 3u:
                pose->curPosX1 = atol(pch);
                break;

                case 4u:
                pose->curPosY1 = atol(pch);
                break;

                case 5u:
                pose->curPosZ1 = atol(pch);
                break;

                case 6u:
                pose->rotZ1 = atol(pch);
                break;

                case 7u:
                pose->rotY1 = atol(pch);
                break;

                case 8u:
                pose->rotX1 = atol(pch);
                break;

                case 9u:
                pose->result2 = atoi(pch);
                break;

                case 10u:
                pose->curPosX1 = atol(pch);
                break;

                case 11u:
                pose->curPosY1 = atol(pch);
                break;

                case 12u:
                pose->curPosZ1 = atol(pch);
                break;

                case 13u:
                pose->rotZ1 = atol(pch);
                break;

                case 14u:
                pose->rotY1 = atol(pch);
                break;

                case 15u:
                pose->rotX1 = atol(pch);
                break;
                        
                default:
                break;                                                    
              }
              pch = strtok(NULL, ",");                                              /* get the neXT2 string in the line */                             
       }
       ret = (pose->result1 & pose->result2);
    }
    return ret;
}

/* ---------- SLMP XT2 send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XT2_VGR_Send: send XT2 message 
 *      
 *  Parameters: char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XT2_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose )
{
   COGN_XT2_VGR_Snd_t snd; 
   size_t len = COGN_XT2_SND_OFFST + sizeof(COGN_XT2_VGR_Snd_t);
   uint8_t ret = -1;
        
   if (( resMode < COGN_VGR_RET_NUM ) && ( resMode > 0 ))    
   {
       snd.cmdId = COGN_XT2_SLMP_CMD;
       snd.partId = partId;  
       snd.curPosX = pose->coord.x;
       snd.curPosY = pose->coord.y;
       snd.curPosZ = pose->coord.z;
       snd.rotX = pose->rotat.x;
       snd.rotY = pose->rotat.y;
       snd.rotZ = pose->rotat.z;
       snd.resMode = resMode;
   
       if (sizeof(msg) >= len)
       {
           memcpy((void*) msg+COGN_XT2_SND_OFFST, (void*) &snd, sizeof(COGN_XT2_VGR_Snd_t));
           ret = len;
       }
   } 
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XT2_VGR_Receive: receive XT2 message 
 *      
 *  Parameters: char *msg, COGN_XT2_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XT2_VGR_Receive( const char *msg, COGN_XT2_VGR_Rcv_t *rcv )
{
   size_t len = COGN_XT2_RCV_OFFST + sizeof(COGN_XT2_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XT2_RCV_OFFST, sizeof(COGN_XT2_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXTS :  wrapper for writing XTS to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose
 *  Return: int8_t -1 inavlid parameters
 *----------------------------------------------------------------------------*/
int8_t COGN_SendXTS( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose )
{
   int8_t ret = 0;        
   if (( resMode >= COGN_VGR_RET_NUM ) || ( resMode <= 0 )) ret = -1;         
   API_GOGN_XTS_VGR(msg,partID,resMode,pose);
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseXTS_AlignmentReply:  Parses the XTS ascci response
 *      
 *  Parameters: const char* msg, COGN_XTS_VGR_Rcv_t *pose
 *  Return: uint8_t The result sXTStus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseXTS_AlignmentReply(const char* msg, COGN_XTS_VGR_Rcv_t *pose)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    
    if (!strncmp((char*)msg,"XTS",2U))                                                  // message is XTS = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
              {
                case 2u:
                pose->result1 = atoi(pch);
                break;

                case 3u:
                pose->curPosX1 = atol(pch);
                break;

                case 4u:
                pose->curPosY1 = atol(pch);
                break;

                case 5u:
                pose->curPosZ1 = atol(pch);
                break;

                case 6u:
                pose->rotZ1 = atol(pch);
                break;

                case 7u:
                pose->rotY1 = atol(pch);
                break;

                case 8u:
                pose->rotX1 = atol(pch);
                break;

                case 9u:
                pose->score1 = atol(pch);
                break;

                case 10u:
                pose->score2 = atol(pch);
                break;
                        
                default:
                break;                                                    
           }
           pch = strtok(NULL, ",");                                              /* get the neXTS string in the line */                             
       }
       ret = pose->result1;
    }
    return ret;
}

/* ---------- SLMP XTS send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XTS_VGR_Send: send XTS message 
 *      
 *  Parameters: char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTS_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose )
{
   COGN_XTS_VGR_Snd_t snd; 
   size_t len = COGN_XTS_SND_OFFST + sizeof(COGN_XTS_VGR_Snd_t);
   uint8_t ret = -1;
        
   if (( resMode < COGN_VGR_RET_NUM ) && ( resMode > 0 ))    
   {
       snd.cmdId = COGN_XTS_SLMP_CMD;
       snd.partId = partId;  
       snd.curPosX = pose->coord.x;
       snd.curPosY = pose->coord.y;
       snd.curPosZ = pose->coord.z;
       snd.rotX = pose->rotat.x;
       snd.rotY = pose->rotat.y;
       snd.rotZ = pose->rotat.z;
       snd.resMode = resMode;
   
       if (sizeof(msg) >= len)
       {
           memcpy((void*) msg+COGN_XTS_SND_OFFST, (void*) &snd, sizeof(COGN_XTS_VGR_Snd_t));
           ret = len;
       }
   } 
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XTS_VGR_Receive: receive XTS message 
 *      
 *  Parameters: char *msg, COGN_XTS_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTS_VGR_Receive( const char *msg, COGN_XTS_VGR_Rcv_t *rcv )
{
   size_t len = COGN_XTS_RCV_OFFST + sizeof(COGN_XTS_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XTS_RCV_OFFST, sizeof(COGN_XTS_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXTLC :  wrapper for writing XTLC to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, COGN_LCResult_e lcRes, const COGN_pose_t pose
 *  Return: int8_t -1 inavlid parameters
 *----------------------------------------------------------------------------*/
int8_t COGN_SendXTLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, COGN_LCResult_e lcRes, const COGN_pose_t pose )
{
   int8_t ret = 0;        
   if ((( resMode >= COGN_VGR_RET_NUM ) || ( resMode <= 0 )) || (( lcRes >= COGN_LC_RET_NUM ) || ( lcRes <= 0 ))) ret = -1;         
   API_GOGN_XTLC_VGR(msg,partID,resMode,lcRes,pose);
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseXTLC_AlignmentReply:  Parses the XTLC ascci response
 *      
 *  Parameters: const char* msg, COGN_XTLC_VGR_Rcv_t *pose
 *  Return: uint8_t The result sXTLCtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseXTLC_AlignmentReply(const char* msg, COGN_XTLC_VGR_Rcv_t *pose)
{
    char * pch = NULL;
    char * method = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    
    if (!strncmp((char*)msg,"XTLC",2U))                                                  // message is XTLC = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
                case 2u:
                pose->result1 = atoi(pch);
                break;

                case 3u:
                pose->curPosX1 = atol(pch);
                break;

                case 4u:
                pose->curPosY1 = atol(pch);
                break;

                case 5u:
                pose->curPosZ1 = atol(pch);
                break;

                case 6u:
                pose->rotZ1 = atol(pch);
                break;

                case 7u:
                pose->rotY1 = atol(pch);
                break;

                case 8u:
                pose->rotX1 = atol(pch);
                break;

                case 9u:
                pose->LCResult = atol(pch);
                break;

                case 10u:
                pose->LCJudge = atol(pch);
                break;
                        
                default:
                break;                                                    
              }
              pch = strtok(NULL, ",");                                              /* get the neXTLC string in the line */                             
       }
       ret = pose->result1;
    }
    return ret;
}

/* ---------- SLMP XTLC send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XTLC_VGR_Send: send XTLC message 
 *      
 *  Parameters: char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTLC_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, COGN_LCResult_e lcRes, const COGN_pose_t *pose )
{
   COGN_XTLC_VGR_Snd_t snd; 
   size_t len = COGN_XTLC_SND_OFFST + sizeof(COGN_XTLC_VGR_Snd_t);
   uint8_t ret = -1;
        
   if (( resMode < COGN_VGR_RET_NUM ) && ( resMode > 0 ))    
   {
       snd.cmdId = COGN_XTLC_SLMP_CMD;
       snd.partId = partId;  
       snd.curPosX = pose->coord.x;
       snd.curPosY = pose->coord.y;
       snd.curPosZ = pose->coord.z;
       snd.rotX = pose->rotat.x;
       snd.rotY = pose->rotat.y;
       snd.rotZ = pose->rotat.z;
       snd.resMode = resMode;
       snd.LCResultMode = lcRes;
           
       if (sizeof(msg) >= len)
       {
           memcpy((void*) msg+COGN_XTLC_SND_OFFST, (void*) &snd, sizeof(COGN_XTLC_VGR_Snd_t));
           ret = len;
       }
   } 
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XTLC_VGR_Receive: receive XTLC message 
 *      
 *  Parameters: char *msg, COGN_XTLC_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTLC_VGR_Receive( const char *msg, COGN_XTLC_VGR_Rcv_t *rcv )
{
   size_t len = COGN_XTLC_RCV_OFFST + sizeof(COGN_XTLC_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XTLC_RCV_OFFST, sizeof(COGN_XTLC_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendXTMP :  wrapper for writing XTMP to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose
 *  Return: int8_t -1 inavlid parameters
 *----------------------------------------------------------------------------*/
int8_t COGN_SendXTMP( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose )
{
   int8_t ret = 0;        
   if (( resMode >= COGN_VGR_RET_NUM ) || ( resMode <= 0 )) ret = -1;         
   API_GOGN_XTMP_VGR(msg,partID,resMode,pose);
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseXTMP_AlignmentReply:  Parses the XTMP ascci response
 *      
 *  Parameters: const char* msg, COGN_XTMP_VGR_Rcv_t *pose
 *  Return: uint8_t The result sXTMPtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseXTMP_AlignmentReply(const char* msg, COGN_XTMP_VGR_Rcv2_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
        
    if (!strncmp((char*)msg,"XTMP",2U))                                                  // message is XTMP = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {
                case 2u:
                pose->result1 = atoi(pch);
                break;

                case 3u:
                valueIn = atol(pch);
                pose->primaryPartId = valueIn & 0x000Fu;
                pose->backupNo1PartId = valueIn & 0x00F0u;        
                pose->backupNo2PartId = valueIn & 0x0F00u;
                pose->backupNo3PartId = valueIn & 0xF000u;        
                break;
                        
                case 4u:
                pose->curPosX1 = atol(pch);
                break;

                case 5u:
                pose->curPosY1 = atol(pch);
                break;

                case 6u:
                pose->curPosZ1 = atol(pch);
                break;

                case 7u:
                pose->rotZ1 = atol(pch);
                break;

                case 8u:
                pose->rotY1 = atol(pch);
                break;

                case 9u:
                pose->rotX1 = atol(pch);
                break;
                        
                default:
                break;                                                    
           }
           pch = strtok(NULL, ",");                                             /* get the neXTMP string in the line */                             
       }
       ret = pose->result1;
    }
    return ret;
}

/* ---------- SLMP XTMP send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_XTMP_VGR_Send: send XTMP message 
 *      
 *  Parameters: char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTMP_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose )
{
   COGN_XTMP_VGR_Snd_t snd; 
   size_t len = COGN_XTMP_SND_OFFST + sizeof(COGN_XTMP_VGR_Snd_t);
   uint8_t ret = -1;
        
   if (( resMode < COGN_VGR_RET_NUM ) && ( resMode > 0 ))    
   {
       snd.cmdId = COGN_XTMP_SLMP_CMD;
       snd.partId = partId;  
       snd.curPosX = pose->coord.x;
       snd.curPosY = pose->coord.y;
       snd.curPosZ = pose->coord.z;
       snd.rotX = pose->rotat.x;
       snd.rotY = pose->rotat.y;
       snd.rotZ = pose->rotat.z;
       snd.resMode = resMode;
           
       if (sizeof(msg) >= len)
       {
           memcpy((void*) msg+COGN_XTMP_SND_OFFST, (void*) &snd, sizeof(COGN_XTMP_VGR_Snd_t));
           ret = len;
       }
   } 
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_XTMP_VGR_Receive: receive XTMP message 
 *      
 *  Parameters: char *msg, COGN_XTMP_VGR_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_XTMP_VGR_Receive( const char *msg, COGN_XTMP_VGR_Rcv_t *rcv )
{
   size_t len = COGN_XTMP_RCV_OFFST + sizeof(COGN_XTMP_VGR_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_XTMP_RCV_OFFST, sizeof(COGN_XTMP_VGR_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendLF :  wrapper for writing LF to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t stepID, const uint32_t prodID, const COGN_pose_t pose
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendLF( char *msg, const uint32_t stepID, const uint32_t prodID, const COGN_pose_t pose )
{
   API_GOGN_LF_MSC(msg,stepID,prodID,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseLF_AlignmentReply:  Parses the LF ascci response
 *      
 *  Parameters: const char* msg, COGN_LF_MSC_Rcv_t *pose
 *  Return: uint8_t The result sLFtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseLF_AlignmentReply(const char* msg, COGN_LF_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"LF",2U))                                                  // message is LF = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	        case 2u:
	        pose->result = atoi(pch);
	        break;

                case 3u:
		pose->token = atol(pch);
                break;
			
                case 4u:
                pose->prodID = atol(pch);
                break;
			
                default:
                break;			  			  
           }
	   pch = strtok(NULL, ",");                                             /* get the neLF string in the line */   			  
       }
       ret = pose->result;
    }
    return ret;
}

/* ---------- SLMP LF send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_LF_MSC_Send: send LF message 
 *      
 *  Parameters: char *msg, const uint32_t stepId, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_LF_MSC_Send( char *msg, const uint32_t stepId, const COGN_pose_t *pose )
{
   COGN_LF_MSC_Snd_t snd; 
   size_t len = COGN_LF_SND_OFFST + sizeof(COGN_LF_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_LF_SLMP_CMD;
   snd.stepID = stepId;  
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.prodID = 0UL;
	   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_LF_SND_OFFST, (void*) &snd, sizeof(COGN_LF_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_LF_MSC_Receive: receive LF message 
 *      
 *  Parameters: const char *msg, COGN_LF_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_LF_MSC_Receive( const char *msg, COGN_LF_MSC_Rcv_t *rcv )
{
   size_t len = COGN_LF_RCV_OFFST + sizeof(COGN_LF_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_LF_RCV_OFFST, sizeof(COGN_LF_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTPR :  wrapper for writing TPR to message buffer 
 *                 (you can add tcp send as you wish)
 *      
 *  Parameters: char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t pose
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendTPR( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t pose )
{
   API_GOGN_TPR_MSC(msg,partID,align,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseTPR_AlignmentReply:  Parses the TPR ascci response
 *      
 *  Parameters: const char* msg, COGN_TPR_MSC_Rcv_t *pose
 *  Return: uint8_t The result sTPRtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
uint8_t COGN_ParseTPR_AlignmentReply(const char* msg, COGN_TPR_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"TPR",2U))                                                  // message is TPR = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
	  {			
	        case 2u:
	        pose->result = atoi(pch);
	        break;
			
            default:
            break;			  			  
          }
          pch = strtok(NULL, ",");                                              /* get the neTPR string in the line */   			  
       }
       ret = pose->result;
    }
    return ret;
}

/* ---------- SLMP TPR send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TPR_MSC_Send: send TPR message 
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TPR_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t *pose )
{
   COGN_TPR_MSC_Snd_t snd; 
   size_t len = COGN_TPR_SND_OFFST + sizeof(COGN_TPR_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_TPR_SLMP_CMD;
   snd.partID = partID;  
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.AlignMode = align;
	   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) msg+COGN_TPR_SND_OFFST, (void*) &snd, sizeof(COGN_TPR_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TPR_MSC_Receive: receive TPR message 
 *      
 *  Parameters: char *msg, COGN_TPR_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TPR_MSC_Receive( const char *msg, COGN_TPR_MSC_Rcv_t *rcv )
{
   size_t len = COGN_TPR_RCV_OFFST + sizeof(COGN_TPR_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TPR_RCV_OFFST, sizeof(COGN_TPR_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendGP :  wrapper for writing GP to message buffer 
 *                 ( you can add tcp send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const uint32_t align, const COGN_pose_t pose
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendGP( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const uint32_t align, const COGN_pose_t pose )
{
   API_GOGN_GP_MSC(msg,partID,resMode,align,pose);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseGP_AlignmentReply:  Parses the GP ascci response
 *      
 *  Parameters: const char* msg, COGN_GP_MSC_Rcv_t *pose
 *  Return: int16_t The result sGPtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseGP_MSC_AlignmentReply(const char* msg, COGN_GP_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"GP",2U))                                                  // message is GP = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	        case 2u:
	        pose->result = atoi(pch);
	        break;

                case 3u:
                pose->x = atol(pch);
                break;

                case 4u:
                pose->y = atol(pch);
                break;

                case 5u:
                pose->z = atol(pch);
                break;

                case 6u:
                pose->az = atol(pch);
                break;

                case 7u:
                pose->by = atol(pch);
                break;

                case 8u:
                pose->cx = atol(pch);
                break;
				
                default:
                break;			  			  
           }
	   pch = strtok(NULL, ",");                                              /* get the neGP string in the line */   			  
       }
       ret = pose->result;
    }
    return ret;
}

/* ---------- SLMP GP send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_GP_MSC_Send: send GP message 
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GP_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, COGN_VGR_Result_e resMode, const COGN_pose_t *pose )
{
   COGN_GP_MSC_Snd_t snd; 
   size_t len = COGN_GP_SND_OFFST + sizeof(COGN_GP_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_GP_SLMP_CMD;
   snd.partID = partID;  
   snd.curPosX = pose->coord.x;
   snd.curPosY = pose->coord.y;
   snd.curPosZ = pose->coord.z;
   snd.rotX = pose->rotat.x;
   snd.rotY = pose->rotat.y;
   snd.rotZ = pose->rotat.z;
   snd.AlignMode = align % 4;
   snd.resMode = resMode % COGN_VGR_RET_NUM;	   
   if (snd.resMode == 0) snd.resMode = COGN_VGR_RET_ABS;   /* force default return */
   if (snd.AlignMode == 0) snd.AlignMode = 1;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_GP_SND_OFFST, (void*) &snd, sizeof(COGN_GP_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GP_MSC_Receive: receive GP message 
 *      
 *  Parameters: char *msg, COGN_GP_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GP_MSC_Receive( const char *msg, COGN_GP_MSC_Rcv_t *rcv )
{
   size_t len = COGN_GP_RCV_OFFST + sizeof(COGN_GP_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_GP_RCV_OFFST, sizeof(COGN_GP_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendLC :  wrapper for writing LC to message buffer 
 *                 ( you can add tcp send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint32_t partID, COGN_VGR_Result_e resMode
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode )
{
   API_GOGN_LC_MSC(msg,partID,resMode);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseLC_AlignmentReply:  Parses the LC ascci response
 *      
 *  Parameters: const char* msg, COGN_LC_MSC_Rcv_t *pose
 *  Return: int16_t The result sLCtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseLC_MSC_AlignmentReply(const char* msg, COGN_LC_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"LC",2U))                                                  // message is LC = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
	  {			
	    case 2u:
	    pose->status = atoi(pch);
	    break;

            case 3u:
            pose->result = atol(pch);
            break;

            case 4u:
            pose->LCJudge = atoi(pch);
            break;
				
            default:
            break;			  			  
	  }
	  pch = strtok(NULL, ",");                                              /* get the neLC string in the line */   			  
       }
       ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP LC send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_LC_MSC_Send: send LC message 
 *      
 *  Parameters: char *msg, const uint32_t partID, const COGN_pose_t *pose
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_LC_MSC_Send( char *msg, const uint32_t partID, COGN_LCResult_e resMode )
{
   COGN_LC_MSC_Snd_t snd; 
   size_t len = COGN_LC_SND_OFFST + sizeof(COGN_LC_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_LC_SLMP_CMD;
   snd.partID = partID;  
   snd.resMode = resMode % COGN_LC_RET_NUM;	   
   if (snd.resMode == 0) snd.resMode = COGN_LC_ABS;   /* force default return */
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_LC_SND_OFFST, (void*) &snd, sizeof(COGN_LC_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_LC_MSC_Receive: receive LC message 
 *      
 *  Parameters: char *msg, COGN_LC_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_LC_MSC_Receive( const char *msg, COGN_LC_MSC_Rcv_t *rcv )
{
   size_t len = COGN_LC_RCV_OFFST + sizeof(COGN_LC_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_LC_RCV_OFFST, sizeof(COGN_LC_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTP :  wrapper for writing TP to message buffer 
 *                 ( you can add tcp send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint32_t partID, const uint16_t alignMode
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendTP( char *msg, const uint32_t partID, const uint16_t alignMode )
{
   API_GOGN_TP_MSC(msg,partID,alignMode);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseTP_AlignmentReply:  Parses the TP ascci response
 *      
 *  Parameters: const char* msg, COGN_TP_MSC_Rcv_t *pose
 *  Return: int16_t The result sTPtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseTP_MSC_AlignmentReply(const char* msg, COGN_TP_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"TP",2U))                                                  // message is TP = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	     case 2u:
	     pose->status = atoi(pch);
	     break;
				
             default:
             break;			  			  
           }
	   pch = strtok(NULL, ",");                                              /* get the neTP string in the line */   			  
       }
       ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP TP send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TP_MSC_Send: send TP message 
 *      
 *  Parameters: char *msg, const uint32_t partID, const uint16_t alignMode
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TP_MSC_Send( char *msg, const uint32_t partID, const uint16_t alignMode )
{
   COGN_TP_MSC_Snd_t snd; 
   size_t len = COGN_TP_SND_OFFST + sizeof(COGN_TP_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_TP_SLMP_CMD;
   snd.partID = partID;  
   snd.AlignMode = alignMode % 3;	   
   if (snd.AlignMode == 0) snd.AlignMode = 1;   /* force default return */
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_TP_SND_OFFST, (void*) &snd, sizeof(COGN_TP_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TP_MSC_Receive: receive TP message 
 *      
 *  Parameters: char *msg, COGN_TP_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TP_MSC_Receive( const char *msg, COGN_TP_MSC_Rcv_t *rcv )
{
   size_t len = COGN_TP_RCV_OFFST + sizeof(COGN_TP_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TP_RCV_OFFST, sizeof(COGN_TP_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendCP :  wrapper for writing CP to message buffer 
 *                 ( you can add tcp send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg,
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendCP( char *msg )
{
   API_GOGN_CP_MSC(msg);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseCP_AlignmentReply:  Parses the CP ascci response
 *      
 *  Parameters: const char* msg, COGN_CP_MSC_Rcv_t *pose
 *  Return: int16_t The result sCPtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseCP_MSC_AlignmentReply(const char* msg, COGN_CP_MSC_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"CP",2U))                                                  // message is CP = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
	      {			
	        case 2u:
	        pose->status = atoi(pch);
	        break;
				
            default:
            break;			  			  
	      }
	      pch = strtok(NULL, ",");                                              /* get the neCP string in the line */   			  
       }
	   ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP CP send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_CP_MSC_Send: send CP message 
 *      
 *  Parameters: char *msg, const uint16_t rStat
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_CP_MSC_Send( char *msg, const uint16_t rStat )
{
   COGN_CP_MSC_Snd_t snd; 
   size_t len = COGN_CP_SND_OFFST + sizeof(COGN_CP_MSC_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_CP_SLMP_CMD;
   snd.reqStat = rStat;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_CP_SND_OFFST, (void*) &snd, sizeof(COGN_CP_MSC_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_CP_MSC_Receive: receive CP message 
 *      
 *  Parameters: char *msg, COGN_CP_MSC_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_CP_MSC_Receive( const char *msg, COGN_CP_MSC_Rcv_t *rcv )
{
   size_t len = COGN_CP_RCV_OFFST + sizeof(COGN_CP_MSC_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_CP_RCV_OFFST, sizeof(COGN_CP_MSC_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendGS :  wrapper for writing GS to message buffer 
 *                 ( you can add tGS send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint8_t cam
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendGS( char *msg, const uint8_t cam )
{
   API_COGN_GS_SV(msg,cam);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseGS_AlignmentReply:  Parses the GS ascci response
 *      
 *  Parameters: const char* msg, COGN_GS_SV_Rcv_t *pose
 *  Return: int16_t The result sGStus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseGS_SV_AlignmentReply(const char* msg, COGN_GS_SV_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strings found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"GS",2U))                                                  // message is GS = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	        case 2u:
	        pose->status = atoi(pch);
	        break;
				
                default:
                break;			  			  
           }
	   pch = strtok(NULL, ",");                                              /* get the neGS string in the line */   			  
       }
       ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP GS send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_GS_SV_Send: send GS message 
 *      
 *  Parameters: char *msg, const uint16_t rStat
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GS_SV_Send( char *msg, const uint16_t cameraNo )
{
   COGN_GS_SV_Snd_t snd; 
   size_t len = COGN_GS_SND_OFFST + sizeof(COGN_GS_SV_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_GS_SLMP_CMD;
   snd.camera = cameraNo;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_GS_SND_OFFST, (void*) &snd, sizeof(COGN_GS_SV_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GS_SV_Receive: receive GS message 
 *      
 *  Parameters: char *msg, COGN_GS_SV_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GS_SV_Receive( const char *msg, COGN_GS_SV_Rcv_t *rcv )
{
   size_t len = COGN_GS_RCV_OFFST + sizeof(COGN_GS_SV_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_GS_RCV_OFFST, sizeof(COGN_GS_SV_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendGV :  wrapper for writing GV to message buffer 
 *                 ( you can add tGV send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint8_t cam
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendGV( char *msg, const uint8_t cam )
{
   API_COGN_GV_SV(msg,cam);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseGV_AlignmentReply:  Parses the GV ascci response
 *      
 *  Parameters: const char* msg, COGN_GV_SV_Rcv_t *pose
 *  Return: int16_t The result sGVtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseGV_SV_AlignmentReply(const char* msg, COGN_GV_SV_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strinGV found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp((char*)msg,"GV",2U))                                                  // message is GV = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	        case 2u:
	        pose->status = atoi(pch);
	        break;

	        case 3u:
	        pose->major = atol(pch);
	        break;

	        case 4u:
	        pose->minor = atol(pch);
	        break;

	        case 5u:
	        pose->subMinor = atol(pch);
	        break;
			
            default:
            break;			  			  
          }
	  pch = strtok(NULL, ",");                                              /* get the neGV string in the line */   			  
       }
       ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP GV send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_GV_SV_Send: send GV message 
 *      
 *  Parameters: char *msg, const uint16_t cameraNo
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GV_SV_Send( char *msg, const uint16_t cameraNo )
{
   COGN_GV_SV_Snd_t snd; 
   size_t len = COGN_GV_SND_OFFST + sizeof(COGN_GV_SV_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_GV_SLMP_CMD;
   snd.camera = cameraNo;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_GV_SND_OFFST, (void*) &snd, sizeof(COGN_GV_SV_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_GV_SV_Receive: receive GV message 
 *      
 *  Parameters: char *msg, COGN_GV_SV_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_GV_SV_Receive( const char *msg, COGN_GV_SV_Rcv_t *rcv )
{
   size_t len = COGN_GV_RCV_OFFST + sizeof(COGN_GV_SV_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_GV_RCV_OFFST, sizeof(COGN_GV_SV_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendPID :  wrapper for writing PID to message buffer 
 *                 ( you can add tPID send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint32_t prodID
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendPID( char *msg, const uint32_t prodID )
{
   API_COGN_PID_SV(msg,prodID);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParsePID_AlignmentReply:  Parses the PID ascci response
 *      
 *  Parameters: const char* msg, COGN_PID_SV_Rcv_t *pose
 *  Return: int16_t The result sPIDtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParsePID_SV_AlignmentReply(const char* msg, COGN_PID_SV_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strinPID found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp(msg,"PID",2U))                                                  // message is PID = 
    {
       pch = strtok((char*)msg,",");                                                   // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
	      {			
	        case 2u:
	        pose->status = atoi(pch);
	        break;
			
            default:
            break;			  			  
	      }
	      pch = strtok(NULL, ",");                                              /* get the nePID string in the line */   			  
       }
	   ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP PID send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_PID_SV_Send: send PID message 
 *      
 *  Parameters: char *msg, const uint32_t prodID
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_PID_SV_Send( char *msg, const uint32_t prodID )
{
   COGN_PID_SV_Snd_t snd; 
   size_t len = COGN_PID_SND_OFFST + sizeof(COGN_PID_SV_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_PID_SLMP_CMD;
   snd.prodID = prodID ;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_PID_SND_OFFST, (void*) &snd, sizeof(COGN_PID_SV_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_PID_SV_Receive: receive PID message 
 *      
 *  Parameters: char *msg, COGN_PID_SV_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_PID_SV_Receive( const char *msg, COGN_PID_SV_Rcv_t *rcv )
{
   size_t len = COGN_PID_RCV_OFFST + sizeof(COGN_PID_SV_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_PID_RCV_OFFST, sizeof(COGN_PID_SV_Rcv_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_SendTM :  wrapper for writing TM to message buffer 
 *                 ( you can add tTM send as you wish or just call the macro at top level )
 *      
 *  Parameters: char *msg, const uint32_t prodID, const uint8_t trigVal
 *  Return: void
 *----------------------------------------------------------------------------*/
void COGN_SendTM( char *msg, const uint32_t prodID, const uint8_t trigVal )
{
   uint8_t trig2send = trigVal % 2u;	
   API_COGN_TM_TRIG(msg,prodID,trig2send);
}

/*-----------------------------------------------------------------------------
 *  COGN_ParseTM_AlignmentReply:  Parses the TM ascci response
 *      
 *  Parameters: const char* msg, COGN_TM_TRIG_Rcv_t *pose
 *  Return: int16_t The result sTMtus 1: Success <=0: Fail
 *----------------------------------------------------------------------------*/
int16_t COGN_ParseTM_TRIG_AlignmentReply(const char* msg, COGN_TM_TRIG_Rcv_t *pose)
{
    char * pch = NULL;
    uint8_t itemNum = 0U, ret = 0U;                                             // number of strinTM found   
    uint32_t valueIn = 0UL;
	
    if (!strncmp(msg,"TM",2U))                                                  // message is TM = 
    {
       pch = strtok((char*)msg,",");                                            // split it by commas
       while (pch != NULL)
       {
          itemNum = ++itemNum % UINT8_MAX;
          switch(itemNum)
          {			
	        case 2u:
	        pose->status = atoi(pch);
	        break;
			
            default:
            break;			  			  
	  }
	  pch = strtok(NULL, ",");                                              /* get the neTM string in the line */   			  
       }
       ret = pose->status;
    }
    return ret;
}

/* ---------- SLMP TM send ------------------------------------ */

/*-----------------------------------------------------------------------------
 *  COGN_TM_TRIG_Send: send TM message 
 *      
 *  Parameters: char *msg, const uint32_t prodID, const uint16_t trigVal
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TM_TRIG_Send( char *msg, const uint32_t prodID, const uint16_t trigVal )
{
   COGN_TM_TRIG_Snd_t snd; 
   size_t len = COGN_TM_SND_OFFST + sizeof(COGN_TM_TRIG_Snd_t);
   uint8_t ret = -1;
	
   snd.cmdId = COGN_TM_SLMP_CMD;
   snd.prodID = prodID ;
   snd.trigger = trigVal % 2u;
   
   if (sizeof(msg) >= len) 
   {
       memcpy((void*) msg+COGN_TM_SND_OFFST, (void*) &snd, sizeof(COGN_TM_TRIG_Snd_t));
       ret = len;
   }
   return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_TM_TRIG_Receive: receive TM message 
 *      
 *  Parameters: char *msg, COGN_TM_TRIG_Rcv_t *rcv 
 *  Return: uint8_t
 *----------------------------------------------------------------------------*/
uint8_t COGN_TM_TRIG_Receive( const char *msg, COGN_TM_TRIG_Rcv_t *rcv )
{
   size_t len = COGN_TM_RCV_OFFST + sizeof(COGN_TM_TRIG_Rcv_t);
   uint8_t ret = -1;
   
   if (sizeof(msg) >= len)
   {
       memcpy((void*) rcv, (void*) msg+COGN_TM_RCV_OFFST, sizeof(COGN_TM_TRIG_Rcv_t));
       ret = len;
   }
   return ret;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
