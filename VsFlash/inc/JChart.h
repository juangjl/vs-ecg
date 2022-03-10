/**
 * @file JChart.h
 * @brief Chart API
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology, all rights reserved.
 * @note
*/ 
#ifndef __JCHART_H__
#define __JCHART_H__

#include "Global.h"
#define CHPART_INVALID_POS								(-999999)
#define CHART_X_MAX												(999999999)
#define CHART_X_MIN												(-999999999)

#define CHART_Y_MAX												(999999999)
#define CHART_Y_MIN												(-999999999)

/// Chart mode
#define CHART_MODE_GRID_AUTO							(1<<0)
#define CHART_MODE_GRID_MAJOR_LINE				(1<<1)
#define CHART_MODE_GRID_SUB_LINE					(1<<2)

#define CHART_MODE_GRID_CENTER_LINE				(1<<3)

#define CHART_MODE_AMP_AUTO_GAIN					(1<<4)

#define CHART_MODE_TIME_MODE							(1<<5)
#define CHART_MODE_FIX_COUNT							(1<<6)

#define CHART_MODE_DATA_CENTER						(1<<7)
#define CHART_MODE_ZERO_CENTER						(1<<8)

#define CHART_MODE_INFO_AREA							(1<<9)

#define CHART_MODE_LABEL_Y								(1<<10)
#define CHART_MODE_LABEL_X								(1<<11)

#define CHART_MODE_X_TIME									(1<<12)

#define CHART_MODE_GAIN_AUTO							(1<<13)
#define CHART_MODE_AUTO_GAIN2							(1<<14)
#define CHART_MODE_FIX_RANGE							(1<<15)
#define CHART_MODE_FIX_RANGE_ECG					(1<<16)


#define JCHART_MAX_SAMPLE									(2048)

#define JCHART_AUTO_GAIN2_DELTA						(5000)

typedef struct JPointSt
{
	JFLOAT x;
	JFLOAT y;
} JPoint;


typedef struct JDataStatSt
{
	JFLOAT fXMax;
	JFLOAT fXMin;	
	JFLOAT fXAvg;
	JFLOAT fXSum;

	JFLOAT fYMax;
	JFLOAT fYMin;	
	JFLOAT fYAvg;	
	JFLOAT fYCur;	
	JFLOAT fYSum;
} JDataStat;

typedef struct JChartST
{
	JINT 		iLineID;
	JDWORD 	dwChartMode;
	JBYTE 	bChartType;

	int 		iRow;
	int 		iCol;	
	
	JFLOAT 	fMaxVal;
	JFLOAT 	fMinVal;	

	JFLOAT 	fSampleRate;

	/// Layout 
	JINT  	iCanvasLeft;
	JINT  	iCanvasTop;	
	JINT 		iCanvasWidth;
	JINT 		iCanvasHeight;

	JINT  	iChartLeft;
	JINT  	iChartTop;	
	JINT 		iChartWidth;
	JINT 		iChartHeight;	


	JINT  	iChartX0;	///< absolute position of the screen for chart
	JINT  	iChartY0;	///< absolute position of the screen for chart	
	JINT  	iChartX1;	///< absolute position of the screen for chart
	JINT  	iChartY1;	///< absolute position of the screen for chart
		
	JINT  	iInfoLeft;
	JINT  	iInfoTop;	
	JINT 		iInfoWidth;
	JINT 		iInfoHeight;	

	JINT 		fLabelWidth;
	JINT 		fLabelHeight;	

	JINT 		fCanvasWidth;
	JINT 		fCanvasHeight;	

	JINT 		iCellWidth;
	JINT 		iCellHeight;	
	/// previous count
	JINT 		iDataCnt;

	/// data value
	JFLOAT 	fXValMin;
	JFLOAT 	fXValMax;	

	JFLOAT 	fXValFixedMax;
	JFLOAT 	fXValFixedMin;
	JFLOAT 	fXValFixRange;

	JFLOAT  fXValWidth;

	JFLOAT 	fYValFixedMax;
	JFLOAT 	fYValFixedMin;
	JFLOAT 	fYValFixRange;

	JFLOAT 	fYValMax;
	JFLOAT 	fYValMin;
	JFLOAT  fYValAmp;

	JFLOAT 	fYValMaxPre;
	JFLOAT 	fYValMinPre;

  JINT    iVoff;
  JINT    iAttn;
  JINT    iSpan;
  /// Cursor
  JINT    iCursorX;
  JBOOL   bCursorEn;
  JINT    iCursorXMin;  ///< data index
  JINT    iCursorXMax;  ///< data index  

	JFLOAT  fLineWidth;  
	/// Colors
	COLORREF colorCanvasBg;
	COLORREF colorChartBg;	
	COLORREF colorLine;		
	COLORREF colorGridMajor;			
	COLORREF colorGridSub;	

	COLORREF colorXLabel;			
	COLORREF colorYLabel;				

	JINT 			iDataSetNum;	
	JDataStat dataStat;

	JDataSet 	pDataStat;
	JINT 	 		iLineCnt;
	JDataSet  *pDataSet;

	///--------------------------------------///
	/// JDraw
	///--------------------------------------///
	JDraw 	*pDC;
} JChart;

extern  JVOID 	JChartInit(JChart *pThis);

extern  JVOID 	JChartDataSet(JChart *pThis, JDataSet *pDataSet);
extern  JBOOL 	JChartStatCalculate(JChart *pThis, JDataStat *pDataStat);
extern  JVOID 	JChartDCSet(JChart *pThis, JDraw *pDC);
extern  JBOOL 	JChartDCCheck(JChart *pThis);

extern  void    JChartSampleRateSet(JChart *pThis, JFLOAT freq);

extern  JVOID 	JChartReset(JChart *pThis);
extern  JVOID		JChartCellSet(JChart *pThis, JINT iRow, JINT iCol);

extern  JVOID 	JChartModeSet(JChart *pThis, JDWORD dwChartMode);
extern  JVOID 	JChartModeClear(JChart *pThis,  JDWORD dwChartMode);

extern  JVOID 	JChartGridDraw(JChart *pThis);	
extern  JVOID 	JChartGridAutoDraw(JChart *pThis);	

extern  JINT	 	JChartLineEcgDraw(JChart *pThis);	
extern  JINT 		JChartLineTimeHourDraw(JChart *pThis);

extern 	JINT 		JChartLineTimeDraw(JChart *pThis);
extern  JVOID   JChartLineXYDraw(JChart *pThis);

extern  JVOID 	JChartBarDraw(JChart *pThis);		
extern  JVOID   JChartCursorDraw(JChart *pThis);	
extern  JVOID		JChartInfoDraw(JChart *pThis);

extern  JBOOL 	JChartLabelXDraw(JChart *pThis);
extern  JBOOL	 	JChartLabelYDraw(JChart *pThis);	
extern  JBOOL 	JChartLabelDraw(JChart *pThis);	
extern  JBOOL 	JChartLabelXDrawEx(JChart *pThis, char *strStart, char *strCenter, char *strEnd);

extern  JVOID   JChartChartPosSet(JChart *pThis, JINT left, JINT top, JINT right, JINT bottom);
extern  JVOID 	JChartChartDraw(JChart *pThis);
extern  JVOID 	JChartChartClear(JChart *pThis);

extern  JVOID   JChartAxisXSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax);
extern  JVOID   JChartAxisXSet2(JChart *pThis, JFLOAT fMax, JFLOAT fWidth);
extern  JVOID   JChartAxisXSetMax(JChart *pThis, JFLOAT fMax);
extern  JVOID   JChartAxisYSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax);	

extern  JVOID 	JChartDrawLabelEx(JChart *pThis, JFLOAT fValX, JINT xOff, JINT yOff , char * label);
extern  JVOID   JChartDrawDotLine(JChart *pThis, JINT startX0, JINT endX1);

extern  JBOOL   JChartLineDotYDraw(JChart *pThis, JINT x0Idx);
extern  void    JChartCursorXYDraw(JChart *pThis);

extern  JVOID   JChartCanvasPosSet(JChart *pThis, JINT left, JINT top, JINT width, JINT height);	
extern  JVOID 	JChartCanvasDraw(JChart *pThis);

extern JVOID 	JChartInfoPrint(JChart *pThis);

#endif ///< __JCHART_H__

