/**
 * @file JAtr.h
 *
 *  JAtr.h ATR
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __JATR_H__
#define __JATR_H__

#include "Global.h"

///-------------------------------------------------------------------///
///
/// Annotation Code
/// https://archive.physionet.org/physiobank/annotations.shtml
/// https://archive.physionet.org/physiotools/wfdb/lib/ecgcodes.h
///-------------------------------------------------------------------///
#define	ATR_NOTQRS		(0)				/// 0  0 not-QRS (not a getann/putann code) 
#define ATR_NORMAL		(1)				/// 1  N normal beat 
#define	ATR_LBBB			(2)				/// 2  L left bundle branch block beat 
#define	ATR_RBBB			(3)			  /// 3  R right bundle branch block beat 
#define	ATR_ABERR			(4)			  /// 4  a aberrated atrial premature beat 
#define	ATR_PVC		  	(5)				/// 5  V premature ventricular contraction 
#define	ATR_FUSION		(6)			  /// 6  F fusion of ventricular and normal beat 
#define	ATR_NPC		  	(7)	      /// 7  J nodal (junctional) premature beat 
#define	ATR_APC				(8)				/// 8  A atrial premature contraction 
#define	ATR_SVPB			(9)				/// 9  S premature or ectopic supraventricular beat 
#define	ATR_VESC			(10)			/// 10 E ventricular escape beat 
#define	ATR_NESC			(11)			/// 11 j nodal (junctional) escape beat 
#define	ATR_PACE			(12)			/// 12 / paced beat 
#define	ATR_UNKNOWN		(13)			/// 13 Q unclassifiable beat 
#define	ATR_NOISE			(14)			/// 14 ~ signal quality change 
#define ATR_15		    (15)			/// 15 # ATR = 15
#define ATR_ARFCT			(16)			/// 16 | isolated QRS-like artifact 
#define ATR_17		    (15)			/// 17 # ATR = 17
#define ATR_STCH			(18)			/// 18 s ST change 
#define ATR_TCH				(19)			/// 19 T T-wave change 
#define ATR_SYSTOLE		(20)			/// 20 * systole 
#define ATR_DIASTOLE 	(21)			/// 21 D diastole 
#define	ATR_NOTE			(22)			/// 22 " comment annotation 
#define ATR_MEASURE 	(23)			/// 23 = measurement annotation 
#define ATR_PWAVE			(24)			/// 24 P P-wave peak 
#define	ATR_BBB				(25)			/// 25 B left or right bundle branch block 
#define	ATR_PACESP		(26)			/// 26 ^ non-conducted pacer spike 
#define ATR_TWAVE			(27)			/// 27 t T-wave peak 
#define ATR_RHYTHM		(28)			/// 28 + rhythm change 
#define ATR_UWAVE			(29)			/// 29 u U-wave peak 
#define	ATR_LEARN			(30)			/// 30 ? learning 
#define	ATR_FLWAV			(31)			/// 31 ! ventricular flutter wave 
#define	ATR_VFON			(32)			/// 32 [ start of ventricular flutter/fibrillation 
#define	ATR_VFOFF			(33)			/// 33 ] end of ventricular flutter/fibrillation 
#define	ATR_AESC			(34)			/// 34 e atrial escape beat 
#define ATR_SVESC			(35)			/// 35 n supraventricular escape beat 
#define ATR_LINK    	(36)			/// 36 @ link to external data (aux contains URL) 
#define	ATR_NAPC			(37)			/// 37 x non-conducted P-wave (blocked APB) 
#define	ATR_PFUS			(38)			/// 38 f fusion of paced and normal beat 
#define ATR_WFON			(39)			/// 39 ( waveform onset 
#define ATR_WFOFF			(40)			/// 40 ) waveform end 
#define ATR_RONT			(41)	    /// 41 r R-on-T premature ventricular contraction 

//#define ATR_PQ				(WFON)	/// 39 ' PQ junction (beginning of QRS) 
//#define	ATR_JPT				(WFOFF)	/// 40 , J point (end of QRS) 


/// ... annotation codes between RONT+1 and ACMAX inclusive are user-defined 

#define	ATR_ACMAX			(49)			/// value of largest valid annot code (must be < 50) 


#define  ATR_SKIP			(59)			///< the next four bytes are the interval in PDP-11 long integer format (the high 16 bits first, then the low 16 bits, with the low byte first in each pair).
#define  ATR_NUM			(60)			///< annotation num field for current and subsequent annotations; otherwise, assume previous annotation num (initially 0).
#define  ATR_SUB			(61)		  ///< annotation subtyp field for current annotation only; otherwise, assume subtyp = 0.
#define  ATR_CHN			(62)		  ///< annotation chan field for current and subsequent annotations; otherwise, assume previous chan (initially 0).
#define  ATR_AUX			(63)			///< number of bytes of auxiliary information (which is contained in the next I bytes); an extra null, not included in the byte count, is appended if I is odd.

#define  ATR_NONE     (255)	     ///< ADD by JL 

#define LABEL_NOTQRS	 "[NOTQRS]"	          /// 0 not-QRS (not a getann/putann code) 
#define LABEL_NORMAL	 "NORMAL"	            /// 1 normal beat 
#define LABEL_LBBB		 "LBBB"		            /// 2 left bundle branch block beat 
#define LABEL_RBBB		 "RBBB"		            /// 3 right bundle branch block beat 
#define LABEL_ABERR		 "ABERR"		          /// 4 aberrated atrial premature beat 
#define LABEL_PVC		   "PVC"		            /// 5 premature ventricular contraction 
#define LABEL_FUSION	 "FUSION"	            /// 6 fusion of ventricular and normal beat 
#define LABEL_NPC		   "NPC"		            /// 7 nodal (junctional) premature beat 
#define LABEL_APC			 "APC"				       	/// 8 atrial premature contraction 
#define LABEL_SVPB		 "SVPB"		  	       	/// 9 premature or ectopic supraventricular beat 
#define LABEL_VESC		 "VESC"		  	       	/// 10 ventricular escape beat 
#define LABEL_NESC		 "NESC"		  	       	/// 11 nodal (junctional) escape beat 
#define LABEL_PACE		 "PACE"		  	       	/// 12 paced beat 
#define LABEL_UNKNOWN	 "UNKNOWN"		       	/// 13 unclassifiable beat 
#define LABEL_NOISE		 "NOISE"			       	/// 14 signal quality change 
#define LABEL_ATR_15	 "15"									/// 15 ATR = 15
#define LABEL_ARFCT		 "ARFCT"			       	/// 16 isolated QRS-like artifact 
#define LABEL_ATR_17	 "17"									/// 17 ATR = 17
#define LABEL_STCH		 "STCH"		  	       	/// 18 ST change 
#define LABEL_TCH			 "TCH"				       	/// 19 T-wave change 
#define LABEL_SYSTOLE	 "SYSTOLE"		       	/// 20 systole 
#define LABEL_DIASTOLE "DIASTOLE"  	       	/// 21 diastole 
#define LABEL_NOTE		 "NOTE"		  	       	/// 22 comment annotation 
#define LABEL_MEASURE  "MEASURE"  	       	/// 23 measurement annotation 
#define LABEL_PWAVE		 "PWAVE"			       	/// 24 P-wave peak 
#define LABEL_BBB			 "BBB"				       	/// 25 left or right bundle branch block 
#define LABEL_PACESP	 "PACESP"	  	       	/// 26 non-conducted pacer spike 
#define LABEL_TWAVE		 "TWAVE"			       	/// 27 T-wave peak 
#define LABEL_RHYTHM	 "RHYTHM"	  	       	/// 28 rhythm change 
#define LABEL_UWAVE		 "UWAVE"			       	/// 29 U-wave peak 
#define LABEL_LEARN		 "LEARN"			       	/// 30 learning 
#define LABEL_FLWAV		 "FLWAV"			       	/// 31 ventricular flutter wave 
#define LABEL_VFON		 "VFON"		  	       	/// 32 start of ventricular flutter/fibrillation 
#define LABEL_VFOFF		 "VFOFF"			       	/// 33 end of ventricular flutter/fibrillation 
#define LABEL_AESC		 "AESC"		  	       	/// 34 atrial escape beat 
#define LABEL_SVESC		 "SVESC"			       	/// 35 supraventricular escape beat 
#define LABEL_LINK     "LINK"     	       	/// 36 link to external data (aux contains URL) 
#define LABEL_NAPC		 "NAPC"		  	       	/// 37 non-conducted P-wave (blocked APB) 
#define LABEL_PFUS		 "PFUS"		  	       	/// 38 fusion of paced and normal beat 
#define LABEL_WFON		 "WFON"		  	       	/// 39 waveform onset 
#define LABEL_WFOFF		 "WFOFF"			       	/// 40 waveform end 
#define LABEL_RONT		 "RONT"		  	        /// 41 R-on-T premature ventricular contraction 

#define LABEL_ATR_42	 "42"									/// 42 ATR
#define LABEL_ATR_43	 "43"									/// 43 ATR
#define LABEL_ATR_44	 "44"									/// 44 ATR
#define LABEL_ATR_45	 "45"									/// 45 ATR
#define LABEL_ATR_46	 "46"									/// 46 ATR
#define LABEL_ATR_47	 "47"									/// 47 ATR
#define LABEL_ATR_48	 "48"									/// 48 ATR
#define LABEL_ATR_49	 "49"									/// 49 ATR

#define LABEL_ATR_50	 "50"									/// 50 ATR
#define LABEL_ATR_51	 "51"									/// 51 ATR
#define LABEL_ATR_52	 "52"									/// 52 ATR
#define LABEL_ATR_53	 "53"									/// 53 ATR
#define LABEL_ATR_54	 "54"									/// 54 ATR
#define LABEL_ATR_55	 "55"									/// 55 ATR
#define LABEL_ATR_56	 "56"									/// 56 ATR
#define LABEL_ATR_57	 "57"									/// 57 ATR
#define LABEL_ATR_58	 "58"									/// 58 ATR
#define LABEL_ATR_SKIP "[SKIP]"							/// 59 the next four bytes are the interval in PDP-11 long integer format (the high 16 bits first, then the low 16 bits, with the low byte first in each pair).

#define LABEL_ATR_NUM	 "[NUM]"							/// 60 annotation num field for current and subsequent annotations; otherwise, assume previous annotation num (initially 0).
#define LABEL_ATR_SUB	 "[SUB]"							/// 61 annotation subtyp field for current annotation only; otherwise, assume subtyp = 0.
#define LABEL_ATR_CHN	 "[CHN]"							/// 62 annotation chan field for current and subsequent annotations; otherwise, assume previous chan (initially 0).
#define LABEL_ATR_AUX	 "[AUX]"							/// 63 number of bytes of auxiliary information (which is contained in the next I bytes); an extra null, not included in the byte count, is appended if I is odd.

#define ABBREV_NOTQRS	    "NOTQRS"	            /// 0 not-QRS (not a getann/putann code) 
#define ABBREV_NORMAL	    "N"	                  /// 1 normal beat 
#define ABBREV_LBBB		    "L"		                /// 2 left bundle branch block beat 
#define ABBREV_RBBB		    "R"		                /// 3 right bundle branch block beat 
#define ABBREV_ABERR		  "a"		                /// 4 aberrated atrial premature beat 
#define ABBREV_PVC		    "V"		                /// 5 premature ventricular contraction 
#define ABBREV_FUSION	    "F"	                  /// 6 fusion of ventricular and normal beat 
#define ABBREV_NPC		    "J"		                /// 7 nodal (Junctional) premature beat 
#define ABBREV_APC			  "A"				       	    /// 8 atrial premature contraction 
#define ABBREV_SVPB		    "S"   		  	       	/// 9 premature or ectopic supraventricular beat 
#define ABBREV_VESC		    "E"		  	       	    /// 10 ventricular escape beat 
#define ABBREV_NESC		    "j"		  	       	    /// 11 nodal (junctional) escape beat 
#define ABBREV_PACE		    "//"		 	       	    /// 12 paced beat 
#define ABBREV_UNKNOWN	  "Q"		             	  /// 13 unclassifiable beat 
#define ABBREV_NOISE		  "~"			           	  /// 14 signal quality change 
#define ABBREV_ATR_15	    "15"									/// 15 ATR = 15
#define ABBREV_ARFCT		  "|"			       	      /// 16 isolated QRS-like artifact 
#define ABBREV_ATR_17	    "17"									/// 17 ATR = 17
#define ABBREV_STCH		    "s"		  	       	    /// 18 ST change 
#define ABBREV_TCH			  "T"	  			       	  /// 19 T-wave change 
#define ABBREV_SYSTOLE	  "*"		           	    /// 20 systole 
#define ABBREV_DIASTOLE   "D"          	       	/// 21 diastole 
#define ABBREV_NOTE		    "\""		  	         	/// 22 comment annotation 
#define ABBREV_MEASURE    "="         	     	  /// 23 measurement annotation 
#define ABBREV_PWAVE		  "P"			       	      /// 24 P-wave peak 
#define ABBREV_BBB			  "B"				       	    /// 25 left or right bundle branch block 
#define ABBREV_PACESP	    "^"	  	       	      /// 26 non-conducted pacer spike 
#define ABBREV_TWAVE		  "t"			       	      /// 27 T-wave peak 
#define ABBREV_RHYTHM	    "+"	        	       	/// 28 rhythm change 
#define ABBREV_UWAVE		  "u"			       	      /// 29 U-wave peak 
#define ABBREV_LEARN		  "?"		    	       	  /// 30 learning 
#define ABBREV_FLWAV		  "!"			       	      /// 31 ventricular flutter wave 
#define ABBREV_VFON		    "["		  	       	    /// 32 start of ventricular flutter/fibrillation 
#define ABBREV_VFOFF		  "]"	    		       	  /// 33 end of ventricular flutter/fibrillation 
#define ABBREV_AESC		    "e"		  	       	    /// 34 atrial escape beat 
#define ABBREV_SVESC		  "n"			       	      /// 35 supraventricular escape beat 
#define ABBREV_LINK       "@"       	       	  /// 36 link to external data (aux contains URL) 
#define ABBREV_NAPC		    "x"		  	       	    /// 37 non-conducted P-wave (blocked APB) 
#define ABBREV_PFUS		    "f"		  	       	    /// 38 fusion of paced and normal beat 
#define ABBREV_WFON		    "("		      	       	/// 39 waveform onset 
#define ABBREV_WFOFF		  ")"	    		       	  /// 40 waveform end 
#define ABBREV_RONT		    "RONT"		  	        /// 41 R-on-T premature ventricular contraction 

#define ABBREV_ATR_42	    "42"									/// 42 ATR
#define ABBREV_ATR_43	    "43"									/// 43 ATR
#define ABBREV_ATR_44	    "44"									/// 44 ATR
#define ABBREV_ATR_45	    "45"									/// 45 ATR
#define ABBREV_ATR_46	    "46"									/// 46 ATR
#define ABBREV_ATR_47	    "47"									/// 47 ATR
#define ABBREV_ATR_48	    "48"									/// 48 ATR
#define ABBREV_ATR_49	    "49"									/// 49 ATR  

#define ABBREV_ATR_50	    "50"									/// 50 ATR
#define ABBREV_ATR_51	    "51"									/// 51 ATR
#define ABBREV_ATR_52	    "52"									/// 52 ATR
#define ABBREV_ATR_53	    "53"									/// 53 ATR
#define ABBREV_ATR_54	    "54"									/// 54 ATR
#define ABBREV_ATR_55	    "55"									/// 55 ATR
#define ABBREV_ATR_56	    "56"									/// 56 ATR
#define ABBREV_ATR_57	    "57"									/// 57 ATR
#define ABBREV_ATR_58	    "58"									/// 58 ATR
#define ABBREV_ATR_SKIP   "[SKIP]"							/// 59 the next four bytes are the interval in PDP-11 long integer format (the high 16 bits first, then the low 16 bits, with the low byte first in each pair).

#define ABBREV_ATR_NUM	  "[NUM]"							/// 60 annotation num field for current and subsequent annotations; otherwise, assume previous annotation num (initially 0).
#define ABBREV_ATR_SUB	  "[SUB]"							/// 61 annotation subtyp field for current annotation only; otherwise, assume subtyp = 0.
#define ABBREV_ATR_CHN	  "[CHN]"							/// 62 annotation chan field for current and subsequent annotations; otherwise, assume previous chan (initially 0).
#define ABBREV_ATR_AUX	  "[AUX]"							/// 63 number of bytes of auxiliary information (which is contained in the next I bytes); an extra null, not included in the byte count, is appended if I is odd.


#pragma pack(push)
#pragma pack(1)

typedef struct JAtrSt
{    
  JBYTE bAtr;  
  JBYTE bMS[3];
} JAtrType;

#define ATR_QUEUE_CNT  (128)
typedef struct JAtrCtlSt
{
  JINT iAtrCnt;
  JINT iAtrQueueHead;
  JINT iAtrQueueTail;  
  JAtrType pAtrData[ATR_QUEUE_CNT];
} JAtrQueueType;
#pragma pack(pop)

extern JAtrQueueType AtrQueue;
extern const char * JAtrLabel[];

extern JBOOL  JAtrFileBinSave(char * strFileName, JINT idx, JINT A, JFLOAT fTimeSec);
extern JBOOL  JAtrFileCsvSave(char * strFileName, JINT idx, JDWORD A, JFLOAT fTimeSec, JFLOAT fDeltaSec);

extern void   JAtrDataGet(JAtrType *pAtr, JINT *piAtr, JFLOAT *pfTimeSec);
extern void   JAtrDataPrint(JAtrType *pAtr);
extern void   JAtrDataClean(JAtrType *pAtr);

extern JINT   JAtrSizeGet(JAtrQueueType * pAtrCtl);
extern JBOOL  JAtrFullCheck(JAtrQueueType * pAtrCtl);
extern JBOOL  JAtrDelete(JAtrQueueType * pAtrCtl);
extern void   JAtrRead(JAtrQueueType * pAtrCtl,  JAtrType *pAtrRead);
extern void   JAtrReadOut(JAtrQueueType * pAtrCtl,  JAtrType *pAtrRead);
extern void   JAtrAdd(JAtrQueueType * pAtrCtl, JINT  iAtr, JFLOAT fTimeSec);
extern void   JAtrAddEx(JAtrQueueType * pAtrQueue, JAtrType *pAtrNew);
extern void   JAtrInit(JAtrQueueType * pAtrCtl);
#endif ///< __JATR_H__

