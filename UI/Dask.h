#ifndef		_DASK_H
#define		_DASK_H

#ifdef __cplusplus
extern "C" {
#endif

//DASK Data Types
typedef unsigned char   U8;
typedef short           I16;
typedef unsigned short  U16;
typedef long            I32;
typedef unsigned long   U32;
typedef float           F32;
typedef double          F64;

//ADLink PCI Card Type
#define PCI_6208V       1
#define PCI_6208A       2
#define PCI_6308V       3
#define PCI_6308A       4
#define PCI_7200        5
#define PCI_7230        6
#define PCI_7233        7
#define PCI_7234        8
#define PCI_7248        9
#define PCI_7249        10
#define PCI_7250        11
#define PCI_7252        12
#define PCI_7296        13
#define PCI_7300A_RevA  14
#define PCI_7300A_RevB  15
#define PCI_7432        16
#define PCI_7433        17
#define PCI_7434        18
#define PCI_8554        19
#define PCI_9111DG      20
#define PCI_9111HR      21
#define PCI_9112        22
#define PCI_9113        23
#define PCI_9114DG      24
#define PCI_9114HG      25
#define PCI_9118DG      26
#define PCI_9118HG      27
#define PCI_9118HR      28
#define PCI_9810        29
#define PCI_9812        30
#define PCI_7396        31
#define PCI_9116        32
#define PCI_7256        33
#define PCI_7258        34

#define MAX_CARD        32

//Error Number
#define NoError                       0
#define ErrorUnknownCardType         -1
#define ErrorInvalidCardNumber       -2
#define ErrorTooManyCardRegistered   -3
#define ErrorCardNotRegistered       -4
#define ErrorFuncNotSupport          -5
#define ErrorInvalidIoChannel        -6
#define ErrorInvalidAdRange          -7
#define ErrorContIoNotAllowed        -8
#define ErrorDiffRangeNotSupport     -9
#define ErrorLastChannelNotZero      -10
#define ErrorChannelNotDescending    -11
#define ErrorChannelNotAscending     -12
#define ErrorOpenDriverFailed        -13
#define ErrorOpenEventFailed         -14
#define ErrorTransferCountTooLarge   -15
#define ErrorNotDoubleBufferMode     -16
#define ErrorInvalidSampleRate       -17
#define ErrorInvalidCounterMode      -18
#define ErrorInvalidCounter          -19
#define ErrorInvalidCounterState     -20
#define ErrorInvalidBinBcdParam      -21
#define ErrorBadCardType             -22
#define ErrorInvalidDaRefVoltage     -23
#define ErrorAdTimeOut               -24
#define ErrorNoAsyncAI               -25
#define ErrorNoAsyncAO               -26
#define ErrorNoAsyncDI               -27
#define ErrorNoAsyncDO               -28
#define ErrorNotInputPort            -29
#define ErrorNotOutputPort           -30
#define ErrorInvalidDioPort          -31
#define ErrorInvalidDioLine          -32
#define ErrorContIoActive            -33
#define ErrorDblBufModeNotAllowed    -34
#define ErrorConfigFailed            -35
#define ErrorInvalidPortDirection    -36
#define ErrorBeginThreadError        -37
#define ErrorInvalidPortWidth        -38
#define ErrorInvalidCtrSource        -39
#define ErrorOpenFile                -40
#define ErrorAllocateMemory          -41
#define ErrorDaVoltageOutOfRange     -42
//Error number for driver API 
#define ErrorConfigIoctl			 -201
#define ErrorAsyncSetIoctl			 -202
#define ErrorDBSetIoctl				 -203
#define ErrorDBHalfReadyIoctl		 -204
#define ErrorContOPIoctl			 -205
#define ErrorContStatusIoctl		 -206
#define ErrorPIOIoctl				 -207
#define ErrorDIntSetIoctl			 -208
#define ErrorWaitEvtIoctl			 -209
#define ErrorOpenEvtIoctl			 -210
#define ErrorCOSIntSetIoctl			 -211
#define ErrorMemMapIoctl			 -212
#define ErrorMemUMapSetIoctl		 -213
#define ErrorCTRIoctl			     -214
#define ErrorGetResIoctl		     -215


#define TRUE    1
#define FALSE   0

//Synchronous Mode
#define SYNCH_OP        1
#define ASYNCH_OP       2

//AD Range
#define AD_B_10_V       1
#define AD_B_5_V        2
#define AD_B_2_5_V      3
#define AD_B_1_25_V     4
#define AD_B_0_625_V    5
#define AD_B_0_3125_V   6
#define AD_B_0_5_V      7
#define AD_B_0_05_V     8
#define AD_B_0_005_V    9
#define AD_B_1_V       10
#define AD_B_0_1_V     11
#define AD_B_0_01_V    12
#define AD_B_0_001_V   13
#define AD_U_20_V      14
#define AD_U_10_V      15
#define AD_U_5_V       16
#define AD_U_2_5_V     17
#define AD_U_1_25_V    18
#define AD_U_1_V       19
#define AD_U_0_1_V     20
#define AD_U_0_01_V    21
#define AD_U_0_001_V   22

//Clock Mode
#define TRIG_SOFTWARE           0
#define TRIG_INT_PACER          1
#define TRIG_EXT_STROBE         2
#define TRIG_HANDSHAKE          3
#define TRIG_CLK_10MHZ          4  //PCI-7300A
#define TRIG_CLK_20MHZ          5  //PCI-7300A
#define TRIG_DO_CLK_TIMER_ACK   6  //PCI-7300A Rev. B
#define TRIG_DO_CLK_10M_ACK     7  //PCI-7300A Rev. B
#define TRIG_DO_CLK_20M_ACK     8  //PCI-7300A Rev. B

//Virtual Sampling Rate for using external clock as the clock source
#define CLKSRC_EXT_SampRate        10000

/*-------- Constants for PCI-6208A/PCI-6308A/PCI-6308V -------------------*/
//Output Mode
#define P6208_CURRENT_0_20MA    0
#define P6208_CURRENT_4_20MA    3
#define P6208_CURRENT_5_25MA    1
#define P6308_CURRENT_0_20MA    0
#define P6308_CURRENT_4_20MA    3
#define P6308_CURRENT_5_25MA    1
//AO Setting
#define P6308V_AO_CH0_3         0
#define P6308V_AO_CH4_7         1
#define P6308V_AO_UNIPOLAR      0
#define P6308V_AO_BIPOLAR       1
/*-------- Constants for PCI-7200 --------------------*/
//InputMode
#define DI_WAITING              0x02
#define DI_NOWAITING            0x00

#define DI_TRIG_RISING          0x04
#define DI_TRIG_FALLING         0x00

#define IREQ_RISING             0x08
#define IREQ_FALLING            0x00

//Output Mode
#define OREQ_ENABLE             0x10
#define OREQ_DISABLE            0x00

#define OTRIG_HIGH              0x20
#define OTRIG_LOW               0x00

/*-------- Constants for PCI-7248/7296/7396 ---------------*/
//DIO Port Direction
#define INPUT_PORT      1
#define OUTPUT_PORT     2

//Channel & Port
#define Channel_P1A             0
#define Channel_P1B             1
#define Channel_P1C             2
#define Channel_P1CL            3
#define Channel_P1CH            4
#define Channel_P1AE            10
#define Channel_P1BE            11
#define Channel_P1CE            12
#define Channel_P2A             5
#define Channel_P2B             6
#define Channel_P2C             7
#define Channel_P2CL            8
#define Channel_P2CH            9
#define Channel_P2AE            15
#define Channel_P2BE            16
#define Channel_P2CE            17
#define Channel_P3A             10
#define Channel_P3B             11
#define Channel_P3C             12
#define Channel_P3CL            13
#define Channel_P3CH            14
#define Channel_P4A             15
#define Channel_P4B             16
#define Channel_P4C             17
#define Channel_P4CL            18
#define Channel_P4CH            19
#define Channel_P5A             20
#define Channel_P5B             21
#define Channel_P5C             22
#define Channel_P5CL            23
#define Channel_P5CH            24
#define Channel_P6A             25
#define Channel_P6B             26
#define Channel_P6C             27
#define Channel_P6CL            28
#define Channel_P6CH            29
//the following are used for PCI7396
#define Channel_P1              30
#define Channel_P2              31
#define Channel_P3              32
#define Channel_P4              33
#define Channel_P1E             34 //only used by DIO_PortConfig function
#define Channel_P2E             35 //only used by DIO_PortConfig function
#define Channel_P3E             36 //only used by DIO_PortConfig function
#define Channel_P4E             37 //only used by DIO_PortConfig function
/*-------- Constants for PCI-7300A -------------------*/
//Wait Status
#define P7300_WAIT_NO           0
#define P7300_WAIT_TRG          1
#define P7300_WAIT_FIFO         2
#define P7300_WAIT_BOTH         3

//Terminator control
#define P7300_TERM_OFF          0
#define P7300_TERM_ON           1

//DI control signals polarity for PCI-7300A Rev. B
#define P7300_DIREQ_POS         0x00000000L
#define P7300_DIREQ_NEG         0x00000001L
#define P7300_DIACK_POS         0x00000000L
#define P7300_DIACK_NEG         0x00000002L
#define P7300_DITRIG_POS        0x00000000L
#define P7300_DITRIG_NEG        0x00000004L

//DO control signals polarity for PCI-7300A Rev. B
#define P7300_DOREQ_POS         0x00000000L
#define P7300_DOREQ_NEG         0x00000008L
#define P7300_DOACK_POS         0x00000000L
#define P7300_DOACK_NEG         0x00000010L
#define P7300_DOTRIG_POS        0x00000000L
#define P7300_DOTRIG_NEG        0x00000020L
/*-------- Constants for PCI-7432/7433/7434 ---------------*/
#define PORT_DI_LOW             0
#define PORT_DI_HIGH            1
#define PORT_DO_LOW             0
#define PORT_DO_HIGH            1
#define P7432R_DO_LED           1
#define P7433R_DO_LED           0
#define P7434R_DO_LED           2
#define P7432R_DI_SLOT          1
#define P7433R_DI_SLOT          2
#define P7434R_DI_SLOT          0
/*-- Dual-Interrupt Source control for PCI-7248/96 & 7432/33 & 7230 & 8554 & 7396 &7256 ---*/
#define INT1_DISABLE            -1    //INT1 Disabled
#define INT1_COS                 0    //INT1 COS : only available for PCI-7396, PCI-7256
#define INT1_FP1C0               1    //INT1 by Falling edge of P1C0 : only available for PCI7248/96/7396
#define INT1_RP1C0_FP1C3         2    //INT1 by P1C0 Rising or P1C3 Falling : only available for PCI7248/96/7396
#define INT1_EVENT_COUNTER       3    //INT1 by Event Counter down to zero : only available for PCI7248/96/7396
#define INT1_EXT_SIGNAL          1    //INT1 by external signal : only available for PCI7432/7433/7230/8554
#define INT1_COUT12              1    //INT1 COUT12 : only available for PCI8554
#define INT1_CH0				 1    //INT1 CH0 : only available for PCI7256
#define INT2_DISABLE            -1    //INT2 Disabled
#define INT2_COS                 0    //INT2 COS : only available for PCI-7396
#define INT2_FP2C0               1    //INT2 by Falling edge of P2C0 : only available for PCI7248/96/7396
#define INT2_RP2C0_FP2C3         2    //INT2 by P2C0 Rising or P2C3 Falling : only available for PCI7248/96/7396
#define INT2_TIMER_COUNTER       3    //INT2 by Timer Counter down to zero : only available for PCI7248/96/7396
#define INT2_EXT_SIGNAL          1    //INT2 by external signal : only available for PCI7432/7433/7230/8554
#define INT2_CH1				 2	  //INT2 CH1 : only available for PCI7256

/*-------- Constants for PCI-8554 --------------------*/
//Clock Source of Cunter N
#define ECKN            0
#define COUTN_1         1
#define CK1             2
#define COUT10          3

//Clock Source of CK1
#define CK1_C8M         0
#define CK1_COUT11      1

//Debounce Clock
#define DBCLK_COUT11    0
#define DBCLK_2MHZ      1

/*-------- Constants for PCI-9111 --------------------*/
//Dual Interrupt Mode
#define P9111_INT1_EOC            0       //Ending of AD conversion
#define P9111_INT1_FIFO_HF        1       //FIFO Half Full
#define P9111_INT2_PACER          0       //Every Timer tick
#define P9111_INT2_EXT_TRG        1       //ExtTrig High->Low

//Channel Count
#define P9111_CHANNEL_DO          0
#define P9111_CHANNEL_EDO         1
#define P9111_CHANNEL_DI          0
#define P9111_CHANNEL_EDI         1

//EDO function
#define P9111_EDO_INPUT           1   //EDO port set as Input port
#define P9111_EDO_OUT_EDO         2   //EDO port set as Output port
#define P9111_EDO_OUT_CHN         3   //EDO port set as channel number ouput port

//AO Setting
#define P9111_AO_UNIPOLAR         0
#define P9111_AO_BIPOLAR          1

/*-------- Constants for PCI-9118 --------------------*/
#define P9118_AI_BiPolar          0x00
#define P9118_AI_UniPolar         0x01

#define P9118_AI_SingEnded        0x00
#define P9118_AI_Differential     0x02

#define P9118_AI_ExtG             0x04

#define P9118_AI_ExtTrig          0x08

#define P9118_AI_DtrgNegative     0x00
#define P9118_AI_DtrgPositive     0x10

#define P9118_AI_EtrgNegative     0x00
#define P9118_AI_EtrgPositive     0x20

#define P9118_AI_BurstModeEn      0x40
#define P9118_AI_SampleHold       0x80
#define P9118_AI_PostTrgEn        0x100
#define P9118_AI_AboutTrgEn       0x200

/*-------- Constants for PCI-9116 --------------------*/
#define P9116_AI_LocalGND	      0x00
#define P9116_AI_UserCMMD         0x01
#define P9116_AI_SingEnded        0x00
#define P9116_AI_Differential     0x02
#define P9116_AI_BiPolar          0x00
#define P9116_AI_UniPolar         0x04

#define P9116_TRGMOD_SOFT         0x00   //Software Trigger Mode
#define P9116_TRGMOD_POST         0x10   //Post Trigger Mode
#define P9116_TRGMOD_DELAY        0x20   //Delay Trigger Mode
#define P9116_TRGMOD_PRE          0x30   //Pre-Trigger Mode
#define P9116_TRGMOD_MIDL         0x40   //Middle Trigger Mode
#define P9116_AI_TrgPositive      0x00
#define P9116_AI_TrgNegative      0x80
#define P9116_AI_ExtTimeBase	  0x100
#define P9116_AI_IntTimeBase	  0x000
#define P9116_AI_DlyInSamples     0x200
#define P9116_AI_DlyInTimebase    0x000
#define P9116_AI_ReTrigEn         0x400
#define P9116_AI_MCounterEn       0x800
#define P9116_AI_SoftPolling      0x0000
#define P9116_AI_INT		      0x1000
#define P9116_AI_DMA			  0x2000

/*-------- Constants for PCI-9812 --------------------*/
//Trigger Mode
#define P9812_TRGMOD_SOFT         0x00   //Software Trigger Mode
#define P9812_TRGMOD_POST         0x01   //Post Trigger Mode
#define P9812_TRGMOD_PRE          0x02   //Pre-Trigger Mode
#define P9812_TRGMOD_DELAY        0x03   //Delay Trigger Mode
#define P9812_TRGMOD_MIDL         0x04   //Middle Trigger Mode

//Trigger Source
#define P9812_TRGSRC_CH0          0x00   //trigger source --CH0
#define P9812_TRGSRC_CH1          0x08   //trigger source --CH1
#define P9812_TRGSRC_CH2          0x10   //trigger source --CH2
#define P9812_TRGSRC_CH3          0x18   //trigger source --CH3
#define P9812_TRGSRC_EXT_DIG      0x20   //External Digital Trigger

//Trigger Polarity
#define P9812_TRGSLP_POS          0x00   //Positive slope trigger
#define P9812_TRGSLP_NEG          0x40   //Negative slope trigger

//Frequency Selection
#define P9812_AD2_GT_PCI          0x80   //Freq. of A/D clock > PCI clock freq.
#define P9812_AD2_LT_PCI          0x00   //Freq. of A/D clock < PCI clock freq.

//Clock Source
#define P9812_CLKSRC_INT          0x000   //Internal clock
#define P9812_CLKSRC_EXT_SIN      0x100  //External SIN wave clock
#define P9812_CLKSRC_EXT_DIG      0x200  //External Square wave clock

/*-------- Timer/Counter -----------------------------*/
//Counter Mode (8254)
#define TOGGLE_OUTPUT             0     //Toggle output from low to high on terminal count
#define PROG_ONE_SHOT             1     //Programmable one-shot
#define RATE_GENERATOR            2     //Rate generator
#define SQ_WAVE_RATE_GENERATOR    3     //Square wave rate generator
#define SOFT_TRIG                 4     //Software-triggered strobe
#define HARD_TRIG                 5     //Hardware-triggered strobe

//General Purpose Timer/Counter
//Counter Mode
#define General_Counter           0x00 //general counter
#define Pulse_Generation          0x01 //pulse generation
//GPTC clock source
#define GPTC_CLKSRC_EXT			  0x08
#define GPTC_CLKSRC_INT			  0x00
#define GPTC_GATESRC_EXT		  0x10
#define GPTC_GATESRC_INT		  0x00
#define GPTC_UPDOWN_SELECT_EXT	  0x20
#define GPTC_UPDOWN_SELECT_SOFT	  0x00
#define GPTC_UP_CTR				  0x40
#define GPTC_DOWN_CTR			  0x00
#define GPTC_ENABLE				  0x80
#define GPTC_DISABLE			  0x00
 
//16-bit binary or 4-decade BCD counter
#define BIN             0
#define BCD             1

//Previous renamed functions re-directed for compatibility 
#define AI_VScale		AI_VoltScale
#define AO_VScale		AO_VoltScale
#define CTR_Reset		CTR_Clear

//DAQ Event type for the event message  
#define AIEnd    0
#define DIEnd    0
#define DOEnd    0
#define DBEvent  1

/*------------------------------------------------------------------
** PCIS-DASK Function prototype
------------------------------------------------------------------*/
I16 __stdcall Register_Card (U16 CardType, U16 card_num);
I16 __stdcall Release_Card  (U16 CardNumber);
I16 __stdcall GetActualRate (U16 CardNumber, F64 fSampleRate, F64 *fActualRate);
/*---------------------------------------------------------------------------*/
I16 __stdcall AI_9111_Config (U16 CardNumber, U16 TrigSource, U16 PreTrgEn, U16 TraceCnt);
I16 __stdcall AI_9112_Config (U16 CardNumber, U16 TrigSource);
I16 __stdcall AI_9113_Config (U16 CardNumber, U16 TrigSource);
I16 __stdcall AI_9114_Config (U16 CardNumber, U16 TrigSource);
I16 __stdcall AI_9116_Config (U16 CardNumber, U16 ConfigCtrl, U16 TrigCtrl, U16 PostCnt, U16 MCnt, U16 ReTrgCnt);
I16 __stdcall AI_9118_Config (U16 CardNumber, U16 ModeCtrl, U16 FunCtrl, U16 BurstCnt, U16 PostCnt);
I16 __stdcall AI_9812_Config (U16 CardNumber, U16 TrgMode, U16 TrgSrc, U16 TrgPol, U16 ClkSel, U16 TrgLevel, U16 PostCnt);
I16 __stdcall AI_9812_SetDiv (U16 wCardNumber, U32 PacerVal);
I16 __stdcall AI_9114_PreTrigConfig (U16 CardNumber, U16 PreTrgEn, U16 TraceCnt);
I16 __stdcall AI_9116_CounterInterval (U16 wCardNumber, U32 ScanIntrv, U32 SampIntrv);
I16 __stdcall AI_InitialMemoryAllocated (U16 CardNumber, U32 *MemSize);
I16 __stdcall AI_ReadChannel (U16 CardNumber, U16 Channel, U16 AdRange, U16 *Value);
I16 __stdcall AI_VReadChannel (U16 CardNumber, U16 Channel, U16 AdRange, F64 *voltage);
I16 __stdcall AI_VoltScale (U16 CardNumber, U16 AdRange, I16 reading, F64 *voltage);
I16 __stdcall AI_ContReadChannel (U16 CardNumber, U16 Channel, U16 AdRange,
               U16 *Buffer, U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContReadMultiChannels (U16 CardNumber, U16 NumChans, U16 *Chans,
               U16 *AdRanges, U16 *Buffer, U32 ReadCount,
               F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContScanChannels (U16 CardNumber, U16 Channel, U16 AdRange,
               U16 *Buffer, U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContReadChannelToFile (U16 CardNumber, U16 Channel, U16 AdRange,
               U8 *FileName, U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContReadMultiChannelsToFile (U16 CardNumber, U16 NumChans, U16 *Chans,
               U16 *AdRanges, U8 *FileName, U32 ReadCount,
               F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContScanChannelsToFile (U16 CardNumber, U16 Channel, U16 AdRange,
               U8 *FileName, U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall AI_ContStatus (U16 CardNumber, U16 *Status);
I16 __stdcall AI_ContVScale (U16 wCardNumber, U16 adRange, void *readingArray, F64 *voltageArray, I32 count);
I16 __stdcall AI_AsyncCheck (U16 CardNumber, BOOLEAN *Stopped, U32 *AccessCnt);
I16 __stdcall AI_AsyncClear (U16 CardNumber, U32 *AccessCnt);
I16 __stdcall AI_AsyncDblBufferHalfReady (U16 CardNumber, BOOLEAN *HalfReady, BOOLEAN *StopFlag);
I16 __stdcall AI_AsyncDblBufferMode (U16 CardNumber, BOOLEAN Enable);
I16 __stdcall AI_AsyncDblBufferTransfer (U16 CardNumber, U16 *Buffer);
I16 __stdcall AI_AsyncDblBufferOverrun (U16 CardNumber, U16 op, U16 *overrunFlag);
I16 __stdcall AI_EventCallBack (U16 CardNumber, I16 mode, I16 EventType, U32 callbackAddr);
/*---------------------------------------------------------------------------*/
I16 __stdcall AO_6208A_Config (U16 CardNumber, U16 V2AMode);
I16 __stdcall AO_6308A_Config (U16 CardNumber, U16 V2AMode);
I16 __stdcall AO_6308V_Config (U16 wCardNumber, U16 Channel, U16 wOutputPolarity, F64 refVoltage);
I16 __stdcall AO_9111_Config (U16 CardNumber, U16 OutputPolarity);
I16 __stdcall AO_9112_Config (U16 CardNumber, U16 Channel, F64 refVoltage);
I16 __stdcall AO_WriteChannel (U16 CardNumber, U16 Channel, I16 Value);
I16 __stdcall AO_VWriteChannel (U16 CardNumber, U16 Channel, F64 Voltage);
I16 __stdcall AO_VoltScale (U16 CardNumber, U16 Channel, F64 Voltage, I16 *binValue);
I16 __stdcall AO_SimuWriteChannel (U16 wCardNumber, U16 wGroup, I16 *pwBuffer);
I16 __stdcall AO_SimuVWriteChannel (U16 wCardNumber, U16 wGroup, F64 *VBuffer);
/*---------------------------------------------------------------------------*/
I16 __stdcall DI_7200_Config (U16 CardNumber, U16 TrigSource, U16 ExtTrigEn, U16 TrigPol, U16 I_REQ_Pol);
I16 __stdcall DI_7300A_Config (U16 CardNumber, U16 PortWidth, U16 TrigSource, U16 WaitStatus, U16 Terminator, U16 I_REQ_Pol, BOOLEAN clear_fifo, BOOLEAN disable_di);
I16 __stdcall DI_7300B_Config (U16 CardNumber, U16 PortWidth, U16 TrigSource, U16 WaitStatus, U16 Terminator, U16 I_Cntrl_Pol, BOOLEAN clear_fifo, BOOLEAN disable_di);
I16 __stdcall DI_InitialMemoryAllocated (U16 CardNumber, U32 *DmaSize);
I16 __stdcall DI_ReadLine (U16 CardNumber, U16 Port, U16 Line, U16 *State);
I16 __stdcall DI_ReadPort (U16 CardNumber, U16 Port, U32 *Value);
I16 __stdcall DI_ContReadPort (U16 CardNumber, U16 Port, void *Buffer,
               U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall DI_ContReadPortToFile (U16 CardNumber, U16 Port, U8 *FileName, 
								  U32 ReadCount, F64 SampleRate, U16 SyncMode);
I16 __stdcall DI_ContStatus (U16 CardNumber, U16 *Status);
I16 __stdcall DI_AsyncCheck (U16 CardNumber, BOOLEAN *Stopped, U32 *AccessCnt);
I16 __stdcall DI_AsyncClear (U16 CardNumber, U32 *AccessCnt);
I16 __stdcall DI_AsyncDblBufferHalfReady (U16 CardNumber, BOOLEAN *HalfReady);
I16 __stdcall DI_AsyncDblBufferMode (U16 CardNumber, BOOLEAN Enable);
I16 __stdcall DI_AsyncDblBufferTransfer (U16 CardNumber, void *Buffer);
I16 __stdcall DI_ContMultiBufferSetup (U16 wCardNumber, void *pwBuffer, U32 dwReadCount, U16 *BufferId);
I16 __stdcall DI_ContMultiBufferStart (U16 wCardNumber, U16 wPort, F64 fSampleRate);
I16 __stdcall DI_AsyncMultiBufferNextReady (U16 CardNumber, BOOLEAN *bNextReady, U16 *wBufferId);
I16 __stdcall DI_AsyncDblBufferOverrun (U16 CardNumber, U16 op, U16 *overrunFlag);
I16 __stdcall DI_EventCallBack (U16 CardNumber, I16 mode, I16 EventType, U32 callbackAddr);
/*---------------------------------------------------------------------------*/
I16 __stdcall DO_7200_Config (U16 CardNumber, U16 TrigSource, U16 OutReqEn, U16 OutTrigSig);
I16 __stdcall DO_7300A_Config (U16 CardNumber, U16 PortWidth, U16 TrigSource, U16 WaitStatus, U16 Terminator, U16 O_REQ_Pol);
I16 __stdcall DO_7300B_Config (U16 CardNumber, U16 PortWidth, U16 TrigSource, U16 WaitStatus, U16 Terminator, U16 O_Cntrl_Pol, U32 FifoThreshold);
I16 __stdcall DO_InitialMemoryAllocated (U16 CardNumber, U32 *MemSize);
I16 __stdcall DO_WriteLine (U16 CardNumber, U16 Port, U16 Line, U16 Value);
I16 __stdcall DO_WritePort (U16 CardNumber, U16 Port, U32 Value);
I16 __stdcall DO_WriteExtTrigLine (U16 CardNumber, U16 Value);
I16 __stdcall DO_ReadLine (U16 CardNumber, U16 Port, U16 Line, U16 *Value);
I16 __stdcall DO_ReadPort (U16 CardNumber, U16 Port, U32 *Value);
I16 __stdcall DO_ContWritePort (U16 CardNumber, U16 Port, void *Buffer,
               U32 WriteCount, U16 Iterations, F64 SampleRate, U16 SyncMode);
I16 __stdcall DO_PGStart (U16 CardNumber, void *Buffer, U32 WriteCount, F64 SampleRate);
I16 __stdcall DO_PGStop (U16 CardNumber);
I16 __stdcall DO_ContStatus (U16 CardNumber, U16 *Status);
I16 __stdcall DO_AsyncCheck (U16 CardNumber, BOOLEAN *Stopped, U32 *AccessCnt);
I16 __stdcall DO_AsyncClear (U16 CardNumber, U32 *AccessCnt);
I16 __stdcall EDO_9111_Config (U16 CardNumber, U16 EDO_Fun);
I16 __stdcall DO_ContMultiBufferSetup (U16 CardNumber, void *pwBuffer, U32 dwWriteCount, U16 *BufferId);
I16 __stdcall DO_AsyncMultiBufferNextReady (U16 CardNumber, BOOLEAN *bNextReady, U16 *wBufferId);
I16 __stdcall DO_ContMultiBufferStart (U16 wCardNumber, U16 wPort, double fSampleRate);
I16 __stdcall DO_EventCallBack (U16 CardNumber, I16 mode, I16 EventType, U32 callbackAddr);
/*---------------------------------------------------------------------------*/
I16 __stdcall DIO_PortConfig (U16 CardNumber, U16 Port, U16 Direction);
I16 __stdcall DIO_SetDualInterrupt (U16 CardNumber, I16 Int1Mode, I16 Int2Mode, HANDLE *hEvent);
I16 __stdcall DIO_SetCOSInterrupt (U16 CardNumber, U16 Port, U16 ctlA, U16 ctlB, U16 ctlC);
I16 __stdcall DIO_INT1_EventMessage (U16 CardNumber, I16 Int1Mode, HANDLE windowHandle, U32 message, void *callbackAddr());
I16 __stdcall DIO_INT2_EventMessage (U16 CardNumber, I16 Int2Mode, HANDLE windowHandle, U32 message, void *callbackAddr());
I16 __stdcall DIO_7300SetInterrupt (U16 CardNumber, I16 AuxDIEn, I16 T2En, HANDLE *hEvent);
I16 __stdcall DIO_AUXDI_EventMessage (U16 CardNumber, I16 AuxDIEn, HANDLE windowHandle, U32 message, void *callbackAddr());
I16 __stdcall DIO_T2_EventMessage (U16 CardNumber, I16 T2En, HANDLE windowHandle, U32 message, void *callbackAddr());
I16 __stdcall DIO_GetCOSLatchData(U16 wCardNumber, U16 *CosLData);
/*---------------------------------------------------------------------------*/
I16 __stdcall CTR_Setup (U16 CardNumber, U16 Ctr, U16 Mode, U32 Count, U16 BinBcd);
I16 __stdcall CTR_Clear (U16 CardNumber, U16 Ctr, U16 State);
I16 __stdcall CTR_Read (U16 CardNumber, U16 Ctr, U32 *Value);
I16 __stdcall CTR_8554_ClkSrc_Config (U16 CardNumber, U16 Ctr, U16 ClockSource);
I16 __stdcall CTR_8554_CK1_Config (U16 CardNumber, U16 ClockSource);
I16 __stdcall CTR_8554_Debounce_Config (U16 CardNumber, U16 DebounceClock);
I16 __stdcall GCTR_Setup (U16 wCardNumber, U16 wGCtr, U16 wGCtrCtrl,U32 dwCount);
I16 __stdcall GCTR_Clear (U16 wCardNumber, U16 wGCtr);
I16 __stdcall GCTR_Read (U16 wCardNumber, U16 wGCtr, U32 *pValue);
/*---------------------------------------------------------------------------*/
I16 __stdcall AI_GetEvent(U16 wCardNumber, HANDLE *hEvent);
I16 __stdcall AO_GetEvent(U16 wCardNumber, HANDLE *hEvent);
I16 __stdcall DI_GetEvent(U16 wCardNumber, HANDLE *hEvent);
I16 __stdcall DO_GetEvent(U16 wCardNumber, HANDLE *hEvent);
/*---------------------------------------------------------------------------*/
I16 __stdcall AI_GetView(U16 wCardNumber, U32 *pView);
I16 __stdcall DI_GetView(U16 wCardNumber, U32 *pView);
I16 __stdcall DO_GetView(U16 wCardNumber, U32 *pView);
/*---------------------------------------------------------------------------*/
I16 __stdcall GetCardType (U16 wCardNumber, U16 *cardType);
I16 __stdcall GetBaseAddr(U16 wCardNumber, U32 *BaseAddr, U32 *BaseAddr2);
I16 __stdcall GetLCRAddr(U16 wCardNumber, U32 *LcrAddr);

#ifdef __cplusplus
}
#endif

#endif		//_DASK_H
