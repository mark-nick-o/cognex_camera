#ifndef __definitions_h
#define __definitions_h
//    definitions.h : General Global declarations
//
//
//    Version : @(#) 1.0
//    Copyright (C) 2020 A C P Avaiation Walkerburn Scotland
//
//
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>                                                             /* defines size_t and NULL */

#ifndef __GNUC__
#define __GNUC__ 1                                                              /* define the compiler as a derivative of gcc   */
#endif                                                                          /* set the level */

/* #define D_FT900                                                              for mikroC for FT90x */
#ifdef D_FT900
#ifndef Net_Ethernet_Intern_sendUDP                                             /* PIC32 function */
#define Net_Ethernet_Intern_sendUDP(a,b,c,d,e) Ethernet_Intern_sendUDP(a,b,c,d,e)  /* re-define them */
#endif
#endif /* end FT900 */

#ifndef free                                                                    /* for a different compiler which is case sensitive but not the norm for c */
#define free(a,b) Free(a,b)
#endif
#ifndef malloc                                                                  /* for a different compiler which is case sensitive but not the norm for c */
#define malloc(a) Malloc(a)
#endif

#ifndef Uart1_write_text                                                        /* macros to port the write text command between compiler versions */
#define Uart1_write_text(a) UART1_Write_Text(a)
#endif
#ifndef Uart2_write_text
#define Uart2_write_text(a) UART2_Write_Text(a)
#endif
#ifndef Uart3_write_text
#define Uart3_write_text(a) UART3_Write_Text(a)
#endif
#ifndef Uart4_write_text
#define Uart4_write_text(a) UART4_Write_Text(a)
#endif
#ifndef Uart5_write_text
#define Uart5_write_text(a) UART5_Write_Text(a)
#endif
#ifndef Uart6_write_text
#define Uart6_write_text(a) UART6_Write_Text(a)
#endif

#ifndef UART1_write_text                                                        /* macros to port the write text command between compiler versions */
#define UART1_write_text(a) UART1_Write_Text(a)
#endif
#ifndef UART2_write_text
#define UART2_write_text(a) UART2_Write_Text(a)
#endif
#ifndef UART3_write_text
#define UART3_write_text(a) UART3_Write_Text(a)
#endif
#ifndef UART4_write_text
#define UART4_write_text(a) UART4_Write_Text(a)
#endif
#ifndef UART5_write_text
#define UART5_write_text(a) UART5_Write_Text(a)
#endif
#ifndef UART6_write_text
#define UART6_write_text(a) UART6_Write_Text(a)
#endif

#ifndef UART1_write
#define UART1_write(x) UART1_Write(x)
#endif
#ifndef UART2_write
#define UART2_write(x) UART2_Write(x)
#endif
#ifndef UART3_write
#define UART3_write(x) UART3_Write(x)
#endif
#ifndef UART4_write
#define UART4_write(x) UART4_Write(x)
#endif
#ifndef UART5_write
#define UART5_write(x) UART5_Write(x)
#endif
#ifndef UART6_write
#define UART6_write(x) UART6_Write(x)
#endif

// floating point typedefs
#ifndef float32_t
typedef float float32_t;
#endif                                                                          /* these dont seem to be in my stdint ? */
//#define float32_t float 
#ifndef float64_t
typedef double float64_t;
#endif 
typedef long double float80_t;

/* define the version of this software */
#define ACP_PIC32_STR(v) #v
#define ACP_PIC32_VERSION_I(maj, min, rev)  ACP_PIC32_STR(maj) "." ACP_PIC32_STR(min) "." ACP_PIC32_STR(rev)
#define VERSION_MAJOR 001
#define VERSION_MINOR 003
#define VERSION_REVISION 004
#define ACP_PIC32_VERSION ACP_PIC32_VERSION_I(VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION)

#define CAM_USE_ASCII                                                           // define if you want to use ascii for the data in the Xstream message set after testing

/* #define Lo(param) ((char *)&param)[0u]                                           Lo byte */
/* #define Hi(param) ((char *)&param)[1u]                                           Hi byte */
// if not in stdlib :: #define RAND_MAX 32767
#define ROUNDINT(x) ((int32_t)floor((x)+0.5f))
#define ROUNDUINT(x) ((uint32_t)floor((x)+0.5f))
#define ROUNDSINT(x) ((int16_t)floor((x)+0.5f))
#define ROUND8INT(x) ((int8_t)floor((x)+0.5f))
#define FMOD2(x,y) ROUNDUINT(x) % ROUNDUINT(y);
#define ROUND(x,y) floor(x * pow(10.0f, y))/pow(10.0f, y)                       // No round in mikroE so define it here
#define FMOD(x,y) (x-y*floor(x/y))                                              // Floating modulus ??????
#define PI (float64_t) (4.0f * atan(1.0f))                                      // Define PI constant alt to const double pi = 4.0 * atan(1.0);
#define PI_2 (float64_t) (2.0f * atan(1.0f))                                    // Define PI constant alt to const double pi = 4.0 * atan(1.0);
#define M_E exp(1.0f)                                                           // M_E
#define NaN (255U<<23U)                                                         // Not a number defined as all exponent bits set
#define IsaNan(v) (((uint32_t) v & 0x7fffffffL) > 0x7f800000L)                  // Function to check for a NaN (not a number or invalid float)
#ifndef NULL
#define NULL '\0'                                                               // Define the NULL string terminator
#endif
#define CONSTRAIN(num, min, max) (num < min ? min : (num > max ? max : num))    // ref Shubhankar Agarwal <shubhankar0109@gmail.com>

/*#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif*/
/* =================== common conversions =================================== */
#define UNIX_REFERENCE_YEAR 1970U                                               // Year for UNIX Timestamp (time difference or sending EGD)
#define BITCOUNT(x) (((BX_(x)+(BX_(x)>>4L)) & 0x0F0F0F0FL) % 255U)
#define BX_(x) ((x) - (((x)>>1L)&0x77777777L) - (((x)>>2UL)&0x33333333L) - (((x)>>3L)&0x11111111L))
#define MD5_MAX_LEN 32U                                                         // length of the string returned by the getFileMd5() java call and returned in an AJAX reply
#define EARTH_RADIUS 6378137.0f                                                 // used for GPS position calculations
#define SPLICE(x,y) x ## _ ## y                                                 // joins x_y
#define KNOT2MTR(Knot) (Knot*0.5144f)
#define MTR2KNOT(Mtr) (Mtr*1.944f)
#define FEET2MTR(Feet) (Feet*0.3048f)
#define MTR2FEET(Mtr) (Mtr*3.2808f)
#define hzPerKnToHzPerMPerS(v) ( v*3600.0f/1852.0f )                            // convert to Hz per Nautical Mile per second.
#define hzPerMPerSToHzPerKn(v) ( v*1852.0f/3600.0f )
#define knotsToMs(v) ( v*1852.0f/3600.0f )
#define metersToNMiles(v) ( v/1852.0f )
#define fixAnglePos( v ) do{if(v < 0){v = PI*2.0f+d;} } while(0)                // change negative angle to positive
#define DEGREE_TO_RADIAN(deg) ( (PI*deg)/180.0f )                               // convert degrees to radians
#define RADIAN_TO_DEGREE(rad) ( (180.0f*rad)/PI )                               // convert radians to degrees
#define RADPSEC_FROM_METREPSEC(ms) { (16.5289f*ms) }                            // Convert meters/sec into radians/sec
#define GRAV_CONST 9.807f                                                       // GRAVITY_MAGNITUDE
#define CPU_TICKS_PER_SECOND 40000000UL                                         // number of ticks per second
#define CPU_CLOCK_SPEED (CPU_TICKS_PER_SECOND*2.0f)
#define TICKS2SEC(ticks) ((float64_t)ticks/(float64_t)CPU_TICKS_PER_SECOND)     // convert the ticks into seconds
#define SEC2US(sec) (1.0e6*sec)
#define EARTHRADIUSEQUATORIAL 6378137.0f
#define EARTHRADIUSPOLAR 6356752.0f
#define EARTHRADIUSMEAN 6372797.0f
#define EARTHRADIUS1976ISA 6356.766f
#define MOLWTDRYAIR 28.9644f                                                    // molecular wt of dry air
#define MOLWTWATER 18.016f                                                      // mol wt water
#define C1_CONST ( 1 - (MOLWTWATER / MOLWTDRYAIR) )
#define h_20190520 6.62607015E-34f
#define EARTH_SEMI_MAJOR_AXIS_A 6378137.0f                                      //[m] from WGS-84 reference ellipsoid
#define EARTH_SEMI_MINOR_AXIS_B 6356752.314f                                    //[m]
#define GAUSS2TESLA(g) 1.0e-4f*g                                                // from mavlink 2 ros for magnetic field
#define TESLA2GAUSS(t) t/1.0e-4f
#define MASS_DENSITY_FLUID 1.180f                                               // constant used for drag calculations
#define R_D 287.05f                                                             // specific gas constant for dry air
#define R_V 461.495f                                                            // specific gas constant for water vapor
// ================== various math constants ===================================
#define D_LOG_SQRT_2_PI    0.9189385332046727417803297364056176f                //! Log Root of 2 Pi
#define D_SQRT_2_PI        2.5066282746310002416123552393401041f                //! Root of 2*Pi
#define D_SQRT_PI          1.7724538509055160272981674833411451f                //! Root of Pi
#define D_SQRT_2           1.4142135623730950488016887242096981f                //! Root of 2 DEFINED in cmath as M_SQRT2, but is not 128 bit
#define D_LOG_2_PI         1.8378770664093454835606594728112353f                //! Natural Log of 2*Pi
#define D_LOG_PI           1.1447298858494001741434273513530587f                //! Natural Log of Pi
#define D_LOG_2            0.6931471805599453094172321214581766f                //! Natural Log of 2 DEFINED in cmath as M_LN2, but is not 128 bit
#define D_LOG_SQRT_2       0.3465735902799726547086160607290883f                //! Natural Log of sqrt of 2
#define D_2_PI             6.2831853071795862319959269370883703f                //! 2*Pi
#define D_EULER_GAMMA      0.5772156649015328606065120900824024f                //! The Euler-Mascheroni Constant (Not the same as e)
#define D_DEGREE           0.0174532925199432957692369076848861f                //! Number of radians in one degree
#define D_GOLDEN_RATIO     1.6180339887498948482045868343656381f                //! The golden ratio
#define D_CATALAN          0.9159655941772190150546035149323841f                //! Catalan's Constant
#define D_GLAISHER         1.2824271291006226368753425688697917f                //! Glaisher-Kinkelin Constant
#define D_KHINCHIN         2.6854520010653064453097148354817956f                //! Khinchin's Constant
#define D_SOLDNER          1.4513692348833810502839684858920274f                //! Ramanujan-Soldner's Constant
#define D_APERY            1.2020569031595942853997381615114499f                //! Apery's Constant
#define D_GAUSS_KUZMAN     0.3036630028987326585974481219015562f                //! Gauss-Kuzmin-Wirsing constant
#define D_FRANSEN          2.8077702420285193652215011865577729f                //! Fransén-Robinson constant
#define D_SERPINSKY        2.5849817595792532170658935873831711f                //! Sierpin'ski's constant
#define D_MILL             1.3063778838630806904686144926026057f                //! Mills' constant
#define D_OMEGA            0.5671432904097838729999686622103555f                //! Omega constant
#define D_GOLOMB_DICKMAN   0.6243299885435508709929363831008372f                //! Golomb-Dickman constant
// ================== various math formula ===================================
#define math_sec(A) 1.0f/cos(A)                                                 // secent
#define math_cosec(A) 1.0f/sin(A)                                               // cosecant
#define math_cotan(A) 1.0f/tan(A)                                               // cotangent
#define math_asec(A) acos(1.0f/A)                                               //! inverse secant
#define math_acosec(A) asin(1.0f/A)                                             //! inverse cosecant
#define math_sech(A) (1.0f/cosh(A))                                             //! Hyperbolic Secant
#define math_cosech(A) (1.0f/sinh(A))                                           //! Hyperbolic Cosecant
#define math_cotanh(A) (1.0/tanh(A))                                            //! Hyperbolic cotangent
#define math_logNforPixel(A,N) (log(A) / log(N))                                //! logN for pixel
#define math_logsig(A,a,b) (1.0f/(1.0f+exp((float64_t)(- (b * (A - a))))))      //! log sigmoid for pixel
#define math_logsig2(x,a,b) (1.0f/(1.0f+exp((float64_t)(-x*a + b))))            //! log sigmoid for pixel with offset
/*! Values like a = 10 and b = 5 create a nice sigmoid for x = 0 to 1 since
    the center of the sigmoid is at b/a.
    @param a The slope for the sigmoid
    @param b The offset for the sigmoid
*/
#define math_tansig(A) (2.0f/1.0f+exp(-2.0f*(float64_t)(A))-1.0f)               //! tan sigmoid for pixel
#define math_angDiff(A,B) min((A-B),PI)                                         // Angle difference, which is the minimum circular difference between two angles. Angles are in rad. Only for angles from 0 to PI
//! find p from a Gaussian distribution
#define math_gauss(A, Mu, Std) ((1.0f/(sqrt(D_2_PI*pow((float64_t)(Std),2.0f))))*exp(-1.0f*(pow(((float64_t)(A)-(float64_t)(Mu)),2.0f)/(2.0f*pow((float64_t)(Std),2.0f)))))
//! find p from a gamma distribution
#define math_gamma(X, A, B) ((pow((float64_t)(X),(float64_t)(A) -1.0f) * pow((float64_t)(B),(float64_t)(A))*exp((float64_t)(-1.0f*B*X)))/lngamma((float64_t)(A)))
#define math_onlineMean(mu, A, n) (mu + (A - mu/n))                             //compute the stddev and mean of each feature This algorithm is due to Knuth (The Art of Computer Programming, volume 2:
#define math_onlineStdev(mu, stdev, A, n)       \
do                                              \
{                                               \
  float64_t ret = stdev;                        \
  if (n > 2) /*watch for divide by 0 */         \
  {                                             \
    ret = (stdev * (n-2)) + (A - mu)*(A - mu);  \
    ret /= T(n-1);                              \
  }                                             \
  return ret;                                   \
} while(0)                                      \

#define math_sinc(x) do { if (x==0) return 1; else return sin(x)/(x); } while(0)
#define math_sinhc(x) do { if (x==0) return 1; else return sinh(x)/(x); } while(0)        

// ================== for quadrotor controls ===================================
// mass inertia
#define Thxxyy 2.32e-3f                                                         // moment of inertia around x,y [ kg*m^2 ]
#define Thzz 3e-4f                                                              // moment of inertia around z [ kg*m^2 ]
#define f_hover (mQ * GRAV_CONST)
// Thrust parameters
#define kF (6.17092e-8f * 3600.0f / (2.0f * PI * 2.0f * PI))                    // rotor thrust coefficient [ N/rad^2 ]
#define kM (1.3167e-9f * 3600.0f / (2.0f * PI * 2.0f * PI))                     // rotor moment coefficient [ Nm/rad^2]
#define wmax (7800.0f * 2.0f * PI / 60.0f)                                      // maximum rotor speed [ rad/s ]
#define wmin (1200.0f * 2.0f * PI / 60.0f)                                      // minimum rotor speed [ rad/s ]
#define Fsat_min (kF * wmin * wmin)
#define Fsat_max (kF * wmax * wmax)
// =============================================================================
//  safe atan and asin functions author Rosen Diankov ported by ACP
// =============================================================================
#define IKPI_2  ((float64_t)1.57079632679490f)
// allows asin and acos to exceed 1. has to be smaller than thresholds used for branch conds and evaluation
#ifndef IKFAST_SINCOS_THRESH
#define IKFAST_SINCOS_THRESH ((float64_t)1e-7f)
#endif
// used to check input to atan2 for degenerate cases. has to be smaller than thresholds used for branch conds and evaluation
#ifndef IKFAST_ATAN2_MAGTHRESH
#define IKFAST_ATAN2_MAGTHRESH ((float64_t)1e-7f)
#endif
// safe check for asin
#define IKsin(ret,a1) do{ if (!IsaNan(a1) && ((a1 > -1-IKFAST_SINCOS_THRESH) && (a1 < 1+IKFAST_SINCOS_THRESH))) {  ret = asin(a1); } else if (a1<=-1) { ret = -IKPI_2; } else if (a1>=1) { ret = IKPI_2; } } while(0)
// safe check for acos
#define IKcos(ret,a1) do{ if (!IsaNan(a1) && ((a1 > -1-IKFAST_SINCOS_THRESH) && (a1 < 1+IKFAST_SINCOS_THRESH))) {  ret = acos(a1); } else if (a1<=-1) { ret = PI; } else if (a1>=1) { ret = 0.0f; } } while(0)
// safe check for atan2
#define IKatan2(ret,a1,a2)  do{ if ((!IsaNan(a1) && !IsaNan(a2)) && (((a1 >= IKFAST_ATAN2_MAGTHRESH) || (a2 >= IKFAST_ATAN2_MAGTHRESH)) || ((-a1 <= -IKFAST_ATAN2_MAGTHRESH) || (-a2 <= -IKFAST_ATAN2_MAGTHRESH)))){  ret = atan2(a1,a2); } else if (IsaNan(a1)) { ret = IKPI_2; } else if (IsaNan(a2)) { ret = 0.0f; } } while(0)

/**
 * @brief Handy macro to find the number of elements in array a[]. Must be used
 * with actual array, not pointer. Copyright (C) 2003 Elwood C. Downey
 */
#define NARRAY(a) (sizeof(a) / sizeof(a[0u]))

//#define _CPU_BIG_ENDIAN                                                         // set this define if you need endian swap

/* ==================== alignment cross compiler =========================== */
#if (defined(__GNUC__)  || defined(D_FT900))
#define ALIGNED(x) __attribute__ ((aligned(x)))                                 /* Allign to boundaries of x */
#define IKFAST_ALIGNED16(variable) variable __attribute((aligned(16)))          /* allign to 16 bit boundary */
#elif defined(_MSC_VER)
#define ALIGNED(x) __declspec(align(16))                                        /* Allign to boundaries of x */
#define IKFAST_ALIGNED16(variable) __declspec(align(16)) variable               /* allign to 16 bit boundary */
#endif

#define CORE_TICK_SECOND 40000000UL                                             // core ticks equal to one second
// --------------- Set-up the system -------------------------------------------
//
//
#define TIMER1_NEEDED                                                           // To process UDP stack timer for retry
/* ============== Choose the GPS You want in the core ===================== */
//#define GPS_INCLUDED                                                            //If we want GPS from the ducati open source version
#define GPS_INCLUDED2                                                           // If want UBLOX or Futano GPS code
#if (defined(GPS_INCLUDED2) && defined(GPS_INCLUDED))
#error "Two separate GPS methods cannot be defined together "
#endif /* end 2 GPS includes throw error */
#if (defined(GPS_INCLUDED) || defined(GPS_INCLUDED2))                           /* if we are using GPS then define the maximum length of the packet */
#define MAX_GPS_MSG_LEN 768U
#define GPS_BAUD_RATE 9600U                                                     // Define the baud rate to be used for the GPS
#endif
//#define NAVILOCK_USED                                                           // link to navilock GPS
#if defined(NAVILOCK_USED)
#define NAVI_RESEND_MAX 3u
#define NAVI_RETRY_TIM 0.4f*CPU_TICKS_PER_SECOND
#define NAVI_MAX_NO_OF_POINTS 20u
#endif
/* ============= Robotics required ========================================== */
#define ROBOT_HELPER                                                            // If we want the Robot helper library from NATE 711 DOGGO Project
#if defined(ROBOT_HELPER)
//#define UART1_INTERUPT                                                          // for odrive communication
#define OD_BAUD_RATE 9600L                                                      // Odrive Baud Rate
#endif

/* ============ motion capture systems. ====================================  */
#define TF_DISTORT                                                              /* tf distortion ref : vicon bridge This is a driver providing data from VICON motion capture systems. It is based on the vicon_mocap package from the starmac stacks. */

/* ============ Drives ====================================================== */
#define VOLZ_PROTOCOL                                                           // VolZ protocol servo
#define ROBOTIS_PROTOCOL                                                        // Robotis protocol servo
#define DSHOT_MOTOR                                                             // dShot motor
#define KIN_SCUL                                                                // kinetic sculpture
#define FUTABA303_USED                                                          // futaba 303
#define AVNav_USED                                                              // AVNav submarine
#define VIDEORAY_M5_USED                                                        // Videoray M5 motors
#if defined(VIDEORAY_M5_USED)
#ifndef USE_RS485
#define USE_RS485                                                               // video ray uses rs485
#else
#error "RS485 pin already assigned"
#endif /* rs485 */
#endif /* end videoray m5 */
#define STEPPER_MOTOR                                                           // stepper motor
#define TILT_SERVO1_USED                                                        // tilted servo ref:- A-star ROS

/* ========== radio node =================================================== */
#define TRAMP_PROTOCOL                                                          // tramp protocol

/* ============ PID Controller ============================================== */
#define PID_LOOPS                                                               // If we want the PID Loops and Auto Tuning

/* ====== SBGC Axis Controller Remote Control HMI or messaging ========= */
#define SBGC_GIMBAL_HMI                                                         // SBGC Gimbal is being used
/* ====== SBGC Axis Controller Joystick ================================ */
#define SBGC_GIMBAL_JOY                                                         // SBGC Gimbal joystick is connected
//#define PROCESS_SMOOTH_INPUT_BEAR                                             //define these if you want non-linear processing of ADC inputs
#define PROCESS_SMOOTH_INPUT_DIFF
//#define USE_CALIB_VALS
#define SBGC_ACK_USED                                                           // use additonal ACK for UDP with SimpleBGC protocol (COM PIC)

/* ===== HMI Alarm Banner with Acknowledge (used for Camera/Gimbal) ========= */
#define ALARM_BANNER_USED                                                       // Alarm Banner used
#define COMMANDER_GROUND_STATION                                                // Commander Ground Station GUI

/* ============ GPS Position Sprayer ========================================*/
#define GPS_POS_SPRAYER                                                         // If we want a GPS positioned PID loop
#ifdef GPS_POS_SPRAYER                                                          // If we have PID loop sparyer working off GPS
#if (!defined(GPS_INCLUDED2) && !defined(GPS_INCLUDED))
#error "You must have chosen a GPS to use the position sprayer option"
#endif /* no GPS throw error */
#define MAX_TIME_TO_FIND_AREA 50U                                               // time in ticks to find the araa if cant find set-point in this time drop out loop and do something else
#define NO_SPRAY_OF_AREAS 4u                                                    // define the number of squares that make up the area
#define GPS_POS_HT_DB 10u                                                       // deadband on the required height for the calculated cone of the sprayer
#define _defSpraySpeed 50.0f                                                    // default spray speed if no data or gps turned off
#define _defSprayConeHt 6.75f                                                   // default spray cone height
#define POS_SPEED_COMPENSATE                                                    // compensate the position set-point with the craft speed
#define POS_SPEED_FACTOR 0.8765f                                                // speed factor for above compensation
#define MAX_REM_SPT 100.0f                                                      // maximum remote setpoint allowed
#define SPRAYER_START_DELAY 15u                                                 /* delay before starting sprayer when vehicle starts to move */
#define SPRAYER_STOPPED 0u                                                      /* sprayer state engine */
#define SPRAYER_MOVING 1u
#define SPRAYER_RUNNING_LONG_ENOUGH 2u
#define SPRAYER_IS_MOVING  2.5f                                                 /* speed over this starts the sprayer */
#define SPRAYER_SLOW_DOWN_DELTA 0.3f                                            /* delta for the speed */
#ifndef PID_LOOPS                                                               // if we dont have PID included
#define PID_LOOPS                                                               // we need it
/* #error "GPS Position Sprayer included and no PID defined :: PID library has been included"  */
#endif                                                                          // --- end pid
#endif                                                                          // --- end gps pos sprayer

/* ===== batch mixer system in air or ground craft ========================= */
#define BATCH_MIXER                                                             // we have a batch mixer and dosing system
#if defined(BATCH_MIXER)
#define EXTENDED_ARM                                                            // system also has extended dosing arm additonal to the batch tank
#define _LevelEmpty 10.0f                                                        /* batch start level */
#define LevelFirstAdditCorse 38.0f                                              /* first cut off level coarse */
#define LevelFirstAdditFine 40.0f                                               /* first cut off level fine */
#define LevelSecAdditCorse 67.0f                                                /* second cut off level coarse */
#define LevelSecAdditFine 70.0f                                                 /* second cut off level fine */
#define _corse1Time 1000ULL                                                      /* time(1/10s) to do corse substance1 if there is no level measurement working and we switched to timedOn mode */
#define _fine1Time 100ULL                                                        /* time(1/10s) to do fine substance1 if there is no level measurement working and we switched to timedOn mode */
#define _corse2Time 600ULL                                                       /* time(1/10s) to do corse substance2 if there is no level measurement working and we switched to timedOn mode */
#define _fine2Time 50ULL                                                         /* time(1/10s) to do fine substance2 if there is no level measurement working and we switched to timedOn mode */
#define _dosingTime 23500ULL                                                     /* time(1/10s) to dose for if there is no level measurement working and we switched to timedOn mode */
#define _mixTime 750ULL                                                          /* time(1/10s) to mix before opening the valve for dosing / spraying activation */
#define _solid1Time 25300ULL                                                     /* time(1/10s) to convey solids into the vessel */
#define _errorTime 500ULL                                                       /* time 1/10s to exceed the timed value by, before advancing the sequence, when using level instrument measument */
#if defined(EXTENDED_ARM)
#define EXT_ARM_BOUNCE_THRESHOLD 500U                                           /* only change the armActState->trigger_state if all states persist for longer than this e.g 50 for 5 seconds */
#define sprayEndStopMaxtime 2000ULL                                             /* maximum time before stopping */
#define sprayMidStopMaxtime 2000ULL
#define sprayRevStopMaxtime 2000ULL
#endif   /* end extended arm */
#endif   /* end batch mixer */

/* ============== positon distance measurement radars ===================== */
/* ============== used in cone height for spray control =================== */
#define JRT_LIDDAR_USED                                                         // JRT Liddar sensor used
#ifdef  JRT_LIDDAR_USED
#define MY_USB_HID_EP_IS 1                                                      // usb hid endpoint
#define PNEU_HT_CONTROL                                                         // pneumatic height control needed for sprayer
#endif

/* ======= other Radar type liddar measement for obstacle avoidance ======= */
#define LWNX_LIDDAR_USED                                                        // Lightware OptoElectronics Liddar attached
#define LEDDARTECH_LIDDAR_USED                                                  // LeddarTech Liddar being used
#define LIDAR_LITESTART_USED                                                    // Lidar Litestart

/* ====== PLC interfaces =================================================== */
#define GEF_EGD_PLC                                                             // GEFanuc PLC Connected helper library for EGD over UDP

/* ====== IC Sensors ======================================================= */
#define BOSCH_BME680_USED                                                       // Humidity sensor attached on i2c
#define MPU6050_ACC_GYRO                                                        // mpu6050 connected on i2c for accelerometer and gyro data
#define LSM303M_USED                                                            // LSM303D Accelerometer/Magnetometer. on spi
#define FBM320_BARO_USED                                                        // FBM320 Barometer
#define QMP6988_BARO_USED                                                       // QMP6988 Barometer
#define KELLER_BARO_USED                                                        // Keller Barometer
#define INA3221_POWER_USED                                                      // Texas INA3221 Power Monitor on i2c
#define BH1750_LUX_USED                                                         // BH1750 Lux meter
#define HMC6352_COMPASS_USED                                                    // HMC6352 Compass
#define I2C_CAMERA                                                              // omnivision i2c mobile camera
#define CYPS_24GHZ_USB                                                          // Cypress 2.4 Ghz USB Radio on SPI
#define WANT_IAQ2000_Co2                                                        // AppliedSensor iAQ-2000 co2 monitor
#define HTU21D_HUMID_USED                                                       // htu21d humidity & temperature sensor
#define CCS811_AIR_QUAL                                                         // air quality monitor https://ams.com/documents/20143/36005/CCS811_DS000459_6-00.pdf/c7091525-c7e5-37ac-eedb-b6c6828b0dcf#page=16
#define PX4_OPTICAL_FLOW_USED                                                   // px4 optical flow sensor

/* ====== Serial AHRS VectorNav ============================================ */
#define VECTTORNAV_VN100                                                        /* VN100 VectorNAV connected on serial 11500 Baud */

/* ====== USB Axis measurement ============================================= */
#define NAVSTIK_USED                                                            /* navstik accelerometer, gyro and magnetrometer */

/* ===== Allan Variance visual odometry ==================================== */
#define ALLAN_VAR_FUNCS 

/* ------ Modbus Protocol (PLC, external I/O, webserver, liddar) =========== */
/* ====== Support BIN,RTU,Daniels,Ascii, TCP serial ======================== */
#define MODBUS_NEEDED                                                           // Modbus protocol conenction
#define MODBUS_SERIAL
#define MODBUS_TCP
#define TCP_IP_MAX_BYTES 260u                                                   // max tcp/ip pdu frame (Check!!!!!!!!!!!!!!)
#define PL101_USED                                                              /* Procon PL101 PLC Webserver or Logic Interface */
#define PROCON_TCP_16DI_USED                                                    /* Procon ELectronic Modbus TCP 16DI logic and counter up to 1KHz */
#define NOVUS_DR4C_USED                                                         /* NOVUS DigiRail-4C Universal counter Module  */
#define NOVUS_DR2R_USED                                                         /* NOVUS DigiRail-2R Universal 2 relay out Module */ 
#define NOVUS_DR2A_USED                                                         /* NOVUS DigiRail-2A Universal Analog Input Module */
#if defined(LEDDARTECH_LIDDAR_USED)
#ifndef MODBUS_NEEDED
#define MODBUS_NEEDED                                                           // Modbus protocol conenction
#ifndef MODBUS_SERIAL
#define MODBUS_SERIAL                                                           // leddar tech is on serial connection
#endif
#endif
#endif /* leddar */

/* ====== ethernet IP (allen bradley yasakawa turck etc) ==================== */
#define ETH_IP_USED

/* ========== NVFlash ===================================== */
#define NV_FLASH_USED

/* ========== XML Parser library ===================================== */
#define XML_PARSER_USED

/* ===== Encoder Systems ==================================================== */
#define USE_SPEKTRUM                                                            // use spektrum
#define ENCODER_HELPER
#ifdef ENCODER_HELPER                                                           // use encoders
#undef USE_SPEKTRUM                                                             // cant have both mutually exclusive
#define ENCO_MAX_RPM 10.0f
#define ENCO_MAX_RAW 65535u
#define USE_MLINK
#endif

#define PULSE_TACHO
#if defined(PULSE_TACHO)                                                        // pulse tachometer odometer flow meter is attached
#define ROT_SENS_DIST 32.6758f                                                  // distance between sensor heads
#endif

/* ===== power management =================================================== */
#define LINEAR_FLOAT_PMBUS                                                      // for conversion of float to and from linear11 and linear16 values for PMBUS
#define FLASH_MEM_USED                                                          // flash memory used for storing data

/* ===== motor craft with object avoidance AI =============================== */
#define CRAFT_MTR_PIDS                                                          // craft motor pids
#ifdef CRAFT_MTR_PIDS
#define CRAFT_NUM_OF_MTRS 10u
#define TERRAIN_FOLLOW_USED                                                     // terrain following object
#endif

/* ====== Can Bus ========================================================== */
#define USE_CAN                                                                 // Can BUS or AUVCAN is required
#define CAN_RESEND_CNT 3u                                                       // number of times to send and wait if can is busy
#define USE_TCP_CAN                                                             // can over tcp

/* ======= Machine Learning ================================================= */
#define MACHINE_LEARN

/* ====== Motorised Vehicle Link MAVLINK for remote UAV ==================== */
#define USE_MAVLINK                                                             // MAVLINK used
#if (!defined(GPS_INCLUDED2) && !defined(GPS_INCLUDED))
#error "Must have a GPS for use with mavlink"
#endif

/* ========== UbiBot Agiculture Sensors ==================================== */
#define UBIBOT_DEVICE_USED                                                      // ubiBOT precision agriculture interface device
#define UBIBOT_SERVER_USED                                                      // ubiBOT precision agriculture interface server (using a lor of memory) http???
#if (defined(UBIBOT_DEVICE_USED) || defined(UBIBOT_SERVER_USED))
#define UBIBOT_USED                                                             // for general library
#if defined(UBIBOT_SERVER_USED)
#define UBIBOT_IP_ADDR "192.168.1.1"                                            // default tcp/ip address
#define UBIBOT_TCP_PORT 5001U                                                   // tcp/ip port for communications
#endif  /* end server */
#if defined(UBIBOT_DEVICE_USED)
#define UBIBOT_SERIAL_BAUD 115200UL                                             // serial port speed
#endif  /* end device */
#endif  /* end server and or device */

// ============== CAMERA TYPES Supported =======================================
#define XS_CAM (1u<<0u)                                                         // Bit set for we have AMP XS Encoder Cameras as the main camera device used in (e.g. mavlink qgroundcontrol etc)
#define RC_CAM (1u<<1u)                                                         // Bit set to say we have Run Cam Cameras as the main camera (e.g. mavlink qgroundcontrol etc)
#define XY_CAM (1u<<2u)                                                         // Bit set to say we have Xiong Yi Action Camera as the main camera (e.g. mavlink qgroundcontrol etc)
#define RF_CAM (1u<<3u)                                                         // Bit set to say we have Rayfin Camera as the main camera (e.g. mavlink qgroundcontrol etc)

#define REMOTE_TCP_AMP_XY_CAM                                                   // Control over remote tcp connection the amp xy decoder/encoder on uart4
#define REMOTE_UDP_AMP_XY_CAM                                                   // Control over remote tcp connection the amp xy decoder/encoder on uart4
#define SEQ_CAM_USED                                                            // Parrot Sequoia camera is connected (using a lot of memory) http??? yes look tomorrow
#define YI_CAM_USED                                                             // Yi Action Cam used
#define RUN_CAM_USED                                                            // Run Cam Used
#define REMOTE_TCP_RUN_CAM                                                      // Control over remote tcp connection the run cam on uart5
#define REMOTE_UDP_RUN_CAM                                                      // Control over remote tcp connection the run cam on uart5
#define REMOTE_TCP_SBGC                                                         // Remote Gimbal control over TCP to serial via this CPU enabled
#define REMOTE_UDP_SBGC                                                         // Remote Gimbal control over UDP to serial via this CPU enabled
#define CAMERA_TYPE XS_CAM                                                      // Define the encoder set-up we have
#if ((CAMERA_TYPE == XS_CAM) && defined(CAMERA_TYPE))
#define XS_ACK_USED                                                             // use ACK for UDP with XS Encoder
#define UART4_INTERUPT                                                          // If you want to have serial XS encoder commands
//#define XS_CUMULATE_REC_TIM                                                   Set this if you want the MAVLINK camera record time to be not reset each time
#endif
#define CANON_CAM_USED                                                          // Canon library
#define PENTAX_CAM_USED                                                         // Pentax library
#define SONY_VISCA_PROTO_USED                                                   // Sony Visca camera protocol required
#define ZEUS_CAM_USED                                                           // Zeus thermal imaging camera
#define MICROSCAN_USED                                                          // Microscan vision ANPR OCR camera used
#if defined(MICROSCAN_USED)
#define ANCR_MAX_MSG 15U                                                        // maximum charactures in number plate (tag)
#define MICROSCAN_OUT_TCP                                                       // using tcp as the output stream
//#define MICROSCAN_OUT_UART                                                      // using serial UART
#if (defined(MICROSCAN_OUT_TCP) && defined(MICROSCAN_OUT_UART))
#error "You can only have either serial or tcp connection to the microscan camera "
#endif  /* end error trap */
#endif /* end microscan ocr */
#define PELCO_PTZ_USED                                                          // Pelco-D PTZ protocol required
#define SMPTE_USED                                                              // SMPTE or Midi MTC required for timestamping video
#define RAYFIN_WATER_CAM_USED                                                   // Rayfin underwater camera and accessories i.e laser and light control
#define COGNEX_CAM_USED                                                         // Cognex 3D camera
#define SLMP_MITSI                                                              // SLMP protcol (mitsubishi) can be used with Cognex Camera

/* ===== Lighting / Shutter controls ======================================= */
#define DMX_USED                                                                // DMX used
#define DALI_USED                                                               // Dali Used
#define ART_NET_USED                                                            // Art-Net support for DMX512 required
#define ASN_E1_USED                                                             // Lightweight streaming protocol for transport of DMX512 using ACN

/* ===== Video Audio Switches / Conversion Formats and processing ========== */
#define LW3_SWITCH_USED                                                         // Lightwave LW3 protocol used for audio/video switch control
#define COLOR_CODEC_USED                                                        // Color codec conversion library included
#define LASER_DISPLAY_USED                                                      // handle or create ILDA files

/* ======= keyboard input / sound ========================================== */
#define MIDI_USED                                                               // midi used

/* ======= Ethernet Communication ciphers / encoders / servers ============= */
#define CBOR_COMS_USED                                                          // Using CBOR for iOt coAp or oscoAp and cipher used */
#if defined(CBOR_COMS_USED)
//#define ALGO_CHA_CHA                                                            /* the cipher is cha cha */
//#define ALGO_SEED                                                               /* the cipher is seed */
//#define ALGO_CAMELLIA                                                           /* the cipher is cemellia */
#define ADV_ENCPT_STD_USED                                                      /* AES used as the cipher e.g. OSCoAP */
#if defined(ADV_ENCPT_STD_USED)
#define IOT_SHA_256                                                             /* the hash is sha256 */
#endif
//#define ALGO_ARIA                                                               /* ARIA alogrythm used */
//#define ALGO_SALSA20                                                            /* salsa20 */
//#define ALGO_DES                                                                /* the ciper is DES */
#endif
#define JSON_COMS_USED                                                          // Using JSON for additional webservice
#if defined(JSON_COMS_USED)
#define JSON_ENABLE_BASE64                                                      // enable base 64
#define JSON_ENABLE_HEX                                                         // enable hex
#endif
#define GEO_JSON_USED                                                           // parse geoJSON from a web map for co-ordinates
#define RION_USED                                                               // Raw Internet Object Notation
#define USE_MSGPACK                                                             // use message pack
#define USE_BISON                                                               // use bison
#define USE_NTP                                                                 // use NTP (time sycronisation)
#define PROTOBUF_USED                                                           /* protocol buffers used e.g. google */
#define AIRMAP_USED                                                             /* Air map is used for telemetry */
#if defined(AIRMAP_USED)
#ifndef PROTOBUF_USED                                                           /* we cant not have protobuf if we need airmap */
#define PROTOBUF_USED
#endif
#endif

/* ===== Remote iOt monitoring and control =============================== */
#define UBIDOT_USED                                                             // UbiDot iOt server connection via http

/* ===== PIC Needs Filesystem (recipe management / photo store etc) ====== */
#define USE_MMC_SPI2                                                            // use multimedia card spi fat16 file system
#if defined(USE_MMC_SPI2)
#ifndef RION_USED
#define RION_USED                                                               /* currently uses a rion object for time */
#endif /* rion */
#endif /* mmc */

/* ====== Connect to GSM / GPRS Modem ====================================== */
#define GPRS_GSM_MODEM                                                          // include a GSM/GPRS modem

/* ===== Weather Station Connection ======================================== */
#define WEATHER_STAT                                                            // weather station connected

/* ==== air desnity calcs =================================================== */
#define AIR_DENSITY_CALC

/* ==== Display signs (flying or on ground or as warning) ================== */
#define XTCALL_DISPLAY                                                          // external calls display banner on RS232
#if defined(XTCALL_DISPLAY)
#define MAX_NUM_OF_WINS 8u                                                      /* we have no more than 8 windows on the display (you can make smaller to save memory if you dont want them) */
#endif
#define MOVSIN_DISPLAY                                                          // moving sign protocol on serial or ethernet

/* ====== Marine Communication ============================================== */
#define MARINE_PROTO_USED                                                       /* needs this for any of the above group section to be used */
#define NMEA2000_USED
#define NMEA0183_USED
#define SEASMART_USED
#if defined(SEASMART_USED)
#ifndef NMEA2000_USED
#define NMEA2000_USED
#endif /* nmea2000 */
#endif /* seasmart */
#define YDWG_JSON_USED
#if defined(YDWG_JSON_USED)
#ifndef NMEA0183_USED
#define NMEA0183_USED                                                           /* needs this library for conversion routines */
#endif /* nmea0183 check */
#endif /* ydwg json dependancy */
#define ACTISENSE_USED
#if defined(ACTISENSE_USED)
#ifndef NMEA2000_USED
#define NMEA2000_USED
#endif /* nmea2000 */
#ifndef NMEA0183_USED
#define NMEA0183_USED                                                           /* needs this library for conversion routines */
#endif /* nmea0183 check */
#endif /* actisense */

/* ===== J1939 Can Bus ====================================================== */
#define J1939_USED
#define LINAK_ACTUATOR_USED                                                     /* linak actuator */
#define CARLING_KEYPAD_USED                                                     /* carling tech keypad */
#define ENGINE_CTL_USED                                                         /* engine controls ECU */
#define APEM_JOYSTCK_USED                                                       /* apem joystick */
#define GEFRAN_PRESSURE_USED                                                    /* gefran pressure sensor */
#define STW_TEMPERAT_USED                                                       /* stw battery temperature sensor */

/* ===== Machine learning Artificial Intelligence =========================== */
#define ML_AI_NEEDED                                                            /* any below require this tag */
#define NELDER_MEAD                                                             /* nelder mead optimization algorythms */
#define NAIVE_BAYES_USED                                                        /* naive bayes classification algorythms */
#define RANDOM_FORREST_USED                                                     /* random forrest classification algorythms (not complete)*/
#define LOGISTIC_REGRESSION_USED                                                /* logistic regressiob classification algorythms */
#define LINEAR_REGRESSION_USED                                                  /* linear regression learning algorythms */
#define UNIVARIATE_SMOOTH                                                       /* Smooth univariate methods of optimization Bisection Newton Secant RFM */
/* ======== Port State Configurations ======================================= */
//Node
#define AIR 1U
#define MASGS 2U
#define FIRGS 3U
#define COMGS 4U
#define GIMJOY 5U
#define THIS_NODE_IS GIMJOY                                                     /* define what the current node for this application is */

/* Delay routines --- use with caution this will prevent any other action in PIC */
#ifndef usleep
   #define usleep(delay) do{{volatile uint32_t n = delay * 4; while(n > 0) n--;}}while(0)
#endif
#ifndef sleep
   #define sleep(delay) do{{volatile uint32_t n = delay * 4000; while(n > 0) n--;}}while(0)
#endif
#ifndef arraysize
   #define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif
#define PTR_OFFSET(addr, offset) ((void *) ((uint8_t *) (addr) + (offset)))

#define ROL8(a, n) (((a) << (n)) | ((a) >> (8 - (n))))                          //Rotate left operation
#define ROL16(a, n) (((a) << (n)) | ((a) >> (16 - (n))))
#define ROL32(a, n) (((a) << (n)) | ((a) >> (32 - (n))))
#define ROL64(a, n) (((a) << (n)) | ((a) >> (64 - (n))))
#define ROR8(a, n) (((a) >> (n)) | ((a) << (8 - (n))))                          //Rotate right operation
#define ROR16(a, n) (((a) >> (n)) | ((a) << (16 - (n))))
#define ROR32(a, n) (((a) >> (n)) | ((a) << (32 - (n))))
#define ROR64(a, n) (((a) >> (n)) | ((a) << (64 - (n))))

/* ===== PAW3902 Optical Flow IC ============================================ */
#define PAW_OPTICAL_FLOW_USED
#if defined(PAW_OPTICAL_FLOW_USED)
#define PAW_SAMPLE_INTERVAL_MODE_0 CPU_TICKS_PER_SECOND / 126LU                        /* 126 fps */
#define PAW_SAMPLE_INTERVAL_MODE_1 CPU_TICKS_PER_SECOND / 126LU                        /* 126 fps */
#define PAW_SAMPLE_INTERVAL_MODE_2 CPU_TICKS_PER_SECOND / 50LU                        /* 50 fps */
#endif

/* ====== FFT Notch ========================================================= */
#define FFT_NOTCH_REQ

/* ===== Serial Communication ==============================================  */

/* If we want to use UART2 for simpleBGC (direct serial) */
#if (defined(SBGC_GIMBAL_HMI) || defined(SBGC_GIMBAL_JOY))
#define UART2_INTERUPT                                                          /*  Add this if you want to use the UART2 serial port for SimpleSBGC */
#endif

#define ACK 0x6U                                                                /* acknowledge char */
#define NAK 0x15U                                                               /* not acknowledge char */

#define TRUE 1U
#define FALSE 0U
#define CLEAR 0U
#define SET 1U
#define U1STA_Add 0X6010U
#define U2STA_Add 0X6810U
#define U3STA_Add 0X6410U
#define U4STA_Add 0X6210U
#define U5STA_Add 0X6A10U

#define UDPSTA_Add 0X123U
#define COMCLSTA_Add 0XB102U

#define TCPSTL_Add 0XB354U

#define U1STA_OERR 0X01U
#define U2STA_OERR 0X01U
#define U3STA_OERR 0X01U
#define U4STA_OERR 0X01U
#define U5STA_OERR 0X01U
#define U1STA_FERR 0X02U
#define U2STA_FERR 0X02U
#define U3STA_FERR 0X02U
#define U4STA_FERR 0X02U
#define U5STA_FERR 0X02U
#define U1STA_PERR 0X03U
#define U2STA_FERR 0X02U
#define U3STA_FERR 0X02U
#define U4STA_FERR 0X02U
#define U5STA_FERR 0X02U
#define U2STA_B2UR 0X01U

#define UDPSTA_UART2 0X01U

// ================ UART2 Serial state engine
#define UART2_BUFFER_EMPTY 0U
#define UART2_BYTE_IN_BUFFER 1U
#define UART2_PACKET_IN_BUFFER 2U

/* =============== UART4.State XS Encoder ================================= */
#define UART4_BUFFER_EMPTY 0U
#define UART4_BYTE_IN_BUFFER 1U
#define UART4_SEND_UDP 3U
#define UART4_CHECK_ACK_CRC 4U
#define UART4_WAIT_ACK_CRC 5U
#define UART4_CHECK_ACK_TIME_OUT 6U
#define UART4_ACK_TIME_OUT 7U
#define UART4_RECEIVED_ACK_CRC 2U
#define UART4_PACKET_IN_BUFFER 8U                                               /* plus carry states of g_extended */

// ================ UART5 Serial state engine
#define UART5_BUFFER_EMPTY 0U
#define UART5_BYTE_IN_BUFFER 1U
#define UART5_PACKET_IN_BUFFER 2U

#define RUN_CAM_NO_CMD_FOUND 127u

/* ================ UART1 Serial state engine ODrive ====================== */
#define UART1_BUFFER_EMPTY 0U
#define UART1_BYTE_IN_BUFFER 1U
#define UART1_PACKET_IN_BUFFER 2U

#if defined(SONY_VISCA_PROTO_USED)
/* =============== viscaSerial.State ====================================== */
#define VISCA_BUFFER_EMPTY 0U
#define VISCA_BYTE_IN_BUFFER 1U
#define VISCA_SEND_UDP 3U
#define VISCA_CHECK_ACK_CRC 4U
#define VISCA_WAIT_ACK_CRC 5U
#define VISCA_CHECK_ACK_TIME_OUT 6U
#define VISCA_ACK_TIME_OUT 7U
#define VISCA_RECEIVED_ACK_CRC 2U
#define VISCA_PACKET_IN_BUFFER 8U
#define VISCA_PACKET_READ_COMPLETE 9U
#define VISCA_PACKET_READ_ERROR 9U
#endif

//U2STA_Add
#define U2STA_B2TO 1U
#define UART2_BUFFER_OVERFLOW 2U
#define UART2_BAD_CRC 3U
// UDP UDPSTA_Add
#define UDP_PACKET_SEND_FAIL 0U
#define UDP_PACKET_SEND_GOOD 1U
#define UDP_UART2_PACKET_ACK_TIMEOUT 2U
#define UDP_PACKET_ACK_RECEIVED 3U
#define UDP_UART2_SEND_PACKET_FAIL 4U
#define UDP_UART2_Packet_RECEIVED 5U
#define UDP_UART2_Packet_BAD_CRC 6U

#define COMCLSTA_ 0Xxx
#define COMCLSTA_INIT 0X01U
#define COMSESTA_INIT 0x01U

// ===== Ethernet UDP and TCP Frame send state engine ==========================
#define ETH_SEND_UDP 3U
#define ETH_CHECK_ACK_CRC 4U
#define ETH_WAIT_ACK_CRC 5U                                                     // UDP or TCP packet was received
#define ETH_CHECK_ACK_TIME_OUT 6U
#define ETH_ACK_TIME_OUT 7U
#define ETH_RECEIVED_ACK_CRC 8U
#define ETH_ACK_SENT_TCP 9U                                                     // For TCP a dummy ack was sent
#define ETH_PROCESSED_TCP 10U                                                   // We have processed the incoming packet
#define ETH_ACK_OLD_DATA_REQ 11U                                                // We were asked to re-transmit the existing data
#define ETH_ACK_RESENT 12U                                                      // We re-sent an ACK from the SYN_ACK received stage
#define ETH_NEW_TCP_DATA 13U                                                    // New TCP data ready to send
#define ETH_OLD_DATA_SENT 14U                                                   // Old data was re-transmitted
#define ETH_UDP_PACKET_RECEIVED 15U                                             // UDP Packet received
#define ETH_UDP_PACKET_PROCESSED 15U                                            // UDP Packet processed

#define ETHER_LINK_STATE 1U
#define SOCKET_STATE 2U                                                         // Socket status (used_socket ->state)
#define Eth_Progress 3U                                                         // Eth_Process_Status
#define CONNECT_TCP_STATE 4U                                                    // = Net_Ethernet_Intern_connectTCP

// EatherConState
#define UNDEFINED 0U
#define CLOSE_SOCKET 1U
#define OPEN_SOCKET 2U
#define WAIT_SOCKET_OPEN 3U
#define SEND_TCP_MSG 4U
#define CHECK_MSG_GONE 5U
#define TCP_SEND_ERROR 6U
#define ETHUNDEFINED 7U
#define TX_SUCCESS 8U
#define WAIT4CLOSE 9U

#define AIR_LINK_UP 10U
#define AIR_LINK_DOWN 11U
#define MASTER_LINK_UP 12U
#define MASTER_LINK_DOWN 13U
#define FIRE_LINK_UP 14U
#define FIRE_LINK_DOWN 15U
#define LINK_DOWN 16U

// Open SktStatus
#define BAD_SYN_TX 0U
#define GOOD_SYN_TX 1U
#define NO_SOCKET_AVAIL 2U
#define NO_ARP_RESOLVE 3U
#define DUMMY_ACK_ERROR 6U
#define RESPONSE_TIMEOUT 5U
#define FIN_CLOSE_ERROR 7U
#define FIN_PROCESS_ERR 8U
#define FIN_TIMEOUT_ERR 9U
// Timer 2
#define ENABLE_T2  0x8008U                                                      // 0x0000
#define DISABLE_T2 0x0000U

// Control of the INTCON (Global and periferal interrupts)
#define GIE_ON 0b10000000                                                       // Global interrupt enable flag
#define GIE_OFF 0b01111111
#define PEIE_ON 0b01000000                                                      // Periferal interrupt enable flag
#define PEIE_OFF 0b10111111
#define T0IE_ON 0b00100000                                                      // Timer 0 overflow interrupt enable flag
#define T0IE_OFF 0b11011111
#define INTE_ON 0b00010000                                                      // External interrupt enable flag
#define INTE_OFF 0b11101111
#define RBIE_ON 0b00001000                                                      // RB Port change interrupt enable flag
#define RBIE_OFF 0b11110111
#define T0IF_ON 0b00000100                                                      // T0 overflow interrupt flag
#define T0IF_OFF 0b11111011
#define INTF_ON 0b00000010                                                      // external interrupt flag
#define INTF_OFF 0b11111101
#define RBIF_ON 0b00000001                                                      // RB port interrupt flag
#define RBIF_OFF 0b11111110

// PIE1 and PIE2 periferal interrupts are defined in the relevant datasheets
// The following are available
// Timer 1 overflow
// TMR2 to PR2 match
// CCP1 and 2 interrupt
// SSPIE synchronous serial port  (needs to be enabled for i2c interrupts)
// RCIE USART Rx interrupt
// TXIE UDSTY Tx interrupt
// ADIE A/D converter
// ADCIE slope A/D trip interrupt
// OVFIE A/D timer
// PSPIE parallel slave port
// EEIE write complete interrupt
// LCDIE LCD interrupt
// CMIE Comparator interrupt enable

// ======================== TCP Socket States ==================================
//      TCP A                                                TCP B
//
//  1.  TCP_STATE_CLOSED                                 TCP_STATE_LISTEN
//
//  2.  SYN-SENT    --> <SEQ=100><CTL=SYN>               --> SYN-RECEIVED
//
//  3.  ESTABLISHED <-- <SEQ=300><ACK=101><CTL=SYN,ACK>  <-- SYN-RECEIVED/
//
//  4.  ESTABLISHED --> <SEQ=101><ACK=301><CTL=ACK>       --> ESTABLISHED
//
//  5.  ESTABLISHED --> <SEQ=101><ACK=301><CTL=ACK><DATA> --> ESTABLISHED
//
#define TCP_STATE_CLOSED 0U                                                     // This is the default state that each connection starts in before the process of establishing it begins
#define TCP_STATE_LISTEN 1U                                                     // A device (normally a server) is waiting to receive a synchronize (SYN) message from a client. It has not yet sent its own SYN message
#define TCP_STATE_SYN_SENT 4U                                                   // The device (normally a client) has sent a synchronize (SYN) message and is waiting for a matching SYN from the other device (usually a server)
#define TCP_STATE_SYN_RECEIVED 9U                                               // The device has both received a SYN from its partner and sent its own SYN. It is now waiting for an ACK to its SYN to finish connection setup
#define TCP_STATE_ESTABLISHED 3U                                                // Data can be exchanged freely once both devices in the connection enter this state. This will continue until the connection is closed
#define TCP_STATE_CLOSE_WAIT 10U                                                // The device has received a close request (FIN) from the other device. It must now wait for the application to acknowledge this request and generate a matching request
#define TCP_STATE_LAST_ACK 11U                                                  // A device that has already received a close request and acknowledged it, has sent its own FIN and is waiting for an ACK to this request
#define TCP_STATE_FIN_WAIT_1 5U                                                 // A device in this state is waiting for an ACK for a FIN it has sent, or is waiting for a connection termination request from the other device
#define TCP_STATE_FIN_WAIT_2 6U                                                 // A device in this state has received an ACK for its request to terminate the connection and is now waiting for a matching FIN from the other device
#define TCP_STATE_CLOSING 12U                                                   // The device has received a FIN from the other device and sent an ACK for it, but not yet received an ACK for its own FIN message
#define TCP_STATE_TIME_WAIT 13U                                                 // The device has now received a FIN from the other device and acknowledged it, and sent its own FIN and received an ACK for it. We are done, except for waiting to ensure the ACK is received and prevent potential overlap with new connections
#define TCP_STATE_RETRANSMIT 7U                                                 // Need to re-transmit the last message

#define TCP_NO_SYN_SEND 0U                                                      // 0 - no successful transmit SYN segment.
#define TCP_SYN_SUCCESS 1U                                                      // 1 - successful transmit SYN segment.
#define TCP_NO_SOCK 2U                                                          // 2 - no available socket.
#define TCP_NO_ARP 3U                                                           // 3 - no ARP resolve

//#define UART6_INTERUPT                                                          // Liddar is requested connected on UART6 at 115200 baud
#ifdef UART6_INTERUPT
#define LIDDAR_BAUD_RATE 115200L                                                // slowest rate but its the fastest for the PIC32
#define LIDDAR_PORT 6U                                                          // speaks on UART6
#ifndef LWNX_LIDDAR_USED                                                        // Lightware OptoElectronics Liddar attached
#define LWNX_LIDDAR_USED                                                        // Lightware OptoElectronics Liddar attached
#endif
#endif

#ifdef LWNX_LIDDAR_USED
#ifndef UART6_INTERUPT
#define UART6_INTERUPT
#define LIDDAR_BAUD_RATE 115200L                                                // slowest rate but its the fastest for the PIC32
#define LIDDAR_PORT 6U                                                          // speaks on UART6
#endif
#endif

#if defined(RUN_CAM_USED)                                                       // RunCam is requested
#define UART5_INTERUPT                                                          // we are using serial UART5 for the messages
#define RC_BAUD_RATE 9600L                                                      // baud rate for run cam
#endif

#if (defined(GPS_INCLUDED) || defined(GPS_INCLUDED2))
#define UART3_INTERUPT                                                          // using GPS books the UART3 resource
#endif

#define MCU_NAME PIC32MX795F512L                                                // define the MCU you are using be sure to check code for this

/* +++++++++++++++++++++++++++ MAVLink +++++++++++++++++++++++++++++++++++++ */
#if defined(USE_MAVLINK)
#define MAV_VER 2u                                                              // define the MAVLINK version 1 or 2 you are using (at current you can only have one but support both later)
#define UAMAV_BUFFER_EMPTY 0U                                                   // ================ MAVLINK Packet receive state engine
#define UAMAV_BYTE_IN_BUFFER 1U
#define UAMAV_PACKET_IN_BUFFER 2U
#define SERIAL_MAVLINK                                                          // define if we want to use serial mavlink
#if defined(SERIAL_MAVLINK)
#define MAV_BAUD_RATE 57600U
#define MAVLINK_USE_UART1                                                       // choose you're UART which you are using for MAVLINK protocol
//#define MAVLINK_USE_UART2                                                       // choose you're UART which you are using for MAVLINK protocol
//#define MAVLINK_USE_UART3                                                       // choose you're UART which you are using for MAVLINK protocol
//#define MAVLINK_USE_UART4                                                       // choose you're UART which you are using for MAVLINK protocol
//#define MAVLINK_USE_UART5                                                       // choose you're UART which you are using for MAVLINK protocol
//#define MAVLINK_USE_UART6                                                       // choose you're UART which you are using for MAVLINK protocol
#if (defined(UART1_INTERUPT) && defined(MAVLINK_USE_UART1))                       // already in use
#error "You have already assigned UART1! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART1                                                        /* remove the define as we already assigned the UART to something else  */
#elif (defined(UART2_INTERUPT) && defined(MAVLINK_USE_UART2))
#error "You have already assigned UART2! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART2                                                        /* remove the define as we already assigned the UART to something else  */
#elif (defined(UART3_INTERUPT) && defined(MAVLINK_USE_UART3))
#error "You have already assigned UART3! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART3                                                        /* remove the define as we already assigned the UART to something else  */
#elif (defined(UART4_INTERUPT) && defined(MAVLINK_USE_UART4))
#error "You have already assigned UART4! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART4                                                        /* remove the define as we already assigned the UART to something else  */
#elif (defined(UART5_INTERUPT) && defined(MAVLINK_USE_UART5))
#error "You have already assigned UART5! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART5                                                        /* remove the define as we already assigned the UART to something else  */
#elif (defined(UART6_INTERUPT) && defined(MAVLINK_USE_UART6))
#error "You have already assigned UART6! please choose an unassigned port for MAVLINK"
#undef MAVLINK_USE_UART6                                                        /* remove the define as we already assigned the UART to something else  */
#endif                                                                          /* end check UART for mavlink */
#else                                                                           /* we are using mavlink UDP */
#define MAV_STA_UDP_DATA_PORT 14551U                                            /* our mavlink over UDP port */
#define MAV_GC_UDP_DATA_PORT 14550U                                             /* remote (qgroundcontrol) over UDP port */
#define MAV_FILTER_INCLUDE                                                      /* include a filter on the incoming messages */
#endif                                                                          /* end mavlink serial or UDP */

#if (MAV_VER == 2u)                                                             /* --------------- MAVLINK VERSION 2.0 ------------------ */
#define MAVLINK_TIMESTAMP_CHK                                                   // you want to check the timestamp for single tuple messages in the interrupt
#define MAV_MAX_MSG_LEN 279U                                                    /* define the maximum mavlink message size */
#elif (MAV_VER == 1u)                                                           /* --------------- MAVLINK VERSION 1.0 ------------------ */
#define MAV_MAX_MSG_LEN 263U                                                    /* define the maximum mavlink message size */
#else
#error "You can only have version 1.0 or version 2.0 for MAVLINK "              /* throw an error if we dont define the vcrsion of mavlink */
#endif
#define USE_MAV_PULSE_OBJECT                                                    // we want to drive a pulse object over MAVLINK
#endif                                                                          /* end mavlink */

/* ====== NaviLock System ========================== */
#if defined(NAVILOCK_USED)

//#define NAVLINK_USE_UART1                                                       // choose you're UART which you are using for NAVLINK protocol
//#define NAVLINK_USE_UART2                                                       // choose you're UART which you are using for NAVLINK protocol
//#define NAVLINK_USE_UART3                                                       // choose you're UART which you are using for NAVLINK protocol
//#define NAVLINK_USE_UART4                                                       // choose you're UART which you are using for NAVLINK protocol
//#define NAVLINK_USE_UART5                                                       // choose you're UART which you are using for NAVLINK protocol
//#define NAVLINK_USE_UART6                                                       // choose you're UART which you are using for NAVLINK protocol

#if ((defined(UART1_INTERUPT) || defined(MAVLINK_USE_UART1)) && defined(NAVLINK_USE_UART1))                       // already in use
#error "You have already assigned UART1! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART1                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((defined(UART2_INTERUPT) || defined(MAVLINK_USE_UART2)) && defined(NAVLINK_USE_UART2))
#error "You have already assigned UART2! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART2                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((defined(UART3_INTERUPT) || defined(MAVLINK_USE_UART3)) && defined(NAVLINK_USE_UART3))
#error "You have already assigned UART3! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART3                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((defined(UART4_INTERUPT) || defined(MAVLINK_USE_UART4)) && defined(NAVLINK_USE_UART4))
#error "You have already assigned UART4! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART4                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((defined(UART5_INTERUPT) || defined(MAVLINK_USE_UART5)) && defined(NAVLINK_USE_UART5))
#error "You have already assigned UART5! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART5                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((defined(UART6_INTERUPT) || defined(MAVLINK_USE_UART6)) && defined(NAVLINK_USE_UART6))
#error "You have already assigned UART6! please choose an unassigned port for NAVLINK"
#undef NAVLINK_USE_UART6                                                        /* remove the define as we already assigned the UART to something else  */
#elif ((!defined(NAVLINK_USE_UART1) && (!defined(NAVLINK_USE_UART2) && (!defined(NAVLINK_USE_UART3) && (!defined(NAVLINK_USE_UART4) && (!defined(NAVLINK_USE_UART5) && !defined(NAVLINK_USE_UART6)))))))
#error "You have defined NAVLINK but not set the UART port!"
#else
#define NAVI_BAUD_RATE 115200UL
#define NAVI_READ_UINT32(buffer, offset) (((unsigned char)buffer[offset]) | (((unsigned char)buffer[offset+1u])<<8u) \
                | (((unsigned char)buffer[offset+2u])<<16u) | (((unsigned char)buffer[offset+3u])<<24u))

#define NAVI_READ_USHORT16(buffer, offset) (((unsigned char)buffer[offset]) | (((unsigned char)buffer[offset+1u])<<8u))
#define NAVI_DEVICE_MEM_SIZE (2*1024*1024)                                      //[bytes], 2MB
#define NAVI_TRAK_DATA_LEN 24u                                                  //[bytes] how much space one track uses
#define NAVI_POINT_DATA_LEN 16u                                                 //[bytes] how much space one point uses
#define NAVI_POINT_START_ADDR 3584                                              //address with the first point
#define NAVI_TIME_BETWEEN_POINTS 5                                              //[s] approximate delta time between two saved points
#define NAVI_SPEED_FACTOR 1.8f                                                  //calculate km/h from device speed
#endif /* end check UART for NAVlink */
#endif /* end navilock */

/* define the ADC method */
#define ADC_AUTO_COLLECT 1u
#define ADC_MAN_COLLECT 2u
#define ADC_NO_COLLECT 3u
#define AIN_ADC_METHOD ADC_MAN_COLLECT

#if (defined(SBGC_GIMBAL_JOY) && (AIN_ADC_METHOD == ADC_NO_COLLECT))
#error "you must define either ADC_AUTO_COLLECT or ADC_MAN_COLLECT with SBGC_GIMBAL_JOY"
#endif

// use type_str to return the type of T as a string
// Add you're own structures as A
#define type_str(T) _Generic( (T), int: "int",\
long: "long",\
uint8_t: "uint8_t", \
uint16_t: "uint16_t", \
uint32_t: "uint32_t", \
uint64_t: "uint64_t", \
int8_t: "int8_t", \
int16_t: "int16_t", \
int32_t: "int32_t", \
int64_t: "int64_t", \
float32_t: "float32_t", \
float64_t: "float64_t", \
char: "char", \
float: "float", \
unsigned char: "uchar", \
size_t: "size_t", \
A: "A",\
default: "Unknown type")

// show the number of arguments passed to the macro (considser use if prob with va_arg)

/* static complains about VA_ARGS here ...... ??
#define PP_NARG(...) \
    PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) \
    PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N( \
     _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63,  N, ...) N

#define PP_RSEQ_N() \
    63,62,61,60,                   \
    59,58,57,56,55,54,53,52,51,50, \
    49,48,47,46,45,44,43,42,41,40, \
    39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20, \
    19,18,17,16,15,14,13,12,11,10, \
     9, 8, 7, 6, 5, 4, 3, 2, 1, 0
     
#define NUM_ARGS_PASSED(...) PP_NARG(__VA_ARGS__)                                usage NUM_ARGS_PASSED(1,22,3,40,15) returns 5 as num_arg
*/
#ifndef size_t
#define size_t int16_t
#endif

// =============== encoding functions ==========================================
#define BASE64_SUPPORT ENABLED                                                  // enable base 64 encoding / decoding functions
#define BASE64URL_SUPPORT ENABLED                                               // enable base 64 encoding / decoding functions
#define RADIX64_SUPPORT ENABLED                                                 // enable radix 64 encoding / decoding functions
#define ASN1_SUPPORT                                                            // enable asn1 encoding / decoding functions
#define TRACE_LEVEL_DEBUG 1u                                                    // set the level to turn the debug prints on
#define CRYPTO_TRACE_LEVEL 0u                                                   // set the debug trace level off

#define MAX_CAN_MSG_LEN 8U                                                      // Can messages are 8 bytes long
#define CoAP_CMD_MAX_BYTES 80u                                                  // maximum message length for CoAP over UDP
#define SMPTE_CMD_MAX_BYTES 80u                                                 // smpte over udp maximum message size

// =============== handle wav sound files ======================================
#define USE_WAV_SOUND

// ============== MAVLINK ======================================================
//#define ENUM_BIGGER_THAN_INT16                                                // there are some enum > 65535 not allowed in mikroE C but disabled by not having this comment out unless needed

#define _MMC_REALTIME_DONE (1u<<0u)                                             /* bit 1 denotes that we have loaded to program memory the realtime parameters */
#define _MMC_RCP_DONE (1u<<1u)                                                  /* bit 2 denotes that we have loaded to program memory the batch and field parameters */

#define NO_OF_ROT_TEETH 10u                                                     /* define how many pickup sensors make up one rotation cycle for a pulse encoded input */
#define __roStop 0u                                                             /* craft becomes stationary */
#define Rig 1u                                                                  /* craft goes right */
#define Lef 2u                                                                  /* craft goes left */
#define Back 1u                                                                 /* craft goes back */
#define fwd 2u                                                                  /* craft goes forward */

#ifndef false                                                                   /* these were in then went out so put them here */
#define false 0u
#endif
#ifndef true
#define true 1u
#endif
#ifndef Lo
#define Lo(param) ((char *)&param)[0]
#endif
#ifndef Hi
#define Hi(param) ((char *)&param)[1]
#endif

#define NMEA0183_MAX_MSG_LEN 200u                                               /* !!!!! needs to be defined */

/** @file macrodef.h
 *  @brief Helper macros for various parts of Nautical.
 *
 *  @author Seth Girvan (Lord)
 */
// Sets the `bit`-th bit of `reg` to 1. (beginning from LSB). eg:
// Pretend EXAMPLE_REG is a 1-byte register, initialized as 0000 0000.
// Then SET_BIT_HIGH(EXAMPLE_REG, 3) will set the 3rd bit from LSB to 1, i.e. 0000 0100.
// Same goes for the other macros below.
#define SET_BIT_HIGH(reg, bit) reg |= (1U << bit)
#define SET_BIT_LOW(reg, bit) reg &= ~(1U << bit)                               // Sets the `bit`-th bit of `reg` to 0.
#define BIT_VALUE(reg, bit) reg & (1U << bit)                                   // Gets the value of the `bit`-th bit of `reg`.
#define TOGGLE_BIT(reg, bit) reg ^= (1U << bit)                                 // Toggles `bit`-th bit of `reg`.
#define IN_RANGE(min, val, max) (min <= val && val <= max)
#define TRUNC(min, val, max) (val <= min ? min : (val >= max ? max : val))
#define STRINGIFY_N(a) #a
// Macro expands a, then stringifies it.
#define STRINGIFY_X(a) STRINGIFY_N(a)
#define CC_NNN(a, b, c) a ## b ## c
#define FMIN(min, val) (val <= min ? val : min)
#define FMAX(max, val) (val >= max ? val : max)

#define SMALLQ0 0.01F                                                           // limit of quaternion scalar component requiring special algorithm
#define CORRUPTQUAT 0.001F                                                      // threshold for deciding rotation quaternion is corrupt
#define SMALLMODULUS 0.01F                                                      // limit where rounding errors may appear

#define FLT_EPSILON 1.19209290E-07F
#define DBL_EPSILON 2.2204460492503131E-16

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* -------- end of definitions library ----------- */
