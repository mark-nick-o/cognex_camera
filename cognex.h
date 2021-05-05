#ifndef _cognex_H
#define _cognex_H

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ============== COGNEX 3D Inspection Camera =============================== */
#if defined(COGNEX_CAM_USED)

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define COGPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define COGPACKED __attribute__((packed))                                     /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define COGPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define COGPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define COGPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif

#define COGN_MAX_SIZE_OF_RECIPE 50u                                             /* maximum number of caractures for recipe command */

typedef enum {
    COGN_Internal_error = -9999,
    COGN_Timeout = -1000,
    COGN_UnknownCommand = -1001,
    COGN_Index_out_of_range = -1002,
    COGN_Too_few_arguments = -1003,
    COGN_Invalid_argument_type = -1004,
    COGN_Invalid_argument = -1005,
    COGN_Command_not_allowed = -1006,
    COGN_Combination_not_allowed = -1007,
    COGN_Busy = -1008,
    COGN_Not_fully_implemented = -1009,
    COGN_Not_supported = -1010,
    COGN_Result_string_to_long = -1011,
    COGN_Invalid_camera_ID = -1012,
    COGN_Invalid_camera_feature_ID = -1013,
    COGN_Invalid_result_mode = -1014,	
    COGN_Invalid_LCheck_result_mode = -1015,	
    COGN_Invalid_arg_type_definition = -1018,
    COGN_Different_recipe_names = -1101,
    COGN_Different_versions = -1102,
    COGN_Not_calibrated = -2001,
    COGN_Calibration_failed = -2002,
    COGN_Invalid_calibration_data = -2003,
    COGN_Not_given_calibration_pose_reached = -2004, 
    COGN_No_start_command = -2005,
    COGN_Feature_not_trained = -3001,
    COGN_Feature_not_found = -3002,
    COGN_Feature_not_mapped = -3003,
    COGN_Part_pose_not_trained = -3004,
    COGN_Robot_pose_not_trained = -3005,
    COGN_No_GC_result_and_GCP_result_mode_does_not_work	= -3006,
    COGN_Invalid_part_ID = -4001,
    COGN_Not_all_features_located_for_this_part = -4002,
    COGN_No_valid_grip_correction_for_part = -4003,
    COGN_No_valid_frame_correction_for_part = -4004
} COGN_Error_Code_Returned_e;

#define COGN_WORD_LEN 2u                                                        /* wordf len is 2 bytes */
#define COGN_TA_SLMP_CMD 3010u
#define COGN_TA_SND_OFFST 2u*COGN_WORD_LEN                                      /* offset for memcpy */
#define COGN_TA_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
} COGN_TA_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;
    uint32_t partId;
}) COGN_TA_GP_Snd_t;                                                                
#endif

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* should be equal to COGN_TA_SLMP_CMD */
    uint8_t rcvStatus;
} COGN_TA_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;
    uint8_t rcvStatus;
}) COGN_TA_GP_Rcv_t;                                                                
#endif

#if defined(D_FT900)
typedef struct COGPACKED {
   uint32_t x;
   uint32_t y;
   uint32_t z;
} COGN_u32Vectr_t;
#else
COGPACKED(
typedef struct  {
   uint32_t x;
   uint32_t y;
   uint32_t z;
}) COGN_u32Vectr_t;                                                                
#endif

typedef enum { COGN_RET_ABS = 1, COGN_RET_OFF = 2, COGN_GP_RET_NUM } COGN_GP_Result_e;
typedef enum { COGN_LC_ABS = 1, COGN_LC_DIFF = 2, COGN_LC_REL = 3, COGN_LC_RET_NUM } COGN_LCResult_e;

#if defined(D_FT900)
typedef struct COGPACKED {
   COGN_u32Vectr_t coord;                                                       /* coordinate (absolute or offset) of the motion system’s destination pose. */
   COGN_u32Vectr_t rotat;                                                       /*  (absolute or offset) of the motion system’s destination pose */
   uint32_t score[2u];
   uint32_t LCResult;                                                           /* The L-Check result */
   uint8_t LCJudge;                                                             /* The L-Check judgement */
   uint32_t foundPartId;                                                        /* The PartID of the part that was successfully located. This can be the primary PartID or any backup PartID */
   uint32_t theta;
} COGN_pose_t;
#else
COGPACKED(
typedef struct  {
   COGN_u32Vectr_t coord;                                                       /* coordinate (absolute or offset) of the motion system’s destination pose. */
   COGN_u32Vectr_t rotat;                                                       /*  (absolute or offset) of the motion system’s destination pose */
   uint32_t score[2u];
   uint32_t LCResult;                                                           /* The L-Check result */
   uint8_t LCJudge;                                                             /* The L-Check judgement */
   uint32_t foundPartId;                                                        /* The PartID of the part that was successfully located. This can be the primary PartID or any backup PartID */
   uint32_t theta;
}) COGN_pose_t;                                                                
#endif

#define COGN_XA_SLMP_CMD 3011u
#define COGN_XA_SND_OFFST 2u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XA_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XA_GP_Snd_t;                                                                
#endif

#define COGN_XA_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XA_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XA_GP_Rcv_t;                                                                
#endif

#define COGN_XAS_SLMP_CMD 3012u
#define COGN_XAS_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XAS_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XAS_GP_Snd_t;                                                                
#endif

#define COGN_XAS_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
    uint32_t Score1;                                                            /* The current score of the target */
    uint32_t Score2;                                                            /* The current score of the 2nd feature. This applies only to parts that have 2 features */
} COGN_XAS_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
    uint32_t Score1;                                                            /* The current score of the target */
    uint32_t Score2;                                                            /* The current score of the 2nd feature. This applies only to parts that have 2 features */
}) COGN_XAS_GP_Rcv_t;                                                                
#endif

/* ================= Train Alignment “Golden Pose  =======================  */

/* --------------------- tcp/ip ascii send ---------------------------------  */
#define API_GOGN_TA_GP(X,partID)  do{ sprintf(X,"TA,%u",partID); } while(0)     /* The part to train the golden pose for. PartIDs depend on the recipe configuration */

/* --------------------- Execute “Golden Pose Alignment” -------------------  */
/* 
    X = char*, partId = uint32_t resultMode = COGN_GP_Result_e, 
    VectrCurrentPos = Vectr,  VectrRotatCurPos = Vectr 
*/
#define API_COGN_XA_GP(X, partID, resultMode, VectrCurrentPos, VectrRotatCurPos) \
 do                                                                             \
 {                                                                              \
    resultMode = resultMode % (COGN_GP_RET_NUM-1);                              \
    switch(resultMode)                                                          \
    {                                                                           \
        case COGN_RET_ABS:                                                      \
        sprintf(X,"XA,%u,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
                                                                                \
        case COGN_RET_OFF:                                                      \
        sprintf(X,"XA,%u,Off,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
                                                                                \
        default:                                                                \
        sprintf(X,"XA,%u,Off,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
    }                                                                           \
 } while(0)                                                                       

/* ================= Execute “Golden Pose Alignment” with Score ============  */

/* tcp/ip ascii send */

/* Execute “Golden Pose Alignment” with score */
/* X = char*, partId = uint32_t resultMode = COGN_GP_Result_e, VectrCurrentPos = Vectr,  VectrRotatCurPos = Vectr */
#define API_COGN_XAS_GP(X, partID, resultMode, VectrCurrentPos, VectrRotatCurPos) \
 do                                                                             \
 {                                                                              \
    resultMode = resultMode % (COGN_GP_RET_NUM-1);                              \
    switch(resultMode)                                                          \
    {                                                                           \
        case COGN_RET_ABS:                                                      \
        sprintf(X,"XAS,%u,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
                                                                                \
        case COGN_RET_OFF:                                                      \
        sprintf(X,"XAS,%u,Off,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
                                                                                \
        default:                                                                \
        sprintf(X,"XAS,%u,Off,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
        break;                                                                  \
    }                                                                           \
 } while(0)                                                                      

/* ================= Execute Alignment (with L-Check) ============  */

/* tcp/ip ascii send */

/* Execute “Golden Pose Alignment” with score */
/* X = char*, partId = uint32_t resultMode = COGN_GP_Result_e, VectrCurrentPos = Vectr,  VectrRotatCurPos = Vectr */
#define API_GOGN_XALC_GP(X, partID, resultMode, LCresultMode, VectrCurrentPos, VectrRotatCurPos) \
 do                                                                             \
 {                                                                              \
    resultMode = resultMode % (COGN_GP_RET_NUM-1);                              \
        switch(LCresultMode) \
        { \
        case COGN_LC_ABS: \
        switch(resultMode)                                                          \
        {                                                                           \
            case COGN_RET_ABS:                                                      \
            sprintf(X,"XALC,%u,Abs,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            case COGN_RET_OFF:                                                      \
            sprintf(X,"XALC,%u,Off,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            default:                                                                \
            sprintf(X,"XALC,%u,Off,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
        }                                                                        \
        break; \
                \
        case COGN_LC_DIFF: \
        switch(resultMode)                                                          \
        {                                                                           \
            case COGN_RET_ABS:                                                      \
            sprintf(X,"XALC,%u,Abs,Diff,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            case COGN_RET_OFF:                                                      \
            sprintf(X,"XALC,%u,Off,Diff,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            default:                                                                \
            sprintf(X,"XALC,%u,Off,Diff,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
        }                                                                        \
        break; \
                \
        case COGN_LC_REL: \
        switch(resultMode)                                                          \
        {                                                                           \
            case COGN_RET_ABS:                                                      \
            sprintf(X,"XALC,%u,Abs,Rel,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            case COGN_RET_OFF:                                                      \
            sprintf(X,"XALC,%u,Off,Rel,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            default:                                                                \
            sprintf(X,"XALC,%u,Off,Rel,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
        }                                                                        \
        break; \
        default: \
        break; \
    }    \
 } while(0)                                                                       

                      
/* ====================== SLMP data send ===================================  */
#define COGN_XALC_SLMP_CMD 3013u
#define COGN_XALC_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t LCMode;                                                            /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XALC_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t LCMode;                                                            /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XALC_GP_Snd_t;                                                                
#endif

#define COGN_XALC_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
    uint32_t LCResult;                                                          /* The L-Check result. */
    uint32_t LCJudge;                                                           /* The L-Check judgement result 1=pass 0=fail */
} COGN_XALC_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
    uint32_t LCResult;                                                          /* The L-Check result. */
    uint32_t LCJudge;                                                           /* The L-Check judgement result 1=pass 0=fail */
}) COGN_XALC_GP_Rcv_t;                                                                
#endif

/* ================= Execute Alignment with backup pattern (Multi-Pattern mode) ============  */

/* tcp/ip ascii send */

/* Execute Alignment with backup pattern (Multi-Pattern mode) */
/* X = char*, partId = uint32_t resultMode = COGN_GP_Result_e, VectrCurrentPos = Vectr,  VectrRotatCurPos = Vectr */
#define API_GOGN_XAMP_GP(X, partID, resultMode, VectrCurrentPos, VectrRotatCurPos) \
 do                                                                             \
 {                                                                              \
    resultMode = resultMode % (COGN_GP_RET_NUM-1);                              \
    switch(resultMode)                                                          \
    {                                                                           \
            case COGN_RET_ABS:                                                      \
            sprintf(X,"XAMP,%u,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            case COGN_RET_OFF:                                                      \
            sprintf(X,"XAMP,%u,Off,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
                                                                                \
            default:                                                                \
            sprintf(X,"XAMP,%u,Abs,%d,%d,%d,%d,%d,%d",partID,VectrCurrentPos.x,VectrCurrentPos.y,VectrCurrentPos.z,VectrRotatCurPos.z,VectrRotatCurPos.y,VectrRotatCurPos.x); \
            break;                                                                  \
        }                                                                        \
 } while(0)                                                                       

                      
/* ====================== SLMP data send ===================================  */
#define COGN_XAMP_SLMP_CMD 3014u
#define COGN_XAMP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XAMP_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t partId;
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XAMP_GP_Snd_t;                                                                
#endif

#define COGN_XAMP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t foundPartId;                                                       /* The PartID of the part that was successfully located. This can be the primary PartID or any backup PartID. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XAMP_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TA_SLMP_CMD at initialisation */
    uint32_t mode;                                                              /* The requested result mode */
    uint32_t foundPartId;                                                       /* The PartID of the part that was successfully located. This can be the primary PartID or any backup PartID. */        
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XAMP_GP_Rcv_t;                                                                
#endif

/* ================= Set Golden Pose ============  */

/* tcp/ip ascii send */

/* Set Golden Pose */
#define API_GOGN_SGP_GP(X,stepID,coord,pose)  do{ sprintf(X,"SGP,%u,%d,%d,%d,%d",stepID,coord,pose.coord.x,pose.coord.y,pose.theta); } while(0) 
 
/* ====================== SLMP data send ===================================  */
#define COGN_SGP_SLMP_CMD 3020u
#define COGN_SGP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_SGP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
    uint32_t X;                                                                  /* X-coordinate of the Golden Pose in the selected coordinate system */
    uint32_t Y;                                                                  /* Y-coordinate of the Golden Pose in the selected coordinate system */
    uint32_t Theta;                                                              /* Theta of the Golden Pose */
} COGN_SGP_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_SGP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
    uint32_t X;                                                                  /* X-coordinate of the Golden Pose in the selected coordinate system */
    uint32_t Y;                                                                  /* Y-coordinate of the Golden Pose in the selected coordinate system */
    uint32_t Theta;                                                              /* Theta of the Golden Pose */
}) COGN_SGP_GP_Snd_t;                                                                
#endif

#define COGN_SGP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
} COGN_SGP_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
}) COGN_SGP_GP_Rcv_t;                                                                
#endif

typedef enum {
    Home2D = 1,
    Cam2D = 2,
    Raw2D = 3
} COGN_coord_e;

/* ================= Get Golden Pose ============  */

/* tcp/ip ascii send */

/* Get Golden Pose */
#define API_GOGN_GCP_GP(X, stepID, coord) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"GGP,%u,%d",stepID,coord);  } while(0)                                                                          
                                                                       

                      
/* ====================== SLMP data send ===================================  */
#define COGN_GCP_SLMP_CMD 3021u
#define COGN_GCP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_GCP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
} COGN_GCP_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_GCP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
}) COGN_GCP_GP_Snd_t;                                                                
#endif

#define COGN_GCP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_GCP_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t x;
    uint32_t y;
    uint32_t theta;
} COGN_GCP_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_GCP_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t x;
    uint32_t y;
    uint32_t theta;
}) COGN_GCP_GP_Rcv_t;                                                                
#endif

/* ================= Get Current Pose ======================================  */

/* tcp/ip ascii send */

/* Get Current Pose */
#define API_GOGN_GCCP_GP(X, stepID, coord, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"GCP,%u,%d,%d,%d,%d,%d,%d,%d",stepID,coord,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0) 
                                                                                            
/* ====================== SLMP data send ===================================  */
#define COGN_GCCP_SLMP_CMD 3022u
#define COGN_GCCP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_GCCP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_GCCP_GP_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_GCCP_SLMP_CMD at initialisation */
    uint32_t stepId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t coord;
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_GCCP_GP_Snd_t;                                                                
#endif

#define COGN_GCCP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_GCCP_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t x;
    uint32_t y;
    uint32_t theta;
} COGN_GCCP_GP_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_GCCP_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t x;
    uint32_t y;
    uint32_t theta;
}) COGN_GCCP_GP_Rcv_t;                                                                
#endif

/* Train Part Pose --- Train the part pose. A corresponding robot pose (pick or place) must be trained using the TTR command */

#define API_GOGN_TT_VGR(X, partID, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"TT,%u,%d,%d,%d,%d,%d,%d,%d",partID,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_TT_SLMP_CMD 4010u
#define COGN_TT_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_TT_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_TT_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_TT_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_TT_VGR_Snd_t;                                                                
#endif

#define COGN_TT_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TT_SLMP_CMD at initialisation */
    uint16_t result;
} COGN_TT_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TT_SLMP_CMD at initialisation */
    uint16_t result;
}) COGN_TT_VGR_Rcv_t;                                                                
#endif


/* Train Robot Pose --- Train the robot pick (or place) pose. A corresponding part pose must be trained using the TT command. */

#define API_GOGN_TTR_VGR(X, partID, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"TTR,%u,%d,%d,%d,%d,%d,%d,%d",partID,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_TTR_SLMP_CMD 4011u
#define COGN_TTR_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_TTR_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_TTR_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_TTR_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_TTR_VGR_Snd_t;                                                                
#endif

#define COGN_TTR_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_TTR_SLMP_CMD at initialisation */
    uint16_t result;
} COGN_TTR_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_TTR_SLMP_CMD at initialisation */
    uint16_t result;
}) COGN_TTR_VGR_Rcv_t;                                                                
#endif


/* Execute Pick or Place Alignment --- Locate the part and get the corrected robot pick (or place) pose. */

typedef enum { COGN_VGR_RET_ABS = 1, COGN_VGR_RET_OFF = 2, COGN_VGR_RET_FRAME = 3, COGN_VGR_RET_GC = 4, COGN_VGR_RET_GCP = 5, COGN_VGR_RET_NUM } COGN_VGR_Result_e;

#define API_GOGN_XT_VGR(X, partID, resMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"XT,%u,%d,%d,%d,%d,%d,%d,%d,%d",partID,resMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_XT_SLMP_CMD 4012u
#define COGN_XT_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XT_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XT_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XT_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XT_VGR_Snd_t;                                                                
#endif

#define COGN_XT_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XT_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t curPosX;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX;                                                              /* The X-rotation of the result pose (absolute or offset) */
} COGN_XT_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XT_SLMP_CMD at initialisation */
    uint16_t result;
    uint32_t curPosX;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX;                                                              /* The X-rotation of the result pose (absolute or offset) */
}) COGN_XT_VGR_Rcv_t;                                                                
#endif


/* Execute Pick or Place Alignment (2 Parts) --- Locate two parts at a time and return pick or place pose for both */

#define API_GOGN_XT2_VGR(X, partID, resMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"XT2,%u,%d,%d,%d,%d,%d,%d,%d,%d",partID,resMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_XT2_SLMP_CMD 4012u
#define COGN_XT2_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XT2_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XT2_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XT2_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XT2_VGR_Snd_t;                                                                
#endif

#define COGN_XT2_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XT2_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
    uint16_t result2;
    uint32_t curPosX2;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY2;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ2;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ2;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY2;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX2;                                                              /* The X-rotation of the result pose (absolute or offset) */
} COGN_XT2_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XT2_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
    uint16_t result2;
    uint32_t curPosX2;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY2;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ2;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ2;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY2;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX2;                                                              /* The X-rotation of the result pose (absolute or offset) */
}) COGN_XT2_VGR_Rcv_t;                                                                
#endif


/* Execute Pick or Place alignment with Score ==== Locate the part and get the corrected robot pick (or place) pose and the score of the feature */

#define API_GOGN_XTS_VGR(X, partID, resMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"XTS,%u,%d,%d,%d,%d,%d,%d,%d,%d",partID,resMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_XTS_SLMP_CMD 4013u
#define COGN_XTS_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XTS_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XTS_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XTS_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XTS_VGR_Snd_t;                                                                
#endif

#define COGN_XTS_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XTS_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                          /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                          /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                          /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                             /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                             /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                             /* The X-rotation of the result pose (absolute or offset) */
    uint16_t score1;                                                            /* The current score of the feature  */
    uint32_t score2;                                                            /* The current score of the 2nd feature. This applies only to parts that have 2 features */
} COGN_XTS_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XTS_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                          /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                          /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                          /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                             /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                             /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                             /* The X-rotation of the result pose (absolute or offset) */
    uint16_t score1;                                                            /* The current score of the feature  */
    uint32_t score2;                                                            /* The current score of the 2nd feature. This applies only to parts that have 2 features */
}) COGN_XTS_VGR_Rcv_t;                                                                
#endif


/* Execute Pick or Place alignment with Score ==== Locate the part and get the corrected robot pick (or place) pose and the score of the feature */

#define API_GOGN_XTLC_VGR(X, partID, resMode, lcRes, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"XTLC,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d",partID,resMode,lcRes,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_XTLC_SLMP_CMD 4014u
#define COGN_XTLC_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XTLC_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
        uint32_t LCResultMode;                                                      /* Specifies how the L-Check result shall be returned: */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XTLC_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XTLC_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
        uint32_t LCResultMode;                                                      /* Specifies how the L-Check result shall be returned: */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XTLC_VGR_Snd_t;                                                                
#endif

#define COGN_XTLC_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XTLC_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
    uint32_t LCResult;                                                           /* The L_Check result */
    uint32_t LCJudge;                                                           /* The L-Check judgemen 1=ok */
} COGN_XTLC_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XTLC_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
    uint32_t LCResult;                                                           /* The L_Check result */
    uint32_t LCJudge;                                                           /* The L-Check judgemen 1=ok */
}) COGN_XTLC_VGR_Rcv_t;                                                                
#endif

/* Execute Pick or Place alignment with backup pattern (Multi-Pattern) ==== Multi-Pattern mode allows to specify backup patterns (PartIDs). If the primary part has not been found, the system will automatically try to locate the backup parts instead in order to produce a valid alignment result. When EncodedPartID is provided on a command argument, all PartID settings on the HMI are ignored. If EncodedPartID = 0 is used with no PartID setting on the HMI, error code: -4001 (invalid Part ID) is returned. */

#define API_GOGN_XTMP_VGR(X, partID, resMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"XTMP,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d",partID,resMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_XTMP_SLMP_CMD 4015u
#define COGN_XTMP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XTMP_VGR_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint32_t partId;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XTMP_VGR_Snd_t;                                                                
#endif

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint32_t primaryPartId : 4u;                                                 /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo1PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo2PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo3PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t spare : 16u;                                                        /* spare bits */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_XTMP_VGR_Snd2_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint32_t primaryPartId : 4u;                                                 /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo1PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo2PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo3PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t spare : 16u;                                                        /* spare bits */
    uint32_t resMode;                                                             /* Specifies how the result will be returned type : COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_XTMP_VGR_Snd2_t;                                                                
#endif

#define COGN_XTMP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t partId;                                                             /* Part Id of primary and backup parts */
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
} COGN_XTMP_VGR_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t partId;                                                             /* Part Id of primary and backup parts */
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
}) COGN_XTMP_VGR_Rcv_t;                                                                
#endif

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t primaryPartId : 4u;                                                 /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo1PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo2PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo3PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t spare : 16u;                                                        /* spare bits */
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
} COGN_XTMP_VGR_Rcv2_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_XTMP_SLMP_CMD at initialisation */
    uint16_t result1;
    uint32_t primaryPartId : 4u;                                                 /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo1PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo2PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t backupNo3PartId : 4u;                                               /* The PartID of the primary and backup part(s) to locate. PartIDs depend on the recipe configuration */
    uint32_t spare : 16u;                                                        /* spare bits */
    uint32_t curPosX1;                                                           /* The X-coordinate of the result pose (absolute or offset) */
    uint32_t curPosY1;                                                           /* The Y-coordinate of the result pose (absolute or offset)*/
    uint32_t curPosZ1;                                                           /* The Z-coordinate of the result pose (absolute or offset) */
    uint32_t rotZ1;                                                              /* The Z-rotation of the result pose (absolute or offset) */
    uint32_t rotY1;                                                              /* The Y-rotation of the result pose (absolute or offset) */
    uint32_t rotX1;                                                              /* The X-rotation of the result pose (absolute or offset) */
}) COGN_XTMP_VGR_Rcv2_t;                                                                
#endif


/* Locate Features ==== Locates the features of a part and stores the feature poses in the internal feature table. Which features to be located is specified with the StepID argument */

#define API_GOGN_LF_MSC(X, stepId, prodID, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"LF,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d",stepID,prodID,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_LF_SLMP_CMD 5011u
#define COGN_LF_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_LF_SLMP_CMD at initialisation */
    uint32_t stepID;                                                            /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t prodID;                                                            /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_LF_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_LF_SLMP_CMD at initialisation */
    uint32_t stepID;                                                            /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t prodID;                                                            /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_LF_MSC_Snd_t;                                                                
#endif

#define COGN_LF_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
    uint32_t token;
    uint32_t prodID;
} COGN_LF_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
    uint32_t token;
    uint32_t prodID;
}) COGN_LF_MSC_Rcv_t;                                                                
#endif


/* Train Motion Pose ==== Trains the motion pose that corresponds to the feature poses that were trained by the TP command. This command is required for shuttling part configurations or for AlignMode 2 applications. */

#define API_GOGN_TPR_MSC(X, partID, AlignMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"TPR,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d",partID,AlignMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_TPR_SLMP_CMD 5013u
#define COGN_TPR_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_TPR_SLMP_CMD at initialisation */
        uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t AlignMode;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_TPR_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_TPR_SLMP_CMD at initialisation */
        uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t AlignMode;                                                             /* Only steps containing a single feature can be selected here. */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_TPR_MSC_Snd_t;                                                                
#endif

#define COGN_TPR_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
} COGN_TPR_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
}) COGN_TPR_MSC_Rcv_t;                                                                
#endif


/* Get Pose ==== Gets the motion pose required to align the part with its golden pose. The pose is the current motion posed based on the features found using LF command */

#define API_GOGN_GP_MSC(X, partID, AlignMode, resultMode, pose) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"GP,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",partID,AlignMode,resultMode,pose.coord.x,pose.coord.y,pose.coord.z,pose.rotat.z,pose.rotat.y,pose.rotat.x);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_GP_SLMP_CMD 5014u
#define COGN_GP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_GP_SLMP_CMD at initialisation */
    uint32_t partID;                                                            /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t AlignMode;                                                         /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                           /* COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
} COGN_GP_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_GP_SLMP_CMD at initialisation */
    uint32_t partID;                                                            /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t AlignMode;                                                         /* Only steps containing a single feature can be selected here. */
    uint32_t resMode;                                                           /* COGN_VGR_Result_e */
    uint32_t curPosX;                                                           /* The X-coordinate of the current position of the motion system */
    uint32_t curPosY;                                                           /* The Y-coordinate of the current position of the motion system */
    uint32_t curPosZ;                                                           /* The Z-coordinate of the current position of the motion system */
    uint32_t rotZ;                                                              /* The Z-rotation of the current position of the motion system */
    uint32_t rotY;                                                              /* The Y-rotation of the current position of the motion system */
    uint32_t rotX;                                                              /* The X-rotation of the current position of the motion system */
}) COGN_GP_MSC_Snd_t;                                                                
#endif

#define COGN_GP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
        uint32_t x;
        uint32_t y;
        uint32_t z;        
        uint32_t az;
        uint32_t by;
        uint32_t cx;
} COGN_GP_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                             /* set to COGN_SGP_SGP_CMD at initialisation */
    uint16_t result;
        uint32_t x;
        uint32_t y;
        uint32_t z;        
        uint32_t az;
        uint32_t by;
        uint32_t cx;
}) COGN_GP_MSC_Rcv_t;                                                                
#endif


/* L-Check ==== L-Check compares the runtime-distance between the two features of the part with the traintime distance. A big deviation may suggest that incorrect features have been located. Pass/fail results are judged based on the threshold specified on the HMI by comparing against the training feature distance (TA, TT commands) */

#define API_GOGN_LC_MSC(X, partID, resultMode) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"LC,%u,%d",partID,resultMode);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_LC_SLMP_CMD 5015u
#define COGN_LC_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_LC_SLMP_CMD at initialisation */
    uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t resMode;                                                            /* COGN_VGR_Result_e */
} COGN_LC_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_LC_SLMP_CMD at initialisation */
    uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint32_t resMode;                                                            /*  COGN_VGR_Result_e */
}) COGN_LC_MSC_Snd_t;                                                                
#endif

#define COGN_LC_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
    uint32_t result;
    uint16_t LCJudge;
} COGN_LC_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
    uint32_t result;
    uint16_t LCJudge;
}) COGN_LC_MSC_Rcv_t;                                                                
#endif


/* Train Part Pose ==== Trains the golden pose for the part located by previously executed “LF” command(s)  */

#define API_GOGN_TP_MSC(X, partID, alignMode) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"TP,%u,%d",partID,alignMode);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_TP_SLMP_CMD 5012u
#define COGN_TP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                              /* set to COGN_TP_SLMP_CMD at initialisation */
    uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint16_t AlignMode;                                                         
} COGN_TP_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                              /* set to COGN_TP_SLMP_CMD at initialisation */
    uint32_t partID;                                                             /* Selects the step to execute. Which features are to be located in a specific step depends on the recipe configuration */
    uint16_t AlignMode;                                                         
}) COGN_TP_MSC_Snd_t;                                                                
#endif

#define COGN_TP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
} COGN_TP_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
}) COGN_TP_MSC_Rcv_t;                                                                
#endif


/* Clear Positions ==== Clears the runtime feature locations in the internal feature table. This command should be used at the beginning of a cycle. It prevents a part pose from being computed using feature locations from a previous cycle.  */

#define API_GOGN_CP_MSC(X) \
 do                                                                             \
 {                                                                              \
     strcpy((char*)X,(char*)"CP");  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_CP_SLMP_CMD 5010u
#define COGN_CP_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t reqStat;                                                           /* Argument0: the requested status */                                                        
} COGN_CP_MSC_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                            
    uint16_t reqStat;                                                           /* Argument0: the requested status */                                                       
}) COGN_CP_MSC_Snd_t;                                                                
#endif

#define COGN_CP_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
} COGN_CP_MSC_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
}) COGN_CP_MSC_Rcv_t;                                                                
#endif


/* Get State ==== Returns the current State  */

#define API_COGN_GS_SV(X,cam) \
 do                                                                             \
 {                                                                              \
     sprintf(X,"GS,%u",cam);  } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_GS_SLMP_CMD 1010u
#define COGN_GS_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memGSy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t camera;                                                             /* Argument0: the requested status */                                                        
} COGN_GS_SV_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                            
    uint16_t camera;                                                             /* Argument0: the requested status */                                                       
}) COGN_GS_SV_Snd_t;                                                                
#endif

#define COGN_GS_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memGSy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
} COGN_GS_SV_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
}) COGN_GS_SV_Rcv_t;                                                                
#endif

/* Get Version ==== Returns the current version of the loaded recipe.  */

#define API_COGN_GV_SV(X,cam)  do{ sprintf(X,"GV,%u",cam); } while(0)

/* ====================== SLMP data send ===================================  */
#define COGN_GV_SLMP_CMD 1011u
#define COGN_GV_SND_OFFST 2u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t camera;                                                            /* Argument0: the requested status */                                                        
} COGN_GV_SV_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                            
    uint16_t camera;                                                            /* Argument0: the requested status */                                                       
}) COGN_GV_SV_Snd_t;                                                                
#endif

#define COGN_GV_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
    uint32_t major;
    uint32_t minor;
    uint32_t subMinor;
} COGN_GV_SV_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
    uint32_t major;
    uint32_t minor;
    uint32_t subMinor;
}) COGN_GV_SV_Rcv_t;                                                                
#endif


/* Set Product ID ==== Sets the product ID which is used as a prefix for the image filename in image logging  */

#define API_COGN_PID_SV(X,cam)  do{ sprintf(X,"PID,%u",cam); } while(0)
	
/* ====================== SLMP data send ===================================  */
#define COGN_PID_SLMP_CMD 5050u
#define COGN_PID_SND_OFFST 2u*COGN_WORD_LEN                                     /* offset for memPIDy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint32_t prodID;                                                            /* product ID */                                                        
} COGN_PID_SV_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                            
    uint32_t prodID;                                                            /* product ID */                                                     
}) COGN_PID_SV_Snd_t;                                                                
#endif

#define COGN_PID_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
} COGN_PID_SV_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
}) COGN_PID_SV_Rcv_t;                                                                
#endif


/* Trigger Mode ==== Switches the hardware trigger on/off.  */

#define API_COGN_TM_TRIG(X,cam,trig)  do{ sprintf(X,"TM,%u,%d",cam,trig); } while(0)
	
/* ====================== SLMP data send ===================================  */
#define COGN_TM_SLMP_CMD 1050u
#define COGN_TM_SND_OFFST 2u*COGN_WORD_LEN                                      /* offset for memTMy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t prodID;       	                                                /* product ID */ 
    uint16_t trigger; 	
} COGN_TM_TRIG_Snd_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                            
    uint16_t prodID;                                                    	/* product ID */
    uint16_t trigger;	
}) COGN_TM_TRIG_Snd_t;                                                                
#endif

#define COGN_TM_RCV_OFFST 5u*COGN_WORD_LEN                                      /* offset for memcpy */

#if defined(D_FT900)
typedef struct COGPACKED {
    uint16_t cmdId;                                                            
    uint16_t status;
} COGN_TM_TRIG_Rcv_t;
#else
COGPACKED(
typedef struct  {
    uint16_t cmdId;                                                           
    uint16_t status;
}) COGN_TM_TRIG_Rcv_t;                                                                
#endif

/* -------------------- Command Strings ------------------------------------  */
extern void COGN_SendTA( char *msg, const uint32_t partID );
extern uint8_t COGN_ParseTA_AlignmentReply(char* msg);

/* -------------------- SLMP -----------------------------------------------  */
extern uint8_t COGN_TA_GP_Send( char *msg, const uint32_t partId );
extern uint8_t COGN_TA_GP_Receive( char *msg, COGN_TA_GP_Rcv_t *rcv );

/* --------------------- GoldenPose ----------------------------------------  */
/* -------------------- Command Strings ------------------------------------  */
extern void COGN_SendXA( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
extern void COGN_SendXAS( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
extern void COGN_SendXALC( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode, COGN_LCResult_e LCresultMode );
extern void COGN_SendXAMP( char *msg, const uint32_t partID, const COGN_u32Vectr_t currentPosn, const COGN_u32Vectr_t rotateCurrentPosn, COGN_GP_Result_e resultMode );
extern void COGN_SendSGP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose );

extern uint8_t COGN_ParseGP_AlignmentReply( char* msg, COGN_pose_t *pose );
extern uint8_t COGN_ParseSGP_AlignmentReply(char* msg);
/* -------------------- SLMP -----------------------------------------------  */
extern uint8_t COGN_XA_GP_Receive( char *msg, COGN_XA_GP_Rcv_t *rcv );
extern uint8_t COGN_XA_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
extern uint8_t COGN_XAS_GP_Receive( char *msg, COGN_XAS_GP_Rcv_t *rcv );
extern uint8_t COGN_XAS_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
extern uint8_t COGN_XALC_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, COGN_LCResult_e LCresultMode, const uint32_t partId );
extern uint8_t COGN_XALC_GP_Receive( char *msg, COGN_XALC_GP_Rcv_t *rcv );
extern uint8_t COGN_XAMP_GP_Send( char *msg, const COGN_pose_t *pose, COGN_GP_Result_e mode, const uint32_t partId );
extern uint8_t COGN_XAMP_GP_Receive( char *msg, COGN_XAMP_GP_Rcv_t *rcv );
extern uint8_t COGN_SGP_GP_Send( char *msg, const COGN_pose_t *pose, const uint32_t stepId, COGN_coord_e cord );
extern uint8_t COGN_SGP_GP_Receive( char *msg, COGN_SGP_GP_Rcv_t *rcv );

extern uint8_t COGN_GCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord );
extern uint8_t COGN_GCP_GP_Receive( char *msg, COGN_GCP_GP_Rcv_t *rcv );
extern void COGN_SendGCP( char *msg, const uint32_t stepID, const uint32_t coord );

extern void COGN_SendGCCP( char *msg, const uint32_t stepID, const uint32_t coord, const COGN_pose_t pose );
extern uint8_t COGN_GCCP_GP_Send( char *msg, const uint32_t stepId, COGN_coord_e cord, const COGN_pose_t pose );
extern uint8_t COGN_GCCP_GP_Receive( char *msg, COGN_GCCP_GP_Rcv_t *rcv );

extern uint8_t COGN_ParseGCP_AlignmentReply(char* msg, COGN_GCP_GP_Rcv_t *poseRead);

extern void COGN_SendTT( char *msg, const uint32_t partID, const COGN_pose_t pose );
extern uint8_t COGN_ParseTT_AlignmentReply(char* msg);
extern uint8_t COGN_TT_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose );
extern uint8_t COGN_TT_VGR_Receive( const char *msg, COGN_TT_VGR_Rcv_t *rcv );
extern void COGN_SendTTR( char *msg, const uint32_t partID, const COGN_pose_t pose );
extern uint8_t COGN_ParseTTR_AlignmentReply(char* msg);
extern uint8_t COGN_TTR_VGR_Send( char *msg, const uint32_t partId, const COGN_pose_t *pose );
extern uint8_t COGN_TTR_VGR_Receive( const char *msg, COGN_TT_VGR_Rcv_t *rcv );

extern int8_t COGN_SendXT( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );
extern uint8_t COGN_ParseXT_AlignmentReply(const char* msg, COGN_pose_t *pose);
extern uint8_t COGN_XT_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
extern uint8_t COGN_XT_VGR_Receive( const char *msg, COGN_XT_VGR_Rcv_t *rcv );

extern uint8_t COGN_XT2_VGR_Receive( const char *msg, COGN_XT2_VGR_Rcv_t *rcv );
extern uint8_t COGN_XT2_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
extern uint8_t COGN_ParseXT2_AlignmentReply(const char* msg, COGN_XT2_VGR_Rcv_t *pose);
extern int8_t COGN_SendXT2( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

extern uint8_t COGN_XTS_VGR_Receive( const char *msg, COGN_XTS_VGR_Rcv_t *rcv );
extern uint8_t COGN_XTS_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
extern uint8_t COGN_ParseXTS_AlignmentReply( const char* msg, COGN_XTS_VGR_Rcv_t *pose );
extern int8_t COGN_SendXTS( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

extern uint8_t COGN_XTLC_VGR_Receive( const char *msg, COGN_XTLC_VGR_Rcv_t *rcv );
extern uint8_t COGN_XTLC_VGR_Send( char *msg, const uint32_t partId, COGN_VGR_Result_e resMode, COGN_LCResult_e lcRes, const COGN_pose_t *pose );
extern uint8_t COGN_ParseXTLC_AlignmentReply(const char* msg, COGN_XTLC_VGR_Rcv_t *pose);
extern int8_t COGN_SendXTLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const COGN_pose_t pose );

extern void COGN_SendLF( char *msg, const uint32_t stepID, const uint32_t prodID, const COGN_pose_t pose );
extern uint8_t COGN_ParseLF_AlignmentReply( const char* msg, COGN_LF_MSC_Rcv_t *pose );
extern uint8_t COGN_LF_MSC_Send( char *msg, const uint32_t stepId, const COGN_pose_t *pose );
extern uint8_t COGN_LF_MSC_Receive( const char *msg, COGN_LF_MSC_Rcv_t *rcv );

extern uint8_t COGN_TPR_MSC_Receive( const char *msg, COGN_TPR_MSC_Rcv_t *rcv );
extern uint8_t COGN_TPR_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t *pose );
extern uint8_t COGN_ParseTPR_AlignmentReply(const char* msg, COGN_TPR_MSC_Rcv_t *pose);
extern void COGN_SendTPR( char *msg, const uint32_t partID, const uint32_t align, const COGN_pose_t pose );

extern uint8_t COGN_LC_MSC_Receive( const char *msg, COGN_LC_MSC_Rcv_t *rcv );
extern uint8_t COGN_LC_MSC_Send( char *msg, const uint32_t partID, COGN_LCResult_e resMode );
extern int16_t COGN_ParseLC_MSC_AlignmentReply(const char* msg, COGN_LC_MSC_Rcv_t *pose);
extern void COGN_SendLC( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode );

extern uint8_t COGN_GP_MSC_Receive( const char *msg, COGN_GP_MSC_Rcv_t *rcv );
extern uint8_t COGN_GP_MSC_Send( char *msg, const uint32_t partID, const uint32_t align, COGN_VGR_Result_e resMode, const COGN_pose_t *pose );
extern int16_t COGN_ParseGP_MSC_AlignmentReply(const char* msg, COGN_GP_MSC_Rcv_t *pose);
extern void COGN_SendGP( char *msg, const uint32_t partID, COGN_VGR_Result_e resMode, const uint32_t align, const COGN_pose_t pose );

extern uint8_t COGN_TP_MSC_Receive( const char *msg, COGN_TP_MSC_Rcv_t *rcv );
extern uint8_t COGN_TP_MSC_Send( char *msg, const uint32_t partID, const uint16_t alignMode );
extern void COGN_SendTP( char *msg, const uint32_t partID, const uint16_t alignMode );
extern int16_t COGN_ParseTP_MSC_AlignmentReply(const char* msg, COGN_TP_MSC_Rcv_t *pose);

extern void COGN_SendCP( char *msg );
extern int16_t COGN_ParseCP_MSC_AlignmentReply(const char* msg, COGN_CP_MSC_Rcv_t *pose);
extern uint8_t COGN_CP_MSC_Send( char *msg, const uint16_t rStat );
extern uint8_t COGN_CP_MSC_Receive( const char *msg, COGN_CP_MSC_Rcv_t *rcv );

extern void COGN_SendGS( char *msg, const uint8_t cam );
extern int16_t COGN_ParseGS_SV_AlignmentReply(const char* msg, COGN_GS_SV_Rcv_t *pose);
extern uint8_t COGN_GS_SV_Send( char *msg, const uint16_t cameraNo );
extern uint8_t COGN_GS_SV_Receive( const char *msg, COGN_GS_SV_Rcv_t *rcv );

extern void COGN_SendGV( char *msg, const uint8_t cam );
extern int16_t COGN_ParseGV_SV_AlignmentReply(const char* msg, COGN_GV_SV_Rcv_t *pose);
extern uint8_t COGN_GV_SV_Send( char *msg, const uint16_t cameraNo );
extern uint8_t COGN_GV_SV_Receive( const char *msg, COGN_GV_SV_Rcv_t *rcv );

extern void COGN_SendPID( char *msg, const uint32_t prodID );
extern int16_t COGN_ParsePID_SV_AlignmentReply(const char* msg, COGN_PID_SV_Rcv_t *pose);
extern uint8_t COGN_PID_SV_Send( char *msg, const uint32_t prodID );
extern uint8_t COGN_PID_SV_Receive( const char *msg, COGN_PID_SV_Rcv_t *rcv );

extern void COGN_SendTM( char *msg, const uint32_t prodID, const uint8_t trigVal );
extern int16_t COGN_ParseTM_TRIG_AlignmentReply(const char* msg, COGN_TM_TRIG_Rcv_t *pose);
extern uint8_t COGN_TM_TRIG_Send( char *msg, const uint32_t prodID, const uint16_t trigVal );
extern uint8_t COGN_TM_TRIG_Receive( const char *msg, COGN_TM_TRIG_Rcv_t *rcv );

#endif /* end cognex camera */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end library 
