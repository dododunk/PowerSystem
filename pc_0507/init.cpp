
#include "header.h "


/////////AD card parameter////////////////////////

HANDLE hDevice_AD ;  //采集卡对象句柄


PCI8664_STATUS_AD    AD_Status ;//ad采集卡状态结构体

int DeviceLgcID ;   

PCI8664_PARA_AD ADPara ;		// Initialization AD parameter structure


LONG nReadSizeWords;		// Each time the number of read  AD data

LONG nRetSizeWords;

int nADChannel = 0;

SHORT ADData;

SHORT   ADBuffer[AD_DATA_LEN]; // Receive AD data buffer ;

bool   g_ad_device_init = false ;

/////////AD card parameter////////////////////////



/*
int  Fun_AD_Device_Init( )
{
if( g_ad_device_init == false )
{
   DeviceLgcID = 0; 

   hDevice_AD = PCI8664_CreateDevice( DeviceLgcID );
		
   if( hDevice_AD == INVALID_HANDLE_VALUE ) 
   {
	  AfxMessageBox( "init error!") ;
			
	  g_ad_device_init =  false ;
	}
	else
	{
      g_ad_device_init = true ;
	}
}	

memset(&ADPara, sizeof(ADPara), 0x00);	// reset the parameters to certainty value 0 (strongly recommended) 

// Preset hardware parameters
ADPara.ADMode		= PCI8664_ADMODE_SEQUENCE;		// continuous sampling

ADPara.FirstChannel = 12 ;							// first channel

ADPara.LastChannel	= 14 ;							// last channel

ADPara.Frequency	= 1000000;						// sampling frequency(Hz)

ADPara.GroupInterval= 1 ;							// group interval(uS)

ADPara.LoopsOfGroup = 1 ;							// loops of group

ADPara.Gains		= PCI8664_GAINS_1MULT;

//ADPara.InputRange	= PCI8664_INPUT_N5000_P5000 ;	// 输入范围： + - 5V // Analog Input Range range

ADPara.InputRange	= PCI8664_INPUT_0_P10000 ; 

ADPara.TriggerMode	= PCI8664_TRIGMODE_SOFT;		// software trigger

ADPara.TriggerType	= PCI8664_TRIGTYPE_EDGE;		// edge trigger 

ADPara.TriggerDir   = PCI8664_TRIGDIR_NEGATIVE;		// negative trigger	

ADPara.ClockSource	= PCI8664_CLOCKSRC_IN;			// internal clock

ADPara.bClockOutput = PCI8664_CLOCKOUT_DISABLE;

if(!PCI8664_InitDeviceProAD( hDevice_AD ,  &ADPara ) )		// Initial AD
{
    AfxMessageBox( "PCI采集卡AD参数设置失败！" ) ;

	return 0;  
}

return _OK ;
}
/*
nReadSizeWords = 1024*4; 

if(!PCI8664_StartDeviceProAD(hDevice)) // Start AD
{
    MessageBox( "PCI采集卡AD软件触发失败" ) ；

	return 0; 
}
*/


int  Fun_AD_Device_Init_Test( )
{
  DeviceLgcID = 0;

  hDevice_AD = PCI8664_CreateDevice(DeviceLgcID); // create device object

  if( hDevice_AD == INVALID_HANDLE_VALUE)
  {
		AfxMessageBox( "PCI采集卡初始化失败！" ) ;

		return 0; 
  }
			
memset( &ADPara, 0x00 , sizeof(ADPara) );	// reset the parameters to certainty value 0 (strongly recommended) 

// Preset hardware parameters
//ADPara.ADMode		= PCI8664_ADMODE_GROUP ; //PCI8664_ADMODE_SEQUENCE;		// continuous sampling

ADPara.ADMode		= PCI8664_ADMODE_SEQUENCE;

ADPara.FirstChannel = 15 ;							// first channel
//ADPara.FirstChannel = 15 ;

//ADPara.LastChannel	= _AD_SAMPLE_CHANNEL_MAX ;							// last channel

ADPara.LastChannel	= 17 ;

ADPara.Frequency	= 1000000;						// sampling frequency(Hz)

ADPara.GroupInterval= 1 ;							// group interval(uS)

ADPara.LoopsOfGroup = 1 ;							// loops of group

ADPara.Gains		= PCI8664_GAINS_1MULT ;

//const long PCI8664_INPUT_N10000_P10000	= 0x00; // ±10000mV
//const long PCI8664_INPUT_N5000_P5000	= 0x01; // ±5000mV
//const long PCI8664_INPUT_0_P10000

ADPara.InputRange	= PCI8664_INPUT_N10000_P10000 ;	// 输入范围： + - 5V // Analog Input Range range

ADPara.TriggerMode	= PCI8664_TRIGMODE_POST;		// external trigger

//ADPara.TriggerMode	= PCI8664_TRIGMODE_SOFT;

//ADPara.TriggerType	= PCI8664_TRIGTYPE_EDGE;		// edge trigger
 
ADPara.TriggerType	= PCI8664_TRIGTYPE_PULSE ;

ADPara.TriggerDir   = PCI8664_TRIGDIR_POSITIVE;		// positive trigger	

ADPara.ClockSource	= PCI8664_CLOCKSRC_IN;			// internal clock

ADPara.bClockOutput = PCI8664_CLOCKOUT_DISABLE;

ADPara.TimeoutForNpt  = 60 ; 


///*
if(!PCI8664_InitDeviceProAD( hDevice_AD ,  &ADPara ) )		// Initial AD
{
    AfxMessageBox( "PCI采集卡AD参数设置失败！" ) ;

	return 0;  
}
//*/
return _OK ;
}
/*
nReadSizeWords = 1024*4; 

if(!PCI8664_StartDeviceProAD(hDevice)) // Start AD
{
    MessageBox( "PCI采集卡AD软件触发失败" ) ；

	return 0; 
}
*/