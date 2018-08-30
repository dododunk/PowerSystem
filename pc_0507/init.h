
#include "stdafx.h"




/////////AD card parameter////////////////////////

extern   HANDLE hDevice_AD ;  //采集卡对象句柄


extern   PCI8664_STATUS_AD    AD_Status ;//ad采集卡状态结构体

extern   int DeviceLgcID ;   

extern   PCI8664_PARA_AD ADPara ;		// Initialization AD parameter structure


extern   LONG nReadSizeWords;		// Each time the number of read  AD data

extern   LONG nRetSizeWords;

extern   int nADChannel ;

extern   SHORT ADData;

extern   bool   g_ad_device_init ;

#define AD_DATA_LEN 1024*8 

extern   SHORT   ADBuffer[AD_DATA_LEN]; // Receive AD data buffer

/////////AD card parameter////////////////////////


extern  void  Fun_PC_CLK_Init() ;

extern  int   Fun_AD_Device_Init( ) ;

extern  int   Fun_AD_Device_Init_Test( ) ;