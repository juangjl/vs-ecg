/**
 * @file FORM5.h
 *
 *  FORM5 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM5_H__
#define __FORM5_H__
#include "Global.h"

typedef struct ViewDataFORM5St
{
	JBOOL bShow;
	///--------------------------------------------------------///
	/// Window --> Box --> View(Fixed)
	///--------------------------------------------------------///
	GtkWidget *pWindow;
	GtkWidget *pView;

	///--------------------------------------------------------///
	/// Label
	///--------------------------------------------------------///
		  
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// ComboBox
	///--------------------------------------------------------///	
	
	///--------------------------------------------------------///
	/// Frame (group)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///

} ViewDataForm5Type;

#endif ///< __FORM5_H__
