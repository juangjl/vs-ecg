/**
 * @file Form2.h
 *
 *  Form2 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM2_H__
#define __FORM2_H__

#include "Global.h"

#define FORM2_FRAME0_LEFT								(20)
#define FORM2_FRAME0_TOP								(50)
#define FORM2_FRAME0_WIDTH							(480)
#define FORM2_FRAME0_HEIGHT							(150)
#define FORM2_FRAME0_XGAP								(20)
#define FORM2_FRAME0_YGAP								(20)
#define FORM2_FRAME0_ROW								(30 + FORM2_FRAME0_YGAP)

#define FORM2_FRAME1_LEFT								(520)
#define FORM2_FRAME1_TOP								(50)
#define FORM2_FRAME1_WIDTH							(480)
#define FORM2_FRAME1_HEIGHT							(540)
#define FORM2_FRAME1_XGAP								(20)
#define FORM2_FRAME1_YGAP								(20)
#define FORM2_FRAME1_ROW								(30 + FORM2_FRAME1_YGAP)

#define FORM2_FRAME2_LEFT								(20)
#define FORM2_FRAME2_TOP								(220)
#define FORM2_FRAME2_WIDTH							(480)
#define FORM2_FRAME2_HEIGHT							(150)
#define FORM2_FRAME2_XGAP								(20)
#define FORM2_FRAME2_YGAP								(20)
#define FORM2_FRAME2_ROW								(30 + FORM2_FRAME2_YGAP)

#define FORM2_FRAME3_LEFT								(20)
#define FORM2_FRAME3_TOP								(390)
#define FORM2_FRAME3_WIDTH							(480)
#define FORM2_FRAME3_HEIGHT							(150)
#define FORM2_FRAME3_XGAP								(20)
#define FORM2_FRAME3_YGAP								(20)
#define FORM2_FRAME3_ROW								(30 + FORM2_FRAME3_YGAP)



typedef struct GtkDataForm2St
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
	GtkWidget * pLabelCom;
		
	///--------------------------------------------------------///
	/// Entry
	///--------------------------------------------------------///
	GtkWidget * pEntryCom;	
	GtkWidget * pEntryDataDir;		
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnComBrowse;	
	GtkWidget * pBtnComOpen;		
	GtkWidget * pBtnComClose;			
	GtkWidget * pBtnBrowse;	
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	GtkWidget *pProgressBar;

	///--------------------------------------------------------///
	/// List Box
	///--------------------------------------------------------///
	GtkWidget * pListBox1;

} ViewDataForm2Type;

extern void CallbackForm2ListBox1RowActivated (GtkListBox* self, GtkListBoxRow* pRowSelected,  gpointer user_data);

#endif ///< __FORM2_H__
