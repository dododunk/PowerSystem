// TTTView.cpp : implementation of the CTTTView class
//

#include "stdafx.h"
#include "TTT.h"
#include "stdlib.h"
#include "math.h"
#include "TTTView.h"
#include "MainFrm.h"
#include "DisplayAnalyzeWin.h"
#include "TTTDoc.h"
#include "Dask.h"
#include "SwitchLineDlg.h"
#include "AngleSet.h"
#include "ras.h."
#include "bch63457.h"
#include "TestDlg.h"
#include "ChangeFileDlg.h"
#include "SendEveryTime.h"
#include "TIMEDLG.h"
#include "Afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
POINT input_pos[16]= {{470, 280},  {440, 280},
                       {410, 280},  {380, 280},
                       {350, 280},  {320, 280},
                       { 290, 280},  {260, 280},
                       {230, 280},  {200, 280},
                       {170, 280},  {140, 280},
                       {110, 280},  {80, 280},
                       { 50, 280},  { 20, 280},
                      };
POINT output_pos[16] ={
                       {470, 340},  {440, 340},
                       {410, 340},  {380, 340},
                       {350, 340},  {320, 340},
                       { 290, 340},  {260, 340},
                       {230, 340},  {200, 340},
                       {170, 340},  {140, 340},
                       {110, 340},  {80, 340},
                       { 50, 340},  { 20, 340},
                      };

POINT io_pos[16] ={
                       {395, 40},  {370, 40},
                       {345, 40},  {320, 40},
                       {295, 40},  {270, 40},
                       { 245, 40},  {220, 40},
                       {195, 40},  {170, 40},
                       {145, 40},  {120, 40},
                       {95, 40},  {70, 40},
                       { 45, 40},  { 20, 40},
                      };

//相关检验数据表 20度
short Correlation_Table20[256] = 
{
  -6,  -6,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -7,  -5,  -5,  -6,  -6,
  -5,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -6,  -5,  -6,  -6,  -6,  -6,
  -5,  -7,  -6,  -6,  -5,  -6,  -7,  -7,  -6,  -6,  -5,  -6,  -6,  -6,  -5,  -5,
  -5,  -4,  -5,  -6,  -5,  -4,  -5,  -6,  -6,  -5,  -6,  -5,  -5,  -5,  -5,  -5,
  -5,  -6,  -6,  -6,  -6,  -6,  -7,  -7,  -6,  -5,  -6,  -6,  -6,  -5,  -5,  -4,
  -4,  -4,  -4,  -5,  -4,  -5,  -5,  -5,  -4,  -5,  -5,  -5,  -5,  -5,  -6,  -6,
  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -5,  -5,  -4,  -6,
  -5,  -6,  -4,  -4,  -5,  -5,  -6,  -5,  -5,  -5,  -6,  -5,  -6,  -6,  -6,  -6,
  -6,  -7,  -6,  -7,  -6,  -4,  -7,  -7,  -5,  -5,  -5,  -5,  -5,  -4,  -5,  -4,
  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -5,  -4,  -5,  -4,  -4,  -5,  -4,  -5,  -5,
  -4,  -5,  -5,  -3,  -5,  -4,  -4,  -4,  -5,  -4,  -4,  -4,  -4,  -4,  -3,  -4,
   4,   9,  15,  47,  84, 125, 190, 281, 414, 586, 790,1005,1212,1395,1543,1656,
1733,1783,1807,1812,1804,1786,1765,1743,1719,1699,1678,1661,1646,1631,1618,1605,
1592,1576,1559,1537,1514,1485,1454,1417,1376,1330,1281,1228,1171,1111,1051, 988,
 920, 858, 792, 727, 664, 600, 538, 480, 423, 368, 315, 269, 228, 187, 153, 121,
  96,  69,  49,  31,  14,  -2, -16, -29, -40, -51, -59, -60, -55, -52, -47, -49
};

//相关检验数据表 10度
short Correlation_Table10[256] = 
{
	  -3,  -3,  -3,  -2,  -3,  -2,  -3,  -2,  -4,  -2,  -4,  -2,  -3,  -3,  -3,  -3,
	  -3,  -2,  -2,  -3,  -2,  -3,  -2,  -3,  -2,  -3,  -3,  -2,  -3,  -3,  -3,  -2,
	  -3,  -1,  -4,  -1,  -4,  -2,  -4,  -2,  -4,  -3,  -3,  -3,  -4,  -3,  -5,  -3,
	  -3,  -2,  -3,  -3,  -3,  -4,  -4,  -3,  -2,  -3,  -2,  -2,  -3,  -2,  -1,  -3,
	  -2,  -2,  -2,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -4,  -2,  -3,  -3,  -4,
	  -3,  -4,  -4,  -3,  -3,  -4,  -3,  -3,  -2,  -3,  -2,  -2,  -3,  -3,  -2,  -2,
	  -3,  -2,  -3,  -3,  -2,  -1,  -3,  -2,  -2,  -3,  -2,  -1,  -1,  -2,  -2,  -2,
	  -3,  -2,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -3,  -3,  -3,  -3,  -3,  -4,  -4,
	  -3,  -3,  -4,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,
	  -1,  -1,  -2,  -1,  -2,  -1,  -1,  -2,  -2,  -1,  -1,  -1,  -2,  -1,  -1,  -1,
	  -2,   0,  -1,  -1,  -1,  -1,  -2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -2,
	  -3,  -2,  -2,  -1,  -1,   0,  -1,   0,   1,   6,  14,  20,  26,  32,  37,  45,
	  54,  61,  72,  85,  98, 113, 130, 148, 170, 192, 216, 242, 267, 292, 316, 339,
	 362, 383, 398, 415, 425, 433, 440, 442, 440, 440, 433, 426, 414, 403, 389, 376,
	 362, 346, 330, 314, 296, 281, 265, 250, 233, 217, 201, 184, 168, 153, 140, 126,
	 113, 101,  89,  79,  69,  57,  51,  42,  36,  28,  21,  15,  11,   6,   0,  -3
};

//相关检验数据表 5度
short Correlation_Table05[256] = 
{
   -3,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -4,   -2,   -4,   -2,   -3,   -3,   -3,   -3,
   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -3,   -3,   -2,
   -2,   -2,   -3,   -2,   -3,   -3,   -3,   -3,   -4,   -3,   -3,   -3,   -4,   -3,   -5,   -3,
   -2,   -3,   -3,   -3,   -3,   -4,   -3,   -3,   -3,   -3,   -2,   -3,   -2,   -2,   -2,   -2,
   -2,   -2,   -2,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -2,   -3,   -3,   -4,
   -3,   -4,   -4,   -3,   -3,   -4,   -3,   -3,   -2,   -3,   -2,   -2,   -3,   -3,   -2,   -2,
   -3,   -2,   -3,   -3,   -1,   -2,   -3,   -2,   -2,   -2,   -3,    0,   -3,    0,   -3,   -2,
   -3,   -1,   -1,   -2,   -2,   -2,   -2,   -2,   -2,   -3,   -3,   -3,   -3,   -3,   -4,   -4,
   -3,   -3,   -4,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -1,   -2,
   -1,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -2,   -1,   -1,   -1,   -2,   -1,    0,   -2,
   -1,   -1,   -1,   -1,   -1,   -1,   -2,   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -2,
   -3,   -2,   -2,   -1,    0,   -1,   -1,   -1,   -2,   -2,   -1,    0,    0,   -1,    0,    0,
   -1,   -1,    0,   -1,   -2,   -1,   -1,    0,    0,    0,    0,    1,    4,    9,   16,   22,
   27,   35,   39,   47,   56,   64,   77,   88,  101,  118,  135,  155,  174,  196,  221,  248,
  271,  297,  320,  334,  334,  284,  269,  254,  237,  222,  203,  188,  172,  157,  143,  130,
  116,  104,   92,   82,   70,   60,   53,   44,   37,   30,   22,   17,   12,    8,    0,   -1,
};

//相关检验数据表 20度
short  SourceArrays[256] = 
	{ 
	  -6,  -6,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -7,  -5,  -5,  -6,  -6,
	  -5,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -6,  -5,  -6,  -6,  -6,  -6,
	  -5,  -7,  -6,  -6,  -5,  -6,  -7,  -7,  -6,  -6,  -5,  -6,  -6,  -6,  -5,  -5,
	  -5,  -4,  -5,  -6,  -5,  -4,  -5,  -6,  -6,  -5,  -6,  -5,  -5,  -5,  -5,  -5,
	  -5,  -6,  -6,  -6,  -6,  -6,  -7,  -7,  -6,  -5,  -6,  -6,  -6,  -5,  -5,  -4,
	  -4,  -4,  -4,  -5,  -4,  -5,  -5,  -5,  -4,  -5,  -5,  -5,  -5,  -5,  -6,  -6,
	  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -5,  -5,  -4,  -6,
	  -5,  -6,  -4,  -4,  -5,  -5,  -6,  -5,  -5,  -5,  -6,  -5,  -6,  -6,  -6,  -6,
	  -6,  -7,  -6,  -7,  -6,  -4,  -7,  -7,  -5,  -5,  -5,  -5,  -5,  -4,  -5,  -4,
	  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -5,  -4,  -5,  -4,  -4,  -5,  -4,  -5,  -5,
	  -4,  -5,  -5,  -3,  -5,  -4,  -4,  -4,  -5,  -4,  -4,  -4,  -4,  -4,  -3,  -4,
	   4,   9,  15,  47,  84, 125, 190, 281, 414, 586, 790,1005,1212,1395,1543,1656,
	1733,1783,1807,1812,1804,1786,1765,1743,1719,1699,1678,1661,1646,1631,1618,1605,
	1592,1576,1559,1537,1514,1485,1454,1417,1376,1330,1281,1228,1171,1111,1051, 988,
	 920, 858, 792, 727, 664, 600, 538, 480, 423, 368, 315, 269, 228, 187, 153, 121,
	  96,  69,  49,  31,  14,  -2, -16, -29, -40, -51, -59, -60, -55, -52, -47, -49
	};

//相关检验数据表 5度
long CorrelationSix_Table05[25] =
{ 
   0,     0,    0,     0,    9,
   28,   47,   76,   118,  175, 
  246,  317,  295,   237,   187, 
  143,  104,   70,    44,    23,
    6,    1,    0,     0,     0  
};

//相关检验数据表 10度
long CorrelationSix_Table10[25] =
{ 
  -3,   2,   20,   38,   62, 
  98, 149,  216,  291,  361,
 412, 438,  437,  414,  375,
 330,  280, 233,  184,  139,
 101,   68,  43,   21,    5
};

//相关检验数据表 20度
long CorrelationSix_Table20[25] =
{ 
   -1,   23,  133,  427, 1002,
 1531, 1774, 1800, 1742, 1679,
 1631, 1591, 1536, 1452, 1329,
 1170,  986,  792,  600,  423,
  270,  153,   71,   14,   -4
};

/////////////////////////////////////////////////////////////////////////////
// CTTTView 117 248
short DataBuf[1000000];//135000 全采的话：512*4*4*63 = 516096
short TempDataBuf[1000000];
int   DiffAll[200000],SumAll[20000];
int   DataLen,RecCount;
unsigned  short  Value;
float  g_GainSampleWin;
float g_CurrentGainSampleWin;
BOOL     m_TestPhase = FALSE;
short       	m_TestCurrent[140000];//电流
short           m_TestVoltage[140000];//电压
int             m_TestParameter[6];

U32   nReadCount = 2048;
I16   card;
UINT  SampleRate;
BOOL  bClearOp, bClearOp1, bParity, bClearRecv;
CDisplayWaveWin    m_wndWaveWin;
CDisplayAnalyzeWin m_wndAnalyzeWin;
I16                       err;
unsigned short ReadBuff[1024];
int               m_DivideVal;    //采的数要除的值1、PCI-9111DR   16     2、PCI-9111HR     1 
CEvent            eventWriteD;


#define LASTCHANNEL   15//15//;//
#define DISPWINWIDTH 640

IMPLEMENT_DYNCREATE(CTTTView, CFormView)

BEGIN_MESSAGE_MAP(CTTTView, CFormView)
//{{AFX_MSG_MAP(CTTTView)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
ON_CBN_SELCHANGE(IDC_COMBO_SMPRATE, OnSelchangeComboSmprate)
ON_BN_CLICKED(IDC_CHECK_CH3, OnCheckCh3)
ON_BN_CLICKED(IDC_CHECK_CH0, OnCheckCh0)
ON_BN_CLICKED(IDC_CHECK_CH1, OnCheckCh1)
ON_BN_CLICKED(IDC_CHECK_CH2, OnCheckCh2)
ON_BN_CLICKED(IDC_CHECK_CH4, OnCheckCh4)
ON_BN_CLICKED(IDC_CHECK_CH5, OnCheckCh5)
ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
ON_EN_CHANGE(IDC_EDIT_STARTPOINT, OnChangeEditStartpoint)
ON_CBN_SELCHANGE(IDC_COMBO_CYCLENUM, OnSelchangeComboCyclenum)
ON_EN_CHANGE(IDC_EDIT_GAIN, OnChangeEditGain)
ON_BN_CLICKED(IDC_RADIO_REALTIME, OnRadioRealtime)
ON_BN_CLICKED(IDC_RADIO_ANALYZE, OnRadioAnalyze)
ON_BN_CLICKED(IDC_BUTTON_SHIFTLEFT, OnButtonShiftleft)
ON_BN_CLICKED(IDC_BUTTON_SHIFTRIGHT, OnButtonShiftright)
ON_BN_CLICKED(IDC_BUTTON_ASHIFTLEFT, OnButtonAshiftleft)
ON_BN_CLICKED(IDC_BUTTON_ASHIFTRIGHT, OnButtonAshiftright)
ON_EN_CHANGE(IDC_EDIT_GAINSMPWIN, OnChangeEditGainsmpwin)
ON_CBN_SELCHANGE(IDC_COMBO_CHSELECT, OnSelchangeComboChselect)
ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
ON_BN_CLICKED(IDC_CHECK_AVER4, OnCheckAver4)
ON_BN_CLICKED(IDC_CHECK_DIFFI, OnCheckDiffi)
ON_EN_CHANGE(IDC_EDIT_ANGLE, OnChangeEditAngle)
ON_EN_CHANGE(IDC_EDIT_THRESHOLD, OnChangeEditThreshold)
ON_EN_CHANGE(IDC_EDIT_SENDCODE, OnChangeEditSendcode)
ON_BN_CLICKED(IDC_CHECK_CH10, OnCheckCh10)
ON_BN_CLICKED(IDC_CHECK_CH9, OnCheckCh9)
ON_BN_CLICKED(IDC_CHECK_CH8, OnCheckCh8)
ON_BN_CLICKED(IDC_CHECK7, OnCheckBandPass)
ON_EN_CHANGE(IDC_EDIT_BANDPASSANGLE, OnChangeEditBandpassangle)
ON_BN_CLICKED(IDC_CHECK_DVDT, OnCheckDvdt)
ON_BN_CLICKED(IDC_REAL_START, OnRealStart)
ON_BN_CLICKED(IDC_REALSTOP, OnRealstop)
ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
ON_BN_CLICKED(IDC_BUTTON_ANGLE, OnButtonAngle)
ON_BN_CLICKED(IDC_REAL_RECORD, OnRealRecord)
ON_BN_CLICKED(IDC_REAL_SEND, OnRealSend)
ON_BN_CLICKED(IDC_BUTTON_STOPREC, OnButtonStoprec)
ON_BN_CLICKED(IDC_READLINE, OnReadline)
	ON_CBN_SELCHANGE(IDC_PROTOCOLS, OnSelchangeProtocols)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_SETTIMER, OnSettimer)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_ZHONGZHI, OnZhongzhi)
	ON_BN_CLICKED(IDC_DECODE, OnDecode)
	ON_BN_CLICKED(IDC_FFT, OnFft)
	ON_BN_CLICKED(IDC_READFILTER, OnReadfilter)
	ON_BN_CLICKED(IDC_DELETEFILE, OnDeletefile)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_BCHTEST, OnBchtest)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK_DIFFI2, OnCheckDiffi2)
	ON_BN_CLICKED(IDC_CHECK_DIFFI3, OnCheckDiffi3)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_TESTDATA, OnTestdata)
	ON_EN_CHANGE(IDC_STARTPOINT, OnChangeStartpoint)
	ON_EN_CHANGE(IDC_WAVEPOINTS, OnChangeWavepoints)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPINSTART, OnOutofmemorySpinstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINSTART, OnDeltaposSpinstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINAVERAGE, OnDeltaposSpinaverage)
	ON_BN_CLICKED(IDC_FINDZERO, OnFindzero)
	ON_BN_CLICKED(IDC_ALLADD, OnAlladd)
	ON_EN_CHANGE(IDC_ALLTIMES, OnChangeAlltimes)
	ON_BN_CLICKED(IDC_INITIALIZE, OnInitialize)
	ON_BN_CLICKED(IDC_COMSET, OnComset)
	ON_EN_CHANGE(IDC_ANGLE, OnChangeAngle)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHANGEUSEDATA, OnChangeusedata)
	ON_BN_CLICKED(IDC_SENDALLONE, OnSendallone)
	ON_BN_CLICKED(IDC_BUTTON_TESTPHASE, OnButtonTestphase)
	ON_EN_CHANGE(IDC_EDIT_CURRENTGAINSMPWIN, OnChangeEditCurrentgainsmpwin)
	ON_CBN_SELCHANGE(IDC_ORDERCOMBO, OnSelchangeOrdercombo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP

// Standard printing commands
ON_MESSAGE(WM_EVENT, OnEvent)
ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTTView construction/destruction
//
CTTTView::CTTTView()
: CFormView(CTTTView::IDD)
{
	//{{AFX_DATA_INIT(CTTTView)
	m_iSampleRate =     9;
	m_bCh0        = FALSE;
	m_bCh1        = FALSE;
	m_bCh2        = FALSE;
	m_bCh3        = FALSE;
	m_bCh4        = FALSE;
	m_bCh5        = FALSE;
	m_bCh8        = FALSE;
	m_bCh9        = FALSE;
	m_bCh10       = FALSE;
	m_nStartPoint = 0;
	m_nCycleNum   = 0;
	m_iCycleNum   = -1;
	m_iModeSel    = 0;
	m_fGain       = 0.0f;
	m_fGainSampleWin = 0.0f;
	m_iChSelect   = 0;
	m_bDiff2      = FALSE;
	m_bAver4      = FALSE;
	m_bDiffI      = TRUE;
	m_bBandPass   = FALSE;
	m_generatrix  =     0;
	m_phase       =     0;
	m_module      = 13107101;
	m_data        = _T("");
	m_tong789     =  FALSE;
	m_SendOrder   = _T("");
	m_ReceiveStr  = _T("");
	m_addone      =  FALSE;
	m_IfWriteToLog = FALSE;
	m_qzhikiu      = FALSE;
	m_bDiff3       = FALSE;
	m_findpipeimax =  TRUE;
	m_radio        =     1;
	m_quancai      = FALSE;
	m_AllAdd       = FALSE;
	m_alltimes     =     1;
	m_delay        =  1000;
	m_angle        =    20;
	m_derrors      =    31;
	m_check4bit    = FALSE;
	m_xinjiaobian  = FALSE;
	m_Is0Station   =  TRUE;
	m_fCurrentGainSampleWin = 1.0f;
	m_equal = FALSE;
	m_wavepoints   =   512;
	m_millondseconds = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_fGain           =  1.0;
	m_iCycleNum       =    2;
	m_fGainSampleWin  =  1.0;
	m_iChSelect       =    0;
	Line              =    0;
	m_angles          =    0;
	m_iBandPassPoints =   62;//128;

	m_startpoint      = 1024;
	m_wavepoints      =  512;

	//通道 
	m_Channels        =   1;
	m_Stopping        = FALSE;

	m_SuccessTimes    =   0;
   	m_TotalTimes      =   0;
	m_CollectErrors   =   0;//采集错误
	
	CTTTApp * pt = (CTTTApp*)AfxGetApp();
    
	if(pt->m_ifcardis9111dr)
	{	
		m_maxDecimalVal = 4096;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
		m_DivideVal     =   16;//采的数要除的值1、PCI-9111DR   16     2、PCI-9111HR     1 
	}
	else
	{
		m_maxDecimalVal = 65536;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
		m_DivideVal     =     1;//采的数要除的值1、PCI-9111DR   16     2、PCI-9111HR     1 
	} 

	m_StatusStr      =      "";
	
	m_TestPhase      =   FALSE;
	m_TimeSeconds    =       0;

}

CTTTView::~CTTTView()
{

	bClearOp  = TRUE;
	Sleep(200);

}

void CTTTView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTTView)
	DDX_Control(pDX, IDC_ORDERCOMBO, m_ordercombo);
	DDX_Control(pDX, IDC_COMBO_SMPRATE, m_SmprateComb);
	DDX_Control(pDX, IDC_PROTOCOLS, m_ProtocolControl);
	DDX_Control(pDX, IDC_CHECKCOMBOX, m_comcheck);
	DDX_Control(pDX, IDC_DATACOMBO, m_comdata);
	DDX_Control(pDX, IDC_STOPCOMBO, m_comstop);
	DDX_Control(pDX, IDC_COMBOBIT, m_combobit);
	DDX_Control(pDX, IDC_COMBOPORT, m_comboport);
	DDX_Control(pDX, IDC_SPINAVERAGE, m_SpinAverage);
	DDX_Control(pDX, IDC_SPINSTART, m_Spinstart);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_CBIndex(pDX, IDC_COMBO_SMPRATE, m_iSampleRate);
	DDX_Check(pDX, IDC_CHECK_CH0, m_bCh0);
	DDX_Check(pDX, IDC_CHECK_CH1, m_bCh1);
	DDX_Check(pDX, IDC_CHECK_CH2, m_bCh2);
	DDX_Check(pDX, IDC_CHECK_CH3, m_bCh3);
	DDX_Check(pDX, IDC_CHECK_CH4, m_bCh4);
	DDX_Check(pDX, IDC_CHECK_CH5, m_bCh5);
	DDX_Check(pDX, IDC_CHECK_CH8, m_bCh8);
	DDX_Check(pDX, IDC_CHECK_CH9, m_bCh9);
	DDX_Check(pDX, IDC_CHECK_CH10, m_bCh10);
	DDX_Text(pDX, IDC_EDIT_STARTPOINT, m_nStartPoint);
	DDX_CBIndex(pDX, IDC_COMBO_CYCLENUM, m_iCycleNum);
	DDX_Radio(pDX, IDC_RADIO_REALTIME, m_iModeSel);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_fGain);
	DDX_Text(pDX, IDC_EDIT_GAINSMPWIN, m_fGainSampleWin);
	DDX_CBIndex(pDX, IDC_COMBO_CHSELECT, m_iChSelect);
	DDX_Check(pDX, IDC_CHECK_DIFFI2, m_bDiff2);
	DDX_Check(pDX, IDC_CHECK_AVER4, m_bAver4);
	DDX_Check(pDX, IDC_CHECK_DIFFI, m_bDiffI);
	DDX_Check(pDX, IDC_CHECK7, m_bBandPass);
	DDX_Text(pDX, IDC_GENERATRIX, m_generatrix);
	DDX_Text(pDX, IDC_PHASE, m_phase);
	DDX_Text(pDX, IDC_MODULE, m_module);
	DDX_Text(pDX, IDC_DATAVALUE, m_data);
	DDX_Check(pDX, IDC_CHECK5, m_tong789);
	DDX_Text(pDX, IDC_SENDORDER, m_SendOrder);
	DDX_Text(pDX, IDC_RECEIVE, m_ReceiveStr);
	DDX_Check(pDX, IDC_ADDONE, m_addone);
	DDX_Check(pDX, IDC_CHECK9, m_IfWriteToLog);
	DDX_Check(pDX, IDC_CHECK10, m_qzhikiu);
	DDX_Check(pDX, IDC_CHECK_DIFFI3, m_bDiff3);
	DDX_Check(pDX, IDC_FINDPIPEVALUE, m_findpipeimax);
	DDX_Radio(pDX, IDC_RADIO3, m_radio);
	DDX_Check(pDX, IDC_CHECK11, m_quancai);
	DDX_Check(pDX, IDC_ALLADD, m_AllAdd);
	DDX_Text(pDX, IDC_ALLTIMES, m_alltimes);
	DDX_Control(pDX, IDC_MSCOMM, m_Com);
	DDX_Text(pDX, IDC_DELAY, m_delay);
	DDX_Text(pDX, IDC_ANGLE, m_angle);
	DDX_Text(pDX, IDC_EDITT, m_derrors);
	DDX_Check(pDX, IDC_CHECK4BIT, m_check4bit);
	DDX_Check(pDX, IDC_CHECK12, m_xinjiaobian);
	DDX_Check(pDX, IDC_IS0STATION, m_Is0Station);
	DDX_Text(pDX, IDC_EDIT_CURRENTGAINSMPWIN, m_fCurrentGainSampleWin);
	DDX_Check(pDX, IDC_CHECK13, m_equal);
	DDX_Text(pDX, IDC_DELAYHAOMIAO, m_millondseconds);
	//}}AFX_DATA_MAP
}

BOOL CTTTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}



void CTTTView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	CString                    str;
    SampleRate             =     9;
    g_Gain                 =     1;
	g_GainSampleWin        =     1;
	g_CurrentGainSampleWin =     1;
    g_Extend               =     10;
	CycleNum               =     1;
	PointsNum              =   512;//1/4波
    bParity                = FALSE;
	bFlash                 = FALSE;
	bClearRecv             = FALSE;
	MinSum                 =  1000;
	BandPassAngle          =    45;
	m_protocol             =    71;

    CTTTApp * pt = (CTTTApp*)AfxGetApp();

    if(pt->m_ifcardis9111dr)
	{
		
		if((card = Register_Card(PCI_9111DG, 0)) <0 ) 
		{
			 
			MessageBox("采集卡初始化时错误，检查采集卡是否安装或松动！\r\n否则读表采集等功能操作时将会出错！","警告",MB_OK|MB_ICONWARNING);
		
		}

	}
	else
	{
		
		if((card = Register_Card(PCI_9111HR, 0)) <0 ) 
		{
		
			MessageBox("采集卡初始化时错误，检查采集卡是否安装或松动！\r\n否则读表采集等功能操作时将会出错！","警告",MB_OK|MB_ICONWARNING);
		
		}

	}
	
  //err = AI_9111_Config(card, TRIG_EXT_STROBE, 0, 1024);
	err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    //Beep(300,400);
		
    }
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
    if (err!=0)
	{
    	//Beep(300,400);
		
    }
	
	/*
	
	*/
	////////////////////////////////////////
	
	m_wndWaveWin.SubclassDlgItem(IDC_WAVE, this);
    m_wndAnalyzeWin.SubclassDlgItem(IDC_ANALYZE, this);

	//相位
	m_spin3.SetRange(0, 2);
	m_spin3.SetPos(0);
	//母线编号
	m_spin4.SetRange(1, 4);
	m_spin4.SetPos(1);

	
	m_Spinstart.SetRange(0,2500);
	m_Spinstart.SetPos(1024);
	
	m_SpinAverage.SetRange(400,5000);
	m_SpinAverage.SetPos(512);

    OnRadio1();

	CEdit* pyy = (CEdit*)GetDlgItem(IDC_ORDER);
    pyy->SetLimitText(2);
	pyy = (CEdit*)GetDlgItem(IDC_ORDER);
    pyy->SetWindowText("02");

	m_SmprateComb.ResetContent();

	for(int i = 10; i <= 100; i = i + 10)
	{
		str.Format("%3d",i);
		m_SmprateComb.AddString(str);

	}

    m_SmprateComb.SetCurSel(9);

	OnRadioRealtime();

	m_ProtocolControl.ResetContent();
	m_ProtocolControl.AddString("21");
    m_ProtocolControl.AddString("22");
    m_ProtocolControl.AddString("31");
    m_ProtocolControl.AddString("32");
	m_ProtocolControl.AddString("61");
    m_ProtocolControl.AddString("62");
	m_ProtocolControl.AddString("71");
    m_ProtocolControl.AddString("72");
    m_ProtocolControl.AddString("73");

    m_ProtocolControl.SetCurSel(6);
	
	InitOrderCombo(71);

	OnSelchangeProtocols();
	
	GetDlgItem(IDC_CHECK13)->EnableWindow(FALSE);

	//初始化端口
	GetComPorts();
	
}


UINT WriteD(LPVOID pParam)
{	
	Beep(5000,400);
	int type =(int)pParam;
	CMainFrame* pts   = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pts->GetActiveView());
	WaitForSingleObject(eventWriteD.m_hObject,INFINITE);
	Beep(5000,400);
	//发命令
   	pview->SendOrderToSCM(115/*模块号*/,0/*手拉手电站码*/,1/*母线*/,1 + 1/*线号*/,0/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,0x02/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);
	return 0;

}

/////////////////////////////////////////////////////////////////////////////
// CTTTView printing

BOOL CTTTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTTTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTTTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTTTView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTTTView diagnostics

#ifdef _DEBUG
void CTTTView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTTTView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTTTDoc* CTTTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTTTDoc)));
	return (CTTTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTTView message handlers

BOOL CTTTView::DestroyWindow() 
{
	Release_Card(card);
    KillTimer(1);  
	KillTimer(2); 
	return CFormView::DestroyWindow();
}

void CTTTView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:
		{
			KillTimer(1);
			//检查串口情况
			CheckComData();
			break;
		}
	case 2:
		{
			//全发1
			SendAllOne();
			break;
		}
	}

	CFormView::OnTimer(nIDEvent);
}

UINT  ScanChannels(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	CString                  str;
	unsigned short ReadBuf[1024];
    BOOLEAN    bHalfReady, bStop;
	float                  m_kkk;

    U32  count1,count2 =     0;
    do{
		do {
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStop);
		} while (!bHalfReady);

		AI_AsyncDblBufferTransfer(card, ReadBuf);

		//算789通道出来的数据
		m_wndWaveWin.NewDataIn(ReadBuf,nReadCount/2); 

	}while(!bClearOp);

    AI_AsyncClear(card, &count1);
	
    return 0;
}

void CTTTView::OnButtonStart() 
{
	//显示波形关了
	m_ShowWave     =   FALSE;
  	g_Extend       =      10;
	UpdateData(FALSE);
	m_TestPhase    =   FALSE;

	unsigned short *ai_buf=NULL;
    I16 err;
	
    err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    Beep(300,400);
		return;
    }
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
  
	err = AI_ContScanChannels(card,LASTCHANNEL, AD_B_10_V, ai_buf, nReadCount,(SampleRate+1)*1000, ASYNCH_OP);
  	
	AfxBeginThread(ScanChannels,this);
	bClearOp = 0;
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMSET)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);
}

void CTTTView::OnButtonStop() 
{
	bClearOp   =      1;	
//	m_TestPhase = FALSE;

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMSET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(TRUE);
}


void CTTTView::OnSelchangeComboSmprate() 
{
	UpdateData();
	SampleRate = m_iSampleRate;
}

void CTTTView::OnCheckCh3() 
{
	UpdateData();
	//通道 
	m_Channels        = 3;
}

void CTTTView::OnCheckCh0() 
{
	UpdateData();
	//通道 
	m_Channels        =  0;
}

void CTTTView::OnCheckCh1() 
{
	UpdateData();
	//通道 
	m_Channels        =  1;
}

void CTTTView::OnCheckCh2() 
{
	UpdateData();
	//通道 
	m_Channels        =  2;
}

void CTTTView::OnCheckCh4() 
{
	UpdateData();
	//通道 
	m_Channels        =  4;
}

void CTTTView::OnCheckCh5() 
{
	UpdateData();
	//通道 
	m_Channels        =  5;
}

void CTTTView::OnCheckCh8() 
{
	UpdateData();
	//通道 
	m_Channels        =  8;
}

void CTTTView::OnCheckCh9() 
{
	UpdateData();
	//通道 
	m_Channels        =  9;
}

void CTTTView::OnCheckCh10() 
{
	UpdateData();
	//通道 
	m_Channels        =  10;
}


void CTTTView::OnChangeEditStartpoint() 
{
	UpdateData();
	OnButtonUpdate();
}

void CTTTView::OnSelchangeComboCyclenum() 
{
	UpdateData();
	

	switch(m_iCycleNum)
	{
	case 0:
		{
			CycleNum = 1; 
			g_Extend = DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 1:
		{
			CycleNum = 2; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 2:
		{
			CycleNum = 4;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 3:
		{
			CycleNum = 8;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/8;
		    break;
		}
	case 4: 
		{	
			CycleNum = 16; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/16;
		    break;
		}
	}
    OnButtonUpdate();
	
}


int CTTTView::FindZeroPointCao(UINT WaveNum)
{
    UINT CntPoint=0,CntCycle  =     0;
	UINT temp,CurZeroPoint    =     0;
	BOOL bReady               = FALSE;
	
    do{
       	temp = DataBuf[CntPoint++];

		if(temp > m_maxDecimalVal/2 - 1)
		{ 
			
			if(CntPoint > CurZeroPoint+10)
			{
				
				bReady = TRUE; 

			}

		}
		else
		{			
			if(bReady)
			{

				if( DataBuf[CntPoint + 10 ]< m_maxDecimalVal/2)
				{  
					CurZeroPoint = CntPoint;
					bReady       = FALSE; 
					CntCycle++;
				}

			}
			
		}
		
	}while(CntCycle<WaveNum+1);
	
	return CntPoint-1;
}

int CTTTView::FindCyclePointsNum(int WaveNum)
{
	UINT cnt=0, cnt1=0;
	int iPointsNum=0;
	char buf[6];
	double temp;
	BOOL bOverZero=false,bReady=false, bExit=false;
	
	do{
		file.Seek(36+WaveNum*2000*8+cnt*8,CFile::begin);
		file.Read(buf,6);
		temp=atof(buf);
		
		if(!bReady)
		{
			if(temp<0)
				bReady=true;   
		}
		else
		{
			if(temp>=0)
			{ 
				bReady   = false; 
				bOverZero=  true;
				cnt1          ++;
			}

		}

		if(bOverZero)
			iPointsNum++;
		if(cnt1==5)
			bExit=true; 
		cnt++;
	}while(!bExit);
	
	return iPointsNum/4;
}

void CTTTView::OnChangeEditGain() 
{
	CString str;
	UpdateData();
	g_Gain = m_fGain;
    str.Format("   +%3.3fV -",10/m_fGain);
	GetDlgItem(IDC_STATIC_ANALYZESCALEP)->SetWindowText(str);
    str.Format("   -%3.3fV -",10/m_fGain);
	GetDlgItem(IDC_STATIC_ANALYZESCALEN)->SetWindowText(str);
	OnButtonUpdate();
}

void CTTTView::OnChangeEditGainsmpwin() 
{
	CString str;
	UpdateData();

	Invalidate();

	g_GainSampleWin        = m_fGainSampleWin;
	g_CurrentGainSampleWin = m_fCurrentGainSampleWin;	

	str.Format("+%3.2fV(+%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEP)->SetWindowText(str);
    str.Format("-%3.2fV(-%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEN)->SetWindowText(str);

	if(m_iModeSel > 0)
	{
	    OnButtonUpdate();
	}
}

void CTTTView::OnRadioRealtime() 
{
	m_TestPhase = FALSE;
	UpdateData();	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE); 
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE); 
	GetDlgItem(IDC_REAL_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	GetDlgItem(IDC_READLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_SETTIMER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(TRUE);

 //   GetDlgItem(IDC_CHECK11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_HIDE);
}   

void CTTTView::OnRadioAnalyze() 
{
	m_TestPhase = FALSE;

	UpdateData();
	
	if(!m_ShowWave)
	{
		Invalidate();
	}

	m_ShowWave     =   TRUE;
    
	switch(CycleNum)
	{
	case 1: 
		{
			g_Extend=DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 2:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 4:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 8:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/8;
			break;
		}
	case 16:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/16;
			break;
		}
	}
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(TRUE);
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_REAL_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_REAL_START)->SetWindowText("读表");
	GetDlgItem(IDC_REALSTOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
    GetDlgItem(IDC_SETTIMER)->EnableWindow(TRUE);
	GetDlgItem(IDC_DECODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);


//	GetDlgItem(IDC_CHECK11)->EnableWindow(FALSE);//TRUE
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_HIDE);
  
	OnSelchangeProtocols();
}

void CTTTView::OnButtonUpdate() 
{
	CString                str;
   	int        iWaveAll[80000];	
	UpdateData(TRUE);

  	m_startpoint = m_Spinstart.GetPos();
	m_wavepoints = m_SpinAverage.GetPos();

	if(m_wavepoints > 5000)
	{
		MessageBox("叠加间隔太大[400,5000]！","",MB_OK|MB_ICONWARNING);
		return;
	}

	PointsNum         =   m_wavepoints;          //每个波采的点数
	MaxCycleNum       =   (DataLen-m_startpoint)/PointsNum;     //采的最大波数
	
	switch(m_iCycleNum)
	{
	case 0:
		{
			CycleNum = 1; 
			g_Extend = DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 1:
		{
			CycleNum = 2; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 2:
		{
			CycleNum = 4;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 3:
		{
			CycleNum = 8;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/8;
		    break;
		}
	case 4: 
		{	
			CycleNum = 16; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/16;
		    break;
		}
	}

	BandPassAngle     =   int(m_iBandPassPoints*180.00/PointsNum + 0.5);

	for(int j = 0; j < CycleNum; j++)
	{

		//如果比原来的大的话
		if(m_nStartPoint + j > MaxCycleNum - 1)
		{ 

			if(DataLen > 0)
			{
				MessageBox("数据已到尽头！"," ",MB_OK|MB_ICONWARNING);
			}
			else
			{
			//	Beep(300,400);
			}

			break;
		}    
	
		//显示值
		for(int  i = 0; i < PointsNum; i ++)
		{
		
			iWaveAll[j*PointsNum+i] = DataBuf[(m_nStartPoint+j)*PointsNum + m_startpoint + i];
		
		}

	}
	
	//所有波叠加
	if(m_AllAdd)
	{
		//是1的波叠加在一起,是0的波叠加在一起
		AllWaveAdd();
	}

	m_wndAnalyzeWin.NewDataIn(iWaveAll,CycleNum*PointsNum);
	m_wndWaveWin.NewDataInAnalyze(iWaveAll,CycleNum*PointsNum);

}

void CTTTView::OnButtonShiftleft() 
{		
	UpdateData(TRUE);
	m_nStartPoint ++;

	PointsNum   = m_wavepoints;                         //每个波采的点数
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //采的最大波数
	
	if(m_nStartPoint + CycleNum > MaxCycleNum - 1)
	{
		m_nStartPoint = MaxCycleNum - CycleNum;
		Beep(300,400);
		//MessageBox("数据已到尽头！"," ",MB_OK|MB_ICONWARNING);
	}
	
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
	}

	UpdateData(FALSE);
	
	//更新数据表
	OnButtonUpdate();
}

void CTTTView::OnButtonAshiftleft() 
{	
	UpdateData(TRUE);
	
	m_nStartPoint += CycleNum;
	PointsNum      = m_wavepoints;                         //每个波采的点数
	MaxCycleNum    = (DataLen-m_startpoint)/PointsNum;     //采的最大波数

	//如果过头了
	if(m_nStartPoint + CycleNum > MaxCycleNum - 1)
	{

		m_nStartPoint = MaxCycleNum - CycleNum;
	
		//add
		if(m_nStartPoint%4 != 0)
		{
			m_nStartPoint = m_nStartPoint - m_nStartPoint%4;
		}
		
		if(m_nStartPoint < 0)
		{
			m_nStartPoint = 0;
		}

        Beep(300,400);
	
	}

	UpdateData(FALSE);
	
	//更新数据表
	OnButtonUpdate();
}

void CTTTView::OnButtonShiftright() 
{
	UpdateData(TRUE);
	m_nStartPoint--;

	PointsNum   = m_wavepoints;                         //每个波采的点数
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //采的最大波数
	
	//如果在前超界
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
		Beep(300,400);
	}
	
	UpdateData(FALSE);
	
	//更新数据表
	OnButtonUpdate();
}


void CTTTView::OnButtonAshiftright() 
{	
	UpdateData(TRUE);

	m_nStartPoint -= CycleNum;

	PointsNum   = m_wavepoints;                         //每个波采的点数
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //采的最大波数
	
	//如果在前超界
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
		Beep(300,400);
	  //MessageBox("数据已到最前头！"," ",MB_OK|MB_ICONWARNING);
	}

	UpdateData(FALSE);
    
	//更新数据表
	OnButtonUpdate();
}


void CTTTView::OnSelchangeComboChselect() 
{
	UpdateData(TRUE);
	BYTE   ORDER[15];
	//从ORDER[0]到ORDER[4]单片机用
	//命令字
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x5B; //触发命令
	ORDER[3]  = (m_generatrix - 1) * 64 + (m_iChSelect + 1) * 4 + 01;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	
	ORDER[4]  =  3;// 延时过0点数   
	
	//传给模块用
	ORDER[5]  = 0xf2; //命令字，要什么东西
	ORDER[6]  = 0;    //模块高地址
	ORDER[7]  = 0;    //模块中地址
	ORDER[8]  = 0;//AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4现为驻留时间,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
	ORDER[9]  = 0;//StatusL;//驻留时间
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和
	
	//暂时无用
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//向单片机发命令
	PcSendToSCM(ORDER);
}


void CTTTView::OnButtonLoad() 
{
	//打开文件对话框
	char szFilter[]="文本文件(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{

		CString            str;
		char            buf[8];
		short    length    =   0;
		long     m_sums    =   0;
		int        kkkk    =   0;
		int   m_postion    =   0;
		int   abstempvalue =   100;
	        
		//得到波形数据文件的单个数据长度
	    length = GetFileEveryDataLength(dlg.GetPathName());
	
		if(!file.Open(dlg.GetPathName( ),CFile::modeRead))
		{
			MessageBox("文件打开错误!","确定",MB_OK); 
			return;
		}

		CWnd* ptt = GetDlgItem(IDC_STATICFILE);
		ptt->SetWindowText("数据文件：" + dlg.GetPathName());
	
		if(length != 4 && length != 5 && length != 6)
		{
			file.Close();
			MessageBox("此数据文件不是TTT波形数据文件！","确定",MB_OK|MB_ICONWARNING);
			return;
		}
	    
		MaxPointsNum = (file.GetLength())/(length + 2);	//12位采集卡数据长度为6，16位采集卡数据长度为8
		DataLen      = MaxPointsNum;

		file.Seek(0,CFile::begin);

		for(UINT j = 0; j < MaxPointsNum; j++)
		{	
			file.Read(buf,length + 2);
			str   =  buf;
			str= str.Left(6);
			str.TrimLeft();
			str.TrimRight();
			
			DataBuf[j] = atoi(str);
			file.Seek(0,CFile::current);

		}
		file.Close();
        
    	UpdateData(TRUE);

		m_iCycleNum   =          2;
		m_bDiffI      =       TRUE;
		m_nStartPoint =          0;
		UpdateData(FALSE);
    	
		//显示更新
		OnButtonUpdate();
		
		OnSelchangeComboCyclenum();
	
     }

}

//区压差
void CTTTView::OnCheckDiff() 
{
	UpdateData();
}

//前八
void CTTTView::OnCheckAver4() 
{
	UpdateData();
	OnButtonUpdate();
}

//带通
void CTTTView::OnCheckBandPass() 
{
	UpdateData();
	OnButtonUpdate();
}

//微分
void CTTTView::OnCheckDvdt() 
{
	UpdateData();
}

//流差
void CTTTView::OnCheckDiffi() 
{
	UpdateData();
	OnButtonUpdate();
}


void CTTTView::OnChangeEditAngle() 
{
	UpdateData();
}

void CTTTView::OnChangeEditBandpassangle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData();
}




void CTTTView::OnChangeEditThreshold() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CTTTView::Delay()
{
	for(int i=0; i< 2000; i++);
	
}

void CTTTView::OnChangeEditSendcode() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}


//双向通讯
BOOL CTTTView::PcSendToSCM(BYTE ORDER[])
{

	SendMessage(WM_EVENT,1,0);

	CString        str;	
	CString       str1;
	U32      output[5];
	BYTE    Receive[5];
	ORDER[14]     =  0;

	if(ORDER[2] == 0x53)
	{
		//add
		//读表协议 31-39或71-79 意义[十位:3-和校验 7-BCH校验 个位:叠加次数]
		ORDER[2] = m_protocol/10*16 + m_protocol%10;
		
		if(m_protocol == 22)
		{
			//22协议当71协议用
			ORDER[2] = 0x71;
		}
		else if(m_protocol == 31)
		{
			ORDER[2] = 0x53;
		}
	
		//读表协议 31-39或71-79 意义[十位:3-和校验 7-BCH校验 个位:叠加次数]
		if(m_protocol >= 71 && m_protocol <= 73)
		{
			//检验字节,BCH校验
			BYTE            g[64];
			BYTE         data[45];
			//CString   str,strtemp;
			//g[63] =             0;
			BYTE         TempVale;
			
			for(int i = 5; i < 10; i ++)
			{
				
				//	str.Format("ORDER[%d]=0x%0x",i,ORDER[i]);
				//	WriteToLog(str);
				TempVale = ORDER[i];
		//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

				
				for(int j = 1; j <= 8; j ++)
				{
					//ssgg 7-5
					//	strtemp.Format("%d",TempVale%2);
					//data[6 + (i-5)*8+j-1] = TempVale%2;//add 2004.12.28
					//TempVale              = TempVale/2;
					data[6 + (i - 5) * 8 + j - 1] = (TempVale & 0x80) == 0 ? 0 : 1;//add 2004.12.28
					TempVale                      = TempVale << 1;
					//end ssgg 7-5
				}
				
			}
			
			//  40-45赋为0
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;
			
//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<46; i++) {
				CString mystr;
				if(data[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
//end ssgg debug

			//转成BCH码
			Encode_Bch_63_45_3(g,data);
			
			//数据又赋回
			for( i = 5; i < 13; i ++)
			{
				
				ORDER[i] = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					//ssgg 7-5
					//ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,j));
					ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow(2,j*(-1) + 7));
					//end ssgg 7-5
				}

		//ssgg debug
		ORDER[12] = 0x67;
		//		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug
				
			}

			ORDER[13] = 0;

		}
		else if(m_protocol == 22)
		{
			//22协议,检验字节,BCH校验
			BYTE             g[31];
			BYTE            gg[62];
			BYTE          data[21];
			//	CString    str,strtemp;
			//把21位数据取出
			long         TempVale = (ORDER[5]<<13) + (ORDER[6]<<5) + (ORDER[7]>>3);
			
			//21个数
			for(int j = 0; j < 21; j ++)
			{
				//21位数据
				data[20-j]   = TempVale%2;
				TempVale     = TempVale/2;     
			}
			
			//转成BCH码
			Encode_Bch_31_21_2(g,data);
			
			//22发双份协议,1则发10,0则发送01
			for(int i = 0; i < 31; i ++)
			{
				
				//如果是1则发0,是0则发1
				if(g[i] == 1)
				{
					gg[2*i  ] = 1;
					gg[2*i+1] = 0;
				}
				else
				{
					gg[2*i  ] = 0;
					gg[2*i+1] = 1;
				}
				
			}
			
			WriteToLog("\r\n");
			
			//数据又赋回 5-----13
			for( i = 5; i < 13; i ++)
			{
				ORDER[i]  = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if((i-5)*8+j < 62)
					{
						ORDER[i] = ORDER[i] + BYTE(gg[(i-5)*8+j]<<(7-j));
						str.Format("gg[%d]=%d",(i-5)*8+j,gg[(i-5)*8+j]);
					}
					else
					{	
						if((i-5)*8+j == 62)
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
							str.Format("gg[%d]=%d",(i-5)*8+j,0);
						}
						else
						{
							ORDER[i] = ORDER[i] + BYTE(1<<(7-j));
							str.Format("gg[%d]=%d",(i-5)*8+j,1);
						}
						
					}
					
					WriteToLog(str);
					
				}
				
				//22协议共有62位，最后一个只有差2位，左移2位
				str.Format("ORDER[%d]=%0x\r\n",i,ORDER[i]);
				WriteToLog(str);
			}
			
			ORDER[13] = 0;
			
		}
		else if(m_protocol == 61 || m_protocol == 62)
		{

			//61,62,协议,检验字节,BCH校验 45_27_3
			BYTE             g[45];
			BYTE          data[27];

			//把21位数据取出
			long         TempVale = (ORDER[5]<<19) + (ORDER[6]<<11) + (ORDER[7]<<3) +  (ORDER[8]>>5);
			
			//21位数据
			for(int j = 0; j < 27; j ++)
			{
				data[26-j]  = TempVale%2;
				TempVale    = TempVale/2;     
			}

			//转成BCH码45_27_3
			Encode_Bch_45_27_3(g,data);

			//数据又赋回
			for(int i = 5; i < 13; i ++)
			{
				
				ORDER[i]     =   0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if(((i-5)*8 + j ) > 44)
					{
						ORDER[i] = ORDER[i] + 0;
					}
					else
					{
						ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,7-j));
					}
					
				}	
				
				//22协议共有62位，最后一个只有差2位，左移2位
				str.Format("ORDER[%d]=%0x\r\n",i,ORDER[i]);
				WriteToLog(str);
				
			}

			ORDER[13] = 0;
			
		}
		
		//如果有星角变
		if(m_xinjiaobian)
		{
			ORDER[13]  = 0x06;
		}

	}


    str= "";

	//发前14位
	for(int j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//检验和
			ORDER[14] = ORDER[14] + ORDER[j];
			
		}
		
		if(ORDER[j] > 15)
		{
		  //str1.Format(" 0x%0x \r\n",ORDER[j]);
            str1.Format(" 0x%0x  ",ORDER[j]);
		}
		else
		{
          //str1.Format(" 0x0%0x \r\n",ORDER[j]);
			str1.Format(" 0x0%0x  ",ORDER[j]);
		}

        str = str + str1;
		
	}
	
	
	str1.Format(" 0x%0x ",ORDER[14]);
	str = str + str1;
    
	m_SendOrder = str;

	SendMessage(WM_EVENT,2,0);
	//ORDER[14] = ORDER[14]%256;
	
	//发送检验和
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//空一个数
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//边发边收
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//时钟
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//时钟
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
		}


		Receive[j] = BYTE(output[j] & 0xff);

		Sleep(1);
		
		
	}
	
	/**/
	str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//最高位两位去掉
	//AfxMessageBox(str1);
    
	CTime time = CTime::GetCurrentTime();
	CString s;
	s.Format("%4d-%2d-%2d %2d:%2d:%2d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //转换时间格式
	//WriteToLog("双向通讯命令：\r\n" + str + "\r\n" + str1 + s);
	
	
	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		WriteToLog("双向通讯时检验和不对!\r\n" + str + "\r\n" + str1);
		Beep(300,400);
		return FALSE;
	}

    switch(ORDER[2])
	{
	case 0x53://pc机发送
		{
			//Receive[1]－－－母线  Receive[2]－－－ 线路 Receive[3]－－－ 相别
			if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
			{
				WriteToLog("双向通讯时触发命令不对 0x53!\r\n" + str + "\r\n" + str1);
				Beep(300,400); 
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5c://设置A相触发角度
		{
			if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
			{
				WriteToLog("双向通讯时设置触发角度不对 0x5C!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5d://设置B相触发角度
		{
			if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
			{
				WriteToLog("双向通讯时设置触发角度不对 0x5d!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5e://设置C相触发角度
		{
			if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
			{
				WriteToLog("双向通讯时设置触发角度不对 0x5e!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x58://读取A相触发角度
		{
			if(Receive[0] != 0x68)
			{
				WriteToLog("双向通讯时设置触发角度不对 0x58!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0x59://读取B相触发角度
		{
			if(Receive[0] != 0x69)
			{
				WriteToLog("双向通讯时设置触发角度不对 0x59!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0x5a://读取C相触发角度
		{
			if(Receive[0] != 0x6a)
			{
				WriteToLog("双向通讯时设置触发角度不对 0x5a!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0x9c://读取直线号
		{
			if(Receive[0] != 0xac)
			{
				WriteToLog("双向通讯时读取直线编号不对 0x5a!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0xC0://设置A相延迟角度
		{
			if(Receive[0] != 0xD0)
			{
				WriteToLog("双向通讯时设置A相延迟角度不对 0xD0!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC1://设置B相延迟角度
		{
			if(Receive[0] != 0xD1)
			{
				WriteToLog("双向通讯时设置B相延迟角度不对 0xD1!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC2://设置C相延迟角度
		{
			if(Receive[0] != 0xD2)
			{
				WriteToLog("双向通讯时设置C相延迟角度不对 0xD2!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC3://读取A相延迟角度
		{
			if(Receive[0] != 0xD3)
			{
				WriteToLog("双向通讯时读取A相延迟角度不对 0xD3!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0xC4://读取B相延迟角度
		{
			if(Receive[0] != 0xD4)
			{
				WriteToLog("双向通讯时读取B相延迟角度不对 0xD4!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xC5://读取C相延迟角度
		{
			if(Receive[0] != 0xD5)
			{
				WriteToLog("双向通讯时读取C相延迟角度不对 0xD5!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xC6://读无线模块的A相电流电压
		{
			if(Receive[0] != 0xD6)
			{
			//	WriteToLog("双向通讯时读无线模块的A相电流电压不对 0xD6!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0xC7://读无线模块的B相电流电压
		{
			if(Receive[0] != 0xD7)
			{
			//	WriteToLog("双向通讯时读无线模块的B相电流电压不对 0xD7!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}

			break;
		}
	case 0xC8://读无线模块的C相电流电压
		{
			if(Receive[0] != 0xD8)
			{
			//	WriteToLog("双向通讯时读无线模块的C相电流电压不对 0xD7!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			
			break;
		}

    /*
	case 0xC6://设置A相发射电流
		{
			if(Receive[0] != 0xD6)
			{
				WriteToLog("双向通讯时设置发射电流不对 0xD6!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC7://设置B相发射电流
		{
			if(Receive[0] != 0xD7)
			{
				WriteToLog("双向通讯时设置发射电流不对 0xD7!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC8://设置C相发射电流
		{
			if(Receive[0] != 0xD8)
			{
				WriteToLog("双向通讯时设置发射电流不对 0xD8!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	*/

	case 0xC9://读取A相发射电流
		{
			if(Receive[0] != 0xD9)
			{
				WriteToLog("双向通讯时读取A相发射电流不对 0xD9!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}

	case 0xCA://读取B相发射电流
		{
			if(Receive[0] != 0xDA)
			{
				WriteToLog("双向通讯时读取B相发射电流不对 0xDA!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xCB://读取C相发射电流
		{
			if(Receive[0] != 0xDB)
			{
				WriteToLog("双向通讯时读取C相发射电流不对 0xDB!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}


	}
	return TRUE;
}

void CTTTView::WriteP9111_CHANNEL_DOPort(int value)
{
	I16     err;
	err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100 + value);//时钟
	if(err != 0)
	{
		//Beep(300,400);
		//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
		//return;
	}

	Sleep(1);

	err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000 + value);
	if(err != 0)
	{
		//Beep(300,400);
		//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
	}

	Sleep(1);
}


void CTTTView::WriteToTxtFile(CString FileName,unsigned short DataBuf[],int length)
{
	//写入文本文件
	FILE  *text;
	CString Str;
	if((text = fopen(FileName,"a")) != NULL)
	{
		for(int i = 0; i < length; i++)
		{
			Str.Format("%5d",DataBuf[i]);
			//Str.Format("%4d",DataBuf[i]);
			fputs(Str + "\r\n",text);
		}
		fclose(text);
	}
}



UINT  ReadChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	
	if(!pview->m_xinjiaobian)
	{
		//角星
		pview->ReadMeter();
	}
	else
	{
		//同相采集同相收
		if(pview->m_equal)
		{
			pview->ReadMeter();
		}
		else
		{
			//星角
			pview->ReadSixChannelMeter();
		}
	}

	return 0;
}

void CTTTView::OnRealStart() 
{

	UpdateData(TRUE);

//	m_nStartPoint = 0;
//  UpdateData(FALSE);

    if(m_derrors > 31 )
	{
        MessageBox("对位个数应小于31！","警告",MB_OK|MB_ICONWARNING);
		return;
	}


	//向采集卡发送
	if(m_iModeSel == 1)
	{
		CWnd* pt  = GetDlgItem(IDC_RECEIVE);
		pt->SetWindowText(" ");
		pt  = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText(" ");	
		pt  = GetDlgItem(IDC_STATICFILE);
		pt->SetWindowText(" ");
		m_ReceiveStr     =  "";
		
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_BUTTON_ANGLE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);

		for(int i = 0; i < 270000; i++)//135000*2 131584
		{
			DataBuf[i] = 0;
		}
		
		AfxBeginThread(ReadChannel,this); 
	//	eventWriteD.ResetEvent(); 
	//	AfxBeginThread(WriteD,this);
		m_ShowWave  = TRUE;	
	}
	else
	{	
		//向串口发送数据
		int         m_order    = 0;
		CString                str;
		UpdateData(TRUE);
		
		if(m_angle  < 5 || m_angle  > 50)
		{
			MessageBox("角度超界[5,50]！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
		
		GetDlgItem(IDC_RECEIVE)->SetWindowText("");
		GetDlgItem(IDC_SENDORDER)->SetWindowText("");
		
		CWnd* pt    =    GetDlgItem(IDC_ORDER);
		pt->GetWindowText(str);	
	
		str.TrimLeft();
		str.TrimRight();
		
		if(str.IsEmpty())
		{
			pt    =    GetDlgItem(IDC_REAL_START);
			pt->EnableWindow(TRUE);
			MessageBox("命令字不能为空！","",MB_OK|MB_ICONWARNING);
			return;
		}
		
		if(str.GetLength() > 1)
		{
			m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
		}
		else
		{
			m_order = GetHexValue(str.GetAt(0));
		}
		
		SendByteArray.RemoveAll();
		BYTE             TempByte;

        //起始字节
        SendByteArray.Add(0x68);    
		//广播
        SendByteArray.Add(0xff);            
        
		//合成字节,命令字(2)+相位(2)+下行协议(4)     
		switch(m_protocol)
		{
		case 61:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 5;
				break;
			}
		case 62:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 6;
				break;
			}
	 	case 71:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 1;
				break;
			}
		case 72:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 2;
				break;
			}
		case 73:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 3;
				break;
			}
		case 74:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 4;
				break;
			}
		case 21:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 9;
				break;
			}
		case 22:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 10;
				break;
			}
		case 23:
			{
                TempByte = 2*64 + (m_phase + 1)*16 + 11;
				break;
			}
		case 24:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 12;
				break;
			}
	
		}
        SendByteArray.Add(TempByte);            
		
		//上行协议,暂时没有用
		switch(m_protocol)
		{
		case 61:
			{
				TempByte =  5;
				break;
			}
		case 62:
			{
				TempByte =  6;
				break;
			}
	 	case 71:
			{
				TempByte =  1;
				break;
			}
		case 72:
			{
				TempByte =  2;
				break;
			}
		case 73:
			{
				TempByte =  3;
				break;
			}
		case 74:
			{
				TempByte =  4;
				break;
			}
		case 21:
			{
				TempByte =  9;
				break;
			}
		case 22:
			{
				TempByte = 10;
				break;
			}
		case 23:
			{
                TempByte =  11;
				break;
			}
		case 24:
			{
				TempByte = 12;
				break;
			}
	
		}

        SendByteArray.Add(TempByte);
		//发送角度
		SendByteArray.Add(m_angle);

		//数据5-13
		if(m_protocol == 61 || m_protocol== 62)
		{
			ComeIntoBch60(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/,m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);
		}
		else if(m_protocol > 70)
		{
			ComeIntoBch70(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/,m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);
		}
		else
		{
			ComeIntoBch20(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/,m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);
		}
    
		TempByte = 0;
		
		//14 检验和
		for(int i = 0; i < 14; i ++)
		{
			TempByte = TempByte + SendByteArray[i];
		}

		SendByteArray.Add(TempByte);      

		//15结束符
        SendByteArray.Add(0x16);

		//向串口发送
		SendByteArrayToCom();
	
	}
	
}

void CTTTView::OnRealstop() 
{

	bClearOp    = TRUE;//让线程退出
	m_Stopping  = TRUE;
	Sleep(200);
	CWnd* pts   = GetDlgItem(IDC_REAL_START);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SEND);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SETTIMER);
	pts->EnableWindow(TRUE);
    pts = GetDlgItem(IDC_DECODE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_RADIO_REALTIME);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_COMSET);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SENDALLONE);
	pts->EnableWindow(TRUE);	
	pts = GetDlgItem(IDC_BUTTON_ANGLE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_REALSTOP);
	pts->EnableWindow(FALSE);
	KillTimer(1);
	KillTimer(2);
}

BOOL CTTTView::SendOrderToSCM(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/, BYTE ZeroDots/* 延时过0点数*/,BYTE Item/* 要什么东西,命令字*/,int status/*可放时间或其它东西*/)
{
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 意义为模块号为16表号为01
	AddrH = int((int(ModuleNum/100)%65536)/256);//高位    对应的为数据1
    AddrM = (int(ModuleNum/100)%65536)%256;     //中间位  对应的为数据2
	AddrL = ModuleNum%100 - 1;                  //低4位   分给表号
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}
    
	
	StatusH = status/256;        //高位    对应的为数据3的后2位
	StatusL = status%256;        //低位    数据4
	
	switch(Phase)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
            
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
		    
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// 延时过0点基数       
	//相别 
	
	//ORDER[5]到ORDER[10]由单片机用片机传给模块用

	if(m_protocol == 22)
	{
		
		//如果协议为22	
		if(!m_check4bit)
		{
			
			//如果是 485表: 10(监督位) + 14(地址)+ 7(命令)
			//如果是脉冲表: 10(监督位) + 14(地址)+ 4(字地址) + 3(命令)
			
			//地址前8位
			ORDER[5]  = (ModuleNum/100)>>6; //地址高位
			
			if(ModuleNum%100 == 15)
			{
				//485表  6位地址 + 2位命令字的高位(共7位命令字)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + (Item>>5);
				//5位命令字 + 3个0
				ORDER[7]  = (Item%32)*8;
			}
			else
			{
				//脉冲表 6位地址 + 子表地址2位高位(共4位子表地址)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
				//子表地址2位低位(共4位子表地址) + 3位命令字  + 3个0
				ORDER[7]  = ((ModuleNum%100-1)%4)*64  + ((Item%8)*8);
			}
			
		}
		else
		{
			//如果有3位检验和
			//如果是 485表: 10(监督位) + 3(检验和) + 11(地址)  +  7(命令)   
			//如果是脉冲表: 10(监督位) + 3(检验和) + 11(地址)  +  4(子地址) + 3(命令) 
			
			
			long      m_Modules       =      0;
			BYTE       m_data[18],m_checkvalue;	
			
			
			if(ModuleNum%100 >= 12)
			{
				//485  11(地址)  +  7(命令)
				m_Modules = ((ModuleNum/100)<<7) + Item;
			}
			else
			{
				//     11(地址)  +  4(子地址) + 3(命令)
				m_Modules = ((ModuleNum/100)<<7) + ((ModuleNum%100-1)>>3) + Item;
			}
			
			//3位校验和
			m_checkvalue              =     0 ;
			
			//18位数据
			for(int j = 0; j < 18; j ++)
			{
				m_data[17-j]       =       m_Modules%2;
				m_Modules          =       m_Modules/2;     
			}
			
			for( j = 0; j < 6; j ++)
			{
				m_checkvalue = m_checkvalue  + (m_data[3*j]*4+m_data[3*j+1]*2+m_data[3*j+2]*1);
			}
			
			m_checkvalue     = m_checkvalue%8;
			
			
			//3(检验和) + 地址前5位
			ORDER[5]  =  (m_checkvalue<<5) +  ((ModuleNum/100)>>6);
			
			if(ModuleNum%100 >= 12)
			{
				//485表         6位地址 + 2位命令字的高位(共7位命令字) 
				ORDER[6]        = (((ModuleNum/100)%64)<<2) + (Item>>5);
				//5位命令字(共7位命令字)  + 3个0
				ORDER[7]        = ((Item%32)<<3) + 0;
			}
			else
			{
				//脉冲表        6位地址 + 子表地址2位高位(共4位子表地址) 
				ORDER[6]        = (((ModuleNum/100)%64)<<2) + ((ModuleNum%100-1)>>2);
				//              子表地址后2位(共4位子表地址) +  3位命令字(共3位命令字) + 3个0
				ORDER[7]        = (((ModuleNum%100-1)%4)<<6) + (Item<<3) + 0;
			}
			
			
		}
		
		ORDER[8]  =     0;
		ORDER[9]  =     0;

	}
	else if(m_protocol == 61 || m_protocol ==62)
	{

		//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用       + 6位标志码
		//如果是 485表: 18(监督位) + 14(地址) + "1"(485标志)           + 5(命令) + 7位特征码(0001000)
		//如果是脉冲表: 18(监督位) + 14(地址) + "0"(脉冲表字地址)      + 2(命令) + 7位特征码(0001000)
			
		//地址前8位
		ORDER[5]  = (ModuleNum/100)>>6; //地址高位
		
		if(ModuleNum%100 > 12)//>=
		{
			//485表  6位地址  +  1位(485标志) + 1位命令字(共5位命令字)
			ORDER[6]  = ((ModuleNum/100)%64)* 4 + 1*2 + (Item>>4);
			//4位命令字(共5位命令字) + 4位特征码(0001)
			ORDER[7]  = (Item%16)*16 + 1;
			//3位特征码(000) + 5个0
			ORDER[8]  =  0;
			
		}
		else
		{	
			
			//停送电
			if(Item == 0x00 || Item==0x01)
			{
				//使断电停电不容易出现，发第7块表的停送电 0111
				//脉冲表 6位地址 + 子表地址2位高位(共4位子表地址)
				ORDER[6]  = ((ModuleNum/100)%64)* 4  +  1;
				//子表地址2位低位(共4位子表地址)+2位命令字+4位特征码(0001)
				ORDER[7]  = 3*64+ (Item%4)*16        +  1;
				
			}
			else
			{
				//脉冲表 6位地址 + 子表地址2位高位(共4位子表地址)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
				//子表地址2位低位(共4位子表地址)+2位命令字+4位特征码(0001)
				ORDER[7]  = ((ModuleNum%100-1)%4)*64+ (Item%4)*16     +    1;
				
			}
			
			//3位特征码(000) + 5个0
			ORDER[8]  =   0;//00000000
		}	
		
		ORDER[9]  =     0;

		
	}
	else
	{
			
			//如果协议为31、32、71、72等
			ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //命令字，要什么东西＋模块地址最高位
			ORDER[6]  = AddrH;//模块高地址
			ORDER[7]  = AddrM;//模块中地址
			
			
			
			//临时用
			/*	
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
			ORDER[9]  = StatusL;//驻留时间
			if(status == 0)
			{
			ORDER[9] = 0x67;
			}
			*/
			
			//临时用,假如是广播冻结
			if(Item == 0xF2)
			{
				ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
			}
			else
			{
				
				if(m_Is0Station)
				{
					//如果是0站
					ORDER[8]  = AddrL*16 + PhaseBit* 4 + 0;
				}
				else
				{
					//如果是0站
					ORDER[8]  = AddrL*16 + PhaseBit* 4 + 1;
				}
				
			}
			
			//新的选择
			switch(Item)
			{
			case 0xF2://假如是广播冻结
				{
					ORDER[9]  = StatusL;//驻留时间
					break;
				}
			case 0x02://读有功电度
				{	
					break;
				}
			case 0x3a://读电压
				{
					break;
				}
			case 0x3e://表底清0
				{
					break;
				}
			case 0x40://电流测试清0
				{
					break;
				}
			case 0xF7://送电操作
				{
					
					//送电操作  D3 = 0000****
					//	ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
					break;
					
				}
			case 0xf6://断电操作
				{	
					
					//断开状态时 D3 = 1111****
					//	ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
					break;
					
				}
			case 0x82://读冻结有功电度
				{
					
					//假如为其它命令
					break;
					
				}
				
			default:
				{
					//假如为其它命令
					ORDER[9]  =  0x67;                                 //此字节后三位为延时过0点数
				}
				
			}
			
			
			
			//根据零点数,发ORDER[9]的值
			switch(ZeroDots)
			{
			case 3:
				{
					
					ORDER[9]  = 0x60 + 0x07;    //此字节后三位为延时过0点数
					break;
					
				}
			case 5:
				{
					
					ORDER[9]  = 0x60 + 0x07;    //此字节后三位为延时过0点数
					break;
					
				}
			case 20:
				{
					
					ORDER[9]  = 0x60 +  0x06;    //此字节后三位为延时过0点数
					break;
					
				}	
			case 30:
				{
					
					ORDER[9]  = 0x60 +  0x05;     //此字节后三位为延时过0点数
					break;
					
				}
			case 60:
				{
					
					ORDER[9]  = 0x60 +  0x04;     //此字节后三位为延时过0点数
					break;
					
				}
			case 100:
				{
					
					ORDER[9]  = 0x60 +  0x03;      //此字节后三位为延时过0点数
					break;
					
				}
			case 160:
				{
					
					ORDER[9]  = 0x60 +  0x02;      //此字节后三位为延时过0点数
					break;
					
				}	
			case 200:
				{
					
					ORDER[9]  = 0x60 +  0x01;      //此字节后三位为延时过0点数
					break;
					
				}
			case 240:
				{
					
					ORDER[9]  =  0x60 + 0x00;     //此字节后三位为延时过0点数
					break;
					
				}
			}
			
	}

	
	//检验字节
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和

	//status
	//暂时无用
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//向单片机发命令
	return PcSendToSCM(ORDER);
	Sleep(5);
}

BOOL CTTTView::DecodeBCH63394(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 6, n = 63 , length = 63, t = 4, k = 39, d = 9;
    int   alpha_to[64], index_of[64];
	CString str;
	    alpha_to[0]  = 1,index_of[0]   = -1,
		alpha_to[1]  = 2,index_of[1]   = 0,
		alpha_to[2]  = 4,index_of[2]   = 1,
		alpha_to[3]  = 8,index_of[3]   = 6,
		alpha_to[4]  = 16,index_of[4]  = 2,
		alpha_to[5]  = 32,index_of[5]  = 12,
		alpha_to[6]  = 3,index_of[6]   = 7,
		alpha_to[7]  = 6,index_of[7]   = 26,
		alpha_to[8]  = 12,index_of[8]  = 3,
		alpha_to[9]  = 24,index_of[9]  = 32,
		alpha_to[10] = 48,index_of[10] = 13,
		alpha_to[11] = 35,index_of[11] = 35,
		alpha_to[12] = 5,index_of[12]  = 8,
		alpha_to[13] = 10,index_of[13] = 48,
		alpha_to[14] = 20,index_of[14] = 27,
		alpha_to[15] = 40,index_of[15] = 18,
		alpha_to[16] = 19,index_of[16] = 4,
		alpha_to[17] = 38,index_of[17] = 24,
		alpha_to[18] = 15,index_of[18] = 33,
		alpha_to[19] = 30,index_of[19] = 16,
		alpha_to[20] = 60,index_of[20] = 14,
		alpha_to[21] = 59,index_of[21] = 52,
		alpha_to[22] = 53,index_of[22] = 36,
		alpha_to[23] = 41,index_of[23] = 54,
		alpha_to[24] = 17,index_of[24] = 9,
		alpha_to[25] = 34,index_of[25] = 45,
		alpha_to[26] = 7,index_of[26]  = 49,
		alpha_to[27] = 14,index_of[27] = 38,
		alpha_to[28] = 28,index_of[28] = 28,
		alpha_to[29] = 56,index_of[29] = 41,
		alpha_to[30] = 51,index_of[30] = 19,
		alpha_to[31] = 37,index_of[31] = 56,
		alpha_to[32] = 9,index_of[32]  = 5,
		alpha_to[33] = 18,index_of[33] = 62,
		alpha_to[34] = 36,index_of[34] = 25,
		alpha_to[35] = 11,index_of[35] = 11,
		alpha_to[36] = 22,index_of[36] = 34,
		alpha_to[37] = 44,index_of[37] = 31,
		alpha_to[38] = 27,index_of[38] = 17,
		alpha_to[39] = 54,index_of[39] = 47,
		alpha_to[40] = 47,index_of[40] = 15,
		alpha_to[41] = 29,index_of[41] = 23,
		alpha_to[42] = 58,index_of[42] = 53,
		alpha_to[43] = 55,index_of[43] = 51,
		alpha_to[44] = 45,index_of[44] = 37,
		alpha_to[45] = 25,index_of[45] = 44,
		alpha_to[46] = 50,index_of[46] = 55,
		alpha_to[47] = 39,index_of[47] = 40,
		alpha_to[48] = 13,index_of[48] = 10,
		alpha_to[49] = 26,index_of[49] = 61,
		alpha_to[50] = 52,index_of[50] = 46,
		alpha_to[51] = 43,index_of[51] = 30,
		alpha_to[52] = 21,index_of[52] = 50,
		alpha_to[53] = 42,index_of[53] = 22,
		alpha_to[54] = 23,index_of[54] = 39,
		alpha_to[55] = 46,index_of[55] = 43,
		alpha_to[56] = 31,index_of[56] = 29,
		alpha_to[57] = 62,index_of[57] = 60,
		alpha_to[58] = 63,index_of[58] = 42,
		alpha_to[59] = 61,index_of[59] = 21,
		alpha_to[60] = 57,index_of[60] = 20,
		alpha_to[61] = 49,index_of[61] = 59,
		alpha_to[62] = 33,index_of[62] = 57,
		alpha_to[63] = 0,index_of[63]  = 58;
	
	t2 = 2 * t;
	
	////计算综合病症 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//修改 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // 设置错误标志
			// 转换综合病症从多项式到索引形式
			s[i] = index_of[s[i]];
			
	}
	
	//有错误的话
	if (syn_error) 
	{
		
		//计算错误的位置多项式用欧几里运算法则
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//计算b(x)数组值
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// 规格化错误位置多项式
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// 用Chien search找到错误的位置 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			}
			
			
			if (count == l[u])
			{
				//	// no. roots = degree of elp hence <= t errors 
				str.Format("纠正错误个数： count = %d",count);
				WriteToLog(str);
				
				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					if( loc[i] < 24)
					{
						str.Format("纠正错误位置：%d",23 - loc[i]);
					}
					else
					{
						str.Format("纠正错误位置：%d",86 - loc[i]);
					}

				  //str.Format("纠正错误位置：%d",loc[i]);
					WriteToLog(str);

				}
				return TRUE;
				
			}
			else
			{
				//
				str.Format("错误个数为： count = %d，l[%d] = %d",count,u,l[u]);
				WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> length为数据值 
		}
		else
		{
			//
			str.Format("错误个数为：%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//
		str = "t = 0,没有错误";
		WriteToLog(str);//
		return TRUE;
	}

}

void CTTTView::WriteToLog(CString Str)
{
	
	if(m_IfWriteToLog)
	{
		//写入文本文件
		FILE *text;
		if((text = fopen("c:\\data.txt","a")) != NULL)
		{
			fputs(Str + "\r\n",text);
			fclose(text);
		}

	}
}

void CTTTView::ReadMeter()
{ 
	WriteToLog("[星星读表]");

	//循环读数   
	int     HalfCount  =     0;
	CString                str;
    BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
    U32                  count;
	DataLen            =     0; 
    memset(ReadBuff,0,1024);
	int         DataValues = 0;
	int         m_order    = 0;
	int i, j;
    CWnd* pt    =    GetDlgItem(IDC_ORDER);
    pt->GetWindowText(str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		pt    =    GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(TRUE);
		MessageBox("命令字不能为空！","",MB_OK|MB_ICONWARNING);
		return;
	}
    
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(FALSE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(FALSE);

	pt = GetDlgItem(IDC_REAL_START);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_DECODE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO_REALTIME);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_COMSET);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SENDALLONE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BUTTON_ANGLE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);

	//发命令
//	SendOrderToSCM(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/,m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);

		//向单片机发指令
	for(i=0; i<3; i++) {
		if(!SendOrderToSCM(1001+i*100/*模块号*/,
							1/*手拉手电站码*/,
							1/*母线*/,
							1/*线号*/, 
							i/*相选择0A 1B 2C*/,
							3, 
							0x02/* 要什么东西,命令字*/,
							0)) /*m_SendAngle*/
		{
			Beep(300,400);
			Beep(300,400);
		}
		Sleep(1000);
	}


	//连续读通道数据,m_CollectChannels采集通道
	//err = AI_ContReadChannel(card,m_CollectChannels, AD_B_10_V, ReadBuff, 1024, 
	//	(F64)100000, ASYNCH_OP);//1024
	//if (err!=0) 
	//{  
		//Beep(300,400); 
    //}    
	err = AI_ContScanChannels (card, 2, AD_B_10_V, ReadBuff,1024, CLKSRC_EXT_SampRate, ASYNCH_OP);
	if (err != 0) 
		return;

	//long m_rrr  = GetTickCount(); 

	int     m_Waves = 0;
	CString          ss;

    bClearOp        = FALSE;
	long begintimes = GetTickCount();
    BOOL     m_recording  = TRUE;

	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//获得时钟频率
	dff = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);//获得初始值
		
   	do
	{
	
	    long begintime1 = GetTickCount();
        qt1 = litmp.QuadPart;

		do
		{
			//半满
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
		
			if(m_protocol == 22)
			{
				
				if(GetTickCount() - begintimes > 8000)
				{
				//	ss.Format("采集%d秒,数据长度%d",(GetTickCount() - begintimes)/1000,DataLen);
				//	WriteToLog(ss);
					bClearOp = TRUE;
				}

			}
			else
			{
				
				if(GetTickCount() - begintimes > ((m_protocol%10)*12000))
				{
				//	ss.Format("采集%d秒,数据长度%d",(GetTickCount() - begintimes)/1000,DataLen);
				//	WriteToLog(ss);
					bClearOp = TRUE;
				}

			}
				
		} while (!bHalfReady && !bClearOp);
		
		
		if (!bClearOp) 
		{
			
			//传送半满数据
			AI_AsyncDblBufferTransfer(card, ReadBuff);
			bHalfReady = FALSE;

			if(m_recording)
			{
				ss.Format("发完到收时间差:%d",GetTickCount()- begintimes);
				WriteToLog(ss);	
				
				m_recording = FALSE;
			}
			
			for(int i = 0; i < 512; i++)
			{	
				//最大值         m_maxDecimalVal      1、PCI-9111DR 4096     2、PCI-9111HR 65536 
		        //采的数要除的值  m_DivideVal         1、PCI-9111DR   16     2、PCI-9111HR     1 
				DataValues = ReadBuff[i]/m_DivideVal;
				
				//读到数组,大于m_maxDecimalVal/2为负数
				if(DataValues > m_maxDecimalVal/2)
				{
					DataValues =  -(m_maxDecimalVal - DataValues);
				}
				
				TempDataBuf[DataLen++] = DataValues;
                

			//	U32 dig_inn;
			//	long m_time1 =  GetTickCount();
			//  DI_ReadPort(card, P9111_CHANNEL_EDI,&dig_inn); 
			//	long m_time2 =  GetTickCount();

			//	CString stddr;
			//	stddr.Format("时间长度：%d,值;%d",m_time2-m_time1,dig_inn);
	        //  WriteToLog(stddr);
			
			}

	//		eventWriteD.SetEvent();

			//m_Waves ++;
			m_Waves += 2;
			QueryPerformanceCounter(&litmp);//获得终止值
			qt2 = litmp.QuadPart;
			dfm = (double)(qt2-qt1);
			dft = dfm/dff;//获得对应的时间值

		    ss.Format("[第%3d个脉冲群，与%3d个的时间间隔%.2f毫秒]",m_Waves,m_Waves-1,dft*1000);
		    WriteToLog(ss);
			
		    long m_waittimes = 0;

			if(!m_quancai)
			{
			
				
				if(m_protocol == 22)
				{
					m_waittimes = 8000;
				}
				else
				{
					m_waittimes = m_protocol%10*12000;//8000
				}

				switch(m_protocol)
				{
				case 22:
					{
						
					}
				case 31:
					{
						
					}
				case 32:
					{
						
					}
				case 71:
					{
						
					}
				case 72:
					{
						
						
					}
				case 73:
					{
						//64*4
						if(DataLen >= 196608 /*131584*/)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 61:
					{
						// 1024 + 45*4*512  = 93184
						if(DataLen >= 93184)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 62:
					{
						//1024 + 4*45*2*512 = 185344
						if(DataLen >= 185344)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				}

				//正常采数
				if((GetTickCount() - begintimes > m_waittimes))// 115200多采2004个点  229
				{  
					bClearOp = TRUE;
					break;
				}
				
			}
			else
			{	
				if(m_protocol == 22)
				{
					m_waittimes = 8000;
				}
				else
				{
					m_waittimes = m_protocol%10*8000;
				}
                
				//全波采
				if(DataLen >= 263168 || (GetTickCount() - begintimes > m_waittimes))// 115200多采2004个点  229
				{  
					bClearOp = TRUE;
					break;
				}
				
			}
			
		}
		
	}while (!bClearOp && !bStopped);
	
    AI_AsyncClear(card, &count);
	
	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(TRUE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(TRUE);
	
	//ss.Format("\r\n\r\n===============时间差为：%d===============",m_times2 - m_times1);
	//WriteToLog(ss);
	long m_checklengths = 0;

	switch(m_protocol)
	{
	case 22:
		{
			
		}
	case 31:
		{
			
		}
	case 32:
		{
			
		}
	case 71:
		{
			
		}
	case 72:
		{
			
			
		}
	case 73:
		{
			//64*4
			m_checklengths = 131584;
			break;
		}
	case 61:
		{
			// 1024 + 45*4*512  = 93184
			m_checklengths = 93184;
			break;
		}
	case 62:
		{
			//1024 + 4*45*2*512 = 185344
			m_checklengths = 185344;
			break;
		}
	}

    ss.Format("给点：%d",DataLen);
	WriteToLog(ss);
	DataLen = 131584;

	for(j=0; j<256*64*4; j++) {
		if(TempDataBuf[j] >= 2048)
			TempDataBuf[j] = TempDataBuf[j] - 4096;

		DataBuf[j*2] = TempDataBuf[j*3 + i + 207];
		DataBuf[j*2 + 1] = TempDataBuf[j*3 + i + 207];
	}


	if(DataLen >= m_checklengths)
	{
		double GetValue = Decode();

		if(GetValue >= 0)//解码
		{
			m_SuccessTimes  = m_SuccessTimes + 1;
			m_data.Format("%f",GetValue);//.2
		}
		else
		{
			m_data = "NULL";
		}

	//	OnButtonUpdate();

	}
	else
	{
		Beep(300,400);
		m_ReceiveStr = "<<采集数据错误>>";
		m_data       = "NULL";
		m_CollectErrors    ++;
	}
	
	m_TotalTimes  = m_TotalTimes  + 1;
	

	CEdit * ptt = (CEdit *)GetDlgItem(IDC_DATAVALUE);
	ptt->SetWindowText(m_data);
	ptt        =  (CEdit *)GetDlgItem(IDC_RECEIVE);
	ptt->SetWindowText(m_ReceiveStr);
	

	CWnd* pts   = GetDlgItem(IDC_REAL_START);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SEND);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SETTIMER);
	pts->EnableWindow(TRUE);
    pts = GetDlgItem(IDC_DECODE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_RADIO_REALTIME);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_COMSET);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SENDALLONE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_BUTTON_ANGLE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_REALSTOP);
	pts->EnableWindow(FALSE);
}

void CTTTView::OnButtonSave() 
{

    //保存文件对话框
	char szFilter[]="文本文件(*.TXT)|*.TXT||";

   	CFileDialog dlg(FALSE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{
		
		CString  str;

		if(!file.Open(dlg.GetFileName(),CFile::modeWrite | CFile::modeCreate))
		{	
			MessageBox("写文件错误!","确定",MB_OK);
			return;
		}
		
		file.Seek(0,CFile::begin);

		str.Format("%6d",DataBuf[0]);
		str = str + "\r\n";
		file.Write(str,8);
			
		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
	      
			//16位采集卡
			str.Format("%6d",DataBuf[i]);

			str = str + "\r\n";
			file.Write(str,8);
		}

		file.Close();

		MessageBox("数据文件已成功保存!","确定",MB_OK);
	}

}


//long ModuleNo   模块号
//int  times      读表次数
//int  mode       写表模式 //0 error,1 right
void CTTTView::WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode)
{
	
	CFile       file;
	CString filename;
	CString      str;

	filename.Format("%d%d",ModuleNo,times);
	
	if(mode == 0)
	{
		filename = filename + "ERROR.TXT";
	}
	else
	{
        filename = filename + "RIGHT.TXT";
	}
	
	if(file.Open(filename,CFile::modeWrite|CFile::modeCreate))
	{	
		
		file.Seek(0,CFile::begin);
		//str.Format("%4d",DataBuf[0]);
		str.Format("%5d",DataBuf[0]);
		str = str + "\r\n";
		//file.Write(str,6);
		file.Write(str,7);

		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
			//str.Format("%4d",DataBuf[i]);
			str.Format("%5d",DataBuf[i]);
			str = str + "\r\n";
		  //file.Write(str,6);
			file.Write(str,7);
		}
		file.Close();
	}
	
}


//设置角度
//short generatrixno 母线编号
//short phase        相别 0 A相 1 B相 2 C相
//int   angles       角度
//BYTE  kinds  种类 0--信号强度 1－延迟角度
void CTTTView::SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds)
{
	
    	CString    str;
		
		BYTE ORDER[15];
		
		//角度设置 
		ORDER[0]  = 0x51;
		ORDER[1]  = 0x52;//前导码
		
	
		switch(kinds)
		{
		case 0:
			{
				ORDER[2]  = 0x5c + phase;//角度设置
				break;
			}
		case 1:
			{		
				ORDER[2]  = 0xC0 + phase;//延迟角度
				break;
			}
		case 2:
			{
				ORDER[2]  = 0XC6 + phase;//发射电流
				break;
			}
		}

		ORDER[3]  = generatrixno-1;
		ORDER[4]  = (BYTE)angles;
		ORDER[5]  = 0;
		ORDER[6]  = 0;
		ORDER[7]  = 0;
		ORDER[8]  = 0;
		ORDER[9]  = 0;
		ORDER[10] = 0;
		ORDER[11] = 0;
		ORDER[12] = 0;
		ORDER[13] = 0;
		
		//向单片机发命令
		if(PcSendToSCM(ORDER))
		{
			
			switch(phase)
			{
			case 0:
				{  
					switch(kinds)
					{
					case 0:
						{
							str = "A相信号强度设置完毕!";
							break;
						}
					case 1:
						{
							str = "A相延迟角度设置完毕!";
							break;
						}
					case 2:
						{
							str = "A相发射电流设置完毕!";
							break;
						}
					}

					break;
					
				}
			case 1:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "B相信号强度设置完毕!";
							break;
						}
					case 1:
						{
							str = "B相延迟角度设置完毕!";
							break;
						}
					case 2:
						{
							str = "B相发射电流设置完毕!";
							break;
						}
					}

					break;
					
				}
			case 2:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "C相信号强度设置完毕!";
							break;
						}
					case 1:
						{
							str = "C相延迟角度设置完毕!";
							break;
						}
					case 2:
						{
							str = "C相发射电流设置完毕!";
							break;
						}
					}

					break;
					
				}
			
			}
		
		}
		else
		{	
			
			switch(phase)
			{
			case 0:
				{  
					
					switch(kinds)
					{
					case 0:
						{
							str = "A相信号强度设置错误!";
							break;
						}
					case 1:
						{
							str = "A相延迟角度设置错误!";
							break;
						}
					case 2:
						{
							str = "A相发射电流设置错误!";
							break;
						}
					}
					
					break;
					
				}
			case 1:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "B相信号强度设置错误!";
							break;
						}
					case 1:
						{
							str = "B相延迟角度设置错误!";
							break;
						}
					case 2:
						{
							str = "B相发射电流设置错误!";
							break;
						}
					}

					break;
					
				}
			case 2:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "C相信号强度设置错误!";
							break;
						}
					case 1:
						{
							str = "C相延迟角度设置错误!";
							break;
						}
					case 2:
						{
							str = "C相发射电流设置错误!";
							break;
						}
					}

					break;
				}
			}

		}
		
		MessageBox(str," ",MB_OK|MB_ICONASTERISK);
}

//读取角度
//short generatrixno 母线编号
//short phase  相别 0 A相 1 B相 2 C相
//BYTE kinds        0  信号强度 1 延迟角度
void CTTTView::ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds)
{
	
	BYTE ORDER[15];
	CString    str;
	//角度设置
	
	//前导码
	ORDER[0]  = 0x51;
	ORDER[1]  = 0x52;
	

	switch(kinds)
	{
	case 0:
		{
			ORDER[2]  = 0x58 + phase;//读信号角度
			break;
		}
	case 1:
		{	
			ORDER[2]  = 0xC3 + phase;//读延迟角度
			break;
		}
	case 2:
		{	
			ORDER[2]  = 0XC9 + phase;//读发射电流
			break;
		}
	case 3:
		{	
			ORDER[2]  = 0XC6 + phase;//无线模块电流电压
			break;
		}
	}
	
	ORDER[3]  = generatrixno-1;
	ORDER[4]  = 0;
	ORDER[5]  = 0;
	ORDER[6]  = 0;
	ORDER[7]  = 0;
	ORDER[8]  = 0;
	ORDER[9]  = 0;
	ORDER[10] = 0;
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	m_angles  = 0xff;
	
	//向单片机发命令
	if(PcSendToSCM(ORDER))
	{
		
		Sleep(50);
		
		switch(phase)
		{
		case 0:
			{  
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("当前A相设置的角度为%d度！",m_angles);//A相读角度
						break;
					}
				case 1:
					{
						str.Format("当前A相设置的延迟角度为%d度！",m_angles);//A相读延迟角度
						break;
					}
				case 2:
					{
						str.Format("当前A相设置的发射电流为%d！",m_angles);//A相读发射电流
						break;
					}	
				case 3:
					{
						
						//无线模块电流电压
						if(m_angles == 0xff)
						{
							str = "测无线模块A相电流电压通讯故障！！";
						}
						else
						{
							//前1位为电压    0  有  1无
							if(m_angles/128 > 0)
							{
								str.Format("无线模块A相电流电压(电压:无 电流:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("无线模块A相电流电压(电压:有 电流:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}

				}

				break;
				
			}
		case 1:
			{
				switch(kinds)
				{
				case 0:
					{
						str.Format("当前B相设置的角度为%d度！",m_angles);//B相读角度
						break;
					}
				case 1:
					{
						str.Format("当前B相设置的延迟角度为%d度！",m_angles);//B相读延迟角度
						break;
					}
				case 2:
					{
						str.Format("当前B相设置的发射电流为%d！",m_angles);//B相读发射电流
						break;
					}
				case 3:
					{
						
						//无线模块电流电压
						if(m_angles == 0xff)
						{
							str = "测无线模块B相电流电压通讯故障！！";
						}
						else
						{
							//前1位为电压    0  有  1无
							if(m_angles/128 > 0)
							{
								str.Format("无线模块B相电流电压(电压:无 电流:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("无线模块B相电流电压(电压:有 电流:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}
				}

				break;
				
			}
		case 2:
			{
				switch(kinds)
				{
				case 0:
					{
						str.Format("当前C相设置的角度为%d度！",m_angles);//C相读角度
						break;
					}
				case 1:
					{
						str.Format("当前C相设置的延迟角度为%d度！",m_angles);//C相读延迟角度
						break;
					}
				case 2:
					{
						str.Format("当前C相设置的发射电流为%d！",m_angles);//C相读发射电流
						break;
					}
				case 3:
					{
						
						//无线模块电流电压
						if(m_angles == 0xff)
						{
							str = "测无线模块C相电流电压通讯故障！！";
						}
						else
						{
							//前1位为电压    0  有  1无
							if(m_angles/128 > 0)
							{
								str.Format("无线模块C相电流电压(电压:无 电流:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("无线模块C相电流电压(电压:有 电流:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}
				}

				break;
				
			}
		case 3:
			{
				
				str.Format("当前线路编号为%d！",m_angles);       //读取直线号
				break;
				
			}
			
		}
		
		//	MessageBox(str,"",MB_OK|MB_ICONASTERISK);//提示:
	}
	else
	{
		
		switch(phase)
		{
		case 0:
			{  
				switch(kinds)
				{
				case 0:
					{
						str.Format("A相读取角度错误！");
						break;
					}
				case 1:
					{
						str.Format("A相读取延迟角度错误！");
						break;
					}
				case 2:
					{
						str.Format("A相读取发射电流错误！");
						break;
					}	
				case 3:
					{
						str.Format("测无线模块A相电流电压错误！");
						break;
					}
				}

				break;
				
			}
		case 1:
			{
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("B相读取角度错误！");
						break;
					}
				case 1:
					{
						str.Format("B相读取延迟角度错误！");
						break;
					}
				case 2:
					{
						str.Format("B相读取发射电流错误！");
						break;
					}
				case 3:
					{
						str.Format("测无线模块B相电流电压错误！");
						break;
					}
				}

				break;
				
			}
		case 2:
			{
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("C相读取角度错误！");
						break;
					}
				case 1:
					{
						str.Format("C相读取延迟角度错误！");
						break;
					}
				case 2:
					{
						str.Format("C相读取发射电流错误！");
						break;
					}
				case 3:
					{
						str.Format("测无线模块C相电流电压错误！");
						break;
					}
				}

				break;
				
			}
		case 3:
			{
				
				str.Format("当前线路编号读取错误！");//读取直线号
				break;
				
			}
			
		}
		
	}
	
	MessageBox(str," ",MB_OK|MB_ICONASTERISK);
	
}

void CTTTView::OnButtonAngle() 
{
	CAngleSet  dlg;
	dlg.DoModal();		
}

UINT  ReadChannels(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	
	int  HalfCount                   = 0;
    BOOLEAN bHalfReady = 0, bStopped = 0;
    U32                           count1;
	DataLen                =           0;

	do{
	    do {
             AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
	    } while (!bHalfReady && !bStopped);

        AI_AsyncDblBufferTransfer(card, ReadBuff);
           	 for(int i = 0;i < 512; i++)
			 {
			 	 
				 DataBuf[DataLen++] = ReadBuff[i]/m_DivideVal;	
				 
				 if(DataLen > 1000000)
				 {
					 bClearOp = TRUE;
					 break;
				 }
					 
			 }
			 HalfCount++;

	}while (!bClearOp && !bStopped);
     AI_AsyncClear(card, &count1);

     pview->GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	 pview->GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	 return 0;

}


void CTTTView::OnRealRecord() 
{    
	//清除数据
	UpdateData(TRUE);

	short m_selectCh = 0;

	if(m_bCh0)
	{
		m_selectCh ++;	 
		m_Channels        =  0;//通道
	}
	
	if(m_bCh1)
	{
		m_selectCh ++;	
		m_Channels        =  1;//通道
	}
	
	if(m_bCh2)
	{
		m_selectCh ++;
		m_Channels        =  2;//通道
	}
	
	if(m_bCh3)
	{
		m_selectCh ++;
		m_Channels        =  3;//通道
	}
	
	if(m_bCh4)
	{
		m_selectCh ++;
		m_Channels        =  4;//通道
	}
	
	if(m_bCh5)
	{
		m_selectCh ++;
		m_Channels        =  5;//通道
	}

	if(m_bCh8)
	{
		m_selectCh ++;
		m_Channels        =  8;//通道
	}
	
	if(m_bCh9)
	{
		m_selectCh ++;	
		m_Channels        =  9;//通道
	}
	
	if(m_bCh10)
	{
		m_selectCh ++;
		m_Channels        =  10;//通道
	}
	
	//自触发
    if(m_selectCh == 1)
	{
		m_ShowWave  = TRUE;
	}
	else 
	{
		MessageBox("自采波形时，请选择一个且唯一一个\r\n采集通道来采集数据！！","",MB_OK|MB_ICONWARNING);
		return;
	}
	
	
	memset(ReadBuff,0,1024);
	memset(DataBuf,0,1000000);
	/*
    for(int i = 0; i < 1000000; i++)
	{
	   DataBuf[i] = 0;
	}
	*/
		
	err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err != 0) 
	{
	    Beep(300,400);
		return;
    }
	       
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
   
	//通道 
	err = AI_ContReadChannel(card,m_Channels, AD_B_10_V, ReadBuff, /*nReadCount*/1024, 
		    100000, ASYNCH_OP);
  	
	AfxBeginThread(ReadChannels,this);

	bClearOp = 0;
	
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(TRUE);
	
	/*
	DWORD ThreadID =         0;
	HANDLE m_handles = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReadChannels,(void *)this,0,&ThreadID);
	WaitForSingleObject(m_handles,INFINITE);
    CloseHandle(m_handles);

	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	*/

	AfxBeginThread(ReadChannels,this);
	bClearOp = 0;
}

void CTTTView::OnRealSend() 
{
	//清除数据
	BYTE   m_order = 0;
	CString        str;

	UpdateData(TRUE);
    m_nStartPoint = 0;
    UpdateData(FALSE);

	short m_selectCh = 0;

	if(m_bCh0)
	{
		m_selectCh ++;	 
		m_Channels        =  0;//通道
	}
	
	if(m_bCh1)
	{
		m_selectCh ++;	
		m_Channels        =  1;//通道
	}
	
	if(m_bCh2)
	{
		m_selectCh ++;
		m_Channels        =  2;//通道
	}
	
	if(m_bCh3)
	{
		m_selectCh ++;
		m_Channels        =  3;//通道
	}
	
	if(m_bCh4)
	{
		m_selectCh ++;
		m_Channels        =  4;//通道
	}
	
	if(m_bCh5)
	{
		m_selectCh ++;
		m_Channels        =  5;//通道
	}

	if(m_bCh8)
	{
		m_selectCh ++;
		m_Channels        =  8;//通道
	}
	
	if(m_bCh9)
	{
		m_selectCh ++;	
		m_Channels        =  9;//通道
	}
	
	if(m_bCh10)
	{
		m_selectCh ++;
		m_Channels        =  10;//通道
	}
	
	//自触发
    if(m_selectCh == 1)
	{
		m_ShowWave  = TRUE;
	}
	else 
	{
		MessageBox("自采波形时，请选择一个且唯一一个\r\n采集通道来采集数据！！","",MB_OK|MB_ICONWARNING);
		return;
	}
		
	CWnd* pt    =    GetDlgItem(IDC_ORDER);
	pt->GetWindowText(str);	
	
	str.TrimLeft();
	str.TrimRight();
	
	if(str.IsEmpty())
	{
		MessageBox("命令字不能为空！","",MB_OK|MB_ICONWARNING);
		return;
	}
	
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

    //发命令
	SendOrderToSCM(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/, m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 0x02要什么东西,命令字*/,0/*可放时间或其它东西*/);
	
}

void CTTTView::OnButtonStoprec() 
{
	bClearOp =	TRUE;
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	Sleep(100);
	OnButtonUpdate();
}

//读取线路编号
void CTTTView::OnReadline() 
{
	/*
	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//获得时钟频率
	dff = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);//获得初始值
	qt1 = litmp.QuadPart;
	for(int i = 0; i < 10000; i ++)
	{
	}
	QueryPerformanceCounter(&litmp);//获得终止值
	qt2 = litmp.QuadPart;
	dfm = (double)(qt2-qt1);
	dft = dfm/dff;//获得对应的时间值
	*/
	
	UpdateData(TRUE);
	ReadThreePhaseAngle(m_generatrix,3,0);
}


//产生BCH码63－45－3
void CTTTView::Encode_Bch_63_45_3(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 63,k = 45;
	BYTE  bb[18];
	g[0]  = 1;
	g[1]  = 1;
	g[2]  = 1;
	g[3]  = 1;
	g[4]  = 0;
	g[5]  = 0;
	g[6]  = 1;
	g[7]  = 1;
	g[8]  = 0;
	g[9]  = 1;
	g[10] = 0;
	g[11] = 0;
	g[12] = 0;
	g[13] = 0;
	g[14] = 0;
	g[15] = 1;
	g[16] = 1;
	g[17] = 1;

	for (i = 0; i < length - k; i++)//length = 63, k = 45
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	//前面是系数
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];
	}

	//后面是数据
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
	}

		//ssgg debug
			//写入文本文件
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<64; i++) {
				CString mystr;
				if(g[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
		//end ssgg debug
}

//产生BCH码31－21－2
void CTTTView::Encode_Bch_31_21_2(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 31,k = 21;
	BYTE  bb[10];
    g[0]  =    1;
    g[1]  =    0;
    g[2]  =    0;
    g[3]  =    1;
    g[4]  =    0;
    g[5]  =    1;
    g[6]  =    1;
    g[7]  =    0;
    g[8]  =    1;
    g[9]  =    1;
    g[10] =    1;

	for (i = 0; i < length - k; i++)
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	CString str;
	
	//前面是系数
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];	
		
		str.Format("g[%d]=%d",i,g[i]);
		WriteToLog(str);
	}



	//后面是数据
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
		
		str.Format("g[%d]=%d",i + length - k,g[i + length - k]);
		WriteToLog(str);
	}
	
	g[31] = 0;

}


//产生BCH码45－27－3
void CTTTView::Encode_Bch_45_27_3(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 45,k = 27;
	BYTE      bb[18];

   	g[0]   = 1;
	g[1]   = 1;
	g[2]   = 1;
	g[3]   = 1;
	g[4]   = 0;
	g[5]   = 0;
	g[6]   = 1;
	g[7]   = 1;
	g[8]   = 0;
	g[9]   = 1;
	g[10]  = 0;
	g[11]  = 0;
	g[12]  = 0;
	g[13]  = 0;
	g[14]  = 0;
	g[15]  = 1;
	g[16]  = 1;
	g[17]  = 1;

	for (i = 0; i < length - k; i++)
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	CString str;
	
	//前面是系数
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];	
		
		str.Format("g[%d]=%d",i,g[i]);
		WriteToLog(str);
	}

	//后面是数据
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
		
		str.Format("g[%d]=%d",i + length - k,g[i + length - k]);
		WriteToLog(str);
	}
	
}

void CTTTView::OnEvent(WPARAM wParam, LPARAM lParam)
{
	
	switch(wParam)
	{
	case 1:
		{	
			UpdateData(TRUE);
			break;
		}
	case 2:
		{
		    UpdateData(FALSE);	
			break;
		}
	}
	
}

void CTTTView::OnSelchangeProtocols() 
{
	UpdateData(TRUE);	
	
	CString   str;

	if(m_ProtocolControl.GetCount() >= 0)
	{
		m_ProtocolControl.GetLBText(m_ProtocolControl.GetCurSel(),str);
	    m_protocol = atoi(str);

		CWnd* pt = GetDlgItem(IDC_CHECK4BIT);

		if(m_protocol == 22)
		{	
			UpdateData(FALSE);
			pt->EnableWindow(TRUE);
		}
		else
		{
			pt->EnableWindow(FALSE);
		}
		
		InitOrderCombo(m_protocol);
		
		OnSelchangeOrdercombo();

	}

}


BOOL CTTTView::DecodeBCH45273(BYTE recd[])
{
	
        register int i, j, u, q, t2, count = 0, syn_error = 0;
		short elp[8][32], l[1], s[6];
		short root[32], loc[32],reg[32];
		short qt[32], r[8][32];
		short b[8][32];
		short degr[32], degb[32];
		short temp, aux[32]; 
        CString         str;
		short m = 6, n = 63 , length = 45, t = 3, k = 27, d = 7;
	//	short m = 6, n = 63 , length = 56, t = 4, k = 32, d = 9;
     
		
		short alpha_to[64], index_of[64];
	    
		alpha_to[0]  = 1,index_of[0]   = -1,
		alpha_to[1]  = 2,index_of[1]   = 0,
		alpha_to[2]  = 4,index_of[2]   = 1,
		alpha_to[3]  = 8,index_of[3]   = 6,
		alpha_to[4]  = 16,index_of[4]  = 2,
		alpha_to[5]  = 32,index_of[5]  = 12,
		alpha_to[6]  = 3,index_of[6]   = 7,
		alpha_to[7]  = 6,index_of[7]   = 26,
		alpha_to[8]  = 12,index_of[8]  = 3,
		alpha_to[9]  = 24,index_of[9]  = 32,
		alpha_to[10] = 48,index_of[10] = 13,
		alpha_to[11] = 35,index_of[11] = 35,
		alpha_to[12] = 5,index_of[12]  = 8,
		alpha_to[13] = 10,index_of[13] = 48,
		alpha_to[14] = 20,index_of[14] = 27,
		alpha_to[15] = 40,index_of[15] = 18,
		alpha_to[16] = 19,index_of[16] = 4,
		alpha_to[17] = 38,index_of[17] = 24,
		alpha_to[18] = 15,index_of[18] = 33,
		alpha_to[19] = 30,index_of[19] = 16,
		alpha_to[20] = 60,index_of[20] = 14,
		alpha_to[21] = 59,index_of[21] = 52,
		alpha_to[22] = 53,index_of[22] = 36,
		alpha_to[23] = 41,index_of[23] = 54,
		alpha_to[24] = 17,index_of[24] = 9,
		alpha_to[25] = 34,index_of[25] = 45,
		alpha_to[26] = 7,index_of[26]  = 49,
		alpha_to[27] = 14,index_of[27] = 38,
		alpha_to[28] = 28,index_of[28] = 28,
		alpha_to[29] = 56,index_of[29] = 41,
		alpha_to[30] = 51,index_of[30] = 19,
		alpha_to[31] = 37,index_of[31] = 56,
		alpha_to[32] = 9,index_of[32]  = 5,
		alpha_to[33] = 18,index_of[33] = 62,
		alpha_to[34] = 36,index_of[34] = 25,
		alpha_to[35] = 11,index_of[35] = 11,
		alpha_to[36] = 22,index_of[36] = 34,
		alpha_to[37] = 44,index_of[37] = 31,
		alpha_to[38] = 27,index_of[38] = 17,
		alpha_to[39] = 54,index_of[39] = 47,
		alpha_to[40] = 47,index_of[40] = 15,
		alpha_to[41] = 29,index_of[41] = 23,
		alpha_to[42] = 58,index_of[42] = 53,
		alpha_to[43] = 55,index_of[43] = 51,
		alpha_to[44] = 45,index_of[44] = 37,
		alpha_to[45] = 25,index_of[45] = 44,
		alpha_to[46] = 50,index_of[46] = 55,
		alpha_to[47] = 39,index_of[47] = 40,
		alpha_to[48] = 13,index_of[48] = 10,
		alpha_to[49] = 26,index_of[49] = 61,
		alpha_to[50] = 52,index_of[50] = 46,
		alpha_to[51] = 43,index_of[51] = 30,
		alpha_to[52] = 21,index_of[52] = 50,
		alpha_to[53] = 42,index_of[53] = 22,
		alpha_to[54] = 23,index_of[54] = 39,
		alpha_to[55] = 46,index_of[55] = 43,
		alpha_to[56] = 31,index_of[56] = 29,
		alpha_to[57] = 62,index_of[57] = 60,
		alpha_to[58] = 63,index_of[58] = 42,
		alpha_to[59] = 61,index_of[59] = 21,
		alpha_to[60] = 57,index_of[60] = 20,
		alpha_to[61] = 49,index_of[61] = 59,
		alpha_to[62] = 33,index_of[62] = 57,
		alpha_to[63] = 0 ,index_of[63] = 58;
	
	t2 = 2 * t;
	
	////计算综合病症 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//修改 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // 设置错误标志
			// 转换综合病症从多项式到索引形式
			s[i] = index_of[s[i]];
			
	}
	
	//有错误的话
	if (syn_error) 
	{
		
		//计算错误的位置多项式用欧几里运算法则
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//计算b(x)数组值
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// 规格化错误位置多项式
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// 用Chien search找到错误的位置 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			}
			
			
			if (count == l[u])
			{
                m_CollectNos = l[u];

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;
					str.Format("纠正错误位置：%d",loc[i]);
					WriteToLog(str);
				}
				return TRUE;
				
			}
			else
			{
				str.Format("错误个数为： count = %d，l[%d] = %d",count,u,l[u]);
				WriteToLog(str);
				return FALSE;
			}
			
			//length - k -> length为数据值 
		}
		else
		{
			str.Format("错误个数为：%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		m_CollectNos = 0;
		str = "t = 0,没有错误";
		WriteToLog(str);
		return TRUE;
	}
	
}


UINT  ReadBchChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());	
    pview->ReadBCHMeter();
	return 0;
}


void CTTTView::OnSend() 
{
	UpdateData(TRUE);
	CWnd* pt  = GetDlgItem(IDC_RECEIVE);
	pt->SetWindowText(" ");
	m_ReceiveStr = "";
	
	m_SendOrder.TrimLeft();
	m_SendOrder.TrimRight();
	
	if(m_SendOrder.IsEmpty())
	{
		MessageBox("请先输入BCH编码 ！","",MB_OK);
		return;
	}
	
	//向采集卡发送
	if(m_iModeSel == 1)
	{
	
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_BUTTON_ANGLE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);
		
		for(int i = 0; i < 270000; i++)
		{
			DataBuf[i] = 0;
		}
		//memset(DataBuf,0,300000);
		
		AfxBeginThread(ReadBchChannel,this);
		
		m_ShowWave  = TRUE;
	}
	else
	{
		//串口发送
		//向串口发送数据
		int         m_order      = 0;
		CString                  str;
		UpdateData(TRUE);
		CString TestStr = m_SendOrder;
		CString                 Temp1;
		int                         k;
		CString            str1,s;
		SendByteArray.RemoveAll();
		TestStr.TrimRight();
        TestStr.TrimLeft();
	
		GetDlgItem(IDC_RECEIVE)->SetWindowText("");
		GetDlgItem(IDC_SENDORDER)->SetWindowText("");

		while(TestStr.Find(' ') != -1)
		{
			
			k = TestStr.Find(' ');
			Temp1 = TestStr.Left(k);
			
			Temp1.TrimLeft();
			Temp1.TrimRight();
			
			Temp1 = Temp1.Right(Temp1.GetLength()-2);
			Temp1.MakeLower();
	
			SendByteArray.Add(GetHexValue(Temp1));
			TestStr  = TestStr.Right(TestStr.GetLength() - k - 1);
			TestStr.TrimLeft();
			TestStr.TrimRight();
			
		}

	
		
		TestStr = TestStr.Right(TestStr.GetLength() - 2);
		TestStr.MakeLower();

		SendByteArray.Add(GetHexValue(TestStr));
		
		if(SendByteArray.GetSize() < 16)
		{
			MessageBox("所输入数据个数小于16个！","警告",MB_OK|MB_ICONWARNING);
			SendByteArray.RemoveAll();
			return;
		}

		BYTE TempByte  = 0;
		//14 检验和
		for(int i = 0; i < 14; i ++)
		{
			TempByte = TempByte + SendByteArray[i];
		}
		
		SendByteArray[14] = TempByte;      
		
		//15结束符
        SendByteArray[15] = 0x16;

		//向串口发送
		SendByteArrayToCom();
	}

}

void CTTTView::ReadBCHMeter()
{	

	CString TestStr = m_SendOrder;
	CString           Temp1;
	int                   k;
	//循环读数   
	int     HalfCount  =     0;
	BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
	U32                  count;
	DataLen            =     0; 
	memset(ReadBuff,0,1024);
	int          DataValues = 0;
	CByteArray      m_DataArray;
	U32               output[5];
	BYTE             Receive[5];
	CString  str1,str,s;

	while(TestStr.Find(' ') != -1)
	{
	 
		k = TestStr.Find(' ');
	    Temp1 = TestStr.Left(k);
		
		Temp1.TrimLeft();
		Temp1.TrimRight();

		Temp1 = Temp1.Right(Temp1.GetLength()-2);
		Temp1.MakeLower();
      	m_DataArray.Add(GetHexValue(Temp1));

		TestStr  = TestStr.Right(TestStr.GetLength() - k - 1);
		
		TestStr.TrimLeft();
		TestStr.TrimRight();

	}
	
	TestStr = TestStr.Right(TestStr.GetLength() - 2);
    TestStr.MakeLower();

	m_DataArray.Add(GetHexValue(TestStr));

	
	if(m_DataArray.GetSize() < 15)
	{
		MessageBox("BCH输入数据个数不够！","",MB_OK);
		return;
	}
	else
	{
		
		BYTE ORDER[15];
		
		for(int i = 0; i < 14; i++)
		{
			ORDER[i] = m_DataArray[i];
		}	
				
		m_SendOrder = "";
		
		ORDER[14]    = 0;

		//发前14位
		for(int j = 0; j <= 13; j++)
		{

			WriteP9111_CHANNEL_DOPort(ORDER[j]); 
			
			if(j >= 2)
			{	
				//检验和
				ORDER[14] = ORDER[14] + ORDER[j];
			}
			
			if(ORDER[j] > 15)
			{
				//Temp1.Format(" 0x%0x \r\n",ORDER[j]);
				Temp1.Format(" 0x%0x  ",ORDER[j]);
			}
			else
			{
				//Temp1.Format(" 0x0%0x \r\n",ORDER[j]);
				Temp1.Format(" 0x0%0x  ",ORDER[j]);
			}
			m_SendOrder = m_SendOrder + Temp1;
			
		}
		
		
		Temp1.Format(" 0x%0x ",ORDER[14]);
		m_SendOrder = m_SendOrder + Temp1;
		SendMessage(WM_EVENT,2,0);

		//发送检验和
		WriteP9111_CHANNEL_DOPort(ORDER[14]);
        		
		//空一个数
		WriteP9111_CHANNEL_DOPort(0X01);
		
		
		//边发边收
		for( j = 0; j < 5;j ++)
		{
			
			err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//时钟
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
			}
			
			//高的时侯收数,不要延时
			err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
			}
			
			Sleep(1);
			
			err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//时钟
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
			}
			
			//高的时侯收数,不要延时
			err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("写端口失败!","警告：",MB_OK|MB_ICONWARNING);
			}
			Receive[j] = BYTE(output[j] & 0xff);
			Sleep(1);
			
			
		}
		
		/**/
		str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//最高位两位去掉
		//AfxMessageBox(str1);
    
		CTime time = CTime::GetCurrentTime();
		CString s;
		s.Format("%4d-%2d-%2d %2d:%2d:%2d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //转换时间格式
		//WriteToLog("双向通讯命令：\r\n" + str + "\r\n" + str1 + s);
		
		
		if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
		{
			WriteToLog("双向通讯时检验和不对!\r\n" + str + "\r\n" + str1);
			Beep(300,400);
		}
		
		switch(ORDER[2])
		{
		case 0x53://pc机发送
			{
				//Receive[1]－－－母线  Receive[2]－－－ 线路 Receive[3]－－－ 相别
				if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
				{
					WriteToLog("双向通讯时触发命令不对 0x53!\r\n" + str + "\r\n" + str1);
					Beep(300,400); 
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5c://设置A相触发角度
			{
				if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
				{
					WriteToLog("双向通讯时设置触发角度不对 0x5C!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5d://设置B相触发角度
			{
				if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
				{
					WriteToLog("双向通讯时设置触发角度不对 0x5d!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5e://设置C相触发角度
			{
				if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
				{
					WriteToLog("双向通讯时设置触发角度不对 0x5e!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x58://读取A相触发角度
			{
				if(Receive[0] != 0x68)
				{
					WriteToLog("双向通讯时设置触发角度不对 0x58!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x59://读取B相触发角度
			{
				if(Receive[0] != 0x69)
				{
					WriteToLog("双向通讯时设置触发角度不对 0x59!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x5a://读取C相触发角度
			{
				if(Receive[0] != 0x6a)
				{
					WriteToLog("双向通讯时设置触发角度不对 0x5a!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x9c://读取直线号
			{
				if(Receive[0] != 0xac)
				{
					WriteToLog("双向通讯时读取直线编号不对 0x5a!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		}
		
		CTime time0  = CTime::GetCurrentTime();

		
		//连续读通道数据,m_CollectChannels采集通道
		err = AI_ContReadChannel(card,m_CollectChannels, AD_B_10_V, ReadBuff, 1024, 
			(F64)100000, ASYNCH_OP);

		if (err!=0) 
		{  
			Beep(300,400); 
		}
		
		bClearOp  = FALSE;
		
		do
		{
			do
			{
				//半满
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
				
			} while (!bHalfReady && !bClearOp);
			
			if (!bClearOp) 
			{
				
				//传送半满数据
				AI_AsyncDblBufferTransfer(card, ReadBuff);
				bHalfReady     =      FALSE;
				
				for(int i = 0; i < 512; i++)
				{	
					//最大值         m_maxDecimalVal      1、PCI-9111DR 4096     2、PCI-9111HR 65536 
    		        //采的数要除的值 m_DivideVal          1、PCI-9111DR   16     2、PCI-9111HR     1 
					DataValues = ReadBuff[i]/m_DivideVal;
					
					//读到数组,大于m_maxDecimalVal/2为负数
					if(DataValues > m_maxDecimalVal/2)
					{
						DataValues =  -(m_maxDecimalVal - DataValues);
					}
					
					DataBuf[DataLen++] = DataValues;
					
				}
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1     -       time0;
				
				if(m_protocol != 22)
				{
					
					//如果不是22协议
					if(ts.GetTotalSeconds() > (m_protocol%10)*9)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				else
				{						
					//如果是22协议
					if(ts.GetTotalSeconds() > 9)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
				switch(m_protocol)
				{
				case 22:
					{
						
					}
				case 31:
					{
						
					}
				case 32:
					{
						
					}
				case 71:
					{
						
					}
				case 72:
					{
						
						
					}
				case 73:
					{
						//64*4
						if(DataLen >= 131584)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 61:
					{
						// 1024 + 45*4*512  = 93184
						if(DataLen >= 93184)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 62:
					{
						//1024 + 4*45*2*512 = 185344
						if(DataLen >= 185344)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				
				}


			}
			
		}while (!bClearOp && !bStopped);
		
		AI_AsyncClear(card, &count);
		
		long m_checklengths = 0;
		
		switch(m_protocol)
		{
		case 22:
			{
				
			}
		case 31:
			{
				
			}
		case 32:
			{
				
			}
		case 71:
			{
				
			}
		case 72:
			{
				
				
			}
		case 73:
			{
				//64*4
				m_checklengths = 131584;
				break;
			}
		case 61:
			{
				// 1024 + 45*4*512  = 93184
				m_checklengths = 93184;
				break;
			}
		case 62:
			{
				//1024 + 4*45*2*512 = 185344
				m_checklengths = 185344;
				break;
			}
		}
		
		if(DataLen >= m_checklengths)
		{
			double GetValue = Decode();
			
			if(GetValue >= 0)//解码
			{
				m_data.Format("%f",GetValue);//.2
			}
			else
			{
				m_data = "NULL";
			}
			
		}
		else
		{
			m_ReceiveStr = "<<采集数据错误>>";
			m_data       = "NULL";
		}

		CEdit * pt =(CEdit *)GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText(m_data);

		CWnd* pts   = GetDlgItem(IDC_REAL_START);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SEND);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SETTIMER);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_DECODE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_RADIO_REALTIME);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_COMSET);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SENDALLONE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_BUTTON_ANGLE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_REALSTOP);
		pts->EnableWindow(FALSE);
		
	}
		
}

int CTTTView::GetHexValue(CString str)
{
    int iReturn = 0;

	int length = str.GetLength();
    for(int i = length - 1; i >= 0; i--)    
    {
		char cc =  str.GetAt(i);// str[i];

        if(cc >= '0' && cc <= '9')
            iReturn += int((cc - '0') * pow(16,length - i - 1));
        else if(cc >= 'a')
            iReturn += int((cc - 'a' + 10) * pow(16,length - i - 1));
        else 
            iReturn += int((cc - 'A' + 10) * pow(16,length - i - 1));
    }

    return iReturn ;
}

UINT  ContinueReadChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());	
    pview->ContinueRead();
	return 0;
}

void CTTTView::OnSettimer() 
{
	UpdateData(TRUE);
    m_nStartPoint = 0;
    UpdateData(FALSE);

   	CString         str;
    m_Stopping  = FALSE;

	CTIMEDLG        dlg;
	dlg.m_seconds  = m_TimeSeconds;
	
	if(dlg.DoModal() != IDOK)
	{
         return;
	}

	m_TimeSeconds = dlg.m_seconds;

	if(m_addone)
	{
		str = "你想连续读表？模块号逐渐加1？";
	}
	else
	{
		str = "你想连续读表？模块号不变？";
	}

	if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{


		CWnd* pt = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText("  ");
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);
        
		m_data            = "  ";
		m_SuccessTimes    = 0;
   	    m_TotalTimes      = 0;
		m_CollectErrors   = 0;//采集错误

		AfxBeginThread(ContinueReadChannel,this);
		
	}


}



void CTTTView::ContinueRead()
{

	CWnd* pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);

	CString           Temp;
	
	bClearOp  = FALSE;//让线程退出
	
	while (1)
	{	
		
		if(m_Stopping)//让线程退出
		{	
            pt = GetDlgItem(IDC_REAL_START);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SEND);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SETTIMER);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_DECODE);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO_REALTIME);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_COMSET);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SENDALLONE);
			pt->EnableWindow(TRUE);	
			pt = GetDlgItem(IDC_BUTTON_ANGLE);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_REALSTOP);
			pt->EnableWindow(FALSE);
			break;
		}
					
		SendMessage(WM_EVENT,1,0);
	
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);	
		
		for(int i = 0; i < 120000; i++)
		{
		   DataBuf[i] = 0;
		}

		m_ShowWave     =      TRUE;
	    DWORD ThreadID =         0;

		HANDLE m_handles = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReadChannel,(void *)this,0,&ThreadID);
		WaitForSingleObject(m_handles,INFINITE);
        CloseHandle(m_handles);

		if(m_TotalTimes > 0)
		{
		    Temp.Format("读%d次,成功%d次[%.1f%s],采集错误%d次[%.5f%s],读表间隔：%d秒",m_TotalTimes,m_SuccessTimes,m_SuccessTimes*100.00/m_TotalTimes,"%",m_CollectErrors,m_CollectErrors*100.00000/m_TotalTimes,"%",m_TimeSeconds);
		}
		else
		{		 
			Temp.Format("读%d次,成功%d次[%.1f%s],,采集错误0次",0,0,0,"%");
		}
	    
		CWnd* ptt = GetDlgItem(IDC_STATICFILE);
        ptt->SetWindowText(Temp);

		//采集错误
		if(m_TotalTimes > 0)
		{
			Temp.Format("读%d次,成功%d次[%.1f%s]",m_TotalTimes,m_SuccessTimes,m_SuccessTimes*100.00/m_TotalTimes,"%");
		}
		else
		{		 
			Temp.Format("读%d次,成功%d次[%.1f%s]",0,0,0,"%");
		}
		
		ptt = GetDlgItem(IDC_DATAVALUE);
        ptt->SetWindowText(Temp);
		
		ptt = GetDlgItem(IDC_REAL_START);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SEND);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SETTIMER);
		ptt->EnableWindow(FALSE);
    	ptt = GetDlgItem(IDC_DECODE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_RADIO_REALTIME);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_COMSET);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SENDALLONE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_BUTTON_ANGLE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_REALSTOP);
		ptt->EnableWindow(TRUE);

		m_data  =           Temp;

		if(!m_Stopping)
		{
			
			for( i = 0; i < 5*m_TimeSeconds; i ++)
			{

				MSG message;
				if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}

				if(m_Stopping)
				{
					pt = GetDlgItem(IDC_REAL_START);
			        pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SEND);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SETTIMER);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_DECODE);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_RADIO_REALTIME);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_COMSET);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SENDALLONE);
					pt->EnableWindow(TRUE);	
					pt = GetDlgItem(IDC_BUTTON_ANGLE);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_REALSTOP);
					pt->EnableWindow(FALSE);
					break;
				}
				
				Sleep(200);
			}
			
		}
		
		if(m_addone)
		{
			pt = GetDlgItem(IDC_MODULE);
			pt->EnableWindow(FALSE);
			
			m_module = m_module + 1;
			
			if(m_module%100 > 15)
			{
				m_module = (m_module/100 + 1)*100 + 1;
			}
			
			if(m_module > 13107115)
			{
				pt = GetDlgItem(IDC_MODULE);
				pt->EnableWindow(TRUE);	
				pt = GetDlgItem(IDC_REALSTOP);
				pt->EnableWindow(FALSE);
				pt = GetDlgItem(IDC_REAL_START);
				pt->EnableWindow(TRUE);	
				pt = GetDlgItem(IDC_SEND);
				pt->EnableWindow(TRUE);
				MessageBox("读表完毕！！"," ",MB_OK|MB_ICONWARNING);
				break;
			}
			
			SendMessage(WM_EVENT,2,0);

		}

	}
	
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_MODULE);
	pt->EnableWindow(TRUE);
}

void CTTTView::OnFileNew() 
{
	
	
}

void CTTTView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	if(m_iModeSel == 2)
	{
	  status(m_StatusStr);
	}
	else
	{
		status("");
	}
}

void CTTTView::OnFileOpen() 
{
	
	
}

void CTTTView::OnFileSave() 
{
	
	
}

void CTTTView::OnCheck10() 
{
   UpdateData(TRUE);
   OnButtonUpdate();
  
}

void CTTTView::OnZhongzhi() 
{
	UpdateData(TRUE);
	
	//中值滤波
	for(int i = 2; i < 120000 - 2 ; i++)
	{
		 DataBuf[i] = (DataBuf[i-2] + DataBuf[i-1] + DataBuf[i] + DataBuf[i+1] + DataBuf[i+2])/5;
	}

}

void CTTTView::OnDecode() 
{
	UpdateData(TRUE);
	CString       ss;
	
	m_ReceiveStr = "";	
 	
	m_startpoint = m_Spinstart.GetPos();
	m_wavepoints = m_SpinAverage.GetPos();

	long time1 = GetTickCount();
   	double m_GetValue =  0;
    m_GetValue =	Decode();
	long time2 = GetTickCount();

	ss.Format("【解码所耗时间：%6d】\r\n",time2 - time1);
	WriteToLog(ss);
	
	m_data       = "NULL";
	
	if(m_GetValue >= 0)
	{
		m_data.Format("%.2f",(m_GetValue));
	}
	else
	{
		Beep(300,400);
	}

	UpdateData(FALSE);
	
	OnButtonUpdate();
}


void CTTTView::OnFft() 
{
    #define KK  1024
	//re ：实部 ；im：虚部；当ll=1，正变换；当ll=-1，反变换；nn:2的幂；
	double *pr,*pi;
	pr = new double[KK];
	pi = new double[KK];

	for(int i = 0 ; i < 229; i ++)
	{
		for(int j = 0; j < KK; j++)
		{
		   pr[j]     = double(DataBuf[i*KK+j]);
		   pi[j]     = double(DataBuf[i*KK+j]);
     	}
		
		//对数据进行FFT 
		fftnew(pr, pi, KK, 1);
	
		//对数据进行反FFT
		//fftnew(pr, pi, KK, -1);
		
		for( j = 0; j < KK; j++)
		{
		   DataBuf[i*KK+j] = short(pr[j]);
		}

	}
	delete[] pr;
	delete[] pi;

    OnButtonUpdate();
}

BOOL CTTTView::FFT(double * data, unsigned long nn[], int ndim, int isign)
{
    #define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot;
	double tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	for (ntot=1,idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for(idim=ndim;idim>=1;idim--)
	{
		n = nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) 
		{
			if (i2 < i2rev)
			{
				for (i1=i2;i1<=i2+ip1-2;i1+=2) 
				{
					for (i3=i1;i3<=ip3;i3+=ip2) 
					{
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) 
			{
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2)
		{
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) 
			{
				for (i1=i3;i1<=i3+ip1-2;i1+=2) 
				{
					for (i2=i1;i2<=ip3;i2+=ifp2) 
					{
						k1=i2;
						k2=k1+ifp1;
						tempr       = wr*data[k2]-wi*data[k2+1];
						tempi       = wr*data[k2+1]+wi*data[k2];
						data[k2]    = data[k1]-tempr;
						data[k2+1]  = data[k1+1]-tempi;
						data[k1]   += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
	return true;
}



//pr[n]——输入的实部
//pi[n]——数入的虚部
//n，k ——满足n=2^k
//fr[n]——输出的实部
//fi[n]——输出的虚部
//l——0 FFT，1 IFFT
//il——0 输出按实部/虚部；1 输出按模/幅角
void CTTTView::kkfft(double pr[],double pi[],int n,int k,double fr[],double fi[],int l,int il)
{
    int it,m,is,i,j,nv,l0;
    double p,q,s,vr,vi,poddr,poddi;
    for (it=0; it<=n-1; it++)
	{ 
		m  = it; 
		is =  0;
		
		for (i=0; i<=k-1; i++)
		{ 
			j  = m/2;
			is =2*is+(m-2*j);
			m  =   j;
		}
		
		fr[it]=pr[is]; fi[it]=pi[is];
		
	}
	
    pr[0] = 1.0; 
    pi[0] = 0.0;
    p     = 6.283185306/(1.0*n);
    pr[1] = cos(p);
	pi[1] = -sin(p);

    if (l!=0)
	{ 
		pi[1]=-pi[1];
	}
    
	for (i=2; i<=n-1; i++)
	{
		p=pr[i-1]*pr[1]; q=pi[i-1]*pi[1];
        s=(pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
        pr[i]=p-q; pi[i]=s-p-q;
	}
    
	for (it=0; it<=n-2; it=it+2)
	{
		vr=fr[it]; vi=fi[it];
        fr[it]=vr+fr[it+1]; fi[it]=vi+fi[it+1];
        fr[it+1]=vr-fr[it+1]; fi[it+1]=vi-fi[it+1];
	}
    m=n/2; 
	nv=2;
    
	for (l0=k-2; l0>=0; l0--)
	{
		m=m/2; 
		nv=2*nv;

        for (it=0; it<=(m-1)*nv; it=it+nv)
		{
			
			for (j=0; j<=(nv/2)-1; j++)
            { 
				p=pr[m*j]*fr[it+j+nv/2];
				q=pi[m*j]*fi[it+j+nv/2];
				s=pr[m*j]+pi[m*j];
				s=s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
				poddr = p-q; 
				poddi = s-p-q;
				fr[it+j+nv/2]=fr[it+j]-poddr;
				fi[it+j+nv/2]=fi[it+j]-poddi;
				fr[it+j]=fr[it+j]+poddr;
				fi[it+j]=fi[it+j]+poddi;
            }

		}
	}

    if (l!=0)
	{
		for (i=0; i<=n-1; i++)
		{
			fr[i]=fr[i]/(1.0*n);
			fi[i]=fi[i]/(1.0*n);
		}
	}

	if (il!=0)
	{
		for (i=0; i<=n-1; i++)
		{ 
			pr[i]=sqrt(fr[i]*fr[i]+fi[i]*fi[i]);
			
			if (fabs(fr[i])<0.000001*fabs(fi[i]))
			{
			
				if ((fi[i]*fr[i])>0)
				{ 
					pi[i]=90.0;
				}
				else
				{
					pi[i]=-90.0;
				}

			}
			else
			{
				pi[i]=atan(fi[i]/fr[i])*360.0/6.283185306;
			}
			
		}
	}
}


//re ：实部 ；im：虚部；当ll=1，正变换；当ll=-1，反变换；nn:2的幂；
void CTTTView::fftnew(double *re, double *im, int nn, int ll)
{
    #define PI 3.1415926535

	int j, ij, m, l, istep;
	double sc, actep, bctep, bcarg, aw, bw;
	double atemp, btemp;
	j = 0;
	sc = sqrt(1.0 / nn);
	
	for (ij=0; ij<=nn-1; ij++) 
	{
		if (ij <= j) 
		{
			actep = re[j] * sc;
			bctep = im[j] * sc;
			re[j] = re[ij] * sc;
			im[j] = im[ij] * sc;
			re[ij] = actep;
			im[ij] = bctep;
		}
		m = nn/2;
		do 
		{
			if ((j+1)<=m) 
				break;
			j = j - m;
			m = m/2;
		}
		while (m>=1);
		j = j + m;
	}
	
	l = 1;
	do 
	{
		istep = 2 * l;
		for (m=1; m<=l; m++) 
		{
			bcarg = -(PI * ll * (m-1)) / l;
			aw = cos(bcarg); 
			bw = sin(bcarg);
			for (ij=m-1; ij<=nn-1; ij=ij+istep) 
			{
				atemp = aw * re[ij+l] - bw * im[ij+l];
				btemp = aw * im[ij+l] + bw * re[ij+l];
				re[ij+l] = re[ij] - atemp;
				im[ij+l] = im[ij] - btemp;
				re[ij] = re[ij] + atemp;
				im[ij] = im[ij] + btemp;
			}
		}
		l = istep;
	} 
	while( l < nn );
}



//等距节点五点三次平滑
//n-整型变量，输入的点数，要求n>=5
//y-长度为n的数组，存放n个等距观测点上的观测数据
//yy-长度为n的数组，返回时存放平滑结果
void CTTTView::kkspt(int n,double y[],double yy[])
{ 
	int i;
	if (n < 5)
	{ 
		for (i = 0; i <= n-1; i++)
		{
			yy[i]=y[i];
		}
	}
	else
	{ 
		yy[0]=69.0*y[0]+4.0*y[1]-6.0*y[2]+4.0*y[3]-y[4];
		yy[0]=yy[0]/70.0;
		yy[1]=2.0*y[0]+27.0*y[1]+12.0*y[2]-8.0*y[3];
		yy[1]=(yy[1]+2.0*y[4])/35.0;
		for (i=2; i<= n-3; i++)
		{ 
			yy[i]=-3.0*y[i-2]+12.0*y[i-1]+17.0*y[i];
			yy[i]=(yy[i]+12.0*y[i+1]-3.0*y[i+2])/35.0;
		}
		yy[n-2]=2.0*y[n-5]-8.0*y[n-4]+12.0*y[n-3];
		yy[n-2]=(yy[n-2]+27.0*y[n-2]+2.0*y[n-1])/35.0;
		yy[n-1]=-y[n-5]+4.0*y[n-4]-6.0*y[n-3];
		yy[n-1]=(yy[n-1]+4.0*y[n-2]+69.0*y[n-1])/70.0;
	}
}

//相关性检验
double CTTTView::CorrelationCheck(short SourceArray[], short DestArray[], int m,short m_places)
{

    double           A,B,C,Pxy,sums;
	double      DestArrayBak[2000];
	double     DestArrayBaks[2000];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	//去直流
	if(m_qzhikiu)
	{	
		
		for( i = 0; i < m;i ++)
		{
			sums = sums + double(DestArray[i]);
		}
		
		for( i = 0; i < m;i ++)
		{
			
			DestArrayBak[i]  = double(DestArray[i] - sums*1.000/m);
		}

	}
	else
	{
		for( i = 0; i < m;i ++)
		{
			DestArrayBak[i]  = double(DestArray[i]);
		}
		
	}

	//要移动位置
	if(WM_NUMBERS > 0 && m_findpipeimax)
	{

		if(m_places + 1 <= WM_NUMBERS/2)
		{
		
			//差值前移
			for( i = 0; i < m;i ++)
			{
				
				//移动位置匹配
				if(i + (WM_NUMBERS/2 - m_places)*1 < m)
				{
					//数据前移
					DestArrayBak[i] =  DestArrayBak[i + (WM_NUMBERS/2 - m_places)*1];
				}
				else
				{
					DestArrayBak[i] = 0;
				}
							
				//前面数据赋为0
				if(i <= m - m_iBandPassPoints)
				{
					DestArrayBak[i]    =  0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}
				
			}
			
		}
		else if(m_places + 1 > WM_NUMBERS/2 + 1)
		{
			
			//差值后移
			for( i = 0; i < m;i ++)
			{
				
				if(i >= (m_places- WM_NUMBERS/2)*1)
				{
					//数据后移
					DestArrayBaks[i] =  DestArrayBak[i - (m_places- WM_NUMBERS/2)*1];
				}
				else
				{
					DestArrayBaks[i] = 0;
				}
				
				//前面数据赋为0
				if(i <= m - m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}
				
			}
			
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i] = DestArrayBaks[i];
			}
			
		}
		else  if(m_places + 1 == WM_NUMBERS/2 + 1)
		{
         
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i]  = double(DestArray[i]);
				
				//前面数据赋为0
				if(i <= m- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}

			}

		}

	}


	for(i = 0; i < m_iBandPassPoints;i ++)
	{
		A += SourceArray[256-m_iBandPassPoints+i]*DestArrayBak[m -m_iBandPassPoints+i];
        B += SourceArray[256-m_iBandPassPoints+i]*SourceArray[256-m_iBandPassPoints+i];
        C += DestArrayBak[m -m_iBandPassPoints+i]*DestArrayBak[m -m_iBandPassPoints+i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
	/*
    double           A,B,C,Pxy,sums;
	double      DestArrayBak[256];
	double     DestArrayBaks[256];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	//去直流
	if(m_qzhikiu)
	{	
		
		for( i = 0; i < m;i ++)
		{
			sums = sums + double(DestArray[i]);
		}
		
		for( i = 0; i < m;i ++)
		{
			
			DestArrayBak[i]  = double(DestArray[i] - sums*1.000/m);
		}

	}
	else
	{
		for( i = 0; i < m;i ++)
		{
			DestArrayBak[i]  = double(DestArray[i]);
		}
		
	}

	//要移动位置
	if(WM_NUMBERS > 0 && m_findpipeimax)
	{

		if(m_places + 1 <= WM_NUMBERS/2)
		{
		
			//差值前移
			for( i = 0; i < m;i ++)
			{
				
				//移动位置匹配
				if(i + (WM_NUMBERS/2 - m_places)*1 < m)
				{
					//数据前移
					DestArrayBak[i] =  DestArrayBak[i + (WM_NUMBERS/2 - m_places)*1];
				}
				else
				{
					DestArrayBak[i] = 0;
				}
							
				//前面数据赋为0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBak[i]    =  0;
					SourceArray[i]     =  0;
				}
				
			}
			
		}
		else if(m_places + 1 > WM_NUMBERS/2 + 1)
		{
			
			//差值后移
			for( i = 0; i < m;i ++)
			{
				
				if(i >= (m_places- WM_NUMBERS/2)*1)
				{
					//数据后移
					DestArrayBaks[i] =  DestArrayBak[i - (m_places- WM_NUMBERS/2)*1];
				}
				else
				{
					DestArrayBaks[i] = 0;
				}
				
				//前面数据赋为0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;
					SourceArray[i]      =   0;
				}
				
			}
			
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i] = DestArrayBaks[i];
			}
			
		}
		else  if(m_places + 1 == WM_NUMBERS/2 + 1)
		{
         
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i]  = double(DestArray[i]);
				
				//前面数据赋为0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;
					SourceArray[i]      =   0;
				}

			}

		}

	}


	for(i = 0; i < m;i ++)
	{
		A += SourceArray[i]*DestArrayBak[i];
        B += SourceArray[i]*SourceArray[i];
        C += DestArrayBak[i]*DestArrayBak[i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
	*/
}

void CTTTView::OnReadfilter() 
{
	//打开文件对话框
	char szFilter[]="匹配波形数据文件(*.TXT)|*.TXT||";
   	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{
	
		char                 buf[7];
		CString                 str;
		short  GetSourceArray[2048];
	
		//得到波形数据文件的单个数据长度
	    short length = GetFileEveryDataLength(dlg.GetPathName());
	
		if(!file.Open(dlg.GetPathName( ),CFile::modeRead))
		{
			MessageBox("文件打开错误!","确定",MB_OK); 
			return;
		}

		if(length != 4 && length != 5)
		{
			file.Close();
			MessageBox("此数据文件不是TTT波形数据文件！","确定",MB_OK|MB_ICONWARNING);
			return;
		}

		MaxPointsNum = (file.GetLength())/(length + 2);	//12位采集卡length + 2为6 16位采集卡length + 2为7
	
		if(MaxPointsNum != 2048)
		{
			MessageBox("匹配波形数据大小应为2048个数据!","确定",MB_OK);
			file.Close();
			return;
		}

		CWnd* ptt = GetDlgItem(IDC_STATICFILE2);
		ptt->SetWindowText("匹配文件：" + dlg.GetPathName());

		file.Seek(0,CFile::begin);
		
		for(UINT j = 0; j < MaxPointsNum; j++)
		{
			file.Read(buf,length+2);
			str   =      buf;
			str.TrimLeft();
			str.TrimRight();
			GetSourceArray[j] = atoi(str);
			file.Seek(0,CFile::current);
		}
		file.Close();

		//从3-1,4-2
		for(int i = 0;i < 512;i ++)   
		{ 
			//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
		    GetSourceArray[i]       = GetSourceArray[2 * 512 + i] - GetSourceArray[i];
			GetSourceArray[512 +i]  = GetSourceArray[3 * 512 + i] - GetSourceArray[512 + i];
		}
		
		//叠加数据
		for( i = 0;i < 256;i ++)   
		{ 
			SourceArrays[i]  = GetSourceArray[i] + GetSourceArray[256+i] + GetSourceArray[512+i] + GetSourceArray[768+i];
			m_ppwave[i]      = SourceArrays[i];
			
			str.Format("%5d,",SourceArrays[i]);
			//WriteToLog(str);
			
			//写入文本文件
			FILE *text;
			if((text = fopen("c:\\datas.txt","a")) != NULL)
			{
				fputs(str ,text);
			
				if((i+1)%16 == 0)
				{
					fputs("\r\n",text); 
				}
				
				fclose(text);
			}

		}

		UpdateData(FALSE);	
		
		OnButtonUpdate();

	}
	
}


void CTTTView::OnDeletefile() 
{
	if(::DeleteFile("C:\\data.txt") != 0)
	{
		MessageBox("日志文件已经删除!"," ",MB_OK);
	}
	else
	{
        MessageBox("对不起，找不到日志文件！"," ",MB_OK|MB_ICONWARNING);
	}
	
}

void CTTTView::OnOpenfile() 
{
	CString strFileName("C:\\data.txt");
	CFileFind  fFind;
	BOOL bExist = fFind.FindFile(strFileName);   //判断文件是否存在
	fFind.Close ();
	
	if(!bExist)   //如果文件不存在则创建
	{
         MessageBox("对不起，找不到日志文件！","",MB_OK|MB_ICONWARNING);
	}
	else
	{
		//打开此文本文件
	    WinExec( "notepad.exe C:\\data.txt",SW_SHOWMAXIMIZED);
	}
	
}

//得到中值滤波
short CTTTView::GetMedianNum(short bArray[], int iFilterLen)
{
	//循环变量
	int		i;
	int		j;
	
	// 中间变量
	short    bTemp;
	
	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// 返回中值
	return bTemp;
}

void CTTTView::OnBchtest() 
{   
  /* card: kortets ID. Gis her startverdi -1, verdi settes senere av funksjonen Register_Card.  
       I16 er en datatype som er definert i dask.h. 16 bit signed int. */ 
 

    /* cardNumber: nummer til kort i maskinen. Refererer til fysisk plass p? hovedkortet. */  
 //   I16 cardNumber = 0;  

    /* cardType: type kort som skal benyttes. Konstanter som svarer til de ulike kort som st?ttes av  
        biblioteket finnes i dask.h.  */ 
 //   int cardType=PCI_9111DG;  

    /* Variabel som skal motta verdi fra digital inngang */  
//  U32 dig_inn = 0;  

    /* Initierer kort og softwarebibliotek som benyttes. Returnerer ID til kortet, eller negativ feilkode   
       dersom feil oppst?r. */  
  //  card = Register_Card(cardType, cardNumber); 

    /* Avslutter om initsieringen ikke gikk bra. */  
   // if (card < 0) 
   // {  
   //     printf("Feil ved initsiering av kortet." ); 
   //     printf("\nFeilkode: %d", card); 
   //     exit(1); 
   // } 

    /* Skriver kortets ID til skjerm. */ 
  //  printf("Card ID= %d", card); 
//	long m_time1 =  GetTickCount();

    /* Henter verdi fra digital inngang og skriver denne til skjerm */  


//  DI_ReadPort(card, P9111_CHANNEL_EDI,&dig_inn); 
/*
    long m_time2 =  GetTickCount();
    BYTE m_temp  = dig_inn & 0xff;
	char                   t[32] ;
	
	itoa(dig_inn, t, 2);
	CString        stddr;

	stddr.Format("运算时间：%d毫秒,二进制值:%s",m_time2-m_time1,t);
	AfxMessageBox(stddr);

    printf("\nVerdi fra digital inngang: %d\n", dig_inn);  

  //Release_Card(card);  



	return;

	CString      sFolderPath;
	BROWSEINFO            bi;
	char    Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner      = NULL;
	bi.pidlRoot       = NULL;
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle      = "修改接收路径";
	bi.ulFlags        = 0;
	bi.lpfn           = NULL;
	bi.iImage         = NULL;
	
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//取得文件夹路径到Buffer里
		sFolderPath =                 Buffer;//将路径保存在一个CString对象里
		AfxMessageBox(sFolderPath);
	}

	LPMALLOC       lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc)))
		return;
	//释放内存
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	//写入文本文件
	FILE *text;
	if((text = fopen(sFolderPath + "\\data.txt","a")) != NULL)
	{
		fputs("jfvgffg\r\n",text);
		fclose(text);
	}
	else
	{
        AfxMessageBox("文件打开错误！");
	}

	return;
	
	COleDateTime dateTest;
   // dateTest value = midnight 30 December 1899
    dateTest = COleDateTime::GetCurrentTime();
    CString        strtime;
	strtime.Format("%4d-%02d-%02d %02d:%02d:%02d",dateTest.GetYear(),dateTest.GetMonth(),dateTest.GetDay(),dateTest.GetHour(),dateTest.GetMinute(),dateTest.GetSecond());
	
   	AfxMessageBox(strtime);
	return;


	CString        strtime;
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CTime dateTest(systime);
	strtime.Format("%4d-%02d-%02d %02d:%02d:%02d",dateTest.GetYear(),dateTest.GetMonth(),dateTest.GetDay(),dateTest.GetHour(),dateTest.GetMinute(),dateTest.GetSecond());

	AfxMessageBox(strtime);
    */
   /*
	
	int m_bitvalue =  255;
	CString m_ReadRangeStr;
	m_ReadRangeStr.Format("%03x",m_bitvalue);
	AfxMessageBox(m_ReadRangeStr);
	return;
	*/
	/*
	//61,62,协议,检验字节,BCH校验 45_27_3
	BYTE          data[27];
	//61,62,协议,检验字节,BCH校验 45_27_3
	BYTE             g[45];

    //27位数据
	for(int j = 0; j < 27; j ++)
	{
		if(j == 26)
		{
			data[j] = 1;
		}
		else
		{
			data[j] = 0;
		}
	}
	
	//转成BCH码45_27_3
	Encode_Bch_45_27_3(g,data);
	return;
	*/

	/*
	BYTE gg[31];
	gg[ 0] =   0;
	gg[ 1] =   0;
	gg[ 2] =   1;
	gg[ 3] =   1;
	gg[ 4] =   0;	
	gg[ 5] =   0;
	gg[ 6] =   1;
	gg[ 7] =   1;
	gg[ 8] =   0;
	gg[ 9] =   1;
	gg[10] =   0;
	gg[11] =   1;
	gg[12] =   1;
	gg[13] =   0;
	gg[14] =   0;
	gg[15] =   0;
	gg[16] =   0;
	gg[17] =   0;
	gg[18] =   0;
	gg[19] =   0;	
	gg[20] =   0;
	gg[21] =   0;
	gg[22] =   0;
	gg[23] =   0;
	gg[24] =   0;
	gg[25] =   0;
	gg[26] =   0;
	gg[27] =   0;
	gg[28] =   0;
	gg[29] =   0;
    gg[30] =   1;


 	DecodeBCH31212(gg);
	return;
	*/
 
    int               m_kkkk  = 113;
	int                       i;
	CString            str,str1;

	read_p();               /* Read m */
	
	for(int re = 0; re <= m; re ++)
	{
		str.Format("p[%d] = %d",re,p[re]);
		WriteToLog(str);
	}

	BYTE   recdbak[1024];

	//产生伽罗瓦域GF(2**m)
	generate_gf();          
	
	str.Format("int alpha_to[%d] ={",length);

	for( re = 0; re < pow(2,m); re ++)
	{

		if(re < pow(2,m) - 1)
		{
		   str1.Format("%3d,",alpha_to[re]);
		}
		else
		{
			str1.Format("%3d};",alpha_to[re]);
		}

		//换行
		if((re + 1)%8 == 0)
		{ 
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;
	  //.Format("alpha_to[%d] = %d,index_of[%d] = %d",re,alpha_to[re],re,index_of[re]);
	
	}

	WriteToLog(str);
	

	str.Format("int index_of[%d] ={",length);

	for( re = 0; re < pow(2,m); re ++)
	{
	    if(re < pow(2,m) - 1)
		{
		   str1.Format("%3d,",index_of[re]);
		}
		else
		{
			str1.Format("%3d};",index_of[re]);
		}

		//换行
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	/*
	for( re = 0; re < pow(2,m); re ++)
	{
		str.Format("alpha_to[%d] = %d,index_of[%d] = %d",re,alpha_to[re],re,index_of[re]);
		WriteToLog(str);
	}
	*/
    
	//计算多项式
	gen_poly(); 

	str.Format("int        g[%d] ={",GetNo + 1);

	for( re = 0; re <= GetNo; re ++)
	{
	    if(re <= GetNo - 1)
		{
		   str1.Format("%3d,",g[re]);
		}
		else
		{
			str1.Format("%3d};",g[re]);
		}

		//换行
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	//随机生成数据
	srand((unsigned)time(NULL));

	str.Format("int     data[%d] ={",k);

	for( re = 0; re < k; re ++)
	{
		data[re] =  rand()%2;
	    
		if(re <  k - 1)
		{
		   str1.Format("%3d,",data[re]);
		}
		else
		{
			str1.Format("%3d};",data[re]);
		}

		//换行
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	/*
	for (i = 0; i < k; i++)
	{
		//data[i] =  rand()%2;  
        if(i < k - 1)
		{
			data[i] = 0;
		}
		else
		{
			data[i] = 1;
		}

		str.Format("data[%d] = %d",i,data[i]);
		WriteToLog(str);
	}
	*/
	
    
	//生成BCH码
	Encode_Bch();           
	
	//随机数
	for (i = 0; i < length - k; i++)
	{
		str.Format("bb[%d] = %d",i,bb[i]);
		WriteToLog(str);
	}
    
	//前面是系数
	for (i = 0; i < length - k; i++)
	{
		recd[i] = bb[i];
	}

	//后面是数据
	for (i = 0; i < k; i++)
	{
		recd[i + length - k] = data[i];
	}

	//代码多项式
	str = "代码多项式为:";
    WriteToLog(str);

	for (i = 0; i < length; i++) 
	{
		str.Format("recd[%d] = %d,",i,recd[i]);
		WriteToLog(str);
	}

//	return;
   	
	//输入错误个数
	numerr = 2;
   	
	//输入错误位置
	errpos[0] = 27;
	errpos[1] = 38;
//	errpos[2] = 23;
       	
    //测试BCH是否能用
	for(int hhhh = 0; hhhh < length; hhhh ++)
	{
		recdbak[hhhh] = recd[hhhh];
	}

	/*
	for(int kkk = 0; kkk < length; kkk ++)
	{
			
		for(int kkkj = 0; kkkj < length; kkkj ++)
		{
			
		//	for(int kkks = 0; kkks < length; kkks ++)
			{
				
				recd[kkkj]  ^=  1;
				recd[kkk]   ^=  1;
			//	recd[kkks]  ^=  1;

				//str.Format("错误位置1：%d，错误位置2：%d,错误位置3：%d",kkkj,kkk,kkks);
				str.Format("错误位置1:%d,错误位置2:%d",kkkj,kkk);
				WriteToLog(str);
				
				//解码数据
				decode_bch();
				
				WriteToLog("\r\n");
			}
			
		}

	}
	*/    

	if(numerr > 0)
	{
		for(i = 0; i < length; i ++)
		{
			recd[i] = recdbak[i];
		}		
		
		for (i = 0; i < numerr; i++)
		{
			recd[errpos[i]] ^= 1;

			str.Format("加错误位置第%d位:%d",i+1,errpos[i]);
			WriteToLog(str);
		}
		
		for( i = 0; i < length; i ++)
		{
			recdbak[i] = recd[i];
		}	

		//解码数据
		decode_bch();
		
		WriteToLog("对比结果如下:");
		
		for (i = 0; i < length; i++) 
		{

			if(recdbak[i] == recd[i])
			{
				str.Format("解前 recd[%3d] = %3d,解后 recd[%3d] = %2d",i,recdbak[i],i,recd[i]);
			}
			else
			{
				str.Format("解前 recd[%3d] = %3d,解后 recd[%3d] = %2d  《检查错位》",i,recdbak[i],i,recd[i]);
			}

			WriteToLog(str);
		}
		
	}

	/**/


	MessageBox("BCH测试结束！！","确定",MB_OK);
    return;


}

short CTTTView::GetFileEveryDataLength(CString filename)
{ 
	FILE *text;
	CString str;
	char s[120];
	
	if((text  = fopen(filename,"r"))==NULL)
	{
		return  0;
	}
	else
	{
		fgets(s,120,text);
		str = s;
		str.TrimRight();
		fclose(text);
		return str.GetLength();
	}

}

void CTTTView::OnRadio1() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table10[i];
	}
	
	//叠加数据
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}
	
	OnButtonUpdate();
	
	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("匹配角度：10度");

}

void CTTTView::OnRadio2() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table20[i];
	}
	
	//叠加数据
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}	
	
	OnButtonUpdate();

	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("匹配角度：20度");
}

void CTTTView::OnCheckDiffi2() 
{
    OnButtonUpdate();	
}

void CTTTView::OnCheckDiffi3() 
{
	OnButtonUpdate();	
}

//找匹配值最大的那个数
double CTTTView::Decode()
{	
	CString             str,signstr;
    short               Diffs[3000];
    BYTE  SignalBit[100],TempSignalBit[100],TempSignalBitbak[100],Signal[8],m_result;
	BYTE       m_PlaceDifferent[45];

	m_ReceiveStr               = "";
	BYTE                   Data[39];
	double dataValue       =      0;
	double dataValueValue  =     -1;
	double m_ppvalue       =      0;
	long   m_sums          =      0;
	double m_maxppvalue    =      0;
	short  m_pipeiplace    =      0;
  	long   m_maxpptimes    =      1;//匹配次数
	long                Diffn[1024];
	BOOL               m_checkplace;
    BYTE     m_GetOverRecords  =  0;//大于0.6的个数
	double         m_ThreePipei[150];
    BYTE         m_ByteRecords =  0;//收的字节数

	switch(m_protocol)
	{
	case 31:
		{

		}
	case 32:
		{

		}
	case 71:
		{
			
		}
	case 72:
		{

		}
	case 73:
		{
			m_ByteRecords = 63;
			break;
		}
	case 61:
		{
			m_ByteRecords = 45;
			break;
		}
	case 62:
		{
			m_ByteRecords = 90;
			break;
		}
	}

	
	//找匹配最大值
	if(m_findpipeimax)
	{
		m_maxpptimes	= WM_NUMBERS;
	}
	
	signstr.Format("===========================［解码，起始点为第%d个点］===========================",m_startpoint);
	
	m_ppvalue    =    0;
	WriteToLog(signstr);
	
	long          time0     = GetTickCount();
	double*		 m_ppresult	= new double[m_maxpptimes * m_ByteRecords];
		
   	//原始匹配波
	if (m_radio < 3)
	{
		//波形折算成位
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			
			//用相关性算法求解,3-1,4-2
			for(int i = 0;i < m_wavepoints;i ++)   
			{ 
				//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
				Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
				Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
			}
			
			//叠加数据
			for( i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//平均值
				Diffs[i]       = Diffs[i] + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
			}
		
			//匹配值
			for(int jj = 0; jj < m_maxpptimes; jj ++)
			{
				
				m_ppresult[index*m_maxpptimes + jj]   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,jj);

			}
			
			
		}
    
	}
	else
	{
		
		long    Diffs_Sums[256];
		short   Diffs_All[25600];

		WriteToLog("【自己学习解码】");
		
		for(int t = 0; t < 256; t ++)
		{
              Diffs_Sums[t]  =  0;
		}

		//自学习,波形折算成位
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			
			//用相关性算法求解,3-1,4-2
			for(int i = 0;i < m_wavepoints;i ++)   
			{ 
				//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
				Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
				Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
			}
			
			//叠加数据
			for( i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//平均值
				Diffs[i]                              = Diffs[i]      + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
			    //累加值
				Diffs_Sums[i]                         = Diffs_Sums[i] + abs(Diffs[i]);
				//差值存贮
				Diffs_All[index*(m_wavepoints/2) + i] = Diffs[i];
			}            
		
		}

		//叠加波形平均值
		for(int  i = 0;i < m_wavepoints/2;i ++)
		{
			//累加值
			SourceArrays[i]                         = short(Diffs_Sums[i]/m_ByteRecords);
		}		

		//自学习,波形折算成位
		for( index = 0; index < m_ByteRecords ;index ++)
		{
			
			//用相关性算法求解,3-1,4-2
			for(int i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//得到信号尖
				Diffs[i]  = Diffs_All[index*(m_wavepoints/2) + i];
			}
			
			//匹配值
			for(int jj = 0; jj < m_maxpptimes; jj ++)
			{				
				m_ppresult[index*m_maxpptimes + jj]   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,jj);
			}
			
			
		}

	}

	m_maxppvalue  =    0;//最大匹配值
	
	//找最大匹配值
	for(int jj = 0; jj < m_maxpptimes; jj ++)
	{
		
		m_ppvalue    =    0;//匹配值和
		
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			m_ppvalue = fabs(m_ppresult[jj + m_maxpptimes * index]) + m_ppvalue;
		}	

		//匹配值绝对值和:
		if(m_findpipeimax)
		{
			if(jj + 1 <= m_maxpptimes/2)
			{
				signstr.Format("【匹配绝对值和:%6.3f，数据左移%02d点】",m_ppvalue,int(m_maxpptimes/2 - jj));			
			}
			else if(jj + 1 > m_maxpptimes/2 + 1)
			{
				signstr.Format("【匹配绝对值和:%6.3f，数据右移%02d点】",m_ppvalue,jj - m_maxpptimes/2);
			}
			else if(jj + 1 == m_maxpptimes/2 + 1)
			{
				signstr.Format("【匹配绝对值和:%6.3f，数据没有移动】",m_ppvalue);
			}
			
		}
		else
		{
			signstr.Format("【匹配绝对值和：%6.3f】",m_ppvalue);
		}
		
		WriteToLog(signstr);
		
		
		if(m_ppvalue > m_maxppvalue)
		{
			m_maxppvalue =  m_ppvalue;//最大匹配值
			m_pipeiplace =         jj;//记住最佳匹配位置
		}
		
	}
	
	//找匹配最大值
	if(m_findpipeimax)
	{

		//匹配绝对最大值及最佳位置
		if(m_pipeiplace + 1 <= m_maxpptimes/2)
		{
			signstr.Format("\r\n【匹配绝对和最大值：%6.3f，数据左移%02d点】\r\n",m_maxppvalue,m_maxpptimes/2 - m_pipeiplace);			
		}
		else if(m_pipeiplace + 1 > m_maxpptimes/2 + 1)
		{
			signstr.Format("\r\n【匹配绝对和最大值：%6.3f，数据右移%02d点】\r\n",m_maxppvalue,m_pipeiplace - m_maxpptimes/2);
		}
		else if(m_pipeiplace + 1 == m_maxpptimes/2)
		{
			signstr.Format("\r\n【匹配绝对和最大值：%6.3f，数据没有移动】\r\n",m_maxppvalue);
		}
		
		WriteToLog(signstr);

	}
	
	
    //最佳匹配位置的数据
	for(int index = 0; index < m_ByteRecords ;index ++)
	{
		//存匹配系统
		m_ThreePipei[index] = m_ppresult[m_pipeiplace + m_maxpptimes * index];

		//匹配值和
		if(m_ppresult[m_pipeiplace + m_maxpptimes * index]  > 0)
		{
			SignalBit[index] = 0;
		}
		else 
		{
			SignalBit[index] = 1;
		}

		//匹配值大于0.6的个数
		if(fabs(m_ppresult[m_pipeiplace + m_maxpptimes * index]) > 0.65)
		{
			m_GetOverRecords ++;
		}
		
		signstr.Format(" 收到的数为：SignalBit[%2d] = %0x [%.3f]",index,SignalBit[index],m_ppresult[m_pipeiplace + m_maxpptimes * index]);
		WriteToLog(signstr);
		
		//回车行
		if((index + 1) % 8 == 0 || index == m_ByteRecords - 1)
		{
			
			if((index + 1) % 8 == 0)
			{
				
				if(SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{	
					signstr.Format(" 0x%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				
			}
			else
			{	

				BYTE   m_addValue  =    0;
 
				if(index == m_ByteRecords - 1)
				{
					BYTE        m_ttts;
					m_ttts   =  m_ByteRecords- (m_ByteRecords/8)*8;


					for(int jjj = 0; jjj < m_ttts; jjj ++)
					{
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow(2,m_ttts-1-jjj));
					
					}
				
				}

				/*
				if(SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{
					signstr.Format(" 0x%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				*/

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\n十六进制为:"+ signstr + "\r\n");
			m_ReceiveStr = m_ReceiveStr + signstr;
			
		}
		
	}
	
	delete[]   m_ppresult;

	if(m_protocol == 22)
	{		
		
		//不同的组数
		m_sums    =     0;
		dataValue =    -1;
		
		/*********顺序调整，如果是22协议的话*/
		for(short i = 0; i <  31; i ++)
		{

			//对比两次接收到的数据
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{

				//记住不同的位置
				if(m_sums <= m_derrors)
				{
					m_PlaceDifferent[m_sums] = i;
				}
							
				m_sums ++;
			}
			
		}
		
		str.Format("  对位错(%d)",m_sums);
		WriteToLog(str);

		//如果有5组数不相同的话
		if(m_sums > m_derrors)
		{	
			m_ReceiveStr = m_ReceiveStr + str;
			return -1;
		}
		else
		{
	        WriteToLog("22协议解码如下:\r\n");
		}
        
		str.Format("对位错［%d］",m_sums);
		m_ReceiveStr    =             str;

		//数据叠加再处理,解码10度和5度角,用的是新协议,前1024个点是空的,波形折算成位
		BYTE              DJSignalBit[32];

		for(index = 0; index < 32 ;index ++)
		{

			if(index < 31)
			{
				
				//用相关性算法求解,3-1,4-2
				for(int i = 0;i < 512;i ++)   
				{ 
					//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
					Diffs[i]        = DataBuf[(2*index * 4 + 2) * 512 + i + 1024] - DataBuf[ 2*index * 4 *  512 + i  + 1024];
					Diffs[512 + i]  = DataBuf[(2*index * 4 + 3) * 512 + i + 1024] - DataBuf[(2*index * 4 + 1) * 512 + i + 1024];
					
					//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
					Diffn[i]        = DataBuf[((2*index + 1) * 4 + 2) * 512 + i + 1024] - DataBuf[(2*index + 1) * 4      *  512 + i  + 1024];
					Diffn[512 + i]  = DataBuf[((2*index + 1) * 4 + 3) * 512 + i + 1024] - DataBuf[((2*index +1) * 4 + 1) *  512 + i  + 1024];
				}
				
				//叠加数据
				for( i = 0;i < 256;i ++)   
				{ 
					//0和31叠加，1和32叠加
					Diffs[i]   = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,m_pipeiplace);
				
				//存匹配系统
		        m_ThreePipei[62 + index] = m_ppvalue;

				if(m_ppvalue  > 0)
				{
					DJSignalBit[index] = 0;
				}
				else 
				{
					DJSignalBit[index] = 1;
				} 

			}
			else
			{

               DJSignalBit[31] = 0;
			
			}
			
			str.Format("DJSignalBit[%d] = %d [%.3f]",index,DJSignalBit[index],m_ppvalue);
			WriteToLog(str);
						
			if((index + 1) % 8 == 0)
			{
				
				m_result = DJSignalBit[index - 7] * 128 + DJSignalBit[index - 6] * 64 + DJSignalBit[index - 5]* 32 + DJSignalBit[index - 4] * 16  + DJSignalBit[index - 3] * 8 + DJSignalBit[index - 2] * 4 + DJSignalBit[index - 1] * 2  + DJSignalBit[index];

				if(m_result < 16)
				{
					signstr.Format(" 0x0%0x  ",m_result);
				}
				else
				{
					signstr.Format(" 0x%0x  ",m_result);
				}	
				
				WriteToLog("\r\n十六进制为:"+ signstr + "\r\n");

			    m_ReceiveStr = m_ReceiveStr + signstr;
				
			}
			
		}

		WriteToLog(" 序号         原匹配值         重发匹配值           叠加匹配值");

		for(index = 0; index < 31 ;index ++)
		{

			str.Format(" %2d      %12.3f      %12.3f         %12.3f ",index,m_ThreePipei[2*index],m_ThreePipei[2*index + 1],m_ThreePipei[62 + index]);
            WriteToLog(str);
		}
		
		WriteToLog("\r\n");

		//倒数
		for( i = 0; i <  31; i ++)
		{
			//31,21,2
			TempSignalBit[i]        = DJSignalBit[i];
			
			if( i < 10 )
			{
				TempSignalBit[i]    = DJSignalBit[9 - i];
			}
			else
			{
				TempSignalBit[i]    = DJSignalBit[30 - i + 10];
			}

		}
	
		
		//纠码个数
		m_CollectNos    =   10;
			
		//31212解码
		if(DecodeBCH31212(TempSignalBit))
		{
			   
			signstr.Format(" 纠［%d］匹值>0.65［%d］个",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
			
			
			//对一下纠的位,如果有纠码的位
			if(m_CollectNos > 0)
			{
				
				m_checkplace  =    FALSE;
				
				//对位算法,查纠的位是否是在不同的位置中
				for(int i = 0; i < m_CollectNos;i ++)
				{
					
					m_checkplace  = FALSE;
					
					//有几个错
					for(int j = 0; j < m_sums; j++)
					{
						
						if(m_PlaceDifferent[j] == m_CollectPlace[i])
						{
							m_checkplace = TRUE;
							break;
						}
						
					}

					
					if(!m_checkplace)
					{
						signstr.Format("  ＊[%d]",m_CollectPlace[i]);
						m_ReceiveStr = m_ReceiveStr + signstr;
					}
					
				}
				
			}
			

			//从10-30为数据位低->高发展，回的数为16进制
			//电流  0～30A
			//电压  0～300V
		    //送电成功0x33
			//电表故障 21全为1(111111111111111111111)，正常的数最低位为********************0
            //驻留没有驻留上  (000000000000000000001)  20个0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;

			signstr.TrimLeft();
			signstr.TrimRight();
						
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}
		
			//16进制
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(TempSignalBit[10 + i]*pow(2,i));
			}
			
			//电流、电压为
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{



				
			}
   	
		
		}
		else
		{
			
			signstr.Format("  ［纠码错误］匹值>0.65有［%d］个",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
		}
		
		////////////////////////////////////////////////////////
		CString              Strtemp1,Strtemp2,Strtemp3,Strtemp4,Strtemp5;
		Strtemp1             =  Strtemp2   =   Strtemp3= Strtemp4 = Strtemp5     = "";
		BYTE     m_GetNumber1,m_GetNumber2,m_GetNumber3,m_GetNumber4,m_GetNumber5;
		m_GetNumber1 = m_GetNumber2 = m_GetNumber3  = m_GetNumber4 = m_GetNumber5 = 0;
	
        //纠码结果
		BYTE     JM[31]; 

		//又开始倒纠码结果
		for( i = 0; i <  31; i ++)
		{
			if( i < 10 )
			{
				JM[i]    = TempSignalBit[9 - i];
			}
			else
			{
				JM[i]    = TempSignalBit[30 - i + 10];
			}
			
		}
		
		//Strtemp1前31个数,Strtemp2后31个数,Strtemp3为解码后的31个数
		Strtemp1  = "第一次31个数:";
		Strtemp2  = "重发的31个数:";
		Strtemp3  = "叠加后31个数:";				
		Strtemp4  = "纠码后31个数:";

		//和原始数据对比
		for( i = 0; i <  31; i ++)
		{
			
			//第一次31个数
			if(SignalBit[2*i] == 0)
			{
				Strtemp1 = Strtemp1 + " 0";
			}
			else
			{
				Strtemp1 = Strtemp1 + " 1";
			}
			
			//重发的31个数
			if(SignalBit[2*i+1] == 0)
			{
				Strtemp2 = Strtemp2 + " 0";
			}
			else
			{
				Strtemp2 = Strtemp2 + " 1";
			}
			
			//叠加后31个数
			if(DJSignalBit[i] == 0)
			{
				Strtemp3 = Strtemp3 + " 0";
			}
			else
			{
				Strtemp3 = Strtemp3 + " 1";
			}
			
			//纠码后31个数
			if( JM[i] == 0)
			{
				Strtemp4 = Strtemp4 + " 0";
			}
			else
			{
				Strtemp4 = Strtemp4 + " 1";
			}
			
			
			//对比两次接收到的数据
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{					
				m_GetNumber1 ++;
			}	
			
			//对比叠加后和第一次的数据	
			if(SignalBit[2*i]    != DJSignalBit[i])
			{
				m_GetNumber2++;
			}
			
			//对比叠加后和第二次的数据	
			if(SignalBit[2*i + 1] != DJSignalBit[i])
			{
				m_GetNumber3++;
			}
			
			//对比纠码后和第一次的数据	
			if(SignalBit[2*i]  != JM[i])
			{
				m_GetNumber4++;
			}
			
			//对比纠码后和第二次的数据	
			if(SignalBit[2*i + 1] != JM[i])
			{
				m_GetNumber5++;
			}
			
		}
		
		if(dataValue >= 0)
		{
			Strtemp5.Format("对比结果如下：\r\n两次接收到的数据不同个数:%d\r\n叠加后和第一次不同个数:%d,叠加后和第二次不同个数:%d\r\n纠码后和第一次不同个数:%d,纠码后和第二次不同个数:%d,纠码个数:%d",m_GetNumber1,m_GetNumber2,m_GetNumber3,m_GetNumber4,m_GetNumber5,m_CollectNos);
			WriteToLog(Strtemp1+ "\r\n" + Strtemp2 + "\r\n" + Strtemp3 + "\r\n" + Strtemp4 + "\r\n" + Strtemp5 + "\r\n" );
		}
		else
		{
			Strtemp5.Format("对比结果如下：\r\n两次接收到的数据不同个数:%d\r\n叠加后和第一次不同个数:%d,叠加后和第二次不同个数:%d\r\n",m_GetNumber1,m_GetNumber2,m_GetNumber3);
			WriteToLog(Strtemp1+ "\r\n" + Strtemp2 + "\r\n" + Strtemp3 + "\r\n" + Strtemp5 + "\r\n" );
		}

		
		////////////////////////////////////////////////////////
	
		//31212解码
		if(dataValue >= 0)
		{
			//正确的话
			Beep(5000,400); 
			return dataValue/10;
		}

	}
	else if(m_protocol == 61)
	{

		//61协议,倒数
		for(int i = 0; i <  45; i ++)
		{
			
			//45,27,3
			if( i < 18 )
			{
				TempSignalBit[i]    = SignalBit[17 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[44 - i + 18];
			}
			
		}
		
		
		//纠码个数
		m_CollectNos    =   10;
		
		//45273解码
		if(DecodeBCH45273(TempSignalBit))
		{
			
			signstr.Format(" 纠［%d］匹值>0.65［%d］个",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
				
			//61协议,倒回原来的数
			for(int i = 0; i <  45; i ++)
			{
				
				//45,27,3
				if( i < 18 )
				{
					SignalBit[i]    =  TempSignalBit[17 - i];
				}
				else
				{
					SignalBit[i]    =  TempSignalBit[44 - i + 18];
				}
				
			}

			//16进制
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			}		
						
			m_sums     =      0;
			
			//7位一检验和
			for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			{
				
				//数据位变成字节,7位一检验和 
				for( i = 0;i < 7; i ++)
				{  	
					
					m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					
				}
				
			}
			
			//检验和是否相同
			if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			{
				
				//45273解码
				if(dataValue >= 0)
				{
					//正确的话
					Beep(5000,400); 
					return dataValue/10;
				}
				
			}
			else
			{
				//检验和不对
				str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				WriteToLog(str);
				return       -1;
			}
			
			//从10-30为数据位低->高发展，回的数为16进制
			//电流  0～30A
			//电压  0～300V
			//送电成功0x33
			//电表故障 21全为1(111111111111111111111)，正常的数最低位为********************0
            //驻留没有驻留上  (000000000000000000001)  20个0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;
			
			signstr.TrimLeft();
			signstr.TrimRight();
			
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}
			
			//电流、电压为
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{
				
				
				
				
			}
			
		}
		else
		{
			
			signstr.Format("  ［纠码错误］匹值>0.65有［%d］个",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
			return -1;
		}
		
		
		
	}
	else if(m_protocol == 62)
	{	
		//62协议,不同的组数
		m_sums    =     0;
		dataValue =    -1;
		
		/*********顺序调整，如果是22协议的话*/
		for(short i = 0; i <  45; i ++)
		{

			//对比两次接收到的数据
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{

				//记住不同的位置
				if(m_sums <= m_derrors)
				{
					m_PlaceDifferent[m_sums] = i;
				}
							
				m_sums ++;
			}
			
		}
		
		str.Format("  对位错［%d］",m_sums);
		WriteToLog(str);

		m_ReceiveStr    =             str;

		//数据叠加再处理,解码10度和5度角,用的是新协议,前1024个点是空的,波形折算成位
		BYTE              DJSignalBit[48];

		for(index = 0; index < 48 ;index ++)
		{

			if(index < 45)
			{
				
				//用相关性算法求解,3-1,4-2
				for(int i = 0;i < 512;i ++)   
				{ 
					//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
					Diffs[i]        = DataBuf[(2*index * 4 + 2) * 512 + i + 1024] - DataBuf[ 2*index * 4 *  512 + i  + 1024];
					Diffs[512 + i]  = DataBuf[(2*index * 4 + 3) * 512 + i + 1024] - DataBuf[(2*index * 4 + 1) * 512 + i + 1024];
					
					//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
					Diffn[i]        = DataBuf[((2*index + 1) * 4 + 2) * 512 + i + 1024] - DataBuf[(2*index + 1) * 4      *  512 + i  + 1024];
					Diffn[512 + i]  = DataBuf[((2*index + 1) * 4 + 3) * 512 + i + 1024] - DataBuf[((2*index +1) * 4 + 1) *  512 + i  + 1024];
				}
				
				//叠加数据
				for( i = 0;i < 256;i ++)   
				{ 
					//0和31叠加，1和32叠加
					Diffs[i]   = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,m_pipeiplace);
				
				//存匹配系统
		        m_ThreePipei[90 + index] = m_ppvalue;

				if(m_ppvalue  > 0)
				{
					DJSignalBit[index] = 0;
				}
				else 
				{
					DJSignalBit[index] = 1;
				} 
				
				str.Format("DJSignalBit[%d] = %d [%.3f]",index,DJSignalBit[index],m_ppvalue);
			    WriteToLog(str);

			}
			else
			{

               DJSignalBit[index] = 0;
			
			}
			
		
						
			if((index + 1) % 8 == 0)
			{
				
				m_result = DJSignalBit[index - 7] * 128 + DJSignalBit[index - 6] * 64 + DJSignalBit[index - 5]* 32 + DJSignalBit[index - 4] * 16  + DJSignalBit[index - 3] * 8 + DJSignalBit[index - 2] * 4 + DJSignalBit[index - 1] * 2  + DJSignalBit[index];

				if(m_result < 16)
				{
					signstr.Format(" 0x0%0x  ",m_result);
				}
				else
				{
					signstr.Format(" 0x%0x  ",m_result);
				}
				
				if((index + 1)/8 == 6)
				{

					if((m_result>>3) < 16)
					{
						signstr.Format(" 0x0%0x  ",(m_result>>3));
					}
					else
					{
						signstr.Format(" 0x%0x  ",(m_result>>3));
					}
					
				}
				
				WriteToLog("\r\n十六进制为:"+ signstr + "\r\n");

			    m_ReceiveStr = m_ReceiveStr + signstr;
				
			}
			
		}

		WriteToLog(" 序号         原匹配值         重发匹配值           叠加匹配值");

		for(index = 0; index < 45 ;index ++)
		{

			str.Format(" %2d      %12.3f      %12.3f         %12.3f ",index,m_ThreePipei[2*index],m_ThreePipei[2*index + 1],m_ThreePipei[90 + index]);
            WriteToLog(str);
		}
		
		WriteToLog("\r\n");

		//倒数
		for( i = 0; i <  45; i ++)
		{
			//45,27,3
			TempSignalBit[i]        = DJSignalBit[i];
			
			if( i < 18 )
			{
				TempSignalBit[i]    = DJSignalBit[17 - i];
			}
			else
			{
				TempSignalBit[i]    = DJSignalBit[44 - i + 18];
			}

		}
	
		
		//纠码个数
		m_CollectNos    =   10;
			
		//45273解码
		if(DecodeBCH45273(TempSignalBit))
		{
			   
			signstr.Format(" 纠［%d］匹值>0.65［%d］个",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
			
			//62协议,倒回原来的数
			for(int i = 0; i <  45; i ++)
			{
				
				//45,27,3
				if( i < 18 )
				{
					SignalBit[i]    =  TempSignalBit[17 - i];
				}
				else
				{
					SignalBit[i]    =  TempSignalBit[44 - i + 18];
				}
				
			}

			//16进制
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			}		
						
			m_sums     =      0;
			
			//7位一检验和
			for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			{
				
				//数据位变成字节,7位一检验和 
				for( i = 0;i < 7; i ++)
				{  	
					
					m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					
				}
				
			}
			
			//检验和是否相同
			if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			{
				
				//45273解码
				if(dataValue >= 0)
				{
					//正确的话
					Beep(5000,400); 
					return dataValue/10;
				}
				
			}
			else
			{
				//检验和不对
				str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				WriteToLog(str);
				return       -1;
			}

			//从10-30为数据位低->高发展，回的数为16进制
			//电流  0～30A
			//电压  0～300V
		    //送电成功0x33
			//电表故障 21全为1(111111111111111111111)，正常的数最低位为********************0
            //驻留没有驻留上  (000000000000000000001)  20个0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;

			signstr.TrimLeft();
			signstr.TrimRight();
						
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}

			//电流、电压为
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{



				
			}
		
		}
		else
		{
			
			signstr.Format("  ［纠码错误］匹值>0.65有［%d］个",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
			return -1;
		}
    
    }
	else
	{
		
		//顺序调整
		for(int i = 0; i <  63; i ++)
		{
			
			if( i < 24)
			{
				TempSignalBit[i]    = SignalBit[23 - i];
				TempSignalBitbak[i] = SignalBit[23 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[62 - i + 24];
				TempSignalBitbak[i] = SignalBit[62 - i + 24];
			}
			
		}
		
		long time1 = GetTickCount();
		signstr.Format("【匹配所耗时间：%6d】",time1 - time0);
		WriteToLog(signstr);
		
		
		//对收到的数纠码
		if(DecodeBCH63394(TempSignalBit))//纠码对的话
		{
			
			dataValue =    0;
			
			for( i = 0; i < 39; i++)
			{
				//数据又倒过来
				Data[i] = TempSignalBit[62 - i];
			}	
			
			//回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好， "电表故障1"
			//回的值为AAAAAA.AA,扩展模块的表没有连好，           "电表故障2"
			m_sums     =      0;
			
			//数据位变成字节 
			for( i = 0;i < 8; i ++)
			{  	
				//解出数据
				Signal[i] = Data[i * 4] * 8 + Data[i * 4 + 1] * 4 + Data[i * 4 + 2] * 2 + Data[i * 4 + 3] ;
				dataValue = dataValue + Signal[i] * 100000.0/pow(10,i);
				
				//检验和相加
				if((i + 1)%2 != 0)
				{
					m_sums  = m_sums  + Signal[i]*16;
				}
				else
				{		
					m_sums  = m_sums  + Signal[i];
				}
				
			}
			
			if(m_sums%128 != Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			{
				CString                      str;
				str.Format("%0x,%0x",m_sums%128,Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38]);
				WriteToLog(str + "校验和不对！");
			}
			
			//下结论
			if( Signal[0] == 0x0f && Signal[1] == 0x0e && Signal[2] == 0x0f && Signal[3] == 0x0e && Signal[4] == 0x0f && Signal[5] == 0x0e && Signal[6] == 0x0f && Signal[7] == 0x0e)
			{
				Beep(5000,400); 
				//电表故障1
				WriteToLog("电表故障1");
			}
			else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a)
			{
				Beep(5000,400); 
				//电表故障2
				WriteToLog("电表故障2");
			}
			else if( Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			{
				//读驻留时模块没有收到过驻留命令回的数
				Beep(5000,400); 
				//模块没有收到过驻留命令
				WriteToLog("模块没有收到过驻留命令");
				
			}	
			else if(Signal[0] > 9 || Signal[1] > 9 || Signal[2] > 9 || Signal[3] > 9 || Signal[4] > 9 || Signal[5] > 9 || Signal[6] > 9 || Signal[7] > 9)
			{
				dataValue =   -1;
			}
			
			dataValueValue =    dataValue;
		}

	}
	
	if(dataValueValue > -1)
	{
		//正确的话
		Beep(5000,400); 
	}

	return dataValueValue;
}

void CTTTView::OnRadio3() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table05[i];
	}
	
	//叠加数据
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}
	
	OnButtonUpdate();

	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("匹配角度：5度");
	
}


void CTTTView::OnCheck9() 
{
	UpdateData();
}

void CTTTView::OnTestdata() 
{
	CTestDlg DLG;
	DLG.DoModal();
}

void CTTTView::OnChangeStartpoint() 
{
//	UpdateData();
//	OnButtonUpdate();
}

void CTTTView::OnChangeWavepoints() 
{
	//g_Extend = DISPWINWIDTH/(float)PointsNum;
}

void CTTTView::OnCheck11() 
{
	UpdateData();
    
	if(m_quancai)
	{
		m_Spinstart.SetPos(1860);
		m_SpinAverage.SetPos(999);
	}
	else
	{
		m_Spinstart.SetPos(1024);
		m_SpinAverage.SetPos(512);
	}
	
	m_startpoint  =  m_Spinstart.GetPos();
	m_wavepoints  =  m_SpinAverage.GetPos();

	OnRadio1();
	
	if(m_wavepoints/2 > 256)
	{
		
		for(int  i = m_wavepoints/2 ; i >= 0; i --)   
		{ 
			if((255 - (m_wavepoints/2 - i)) >= 0)
			{
				m_ppwave[i]  = m_ppwave[255 - (m_wavepoints/2 - i)];
			}
			else
			{
				m_ppwave[i]  =  0;
			}
			
		}
		
	}

	UpdateData(FALSE);
    OnButtonUpdate();
	
}

void CTTTView::OnOutofmemorySpinstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//AfxMessageBox("error!");
	*pResult = 0;
}

void CTTTView::OnDeltaposSpinstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    UpdateData();

	OnButtonUpdate();
	*pResult = 0;
}

void CTTTView::OnDeltaposSpinaverage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	UpdateData();

	OnRadio1();

	if(m_wavepoints/2 > 256)
	{
		
		for(int  i = m_wavepoints/2 ; i >= 0; i --)   
		{ 
		
			if((255 - (m_wavepoints/2 - i)) >= 0)
			{
				m_ppwave[i]  = m_ppwave[255 - (m_wavepoints/2 - i)];
			}
			else
			{
				m_ppwave[i]  =  0;
				
			}

		}
		
	}

	OnButtonUpdate();	
	
	*pResult = 0;
}


//找过零点
void CTTTView::OnFindzero() 
{
	
	short   m_BeginValue  =    10;//以10为基点
	short   m_RangeValue  =    30;//找50个点中有
	short   m_rumbers     =     0;//
	CString                   str;
	BOOL    m_ready      =  FALSE;
    
	str.Format("DataLen = %d",DataLen);
	WriteToLog(str);

	for(int i = 0 ; i < DataLen - m_RangeValue; i ++)
	{
         
		
		if( DataBuf[i] <= m_BeginValue && DataBuf[i] >= 0)
		{
            
			//找最小点
    		m_rumbers    =          0;	
			
			//找后10个数
			for(int j = i + 1; j < i + 11; j ++)
			{ 
				//大于0或比前一个数要大
				if(DataBuf[j] > DataBuf[i] || DataBuf[j] >= 0 )
				{		
					m_rumbers ++;
				}
				
			}	

			//如果小于1个
			if(m_rumbers  < 1)
			{
				m_ready      =       TRUE;
				m_BeginValue = DataBuf[i];
			}
		
		}

		 //如果准备好了
		 if(m_ready)
		 {
		
			 m_rumbers = 0;
			 
			 for(int j = i + 1 ; j < i + m_RangeValue; j ++)
			 {
				 //数够数
				 if(DataBuf[j] < m_BeginValue)
				 {
					 m_rumbers ++;
				 }
				 
			 }
			 
			 //有80％的点小于其的话
			 if(m_rumbers*1.000/m_RangeValue > 0.8)
			 {
				 str.Format("过零点位置为%d",i + 1);
				 WriteToLog(str);
				 i =  i + m_RangeValue;
			 }

			 m_ready      = FALSE;
			 m_BeginValue =    10;
		 }
	
	}

	MessageBox("找零点过程完毕！"," ",MB_OK);


	/*
	UINT CntPoint = 0,CntCycle =     0;
	UINT temp,CurZeroPoint     =     0;
	BOOL bReady                = FALSE;
	
    do{
       	temp = DataBuf[CntPoint++];

		if(temp > m_maxDecimalVal/2 - 1)
		{ 
			if(CntPoint > CurZeroPoint + 100)
			{
				bReady = TRUE; 
			}
		}
		else
		{			
			if(bReady)
			{
				
				if(DataBuf[CntPoint+100] < m_maxDecimalVal/2)
				{  
					CurZeroPoint= CntPoint;
					bReady      = FALSE; 
					CntCycle++;
				}

			}
			
		}
		
	}while(CntCycle < WaveNum + 1);
	
	return CntPoint-1;
	*/
}

//是1的波叠加在一起,是0的波叠加在一起
void CTTTView::AllWaveAdd()
{	
    short               Diffs[3000];
	double m_ppvalue       =      0;
	CString                     str;

	for(int i = 0; i < 10000; i++)
	{
		m_ppAllWave[i] = 0;
	}
	
	//波形折算成位
	for(int index = 0; index < 63 ;index ++)
	{
		
		//用相关性算法求解,3-1,4-2
		for(int i = 0;i < m_wavepoints;i ++)   
		{ 
			//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
			Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
			Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
		}
		
		//叠加数据
		for( i = 0;i < m_wavepoints/2;i ++)   
		{ 
			//平均值
			Diffs[i]  = Diffs[i] + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
		}
	
		//匹配值
		m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
		
		//pr[n]——输入的实部
		//pi[n]——数入的虚部
		//n，k——满足n=2^k
		//fr[n]——输出的实部
		//fi[n]——输出的虚部
		//l——0 FFT，1 IFFT
		//il——0 输出按实部/虚部；1 输出按模/幅角		  
		//kkfft(double pr[],double pi[],int n,int k,double fr[],double fi[],int l,int il);
		
		// 入口参数： 
		// l: l = 0, 傅立叶变换; l = 1, 逆傅立叶变换
		// il: il = 0,不计算傅立叶变换或逆变换模和幅角；il = 1,计算模和幅角
		// n: 输入的点数，为偶数，一般为32，64，128，...,1024等
		// k: 满足n=2^k(k>0),实质上k是n个采样数据可以分解为偶次幂和奇次幂的次数
		// pr[]: l=0时，存放N点采样数据的实部
		// l=1时, 存放傅立叶变换的N个实部
		// pi[]: l=0时，存放N点采样数据的虚部 
		// l=1时, 存放傅立叶变换的N个虚部
	
		// 出口参数：
		// fr[]: l=0, 返回傅立叶变换的实部
		// l=1, 返回逆傅立叶变换的实部
		// fi[]: l=0, 返回傅立叶变换的虚部

		// l=1, 返回逆傅立叶变换的虚部
		// pr[]: il = 1,i = 0 时，返回傅立叶变换的模
		// il = 1,i = 1 时，返回逆傅立叶变换的模
		// pi[]: il = 1,i = 0 时，返回傅立叶变换的辐角
		// il = 1,i = 1 时，返回逆傅立叶变换的辐角


		/*
		if(m_wavepoints == 512)
		{
			double pr[256],pi[256],fr[256],fi[256];
			
			for(i = 0; i <  256; i ++)
			{
				
				
				if( i < 256 - m_iBandPassPoints)
				{
					pr[i] =  0;
				}
				else
				{
					pr[i] = double(Diffs[i]);
				}

				pi[i] = 0;
				fr[i] = 0;
				fi[i] = 0;
			}

		    kkfft(pr,pi,256,8,fr,fi,0,1);
			
			for(i = 0; i <  256; i ++)
			{
				str.Format("pr[%3d]=%13.3f,pi[%3d]=%13.3f,fr[%3d]=%13.3f,fi[%3d]=%13.3f",i,pr[i],i,pi[i],i,fr[i],i,fi[i]);
				//str.Format("pr[%3d]=%13.3f, pi[%3d]=%13.3f",i,fr[i],i,fr[i]);
				//str.Format("fr[%3d]=%13.3f, fi[%3d]=%13.3f",i,fr[i],i,fi[i]);
				WriteToLog(str);
			}

		}
		*/

		for( i = 0; i < m_wavepoints/2; i ++)
		{
			if(m_ppvalue > 0)
			{
				m_ppAllWave[i] = m_ppAllWave[i] + Diffs[i];
			}
			else
			{
				m_ppAllWave[m_wavepoints/2 + i] = m_ppAllWave[m_wavepoints/2 + i] + Diffs[i];
			}
			
		}

		
	}
	
	/*
	//叠加波处理
	for( i = 0; i < m_wavepoints/2; i ++)
	{
		//向上的叠加波
		Diffs[i] = m_ppAllWave[i];
	}
	
	//匹配值
	m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
    str.Format("向上的叠加波匹配值:%.2f",m_ppvalue);
	WriteToLog(str);

	
	for( i = 0; i < m_wavepoints/2; i ++)
	{
		//向上的叠加波
		Diffs[i] = m_ppAllWave[m_wavepoints/2 + i];
	}
	
	//匹配值
	m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
    str.Format("向下的叠加波匹配值:%.2f",m_ppvalue);
    WriteToLog(str);


	CString   str;

	//叠加波形
	for( i = 0; i < m_wavepoints/2; i ++)
	{

		if(m_ppAllWave[i] > 0)
		{
            str.Format("%5d",m_ppAllWave[i]);
		}
		else
		{
			str.Format("%5d",0);
		}

	    WriteToLog(str);
	}
	*/

}




void CTTTView::OnAlladd() 
{
	UpdateData(TRUE);

	/*
	//所有波叠加
	if(m_AllAdd)
	{
		//是1的波叠加在一起,是0的波叠加在一起
		AllWaveAdd();
	}
	*/
	
	OnButtonUpdate();
	
}

void CTTTView::OnChangeAlltimes() 
{
	UpdateData();
	OnButtonUpdate();
	
}

void CTTTView::OnInitialize() 
{
	UpdateData(TRUE);
    CString    ComStr;
	int k      =    0;

	if(m_comboport.GetCurSel() != CB_ERR)
	{
		//索引号从0开始的
		m_comboport.GetLBText(m_comboport.GetCurSel(), ComStr);
	}
	else
	{
		MessageBox("串口选择错误！","警告",MB_OK|MB_ICONWARNING);
		return;
	} 
	
	k = ComStr.Find("M");
	if(k != -1)
	{
		k = atoi(ComStr.Right(ComStr.GetLength()- k - 1));
	}
	else
	{
		MessageBox("串口选择错误！","警告",MB_OK|MB_ICONWARNING);
		return;
	}


	//串口
	//串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
	//设置各种参数m_comboport.GetCurSel()
	OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
	MessageBox("串口初始化成功！"," ",MB_OK|MB_ICONINFORMATION);
}


/***************************************************************
串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
波特率 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
检验位 0-无校验,1－奇校验,2－偶校验
数据位 0-4     ,1-5      ,2-6      ,3-7    ,4-8
停止位 0-1     ,1-1.5    ,2-2
//二进制方式传送
**************************************************************/
void CTTTView::OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex)
{
    m_StatusStr = "";
	
	CString SpeedIndexstr;
    CString CheckIndexstr;
    CString  DataIndexstr;
	CString  StopIndexstr;
	CString  ParameterStr;
	
	//波特率 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000
	switch(SpeedIndex)
	{
	case 0:
		{
			SpeedIndexstr = "600";
			break;
		}
	case 1:
		{
			SpeedIndexstr = "1200";
			break;
		}
	case 2:
		{
			SpeedIndexstr = "2400";
			break;
		}
	case 3:
		{
			SpeedIndexstr = "4800";
			break;
		}
	case 4:
		{
			SpeedIndexstr = "9600";
			break;
		}
	case 5:
		{
			SpeedIndexstr = "14400";
			break;
		}
	case 6:
		{
			SpeedIndexstr = "19200";
			break;
		}
	case 7:
		{
			SpeedIndexstr = "28800";
			break;
		}
	case 8:
		{
			SpeedIndexstr = "38400";
			break;
		}	
	case 9:
		{
			SpeedIndexstr = "56000";
			break;
		}
	case 10:
		{
			SpeedIndexstr = "128000";
			break;
		}
	case 11:
		{
			SpeedIndexstr = "256000";
			break;
		}	
		
	}
	
	//检验位 0-无校验,1－奇校验,2－偶校验
	switch(CheckIndex)
	{
	case 0:
		{
			//0-无校验
			CheckIndexstr = "N";
			break;
		}
	case 1:
		{
			//1－奇校验
			CheckIndexstr = "O";
			break;
		}
	case 2:
		{
			//2－偶校验
			CheckIndexstr = "E";
			break;
		}
	}
	
	//数据位 0-4     ,1-5      ,2-6      ,3-7    ,4-8
	switch(DataIndex)
	{
	case 0:
		{
			DataIndexstr = "4";
			break;
		}
	case 1:
		{
			DataIndexstr = "5";
			break;
		}
	case 2:
		{
			DataIndexstr = "6";
			break;
		}
	case 3:
		{
			DataIndexstr = "7";
			break;
		}
	case 4:
		{
			DataIndexstr = "8";
			break;
		}
	}
    
	//StopIndexstr;停止位 0-1     ,1-1.5    ,2-2
	switch(StopIndex)
	{
	case 0:
		{
			StopIndexstr = "1";
			break;
		}
	case 1:
		{
			StopIndexstr = "1.5";//"1.5",只有数据位为5时用;
			break;
		}
	case 2:
		{
			StopIndexstr = "2";
			break;
		}
		
	}
	
	if(m_Com.GetPortOpen()) //打开串口   
	{
		m_Com.SetPortOpen(FALSE);
	}
	

	m_Com.SetCommPort(ComIndex + 1); //选择COM,从0开始
    m_Com.SetInBufferSize(1024);     //设置输入缓冲区的大小，Bytes
	m_Com.SetOutBufferSize(512);     //设置输出缓冲区的大小，Bytes
	
    //打开端口
	m_Com.SetPortOpen(TRUE);

	m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加

	m_Com.SetInputMode(1);//0 文本形式 1二进制形式

    //设置波特率 ，检验位 ，数据位 ，停止位	
	ParameterStr.Format("%s,%s,%s,%s",SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);
    
	m_Com.SetSettings(ParameterStr);//"600,n,8,1"
	m_Com.SetRThreshold(1);//每接收1个字符就触发1次接收事件
	m_Com.SetInputLen(0);  //每次读取一个字符,二进制形式
	m_Com.GetInput();      //清除原有的数据
		
	ParameterStr.Format("串口初始化成功【COM%d,%s,%s,%s,%s】",ComIndex+1,SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);
    m_StatusStr = ParameterStr;

	status(ParameterStr);
	
}


//检测有几个端口能用
void CTTTView::GetComPorts()
{
	HANDLE				m_hComm;
    CString             ComStr;
	m_comboport.ResetContent();

	for(int i = 0; i < 10; i ++)
	{
		
		ComStr.Format("COM%d",i + 1);
		
		// get a handle to the port
		m_hComm = CreateFile(ComStr,		// communication port string (COMX)
			GENERIC_READ | GENERIC_WRITE,	// read/write types
			0,								// comm devices must be opened with exclusive access
			NULL,							// no security attributes
			OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
			FILE_FLAG_OVERLAPPED,			// Async I/O
			0);							    // template must be 0 for comm devices
		
		if (m_hComm != INVALID_HANDLE_VALUE)
		{
			m_comboport.AddString(ComStr);
			CloseHandle(m_hComm);
		}
		
	}

	if(m_comboport.GetCount() > 0)
	{
		m_comboport.SetCurSel(0);
		m_combobit.SetCurSel(4);
		m_comcheck.SetCurSel(0);
		m_comdata.SetCurSel(4);
		m_comstop.SetCurSel(0);	
		
		//设置各种参数m_comboport.GetCurSel()
	    OptionClick(m_comboport.GetCurSel(),m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
	
	}
	
}


//状态栏上显示信息
void CTTTView::status(CString strname)
{
	CStatusBar*          pStatus;
	pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	
	if (pStatus)
	{
		pStatus->SetPaneText(0,strname);
	}
	
}

void CTTTView::OnComset() 
{
	m_TestPhase = FALSE;

	UpdateData();
	
	if(m_module > 1638415)
	{
		m_module = 1638301;
		UpdateData(FALSE);
	}
	
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_SHOW);	

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE); 
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);

	GetDlgItem(IDC_REAL_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_REAL_START)->SetWindowText("发送");
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
    GetDlgItem(IDC_SETTIMER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECODE)->EnableWindow(FALSE);

	GetDlgItem(IDC_REAL_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	GetDlgItem(IDC_READLINE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_ORDER)->SetWindowText("03");

	OnSelchangeProtocols(); 
}

//向串口发送数据
void CTTTView::SendByteArrayToCom()
{
	//发送数组时用
	if(m_Com.GetPortOpen())
	{
		CString  str,str1;
		str      =     "";

		for(int i = 0; i < SendByteArray.GetSize(); i ++)
		{	
			
			
			if(SendByteArray[i] > 15)
			{
				str1.Format(" 0x%0x ",SendByteArray[i]);
			}
			else
			{
				str1.Format(" 0x0%0x ",SendByteArray[i]);
			}

			/*
			if(i == 0)
			{
				//AfxMessageBox(str);
				str1.TrimLeft();
				str1.TrimRight();
				str = str + str1;
			}
			else
			{*/
				
				if(i == 4 || i == 13)
				{
					str = str + str1 + "   ";
				}
				else
				{
					str = str + str1;
				}
		//	}
		
		}

		CWnd* pt = GetDlgItem(IDC_SENDORDER);
		pt->SetWindowText(str);
		
		UpdateData(TRUE);
        UpdateData(FALSE);

		m_Com.GetInput();
		m_Com.SetOutput(COleVariant(SendByteArray));
		m_Com.SetOutBufferCount(0);
		//延时m_delay,启动计时器
		SetTimer(1,m_delay,NULL);
	}
	else
	{
		MessageBox("串口打开错误！","警告",MB_OK|MB_ICONWARNING);
	}

}

//检查串口收到的数据
void CTTTView::CheckComData()
{
	//二进制方式
	COleVariant            varInput; 
	varInput.parray         =  NULL;
	long                     ix,l,u;
	BYTE                   TempByte;
	CString                     str;
	
	//取值计算
	varInput     = m_Com.GetInput();
	m_ReceiveStr =               "";
	
	if(varInput.parray != NULL) 
	{ 
	
		m_ReceiveStr = "";
		//得到安全数组上界
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//得到安全数组下界
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//得到数组中数据值
		for(ix = l; ix <= u; ix ++)
		{
			SafeArrayGetElement(varInput.parray,&ix,&TempByte);
			str.Format("0x%0x ",TempByte);
			m_ReceiveStr = m_ReceiveStr + str;
		}
		
	}
	
	m_ReceiveStr.TrimLeft();
    m_ReceiveStr.TrimRight();

	if(m_ReceiveStr.IsEmpty())
	{
	   m_ReceiveStr = "<<接收超时>>";
	}

	UpdateData(FALSE);

}

//生成BCH包
//long ModuleNum   模块号
//BYTE StationNo   手拉手电站码
//BYTE MotherLine  母线
//BYTE LineNo      线号
//BYTE Phase       相选择0A 1B 2C
//BYTE ZeroDots    延时过0点数
//BYTE Item        要什么东西,命令字
//int status       可放时间或其它东西
void CTTTView::ComeIntoBch20(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE          ORDER[9];
	BYTE          PhaseBit;
	long        m_PhaseBit;

	BYTE    data[21],g[32];
	memset(data,0,21);

	BYTE       AddrH,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 意义为模块号为16表号为01
	AddrH = (ModuleNum/100)>>13;//高位    对应的为数据
   	AddrL = ModuleNum%100 - 1;  //低4位   脉冲子表地址
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 8;i++)
	{
		ORDER[i] = 0;
	}
	
	StatusH = status/256;        //高位    对应的为数据3的后2位
	StatusL = status%256;        //低位    数据4
	
	switch(Phase)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
            
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
		    
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[4]  = ZeroDots;// 延时过0点基数       
	//相别 
	
	//ORDER[5]到ORDER[10]由单片机用片机传给模块用
	ORDER[5]  = Item*32 + AddrL*2 + AddrH; //命令字(3) + 脉冲表子表地址(4) + 模块地址最高位(1);
		
	
	PhaseBit  = Item;

	for(int j = 0; j < 3; j ++)
	{
		data[2-j]  = Item%2;
		Item       = Item/2;
	}

	
    for( j = 0; j < 4; j ++)
	{
		data[6-j]   = AddrL%2;
		AddrL       = AddrL/2;
	}

	//高位
	data[7]         =  AddrH;

	//模块号
	m_PhaseBit       = ModuleNum/100;

	//转成位
	for(j = 0 ; j < 14; j ++)
	{
		data[20 - j]  = m_PhaseBit%2;
		m_PhaseBit    = m_PhaseBit/2;
	}

  	/*
	CString    str;

	for(j = 0; j < 21; j ++)
	{ 
	     str.Format("data[%d]=%d",j,data[j]);
		
		if((j + 1)%8 == 0)
		{
			WriteToLog(str + "\r\n");
		}
		else
		{
			WriteToLog(str);
		}
	}
	*/
    
	//////////////////////add 20060207
	/*
	for(j = 0; j < 21; j ++)
	{
		if(j == 20)
		{
			data[j] = 1;
		}
		else
		{
			data[j] = 0;
		}
		
	}
	*/
	
	/////////////////////////////add 20060207

	//转成BCH码
	Encode_Bch_31_21_2(g,data);
	
 	/*
	for(j = 0; j < 32; j ++)
	{
		
        str.Format("g[%d]=%d",j,g[j]);

		if((j + 1)%8 == 0)
		{
			WriteToLog(str + "\r\n");
		}
		else
		{
			WriteToLog(str);
		}

	}

	DecodeBCH31212(g);
	*/

	//数据又赋回
	for( i = 5; i < 9; i ++)
	{
		
		ORDER[i]  = 0;
		
		for(int j = 0; j < 8;j ++)
		{
			//
			ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]<<(7-j));
		}

	//	str.Format("ORDER[%d]=%0x",i,ORDER[i]);
	//	WriteToLog(str);

	}

	for( i = 5; i <= 13; i ++)
	{
	
		if( i < 9)
		{
			SendByteArray.Add(ORDER[i]);
		}
		else
		{
			SendByteArray.Add(0x00);
		}

	}
}


//生成BCH包
//long ModuleNum   模块号
//BYTE StationNo   手拉手电站码
//BYTE MotherLine  母线
//BYTE LineNo      线号
//BYTE Phase       相选择0A 1B 2C
//BYTE ZeroDots    延时过0点数
//BYTE Item        要什么东西,命令字
//int status       可放时间或其它东西
void CTTTView::ComeIntoBch70(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 意义为模块号为16表号为01
	AddrH = int((int(ModuleNum/100)%65536)/256);//高位    对应的为数据1
    AddrM = (int(ModuleNum/100)%65536)%256;     //中间位  对应的为数据2
	AddrL = ModuleNum%100 - 1;                  //低4位   分给表号
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}
    
	
	StatusH = status/256;        //高位    对应的为数据3的后2位
	StatusL = status%256;        //低位    数据4
	
	switch(Phase)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
            
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
		    
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// 延时过0点基数       
	//相别 
	
	//ORDER[5]到ORDER[10]由单片机用片机传给模块用
	
	/*
	if(Item == 0xF7)//单独处理
	{
		ORDER[5]  = 0xF6 + int(int(ModuleNum/100)/65536); //命令字，要什么东西＋模块地址最高位
		
	}
	else
	*/
	{
		
		ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //命令字，要什么东西＋模块地址最高位
		
	}
	
	ORDER[6]  = AddrH;//模块高地址
	ORDER[7]  = AddrM;//模块中地址
	ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
	
	//新的选择
	switch(Item)
	{
	case 0xF2://假如是广播冻结
		{
			ORDER[9]  = StatusL;//驻留时间
			break;
		}
    case 0x02://读有功电度
		{	
            break;
		}
	case 0x3a://读电压
		{
			break;
		}
	case 0x3e://表底清0
		{
			break;
		}
	case 0x40://电流测试清0
		{
            break;
		}
	case 0xF7://送电操作
		{
			
			//送电操作  D3 = 0000****
		//	ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
			break;
			
		}
	case 0xf6://断电操作
		{	
			
			//断开状态时 D3 = 1111****
			ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
			break;
			
		}
	case 0x82://读冻结有功电度
		{
			
			//假如为其它命令
            break;
			
		}
		
	default:
		{
			//假如为其它命令
			ORDER[9]  =  0x67;                                 //此字节后三位为延时过0点数
		}
		
	}
	
	
	
	//根据零点数,发ORDER[9]的值
    switch(ZeroDots)
	{
	case 3:
		{
			
			ORDER[9]  = 0x60 + 0x07;    //此字节后三位为延时过0点数
			break;
			
		}
	case 5:
		{
			
			ORDER[9]  = 0x60 + 0x07;    //此字节后三位为延时过0点数
			break;
			
		}
	case 20:
		{
			
			ORDER[9]  = 0x60 +  0x06;    //此字节后三位为延时过0点数
			break;
			
		}	
	case 30:
		{
			
			ORDER[9]  = 0x60 +  0x05;     //此字节后三位为延时过0点数
			break;
			
		}
	case 60:
		{
			
			ORDER[9]  = 0x60 +  0x04;     //此字节后三位为延时过0点数
			break;
			
		}
	case 100:
		{
			
			ORDER[9]  = 0x60 +  0x03;      //此字节后三位为延时过0点数
			break;
			
		}
	case 160:
		{
			
			ORDER[9]  = 0x60 +  0x02;      //此字节后三位为延时过0点数
			break;
			
		}	
	case 200:
		{
			
			ORDER[9]  = 0x60 +  0x01;      //此字节后三位为延时过0点数
			break;
			
		}
	case 240:
		{
			
			ORDER[9]  =  0x60 + 0x00;     //此字节后三位为延时过0点数
			break;
			
		}
	}
	
	//检验字节
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和

	 /*
	 CString str;
	 for(int j = 0 ; j < 11; j++)
	 {
		str.Format("ORDER[%d]=%0X",j,ORDER[j]);
	    WriteToLog(str);
	 }
	*/
	
	//status
	//暂时无用
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//BCH打包
	//检验字节,BCH校验
	BYTE            g[64];
	BYTE         data[45];

	//	g[63] =             0;
	for( i = 5; i < 10; i ++)
	{
		
		//	str.Format("ORDER[%d]=0x%0x",i,ORDER[i]);
		//	WriteToLog(str);
		PhaseBit = ORDER[i];

		//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

		for(int j = 1; j <= 8; j ++)
		{
			
			//strtemp.Format("%d",PhaseBit%2);
			//WriteToLog(strtemp);
			//data[(i-5)*8+j-1] = TempVale%2;   //add 2004.12.28
			//ssgg 7-5
			//data[6 + (i-5)*8+j-1] = PhaseBit%2;//add 2004.12.28
			//PhaseBit              = PhaseBit/2;
			data[6 + (i - 5) * 8 + j - 1] = (PhaseBit & 0x80) == 0 ? 0 : 1;//add 2004.12.28
			PhaseBit                      = PhaseBit << 1;
			//end ssgg 7-5
		}
		
	}
	
	//  40-45赋为0
	//	data[40] = data[41] = data[42] = data[43] = data[44] = 0;
	data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;

//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<46; i++) {
				CString mystr;
				if(data[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
//end ssgg debug

	//转成BCH码
	Encode_Bch_63_45_3(g,data);
	
	//数据又赋回
	for( i = 5; i < 13; i ++)
	{
		
		ORDER[i] = 0;
		
		for(int j = 0; j < 8;j ++)
		{
			//ssgg 7-5
			//ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,j));
			ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow(2,j*(-1) + 7));
			//end ssgg 7-5
		}
		
	}
	
	ORDER[13] = 0;
		//ssgg debug
		//		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

	for( i = 5; i <= 13; i ++)
	{
		SendByteArray.Add(ORDER[i]);
	}
}

//生成BCH包
//long ModuleNum   模块号
//BYTE StationNo   手拉手电站码
//BYTE MotherLine  母线
//BYTE LineNo      线号
//BYTE Phase       相选择0A 1B 2C
//BYTE ZeroDots    延时过0点数
//BYTE Item        要什么东西,命令字
//int status       可放时间或其它东西
void CTTTView::ComeIntoBch60(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 意义为模块号为16表号为01
	AddrH = int((int(ModuleNum/100)%65536)/256);//高位    对应的为数据1
    AddrM = (int(ModuleNum/100)%65536)%256;     //中间位  对应的为数据2
	AddrL = ModuleNum%100 - 1;                  //低4位   分给表号
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}    
	
	StatusH = status/256;        //高位    对应的为数据3的后2位
	StatusL = status%256;        //低位    数据4
	
	switch(Phase)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
            
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
		    
			//如果是789上收
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// 延时过0点基数       
	
	//相别 
    //ORDER[5]到ORDER[10]由单片机传给模块用 20位数据有用 + 7位特征码(0001000)
	//如果是 485表: 18(监督位) + 14(地址) + "1"(485标志)           + 5(命令) + 7位特征码(0001000)
	//如果是脉冲表: 18(监督位) + 14(地址) + "0"(脉冲表字地址)      + 2(命令) + 7位特征码(0001000)
	
	//地址前8位
	ORDER[5]  = (ModuleNum/100)>>6; //地址高位
	
	if(ModuleNum%100 >= 12)
	{
		//485表  6位地址  +  1位(485标志) + 1位命令字(共5位命令字)
		ORDER[6]  = ((ModuleNum/100)%64)* 4 + 1*2 + (Item>>4);
		//4位命令字(共5位命令字) + 4位特征码(0001)
		ORDER[7]  = (Item%16)*16 + 1;
		//3位特征码(000) + 5个0
		ORDER[8]  =  0x00;//00000000
		
	}
	else
	{	
		
		//停送电
		if(Item == 0x00 || Item==0x01)
		{
			//使断电停电不容易出现，发第7块表的停送电 0111
			//脉冲表 6位地址 + 子表地址2位高位(共4位子表地址)
			ORDER[6]  = ((ModuleNum/100)%64)* 4  +  1;
			//子表地址2位低位(共4位子表地址)+2位命令字+4位特征码(0001)
			ORDER[7]  = 3*64+ (Item%4)*16        +  1;
			
		}
		else
		{
			//脉冲表 6位地址 + 子表地址2位高位(共4位子表地址)
			ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
			//子表地址2位低位(共4位子表地址)+2位命令字+4位特征码(0001)
			ORDER[7]  = ((ModuleNum%100-1)%4)*64+ (Item%4)*16     +    1;
			
		}
		
		//3位特征码(000) + 5个0
		ORDER[8]  =  0x00;//00000000
	}
	
	//BCH打包
	//检验字节,BCH校验
	//61,62,协议,检验字节,BCH校验 45_27_3
	BYTE             g[45];
	BYTE          data[27];
	
	//把27位数据取出
	long         TempVale = (ORDER[5]<<19) + (ORDER[6]<<11) + (ORDER[7]<<3) +  (ORDER[8]>>5);
	
	//21位数据
	for(int j = 0; j < 27; j ++)
	{
		data[26-j]  = TempVale%2;
		TempVale    = TempVale/2;     
	}
		
	//转成BCH码
	Encode_Bch_45_27_3(g,data);

	//数据又赋回
	for( i = 5; i < 13; i ++)
	{
		
		ORDER[i]     =   0;
		
		for(int j = 0; j < 8;j ++)
		{
			
			if(((i-5)*8 + j ) > 44)
			{
				ORDER[i] = ORDER[i] + 0;
			}
			else
			{
				ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,7-j));
			}
			
		}	
		
	}
	
	ORDER[13] = 0;

	for( i = 5; i <= 13; i ++)
	{
		SendByteArray.Add(ORDER[i]);
	}
}

void CTTTView::OnChangeAngle() 
{
	UpdateData(TRUE);
	
	/*
	if(m_angle  < 5 || m_angle  > 50)
	{
		MessageBox("角度超界[5,50]！","警告",MB_OK|MB_ICONWARNING);
        m_angle  =     30;
		UpdateData(FALSE);
	}
	*/

}

//31-21-2
BOOL CTTTView::DecodeBCH31212(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 5, n = 31 , length = 31, t = 2, k = 21, d = 5;
   
	m_CollectPlace[0] = 0;
	m_CollectPlace[1] = 0;

	CString str;
	
	int alpha_to[] = {  1,  2,  4,  8, 16,  5, 10, 20, 
		                13, 26, 17,  7, 14, 28, 29, 31, 27, 19,  3,  6, 12, 24, 21, 15,30, 25, 23, 11, 22,  9, 18,  0};
  
	int index_of[] = { -1,  0,  1, 18,  2,  5, 19, 11,
                         3, 29,  6, 27, 20,  8, 12, 23,
                         4, 10, 30, 17,  7, 22, 28, 26,
                         21, 25,  9, 16, 13, 14, 24, 15};
	t2 = 2 * t;
	
	////计算综合病症 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//修改 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // 设置错误标志
			// 转换综合病症从多项式到索引形式
			s[i] = index_of[s[i]];
			
	}
	
	//有错误的话
	if (syn_error) 
	{
		
		//计算错误的位置多项式用欧几里运算法则
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//计算b(x)数组值
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// 规格化错误位置多项式
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// 用Chien search找到错误的位置 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			
			}
			
			
			if (count == l[u])
			{
				//	// no. roots = degree of elp hence <= t errors 
				str.Format("纠正错误个数： count = %d",count);
				WriteToLog(str);
				
				//纠码的个数
				m_CollectNos = count;

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					/*
					if( loc[i] < 24)
					{
						str.Format("纠正错误位置：%d",23 - loc[i]);
					}
					else
					{
						str.Format("纠正错误位置：%d",86 - loc[i]);
					}
					*/
								
					if( loc[i] < 10)
					{
						m_CollectPlace[i] = 9 - loc[i];
						str.Format("纠正错误位置：%d",9 - loc[i]);
					}
					else
					{
						m_CollectPlace[i] = 40 - loc[i];
						str.Format("纠正错误位置：%d",40 - loc[i]);
					}
					                  
				    //str.Format("纠正错误位置：%d",loc[i]);
					
					WriteToLog(str);
					

				}
				return TRUE;
				
			}
			else
			{
				//
				str.Format("错误个数为： count = %d，l[%d] = %d",count,u,l[u]);
				WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> length为数据值 
		}
		else
		{
			//
			str.Format("错误个数为：%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//	
		m_CollectNos    =    0;
		str = "t = 0,没有错误";
		WriteToLog(str);//
		return TRUE;
	}

}

void CTTTView::OnCheck12() 
{
	UpdateData();
	
	if(m_xinjiaobian)
	{
		GetDlgItem(IDC_CHECK13)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK13)->EnableWindow(FALSE);
	}
}

void CTTTView::OnChangeusedata() 
{
	CChangeFileDlg dlg;
	dlg.DoModal();
	
}

void CTTTView::OnSendallone() 
{
	CSendEveryTime  dlg;

	if(dlg.DoModal() == IDOK)
	{
		CWnd* pt = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText("  ");
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);

        SetTimer(2,dlg.m_Seconds*1000,NULL);
		OnTimer(2);
	
	}
}

//全发1
void CTTTView::SendAllOne()
{

	UpdateData(TRUE);
    BYTE           Receive[5];
	BYTE            ORDER[15];
	U32             output[5];
	CString        str,bakstr;
	
    // A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
	}
 
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	ORDER[3]  = (BYTE)(m_generatrix - 1) * 64 + (BYTE)((m_iChSelect + 1) * 4) + (m_phase + 1);//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[4]  = 3;    // 延时过0点基数       

	//读表协议 31-39或71-79 意义[十位:3-和校验 7-BCH校验 个位:叠加次数]
	ORDER[2] = m_protocol/10*16 + m_protocol%10;
	
	if(m_protocol == 22)
	{
		//22协议当71协议用
		ORDER[2] = 0x71;
	}
	else if(m_protocol == 31)
	{
		ORDER[2] = 0x53;
	}
	
	
	//数据又赋回
	for( i = 5; i <= 13; i ++)
	{
		ORDER[i] = 0xff;
	}			
		
 	//发前14位
	for(int j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//检验和
			ORDER[14] = ORDER[14] + ORDER[j];
		}

	}

	//发送检验和
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//空一个数
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//边发边收
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//时钟
		if(err != 0)
		{
			Beep(300,400);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//时钟
		if(err != 0)
		{
			Beep(300,400);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		}

		Receive[j] = BYTE(output[j] & 0xff);

		Sleep(1);
	}
	
	/*
	str = "";
	for(j = 0; j <= 14; j ++)
	{
		bakstr.Format("ORDER[%d]=%0x \r\n",j,ORDER[j]);
		str = str + bakstr;
	}
	
	WriteToLog("发送指令：" + str);

	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		str.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//最高位两位去掉
		WriteToLog("双向通讯时检验和不对!\r\n" + str + "\r\n");
		Beep(300,400);
	}
	*/

}



//测试相位
void CTTTView::OnButtonTestphase() 
{
	UpdateData(TRUE);
	BYTE         ORDER[15];
    BYTE  temp         = 0;
	BYTE  m_phaseValue = 0;

	//A相
	if(m_bCh8) 
	{
		temp         ++ ;
		m_phaseValue = 0;
	}
	
	//B相
	if(m_bCh9) 
	{
		temp         ++ ;	
		m_phaseValue = 1;

	}

	//C相
	if(m_bCh10) 
	{
		temp         ++ ;
		m_phaseValue = 2;
	}
	
	if(temp > 1)
	{
		MessageBox("测相位不能同时选二相或以上电压！请重选！"," ",MB_OK|MB_ICONASTERISK);
		return;
	} 

	//显示波形关了
	m_ShowWave     =   FALSE;
  	g_Extend       =      10;
	UpdateData(FALSE);

	unsigned short *ai_buf=NULL;
    I16                     err;
	
    err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    Beep(300,400);
		return;
    }

	if(temp > 0)
	{
	
		//命令字,ORDER[0]到ORDER[4]发给单片机用
		ORDER[0]  = 0x51;           //前导码
		ORDER[1]  = 0x52;           //前导码
		ORDER[2]  = 0x6c + m_phaseValue; //触发命令
		ORDER[3]  = (BYTE)(m_generatrix - 1) * 64 + (BYTE)((m_iChSelect + 1) * 4) + (m_phaseValue + 1);//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
		ORDER[4]  = 3;// 延时过0点基数 
		ORDER[5]  = 0;
		ORDER[6]  = 0;
		ORDER[7]  = 0;
		ORDER[8]  = 0;
		ORDER[9]  = 0;
		ORDER[10] = 0;
		ORDER[11] = 0;
		ORDER[12] = 0;
		ORDER[13] = 0;
		
		//向单片机发命令
		if(!PcSendToSCM(ORDER))
		{
			MessageBox("对方没有响应指令！！请重试！！"," ",MB_OK|MB_ICONASTERISK);
			return;
		}
	
	}
    
	err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
  
	err = AI_ContScanChannels(card,LASTCHANNEL, AD_B_10_V, ai_buf, nReadCount,(SampleRate+1)*1000, ASYNCH_OP);
  	
	//测相的话
	m_TestPhase = TRUE;
	AfxBeginThread(ScanChannels,this);

	bClearOp = 0;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);
	
}

void CTTTView::OnChangeEditCurrentgainsmpwin() 
{
	CString str;
	UpdateData();

	Invalidate();

	g_GainSampleWin        = m_fGainSampleWin;
	g_CurrentGainSampleWin = m_fCurrentGainSampleWin;	

	str.Format("+%3.2fV(+%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEP)->SetWindowText(str);
    str.Format("-%3.2fV(-%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEN)->SetWindowText(str);

	if(m_iModeSel > 0)
	{
	    OnButtonUpdate();
	}
	
}

//换算电流值
int CTTTView::ChangeIValue(BYTE m_Ivale)
{
	int m_ReturnValue = 0;

	if(m_Ivale <= 22)
	{
		m_ReturnValue = m_Ivale*1.000/22*400;
	}
	else if(m_Ivale > 22 && m_Ivale <= 38)
	{
		m_ReturnValue = 400 + (m_Ivale-22)*1.000/(38-22)*(720 - 400);
	}
	else if(m_Ivale > 38 && m_Ivale <= 53)
	{
		m_ReturnValue = 720 + (m_Ivale-38)*1.000/(53-38)*(800 -720);
	}
	else if(m_Ivale > 53 && m_Ivale <= 57)
	{
		m_ReturnValue = 800 + (m_Ivale-53)*1.000/(57-53)*(912 - 800);
	}
	else if(m_Ivale > 57 && m_Ivale <= 73)
	{
		m_ReturnValue = 912 + (m_Ivale-57)*1.000/(73-57)*(1200 -912);
	}
	else if(m_Ivale > 73 && m_Ivale <= 96)
	{
		m_ReturnValue = 1200 + (m_Ivale-73)*1.000/(96-73)*(1300 - 1200);
	}
	else
	{
		m_ReturnValue = 1500;
	}

	return int(m_ReturnValue);


}

//星角变全采六通道解码,解6次－－－－－读表协议
double CTTTView::DecodeSixChannel(long ModuleNum, BYTE Protocol, BYTE Item, BYTE m_phase)
{	
	CString               str,signstr;
	BYTE                     Data[39];
	double dataValue         =     -1;
	int   index              =      0;
    long                   Diffs[200];
	long         m_sums        =    0;
	int          m_StartPlace  =    0;
	double  m_maxppvalue       =    0;
	short   m_pipeiplace       =    0;
	int     m_maxpptimes       =    5;//多采5个波
	double  m_ppvalue          =    0;
    BYTE  SignalBit[100],TempSignalBit[100],Signal[10];
	double          m_ppresult[6000];//匹配结果
    int            m_ChaValue =    25;//25个点的匹配波;
    short        m_PlaceDifferent[31];//22协议不同的对比位置
	BOOL         m_checkplace = FALSE;
	BYTE         m_ByteRecords =    0;//收的字节数
	int              m_ZeroPalce[1500];//过零点位置
	short             m_tempdata1[400];
    short             m_tempdata2[400];
	short             m_tempdata3[400];
    short             m_tempdata4[400];

	for(int i = 0; i < 6000;i ++)
	{
		m_ppresult[i] = 0;
	}

	//时间控制
	if(Protocol == 22)
	{
	    //(5 + 31*4*2)*2048 = 518144  提前采集
		if(DataLen < 518144)
		{	
			return -1;
		}
		
		m_ByteRecords = 62;

	}
	else if(Protocol == 31 || Protocol== 32 || Protocol == 71 || Protocol == 72 || Protocol == 73)
	{
		//(5 + 63*4)*2048 = 526336   提前采集
		if(DataLen < 526336)
		{	
			return -1;
		}
		
		m_ByteRecords = 63;

	}
	else if(Protocol == 61)
	{
		//(5 + 45*4)*2048 = 378880    提前采集
		if(DataLen < 378880)
		{	
			return -1;
		}
		
		m_ByteRecords = 45;
		
	}
	else if(Protocol == 62)
	{
		//(5 + 2*45*4)*2048 = 747520  提前采集
		if(DataLen < 747520)
		{	
			return -1;
		}	
		
		m_ByteRecords = 90;
		
	}

	//测试三相电压电流,从三相中找匹配值最大的结果
	for(int m_PhaseTest = 0; m_PhaseTest < 3; m_PhaseTest ++)
	{

		//初始化过0点坐标
		for(int i = 0; i < 1500; i ++)
		{
			m_ZeroPalce[i]  =  0;
		}
		
		//采集的数据转换
		for( i = 0;i < DataLen/6; i ++)
		{
			m_TestCurrent[i]  = DataBuf[i*6 + m_PhaseTest    ]; //m_phase相电流数据
			m_TestVoltage[i]  = DataBuf[i*6 + m_PhaseTest + 3]; //m_phase相电压数据

			/*
			if(m_PhaseTest == 2)
			{
				str.Format("%6d",m_TestVoltage[i]);
				WriteToLog(str);
			}
			*/
		}
		
		index   =     0;
		
		//找电压过0点
		for( i = 0;i < DataLen/6; i ++)
		{
			
			m_StartPlace = FindZeroPoint(m_TestVoltage,i,30);
			
			if(m_StartPlace > m_ChaValue) // 20度有用 20*2000/6/360 = 18.5
			{
				
				if(index < 1500)
				{
					m_ZeroPalce[2*index] = m_StartPlace;//电压过零点位置
					//m_ZeroPalce[index] = m_StartPlace;//电压过零点位置
					index                         ++ ;
				}
				
				//找下一个过零点
				i  = i + 300;	
			 // i  = i + 150;
			
			}	
			
		}

		
		//过0点
		for( i = 0;i < index - 1; i ++)
		{
            m_ZeroPalce[2*i + 1] = (m_ZeroPalce[2*i] + m_ZeroPalce[2*(i + 1)])/2;
		}
		
		
		//检验过零点的有效性
		for( i = 1; i < 1500 ; i ++)
		{
			
			if(m_ZeroPalce[i - 1] > 0 && m_ZeroPalce[i] > 0)
			{
				
			
				/**/
			//	if(m_PhaseTest == 2)
				{
				//	str.Format("m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,相差:%d",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
				//	WriteToLog(str);
				}
				
				
				/*
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 33)
				{	
					
					str.Format("【电压过零点计算错误:m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,相差:%d】",i - 1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
					WriteToLog(str);
					return           -1;		
					
				}
		    	*/
			
				
				//修正间隔
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 15)
				{
				
					m_ZeroPalce[i] = m_ZeroPalce[i - 1] + 167;	
				
				}
				
			}
			
		}
		
		
		//第一个不是正向波,下移半个波
		index = 0;
		
		for( i = 0; i < 20; i ++)
		{
			
			if(m_TestVoltage[m_ZeroPalce[0] - i] >= 0)
			{
				
				index ++ ;
				
			}
			
		}
		
		//如果有60%是大于0的数
		if(index > 12)
		{
			//	signstr.Format("\r\n【第一个波不是正向波】\r\n");
			//	WriteToLog(signstr);
			
			for(int i = 0 ; i < 1499; i ++)
			{
				
				m_ZeroPalce[i]  = m_ZeroPalce[i + 1];
				
			}
			
		}/**/
		
				
		//移1个波,找第一个过0点  m_frontdot 电流比电压落后的点数
		for(int hhh = 0; hhh < m_maxpptimes; hhh ++)
		{
			
			//解码10度角,用的是新协议,前1024个点是空的,波形折算成位
			for(index = 0; index < m_ByteRecords ;index ++)
			{
				
				
				for(int i = 0 ; i < 2*m_ChaValue; i ++)
				{	
					
					//第一个波,过零点前后各取m_ChaValue个点			
					m_tempdata1[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 1]  - m_ChaValue + i]; 
					m_tempdata1[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 2]  - m_ChaValue + i]; 
					
					//第二个波	
					m_tempdata2[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 3]  - m_ChaValue + i]; 
					m_tempdata2[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 4]  - m_ChaValue + i]; 
					
					//第三个波
					m_tempdata3[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 5]  - m_ChaValue + i]; 
					m_tempdata3[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 6]  - m_ChaValue + i]; 
					
					//第四个波
					m_tempdata4[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 7]  - m_ChaValue + i]; 
					m_tempdata4[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 8]  - m_ChaValue + i]; 
					
				}	
				
				//4个波相减
				for( i = 0; i < 4*m_ChaValue; i ++)
				{
					m_tempdata1[i] = m_tempdata3[i] - m_tempdata1[i]  +  m_tempdata4[i] - m_tempdata2[i]; 
				}
				
				//2个波尖相加
			    //WriteToLog("\r\n\r\n");
				//str.Format("相别:%d,第%d个波:",m_PhaseTest,hhh + 1);
				//WriteToLog(str);

				for( i = 0; i < m_ChaValue; i ++)
				{
					Diffs[i] = m_tempdata1[3*m_ChaValue/2 + i] + m_tempdata1[5*m_ChaValue/2 + i]; 

				    /*
					if( hhh == 2 || hhh == 3 || hhh == 4)
					{
						str.Format("Diffs[%4d] = %5d",i,Diffs[i]);
						WriteToLog(str);	
						
						if(i == (m_ChaValue - 1))
						{
							//2个波尖相加
							WriteToLog("\r\n\r\n");
						}

					}
					*/
				

				}
				
				//5度匹配波
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  +                                hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table05,Diffs,25);
				//10度匹配波
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  +   m_maxpptimes*m_ByteRecords + hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table10,Diffs,25);
				//20度匹配波
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  + 2*m_maxpptimes*m_ByteRecords + hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table20,Diffs,25);
			}
			
		}
		
	}
  
	/*	
	for(int j = 0; j  < 3*3*m_maxpptimes*m_ByteRecords; j ++)
	{
		
		if( ((j + 1)%m_ByteRecords) == 0)
		{
			str.Format("m_ppresult[%4d] = %8.2f\r\n\r\n\r\n\r\n",j%m_ByteRecords,m_ppresult[j]);
			
		}
		else
		{
			str.Format("m_ppresult[%4d] = %8.2f",j%m_ByteRecords,m_ppresult[j]);
		}
		
		WriteToLog(str);
	}
	*/

		
	//从5、10及20度中找出最大匹值
	m_maxppvalue  =    0;

	//找最大匹配值
	for(int jj = 0; jj < 3*3*m_maxpptimes; jj ++)//m_maxpptimes个波
	{
		
		m_ppvalue    =    0;//匹配值和
		
		for(index = 0; index < m_ByteRecords ;index ++)
		{
			
			m_ppvalue = fabs(m_ppresult[jj*m_ByteRecords + index]) + m_ppvalue;
			
		}
		
		if(m_ppvalue > m_maxppvalue)
		{
			m_maxppvalue  =  m_ppvalue;//最大匹配值
			m_pipeiplace  =         jj;//记住最佳匹配位置
		}

		signstr.Format("位置：%d,值：%.2f",jj + 1,m_ppvalue);
		WriteToLog(signstr);
	}

    signstr.Format("模块号：%d,相别：%d,第%d个波,角度：%d度,匹配位置：%d,匹配和值：%.2f，均值：%.2f",ModuleNum,m_pipeiplace/(3*m_maxpptimes),(m_pipeiplace%m_maxpptimes) + 1,5*int(pow(2,((m_pipeiplace%(3*m_maxpptimes))/m_maxpptimes))),m_pipeiplace+1,m_maxppvalue,float(m_maxppvalue/m_ByteRecords));
    WriteToLog(signstr);

	WriteToLog("最佳匹配结果如下：\r\n");

	//最佳匹配位置的数据
	for(index = 0; index < m_ByteRecords ;index ++)
	{
		
		//匹配值和
		if(m_ppresult[m_pipeiplace*m_ByteRecords + index]  > 0)
		{
			SignalBit[index] = 0;
		}
		else 
		{
			SignalBit[index] = 1;
		}

		signstr.Format(" 收到的数为：SignalBit[%2d] = %0x [%.3f]",index,SignalBit[index],m_ppresult[m_pipeiplace*m_ByteRecords + index]);
		WriteToLog(signstr);
		
		//回车行
		if((index + 1) % 8 == 0 || index == m_ByteRecords - 1)
		{
			
			if((index + 1) % 8 == 0)
			{
				
				if(SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{	
					signstr.Format(" 0x%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				
			}
			else
			{	

				BYTE   m_addValue  =    0;
 
				if(index == m_ByteRecords - 1)
				{
					BYTE        m_ttts;
					m_ttts   =  m_ByteRecords- (m_ByteRecords/8)*8;


					for(int jjj = 0; jjj < m_ttts; jjj ++)
					{
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow(2,m_ttts-1-jjj));
					
					}
				
				}

				/*
				if(SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{
					signstr.Format(" 0x%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				*/

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\n十六进制为:"+ signstr + "\r\n");
			m_ReceiveStr = m_ReceiveStr + signstr;
			
		}
		
	}

	if(Protocol == 22)
	{
		
		//不同的组数
		m_sums            =    0;
		
		//如果是22协议的话,对比两次收到的数
		for(short i = 0; i <  31; i ++)
		{
			
			//对比两次接收到的数据
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{
				//记住不同的位置
				m_PlaceDifferent[m_sums] = i;
				m_sums                    ++;
				
			}
			
		}
		
		//数据叠加再处理,解码10度和5度角,用的是新协议,前1024个点是空的,波形折算成位
		for(index = 0; index < 31 ;index ++)
		{
			
			//两匹配系数相加
			m_ppvalue = m_ppresult[m_pipeiplace*m_ByteRecords + 2*index] + m_ppresult[m_pipeiplace*m_ByteRecords + 2*index + 1]; 
			
			//得0或1
			if(m_ppvalue  > 0)
			{
				SignalBit[index] = 0;
			}
			else 
			{
				SignalBit[index] = 1;
			} 
			
		}
		
		//数据顺序调整
		for( i = 0; i <  31; i ++)
		{
			//31,21,2
			if( i < 10 )
			{
				TempSignalBit[i]    = SignalBit[9 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[30 - i + 10];
			}
			
		}	
		
		//纠码个数
		m_CollectNos    =   10;
		dataValue       =   -1;
		
		//WriteToLog("\r\n开始解码\r\n");	
		
		Sleep(100);	
		
		if(!(m_sums <= 6))
		{	
			//WriteToLog("范围错误");
			return -1;
		}
		
		//31212解码
		if(DecodeBCH31212(TempSignalBit))
		{
			
			//对一下纠的位,如果有纠码的位
			if(m_CollectNos > 0)
			{
				m_checkplace  =    FALSE;
				
				//对位算法,查纠的位是否是在不同的位置中
				for(int i = 0; i < m_CollectNos;i ++)
				{
					
					m_checkplace  = FALSE;
					
					//有几个错
					for(int j = 0; j < m_sums; j++)
					{
						
						if(m_PlaceDifferent[j] == m_CollectPlace[i])
						{
							m_checkplace = TRUE;
							break;
						}
						
					}
					
					if(!m_checkplace)
					{
						break;
					}
					
				}
				
				//纠出的位置要在两组不同的数据位置中
				if(!m_checkplace)
				{
					return -1;
				}
				
			}
			
			//signstr.Format("对位：m_CollectNos＝%d",m_CollectNos);
			//WriteToLog("\r\n"+ signstr + "\r\n");
			
			// 如果纠出的位在不同的位置中或者没有错误
			if(m_checkplace || m_CollectNos == 0)
			{
				
				//从10-30为数据位低->高发展，回的数为16进制
				//电流  0～30A
				//电压  0～300V
				//送电成功0x32
				//电表故障 21全为1(111111111111111111111)，正常的数最低位为********************0
				//驻留没有驻留上  (000000000000000000001)  20个0 + 1
				
				//16进制解码
				dataValue   =     0.00;
				
				for( i = 0; i < 21; i++)
				{
					dataValue = dataValue + double(TempSignalBit[10 + i]*pow(2,i));
				}
				
				//str.Format("dataValue = %d",int(dataValue));
				//WriteToLog(str);
				
				if(TempSignalBit[10] == 1)
				{
					
					//电表通讯错误,只有485表才有电表通讯错误
					if(ModuleNum%100 >= 12 && long(dataValue)==2097151)
					{
						//电表通讯错误
						return  -2;			
					}
					
					//驻留没有驻留上,驻留指令最低位为0
					if(long(dataValue)== 1 && (Item%2==0) )
					{
						//驻留没有驻留上
						return  -4;			
					}	
					
					//最低位为则错误
					dataValue       =   -1;
					
				}
				else
				{
					//功率因素2位小数
					if(Item == 0x63 ||  Item == 0x62)
					{
						
						//最大值为100*1000
						if(dataValue <= 100000)
						{
							return dataValue/1000;
						}
						else
						{
							dataValue =  -1;
						}
						
					}
					else
					{
						//电流,最大值为0～30
						if((Item>= 0x64 && Item<=0x69) || Item == 0x04)
						{
							//最大值为300
							if(dataValue < 300)
							{
								return dataValue/10;
							}
							else
							{
								dataValue =  -1;
							}
							
						}
						
						//电压,最大值为0～300
						if((Item>= 0x6a && Item==0x6f) || Item==0x01)
						{
							//最大值为300
							if(dataValue < 3000)
							{
								return dataValue/10;
							}
							else
							{
								dataValue =  -1;
							}
							
						}	
						
					}
					
					if(dataValue >=  0)
					{
						return dataValue/10;
					}
					
				}
				
			}
			
		 }
		 
		 //31212解码
		 dataValue   =   -1;
		 
	 }
	 else if (Protocol == 61 || Protocol == 62)
	 {
		 
		 // WriteToLog("\r\n6162协议开始解码\r\n");
		 
		 //61,62协议
		 if (Protocol == 62)
		 {
			 
			 //62协议,数据叠加再处理,解码10度和5度角,用的是新协议,前1024个点是空的,波形折算成位
			 for(index = 0; index < 45 ;index ++)
			 {
				 
				 //两匹配系数相加
				 m_ppvalue = m_ppresult[m_pipeiplace*m_ByteRecords + 2*index] + m_ppresult[m_pipeiplace*m_ByteRecords + 2*index + 1]; 
				 
				 //得0或1
				 if(m_ppvalue  > 0)
				 {
					 SignalBit[index] = 0;
				 }
				 else 
				 {
					 SignalBit[index] = 1;
				 } 
				 
			 }
			 
		 }
		 
		 //数据顺序调整
		 for(int  i = 0; i <  45; i ++)
		 {
			 //45,27,3
			 if( i < 18 )
			 {
				 TempSignalBit[i]    = SignalBit[17 - i];
			 }
			 else
			 {
				 TempSignalBit[i]    = SignalBit[44 - i + 18];
			 }
			 
		 }	
		 
		 dataValue  =   -1;

		 
		 //对收到的数纠码,45273
		 if(DecodeBCH45273(TempSignalBit))//纠码对的话
		 {
			 //从10-30为数据位低->高发展，回的数为16进制
			 //电流  0～30A
			 //电压  0～300V
			 //送电成功0x32
			 //电表故障 21全为1(111111111111111111111)，正常的数最低位为********************0
			 //驻留没有驻留上  (000000000000000000001)  20个0 + 1
			 //WriteToLog("解码成功");
			 
			 //6162协议,倒回原来的数
			 for(int i = 0; i <  45; i ++)
			 {
				 
				 //45,27,3
				 if( i < 18 )
				 {
					 SignalBit[i]    =  TempSignalBit[17 - i];
				 }
				 else
				 {
					 SignalBit[i]    =  TempSignalBit[44 - i + 18];
				 }
				 
			 }
			
			 //16进制
			 dataValue = 0.00;
			 
			 for( i = 0; i < 21; i++)
			 {
				 dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			 }		
			 
			 m_sums     =      0;
			 
			 //7位一检验和
			 for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			 {
				 
				 //数据位变成字节,7位一检验和 
				 for( i = 0;i < 7; i ++)
				 {  	
					 
					 m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					 
				 }
				 
			 }
			 
			 //如果检验和对的话
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
			
				 //45273解码
				 if(dataValue >= 0)
				 {
					 //正确的话
					 Beep(5000,400); 
					 return dataValue/10;
				 }
				 
			 }
			 else
			 {
				 //检验和不对
				 str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				 WriteToLog(str);
				 return       -1;
			 }

			 /*
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
				 
				 //算出值
				 for( i = 0; i < 21; i++)
				 {
					 dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
				 }	
				 
				 if(SignalBit[38] == 1)
				 {
					 
					 //电表通讯错误,只有485表才有电表通讯错误
					 if(ModuleNum%100 >= 12 && long(dataValue)==2097151)
					 {
						 //正确的话
                 		 Beep(5000,400); 
						 //电表通讯错误
						 return  -2;			
					 }
					 
					 //驻留没有驻留上,驻留指令最低位为0
					 if(long(dataValue)== 1 && (Item%2==0) )
					 {
						 //驻留没有驻留上
						 return  -4;			
					 }	
					 
					 //最低位为则错误
					 dataValue       =   -1;
					 
				 }
				 else
				 {
					 
					 //如果大于等于0
					 if(dataValue >= 0)
					 {
						 
						 //功率因素2位小数
						 if(Item==0x07 ||  Item==0x06 )
						 {
							 
							 //最大值为100*1000
							 if(dataValue <= 1000)
							 {
								 return dataValue/1000;
							 }
							 else
							 {
								 dataValue  =      -1;
							 }
							 
						 }
						 else
						 {
							 //电流,最大值为0～30,电压,最大值为0～300,三相电流电压合在一起了 ,每相7个字节，ABC各7位电流：*0.2，电压：*2
							 if(Item == 0x08 || Item == 0x09 || Item == 0x0B || Item == 0x0A) 
							 {								
								 return dataValue;
							 }
							 
						 }
						 
						 if(dataValue >= 0)
						 {
							 //除以10
							 return dataValue/10;
						 }
						 
						 
					 }
					 
					 
				 }
				 
				 
			 }
			 */
			 
			 //检验和不对
			 dataValue =  -1;
			 
			 str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
			 WriteToLog(str);
		}
			
			
	 }
	 else
	 {
			 
		 //顺序调整，如果是31、32、71、72协议的话
		 for(int i = 0; i <  63; i ++)
		 {
			 
			 if( i < 24 )
			 {
				 TempSignalBit[i]    =  SignalBit[23 - i];
			 }
			 else
			 {
				 TempSignalBit[i]    =  SignalBit[62 - i + 24];
			 }
			 
		 }	
		 
		 //	Sleep(100);
		 //	WriteToLog("解码开始");
		 dataValue = -1;
		 
		 //对收到的数纠码,63394
		 if(DecodeBCH63394(TempSignalBit))
		 {
			 
			 dataValue    =  0;
			 
			 for( i = 0; i < 39; i++)
			 {
				 //数据又倒过来
				 Data[i] = TempSignalBit[62 - i];
			 }	
			 
			 //回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好， "电表通讯错误"
			 //回的值为AAAAAA.AA,扩展模块的表没有连好，           "电表故障2"
			 m_sums      =      0;
			 
			 //数据位变成字节 
			 for( i = 0;i < 8; i ++)
			 {
				 
				 Signal[i] = Data[i * 4] * 8 + Data[i * 4 + 1] * 4 + Data[i * 4 + 2] * 2 + Data[i * 4 + 3] ;
				 dataValue = dataValue + Signal[i] * 100000.00/pow(10,i);
				 
				 //检验和
				 if((i + 1)%2 != 0)
				 {
					 m_sums  = m_sums  + Signal[i]*16;//高位在前
				 }
				 else
				 {		
					 m_sums = m_sums  + Signal[i];   //低位在后
				 }
				 
			 }	
			 
			 if(Signal[0] == 0x0f && Signal[1] == 0x0e && Signal[2] == 0x0f && Signal[3] == 0x0e && Signal[4] == 0x0f && Signal[5] == 0x0e && Signal[6] == 0x0f && Signal[7] == 0x0e && (ModuleNum%100 >= 12))
			 {	 
				 //正确的话
                 Beep(5000,400); 
				 //只有485表才有电表故障,485电表通讯错误
				 return  -2;			
			 }
			 else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
			 {
				 //正确的话
                 Beep(5000,400); 
				 //只有485表才有电表故障,电表故障2
				 return  -3;
			 }
			 else if(Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			 {
				 //正确的话
                 Beep(5000,400); 
				 //读驻留时模块没有收到过驻留命令回的数
				 return  -4;
			 }	
			 else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			 {   
				 
				 //检验和
				 if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
				 {
					 
					 //485表为0不正常
					 if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
					 {
						 return  -2;
					 }					 
					 
					 //正确的话
                     Beep(5000,400);

					 return  dataValue;
					 
				 }
				 
				 return   -1;
				 
			 }
			 
			 return   -1;
			 
		 }
		 
	 }
	 
	 return dataValue;
}

//找过0点的位置,找10个点,有一半为负的话,先5个负,后5个正,k个点
int CTTTView::FindZeroPoint(short m_CollectData[], int m_StartPlace, int k)
{	
	/*
	int m_ZheSums    =  0;//正的个数
	int m_FuSums     =  0;//负的个数
	int m_dots       = -1;//前起点
	int m_Fvalue     =  0;
    int m_Zvalue     =  0;
	int m_AddByOrder =  0;
	m_ZheSums        =  0;//正的个数
	m_FuSums         =  0;//负的个数

	
	for(int i = m_StartPlace; i < m_StartPlace + k; i ++)
	{	
	
		//正向,由-到+递增		
		if(m_CollectData[i] < 0)
		{
			
			//负的相加
			m_FuSums ++;
			
			if(i < (m_StartPlace + k/2))
			{
				
				//负的值相加
				m_Fvalue = m_Fvalue + m_CollectData[i];
				
			}
			
		}
		else
		{
			
			//正的相加
			m_ZheSums ++;
			
			if(i >= (m_StartPlace + k/2))
			{
				
				//正的值相加
				m_Zvalue = m_Zvalue + m_CollectData[i];
				
			}
			
		}	
		
    }	

	//如果满足下列条件
	if(((m_ZheSums == m_FuSums) || (m_ZheSums == (m_FuSums + 2)))  && (m_Zvalue*m_Fvalue) < 0  && (m_FuSums > 0))
	{
		m_dots = m_StartPlace + k/2 + 1;
	}
	*/


	int m_ZheSums     =  0;//正的个数
	int m_FuSums      =  0;//负的个数
	int m_dots        = -1;//前起点

	for(int i = m_StartPlace; i < m_StartPlace + k; i ++)
	{	
	
		//正向,由-到+递增		
		if(m_CollectData[i] < 0)
		{
			//负的相加
			m_FuSums ++;
		}
		else
		{
			//正的相加
			m_ZheSums ++;
		}		
    
	}	

	//如果满足下列条件
	if((abs(m_ZheSums - m_FuSums) <= 2) && (m_ZheSums > 0))
	{
		m_dots = m_StartPlace + k/2 + 1;
	}

	return  m_dots;
}

//采集六通道相关性检验
double CTTTView::CorrelationSixChannelCheck(long SourceArray[], long DestArray[], int K)
{
    double           A,B,C,Pxy,sums;
	int                           i;
   	A = B = C = Pxy = sums = 0.000;
	
	for(i = 0; i < K;i ++)
	{
		A += SourceArray[i]*DestArray[i];
        B += SourceArray[i]*SourceArray[i];
        C += DestArray[i]  *DestArray[i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
}


//全采三相电流读表数据,采集六通道
void CTTTView::ReadSixChannelMeter()
{
    WriteToLog("[星角读表]");

	//循环读数   
	int     HalfCount  =     0;
	CString                str;
    BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
    U32                  count;
	DataLen            =     0; 
    memset(ReadBuff,0,1024);
	int         DataValues = 0;
	int         m_order    = 0;	
	int m_YanShiMillSecond = 0;//延时
    m_Stopping             = FALSE;
	CTime                timet;

    CWnd* pt    =    GetDlgItem(IDC_ORDER);
    pt->GetWindowText(str);

	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		pt    =    GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(TRUE);
		MessageBox("命令字不能为空！","",MB_OK|MB_ICONWARNING);
		return;
	}
    
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(FALSE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(FALSE);

	pt = GetDlgItem(IDC_REAL_START);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_DECODE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO_REALTIME);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_COMSET);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SENDALLONE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BUTTON_ANGLE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);
	
	//add 20061218
	long time11  = GetTickCount();

	//发命令
	SendOrderToSCM(m_module/*模块号*/,0/*手拉手电站码*/,m_generatrix/*母线*/,m_iChSelect + 1/*线号*/,m_phase/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,m_order/* 要什么东西,命令字*/,0/*可放时间或其它东西*/);

	unsigned short *ai_buf=NULL;
	
	//开始采集数据
	memset(DataBuf,0,800000);
	memset(ReadBuff,0,1024);
	
	//双缓冲模式
	err = AI_AsyncDblBufferMode(card, 1); 	
	
	if(err != 0)
	{
		//Beep(300,400);
		//Beep(300,400);
	}

	/*	
	err = AI_AsyncDblBufferMode(card, 0); 	

    //外触发状态
	err = AI_9111_Config(card,TRIG_EXT_STROBE,0,0);//1024 512
	
	if (err !=  0) 
	{  
		//Beep(300,400);
		//Beep(300,400);
	}

	//采集8通道的数据 0-A相电流 1－B相电流 2－C相电流 3-A相电压 4－B相电压 5－C相电压
	err = AI_ContScanChannels(card,5,AD_B_10_V,ai_buf,512,(F64)100000,SYNCH_OP);//ASYNCH_OP ASYNCH_OP SYNCH_OP

	//U16 analog_input[1];
	//AI_ReadChannel(card,0, AD_B_10_V, &analog_input[0]);

	long time22  = GetTickCount();
	str.Format("时间差:%d",time22 - time11);
	WriteToLog(str);
	//add 20061218
    */

	//自采模式TRIG_INT_PACER
	err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		//Beep(300,400);
		//Beep(300,400);
	}
	

	//各协议的延时控制
	switch(m_protocol)
	{
	case 22:
		{
			m_YanShiMillSecond =  31*2*20*2;//2480  //延时毫秒  124
			break;
		}
	case 31:
		{
			
		}			
	case 71:
		{				
			m_YanShiMillSecond =  64*2*20;//2560  //延时毫秒   127
			break;
		}	
	case 32:
		{
			
		}
	case 72:
		{				
			m_YanShiMillSecond = 64*2*20*2;//5040  //延时毫秒  127*2 + 1
			break;
		}
	case 73:
		{				
			m_YanShiMillSecond = 64*2*20*3;//5040  //延时毫秒  127*3 + 1
			break;
		}
	case 33:
		{
			
		}
   case 61:
	   {
		   m_YanShiMillSecond =  45*2*20; //1800   //延时毫秒   89
		   break;
	   }
   case 62:
	   {
		   m_YanShiMillSecond =  45*2*20*2;//3600  //延时毫秒  89*2+1
		   break;
	   }
	}
	
	//延时毫秒
	m_YanShiMillSecond = m_YanShiMillSecond + m_millondseconds;

	timet = CTime::GetCurrentTime();	
	//str.Format("开始解码 "",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	//WriteToLog(str);

	str.Format("抄表协议:%d,延时:%d毫秒 %4d-%02d-%02d %02d:%02d:%02d",m_protocol,m_YanShiMillSecond,timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	WriteToLog(str);

	bClearOp     =              FALSE;
	
	LARGE_INTEGER               litmp;
	LONGLONG                  qt1,qt2;
	double                dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//获得时钟频率
	dff =      (double)litmp.QuadPart;

	QueryPerformanceCounter(&litmp);  //获得初始值
	qt1 =              litmp.QuadPart;
	
	while(1)
	{	
		QueryPerformanceCounter(&litmp);//获得终止值
		qt2 =      litmp.QuadPart;
		dfm = (double)(qt2 - qt1);
		dft =    dfm*1000.000/dff;//获得对应的时间值
		
		if(m_Stopping)
		{
			break;
		}
		else
		{
			
			if((m_YanShiMillSecond - int(dft)) >= 200)
			{
				SurrenderWindowMessage();
				Sleep(200);
				SurrenderWindowMessage();
			}
			else
			{
				
				if((m_YanShiMillSecond - int(dft) - 20) <= 0)
				{
					break;
				}
				
			}
			
		}
		
	}	



	CTime time0  = CTime::GetCurrentTime();
	
	//采集ABC三相电流电压6个通道
	err = AI_ContScanChannels(card,5, AD_B_10_V,ai_buf,2048,(F64)100000, ASYNCH_OP);

	if (err !=   0) 
	{  
		//	Beep(300,400);
		//	Beep(300,400);
	}

	do
	{
		do
		{
			//半满
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
			
			
			CTimeSpan ts    = CTime::GetCurrentTime() - time0;
			
			if(m_protocol != 22)
			{
				
				//如果不是22协议
				if(ts.GetTotalSeconds() > (m_protocol%10)*11 || m_Stopping)
				{
					
					bClearOp = TRUE;
					
				}
				
			}
			else
			{	
				//如果是22协议
				if(ts.GetTotalSeconds() > 10 || m_Stopping)
				{
					
					bClearOp = TRUE;
					
				}
				
			}
			
		} while (!bHalfReady && !bClearOp);
		
		if(m_Stopping)
		{
			bClearOp = TRUE;
		}
		
		if(!bClearOp) 
		{
			
			//传送半满数据
			AI_AsyncDblBufferTransfer(card, ReadBuff);
			
			bHalfReady = FALSE;
			
			for(int i = 0; i < 1024; i++)
			{	
				
				ReadBuff[i] = ReadBuff[i]/16;
				
				//大于2048为负数
				if(ReadBuff[i] >= 2048)
				{
					DataBuf[DataLen++] =  -(4096 - ReadBuff[i]);
				}
				else
				{
					DataBuf[DataLen++] =   ReadBuff[i];
				}
				
			}
			
			SurrenderWindowMessage();
			
			if(m_Stopping)
			{
				bClearOp = TRUE;
			}
			
			CTimeSpan ts    = CTime::GetCurrentTime() - time0;
			
			//时间控制
			switch(m_protocol)
			{
			case 22:
				{
					//(5 + 31*4*2)*2048 = 518144  提前采集
					if(DataLen >= 518144)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 31:
				{
					
				}
			case 32:
				{
					
				}
			case 71:
				{
					
				}
			case 72:
				{
					
					
				}
			case 73:
				{
					//(5 + 63*4)*2048 = 526336   提前采集
					if(DataLen >= 526336)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 61:
				{
					//(5 + 45*4)*2048 = 378880    提前采集
					if(DataLen >= 378880)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 62:
				{
					//(5 + 2*45*4)*2048 = 747520   提前采集
					if(DataLen >= 747520 )
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			}				
			
			if(m_protocol != 22)
			{
				//如果不是22协议
				if(ts.GetTotalSeconds() > (m_protocol%10)*11 || m_Stopping)
				{
					bClearOp = TRUE;
					break;
				}
			}
			else
			{	
				//如果是22协议
				if(ts.GetTotalSeconds() > 10 || m_Stopping)
				{
					bClearOp = TRUE;
					break;
				}
			}
			
		  }
			
			
        }while (!bClearOp && !bStopped);
		
		AI_AsyncClear(card, &count);
	
	  //  long time33  = GetTickCount();;
	  //  str.Format("时间差:%d",time33 - time22);
	  //  WriteToLog(str);

		//时间
		timet = CTime::GetCurrentTime();	
		str.Format("开始解码 %4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	    WriteToLog(str);
		
		//返回值
		double GetValue  = DecodeSixChannel(m_module,m_protocol,m_phase,m_phase);
		
		if(GetValue >= 0)//解码
		{	 
			//正确的话
         //  Beep(5000,400); 
			m_SuccessTimes  = m_SuccessTimes + 1;
			m_data.Format("%.2f",GetValue);//
		}
		else
		{
			m_data = "NULL";
		}

		
		m_TotalTimes  = m_TotalTimes  + 1;
		
		CEdit * ptt = (CEdit *)GetDlgItem(IDC_DATAVALUE);
		ptt->SetWindowText(m_data);
		ptt        =  (CEdit *)GetDlgItem(IDC_RECEIVE);
		ptt->SetWindowText(m_ReceiveStr);
		
		CWnd* pts   = GetDlgItem(IDC_REAL_START);
		pts->EnableWindow(TRUE);
		pt= GetDlgItem(IDC_PROTOCOLS);
	    pt->EnableWindow(TRUE);	
		pt= GetDlgItem(IDC_ORDERCOMBO);
	    pt->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SEND);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SETTIMER);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_DECODE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_RADIO_REALTIME);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_COMSET);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SENDALLONE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_BUTTON_ANGLE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_REALSTOP);
		pts->EnableWindow(FALSE);
	
		//改回外触发状态
	    err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);

}

void CTTTView::SurrenderWindowMessage()
{	
	MSG message;
	
	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

}

//初始化order指令
void CTTTView::InitOrderCombo(short m_protcols)
{

	CString                 str;
	m_ordercombo.ResetContent();
	
	if(m_protcols/10 == 3 || m_protcols/10 == 7)
	{
		m_ordercombo.AddString("02-总有功电度");
		m_ordercombo.AddString("06-总无功电度");
		m_ordercombo.AddString("1C-A相电流");
		m_ordercombo.AddString("1E-B相电流");
		m_ordercombo.AddString("20-C相电流");
		m_ordercombo.AddString("16-A相电压");
		m_ordercombo.AddString("18-B相电压");
		m_ordercombo.AddString("1A-C相电压");
		m_ordercombo.AddString("58-尖峰电量");
		m_ordercombo.AddString("5A-峰电量");
		m_ordercombo.AddString("5C-平电量");
		m_ordercombo.AddString("5E-谷电量");
		m_ordercombo.AddString("38-功率因数");

		m_ordercombo.AddString("82-冻结总有功电度");
		m_ordercombo.AddString("86-冻结总无功电度");	
		m_ordercombo.AddString("9C-冻结A相电流");
		m_ordercombo.AddString("9E-冻结B相电流");
		m_ordercombo.AddString("A0-冻结C相电流");
		m_ordercombo.AddString("96-冻结A相电压");
		m_ordercombo.AddString("98-冻结B相电压");
		m_ordercombo.AddString("9A-冻结C相电压");	
		m_ordercombo.AddString("D8-冻结尖峰电量");
		m_ordercombo.AddString("DA-冻结峰电量");
		m_ordercombo.AddString("DC-冻结平电量");
		m_ordercombo.AddString("DE-冻结谷电量");
		m_ordercombo.AddString("B8-冻结功率因数");		
		
	}
	else  if(m_protcols/10 == 6)
	{
		
		m_ordercombo.AddString("1F-总有功电度");
		m_ordercombo.AddString("1D-总无功电度");
		m_ordercombo.AddString("09-三相电流");
		m_ordercombo.AddString("0B-三相电压");
		m_ordercombo.AddString("13-尖峰电量");
		m_ordercombo.AddString("11-峰电量");
		m_ordercombo.AddString("0F-平电量");
		m_ordercombo.AddString("0D-谷电量");
		m_ordercombo.AddString("07-功率因数");
		m_ordercombo.AddString("02-停电次数");
		
		m_ordercombo.AddString("1E-冻结总有功电度");
		m_ordercombo.AddString("1C-冻结总无功电度");
		m_ordercombo.AddString("08-冻结三相电流");
		m_ordercombo.AddString("0A-冻结三相电压");
		m_ordercombo.AddString("12-冻结尖峰电量");
		m_ordercombo.AddString("10-冻结峰电量");	
		m_ordercombo.AddString("0E-冻结平电量");	
		m_ordercombo.AddString("0C-冻结谷电量");		
		m_ordercombo.AddString("06-冻结功率因数");
		
		
	}
	else
	{
		
		m_ordercombo.AddString("5F-有功电度");
		m_ordercombo.AddString("5D-无功电度");	
		m_ordercombo.AddString("69-A相电流");
		m_ordercombo.AddString("67-B相电流");
		m_ordercombo.AddString("65-C相电流");	
		m_ordercombo.AddString("6F-A相电压");
		m_ordercombo.AddString("6D-B相电压");
		m_ordercombo.AddString("6B-C相电压");
		m_ordercombo.AddString("53-尖峰电量");
		m_ordercombo.AddString("51-峰电量");
		m_ordercombo.AddString("4F-平电量");
		m_ordercombo.AddString("4D-谷电量");
		m_ordercombo.AddString("63-功率因数");

		m_ordercombo.AddString("5E-冻结总有功电度");	
		m_ordercombo.AddString("5C-冻结总无功电度");
		m_ordercombo.AddString("68-冻结A相电流");
		m_ordercombo.AddString("66-冻结B相电流");
		m_ordercombo.AddString("64-冻结C相电流");
		m_ordercombo.AddString("6E-冻结A相电压");
		m_ordercombo.AddString("6C-冻结B相电压");
		m_ordercombo.AddString("6A-冻结C相电压");	
		m_ordercombo.AddString("52-冻结尖峰电量");
		m_ordercombo.AddString("50-冻结峰电量");
		m_ordercombo.AddString("4E-冻结平电量");
	    m_ordercombo.AddString("4C-冻结谷电量");	
	    m_ordercombo.AddString("62-冻结功率因数");
		
	}

	m_ordercombo.SetCurSel(0);

}

void CTTTView::OnSelchangeOrdercombo() 
{
	
	CString   str;

	if(m_ordercombo.GetCount() >= 0)
	{
		m_ordercombo.GetLBText(m_ordercombo.GetCurSel(),str);
		str = str.Left(2);

		GetDlgItem(IDC_ORDER)->SetWindowText(str);
	}
	
}

void CTTTView::OnButton1() 
{

	BOOL     m_AutoRecordAvi = FALSE;
	CString         m_parameter[95];
	CString  EightPlaceDirectionName[4];
	EightPlaceDirectionName[0] = "0";
	EightPlaceDirectionName[1] = "1";
	EightPlaceDirectionName[2] = "2";
	EightPlaceDirectionName[3] = "3";
	CString                  AVIFILE;
	AVIFILE = "1_H00_0105205128.264";
//	m_parameter[90] =  "F:\\胡高明\\dvplay\\要改的数据库格式及要求\\要改的数据库格式及要求\\Police.mdb";
	m_parameter[90] =  "F:\\data";

	m_parameter[14] =  "清河街1号";
	m_parameter[15] =  "清河街2号";
//	AfxGetModuleState()->m_dwVersion   =   0x0601;//指定版本  

//	AfxGetModuleState()->m_dwVersion=0x0601;   
 // AfxDaoInit();   

	/*
 
	CDaoDatabase   db;   
	CString   strConnect(   _T(   ";pwd="   ));   
	strConnect   =   strConnect   +   szDBPws;   
	db.Open(   szDBFileName   ,   TRUE,   FALSE,strConnect);   
	AfxDaoTerm();//关闭数据库前，调要该函数   
	db.Close();
	*/

	int       m_channel      =        0;

	CString               m_filename;
	CFileFind                  fFind;
    CString               str,SqlCmd;
	long               m_Records = 0;
	BOOL         m_Successed = FALSE;
	CDaoDatabase                  db;//数据库
	CDaoRecordset        RecSet(&db);//记录集
	COleVariant                  var;//字段类型
	var.ChangeType(VT_I4, NULL);
	CString               m_fangxian;
	CString          m_DataTableName;
	CTime m_StartTime  =  CTime::GetCurrentTime();
	BOOL  m_IsExist    =  FALSE;

	if(m_AutoRecordAvi)
	{
		m_DataTableName.Format("%4d%02d%02dBR",m_StartTime.GetYear(),m_StartTime.GetMonth(),m_StartTime.GetDay());
	}
	else
	{
		m_DataTableName.Format("%4d%02d%02dOT",m_StartTime.GetYear(),m_StartTime.GetMonth(),m_StartTime.GetDay());
	}

	//如果文件目录是空
	if(m_parameter[90].IsEmpty())
	{
		m_parameter[90] = "C:\\DATA";
	}
	
	/*
	//如果此目录不存在
	if(!FolderExist(m_parameter[90]))
	{
		//不存在就建立相关目录
		if(!CreateFolder(m_parameter[90]))
		{
		//	SetResultStr(m_parameter[90] + "目录建立失败！");
			//MessageBox(m_parameter[90] + "目录建立失败！","",MB_OK|MB_ICONWARNING);
			return FALSE;
		}
		
	}
	*/

	//闯红绿灯的数据库记录
	m_filename.Format("%s\\%s",m_parameter[90],"Police.mdb");
	m_Successed         =  fFind.FindFile(m_filename);
	fFind.Close();
	
	if(!m_Successed)
	{
	//	SetResultStr("红绿灯数据文件" + m_filename + "找不到！");
	//	return FALSE;
	}    
	
	m_Successed  = FALSE;


	try
	{

//		AfxMessageBox(m_filename);
		
		// 打开已创建的数据库及表
		//db.Open(m_filename);
        db.Open(m_filename);//,FALSE,FALSE,_T("")
		
		//检测对应的表是否存在
		SqlCmd.Format("SELECT * FROM %s",m_DataTableName);
		
		TRY
		{
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,0);
			//关闭数据库
			RecSet.Close( );
			m_IsExist = TRUE;
		}
		CATCH_ALL(e)
		{ 
			//关闭数据库
			//RecSet.Close( );
			e->Delete();
			m_IsExist = FALSE;
		}
		END_CATCH_ALL;

        //不存在此表则建立
		if(!m_IsExist)
		{
			
			if(m_AutoRecordAvi)
			{
				SqlCmd.Format("SELECT * INTO %s FROM 闯红灯记录 WHERE 1<>1",m_DataTableName);
			}
			else
			{
				SqlCmd.Format("SELECT * INTO %s FROM 其他违章记录 WHERE 1<>1",m_DataTableName);
			}
			
			//运行SQL语句
			db.Execute(SqlCmd);
		}

		if(m_AutoRecordAvi)
		{
			SqlCmd.Format("SELECT COUNT(*)  FROM %s",m_DataTableName);
		}
		else
		{
			SqlCmd.Format("SELECT COUNT(*)  FROM %s",m_DataTableName);
		}

		if(RecSet.IsOpen())
		{
			RecSet.Close();
		}

		//打开已创建的数据表                                  
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd, 0);
		RecSet.GetFieldValue((int)0,var);  
		m_Records = var.lVal;
		RecSet.Close();
		
		COleDateTime m_Current = COleDateTime::GetCurrentTime();

		//红绿灯
		if(m_AutoRecordAvi)
		{
			switch(atoi(EightPlaceDirectionName[m_channel]))
			{
			case 0:
				{
					m_fangxian="东";
					break;
				}
			case 1:
				{
					m_fangxian="南";
					break;
				}
			case 2:
				{
					m_fangxian="西";
					break;
				}
			case 3:
				{
					m_fangxian="北";
					break;
				}
			}

			//原来没有记录
			SqlCmd.Format("INSERT INTO %s(序号,时间,路号,路口,方向,[红灯后时间(秒)],录象,备注) VALUES (%d,'%s','%s','%d','%s',%d,'%s','%s')",m_DataTableName,m_Records + 1,m_Current.Format(),m_parameter[14 + 2*m_channel].Left(20),m_channel,m_fangxian,3,AVIFILE,"闯红灯");
		}
		else
		{
			/*
			switch(m_RealDirection[m_channel])
			{
			case 0:
				{
					m_fangxian="东";
					break;
				}
			case 1:
				{
					m_fangxian="南";
					break;
				}
			case 2:
				{
					m_fangxian="西";
					break;
				}
			case 3:
				{
					m_fangxian="北";
					break;
				}
			}
			*/

			//原来没有记录
			SqlCmd.Format("INSERT INTO %s(序号,日期,时间,地点,违章类别,录象,备注) VALUES (%d,'%s','%s','%s','%s','%s','%s')",m_DataTableName,m_Records + 1,m_Current.Format(),m_Current.Format(),m_parameter[14 + 2*m_channel].Left(20),"其它违章",AVIFILE,"其它违章");
		}
		
		try
		{
			AfxMessageBox(SqlCmd);

			//加入记录，用SQL语句,97字段
			db.Execute(SqlCmd);
			m_Successed = TRUE;
			
		}
		catch(CDaoException* e)
		{
			e->Delete();
			m_Successed = FALSE;
		}
		
		//关闭记录集及库
		db.Close();

	}
	catch(CDaoException* e)
	{
		db.Close();
		e->Delete();
		m_Successed = FALSE;
	}	
	
	if(!m_Successed)
	{
		
		if(m_AutoRecordAvi)
		{
			
			AfxMessageBox("闯红灯记录数据保存失败!!");
			//	SetResultStr("<<闯红灯记录数据保存失败>>");
		}
		else
		{
			AfxMessageBox("其它违章数据保存失败!!");
			//	SetResultStr("<<其它违章数据保存失败>>");
		}
		
	}
	else
	{
        if(m_AutoRecordAvi)
		{
			
			AfxMessageBox("闯红灯记录数据保存成功!!");
		}
		else
		{
			AfxMessageBox("其它违章数据保存成功!!");
		}
		
	}

 //   return   m_Successed;
 //}	
}
