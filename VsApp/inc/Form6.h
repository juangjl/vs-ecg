/**
 * @file Form6.h
 *
 *  Form6 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM6_H__
#define __FORM6_H__
#include "Global.h"

#define FORM6_FRAME0_LEFT								(20)
#define FORM6_FRAME0_TOP								(40)
#define FORM6_FRAME0_WIDTH							(480)
#define FORM6_FRAME0_HEIGHT							(120)
#define FORM6_FRAME0_XGAP								(20)
#define FORM6_FRAME0_YGAP								(20)
#define FORM6_FRAME0_ROW								(30 + FORM6_FRAME0_YGAP)

#define FORM6_FRAME1_LEFT								(520)
#define FORM6_FRAME1_TOP								(40)
#define FORM6_FRAME1_WIDTH							(480)
#define FORM6_FRAME1_HEIGHT							(120)
#define FORM6_FRAME1_XGAP								(20)
#define FORM6_FRAME1_YGAP								(20)
#define FORM6_FRAME1_ROW								(30 + FORM6_FRAME1_YGAP)

#define FORM6_FRAME2_LEFT								(20)
#define FORM6_FRAME2_TOP								(180)
#define FORM6_FRAME2_WIDTH							(480)
#define FORM6_FRAME2_HEIGHT							(120)
#define FORM6_FRAME2_XGAP								(20)
#define FORM6_FRAME2_YGAP								(20)
#define FORM6_FRAME2_ROW								(30 + FORM6_FRAME2_YGAP)

#define FORM6_FRAME3_LEFT								(520)
#define FORM6_FRAME3_TOP								(180)
#define FORM6_FRAME3_WIDTH							(480)
#define FORM6_FRAME3_HEIGHT							(120)
#define FORM6_FRAME3_XGAP								(20)
#define FORM6_FRAME3_YGAP								(20)
#define FORM6_FRAME3_ROW								(30 + FORM6_FRAME3_YGAP)


#define FORM6_FRAME4_LEFT								(20)
#define FORM6_FRAME4_TOP								(320)
#define FORM6_FRAME4_WIDTH							(480)
#define FORM6_FRAME4_HEIGHT							(120)
#define FORM6_FRAME4_XGAP								(20)
#define FORM6_FRAME4_YGAP								(20)
#define FORM6_FRAME4_ROW								(30 + FORM6_FRAME4_YGAP)

#define FORM6_FRAME5_LEFT								(520)
#define FORM6_FRAME5_TOP								(320)
#define FORM6_FRAME5_WIDTH							(480)
#define FORM6_FRAME5_HEIGHT							(120)
#define FORM6_FRAME5_XGAP								(20)
#define FORM6_FRAME5_YGAP								(20)
#define FORM6_FRAME5_ROW								(30 + FORM6_FRAME5_YGAP)

#define FORM6_FRAME6_LEFT								(20)
#define FORM6_FRAME6_TOP								(460)
#define FORM6_FRAME6_WIDTH							(480)
#define FORM6_FRAME6_HEIGHT							(120)
#define FORM6_FRAME6_XGAP								(20)
#define FORM6_FRAME6_YGAP								(20)
#define FORM6_FRAME6_ROW								(30 + FORM6_FRAME6_YGAP)


typedef struct ViewDataForm6ST
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
	GtkWidget * pLabelDeviceName;

	GtkWidget * pLabelDeviceSsn;

	GtkWidget * pLabelMeasZeroBase;
	
	GtkWidget * pLabelMeasLeadOff;
  
	GtkWidget * pLabelLeadOffCompThreshold;

  GtkWidget * pLabelLeadOffCurrent;
  
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	GtkWidget * pEntryDeviceName;

	GtkWidget * pEntryDeviceSsn;
	
	GtkWidget * pEntryLeadOffCompThreshold;
  
	GtkWidget * pEntryLeadOffCurrent;
		
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnDeviceNameSet;
	GtkWidget * pBtnDeviceNameGet;

	GtkWidget * pBtnDeviceReset;

	GtkWidget * pBtnDeviceSsnSet;
	GtkWidget * pBtnDeviceSsnGet;

	GtkWidget * pBtnMeasZeroBaseGet;
	GtkWidget * pBtnMeasZeroBaseOn;
	GtkWidget * pBtnMeasZeroBaseOff;
		
	GtkWidget * pBtnMeasLeadOffGet;
	GtkWidget * pBtnMeasLeadOffEnable;
	GtkWidget * pBtnMeasLeadOffDisable;  
	GtkWidget * pBtnMeasLeadOffCompThresholdSet;
	GtkWidget * pBtnMeasLeadOffCompThresholdGet;
	GtkWidget * pBtnMeasLeadOffCurrSet;
	GtkWidget * pBtnMeasLeadOffCurrGet;
	///--------------------------------------------------------///
	/// Frame (group)
	///--------------------------------------------------------///
	
} ViewDataForm6Type;

#endif ///< __FORM6_H__

