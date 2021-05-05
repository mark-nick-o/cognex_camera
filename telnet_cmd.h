#ifndef __telnet_cmd_
#define __telnet_cmd_

/* ------------------------------------------ */
/* standard telnet commands                   */
/* information refs : Semyonov Y.A. (GNC ITEF)*/
/* Vladislav Bogomolov                        */ 
/* written by AirCamPro                       */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DEFAULT_TELNET_PORT 23u

typedef enum {
	Tel_Binary_exchange = 0,
	Tel_echo = 1,
	Tel_reconnecting = 2,
	Tel_Suppressing_input_buffering	= 3,
	Tel_Dialogue_about_the_size_of_the_message = 4,
	Tel_status = 5,
	Tel_Temporary_label = 6,
	Tel_Remote_access_and_response = 7,
	Tel_Length_of_output = 8,
	Tel_Page_output_size = 9,
	Tel_mode_displaying_characters_return = 10,
	Tel_Withdrawal_of_horizontal_tabs = 11,
	Tel_Installing_tab_position_withdrawal = 12,
	Tel_Page_change_command_output_mode = 13,
	Tel_The_output_vertical_tabs = 14,
	Tel_Determines_position_vertical_tab = 15,
	Tel_mode_displaying_symbol_line_translation = 16,
	Tel_Extended_asciI_code_set = 17,
	Tel_Return_logout = 18,
	Tel_Byte_macro = 19,
	Tel_Data_entry_terminal	= 20,
	Tel_Supdup = 21,
	Tel_Supdup_withdrawal = 22,
	Tel_Departure_location = 23,
	Tel_Terminal_type = 24,
	Tel_End_of_recording = 25,
	Tel_Tacacs_User_Id = 26,
	Tel_Note_output	= 27,
	Tel_Terminal_position_code = 28,
	Tel_Mode = 29,
	Tel_X3_PAD = 30,
	Tel_Window_size	= 31,
        Tel_TSPEED = 32,                                                        /* terminal speed */ 
        Tel_LFLOW = 33,                                                         /* remote flow control */ 
        Tel_LINEMODE = 34,                                                      /* Linemode option */ 
        Tel_XDISPLOC = 35,                                                      /* X Display Location */ 
        Tel_OLD_ENVIRON = 36,                                                   /* Old - Environment variables */ 
        Tel_AUTHENTICATION = 37,                                                /* Authenticate */ 
        Tel_ENCRYPT = 38,                                                       /* Encryption option */ 
        Tel_NEW_ENVIRON = 39,                                                   /* New - Environment variables */ 
        Tel_TN3270E = 40,                                                       /* TN3270 enhancements */ 
        Tel_XAUTH = 41,                       
        Tel_CHARSET = 42,                                                       /* Character set */ 
        Tel_RSP = 43,                                                           /* Remote serial port */ 
        Tel_COM_PORT_OPTION = 44,                                               /* Com port control */ 
        Tel_SLE = 45,                                                           /* Suppress local echo */ 
        Tel_STARTTLS = 46,                                                      /* Start TLS */ 
        Tel_KERMIT = 47,                                                        /* Automatic Kermit file transfer */ 
        Tel_SEND_URL = 48,                    
        Tel_FORWARD_X = 49,                   
        Tel_PRAGMA_LOGON = 138,               
        Tel_SSPI_LOGON = 139,                 
        Tel_PRAGMA_HEARTBEAT = 140, 
        TELTM_EOF = 236,	                                                /* File end sign */
        TELTM_SUSP = 237,	                                                /* Delay the current process */
        TELTM_ABORT = 238,                                                      /* Abortion process */ 
        TELTM_EOR = 239,	                                                /* End of recording */ 
        TELTM_SE = 240,	                                                        /* Completion of the parameters reconciliation (end of subpence) */
        TELTM_NOP = 241,	                                                /* No action */
        TELTM_DM = 242,	                                                        /* SYNCH process data block */
        TELTM_BRK_Stop = 243,                                                   /* brk symbol (break); */
        TELTM_IP_Interrupting = 244,	                                        /* IP function */
        TELTM_io_Breaking = 245,	                                        /* AO function */
        TELTM_AYT_Are_you_here = 246, 	                                        /* ayt function */
        TELTM_EC_erase_the_symbol = 247,                                        /* EC function */
        TELTM_EL_To_erase_the_line = 248,	                                /* EL function */
        TELTM_GA_Continue = 249,	                                        /* GA function */
        TELTM_SB = 250,	                                                        /* The beginning of the subpence */
        TELTM_Will = 251,	                                                /* Start execution (optional) */
        TELTM_WONT_will_not = 252,	                                        /* Failure to perform or continue execution (optional) */
        TELTM_DO_perform = 253,	                                                /* Insoculates the request that the other system performs (optional) */
        TELTM_Dont_No = 254,	                                                /* Requires another system to stop execution (optional) */
        TELTM_IEC = 255                                                         /* Interpreted as the beginning of a team sequence which start @  TEL_EOF */
} Telnet_Cmds_e;

/* ================= load recipe file to cognex camera using telnet ========= */
#define TEL_CR 13
#define TEL_LF 10
#define TEL_NUL 0

#define COGN_user "admin"
#define COGN_passwd ""
#define API_COGN_TCP_TEL_BEGIN(X) do{ strcpy(X,"SO0"); } while(0)
#define API_COGN_TCP_TEL_RCP_LOAD(X,RecipeName)  do{ sprintf(X,"LF<%s>",RecipeName); } while(0)
#define API_COGN_TCP_TEL_JOB_START(X,RecipeName) do( sprintf(X,"EV SetStartup(\\”<%s>.job\\”,1)",RecipeName); } while(0)
#define API_COGN_TCP_TEL_JOB_NEXT(X) do{ strcpy(X,"TS"); } while(0)
#define API_COGN_TCP_TEL_STOP(X) do{ strcpy(X,"SO1"); } while(0)

int8_t transbinaryStart( unsigned char* msg );
int8_t transbinaryStop( unsigned char* msg );
int8_t transNoEcho( unsigned char* msg );
int8_t transNoSurpressBuffer( unsigned char* msg );
int8_t COGN_sendRecipe( unsigned char * msg, unsigned char *rcpFileName );

/*
   IAC WILL TRANSMIT-BINARY,
   which in digital codes looks like - (255 251 0).
*/
/*-----------------------------------------------------------------------------
 *  transbinaryStart: start binary transmission on telnet 
 *      
 *  Parameters: unsigned char* msg
 *  Return: int8_t
 *----------------------------------------------------------------------------*/
int8_t transbinaryStart( unsigned char* msg )
{
  int8_t ret = -1;
  if (sizeof(msg) >= 3u)
  {
      msg[0u] = TELTM_IEC;
      msg[1u] = TELTM_Will;
      msg[2u] = Tel_Binary_exchange;
      ret = 1;
   }
   return ret;
}

/*
   To end this (binary) transfer mode, you need to give a command:
   IAC DON'T TRANSMIT-BINARY (255 254 0).
*/
/*-----------------------------------------------------------------------------
 *  transbinaryStop: stop binary transmission on telnet 
 *      
 *  Parameters: unsigned char* msg
 *  Return: int8_t
 *----------------------------------------------------------------------------*/
int8_t transbinaryStop( unsigned char* msg )
{
  int8_t ret = -1;
  if (sizeof(msg) >= 3u)
  {
     msg[0u] = TELTM_IEC;
     msg[1u] = TELTM_Dont_No;
     msg[2u] = Tel_Binary_exchange;
     ret = 1;
  }
  return ret;
}

/* 
   Line at a time.
   If any options (ECHO and SUPPRESS GO AHEAD) are not enabled, 
   Telnet is in line mode at a time. 
   
   if you need to send char at a time parse the message created in youre tcp sender 
*/ 
/*-----------------------------------------------------------------------------
 *  transNoEcho: telnet no echo
 *      
 *  Parameters: unsigned char* msg
 *  Return: int8_t
 *----------------------------------------------------------------------------*/
int8_t transNoEcho( unsigned char* msg )
{
  int8_t ret = -1;
  if (sizeof(msg) >= 3u)
  {
     msg[0u] = TELTM_IEC;
     msg[1u] = TELTM_Dont_No;
     msg[2u] = Tel_echo;
     ret = 1;
  }
  return ret;
}

/*-----------------------------------------------------------------------------
 *  transNoSurpressBuffer: telnet no buffer surpressing
 *      
 *  Parameters: unsigned char* msg
 *  Return: int8_t
 *----------------------------------------------------------------------------*/
int8_t transNoSurpressBuffer( unsigned char* msg )
{
  int8_t ret = -1;
  if (sizeof(msg) >= 3u)
  {
     msg[0u] = TELTM_IEC;
     msg[1u] = TELTM_Dont_No;
     msg[2u] = Tel_Suppressing_input_buffering;
     ret = 1;
  }
  return ret;
}

/*-----------------------------------------------------------------------------
 *  COGN_sendRecipe: telnet send of a recipe for cognex camera
 *      
 *  Parameters: unsigned char * msg, unsigned char *rcpFileName
 *  Return: int8_t
 *----------------------------------------------------------------------------*/
int8_t COGN_sendRecipe( unsigned char * msg, unsigned char *rcpFileName )
{
   static const unsigned char iac[2u] = { TELTM_IEC, TELTM_IEC };
#if defined(HOST_CR_ONLY)
   static const unsigned char cr[2u] = { TEL_CR, TEL_NUL };
#else
   static const unsigned char cr[2u] = { TEL_CR, TEL_LF };
#endif
   unsigned char recipeMsg[COGN_MAX_SIZE_OF_RECIPE];
   int8_t ret = -1;
   
   if (sizeof(msg) >= COGN_MAX_SIZE_OF_RECIPE+4u)
   {
       memset((void*)recipeMsg, 0u, COGN_MAX_SIZE_OF_RECIPE); 
       memcpy((void*)msg,(void*)&iac,2u);
       API_COGN_TCP_TEL_RCP_LOAD(recipeMsg,rcpFileName);
       memcpy((void*)msg+2u,(void*)recipeMsg,sizeof(recipeMsg));
       memcpy((void*)msg+2u+sizeof(recipeMsg),(void*)&cr,2u);
       ret = 1;
   }
   return ret;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* end telnet */
