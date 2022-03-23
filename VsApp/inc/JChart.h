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
	JFLOAT 	fYValAvg;
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

extern  void 	JChartInit(JChart *pThis);

extern  void 	JChartDataSet(JChart *pThis, JDataSet *pDataSet);
extern  JBOOL JChartStatCalculate(JChart *pThis, JDataStat *pDataStat);
extern  void 	JChartDCSet(JChart *pThis, JDraw *pDC);
extern  JBOOL JChartDCCheck(JChart *pThis);

extern  void  JChartSampleRateSet(JChart *pThis, JFLOAT freq);

extern  void 	JChartReset(JChart *pThis);
extern  void	JChartCellSet(JChart *pThis, JINT iRow, JINT iCol);

extern  void 	JChartModeSet(JChart *pThis, JDWORD dwChartMode);
extern  void 	JChartModeClear(JChart *pThis,  JDWORD dwChartMode);

extern  void 	JChartGridDraw(JChart *pThis);	
extern  void 	JChartGridAutoDraw(JChart *pThis);	

extern  JINT	JChartLineEcgDraw(JChart *pThis);	
extern  JINT 	JChartLineTimeHourDraw(JChart *pThis);

extern 	JINT 	JChartLineTimeDraw(JChart *pThis);
extern  void  JChartLineXYDraw(JChart *pThis);

extern  void 	JChartBarDraw(JChart *pThis);		
extern  void  JChartCursorDraw(JChart *pThis);	
extern  void	JChartInfoDraw(JChart *pThis);

extern  JBOOL JChartLabelXDraw(JChart *pThis);
extern  JBOOL	JChartLabelYDraw(JChart *pThis);	
extern 	JBOOL	JChartLabelDraw(JChart *pThis, char * strLabel, JINT x, JINT y, JDWORD dwColor);

extern  JBOOL JChartLabelXDrawEx(JChart *pThis, char *strStart, char *strCenter, char *strEnd);

extern  void  JChartChartPosSet(JChart *pThis, JINT left, JINT top, JINT right, JINT bottom);
extern  void 	JChartChartDraw(JChart *pThis);
extern  void 	JChartChartClear(JChart *pThis);

extern  void  JChartAxisXSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax);
extern  void  JChartAxisXSet2(JChart *pThis, JFLOAT fMax, JFLOAT fWidth);
extern  void  JChartAxisXSetMax(JChart *pThis, JFLOAT fMax);
extern  void  JChartAxisYSet(JChart *pThis, JFLOAT fMin, JFLOAT fMax);	


extern  void 	JChartDrawLabelEx(JChart *pThis, JFLOAT fValX, JINT xOff, JINT yOff , char * label);
extern  void  JChartDrawDotLine(JChart *pThis, JINT startX0, JINT endX1);


extern  JBOOL JChartLineDotYDraw(JChart *pThis, JINT x0Idx);
extern  void  JChartCursorXYDraw(JChart *pThis);

extern  void  JChartCanvasPosSet(JChart *pThis, JINT left, JINT top, JINT width, JINT height);	
extern  void 	JChartCanvasDraw(JChart *pThis);

extern 	JBOOL	JChartXValToXPos(JChart *pThis,JFLOAT fXVal, JINT *piXPOS);
extern 	void 	JChartTriangleDraw(JChart *pThis, JINT left, JINT top, JINT w, JINT h, JDWORD dwColor);

extern 	void 	JChartInfoPrint(JChart *pThis);

#endif ///< __JCHART_H__

