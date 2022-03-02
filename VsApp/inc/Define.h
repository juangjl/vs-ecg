/**
 * @file Define.h
 *
 *  General Definition
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __DEFINE_H__
#define __DEFINE_H__ 

///-----------------------------------------------------------------------///
/// Information
///-----------------------------------------------------------------------///
#define VS_SERIAL_NO					"000 - 00000"

#define VS_MODEL_NAME					"VS-ECG"
#define VS_VERSION_STR			 	"V1.00"

#define VS_MID							 	(0x45110164)
#define VS_PID							 	(0x00000100)
#define VS_DID							 	(0x00000001)

#define VERSION               (1)

#define VOLATILE 							volatile
#define EXTERN								extern



#define TRUE                	(1)
#define FALSE                	(0)

///-----------------------------------------------------------------------///
/// OS_TYPE
///-----------------------------------------------------------------------///
#define OS_TYPE_WINDOWS       (0)
#define OS_TYPE_UBUNTU        (1)
#define OS_TYPE_MAC_OS        (2)

///-----------------------------------------------------------------------///
/// Global Definition File
///-----------------------------------------------------------------------///
#define PACK  	 	__attribute__ ((__packed__))
#define PACKRAM  	__attribute__ ((__packed__))

///-----------------------------------------------------------------------///
///
///-----------------------------------------------------------------------///
#define DBG_PRINTF(x)  			DbgPrintf0((char *)x)
#define DBG_PRINTF0(x)			DbgPrintf0((char *)x)  		
#define DBG_PRINTF1(x)			DbgPrintf1((char *)x)  		
#define DBG_PRINTF2  		


#define HIGH           	(1)
#define LOW            	(0)

///=====================================================================///  
///  SYSTEM CONTROL2
///=====================================================================///

#define SYS_CTL2_SEC_EVT				  				(1<<0)
#define SYS_CTL2_000MS_EVT			  				(1<<0)
#define SYS_CTL2_100MS_EVT			  				(1<<1)
#define SYS_CTL2_200MS_EVT			  				(1<<2)
#define SYS_CTL2_300MS_EVT			  				(1<<3)
#define SYS_CTL2_400MS_EVT			  				(1<<4)
#define SYS_CTL2_500MS_EVT			  				(1<<5)
#define SYS_CTL2_600MS_EVT			  				(1<<6)
#define SYS_CTL2_700MS_EVT			  				(1<<7)
#define SYS_CTL2_800MS_EVT			  				(1<<8)
#define SYS_CTL2_900MS_EVT			  				(1<<9)

#define SYS_CTL2_00MS_EVT				  				(1<<10)
#define SYS_CTL2_10MS_EVT				  				(1<<11)
#define SYS_CTL2_20MS_EVT				  				(1<<12)
#define SYS_CTL2_30MS_EVT				  				(1<<13)
#define SYS_CTL2_40MS_EVT				  				(1<<14)
#define SYS_CTL2_50MS_EVT				  				(1<<15)
#define SYS_CTL2_60MS_EVT				  				(1<<16)
#define SYS_CTL2_70MS_EVT				  				(1<<17)
#define SYS_CTL2_80MS_EVT				  				(1<<18)
#define SYS_CTL2_90MS_EVT				  				(1<<19)


#define SYS_CTL2_TIMER_100MS_EVT				  (1<<20)
#define SYS_CTL2_TIMER_10MS_EVT					  (1<<21)
#define SYS_CTL2_TIMER_20MS_EVT					  (1<<22)


#endif ///<  __DEFINE_H__


