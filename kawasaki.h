#ifndef __kawa_robot_
#define __kawa_robot_

#include <stdint.h>
#include "Struts.h"
#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __GNUC__                                                                 /* Macro to define packed structures the mikroe compiler is gcc based in definitions.h */
  #define KAWAPACKED( __Declaration__ ) __Declaration__ __attribute__((packed)) ALIGNED(1)
#elif (defined(D_FT900) || defined(__TI_ARM__))                                 /* mikroe FT900 C or TI ref http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_xxq1474359912082.htm */
  #define KAWAPACKED __attribute__((packed))                                    /* keil arm can also use #pragma pack(1) to pack to byte boundaries #pragma pack(4) to align to 4 byte boundaries */
#elif (defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__))                       /* Keil MDK-ARM compiler ? or IAR C compiler */
  #define KAWAPACKED __packed
#elif (defined(_WIN32) || defined(__CWCC__))                                    /* windows or code warrior */
  #define KAWAPACKED
#else                                                                           /* for MPLAB PIC32 */
  #define KAWAPACKED( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#endif

/* ========= Kawasaki Robot Header communicates on port23     =============== */
/*                                                                            */
/*       Written by ACP Aviation                                              */
/*       MESSAGES: ref Tonci Novkovic (python) Eth Zurich                     */
/*                                                                            */
/* ========================================================================== */
#define KAWA_START_MSG_LEN 100u
#define KAWA_CONNECTION_STRING_TUPLE "Connecting to Kawasaki E Controller\r\n\r\nlogin: ', None)"
/* 
   example usage :      
   char buf[KAWA_START_MSG_LEN];
   KAWA_START_MSG(&buf); 
*/
#define KAWA_START_MSG(A) do{ \
    char buf[18u]; \
    buf[0u] = 40u; \
    buf[1u] = 39u; \
    buf[2u] = 0xffu; \
    buf[3u] = 0xfdu; \
    buf[4u] = 0x18u; \
    buf[5u] = 0xffu; \
    buf[6u] = 0xfbu; \
    buf[7u] = 0x01u; \
    buf[8u] = 0xffu; \
    buf[9u] = 0xfau; \
    buf[10u] = 0x18u; \
    buf[11u] = 0x01u; \
    buf[12u] = 0x01u; \
    buf[13u] = 0xffu; \
    buf[14u] = 0xf0u; \
    buf[15u] = 0xffu; \
    buf[16u] = 0xfbu; \
    buf[17u] = 0x03u; \
    sprintf((char*)A,"%u%s",(char*)&buf,KAWA_CONNECTION_STRING_TUPLE); } while(0)
#define KAWA_STATE_STRING_PARTIAL "wh\r\n     JT1       JT2       JT3       JT4       JT5       JT6  \r\n"
#define KAWA_STATE_STRING_PARTIAL_LEN 60u
#define KAWA_MAX_POSE_STATE_REPLY 60u
#define KAWA_MAX_JOINT_STATE_REPLY 60u
#define KAWA_MOTOR_OFF_ERROR "(P1000)Cannot execute program because motor power is OFF."
#define KAWA_TEACH_LOCK_ON_ERROR "(P1002)Cannot execute program because teach lock is ON."
#define KAWA_TEACH_MODE_ERROR "(P1001)Cannot execute program in TEACH mode."
#define KAWA_ERROR_MODE_ERROR = "(P1013)Cannot execute because in error now. Reset error."
#define KAWA_ALREADY_RUNNING_ERROR "(P1009)Program is already running."
#define KAWA_CANNOT_REACH_ERROR "(P1013)Cannot execute because in error now. Reset error."
#define KAWA_NO_ERROR_FEEDBACK ">"
#define KAWA_MOTION_COMPLETE_MESSAGE "DO motion completed.\r\n"
#define KAWA_MIN_STATE_MSG_SIZE 230u                                            /* # Probably a bit higher, conservative estimate */
#define KAWA_STATE_MSG_PARSED_SIZE 5u
#define KAWA_STATE_MSG_JOINT_VALUES_INDEX 2u
#define KAWA_STATE_MSG_POSE_VALUES_INDEX 4u

#define KAWA_LOGIN_USER "b'as\n'"
#define KAWA_LOGIN_REPLY(A,socket_number)  do{ sprintf(A,"as\nThis is AS monitor terminal \"AUX %u \"\r\n>,None",socket_number); } while(0)
#define KAWA_GET_STATE "b'wh\n'"

/*    # SETUP: */
#define KAWA_PORT 23u                                                           /* # 10 Hz, RobotState */
#define KAWA_HOST_IP "192.168.2.2"
#define KAWA_RECEIVE_MSG_SIZE 1500u
#define KAWA_SOCKET_TIMEOUT 5u
#define KAWA_ROS_RATE 6u                                                        /*# ~6 Hz main loop */
#define KAWA_PUB_QUEUE_SIZE10u
#define KAWA_SUB_QUEUE_SIZE 1u
#define KAWA_TIMEOUT_SMALL 0.1f
#define KAWA_TIMEOUT_MEDIUM 0.5f
#define KAWA_TIMEOUT_LARGE 1.0f
#define KAWA_TRANSLATION_DIFFERENCE_THRESHOLD 0.0001f
#define KAWA_ROTATION_DIFFERENCE_THRESHOLD 0.05f

/*    # PARAMS: */
#define KAWA_wait_until_executed 1u
#define KAWA_counter_threshold 40u                                              /*# x0.5 sec wait*/

/*    # TOPICS: */
#define KAWA_pose_pub_topic "pose"
#define KAWA_joint_pub_topic "joint_states"
#define KAWA_completed_move_pub_topic "completed_move"
#define KAWA_pose_sub_topic "command/pose"

typedef enum { KAWA_RCV_START = 1, KAWA_SND_LOGIN = 2, KAWA_RCV_LOGIN = 3, KAWA_SND_GETSTATE = 4, KAWA_RCV_GETSTATE = 5, KAWA_RCV_POSE = 6, KAWA_NUM_MSG_STATES } KAWA_Msg_States_e;

#if defined(D_FT900)
typedef struct KAWAPACKED {
    char string[KAWA_MAX_POSE_STATE_REPLY];                                     /* max number of chars in pose state reply result */
    dVectr position;                                                            /* position */
    dVectr orientation_deg;                                                     /* oreintation in degrees */
    dVectr orientation_rad;                                                     /* orientation in radians */
    dquat orientationquat;                                                      /* orientation quaternion */
} KAWA_pose_t;
#else
KAWAPACKED(
typedef struct  {
    char string[KAWA_MAX_POSE_STATE_REPLY];                                     /* max number of chars in pose state reply result */
    dVectr position;                                                            /* position */
    dVectr orientation_deg;                                                     /* oreintation in degrees */
    dVectr orientation_rad;                                                     /* orientation in radians */
    dquat orientationquat;                                                      /* orientation quaternion */
}) KAWA_pose_t;                                                                
#endif

#if defined(D_FT900)
typedef struct KAWAPACKED {
    char string[KAWA_MAX_JOINT_STATE_REPLY];                                    /* max number of chars in pose state reply result */
    dVectr position;                                                            /* position */
} KAWA_joint_t;
#else
KAWAPACKED(
typedef struct  {
    char string[KAWA_MAX_JOINT_STATE_REPLY];                                    /* max number of chars in pose state reply result */
    dVectr position;                                                            /* position */
}) KAWA_joint_t;                                                                
#endif

#if defined(D_FT900)
typedef struct KAWAPACKED {
    KAWA_Msg_States_e state;                                                    /* state of message collection system */
    uint16_t socket_number;                                                     /* socket number when socket opened */
    KAWA_joint_t joint_states;                                                  /* information about joint */
    KAWA_pose_t pose_states;                                                    /* information about pose */
} kawasaki_robot_t;
#else
KAWAPACKED(
typedef struct  {
    KAWA_Msg_States_e state;                                                    /* state of message collection system */
    uint16_t socket_number;                                                     /* socket number when socket opened */
    KAWA_joint_t joint_states;                                                  /* information about joint */
    KAWA_pose_t pose_states;                                                    /* information about pose */
}) kawasaki_robot_t;                                                                
#endif

extern uint8_t kawasakiGetJoint(kawasaki_robot_t *rob);
extern uint8_t kawasakiGetPose(kawasaki_robot_t *rob);
extern uint8_t kawasakiParseState( const char* msg, kawasaki_robot_t *rob );
extern void kawasakiRcvSendmsg( const char * rcv, char * send, kawasaki_robot_t *rob );

#ifdef __cplusplus
}
#endif
