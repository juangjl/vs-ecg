/**
 * @file serial.cpp
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

#include "Form3.h"

static ViewDataForm3Type  ViewDataForm3;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm3;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackForm3BtnBleScanStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_START;
}

static void CallbackForm3BtnBleScanStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_STOP;
}

static void CallbackForm3BtnBleOpenClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	/// Scan stopped
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_STOP;
	/// Scan connection open
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_OPEN;	
}

static void CallbackForm3BtnBleCloseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	

	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_SCAN_START;
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_CLOSE;
}

static void CallbackForm3BtnBleVscModeStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_VSC_MODE_START;	
}

static void CallbackForm3BtnBleVscModeStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_VSC_MODE_STOP;	
}

static void CallbackForm3BtnBleTestClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
	DBG_PRINTF("[BLE] BLE_TEST\r\n");
	GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_BLE_TEST;	
}

gint CallbackForm3Timer1 (gpointer data)
{    
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type * ) pThis->pViewData;

	BleDeviceItemType *pItem = NULL;
	JINT i 			= 0;
	JWORD wRSSI = 0;
	JINT iRSSI 	= 0;
	char str[256];

	char strBleVersion[256];
	
	///------------------------------------------------------------------------------------///
	///	BLE Model and Version
	///------------------------------------------------------------------------------------///

	if(GlobalVar.iBleState == BLE_STATE_CLOSE)
	{		
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleModelName), "--");
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleVersion),   "--");
	}
	if(GlobalVar.iBleState == BLE_STATE_WAIT)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleModelName), "--");
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleVersion),   "--");
	}
	if(GlobalVar.iBleState == BLE_STATE_CONNECTED)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleModelName), GlobalVar.strBleModelName);
		sprintf(strBleVersion, "%d", GlobalVar.iBleVersion);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleVersion),   strBleVersion);
	}
	if(GlobalVar.iBleState == BLE_STATE_VSC_MODE)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleModelName), GlobalVar.strBleModelName);
		sprintf(strBleVersion, "%d", GlobalVar.iBleVersion);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleVersion),   strBleVersion);
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
		sprintf(str, "VSC MODE transfering ... %d sec", 	GlobalVar.dwVscModeSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBleStatus), str);
	}
	
	///------------------------------------------------------------------------------------///
	///	UI: SCAN TABLE check
	///------------------------------------------------------------------------------------///
	if((GlobalVar.dwSysSta6 & SYS_STA6_BLE_MASTER_SCAN_UPDATED) != 0)
	{	
		GlobalVar.dwSysSta6 &=~ SYS_STA6_BLE_MASTER_SCAN_UPDATED;

		Form3List1RowDeleteAll();

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
			Form3List1RowAdd((char *)&pItem->name[0], iRSSI, &pItem->bAddr[0]);
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

	return TRUE;
}

void CallbackForm3ListBox1RowActivated (GtkListBox* self, GtkListBoxRow* pRowSelected,  gpointer user_data)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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
 	printf("\t BLE_DEVICE_MAC  = '%s' \r\n", strBleDeviceMac);	
}

///------------------------------------------------------------------------------------///
/// FORM3 LIST 1
///------------------------------------------------------------------------------------///
JINT Form3List1RowDeleteAll()
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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

JINT Form3List1RowDelete(JINT idx)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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

JINT Form3List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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

static JINT Form3List1HeaderSet()
{	
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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

static JINT Form3List1Init()
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;		
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

	x0 = FORM3_FRAME0_LEFT + FORM3_FRAME0_XGAP;
	y0 = FORM3_FRAME0_TOP  + FORM3_FRAME0_ROW * 2 + FORM3_FRAME0_YGAP ;
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
	Form3List1HeaderSet();
	
	///----------------------------------------------------------------///
	/// list show
	///----------------------------------------------------------------///	
	gtk_widget_set_size_request(pListBox, w, h); 
	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pListBox, x0, y0);
	gtk_widget_show_all(pListBox);
	gtk_widget_show(pListBox);

	g_signal_connect(G_OBJECT(pListBox), "row-activated",   G_CALLBACK(CallbackForm3ListBox1RowActivated), NULL);
	
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Init Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w 	= 0;
	JINT h 	= 0;	

	char strBleDeviceName[256];
	char strBleDeviceMac[256];

	///-----------------------------------------------------------------------///
	/// Label: Scan On
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME0_LEFT + FORM3_FRAME0_XGAP  + 320;
	y0 = FORM3_FRAME0_TOP  + FORM3_FRAME0_ROW;  
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
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("Device:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: BLE_DEVICE_NAME
	///-----------------------------------------------------------------------///
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, &strBleDeviceName[0]);
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP + 150;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strBleDeviceName);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_name");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
 	pViewDataPtr->pLabelBleDeviceName = pLabel;

  ///-----------------------------------------------------------------------///
	/// Label: Device Mac
	///-----------------------------------------------------------------------/// 
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW *2;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("MAC:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

  ///-----------------------------------------------------------------------///
	/// Label: Ble Device Mac
	///-----------------------------------------------------------------------///
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, &strBleDeviceMac[0]);
  
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP + 150;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW *2;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strBleDeviceMac);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_mac");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelBleDeviceMac = pLabel;

  ///-----------------------------------------------------------------------///
	/// Label: Model Name
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME4_LEFT + FORM3_FRAME4_XGAP;
	y0 = FORM3_FRAME4_TOP  + FORM3_FRAME4_ROW;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("Model Name:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: BLE_MODEL_NAME
	///-----------------------------------------------------------------------///	
	x0 = FORM3_FRAME4_LEFT + FORM3_FRAME4_XGAP + 150;
	y0 = FORM3_FRAME4_TOP  + FORM3_FRAME4_ROW;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
  gtk_widget_set_name(pLabel, "form3_label_ble_device_name");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
 	pViewDataPtr->pLabelBleModelName = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: Version
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME4_LEFT + FORM3_FRAME4_XGAP;
	y0 = FORM3_FRAME4_TOP  + FORM3_FRAME4_ROW * 2;
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("Version:");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: BLE_VERSION
	///-----------------------------------------------------------------------///	
	x0 = FORM3_FRAME4_LEFT + FORM3_FRAME4_XGAP + 150;
	y0 = FORM3_FRAME4_TOP  + FORM3_FRAME4_ROW * 2;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
  gtk_widget_set_name(pLabel, "form3_label_ble_device_name");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
 	pViewDataPtr->pLabelBleVersion = pLabel;	 	

  ///-----------------------------------------------------------------------///
	/// Label: Ble Status
	///-----------------------------------------------------------------------///	  
	x0 	= FORM3_FRAME4_LEFT;
	y0 	= 650;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
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
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	char strValue[256];

	strcpy(strValue, "");
	
  return TRUE;
}

static JINT ButtonInit(void)
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;
	JINT iRet 					= TRUE;
	GtkWidget *pButton 	= NULL;
		
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 0;
	JINT h = 0;	

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStart
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME0_LEFT + FORM3_FRAME0_XGAP;
	y0 = FORM3_FRAME0_TOP  + FORM3_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan start");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleScanStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleScanStart = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStop
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME0_LEFT + FORM3_FRAME0_XGAP + 150;
	y0 = FORM3_FRAME0_TOP  + FORM3_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan stop");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleScanStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleScanStop = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleOpen
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP + 50;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW * 3;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Open");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleOpenClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleOpen  = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleClose
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME1_LEFT + FORM3_FRAME1_XGAP + 50 + 140;
	y0 = FORM3_FRAME1_TOP  + FORM3_FRAME1_ROW * 3;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Close"); 	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleCloseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnBleClose = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> BleVscModeStart
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME2_LEFT + FORM3_FRAME2_XGAP + 50;
	y0 = FORM3_FRAME2_TOP  + FORM3_FRAME2_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Start");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleVscModeStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnVscModeStart = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> pBtnVscModeStop
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME2_LEFT + FORM3_FRAME2_XGAP + 50 + 140;
	y0 = FORM3_FRAME2_TOP  + FORM3_FRAME2_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Stop");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm3BtnBleVscModeStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnVscModeStop = pButton;	

 	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type *)pThis->pViewData;	
  GtkWidget * pFrame = NULL;

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;

	///-----------------------------------------------------------------------///
	/// Frame0: COM
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME0_LEFT;
	y0 = FORM3_FRAME0_TOP;
  w  = FORM3_FRAME0_WIDTH;
  h  = FORM3_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("BLE Scan");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame1: BLE CONNECT
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME1_LEFT;
	y0 = FORM3_FRAME1_TOP;
  w  = FORM3_FRAME1_WIDTH;
  h  = FORM3_FRAME1_HEIGHT;

  pFrame = gtk_frame_new ("BLE Connect");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

  ///-----------------------------------------------------------------------///
	/// Frame2: BLE VSC Mode
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME2_LEFT;
	y0 = FORM3_FRAME2_TOP;
  w  = FORM3_FRAME2_WIDTH;
  h  = FORM3_FRAME2_HEIGHT;

  pFrame = gtk_frame_new ("BLE Measurement");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame4: Device Status
	///-----------------------------------------------------------------------///
	x0 = FORM3_FRAME4_LEFT;
	y0 = FORM3_FRAME4_TOP;
  w  = FORM3_FRAME4_WIDTH;
  h  = FORM3_FRAME4_HEIGHT;

  pFrame = gtk_frame_new ("Device Status");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

  return iRet;  
}

static JINT TimerInit()
{
	ViewDataForm3Type * pViewDataPtr = &ViewDataForm3;	
	g_timeout_add(200, CallbackForm3Timer1, (gpointer)pViewDataPtr->pView);	
	
	return TRUE;
}

static JINT ListInit()
{
	Form3List1Init();
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type * )pThis->pViewData;	
  gtk_widget_show(pViewDataPtr->pView);
  pViewDataPtr->bShow = TRUE;
    
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type * )pThis->pViewData;	
  gtk_widget_hide(pViewDataPtr->pView);
  pViewDataPtr->bShow = FALSE;
    
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm3Type * pViewDataPtr = (ViewDataForm3Type * )pThis->pViewData;	
	GtkWidget *pButton 	= NULL;
  
	pViewDataPtr->pView = gtk_fixed_new();

	///-----------------------------------------------------------------------///
	/// Variable init
	///-----------------------------------------------------------------------///	
	pViewDataPtr->bScanStart = FALSE;

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
///   Form1 
///--------------------------------------------------------------------------------///
JView JVForm3 = 
{
	"Form3",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm3,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};
