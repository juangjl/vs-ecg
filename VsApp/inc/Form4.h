/**
 * @file Form4.h
 *
 *  Form4 Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __Form4_H__
#define __Form4_H__

///------------------------------------------------------------------------------------------------///
/// FRAME
///------------------------------------------------------------------------------------------------///
#define Form4_FRAME0_LEFT											(20)
#define Form4_FRAME0_TOP											(60)
#define Form4_FRAME0_WIDTH										(1120)
#define Form4_FRAME0_HEIGHT										(320)
#define Form4_FRAME0_XGAP											(20)
#define Form4_FRAME0_YGAP											(10)
#define Form4_FRAME0_ROW											(30 + Form4_FRAME0_YGAP)

#define Form4_FRAME1_LEFT											(20)
#define Form4_FRAME1_TOP											(390)
#define Form4_FRAME1_WIDTH										(1120)
#define Form4_FRAME1_HEIGHT										(450)
#define Form4_FRAME1_XGAP											(20)
#define Form4_FRAME1_YGAP											(20)
#define Form4_FRAME1_ROW											(30 + Form4_FRAME1_YGAP)

///------------------------------------------------------------------------------------------------///
/// DRAW AREA
///------------------------------------------------------------------------------------------------///
#define Form4_DRAW_AREA0_LEFT									(Form4_FRAME1_LEFT + 20)
#define Form4_DRAW_AREA0_TOP								  (Form4_FRAME1_TOP + 20)
#define Form4_DRAW_AREA0_WIDTH								(1020)
#define Form4_DRAW_AREA0_HEIGHT								(600)

///------------------------------------------------------------------------------------------------///
/// CHART
///------------------------------------------------------------------------------------------------///
#define Form4_CHART0_LEFT											(80)
#define Form4_CHART0_TOP											(10)
#define Form4_CHART0_WIDTH										(1000)
#define Form4_CHART0_HEIGHT										(400)


typedef struct ViewDataForm4St
{
	JBOOL bShow;
	///--------------------------------------------------------///
	/// Window --> Box --> View(Fixed)
	///--------------------------------------------------------///
	GtkWidget * pWindow;
	GtkWidget * pView;

	///--------------------------------------------------------///
	/// Label
	///--------------------------------------------------------///
  GtkWidget * pLabelDate;
	GtkWidget * pLabelTime;
	
	GtkWidget * pLabelEcgHR;
	GtkWidget * pLabelTemp;
	GtkWidget * pLabelEcgLeadOff;	
	
	GtkWidget * pLabelGSenXNow;
	GtkWidget * pLabelGSenYNow;
	GtkWidget * pLabelGSenZNow;

	GtkWidget * pLabelBattSoc;
	GtkWidget * pLabelBattSec;

	GtkWidget * pLabelHrvSDNN;
	GtkWidget * pLabelHrvNN50;
	GtkWidget * pLabelHrvRMSSD;
	GtkWidget * pLabelHrvRR;
		
	GtkWidget * pLabelHrvVLF;
	GtkWidget * pLabelHrvLF;	
	GtkWidget * pLabelHrvHF;		
	GtkWidget * pLabelHrvLFHF;	

	GtkWidget * pLabelHrvTP;		
	GtkWidget * pLabelHrvLFTP;	
	GtkWidget * pLabelHrvHFTP;		

	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// Frame 
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///
	GtkWidget *	pDrawArea0;

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///
	JChart 			Chart0;

} ViewDataForm4Type;


extern void Form4LabelInfoUpdate(void);

#endif ///< for __CMD_H__

