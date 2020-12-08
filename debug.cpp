/***********************************************************************************
 *Auth:zhrb
 *Time:9/20/2017
 *Vertion:0.1
 *Description:
***********************************************************************************/
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <stdio.h>		/* ..printf */
#include <stdarg.h>		/* va_start va_end */
#include <assert.h>
#include <string.h>

#include "mutex.hpp"

#define		MUL_THREAD		1
#define		CONSOLE_PRINT		0

#ifndef CONSOLE_PRINT
static mutex LogMux;			//

static FILE * LogFp = NULL;			//
//static clock_t ClockLast;			//
//static clock_t ClockStart;			//
#endif

int Debug = 0xff;

/***********************************************************************************
 *
***********************************************************************************/
int DebugInit(const char *name)
{
	int ret = 0;

#ifndef CONSOLE_PRINT
	if (name == NULL){
		return -1;
	}

	LogMux.lock();

	if(LogFp != NULL){
		return -2;
	}

	if (LogFp == NULL){//open once
		//ClockStart = clock();
		LogFp = fopen(name, "w+");
		if (LogFp == NULL){
			ret = -3;
		}
	}
	LogMux.unlock();
#endif

	return ret;
}

/***********************************************************************************
*
***********************************************************************************/
int DebugClose(void)
{
	int ret = 0;

#ifndef CONSOLE_PRINT

	LogMux.lock();
	if (LogFp){
		fclose(LogFp);
		LogFp = NULL;
	}
	LogMux.unlock();

#endif

	return ret;
}

#include <sys/time.h>
void GetTime(char * datetime)
{
	//char datetime[64];
	
	struct timeval tv = {0, 0};
	struct tm *tm;
	
	gettimeofday(&tv, NULL);
	const time_t tmp_time = tv.tv_sec;
	int ms = (int)(tv.tv_usec / 1000);
	tm = localtime(&tmp_time);
/*
	snprintf(datetime, 64, " [%d-%02d-%02d %02d:%02d:%02d.%03d] ",
		tm->tm_year + 1900,
		tm->tm_mon + 1,
		tm->tm_mday,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec, ms);
*/
	snprintf(datetime, 64, "[%02d:%02d:%02d.%03d] ",
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec, 
		ms);
}

/***********************************************************************************
*
***********************************************************************************/
void debug_printf(char * data)
{
	char datetime[64];
	GetTime(datetime);
	//clock_t clock_new = clock();
	//unsigned int tick =  clock_new - ClockStart;

#ifdef CONSOLE_PRINT
	printf("%s:%s\n", datetime, data);
#else
	/*add mutex here??*/
	if (LogFp == NULL){
		DebugInit("printer.log");
	}


	LogMux.lock();
	if (LogFp){
		fprintf(LogFp, "%s:%s\n", datetime, data);

		fflush(LogFp);
	}
	LogMux.unlock();

#endif
}

void printf_no_timestamp(char * data)
{
#ifdef CONSOLE_PRINT
	printf("%s", data);
#else
	/*add mutex here??*/
	if (LogFp == NULL){
		DebugInit("printer.log");
	}

	LogMux.lock();
	if (LogFp){
		fprintf(LogFp, "%s", data);

		fflush(LogFp);
	}
	LogMux.unlock();

#endif
}

void LogDataMap(unsigned short *data, int line, int len, int interval)
{
	if (len > 64)
		return;

	char disp[4096];
	char * buf = (char *)disp;

	//int offset = sprintf(buf, "Load Data Map %d:\n", line);
	int offset = sprintf(buf, "\n");
	buf += offset;
	for (int j = 0; j < line / len; j++){
		for (int i = 0; i < len; i++){
			offset = sprintf(buf, "0X%3X  ", data[j * len + i]);
			buf += offset;
			
			if((interval > 1) && (i % interval == interval - 1)){
				offset = sprintf(buf, "  ");
				buf += 2;
			}
		}
		offset = sprintf(buf, "\n");
		buf += offset;
	}
	debug_printf(disp);
}

void LogHeadOffset()
{

}


