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

#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

typedef struct GlobalVarSt
{  
  ///=========================================///
  /// system Command list 
  ///=========================================///
  JWORD wStatus;
  JWORD wVersion;    
 } GlobalVarType;

#pragma pack(pop)  /// push current alignment to stack

#endif ///< __GLOBAL_VAR_H__

