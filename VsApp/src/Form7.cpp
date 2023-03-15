/**
 * @file Form7.cpp
 *
 *   Form7 function
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
#include "Form7.h"

static ViewDataForm7Type  	ViewDataForm7;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm7;

///------------------------------------------------------------------------------------///
/// Function Area
///------------------------------------------------------------------------------------///
void Form7ButtonUpdate(void)
{			
#ifdef FEATURE_JGATT
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type * ) pThis->pViewData;
	JGattCtlType * pJGattCtl = JGattCtlPtr;

	if(pJGattCtl->iGattState == JGATT_STATE_INIT)
	{
		JViewButtonEnable(pViewDataPtr->pBtnGattOpen);	 
 		JViewButtonDisable(pViewDataPtr->pBtnGattClose);	  

		JViewButtonEnable(pViewDataPtr->pBtnGattScanStart);	 
		JViewButtonDisable(pViewDataPtr->pBtnGattScanStop);	

		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStop);  
	}
	if((pJGattCtl->iGattState == JGATT_STATE_OPEN) ||(pJGattCtl->iGattState == JGATT_STATE_OPENING))
	{
		JViewButtonDisable(pViewDataPtr->pBtnGattOpen);	  
		JViewButtonEnable(pViewDataPtr->pBtnGattClose);	  

		JViewButtonDisable(pViewDataPtr->pBtnGattScanStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattScanStop);	  

		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStop);  
	}
	if(pJGattCtl->iGattState == JGATT_STATE_OPEN_OK)
	{
		JViewButtonDisable(pViewDataPtr->pBtnGattOpen);	  
		JViewButtonEnable(pViewDataPtr->pBtnGattClose);	  

		JViewButtonDisable(pViewDataPtr->pBtnGattScanStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattScanStop);	  

		JViewButtonEnable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStop);  
	}

	if((pJGattCtl->iGattState == JGATT_STATE_SCAN_START) || (pJGattCtl->iGattState == JGATT_STATE_SCAN_RESULT))
	{
		JViewButtonDisable(pViewDataPtr->pBtnGattOpen);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattClose);	  

		JViewButtonDisable(pViewDataPtr->pBtnGattScanStart);	  
		JViewButtonEnable(pViewDataPtr->pBtnGattScanStop);


		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStop);  			  
	}
	if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_START)
	{
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonEnable(pViewDataPtr->pBtnGattVscModeStop);  	
	}
	if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_READ)
	{
		JViewButtonDisable(pViewDataPtr->pBtnGattVscModeStart);	  
		JViewButtonEnable(pViewDataPtr->pBtnGattVscModeStop);  	
	}
	if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_STOP)
	{
		
	}

#endif ///< for OS_TYPE_UBUNTU
}

void Form7LabelUpdate(void)
{			
#ifdef FEATURE_JGATT
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type * ) pThis->pViewData;
	JGattCtlType * pJGattCtl = JGattCtlPtr;
	char strLabel[256];

	if(pJGattCtl->iGattState == JGATT_STATE_INIT)
	{
		sprintf(strLabel, "%s", "GATT is idle");
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattStatus), strLabel);
	}
	if((pJGattCtl->iGattState == JGATT_STATE_OPEN) || (pJGattCtl->iGattState == JGATT_STATE_OPENING))
	{
		sprintf(strLabel, "GATT is opening  ... (%d sec)", pJGattCtl->iOpenTimeSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattStatus), strLabel);
	}
	if(pJGattCtl->iGattState == JGATT_STATE_OPEN_OK)
	{		
		sprintf(strLabel, "GATT is opened ... (%d sec)", pJGattCtl->iOpenTimeSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattStatus), strLabel);
	}
	if((pJGattCtl->iGattState == JGATT_STATE_SCAN_START) || (pJGattCtl->iGattState == JGATT_STATE_SCAN_RESULT))
	{
		sprintf(strLabel, "GATT is scaning ... (%d sec)", pJGattCtl->iScanTimeSec);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattStatus), strLabel);
	}	
	
	if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_READ)
	{
		sprintf(strLabel, "GATT VSC Mode ... (%0.1f sec)", (JFLOAT) (pJGattCtl->t1 - pJGattCtl->tVsdModeStart) / 1000.0);
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattStatus), strLabel);	
	}
	

#endif ///< for OS_TYPE_UBUNTU
}

///------------------------------------------------------------------------------------///
/// Callback functions
///------------------------------------------------------------------------------------///

gint CallbackForm7Timer1 (gpointer data)
{    
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type * ) pThis->pViewData;

	///------------------------------------------------------------------------------------///
	///	UI: Scan table update
	///------------------------------------------------------------------------------------///
	Form7List1Update();
		
	///------------------------------------------------------------------------------------///
	///	UI: Button update
	///------------------------------------------------------------------------------------///
	Form7ButtonUpdate();

	///------------------------------------------------------------------------------------///
	///	UI: Label update
	///------------------------------------------------------------------------------------///
	Form7LabelUpdate();

	return TRUE;
}


static void CallbackForm7BtnGattScanStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	DBG_PRINTF("[UI]: Gatt Scan Start\r\n");
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_SCAN_START;
}

static void CallbackForm7BtnGattScanStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	DBG_PRINTF("[UI]: Gatt Scan Stop\r\n");
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_SCAN_STOP;
}

static void CallbackForm7BtnGattOpenClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	
	/// Connection open
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_OPEN;
}

static void CallbackForm7BtnGattCloseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	/// Connection open
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_CLOSE;
}

static void CallbackForm7BtnBleVscModeStartClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_VSC_MODE_START;	
}

static void CallbackForm7BtnBleVscModeStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	
	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_VSC_MODE_STOP;	
}

void CallbackForm7ListBox1RowActivated (GtkListBox* self, GtkListBoxRow* pRowSelected,  gpointer user_data)
{
#if OS_TYPE == OS_TYPE_UBUNTU	
//#if 1	
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	GtkWidget * pListBox 			 =  pViewDataPtr->pListBox1;
	GtkListBoxRow* pRow = NULL;
	GList *pChildren 		= NULL;
	GList *pItem 				= NULL;
	JINT iRow  = -1;
	JBYTE bRet = FALSE;

	char strGattDeviceName[256];
	char strGattDeviceMac[256];

	JGattScanItemType *pScanItem = NULL;

	JGattCtlType  * pJGattCtl = JGattCtlPtr;

	strcpy(strGattDeviceName, "");
	strcpy(strGattDeviceMac,  "");	

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
		if(pJGattCtl->iScanItemCnt > iRow)
		{			
			pScanItem = &pJGattCtl->ScanItems[iRow];
			
			sprintf(strGattDeviceName, "%s", pScanItem->strName);
			sprintf(strGattDeviceMac, "%02X:%02X:%02X:%02X:%02X:%02X", 
							pScanItem->bAddr[5], pScanItem->bAddr[4], pScanItem->bAddr[3], 
							pScanItem->bAddr[2], pScanItem->bAddr[1], pScanItem->bAddr[0]);

	 	  ConfigStrSet((char *)CONFIG_ITEM_GATT_DEVICE_NAME, strGattDeviceName);			
		  ConfigStrSet((char *)CONFIG_ITEM_GATT_DEVICE_MAC,  strGattDeviceMac); 
		  gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattDeviceName), strGattDeviceName);
		  gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGattDeviceMac),  strGattDeviceMac);
		  /// scan stopped
	  	GlobalVar.dwSysCtl8 |= SYS_CTL8_JGATT_SCAN_STOP;
		}
		else
		{
			printf("[ERROR] the row (%d) > data count (%d)\r\n", iRow, pJGattCtl->iScanItemCnt );
		}
	}
	else
	{
		printf("[ERROR] the row (%d)  not found !!\r\n", iRow);
	}
	
	printf("\t GATT_DEVICE_NAME = '%s' \r\n", 	strGattDeviceName);
 	printf("\t GATT_DEVICE_MAC  = '%s' \r\n", 	strGattDeviceMac);	
#endif ///< for	 OS_TYPE_UBUNTU
}

///------------------------------------------------------------------------------------///
/// List area
///------------------------------------------------------------------------------------///

JINT Form7List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr, char *strTime)
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
		
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;
	GtkWidget	*label3 = NULL;

	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

	char strValue0[256];
	char strValue1[256];
	char strValue2[256];
	char strValue3[256];

  JINT h  = 500;
  JINT w  = 500;

	row = gtk_list_box_row_new();
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	sprintf(strValue0, "%s", strName);
	sprintf(strValue1, "%02X:%02X:%02X:%02X:%02X:%02X", 
						pbMacAddr[0], pbMacAddr[1], pbMacAddr[2], 
						pbMacAddr[3], pbMacAddr[4], pbMacAddr[5]);
	sprintf(strValue2, "%d", iRSSI);
	sprintf(strValue3, "%s", strTime);	
	
	label0 = gtk_label_new(strValue0);
	label1 = gtk_label_new(strValue1);
	label2 = gtk_label_new(strValue2);
	label3 = gtk_label_new(strValue3);	

	gtk_widget_set_size_request(label0, 160, 	30); 
	gtk_widget_set_size_request(label1, 160, 	30); 
	gtk_widget_set_size_request(label2, 60, 	30); 
	gtk_widget_set_size_request(label3, 60, 	30); 

	//gtk_label_set_xalign(GTK_LABEL(label0), 0.01);

	gtk_box_pack_start(GTK_BOX(hbox), label0, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label3, TRUE, TRUE, 0);
	gtk_widget_set_size_request(hbox, w, 30); 
	
	gtk_container_add(GTK_CONTAINER(row), hbox);	
	gtk_container_add(GTK_CONTAINER(pListBox), row);
	gtk_widget_show_all(row);
	return TRUE;
}

JINT Form7List1RowDeleteAll()
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	GtkWidget * pListBox  =  pViewDataPtr->pListBox1;
	
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

JINT Form7List1Update(void)
{
#if OS_TYPE == OS_TYPE_UBUNTU	
//#if 1
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	JGattScanItemType  *pItem = NULL;
	char strTime[32];
	JINT i = 0;
	JINT iRSSI = 0;
	JGattCtlType  * pJGattCtl = JGattCtlPtr;

	if(pViewDataPtr->bShow == FALSE)
	{
		return FALSE;
	}
	if(pJGattCtl->bScanUIUpdate == FALSE)
	{
		return FALSE;
	}
	Form7List1RowDeleteAll();
	
	for(i = 0 ; i < pJGattCtl->iScanItemCnt; i = i + 1)
	{
		pItem = (JGattScanItemType  *)&pJGattCtl->ScanItems[i];		
		
		sprintf(strTime, "%0.3f", 10 - ((JFLOAT)(pItem->iValidCnt * GATT_SCAN_PERIOD) / 1000));
		Form7List1RowAdd((char *)&pItem->strName[0],  pItem->iRSSI, &pItem->bAddr[0], strTime);
	}

	pJGattCtl->bScanUIUpdate = FALSE;	

#endif ///< for OS_TYPE_UBUNTU

	return TRUE;
}

static JINT Form7List1HeaderSet()
{	
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	GtkWidget * pListBox = pViewDataPtr->pListBox1;
	
	GtkWidget *label0 = NULL;
	GtkWidget	*label1 = NULL;
	GtkWidget	*label2 = NULL;
	GtkWidget	*label3 = NULL;

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
	label3 = gtk_label_new("Time");	

	gtk_widget_set_size_request(label0, 160, 30); 
	gtk_widget_set_size_request(label1, 160, 30); 
	gtk_widget_set_size_request(label2, 60,  30);
	gtk_widget_set_size_request(label3, 60,  30); 
	
  gtk_widget_set_name(label0, "list1_header0");  
  gtk_widget_set_name(label1, "list1_header1");  
  gtk_widget_set_name(label2, "list1_header2");
	gtk_widget_set_name(label3, "list1_header3");    
	/// insert labels into hbox
	
	gtk_box_pack_start(GTK_BOX(hbox), label0, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label3, TRUE, TRUE, 0);

	gtk_list_box_row_set_activatable((GtkListBoxRow * )row, FALSE);
	gtk_list_box_row_set_selectable((GtkListBoxRow * )row, 	FALSE);
	gtk_widget_set_size_request(hbox, w, 30); 
	/// insert hbox into rpw	
	gtk_container_add(GTK_CONTAINER(row), hbox);

	gtk_container_add(GTK_CONTAINER(pListBox), row);

	return TRUE;	
}

static JINT Form7List1Init()
{
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;		
	GtkWidget * pListBox = NULL;

	JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;


	GtkWidget *hbox 	= NULL;
	GtkWidget *row  	= NULL;

	x0 = FORM7_FRAME0_LEFT + FORM7_FRAME0_XGAP;
	y0 = FORM7_FRAME0_TOP  + FORM7_FRAME0_ROW * 2 + FORM7_FRAME0_YGAP ;
  w  = 560;
  h  = 500;

	///----------------------------------------------------------------///
	///  Create the listbox 
	///----------------------------------------------------------------///	
	pListBox = gtk_list_box_new();
	pViewDataPtr->pListBox1 = pListBox;

	///----------------------------------------------------------------///
	/// header
	///----------------------------------------------------------------///	
	Form7List1HeaderSet();
	
	///----------------------------------------------------------------///
	/// list show
	///----------------------------------------------------------------///	
	gtk_widget_set_size_request(pListBox, w, h); 
	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pListBox, x0, y0);
	gtk_widget_show_all(pListBox);
	gtk_widget_show(pListBox);

	g_signal_connect(G_OBJECT(pListBox), "row-activated",   G_CALLBACK(CallbackForm7ListBox1RowActivated), NULL);
	
	return TRUE;
}


///------------------------------------------------------------------------------------///
/// Form7 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 200;
	JINT h  = 30;

	char strGattDeviceName[256];
	char strGattDeviceMac[256];

	///-----------------------------------------------------------------------///
	/// Label: Scan On
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME0_LEFT + FORM7_FRAME0_XGAP  + 320;
	y0 = FORM7_FRAME0_TOP  + FORM7_FRAME0_ROW;  
	w 	= 120;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelGattScanOn = pLabel;
	 	
	///-----------------------------------------------------------------------///
	/// Label: Device Name
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW;  
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
	ConfigStrGet((char *)CONFIG_ITEM_GATT_DEVICE_NAME, &strGattDeviceName[0]);
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP + 150;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strGattDeviceName);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_name");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
 	pViewDataPtr->pLabelGattDeviceName = pLabel;

  ///-----------------------------------------------------------------------///
	/// Label: Device Mac
	///-----------------------------------------------------------------------/// 
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW * 2;  
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
	ConfigStrGet((char *)CONFIG_ITEM_GATT_DEVICE_MAC, &strGattDeviceMac[0]);
  
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP + 150;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW *2;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic(strGattDeviceMac);
  gtk_widget_set_name(pLabel, "form3_label_ble_device_mac");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelGattDeviceMac = pLabel;

  ///-----------------------------------------------------------------------///
	/// Label: GATT Status
	///-----------------------------------------------------------------------///	 
	x0 = FORM7_FRAME4_LEFT + FORM7_FRAME4_XGAP + 150;
	y0 = FORM7_FRAME4_TOP  + FORM7_FRAME4_ROW *2;  
	w 	= 200;
	h 	= 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelGattStatus = pLabel;
	
	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;
	JINT iRet = TRUE;
	GtkWidget *pEntry	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 0;
	JINT h  = 0;

	
	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 80;
	JINT h = 30;

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStart
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME0_LEFT + FORM7_FRAME0_XGAP;
	y0 = FORM7_FRAME0_TOP  + FORM7_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan start");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnGattScanStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnGattScanStart = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleScanStop
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME0_LEFT + FORM7_FRAME0_XGAP + 150;
	y0 = FORM7_FRAME0_TOP  + FORM7_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Scan stop");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnGattScanStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnGattScanStop = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleOpen
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP + 50;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW * 3;
	w = 120;
	h = 30;
	pButton= gtk_button_new_with_label("Open");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnGattOpenClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnGattOpen  = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleClose
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME1_LEFT + FORM7_FRAME1_XGAP + 50 + 140;
	y0 = FORM7_FRAME1_TOP  + FORM7_FRAME1_ROW * 3;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Close"); 	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnGattCloseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnGattClose = pButton;	

 	///-----------------------------------------------------------------------///
	/// Button -> BleVscModeStart
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME2_LEFT + FORM7_FRAME2_XGAP + 50;
	y0 = FORM7_FRAME2_TOP  + FORM7_FRAME2_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Start");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnBleVscModeStartClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);
	pViewDataPtr->pBtnGattVscModeStart = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> pBtnVscModeStop
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME2_LEFT + FORM7_FRAME2_XGAP + 50 + 140;
	y0 = FORM7_FRAME2_TOP  + FORM7_FRAME2_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Stop");	
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm7BtnBleVscModeStopClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnGattVscModeStop = pButton;	

	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	
	GtkWidget * pFrame = NULL;  

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
	
	GtkStyleContext *pContext = NULL;

	///-----------------------------------------------------------------------///
	/// Frame0: COM
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME0_LEFT;
	y0 = FORM7_FRAME0_TOP;
  w  = FORM7_FRAME0_WIDTH;
  h  = FORM7_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("Gatt Scan");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame1: BLE CONNECT
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME1_LEFT;
	y0 = FORM7_FRAME1_TOP;
  w  = FORM7_FRAME1_WIDTH;
  h  = FORM7_FRAME1_HEIGHT;

  pFrame = gtk_frame_new ("Gatt Connect");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

  ///-----------------------------------------------------------------------///
	/// Frame2: BLE VSC Mode
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME2_LEFT;
	y0 = FORM7_FRAME2_TOP;
  w  = FORM7_FRAME2_WIDTH;
  h  = FORM7_FRAME2_HEIGHT;

  pFrame = gtk_frame_new ("Gatt Measurement");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);
/*
  ///-----------------------------------------------------------------------///
	/// Frame3: Monitor
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME3_LEFT;
	y0 = FORM7_FRAME3_TOP;
  w  = FORM7_FRAME3_WIDTH;
  h  = FORM7_FRAME3_HEIGHT;

  pFrame = gtk_frame_new ("Gatt Monitor");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame4: Device Status
	///-----------------------------------------------------------------------///
	x0 = FORM7_FRAME4_LEFT;
	y0 = FORM7_FRAME4_TOP;
  w  = FORM7_FRAME4_WIDTH;
  h  = FORM7_FRAME4_HEIGHT;

  pFrame = gtk_frame_new ("Gatt Device Status");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);
	*/
	
  return iRet;  
}

static JINT ProgressBarInit()
{
	JINT x0		 	= 0;
	JINT y0 		= 0;	
	JINT width 	= 0;
	JINT height	= 0;	
	GtkWidget * pProgressBar = NULL;
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	
		
  return TRUE;
}

static JINT ComboBoxInit()
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;
	GtkWidget	*pComboBox = NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	
	return TRUE;
}

static JINT ImageInit(void)
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 530;
	JINT y0 = 1200;

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
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	
	
	g_timeout_add(100, CallbackForm7Timer1, (gpointer)pViewDataPtr->pView);	
	//g_timeout_add(100, CallbackForm7Timer2, (gpointer)pViewDataPtr->pDrawAreaDS0);	
	
	return TRUE;
}

static JINT ListInit()
{
	Form7List1Init();
	return TRUE;
}

static JINT DrawAreaInit()
{
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 
	ViewDataForm7Type * pViewDataPtr = (ViewDataForm7Type *)pThis->pViewData;	
	
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
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm7Type * pViewDataPtr = &ViewDataForm7;	

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
	/// Frame init
	///-----------------------------------------------------------------------///
	FrameInit();

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
	///  Image Init
	///-----------------------------------------------------------------------///	
	ImageInit();

	///-----------------------------------------------------------------------///
	///  Timer init
	///-----------------------------------------------------------------------///	
	TimerInit();

	///-----------------------------------------------------------------------///
	/// List init
	///-----------------------------------------------------------------------///
  ListInit();

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
///   Form7 
///--------------------------------------------------------------------------------///
JView JVForm7 = 
{
	"Form7",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm7,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};

