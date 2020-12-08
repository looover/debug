/*
 *Auth:zhrb
 *Time:9/20/2017
 *Vertion:0.1
 *Description:
*/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#ifdef BIT
	#undef BIT
#endif//!BIT
#define		BIT(x)				(1<<(x))

#define		LOG_DBG_DOMAIN		BIT(0)
#define		LOG_APP_DOMAIN		BIT(1)
#define		LOG_INF_DOMAIN		BIT(2)
#define		LOG_WAR_DOMAIN		BIT(3)
#define		LOG_ERR_DOMAIN		BIT(4)

#define		LOG_BUF_SIZE		256
#define IN_FMT_FFL "%s():%d: "

extern int Debug;
extern void debug_printf(char * data);
extern void printf_no_timestamp(char * data);

extern void LogDataMap(unsigned short *data, int line, int len, int interval = 1);

#define PRINTF(fmt, ...)			\
do {\
	if(1){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE,  fmt,  ##__VA_ARGS__);\
		printf_no_timestamp(tmp);\
	}\
} while (0)

#define EXE_PRINT(fmt, ...)			\
do {\
	if(1){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE,  "[EXE]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define PMD_PRINT(fmt, ...)			\
do {\
	if(1){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE,  "[PMD]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define DBG_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_DBG_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE,  "[DBG]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define APP_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_APP_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE, "[APP]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define INF_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_INF_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE, "[INF]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define WAR_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_INF_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE, "[WAR]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define ERR_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_INF_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE, "[ERR]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

#define HS_PRINT(fmt, ...)			\
do {\
	if (Debug & LOG_DBG_DOMAIN){\
		char tmp[LOG_BUF_SIZE];\
		snprintf(tmp, LOG_BUF_SIZE,  "[NET]" IN_FMT_FFL fmt,  __FUNCTION__, __LINE__, ##__VA_ARGS__);\
		debug_printf(tmp);\
	}\
} while (0)

extern int DebugInit(const char *name);
extern int DebugClose(void);


#endif //!_DEBUG_H_
