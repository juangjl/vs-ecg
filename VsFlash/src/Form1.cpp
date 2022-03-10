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
#include "Form1.h"

ViewDataForm1Type  	ViewDataForm1;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm1;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackForm1EntryFileNameActive(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	printf("entry activate\r\n");
	/// let the widget not focused
	gtk_widget_grab_focus(pViewDataPtr->pBtnBrowse);
}

static void CallbackForm1BtnBrowseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	GtkWidget *dialog = NULL;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
  char *pFileName = NULL;
	
	JINT iTimeMS = 0;
	char strTime[256];


	dialog = gtk_file_chooser_dialog_new ("Open File",
	                                      GTK_WINDOW(AppPtr->pWindow),
	                                      action,
	                                      "_Cancel",
	                                      GTK_RESPONSE_CANCEL,
	                                      "_Open",
	                                      GTK_RESPONSE_ACCEPT,
	                                      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if(res == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    pFileName = gtk_file_chooser_get_filename (chooser);
		ConfigStrSet((char *)CONFIG_ITEM_FILE_NAME, pFileName);
	  gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryFileName), pFileName);    
	  
    g_free (pFileName);
   	gtk_widget_grab_focus(pViewDataPtr->pBtnFlashStart);	
  }

	gtk_widget_destroy (dialog);
}

static void CallbackForm1BtnFlashStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;	
  GlobalVar.dwSysCtl5 |= SYS_CTL5_FLASH_START;	
}

static void CallbackForm1BtnFlashCancelClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;	
  GlobalVar.dwSysCtl5 |= SYS_CTL5_FLASH_CANCEL;	
}

JINT CallbackForm1Timer1 (gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;    

	///------------------------------------------------------------------------------------///
	///	Serial port
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)	
	{	
		JViewButtonDisable(pViewDataPtr->pBtnFlashStart);
		JViewButtonDisable(pViewDataPtr->pBtnFlashCancel);				
	}	

	if(GlobalVar.bFlashStart == TRUE)
	{
		JViewButtonDisable(pViewDataPtr->pBtnFlashStart);
		JViewButtonEnable(pViewDataPtr->pBtnFlashCancel);
	}
	else
	{
		JViewButtonEnable(pViewDataPtr->pBtnFlashStart);
		JViewButtonDisable(pViewDataPtr->pBtnFlashCancel);
	}

	return (TRUE);
}

JINT CallbackForm1Timer2 (gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	char str[256];

	if(GlobalVar.bDFUWriteOn == TRUE)
	{
		sprintf(str, "Progress = %3.1f%%, time eclapsed %d seconds", GlobalVar.fProgress, GlobalVar.iDfuEclapse);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelDFU), str);
		/// Set progress
	  gtk_progress_bar_set_fraction((GtkProgressBar *)pViewDataPtr->pProgressBar, (GlobalVar.fProgress / 100));	
	}

	return (TRUE);
}

///------------------------------------------------------------------------------------///
/// Form1 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w = 0;
	JINT h = 0;

	///-----------------------------------------------------------------------///
	/// Label: LabelDFU
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + 320;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME1_ROW * 2 + 10;  
	pLabel  = gtk_label_new_with_mnemonic("");	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelDFU = pLabel;

	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
		
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w 	= 0;
	JINT h 	= 0;

	char strValue[256];

	///-----------------------------------------------------------------------///
	/// Entry File Name
	///-----------------------------------------------------------------------///
	x0 	= FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP;
	y0 	= FORM1_FRAME0_TOP  + FORM1_FRAME0_ROW;
	w 	= 600;
	h 	= 20;
	ConfigStrGet((char *)CONFIG_ITEM_FILE_NAME, strValue);
	pEntry=  gtk_entry_new(); 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "please browse the input file");
  gtk_widget_set_name(pEntry, "form1_entry_filepath");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
	gtk_entry_set_text(GTK_ENTRY(pEntry), strValue);    
  g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm1EntryFileNameActive), NULL);
  gtk_widget_show(pEntry);
	pViewDataPtr->pEntryFileName = pEntry;

	return TRUE;	
}

static JINT ButtonInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 0;
	JINT h = 0;

	///-----------------------------------------------------------------------///
	/// Button -> Browse
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + 640;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_ROW;
	w = 80;
	h = 30;

	pViewDataPtr->pBtnBrowse = gtk_button_new_with_label("Browse");
	pButton = pViewDataPtr->pBtnBrowse;
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnBrowseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBrowse = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> Flash
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_YGAP + FORM1_FRAME0_ROW * 2;
	w = 100;
	h = 30;
	pViewDataPtr->pBtnBrowse = gtk_button_new_with_label("Flash");
	pButton = pViewDataPtr->pBtnBrowse;
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnFlashStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnFlashStart  = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> Cancel
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP +  120;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_YGAP + FORM1_FRAME0_ROW * 2;
	w = 100;
	h = 30;
	pViewDataPtr->pBtnBrowse = gtk_button_new_with_label("Cancel");
	pButton = pViewDataPtr->pBtnBrowse;
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnFlashCancelClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnFlashCancel = pButton;
	
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
  GtkWidget * pFrame = NULL;
	
  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
  
	///-----------------------------------------------------------------------///
	/// Frame0: ECG Info
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT;
	y0 = FORM1_FRAME0_TOP;
  w  = FORM1_FRAME0_WIDTH;
  h  = FORM1_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("Information");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);


  return iRet;  
}

static JINT ImageInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 530;
	JINT y0 = 650;

	pImage = gtk_image_new_from_file ("img/logo-black.png");
	gtk_widget_set_size_request(pImage, 0, 10); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pImage, x0, y0);
  
  gtk_widget_show(pImage);

	return TRUE;
}

static JINT TimerInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
		
	g_timeout_add(500, CallbackForm1Timer1, (gpointer)pViewDataPtr->pView);	
	g_timeout_add(100, CallbackForm1Timer2, (gpointer)pViewDataPtr->pView);	

	return TRUE;
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

static JINT DrawAreaInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 


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
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
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
	///  Frame init
	///-----------------------------------------------------------------------///	
	FrameInit();

	///-----------------------------------------------------------------------///
	///  Image init
	///-----------------------------------------------------------------------///	
	ImageInit();

 	///-----------------------------------------------------------------------///
	///  Button init
	///-----------------------------------------------------------------------///	
	ButtonInit();

	///-----------------------------------------------------------------------///
	///  Timer init
	///-----------------------------------------------------------------------///	
	TimerInit();

///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	ProgressBarInit();

	///-----------------------------------------------------------------------///
	///  Draw Init
	///-----------------------------------------------------------------------///	
  DrawAreaInit();

	///-----------------------------------------------------------------------///
	///  Chart Init
	///-----------------------------------------------------------------------///	
	ChartInit();
	
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


