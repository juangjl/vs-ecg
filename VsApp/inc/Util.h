/**
 * @file Util.h
 *
 *  utility function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __UTIL_H__
#define __UTIL_H__ 

#define 	GETCH UtilGetch

extern void 	DbgPrintf0(char *msg); ///< with timestampe
extern void	  DbgPrintf1(char *msg); ///< without timestampe
extern int 		UtilGetch(void);

extern void   UtilOSTypeGet(JINT *piOSType);

extern time_t UtilMakeTime(JWORD wYear, JBYTE bMonth, JBYTE bDay, JBYTE bHH, JBYTE bMM, JBYTE bSS);
extern JINT   UtilFileListGet(char *folderPath, char  * strFilter);

#define       MEMCMP_SAME      (0)
#define       MEMCMP_DIFF      (1)

extern void   UtilMemcpy(JBYTE *dst, JBYTE *src, JINT iCnt);
extern JBOOL  UtilMemcmp(JBYTE *dst, JBYTE *src, JINT iCnt);
extern void   UtilMemset(JBYTE *dst, JBYTE bVal, JINT iCnt);

extern void 	UtilDataPrint(JBYTE *pbData, JINT iDataCnt);

extern int 		UtilMsSleep(long ms);
extern int	 	UtilUsSleep(long us);
extern int 		UtilNanoSleep(time_t sec, long nanosec);


extern int 		UtilFileExisted(char *filePath);
extern int   	UtilFolderExisted(char *folderPath);
extern int 		UtilFolderCreate(char *folderPath);

extern JINT 	UtilFileSizeGet(char *fileName);
extern JINT 	UtilTimeStrSet(JINT iTimeMS, char *strTime);

extern void 	UtilWinPathNameSet(char *pPathName);

extern void 	UtilFileFolderGet(char *strFilePath, char *pDir);
extern void 	UtilFileNameGet(char *strFilePath, char *pFileName);

extern JINT 	UtilTimeStrGet(JINT iTimeMS, char *strTime);
extern JINT 	UtilTimeMsGet(char *strTime,  JINT *pTimeMS);


extern void 	UtilLocalTime(JTM *pJTM, time_t t);

extern void 	UtilCurDirGet(char * pCurrDir);

extern void   UtilTimeFolderCreate(char * pDataDir, JTM *pJTM, char * pTimeFolder);

extern void   JTMTimeZoneSecSet(JTM *pJTM, JINT iTimeZoneSec);
extern void 	JTMLocalTimeGet(JTM *pJTM, time_t tNow);
extern void 	JTMGmTimeGet(JTM *pJTM, time_t tNow);

extern void 	JTMPrint(JTM *pJTM);

#endif ///<  __TASK_H__

