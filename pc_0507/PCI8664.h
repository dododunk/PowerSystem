#ifndef _PCI8664_DEVICE_
#define _PCI8664_DEVICE_
//***********************************************************
// AD hardware parameters structure
typedef struct _PCI8664_PARA_AD     
{
	LONG ADMode;            // AD Mode
	LONG FirstChannel;      // First channel[0, 31]
	LONG LastChannel;       // Last channel[0, 31]
	LONG Frequency;         // Sample Rate (unit: Hz)
	LONG GroupInterval;     // Group Interval (unit: microsecond)[1, 419430]
	LONG LoopsOfGroup;	    // Lops of group[1, 255]
	LONG Gains;				// Gain Option
	LONG InputRange;		// Analog Input Range range
	LONG TriggerMode;       // select trigger mode
	LONG TriggerSource;		// select trigger source
	LONG TrigLevelVolt;		// Trigger Level
	LONG TriggerType;		// select trigger type(edge trigger/level trigger)
	LONG TriggerDir;		// select trigger direction(negative trigger/positive trigger)
	LONG ClockSource;		// select clock source
	LONG bClockOutput;      // allow Clock Output,=TRUE:allow Clock Output, =FALSE:forbid Clock Output
	LONG TimeoutForNpt ;

} PCI8664_PARA_AD, *PPCI8664_PARA_AD;

//***********************************************************
// hardware parameter:select the  ADMode of the PCI8664_PARA_AD
const long PCI8664_ADMODE_SEQUENCE		= 0x00; // Continuous Sampling
const long PCI8664_ADMODE_GROUP			= 0x01; // Packet Acquisition

//***********************************************************
// Hardware parameter:select the Gains of the PCI8664_PARA_AD
const long PCI8664_GAINS_1MULT			= 0x00; // one time (use AD8251 amplifier)
const long PCI8664_GAINS_2MULT			= 0x01; // two times(use AD8251 amplifier)
const long PCI8664_GAINS_4MULT			= 0x02; // four times (use AD8251 amplifier)
const long PCI8664_GAINS_8MULT			= 0x03; // eight times(use AD8251 amplifier)

//***********************************************************
// AD hardware parameter:select the Input Range of the PCI8664_PARA_AD
const long PCI8664_INPUT_N10000_P10000	= 0x00; // ¡À10000mV
const long PCI8664_INPUT_N5000_P5000	= 0x01; // ¡À5000mV
const long PCI8664_INPUT_0_P10000		= 0x02; // 0¡«10000mV

//***********************************************************
// Hardware parameter:select the TriggerMode of the PCI8664_PARA_AD
const long PCI8664_TRIGMODE_SOFT		= 0x00; // software trigger(Internal trigger)
const long PCI8664_TRIGMODE_POST		= 0x01; // hardware trigger(External trigger)

//***********************************************************
// hardware parameter:select the TriggerSource of the PCI8664_PARA_AD
const long PCI8664_TRIGSRC_DTR_AD		= 0x00; // select ATR to be trigger source
const long PCI8664_TRIGSRC_ATR_AD		= 0x01; // select DTR to be trigger source

//***********************************************************
// Hardware parameter:select the TriggerType of the PCI8664_PARA_AD
const long PCI8664_TRIGTYPE_EDGE		= 0x00; // edge trigger
const long PCI8664_TRIGTYPE_PULSE		= 0x01; // level trigger

//***********************************************************
// AD hardware parameter:select the TriggerDir of the PCI8664_PARA_AD
const long PCI8664_TRIGDIR_NEGATIVE		= 0x00; // negative trigger(low level or falling trigger)
const long PCI8664_TRIGDIR_POSITIVE		= 0x01; // positive trigger(high level or rising trigger)
const long PCI8664_TRIGDIR_NEGAT_POSIT	= 0x02; // positive and negative trigger(high/low or falling/rising trigger)

//***********************************************************
// AD hardware parameter:select the ClockSource of the PCI8664_PARA_AD
const long PCI8664_CLOCKSRC_IN			= 0x00;	// internal clock
const long PCI8664_CLOCKSRC_OUT			= 0x01;	// external clock

//***********************************************************
// Hardware parameter:select the Clock source of the PCI8664_PARA_AD
const long PCI8664_CLOCKOUT_DISABLE		= 0x00; // clock output disable
const long PCI8664_CLOCKOUT_ENABLE		= 0x01; // clock output enable

//*************************************************************************************
// AD status hardware parameters
typedef struct _PCI8664_STATUS_AD     
{
	LONG bNotEmpty;			//  not empty flag,if FIFO is empty, the value is false, otherwise it is true.
	LONG bHalf;				//  half flag,if the data is more than the half of the FIFO's capacity, the value is true , otherwise it is false.
	LONG bDynamic_Overflow; //  dynamic overflow flag, the value is true when overflow, otherwise it is false.
	LONG bStatic_Overflow;  //  static overflow flag,the value is true when overflow, otherwise it is false.
	LONG bConverting;		//  Whether AD is converting ,true stands for AD is converting and false stands for converting has finished.
	LONG bTriggerFlag;		//  trigger flag, true means that trigger has happened and false means that trigger does not happen.
} PCI8664_STATUS_AD, *PPCI8664_STATUS_AD;

const int PCI8664_MAX_SEGMENT_COUNT = 64;
typedef struct _PCI8664_STATUS_DMA     
{
	LONG iCurSegmentID;								// current segment ID means that the segment is busy.
	LONG bSegmentSts[PCI8664_MAX_SEGMENT_COUNT];	// 1 stands for the data in the current segment which has been got by the user
													// 0 stands for the data in the current segment has not been got by the user
	LONG bBufferOverflow;							// return to status of overflow
} PCI8664_STATUS_DMA, *PPCI8664_STATUS_DMA;

// parameters selection of the Mode parameter in  CreateFileObject
#define PCI8664_modeRead          0x0000			// read mode 
#define PCI8664_modeWrite         0x0001			// write mode 
#define	PCI8664_modeReadWrite     0x0002			// read and write mode
#define PCI8664_modeCreate        0x1000			// create the file that does not exist, or rebuild the file that has existed 
#define PCI8664_typeText          0x4000			// operate file with text mode

//***********************************************************
// user function interface
#ifndef _PCI8664_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## Applicable basic operation to this equipment #################################
	DEVAPI HANDLE FAR PASCAL PCI8664_CreateDevice(int DeviceID = 0);		// create device object
	DEVAPI HANDLE FAR PASCAL PCI8664_CreateDeviceEx(int DevicePhysID = 0);  // use physics ID to creat device object
	DEVAPI int FAR PASCAL PCI8664_GetDeviceCount(HANDLE hDevice);			// get device number
	DEVAPI BOOL FAR PASCAL PCI8664_GetDeviceCurrentID(HANDLE hDevice,		// get current device ID
													PLONG DeviceLgcID, 
													PLONG DevicePhysID);
	DEVAPI BOOL FAR PASCAL PCI8664_ListDeviceDlg(HANDLE hDevice);			// list all PCI devices in the system
    DEVAPI BOOL FAR PASCAL PCI8664_ReleaseDevice(HANDLE hDevice);			// close device,prohibit the transmission and release resource

	//####################### AD read function #################################
	// Suitable for most common users. The interfaces are the simplest, the most efficient and the most reliable, so that users do not have to know the equipment.
	// Complex low-level hardware controlling protocols and the variety of software programming. Only use the following initialized equipment and read  
	// two funtions of the AD data can acquire the data more effiently and continously.
    DEVAPI BOOL FAR PASCAL PCI8664_InitDeviceProAD(						// Initialize the device. When returning TRUE,the device will immediately start the transmission
										HANDLE hDevice,					// device handle
										PPCI8664_PARA_AD pADPara);		// (hardware parameter, which only controls hardware's status  in this function).

    DEVAPI BOOL FAR PASCAL PCI8664_StartDeviceProAD(					// start the device after initialization
										HANDLE hDevice);				// device handle
	
    DEVAPI BOOL FAR PASCAL PCI8664_SetDevFreqencyAD(					
										HANDLE hDevice,					// device handle
										DWORD nADFrequency);			// AD Sample Frequency(Hz)

    DEVAPI BOOL FAR PASCAL PCI8664_ReadDeviceProAD_Npt(					// get AD data through the  non-empty mode
										HANDLE hDevice,					// device handle
										PSHORT pADBuffer,				// the buffer is used to receive the data											
										ULONG nReadSizeWords,			// read data size
										PLONG nRetSizeWords);			// to check the overflowing status of the FIFO(the default is not detected).

	DEVAPI BOOL FAR PASCAL PCI8664_GetDevStatusProAD(					// get status		
										HANDLE hDevice,					// device handle
										PPCI8664_STATUS_AD pADStatus);	// AD status structure
	///////////////////////////////////////////////////////////////////////
	DEVAPI BOOL FAR PASCAL PCI8664_ReadDeviceProAD_Half(				// get AD data through the half mode
										HANDLE hDevice,					// device handle
										PSHORT pADBuffer,				// the buffer is used to receive the data(need 65536 characters's space)
										ULONG nReadSizeWords,			// read data size
										PLONG nRetSizeWords);
								
    DEVAPI BOOL FAR PASCAL PCI8664_StopDeviceProAD(						// stop the device
										HANDLE hDevice);				// device handle

	DEVAPI BOOL FAR PASCAL PCI8664_ReleaseDeviceProAD(					// close the AD device, forbid the transmission and release resource.
									    HANDLE hDevice);				// device handle

	DEVAPI BOOL FAR PASCAL PCI8664_GetDevTriggerPos(				
									HANDLE hDevice,											        
									PULONG nTriggerPos);			
										
	//##################### AD read function (INT Function)###########################
	DEVAPI BOOL FAR PASCAL PCI8664_InitDeviceIntAD(						// initialize the device. the device is all set when returnning to TURE.
										HANDLE hDevice,					// device handle
										HANDLE hEvent,					// (break off event handlers, and it is created by the CreateSystemEvent)
										ULONG nFifoHalfLength,			// read into the data length relative to the offset point(Must be less than half-full length of the FIFO)
										PPCI8664_PARA_AD pPara);		// (hardware parameters,which only control the hardware's status in this function)
    DEVAPI BOOL FAR PASCAL PCI8664_StartDeviceIntAD(					// start the device after initialization
										HANDLE hDevice);				// device handle
	DEVAPI DWORD FAR PASCAL PCI8664_ReadDeviceIntAD(HANDLE hDevice,		// device handle
										PSHORT pADBuffer,				// the buffer is used to receive the original data													
										LONG nReadSizeWords,			// read AD data size(word)  
										PLONG nRetSizeWords);			// return to actual length of the transmission(word)
	
    DEVAPI BOOL FAR PASCAL PCI8664_StopDeviceIntAD(						// stop the device
										HANDLE hDevice);					
	DEVAPI BOOL FAR PASCAL PCI8664_ReleaseDeviceIntAD(HANDLE hDevice);	// device handle

	//##################### AD read function (DMA Function) ###########################
	BOOL DEVAPI FAR PASCAL PCI8664_InitDeviceDmaAD(						// initialize the device
										HANDLE hDevice,					// device handle
										HANDLE hDmaEvent,				// DMA event handle, it is created by the CreateSystemEvent
										SHORT ADBuffer[],				// user buffer
										LONG nReadSizeWords,			// read AD data size(word) 
										LONG nSegmentCount,				// the number of buffer subsections, value range 2-64 
										LONG nSegmentSizeWords,			// buffer subsection's length
										PPCI8664_PARA_AD pADPara);		// (hardware parameters,which only control the hardware's status in this function)

    BOOL DEVAPI FAR PASCAL PCI8664_StartDeviceDmaAD(					// start the device after initialization
										HANDLE hDevice);				// device handle

	BOOL DEVAPI FAR PASCAL PCI8664_GetDevStatusDmaAD(					// acquire DAM status in the process of AD sampling, 
										HANDLE hDevice,					// device handle
										PPCI8664_STATUS_DMA pDMAStatus);// DMA status

	BOOL DEVAPI FAR PASCAL PCI8664_SetDevStatusDmaAD(					// set DAM status in the process of AD sampling,
										HANDLE hDevice,					// device handle
										LONG iClrBufferID);				// clear the buffer ID, and the 0 will be its home.
		
    BOOL DEVAPI FAR PASCAL PCI8664_StopDeviceDmaAD(						// stop the device after it has worked.
										HANDLE hDevice);				// device handle

	BOOL DEVAPI FAR PASCAL PCI8664_ReleaseDeviceDmaAD(					// close the device,forbid the transmission and release the  resource
										HANDLE hDevice);				// device handle
   	
	//################# AD hardware parameter operation function ########################
	DEVAPI BOOL FAR PASCAL PCI8664_SaveParaAD(HANDLE hDevice, PPCI8664_PARA_AD pADPara);  
    DEVAPI BOOL FAR PASCAL PCI8664_LoadParaAD(HANDLE hDevice, PPCI8664_PARA_AD pADPara);
	DEVAPI BOOL FAR PASCAL PCI8664_ResetParaAD(HANDLE hDevice, PPCI8664_PARA_AD pADPara);

	//####################### on/off control function #################################
	//Users can use the function WriteRegisterULong and ReadRegisterULong can be used directly to control register for I/O  
	//Input and output, but it will be more convenient to use the following two functions,and you don't need to  care about the register distribution and operation, and you only need to control each switch channel as easy as the attributive operation for the VB language.
    DEVAPI BOOL FAR PASCAL PCI8664_SetDeviceDO(				// output on/off status
										HANDLE hDevice,		// device handle								        
										BYTE bDOSts[16]);	// on/off status

	DEVAPI BOOL FAR PASCAL PCI8664_GetDeviceDI(				// get on/off status 
										HANDLE hDevice,		// device handle								        
										BYTE bDISts[16]);	// on/off status 
	
	DEVAPI BOOL FAR PASCAL PCI8664_RetDeviceDO(				// read back on/off status
										HANDLE hDevice,		// device handle
										BYTE bDOSts[16]);	// on/off status

	//################# Memory-mapped registers operate, read and write function directly ########################
	// (Applicable for  the users who can control thisequipment more directly, more specificly, low-level and more complicatedly. 
	// For instance, special control process and control efficiency should go with the special control object , so users can achieve that by using these interfaces. 
	DEVAPI BOOL FAR PASCAL PCI8664_GetDeviceAddr(					// get the linearity base adress of the mapping register that has been named, and return to the device number.
												HANDLE hDevice,		// device handle
												PULONG LinearAddr,	// return linearity base adress
											    PULONG PhysAddr,	// physics adress
												int RegisterID);	// register ID£¨0-5£©
	DEVAPI BOOL FAR PASCAL PCI8664_GetDeviceBar(					// get the BAR address from the register has been named
											HANDLE hDevice,			// device handle
											ULONG  pulPCIBar[6]);	// return all BAR addresses
    DEVAPI BOOL FAR PASCAL PCI8664_WriteRegisterByte(				// write single word of data to the mapped register designate port of the device
											HANDLE hDevice,			// device handle
											ULONG LinearAddr,		// the linearity base adress of the mapping register has been named
											ULONG OffsetBytes,		// offset position relatives to the base address
											BYTE Value);			
	DEVAPI BOOL FAR PASCAL PCI8664_WriteRegisterWord(				// write double bytes data
											HANDLE hDevice, 
											ULONG LinearAddr, 
											ULONG OffsetBytes,  
											WORD Value);
	DEVAPI BOOL FAR PASCAL PCI8664_WriteRegisterULong(				// write four bytes data 
											HANDLE hDevice, 
											ULONG LinearAddr, 
											ULONG OffsetBytes,  
											ULONG Value);
	DEVAPI BYTE FAR PASCAL PCI8664_ReadRegisterByte(				// read single bytes data
											HANDLE hDevice, 
											ULONG LinearAddr, 
											ULONG OffsetBytes);
	DEVAPI WORD FAR PASCAL PCI8664_ReadRegisterWord(				// read double bytes data
											HANDLE hDevice, 
											ULONG LinearAddr, 
											ULONG OffsetBytes);
	DEVAPI ULONG FAR PASCAL PCI8664_ReadRegisterULong(				// read four bytes data
											HANDLE hDevice, 
											ULONG LinearAddr, 
											ULONG OffsetBytes);

	//################# I/O port operate, read and write function directly ########################
	//(Appliable for  the users who can control thisequipment more directly, more specificly, low-level and more complicatedly. 
	// For instance, special control process and control efficiency should go with the special control object , so users can achieve that by using these interfaces. 
	// But thesefunctions are mainly applicable to the traditional equipment, such as ISA bus, parallel port and serial port equipment, but it can not be used for the PCI epuipment.)
    DEVAPI BOOL FAR PASCAL PCI8664_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI8664_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI8664_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI8664_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL PCI8664_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL PCI8664_ReadPortULong(HANDLE hDevice, UINT nPort);

   	//######################### file operation function ##############################
    DEVAPI HANDLE FAR PASCAL PCI8664_CreateFileObject(			// initialize the file system
										  HANDLE hDevice,		// device handle
										  LPCTSTR NewFileName,	// new file name
										  int Mode);			// file operation mode   
    DEVAPI BOOL FAR PASCAL PCI8664_WriteFile(					// save the data in the user space
										HANDLE hFileObject,		// device handle,it creat by function of CreateDevice
										PVOID pDataBuffer,		// the space address of user data
										ULONG nWriteSizeBytes); // buffer size(byte)

    DEVAPI BOOL FAR PASCAL PCI8664_ReadFile(					// read data
										  HANDLE hFileObject,	// device handle,it creat by function of CreateDevice
										  PVOID pDataBuffer,	// user buffer that is used to receive the file data
										  ULONG OffsetBytes,	// the offset position begins from the front of the file
										  ULONG nReadSizeBytes); // read the byte size from the offset position

	DEVAPI BOOL FAR PASCAL PCI8664_SetFileOffset(				// set the offset pointer for the file
										  HANDLE hFileObject,   // device handle,it creat by function of CreateDevice
										  ULONG nOffsetBytes);  // file offsetposition

	DEVAPI ULONG FAR PASCAL PCI8664_GetFileLength(HANDLE hFileObject);	// get the length of the appointed file(byte)

    DEVAPI BOOL FAR PASCAL PCI8664_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI8664_GetDiskFreeBytes(				// acquire the disk spce (use 64 bytes variable)
								      LPCTSTR DiskName);				// disk name, such as  disk C is "C:\\", disk D is "D:\\"


	//########################### thread operation function ######################################
	DEVAPI HANDLE FAR PASCAL PCI8664_CreateSystemEvent(void);			// creat the (kernel) system event object.used by the InitDeviceInt and VB function 
	DEVAPI BOOL FAR PASCAL PCI8664_ReleaseSystemEvent(HANDLE hEvent);	// release (kernel) system event object
	
 	DEVAPI DWORD  FAR PASCAL PCI8664_GetLastErrorEx(					// get the the last error message		
																		// of the designated function from the error message database)
									LPCTSTR strFuncName,				// function's name is error. Pay more attention to the capitalization and lowercase
									LPTSTR strErrorMsg);				// return to the error message

	DEVAPI BOOL FAR PASCAL PCI8664_RemoveLastErrorEx(					// remove  the last error message
																		// of the designated function from the error message database)							
									LPCTSTR strFuncName);				// function's name is error,so pay more attention to the capitalization and lowercase


#ifdef __cplusplus
}
#endif

// Automatically include the driven function database
#ifndef _PCI8664_DRIVER_
	#pragma comment(lib, "PCI8664.lib")
	#pragma message("======== Welcome to use our art company's products!")
	#pragma message("======== Automatically linking with PCI8664.dll...")
	#pragma message("======== Successfully linked with PCI8664.dll")
#endif

#endif // _PCI8664_DEVICE_
