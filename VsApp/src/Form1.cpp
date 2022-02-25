/**
 * @file form1.cpp
 *
 *   View function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

#define FORM1_PROGRESS_BAR_GENERATE_LEFT			(20)
#define FORM1_PROGRESS_BAR_GENERATE_TOP				(80)
#define FORM1_PROGRESS_BAR_GENERATE_WIDTH			(600)
#define FORM1_PROGRESS_BAR_GENERATE_HEIGHT		(60)

#define FORM1_DRAW_AREA_DS0_LEFT							(20)
#define FORM1_DRAW_AREA_DS0_TOP								(150)
#define FORM1_DRAW_AREA_DS0_WIDTH							(1020)
#define FORM1_DRAW_AREA_DS0_HEIGHT						(400)

#define FORM1_CHART_ECG_CANVAS_LEFT						(80)
#define FORM1_CHART_ECG_CANVAS_TOP						(10)
#define FORM1_CHART_ECG_CANVAS_WIDTH					(900)
#define FORM1_CHART_ECG_CANVAS_HEIGHT					(360)

typedef struct GtkDataForm1St
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
  GtkWidget *pLabelMain;
  
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	GtkWidget * pEntryFileName;
	GtkWidget * pEntryChartEcgTime;	
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnBrowse;
	GtkWidget * pBtnGenerate;	
	GtkWidget * pBtnChartEcgRun;		


	GtkWidget * pBtnButton1;
	///--------------------------------------------------------///
	/// ComboBox
	///--------------------------------------------------------///	
	GtkWidget * pComboBoxSpeed;
	
	///--------------------------------------------------------///
	/// Frame (group)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	GtkWidget 		*pProgressBar;

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///
	GtkWidget *pDrawAreaDS0;

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///
	
} ViewDataForm1Type;

static ViewDataForm1Type  	ViewDataForm1;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm1;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// Form1 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	///-----------------------------------------------------------------------///
	/// Label main
	///-----------------------------------------------------------------------///
	pViewDataPtr->pLabelMain =gtk_label_new_with_mnemonic("ECG data analysis, please select file ");
	pLabel = pViewDataPtr->pLabelMain;
  gtk_widget_set_name(pLabel, "form1_label_main");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, 20, 50);
  gtk_widget_show(pLabel);
  //gtk_widget_set_size_request(pLabel, 200, 30); 

  //gtk_widget_set_halign(pLabel, GTK_ALIGN_START);    
 
 	///-----------------------------------------------------------------------///
	/// Label time
	///-----------------------------------------------------------------------///
	pViewDataPtr->pLabelMain =gtk_label_new_with_mnemonic("Time:");
	pLabel = pViewDataPtr->pLabelMain;
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, 20, 560);
  gtk_widget_show(pLabel);

	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	


	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;

	
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
  GtkWidget * pFrame = gtk_frame_new ("");
  
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, 600, 120); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, 10, 10);
  gtk_widget_show(pFrame);

  return iRet;  
}

static JINT ProgressBarInit()
{
	JINT x0		 	= 0;
	JINT y0 		= 0;	
	JINT width 	= 0;
	JINT height	= 0;	
	GtkWidget * pProgressBar = NULL;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	
	///-----------------------------------------------------------------------------------///
	/// Progress bar init
	///-----------------------------------------------------------------------------------///
	pProgressBar = gtk_progress_bar_new();

	x0 			= FORM1_PROGRESS_BAR_GENERATE_LEFT;
	y0 			= FORM1_PROGRESS_BAR_GENERATE_TOP;	
	width 	= FORM1_PROGRESS_BAR_GENERATE_WIDTH;
	height 	= FORM1_PROGRESS_BAR_GENERATE_HEIGHT;
	
 	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pProgressBar, x0, y0);
  gtk_widget_set_size_request(pProgressBar, width, height);  	
  gtk_widget_show(pProgressBar);
  gtk_progress_bar_set_fraction((GtkProgressBar *)pProgressBar, 0);
  gtk_widget_set_name(pProgressBar, "form1_progress_bar1");  
  gtk_widget_show(pProgressBar);  
  pViewDataPtr->pProgressBar = pProgressBar;

  return TRUE;
}

static JINT ComboBoxInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	GtkWidget	*pComboBox = NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	///-----------------------------------------------------------------------///
	/// ComboBox -> Speed
	///-----------------------------------------------------------------------///
	x0 = 280;
	y0 = 560;	
  pComboBox = gtk_combo_box_text_new();
  gtk_widget_set_size_request(pComboBox, 80, 30);   
  gtk_widget_set_name(pComboBox, "");  
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "SLOW: 	50ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Normal: 100ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "High: 	200ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Very High: 1000ms");  
  gtk_combo_box_set_active(GTK_COMBO_BOX(pComboBox), 1);
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pComboBox, x0, y0);
	gtk_widget_show(pComboBox);
  pViewDataPtr->pComboBoxSpeed = pComboBox;
  
	return TRUE;
}

static JINT TimerInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	
	
	return TRUE;
}

static JINT DrawAreaInit()
{
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type *)pThis->pViewData;	


	return TRUE;
}


static JINT ChartInit()
{
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;
	printf("%s show\r\n", pThis->name);
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;
	printf("%s hide\r\n", pThis->name);
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	

 	///-----------------------------------------------------------------------///
	///  View init
	///-----------------------------------------------------------------------///
	pViewDataPtr->pView = gtk_fixed_new();
 	
 	///-----------------------------------------------------------------------///
	///  Label init
	///-----------------------------------------------------------------------///
	LabelInit();

 	///-----------------------------------------------------------------------///
	///  Entry init
	///-----------------------------------------------------------------------///
 	EntryInit();

 	///-----------------------------------------------------------------------///
	///  Button init
	///-----------------------------------------------------------------------///	
	ButtonInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
 	ProgressBarInit();

	///-----------------------------------------------------------------------///
	///  ComboBox Init
	///-----------------------------------------------------------------------///	
	ComboBoxInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	TimerInit();

	///-----------------------------------------------------------------------///
	///  Draw Init
	///-----------------------------------------------------------------------///	
  DrawAreaInit();

	///-----------------------------------------------------------------------///
	///  Chart Init
	///-----------------------------------------------------------------------///	
	ChartInit();
	
//	pViewDataPtr->pWindow = gtk_scrolled_window_new(NULL, NULL);
//	gtk_container_add(GTK_CONTAINER(pViewDataPtr->pWindow),   pViewDataPtr->pView);
//  gtk_widget_show(pViewDataPtr->pWindow);

	gtk_container_add(GTK_CONTAINER(AppPtr->pBox),   pViewDataPtr->pView);

  AppMainMenuSet(pViewDataPtr->pView);
	return TRUE;
}

///--------------------------------------------------------------------------------///
///   Form1 
///--------------------------------------------------------------------------------///
JView JVForm1 = 
{
	"Form1",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm1,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


