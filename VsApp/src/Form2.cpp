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

static void CallbackBtnBleScanStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_START;
}

static void CallbackBtnBleScanStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_STOP;
}

static void CallbackBtnBleOpenClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	/// Scan stopped
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_STOP;
	/// Scan connection open
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_OPEN;	
}

static void CallbackBtnBleCloseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	

	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_START;
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_CLOSE;
}

static void CallbackBtnBleVscModeStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	DBG_PRINTF("\r [FORM2] VSC MODE START\r\n");
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_VSC_MODE_START;	
}

static void CallbackBtnBleVscModeStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;	
	DBG_PRINTF("\r [FORM2] VSC MODE STOP\r\n");
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_VSC_MODE_STOP;	
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

	///------------------------------------------------------------------------------------///
	///	BLE Status
	///------------------------------------------------------------------------------------///
	if(GlobalVar.iBleState == BLE_STATE_CLOSE)
	{		
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleStatus ), "BLE is closed");
	}
	if(GlobalVar.iBleState == BLE_STATE_WAIT)
	{
		sprintf(str, "BLE is openning ... (%d sec)", GlobalVar.iBleOpenSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleStatus ), str);
	}
	if(GlobalVar.iBleState == BLE_STATE_CONNECTED)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleStatus ), "BLE is opened");
	}
	if(GlobalVar.iBleState == BLE_STATE_VSC_MODE)
	{
		sprintf(str, "VSC MODE is running, total second = %5d sec", 	GlobalVar.dwVscModeSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleStatus), str);
	}

	
	return TRUE;
}


JINT CallbackForm2Timer2 (gpointer data)
{    
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type * ) pThis->pViewData;

	BleDeviceItemType *pItem = NULL;
	JINT i 			= 0;
	JWORD wRSSI = 0;
	JINT iRSSI 	= 0;
	
	///------------------------------------------------------------------------------------///
	///	UI: SCAN TABLE check
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta6 & SYS_STA6_BLE_MASTER_SCAN_UPDATED) != 0)
	{	
		GlobalVar.dwSysSta6 &=~ SYS_STA6_BLE_MASTER_SCAN_UPDATED;

		Form2List1RowDeleteAll();
		
		for(i = 0 ; i < GlobalVar.BleDeviceList.iCnt; i = i + 1)
		{
			pItem = &GlobalVar.BleDeviceList.BleDeviceItems[i];
			if(*(JBYTE *)&pItem->bRSSI & 0x80)
			{
				wRSSI = *(JBYTE *)&pItem->bRSSI + 0xFF00;
			}
			else
			{
				wRSSI = *(JBYTE *)&pItem->bRSSI;
			}
			iRSSI = (JINT) *(JSHORT *)&wRSSI;
			Form2List1RowAdd((char *)&pItem->name[0], iRSSI, &pItem->bAddr[0]);
		}
	}

	///------------------------------------------------------------------------------------///
	///	UI: text change
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta6 & SYS_STA6_BLE_MASTER_SCAN_ON))
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleScanOn), "BLE device scanning");
	}
	else
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleScanOn), "BLE device scan stopped");
	}

	///------------------------------------------------------------------------------------///
	///	UI: Serial Port Closed
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
	  JViewButtonDisable(pViewDataPtr->pBtnBleOpen);
	  JViewButtonDisable(pViewDataPtr->pBtnBleClose);
	  JViewButtonDisable(pViewDataPtr->pBtnBleScanStart);
	  JViewButtonDisable(pViewDataPtr->pBtnBleScanStop);  

 	  JViewButtonDisable(pViewDataPtr->pBtnVscModeStart);  
 	  JViewButtonDisable(pViewDataPtr->pBtnVscModeStop);   	   	  
 	  
	}	

	///------------------------------------------------------------------------------------///
	///	UI: Serial Port Open
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) != 0)
	{
		///------------------------------------------------------------------------------------///
		///	UI: BLE Conencted
		///------------------------------------------------------------------------------------///		
		if(GlobalVar.bBleConnected == TRUE)
		{
			JViewButtonDisable(pViewDataPtr->pBtnBleScanStart);
			JViewButtonDisable(pViewDataPtr->pBtnBleScanStop);
		
		  JViewButtonDisable(pViewDataPtr->pBtnBleOpen);
		  JViewButtonEnable(pViewDataPtr->pBtnBleClose);		 		 

		  ///------------------------------------------------------------------------------------///
			///	UI: Vsc Mode Start / Stop
			///------------------------------------------------------------------------------------///	
			if(GlobalVar.iBleState == BLE_STATE_VSC_MODE)
			{
				JViewButtonDisable(pViewDataPtr->pBtnVscModeStart);
		  	JViewButtonEnable(pViewDataPtr->pBtnVscModeStop);		  
			}
			else
			{
		  	JViewButtonEnable(pViewDataPtr->pBtnVscModeStart);		  
				JViewButtonDisable(pViewDataPtr->pBtnVscModeStop);
			}		  
  	}
		else
		{
			///------------------------------------------------------------------------------------///
			///	UI: Scan Start / Stop
			///------------------------------------------------------------------------------------///	
			if(GlobalVar.dwSysSta6 & SYS_STA6_BLE_MASTER_SCAN_ON)
			{
			  JViewButtonDisable(pViewDataPtr->pBtnBleScanStart);
			  JViewButtonEnable(pViewDataPtr->pBtnBleScanStop);  	
			}
			else
			{
				JViewButtonEnable(pViewDataPtr->pBtnBleScanStart);
				JViewButtonDisable(pViewDataPtr->pBtnBleScanStop);  	
			}
			JViewButtonEnable(pViewDataPtr->pBtnBleOpen);
		  JViewButtonDisable(pViewDataPtr->pBtnBleClose);
		  
	 	  JViewButtonDisable(pViewDataPtr->pBtnVscModeStart);  
 		  JViewButtonDisable(pViewDataPtr->pBtnVscModeStop);  
		}
	}


	return (TRUE);
}


void CallbackForm2ListBox1RowActivated (GtkListBox* self, GtkListBoxRow* pRowSelected,  gpointer user_data)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox 			 =  pViewDataPtr->pListBox1;
	GtkListBoxRow* pRow = NULL;
	GList *children = NULL;
	GList *pItem 		= NULL;
	JINT iRow  = -1;
	JBYTE bRet = FALSE;

	char strBleDeviceName[256];
	char strBleDeviceMac[256];

	BleDeviceItemType *pBleDeviceItem = NULL;

	strcpy(strBleDeviceName, "");
	strcpy(strBleDeviceMac,  "");	

	children = gtk_container_get_children(GTK_CONTAINER(pListBox));
	
	for(pItem = children; pItem != NULL; pItem = g_list_next(pItem))
	{
		pRow = (GtkListBoxRow*)(pItem->data);
		if(pRow == pRowSelected)
		{
	  	break;
		}
 		iRow = iRow + 1;
	}
	
	g_list_free(children);
	printf("\t ROW  = %d \r\n", iRow);
	if(iRow >= 0)
	{
		/// get the items
		if(GlobalVar.BleDeviceList.iCnt > iRow)
		{			
			pBleDeviceItem = &GlobalVar.BleDeviceList.BleDeviceItems[iRow];
			
			 sprintf(strBleDeviceName, "%s", pBleDeviceItem->name);
			 sprintf(strBleDeviceMac, "%02X:%02X:%02X:%02X:%02X:%02X", 
			 					pBleDeviceItem->bAddr[0], pBleDeviceItem->bAddr[1], pBleDeviceItem->bAddr[2], 
			 					pBleDeviceItem->bAddr[3], pBleDeviceItem->bAddr[4], pBleDeviceItem->bAddr[5]);

	 	  ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, strBleDeviceName);			
		  ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, 	strBleDeviceMac); 

		  gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleDeviceName), strBleDeviceName);
		  gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleDeviceMac),  strBleDeviceMac);

		  /// scan stopped
	  	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_STOP;
		}
		else
		{
			printf("[ERROR] the row (%d) > data count (%d)\r\n", iRow, GlobalVar.BleDeviceList.iCnt);
		}
	}
	else
	{
			printf("[ERROR] the row (%d)  not found !!\r\n", iRow);
	}
	

	printf("\t BLE_DEVICE_NAME = '%s' \r\n", strBleDeviceName);
 	printf("\t BLE_DEVICE_MAC = '%s' \r\n", strBleDeviceMac);	
}



///------------------------------------------------------------------------------------///
/// FORM2 LIST 1
///------------------------------------------------------------------------------------///
JINT Form2List1RowDeleteAll(void)
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

JINT Form2List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr)
{
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
		
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

	char strValue0[256];
	char strValue1[256];
	char strValue2[256];

  JINT h  = 500;
  JINT w  = 500;

	row = gtk_list_box_row_new();
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	sprintf(strValue0, "%s", strName);
	sprintf(strValue1, "%02X:%02X:%02X:%02X:%02X:%02X", 
						pbMacAddr[0], pbMacAddr[1], pbMacAddr[2], 
						pbMacAddr[3], pbMacAddr[4], pbMacAddr[5]);
	sprintf(strValue2, "%d", iRSSI);	
	
	label0 = gtk_label_new(strValue0);
	label1 = gtk_label_new(strValue1);
	label2 = gtk_label_new(strValue2);	


	gtk_widget_set_size_request(label0, 200, 30); 
	gtk_widget_set_size_request(label1, 200, 30); 
	gtk_widget_set_size_request(label2, 100, 30); 
	  
	gtk_box_pack_start(GTK_BOX(hbox), label0, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0)


	;
	gtk_widget_set_size_request(hbox, w, 30); 
	
	gtk_container_add(GTK_CONTAINER(row), hbox);	
	gtk_container_add(GTK_CONTAINER(pListBox), row);
		gtk_widget_show_all(row);
	return TRUE;
}

static JINT Form2List1HeaderSet(void)
{	
	ViewDataForm2Type * pViewDataPtr = (ViewDataForm2Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
	
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

  JINT w  = 500;
  
	//----------------------------------------------------------------///
	/// header
	///----------------------------------------------------------------///	
	row = gtk_list_box_row_new();
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(hbox, "list_header");
	label0 = gtk_label_new("Name");
	label1 = gtk_label_new("MAC");
	label2 = gtk_label_new("RSSI");	

	gtk_widget_set_size_request(label0, 200, 30); 
	gtk_widget_set_size_request(label1, 200, 30); 
	gtk_widget_set_size_request(label2, 100, 30); 
	
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

JINT Form2List1Init(void)
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
	y0 = FORM2_FRAME1_TOP  + FORM2_FRAME1_ROW * 2 + FORM2_FRAME1_YGAP ;
  w  = 500;
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

	///-----------------------------------------------------------------------///
	/// Label: Scan On
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME1_LEFT + FORM2_FRAME1_XGAP  + 320;
	y0 = FORM2_FRAME1_TOP  + FORM2_FRAME1_ROW;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelBleScanOn = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: Device Name
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("Device:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	/// ITEM : BLE_DEVICE_NAME
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, &strBleDeviceName[0]);
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP + 150;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW;  
	w  = 200;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strBleDeviceName);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_name");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
 	pViewDataPtr->pLabelBleDeviceName = pLabel;	

  ///-----------------------------------------------------------------------///
	/// Label: Device Mac
	///-----------------------------------------------------------------------/// 
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW *2;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("MAC:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	/// ITEM : BLE_DEVICE_MAC
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, &strBleDeviceMac[0]);
  
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP + 150;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW * 2;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strBleDeviceMac);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_mac");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelBleDeviceMac = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: Ble Status
	///-----------------------------------------------------------------------///	
	x0 	= FORM2_FRAME2_LEFT;
	y0 	= 580;  
	w 	= 460;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic( "");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
	gtk_widget_set_halign (pLabel, GTK_ALIGN_START);
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelBleStatus  = pLabel;

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

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStart
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME1_LEFT + FORM2_FRAME1_XGAP;
	y0 = FORM2_FRAME1_TOP  + FORM2_FRAME1_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan start");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleScanStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleScanStart = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStop
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME1_LEFT + FORM2_FRAME1_XGAP + 150;
	y0 = FORM2_FRAME1_TOP  + FORM2_FRAME1_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan stop");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleScanStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleScanStop = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleOpen
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP + 50;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW * 3;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Open");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleOpenClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleOpen  = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleClose
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT + FORM2_FRAME2_XGAP + 50 + 140;
	y0 = FORM2_FRAME2_TOP  + FORM2_FRAME2_ROW * 3;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Close"); 	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleCloseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleClose = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleVscModeStart
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME3_LEFT + FORM2_FRAME3_XGAP + 50;
	y0 = FORM2_FRAME3_TOP  + FORM2_FRAME3_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Start");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleVscModeStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnVscModeStart = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> pBtnVscModeStop
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME3_LEFT + FORM2_FRAME3_XGAP + 50 + 140;
	y0 = FORM2_FRAME3_TOP  + FORM2_FRAME3_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Stop");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackBtnBleVscModeStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnVscModeStop = pButton;

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

	///-----------------------------------------------------------------------///
	/// Frame: VS-ECG
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME1_LEFT;
	y0 = FORM2_FRAME1_TOP;
  w  = FORM2_FRAME1_WIDTH;
  h  = FORM2_FRAME1_HEIGHT;

  pFrame = gtk_frame_new ("VS-ECG");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.01, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: VSH101
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME2_LEFT;
	y0 = FORM2_FRAME2_TOP;
  w  = FORM2_FRAME2_WIDTH;
  h  = FORM2_FRAME2_HEIGHT;

  pFrame = gtk_frame_new ("VSH101");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.01, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: VSC-MODE
	///-----------------------------------------------------------------------///
	x0 = FORM2_FRAME3_LEFT;
	y0 = FORM2_FRAME3_TOP;
  w  = FORM2_FRAME3_WIDTH;
  h  = FORM2_FRAME3_HEIGHT;

  pFrame = gtk_frame_new ("VSC MODE");
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
	g_timeout_add(200, CallbackForm2Timer2, (gpointer)pViewDataPtr->pView);	
	
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
	Form2List1Init();
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
