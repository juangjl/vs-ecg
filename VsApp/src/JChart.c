/**
 * @file JChart.c
 * @brief Chart API
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/ 

#include "Global.h"
#define JCHART_COLOR_CANVAS_BACKGROUND				COLOR_GRAY_SILVER
#define JCHART_COLOR_CHART_BACKGROUND					RGB( 0, 	0,	 0)
#define JCHART_COLOR_LINE											RGB( 3, 208,  9)
#define JCHART_COLOR_GRID1										COLOR_GRAY_DARKSLATEGRAY
#define JCHART_COLOR_GRID2										COLOR_GRAY_GAINSBORO

#define JCHART_COLOR_XLABEL										RGB(128, 128, 128)
#define JCHART_COLOR_YLABEL										RGB(128, 128, 128)

#define JCHART_COL														(6)
#define JCHART_ROW														(4)

#define JCHART_FREQ														(500)

#define JCHART_MAX_X_VAL											(6 * 1000) ///< 6 sec  = 6000 ms
#define JCHART_MAX_Y_VAL											(6)

void 	JChartInit(JChart *pThis)
{
	pThis->fLineWidth			= 0.5;
	pThis->colorCanvasBg 	= JCHART_COLOR_CANVAS_BACKGROUND;
	pThis->colorChartBg	 	= JCHART_COLOR_CHART_BACKGROUND;
	pThis->colorLine		 	= RGB(20, 145, 28);
	pThis->colorGridMajor	= JCHART_COLOR_GRID1;
	pThis->colorGridSub	 	= JCHART_COLOR_GRID2;	

	pThis->colorXLabel	 	= JCHART_COLOR_XLABEL;
	pThis->colorYLabel	 	= JCHART_COLOR_YLABEL;

	pThis->iCol 				 	= JCHART_COL;
	pThis->iRow 				 	= JCHART_ROW;	

	pThis->dwChartMode = (CHART_MODE_GRID_AUTO | 
						 						CHART_MODE_GRID_MAJOR_LINE |
						 					  CHART_MODE_GRID_SUB_LINE |
					 	 					  CHART_MODE_GRID_CENTER_LINE |
					 						  CHART_MODE_LABEL_X |
					 						  CHART_MODE_LABEL_Y |
						 						CHART_MODE_INFO_AREA |
//						 						CHART_MODE_GAIN_AUTO | 
//  						 					CHART_MODE_AUTO_GAIN2|
//												CHART_MODE_FIX_RANGE|
												CHART_MODE_FIX_RANGE_ECG |
						 						CHART_MODE_DATA_CENTER|
 						 						CHART_MODE_X_TIME);
  
	/// frequency set	
	JChartAxisXSet(pThis, 0, JCHART_MAX_X_VAL);
	JChartAxisYSet(pThis, 0, JCHART_MAX_Y_VAL);	 

	/// frequency set
	JChartSampleRateSet(pThis, JCHART_FREQ);	
	pThis->fYValMaxPre = -1;
	pThis->fYValMinPre = -1; 	


	pThis->iDataCnt  = 0;

	pThis->iLineCnt  = 0;
	/// fix gain used
	pThis->iAttn = 1;
	pThis->iSpan = 96;
	pThis->iVoff = 0;
	pThis->pDataSet = NULL;   

	pThis->fYValFixRange = (pThis->iRow * 0.1); ///< 6 mV
}

JBOOL 	JChartXValToXPos(JChart *pThis, JFLOAT fXVal, JINT *piXPOS)
{
	JFLOAT fVal = 0;
	JINT iXPos = 0;
	fVal = fXVal  * 1000;
	fVal = (fVal - pThis->fXValMin) ;
	if(fVal < 0)
	{
		fVal = 0;
	}

	iXPos = (fVal - pThis->fXValMin) * 	pThis->iChartWidth / (pThis->fXValWidth) + 	pThis->iChartX0;
	*piXPOS = iXPos;

	return TRUE;
}

void 	JChartSampleRateSet(JChart *pThis, JFLOAT fSampleRate)
{	
	pThis->fSampleRate = fSampleRate;
}

void 	JChartReset(JChart *pThis)
{
	pThis->iDataCnt = -1;
}

void		JChartCellSet(JChart *pThis, JINT iRow, JINT iCol)
{
	pThis->iRow = iRow;
	pThis->iCol = iCol;
}

void 	JChartModeSet(JChart *pThis, JDWORD dwChartMode)
{
	pThis->dwChartMode |= dwChartMode;
}

void 	JChartModeClear(JChart *pThis, JDWORD dwChartMode)
{
	pThis->dwChartMode &= ~dwChartMode;
}

void 	JChartGridDraw(JChart *pThis)
{
	JINT i  = 0;
	
	JINT x0 = 0;
	JINT y0 = 0;

	JINT x1 = 0;
	JINT y1 = 0;
		
	JINT width  = 0;
	JINT height = 0;

	JRect rect;
	JINT iMajorCnt = 5;	///< 1 mahjor cell = 5 sub-cells
	JDraw *pDC = pThis->pDC;

	
	if(pThis->dwChartMode & CHART_MODE_GRID_SUB_LINE)
	{
		pDC->LineWidth(0.2);
		pDC->ForegroundColorSet(pThis->colorGridSub);
		/// Draw horizontal grid line		
		for (i = 1; i < pThis->iCol; i++)
		{
			x0 = (JINT) pThis->iChartX0 + i * pThis->iCellWidth;
			y0 = (JINT) pThis->iChartY0;
			x1 = x0;
			y1 = (JINT)(y0 + pThis->iChartHeight);
			pDC->LineDraw(x0, y0, x1, y1);
		}
		
		/// Draw vertical line
		for (i = 1; i < pThis->iRow; i++)
		{
			x0 = (JINT) pThis->iChartX0;
			y0 = (JINT) pThis->iChartY0 + i * pThis->iCellHeight;
			x1 = (JINT)(x0 + pThis->iChartWidth);
			y1 =  y0;
			pDC->LineDraw(x0, y0, x1, y1);
		}		
	}

	///-------------------------------------------------------------///
	/// Major line
	///-------------------------------------------------------------///	

	if(pThis->dwChartMode & CHART_MODE_GRID_MAJOR_LINE)
	{
		pDC->LineWidth(0.5);
		pDC->ForegroundColorSet(pThis->colorGridSub);
		/// Draw horizontal grid line		
		for (i = iMajorCnt; i < pThis->iCol; i = i + iMajorCnt)
		{
			x0 = (JINT) pThis->iChartX0 + i * pThis->iCellWidth;
			y0 = (JINT) pThis->iChartY0;
			x1 = x0;
			y1 = (JINT)(y0 + pThis->iChartHeight);
			pDC->LineDraw(x0, y0, x1, y1);
		}
		
		/// Draw vertical line
		for(i = iMajorCnt; i < pThis->iRow; i =i + iMajorCnt)
		{
			x0 = (JINT) pThis->iChartX0;
			y0 = (JINT) pThis->iChartY0 + i * pThis->iCellHeight;
			x1 = (JINT)(x0 + pThis->iChartWidth);
			y1 =  y0;
			pDC->LineDraw(x0, y0, x1, y1);
		}		
	}

	///-------------------------------------------------------------///
	/// Outter frame
	///-------------------------------------------------------------///
	pDC->LineWidth(0.2);
	x0  		= (JINT) pThis->iChartX0;
	y0   		= (JINT) pThis->iChartY0;
	width	 	= (JINT) (pThis->iCol) * pThis->iCellWidth;
	height 	= (JINT) (pThis->iRow) * pThis->iCellHeight;

	pDC->ForegroundColorSet(pThis->colorGridMajor);
	pDC->RectDraw(x0, y0, width, height);
	
}

JINT 	JChartLineEcgDraw(JChart *pThis)
{
	JINT i 				= 0;
	JFLOAT fVal 	= 0;
	JDataSet  *pDataSet   = pThis->pDataSet;
	JDataStat *pDataStat  = &pThis->dataStat;

	JFLOAT fHighAmp  	= 0;
	JFLOAT fLowAmp 		= 0;

	JFLOAT fValX  		= 0;
	JFLOAT fValY 			= 0;
	
	JINT iDataCount    = 0; 

	JFLOAT x0 = CHPART_INVALID_POS;
	JFLOAT y0 = CHPART_INVALID_POS;	

	JFLOAT x1 = 0;
	JFLOAT y1 = 0;	

	JINT iSkipCnt = 0;
	JINT iTotalCnt = 0;

	JBOOL bUpdateChart = FALSE;

	JINT iStart = 0;
  JINT iMinX = 0;

  JFLOAT fValXStep = 0;

  JDraw *pDC = pThis->pDC;
  
  JDOUBLE  *fArrX = NULL;
  JDOUBLE  *fArrY  = NULL;  

	JFLOAT 	fEcgAmpMV = (pThis->iRow *  0.1);
	JFLOAT 	fEcgAmpHalf = fEcgAmpMV / 2;
	
	pThis->fYValFixRange = fEcgAmpMV; ///< 6 mV

	if(pDC == NULL)
	{
		printf("[ERROR] There is no DC\r\n");
		return FALSE;
	}
	if(pDataSet == NULL)
	{
		printf("[ERROR] There is no DataSet \r\n");
		return FALSE;
	}
	
	///--------------------------------------------///
	/// Sample count check
	///--------------------------------------------///
  iDataCount =  pDataSet->cnt;

	fValXStep = 1000 / pThis->fSampleRate;
  
  if(iDataCount > JDATA_MAX_CNT)
  {
    printf("[CHART][ERROR][!!!!!!] Sample count  > %d\r\n", JDATA_MAX_CNT );
    iDataCount = JDATA_MAX_CNT;
  }
	
	if(iDataCount == 0)
	{
		return TRUE;
	}	 

	fArrX = (JDOUBLE  *)malloc(sizeof(JDOUBLE) * iDataCount);
	fArrY = (JDOUBLE  *)malloc(sizeof(JDOUBLE) * iDataCount);	

	///--------------------------------------------///
	/// Find max and min, average
	///--------------------------------------------///		
	JChartStatCalculate(pThis, pDataStat);
		
	///--------------------------------------------///
	/// Draw Line
	///--------------------------------------------///		
	if(pThis->dwChartMode & CHART_MODE_GAIN_AUTO)
	{
		pThis->fYValMax = pDataStat->fYMax;
		pThis->fYValMin = pDataStat->fYMin;
		pThis->fYValAvg = pDataStat->fYAvg;

		fHighAmp = (pDataStat->fYMax - pDataStat->fYAvg);
		fLowAmp  = (pDataStat->fYAvg - pDataStat->fYMin);

		if(fHighAmp > fLowAmp)
		{
			pThis->fYValMax = (JFLOAT) (pDataStat->fYAvg + fHighAmp * 1.05);
			pThis->fYValMin = (JFLOAT) (pDataStat->fYAvg - fHighAmp * 1.05);
		}
		else
		{
			pThis->fYValMax = (JFLOAT)(pDataStat->fYAvg + fLowAmp * 1.05);			
			pThis->fYValMin = (JFLOAT)(pDataStat->fYAvg - fLowAmp * 1.05);
		}				
	}	
	if(pThis->dwChartMode & CHART_MODE_FIX_RANGE_ECG)
	{
		pThis->fYValMax = pDataStat->fYMax;
		pThis->fYValMin = pDataStat->fYMin;
		pThis->fYValAvg = pDataStat->fYAvg;

		fHighAmp = (pThis->fYValMax  - pThis->fYValMax);
		fLowAmp  = (pDataStat->fYAvg - pThis->fYValMin);

		if((fHighAmp < fEcgAmpHalf) && (fLowAmp < fEcgAmpHalf))
		{
			pThis->fYValFixedMax = fEcgAmpHalf + pThis->fYValAvg ;
			pThis->fYValFixedMin = pThis->fYValAvg - fEcgAmpHalf;
		}
		else
		{
			pThis->fYValFixedMax = fEcgAmpHalf + pThis->fYValAvg ;
			pThis->fYValFixedMin = pThis->fYValAvg - fEcgAmpHalf;
		}
				
		pThis->fYValMax = pThis->fYValFixedMax;
		pThis->fYValMin = pThis->fYValFixedMin;			 	
	}
	
	pThis->fYValAmp = pThis->fYValMax  - pThis->fYValMin ;

	if((pThis->fYValMax  != pThis->fYValMaxPre) ||
     (pThis->fYValMin  != pThis->fYValMinPre))
	{
		pThis->fYValMaxPre = pThis->fYValMax;
		pThis->fYValMinPre = pThis->fYValMin;
		bUpdateChart = TRUE;
	}

	///--------------------------------------------///
	/// Undraw previous Line
	///--------------------------------------------///		
	iStart = (pThis->iDataCnt - 4);
	if(iStart < 0)
	{
		iStart = 0;
	}
	
	///--------------------------------------------///
	/// Draw Line
	///--------------------------------------------///			
	pThis->iLineCnt = 0;	
	pDC->ForegroundColorSet(pThis->colorLine);
	//pDC->LineWidth(pThis->fLineWidth);	
	pDC->LineWidth(1);	
	for(i = iMinX ; i < (int)iDataCount; i ++)
	{
	  if(i < 0)
    {
      continue;
    } 
    if(i >= pDataSet->cnt)
    {
      continue;
    }

    fVal 		=  pDataSet->data[i];

		fValX = i * fValXStep;
		fValY = fVal;		
    
	  x1 = (JFLOAT) (((fValX - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
    y1 = (JFLOAT) (pThis->iChartHeight - ((fValY - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);

		/// Limited data line in the chart area
		if(x1 <= pThis->iChartX0)
		{
			x1 = pThis->iChartX0 + 1;
		}
		else if(x1 >= pThis->iChartX1)
		{
			x1 =  pThis->iChartX1 - 1;
		}

		if(y1 <= pThis->iChartY0)
		{
			y1 = pThis->iChartY0 + 1;
		}
		else if(y1 >= pThis->iChartY1)
		{
			y1 = pThis->iChartY1 - 1;
		}

		fArrX[i] = x1;
		fArrY[i] = y1;  

		x0 = x1;
		y0 = y1;
		iTotalCnt = iTotalCnt +1;
	}


	pDC->PathDraw(fArrX, fArrY, iTotalCnt);
	free(fArrX);	
	free(fArrY);	
	
	pThis->iDataCnt = pDataSet->cnt;

	return TRUE;
}

JINT 	JChartLineTimeHourDraw(JChart *pThis)
{
	JINT i 				= 0;
	JFLOAT fVal 	= 0;
	JDataSet  *pDataSet   = pThis->pDataSet;
	JDataStat *pDataStat  = &pThis->dataStat;

	JFLOAT fHighAmp  	= 0;
	JFLOAT fLowAmp 		= 0;

	JFLOAT fValX  		= 0;
	JFLOAT fValY 			= 0;
	
	JINT iDataCount    = 0; 

	JFLOAT x0 = CHPART_INVALID_POS;
	JFLOAT y0 = CHPART_INVALID_POS;	

	JFLOAT x1 = 0;
	JFLOAT y1 = 0;	

	JINT iSkipCnt = 0;
	JINT iTotalCnt = 0;

	JBOOL bUpdateChart = FALSE;

	JINT iStart = 0;
  JINT iMinX = 0;

  JFLOAT fValXStep = 0;

  JDraw *pDC = pThis->pDC;
  
  JDOUBLE  *fArrX = NULL;
  JDOUBLE  *fArrY = NULL;  

	if(pDC == NULL)
	{
		printf("[ERROR] There is no DC\r\n");
		return FALSE;
	}
	if(pDataSet == NULL)
	{
		printf("[ERROR] There is no DataSet \r\n");
		return FALSE;
	}
	
	///--------------------------------------------///
	/// Sample count check
	///--------------------------------------------///
  iDataCount =  pDataSet->cnt;

	fValXStep = 1;

	///--------------------------------------------///
	/// X-range seting
	///--------------------------------------------///
	pThis->fXValMin   = 0;
	pThis->fXValMax   = 3600; ///< 1 hour has 3600 sec
	pThis->fXValWidth = 3600;

	///--------------------------------------------///
	/// data count check
	///--------------------------------------------///  
  if(iDataCount >	pThis->fXValWidth)
  {
    printf("[CHART][ERROR][!!!!!!] Sample count  > %d\r\n", (JINT)pThis->fXValWidth);
    iDataCount = 	pThis->fXValWidth;
  }
	
	if(iDataCount == 0)
	{
		return TRUE;
	}	 

	fArrX = ( JDOUBLE  *)malloc(sizeof(JDOUBLE) * iDataCount);
	fArrY = ( JDOUBLE  *)malloc(sizeof(JDOUBLE) * iDataCount);	

	///--------------------------------------------///
	/// Find max and min, average
	///--------------------------------------------///		
	JChartStatCalculate(pThis, pDataStat);
	
	///--------------------------------------------///
	/// Y-Range auto-gain
	///--------------------------------------------///		
	if(pThis->dwChartMode & CHART_MODE_GAIN_AUTO)
	{
		pThis->fYValMax = pDataStat->fYMax;
		pThis->fYValMin = pDataStat->fYMin;

		fHighAmp = (pDataStat->fYMax - pDataStat->fYAvg);
		fLowAmp  = (pDataStat->fYAvg - pDataStat->fYMin);

		if(fHighAmp > fLowAmp)
		{
			pThis->fYValMax = (JFLOAT) (pDataStat->fYAvg + fHighAmp * 1.05);
			pThis->fYValMin = (JFLOAT) (pDataStat->fYAvg - fHighAmp * 1.05);
		}
		else
		{
			pThis->fYValMax = (JFLOAT)(pDataStat->fYAvg + fLowAmp * 1.05);			
			pThis->fYValMin = (JFLOAT)(pDataStat->fYAvg - fLowAmp * 1.05);
		}				
	}	

	pThis->fYValAmp = pThis->fYValMax  - pThis->fYValMin ;

	if((pThis->fYValMax  != pThis->fYValMaxPre) ||
     (pThis->fYValMin  != pThis->fYValMinPre))
	{
		pThis->fYValMaxPre = pThis->fYValMax;
		pThis->fYValMinPre = pThis->fYValMin;
		bUpdateChart = TRUE;
	}

	///--------------------------------------------///
	/// Undraw previous Line
	///--------------------------------------------///		
	iStart = (pThis->iDataCnt - 4);
	if(iStart < 0)
	{
		iStart = 0;
	}
	
	///--------------------------------------------///
	/// Draw Line
	///--------------------------------------------///			
	pThis->iLineCnt = 0;	
	pDC->ForegroundColorSet(pThis->colorLine);
	pDC->LineWidth(pThis->fLineWidth);	
	for(i = 0 ; i < (int)iDataCount; i = i + 1)
	{
	  if(i < 0)
    {
      continue;
    } 
    if(i >= pDataSet->cnt)
    {
      continue;
    }



    fVal 		=  pDataSet->data[i];

		fValX = i * fValXStep;
		fValY = fVal;	
		
	  x1 = (JFLOAT) (((fValX - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
    y1 = (JFLOAT) (pThis->iChartHeight - ((fValY - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);

		/// Limited data line in the chart area
		if(x1 <= pThis->iChartX0)
		{
			x1 = pThis->iChartX0 + 1;
		}
		else if(x1 >= pThis->iChartX1)
		{
			x1 =  pThis->iChartX1 - 1;
		}

		if(y1 <= pThis->iChartY0)
		{
			y1 = pThis->iChartY0 + 1;
		}
		else if(y1 >= pThis->iChartY1)
		{
			y1 = pThis->iChartY1 - 1;
		}

		fArrX[i] = x1;
		fArrY[i] = y1;  

		x0 = x1;
		y0 = y1;
		iTotalCnt = iTotalCnt +1;
	}


	pDC->PathDraw(fArrX, fArrY, iTotalCnt);
	free(fArrX);
	free(fArrY);	
	
	pThis->iDataCnt = pDataSet->cnt;

	return TRUE;
}

JINT 	JChartLineTimeDraw(JChart *pThis)
{
	JINT i 				= 0;
	JFLOAT fVal 	= 0;
	JDataSet  *pDataSet   = pThis->pDataSet;
	JDataStat *pDataStat  = &pThis->dataStat;

	JFLOAT fHighAmp  	= 0;
	JFLOAT fLowAmp 		= 0;

	JFLOAT fValX  		= 0;
	JFLOAT fValY 			= 0;
	
	JINT iDataCount    = 0; 

	JFLOAT x0 = CHPART_INVALID_POS;
	JFLOAT y0 = CHPART_INVALID_POS;	

	JFLOAT x1 = 0;
	JFLOAT y1 = 0;	

	JINT iSkipCnt = 0;
	JINT iTotalCnt = 0;

	JBOOL bUpdateChart = FALSE;

	JINT iStart = 0;
  JINT iMinX = 0;

  JFLOAT fValXStep = 0;

  JDraw *pDC = pThis->pDC;

	if(pDC == NULL)
	{
		printf("[ERROR] There is no DC\r\n");
		return FALSE;
	}
	if(pDataSet == NULL)
	{
		printf("[ERROR] There is no DataSet \r\n");
		return FALSE;
	}
	
	///--------------------------------------------///
	/// Sample count check
	///--------------------------------------------///
  iDataCount =  pDataSet->cnt;

	fValXStep = 1000 / pThis->fSampleRate;
  
  if(iDataCount > JDATA_MAX_CNT)
  {
    printf("[CHART][ERROR][!!!!!!] Sample count  > %d\r\n", JDATA_MAX_CNT );
    iDataCount = JDATA_MAX_CNT;
  }
	
	if(iDataCount == 0)
	{
		return TRUE;
	}	 

	///--------------------------------------------///
	/// Find max and min, average
	///--------------------------------------------///		
	JChartStatCalculate(pThis, pDataStat);
	
	
	///--------------------------------------------///
	/// Draw Line
	///--------------------------------------------///		
	if(pThis->dwChartMode & CHART_MODE_GAIN_AUTO)
	{
		pThis->fYValMax = pDataStat->fYMax;
		pThis->fYValMin = pDataStat->fYMin;

		fHighAmp = (pDataStat->fYMax - pDataStat->fYAvg);
		fLowAmp  = (pDataStat->fYAvg - pDataStat->fYMin);

		if(fHighAmp > fLowAmp)
		{
			pThis->fYValMax = (JFLOAT) (pDataStat->fYAvg + fHighAmp * 1.05);
			pThis->fYValMin = (JFLOAT) (pDataStat->fYAvg - fHighAmp * 1.05);
		}
		else
		{
			pThis->fYValMax = (JFLOAT)(pDataStat->fYAvg + fLowAmp * 1.05);			
			pThis->fYValMin = (JFLOAT)(pDataStat->fYAvg - fLowAmp * 1.05);
		}				
	}
	else if(pThis->dwChartMode & CHART_MODE_AUTO_GAIN2)
	{
		fHighAmp = (pDataStat->fYMax - pDataStat->fYMin);
		fLowAmp = (pDataStat->fYMax - pDataStat->fYMin);		
		pThis->fYValMax = (JINT)((pDataStat->fYMax + 0.1 * fHighAmp)/ JCHART_AUTO_GAIN2_DELTA) * JCHART_AUTO_GAIN2_DELTA + JCHART_AUTO_GAIN2_DELTA ;
		pThis->fYValMin = (JINT)((pDataStat->fYMin - 0.1 * fLowAmp)/ JCHART_AUTO_GAIN2_DELTA) * JCHART_AUTO_GAIN2_DELTA  - JCHART_AUTO_GAIN2_DELTA ; 
		iMinX = 0;
	}
	else if(pThis->dwChartMode & CHART_MODE_FIX_RANGE)
	{
		pThis->fYValMax = pThis->fYValFixedMax;
		pThis->fYValMin = pThis->fYValFixedMin;		

    pThis->fXValWidth = pThis->fXValFixRange;
         
    /// check input data is match display width
    if( (iDataCount * 200) <= pThis->fXValWidth)
    {
      pThis->fXValMax = pThis->fXValFixRange;
      pThis->fXValMin = 0;
      iMinX = 0;
    }
    else
    {	
      pThis->fXValMax = iDataCount * 200;
      pThis->fXValMin = pThis->fXValMax - pThis->fXValWidth;	
      iMinX  = (pThis->fXValMin / 200) -1;
    }

		if(pThis->fXValWidth <= 0)
		{
			pThis->fXValWidth = 1;
		}
	}
  
	pThis->fYValAmp = pThis->fYValMax  - pThis->fYValMin ;

	if((pThis->fYValMax  != pThis->fYValMaxPre) ||
     (pThis->fYValMin  != pThis->fYValMinPre))
	{
		pThis->fYValMaxPre = pThis->fYValMax;
		pThis->fYValMinPre = pThis->fYValMin;
		bUpdateChart = TRUE;
	}

	///--------------------------------------------///
	/// Undraw previous Line
	///--------------------------------------------///		
	iStart = (pThis->iDataCnt - 4);
	if(iStart < 0)
	{
		iStart = 0;
	}
	
	///--------------------------------------------///
	/// Draw Line
	///--------------------------------------------///			
	pThis->iLineCnt = 0;	
	printf("Data count = %d, MinX = %d, XValStep = %0.3f\r\n", (JINT)iDataCount, iMinX, fValXStep);
	pDC->ForegroundColorSet(pThis->colorLine);
	for(i = iMinX ; i < (int)iDataCount; i ++)
	{
	  if(i < 0)
    {
      continue;
    } 
    if(i >= pDataSet->cnt)
    {
      continue;
    }

    fVal 		=  pDataSet->data[i];

		fValX = i * fValXStep;
		fValY = fVal;		
    
	  x1 = (JFLOAT) (((fValX - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
    y1 = (JFLOAT) (pThis->iChartHeight - ((fValY - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);

		/// Limited data line in the chart area
		if(x1 <= pThis->iChartX0)
		{
			x1 = pThis->iChartX0 + 1;
		}
		else if(x1 >= pThis->iChartX1)
		{
			x1 =  pThis->iChartX1 - 1;
		}

		if(y1 <= pThis->iChartY0)
		{
			y1 = pThis->iChartY0 + 1;
		}
		else if(y1 >= pThis->iChartY1)
		{
			y1 = pThis->iChartY1 - 1;
		}

		/// Set pre-point
		if(((i - iMinX) == 0) || (x0 == CHPART_INVALID_POS))
		{
			x0 = x1;
			y0 = y1;			
		}
		if((x1 != x0) || (y1 != y0))
		{					
		 	printf("%-3d: (%0.0f, %0.0f) - >(%0.0f,%0.0f)\r\n", pThis->iLineCnt,fValX, fValY  , x1, y1);
			pDC->LineDraw(x0, y0, x1, y1);
		
			pThis->iLineCnt = pThis->iLineCnt + 1;
		}
		else
		{
			iSkipCnt++;
		}	
		x0 = x1;
		y0 = y1;
		iTotalCnt++;
	}
	pThis->iDataCnt = pDataSet->cnt;

	return TRUE;
}

void   JChartLineXYDraw(JChart *pThis)
{

}

void 	JChartBarDraw(JChart *pThis)
{

}

void   JChartCursorDraw(JChart *pThis)
{
	JDraw *pDC = pThis->pDC;
}

void		JChartInfoDraw(JChart *pThis)
{

}

JBOOL 	JChartLabelXDrawEx(JChart *pThis, char *strStart, char *strCenter, char *strEnd)
{
	JINT x0 		= 0;
	JINT y0 		= 0;

	char str[32];

	JFLOAT fXMargin	 = 36;
	JINT iYMargin	 = 10;
	JINT iCharWidth = 9;

	JINT i = 0;
    
  JFLOAT fDeltaVal;
  
 	JDraw *pDC = pThis->pDC;

 	
	///----------------------------//
	/// start label
	///----------------------------//	
	sprintf(str, "%s", strStart);

	x0 = pThis->iChartX0 ;
	y0 = pThis->iChartY1 + iYMargin;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, str);

	///----------------------------//
	/// center label
	///----------------------------//	
	sprintf(str, "%s", strCenter);

	x0 = pThis->iChartX0 +  pThis->iChartWidth  / 2  - fXMargin/2;
	y0 = pThis->iChartY1 + iYMargin;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, str);	


	///----------------------------//
	/// End label
	///----------------------------//	
	sprintf(str, "%s", strEnd);
	x0 = pThis->iChartX0	 + pThis->iChartWidth - fXMargin;
	y0 = pThis->iChartY0	 + pThis->iChartHeight  + iYMargin;
	
	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, str);
	
	return TRUE;
}


JBOOL 	JChartLabelXDraw(JChart *pThis)
{
	JINT x0 		= 0;
	JINT y0 		= 0;
	JINT x1 		= 0;
	JINT y1 		= 0;	
	JINT wd   	= 0;		
	JINT ht   	= 0;
	char str[32];
	JINT iCnt = 0;
	JINT iYMargin	 = 10;
	JINT iCharWidth = 9;

	JINT iCol = pThis->iCol;
	JINT i = 0;
    
  JFLOAT fDeltaVal;
  
 	JDraw *pDC = pThis->pDC;

 	if(iCol ==0)
	{
		return FALSE;
	}
 	
  /// check the data mode is fix range
  if(pThis->dwChartMode & CHART_MODE_FIX_RANGE)
  {
    fDeltaVal = (pThis->fXValFixRange) / iCol;
  }
  else
  {
    fDeltaVal = (pThis->fXValMax - pThis->fXValMin) / iCol;
  }

//	for(i = 0 ; i < iCol ; i++)
	i = 0;
	{
		///----------------------------//
		/// start label
		///----------------------------//	
		sprintf(str, "%03d", (JINT)((pThis->fXValMin + fDeltaVal * i)));
		
		iCnt = strlen(str);
		wd = iCnt * iCharWidth;		
		ht = 30;
		if(i ==0)
		{
			x0 = pThis->iChartX0 + i * pThis->iCellWidth;
		}
		else
		{
			x0 = pThis->iChartX0 + i * pThis->iCellWidth - wd / 2;		
		}
		y0 = pThis->iChartY1 + iYMargin;
		x1 = x0 + wd;
		y1 = y0 + ht;	

		pDC->ForegroundColorSet(pThis->colorXLabel);
		pDC->TextOut(x0, y0, str);
	}

	///----------------------------//
	/// End label
	///----------------------------//	
	sprintf(str, "%03d", (JINT)(pThis->fXValMax));
	iCnt = strlen(str);
	wd  	= iCnt * iCharWidth;		
	ht   	= 30;
	x0 = pThis->iChartX1;
	y0 = pThis->iChartY1 + iYMargin;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, str);
	
	return TRUE;
}

JBOOL	 	JChartLabelYDraw(JChart *pThis)
{
	JINT x0 		= 0;
	JINT y0 		= 0;

	JINT wd   	= 0;		
	JINT ht   	= 0;
	char str[32];
	char strLabel[258];	
	JINT iCnt = 0;
	JINT iXMargin	 = 12;
	JINT iCharWidth = 6;

	JINT iYMargin	 = 12;
	
	JINT iRow = pThis->iRow;
	JINT i = 0;
	JFLOAT fDeltaVal = (pThis->fYValMax - pThis->fYValMin) / iRow;

	JDraw *pDC = pThis->pDC;


	///----------------------------//
	/// start label (min)
	///----------------------------//	
	i = 0;	
	sprintf(str, "%0.3f", (JFLOAT)(pThis->fYValMin + i * fDeltaVal));
	sprintf(strLabel ,"%-12s", str);
	iCnt 	= strlen(strLabel);
	wd  	= iCnt * iCharWidth;		
	ht 		= 30;
	x0 		= pThis->iChartX0 - wd;
	y0 		= pThis->iChartY0 + pThis->iChartHeight ;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, strLabel);

	///----------------------------//
	/// center label (middle)
	///----------------------------//	
	i = iRow / 2;
	sprintf(str, "%0.3f", (JFLOAT)(pThis->fYValMin + i * fDeltaVal));
	sprintf(strLabel ,"%-12s", str);
	iCnt 	= strlen(strLabel);		
	wd  	= iCnt * iCharWidth;		
	ht 		= 30;
	x0 		= pThis->iChartX0 - wd;
	y0 		= pThis->iChartY0 + pThis->iChartHeight / 2 ;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, strLabel);

	///----------------------------//
	/// End label (max)
	///----------------------------//	
	sprintf(str, "%0.3f", (JFLOAT)(pThis->fYValMax));
	sprintf(strLabel ,"%-12s", str);
	
	iCnt = strlen(strLabel);
	wd = iCnt * iCharWidth;		
	ht = 15;
	x0 = pThis->iChartX0 - wd;
	y0 = pThis->iChartY0 + ht / 2;

	pDC->ForegroundColorSet(pThis->colorXLabel);
	pDC->TextOut(x0, y0, strLabel);
	
	return TRUE;	
}

JBOOL	 	JChartLabelDraw(JChart *pThis, char * strLabel, JINT x, JINT y, JDWORD dwColor)
{
	JDraw *pDC = pThis->pDC;	
	JINT x0 = x;
	JINT y0 = y;

	pDC->ForegroundColorSet(dwColor);
	pDC->TextOut(x0, y0, strLabel);

	return TRUE;
}

void 	JChartChartDraw(JChart *pThis)
{	
	/// Draw line
	JChartLineEcgDraw(pThis);

	JChartLabelXDraw(pThis);
	JChartLabelYDraw(pThis);	  
}

void JChartChartClear(JChart *pThis)
{
	JDraw *pDC = pThis->pDC;

	/// set chart
	pDC->ForegroundColorSet(pThis->colorChartBg);
	pDC->RectFill(pThis->iChartX0, pThis->iChartY0, pThis->iChartWidth, pThis->iChartHeight);
}

void 	JChartCanvasDraw(JChart *pThis)
{	
	JDraw *pDC = pThis->pDC;
	
	pDC->ForegroundColorSet(pThis->colorCanvasBg);
	pDC->RectFill(pThis->iCanvasLeft, pThis->iCanvasTop, pThis->iCanvasWidth, pThis->iCanvasHeight);

	/// set chart
	pDC->ForegroundColorSet(pThis->colorChartBg);
	pDC->RectFill(pThis->iChartX0, pThis->iChartY0, pThis->iChartWidth, pThis->iChartHeight);
}

void   JChartAxisXSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax)
{
	pThis->fXValMin = fMin;
	pThis->fXValMax = fMax;	

	/// Check time mode
	if(pThis->dwChartMode & CHART_MODE_X_TIME)
	{
		if(pThis->fXValMin < 0)
		{
			pThis->fXValMin  = 0;
		}
	}

	pThis->fXValWidth =  pThis->fXValMax  - pThis->fXValMin ;
}

void  JChartAxisXSet2(JChart *pThis, JFLOAT fMax, JFLOAT fWidth)
{
	pThis->fXValMin = fMax - fWidth ;
	pThis->fXValMax = fMax;	

	/// Check time mode
	if(pThis->dwChartMode & CHART_MODE_X_TIME)
	{
		if(pThis->fXValMin < 0)
		{
			pThis->fXValMin  = 0;
		}
		
		if(pThis->fXValMax < fWidth)
		{
			pThis->fXValMax = fWidth;
		}
	}

	pThis->fXValWidth =  fWidth;
}

void   JChartAxisXSetMax(JChart *pThis, JFLOAT fMax)
{
	pThis->fXValMin = fMax - pThis->fXValWidth  ;
	pThis->fXValMax = fMax;	

	/// Check time mode
	if(pThis->dwChartMode & CHART_MODE_X_TIME)
	{
		if(pThis->fXValMin < 0)
		{
			pThis->fXValMin  = 0;
		}

		/// Make sure the width OK
		if(pThis->fXValMax < pThis->fXValWidth )
		{
			pThis->fXValMax = pThis->fXValWidth ;
		}
	}
}

void   JChartAxisYSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax)
{
	pThis->fYValMin = fMin;
	pThis->fYValMax = fMax;	

	pThis->fYValFixedMax = fMax;
	pThis->fYValFixedMin = fMin;

	pThis->fYValAmp =  fMax - fMin;
}

void   JChartCanvasPosSet(JChart *pThis, JINT left, JINT top, JINT width, JINT height)
{
	pThis->iCanvasLeft		 	= left;
	pThis->iCanvasTop 			= top;
	pThis->iCanvasWidth 		= width;
	pThis->iCanvasHeight    = height;	
}

void   JChartChartPosSet(JChart *pThis, JINT left, JINT top, JINT right, JINT bottom)
{
	JINT iCellWidth  = 0;
	JINT iCellHeight = 0;		

	/// Check zero
	if(pThis->iCol <= 0)
	{
		pThis->iCol = JCHART_COL;
	}

	if(pThis->iRow <= 0 )
	{
		pThis->iRow = JCHART_ROW;	
	}

  ///   calculate the cell with and height
	iCellWidth  = (right - left) / (pThis->iCol);
	iCellHeight = (bottom - top) / (pThis->iRow);		

	pThis->iCellWidth  = iCellWidth;
	pThis->iCellHeight = iCellHeight;	

	
	/// Set the chart width and chart height
 	pThis->iChartWidth  = iCellWidth  * pThis->iCol;
 	pThis->iChartHeight = iCellHeight * pThis->iRow; 
	
	pThis->iChartLeft		 	= left;
	pThis->iChartTop 			= top;

	pThis->iChartX0		 	= left 		+ pThis->iCanvasLeft;
	pThis->iChartY0 		= top  	  + pThis->iCanvasTop;
	pThis->iChartX1 		= pThis->iChartX0	 + pThis->iChartWidth  ;
 	pThis->iChartY1 		= pThis->iChartY0  + pThis->iChartHeight;	
	
}

void JChartCursorXYDraw(JChart *pThis)
{
  char str[32];
	JDataSet  *pDataSet   = pThis->pDataSet;	
  JINT xValMax          = pThis->pDataSet->cnt;
  JINT x0Idx            = pThis->iCursorX;
  JINT y0               = 0;
  JFLOAT fXSec          = x0Idx /pThis->fSampleRate;

  JDraw *pDC = pThis->pDC;

  
  if((x0Idx < 0) && (x0Idx >= JDATA_MAX_CNT) && (x0Idx >= xValMax))
  {
    return;
  }

  if((x0Idx >= 0) && (x0Idx <JDATA_MAX_CNT))
  {
    y0  = pDataSet->data[x0Idx];
  }
  else
  {
    return;
  }
  pDC->FontSize(16);
  sprintf(str, "(%.1f,%d)", fXSec, y0); 
  pDC->TextOut(550, 130, str);
  pDC->FontSize(12);
  
}

JBOOL JChartLineDotYDraw(JChart *pThis, JINT x0Idx)
{
  JINT xValMax          = pThis->pDataSet->cnt;
	JINT  x0Loc        		= x0Idx*(1000/pThis->fSampleRate);  ///< index to mSec 
  
  JINT y0;
  JINT x0;
  JINT x1;
  JINT y1;

  JBOOL bSwap            = TRUE;	
  JINT i                 = 0;

  JDraw *pDC = pThis->pDC;

  
  
  if((x0Idx < 0) && (x0Idx >= JDATA_MAX_CNT) && (x0Idx >= xValMax))
  {
    return FALSE;
  }
  
	x0 = (((x0Loc - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
  y0 = pThis->iChartY0 + 1;
	y1 = pThis->iChartY1 - 1;
  x1 = x0 ;

  if((x0 < pThis->iChartX0) || (x0 > pThis->iChartX1))
  {
    return FALSE;
  }
  
  for(i = y0; i< pThis->iChartY1; i+= 10)
  {
    if(y0 > y1)
    {
      break;
    }
    y1 = y0 + 10;

    if(bSwap == TRUE)
    {
      bSwap = FALSE;
      /// draw line
      pDC->LineDraw((JINT)x0,(JINT)y0,(JINT)x1,(JINT)y1);
    
    }
    else
    {
      bSwap = TRUE;
    }

    y0 = y1;
  }

  return TRUE;
}

void JChartDrawDotLine(JChart *pThis, JINT startX0, JINT endX1)
{
	JDataSet  *pDataSet   = pThis->pDataSet;	
	JINT  x0Idx        		= startX0 / (1000/  pThis->fSampleRate);
	JFLOAT startY0        = 0;
  JINT  x1Idx        		= endX1 / (1000/  pThis->fSampleRate);
	JFLOAT endY1 					= 0;
  
  JFLOAT fSlope;
  JINT i;
  JBOOL bSwap = TRUE;	
  JINT iSX0;
  JINT iSX1;
  JFLOAT fStartY0;
  JFLOAT x0 = 0;
	JFLOAT y0 = 0;	
	JFLOAT x1 = 0;
	JFLOAT y1 = 0;	

	JDraw *pDC = pThis->pDC;

  if((x0Idx >= 0) && (x0Idx <JDATA_MAX_CNT))
  {
    startY0        = pDataSet->data[x0Idx];
  }

  if((x1Idx >= 0) && (x1Idx <JDATA_MAX_CNT))
  {
    endY1        = pDataSet->data[x1Idx];
  }
  
  
   
	x0 = (((startX0 - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
	y0 = (pThis->iChartHeight - ((startY0 - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);
  if(y0 < pThis->iChartY0)
  {
    y0 =  pThis->iChartY0 + 1;
  }
  if(y0 >  pThis->iChartY1)
  {
    y0 =  pThis->iChartY1 -1;
  }
	x1 = (((endX1 - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
	y1 = (pThis->iChartHeight - ((endY1 - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);
  if(y1 < pThis->iChartY0)
  {
    y1 =  pThis->iChartY0 + 1;
  }
  if(y1 >  pThis->iChartY1)
  {
    y1 =  pThis->iChartY1 -1;
  }
  
  /// check the X axis is right
	if((x0 <=0) ||(x1 <=0))
	{
    return;
	}
	if((x0 > pThis->iChartWidth +  pThis->iChartX0) )
  {
		return;
	}

  if((x1 > pThis->iChartWidth +  pThis->iChartX0))
	{
	  x1 = (pThis->iChartWidth +  pThis->iChartX0);
	}
	if((x0 < pThis->iChartX0) )
  {
    x0 =  pThis->iChartX0;
  } 
  if((x1 < pThis->iChartX0))
	{
	  return;
  }
  iSX0 = x0;
  iSX1 = x1;
  /// check the peak high is vaild 
  fSlope = ((float)y1 - (float)y0) / ((float)x1 - (float)x0);  

  fStartY0 = y0;  
  for(i = iSX0; i< iSX1; i+= 10)
  {
    x1 = x0 + 10;
    if(x1 > iSX1)
    {
      break;
    }
    y1 = fSlope *  (i - iSX0) + fStartY0;

    if(bSwap == TRUE)
    {
      bSwap = FALSE;
      /// draw line
      pDC->LineDraw((JINT)x0,(JINT)y0,(JINT)x1,(JINT)y1);
    
    }
    else
    {
      bSwap = TRUE;
    }

    x0 = x1;
    y0 = y1;
  }

}

void 	JChartDrawLabelEx(JChart *pThis, JFLOAT fValX, JINT xOff, JINT yOff , char * label)
{
	JDataSet  *pDataSet   = pThis->pDataSet;	
	JINT  xIdx        		= fValX / (1000/  pThis->fSampleRate);
	JFLOAT fValY 					= 0;
	JINT x0 = 0;
	JINT y0 = 0;	

	JINT x1 = 0;
	JINT y1 = 0;	

	JDraw *pDC = pThis->pDC;	
	

  if(xIdx < 0)
  {
    xIdx = 0;
  }
  if(xIdx >= JDATA_MAX_CNT)
  {
    xIdx = JDATA_MAX_CNT - 1;
  }
  fValY = pDataSet->data[xIdx];

	x0 = (JINT) (((fValX - pThis->fXValMin) * (JFLOAT) (pThis->iChartWidth)) / pThis->fXValWidth + pThis->iChartX0);
	y0 = (JINT) (pThis->iChartHeight - ((fValY - pThis->fYValMin) * (JFLOAT) (pThis->iChartHeight)) / pThis->fYValAmp + pThis->iChartY0);

	x1 = x0 + xOff;
	y1 = y0 + yOff;	

  /// check the X axis is right
	if((x0 <=0) ||(x1 <=0))
	{
		return;
	}
	if((x0 > pThis->iChartWidth +  pThis->iChartX0) ||(x1 > pThis->iChartWidth +  pThis->iChartX0))
	{
		return;
	}
	if((x0 < pThis->iChartX0) ||(x1 < pThis->iChartX0))
	{
		return;
	}
  
  /// check the Y axis is right
  if(pThis->dwChartMode & CHART_MODE_FIX_RANGE)
  {
    /// high chart view
    if((y0 < pThis->iChartY0) ||
       (y1 <  pThis->iChartY0))
  	{
    	if(label[0] == 0)
    	{
    		return;
    	}
    	pDC->LineDraw(x0 , pThis->iChartY0 , x1, pThis->iChartY0 + 4);
      pDC->ForegroundColorSet(COLOR_WHITE);
	    pDC->TextOut(x1, pThis->iChartY0 + 15, label);		
  		return;
  	} 
    
    /// low chart view  
    if((y0 >  pThis->iChartHeight + pThis->iChartY0) ||
       (y1 > pThis->iChartHeight + pThis->iChartY0))
  	{
    	if(label[0] == 0)
    	{
    		return;
    	}
    	pDC->LineDraw(x0, pThis->iChartY1 , x1, pThis->iChartY1 - 4);
      pDC->ForegroundColorSet(COLOR_WHITE);
      
	    pDC->TextOut(x1, pThis->iChartY1 - 20, label);		
      
      
  		return;
  	}    	
  }

  if((y1 <  pThis->iChartY1) && (y1 >  pThis->iChartY0) &&
     (y0 > pThis->iChartY0) && (y0 <  pThis->iChartY1))
  {
	  pDC->LineDraw(x0, y0, x1, y1);
  }
  else
  {
  	return;
	}
	/// Draw Label
	if(label[0] == 0)
	{
		return;
	}
	
  pDC->ForegroundColorSet(COLOR_WHITE);
  if((y1-20) < pThis->iChartY1)
  {
    
	  if((y1-20) > pThis->iChartY0)
    { 
      pDC->TextOut(x1, y1 - 20, label);		
    }
    else
    {
      pDC->TextOut(x1,pThis->iChartY0 + 15, label);		
    }
  }
}

void 	JChartDataSet(JChart *pThis, JDataSet *pDataSet)
{
	pThis->pDataSet = pDataSet;
}

JBOOL JChartStatCalculate(JChart *pThis, JDataStat *pDataStat)
{
	JINT i = 0;
	JINT iCnt = 0;
	JFLOAT fValX = 0;
	JFLOAT fValY = 0;
	JDataSet *pDataSet = pThis->pDataSet;

  iCnt = pDataSet->cnt;
	///--------------------------------------------///
	/// Find max and min, average
	///--------------------------------------------///	
	pDataStat->fXSum = 0;
	pDataStat->fXMax = -100000000;	
	pDataStat->fXMin =  100000000;	

	pDataStat->fYSum = 0;
	pDataStat->fYMax = -10000000000;	
	pDataStat->fYMin =  10000000000;

	if(iCnt <= 0)
	{
		return FALSE;
	}
	
	for(i = 0 ; i < iCnt; i++)
	{
		fValX = i * (1000.0 / pThis->fSampleRate);
		fValY = pDataSet->data[i] ;

		///--------------------------------------///
		///  X Values
		///--------------------------------------///
		
		/// find max X
		if(fValX > pDataStat->fXMax)
		{
			pDataStat->fXMax = fValX;
		}
		/// find min X
		if(fValX <  pDataStat->fXMin)
		{
			pDataStat->fXMin = fValX;
		}
		
		///--------------------------------------///
		///  Y Values
		///--------------------------------------///		
		/// find max Y
		if(fValY > pDataStat->fYMax)
		{
			pDataStat->fYMax = fValY;
		}
		/// find min Y
		if(fValY <  pDataStat->fYMin)
		{
			pDataStat->fYMin = fValY;
		}

		pDataStat->fYSum  = pDataStat->fYSum  + fValY;
		pDataStat->fXSum  = pDataStat->fXSum  + fValX;		
	}

	/// Calculate the average
	pDataStat->fYAvg = pDataStat->fYSum / (JFLOAT) iCnt;
	pDataStat->fXAvg = pDataStat->fXSum / (JFLOAT) iCnt;	

	return TRUE;
}

void 	JChartInfoPrint(JChart *pThis)
{	
	printf("%s", "---------------------------------------------------------------------\r\n");
	if(pThis->pDataSet != NULL)
	{
		printf("\t(CNT, IDX) = (%d, %d)\r\n",  			pThis->pDataSet->cnt,  	pThis->pDataSet->idx);	
	}
	printf("\t(CHART_LEFT, CHART_TOP) = (%d, %d)\r\n",  			pThis->iChartLeft,  pThis->iChartTop);	
	printf("\t(ROW, CELL) = (%d, %d)\r\n",  			pThis->iRow,  pThis->iCol);	
	printf("\t(CHART_WIDTH, CHART_HEIGHT) = (%d, %d)\r\n",  			pThis->iChartWidth,  pThis->iChartHeight);	
	printf("\t(X_VAL_MIN, X_VAL_MAX, X_VAL_WIDTH) = (%0.3f, %0.3f, %0.3f)\r\n",  pThis->fXValMin, pThis->fXValMax, pThis->fXValWidth);	
	printf("\t(Y_VAL_MIN, Y_VAL_MAX) = (%0.3f, %0.3f)\r\n",  pThis->fYValMin, pThis->fYValMax);	
	printf("\t(Y_FIXED_MIN, Y_FIXED_MAX, Y_FIXED_RANGE) = (%0.3f, %0.3f, %0.3f)\r\n\r\n",  pThis->fYValFixedMin, pThis->fYValFixedMax, pThis->fYValFixRange);		
}

void 	JChartTriangleDraw(JChart *pThis, JINT left, JINT top, JINT w, JINT h, JDWORD dwColor)
{
	JDraw *pDC = pThis->pDC;
	JDOUBLE x[3];
	JDOUBLE y[3];	
	
	x[0] = left;
	y[0] = top;

	x[1] = left - (w / 2);
	y[1] = top  - (h);

	x[2] = left + (w / 2);
	y[2] = top  - h;

	pDC->ForegroundColorSet(dwColor);
	pDC->TriangleFill(x, y);
}

void 	JChartDCSet(JChart *pThis, JDraw *pDC)
{
	pThis->pDC = pDC;
}

JBOOL 	JChartDCCheck(JChart *pThis)
{
	if(pThis->pDC == NULL)
	{	
		return FALSE;
	}
	return TRUE;
}

