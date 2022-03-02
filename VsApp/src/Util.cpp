/**
 * @file Util.cpp
 *
 *   Utility Function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

///------------------------------------------///
///  Function Area
///------------------------------------------///
void DbgPrintf0(char *msg)
{		
	time_t  t 		= time(NULL);
  struct tm tm 	= *localtime(&t);
  
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms =  tp.tv_usec / 1000;
	
  JTM  jtm;
  jtm.iYear  		= tm.tm_year + 1900;
  jtm.iMonth 		= tm.tm_mon  + 1;
  jtm.iDay   		= tm.tm_mday;
	jtm.iHour	 		= tm.tm_hour;
	jtm.iMin   		= tm.tm_min;
	jtm.iSec   		= tm.tm_sec;	
	jtm.iMS				= ms;

	printf("[%04d-%02d-%02d %02d:%02d:%02d.%03d] %s", 
						jtm.iYear,
						jtm.iMonth,
						jtm.iDay,
						jtm.iHour, 
						jtm.iMin,
						jtm.iSec,
						jtm.iMS,						
					  msg);
}

void DbgPrintf1(char *msg)
{		
	printf("%s", msg);
}

void UtilMemcpy(JBYTE *dst, JBYTE *src, JINT iCnt)
{
	JINT i;
	for(i = 0; i < iCnt ; i++)
	{
		*dst = *src;
		dst++;
		src++;		
	}	
}

JBOOL UtilMemcmp(JBYTE *dst, JBYTE *src, JINT iCnt)
{
  JINT i;
  for(i = 0; i < iCnt ; i++)
  {
    if(*dst != *src)
    {
      return TRUE;
    }
    dst++;
    src++;
  }
  return FALSE;
}

void UtilMemset(JBYTE *dst, JBYTE bVal, JINT iCnt)
{
	JINT i;
	for(i = 0; i < iCnt ; i++)
	{
		*dst = bVal;
		dst++;	
	}
}


time_t UtilMakeTime(JWORD wYear, JBYTE bMonth, JBYTE bDay, JBYTE bHH, JBYTE bMM, JBYTE bSS)
{
	time_t t0 = 0;
  struct tm tm1;
  struct tm *tm2;

	tm1.tm_hour = bHH;
  tm1.tm_min  = bMM;
  tm1.tm_sec  = bSS;
  tm1.tm_year = wYear - 1900;
  tm1.tm_mon 	= bMonth - 1;
  tm1.tm_mday = bDay;
  tm1.tm_isdst  = 0;
//  tm1.tm_gmtoff = 0;
  
  t0 = mktime(&tm1); 	  
//  t0  = t0 - TIMEZONE_OFFSET;
  tm2 = gmtime(&t0);
 // printf("%04u-%02u-%02u-%02d:%02d:%02d\r\n", tm2->tm_year + 1900, tm2->tm_mon, tm2->tm_mday + 1, tm2->tm_hour, tm2->tm_min, tm2->tm_sec); 
	return t0; 
}


JINT UtilFileListGet(char *folderPath, char  * strFilter)
{
	DIR *d = NULL;
	struct dirent *dir;
	d = opendir(folderPath);
	if(d)
	{
	  while((dir = readdir(d))!= NULL)
	  {
	  	if(strstr(dir->d_name, strFilter) != NULL)
	  	{
	    	printf("\t%s\n", dir->d_name);
	  	}
	  }
	  closedir(d);
	}
	else
	{
		printf("not found\r\n");
	}
	return(0);
}

void UtilDataPrint(JBYTE *pbData, JINT iDataCnt)
{
	char 	msg[256];
	JINT 	i = 0;	
	JINT 	iDisplayCnt = 0;
	char  ch = 0;
	char  strText[256];

	if((iDataCnt % 16) != 0)
	{
		iDisplayCnt = iDataCnt - (iDataCnt % 16) + 16;
	}
	else
	{
		iDisplayCnt = iDataCnt;
	}
		
	/// print title
	sprintf(msg, "\t\tData count = %d\r\n", iDataCnt);
	DBG_PRINTF(msg);
	
	for(i = 0 ; i < iDisplayCnt; i = i + 1)
	{
		if((i % 16) == 0)
		{
			msg[0] = 0;
			strText[0] = 0;
			sprintf(msg, "\t\t%04X-%04X :", i, i+ 15);
		}
		if(i < iDataCnt)
		{
			sprintf(msg + strlen(msg), "%02X ", pbData[i]);
			ch = pbData[i];
			if((ch >= 48) && (ch<= 127))
			{
				sprintf(strText + strlen(strText), "%c", pbData[i]);
			}
			else
			{
				sprintf(strText + strlen(strText), "%c", '.');
			}
		}
		else
		{
			sprintf(msg + strlen(msg), "%c%c ", 'x', 'x');
			sprintf(strText + strlen(strText), "%s", ".");						
		}

		if((i % 16) == 7)
		{
			sprintf(msg + strlen(msg), "%s", "- ");
			sprintf(strText + strlen(strText), "%s", " ");									
		}

		if((i % 16) == 15)
		{
			sprintf(msg + strlen(msg), "%s\r\n", strText);
			DBG_PRINTF(msg);
		}
	}

	msg[0] = 0;
	sprintf(msg, "%s", "\r\n");
	DBG_PRINTF(msg);
}


int UtilNanoSleep(time_t sec, long nanosec)
{
   /// Setup timespec
   struct timespec req;
   req.tv_sec  = sec;
   req.tv_nsec = nanosec;
   nanosleep( &req, &req );  
   return 0; 
}

int UtilUsSleep(long us)
{
   /// Setup timespec
   struct timespec req;
   req.tv_sec  = 0;
   req.tv_nsec = us * 1000;
   nanosleep( &req, &req ); 
	return 0;
}

int UtilMsSleep(long ms)
{
	/// Setup timespec
	struct timespec req;
	
	req.tv_sec  = (ms / 1000);
	req.tv_nsec = (ms % 1000) * 1000000;
	nanosleep( &req, &req); 
	return 0;
}

int UtilFileExisted(char *filePath)
{
	struct stat st; 
	if(stat(filePath, &st) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

int UtilFolderExisted(char *folderPath)
{
  struct stat st= {0};

  if(stat(folderPath, &st) == 0 && S_ISDIR(st.st_mode)) 
  {
    return TRUE;
  }
  else 
  {
    return FALSE;
  }
}

int UtilFolderCreate(char *folderPath)
{
	struct stat st = {0};

	#ifdef ARCH_WIN32
	/// create input folder
	if(CreateDirectoryA(folderPath, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		return TRUE;
	}
	else
	{
		printf("Failed to create \"%s\" DIR", folderPath);
	}
	return FALSE;
	#else	
	if(stat(folderPath, &st) == -1)
	{
		mkdir(folderPath, 0777);
	}
	#endif
	return TRUE;
}

void UtilFileFolderGet(char *strFilePath, char *pDir)
{
	JINT 	len = strlen(strFilePath);  
	strcpy(pDir, strFilePath);
	while (len > 0)
	{
		len = len - 1;
		if(pDir[len] == '\\' || pDir[len] == '/')
		{
			pDir[len] = '\0';
			break;
		}
	}
}

void UtilFileNameGet(char *strFilePath, char *pFileName)
{
	JINT len = strlen(strFilePath);  
	JINT idx = 0;
	
	strcpy(pFileName, strFilePath);
	pFileName[len] = 0;		
	while (1)
	{
		if(len< 0)
		{	
			break;
		}
		len = len - 1;
		if(pFileName[len] == '\\' || pFileName[len] == '/')
		{
			pFileName[len] = '\0';
			break;
		}
	}
	/// file name
	while(1)
	{
		len = len + 1;
		if(len >= (JINT)strlen(strFilePath))
		{
			break;
		}		
		pFileName[idx] =	pFileName[len];
		pFileName[idx +1] =	0;
		if(pFileName[len] == 0)
		{
			break;
		}
		idx = idx + 1;
	}
}

JINT UtilFileSizeGet(char *fileName)
{
	JINT iSize = 0;
	struct stat st;
	stat(fileName, &st);
	iSize = st.st_size;
	return iSize;
}

void UtilWinPathNameSet(char *pPathName)
{
#ifdef ARCH_WIN32
	JINT i =0;
	JINT iLen = strlen(pPathName);
	for(i = 0 ; i < iLen ; i = i + 1)
	{
		if(pPathName[i] == '/')
		{
			pPathName[i] = '\\';
		}
	}
#endif ///<for ARCH_WIN32	
}

void JTMTimeZoneSecSet(JTM *pJTM, JINT iTimeZoneSec)
{
	pJTM->iTimeZoneSec = iTimeZoneSec;
}

void JTMLocalTimeGet(JTM *pJTM, time_t tNow)
{	
	struct tm tmNow  =  *localtime(&tNow);  
	///-----------------------------------///
	/// Set current time
	///-----------------------------------///  
	pJTM->iYear  = tmNow.tm_year + 1900;
	pJTM->iMonth = tmNow.tm_mon  + 1;
	pJTM->iDay   = tmNow.tm_mday;
	pJTM->iHour  = tmNow.tm_hour;
	pJTM->iMin   = tmNow.tm_min;
	pJTM->iSec   = tmNow.tm_sec;
	pJTM->t      = tNow;	
}

void JTMGmTimeGet(JTM *pJTM, time_t tNow)
{	
	struct tm tmNow  =  *gmtime(&tNow);  
	///-----------------------------------///
	/// Set current time
	///-----------------------------------///  
	pJTM->iYear  = tmNow.tm_year + 1900;
	pJTM->iMonth = tmNow.tm_mon  + 1;
	pJTM->iDay   = tmNow.tm_mday;
	pJTM->iHour  = tmNow.tm_hour;
	pJTM->iMin   = tmNow.tm_min;
	pJTM->iSec   = tmNow.tm_sec;
	pJTM->t      = tNow;
}

void JTMPrint(JTM *pJTM)
{
	printf("\tJTM = %04d/%02d/%02d-%02d:%02d:%02d\r\n", 
				pJTM->iYear,
				pJTM->iMonth,
				pJTM->iDay,
				pJTM->iHour,
				pJTM->iMin,
				pJTM->iSec);
}

JINT UtilTimeStrGet(JINT iTimeMS, char *strTime)
{
	JINT iMS  = 0;
	JINT iSec  = 0;
	JINT iMin  = 0;	
	JINT iHour = 0;	
	
	JINT iSecTotal  = 0;	
	JINT iMinTotal  = 0;		
	JINT iHourTotal  = 0;			

	iMS = iTimeMS % 1000;
	iSecTotal = (iTimeMS - iMS) / 1000;
	iSec = (iSecTotal) % 60;

	iMinTotal = (iSecTotal - iSec) / 60;
	iMin = (iMinTotal) % 60;

	iHourTotal = (iMinTotal - iMin) / 60;
	
	iHour =iHourTotal;	

 	sprintf(strTime, "%02d:%02d:%02d.%03d", iHour, iMin, iSec, iMS);
	
	return TRUE;
}

JINT UtilTimeMsGet(char *strTime,  JINT *pTimeMS)
{
	JINT iMS  = 0;
	JINT iSec  = 0;
	JINT iMin  = 0;	
	JINT iHour = 0;	
	JINT iSecTotal  = 0;	
	
	sscanf(strTime, "%d:%d:%d.%d", &iHour, &iMin, &iSec, &iMS);
	iSecTotal = iSec + 60 * iMin + iHour * 3600;
	*pTimeMS = iSecTotal * 1000 + iMS;	
	
	return TRUE;
}

void UtilLocalTime(JTM *pJTM, time_t t)
{
	struct tm tmNow  = *localtime(&t);

	///-----------------------------------///
	/// Set current time
	///-----------------------------------///  
	pJTM->iYear  = tmNow.tm_year + 1900;
	pJTM->iMonth = tmNow.tm_mon  + 1;
	pJTM->iDay   = tmNow.tm_mday;
	pJTM->iHour  = tmNow.tm_hour;
	pJTM->iMin   = tmNow.tm_min;
	pJTM->iSec   = tmNow.tm_sec;
	pJTM->t      = t;
}

void UtilCurDirGet(char * pCurrDir)
{
	char msg[256];
	if(getcwd(pCurrDir, 256) != NULL)
	{
  	sprintf(msg, "Current working dir: %s\n", pCurrDir);
  	//DBG_PRINTF(msg);
  }
	else
	{
		sprintf(pCurrDir, "%s", "./");
  	sprintf(msg, "Cannot find current working dir, utilize %s\n", pCurrDir);
  	DBG_PRINTF(msg);		
	}
}


void UtilTimeFolderCreate(char * pDataDir, JTM *pJTM, char * pTimeFolder)
{
	char strFolderName[256];

	/// YEAR
	sprintf(strFolderName, "%s/%04d",
		pDataDir,
		pJTM->iYear);
	UtilFolderCreate(strFolderName);

	/// YEAR/MONTH
	sprintf(strFolderName, "%s/%04d/%02d",
		pDataDir,
		pJTM->iYear, pJTM->iMonth);
	UtilFolderCreate(strFolderName);

	/// YEAR/MONTH/DAY
	sprintf(strFolderName, "%s/%04d/%02d/%02d",
		pDataDir,
		pJTM->iYear, pJTM->iMonth, pJTM->iDay);
	UtilFolderCreate(strFolderName);
	
	/// YEAR/MONTH/DAY/HOUR
	sprintf(strFolderName, "%s/%04d/%02d/%02d/%02d",
		pDataDir,
		pJTM->iYear, pJTM->iMonth, pJTM->iDay,
		pJTM->iHour);
	UtilFolderCreate(strFolderName);

	/// YEAR/MONTH/DAY/HOUR/MIN
	sprintf(strFolderName, "%s/%04d/%02d/%02d/%02d/%02d",
		pDataDir,
		pJTM->iYear, pJTM->iMonth, pJTM->iDay,
		pJTM->iHour, pJTM->iMin);
	UtilFolderCreate(strFolderName);

	/// YEAR/MONTH/DAY/HOUR/MIN/SEC
	sprintf(strFolderName, "%s/%04d/%02d/%02d/%02d/%02d/%02d",
		pDataDir,
		pJTM->iYear, pJTM->iMonth, pJTM->iDay,
		pJTM->iHour, pJTM->iMin, pJTM->iSec);
	UtilFolderCreate(strFolderName);

	strcpy(pTimeFolder, strFolderName);
}

JINT UtilGetch(void)
{
	struct termios oldattr, newattr;
	JINT ch = 0;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON| ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

