/**
 * @file TypeDef.h
 *
 *  TypeDef.h define variable type
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

/// =============================================================///
///  1. General type definition
/// =============================================================///
/// JDWORD
typedef unsigned int         JDWORD; 
/// JWORD
typedef unsigned short       JWORD;
/// JSHORT
typedef  short  				     JSHORT;
/// JBYTE
typedef unsigned char        JBOOL;
/// JBYTE
typedef unsigned char        JBYTE;
/// Signed byte
typedef char                 JCHAR;
/// Float
typedef float                JFLOAT;

/// Float
typedef double               JDOUBLE;

/// void
typedef void                 JVOID;

/// int
typedef int              		 JINT;

/// int
typedef unsigned int      	 JUINT;

typedef unsigned long  				COLORREF;

typedef struct JTMSt
{
	JINT 		iYear;
	JINT 		iMonth;
	JINT 		iDay;
	JINT 		iHour;
	JINT 		iMin;
	JINT 		iSec;	
	JINT 		iMS;		
	JINT 		iTimeZoneSec;
	JDWORD 	t;		
} JTM;

#endif ///< __TYPEDEF_H__

