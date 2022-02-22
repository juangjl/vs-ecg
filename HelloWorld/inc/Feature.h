/**
 * @file feature.h
 *
 *  feature setting
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/

#ifndef __FEATURE_H__
#define __FEATURE_H__

///----------------------------------------------------///
/// FEATURE: Compile the source code in windows
///----------------------------------------------------///
#if __has_include("windows.h") 
	#define ARCH_WIN32										///< default: off, windows  on; other : off
#endif ///< for has_include

#endif  ///< for #ifndef __FEATURE_H__

