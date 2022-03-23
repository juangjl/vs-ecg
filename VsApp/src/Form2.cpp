/**
 * @file Form2.cpp
 *
 *   View function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"
#include "Form2.h"

static ViewDataForm2Type  ViewDataForm2;
///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm2;

///------------------------------------------------------------------------------------///
/// FORM2 LIST 1
///------------------------------------------------------------------------------------///
JINT Form2List1RowDeleteAll()
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox 			 =  pViewDataPtr->pListBox1;
	
	GList *	pChildren = NULL;
	GList *	pItem 		= NULL;
	
	JBOOL 	bRet = TRUE;
	JINT i = 0;

	pChildren = gtk_container_get_children(GTK_CONTAINER(pListBox));
	
	for(pItem = pChildren; pItem != NULL; pItem = g_list_next(pItem))
	{
		if(i > 0)
		{
  		gtk_widget_destroy(GTK_WIDGET(pItem->data));
		}
		i = i + 1;
	}
	
	g_list_free(pChildren);

	return bRet;
}

JINT Form2List1RowDelete(JINT idx)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = 	pViewDataPtr->pListBox1 ;
	
	GList *children = NULL;
	GList *iter = NULL;
	JINT i = 0;
	JBYTE bRet = FALSE;

	children = gtk_container_get_children(GTK_CONTAINER(pListBox));
	
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	{
		if(i == idx)
		{
	  	gtk_widget_destroy(GTK_WIDGET(iter->data));
	  	bRet = TRUE;
	  	break;
		}
 		i = i + 1;
	}
	
	g_list_free(children);

	return bRet;
}

JINT Form2List1RowAdd(char *strValue0, char *strValue1, char *strValue2)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
		
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

  JINT h  = 500;
  JINT w  = 440;

	row = gtk_list_box_row_new();
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	
	label0 = gtk_label_new(strValue0);
	label1 = gtk_label_new(strValue1);
	label2 = gtk_label_new(strValue2);	

	gtk_widget_set_size_request(label0, 80, 	30); 
	gtk_widget_set_size_request(label1, 340, 	30); 
	gtk_widget_set_size_request(label2, 20, 	30); 

	//gtk_label_set_xalign(GTK_LABEL(label0), 0.01);

	gtk_box_pack_start(GTK_BOX(hbox), label0, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0);
	gtk_widget_set_size_request(hbox, w, 30); 
	
	gtk_container_add(GTK_CONTAINER(row), hbox);	
	gtk_container_add(GTK_CONTAINER(pListBox), row);
	gtk_widget_show_all(row);
	return TRUE;
}

static JINT Form2List1HeaderSet()
{	
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
	
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

  JINT w  = 440;
  
	//----------------------------------------------------------------///
	/// header
	///----------------------------------------------------------------///	
	row = gtk_list_box_row_new();
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(hbox, "list_header");
	label0 = gtk_label_new("#");
	label1 = gtk_label_new("Serial Port");
	label2 = gtk_label_new("");	

	gtk_widget_set_size_request(label0, 80, 	30); 
	gtk_widget_set_size_request(label1, 340, 	30); 
	gtk_widget_set_size_request(label2, 20, 	30); 
	
  gtk_widget_set_name(label0, "list1_header0");  
  gtk_widget_set_name(label1, "list1_header1");  
  gtk_widget_set_name(label2, "list1_header2");    
	/// insert labels into hbox
	
	gtk_box_pack_start(GTK_BOX(hbox), label0, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0);

	gtk_list_box_row_set_activatable((GtkListBoxRow * )row , FALSE);
	gtk_list_box_row_set_selectable((GtkListBoxRow * )row , FALSE);
	gtk_widget_set_size_request(hbox, w, 30); 
	/// insert hbox into rpw	
	gtk_container_add(GTK_CONTAINER(row), hbox);

	gtk_container_add(GTK_CONTAINER(pListBox), row);

	return TRUE;	
}

static JINT Form2List1Init()
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = NULL;

	JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;

	GtkWidget *label1 = NULL;
	GtkWidget	*label2 = NULL;
	GtkWidget	*label3 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

	x0 = FORM2_FRAME1_LEFT + FORM2_FRAME1_XGAP;
	y0 = FORM2_FRAME1_TOP  + FORM2_FRAME1_YGAP ;
  w  = 440;
  h  = 500;

	///----------------------------------------------------------------///
	///  Create the listbox 
	///----------------------------------------------------------------///	
	pListBox = gtk_list_box_new();
	pViewDataPtr->pListBox1 = pListBox;

	///----------------------------------------------------------------///
	/// header
	///----------------------------------------------------------------///	
	Form2List1HeaderSet();
	
	///----------------------------------------------------------------///
	/// list show
	///----------------------------------------------------------------///	
	gtk_widget_set_size_request(pListBox, w, h); 
	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pListBox, x0, y0);
	gtk_widget_show_all(pListBox);
	gtk_widget_show(pListBox);

	g_signal_connect(G_OBJECT(pListBox), "row-activated",   G_CALLBACK(CallbackForm2ListBox1RowActivated), NULL);
	
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackForm2BtnComBrowseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
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

static void CallbackForm2BtnComOpenClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
  char strComName[256];
  char msg[256];

  GlobalVar.dwSysCtl5 |= SYS_CTL5_SERIAL_PORT_OPEN;	
}

static void CallbackForm2BtnComCloseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	char msg[256];
  GlobalVar.dwSysCtl5 |= SYS_CTL5_SERIAL_PORT_CLOSE;
}

static void CallbackForm2BtnBrowseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	GtkWidget *dialog = NULL;
	//GtkFileChooserAction action   = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
	gint res;
  char *pFileName = NULL;
	JDataSet *pDataSet = &GlobalVar.dataSet[DATASET_DS0];

	char strTime[256];

	dialog = gtk_file_chooser_dialog_new ("Folder select",
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
    GtkFileChooser *pFileChooser = GTK_FILE_CHOOSER (dialog);
    pFileName = gtk_file_chooser_get_filename (pFileChooser);
	  gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryDataDir), pFileName);    
    ConfigStrSet((char *)CONFIG_ITEM_DATA_ROOT, pFileName);
		strcpy(GlobalVar.strDataDir, pFileName);
    g_free (pFileName);  	
  }

	gtk_widget_destroy (dialog);
}

static void CallbackForm2EntryComChanged(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	char * pStr = NULL;
	char msg[256];
	GtkWidget * pEntry = pViewDataPtr->pEntryCom;

	pStr =  (char *) gtk_entry_get_text(GTK_ENTRY(pEntry));    
  ConfigStrSet((char *)CONFIG_ITEM_SERIAL_PORT, pStr);
	
  sprintf(msg, "[ENTRY] DATA DIR = %s\r\n", pStr);
  DBG_PRINTF(msg);
}

static void CallbackForm2EntryDataDirChanged(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	char * pStr = NULL;
	char msg[256];
	GtkWidget * pEntry = pViewDataPtr->pEntryDataDir;

	pStr =  (char *) gtk_entry_get_text(GTK_ENTRY(pEntry));    
  ConfigStrSet((char *)CONFIG_ITEM_SERIAL_PORT, pStr);
	strcpy(GlobalVar.strDataDir, pStr);
  sprintf(msg, "[ENTRY] DATA DIR = %s\r\n", pStr);
  DBG_PRINTF(msg);
}

gint CallbackForm2Timer1 (gpointer data)
{    
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * ) pThis->pViewData;
	static JINT iSec = 0;
	char msg[256];
	
	JINT i = 0;
	char strValue0[256];
	char strValue1[256];
	char strValue2[256];

	if(pViewDataPtr->bShow == FALSE)
	{
		return TRUE;
	}

	///---------------------------------------------------------------------------///
	/// UI: ort open UI set
	///---------------------------------------------------------------------------///
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

	///---------------------------------------------------------------------------///
	/// UI: Serial port detect
	///---------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
		if(iSec % 5 == 0)
		{
			FuncSerialPortDetect();
			Form2List1RowDeleteAll();

			for(i = 0 ; i < GlobalVar.iSerialPortArrCnt; i = i + 1)
			{			
				sprintf((char *)&strValue0[0], "%02d", (i + 1));
				sprintf((char *)&strValue1[0], "%s", (char *)&GlobalVar.strSerialPortArr[i][0]);
				sprintf((char *)&strValue2[0], "%s", "");

				Form2List1RowAdd((char *)&strValue0[0], (char *)&strValue1[0], (char *)&strValue2[0]);
			}
		}
	}

	///---------------------------------------------------------------------------///
	/// UI: Serial Port OPEN Failed
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl7 & SYS_CTL7_MSG_SERIAL_POR_OPEN_FAILED)
	{
		sprintf(msg, "%s", "Failed to open serial port");
		MESSAGE_BOX(msg);
		GlobalVar.dwSysCtl7 &=~SYS_CTL7_MSG_SERIAL_POR_OPEN_FAILED;
	}

	iSec = (iSec + 1) % 1000;
	return TRUE;
}

void CallbackForm2ListBox1RowActivated (GtkListBox* self, GtkListBoxRow* pRowSelected,  gpointer user_data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox 			 =  pViewDataPtr->pListBox1;
	GtkListBoxRow* pRow = NULL;
	GList *pChildren = NULL;
	GList *pItem 		= NULL;
	JINT iRow  = -1;
	JBYTE bRet = FALSE;

	char strSerialPortame[256];


	pChildren = gtk_container_get_children(GTK_CONTAINER(pListBox));
	
	for(pItem = pChildren; pItem != NULL; pItem = g_list_next(pItem))
	{
		pRow = (GtkListBoxRow*)(pItem->data);
		if(pRow == pRowSelected)
		{
	  	break;
		}
 		iRow = iRow + 1;
	}
	
	g_list_free(pChildren);
	printf("\t ROW  = %d \r\n", iRow);
	if(iRow >= 0)
	{
		/// get the items
		if(GlobalVar.iSerialPortArrCnt > iRow)
		{			
			strcpy(strSerialPortame, GlobalVar.strSerialPortArr[iRow]);
			ConfigStrSet((char *)CONFIG_ITEM_SERIAL_PORT, strSerialPortame);	
			gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryCom), strSerialPortame);
		}
		else
		{
			printf("[ERROR] the row (%d) > data count (%d)\r\n", iRow, 0);
		}
	}
	else
	{
		printf("[ERROR] the row (%d)  not found !!\r\n", iRow);
	}

	gtk_list_box_unselect_all((GtkListBox*)pListBox);

}

static  void CallbackForm2RadioButton1Clicked(GtkWidget *pButton,  gpointer pData)
{
	char msg[256];
	JINT  iSelect = *(JINT *)pData;
	JBOOL bActive = FALSE;

	bActive = gtk_toggle_button_get_active((GtkToggleButton*) pButton);
	if(bActive == FALSE)
	{
		return;
	}

	if(UtilMemcmp((JBYTE *)pData, (JBYTE *)"ON", 2) == MEMCMP_SAME)
	{
		GlobalVar.bVscModeSave = TRUE;
		ConfigStrSet((char *)CONFIG_ITEM_VSC_MODE_SAVE, (char *)"ON");
	}
	else
	{
		GlobalVar.bVscModeSave = FALSE;
		ConfigStrSet((char *)CONFIG_ITEM_VSC_MODE_SAVE, (char *) "OFF");
	}


	sprintf(msg, "\t\t [FORM2][RADIO1] ACTIVE = %d, SELECT = %s\r\n", bActive, (char *)pData);	
	DBG_PRINTF(msg);
}


///------------------------------------------------------------------------------------///
/// FORM2 RADIO Button
///------------------------------------------------------------------------------------///
void Form2RadioButton1Init(void)
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;	
	GtkWidget *pRadioButton = NULL;
	GtkWidget *pRadioButton1 = NULL;
	GtkWidget *pRadioButton2 = NULL;	

	JINT x0 = 0;
	JINT y0 = 0;
	JINT w  = 0;
	JINT h  = 0;	
		
	///-----------------------------------------------------------------------///
	/// Radio Button1
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME3_LEFT + FORM2_FRAME3_XGAP;
	y0 = FORM2_FRAME3_TOP  + FORM2_FRAME3_ROW;
	w  = 100;
	h  = 30;
	const char *pRadioBtnValue[] ={
														"ON",	
														"OFF",		
													};
	JINT idxRadioBtn = 0;													

	pRadioButton = 	gtk_radio_button_new_with_label(NULL, pRadioBtnValue[idxRadioBtn]);
	gtk_widget_set_size_request(pRadioButton, w, h); 
	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pRadioButton, x0, y0);
  gtk_widget_show(pRadioButton);	
	g_signal_connect(G_OBJECT(pRadioButton), "clicked",   G_CALLBACK(CallbackForm2RadioButton1Clicked), (void *) pRadioBtnValue[idxRadioBtn]);
	pRadioButton1 = pRadioButton;
	idxRadioBtn = idxRadioBtn + 1;

	// Create a radio button with a label
	x0 = FORM2_FRAME3_LEFT + FORM2_FRAME3_XGAP + 120;
	y0 = FORM2_FRAME3_TOP  + FORM2_FRAME3_ROW;
	w  = 100;
	h  = 30;

	pRadioButton = 	gtk_radio_button_new_with_label(NULL, pRadioBtnValue[idxRadioBtn]);
  gtk_radio_button_join_group( (GtkRadioButton *)pRadioButton, (GtkRadioButton *)pRadioButton1);
	gtk_widget_set_size_request(pRadioButton, w, h); 
	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pRadioButton, x0, y0);
  gtk_widget_show(pRadioButton);	
	g_signal_connect(G_OBJECT(pRadioButton), "clicked",   G_CALLBACK(CallbackForm2RadioButton1Clicked), (void *) pRadioBtnValue[idxRadioBtn]);
	pRadioButton2 = pRadioButton;
	idxRadioBtn   = idxRadioBtn + 1;

	///----------------------------------------------------------------------///
	///	 Set active
	///----------------------------------------------------------------------///
	if(GlobalVar.bVscModeSave == TRUE)
	{
		gtk_toggle_button_set_active((GtkToggleButton *)pRadioButton1, TRUE);
	}
	else
	{
		gtk_toggle_button_set_active((GtkToggleButton *)pRadioButton2, TRUE);
	}

	return;
}


///------------------------------------------------------------------------------------///
/// Init Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	GtkStyleContext *pContext = NULL;

	///-----------------------------------------------------------------------///
	/// Label: COM_PORT
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + FORM2_FRAME0_XGAP;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_YGAP;  
	pLabel = gtk_label_new_with_mnemonic("COM port setting");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_default");  		
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: FOLDER PATH
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_YGAP;
	pLabel = gtk_label_new_with_mnemonic("COM port setting");
	pContext = gtk_widget_get_style_context(pLabel);	  
	gtk_style_context_add_class(pContext, "label_default");  		
	pLabel = gtk_label_new_with_mnemonic("Data save folder setting");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: LabelCom
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + 220;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_ROW * 2 + 10;  	
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	  
	gtk_style_context_add_class(pContext, "label_default");  		
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);
  pViewDataPtr->pLabelCom = pLabel;
  
  return TRUE;  
}

static JINT EntryInit(void) 
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 300;
	JINT h  = 20;

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
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  gtk_entry_set_text(GTK_ENTRY(pEntry), strValue);    
  g_signal_connect(G_OBJECT(pEntry),   "changed",   G_CALLBACK(CallbackForm2EntryComChanged), NULL);  
  gtk_widget_show(pEntry);

 	///-----------------------------------------------------------------------///
	/// Entry data folder
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW;
	ConfigStrGet((char *)CONFIG_ITEM_DATA_ROOT, strValue);	
	pEntry =  gtk_entry_new(); 
	pViewDataPtr->pEntryDataDir = pEntry; 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "please browse for data folder");
  gtk_widget_set_name(pEntry, "");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  gtk_entry_set_text(GTK_ENTRY(pEntry), strValue);    
  g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm2EntryDataDirChanged), NULL);
  gtk_widget_show(pEntry);

  return TRUE;
}

static JINT ButtonInit(void)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;
	JINT iRet 					= TRUE;
	GtkWidget *pButton 	= NULL;
		
	JINT x0 = 0;
	JINT y0 = 0;

	///-----------------------------------------------------------------------///
	/// Radio Button1
	///-----------------------------------------------------------------------///
	Form2RadioButton1Init();

#ifndef ARCH_WIN32	 	
	///-----------------------------------------------------------------------///
	/// Button -> ComBrowse
	///-----------------------------------------------------------------------///
	x0 = 360;
	y0 = FORM2_FRAME0_TOP  + FORM2_FRAME0_ROW;
	pViewDataPtr->pBtnComBrowse = gtk_button_new_with_label("Browse");
	pButton = pViewDataPtr->pBtnComBrowse;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm2BtnComBrowseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
#endif ///< for not ARCH_WIN32

	///-----------------------------------------------------------------------///
	/// Button -> ComOpen
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME0_TOP  + 2 * FORM2_FRAME0_ROW;
	pViewDataPtr->pBtnComOpen = gtk_button_new_with_label("Open");
	pButton = pViewDataPtr->pBtnComOpen;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm2BtnComOpenClicked), NULL);
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
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm2BtnComCloseClicked), NULL);
  gtk_widget_set_name(pButton, "button_browse");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  

 	///-----------------------------------------------------------------------///
	/// Button -> DataBarowse
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW * 2;
	pViewDataPtr->pBtnBrowse = gtk_button_new_with_label("Browse");
	pButton = pViewDataPtr->pBtnBrowse;
  gtk_widget_set_size_request(pButton, 80, 30); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm2BtnBrowseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	 
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
  GtkWidget * pFrame = NULL;
	GtkStyleContext *pContext = NULL;

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;

	///-----------------------------------------------------------------------///
	/// Frame: COM
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME0_LEFT;
	y0 = FORM2_FRAME0_TOP;
  w  = FORM2_FRAME0_WIDTH;
  h  = FORM2_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("COM");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: SERIAL PORT LIST
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME1_LEFT;
	y0 = FORM2_FRAME1_TOP;
  w  = FORM2_FRAME1_WIDTH;
  h  = FORM2_FRAME1_HEIGHT;

  pFrame = gtk_frame_new ("Serial Port");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);


	///-----------------------------------------------------------------------///
	/// Frame: DATA DIR
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT;
	y0 = FORM2_FRAME2_TOP;
  w  = FORM2_FRAME2_WIDTH;
  h  = FORM2_FRAME2_HEIGHT;

  pFrame = gtk_frame_new ("Data Folder");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  	
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: DATA SAVE
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME3_LEFT;
	y0 = FORM2_FRAME3_TOP;
  w  = FORM2_FRAME3_WIDTH;
  h  = FORM2_FRAME3_HEIGHT;

  pFrame = gtk_frame_new ("Data Save");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  	
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);


  return iRet;  
}

static JINT ImageInit(void)
{
	ViewDataForm2Type * pViewDataPtr = &ViewDataForm2;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 530;
	JINT y0 = 650;

	char strFileName[256];
	sprintf(strFileName, "%s", "img/logo-black.png");

	if(UtilFileExisted(strFileName) == FALSE)
	{
		if(GlobalVar.iOSType == OS_TYPE_MAC_OS)
		{
			sprintf(strFileName, "/Users/Shared/VsEcg/img/logo-black.png");
		}
		if(GlobalVar.iOSType == OS_TYPE_UBUNTU)
		{
			sprintf(strFileName, "/usr/share/VsEcg/img/logo-black.png");
		}
		if(UtilFileExisted(strFileName) == FALSE)
		{
			return FALSE;
		}
	}

	pImage = gtk_image_new_from_file (strFileName);

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

static JINT ListInit()
{
	Form2List1Init();
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * )pThis->pViewData;	
  gtk_widget_show(pViewDataPtr->pView);
  pViewDataPtr->bShow = TRUE;
    
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * )pThis->pViewData;	
  gtk_widget_hide(pViewDataPtr->pView);
  pViewDataPtr->bShow = FALSE;
    
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * )pThis->pViewData;	
	GtkWidget *pButton 	= NULL;
  
	pViewDataPtr->pView = gtk_fixed_new();

	///-----------------------------------------------------------------------///
	/// Label init
	///-----------------------------------------------------------------------///
	LabelInit();

 	///-----------------------------------------------------------------------///
	///  Entry init
	///-----------------------------------------------------------------------///
 	EntryInit();
	
	///-----------------------------------------------------------------------///
	/// Frame init
	///-----------------------------------------------------------------------///
	FrameInit();

	///-----------------------------------------------------------------------///
	/// Button init
	///-----------------------------------------------------------------------///
 	ButtonInit();

	///-----------------------------------------------------------------------///
	/// Timer init
	///-----------------------------------------------------------------------///
	ImageInit();

	///-----------------------------------------------------------------------///
	/// Timer init
	///-----------------------------------------------------------------------///
	TimerInit();

	///-----------------------------------------------------------------------///
	/// List init
	///-----------------------------------------------------------------------///
	ListInit();
 
 	///-----------------------------------------------------------------------///
	/// Main menu set
	///-----------------------------------------------------------------------///
	AppMainMenuSet(pViewDataPtr->pView);

 	gtk_container_add(GTK_CONTAINER(AppPtr->pBox),   pViewDataPtr->pView);
 	
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


