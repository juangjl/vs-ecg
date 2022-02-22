/**
 * @file Func.h
 *
 *  Function Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FUNC_H__
#define __FUNC_H__

extern JBOOL FuncVSDongleOpen(char *strPortName);
extern JBOOL FuncVSDongleClose(void);


extern JBOOL FuncVSDongleVersionGet(void);
extern JBOOL FuncVSDongleTimeSet(void);

#endif ///< for __FUNC_H__
