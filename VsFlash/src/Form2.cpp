/**
 * @file Form2.cpp
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
#include "Form2.h"

ViewDataForm2Type  	ViewDataForm2;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm2;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackBtnComBrowseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	
	GtkWidget *dialog = NULL;
	GtkFileChooserAction action   = GTK_FILE_CHOOSER_ACTION_OPEN;	
		
	gint iRet = 0;
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

	iRet = gtk_dialog_run (GTK_DIALOG (dialog));
	if(iRet == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *pFileChooser = GTK_FILE_CHOOSER (dialog);
    pFileName = gtk_file_chooser_get_filename (pFileChooser);
    ConfigStrSet((char *)CONFIG_ITEM_SERIAL_PORT, pFileName);
    
	  gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryCom), pFileName);    		  
    g_free (pFileName);   	
  }

	gtk_widget_destroy (dialog);
}

static void CallbackBtnComOpenClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
  char strComName[256];
  char msg[256];

  GlobalVar.dwSysCtl5 |= SYS_CTL5_SERIAL_PORT_OPEN;	
}

static void CallbackBtnComCloseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	char msg[256];
  GlobalVar.dwSysCtl5 |= SYS_CTL5_SERIAL_PORT_CLOSE;
}

static void CallbackEntryComChanged(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	char *pStrCom = NULL;
	char msg[256];
	char strCom[256];

	pStrCom =  (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryCom));    
  ConfigStrSet((char *)CONFIG_ITEM_SERIAL_PORT, pStrCom);
  sprintf(msg, "[ENTRY] COM = %s\r\n", pStrCom);
  DBG_PRINTF(msg);
}

JINT CallbackForm2Timer1 (gpointer data)
{    
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * ) pThis->pViewData;
	char str[256];

	///------------------------------------------------------------------------------------///
	///	Serial port
	///------------------------------------------------------------------------------------///
	if(GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelCom), "serial port is open");
		JViewButtonDisable(pViewDataPtr->pBtnComOpen);
		JViewButtonEnable(pViewDataPtr->pBtnComClose);		
	}
	else
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelCom), "serial port is closed");
		JViewButtonDisable(pViewDataPtr->pBtnComClose);
		JViewButtonEnable(pViewDataPtr->pBtnComOpen);				
	}	
	
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Form2 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	

	JINT w 	= 0;
	JINT h 	= 0;	

	char strBleDeviceName[256];
	char strBleDeviceMac[256];
	
	///-----------------------------------------------------------------------///
	/// Label: LabelCom
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + 220;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_ROW * 2 + 10;  
	pViewDataPtr->pLabelCom = gtk_label_new_with_mnemonic("");
	pLabel = pViewDataPtr->pLabelCom;
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);

	
	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	char strValue[256];

	strcpy(strValue, "");
	
	///-----------------------------------------------------------------------///
	/// Entry com
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + FORM2_FRAME0_XGAP;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_ROW;
	ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, strValue);
	pEntry = pViewDataPtr->pEntryCom;
	pEntry =  gtk_entry_new(); 
	pViewDataPtr->pEntryCom = pEntry; 	
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "please set com port");
  gtk_widget_set_name(pEntry, "");  
  gtk_widget_set_size_request(pEntry, 360, 20); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  gtk_entry_set_text(GTK_ENTRY(pEntry), strValue);    
  g_signal_connect(G_OBJECT(pEntry),   "changed",   G_CALLBACK(CallbackEntryComChanged), NULL);  
  gtk_widget_show(pEntry);


	return iRet;	
}

static JINT ButtonInit(void)
{
ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet 					= TRUE;
	GtkWidget *pButton 	= NULL;
		
	JINT x0 = 0;
	JINT y0 = 0;
	
	JINT w = 0;
	JINT h = 0;	

#ifndef ARCH_WIN32	 	
	///-----------------------------------------------------------------------///
	/// Button -> ComBrowse
	///-----------------------------------------------------------------------///
	x0 = 420;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_ROW;
	pViewDataPtr->pBtnComBrowse = gtk_button_new_with_label("Browse");
	pButton = pViewDataPtr->pBtnComBrowse;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnComBrowseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
#endif ///< for not ARCH_WIN32

	///-----------------------------------------------------------------------///
	/// Button -> ComOpen
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + FORM2_FRAME0_XGAP;
	y0 = FORM2_FRAME0_TOP  + 2 * FORM2_FRAME0_ROW;
	pViewDataPtr->pBtnComOpen = gtk_button_new_with_label("Open");
	pButton = pViewDataPtr->pBtnComOpen;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnComOpenClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  

	///-----------------------------------------------------------------------///
	/// Button -> ComClose
	///-----------------------------------------------------------------------///
	x0 = x0 + 100;
	y0 = FORM2_FRAME0_TOP  + 2 * FORM2_FRAME0_ROW;
	pViewDataPtr->pBtnComClose = gtk_button_new_with_label("Close");
	pButton = pViewDataPtr->pBtnComClose;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnComCloseClicked), NULL);
  gtk_widget_set_name(pButton, "button_browse");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  

	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
  GtkWidget * pFrame = NULL;

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;

	///-----------------------------------------------------------------------///
	/// Frame: Serial Port
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT;
	y0 = FORM2_FRAME0_TOP;
  w  = FORM2_FRAME0_WIDTH;
  h  = FORM2_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("Serial Port");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.01, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	
  return iRet;  
}

static JINT ImageInit()
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 900;
	JINT y0 = 650;

	pImage = gtk_image_new_from_file ("img/logo-black.png");
	gtk_widget_set_size_request(pImage, 0, 10); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pImage, x0, y0);
  
  gtk_widget_show(pImage);

	return TRUE;
}

static JINT TimerInit()
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;	
	
	g_timeout_add(500, CallbackForm2Timer1, (gpointer)pViewDataPtr->pView);	
		
	return TRUE;
}

static JINT DrawAreaInit()
{

	return TRUE;
}

static JINT ChartInit()
{
	return TRUE;
}

static JINT ListInit()
{	
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow(void)
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide(void)
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit(void)
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;	

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

	///-----------------------------------------------------------------------///
	///  List Init
	///-----------------------------------------------------------------------///	
	ListInit();
	
	gtk_container_add(GTK_CONTAINER(AppPtr->pBox),   pViewDataPtr->pView);

  AppMainMenuSet(pViewDataPtr->pView);
	return TRUE;
}

///--------------------------------------------------------------------------------///
///   Form2 
///--------------------------------------------------------------------------------///
JView JVForm2 = 
{
	"Form2",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm2,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};
