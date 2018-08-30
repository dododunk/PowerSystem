// IFRMView.cpp : implementation of the CIFRMView class
//

#include "stdafx.h"
#pragma warning(disable : 4244)
#pragma warning(disable : 4258)
#pragma warning(disable : 4995)
#pragma warning(disable : 4996)


#include "MainFrm.h"
#include "IFRMView.h"
#include "Dask.h"
#include "math.h"
#include <comdef.h>
#include "Winbase.h"
#include "CRC.H"
#include "DataBaseInstance.h"
#include "RuntimeAccount.h"
#include "AppInfo.h"

//#include "AmetterRecordset.h"
#include "AmetterRecordset.h"
#include "CHANGEAMMETERset.h"

#include "BreadSettingDlg.h"
#include "SearchDlg.h"
#include "TransformerDlg.h"
#include "AmetterDlg.h"
#include "UserInfoDlg.h"
#include "LineLossDlg.h"
#include "DataInformationDlg.h"
#include "PassWordDlg.h"
#include "GarrisonDlg.h"
#include "ChartDlg.h"
#include "StationCommunDlg.h"
#include "ELKindDlg.h"
#include "SelectTableDlg.h"
#include "AngleSettingDlg.h"
#include "CondtionsDlg.h"
#include "PhaseTestDlg.h"
#include "TimeCheckDlg.h"
#include "ShowInfoDlg.h"
#include "AutoDateReadModuleDlg.h"
#include "TimeSelectDlg.h"
#include "ELECTDEALDlg.h"
#include "ProgressDlg.h"
#include "ZHULIUTIMESELECTDlg.h"
#include "CHANGEAMMETERDLG.h"
#include "Protcoldlg.h"
#include "TestCommDlg.h"
#include "WuGongDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFRMView
//short           DataBuf[190000];
short           DataBuf[800000];
short       	m_TestCurrent[140000];//电流
short           m_TestVoltage[140000];//电压
int             m_TestParameter[6];
int                     DataLen;
I16                        card;
BOOL                   bClearOp;
unsigned short   ReadBuff[1024];
I16                         err;
BOOLEAN       bStopped =  FALSE;
CWinThread     *ReadMeterThread;

IMPLEMENT_DYNCREATE(CIFRMView, CFormView)

BEGIN_MESSAGE_MAP(CIFRMView, CFormView)
//{{AFX_MSG_MAP(CIFRMView)
ON_WM_DESTROY()
ON_WM_SETFOCUS()
ON_WM_SIZE()



ON_COMMAND(ID_TESTREADTABLE, OnTestreadtable)
ON_COMMAND(ID_BREADORDER, OnBreadorder)
ON_COMMAND(ID_TRANFORMER, OnTranformer)
ON_COMMAND(ID_USERINFO, OnUserinfo)
ON_COMMAND(ID_AMMETERINFO, OnAmmeterinfo)
ON_COMMAND(ID_COMMUNICATION, OnCommunication)
ON_COMMAND(ID_STOPRUN, OnStoprun)
ON_WM_TIMER()
ON_COMMAND(ID_OWEMONEY, OnOwemoney)


ON_COMMAND(ID_PRICE, OnPrice)
ON_COMMAND(ID_DATAPASS, OnDatapass)
ON_UPDATE_COMMAND_UI(ID_CONNECTSUCCESS, OnUpdateConnectsuccess)
ON_COMMAND(ID_STOPEXAM, OnStopexam)
ON_COMMAND(ID_ANGLESET, OnAngleset)
ON_WM_PAINT()
ON_COMMAND(ID_PHASETEST, OnPhasetest)
ON_COMMAND(ID_TIMECHECK, OnTimecheck)
	ON_UPDATE_COMMAND_UI(ID_LST_SAVE, OnUpdateLstSave)
	ON_COMMAND(ID_AUTOREADSET, OnAutoreadset)
	ON_COMMAND(ID_BREAkSOMEDAY, OnBREAkSOMEDAY)
	ON_UPDATE_COMMAND_UI(ID_OWEMONEY, OnUpdateOwemoney)
	ON_COMMAND(ID_PASSUSERDATA, OnPassuserdata)
	ON_UPDATE_COMMAND_UI(ID_PASSUSERDATA, OnUpdatePassuserdata)
	ON_UPDATE_COMMAND_UI(ID_SHOWDIALOGBAR, OnUpdateShowdialogbar)
	ON_UPDATE_COMMAND_UI(ID_PHASETEST, OnUpdatePhasetest)
	ON_UPDATE_COMMAND_UI(ID_TESTREADTABLE, OnUpdateTestreadtable)
	ON_NOTIFY(NM_RCLICK, IDC_LISTSS, OnRclickListss)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_HIDEDATA, OnUpdateHidedata)
	ON_COMMAND(ID_SAVEREPORTAS, OnSavereportas)
	ON_UPDATE_COMMAND_UI(ID_SAVEREPORTAS, OnUpdateSavereportas)
	ON_UPDATE_COMMAND_UI(ID_REMOTEMODIFY, OnUpdateRemotemodify)
	
	
	
	ON_COMMAND(ID_GETDATAFROMLONG, OnGetdatafromlong)
	ON_COMMAND(ID_LOCALMODIFY, OnLocalmodify)
	ON_UPDATE_COMMAND_UI(ID_LOCALMODIFY, OnUpdateLocalmodify)
	ON_UPDATE_COMMAND_UI(ID_APPEARSELECTDATA, OnUpdateAppearselectdata)
	
	ON_UPDATE_COMMAND_UI(ID_BREAkSOMEDAY, OnUpdateBREAkSOMEDAY)
	
	ON_UPDATE_COMMAND_UI(ID_DELETEMODULE, OnUpdateDeletemodule)
	ON_COMMAND(ID_DELETEMODULE, OnDeletemodule)
	ON_UPDATE_COMMAND_UI(ID_ANGLESET, OnUpdateAngleset)
	ON_UPDATE_COMMAND_UI(ID_COMMUNICATION, OnUpdateCommunication)
	ON_UPDATE_COMMAND_UI(ID_DATAPASS, OnUpdateDatapass)
	ON_UPDATE_COMMAND_UI(ID_AUTOREADSET, OnUpdateAutoreadset)
	ON_UPDATE_COMMAND_UI(ID_BREADORDER, OnUpdateBreadorder)
	ON_COMMAND(ID_CLOSEREPORT, OnClosereport)
	ON_UPDATE_COMMAND_UI(ID_CLOSEREPORT, OnUpdateClosereport)
	ON_COMMAND(ID_TIMESEARCH, OnTimesearch)
	ON_COMMAND(ID_ZHULIUMODIFY, OnZhuliumodify)
	ON_COMMAND(ID_ZHENSHIMODIFY, OnZhenshimodify)
	ON_UPDATE_COMMAND_UI(ID_TIMESEARCH, OnUpdateTimesearch)
	ON_COMMAND(ID_GETFILE, OnGetfile)
	ON_UPDATE_COMMAND_UI(ID_DISCONNECT, OnUpdateDisconnect)
	ON_COMMAND(ID_CONNECTSUCCESS, OnConnectsuccess)
	ON_COMMAND(ID_STOPORSEND, OnStoporsend)
	ON_UPDATE_COMMAND_UI(ID_STOPORSEND, OnUpdateStoporsend)
	ON_UPDATE_COMMAND_UI(ID_DATAAPPEAR, OnUpdateDataappear)
	ON_UPDATE_COMMAND_UI(ID_LISTSELECT, OnUpdateListselect)
	ON_COMMAND(ID_CHECKEQAUL, OnCheckeqaul)
	ON_UPDATE_COMMAND_UI(ID_CHECKEQAUL, OnUpdateCheckeqaul)
	ON_COMMAND(ID_XIANGCHANGE, OnXiangchange)
	ON_UPDATE_COMMAND_UI(ID_XIANGCHANGE, OnUpdateXiangchange)
	ON_COMMAND(ID_CHECKLINESTATUS, OnChecklinestatus)
	ON_UPDATE_COMMAND_UI(ID_CHECKLINESTATUS, OnUpdateChecklinestatus)
	ON_COMMAND(ID_FINDREPEATRECORDS, OnFindrepeatrecords)
	ON_COMMAND(ID_FAUTOREADSET, OnFautoreadset)
	ON_UPDATE_COMMAND_UI(ID_FAUTOREADSET, OnUpdateFautoreadset)
	ON_COMMAND(ID_CANCELAUTOZHULIU, OnCancelautozhuliu)
	ON_UPDATE_COMMAND_UI(ID_CANCELAUTOZHULIU, OnUpdateCancelautozhuliu)
	ON_COMMAND(ID_CHANGEAMMETER, OnChangeammeter)
	ON_COMMAND(ID_MODIFYPROTCOL, OnModifyprotcol)
	ON_COMMAND(ID_WXCHECKSTATUS, OnWxcheckstatus)
	ON_COMMAND(ID_WUGONGPARAMETER, OnWugongparameter)
	ON_COMMAND(ID_WUGONGDEAL, OnWugongdeal)
	ON_UPDATE_COMMAND_UI(ID_WUGONGDEAL, OnUpdateWugongdeal)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_CLOSE()
	ON_COMMAND(ID_DRFROMACCESS, OnDrfromaccess)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_MESSAGE(WM_EVENT, OnEvent)
ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFRMView construction/destruction


CIFRMView::CIFRMView()
: CFormView(CIFRMView::IDD)
{
	//{{AFX_DATA_INIT(CIFRMView)
	//}}AFX_DATA_INIT
    //发送数据错误次数
	m_PassErrortimes       =     0;
	//电话拔号的标志
	m_IsDialConnectting    = FALSE;
	//是否接收数据标志
	m_ReceiveOk            = FALSE;
	//DialogBar是否存在的判断
	m_DialogBarVisible     =  TRUE;

	m_ModuleFindContionStr =    "";
	m_pSelection           =  NULL;
	m_strReceiveChar       =    "";
	m_iBandPassPoints      =    62;//70个有效点值
	m_ListRows             =     0;//测试读表行号
	m_times                =     1;
	m_iChSelect            =     0;
	m_StartRead            = FALSE;//TRUE;
	m_ZhuLiuTime           =    "";
	m_angles               =     0;
	
    Apppt = (CIFRMApp*)AfxGetApp();
	
	//参数传值变量
	m_PassValue           =      0;
	
	//传来的记录条数
	m_PassRecords         =      0;

	//定时读表参数
	//读哪些项

	TmpOnlyOneThreadRun.SetEvent();		//++

	for(int i = 0; i < 15; i++)
	{
		m_SetLabel[i]      = FALSE;//读表标志
        m_TimeSetLabel[i]  = FALSE;//定时读表标志
		Ports[i]           = FALSE;//串口是否能够打开TRUE  能用  FALSE 不能用
	}
	
	m_DayOrYear[0]         =  TRUE;//居民用表按月抄
	m_DayOrYear[1]         = FALSE;//非居民用表按天抄
	m_sendkind       =           0;// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
    //连接标志
	m_IsConnect      = FALSE;
	//当前传送后的位置
	m_LocalAddress   =     0;
	LowAddress       =     0;
    HighAddress      =     0;
	m_EveryUnit      =     0;
	
    ReadMeterThread   =  NULL;
	
	//手拉手编码
	m_handno         =     0;
	//是否定时发送信号
	m_status         =  TRUE;
	//生成的库名
//	m_ComeIntoDataName =  "";
	//定时读表
	m_TimeStrs       =    "";
	//是否自动发信息
	m_IsAutoSending  = FALSE;
	ReceiveByteArray.RemoveAll();
	//自动读表条件
	m_AutoReadCondtionStr = "";

	/*   英文字段转成汉字字段*/
	/**********1、电价数据表操作***************
	序号	名称	  字段英文名
	1	   用电编号	    ELECTRICITY_NO
	2	   用电种类	    ELECTRICITY_KIND
	3      电价	        ELECTRICITY_ PRICE
	4      备注	        ELECTRICITY_REMARK
	********************************************/
    TB_ELECTRICITYS.SetSize(8);	
	TB_ELECTRICITYS[0] = "ELECTRICITY_NO";
	TB_ELECTRICITYS[1] = "用电编号";
	TB_ELECTRICITYS[2] = "ELECTRICITY_KIND";
	TB_ELECTRICITYS[3] = "用电名称";
	TB_ELECTRICITYS[4] = "ELECTRICITY_PRICE";
	TB_ELECTRICITYS[5] = "电价";
	TB_ELECTRICITYS[6] = "ELECTRICITY_REMARK";
	TB_ELECTRICITYS[7] = "备注";
	/**********2、变台信息数据表操作*************
	序号	名称	     字段英文名
	1   	变台编号	TRANSFORMER_NO
	2   	变台型号	TRANSFORMER_TYPE
	3   	变台容量	TRANSFORMER_CAPACITY
	4	    安装时间	TRANSFORMER_INSTALLTIME
	5	    位置	    TRANSFORMER_POSITION
	6   	所有权   	TRANSFORMER_OWNERSHIP
	7	    接线形式   	TRANSFORMER_CONNECTFORM
	********************************************/

	TB_TRANSFORMERS.SetSize(14);
	TB_TRANSFORMERS[0]  = "TRANSFORMER_NO";
	TB_TRANSFORMERS[1]  = "变台名称";
	TB_TRANSFORMERS[2]  = "TRANSFORMER_TYPE";
	TB_TRANSFORMERS[3]  = "变台型号";
	TB_TRANSFORMERS[4]  = "TRANSFORMER_CAPACITY";
	TB_TRANSFORMERS[5]  = "变台容量";
    TB_TRANSFORMERS[6]  = "TRANSFORMER_INSTALLTIME";
	TB_TRANSFORMERS[7]  = "安装时间";
	TB_TRANSFORMERS[8]  = "TRANSFORMER_POSITION";
	TB_TRANSFORMERS[9]  = "位置";
    TB_TRANSFORMERS[10] = "TRANSFORMER_OWNERSHIP";
	TB_TRANSFORMERS[11] = "所有权";
	TB_TRANSFORMERS[12] = "TRANSFORMER_CONNECTFORM";
	TB_TRANSFORMERS[13] = "接线形式";


	/**********3、电表信息数据表操作*************
	序号	名称	   字段英文名
	1	    电表号码	AMMETER_NO
	2	    生产厂商	AMMETER_MANUFACTURER
	3    	电表型号	AMMETER_TYPE
	4	    脉冲率	    AMMETER_IMPULSE
	********************************************/

	TB_AMMETERS.SetSize(8);
	TB_AMMETERS[0] = "AMMETER_TYPE";
	TB_AMMETERS[1] = "电表型号";
	TB_AMMETERS[2] = "AMMETER_MANUFACTURER";
	TB_AMMETERS[3] = "生产厂商";
	TB_AMMETERS[4] = "AMMETER_IMPULSE";
	TB_AMMETERS[5] = "脉冲率";
	TB_AMMETERS[6] = "AMMETER_REMARK";
	TB_AMMETERS[7] = "备注";

	/**********4、用户信息库数据表操作*************
	序号	名称          	    字段英文名
	1	  公司名或供电局名称    USER_COMPANY
	2	  电站编号             	USER_STATIONNO
	3	  变电站名	            USER_STATIONNAME
	4	  线路编号            	USER_LINENO
	5     线路名称            	USER_LINENAME
	6	  变台名称	            USER_TRANSFORMERNO
	7	  模块号            	USER_MODULENO
	8     模块安装相别	        USER_PHASE
	9	  姓名	                USER_NAME
	10	  用户编号	            USER_NO
	11	  原用户号	            USER_OLDNO
	12	  住址	                USER_ADDRESS
	13	  电话	                USER_PHONE
	14	  用电种类	            USER_ELECTRICITYKIND
	15	  电表编号	            USER_AMMETERNO
	16	  电表型号	            USER_AMMETERTYPE
	16	  表计种类	            USER_AMMETERKIND
	17	  供电方式          	USER_SUPPLYMODE
	18	  安装时间          	USER_INSTALLTIME
	19	  电表初值	            USER_INITIALVALUE
	20	  倍率	                USER_MULTIPLE
	21	  用电描述	            USER_DESCRIBE
	22	  读数标志	            USER_READLABEL
	23	  用电状态	            USER_ETSTATUS
	********************************************/

	TB_USERS.SetSize(70);
	TB_USERS[0]  = "USER_COMPANY";
	TB_USERS[1]  = "供电局名称";
	TB_USERS[2]  = "USER_STATIONNO";
	TB_USERS[3]  = "电站编号";
	TB_USERS[4]  = "USER_STATIONNAME";
	TB_USERS[5]  = "变电站名";
	TB_USERS[6]  = "USER_MOTHERLINE";
    TB_USERS[7]  = "母线编号";
	TB_USERS[8]  = "USER_BAKMOTHERLINE";
    TB_USERS[9]  = "备用母线编号";
	TB_USERS[10] = "USER_LINENO";
	TB_USERS[11] = "出线编号";
	TB_USERS[12] = "USER_BAKLINENO";
	TB_USERS[13] = "备用出线编号";
	TB_USERS[14] = "USER_LINENAME";
	TB_USERS[15] = "线路名称";
	TB_USERS[16] = "USER_TRANSFORMERNO";
    TB_USERS[17] = "变台名称";
	TB_USERS[18] = "USER_MODULENO";
	TB_USERS[19] = "模块号";
	TB_USERS[20] = "USER_PHASE";
	TB_USERS[21] = "安装相别";
	TB_USERS[22] = "USER_NAME";
	TB_USERS[23] = "姓名";
	TB_USERS[24] = "USER_NO";
	TB_USERS[25] = "用户编号";
	TB_USERS[26] = "USER_OLDNO";
	TB_USERS[27] = "原用户号";
	TB_USERS[28] = "USER_ADDRESS";
	TB_USERS[29] = "住址";
	TB_USERS[30] = "USER_PHONE";
	TB_USERS[31] = "电话";  
	TB_USERS[32] = "USER_ELECTRICITYKIND";
	TB_USERS[33] = "用电编号";
	TB_USERS[34] = "USER_AMMETERNO";
	TB_USERS[35] = "表卡编号";
	TB_USERS[36] = "USER_AMMETERKIND";
	TB_USERS[37] = "表计种类";	
	TB_USERS[38] = "USER_INSTALLTIME";
	TB_USERS[39] = "安装时间";
	TB_USERS[40] = "USER_SUPPLYMODE";
	TB_USERS[41] = "供电方式";
	TB_USERS[42] = "USER_INITIALVALUE";
	TB_USERS[43] = "电表初值";
	TB_USERS[44] = "USER_MULTIPLE";
	TB_USERS[45] = "倍率";
	TB_USERS[46] = "USER_PROTOCOL";
	TB_USERS[47] = "抄表协议";
	TB_USERS[48] = "USER_DESCRIBE";
	TB_USERS[49] = "用电描述";
	TB_USERS[50] = "USER_READLABEL";
	TB_USERS[51] = "系统字段";
	TB_USERS[52] = "USER_TIMELABEL";
	TB_USERS[53] = "系统字段";
	TB_USERS[54] = "USER_ETSTATUS";
	TB_USERS[55] = "用电状态";
	TB_USERS[56] = "USER_IDNO";
	TB_USERS[57] = "模块索引";
	TB_USERS[58] = "USER_AMMETERTYPE";
	TB_USERS[59] = "电表型号";
	TB_USERS[60] = "USER_SENDANGLE";
	TB_USERS[61] = "信号强度";
	TB_USERS[62] = "USER_DOWNVALUE";
	TB_USERS[63] = "月报警量下限";	
	TB_USERS[64] = "USER_UPVALUE";
	TB_USERS[65] = "月报警量上限";
	TB_USERS[66] = "USER_RUNSTATUS";
	TB_USERS[67] = "运行状态";
	TB_USERS[68] = "USER_ZHULABEL";
	TB_USERS[69] = "系统字段";

	/**********5、驻留数据表操作*************
	序号	名称          	    字段英文名
	1   	模块号      	GARRISON_MODULENO
	2   	有功电度    	GARRISON_WORKDEGREE
	3   	手拉手有功总	GARRISON_WORKDEGREETOTAL
	4	    无功电度    	GARRISON_LOSEDEGREE
	5	    手拉手无功总	GARRISON_LOSEDEGREETOTAL
	6	    A相电流	        GARRISON_ACURRENT
	7    	B相电流     	GARRISON_BCURRENT
	8	    C相电流     	GARRISON_CCURRENT
	9	    A相电压     	GARRISON_AVOLTAGE
	10   	B相电压	        GARRISON_BVOLTAGE
	11	    C相电压	        GARRISON_CVOLTAGE
	12
	13
	14
	15
	16	    抄表时间	    GARRISON_TRANSCRIBETIME
	17   	对应协议	    GARRISON_PROTOCOL
	18	    驻留时间	    GARRISON_HALTTIME
	********************************************/

	TB_GARRISONS.SetSize(38);
	TB_GARRISONS[0]  = "GARRISON_MODULENO";
	TB_GARRISONS[1]  = "模块号";
	TB_GARRISONS[2]  = "GARRISON_WORKDEGREE";
	TB_GARRISONS[3]  = "有功电度";
    TB_GARRISONS[4]  = "GARRISON_WORKDEGREETOTAL";
	TB_GARRISONS[5]  = "手拉手有功总";
	TB_GARRISONS[6]  = "GARRISON_LOSEDEGREE";
	TB_GARRISONS[7]  = "无功电度";
    TB_GARRISONS[8]  = "GARRISON_LOSEDEGREETOTAL";
	TB_GARRISONS[9]  = "手拉手无功总";
	TB_GARRISONS[10] = "GARRISON_ACURRENT";
	TB_GARRISONS[11] = "A相电流";
	TB_GARRISONS[12] = "GARRISON_BCURRENT";
	TB_GARRISONS[13] = "B相电流" ;
    TB_GARRISONS[14] = "GARRISON_CCURRENT";
	TB_GARRISONS[15] = "C相电流";
	TB_GARRISONS[16] = "GARRISON_AVOLTAGE";
	TB_GARRISONS[17] = "A相电压";
	TB_GARRISONS[18] = "GARRISON_BVOLTAGE";
	TB_GARRISONS[19] = "B相电压";
	TB_GARRISONS[20] = "GARRISON_CVOLTAGE";
	TB_GARRISONS[21] = "C相电压" ;
    TB_GARRISONS[22] = "GARRISON_JFDL";
    TB_GARRISONS[23] = "尖峰电量";
	TB_GARRISONS[24] = "GARRISON_FDL";
    TB_GARRISONS[25] = "峰电量";
	TB_GARRISONS[26] = "GARRISON_PDL";
    TB_GARRISONS[27] = "平电量";				   
   	TB_GARRISONS[28] = "GARRISON_GDL";
    TB_GARRISONS[29] = "谷电量";
	TB_GARRISONS[30] = "GARRISON_GLYS";
    TB_GARRISONS[31] = "功率因数";
    TB_GARRISONS[32] = "GARRISON_TRANSCRIBETIME";
	TB_GARRISONS[33] = "抄表时间";
    TB_GARRISONS[34] = "GARRISON_PROTOCOL";
	TB_GARRISONS[35] = "对应协议";
	TB_GARRISONS[36] = "GARRISON_HALTTIME";
	TB_GARRISONS[37] = "驻留时间";

	/**********6、数据表操作*************
	序号	名称          	    字段英文名
	1   	模块号      	REALTIME_MODULENO
	2   	有功电度    	REALTIME_WORKDEGREE
	3   	手拉手有功总	REALTIME_WORKDEGREETOTAL
	4	    无功电度    	REALTIME_LOSEDEGREE
	5	    手拉手无功总	REALTIME_LOSEDEGREETOTAL
	6	    A相电流	        REALTIME_ACURRENT
	7    	B相电流     	REALTIME_BCURRENT
	8	    C相电流     	REALTIME_CCURRENT
	9	    A相电压     	REALTIME_AVOLTAGE
	10   	B相电压	        REALTIME_BVOLTAGE
	11	    C相电压	        REALTIME_CVOLTAGE
	12	    抄表时间	    REALTIME_TRANSCRIBETIME
	13   	对应协议	    REALTIME_PROTOCOL
	********************************************/

	TB_REALTIMES.SetSize(36); 	
	TB_REALTIMES[0]  = "REALTIME_MODULENO";
	TB_REALTIMES[1]  = "模块号";
	TB_REALTIMES[2]  = "REALTIME_WORKDEGREE";
	TB_REALTIMES[3]  = "有功电度";
    TB_REALTIMES[4]  = "REALTIME_WORKDEGREETOTAL";
	TB_REALTIMES[5]  = "手拉手有功总";
	TB_REALTIMES[6]  = "REALTIME_LOSEDEGREE";
	TB_REALTIMES[7]  = "无功电度";
    TB_REALTIMES[8]  = "REALTIME_LOSEDEGREETOTAL";
	TB_REALTIMES[9]  = "手拉手无功总";
	TB_REALTIMES[10] = "REALTIME_ACURRENT";
	TB_REALTIMES[11] = "A相电流";
	TB_REALTIMES[12] = "REALTIME_BCURRENT";
	TB_REALTIMES[13] = "B相电流";
	TB_REALTIMES[14] = "REALTIME_CCURRENT";
	TB_REALTIMES[15] = "C相电流";
	TB_REALTIMES[16] = "REALTIME_AVOLTAGE";
	TB_REALTIMES[17] = "A相电压";
	TB_REALTIMES[18] = "REALTIME_BVOLTAGE";
	TB_REALTIMES[19] = "B相电压";
	TB_REALTIMES[20] = "REALTIME_CVOLTAGE";
	TB_REALTIMES[21] = "C相电压";
	TB_REALTIMES[22] = "REALTIME_JFDL";
    TB_REALTIMES[23] = "尖峰电量";
	TB_REALTIMES[24] = "REALTIME_FDL";
    TB_REALTIMES[25] = "峰电量";
	TB_REALTIMES[26] = "REALTIME_PDL";
    TB_REALTIMES[27] = "平电量";				   
   	TB_REALTIMES[28] = "REALTIME_GDL";
    TB_REALTIMES[29] = "谷电量";
    TB_REALTIMES[30] = "REALTIME_GLYS";
    TB_REALTIMES[31] = "功率因数";
	TB_REALTIMES[32] = "REALTIME_TRANSCRIBETIME";
	TB_REALTIMES[33] = "抄表时间";
    TB_REALTIMES[34] = "REALTIME_PROTOCOL";
	TB_REALTIMES[35] = "对应协议";

	/*
	CREATE TABLE [dbo].[TB_CHANGEAMMETER] (
	[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,
	[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,
	[CHANGEAMMETER_WORKDEGREETOTAL] [float] NULL ,
	[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,
	[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NULL ,
	[CHANGEAMMETER_JFDL] [float] NULL ,
	[CHANGEAMMETER_FDL] [float] NULL ,
	[CHANGEAMMETER_PDL] [float] NULL ,
	[CHANGEAMMETER_GDL] [float] NULL ,
	[CHANGEAMMETER_GLYS] [float] NULL ,
	[CHANGEAMMETER_UPDATETIME] [datetime] NULL ,
	[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL 
    */

	//换表信息
	TB_CHANGEAMMETERS.SetSize(44);
	TB_CHANGEAMMETERS[0] = "CHANGEAMMETER_MODULENOOLD";
	TB_CHANGEAMMETERS[1] = "原接模块号";
	TB_CHANGEAMMETERS[2] = "CHANGEAMMETER_MODULENO";
	TB_CHANGEAMMETERS[3] = "新接模块号";
	TB_CHANGEAMMETERS[4] = "CHANGEAMMETER_NOOLD";
	TB_CHANGEAMMETERS[5] = "原接电表编号";
	TB_CHANGEAMMETERS[6] = "CHANGEAMMETER_NO";
	TB_CHANGEAMMETERS[7] = "新接电表编号";
	TB_CHANGEAMMETERS[8] = "CHANGEAMMETER_WORKDEGREEOLD";
	TB_CHANGEAMMETERS[9] = "原有功电度差值";
	TB_CHANGEAMMETERS[10] = "CHANGEAMMETER_WORKDEGREE";
	TB_CHANGEAMMETERS[11] = "有功电度值";
	TB_CHANGEAMMETERS[12] = "CHANGEAMMETER_WORKDEGREETOTALOLD";
	TB_CHANGEAMMETERS[13] = "原手拉手有功总";	
	TB_CHANGEAMMETERS[14] = "CHANGEAMMETER_WORKDEGREETOTAL";
	TB_CHANGEAMMETERS[15] = "手拉有总差值";	
	TB_CHANGEAMMETERS[16] = "CHANGEAMMETER_LOSEDEGREEOLD";
	TB_CHANGEAMMETERS[17] = "原无功电度值";
	TB_CHANGEAMMETERS[18] = "CHANGEAMMETER_LOSEDEGREE";
	TB_CHANGEAMMETERS[19] = "无功电度差值";
	TB_CHANGEAMMETERS[20] = "CHANGEAMMETER_LOSEDEGREETOTALOLD";
	TB_CHANGEAMMETERS[21] = "原手拉无功总";
	TB_CHANGEAMMETERS[22] = "CHANGEAMMETER_LOSEDEGREETOTAL";
	TB_CHANGEAMMETERS[23] = "手拉无总差值";
	TB_CHANGEAMMETERS[24] = "CHANGEAMMETER_JFDLOLD";
	TB_CHANGEAMMETERS[25] = "原尖峰电量值";
	TB_CHANGEAMMETERS[26] = "CHANGEAMMETER_JFDL";
	TB_CHANGEAMMETERS[27] = "尖峰电量差值";	
	TB_CHANGEAMMETERS[28] = "CHANGEAMMETER_FDLOLD";
	TB_CHANGEAMMETERS[29] = "原峰电量值";	
	TB_CHANGEAMMETERS[30] = "CHANGEAMMETER_FDL";
	TB_CHANGEAMMETERS[31] = "峰电量差值";
	TB_CHANGEAMMETERS[32] = "CHANGEAMMETER_PDLOLD";
	TB_CHANGEAMMETERS[33] = "原平电量值";
	TB_CHANGEAMMETERS[34] = "CHANGEAMMETER_PDL";
	TB_CHANGEAMMETERS[35] = "平电量差值";	
	TB_CHANGEAMMETERS[36] = "CHANGEAMMETER_GDLOLD";
	TB_CHANGEAMMETERS[37] = "原谷电量值";
	TB_CHANGEAMMETERS[38] = "CHANGEAMMETER_GDL";
	TB_CHANGEAMMETERS[39] = "谷电量差值";
	TB_CHANGEAMMETERS[40] = "CHANGEAMMETER_UPDATETIME";
	TB_CHANGEAMMETERS[41] = "换电表时间";
	TB_CHANGEAMMETERS[42] = "CHANGEAMMETER_NAME";
	TB_CHANGEAMMETERS[43] = "换表人姓名";

    //服务器地址、用户名、密码
	m_address        = "10.127.2.2";// 192.168.18.10
	m_loginname      = "yingkang";
	m_password       = "YingKang";
	m_FtpFileName    = "ykdocs.csv";
	m_QuickReading   =        FALSE;//打包读表
	m_QuickModuleAddress =         0;//快速读表的地址
	m_QuickReadModuleValue =      -1;//快速读表的值
	/*
	m_address          =        "192.168.18.10";// 
	m_loginname        =        "yk";
	m_password         =        "yk";
    */

	m_port             =          21;
	//包头专用标志

	Received           =           0;//判段接收数据的种类	1 －本软件的接收 2－与湖南长沙来的通讯

	//循环次数,默认是1 次
	m_Recycles         =     1;
	//轮之间时间间隔,默认是30分钟
	m_SetRecycleTime   =    30;
	//定时读表的次数
	m_ReadModuleTimes  =     0;
	//发驻留次数
	m_SendGarrisonTimes=     0;

	m_IsHistory        = FALSE;//是否显示历史数据
	m_BackRgbValue     = RGB(255,255,255);//0xFF, 0xFF, 0xE0);
	m_GetDataFromFile  = FALSE;

	//得到错误的次数
	m_GetErrors        =     0;
	//停止传送数据
	m_StopPassing      = FALSE;

	//读表参数
	int ii;
	for(ii = 0; ii < 106; ii ++)
	{
		m_parameter[ii] = 0;
	}

	//FALSE 其它读表  TRUE  驻留读表
	m_others          =   FALSE;
	m_IfChangeData    =   FALSE;//接收远程数据的标志 
	m_DoubleConnected =    TRUE;
	m_SettimerValues  =  600000;//10分钟,定时读驻留或手拉手调制时用
	m_saveyears       =       2;//所有的读表数据保存为2年
    m_Pause           =   FALSE;//线程暂停标志
	m_CheckReading    =   FALSE;//监视读表

	//按驻留日期设置驻留参数
	for(ii = 0; ii < 67; ii ++)
	{
		m_DateReadParameter[ii] = 0;
	}

	m_zhuliukinds       =         0;//0 按表计种类下驻留 1 按日期下驻留

   	for(ii = 0; ii < 128; ii ++)
	{
		m_AllLineThreeCurrent[ii] = 0;//存32条线路4次电流,各线路的电流值最多2*16=32 32*3 = 96 每条线路存3次电流
	}	

	m_Thread_PRIORITY = (DWORD)THREAD_PRIORITY_ABOVE_NORMAL;//THREAD_PRIORITY_ABOVE_NORMAL;//线程级别 THREAD_PRIORITY_NORMAL THREAD_PRIORITY_ABOVE_NORMAL THREAD_PRIORITY_HIGHEST

	m_WgLess          =    0;//无功的种类 0 10分钟 1 20分钟  2 30分钟

}


CIFRMView::~CIFRMView()
{ 
	
	//TRUE 变电站版本  FALSE 电局版
	if(	AppInfo::Instance().m_WhichKind == TRUE)
	{

		//删除采集卡
		if(card == 0)
		{
			Release_Card(card);
		}

	}
    
	m_StartRead  = FALSE;

	//得到修改状态
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("报表已修改,保存报表文件吗?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{

             OnSavereportas(); 

		}

	}

}

void CIFRMView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFRMView)
	DDX_Control(pDX, IDC_MSCOMM, m_Com);
	DDX_Control(pDX, IDC_WINSOCK, m_WinSocket);
	DDX_Control(pDX, IDC_485MSCOMM, m_485MsComm);
	DDX_Control(pDX, IDC_PRINTREPORTS, m_Grid);
	//}}AFX_DATA_MAP
}

BOOL CIFRMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(WHITE_BRUSH),0);
	return CFormView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CIFRMView printing

BOOL CIFRMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;
	
	return TRUE;
}

void CIFRMView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{	
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	//得到选择读表的条件
    if(pMainFrm->m_wndMyDialogBar.IsWindowVisible())
	{	
		
		//如果没有记录
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0)
		{
			
			m_DialogBarVisible  = TRUE;
		    pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
			pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
			//重新布局
         	pMainFrm->RecalcLayout();

		}
	
	}
    
	m_Grid.SetFixedBkColor(RGB(255,255,255));
	m_Grid.OnBeginPrinting(pDC, pInfo);

}

void CIFRMView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
	if(m_DialogBarVisible)
	{

		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		ASSERT_VALID(pMainFrm);
		//如果没有记录
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0  && m_DialogBarVisible  == TRUE)
		{

		    //得到选择读表的条件
		    pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
            pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			//重新布局
         	pMainFrm->RecalcLayout();

		}
	

	}
	
	m_Grid.SetFixedBkColor(RGB(212,208,200));
    m_Grid.OnEndPrinting(pDC, pInfo);
}

void CIFRMView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	m_Grid.OnPrint(pDC, pInfo);

	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CIFRMView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	CFormView::OnDestroy();
	
    Sleep(100);
	
	//TRUE 变电站版本  FALSE电局版
	if(	AppInfo::Instance().m_WhichKind == TRUE)
	{
		
		//销毁计时器
		for(int i = 1; i <= 3; i++)
		{

			KillTimer(i);
		
		}
		
	}
	else
	{
		//定期取数据
		KillTimer(2);
		KillTimer(3);
	}
	
}




void CIFRMView::OnSize(UINT nType, int cx, int cy)
{
	
	//控件定位置
	CRect          rect;
    GetClientRect(rect);
	//控件定位置
    ::SetWindowPos(m_Grid,HWND_TOP,0,0,rect.Width(),rect.Height(),SWP_SHOWWINDOW);//SWP_DRAWFRAME);//

}

/////////////////////////////////////////////////////////////////////////////
// CIFRMView diagnostics

#ifdef _DEBUG
void CIFRMView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIFRMView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIFRMView message handlers

BEGIN_EVENTSINK_MAP(CIFRMView, CFormView)
//{{AFX_EVENTSINK_MAP(CIFRMView)
ON_EVENT(CIFRMView, IDC_MSCOMM,  1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 2 /* ConnectionRequest */, OnConnectionRequestWinsock, VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 0 /* DataArrival */, OnDataArrivalWinsock, VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 5 /* Close */, OnCloseWinsock, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 1 /* Connect */, OnConnectWinsock, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 6 /* Error */, OnErrorWinsock, VTS_I2 VTS_PBSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_PBOOL)
ON_EVENT(CIFRMView, IDC_WINSOCK, 3 /* SendProgress */, OnSendProgressWinsock, VTS_I4 VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 4 /* SendComplete */, OnSendCompleteWinsock, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


//工作线程
UINT WorkerThread( LPVOID pParam )
{
	
	//接收一个窗口类指针，然后设置窗口标题
	int type =(int)pParam;
	CMainFrame* pts   = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CIFRMView* pview = (CIFRMView *)(pts->GetActiveView());

	pview->m_StartRead  = TRUE;

    //开始工作
	switch(type)
	{
	case 0:
		{   
			//设置读的标志
            pview->SetDataReadLabel(pview->SendContionStr);	//循环次数,默认是1 次
			pview->FiveDataChuLi("测试读表",pview->m_SetLabel,FALSE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 1:
		{	
			//设置读的标志
            pview->SetDataReadLabel(pview->SendContionStr);
			pview->FiveDataChuLi("正式读表",pview->m_SetLabel,TRUE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 2:
		{
			//设置读的标志
            pview->SetDataReadLabel(pview->SendContionStr);
			pview->FiveDataChuLi("驻留读表",pview->m_SetLabel,TRUE, 1, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 3://其它处理
		{
			
			//读写各项测试参数,处理各项参数
			//CString title        列标题
			//CString Result       结论
			//CString ConStr       条件范围
			//BYTE    orders       命令关键字
			//BOOL    OnlyReadNot  TRUE  只读没有测试出相的模块
			//                     FALSE 反之
			//int     times        读每个模块的次数
			//BOOL    OnlyOnce     TRUE  好多表共用一个模块时只测试一次   FALSE 每个表都测试一次
			//int     MaxIValue    最大值(为写参数时用)
			//int     MinIValue    最小值
			//int     intervals    间  隔
			//(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals)
            //分解条件
			int         k,l;
			k  =  l  =    0;
			CString str[10];

			while((k = pview->SendContionStr.Find(';')) != -1) 
			{
				
				//以";"来分析条件
				str[l] = pview->SendContionStr.Left(k);
				pview->SendContionStr =	pview->SendContionStr.Right(pview->SendContionStr.GetLength()- k - 1);
				if(l > 9)
				{
					return 0;
				}
				l++;
				
				
			}

			str[9] = pview->SendContionStr;
			pview->DisposeModuleParameter(str[0],str[1],str[2],atoi(str[3]),atoi(str[4]),atoi(str[5]),atoi(str[6]),atoi(str[7]),atoi(str[8]),atoi(str[9]));
			break;
		}
	case 4:
		{
			//发驻留停止后,开始读驻留数据
			pview->FiveDataChuLi("定时驻留",pview->m_TimeSetLabel,TRUE, 1, pview->m_AutoReadCondtionStr,1,1,1);
			break;
		}
	case 5:
		{   
			//检测线路运行状态
			pview->SendMessage(WM_EVENT, 15, 0);
    		break;
		} 
	case 6:
		{    
			//发定时驻留用
			pview->SendBreadorder(pview->m_AutoReadTime,pview->m_SendGarrisonTimes);
			
			//检测线路运行状态
			if(pview->m_StartRead)
			{
				CTime timet = CTime::GetCurrentTime();
				
				if(timet.GetMinute() < 30)
				{
					//检测线路电流
				//	pview->SendMessage(WM_EVENT, 15, 0);
					
					//检测无线模块电流电压
				//	pview->SendMessage(WM_EVENT, 17, 0);
					
					//检测无功补偿表操作
					pview->SendMessage(WM_EVENT, 18, 0);
					
				}

			}

    		break;
		}
	case 7:
		{    
			//定期更新用户数据表
			pview->GetDataFormMarketServer(pview->m_address,pview->m_loginname,pview->m_password,pview->m_FtpFileName,pview->m_port);
    		break;
		}
	case 8:
		{
			//驻留读表中,只读没有读出的记录 2004.11.2加
			pview->FiveDataChuLi("驻留读表",pview->m_SetLabel,TRUE, 1, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 9:
		{	
			//正式读表中,只读没有读出的记录 2004.11.8加
			pview->FiveDataChuLi("正式读表",pview->m_SetLabel,TRUE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 10:
		{   
			//测试读表中,只读没有读出的记录 2004.11.8加
    		pview->FiveDataChuLi("测试读表",pview->m_SetLabel,FALSE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 11:
		{
			//先检测线路运行状态，开始读驻留数据MsgWaitForMultipleObjects
			pview->SendMessage(WM_EVENT, 15, 0);
			pview->FiveDataChuLi("定时驻留",pview->m_TimeSetLabel,TRUE, 1, pview->m_AutoReadCondtionStr,1,1,1);
			break;
		}
	case 12:
		{
			//手拉手专用
			//30分钟一次驻留
			pview->EverySendInfo();			
			//状态栏上显示信息
			pview->StatusStr = " ";
			pview->SendMessage(WM_EVENT, 1, 0);
			break;
		}
	case 13:
		{
			//等时刻点到
			if(pview->WaitShiKedian(pview->m_shikedian))
			{
				
				//如果按了停止按钮
				if(pview->m_StartRead)
				{	
					
					int m_waitfortimes     =                    0;
					CString                      m_CheckDaynicStr;
					m_CheckDaynicStr      = pview->m_DynaicCheckStrCondition;
				
					for( int yyyyyyy = 0 ; yyyyyyy < pview->m_readchecktimes; yyyyyyy ++)
					{
						
						//如果按了停止按钮
						if(!pview->m_StartRead)
						{	
							break;
						}

						//设置读的标志
						pview->SetDataReadLabel(m_CheckDaynicStr);	//循环次数,默认是1 次
						pview->FiveDataChuLi("动态监控",pview->m_SetLabel,TRUE,0, m_CheckDaynicStr,1,1,0);
						
						//如果按了停止按钮
						if(!pview->m_StartRead)
						{	
							break;
						}
							
						while(1)
						{
							//等待时间
							CTime timet = CTime::GetCurrentTime();
							
							//时间点以内
							if(timet.GetMinute() < pview->m_shikedian)
							{
								m_waitfortimes = pview->m_shikedian*60 - timet.GetMinute()*60 - timet.GetSecond();
							}
							else
							{
								m_waitfortimes = pview->m_shikedian*60  + (3600 - timet.GetMinute()*60 - timet.GetSecond());	
							}

							if(m_waitfortimes <= 2)
							{
								break;
							}
							
							//显示状态栏信息
							pview->StatusStr.Format("【已读%d次,共%d次,离下次监视读表%4d秒,请稍侯...】",yyyyyyy+1,pview->m_readchecktimes,m_waitfortimes);
							pview->SendMessage(WM_EVENT, 1, 0);
						
							//向远程发送信息
							pview->SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",pview->StatusStr);
							pview->SendMessage(WM_EVENT, 5, 0);
							
							Sleep(500);
							
							//如果按了停止按钮
							if(!pview->m_StartRead)
							{	
								break;
							}
							
							Sleep(500);
							
						}
						
					}
					
				}

			}
			
			pview->m_StartRead     = FALSE;
			pview->m_CheckReading  = FALSE;
			break;
		}
	case 14:
		{
			//检测无线通讯
			pview->CheckTongXunStatus();
			break;
		}
	case 15:
		{
			//检测无功补偿
			pview->WuGongDeal(pview->SendContionStr);
			break;
		}
	
	
    }

	//关闭线程
//	pview->m_StartRead    =      FALSE;
    pview->PostMessage(WM_EVENT,16, 0);
	return                           0;   // 返回并退出线程
}

//数据读表
void CIFRMView::OnTestreadtable() 
{  
	CString            str;
	CString  SelStr   = "";
	//记录个数
	long     m_records = 0;
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

    //得到对话条的所选条件
    if(!GetDialogBarStr())
	{
		return;
	}

	CCondtionsDlg        dlg;

	if(dlg.DoModal() == IDOK)
	{
	
		m_QuickReading = dlg.m_QuickReading;

	    //变电站版本
		if(AppInfo::Instance().m_WhichKind == TRUE)//TRUE 变电站版本  FALSE电局版
		{

			//普通读表
			if(dlg.m_readradiokinds == 0)
			{

				//驻留时间
				m_ZhuLiuTime   =       dlg.m_GetTimeStr;
				m_StartRead    =                   TRUE;
				SendContionStr = m_ModuleFindContionStr;

				//如果读上次驻留没有读上来的模块
				if(dlg.m_ReadLabel && dlg.m_NoReadingKinds > 0)
				{
					SendContionStr = "(" + SendContionStr + ")" + " AND USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					SetDataReadLabel(SendContionStr);	//设置读的标志

					//相重设为不定
					if(dlg.m_PhaseNoKnown)
					{
						str.Format("Update TB_USER SET USER_PHASE=3 WHERE %s",SendContionStr);
	                    CDataBaseInstance::ExecuteDataBaseSQL(str);
					}

				}

				switch(dlg.m_radio1)
				{
				case 0:
					{  						
						if(dlg.m_ReadLabel)
						{ 
							//只读没有读出的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)10,m_Thread_PRIORITY,0,0,NULL); // 创建并运行 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}
						else
						{ 
							//读此范围的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)0,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}
						
						break;
					}
				case 1:
					{ 
						//正式读表							
						if(dlg.m_ReadLabel)
						{ 
							//只读没有读出的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)9,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}
						else
						{   
							//读此范围的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)1,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}

						break;
					}
				case 2:
					{ 
						
						if(m_IsAutoSending)
						{
							CString       MessageStr;
							m_StartRead  =        FALSE;
							MessageStr   = "定时驻留期间不能驻留读表！";
							MessageBox(MessageStr," ",MB_OK|MB_ICONWARNING);
							return;
						}
						
						//驻留读表,只读上次读不出数的模块						
						if(dlg.m_ReadLabel)
						{ 
							//只读没有读出的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)8,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}
						else
						{
							//读此范围的模块
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)2,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						}

						break;
					}
					
				}

			}
			else
			{
				//查是否和自动驻留冲突
				BOOL m_CanReading = TRUE;
				CString              str;
				BYTE        m_day  =   0;

				//如果在驻留期间
				if(m_IsAutoSending)
				{					
				
					CByteArray          m_TimeArray;//读表日期数组
				
					for(int i = 0; i < 31; i ++)
					{
						
						//提出读表日期
						if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
						{
							m_TimeArray.Add(i+1);
						}
						
					}
					
					//如果没有读表日期则退出
					if(m_TimeArray.GetSize() > 0)
					{	
						//检测各种时间	
						long m_seconds = (dlg.m_readRangle * dlg.m_readtimes)*3600;//读多长时间
						CTimeSpan                                ts;//时间间隙//时间
						ts                   =            m_seconds;
                    	CTime           timet = CTime::GetCurrentTime();
					    CTime            m_CurrentTime2 = timet + ts;//定义时间变量
                        BYTE        m_day1 = timet.GetDay();
                        BYTE        m_day2 = m_CurrentTime2.GetDay();
                    
    					if(m_day2 >= m_day1)
						{

							for(int i = 0;i < m_TimeArray.GetSize();i ++)
							{

								if(m_TimeArray[i] >= m_day1 && m_TimeArray[i] <= m_day2)
								{
									//记录冲突的
                                    m_day = m_TimeArray[i];
									m_CanReading  = FALSE;
									break;
								}
					
							}


						}
						else
						{
							//跨月
							for(int i = 0;i < m_TimeArray.GetSize();i ++)
							{

								if(m_TimeArray[i] <= m_day1 || m_TimeArray[i] >= m_day2)
								{
									//记录冲突的
                                    m_day = m_TimeArray[i];
									m_CanReading  = FALSE;
									break;
								}
					
							}


						}
						
					}
					
				}

				if(m_CanReading)
				{
					m_CheckReading            =            TRUE;//监视读表
					m_shikedian               = dlg.m_shikedian; //监视时间点
					m_readRangle              = dlg.m_readRangle;//读多长时间
					m_readchecktimes          = dlg.m_readtimes; //读表次数
					m_DynaicCheckStrCondition = m_ModuleFindContionStr;
					
					//读此范围的模块
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					str.Format("此操作将影响%d日定时驻留读表,放弃执行吗？？\r\n如果执行有可能导制%d日驻留读不上数！！",m_day,m_day);
					
					if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
					{

						m_CheckReading            =            TRUE;//监视读表
						m_shikedian               = dlg.m_shikedian; //监视时间点
						m_readRangle              = dlg.m_readRangle;//读多长时间
						m_readchecktimes          = dlg.m_readtimes; //读表次数
						m_DynaicCheckStrCondition = m_ModuleFindContionStr;
						
						//读此范围的模块
						ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
						ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						
					}

					
				}
				
			}
			
		}
		else
		{
			/*
			//电局版
			//SelStr---格式为由0和1组成的十一位数表示如:1111111111   
			//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
			//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
			//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
			//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
			//第五位表示 电流             1 － 要读电流             0 - 不读电流
			//第六位表示 电压             1 － 要读电压             0 - 不读电压
			//第七位表示 尖峰电量
            //第八位表示 峰电量
            //第九位表示 谷电量
            //第十位表示 平电量
            //第十一位表示 功率因数
			//合并条件
			SelStr  =  "";
			
			//得到变电站编号
			//m_StationNo = GetStationNo();  
		
			//合并条件
			for(int i = 0; i < 15; i ++)
			{
				
				//累积有功电度、手拉手总有功电度、累积无功电度、手拉手总无功电度、电流、电压
				if( (i >= 0 && i <= 3) || i == 4 || i == 7  || (i >= 10 && i <= 14))
				{
					
					if(m_SetLabel[i] == TRUE)
					{
						SelStr = SelStr + "1";
					}
					else
					{
						SelStr = SelStr + "0";
					}
					
				}
				
			}


			//普通读表
			if(dlg.m_readradiokinds == 0)
			{
			
				//下结论
				switch(dlg.m_radio1)
				{
				case 0:
					{  
						
						//测试读表
						m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
						
						//只读上次没有读出的数据
						if(dlg.m_ReadLabel)
						{
							//读哪一项放在条件后边	//循环次数,默认是1 次
							//轮之间时间间隔,默认是30分钟
							str.Format("BEGINS;COMMAND:18:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						else
						{
							//读哪一项放在条件后边	
							str.Format("BEGINS;COMMAND:01:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						break;
					}
				case 1:
					{ 
						//正式读表，记录个数
						m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", m_ModuleFindContionStr);
						
						//只读上次没有读出的数据
						if(dlg.m_ReadLabel)
						{
							//读哪一项放在条件后边
							str.Format("BEGINS;COMMAND:17:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						else
						{
							//读哪一项放在条件后边
							str.Format("BEGINS;COMMAND:02:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						break;
					}
				case 2:
					{ 
						//驻留读表
						//只读上次读不出数的模块
						if(dlg.m_ReadLabel)
						{
							//记录个数,只读上次没有读出数的模块
							m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
							str.Format("BEGINS;COMMAND:16:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);//驻留读表
						}
						else
						{	
							//记录个数
							m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
							str.Format("BEGINS;COMMAND:03:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);//驻留读表
						}
						break;
					}
					
				}

			}
			else
			{
				//动态监控读表，记录个数
				m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
				str.Format("BEGINS;COMMAND:37:%s:%d:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,dlg.m_shikedian,dlg.m_readRangle,dlg.m_readtimes,SelStr);//动态监控读表
				
			}
		
			//远程发送测试读表、正式读表、驻留读表指令
         	if(SelectSendString(m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
			{
				m_StartRead = TRUE;
			}
			else
			{
				m_StartRead = FALSE;
			}
			*/
			
		}
		
	}
	
}



//发驻留
void CIFRMView::OnBreadorder() 
{   
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CBreadSettingDlg dlg;
    dlg.DoModal();
	m_StartRead = FALSE;
}

void CIFRMView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	
	ResizeParentToFit();

	//可执行文件路径
	GetFileFolderPass =         GetFolder();

	//表格属性
	m_Grid.GetDefaultCell(FALSE,TRUE)->SetFormat(DT_CENTER|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS|DT_SINGLELINE);//
	m_Grid.SetEditable(FALSE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableDragAndDrop(TRUE);
    m_Grid.SetTextBkColor(m_BackRgbValue);//RGB(0xFF,0xFF,0xE0));
    m_Grid.SetBkColor(RGB(128,128,128));  //m_BackRgbValueRGB(255,255,255)
	m_Grid.SetHeaderSort(TRUE);
	m_Grid.SetSingleRowSelection(TRUE);	
	m_Grid.SetModified(FALSE,-1,-1);      //置未修改状态
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	

	//更新数据各种表结构
	if(!UpdateDataTable())
	{
		MessageBox("数据表升级错误，软件各种操作可能不能\r\n正常执行，详情请与英康公司联系！"," ",MB_OK|MB_ICONWARNING);
		//得到DIALOGBAR上的变量,初始化树控件	
		//pMainFrm->SendMessage(WM_CLOSE);
	}

	m_WgLess          =    GetWGTimeEvery();//无功的种类 0 10分钟 1 20分钟  2 30分钟//得到无功的时间间隔

	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
	{
		//初始化树控件
		pMainFrm->m_wndMyDialogBar.Treeinitialize();

		VARIANT        position;
		position.vt   =   VT_I4;
		position.lVal =       2;
		pMainFrm->m_wndMyDialogData.initializeFieldInfo("所有数据","ALL",3,position);
	}
	else
	{
		//接线错误的模块
		CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_LINEERROR");

		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
	}

  	//得到端口个数
	GetComPorts();

	//状态条
	pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);// AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	//指针传递完毕

	//变台数据库
	m_TransformpSet = std::shared_ptr<CTransformRecordset>(new CTransformRecordset);

    //电度表数据库
	m_AmetterSet    = std::shared_ptr<CAmetterRecordset> (new CAmetterRecordset );

	//用户信息数据库
	m_UseInfoset    = std::shared_ptr<CUseInfoRecordSet>(new CUseInfoRecordSet);

	//驻留信息数据库
	m_GarrisonSet   = std::shared_ptr<CGarrisonRecordSet> (new CGarrisonRecordSet);

	//数据信息数据库
	m_DataInfoSet   =std::shared_ptr<CDataInfoRecordSet>(new CDataInfoRecordSet);

	//价格数据库
	m_PriceSet      = std::shared_ptr<CPriceSet> (new CPriceSet );

    //换表信息
	m_CCHANGEAMMETER = std::shared_ptr<CCHANGEAMMETERSet>(new  CCHANGEAMMETERSet);
	
	//如果用户库没有数据
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") <= 0)
	{
		
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		ASSERT_VALID(pMainFrm);

		//得到选择读表的条件
		m_DialogBarVisible  = FALSE;
		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);

	}
	
	//关闭串口
	if(m_Com.GetPortOpen()) //打开串口   
	{
		m_Com.SetPortOpen(FALSE);
	}

	//定时按钮置为FALSE
	ShowDingShiButton(FALSE);

	//变电站版本
	if(	AppInfo::Instance().m_WhichKind)//TRUE 变电站版本  FALSE电局版
	{	
		//演示版本
		if(!AppInfo::Instance().m_YanShi)
		{

			CString error;
			
			if ((card = Register_Card (PCI_9111DG, 0)) <0 ) 
			{	
				if(!AppInfo::Instance().m_AutoRunning)
				{
					MessageBox("采集卡初始化错误，请检查采集卡\r\n安装是否正确！","警告",MB_OK|MB_ICONWARNING);
				}
				else	
				{
					Beep(300,400);
				}
				
			}
			
			//双缓冲区状态
			err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
			if (err != 0)
			{
				//Beep(300,400); 
			}
			
			err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
			if (err != 0) 
			{
				//Beep(300,400);
			}

		}

	
			
		//第二个口为读线总表和站站总表专用 485
        if(Ports[1] == TRUE)
		{
			
			//设置485口，485口初始化
        	if(m_485MsComm.GetPortOpen()) //打开串口   
			{	
				//关闭串行485通讯口
				m_485MsComm.SetPortOpen(FALSE);
			}
			
			m_485MsComm.SetCommPort(2);            //选择COM2
			m_485MsComm.SetInBufferSize(1024);     //设置输入缓冲区的大小，Bytes
			m_485MsComm.SetOutBufferSize(512);     //设置输出缓冲区的大小，Bytes
			
			//打开端口
			m_485MsComm.SetPortOpen(TRUE);
			
			m_485MsComm.SetInputMode(1);           //0 文本形式 1二进制形式
			
			//设置波特率,检验位,数据位,停止位	
			m_485MsComm.SetSettings("1200,E,8,1");//"600,n,8,1"
			//1200,E,8,1
			m_485MsComm.SetRThreshold(1);         //每接收1个字符就触发1次接收事件
			m_485MsComm.SetInputLen(0);           //每次读取一个字符,二进制形式
			m_485MsComm.GetInput();               //清除原有的数据
		}
		else
		{
			//MessageBox("COM2口打开错误,线总表和站总表无法通过485口读取数据！","警告",MB_OK|MB_ICONWARNING);
		}
		
		//得到手拉手信息
		GetHandModuleInformation();
	
		//每隔10分钟发一次调制信号，手拉手用
		if(m_status)
		{
			SetTimer(1,m_SettimerValues,NULL);
		}

		//是否是单一版本,不是单一版本则检测串口或局域网
		/*
		if(!AppInfo::Instance().m_SingleBB) 
		{
			//启动时自动应答
			AutoAnswer(TRUE);
			
			//自动启动自动应答
			SetLocalServer(m_WinSocket.GetLocalIP(),2500);
		}
		*/
		
		//软件一启动就自动驻留读表时间
		if(IsCurveTableExist("TB_Auto"))
		{
			AutoGarrisonTime();
		}
		
		//自动启动按日期驻留
		if(IsCurveTableExist("TB_DateAuto"))
		{
			ByDateAutoGarrisonTime();
		}

		//启动监视软件
		CFileFind               finder;
		CString      m_RunnExeFileName;
        m_RunnExeFileName.Format("%s%s",GetFolder(),"TraySpy.exe");
		
		//如果存在抄表软件
		if(finder.FindFile(m_RunnExeFileName) != 0) 
		{   
			LPCTSTR  m_pszAppName = "TraySpy";
			
			//此程序只能运行一次，用互斥量来判断程序是否已运行
			HANDLE m_hTrayWatchMutex = CreateMutex(NULL,TRUE, m_pszAppName); 
			
			if(GetLastError() != ERROR_ALREADY_EXISTS)
			{ 
				//运行此软件
				WinExec(m_RunnExeFileName,SW_SHOWDEFAULT);
			}
		
		}
			
		finder.Close();
	

	}
	else
	{	
		m_WinSocket.Close();
		//定期更新用户数据表
		//SetTimer(2,1*60000,NULL);//15
	}
	
    m_pSelection = NULL;    // initialize selection

}



//变台数据库
void CIFRMView::OnTranformer() 
{
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	//如果原先打开了则关闭
	if(m_TransformpSet->IsOpen())
	{
		m_TransformpSet->Close();
	}
	
	//数据库表是否打开
	if(m_TransformpSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CTransformerDlg	dlg(m_TransformpSet.get(),0);
		dlg.m_Enalbed  = TRUE;
		dlg.DoModal();
		
		//如果原先打开了则关闭
		if(m_TransformpSet->IsOpen())
		{
			m_TransformpSet->Close();
		}
		
		//变台修改或增加了记录
		if(dlg.m_IfAdding == TRUE)
		{
			//树控件重新刷新一次
			RefreshTree();
		}
		
	}
	else
	{
		MessageBox("数据库表打开错误！"," ",MB_OK|MB_ICONWARNING);
	}
	
}

//电表数据库
void CIFRMView::OnAmmeterinfo() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	if(m_AmetterSet->IsOpen())
	{
		m_AmetterSet->Close();
	}
	
    //数据库表是否打开
	if(m_AmetterSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		CAmetterDlg  dlg(m_AmetterSet.get(),0);
		dlg.m_Enalbed =   TRUE;
		dlg.DoModal();	
		
		if(m_AmetterSet->IsOpen())
		{
			m_AmetterSet->Close();
		}
	}
	else
	{
		MessageBox("数据库表打开错误！"," ",MB_OK|MB_ICONWARNING);
	}

}

//用户数据库
void CIFRMView::OnUserinfo() 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	if(m_UseInfoset->IsOpen())
	{
		m_UseInfoset->Close();
	}
	
	//数据库表是否打开
	if(m_UseInfoset->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CUserInfoDlg dlg(m_UseInfoset.get(),0);
		dlg.m_filtercondtion = "";
		
		dlg.DoModal();	
		
		if(m_UseInfoset->IsOpen())
		{
			m_UseInfoset->Close();
		}
		
		//变台修改或增加了记录
		if(dlg.m_IfAdding == TRUE)
		{	
			//树控件重新刷新一次
			RefreshTree();
			
		}
		
	}
	
}

//通讯对话框
void CIFRMView::OnCommunication() 
{
	//DealOverTimeData(1);
	//return;
    //TRUE--变电站版本  FALSE---电局版
	CStationCommunDlg    dlg;
	dlg.m_WhichKind = AppInfo::Instance().m_WhichKind;
	dlg.DoModal();
}

//状态栏上显示信息
void CIFRMView::status(CString strname)
{
	if (pStatus)
	{
		pStatus->SetPaneText(0,strname);
	}
	
}

//显示或隐藏滚动条
void CIFRMView::ShowProgressCtrl(BOOL m_IsShow)
{
    CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->ShowProgressCtrl(m_IsShow);
}

//停止按钮
void CIFRMView::OnStoprun() 
{
	
	//交出window控制权
	SurrenderWindowMessage();
	
	m_StartRead       =   FALSE;

	//降低线程级别
	if(ReadMeterThread != NULL)
	{
		//WaitForSingleObject(ReadMeterThread->m_hThread,INFINITE);
		ReadMeterThread->SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	}

	for(BYTE i = 0; i < 10; i ++)
	{

		m_StartRead       =   FALSE;
        bStopped          =    TRUE;
		//监视读表
    	m_CheckReading    =   FALSE;	

		//交出window控制权
		SurrenderWindowMessage();
		Sleep(20);	
		
		if(ReadMeterThread == NULL)
		{	
			status("              ");
			break;
		}

	}
	//如果线程暂停
	
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//启动线程退出
		ReadMeterThread->ResumeThread();
		m_Pause  =   FALSE;	
		
		//交出window控制权
		SurrenderWindowMessage();
		Sleep(500);
		//交出window控制权
		SurrenderWindowMessage();
		//如果线程暂停
	}
	
    //停止传送数据
	m_StopPassing    = TRUE;

	KillTimer(2);
	KillTimer(3);

	//演示或隐藏动画
	OperationAnimation(FALSE);
	//隐藏滚动条
	ShowProgressCtrl(FALSE);

	//交出window控制权
	SurrenderWindowMessage();
 
	//SelectSendString(m_sendkind,"BEGINS;DATAS:3:StopData;停止;ENDS",TRUE,FALSE,FALSE);
	//交出window控制权
	//SurrenderWindowMessage();

	//不可以接收数据了
	m_ReceiveOk    =   FALSE;

}


//设定滚动条范围,步长
void CIFRMView::SetProgressCtrlRange(int ups, int downs,int steps)
{ 
	CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->m_progressBar.SetRange(ups , downs);
	pts->m_progressBar.SetStep(steps);
	pts->m_progressBar.SetPos( 0 );
	
}


//设定滚动条下滑
void CIFRMView::SetProgressCtrlSetIt()
{
	CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->m_progressBar.StepIt();
	
}


//读表数据
double CIFRMView::ReadMeter(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/,BYTE Item/* 要什么东西*/,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/,CString m_AmmeterType/*脉冲表型号*/)
{
//	WriteToLog("[星星读表]");


	double  m_RetuenValue =     0;
	double  m_tempvalue   =     0;
	int     HalfCount     =     0;
	BOOLEAN bHalfReady    = FALSE;
	bStopped              = FALSE;
	U32                     count;
	DataLen               =     0;
	U16               overrunFlag;
	CString                   str;//检测电流电压
	BOOL m_changed        = FALSE;
	BYTE     k1  =  0,k2  =   1;

	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);

	//可快速读485表
	m_CanQuickRead71485   = FALSE;

	if(!m_StartRead)
	{
		return -1;
	}

	for(int jj = 0 ; jj < 3; jj ++)
	{
        m_Quick71Value[jj] =   0;
	}
	
//	str.Format("模块号:%d,相别:%d\r\n",ModuleNum,Phase);
//	WriteToLog(str);
	
	//演示版本
	if(AppInfo::Instance().m_YanShi)
	{
		
		for(int jj = 0 ; jj < 7; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(1000);
			}
			else
			{
				break;
			}
			
		}
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		CTime time  = CTime::GetCurrentTime();
		
		if(Item == 0xf6 || Item==0xf8)
		{
			m_RetuenValue = 333333.33;
		}
		else if(Item == 0x38 || Item==0xB8)
		{
			m_RetuenValue = 0.98;
		}
		else
		{
			//返回值ModuleNum
			m_RetuenValue = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01 +  ModuleNum*0.001;
		}
		
	}
	else
	{	

		//如果打包读表,驻留读表慎用
		if(m_QuickReading)
		{  	
			
			//存61、62协议485表快速读表的功率因素
			if(((Protocol/10) == 6) && (Item==0x07 || Item==0x06) && ((ModuleNum%100) > 12))
			{
				
				if(ModuleNum/100 < 20000 )
				{

					//如果原来读出此表的值了
					if(m_QuickGlys[ModuleNum/100 - 1] >= 0)
					{

						return m_QuickGlys[ModuleNum/100 - 1];

					}
					
				}
				
			}		
		
			//存71、72协议485表快速读表的功率因素,峰，谷，平，有功，无功
			if(((Protocol/10) == 7) && (Item == 0x5A || Item == 0x5E || Item == 0x5C || Item == 0x02 || Item == 0x06 || Item == 0xDA || Item == 0xDE || Item == 0xDC || Item == 0x82 || Item == 0x86) && ((ModuleNum%100) >= 12))
			{
				
				CTime     timet    = CTime::GetCurrentTime();
				str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
				
				//此模块是否能快速读表
				if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
				{
					
					if(!((ModuleNum/100) < 100000  && m_QuickGlys[ModuleNum/100] < 0))
					{
						
						//可快速读485表
						m_CanQuickRead71485        = TRUE;
						m_QuickGlys[ModuleNum/100] =    0;
						
						//实时峰，谷，平
						if(Item == 0x5A || Item == 0x5E || Item == 0x5C)
						{
							//峰，谷，平
							Item = 0x64;
						}
						else if(Item == 0x02 || Item == 0x06)
						{
							//实时有功、无功
							Item = 0x66;
						}
						else if(Item == 0xDA || Item == 0xDE || Item == 0xDC)
						{	
							//驻留峰，谷，平
							Item = 0xF4;
						}
						else if(Item == 0x82 || Item == 0x86)
						{
							//驻留实时有功、无功
							Item = 0xF6;
						}
						
					//	str.Format("协议：%d，快速读表模块号：%d，指令:%0x\r\n",Protocol,ModuleNum,Item);
					//	WriteToLog(str); 
					} 
					
				}
							
		  }
		  else
		  {	
				
				//71,72,73协议的脉冲,一次上来3个模块的数据，32位，每个模块10位，最大999，每次上来3个,61,62的485,功率因素和有功功率打包在一起
				if((((ModuleNum%100) <= 8) && (Item==0x02 || Item==0x82) && ((Protocol/10) == 7)) || ((Protocol/10) == 6 && ((ModuleNum%100) > 12) && (Item==0x1F || Item==0x1E)))
				{
					
					CTime     timet    = CTime::GetCurrentTime();
					str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					
					//此模块是否能快速读表
					if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
					{	   
						
						//对比两个模块,71,72,73协议
						if((m_QuickModuleAddress/100 == ModuleNum/100) && ((Protocol/10) == 7))
						{
							
							//快速读表模块子表的范围
							if((m_QuickModuleAddress%100) >= 1 &&  (m_QuickModuleAddress%100) <= 3)
							{
								k1 = 1;
							}
							else if((m_QuickModuleAddress%100) >= 4 &&  (m_QuickModuleAddress%100) <= 6)
							{
								k1 = 2;
							}
							else if((m_QuickModuleAddress%100) >= 7 &&  (m_QuickModuleAddress%100) <= 8)
							{
								k1 = 3;
							} 
							
							//当时读表模块子表的范围
							if((ModuleNum%100) >= 1 &&  (ModuleNum%100) <= 3)
							{
								k2 = 1;
							}
							else if((ModuleNum%100) >= 4 &&  (ModuleNum%100) <= 6)
							{
								k2 = 2;
							}
							else if((ModuleNum%100) >= 7 &&  (ModuleNum%100) <= 8)
							{
								k2 = 3;
							}
							
							//两个在一个段
							if(k1 == k2) 
							{
								
								//m_QuickReadParameter[0] 最新有功电度读表值
								//m_QuickReadParameter[1] 有功电度底值
								//m_QuickReadParameter[2] 3200的倍数,直接算出值								   
								
								//读出的三个打包的值,前10位第一子表模块的值，中间10位第二子表模块的值，后面10位为第三子表模块的值
								if(m_QuickReadModuleValue >= 0)
								{
									
									switch((ModuleNum%10)%3)
									{
									case 1:
										{	  
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
											break;
										}
									case 2:
										{
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
											break;
										}
									case 0:
										{	
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
											break;
										}
									}
									
									//除以脉冲比+表底
									m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
									
								//	str.Format("模块号:%d,原来的值:%f,表底:%f,倍率:%f,\r\n新算出的值:%f,加表底:%f,第一子表:%d,第二子表:%d,第三子表:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
								//	WriteToLog(str);
									
									//算出的数大于或等于合理的话
									if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
									{
								//	    WriteToLog("加表底大于等于原底数");
										return  m_RetuenValue;
									}
									
								//	WriteToLog("加表底小于原底数");
									
									
								}
								else
								{
									
									if(long(m_QuickReadModuleValue) < -1)
									{
										//没有驻留上数据
										return long(m_QuickReadModuleValue);
									}
									
								}									 
								
							}
							
						}
						else
						{
							
							m_changed              =  TRUE;
							
							if((Protocol/10) == 7)
							{
								m_QuickModuleAddress   =     0;//快速读表的地址
								m_QuickReadModuleValue =    -1;
								
								if((ModuleNum%100 <= 3))
								{
									
									//最前3个模块,子表地址为01,02,03
									if(Item == 0x02)
									{
										Item = 0x0E;
									}
									else
									{
										Item = 0x8E;
									}
									
								}
								else if((ModuleNum%100 >= 4) && (ModuleNum%100 <= 6))
								{
									
									//中间3个模块,子表地址为04,05,06
									if(Item == 0x02)
									{
										Item = 0x10;
									}
									else
									{
										Item = 0x90;
									}					   
									
								}
								else 
								{
									//最后2个模块,子表地址为07,08
									if(Item == 0x02)
									{
										Item = 0x12;
									}
									else
									{
										Item = 0x82;
									}					   
									
								}
								
								//   str.Format("协议：%d，快速读表模块号：%d，指令:%0x\r\n",Protocol,ModuleNum,Item);
								//   WriteToLog(str);
								
							}
							else
							{
								//61,62协议
								if(Item == 0x1F)
								{
									Item = 0x01;
								}
								else
								{
									Item = 0x00;
								} 
								
								//   str.Format("协议：%d，快速读表模块号：%d，指令:%0x\r\n",Protocol,ModuleNum,Item);
								//   WriteToLog(str);
								
							}
							
						}
						
					}
					else
					{
							m_QuickReadModuleValue     =              -1;
							m_QuickModuleAddress       =       ModuleNum;//快速读表的地址
					}
						
				}
				   
			}
			  
		}



		//双缓冲区状态
		err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
		if (err !=   0) 
		{  
			return -1;
		}
		
		//外触发状态
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		if (err !=   0) 
		{  
			return -1;
		}


		//向单片机发指令
		if(!SendOrderToSCM(ModuleNum/*模块号*/,StationNo/*手拉手电站码*/,MotherLine/*母线*/,LineNo/*线号*/, Phase/*相选择0A 1B 2C*/,3, Item/* 要什么东西,命令字*/,0,Protocol,m_SendAngle))
		{
			Beep(300,400);
			Beep(300,400);
		}
		
		for(int jj = 0 ; jj < 8; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(150);
			}
			else
			{
				break;
			}
		}


		//开始采集数据

		memset(DataBuf,0,190000);
        memset(ReadBuff,0,1024);
		
		//连续读通道数据
		err = AI_ContReadChannel(card,m_iChSelect, AD_B_10_V, ReadBuff,1024,(F64)100000, ASYNCH_OP);
		
		if (err !=   0) 
		{  
			return -1;
		}
		
		bClearOp     =                   FALSE;
		CTime time0  = CTime::GetCurrentTime();
		
		do
		{
			do
			{
				//半满
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
				
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1 - time0;
				
				if(Protocol != 22)
				{
					//如果不是22协议
					if(ts.GetTotalSeconds() > (Protocol%10)*9 || !m_StartRead)
					{
						bClearOp = TRUE;
					}

				}
				else
				{	
					//如果是22协议
					if(ts.GetTotalSeconds() > 9 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				
			} while (!bHalfReady && !bClearOp);
			
			if(!m_StartRead)
			{
				bClearOp = TRUE;
			}

			if(!bClearOp) 
			{
				
				//传送半满数据
				AI_AsyncDblBufferTransfer(card, ReadBuff);
				
				bHalfReady = FALSE;
				
				for(int i = 0; i < 512; i++)
				{	
					DataBuf[DataLen++] = ReadBuff[i]/16;	
				}
				
				SurrenderWindowMessage();

				if(!m_StartRead)
				{
					bClearOp = TRUE;
				}
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1     -       time0;
				
				//时间控制
				switch(Protocol)
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
				
				
				if(Protocol != 22)
				{
					
					//如果不是22协议
					if(ts.GetTotalSeconds() > (Protocol%10)*10 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				else
				{	
					
					//如果是22协议
					if(ts.GetTotalSeconds() > 9 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
			}
			
		
        }while (!bClearOp && !bStopped && m_StartRead);
	
		AI_AsyncClear(card, &count);
		
		AI_AsyncDblBufferOverrun(card,1,&overrunFlag);
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		//返回值
		m_RetuenValue = Decode(ModuleNum,Protocol,Item);

	}
	
//	str.Format("m_RetuenValue=%.2f\r\n",m_RetuenValue);
//	WriteToLog(str);

	//可快速读485表
	if(m_CanQuickRead71485)
	{	
		

		//检测读出的数据是否有效,如果数据大于0
		if(m_RetuenValue >= 0)
		{
			
			//CTime     timet    = CTime::GetCurrentTime();
			//str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

			//检查71协议485表快速读表是否成功
            Check_71485_Protcol(ModuleNum,Item);

			if(!m_CanQuickRead71485)
			{	
				
				if((ModuleNum/100) < 100000)
				{
					m_QuickGlys[ModuleNum/100] = -1;
				}

                m_RetuenValue = -1;
			}
		

		}
		else
		{

			if((ModuleNum/100) < 100000)
			{
				m_QuickGlys[ModuleNum/100] = -1;
			}
			
			m_CanQuickRead71485 = FALSE;

		}
		
	}
	else if(m_QuickReading && m_changed)
	{	

        //快速读表
		//如果数据大于0
		if(m_RetuenValue >= 0)
		{	
			
			//71,72,73协议
			if((Protocol/10) == 7)
			{	
				//71,72,73肪冲表
				m_QuickReadModuleValue =  long(m_RetuenValue);//三个模块的数据打在一起
				m_QuickModuleAddress   =            ModuleNum;//快速读表的地址
				
				//m_QuickReadParameter[0] 最新有功电度读表值
				//m_QuickReadParameter[1] 有功电度底值
				//m_QuickReadParameter[2] 3200的倍数,直接算出值

				switch((ModuleNum%10)%3)
				{
				case 1:
					{	  
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
						break;
					}
				case 2:
					{
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
						break;
					}
				case 0:
					{	
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
						break;
					}
				}
				
				//除以脉冲比,得出新的数据值
				m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
				
		//		str.Format("模块号:%d,原来的值:%f,表底:%f,倍率:%f,\r\n新算出的值:%f,加表底:%f,第一子表:%d,第二子表:%d,第三子表:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
		//		WriteToLog(str);

				//算出的数大于
				if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
				{
			//		WriteToLog("加表底大于等于原底数");
					return  m_RetuenValue;
				}
				
		//		WriteToLog("加表底小于原底数");
		  	    
				m_RetuenValue          = - 1;
				m_QuickReadModuleValue = - 1;
				
			}
			else
			{
				//61,62,63协议485的才有快速读表,读出的二个打包的值,前7位为功率因素，后勤14位为有功电度,61,62
				long  m_TmepQuickReadModuleValue =  long(m_RetuenValue*10);
				m_tempvalue                      =  (m_TmepQuickReadModuleValue%(int(pow((double)2,14)))) * 0.1;
				float m_TempGlys                 =  (m_TmepQuickReadModuleValue/(int(pow((double)2,14)))) * 0.01;
				
				if(m_tempvalue <= 999.8  &&  m_TempGlys <= 1)
				{
					
					//m_QuickReadParameter[0] 最新有功电度读表值
					//m_QuickReadParameter[1] 有功电度底值
					//m_QuickReadParameter[2] 3200的倍数,直接算出值

					m_RetuenValue = long(m_QuickReadParameter[0] + 0.001)/1000*1000 + m_tempvalue;
					
					//算出的数大于或等于合理的话
					if(m_RetuenValue  >= m_QuickReadParameter[0])
					{
						//存61、62协议485表快速读表的功率因素 
						if(ModuleNum/100 < 20000)
						{
							m_QuickGlys[ModuleNum/100 - 1] = m_TempGlys;
						}
						
						return  m_RetuenValue;
					}
					
				}
				
				m_RetuenValue          = - 1;
			}
			
		}
		else
		{
			//读过此表，模块不支持此指点令
			m_QuickReadModuleValue     =   m_RetuenValue;
			m_QuickModuleAddress       =       ModuleNum;//快速读表的地址
		}
		
		
	}
	else
	{

		//1-12为脉冲表
		if(ModuleNum%100 <= 12 && m_RetuenValue > 0  && !m_AmmeterType.IsEmpty())
		{
			//默认脉冲率为3200，得折算值
			m_RetuenValue = m_RetuenValue* 3200.00/GetAmmeterImpulse(m_AmmeterType);
		}
		
	}
  TmpOnlyOneThreadRun.SetEvent();


	return m_RetuenValue;
}


//查表得到脉冲表的脉冲率
int CIFRMView::GetAmmeterImpulse(CString m_AmmeterType)
{
	CString       strValue;
	CDatabase           db;	

	strValue.Format("RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);

    //打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset    rs(&db );
		strValue.Format("SELECT AMMETER_TYPE,AMMETER_IMPULSE FROM TB_AMMETER  WHERE RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);
		rs.Open(CRecordset::dynaset,strValue);	
		
		if(rs.IsEOF())
		{
			rs.Close( );
			db.Close( );
			return 3200;
		}
		
		rs.GetFieldValue((short)1,strValue);

		rs.Close( );
		db.Close( );

		if(atoi(strValue) > 0)
		{
			return atoi(strValue);
		}

	}

	return 3200;
}

void CIFRMView::OnTimer(UINT nIDEvent) 
{
	CFormView::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
	case 1:
		{	
	
			
			//0 按表计种类下驻留 1 按日期下驻留
			switch(m_zhuliukinds)
			{
			case 0:
				{
					//按表计种类下驻留
					DingShiDeal();
					break;	
				}
			case 1:
				{
					//按日期下驻留
					ByDateDingShiDeal();
					break;
				}
			}
	


			break;
		
		}
	case 2:
		{  
		    //包头远程版专用，定期更新用户数据表，如果在传递数据或其它工作的话，就不更新	
			if(!(ReadMeterThread != NULL ||  m_StartRead == TRUE)) 
			{	
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)7,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
			}

			break;
		}
	case 3:
		{	  
			
			//得到错误的次数
			m_GetErrors ++;	
			BOOL m_connectings = TRUE;
		    
			//连接状态显示
			switch(m_sendkind)
			{
			case 0:
				{
					m_connectings = m_Com.GetPortOpen();
					break;
				}
			case 1:
				{
					m_connectings = m_Com.GetCTSHolding();
					break;
				}
			case 2:
				{ 
					m_connectings = m_IsConnect;
					break;
				}
			}
		
		
			if(m_GetErrors  > 30  || m_StopPassing || !m_connectings)
			{	
				
				KillTimer(3);
				
				//演示或隐藏动画
				OperationAnimation(FALSE);
				
				//隐藏滚动条
				ShowProgressCtrl(FALSE);
				
				//得到错误的次数
				m_GetErrors     =     0;
				
				if(!AppInfo::Instance().m_WhichKind)
				{
					status("               ");
					
					//如果是远程端,弹出对话框
					if(m_StopPassing)
					{
						MessageBox("接收数据已被中止！！","",MB_OK|MB_ICONWARNING);
					}
					else
					{
						MessageBox("传输线路出现问题，请检查线路！","",MB_OK|MB_ICONWARNING);
					}

				}
				else
				{
				
					//如果是站,则在状态栏中显示信息
					if(m_StopPassing)
					{
						status("【接收数据已被中止】");
						SendContionStr = "BEGINS;MESSAGE:0:远程机器已停止接收读数!;ENDS";
                        SendMessage(WM_EVENT, 4, 0);
					}
					else
					{
						status("【传输线路出现问题,请检查线路】");
					}

				}
				
			}
			else
			{
				//格式：BEGINS;COMMAND:25:数据表名:要的记录数位置;ENDS
				SendContionStr.Format("BEGINS;COMMAND:25:%s:%d;ENDS",m_PassDataFileName,m_CurrentPassPostions);
				//发送数据
				SendMessage(WM_EVENT, 5, 0);
			}

			break;
		}
	}
	
}


//解码,解6次－－－－－读表协议
double CIFRMView::Decode(long ModuleNum,BYTE Protocol,BYTE Item)
{	
	CString               str,signstr;
	BYTE                     Data[39];
	double dataValue         =     -1;
	int   index              =      0;
    long                  Diffs[1024];
	long                  Diffn[1024];
	long         m_sums        =    0;
	double  m_maxppvalue       =    0;
	short   m_pipeiplace       =    0;
	int     m_maxpptimes = WM_NUMBERS;
	double  m_ppvalue          =    0;
    BYTE  SignalBit[100],TempSignalBit[100],Signal[10];
	double         m_ppresult10[7300];//10度匹配结果
	double         m_ppresult05[7300];// 5度匹配结果
	double           m_ppresult[7300];//    匹配结果
    short        m_PlaceDifferent[31];//22协议不同的对比位置
	BOOL         m_checkplace = FALSE;
	BYTE         m_ByteRecords =    0;//收的字节数
	int i;
	switch(Protocol)
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
			//如果没有采集够数
			if(DataLen < 131584)
			{
				return -1;
			} 

			m_ByteRecords = 63;
			break;
		}
	case 61:
		{			
			if(DataLen < 93184)
			{
			//	str.Format("61采点不够:%d,应为93184",DataLen);
			//	WriteToLog(str);
     			return -1;
			} 

			m_ByteRecords = 45;
			break;
		}
	case 62:
		{			
			if(DataLen < 185344)
			{	
				//str.Format("62采点不够:%d,应为185344",DataLen);
				//WriteToLog(str);
				return -1;
			}
			
			m_ByteRecords = 90;
			break;
		}
	}
	
	//采集的数据转换
	for( i = 0;i < DataLen; i ++)
	{
		//大于2048为负数
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
		
	}

    //解码10度角,用的是新协议,前1024个点是空的,波形折算成位
	for(index = 0; index < m_ByteRecords ;index ++)
	{
		
		//用相关性算法求解,3-1,4-2
		for( i = 0;i < 512;i ++)   
		{ 
			//得到信号尖,间一个波减前一个波,如3-1,4-2个波,出4个尖
			Diffs[i]        = DataBuf[(index * 4 + 2) * 512 + i + 1024] - DataBuf[index * 4 *  512 + i  + 1024];
			Diffs[512 + i]  = DataBuf[(index * 4 + 3) * 512 + i + 1024] - DataBuf[(index * 4 + 1) * 512 + i + 1024];
		}
		
		//叠加数据
		for( i = 0;i < 256;i ++)   
		{ 
			Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i];
		}
		
		//匹配值
		for(int jj = 0; jj < m_maxpptimes; jj ++)
		{
			//10度匹配波
			m_ppresult10[index*m_maxpptimes + jj]   = CorrelationCheck(Correlation_Table10,Diffs,jj);
			//5度匹配波
			m_ppresult05[index*m_maxpptimes + jj]   = CorrelationCheck(Correlation_Table05,Diffs,jj);
		}
		
	}
	

	for(short yyy = 0 ; yyy < 2; yyy ++)
	{
		
		switch(yyy)
		{
		case 0:
			{	  
				//signstr.Format("【++++++++++10度解码++++++++++】");
				//WriteToLog(signstr);

				//10度
				for(int jj = 0 ; jj < m_ByteRecords*m_maxpptimes; jj ++)
				{
					m_ppresult[jj] = m_ppresult10[jj];
				}
				break;
			}
		case 1:
			{	
				//signstr.Format("【++++++++++05度解码++++++++++】");
				//WriteToLog(signstr);
				
				//5度
				for(int jj = 0 ; jj < m_ByteRecords*m_maxpptimes; jj ++)
				{
					m_ppresult[jj] = m_ppresult05[jj];
				}

				break;
			}
		}

		//最大匹配值
		m_maxppvalue  =    0;
		
		//找最大匹配值
		for(int jj = 0; jj < m_maxpptimes; jj ++)
		{
			
			m_ppvalue    =    0;//匹配值和
			
			for(index = 0; index < m_ByteRecords ;index ++)
			{
				
				m_ppvalue = fabs(m_ppresult[jj + m_maxpptimes * index]) + m_ppvalue;
				
			}
			
		//	signstr.Format("匹配系统值：m_ppresult[%d]=%.3f",jj,m_ppvalue);
		//	WriteToLog(signstr);	
			
			if(m_ppvalue > m_maxppvalue)
			{
				m_maxppvalue  =  m_ppvalue;//最大匹配值
				m_pipeiplace  =         jj;//记住最佳匹配位置
			}
			
		}
		
		//signstr.Format("m_pipeiplace=%d",m_pipeiplace);
		//WriteToLog(signstr);

	    //最佳匹配位置的数据
	    for(index = 0; index < m_ByteRecords ;index ++)
		{
			
	//	    signstr.Format("m_ppresult[%d] = %.3f",m_pipeiplace + m_maxpptimes * index,m_ppresult[m_pipeiplace + m_maxpptimes * index]);
	//	    WriteToLog(signstr);

			//匹配值和
			if(m_ppresult[m_pipeiplace + m_maxpptimes * index]  > 0)
			{
				SignalBit[index] = 0;
			}
			else 
			{
				SignalBit[index] = 1;
			}

		 	//signstr.Format("m_ppresult[%d]=%.3f",index,m_ppresult[m_pipeiplace + m_maxpptimes * index]);
		    //WriteToLog("\r\n"+ signstr + "\r\n");
			
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
				
				//用相关性算法求解,3-1,4-2
				for( i = 0;i < 512;i ++)   
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
					Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				
				if(yyy == 0)
				{   
					//10度
					m_ppvalue = CorrelationCheck(Correlation_Table10,Diffs,m_pipeiplace);
				}
				else
				{
					// 5度
					m_ppvalue = CorrelationCheck(Correlation_Table05,Diffs,m_pipeiplace);
				}
				
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
			
		//	WriteToLog("\r\n开始解码\r\n");	
			Sleep(100);	
			
			if(!(m_sums <= 6 ))
			{	
				//WriteToLog("范围错误");
				return -1;
			}
			
			//31212解码
			if(DecodeBCH31212(TempSignalBit))
			{

			//	signstr.Format("匹配位置:m_pipeiplace=%d,命令：0x%0x，模块号：%d,纠码：m_CollectNos＝%d，对位错：m_sums=%d",m_pipeiplace,Item,ModuleNum,m_CollectNos,m_sums);
			//	WriteToLog("\r\n"+ signstr + "\r\n");

        		//对一下纠的位,如果有纠码的位
				if(m_CollectNos > 0)
				{
					m_checkplace  =    FALSE;
					
					//对位算法,查纠的位是否是在不同的位置中
					for(i = 0; i < m_CollectNos;i ++)
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
						dataValue = dataValue + double(TempSignalBit[10 + i]*pow((double)2,i));
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
						if(Item== 0x63 ||  Item== 0x62 )
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
							if((Item>= 0x64 && Item<=0x69) || Item==0x04)
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
						 Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
					 }				
					 
					 if(yyy == 0)
					 {   
						 //10度
						 m_ppvalue = CorrelationCheck(Correlation_Table10,Diffs,m_pipeiplace);
					 }
					 else
					 {
						 // 5度
						 m_ppvalue = CorrelationCheck(Correlation_Table05,Diffs,m_pipeiplace);
					 }
					 
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
			 for(  i = 0; i <  45; i ++)
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
		//	 WriteToLog("解码开始");
			
			//对收到的数纠码,45273
			if(DecodeBCH63394(TempSignalBit,FALSE))//纠码对的话
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

				//16进制解码
				dataValue   =     0.00;
				m_sums      =        0;
				
				//7位一检验和
				for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
				{
					
					//数据位变成字节,7位一检验和 
					for( i = 0;i < 7; i ++)
					{  	
						
						m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow((double)2,6-i));
						
					}
					
				}
				
				//如果检验和对的话
			    if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
				{
					
					//算出值
					for( i = 0; i < 21; i++)
					{
						dataValue = dataValue + double(SignalBit[18 + i]*pow((double)2,20-i));
					}	
					
		//			str.Format("dataValue = %d",int(dataValue));
		//			AfxMessageBox(str);
		//			WriteToLog(str);
					
					if(SignalBit[38] == 1)
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
								if(Item==0x08 || Item==0x09 || Item==0x0B || Item==0x0A) 
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
				else
				{
					//检验和不对
					dataValue =  -1;
					
				}

    			//str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				//WriteToLog(str);
			
			}

			//45273解码
			dataValue   =   -1;
			 
		 }
	     else
		 {
			
			//顺序调整，如果是31、32、71、72协议的话
			for( i = 0; i <  63; i ++)
			{
				
				if( i < 24 )
				{
					TempSignalBit[i]    = SignalBit[23 - i];
				}
				else
				{
					TempSignalBit[i]    = SignalBit[62 - i + 24];
				}
				
			}	
			
		//	Sleep(100);

			//对收到的数纠码,63394
			if(DecodeBCH63394(TempSignalBit,TRUE))//纠码对的话
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
					dataValue = dataValue + Signal[i] * 100000.00/pow((double)10,i);
					
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
					//只有485表才有电表故障,485电表通讯错误
					return  -2;			
				}
				else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
				{
					
					//只有485表才有电表故障,电表故障2
					return  -3;
				}
				else if( Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
				{
					
					//读驻留时模块没有收到过驻留命令回的数
					return  -4;
					
				}	
				else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
				{  	

					//打包读表、3电压A流、BC电流功率因素无功功率、
					if(m_QuickReading && ((Protocol/10)== 7)  && ((ModuleNum%100) >= 12) && (Item==0x60 || Item==0xF0 || Item==0x62 || Item==0xF2 || Item==0x64 || Item==0x66 || Item==0xf4 || Item==0xf6))
					{
                       
					    //71,72的快速读表
						if(Item==0x60 || Item==0xF0 || Item==0x62 || Item==0xF2)
						{																
							 
							 //3电压A电流,BC电流,功率因素,无功功率
							 for(int iiiii = 0 ; iiiii < 4; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 8 ; jjjjj ++)
								 {
                                      m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*8 + jjjjj]*int(pow((double)2,7-jjjjj));
                                 }

                             }

							 if(Item==0x60 || Item==0xF0)
							 {
								 //3电压A电流
								 m_Quick71Value[0] = m_Quick71Value[0]*2;
								 m_Quick71Value[1] = m_Quick71Value[1]*2;
								 m_Quick71Value[2] = m_Quick71Value[2]*2;
								 m_Quick71Value[3] = m_Quick71Value[3]*0.2;
							 }
							 else
							 {
								 //BC电流,功率因素,无功功率
								 m_Quick71Value[0] = m_Quick71Value[0]*0.2;
								 m_Quick71Value[1] = m_Quick71Value[1]*0.2;
								 m_Quick71Value[2] = m_Quick71Value[2]*0.01;
								 m_Quick71Value[3] = m_Quick71Value[3]*0.01;
							 }


						}
						else if (Item == 0x64 || Item == 0xF4)
						{											
							
							 //峰，平，谷快速读表
							 for(int iiiii = 0 ; iiiii < 3; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 10 ; jjjjj ++)
								 {
                                     
									   m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*10 + jjjjj]*int(pow((double)2,9-jjjjj));
                                 
								 }

                             }
						
						}
						else if(Item == 0x66 || Item == 0xF6)
						{
							
							//有功、无功
							for(int iiiii = 0 ; iiiii < 2; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 16 ; jjjjj ++)
								 {
                                     
									   m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*16 + jjjjj]*int(pow((double)2,15-jjjjj));
                                 
								 }

                             }
							
						//	WriteToLog(strValue);

						}

    					/*
						dataValue =   0; 

						//二进制的数
						for(int jjj = 0; jjj < 32; jjj ++)
						{
                            dataValue = dataValue + Data[jjj]*int(pow((double)2,31-jjj));
							
							str.Format("快速读表值:%.2f",dataValue);
					  	    WriteToLog(str);

						}
						*/

					//	str.Format("快速读表值:%.2f",dataValue);
					//	WriteToLog(str);

						return 1;//(dataValue + 0.001);
					}
					
					//快速读表,三个数据打在一起
					if(ModuleNum%100 <= 8 && (Item==0x0E || Item==0x8e || Item==0x10 || Item==0x90 || Item==0x12 || Item==0x92) && m_QuickReading)
					{
                        dataValue =   0;

						//二进制的数
						for(int jjj = 0; jjj < 30; jjj ++)
						{
                            dataValue = dataValue + Data[jjj]*int(pow((double)2,29-jjj));
						}

					//	str.Format("快速读表值:%d",long(dataValue));
					//	WriteToLog(str); 

						return  long(dataValue + 0.001);
					}

					//检验和
					if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
					{
						//WriteToLog("检验和对!");
						
						//0的处理,485表都是0的话，不正常,有功为0不正常
						if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
						{
							return  -2;
						}
						
						return  dataValue;
						
					}
					
					//WriteToLog("检验和不对!");
					
					dataValue = -1;
				}

				

				dataValue =  -1;

			}

			/*********顺序调整，如果是31、71、72协议的话*/
			dataValue =  -1;
			
		}

    }
		
	return dataValue;
}


void CIFRMView::WriteP9111_CHANNEL_DOPort(int value)
{
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


/****************************  执行命令   **********************************
COMMAND  执行命令
格式为:
1、BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  参数1---母线,参数2---相别,参数3---发送的时间单位数(8的倍数),参数4---发送的时间(字符形式) 执行发驻留命令
2、BEGINS;COMMAND:01:参数1;ENDS              参数1---数据范围                       执行测试读表操作
3、BEGINS;COMMAND:02:参数1;ENDS              参数1---数据范围                       执行正式读表操作
4、BEGINS;COMMAND:03:参数1;ENDS              参数1---数据范围                       执行驻留读表操作
5、BEGINS;COMMAND:04:参数1;ENDS              参数1---数据范围                       执行送电操作
6、BEGINS;COMMAND:05:参数1;ENDS              参数1---数据范围                       执行停电操作
****************************************************************************/
//图表显示
void CIFRMView::OnOwemoney() 
{  
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
    CChartDlg     dlg;
	dlg.DoModal();

}


/************************************************************************
**    总格式:引导字BEGINS;命令字选项;*;*;*;*;*;*;ENDS 
**
**     MESSAGE    显示消息对话框
**          格式为:
**               a、BEGINS;MESSAGE:0:内容;ENDS 显示提示对话框
**               b、BEGINS;MESSAGE:1:内容;ENDS 显示警告对话框
**
**     DATAS      数据传递
**         收到的格式有两种:
**         a、BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
**         b、BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
**         c、BEGINS;DATAS:2:表名;读表结束;ENDS      数据传送结束标志
**         d、BEGINS;DATAS:3:StopData;停止;ENDS      设置停止按钮标记
** 
**                                      
**     SEND       发送数据(在列表中显示)
**          格式为:
**                   BEGINS;SEND:表名:查询条件;ENDS 要其传送满足条件的数据
** 												 
** 
**    COMMAND  执行命令
**    格式为:
**    1、BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  参数1---母线,参数2---相别,参数3---发送的时间单位数(8的倍数),参数4---发送的时间(字符形式) 执行发驻留命令
**    2、BEGINS;COMMAND:01:参数1;ENDS              参数1---数据范围                       执行测试读表操作
**    3、BEGINS;COMMAND:02:参数1;ENDS              参数1---数据范围                       执行正式读表操作
**    4、BEGINS;COMMAND:03:参数1;ENDS              参数1---数据范围                       执行驻留读表操作
**    5、BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
**                         参数1---标题         参数2---结果                   参数3---条件范围
**    	                   参数4---命令字       参数5---是否只读相不定         参数6---次数        
**    	                   参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
**    	                   参数10--间隔         读写各项测试参数,处理各项参数
****************************************************************************/
void CIFRMView::OnOnCommMscomm() 
{
	
	switch(m_Com.GetCommEvent()) 
	{ 
	case 1: 
		{
		
			break; 
		}
	case 2: 
		{   
		    //接收二进制数据方式,分析可能的数据 
			BinarySystemReceive();
			break; 
		}
	default: 
		{
			// 传输事件出错,清除缓冲区 
			m_Com.SetOutBufferCount(0);  
			break; 
		}

	}

}

/***************************************************************
串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
波特率 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
检验位 0-无校验,1－奇校验,2－偶校验
数据位 0-4     ,1-5      ,2-6      ,3-7    ,4-8
停止位 0-1     ,1-1.5    ,2-2
//二进制方式传送
**************************************************************/
void CIFRMView::OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex)
{

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
    
	//停止位 0-1,1-1.5,2-2
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
	m_Com.SetPortOpen(TRUE);         //打开端口
	m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加
	m_Com.SetInputMode(1);           //0 文本形式 1二进制形式
    
	ParameterStr.Format("%s,%s,%s,%s",SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);//设置波特率 ，检验位 ，数据位 ，停止位	
	m_Com.SetSettings(ParameterStr); //"600,n,8,1"
	m_Com.SetRThreshold(1);          //每接收1个字符就触发1次接收事件
	m_Com.SetInputLen(0);            //每次读取一个字符,二进制形式
	m_Com.GetInput();                //清除原有的数据
	
}

//拔号
void CIFRMView::Dial(CString m_strPhoneNumber,BOOL IfVoice)
{
	
	StatusStr = "";
	CString          strTemp;
	m_Com.SetDTREnable(TRUE);//Open DTR
	m_Com.SetRTSEnable(TRUE);//Open RTS 允许串口--->moden发数据
		
	SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM复位（Reset），重新读取预存第0组的设定参数值。
	Sleep(500);

	if(IfVoice)
	{
		//有声
		strTemp = "ATM1\r\n";//
	}
	else
	{
		//无声
		strTemp = "ATM0\r\n";//
	}

	//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
	//Str             发送字符
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	SelectSendString(1,strTemp,FALSE,FALSE,FALSE);
  	Sleep(500);

	//strTemp = "ATDT" + m_strPhoneNumber + "\r\n"; ATDT 语音拔号
	strTemp = "ATD" + m_strPhoneNumber + "\r\n";
	//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
	//Str             发送字符
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	SelectSendString(1,strTemp,FALSE,FALSE,FALSE);

	Sleep(300);

	//电话拔号的标志
	m_IsDialConnectting    = FALSE;


}

//断开连接
void CIFRMView::DisConnect(short kinds)
{	
	switch(kinds)
	{
	case 0:
		{   
			//打开串口
			if(m_Com.GetPortOpen())    
			{
				m_Com.SetPortOpen(FALSE);
			}
			break;
		}
	case 1:
		{
			if(m_Com.GetCDHolding())
			{
				//如果是远程版的话
				if(!AppInfo::Instance().m_WhichKind)
				{	
					SelectSendString(1, "BEGINS;COMMAND:28:^CLOSED^MODEM?^OK!;ENDS", FALSE,FALSE,TRUE);
				}
								
				SelectSendString(1,"+++",FALSE,FALSE,FALSE);     //而且收到连续三个+++, 之后3秒钟又没有任何数据, Modem就进入命令模式, 可以利用AT命令集进行配置
				Sleep(3200);

				SelectSendString(1,"ATH0\r\n",FALSE,FALSE,FALSE);//断开电话连接
				Sleep(500);
				
				SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM复位（Reset），重新读取预存第0组的设定参数值。
				Sleep(500);

				//如果是本地版
				if(AppInfo::Instance().m_WhichKind)
				{
					//自动应答状态
					AutoAnswer(FALSE);
				}

				status("【拔号网络已断开】");
				
			}
			break;
		}
	case 2:
		{
			if(m_IsConnect)
			{
				//如果是远程版的话
				if(!AppInfo::Instance().m_WhichKind)
				{			
		            SelectSendString(2, "BEGINS;COMMAND:28:^CLOSED^INTERNET?^OK!;ENDS", FALSE,FALSE,TRUE);
					Sleep(100);
				}
				
				OnCloseWinsock();
			}
   			break;
		}

	}

	//TRUE 变电站版本  FALSE电局版
	if(!AppInfo::Instance().m_WhichKind)
	{
		//如果是远程版的话
		m_StartRead = FALSE;
		status("                     ");
	}

}

/******************************************************************
**         收到的格式有两种:
**         a、BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
**         b、BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
**         c、BEGINS;DATAS:2:表名;读表结束;ENDS      数据传送结束标志
**         d、BEGINS;DATAS:3:StopData;停止;ENDS      设置停止按钮标记
*******************************************************************/
//实时接收显示数据
void CIFRMView::RealTimeReceiveData(CString str)
{	
	CString  data,GetStr,StrTemp;
	CString    FileName,DataName;
	CString         TempStr[27];		
	CFileFind            finder; 
    int           k =         0;

	BOOL   m_IfRepeat =   FALSE;//断点时是否重写列表
	
	//已经去掉了"BEGINS;"和 ";ENDS",只剩下中间的东东了
	switch(atoi(str.Mid(6,1)))
	{
	case 0:
		{
			//BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
			k   =  str.Find(';');
			status("【正在接收数据，请稍侯...】");
			
			//演示或隐藏动画
			OperationAnimation(TRUE);

			if(k != -1)
			{
				data             =    str.Right(str.GetLength() - k - 1);
				m_PassRecords    =    0;
				StrTemp = str.Left(k);
				//得到传送的数据表名
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
    			//////////////////////////////////
				//data为数据+";0"或"0;"
				//;0 为不是断点传输 ;1是断点传输
				k = atoi(data.Right(1));

				//数据
				data = data.Left(data.GetLength() - 1);//-2);
                //////////////////////////////////////////////
				
				//文件名	
                FileName.Format("%s%s.txt",GetFolder(),DataName);
                
				//不是断点传输
				if(k == 0)
				{
					//如果存在数据则添加入库
					if(finder.FindFile(FileName) != 0) 
					{ 
						//存在此文件的话则删除此文件
						::DeleteFile(FileName);
					}

				}
				else
				{
					
					//是断点传输
					m_IfRepeat = TRUE;
					
					//如果不重写列表的话
					if(!m_IfRepeat)
					{
						//行数即为原来传的记录个数
						m_PassRecords = m_Grid.GetColumnCount();
					}
					else
					{
						//从文件中取出行数
						m_PassRecords = GetDataLines(FileName);
					}
	
				}

				//如果是不支持断点或支持断点但要重写列标题
				if(k == 0 || (k== 1 && m_IfRepeat))
				{
					//显示列表头
                    ShowGridHead(data);
					SurrenderWindowMessage();
				}
						
				m_StartRead  =  TRUE;

				//可以接收数据了
				m_ReceiveOk  =  TRUE;

			}
			break;
		}
    case 1:
		{
			//BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
			//不能接收数据
			if(!m_ReceiveOk)
			{
				return;
			}

	        //演示或隐藏动画
			OperationAnimation(TRUE);

			m_PassRecords++;
			CString     strValue;
			CString m_FieldNames;//字段名称
			long        ModuleNo;//模块号

			k   =  str.Find(';');
			
			if(k != -1)
			{
				
				data    = str.Right(str.GetLength() - k - 1);
				StrTemp = str.Left(k);
				//得到传送的数据表名
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
				
				//文件名	
				FileName.Format("%s%s.txt",GetFolder(),DataName);
			    int    colum     = 0;
				
				while(data.Find(';') != -1)
				{
					
					k   =  data.Find(';');
					
					if(k != -1)
					{
						
                        TempStr[colum] =  data.Left(k);
						//用,分开
						GetStr = GetStr + TempStr[colum] + ",";
						
						TempStr[colum] = " " + TempStr[colum];
						
						data  = data.Right(data.GetLength() - k - 1);
						
						colum++;
					}
					
				}
				
				
				TempStr[colum] = data;
				
				GetStr = GetStr + TempStr[colum];
				
				//写入文本文件
				FILE *text;
				if((text = fopen(FileName,"a")) != NULL)
				{
					fputs(GetStr + "\r\n",text);
					fclose(text);
				}
				
				//如果有数据
				if(colum > 0)
				{	

					//add 2004.10.13if(colum + 1 == m_list.GetColumns() && m_list.GetColumns()>0)
					if(colum + 1 == m_Grid.GetColumnCount() && m_Grid.GetColumnCount() > 0)
					{
						//显示结果列表
						AddlistItem(TempStr,colum + 1);
					}
                    
				    //IfWriteData     是否写入数据库 FALSE---不写 TRUE---写
                    //WhichTable      哪个表 0----数据表 1----驻留表
					if(DataName == "ZSDB_DATA")
					{
						//正式读表 
						if(TempStr[11].Find("电表故障") != -1)
						{
							return;
						}
						
						//模块号
						ModuleNo = atol(TempStr[5]);
						
						//时间去空格
						TempStr[12].TrimLeft();
						TempStr[12].TrimRight();
						
    					TempStr[10].TrimLeft();
						TempStr[10].TrimRight();
						
						//根据传来的值来判段是什么值 
						if(TempStr[10] == "有功电度")
						{
							m_FieldNames = "REALTIME_WORKDEGREE";
						}
						else if(TempStr[10] == "累积有功电度")
						{
							m_FieldNames = "REALTIME_WORKDEGREETOTAL";
						}
						else if(TempStr[10] == "无功电度")
						{
							m_FieldNames = "REALTIME_LOSEDEGREE";
						}
						else if(TempStr[10] == "累积无功电度")
						{
							m_FieldNames = "REALTIME_LOSEDEGREETOTAL";
						}
						else if(TempStr[10] == "A相电流")
						{
							m_FieldNames = "REALTIME_ACURRENT";
						}
						else if(TempStr[10] == "B相电流")
						{
							m_FieldNames = "REALTIME_BCURRENT";
						}
						else if(TempStr[10] == "C相电流")
						{
							m_FieldNames = "REALTIME_CCURRENT";
						}
						else if(TempStr[10] == "A相电压")
						{
							m_FieldNames = "REALTIME_AVOLTAGE";
						}
						else if(TempStr[10] == "B相电压")
						{
							m_FieldNames = "REALTIME_BVOLTAGE";
						}
						else if(TempStr[10] == "C相电压")
						{
							m_FieldNames = "REALTIME_CVOLTAGE";
						}
						else if(TempStr[10] == "电压")
						{
							
							//查是哪一象的模块
							if(TempStr[8].Find('A') != -1)
							{
								m_FieldNames = "REALTIME_AVOLTAGE";
							}
							else if(TempStr[8].Find('B') != -1)
							{
								m_FieldNames = "REALTIME_BVOLTAGE";
							}
							else
							{
								m_FieldNames = "REALTIME_CVOLTAGE";
							}
							
						}
						
						//存入正式读表表中
						//REALTIME_MODULENO 模块号 , REALTIME_PROTOCOL 对应协议   
						strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_TRANSCRIBETIME,REALTIME_PROTOCOL) VALUES (%d,%.2f,'%s',%d)",m_FieldNames,ModuleNo,atof(TempStr[11]),TempStr[12],0);
					
						//运行SQL语句
						CDataBaseInstance::ExecuteDataBaseSQL(strValue);

						
					}
					else if(DataName == "ZLDB_DATA")
					{	

						//驻留读表,有故障的模块写入表中
						if(TempStr[11].Find("电表故障") != -1)
						{
							return;
						}
						
						//模块号
						ModuleNo = atol(TempStr[5]);
						
						//时间去空格
						TempStr[12].TrimLeft();
						TempStr[12].TrimRight();
						
						//驻留数据表,驻留读表的话,存入TB_GARRISON表中
						strValue.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",ModuleNo,TempStr[12]/*驻留时间*/);
						
						TempStr[10].TrimLeft();
						TempStr[10].TrimRight();
						
						
						//根据传来的值来判段是什么值 
						if(TempStr[10] == "有功电度")
						{
							m_FieldNames = "GARRISON_WORKDEGREE";
						}
						else if(TempStr[10] == "累积有功电度")
						{
							m_FieldNames = "GARRISON_WORKDEGREETOTAL";
						}
						else if(TempStr[10] == "无功电度")
						{
							m_FieldNames = "GARRISON_LOSEDEGREE";
						}
						else if(TempStr[10] == "累积无功电度")
						{
							m_FieldNames = "GARRISON_LOSEDEGREETOTAL";
						}
						else if(TempStr[10] == "A相电流")
						{
							m_FieldNames = "GARRISON_ACURRENT";
						}
						else if(TempStr[10] == "B相电流")
						{
							m_FieldNames = "GARRISON_BCURRENT";
						}
						else if(TempStr[10] == "C相电流")
						{
							m_FieldNames = "GARRISON_CCURRENT";
						}
						else if(TempStr[10] == "A相电压")
						{
							m_FieldNames = "GARRISON_AVOLTAGE";
						}
						else if(TempStr[10] == "B相电压")
						{
							m_FieldNames = "GARRISON_BVOLTAGE";
						}
						else if(TempStr[10] == "C相电压")
						{
							m_FieldNames = "GARRISON_CVOLTAGE";
						}
						else if(TempStr[10] == "电压")
						{
							
							//查是哪一象的模块
							if(TempStr[8].Find('A') != -1)
							{
								m_FieldNames = "GARRISON_AVOLTAGE";
							}
							else if(TempStr[8].Find('B') != -1)
							{
								m_FieldNames = "GARRISON_BVOLTAGE";
							}
							else
							{
								m_FieldNames = "GARRISON_CVOLTAGE";
							}
							
						}
						
						//原先驻留库中没有此驻留时间的数据
						if(CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", strValue) < 1)
						{
							//GARRISON_MODULENO 模块号 , GARRISON_PROTOCOL 对应协议  , GARRISON_HALTTIME 驻留时间
							strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,%s,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s','%s')",m_FieldNames,ModuleNo,atof(TempStr[11]),0,TempStr[12],TempStr[12]);
						}
						else
						{   
							//原先驻留库中有此驻留时间的数据,则替换原来数据
							//如果是读有功电度或冻结电度,则加上原来的表底
							strValue.Format("UPDATE TB_GARRISON SET %s = %.2f,GARRISON_HALTTIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_FieldNames,atof(TempStr[11]),TempStr[12],ModuleNo,TempStr[12]);
						}
				
						//运行SQL语句
						CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										
						
					}
				    
					m_StartRead =  TRUE;
				
                 }
				
			}
			m_StartRead =	TRUE;			
			break;
		}
	case 2:
		{
			
			//不能接收数据
			if(!m_ReceiveOk)
			{
				return;
			}

			BOOL  m_IsOk = FALSE;
			m_StartRead         =        FALSE;
			m_ReceiveOk         =        FALSE;
			//BEGINS;DATAS:2:表名;读表结束;ENDS      数据传送结束标志
			k   =  str.Find(';');
			
			if(k != -1)
			{
				
				data  = str.Right(str.GetLength() - k - 1);
				StrTemp = str.Left(k);
				//得到传送的数据表名
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
				//文件名	
				FileName.Format("%s%s.txt",GetFolder(),DataName);
				//显示有多少条记录传过来了
				data.Format("接收数据完毕,记录%d条,文件:安装目录+%s.TXT",m_PassRecords,DataName);
				status(data);

				//演示或隐藏动画
			    OperationAnimation(FALSE);
				
				//如果存在数据则添加入库
				if(finder.FindFile(FileName) != 0) 
				{ 
	
					if(DataName != "ZSDB_DATA" && DataName != "ZLDB_DATA" && DataName != "TB_HISTORYDATAS")
					{
						
                        //本地版，远程传来的数据
						if(	AppInfo::Instance().m_WhichKind == TRUE)
						{
						 
							//处理重复数据记录 m_DataName   表名,TxtFileName  导入文本文件
							DealRepeatRecord(DataName,FileName);
							
							//发送信息
							SendContionStr.Format("接收数据完毕，添加记录%d条［注：重复记录先删后添］",m_PassRecords);
							status(SendContionStr);

                    		//发送信息
							SendContionStr.Format("BEGINS;MESSAGE:0:远程机器接收数据完毕,共添加数据记录%d条！\r\n注：遇到重复记录时先删除重复记录后添加！;ENDS",m_PassRecords);
							SendMessage(WM_EVENT, 4, 0);
							
							//如果是用户数据表或变台表
							if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
							{
								//树控件重新刷新一次
								RefreshTree();
							}

								
						}
						else
						{

							data.Format("数据传送完毕，你想把远程传来的共计%d条数据记录，\r\n存入本地对应的库表中吗?",m_PassRecords);
													
							if(MessageBox(data,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
							{
								//处理重复数据记录 m_DataName   表名,TxtFileName  导入文本文件
							    DealRepeatRecord(DataName,FileName);

								//如果是用户数据表或变台表
								if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
								{
									//树控件重新刷新一次
									RefreshTree();
								}

							}
											
						}
							
						
					}
					//不是读模块生成的数的话
							
				}
				//如果传来的数据存在文件中的话
				
			}

			break;
			//能接收数据
		}
		
	}
	
}


//初始化数据库
void CIFRMView::InitGrid(CString table,CString BeginTime,CString EndTime)
{

	//打开数据库
	CDatabase               db;
	CString    strSql,strValue;
	
	//起始时间
	short m_year,m_month,m_day,m_hour,m_minuter,m_second;
    m_year       =         atoi(BeginTime.Mid( 0,4));
    m_month      =         atoi(BeginTime.Mid( 5,2));
    m_day        =         atoi(BeginTime.Mid( 8,2));
    m_hour       =         atoi(BeginTime.Mid(11,2));
	m_minuter    =         atoi(BeginTime.Mid(14,2));
    m_second     =         atoi(BeginTime.Mid(17,2));

	if(m_minuter == 0 && m_second == 0)
	{
       BeginTime.Format("%d-%d-%d %d时",m_year,m_month,m_day,m_hour);
	}
	else
	{   
		if(m_second == 0)
		{
		   BeginTime.Format("%d-%d-%d %d:%d",m_year,m_month,m_day,m_hour,m_minuter);
		}
		else
		{
            BeginTime.Format("%d-%d-%d %d:%d:%d",m_year,m_month,m_day,m_hour,m_minuter,m_second);
		}
	} 
	
	//终止时间
	m_year       =         atoi(EndTime.Mid( 0,4));
    m_month      =         atoi(EndTime.Mid( 5,2));
    m_day        =         atoi(EndTime.Mid( 8,2));
    m_hour       =         atoi(EndTime.Mid(11,2));
	m_minuter    =         atoi(EndTime.Mid(14,2));
    m_second     =         atoi(EndTime.Mid(17,2));

	if(m_minuter == 0 && m_second == 0)
	{
       EndTime.Format("%d-%d-%d %d时",m_year,m_month,m_day,m_hour);
	}
	else
	{   
		if(m_second == 0)
		{
			EndTime.Format("%d-%d-%d %d:%d",m_year,m_month,m_day,m_hour,m_minuter);
		}
		else
		{
            EndTime.Format("%d-%d-%d %d:%d:%d",m_year,m_month,m_day,m_hour,m_minuter,m_second);
		}
	}

	//得到修改状态
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("原来报表已修改,保存报表文件吗?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			OnSavereportas(); 
		}

	}
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		
		//得到记录个数
		long fields = CDataBaseInstance::GetAllRecordsCount(table,"ALL"); 
		
		//如果没有记录
		if(fields < 1)
		{	
			//关闭数据库
			db.Close();
			MessageBox("没有数据可生成报表！！"," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
		strSql.Format("SELECT * FROM %s",table);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到字段个数
		short nFields = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
		
		//删除所有的数据
	    m_Grid.DeleteAllItems();
		
		m_IsHistory    =  FALSE;//是否显示历史数据
		
		//表格
		m_Grid.GetDefaultCell(FALSE,TRUE)->SetFormat(DT_CENTER|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS|DT_SINGLELINE);
        m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(fields + 1);	        //行
		m_Grid.SetColumnCount(nFields + 1);     //列
		m_Grid.SetGridLineColor(RGB(212,208,200));    //RGB(0,0,0)线颜色
		m_Grid.SetColumnWidth(0, 80);
		m_Grid.SetBkColor(RGB(255,255,255));

		for(int i = 0;i < nFields + 1; i++)
		{

			if(i == 0)
			{
				//加上序号列
				m_Grid.SetItemTextFmt(0, i, "序号");
			}
			else
			{
				//数据列
				rs.GetODBCFieldInfo(i - 1,fieldinfo);
				
				fieldinfo.m_strName.TrimLeft();
				fieldinfo.m_strName.TrimRight();
				
				if(fieldinfo.m_strName.Find("本次") != -1 || fieldinfo.m_strName.Find("本月") != -1 )
				{
					fieldinfo.m_strName.Replace("本次",EndTime);
					fieldinfo.m_strName.Replace("本月",EndTime);
				}
				else
				{
					
					if(fieldinfo.m_strName.Find("上次") != -1 || fieldinfo.m_strName.Find("上月") != -1 )
					{
						fieldinfo.m_strName.Replace("上次",BeginTime);
						fieldinfo.m_strName.Replace("上月",BeginTime);
					}

				}
				
				if(fieldinfo.m_strName.Find("读数") != -1)
				{
					fieldinfo.m_strName.Replace("读数","");
				}

				m_Grid.SetItemTextFmt(0, i, fieldinfo.m_strName);
			}
		
		}
		
		status("正在生成打印报表，请稍侯...");
		ShowProgressCtrl(TRUE);
		
		//范围
		SetProgressCtrlRange(0, fields,1);

		
		//读数据信息
		for(int j = 0;j < fields; j++)
		{
			//字段数
			SurrenderWindowMessage();//交出window控制权
		
			for(int i = 0; i < nFields + 1; i++)
			{
				
				if(i == 0)
				{
					strValue.Format("%6d",j + 1);
				}
				else
				{	
					rs.GetFieldValue(int(i - 1),strValue);
					
					strValue.TrimLeft();
					strValue.TrimRight();

					//如果值为空的话
					if(strValue.IsEmpty())
					{
						strValue.Format(" ");
					}
					else
					{
						//有点为数据
						if(strValue.Find(".") != -1)
						{
							strValue.Format("%.2f",atof(strValue));
						}

						//如果是0.00的话,用0换
						if(strValue == "0.00")
						{
                            strValue = " 0";
						}
						
					}
								
				}
				
				//显示数据
				m_Grid.SetItemTextFmt(j + 1,i,strValue);
				
			}
			
			//库下滑一个记录
			rs.MoveNext();
            
			//滚动条下移
			SetProgressCtrlSetIt();
			
		}

		//关闭数据库
		rs.Close( );
		db.Close( );
	
        m_Grid.ShowWindow(SW_SHOW);
		ShowProgressCtrl(FALSE);//隐滚动条
		status("                   ");
    	m_Grid.SetModified(TRUE,-1,-1);	//置已修改状态
	}
	
}

//拔号连接
BOOL CIFRMView::Connect(BOOL  ShowMessage,BOOL IfVoice)
{
	SurrenderWindowMessage();
	
	SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM复位（Reset），重新读取预存第0组的设定参数值。
	Sleep(500);
	SurrenderWindowMessage();

	if(IfVoice)
	{
		//有声	
    	SelectSendString(1,"ATM1\r\n",FALSE,FALSE,FALSE);
	}
	else
	{
		//无声
		SelectSendString(1,"ATM0\r\n",FALSE,FALSE,FALSE);
	}

	Sleep(500);
	SurrenderWindowMessage();

	//状态栏提示信息
	StatusStr   =         "";

	//Modem自动等待连接	
	SelectSendString(1,"ATS0=1\r\n",FALSE,FALSE,FALSE);

	Sleep(500);
    SurrenderWindowMessage();
   	
	if(ShowMessage)
	{
		//全部变为大写
	    StatusStr.MakeUpper();
		
		//如果没有返回值OK
		if(StatusStr.Find("OK") == -1)
		{
			MessageBox("自动应答设置失败,请检查MODEM是否\r\n已连接且电源是否已打开！","警告",MB_OK|MB_ICONWARNING);
			return FALSE;
		}

	}
	else
	{
		//全部变为大写
	    StatusStr.MakeUpper();

		//如果没有返回值OK
		if(StatusStr.Find("OK") == -1)
		{	
			//显示状态栏信息
		    StatusStr = "【自动应答失败】";
			SendMessage(WM_EVENT, 1, 0);

	    	//WriteToLog(StatusStr);
			return FALSE;
		} 
		
		StatusStr = "【自动应答成功】";
		SendMessage(WM_EVENT, 1, 0);

		//WriteToLog(StatusStr);
	
	}

    //自动应答存贮
	SelectSendString(1,"AT&W\r\n",FALSE,FALSE,FALSE);
	Sleep(500);
	SurrenderWindowMessage();

	m_Com.SetDTREnable(TRUE);//Open DTR
	return TRUE;
	
}

//数据库表转成文本文件
BOOL CIFRMView::WriteDataToTextFile(CString dataname,CString Sqlstr,long records,CString filename)
{
	//建立文本指针	
	FILE*     text;
	CString GetStr;
	
	//打开数据库
	CDatabase   db;
	
	if((text = fopen(filename,"w"))==NULL)
	{
		return  FALSE;
	}
	
	status("正在保存表" + dataname + "数据成文本文件" + filename + "，请稍侯...");
	ShowProgressCtrl(TRUE);
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset   rs(&db);
		SetProgressCtrlRange(0, records,1);
		rs.Open(CRecordset::forwardOnly,Sqlstr);
		//得到字段个数
		short nFields = rs.GetODBCFieldCount();
		
		//读用户信息
		for(int  j = 0;j < records; j++)
		{
			
			GetStr  = "";
			
			//字段数
			for(int i = 0; i < nFields; i++)
			{
				
				rs.GetFieldValue(int(i),Sqlstr);
				
				Sqlstr.TrimRight();
				
				if(Sqlstr.GetLength() < 18)
				{
					
					if(Sqlstr.Find('.') != -1)
					{
						Sqlstr.Format("%.2f",atof(Sqlstr));
					}
					
				}
				
				//最后一个字段
				if(i == nFields - 1)
				{
					GetStr = GetStr + Sqlstr;
				}
				else
				{
					GetStr = GetStr + Sqlstr + ",";
				}
				
			}
            
			GetStr.TrimLeft();
            GetStr.TrimRight();

			int k = GetStr.GetLength();

			for(int ii = 0; ii < 300 - k;ii ++)
			{
				GetStr = GetStr + " ";
			}

			fputs(GetStr + "\r\n",text);
			
			SetProgressCtrlSetIt();
			
			//下滑一个记录
			rs.MoveNext();
		}
		
		
		//关闭数据库
		rs.Close();
		
		db.Close();
		
		fclose(text);
		//隐藏状态条
		status("                            ");
		ShowProgressCtrl(FALSE);
		return TRUE;

	}

	return FALSE;
}


//价格数据表操作
void CIFRMView::OnPrice() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	//检查数据库是否打开
	if(m_PriceSet->IsOpen())
	{
		m_PriceSet->Close();
	}
	
	//数据表打开是否正确
	if(m_PriceSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		CELKindDlg  dlg(m_PriceSet.get(),0);
		dlg.DoModal();	
		
		//检查数据库是否打开
		if(m_PriceSet->IsOpen())
		{
			m_PriceSet->Close();
		}

	}
	else
	{
		MessageBox("数据库表打开错误！"," ",MB_OK|MB_ICONWARNING);
	}
	
}

//生成抄表清单
void CIFRMView::FormChaoBiaoData(CString SqlStr,CString BeginTime,CString EndTime)
{
	CString                                     Str;
	status("正在生成抄表电费清单统计表，请稍侯...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
    
	BeginTime.TrimLeft();
    EndTime.TrimRight();

	//表处理
	if(IsCurveTableExist("TB_EXCERPTION"))
	{
		//删除原来的库表
		Str.Format("DROP TABLE TB_EXCERPTION");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	SetProgressCtrlSetIt();
	
	Str = "CREATE TABLE [dbo].[TB_EXCERPTION] (\
		[变台名称] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
		[用户编号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[姓名] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
		[原户号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[模块号] [bigint] NULL ,\
		[计量表编号] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
		[用电类别] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
		[类型] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[上次读数] [float] NULL ,\
		[本次读数] [float] NULL ,\
		[倍率] [int] NULL ,\
		[电量] [float] NULL,\
		[电价] [float] NULL ,\
		[金额] [float] NULL \
    	) ON [PRIMARY]";
		
	//建立数据表
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
//	WriteToLog(Str);
	SetProgressCtrlSetIt();
	
    //此次读表，运行SQL语句用电类别
	Str.Format("INSERT TB_EXCERPTION(变台名称,用户编号,姓名,原户号,模块号,计量表编号,用电类别,类型,上次读数,本次读数,倍率,电量,电价,金额)\
		        SELECT  USER_TRANSFORMERNO AS 变台名称,RTRIM(LTRIM(a.USER_NO)) AS 用户编号,RTRIM(LTRIM(a.USER_NAME)) AS 姓名,RTRIM(LTRIM(a.USER_OLDNO)) AS 原户号,a.USER_MODULENO,a.USER_AMMETERNO,f.ELECTRICITY_KIND,'%s',\
				d.GARRISON_WORKDEGREE,e.GARRISON_WORKDEGREE,a.USER_MULTIPLE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2),f.ELECTRICITY_PRICE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2)*f.ELECTRICITY_PRICE\
					   FROM TB_USER a ,TB_GARRISONBAK d,TB_GARRISONBAK e,TB_ELECTRICITY f WHERE (%s) AND f.ELECTRICITY_NO=a.USER_ELECTRICITYKIND AND d.GARRISON_MODULENO=a.USER_MODULENO AND e.GARRISON_MODULENO=a.USER_MODULENO  AND d.GARRISON_HALTTIME='%s' AND e.GARRISON_HALTTIME='%s'","有功电度",SqlStr,BeginTime,EndTime);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

//	WriteToLog(Str);
    SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  

}

//传送数据表数据
void CIFRMView::OnDatapass() 
{
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
    CString      str;
	
	CSelectTableDlg dlg;
	
	if(dlg.DoModal() == IDOK)
	{
		
		switch(dlg.m_selects)
		{
		case 0:
			{
				
              	//格式: BEGINS;SEND:0:表名:查询条件;ENDS   发送数据,不支持断点传输
				str.Format("BEGINS;SEND:0:%s:%s;ENDS",dlg.StrTable,dlg.Sqlstr);
			    
				//远程发送索取表信息指令
				if(SelectSendString(m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
				{ 
					//停止传送数据
	                m_StopPassing = FALSE;
					m_GetErrors = 0;
				}
				
				m_StartRead = FALSE;
				break;

			}
		case 1:
			{
			
				if(m_Com.GetPortOpen() || m_Com.GetCDHolding() || m_IsConnect)
				{
					m_GetErrors   =   0;
					//提出符合条件的记录
					CString m_filename,m_SqlStr;
					m_filename.Format("%s%s%s",GetFolder(),dlg.StrTable,".TXT");
					
					long fields = CDataBaseInstance::GetAllRecordsCount(dlg.StrTable,dlg.Sqlstr);
					
					if(dlg.Sqlstr == "ALL")
					{
						m_SqlStr.Format("SELECT * FROM %s",dlg.StrTable);
					}
					else
					{
						m_SqlStr.Format("SELECT * FROM %s WHERE %s",dlg.StrTable,dlg.Sqlstr);
					}
					
					if(fields > 0)
					{	
						//停止传送数据
	                    m_StopPassing = FALSE;
						//告诉对方有多少数据
						WriteDataToTextFile(dlg.StrTable,m_SqlStr,fields,m_filename);	
						//告诉对方没有数据
						SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS",dlg.StrTable,fields);
						SendMessage(WM_EVENT, 4, 0);
					}
					else
					{
						m_StartRead = FALSE;
						//告诉对方没有数据
						MessageBox("对不起，此表中没有满足此条件的数据信息!","警告",MB_OK|MB_ICONWARNING);
						return;
					}
					
				}
				else
				{
					MessageBox("端口打开错误!","警告",MB_OK|MB_ICONWARNING);
					return;
				}
				break;
			}
		case 2:
			{
				//远程清除
				if(	AppInfo::Instance().m_WhichKind == FALSE)//TRUE 变电站版本  FALSE电局版
				{	
					
					//格式: BEGINS;SEND:0:表名:查询条件;ENDS   发送数据,在列表中显示数据 
					//str.Format("BEGINS;SEND:0:%s:%s;ENDS",dlg.StrTable,dlg.Sqlstr);
					if(dlg.Sqlstr == "ALL")
					{
					   str.Format("BEGINS;COMMAND:12:DELETE FROM %s ;ENDS",dlg.StrTable);
					}
					else
					{
					   str.Format("BEGINS;COMMAND:12:DELETE FROM %s WHERE %s;ENDS",dlg.StrTable,dlg.Sqlstr);
					}
					
				    //远程发送清除对方表的指令
					if(SelectSendString(m_sendkind, str, TRUE,TRUE,TRUE) == TRUE)
					{
						//m_StartRead = TRUE;
					}
					else
					{
						m_StartRead = FALSE;
					}
					
				}

				break;
			}
		}

	}
	
}


void CIFRMView::OnUpdateConnectsuccess(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(FALSE);
	return;

	CString      TimeStr; 
	
	//TRUE-变电站版本  FALSE-电局版
	if(AppInfo::Instance().m_WhichKind)
	{

		//如果两种状态都通的情况下
		if(m_IsConnect && m_Com.GetCDHolding())
		{	
		
			if(m_DoubleConnected)
			{
				
				m_sendkind        =     1;
				m_DoubleConnected = FALSE;

		    	//关闭远程猫
				SelectSendString(1, "BEGINS;COMMAND:32:【本地版正与局域网远程版在连接(忙)，拔号连接将断开】;ENDS",TRUE,FALSE,TRUE);
				Sleep(200);

				DisConnect(1);
				Sleep(200);
				
				//设成自动应答模式
				AutoAnswer(FALSE);
				m_sendkind = 2;
          
				return;

			}
		
		}
		else if(m_Com.GetCDHolding())
		{  
			//是猫在连接状态
			m_DoubleConnected = TRUE;
			m_sendkind        =    1;

		}
		else if(m_IsConnect)
		{
			//是局域网在连接
            m_DoubleConnected = TRUE;
			m_sendkind        =    2;

		}

	} 


	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{
		 	pCmdUI->Enable(m_Com.GetPortOpen());
			break;
		}
	case 1:
		{	//电话拔号的标志,且是电局版的时候
	        pCmdUI->Enable(m_Com.GetCDHolding());
        
			if(m_Com.GetCDHolding() && !m_IsDialConnectting)
			{
		        
				if(ReadMeterThread != NULL)
				{	
					//拔通时停止原来的工作
				    m_StartRead    =   FALSE;
                    SurrenderWindowMessage();
					Sleep(1000);
				    SurrenderWindowMessage();
				}
				
				m_others         =            FALSE;//				
			    status("【拔号连接成功】");
				ReceiveByteArray.RemoveAll();

				m_IsDialConnectting =   TRUE;	
			    m_IfChangeData      =   TRUE;//修改接收数据标志	
			    m_PassErrortimes    =      0;//错误次数赋为0
			
			}
			else
			{
               
				if(!m_Com.GetCDHolding() && m_IsDialConnectting)
				{
					
			        m_PassErrortimes    =           0;//错误次数赋为0
					m_IsDialConnectting =       FALSE;
					m_IfChangeData      =       FALSE; //修改接收数据标志

					ReceiveByteArray.RemoveAll();
					OperationAnimation(FALSE);        //隐藏状态栏动画
    				StatusStr    =         "";
					Received     =          0;        //如果和长沙在通讯
					
					//本地版时
					if(AppInfo::Instance().m_WhichKind)   
					{
						AutoAnswer(FALSE);	          //自动应答
					}
					
					status("【拔号断开连接】");

				}

			}

			break;
		}
	case 2:
		{   
			//连接标志
			pCmdUI->Enable(m_IsConnect);

			if(m_IsConnect && !m_IsDialConnectting)
			{
			   	
				if(ReadMeterThread != NULL)
				{	
					//拔通时停止原来的工作
				    m_StartRead    =   FALSE;
                    SurrenderWindowMessage();
					Sleep(1000);
				    SurrenderWindowMessage();
				}
			
				m_others         =            FALSE;//
				m_IfChangeData   =             TRUE;//修改接收数据标志
				status("【连接成功,本机:" + m_WinSocket.GetLocalIP() + ",联机:" + m_WinSocket.GetRemoteHostIP()+ "】");
				
				m_IsDialConnectting =       TRUE;
			    m_PassErrortimes    =          0;//错误次数赋为0

			}
			else
			{

				if(!m_IsConnect && m_IsDialConnectting)
				{
					
					//重新启动服务器
					if(AppInfo::Instance().m_WhichKind)
					{
						SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
					}

					status("【TCP/IP网络已断开】");
					m_IsDialConnectting =          FALSE;
					m_IfChangeData      =          FALSE;          //修改接收数据标志
					
				}
				
			}

			break;
		}

	}

}

//写入日记文件
void CIFRMView::WriteToLog(CString Str)
{
	CString  YearLog;
	CTime time  = CTime::GetCurrentTime();
	YearLog.Format("%sifrm%dlog.txt",GetFileFolderPass,time.GetYear());

	FILE *text;
	if((text = fopen(YearLog,"a")) != NULL)
	{
		fputs(Str + "\r\n",text);
		fclose(text);
	}
	
}

void CIFRMView::OnStopexam() 
{
	m_StartRead = FALSE;	
}


void CIFRMView::SurrenderWindowMessage()
{
	
	MSG message;
	
	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

	}
	
}

//long ModuleNo  模块号
//int times      读表次数
//int mode       写表模式 0 error,1 right
void CIFRMView::WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode)
{
	
	CFile       file;
	CString      str;
	CString filename;
	filename.Format("%d%d",ModuleNo,times);
	if(mode == 0)
	{
		filename = filename + "ERROR.TXT";
	}
	else
	{
        filename = filename + "RIGHT.TXT";
	}
	
	if(file.Open(filename,CFile::modeWrite | CFile::modeCreate))
	{	
		file.Seek(0,CFile::begin);
		str.Format("%4d",DataBuf[0]);
		str = str + "\r\n";
		file.Write(str,6);

		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
			str.Format("%4d",DataBuf[i]);
			str = str + "\r\n";
			file.Write(str,6);
		}

		file.Close();
	}
	
}

//双向通讯
BOOL CIFRMView::PcSendToSCM(BYTE ORDER[],BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/)
{
	
	CString        str;	
	CString       str1;
	U32      output[5];
	BYTE    Receive[5];

	ORDER[14]     =  0;

	if(ORDER[2] == 0x53)
	{

		//读表协议 31-39或71-79 意义[十位:3-和校验 7-BCH校验 个位:叠加次数]				
		//十六进制的协议
		ORDER[2] = Protocol/10*16 + Protocol%10;
		
		//如果是22协议
		if(Protocol == 22)
		{
			//当71协议用
			ORDER[2] = 0x71;
		}
		else if(Protocol == 31)
		{
			ORDER[2] = 0x53;
		}	

		//71,72协议
		if(Protocol >= 71 && Protocol <= 73)
		{
			
			//检验字节,BCH校验
			BYTE            g[64];
			BYTE         data[45];
			//	CString   str,strtemp;
			BYTE         TempVale;
			
			//0-5赋为0,前6个数为0
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;
			
			//40个数
			int i;
			for(i = 5; i < 10; i ++)
			{
				
				//str.Format("合成前:ORDER[%d]=0x%0x \r\n",i,ORDER[i]);
				//WriteToLog(str);
				
				TempVale = ORDER[i];
				
				//折成位
				for(int j = 1; j <= 8; j ++)
				{
					data[6 + (i - 5) * 8 + j - 1] = TempVale%2;//add 2004.12.28
					TempVale                      = TempVale/2;
				}
				
			}
			
			//转成BCH码
			//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
            Encode_Bch(g,data,0);
			
			//数据又赋回 5-----13
			for( i = 5; i < 13; i ++)
			{
				
				ORDER[i] = 0;
				
				//位又合成命令字
				for(int j = 0; j < 8;j ++)
				{
					ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow((double)2,j));
				}
				
				//str.Format("合成后:ORDER[%d]=0x%0x \r\n",i,ORDER[i]);
				//WriteToLog(str);
				
			}
			
			ORDER[13] = 0;
		}
		else if(Protocol== 22)
		{
		
			//22协议,检验字节,BCH校验
			BYTE             g[31];
			BYTE            gg[62];
			BYTE          data[21];
			long         TempVale = (ORDER[5]<<13) + (ORDER[6]<<5) + (ORDER[7]>>3);
			
			//21个数
			for(int j = 0; j < 21; j ++)
			{
				//21位数据
				data[20-j] = TempVale%2;
				TempVale     = TempVale/2;     
			}
			
			//转成BCH码
			Encode_Bch(g,data,2);
			
			//22发双份协议,1则发10,0则发送01
			int i = 0;
			for(i = 0; i < 31; i ++)
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
			
			//数据又赋回 5-----13
			for( i = 5; i < 13; i ++)
			{
				ORDER[i]  = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if((i-5)*8+j < 62)
					{
						ORDER[i] = ORDER[i] + BYTE(gg[(i-5)*8+j]<<(7-j));
					}
					else
					{	
						if((i-5)*8+j == 62)
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
						}
						else
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
						}
						
					}
					
				}
			}
			
			ORDER[13] = 0;
			
		}
		else if(Protocol == 61 || Protocol == 62)
		{

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

			//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
			//转成BCH码45_27_3
			Encode_Bch(g,data,1);

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
						ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow((double)2,7-j));
					}
					
				}	
							
			}

			ORDER[13] = 0;
			
		}

	}
	
	ORDER[13]  = m_SendAngle;//发射角度
	
	//long begintimes = GetTickCount();
	
	//发前14位
	int j;
	for(j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//检验和
			ORDER[14] = ORDER[14] + ORDER[j];
		}
	
		//str.Format("发送结果:ORDER[%d]=0x%0x \r\n",j,ORDER[j]);
		//WriteToLog(str);
	//	str1.Format(" %0x \r\n",ORDER[j]);
    //  str = str + str1;
	}	
	

	
	//str.Format("发送结果:ORDER[14]=0x%0x \r\n",ORDER[14]);
	//WriteToLog(str);
	
	//str.Format("ORDER[%d]= %0x \r\n",j,ORDER[j]);
	//WriteToLog(str);
	
	//str1.Format(" %0x ",ORDER[14]);
	//str = str + str1;
    
	//ORDER[14] = ORDER[14]%256;
	//WriteToLog("双向通讯命令：\r\n" + str);	
	
	//发送检验和
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//str.Format("发送用时%d毫秒",GetTickCount()-begintimes);
	//WriteToLog(str);
	
	//空一个数
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//边发边收
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//时钟
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//时钟
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		//高的时侯收数,不要延时
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			//Beep(300,400);
		}

		Receive[j] = BYTE(output[j] & 0xff);
		Sleep(1);
	}
	
    /**/
	str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//最高位两位去掉
    CTime time = CTime::GetCurrentTime();
	CString s;
	s.Format("%4d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //转换时间格式
//	WriteToLog("双向通讯命令：\r\n" + str + "\r\n" + str1 + s);
	
	
//	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		//AfxMessageBox("双向通讯命令检验码不对：\r\n" + str + "\r\n" + str1 + s);
		
		//WriteToLog("双向通讯命令检验码不对：\r\n" + str + "\r\n" + str1 + s);
		//Beep(300,400);
//		return FALSE;
	}
	
	switch(ORDER[2])
	{
	case 0x53://pc机发送
		{
			//Receive[1]－－－母线  Receive[2]－－－ 线路 Receive[3]－－－ 相别
			if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
			{
//	    		WriteToLog("双向通讯时触发命令不对 0x53!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5c://设置A相触发角度
		{
			if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
			{
//				WriteToLog("双向通讯时设置触发角度不对 0x5C!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5d://设置B相触发角度
		{
			if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
			{
//				WriteToLog("双向通讯时设置触发角度不对 0x5d!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0x5e://设置C相触发角度
		{
			if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
			{
//				WriteToLog("双向通讯时设置触发角度不对 0x5e!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0x58://读取A相触发角度
		{
			if(Receive[0] != 0x68)
			{
//				WriteToLog("双向通讯时设置触发角度不对 0x58!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
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
//				WriteToLog("双向通讯时设置触发角度不对 0x59!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
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
//				WriteToLog("双向通讯时设置触发角度不对 0x5a!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
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
			//	WriteToLog("双向通讯时读取直线编号不对 0x5a!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("双向通讯时设置A相延迟角度不对 0xD0!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC1://设置B相延迟角度
		{
			if(Receive[0] != 0xD1)
			{
			//	WriteToLog("双向通讯时设置B相延迟角度不对 0xD1!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC2://设置C相延迟角度
		{
			if(Receive[0] != 0xD2)
			{
			//	WriteToLog("双向通讯时设置C相延迟角度不对 0xD2!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC3://读取A相延迟角度
		{
			if(Receive[0] != 0xD3)
			{
			//	WriteToLog("双向通讯时读取A相延迟角度不对 0xD3!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("双向通讯时读取B相延迟角度不对 0xD4!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("双向通讯时读取C相延迟角度不对 0xD5!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
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

	}


	return TRUE;
}


void CIFRMView::OnAngleset() 
{
 
	//判断是否有程序在运行
	if(CheckRunning())
	{      
		return;
	}
	
	CAngleSettingGlg  dlg;
	dlg.m_WhichKind = AppInfo::Instance().m_WhichKind;
	dlg.DoModal();	
	
}

//向李熙电路板发指令
BOOL CIFRMView::SendOrderToSCM(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/, BYTE ZeroDots/* 延时过0点数*/,BYTE Item/* 要什么东西,命令字*/,int status/*可放时间或其它东西*/,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/)
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
    for(int i = 0 ;i < 15;i ++)
	{
		ORDER[i] = 0;
	}
    
	
	StatusH = status/256;                       //高位    对应的为数据3的后2位
	StatusL = status%256;                       //低位    数据4
	 
	switch(Phase)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
			m_iChSelect = 0;
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			m_iChSelect = 1;
			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
			m_iChSelect = 2;
			break;
		}
	}
	
	//命令字,ORDER[0]到ORDER[4]发给单片机用
	ORDER[0]  = 0x51;    //前导码
	ORDER[1]  = 0x52;    //前导码
	ORDER[2]  = 0x53;    //触发命令
 	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[4]  = ZeroDots;// 延时过0点基数       

	//如果协议为22
	if(Protocol == 22)
	{
		
		//模块号大于0的话为正常读表、停电
		if(ModuleNum > 0)
		{
			//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用  
			//如果是 485表: 10(监督位) + 14(地址)+ 7(命令)
			//如果是脉冲表: 10(监督位) + 14(地址)+ 4(字地址) + 3(命令)
			
			//地址前8位
			ORDER[5]  = (ModuleNum/100)>>6; //地址高位
			
			if(ModuleNum%100 >= 12)
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
			//发站信息
			if(m_handno == 0)
			{
				//o号站 发全0，21个0
				ORDER[5]  = 0x0; 
				ORDER[6]  = 0x0;
				ORDER[7]  = 0x0;
			}
			else
			{
				//1号站 发14个0，7个1	
				ORDER[5]  = 0x0;  //8个0
				ORDER[6]  = 0x03; //6个0 + 2个1
				ORDER[7]  = 0xf8; //5个1 ＋3个0
			}
			
		}
		
		ORDER[8]  =     0;
		ORDER[9]  =     0;


	}
	else  if(Protocol == 61 || Protocol == 62)
	{
		
		//模块号大于0的话为正常读表、停电
		if(ModuleNum > 0)
		{
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
			
		}
		else
		{
			//发站信息
			if(m_handno == 0)
			{
				//o号站 发全0，20个0 ＋ 7位特征码(0001000)
				ORDER[5]  = 0x00; //8个0
				ORDER[6]  = 0x00; //8个0
				ORDER[7]  = 0x01; //4个0 ＋ 0001
				ORDER[8]  = 0x00;
			}
			else
			{
				//1号站       20个1＋ 7位特征码(0001000)	
				ORDER[5]  = 0xff;  //8个1
				ORDER[6]  = 0xff;  //8个1
				ORDER[7]  = 0xf1;  //4个1 ＋0001
				ORDER[8]  = 0x00;
			}
			
		}
	
		ORDER[9]  =     0;
		
	}
	else
	{	
		//如果协议为31、32、71、72等
		//ORDER[5]到ORDER[10]由单片机传给模块用
		ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //命令字，要什么东西＋模块地址最高位
		ORDER[6]  = AddrH;//模块高地址
		ORDER[7]  = AddrM;//模块中地址
		
		//假如是广播冻结
		if(Item == 0xF2)
		{
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
		}
		else
		{
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StationNo;  //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
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
		case 0xF6://送电操作
			{
				
				//送电操作  D3 = 0000****
				//ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
				break;
			}
		case 0xf8://断电操作
			{	
				//断开状态时 D3 = 1111****
				//ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //合成字节,前1-4位为模块低地址,5-6为相位标记(01 A 10 B 11 C),7-8位为手拉手站号
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
				ORDER[9]  =  0x67;                             //此字节后三位为延时过0点数
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
		
		//0x46  写电流值
		//0x4A  写 角 度
		//0x4e  写脉冲率
		//0x52  写变台容量//不要了
		if(Item == 0x46 || Item == 0x4A || Item == 0x4e)
		{
			ORDER[9]  =	m_PassValue;   
		}
		
		//写电流时有换算表,ConversionCurrentValue
		if(Item == 0x46)
		{
			ORDER[9]  =	ConversionCurrentValue(m_PassValue);
		}
		
		
    }
	
	//检验字节,和校验
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和
	//暂时无用
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//向单片机发命令
	return PcSendToSCM(ORDER,Protocol/*读表协议*/,m_SendAngle/*发送的角度*/);
	Sleep(5);
}

//纠码种类63394
BOOL CIFRMView::DecodeBCH63394(BYTE recd[],BOOL m_Is63394)
{
    int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
	int        alpha_to[64], index_of[64];
	CString                           str;
    int   m = 6, n = 63,length,t,k,d;

	if(m_Is63394)
	{
		//63394
		length           =            63;
		t                =             4;
		k                =            39;
		d                =             9;
	}
	else
	{	
		//45273
		length           =            45;
		t                =             3;
		k                =            27;
		d                =             7;
	}

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
	
	t2 = 2 * t;//short
	
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
				//	no. roots = degree of elp hence <= t errors 
				//	str.Format("纠正错误个数： count = %d",count);
				//	WriteToLog(str);
				
				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;	
					
					if(loc[i] >= 24)
					{
						//32-47位为******.**前4个高字节的数不能纠,总共16位
						if((86 - loc[i]) >= 32 && (86 - loc[i]) <= 55)
						{

						}
					
					}
					
				//	str.Format("纠正错误位置：%d",loc[i]);
				//	WriteToLog(str);
				}
				return TRUE;
				
			}
			else
			{
		//		str.Format("错误个数为： count = %d，l[%d] = %d",count,u,l[u]);
		//		WriteToLog(str);
				return FALSE;
			}
			//length - k -> length为数据值 
		}
		else
		{
		//	str.Format("错误个数为：%d > 4 ",l[u]);
		//	WriteToLog(str);
			return FALSE;
		}
		
   	}
	else
	{
	//	str = "t = 0,没有错误";
	//	WriteToLog(str);
		return TRUE;
	}
	
}

BOOL CIFRMView::DecodeBCH31212(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 5, n = 31 , length = 31, t = 2, k = 21, d = 5;
   	
	m_CollectPlace[0]       =       0;
	m_CollectPlace[1]       =       0;

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
			//	str.Format("纠正错误个数： count = %d",count);
			//	WriteToLog(str);
				
				//纠码的个数
				m_CollectNos = count;

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					if( loc[i] < 10)
					{
						m_CollectPlace[i] = 9 - loc[i];
						//str.Format("纠正错误位置：%d",9 - loc[i]);
					}
					else
					{
						m_CollectPlace[i] = 40 - loc[i];
					    //str.Format("纠正错误位置：%d",41 - loc[i]);
					}
					                  
				    //str.Format("纠正错误位置：%d",loc[i]);
					//WriteToLog(str);
					

				}
				return TRUE;
				
			}
			else
			{
				//
				//str.Format("错误个数为： count = %d，l[%d] = %d",count,u,l[u]);
				//WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> length为数据值 
		}
		else
		{
			//
			//str.Format("错误个数为：%d > 4 ",l[u]);
			//WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//	
		m_CollectNos    =    0;
		//str = "t = 0,没有错误";
		//WriteToLog(str);//
		return TRUE;
	}

}

//发驻留命令,每次二遍
void CIFRMView::SendBreadorder(CTime  m_iBroadTime,int times)
{


	CString            str;
	long         broadTime;
	BYTE         ORDER[15];
	BYTE          PhaseBit;
    CTime            time0;
	
	//1601 模块号为16表号为01
	BYTE AddrH,AddrM,AddrL;
	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	StatusStrRead = StatusStr;


	//在自动驻留状态
	if(m_IsAutoSending)
	{
		m_others  =   TRUE;
	}

    //显示状态栏信息
	if(times == 1)
	{
		StatusStr.Format("【正在发驻留%4d-%02d-%02d %02d:%02d:%02d命令，请稍侯...】",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond()); 
	}
	else
	{
		StatusStr.Format("【正在第%d次发驻留%4d-%02d-%02d %02d:%02d:%02d命令，请稍侯...】",times,m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond()); 
	}

	SendMessage(WM_EVENT, 1, 0);
	
	//状态栏显示信息
	//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",str);
	//SendMessage(WM_EVENT, 5, 0);

	m_StartRead  =         TRUE;//能够发的标志

	//得到发驻留信息的母线和协议种类
    SendMessage(WM_EVENT, 20, 0);
	
	if(m_MotherLineArray.GetSize() <= 0 || m_ProtColArray.GetSize() <= 0)
	{
		//显示状态栏信息
		StatusStr.Format("【用户数据表中无用户数据，发送驻留停止】"); 
		SendMessage(WM_EVENT, 1, 0);
		return;
	}

	//好多种协议，每一种都发一次
	for(int kk = 0; kk < m_ProtColArray.GetSize(); kk ++)
	{
		
		SurrenderWindowMessage();
		
		if(!m_StartRead)
		{
			break;
		}

		Sleep(200);
		
		//两母线
		for(int j = 0; j < 2; j++)
		{

			BOOL m_CanContinue = FALSE;

			for(int hhh = 0; hhh < m_MotherLineArray.GetSize(); hhh ++)
			{

                if(m_MotherLineArray[hhh] == (j + 1))
				{
                   m_CanContinue = TRUE;
				   break;
				}

			}

			if(!m_CanContinue)
			{
				continue;
			}

			SurrenderWindowMessage();
			Sleep(200); 

			if(!m_StartRead)
			{
				break;
			}
			
			//三相
	    	for(int i = 0; i < 3; i++)
			{

				SurrenderWindowMessage();
				
				if(!m_StartRead)
				{
					break;
				}

				//计算出发送时间
				time0           = CTime::GetCurrentTime();
				CTimeSpan ts    = m_iBroadTime  -   time0;

				if(m_ProtColArray[kk] == 22 || m_ProtColArray[kk] == 61 || m_ProtColArray[kk] == 62)
				{
					//22协议精度为30分钟，发的为30分钟的倍数,4分钟范围内
					broadTime       = (ts.GetTotalSeconds() + 240)/1800;//倒计时
				}
				else
				{
					//31、32、33、71、72、73精度为8秒分钟
					broadTime       = ts.GetTotalSeconds()/8;//倒计时
				}
				
				if(broadTime <= 0 || !m_StartRead)       //如果按了停止则中断发驻留
				{
					break;
				}
				
				BYTE StatusH,StatusL;
				
				//广播地址
				AddrH = 0;                                  //高位    对应的为数据1
				AddrM = 0;                                  //中间位  对应的为数据2
				AddrL = (broadTime>>10)&0x0f;               //低4位   其是时间的高4位
				// A 01 B 02  C 03
				
				StatusH = (broadTime>>8); 
				StatusH = StatusH & 0x03;                   //高2位   其是时间的高2位
				StatusL = broadTime%256;                    //低8位   其是时间的低8位
				
				switch(i)
				{ 
				case  0://A相
					{
						PhaseBit    = 0x01;
						break;
					}
				case  1://B相
					{
						PhaseBit    = 0x02; 
						break;
					}
				case 2://C相
					{  
						PhaseBit    = 0x03;
						break;
					}
				}
				
				//从ORDER[0]到ORDER[4]单片机用
				//命令字
				ORDER[0]  = 0x51; //前导码
				ORDER[1]  = 0x52; //前导码
				ORDER[2]  = 0x53; //触发命令
				ORDER[3]  = j*64  + 0 + PhaseBit;//合成字节 前2位为(j 0，1二根母线)母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
				ORDER[4]  =    3; // 延时过0点数   
						
				if(m_ProtColArray[kk] == 22)
				{
					//如果协议为22	
					//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用  
					//格式：10位监督码+7(7个1)+ 7(7位驻留时间)+ 7(7个0)
					//地址前8位
					ORDER[5]  = 254   + (broadTime>>6); //时间高1位	
					//时间后6位 + 2位0
					ORDER[6]  = (broadTime%64)*4 + 0;
					ORDER[7]  =                    0;
					ORDER[8]  =                    0;
					ORDER[9]  =                    0;
				}
				else
				{
					
					if(m_ProtColArray[kk] == 61 || m_ProtColArray[kk] == 62)
					{
						//61,62协议
						//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用  
						//格式：18位监督码+ 地址高8位全1 +  地址低6位(6位驻留时间) + 6(6个0) + 0001000
						//地址前8位
						ORDER[5]  =                 0xff; //地址高8位全1	
						ORDER[6]  =       (broadTime<<2); //地址低6位(6位驻留时间) + 2个0
						ORDER[7]  =                    1; //4个0  +  0001
						ORDER[8]  =                    0; //000   +  5个0
						ORDER[9]  =                    0;
					}
					else
					{
						//31,32,33,71,72,72协议
						//传给模块用
						ORDER[5]  = 0xf2; //命令字，要什么东西
						ORDER[6]  = 0;    //模块高地址
						ORDER[7]  = 0;    //模块中地址
						ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4现为驻留时间,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
						ORDER[9]  = StatusL;//驻留时间
					}
					
				}			

				ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和
				
				//暂时无用
				ORDER[11] = 0;
				ORDER[12] = 0;
				ORDER[13] = 0;
			
				//演示版本
				if(!AppInfo::Instance().m_YanShi)
				{
					//62协议
					//向单片机发命令
					if(!PcSendToSCM(ORDER,m_ProtColArray[kk]/*读表协议*/,0))
					{
						Beep(300,400);
					}

				}
				
				if(times == 1)
				{	
					str.Format("发驻留%4d-%02d-%02d %02d:%02d:%02d,母线%d协议%d,",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond(),j + 1,m_ProtColArray[kk]); 
				}
				else
				{
					str.Format("驻留%4d-%02d-%02d %02d:%02d:%02d,第%d次母线%d协议%d",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond(),times,j + 1,m_ProtColArray[kk]); 
				}
				
				switch(i)
				{
				case 0:
					{	
						//显示状态栏信息
						StatusStr = "【" + str + "A相成功】";
						break;
					}
				case 1:
					{
						//显示状态栏信息
						StatusStr = "【" + str + "B相成功】";
						break;
					}
				case 2:
					{
						//显示状态栏信息
						StatusStr = "【" + str + "C相成功】";
						break;
					}
					
				}	
				
				SendMessage(WM_EVENT, 1, 0);
				
				//发送的字符BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
				//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
				//SendMessage(WM_EVENT, 5, 0);
				
				SurrenderWindowMessage();

				//存驻留时间入表
				m_AutoReadTime = m_iBroadTime;
				SendMessage(WM_EVENT, 11, 0);
				  
				//等待时间
				BYTE  m_SendTimers  =    0;

				if(m_ProtColArray[kk] == 22)
				{
					//22协议等待时间
					m_SendTimers =  8;
				}
				else
				{
					m_SendTimers = (m_ProtColArray[kk]%10)*9;
				}
				
                for(BYTE jj = 0 ; jj < m_SendTimers; jj ++)
				{
					SurrenderWindowMessage();
					
					if(m_StartRead)
					{
						Sleep(1000);
					}
					else
					{
						break;
					}
					
				}				
				
				SurrenderWindowMessage();
				Sleep(1000);

				//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
				//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS","");
				//SendMessage(WM_EVENT, 5, 0);	
							
           }

		 
       }

	  
	}	
	
	if(times == 1)
	{
		StatusStr.Format("【发驻留时间%4d-%02d-%02d %02d:%02d:%02d命令完毕】",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
	}
	else
	{
		StatusStr.Format("【第%d次发驻留时间%4d-%02d-%02d %02d:%02d:%02d命令完毕】",times,m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
	}

	SendMessage(WM_EVENT, 1, 0);
	m_times                 ++;

	StatusStr = StatusStrRead;
	
	//如果在自动驻留状态
	if(m_IsAutoSending)
	{
		m_others       =    FALSE;
	}

   TmpOnlyOneThreadRun.SetEvent();

}

void CIFRMView::OnPaint() 
{
	CPaintDC dc(this); 

    CBrush brush(m_BackRgbValue);//RGB(128,128,128));
    CRect                   rect;
    GetClientRect(rect);
    dc.FillRect(&rect,&brush);
	
    
	
  	/*
    CDC dcImage;
    if (!dcImage.CreateCompatibleDC(&dc))
		return;
	
	CRect m_Rect;
	GetClientRect(&m_Rect);
	
	CBitmap m_bitmap;
	
    if (!m_bitmap.LoadBitmap(IDB_GRIDBACK))
	  return;
  
    BITMAP bm;
    m_bitmap.GetBitmap( &bm );
    CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
    dc.StretchBlt(0,0,m_Rect.Width(),m_Rect.Height(),&dcImage,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);	
    dcImage.SelectObject(pOldBitmap);
    */
		
	// Do not call CFormView::OnPaint() for painting messages
}

//title           对话框标题
//IfWriteData     是否写入数据库 FALSE---不  写   TRUE---写
//WhichTable      哪个表            0----数据表   1----驻留表
//constr          条件              ALL--所  有
//recycles        循环次数
//Settimes        每二次时间间隔
//m_ReadKinds     0---手工读   1----定时读表 
void CIFRMView::FiveDataChuLi(CString title,BOOL  SELECT[],BOOL IfWriteData, int WhichTable, CString constr,int recycles,int Settimes,BYTE m_ReadKinds)
{
    int     READTIMES        =        0;//读表次数
	BYTE    MotherLine       =        0;//母线编号
	BYTE    LineNo           =        0;//线  号
	BYTE    BakMotherLine    =        0;//备用母线编号
	BYTE    BakLineNo        =        0;//备用线号
	BYTE    PhaseNo          =        0;//相  别
    long    ModuleNo         =        0;//模块号
	BYTE    StationNo        =        0;//手拉手变电站编码
	BYTE    tempvalue,value  =        0;//指令代码
    BYTE    m_AMMETERKIND    =        0;//表计种类
	BYTE    m_SUPPLYMODED    =        0;//供电方式 0-单边供电 1－站手拉手 2－线手拉手供电
	BYTE    m_PROTOCOL       =        0;//读表协议
	BYTE    m_SendAngle      =        0;//发送的角度 
	float   m_BeginValue     =        0;//电表初值 
	double  CurrentValue     =        0;//开始读模块数据
	long                         fields;//记录个数
	short                       nFields;//字段个数
	long    m_OldModule       =    - 10;
	double  m_OldCurrentValue =   -10.0;
	BOOL    m_UseOldValue     =   FALSE;
	BYTE    m_OldReadHour     =      24;
	BYTE    m_OldReadMinute   =      60;
	BOOL    m_StillRunning    =   FALSE;
	short   m_CheckTimes      =       0;
	long    m_PhaseModule     =       0;
	BYTE    m_PhaseBak        =       3;
	CTime        m_CheckreadModuleTimes;//读表时间
	CString 	 m_ReadAmmeterType,m_ReadMeterLabel;//读表类型
	CString      strValue,m_FieldNames,m_ReadTime;
	CString       strSql,HisStrSql,DataStr  = "";
	CDatabase                         db;
    CTimeSpan                       ttts;

	constr.TrimLeft();
	constr.TrimRight();
	int i;
	for( i = 0; i < 31; i ++)
	{
		m_All_Line_Current[i] = 2;//没有检测状态
	}

	//存61、62协议485表快速读表的功率因素 
	for(i = 0; i < 20000; i ++)
	{
       m_QuickGlys[i] =  -1;
	}	
	
	m_QuickModuleAddress =         0;//快速读表的地址
	m_QuickReadModuleValue =      -1;//快速读表的值

	//销户的用户不读
	constr = "(" + constr + ") AND USER_RUNSTATUS<=2";

	//删除原来的数
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);                      //13列

	m_StartRead              =              TRUE;//读停标志
	m_ZhuLiuTime             =   GetZhuLiuTime();//驻留时间    
	
	//显示状态栏信息
	StatusStr = "正在" + title + "，请稍侯...";
	SendMessage(WM_EVENT, 1, 0);

	//如果DIALOGBAR可见的话则隐藏
	SendMessage(WM_EVENT, 6, 0);
	memset(m_QuickGlys,0,100000);
  
	//不是定时读表
	if(WhichTable < 2)
	{   
		//行号从0开始
		m_ListRows              =    1;
	}
	
    if(m_ReadKinds == 0)
	{

		if(WhichTable == 1)//      哪个表            0----数据表   1----驻留表
		{
		   m_QuickReading   =         FALSE;//注意:驻留读表慎用快速读表
		}
			
		m_ReadMeterLabel = "USER_READLABEL";//普通读表
		m_others         =            FALSE;//FALSE 其它读表  TRUE  驻留读表
		READTIMES        =                5;//5次
	}
	else
	{
		m_QuickReading   =            FALSE;//注意:驻留读表慎用快速读表
		m_ReadMeterLabel = "USER_TIMELABEL";//定时自动读表
		m_others         =             TRUE;//FALSE 其它读表  TRUE  驻留读表
		READTIMES        =                1;//1次

		//驻留读表最后一次，则读5次
		if(m_IsAutoSending)
		{	

            
			if(m_zhuliukinds == 0)
			{

				//按表计种类读数
				if(m_ReadModuleTimes == m_parameter[106])
				{
					//最后一次读表5次
					READTIMES  =   5;
					
				}
				
			}
			else
			{
				
				if(m_ReadModuleTimes == m_DateReadParameter[63])
				{
					
					//最后一次读表5次
					READTIMES  =   5;
					
				}
				
			}

		}

	}
	
	//处理特殊的东东开始,如果是脉冲表的话处理,15种类型的数据 0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14－功率因数
	for(int hhh = 1; hhh < 15; hhh ++)
	{
		
		if(hhh == 7 || hhh == 8 || hhh == 9)
        {
			//脉冲表只有读自身电压
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s%d",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_MODULENO%100<=12 AND USER_PHASE<>",hhh - 7);
		}
		else
		{
			//脉冲表只有有功电度
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_MODULENO%100<=12");
		}

		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		//61，62协议没有BC相电流电压可读A相时，三相同时就上数
		if(hhh == 5 || hhh == 6 || hhh == 8 || hhh == 9)
		{
			//手拉手处理，居民表、线路表或站总表没有手拉手
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_PROTOCOL=61 OR USER_PROTOCOL=62");
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		}
		
		if(hhh == 1 || hhh == 3)
		{
			//手拉手处理，居民表、线路表或站总表没有手拉手
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"(USER_MODULENO%100>12 AND USER_SUPPLYMODE=0) OR (USER_AMMETERKIND>3)");
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		}
	
	}
	
	//销户的不能读数
	strSql = "UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY',USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_RUNSTATUS>2";	
	CDataBaseInstance::ExecuteDataBaseSQL(strSql);

	//61,62协议无自己电压读	
	strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,2,14,'YYYYYYYYYYYYYY') WHERE %s AND (USER_PROTOCOL=61 OR USER_PROTOCOL=62)",m_ReadMeterLabel,m_ReadMeterLabel,"USER_MODULENO%100<=12");
    CDataBaseInstance::ExecuteDataBaseSQL(strSql);
	//处理特殊的东东结束

	//数据库表
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
		
		if(WhichTable < 2 || (WhichTable >= 2 && m_times <= 1))
		{
			//写列表标题
			SendMessage(WM_EVENT, 2, 0);
		}
		
		//读多少轮
        for(int www = 0; www < recycles; www++)
		{
			
			//监视读表
			if(m_CheckReading)
			{
				m_CheckreadModuleTimes = CTime::GetCurrentTime();//动态监控读表时间
			}			

			SurrenderWindowMessage();
			
			//如果按了停止按钮
			if(!m_StartRead)
			{	
				break;
			}		

			ShowProgressCtrl(TRUE);//显示滚动条
	
    	    //开始扫一轮,15种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数
			for(int a = 0 ; a < 15 ; a ++)
			{
				
				SurrenderWindowMessage();

				//如果按了停止按钮
				if(!m_StartRead)
				{	
					break;
				}

				//动态监控读表时间
				if(m_CheckReading)
				{

					ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

					//1分钟前停止
					if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
					{
						break;
					}

				}			


				//如果选择了此项      
				if(SELECT[a] == TRUE)
				{
				
					//每个读五次
					for(int m_ReadTimes = 0;m_ReadTimes < READTIMES;m_ReadTimes ++)
					{
						
						SurrenderWindowMessage();

						//如果按了停止按钮
						if(!m_StartRead)
						{	
							break;
						}

					    //动态监控读表时间
						if(m_CheckReading)
						{

							ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

							//1分钟前停止
							if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
							{
								break;
							}

						}
						
						//找出原来有标记的地方
						strSql.Format("(%s) AND SUBSTRING(%s,%d,1)='N'",constr,m_ReadMeterLabel,a + 1);
					
						if(rs.IsOpen())
						{
							rs.Close();
						}
						
						//查满足条件的个数
						strValue.Format("SELECT COUNT(*) FROM TB_USER WHERE %s",strSql);
						rs.Open(CRecordset::forwardOnly,strValue);
						rs.GetFieldValue(short(0),strValue);
						rs.Close();
						
						fields = atoi(strValue);
					
						if(fields <= 0)	
						{
							m_ReadTimes = READTIMES;//没有满足条件的记录的话，返回
							continue;
						}

						strSql.Format("SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE (%s) AND SUBSTRING(%s,%d,1)='N' ORDER BY USER_AMMETERKIND DESC,USER_MODULENO ASC",constr,m_ReadMeterLabel,a + 1);
				
						rs.Open(CRecordset::forwardOnly,strSql);
						nFields = rs.GetODBCFieldCount();//得到字段个数
						rs.Close();
						
						SetProgressCtrlRange(0, fields,1);
						
						//打开数据库数据
						rs.Open(CRecordset::forwardOnly,strSql);
						
						//读用户信息
						for(int j = 0;j < fields; j ++)
						{
							
							SurrenderWindowMessage();

							//如果按了停止按钮
							if(!m_StartRead)
							{	
								break;
							}
							
							//动态监控读表时间
							if(m_CheckReading)
							{

								ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

								//1分钟前停止
								if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
								{
									break;
								}

							}			

							//序号
							m_StrArray[0].Format("%6d",m_ListRows);
							m_StrArray[1]   = title;
																			
							///////////////////////////////////得到字段信息/////////////////////////
							for(int i = 0; i < nFields; i ++)
							{
								rs.GetFieldValue(int(i),strValue);
								strValue.TrimRight();

								switch(i)
								{
								case 0:
									{
										//姓   名
										m_StrArray[2] = strValue;
										break;
									}
								case 1:
									{ 
										//用户编号  
										m_StrArray[3] = strValue;
										break;
									}
    						   case 2:
									{ 
										//住   址  
										m_StrArray[4] = strValue;
										break;
									}
								case 3:
									{  
										//模块号
										m_StrArray[5].Format("%8s",strValue);
										ModuleNo = atol(strValue);
										break;
									}
								case 4:
									{  
										//电表号
										m_StrArray[6].Format("%8s",strValue);
										break;
									}
								case 5:
									{  
										//母线编号
										MotherLine = atoi(strValue); 
										
										if(MotherLine > 2)
										{
											MotherLine = 2;
										}
										
										if(MotherLine < 1)
										{
											MotherLine = 1;
										}

										break;
									}
								case 6:
									{	
										//线路名称
										m_StrArray[7] = strValue;
     									break;
									}
								case 7:
									{
										//线路编号
										strValue.TrimLeft();
										strValue.TrimRight();
										LineNo = atoi(strValue);

										if(LineNo > 15)
										{
											LineNo = 15;
										}
										
										if(LineNo < 1)
										{
											LineNo = 1;
										}

										break;
									}
								case 8:
									{
										//相
                                        PhaseNo       = atoi(strValue);	
																			
										if(PhaseNo >= 3)
										{											
										//	strValue.Format("读数据表中模块号:%d,相别:%d,m_PhaseBak=%d\r\n",ModuleNo,PhaseNo,m_PhaseBak);
										//	WriteToLog(strValue);

											//原来是否上来过相
											if((m_PhaseModule/100) == (ModuleNo/100))
											{
												PhaseNo = m_PhaseBak;
											}
											else
											{
												PhaseNo = 3;
											}

										}

										break;
									}
							   case 9:
									{
										//变台名称
										m_StrArray[9] = strValue;
						     			break;
									}
								case 10:
									{
										//手拉手电站码,电表初值
										StationNo    = m_handno;
										m_BeginValue = float(atof(strValue));
										break;
									}
								case 11:
									{
										//表计种类
										m_AMMETERKIND = atoi(strValue);
										break;
									}
								case 12:
									{
										//供电方式
										m_SUPPLYMODED = atoi(strValue);
										break;
									}
								case 13:
									{
										//读表协议71-73 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
										m_PROTOCOL = atoi(strValue);
										
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A相",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B相",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C相",m_PROTOCOL);
												break;
											}
										default:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"未知",m_PROTOCOL);
												break;
											}
										}

										//61,62协议读A相电流电压时同时上ABC三相数据
										if((a==4 || a==7)  && (m_PROTOCOL==61 || m_PROTOCOL==62)  && PhaseNo<3)
										{	
											m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"3相",m_PROTOCOL);
										}

										break;
									}
								case 14:
									{
										//读表的角度,是否是星角连接,偏移角度,星角为30度
										if(IsDyConnect(m_StrArray[9]))
										{
											m_SendAngle   =                        6;//5度一个档次
											m_StrArray[9] = m_StrArray[9] + "(星角)";
										}
										else
										{
											m_SendAngle = 0;
										}

										break;
									}
								case 15:
									{
										//电表种类
										strValue.TrimLeft();
                                        strValue.TrimRight();
										m_ReadAmmeterType = strValue;

										//如果是其它的话
										if(a > 2)
										{
                                           m_ReadAmmeterType  = "";
										}

										break;
									}
								case 16:
									{
										//备用母线编号
										BakMotherLine = atoi(strValue);

										if(m_SUPPLYMODED == 2)
										{
											
											if(BakMotherLine > 2)
											{
												BakMotherLine = 2;
											}	
											
											if(BakMotherLine < 1)
											{
												BakMotherLine = 1;

											}

										}

										break;
									}	
								case 17:
									{
										//备用出线号
										BakLineNo     = atoi(strValue);
                                        
										if(m_SUPPLYMODED == 2)
										{
											
											if(BakLineNo > 15)
											{
												BakLineNo = 15;
											}
											
											if(BakLineNo < 1)
											{
												BakLineNo = 1;
											}
											
										}

										break;
									}
									
								}
								
							 }
							 
							 ///////////////////////////////////得到字段完毕/////////////////////////
							 
							 
							 ///////////////////////////////////选择开始//////////////////////////////
							 switch(a)
							 {
							 case 0:
								 {
									 //WhichTable  哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {  
										 //如果是站手拉手供电的话
										 if(m_SUPPLYMODED == 1)
										 {
										
											 //如果为22协议
											 if(m_PROTOCOL == 22)
											 {
												 
												 //测试正式读表，手拉手方式,读有功电度-单边累加值
												 if(m_handno == 0)
												 {
													 value  = 0x57;
												 }
												 else
												 {  
													 value  = 0x5B;
												 }
												 
											 }
											 else
											 {

												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
												     //测试正式读表，手拉手方式,读有功电度-单边累加值
													 if(m_handno == 0)
													 {
														 value  = 0x17;
													 }
													 else
													 {  
														 value  = 0x1B;
													 }
													 
												 }
												 else
												 {													 
													 //测试正式读表，手拉手方式,读有功电度-单边累加值
													 if(m_handno == 0)
													 {
														 value  = 0x50;
													 }
													 else
													 {  
														 value  = 0x54;
													 }

												 }

											 }
											
											 m_StrArray[10].Format("%d站有功",m_handno);
										 
										 }
										 else
										 {
											
											 //单方供电,读有功电度-表总值,如果为22协议
											 if(m_PROTOCOL == 22)
											 { 
												 
												 if(ModuleNo%100 < 12)
												 {
													 value = 0x07;
												 }
												 else
												 {
													 value = 0x5F;
												 }
												 
											 }
											 else
											 {
												 
												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(ModuleNo%100 < 12)
													 {
														 value = 0x03;
													 }
													 else
													 {
														 value = 0x1F;
													 }
													 
												 }
												 else
												 {
												    value = 0x02;

												 }

											 }
											 
											 m_StrArray[10] = "有功电度";

										 }
										 m_FieldNames       = "REALTIME_WORKDEGREE";
										 
									 }
									 else
									 {
										 //驻留读表,手拉手方式
										 if(m_SUPPLYMODED == 1)
										 {
											 
											 //手拉手方式，如果为22协议
											 if(m_PROTOCOL == 22)
											 {
												 
												 //读冻结有功电度-单边累加值
												 if(m_handno == 0)
												 {
													 value  = 0x56;
												 } 
												 else
												 {   
													 value  = 0x5A;
												 }
												 
											 }
											 else
											 {

												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 { 
													 //读冻结有功电度-单边累加值
													 if(m_handno == 0)
													 {
														 value  = 0x16;
													 } 
													 else
													 {   
														 value  = 0x1A;
													 }
													 
												 }
												 else
												 {
													 //读冻结有功电度-单边累加值
													 if(m_handno == 0)
													 {
														 value  = 0xD0;
													 }
													 else
													 {   
														 value  = 0xD4;
													 }
												 }


											 }

											 m_StrArray[10].Format("%d站有功",m_handno);
										 }
										 else
										 {

											 //单方供电,读冻结有功电度-表总值，如果为22协议
											 if(m_PROTOCOL == 22)
											 {
												 
												 if(ModuleNo%100 < 12)
												 {
													 value = 0x06;
												 }
												 else
												 {
													 value = 0x5E;
												 }

											 }
											 else
											 {
												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(ModuleNo%100 < 12)
													 {
														 value = 0x02;
													 }
													 else
													 {
														 value = 0x1E;
													 }

												 }
												 else
												 {
													 value     = 0x82;
												 }

											 }

											 m_StrArray[10]  = "有功电度";
										 }

										 m_FieldNames        = "GARRISON_WORKDEGREE";
									 }

									 break;
								 }	 
							 case 1:
								 {
									 //1和3为手拉手供电专用,WhichTable  哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读表,读有功电度-表总值
										 if(m_PROTOCOL == 22)
										 {
											 value        = 0x5F;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value        = 0x1F;
											 }
											 else
											 {
												 value        = 0x02;
											 }

										 }

										 m_FieldNames = "REALTIME_WORKDEGREETOTAL";
									 }
									 else
									 {
										 //驻留读表,读冻结有功电度-表总值
										 if(m_PROTOCOL == 22)
										 {
											 value        = 0x5E;
										 }
										 else
										 { 
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value        = 0x1E;
											 }
											 else
											 {
												 value        = 0x82;
											 }

										 }

										 m_FieldNames = "GARRISON_WORKDEGREETOTAL";
									 }

									 m_StrArray[10]   = "总有功";
									 break;
								 }
							 case 2:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {  
										 //手拉手方式
										 if(m_SUPPLYMODED == 1)
										 {
											 
											 //如果为22协议
											 if(m_PROTOCOL == 22)
											 {
												 
												 //手拉手方式
												 if(m_handno == 0)
												 {
													 //读无功电度-单边累加值
													 value = 0x55;
												 }
												 else
												 {  
													 //读无功电度-单边累加值
													 value = 0x59;
												 }
												 
											 }
											 else
											 {
												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 { 
													 //手拉手方式
													 if(m_handno == 0)
													 {
														 //读无功电度-单边累加值
														 value = 0x15;
													 }
													 else
													 {  
														 //读无功电度-单边累加值
														 value = 0x19;
													 }
													 
												 }
												 else
												 {
													 //手拉手方式
													 if(m_handno == 0)
													 {
														 //读无功电度-单边累加值
														 value = 0x52;
													 }
													 else
													 {  
														 //读无功电度-单边累加值
														 value = 0x56;
													 }

												 }

											 }

											 m_StrArray[10].Format("%d站无功",m_handno);
											 
										 }
										 else
										 {   
											 //单方供电,读无功电度-表总值
											 if(m_PROTOCOL == 22)
											 {
												 value = 0x5D;            
											 }
											 else
											 { 
												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 value = 0x1D;  
												 }
												 else
												 {
													 value = 0x06; 
												 }

											 }

											 m_StrArray[10] = "无功电度";
										 }

										 m_FieldNames       = "REALTIME_LOSEDEGREE";//读无功电度

									 }
									 else
									 {
										 //驻留读表,手拉手方式
										 if(m_SUPPLYMODED == 1)
										 {
                                             
											 //如果为22协议
											 if(m_PROTOCOL == 22)
											 {

												 if(m_handno == 0)
												 {
													 //读冻结无功电度-0站单边累加值
													 value  = 0x54;
												 }
												 else
												 {
													 //读冻结无功电度-1站单边累加值
													 value  = 0x58;
												 }
												 
											 }
											 else
											 {
												  //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(m_handno == 0)
													 {
														 //读冻结无功电度-0站单边累加值
														 value  = 0x14;
													 }
													 else
													 {
														 //读冻结无功电度-1站单边累加值
														 value  = 0x18;
													 }

												 }
												 else
												 {
													 if(m_handno == 0)
													 {
														 //读冻结无功电度-单边累加值
														 value   = 0xD2;
													 }
													 else
													 {
														 //读冻结无功电度-单边累加值
														 value   = 0xD6;
													 }
												 }

											 }

											 m_StrArray[10].Format("%d站无功",m_handno);
											 
										 }
										 else
										 {
											 //单方供电,读冻结无功电度-表总值
											 if(m_PROTOCOL == 22)
											 {
												 value = 0x5C;
											 }
											 else
											 {
												 //61、62协议
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 value = 0x1C;
												 }
												 else
												 {
													 value = 0x86;
												 }

											 }

											 m_StrArray[10]    = "无功电度";
										 }

										 m_FieldNames = "GARRISON_LOSEDEGREE";
										 
									 }

									 break;
								 }	 
							 case 3:
								 {
									 //1和3 为手拉手供电读总表时专用,WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {  
										 //测试读无功电度-表总值,如果为22协议
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x5D;
										 }
										 else
										 { 
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x1D;
											 }
											 else
											 {
												 value  = 0x06;
											 }

										 }

										 m_FieldNames = "REALTIME_LOSEDEGREETOTAL";//读无功电度
									 }
									 else
									 {
										 //驻留读表,读冻结无功电度-表总值
                                         if(m_PROTOCOL == 22)
										 {
											 value   = 0x5C;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value   = 0x1C;
											 }
											 else
											 {
												 value   = 0x86;
											 }
											 
										 }

										 m_FieldNames = "GARRISON_LOSEDEGREETOTAL";
									 
									 }
									 
									 m_StrArray[10]   = "总无功";

									 break;
								 }
							 case 4:
								 {   
									 //WhichTable  哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读表,A相电流
										 if(m_PROTOCOL == 22)
										 {
											 value  =  0x69;
										 }
										 else
										 {
											 //61、62协议
											 if((m_PROTOCOL/10) == 6)
											 {
												 value  =  0x09;
											 }
											 else 
											 { 
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  =  0x1C;  
												 }

											 }
											 
										 }

										 m_FieldNames = "REALTIME_ACURRENT";
									 }
									 else
									 {
										 //驻留读表,A相电流,如果为22协议
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x68;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x08;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0xF0; 
												 }
												 else
												 {
													 value  = 0x9C;
												 }

											 }

										 }				   
										 
										 m_FieldNames = "GARRISON_ACURRENT";
									 }

									 //61、62协议
									 if((ModuleNo%100) >=12)
									 {

										 if(int(m_PROTOCOL/10) == 6) 
										 {

                                             m_StrArray[10]   = "三相电流";
										 
										 }
										 else
										 { 
											 //71，72，73协议快速读
											 if((m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
									              m_StrArray[10]   = "3电压A电流";
											 }
											 else
											 {
												 m_StrArray[10]    = "三相电流";
											 }

										 }
									 }
									 else
									 {
										 m_StrArray[10]   = " A相电流";
									 }

									 break;
								 } 
							 case 5:
								 {  
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读B相电流,如果为22协议
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x67;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x09;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0x62; 
												 }
												 else
												 {
												    value   =  0x1E;  
												 }
											 }

										 }

										 m_FieldNames = "REALTIME_BCURRENT";
										 
									 }
									 else
									 {
										 //驻留读B相电流
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x66;	 
										 }
										 else
										 {
											 //61、62协议
											 if((m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x08;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0xF2; 
												 }
												 else
												 {
												    value   =  0x9E;  
												 }

											 }

										 }
     									
										 m_FieldNames = "GARRISON_BCURRENT";
									 }

									  //61、62协议
									 if((ModuleNo%100) >=12)
									 {

										 if((m_PROTOCOL/10) == 6)
										 {
										      m_StrArray[10]   = "三相电流";
										 }
										 else
										 {
											 //71，72，73协议快速读
											 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
												 m_StrArray[10]   = "BC电流、功因、无功率";
												 
											 }
											 else
											 {
												 m_StrArray[10]   = "三相电流";
											 }

										 }

									 }
									 else
									 {
										 m_StrArray[10]   = " B相电流";
									 }

									 break;
								 }
							 case 6:
								 {   
									 //WhichTable哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读C相电流 
										 if(m_PROTOCOL == 22)
										 {
											  value   = 0x65;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x09;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0x62; 
												 }
												 else
												 {
												     value  = 0x20;  
												 }

											 }
										 
										 }

										 m_FieldNames = "REALTIME_CCURRENT";
									 }
									 else
									 {
										 //驻留读C相电流
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x64;
										 }
										 else
										 { 
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x08;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0xF2; 
												 }
												 else
												 {
												    value  =  0xA0;  
												 }

											 }

										 }

										 m_FieldNames = "GARRISON_CCURRENT";
									 }
                                     
									 //61、62协议
									 if((ModuleNo%100) >=12)
									 {
										 
										 if(int(m_PROTOCOL/10) == 6)
										 {											 
											 m_StrArray[10]   = "三相电流";
										 }
										 else
										 {
											 //71，72，73协议快速读
											 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
												 m_StrArray[10]   = "BC电流、功因、无功率";
											 }
											 else
											 {
												 m_StrArray[10]   = "三相电流";
											 }
										 
										 }

									 }
									 else
									 {
										 m_StrArray[10]   = " C相电流";
									 }

									 break;
								 }
							 case 7:
								 {   
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读A相电压
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x6F;
										 }
										 else
										 { 
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  = 0x16;
												 }
												 
											 }
											 
										 }

										 m_FieldNames = "REALTIME_AVOLTAGE";
										 
									 }
									 else
									 {
										 //驻留读A相电压
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x6E;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0A;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0xF0; 
												 }
												 else
												 {
												    value  = 0x96;
												 }

											 }

										 }

										 m_FieldNames = "GARRISON_AVOLTAGE";
									 }
									 
									 //模块号<＝12的，读自采电压
									 if(ModuleNo%100 <= 12)
									 {
										 
										 //模块自采电压,如果为22协议
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  =   0x01;
										 }
										 else
										 {
											 value  =   0x3A;
										 }

										 m_StrArray[10] = "电压";

									 }
									 else
									 {
									
										 //61、62协议
										 if((ModuleNo%100) >=12)
										 {
											
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "三相电压";
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC电压A电流";
												 }
												 else
												 {
													 m_StrArray[10] = "三相电压";
												 }

											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " A相电压";
										 }
									 
									 }

									 break;
								 }  
							 case 8:
								 {	
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读表B相电压 
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6D;
										 }
										 else
										 {	 
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value   =  0x18;
												 }
												 
											 }

										 }

										 m_FieldNames = "REALTIME_BVOLTAGE";
									 }
									 else
									 {
										 //驻留读B相电压
										 if(m_PROTOCOL == 22)
										 {
											  value   =  0x6C;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0A;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0xF0; 
												 }
												 else
												 {
												    value  = 0x98;
												 }

											 }

										 }
										 
										 m_FieldNames = "GARRISON_BVOLTAGE";
									 }
									 
									 //模块号<＝12的，读自采电压
									 if(ModuleNo%100 <= 12)
									 {
										 //模块自采电压
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  = 0x01;
										 }
										 else
										 {
											 value  = 0x3A;
										 }

										 m_StrArray[10] = "电压";
									 }
									 else
									 { 
										 //61、62协议
										 if((ModuleNo%100) >=12)
										 {
											 
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "三相电压";
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC电压A电流";
												 }
												 else
												 {
													 m_StrArray[10] = "三相电压";
												 }
												 
											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " B相电压";
										 }

									 }

									 break;
								 }
							 case 9:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读C相电压
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6B;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  = 0x1A;
												 }
												 
											 }

										 }

										 m_FieldNames = "REALTIME_CVOLTAGE";
									 }
									 else
									 {
										 //驻留读C相电压 
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6A;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value   =  0x0A;
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,ABC相三相电压+A相电流
                                                     value  =  0xF0; 
												 }
												 else
												 {
													 value   =  0x9A;
												 }
											 }
										
										 }

										 m_FieldNames = "GARRISON_CVOLTAGE";
									 }
                         
									 //模块号<＝12的，读自采电压
									 if(ModuleNo%100 <= 12)
									 {
										//模块自采电压
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  = 0x01;
										 }
										 else
										 {
											 value  = 0x3A;
										 }

										 m_StrArray[10] = "电压";

									 }
									 else
									 {
										 //61、62协议
										 if((ModuleNo%100) >=12)
										 {
											 
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "三相电压";
											 }
											 else
											 {
												 //71，72，73协议快速读
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC电压A电流";
												 }
												 else
												 {
													 m_StrArray[10]   = "三相电压";
												 }
												 
											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " C相电压";
										 }
										 
									 }

									 break;
								 }
							 case 10:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读尖峰电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x53;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x13;
											 }
											 else
											 {
												 value  = 0x58;
											 }

										 }

										 m_FieldNames = "REALTIME_JFDL";
									 }
									 else
									 {
										 //驻留读尖峰电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x52;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x12;
											 }
											 else
											 {
												 value  = 0xD8;
											 }

										 }

										 m_FieldNames = "GARRISON_JFDL";
										 
									 }
                         			
									 m_StrArray[10]   = "尖峰电量";

									 break;
								 }	 
							 case 11:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读峰电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x51;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x11;
											 }
											 else
											 {
												 value  = 0x5A;
											 }

										 }

										 m_FieldNames = "REALTIME_FDL";
									 }
									 else
									 {
										 //驻留读表峰电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x50;
										 }
										 else
										 { 
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x10;
											 }
											 else
											 {
												 value  = 0xDA;
											 }

										 }
										 m_FieldNames = "GARRISON_FDL";
									 }
                         			
									 m_StrArray[10] = "峰电量";
									 break;
								 }	 
							 case 12:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   

										 //测试正式读平电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4F;
										 }
										 else
										 { 
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x0f;
											 }
											 else
											 {
												 value  = 0x5C;
											 }
											 
										 }

										 m_FieldNames = "REALTIME_PDL";
									 }
									 else
									 {
										 //驻留读平电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4E;
										 }
										 else
										 {	
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x0e;
											 }
											 else
											 {
												 value  = 0xDC;
											 }

										 }

										 m_FieldNames = "GARRISON_PDL";
									 }
                         			
									 m_StrArray[10]   = "平电量";
									 break;
								 }	
							 case 13:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读谷电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4D;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 { 
												 value  = 0x0D;
												 
											 }
											 else
											 {
												 value  = 0x5E;
											 }

										 }
										 
										 m_FieldNames = "REALTIME_GDL";
									 }
									 else
									 {
										 //驻留读谷电量
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4C;
										 }
										 else
										 {
											 //61、62协议
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 { 
												 value  = 0x0C;
											 }
											 else
											 {
												 value  = 0xDE;
											 }
										 }

										 m_FieldNames = "GARRISON_GDL";
									 }
                         			
									 m_StrArray[10]   = "谷电量";
									 break;
								 }	
							 case 14:
								 {
									 //WhichTable 哪个表 0----数据表 1----驻留表
									 if(WhichTable != 1)
									 {   
										 //测试正式读功率因数
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x63;
										 }
										 else
										 {
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x07;
											 }
											 else
											 { 
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0x62; 
												 }
												 else
												 {
												     value  = 0x38;
												 }

											 }

										 }

										 m_FieldNames = "REALTIME_GLYS";
									 
									 }
									 else
									 {

										 //驻留读功率因数
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x62;
										 }
										 else
										 { 
											 //61、62协议
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x06;
											 }
											 else
											 {	 
												 //71，72，73协议快速读
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //一个包含有4个数,BC相电流+功率因素+无功功率
                                                     value  =  0xF2; 
												 }
												 else
												 {
													 value  = 0xB8;
												 }

											 }
											 
										 }

										 m_FieldNames = "GARRISON_GLYS";
									 }

									 //71，72，73协议快速读
									 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
									 {
										 m_StrArray[10]   = "BC电流、功因、无功率";
									 }
									 else
									 {
                               			 m_StrArray[10]   = "功率因数";
									 }

									 break;
								 }
								 
							}
							
							/////////////////////////////选择结束////////////////////////
					
							//显示状态栏信息,发送显示状态栏提示	
							StatusStr.Format("%s[%d-%d-%d][%s%d-%d][%d],完成%.2f％,请稍侯...",title,www + 1,recycles,Settimes,m_StrArray[10],fields,j + 1,ModuleNo,float(j)*100/fields);
							SendMessage(WM_EVENT,1,0);

    						///////////////////////////////////开始读表/////////////////////////
							//赋初始值
							CurrentValue = -1;
	                        
							//如果是线表或站总表则是直接读表,否则下发命令读
							if(m_AMMETERKIND <= 5)
							{	

								//定时驻留读表,按小时测电流
								if(m_ReadKinds > 0)
								{
								
									CTime  EveryHourtimet= CTime::GetCurrentTime();
									
									//按小时检查电流大小，读表中调用
									if(m_OldReadHour != EveryHourtimet.GetHour() && EveryHourtimet.GetMinute() < 10)
									{
										EveryHourCheckLine();
										m_OldReadHour = EveryHourtimet.GetHour();
										StatusStr.Format("%s[%d-%d-%d][%s%d-%d][%d],完成%.2f％,请稍侯...",title,www + 1,recycles,Settimes,m_StrArray[10],fields,j + 1,ModuleNo,float(j)*100/fields);
										SendMessage(WM_EVENT,1,0);
									}
									
									BOOL  m_ChuWG = FALSE;

									switch(m_WgLess)
									{
										
									case 0:
										{
											//10分钟,无功补偿表操作
											if(EveryHourtimet.GetMinute()/10 != m_OldReadMinute)
											{
                                               m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/10;
											}

											break;
										}
									case 1:
										{
											//20分钟
											if(((EveryHourtimet.GetMinute()/10)%2) == 0  && (EveryHourtimet.GetMinute()/20)!= m_OldReadMinute)
											{
											   m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/20;
											}
											
											break;
										}
									case 2:
										{
											//30分钟
											if(((EveryHourtimet.GetMinute()/10)%3) == 0  && (EveryHourtimet.GetMinute()/30)!= m_OldReadMinute)
											{
											   m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/30;
											}

											break;
										}

									}
								
											
									if(m_ChuWG)
									{
										strValue =  StatusStr;
										
										//所有的无功表处理一次
										ALLWuGongDeal();

										StatusStr = strValue;
										SendMessage(WM_EVENT,1,0);
									}
								
								}

								//如果是相别没有定下来
								if(PhaseNo > 2)
								{
									
									//三相都要测试一下
									for(int m_TestReadtimes = 0; m_TestReadtimes < 3; m_TestReadtimes ++)
									{
										
										if(m_StartRead)
										{
							
											//如果没有检测
											if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
											{
												
												//如果有电流
												if(CheckIfHaveCurrentValue(MotherLine,LineNo))
												{
													
													m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
													
												}
												
											}										
										
											
											//如果有电流
											if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
											{	

												if(m_SendAngle == 0)
												{
													//下发命令读数
													CurrentValue =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//星角变读表,下发命令读数
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo, m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}

											}
											else
											{
                                                CurrentValue =  -6;//没有电流
											}
																				
										}
                                        
										//一天不超过300度
										SurrenderWindowMessage();
											
										//如果是线手拉手，再读一次数据
										if((int(CurrentValue) == -1 || int(CurrentValue) == -6) && m_SUPPLYMODED == 2 && m_StartRead)
										{
										
											
											//如果没有检测
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] > 1)
											{
												
												//如果有电流
												if(CheckIfHaveCurrentValue(BakMotherLine,BakLineNo))
												{
													
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  0;
													
												}
												
											}									
											
											//备用线上如果有电流
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] == 1 )
											{
												
												if(m_SendAngle == 0)
												{
													//下发命令读数
												     CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//星角变读表,下发命令读数
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												
												//如果在备用母线和备用出线上读出来
												if(int(CurrentValue) != -1)
												{
													
													MotherLine =   BakMotherLine;
													LineNo     =       BakLineNo;
													PhaseNo    = m_TestReadtimes;
													
												}
											
											}
									

										}
										
										SurrenderWindowMessage();

										//如果按了停止按钮
										if(!m_StartRead)
										{	
											break;
										}

									    //动态监控读表时间
										if(m_CheckReading)
										{

											ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

											//1分钟前停止
											if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
											{
												break;
											}

										}			

										SurrenderWindowMessage();

										//如果找出了相位
										if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
										{	
										
											//相
											switch(m_TestReadtimes)
											{
											case 0:
												{
												    m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A相",m_PROTOCOL);
													break;
												}
											case 1:
												{
													m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B相",m_PROTOCOL);
													break;
												}
											case 2:
												{
													m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C相",m_PROTOCOL);
													break;
												}
										
											}

											//修改相别值
											strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",m_TestReadtimes,ModuleNo - 16,ModuleNo + 16);//修改相别值
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
																					
                                            //记下相别值
											PhaseNo         = m_TestReadtimes;
											m_PhaseBak      = PhaseNo;
											m_PhaseModule   = ModuleNo;                							
											break;
										}

										SurrenderWindowMessage();

										//Sleep(300);

										//如果按了停止按钮
										if(!m_StartRead)
										{	
											break;
										}
							
									}

								}
								else
								{
									
									SurrenderWindowMessage();
									//Sleep(200);

									//相定的话,把原来的表计录下来
									if(m_OldModule > 0 && m_OldCurrentValue >= 0 && a >= 7 && a <= 9 && m_OldModule/100 == ModuleNo/100 && ModuleNo%100 <= 12)
									{	
										CurrentValue      =   m_OldCurrentValue;
										m_OldModule       =            ModuleNo;
										m_UseOldValue     =                TRUE;
									}
									else
									{	
										
										//如果没有检测
										if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
										{
											
											//如果有电流
											if(CheckIfHaveCurrentValue(MotherLine,LineNo))
											{
												
												m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
											}
											else
											{
												m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
												
											}
											
										}									
										
										//如果有电流
										if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
										{
											
											//下发命令读数
											if(m_SendAngle == 0)
											{
												//下发命令读数
												CurrentValue      =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
											}
											else
											{
												//星角变读表,下发命令读数
												CurrentValue      =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
											}

											m_UseOldValue     =  FALSE;

										}
										else
										{
											CurrentValue =  -6;//没有电流
										}
									    
										SurrenderWindowMessage();

										//如果是线手拉手，再读一次数据
										if((int(CurrentValue) == -1 || int(CurrentValue) == -6)  &&  m_SUPPLYMODED == 2 && m_StartRead)
										{
											
											//如果没有检测
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] > 1)
											{
												
												//如果有电流
												if(CheckIfHaveCurrentValue(BakMotherLine,BakLineNo))
												{
													
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  0;
													
												}
												
											}									
											
											//如果有电流
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] == 1 )
											{

												//下发命令读数
												if(m_SendAngle == 0)
												{
													//下发命令读数
													CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//星角变读表,下发命令读数
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												
												//如果在备用母线和备用出线上读出来
												if(int(CurrentValue) != -1)
												{
													switch(PhaseNo)
													{
													case 0:
														{
															m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A相",m_PROTOCOL);
															break;
														}
													case 1:
														{
															m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B相",m_PROTOCOL);
															break;
														}
													case 2:
														{
															m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C相",m_PROTOCOL);
															break;
														}
													}
													
													MotherLine = BakMotherLine;
													LineNo     =     BakLineNo;
												}

											}

										}

										SurrenderWindowMessage();

										//如果按了停止按钮
										if(!m_StartRead)
										{	
											break;
										}

									    //动态监控读表时间
										if(m_CheckReading)
										{

											ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

											//1分钟前停止
											if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
											{
												break;
											}

										}			

										if(a >= 7 && a <= 9 && (ModuleNo%100 <= 12))
										{
											m_OldModule       =      ModuleNo;
											m_OldCurrentValue =  CurrentValue;
										}

									}

									/*
									if(m_ReadTimes > 3  &&  m_GetDataFromFile)
									{
										//时间
										CTime timet = CTime::GetCurrentTime();	
										strValue.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
										CurrentValue  =	GetTestData(ModuleNo,strValue);	
									}
									*/
								}

								SurrenderWindowMessage();
								
								//如果是脉冲表,读有功电度或冻结电度,则加上原来的表底
    							if((a < 1) && (ModuleNo%100 < 12) && (CurrentValue >= 0))
								{
									//加上电表初值
									CurrentValue =  CurrentValue + m_BeginValue;
								}							
						

								//特别处理结束,如果是读驻留的话，如果读出的值和上次一样，则再读一个实时值填入
								if((WhichTable == 1  && (CurrentValue >= 0 || int(CurrentValue) == -4)) && !m_CanQuickRead71485)
								{
                                    
									//释放CPU时间
									SurrenderWindowMessage();									
	                                
									//如果还在读
									if(m_StartRead)
									{
									
										//除电流、电压、功率因素外一次应该比一次大,如果没有驻留过或者还是上次的驻留
										if(((a < 4 || (a > 9 && a < 13)) && CurrentValue >= 0) || (int(CurrentValue)==-4))
										{ 

											m_StillRunning = FALSE;

											if(CurrentValue >= 0)
											{
												//如果不合理
												if(!CheckReadValueValid(ModuleNo,m_FieldNames,CurrentValue,m_ZhuLiuTime,1))
												{												   
												   //WriteToLog("检测驻留比原来小或等,不理会");                                                    
													m_StillRunning = TRUE;
													CurrentValue   =   -1;
												}
												
											}										

											//检测数据有效性结束
											if(m_StillRunning || (int(CurrentValue) == -4))
											{

												//无效的话,读实时的值
												if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
												{
													//22         协议命令字 正式命令=驻留命令+1
													tempvalue     =  value + 0x01;
												}
												else
												{
													//31,32,71,72协议命令字 正式命令=驻留命令-0x80
													tempvalue     =  value - 0x80;
												}
													
												//如果还在读
												if(m_StartRead)
												{

													//如果没有检测
													if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
													{
														
														//如果有电流
														if(CheckIfHaveCurrentValue(MotherLine,LineNo))
														{
															
															m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
														}
														else
														{
															m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
															
														}
														
													}									
													
													//如果有电流
													if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
													{
														
														m_CheckTimes =  0;

														//连续读数2次
														for(int m_qqq = 0; m_qqq < 3; m_qqq++)
														{	
															//释放CPU时间
															SurrenderWindowMessage();
															
															//下发命令读数
															if(m_SendAngle == 0)
															{
																//下发命令读数,读一个实时的数，值为－4没有收到过驻留
																CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,tempvalue,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
															}
															else
															{
																//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留
																CurrentValue  =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,tempvalue,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
															}
															
															SurrenderWindowMessage();

														    if(CurrentValue >= 0  && m_StartRead)
															{
															
																//如果是脉冲表,读有功电度或冻结电度,则加上原来的表底
																if((a < 1) && (ModuleNo%100 < 12) && (CurrentValue >= 0))
																{
																	//加上电表初值
																	CurrentValue =  CurrentValue + m_BeginValue;
																}		

																//检测数据有效性结束
																if(!CheckReadValueValid(ModuleNo,m_FieldNames,CurrentValue,m_ZhuLiuTime,0))
																{
																	m_CheckTimes ++;
																//	WriteToLog("<<检测驻留比原来小,不理会>>");
                                                                    CurrentValue = -1;
																}
																else
																{
																	break;
																}
																
																if(!m_StartRead)
																{
																	CurrentValue = -1;
																	break;
																}

															}
															
															//释放CPU时间
															SurrenderWindowMessage();
															
														}

														SurrenderWindowMessage();

														//连续有2次以上，读出实际值比原来的小的话，下次不读
														if(m_CheckTimes > 1 && CurrentValue < 0)
														{															
															strValue.Format("UPDATE TB_USER SET %s = STUFF(%s,%d,1,'Y') WHERE USER_MODULENO=%d",m_ReadMeterLabel,m_ReadMeterLabel,a+1,ModuleNo);
															CDataBaseInstance::ExecuteDataBaseSQL(strValue);
														}

													}
													else
													{
														CurrentValue  =  -6;//没有电流
													}

												}


											}
										
										}

									
									}

									//释放CPU时间
									SurrenderWindowMessage();
								
									if(!m_StartRead)
									{	
										break;
									}

								    //动态监控读表时间
									if(m_CheckReading)
									{

										ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

										//1分钟前停止
										if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
										{
											break;
										}

									}			
									
								}
								//特别处理结束
												
							}
							else
							{
								//long  m_address 表地址
								//short kinds     种  类  0---有功 2---无功 4---A相电流 5---B相电流 6---C相电流 7---A相电压 8---B相电压 9---C相电压
								//直接从485口读数据
								if(a != 1 || a != 3)//1,3为手拉手读总有功或总无功
								{
									//m_StrArray[9]变台名称  485口上的电表高6位在变台名称中
									m_StrArray[9].TrimLeft();
									m_StrArray[9].TrimRight();

									//串口表12位地址
									strValue.Format("%6d%6d",atol(m_StrArray[9]),int(ModuleNo/100)); 
									strValue.Replace(' ', '0');
					
									CurrentValue =  ReadDataFrom485Com2(strValue,a);

									m_StrArray[9] = "串口读表";
								}
								else
								{
									continue;
								}
								
							}
							
							///////////////////////////////////根据读表值下结论/////////////////////////
							//在列表上显示出结果
							if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3 || int(CurrentValue) == -6)
							{

								if(!m_UseOldValue)
								{
									
									if(!m_IsAutoSending)
									{
										//定时驻留读表不响
										Beep(5000,400);  //2004.12.13加
									}

								}
															
								//设置读成功标志
								if(int(CurrentValue) != -6)
								{
									strValue.Format("UPDATE TB_USER SET %s = STUFF(%s,%d,1,'Y') WHERE USER_MODULENO=%d",m_ReadMeterLabel,m_ReadMeterLabel,a+1,ModuleNo);
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								}
								
								//时间
								CTime timet = CTime::GetCurrentTime();
								
								//是驻留读表的话
								if(	WhichTable == 1)
								{

									m_StrArray[12] = m_ZhuLiuTime;//驻留时间
									m_ReadTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

								}
								else
								{	
									
									//动态监控读表时间
									if(m_CheckReading)
									{
										m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),m_shikedian,0);
									}
									else
									{
										m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
									}

								}

								/********************选择结束**************/
								if(CurrentValue >= 0)
								{
								
									if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
									{
										//61,62协议小数点为1位
								    	strValue.Format("%.1f",CurrentValue);
									}
									else
									{
										strValue.Format("%.2f",CurrentValue);

									}

									m_StrArray[11].Format("%12s",strValue);
									
									//61、62协议的485表的电流电压处理
									if(int(m_PROTOCOL/10) == 6 && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
									{
										//6162协议
										if(value==0x08 || value==0x09)
										{
										   //分开三相电流
										   m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2);
										}
										else if(value==0x0B || value==0x0A)
										{
										   //分开三相电压
										   m_StrArray[11].Format("%3d,%3d,%3d",(int(CurrentValue)/16384)*2,((int(CurrentValue)%16384)/128)*2,(int(CurrentValue)%128)*2);
										}

									}

									//71,72的快速读表
									if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0xF0 || value==0x62 || value==0xF2))
									{
										
										if(value==0x60 || value==0xF0)
										{											
											//3电压A电流 
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3]);//(long(CurrentValue)/long(pow((double)2,24)))*2.0,((long(CurrentValue)%long(pow((double)2,24)))/long(pow((double)2,16)))*2.0,((long(CurrentValue)%long(pow((double)2,16)))/long(pow((double)2,8)))*2.0,(long(CurrentValue)%long(pow((double)2,8)))*0.2);
											m_StrArray[10]   = "3电压A电流";
											//3电压A电流 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 4)+'Y'+SUBSTRING(%s,6,2)+'YYY'+SUBSTRING(%s, 11, 5)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);									

										}
										else
										{
											//BC电流,功率因素,无功功率
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3]);//(long(CurrentValue)/long(pow((double)2,24)))*0.2,((long(CurrentValue)%long(pow((double)2,24)))/long(pow((double)2,16)))*0.2,((long(CurrentValue)%long(pow((double)2,16)))/long(pow((double)2,8)))*0.01,(long(CurrentValue)%long(pow((double)2,8)))*0.01);
											m_StrArray[10]   = "BC电流功因无功率";
											//BC电流、功率因素、无功功率 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
										    strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 5)+'YY'+SUBSTRING(%s,8,6)+'Y'", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
											
										}	
										
									//	WriteToLog(strValue);								
										
									}

									/////////////////////////////////////////////////
									//71,72的快速读表,
									if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
									{

                                        if(value==0x5A || value==0x5E || value==0x5C)
										{											
											//实时峰，谷，平快速读表
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
											m_StrArray[10]   = "峰平谷快读";
											//实时峰，谷，平快速读表 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 11) + 'YYY' +SUBSTRING(%s, 15, 1)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
  										    CDataBaseInstance::ExecuteDataBaseSQL(strValue);
									
										}
										else if(value==0x02 || value==0x06)
										{
											//实时有功、无功%f
											m_StrArray[11].Format("%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1]);
											m_StrArray[10]   = "有功无功快读";
											//实时有功、无功 .a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
											strValue.Format("UPDATE TB_USER SET %s = 'Y' +  SUBSTRING(%s, 2, 1) + 'Y' + SUBSTRING(%s , 4, 11)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										}
										else if(value == 0xDA || value == 0xDE || value == 0xDC)
										{
                                            //驻留峰，平，谷
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
											m_StrArray[10]   = "峰平谷快读";
											//驻留峰，谷，平快速读表 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 11) + 'YYY' +SUBSTRING(%s, 15, 1)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);	
                                        } 
										else if(value == 0x82 || value == 0x86)
									    { 	 
											//驻留实时有功、无功
											m_StrArray[11].Format("%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1]);
											m_StrArray[10]   = "有功无功快读";
											//驻留有功、无功 .a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数														
											strValue.Format("UPDATE TB_USER SET %s = 'Y' +  SUBSTRING(%s, 2, 1) + 'Y' + SUBSTRING(%s , 4, 11)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);									       
                                        }	
										
									//	WriteToLog(strValue);

									}
														
									////////////////////////////////////////////////////////

									
									//存贮数据入数据库中,传送来的数应小于999999.99
									switch(WhichTable)
									{
									case 0:
										{
											//如果是数据表,正式读表的话,存入TB_REALTIME表中
											if(IfWriteData)
											{
												
												//动态监控读表时间
												if(m_CheckReading)
												{
													//动态监控读表,存入TB_REALTIME表中,读表协议100,专用
													strValue.Format("REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",ModuleNo,m_StrArray[12]);
													
													if(CDataBaseInstance::GetAllRecordsCount("TB_REALTIME", strValue) < 1)
													{
														
														//原先表中没有此数据,则新加	
														if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
														{

															//61、62协议的485表的电流电压处理
															if(value==0x08 || value==0x09)
															{
																//分开三相电流
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,100,m_StrArray[12]);
															}
															else if(value==0x0B || value==0x0A)
															{
																//分开三相电压
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,100,m_StrArray[12]);
															}

														
														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
														{
																								                       
															//71、72协议的485表的电流电压处理
															if(value==0x60)
															{ 															
																//3电压A电流
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_ACURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],100,m_StrArray[12]);
															}
															else
															{															
																//BC电流、功率因素、无功功率
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_GLYS,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],100,m_StrArray[12]);
															}

															
														}														
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
														{
														
															//71,72的快速读表,
															if(value == 0x5A || value == 0x5E || value == 0x5C)
															{	
															
																//实时峰，平，谷快速读表
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL) VALUES (%d,%.1f,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
															}
															else if(value == 0x02 || value == 0x06)
															{
															
																//实时有功、无功
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_WORKDEGREETOTAL,REALTIME_LOSEDEGREETOTAL) VALUES (%d,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1]);
															}
																												
														}
														else
														{															
														
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s')",m_FieldNames,ModuleNo,CurrentValue,100,m_StrArray[12]);
														
														}


													}
													else
													{
														
														//原先实时表中有此数据,则替换原来数据
														if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
														{
															
															//61、62协议的485表的电流电压处理
															if(value==0x08 || value==0x09)
															{
																//分开三相电流
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_ACURRENT=%.1f,REALTIME_BCURRENT=%.1f,REALTIME_CCURRENT=%.1f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,ModuleNo,m_StrArray[12]);
															}
															else if(value==0x0B || value==0x0A)
															{
																//分开三相电压
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_AVOLTAGE=%.1f,REALTIME_BVOLTAGE=%.1f,REALTIME_CVOLTAGE=%.1f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,ModuleNo,m_StrArray[12]);
															}


														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
														{
															
															//71、72协议的485表的电流电压处理
															if(value==0x60)
															{
																//3电压A电流
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_AVOLTAGE=%.2f,REALTIME_BVOLTAGE=%.2f,REALTIME_CVOLTAGE=%.2f,REALTIME_ACURRENT=%.2f,REALTIME_TRANSCRIBETIME='%s' WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],ModuleNo,m_StrArray[12]);
															}
															else
															{	
																//BC电流、功率因素、无功功率
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_BCURRENT=%.2f,REALTIME_CCURRENT=%.2f,REALTIME_GLYS=%.2f,REALTIME_TRANSCRIBETIME='%s' WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],ModuleNo,m_StrArray[12]);
															}
															
														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
														{
															
															//71,72的快速读表,
															if(value == 0x5A || value == 0x5E || value == 0x5C)
															{	
																//实时峰，平，谷快速读表
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_FDL=%.2f,REALTIME_PDL=%.2f,REALTIME_GDL=%.2f WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],ModuleNo,m_StrArray[12]);
															}
															else if(value == 0x02 || value == 0x06)
															{
															
																//实时有功、无功
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_WORKDEGREETOTAL=%.2f,REALTIME_LOSEDEGREETOTAL=%.2f WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],ModuleNo,m_StrArray[12]);
															}
																													
														}
														else
														{
															strValue.Format("UPDATE TB_REALTIME SET %s = %.2f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",m_FieldNames,CurrentValue,ModuleNo,m_StrArray[12]);
														}

													}
																								
												
												}
												else
												{
												
													
													if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
													{
														
														//61、62协议的485表的电流电压处理
														if(value==0x08 || value==0x09)
														{
															//分开三相电流
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_PROTOCOL,m_StrArray[12]);
														}
														else if(value==0x0B || value==0x0A)
														{
															//分开三相电压
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_PROTOCOL,m_StrArray[12]);
														}
														
													}
													else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
													{

														//71、72协议的485表的电流电压处理
														if(value==0x60)
														{
															//3电压A电流
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_ACURRENT,REALTIME_PROTOCOL,REALTIME_HALTTIME,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
														}
														else
														{	
															//BC电流、功率因素、无功功率
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_GLYS,REALTIME_PROTOCOL,REALTIME_HALTTIME,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0]*0.2,m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
														}
													
													}
													else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
													{
														
														//71,72的快速读表,
														if(value == 0x5A || value == 0x5E || value == 0x5C)
														{	
															//实时峰，平，谷快速读表
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL) VALUES (%d,%.1f,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
														}
														else if(value == 0x02 || value == 0x06)
														{	
														    //实时有功、无功
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_WORKDEGREETOTAL,REALTIME_LOSEDEGREETOTAL) VALUES (%d,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1]);
														}
																										
													}
													else
													{
														
														//普通读表则新加
														strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_TRANSCRIBETIME,REALTIME_PROTOCOL) VALUES (%d,%.2f,'%s',%d)",m_FieldNames,ModuleNo,CurrentValue,m_StrArray[12],m_PROTOCOL);
													}
																						
												}
												
												//运行SQL语句
												CDataBaseInstance::ExecuteDataBaseSQL(strValue);

											}
											
											break;
										}
									case 1:
										{
											//驻留数据表,驻留读表的话,存入TB_GARRISON表中
											strValue.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",ModuleNo,m_ZhuLiuTime/*驻留时间*/);
											
											//原先驻留库中没有此驻留时间的数据
											if(CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", strValue) < 1)
											{
												
												//原先表中没有此数据,则新加
												if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
												{
												
													//61、62协议的485表的电流电压处理
													if(value==0x08 || value==0x09)
													{
														//分开三相电流
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_ACURRENT,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													else if(value==0x0B || value==0x0A)
													{
														//分开三相电压
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													
												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0xF0 || value==0xF2))
												{
	                                                
													//71、72协议的485表的电流电压处理
													if(value==0xF0)
													{
														//3电压A电流
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_ACURRENT,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													else
													{
														//BC电流、功率因素、无功功率
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_GLYS,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}

												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
												{
													
													//71,72的快速读表,
													if(value == 0xDA || value == 0xDE || value == 0xDC)
													{
														//驻留峰，平，谷
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_FDL,GARRISON_PDL,GARRISON_GDL,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													} 
													else if(value == 0x82 || value == 0x86)
													{ 
														//驻留实时有功、无功
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_WORKDEGREETOTAL,GARRISON_LOSEDEGREETOTAL,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													
												}
												else
												{
													strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,%s,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s','%s')",m_FieldNames,ModuleNo,CurrentValue,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
												}

											}
											else
											{   
												
												
												if((m_PROTOCOL == 61 || m_PROTOCOL == 62) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
												{
													
													//61、62协议的485表的电流电压处理
													if(value==0x08 || value==0x09)
													{
														//分开三相电流
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_ACURRENT=%.2f,GARRISON_BCURRENT=%.2f,GARRISON_CCURRENT=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													else if(value==0x0B || value==0x0A)
													{
														//分开三相电压
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_AVOLTAGE=%.2f,GARRISON_BVOLTAGE=%.2f,GARRISON_CVOLTAGE=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													
												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0xF0 || value==0xF2))
												{
	                                                
													//71、72协议的485表的电流电压处理
													if(value==0xF0)
													{
														//3电压A电流
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_AVOLTAGE=%.2f,GARRISON_BVOLTAGE=%.2f,GARRISON_CVOLTAGE=%.2f,GARRISON_ACURRENT=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													else
													{
														//BC电流、功率因素、无功功率
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_BCURRENT=%.2f,GARRISON_CCURRENT=%.2f,GARRISON_GLYS=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}

												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
												{
													
													//71,72的快速读表,
													if(value == 0xDA || value == 0xDE || value == 0xDC)
													{
														//驻留峰，平，谷
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_FDL=%.2f,GARRISON_PDL=%.2f,GARRISON_GDL=%.2f WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],ModuleNo,m_ZhuLiuTime);
													} 
													else if(value == 0x82 || value == 0x86)
													{ 	
														//驻留实时有功、无功
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_WORKDEGREETOTAL=%.2f,GARRISON_LOSEDEGREETOTAL=%.2f WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],ModuleNo,m_ZhuLiuTime);
													}
													
												}
												else
												{
													//原先驻留库中有此驻留时间的数据,则替换原来数据
													strValue.Format("UPDATE TB_GARRISON SET %s = %.2f,GARRISON_TRANSCRIBETIME='%s',GARRISON_PROTOCOL=%d WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_FieldNames,CurrentValue,m_ReadTime,m_PROTOCOL,ModuleNo,m_ZhuLiuTime);
												}


											}
											
											//运行SQL语句
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);

											break;
										}
										
									}

									
								}
								else
								{

									if(int(CurrentValue) == -2)
									{	
										//回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好
										m_StrArray[11] = "表通讯错误";
									}
									else if(int(CurrentValue) == -3)
									{
										//回的值为AAAAAA.AA,扩展模块的表没有连好
										m_StrArray[11] = "扩展表故障";
									}
									else if(int(CurrentValue) == -6)
									{
										//线路停电
										m_StrArray[11] = "线路停电";
									}
									
									m_ReadTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
									
									if(int(CurrentValue) == -2 || int(CurrentValue) == -3)
									{
										//有接线错误的写入数据表
										if(	WhichTable == 1)
										{
											//是驻留读表的话
											strValue.Format("INSERT INTO TB_LINEERROR(LINEERROR_MODULE,LINEERROR_READTIME,LINEERROR_HALTTIME,LINEERROR_KINDS) VALUES (%d,'%s','%s',%d)",ModuleNo,m_ReadTime,m_StrArray[12],2);
											//运行SQL语句
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										}
										else
										{
											
											if(IfWriteData)
											{
												strValue.Format("INSERT INTO TB_LINEERROR(LINEERROR_MODULE,LINEERROR_READTIME,LINEERROR_HALTTIME,LINEERROR_KINDS) VALUES (%d,'%s','%s',%d)",ModuleNo,m_StrArray[12],"",1);
												//运行SQL语句
												CDataBaseInstance::ExecuteDataBaseSQL(strValue);
											}
											
										}

									}

								}
					
    							//显示结果列表
								for(i = 0; i < 13; i++)
								{	
                        
									//如果是第一列
									if(i == 1)
									{
										//如果是线表或站总表
										if(m_AMMETERKIND > 4)
										{
											m_StrArray[i] = m_StrArray[i] + "[串2]";
										}
										
									}
									
     								m_StrArray[i] = " " + m_StrArray[i];
									
								}
								
								//显示列表数据
								SendMessage(WM_EVENT, 3, 0);
							
								//行号自加
								m_ListRows++;
								
							  }
							  
							  //在列表上显示出结果
							  if(CurrentValue <  0)
							  {
								  //时间
								  CTime timet = CTime::GetCurrentTime();
								  m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
								  
								  //是最后一次没有读出表的话,记录下来,或者回的数据不合要求,如果是驻留读表
								  if((m_ReadTimes == READTIMES -1 || int(CurrentValue) == -2 || int(CurrentValue) == -3) && WhichTable== 1) 
								  {  
									  //去掉空格字符
									  for(int i = 0; i <= 12; i ++)
									  {
                               			  m_StrArray[i].TrimLeft(); 
							    		  m_StrArray[i].TrimRight(); 
									  }
											  
								  }
					  
							  }
							  
							  ///////////////////////////////////根据读表值结论完/////////////////////////
							  
							  //用户库下滑一个记录
							  rs.MoveNext();
							  SetProgressCtrlSetIt();
							  
							}
							//关闭数据库
							
							if(rs.IsOpen())
							{
								rs.Close();
							}

							//如果按了停止按钮
							if(!m_StartRead)
							{	
								break;
							}

							//动态监控读表时间
							if(m_CheckReading)
							{
								
								ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;
								
								//1分钟前停止
								if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
								{
									break;
								}
								
							}			

					  }

				}
				 
			}
			//扫完一轮结束
			
			//隐藏滚动条
			ShowProgressCtrl(FALSE);

	    	CTime RecycleTime1 = CTime::GetCurrentTime();
			CTime RecycleTime2 = CTime::GetCurrentTime();

			CTimeSpan       ts;	
	
			//recycles        循环次数
			//Settimes        每二次时间间隔,分钟
			//延时让工控机休息
			if(www  < (recycles - 1) && m_StartRead)//有可读记录标志且循环次数没有到
			{	
				
				//在原库中作标记,设初始化标志
				strSql.Format("(%s) AND (%s<>'YYYYYYYYYYYYYY')",constr,m_ReadMeterLabel);
				
				//得到记录个数
				fields     = CDataBaseInstance::GetAllRecordsCount("TB_USER",strSql);  
				
				if(fields  > 0)
				{
					
					while(1)
					{
						
						RecycleTime2 = CTime::GetCurrentTime();
						ts = RecycleTime2 - RecycleTime1;
						
						if(ts.GetTotalSeconds() >=  Settimes * 60 || !m_StartRead)
						{
							break;
						}
						
						//延时一秒
						Sleep(1000);

						//显示状态栏信息,发送显示状态栏提示	
						StatusStr.Format("【共%d轮，已读%d轮，离下轮还有%d分%d秒，请稍侯...】",recycles,www + 1,(Settimes * 60 - ts.GetTotalSeconds())/60,(Settimes * 60 - ts.GetTotalSeconds())%60);
						SendMessage(WM_EVENT,1,0);

						//放出windows消息
						SurrenderWindowMessage();
					}

				}
				
			}
				        
        }
        
		//如果按了停止按钮
		if(!m_StartRead)
		{
			
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			if(db.IsOpen())
			{
				db.Close();
			}
			
			//显示状态栏信息
			StatusStr = "【读数中途被停止】";
			SendMessage(WM_EVENT, 1, 0);
			
			//隐藏滚动条
			ShowProgressCtrl(FALSE);
		    return;
		}
		
		//所有轮扫完
		if(rs.IsOpen())
		{
			rs.Close();
		}
	
		if(db.IsOpen())
		{
			db.Close();
		}

	}

	//所有轮扫完
	if(db.IsOpen())
	{
		db.Close();
	}

    //发送显示状态栏提示
	StatusStr = "【读表结束】";
	SendMessage(WM_EVENT, 1, 0);
	
   	//更新列表框中数据
	SendMessage(WM_EVENT, 13, 0);
	
	//隐藏滚动条
	ShowProgressCtrl(FALSE);
	
	m_times           ++;
	
	//动态监控读表时间
	if(!m_CheckReading)
	{
		m_StartRead  = FALSE;
	}

	m_others         = FALSE;

}

void CIFRMView::OnPhasetest() 
{
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CPhaseTestDlg        dlg;
	CString       PassStr;
	
	//记录总个数
	long    m_records = 0;

	//得到对话条的所选条件
    if(!GetDialogBarStr())
	{
		return;
	}

	dlg.m_StrSql = m_ModuleFindContionStr;
	
	if(dlg.DoModal() == IDOK)
	{
		
		//是否相不定,记录个数
		if(dlg.m_nook == TRUE)
		{
            m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", dlg.m_StrSql + " AND USER_PHASE=3");
		}
		else
		{
            m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", dlg.m_StrSql);
		}

		switch(dlg.m_radio)
		{
		case 0:
			{  
				//测试三相别
				//CString title        列标题
				//CString Result       结论
				//CString ConStr       条件范围
				//BYTE    orders       命令关键字
				//BOOL    OnlyReadNot  TRUE  只读没有测试出相的模块,FALSE 反之
				//int     times        读每个模块的次数
				//BOOL    OnlyOnce     TRUE  好多表共用一个模块时只测试一次,FALSE 每个表都测试一次
				//int     MaxIValue    最大值(为写参数时用)
				//int     MinIValue    最小值
				//int     intervals    间  隔
				//电局版本
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//要读东西   
					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					//                  参数11               满足条件记录个数
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","模块相别测定","测定成功",dlg.m_StrSql,0x02,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","模块相别测定","测定成功",dlg.m_StrSql,0x02,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}

				break;
			}
		case 1:
			{
				//读DSP电流值
				//CString title        列标题
				//CString Result       结论
				//CString ConStr       条件范围
				//BYTE    orders       命令关键字
				//BOOL    OnlyReadNot  TRUE  只读没有测试出相的模块,FALSE 反之
				//int     times        读每个模块的次数
				//BOOL    OnlyOnce     TRUE  好多表共用一个模块时只测试一次,FALSE 每个表都测试一次
				//int     MaxIValue    最大值(为写参数时用)
				//int     MinIValue    最小值
				//int     intervals    间  隔
				
				//电局版本
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//要读东西   
					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","读DSP电流","读值成功",dlg.m_StrSql, 0x48,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","读DSP电流","读值成功",dlg.m_StrSql, 0x48,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				
				break;
			}
		case 2:
			{
				//读电流值
				//CString title        列标题
				//CString Result       结论
				//CString ConStr       条件范围
				//BYTE    orders       命令关键字
				//BOOL    OnlyReadNot  TRUE  只读没有测试出相的模块,FALSE 反之
				//int     times        读每个模块的次数
				//BOOL    OnlyOnce     TRUE  好多表共用一个模块时只测试一次,FALSE 每个表都测试一次
				//int     MaxIValue    最大值(为写参数时用)
				//int     MinIValue    最小值
				//int     intervals    间  隔
				
				//电局版本
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//要读东西   
					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","读电流值","读值成功",dlg.m_StrSql,0x44,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","读电流值","读值成功",dlg.m_StrSql,0x44,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}

				break;
			}
			
				
		}
	 
		//电局版本,下结论
		if(AppInfo::Instance().m_WhichKind == FALSE)
		{
			
			//远程发送调试参数的指令
			if(SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE) == TRUE)
			{
				
				m_StartRead = TRUE;
				
			}
			else
			{
				m_StartRead = FALSE;
			}
			
		}
		
     }
	 
}


//得到驻留时间
CString CIFRMView::GetZhuLiuTime()
{
	
	CString         str;
	//打开数据库
	CDatabase        db;
	CString      strSql;
	CString    strValue;
	str        =     "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
        
		//得到记录个数
		long fields = CDataBaseInstance::GetAllRecordsCount("TB_HALTTIME", "ALL");
		
		if(fields > 0)
		{
			
			strSql = "SELECT * FROM TB_HALTTIME";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//读用户信息
			for(int j = 0;j < fields; j++)
			{
				//得到值
				rs.GetFieldValue((short)0,str);
				str.TrimRight();
				
				//库下滑一个记录
				rs.MoveNext();
			}
			
		}
		
		//关闭数据库
		rs.Close( );
		db.Close( );
	}
	return str;
	
}

void CIFRMView::SendOfficeBreadorder(int generatrix,int times,int m_iBroadTime,BYTE m_Potocol,CString NewTime)
{
	
	CString         StrSql;
	
	BYTE         ORDER[15];
	BYTE          PhaseBit;
	
	//1601 模块号为16表号为01
	BYTE AddrH,AddrM,AddrL;
	
	//交出window控制权
	SurrenderWindowMessage();
	
	//广播地址
	AddrH = 0;          //高位    对应的为数据1
	AddrM = 0;          //中间位  对应的为数据2


	AddrL = m_iBroadTime/int(pow((double)2,10));     //低4位,其是时间的高4位
	// A 01 B 02  C 03
	
    m_StartRead = TRUE;
	
	BYTE StatusH,StatusL;
	StatusH    = (m_iBroadTime%(int(pow((double)2,10))))/256; //高位,对应的为数据3的后2位
	StatusL    =  m_iBroadTime%256;                   //低位    数据4
	switch(times)
	{ 
	case  0://A相
		{
			PhaseBit    = 0x01;
			//	ORDER[4]    = 0x40;  
			break;
		}
	case  1://B相
		{
			PhaseBit    = 0x02; 
			//	ORDER[4]    = 0x80;  
			break;
		}
	case 2://C相
		{  
			PhaseBit    = 0x03;
			//	ORDER[4]    = 0xC0;   
			break;
		}
	}
	
	//命令字
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x53; //触发命令
	
	ORDER[3]  = generatrix*64  + 0 + PhaseBit;//合成字节 前2位为(j 0，1二根母线)母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
//	ORDER[3]  = 0 + PhaseBit;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[4]  = 3;// 延时过0点数 
	
	//ORDER[0]到ORDER[4]单片机用  
	
	/*
	//传给模块用
	ORDER[5]  = 0xf2; //命令字，要什么东西
	ORDER[6]  = 0;//模块高地址
	ORDER[7]  = 0;//模块中地址
	ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4现为驻留时间,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
	ORDER[9]  = StatusL;//驻留时间
	*/

	if(m_Potocol == 22)
	{
		//如果协议为22	
		//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用  
		//格式：10位监督码+7(7个1)+ 7(7位驻留时间)+ 7(7个0)
		//地址前8位
		ORDER[5]  = 254   + (m_iBroadTime>>6); //时间高1位	
		//时间后6位 + 2位0
		ORDER[6]  = (m_iBroadTime%64)*4 + 0;
		ORDER[7]  =                    0;
		ORDER[8]  =                    0;
		ORDER[9]  =                    0;
	}
	else
	{
					
		if(m_Potocol == 61 || m_Potocol == 62)
		{
			//61,62协议
			//ORDER[5]到ORDER[10]由单片机传给模块用 21位数据有用  
			//格式：18位监督码+ 地址高8位全1 +  地址低6位(6位驻留时间) + 6(6个0) + 0001000
			//地址前8位
			ORDER[5]  =                 0xff; //地址高8位全1	
			ORDER[6]  =    (m_iBroadTime<<2); //地址低6位(6位驻留时间) + 2个0
			ORDER[7]  =                    1; //4个0 ＋ 0001
			ORDER[8]  =                    0; //000 + 5个0
			ORDER[9]  =                    0;
		}
		else
		{
			//31,32,33,71,72,72协议
			//传给模块用
			ORDER[5]  = 0xf2; //命令字，要什么东西
			ORDER[6]  = 0;    //模块高地址
			ORDER[7]  = 0;    //模块中地址
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //合成字节,前1-4现为驻留时间,5-6为相位标记(01 A 10 B 11 C),7-8位发驻留时间用
			ORDER[9]  = StatusL;//驻留时间
		}

					
	}			

	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//检验和 ORDER[5]到ORDER[9]之和

	//暂时无用
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//向单片机发命令
	if(PcSendToSCM(ORDER,m_Potocol/*读表协议*/,0))
	{
		
		switch(times)
		{
		case 0:
			{
				StrSql.Format("第%d段母线，驻留A相成功，时间%s,协议[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
		case 1:
			{
				StrSql.Format("第%d段母线，驻留B相成功，驻留时间%s,协议[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
		case 2:
			{
				StrSql.Format("第%d段母线，驻留C相成功，驻留时间%s,协议[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
			
		}
		
	}
	
    //删除驻留时间
	StrSql = "DELETE FROM TB_HALTTIME";
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	
	//存贮驻留时间
	StrSql.Format("INSERT INTO TB_HALTTIME(HALTTIME_TIME) VALUES ('%s')",NewTime);
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	m_StartRead = FALSE;

}

void CIFRMView::WriteListHeading()
{
	//删除所有的数据
	m_Grid.DeleteAllItems();
    m_Grid.ShowWindow(SW_SHOW);		
	
	//是否显示历史数据
	m_IsHistory     =    FALSE;

	TRY { 
		m_Grid.SetFixedRowCount(1);
	    m_Grid.SetRowCount(1);     //行
    	m_Grid.SetColumnCount(13); //列
    	//填充数据和行号
	    CStringArray m_StrArrays;
		short         m_wide[13];
		m_StrArrays.SetSize(13);
        m_StrArrays[0]  = "序号";
		m_wide[0]       =  36;
		m_StrArrays[1]  = "读表类型";
		m_wide[1]       =  75;
		m_StrArrays[2]  = "用户名称";
		m_wide[2]       =  75;
		m_StrArrays[3]  = "用户编号";
		m_wide[3]       =  60;
		m_StrArrays[4]  = "地址";
        m_wide[4]       =  105;
		m_StrArrays[5]  = "模块号";
		m_wide[5]       =  60;
		m_StrArrays[6]  = "电表号";
		m_wide[6]       =  60;
		m_StrArrays[7]  = "线路名称";
		m_wide[7]       =  60;
		m_StrArrays[8]  = "线路参数";
		m_wide[8]       =  86;
		m_StrArrays[9]  = "变台名称";
		m_wide[9]       =  90;
		m_StrArrays[10]  = "类型";
		m_wide[10]       =  80;
		m_StrArrays[11] = "读表值";
		m_wide[11]       =  110;
		m_StrArrays[12] = "时间";
	    m_wide[12]       =  115;
	    
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
		#ifndef _WIN32_WCE
		   dwTextStyle |= DT_END_ELLIPSIS;
		#endif

	   for (int col = 0; col < m_Grid.GetColumnCount(); col++)
	   { 
		   
		   GV_ITEM        Item;
		   Item.mask = GVIF_TEXT|GVIF_FORMAT;
		   Item.row      =   0;
		   Item.col      = col;
		   Item.nFormat = dwTextStyle;
		   Item.strText.Format("%s",(m_StrArrays[col]));
		   m_Grid.SetItem(&Item);
		   m_Grid.SetColumnWidth(col,m_wide[col]); 
		   
	   }
        
		//只读状态
		m_Grid.SetModified(FALSE,-1,-1);
		//标题
		m_Grid.m_title  = "";

		m_Grid.SetBkColor(RGB(255,255,255));

		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	END_CATCH

	/******************************************************************
	**         收到的格式有两种:
	**         a、BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
	**         b、BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
	**         c、BEGINS;DATAS:2:表名;读表结束;ENDS      数据传送结束标志
	*******************************************************************/
	SurrenderWindowMessage();//交出window控制权
   
	/*
	//如果连接好的话
	//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
	//Str             发送字符
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	if(SelectSendString(m_sendkind,"BEGINS;DATAS:0:" + m_ComeIntoDataName + ";序号,36;读表类型,85;用户名称,95;用户编号,60;地址,125;模块号,60;电表号,80;线路名称,60;母线-线-相-协议,96;变台名称,65;类型,60;读表值,75;时间,115;0;ENDS",TRUE,FALSE,FALSE))
	{
		SurrenderWindowMessage();//交出window控制权
		Sleep(500);
	}
    
	SurrenderWindowMessage();//交出window控制权
	*/
  
}




BOOL CIFRMView::StopRunning()
{
	//如果按了停止按钮
	if(m_StartRead == FALSE)
	{	
		ShowProgressCtrl(FALSE);
		status("【读数中途被停止】");//提示:
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	
}

//显示列表数据
void CIFRMView::AddlistItem(CString m_StrArray[], int n)
{
	//插入一行数据
   	m_Grid.InsertRow(_T(" "), -1);
	m_Grid.Invalidate();

	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	#ifndef _WIN32_WCE
	   dwTextStyle |= DT_END_ELLIPSIS;
	#endif

	for (int col = 0; col < n; col++)
	{ 
		
		GV_ITEM  Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     = m_Grid.GetRowCount() - 1;
		Item.col     = col;
		Item.nFormat = dwTextStyle;
		Item.strText.Format("%s",(m_StrArray[col]));
		m_Grid.SetItem(&Item);
	}
	
	m_Grid.SetModified(FALSE,-1,-1);
	m_Grid.Invalidate();
	
}

/****************************  执行命令   **********************************
**    COMMAND  执行命令
**    格式为:

1、供电局要变电站执行发驻留时间命令, 变电站发广播信息命令所有模块驻留同一时刻的数据,如有功电度等。
格式：BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  
参数1---母线
参数2---相别
参数3---发送的时间单位数(8的倍数)
参数4---发送的时间(字符形式) 执行发驻留命令

2、供电局要变电站执行测试读表操作命令,只是实时读表,不保存读回数据
格式：BEGINS;变电站编号;COMMAND:01:参数1:参数2;ENDS 
参数1---用户数据范围(用户数据范围，条件字符串)
参数2---格式为由0和1组成的四位数表示如:1111   
第一位表示 有功电度 1 － 要读有功电度 0 - 不读有功电度
第二位表示 无功电度 1 － 要读无功电度 0 - 不读无功电度
第三位表示     电流 1 － 要读电流     0 - 不读电流
第四位表示     电压 1 － 要读电压     0 - 不读电压

3、供电局要变电站执行正式读表操作命令,正式读表,数据保存在正式读表数据表中,  
格式：BEGINS;变电站编号;COMMAND:02:参数1:参数2;ENDS 
参数1---用户数据范围(用户数据范围，条件字符串)
参数2---格式为由0和1组成的四位数表示如:1111   
第一位表示 有功电度 1 － 要读有功电度 0 - 不读有功电度
第二位表示 无功电度 1 － 要读无功电度 0 - 不读无功电度
第三位表示     电流 1 － 要读电流     0 - 不读电流
第四位表示     电压 1 － 要读电压     0 - 不读电压

4、供电局要变电站执行驻留读表操作命令，读回的驻留数据存放在TB_GARRISON中
格式：BEGINS;变电站编号;COMMAND:03:参数1:参数2;ENDS 
参数1---用户数据范围(用户数据范围，条件字符串) 
参数2---格式为由0和1组成的四位数表示如:1111   
第一位表示 有功电度 1 － 要读有功电度 0 - 不读有功电度
第二位表示 无功电度 1 － 要读无功电度 0 - 不读无功电度
第三位表示     电流 1 － 要读电流     0 - 不读电流
第四位表示     电压 1 － 要读电压     0 - 不读电压

5、供电局要变电站执行停电操作命令
格式：BEGINS;变电站编号;COMMAND:04:参数1;ENDS
参数1---用户数据范围(用户数据范围，条件字符串)  与
  
6、供电局要变电站执行送电操作命令
格式：BEGINS;变电站编号;COMMAND:05:参数1;ENDS
参数1---用户数据范围(用户数据范围，条件字符串)      

7、供电局要变电站执行定时读表设置
//格式：BEGINS;变电站编号;COMMAND:06:参数1;参数2;参数3;参数4;参数5;参数6;参数7;参数8;参数9;ENDS 
//参数1---驻留时刻 格式：点：分：秒如：0：00：00 
//参数2---发驻留次数,总共发多少次
//参数3---间隔，多长时间发一次驻留时刻命令,以便每一个模块都收到
//参数4---居民用表选择   0 每月一读          N天一读 N>=1 
//参数5---大用户表       0 每月一读          N天一读 N>=1
//参数6---变台总表       0 每月一读          N天一读 N>=1
//参数7---线路总表       0 每月一读          N天一读 N>=1
//参数8---电站总表       0 每月一读          N天一读 N>=1
//参数9---格式为由0和1组成的六位数表示如:111111   
//第一位表示 有功电度    0 - 不读有功电度    1 － 要读有功电度     
//第二位表示 有功电度种类0 －只读单边累加值  1 -  读单边累加值及表有功总值
//第三位表示 无功电度    0 - 不读无功电度    1 － 要读无功电度
//第四位表示 无功电度种类0 －只读单边累加值  1 -  读单边累加值及表无功总值
//第五位表示 电流        0 - 不读电流        1 － 要读电流      
//第六位表示 电压        0 - 不读电压        1 － 要读电压
//分解参数

8、供电局设置变电站发送设置角度大小
格式：BEGINS;COMMAND:07:参数1:参数2;ENDS   
参数1---哪一相 0－A 1－B 2－C相  
参数2---角度大小

9、供电局读变电站触发角度大小
BEGINS;COMMAND:08:参数1:参数2;ENDS 
参数1---母线编号  
参数2---哪一相 0－A 1－B 2－C相   

12、供电局向变电站发其它指令, 如:读写各项测试参数,处理各项参数
格式: BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
参数1---标题  如" 读变台容量"
参数2---结果  如" 读变台容量成功"
参数3---条件范围,数据范围
参数4---命令字   命令关键字
参数5---是否只读相不定   TRUE  只读没有测试出相的模块, FALSE 反之全部读   
参数6---次数        读每个模块的次数
参数7---是否只读一次,好多表共用一个模块时只测试一次   FALSE 每个表都测试一次,如电流测试一个模块有好多表,但模块只要读一个就够了,用不着每个表都读。
参数8---最小值(也当发送时传数)
参数9---最大值，(为写参数时用)
参数10--间隔        
********************************************************************/
void CIFRMView::CarryOutOrders(CString Str)
{

	CString             KeyStr;
	CString         Conditions;
	int    colum          =  0;
	
	int    k          =  Str.Find("COMMAND:");
	
	if(k != -1)
	{
		KeyStr  =   Str.Mid(8,2); 
		CString       TempStr[4];
		
		//初始化读表内容
		for(int j = 0; j < 15; j ++)
		{
			m_SetLabel[j] = FALSE;
		}
		
		//根据关键字判断是哪种命令
		switch(atoi(KeyStr))
		{
		case 0:  
			{
				
				//发驻留命令 
			    //BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  参数1---母线,参数2---相别,参数3---发送的时间单位数(8的倍数),参数4---发送的时间(字符形式) 执行发驻留命令				//str.Format("BEGINS;COMMAND:00:%d:%d:%d:%s;ENDS",i,broadTime,协议,s);
				Str = Str.Right(Str.GetLength() - 11);
				CString              strs[5];
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{

					//母线
                    strs[0] = Str.Left(k);
                    Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					//相别
					strs[1] = Str.Left(k);
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//发送的时间单位数(8的倍数)
						strs[2] = Str.Left(k);	
						Str = Str.Right(Str.GetLength() - k -1);
						k    =  Str.Find(':');
						
						//发送的协议
                        strs[3] = Str.Left(k);
						
						//发送的时间(字符形式)
						strs[4] = Str.Right(Str.GetLength() - k - 1);
						
						//回答执行命令正确
						SendErrorMessage(2);
						
						SendOfficeBreadorder(atoi(strs[0]),atoi(strs[1]),atoi(strs[2]),atoi(strs[3]),strs[4]);
						
					}
					
				}
				break;
				
			}
		case 1:
			{
				
				//供电局要变电站执行测试读表操作命令,只是实时读表,不保存读回数据
				//BEGINS;变电站编号;COMMAND:01:参数1:参数2:参数3:参数4:参数5;ENDS  
				//参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}

					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
	                
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					//回答执行命令正确
					SendErrorMessage(2);

					SendContionStr = Conditions;
           			ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)0,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
				break;
				
			}
		case 2:
			{
				//供电局要变电站执行正式读表操作命令,只是实时读表,不保存读回数据
				//BEGINS;变电站编号;COMMAND:02:参数1:参数2:参数3:参数4:参数5;ENDS 
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					
					//回答执行命令正确
					SendErrorMessage(2);

					SendContionStr = Conditions;
              	    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)1,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
				break;
				
			}
		case 3:
			{
				//供电局要变电站执行驻留读表操作命令,保存读回数据
				//BEGINS;变电站编号;COMMAND:03:参数1:参数2:参数3:参数4:参数5;ENDS 
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				if(m_IsAutoSending)
				{
					SendContionStr = "BEGINS;MESSAGE:0: 定时驻留期间不能驻留读表！;ENDS";
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					
					//回答执行命令正确
					SendErrorMessage(2);

					SendContionStr = Conditions;
           		    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)2,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
				break;
				
			} 
		case 4:
			{   
				//供电局要变电站执行停电操作命令
				//格式：BEGINS;变电站编号;COMMAND:04:参数1:参数2;ENDS
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---满足条件的记录个数
  
				Str = Str.Right(Str.GetLength() - 11);
				k    =  Str.Find(':');
				if(k !=  -1)
				{	
					
					
					//检查两边记录的记录数是否一致
					if(atol(Str.Right(Str.GetLength() - k - 1)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Str.Left(k)))
					{
						//0 --- 数据不一致  1------参数传输错误 
                        SendErrorMessage(0);
						return;
					}


					//回答执行命令正确
					SendErrorMessage(2);

					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","停电操作","停电成功",Str.Left(k), 0xf8,FALSE,5,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
                    SendErrorMessage(1);
					return;

				}
				break;
				
			}
		case 5:
			{   
				//供电局要变电站执行送电操作命令
				//格式：BEGINS;变电站编号;COMMAND:05:参数1;ENDS
				//参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---满足条件的记录个数
				
				Str = Str.Right(Str.GetLength() - 11);
				k    =  Str.Find(':');
				if(k !=  -1)
				{	
					
					
					//检查两边记录的记录数是否一致
					if(atol(Str.Right(Str.GetLength() - k - 1)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Str.Left(k)))
					{
						//0 --- 数据不一致  1------参数传输错误 
                        SendErrorMessage(0);
						return;
					}

					//回答执行命令正确
					SendErrorMessage(2);

					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					//SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","送电操作","送电成功",Str.Left(k), 0xF7,FALSE,5,TRUE,1,1,1);
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","送电操作","送电成功",Str.Left(k), 0xF6,FALSE,5,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
                    SendErrorMessage(1);
					return;

				}
				break;
				
			}
		case 6:
			{   
				//设置延迟角度大小 
				//格式：BEGINS;COMMAND:06:参数1:参数2:参数3;ENDS
				//参数1---母线编号  
				//参数2---哪一相 0－A 1－B 2－C相  
				//参数3---角度大小
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0;
				BYTE m_Angle      = 0;
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					m_phase      = atoi(Str.Left(k));                      //相    别
					m_Angle      = atoi(Str.Right(Str.GetLength() - k -1));//角度大小
					
					//回答执行命令正确
					SendErrorMessage(2);
					
					//设置角度
					//short phase  相别 0 A相 1 B相 2 C相
					//int   angles 角度
					SetPhaseAngle(m_generatrix,m_phase,m_Angle,1);
					
				}
				break;
							
			}
		case 7:
			{   
				
				//设置触发角度大小 
				//格式：BEGINS;COMMAND:07:参数1:参数2:参数3;ENDS
				//参数1---母线编号  
				//参数2---哪一相 0－A 1－B 2－C相  
				//参数3---角度大小
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0;
				BYTE m_Angle      = 0;
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
			
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					m_phase      = atoi(Str.Left(k));                      //相    别
					m_Angle      = atoi(Str.Right(Str.GetLength() - k -1));//角度大小
					
					//回答执行命令正确
					SendErrorMessage(2);

					//设置角度
					//short phase  相别 0 A相 1 B相 2 C相
					//int   angles 角度
					SetPhaseAngle(m_generatrix,m_phase,m_Angle,0);
					
				}
				break;
				
			}
		case 8:
			{   
				
				//读触发角度大小
				//BEGINS;COMMAND:08:参数1:参数2;ENDS 
				//参数1---母线编号  
				//参数2---哪一相 0－A 1－B 2－C相 
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0; 
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					//相别
					m_phase      = atoi(Str.Right(Str.GetLength() - k -1));//角度大小

					//回答执行命令正确
					SendErrorMessage(2);

					//读取角度
					//short phase  相别 0 A相 1 B相 2 C相
					ReadThreePhaseAngle(m_generatrix,m_phase,0);
				}
				break;
				
			}
		case 9:
			{  
		    	//读延迟角度大小
				//BEGINS;COMMAND:08:参数1:参数2;ENDS 
				//参数1---母线编号  
				//参数2---哪一相 0－A 1－B 2－C相 
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0; 
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					//相别
					m_phase      = atoi(Str.Right(Str.GetLength() - k -1));//角度大小

					//回答执行命令正确
					SendErrorMessage(2);

					//读取角度
					//short phase  相别 0 A相 1 B相 2 C相
					ReadThreePhaseAngle(m_generatrix,m_phase,1);
				}
				break;
			}
		case 10:
			{   
				//回答执行命令正确
				SendErrorMessage(2);

                ReadRemoteTime();				
				break;
			}
		case 11:
			{
				//要读东西   
				//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
				//                  参数1---标题         参数2---结果            参数3---条件范围
				//                  参数4---命令字       参数5---是否只读相不定  参数6---次数        
				//                  参数7---是否只读一次 参数8---最小值(也当发送数据时用)   参数9--- 最大值 
				//                  参数10--间隔         读写各项测试参数,处理各项参数
				//                  参数11--记录个数
			    //CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals
				BOOL    OnlyReadNot;
				BOOL       OnlyOnce;
				long  m_records = 0;
				
				Str = Str.Right(Str.GetLength() - 11);
				CString  TempStr[11];
				
				int    colum     = 0;
				
				while(Str.Find(':') != -1)
				{
					
					k   =  Str.Find(':');
					
					if(k != -1)
					{
						
						if(colum < 10)
						{
							
							TempStr[colum] =  Str.Left(k);

						}
						
						Str  = Str.Right(Str.GetLength() - k - 1);
						
						SurrenderWindowMessage();//交出window控制权
						colum++;
						
					}
					
				}
				
				TempStr[10] = Str;
				
				//检验两边记录的个数是否相等
				if(atoi(TempStr[4]) == 1)
				{
					//只测试相不定的模块
					m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", TempStr[2] + " AND USER_PHASE=3");
				}
				else
				{
					//所有的模块都测试
					m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", TempStr[2]);
				}

				if(m_records != atol(TempStr[10]))
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(0);
					return;
				}

				if(atoi(TempStr[4]) == 0)
				{   
					//传来的是0，则OnlyReadNot为FALSE
					OnlyReadNot = FALSE;
				}
				else
				{   
					//传来的是1，则OnlyReadNot为TRUE
					OnlyReadNot = TRUE;
				}
				
				if(atoi(TempStr[6]) == 0)
				{   
					//传来的是0，则OnlyOnce为FALSE
					OnlyOnce = FALSE;
				}
				else
				{   
					//传来的是1，则OnlyOnce为TRUE
					OnlyOnce = TRUE;
				}
				
				//回答执行命令正确
				SendErrorMessage(2);

				SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d",TempStr[0],TempStr[1],TempStr[2],atoi(TempStr[3]),OnlyReadNot,atoi(TempStr[5]),OnlyOnce,atoi(TempStr[7]),atoi(TempStr[8]),atoi(TempStr[9]));
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				break;
				
			}
		case 12:
			{
				//执行网上传来的SQL语句  
				//BEGINS;COMMAND:12:参数1;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
				CDataBaseInstance::ExecuteDataBaseSQL(Str);
				
				//回答执行命令正确
				SendErrorMessage(2);

				if(Str.Find("DELETE") != -1 && Str.Find("TB_HALTTIME") == -1)
				{
					//发送信息
					SendContionStr = "BEGINS;MESSAGE:0:远程机器删除数据完毕!;ENDS";
					SendMessage(WM_EVENT, 4, 0);
					
					m_StartRead    = FALSE;
				    
					status("【删除数据完毕】");

					if(Str.Find("TB_USER") != -1)
					{
						//树控件重新刷新一次
						RefreshTree();
					}

				}	
				break;
			} 
		case 13:
			{
				//校时处理  
				//BEGINS;COMMAND:13:年-月-日-时-分-秒;ENDS   
				Str = Str.Right(Str.GetLength() - 11);

				//回答执行命令正确
				SendErrorMessage(2);

				//设置系统时间
				SetLocalTimes(Str);
				break;
			}
		case 14:
			{
				//校时处理  
				//BEGINS;COMMAND:15:年-月-日-时-分-秒;ENDS   
				CString  TimeStr;
				CTime time = CTime::GetCurrentTime();
				TimeStr.Format("BEGINS;COMMAND:15:%d-%d-%d-%d-%d-%d;ENDS",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				
				//回答执行命令正确
				SendErrorMessage(2);

				SetRemoteTime(TimeStr);
				break;
			}  
		case 15:
			{
				//校时处理  
				//BEGINS;COMMAND:15:年-月-日-时-分-秒;ENDS  
				m_TimeStrs = Str.Right(Str.GetLength() - 11);

				//回答执行命令正确
				SendErrorMessage(2);

				break;
			}
		case 16:
			{
				//只读没有读出相别的模块的驻留数据
				//BEGINS;变电站编号;COMMAND:16:参数1:参数2:参数3:参数4:参数5;ENDS 
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				if(m_IsAutoSending)
				{
					SendContionStr = "BEGINS;MESSAGE:0: 定时驻留期间不能驻留读表！;ENDS";
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					SendContionStr = Conditions;
					
					//回答执行命令正确
					SendErrorMessage(2);

                    //只读没有读出相别的模块的驻留数据
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)8,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
				break;
			}
		case 17:
			{
				//只读没有读出相别的模块的正式读表数据
                //BEGINS;变电站编号;COMMAND:17:参数1:参数2:参数3:参数4:参数5;ENDS 
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					//回答执行命令正确
					SendErrorMessage(2);

					SendContionStr = Conditions;

                    //只读没有读出相别的模块的正式读表数据
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)9,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
				break;
			}
		case 18:
			{
				//只读没有读出相别的模块的测试读表数据
                //BEGINS;变电站编号;COMMAND:18:参数1:参数2:参数3:参数4:参数5;ENDS 
                //参数1---用户数据范围(用户数据范围，条件字符串)
				//参数2---记录个数
				//参数3---循环次数
				//参数4---时间间隔
				//参数5---格式为由0和1组成的六位数表示如:111111   
				//第一位表示 累积有功电度     1 － 要读累积有功电度     0 - 不读累积有功电度
				//第二位表示 手拉手总有功电度 1 － 要读手拉手总有功电度 0 - 不读手拉手总有功电度
				//第三位表示 累积无功电度     1 － 要读累积无功电度     0 - 不读累积无功电度
				//第四位表示 手拉手总无功电度 1 － 要读手拉手总无功电度 0 - 不读手拉手总无功电度
				//第五位表示 电流             1 － 要读电流             0 - 不读电流
				//第六位表示 电压             1 － 要读电压             0 - 不读电压
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//检查两边记录的记录数是否一致
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- 数据不一致  1------参数传输错误 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//轮之间时间间隔,默认是30分钟
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- 数据不一致  1------参数传输错误 
						SendErrorMessage(1);
						return;
					}
				
					
					//累积有功电度
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//手拉手总有功电度
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//累积无功电度
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//手拉手总无功电度
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//电流
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//电压
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//尖峰电量
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //峰电量
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//平电量
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//谷电量
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}	
					
					//功率因数
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					//回答执行命令正确
					SendErrorMessage(2);

					SendContionStr = Conditions;
                    //只读没有读出相别的模块的测试读表数据
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)10,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				else
				{
					//0 --- 数据不一致  1------参数传输错误 
					SendErrorMessage(1);
					return;
				}
       			break;
			}
		case 19:
			{
				//执行网上传来的SQL语句,不返回信息  
				//BEGINS;COMMAND:19:参数1;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
				CDataBaseInstance::ExecuteDataBaseSQL(Str);
				break;
			} 
         case 20:
			 {
			   //远程设置手拉手调制信息	
				CDatabase                     dbs;
				int    colum     =              0;
			 	CString  TempStr[5],SqlStr,StrSql;
    			//参数放到数组中
				Str = Str.Right(Str.GetLength() - 11);	
				
				while(Str.Find(':') != -1)
				{
					
					k   =  Str.Find(':');
					
					if(k != -1)
					{
						
						if(colum < 2)
						{
							TempStr[colum] =  Str.Left(k);
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//交出window控制权
						    colum++;
						}
						else
						{
                            break;

						}
				

					}
					
				}
				
				TempStr[2] = Str;
		
				if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
				{	
					//手拉手站代码
					m_handno        =  atoi(TempStr[0]);
					//是否发送调制信号
					m_status        =  atoi(TempStr[2]);

	    			StrSql = "DELETE FROM TB_HAND";
					dbs.ExecuteSQL(StrSql);
					StrSql.Format("INSERT INTO TB_HAND(HAND_NO,HAND_STATIONNAME,HAND_STATUS) VALUES (%d,'%s',%d)",m_handno,TempStr[1],m_status);
					dbs.ExecuteSQL(StrSql);
					dbs.Close();
									
					//设置定时信息
					SetTimersign();
					StrSql = "手拉手供电各项信息远程设置成功！";
					status(StrSql);
                    //发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
					SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StrSql);
					//发送数据
					SendMessage(WM_EVENT, 5, 0);
				
				}
		    	 break;
			 }
		 case 21:
			 {
   
			    break;
			 }
		 case 22:
			 {
				//执行模块号的远程修改  
				//BEGINS;COMMAND:22:原模块号;原相别;新模块号;新相别;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
                CString    TempStr[4];
				BYTE    colum    =  0;
			    
				while(Str.Find(';') != -1)
				{
					k   =  Str.Find(';');
					if(k != -1)
					{
						if(colum < 3)
						{
							TempStr[colum] =  Str.Left(k);
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//交出window控制权
						    colum++;
						}
						else
						{
                            break;
						}

					}

				}
 				
				TempStr[3] = Str;

				//得到旧记录个数
				Str.Format("USER_MODULENO=%s",TempStr[0]);
				long  oldfields =  CDataBaseInstance::GetAllRecordsCount("TB_USER", Str);
			    
				//得到新记录个数
				Str.Format("USER_MODULENO=%s",TempStr[2]);
				long  newfields =  CDataBaseInstance::GetAllRecordsCount("TB_USER", Str);

				if(oldfields < 1 || (newfields > 0 && TempStr[0] != TempStr[2]))
				{ 
				                   
					if(oldfields < 1)
					{
						Str.Format("变电站不存在要修改的模块号%s！远程修改失败！",TempStr[0]);
						//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
						SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS",Str);
						status(Str);
					}
					else
					{
                        Str.Format("变电站已经存在要修改后的模块号%s！远程修改失败！",TempStr[2]);
						//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
						SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS",Str);
						status(Str);
					}

				}
				else
				{
	                Str.Format("UPDATE TB_USER SET USER_MODULENO=%s,USER_PHASE=%d WHERE USER_MODULENO=%s",TempStr[2],atoi(TempStr[3]),TempStr[0]);
                 	CDataBaseInstance::ExecuteDataBaseSQL(Str);
					Str.Format("远程模块号%s成功修改成%s！",TempStr[0],TempStr[2]);
					status(Str);
					//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
					SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",Str);
				}
				//发送数据
				SendMessage(WM_EVENT, 5, 0);
     			break;
			 }
		 case 23:
			 {	
				 //得到DIALOGBAR上的变量,初始化树控件	
				 CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
				 ASSERT_VALID(pMainFrm);	
				 //初始化树控件
				 pMainFrm->m_wndMyDialogBar.Treeinitialize();
				 break;
			 }	
		 case 24:
			 {	
				 //得到远程机表上的记录个数	
				 //格式：BEGINS;COMMAND:24:数据表名:记录个数;ENDS
				 Str     = Str.Right(Str.GetLength() - 11);
				 int k   =  Str.Find(':');
				 CString       m_fileName;

				 if(k != -1)
				 {
					 //停止传送数据
	                 m_StopPassing      = FALSE;

					 m_PassDataFileName =  Str.Left(k);//数据表名
					 m_PassDataRecords  = atoi(Str.Right(Str.GetLength() - k - 1));//记录个数
                     
					 if(m_PassDataRecords > 0)
					 {
						 Str.Format("接收远程表" + m_PassDataFileName + "的数据，记录共%d个,请稍侯...",m_PassDataRecords);
						 //初始化滚动条
						 status(Str);

						 ShowProgressCtrl(TRUE);
						 SetProgressCtrlRange(0,m_PassDataRecords,1);
						 m_CurrentPassPostions =  1;
				         m_fileName.Format("%s%s%s",GetFolder(),m_PassDataFileName,".TXT");
                         
						 CFileFind    finder;
						 if(finder.FindFile(m_fileName) != 0) 
						 { 
							//存在此文件的话则删除此文件
							::DeleteFile(m_fileName);
						 }

						 //激活定时器取数
						 SetTimer(3,1000,NULL);
					 }

				 }
				 break;
			 }
		 case 25:
			 {
				 //格式：BEGINS;COMMAND:25:数据表名:要的记录数位置;ENDS
				 CString   m_fileName;
				 int      m_positions;

				 Str = Str.Right(Str.GetLength() - 11);
				 int k   =  Str.Find(':');
				 
				 if(k != -1)
				 {
				     m_fileName          = Str.Left(k);                             //数据表名
					 m_positions         = atoi(Str.Right(Str.GetLength() - k - 1));//要的记录位置

					 m_fileName          = GetFolder() + m_fileName + ".TXT";
					 CString   m_InfoStr = GetDataLineCString(m_fileName,m_positions);
		
					 //从文本文件中取数
					 if(m_InfoStr.IsEmpty())
					 {	
						 //格式：BEGINS;COMMAND:26:数据信息;ENDS
			             SendContionStr.Format("BEGINS;COMMAND:26:%s;ENDS","NOFINDDATA?OK!");
					 }
					 else
					 {	
						 //格式：BEGINS;COMMAND:26:数据信息;ENDS
			             SendContionStr.Format("BEGINS;COMMAND:26:%s;ENDS",m_InfoStr);
					 } 

					 //发送数据
			         SendMessage(WM_EVENT, 5, 0); 
					 
					 //如果是拔号的话
				//	 if(m_sendkind == 1)
				//	 {
				//		 Sleep(500);
				//	 }
					
					 Str.Format("发送表%s第%d条记录完毕...",Str.Left(k),m_positions);
					 status(Str);
					 
				 }
         		 break;
			 }
	   case 26:
		   {    
				 //格式：BEGINS;COMMAND:26:数据信息;ENDS
				 Str = Str.Right(Str.GetLength() - 11);
				 
				 //错误的次数赋为0
	             m_GetErrors    =   0;

				 if(Str.Find("NOFINDDATA?OK!") != -1)
				 {	

					 m_StartRead = FALSE;
					 status("                            ");
					 ShowProgressCtrl(FALSE);//没有数据
					 KillTimer(3);

				 }
				 else
				 {	 
					
					 CString             m_fileName;
					 m_fileName.Format("%s%s%s",GetFolder(),m_PassDataFileName,".TXT");
					
				     //移动滚动条
					 SetProgressCtrlSetIt();	
						 
					 //写入文本文件
					 FILE *text;
					 if((text = fopen(m_fileName,"a")) != NULL)
					 {
						 fputs(Str + "\r\n",text);
						 fclose(text);
					 }
						 
					 //显示状态栏信息
					 Str.Format("接收远程表" + m_PassDataFileName + "数据［%d－%d］,请稍侯...",m_CurrentPassPostions,m_PassDataRecords);
					 status(Str);
					 
					 m_CurrentPassPostions ++;
					 KillTimer(3);
					 OnTimer(3);
													
					 //如果个数够了的话
					 if(m_CurrentPassPostions > m_PassDataRecords)
					 { 	
						 //停止传送数据
	                     m_StopPassing = FALSE;
						 KillTimer(3);	
					    
						 status("             ");
						 ShowProgressCtrl(FALSE);
						 
						 SurrenderWindowMessage();

						 m_StartRead  =  FALSE; 
						 
						 if(!AppInfo::Instance().m_WhichKind)
						 {
							 
							 if(MessageBox("显示远程接收来的所有数据吗？","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
							 {
								 //显示接收来的数据
								 AppearAccept(m_PassDataFileName);
							 }

						 }
                        
						 //询问是否要重加入数据
						 AskIfAddData(m_PassDataFileName,m_fileName);
                        
					 }
					 else
					 {

						 if(!m_StopPassing)
						 {
							 //激活定时器取数
							 SetTimer(3,1000,NULL);
						 }
						 else
						 {
							 status("【接收数据已被中止】");
						 }

					 }

				 }
         		 break;
			 }
	   case 27:
		   {
			   //远程查询对方的驻留设置
			   if(!m_IsAutoSending)
			   {
				   SendContionStr = "BEGINS;MESSAGE:0:对方机器还没有设置定时发驻留读表!;ENDS";
			   }
			   else
			   {  
				   SendContionStr.Format("BEGINS;MESSAGE:0:对方机器定时发驻留读表设置%s！;ENDS",m_DingShiString);
			   }
			   
			   //发送信息
			   SendMessage(WM_EVENT, 4, 0);
               break;
		   }
	   case 28:
		   {
			   //告诉远程机断开 
			   //格式：BEGINS;COMMAND:28:数据信息;ENDS			 
			   Str = Str.Right(Str.GetLength() - 11);
			   Str.TrimLeft();
			   Str.TrimRight();
			   
			   //断开了，接收数据标志赋为FALSE
			   if(ReadMeterThread == NULL)
			   {
				   m_IfChangeData = FALSE;
			   }
			   
			   switch(m_sendkind)
			   {
			   case 0:
				   {
					   
					   break;
				   }
			   case 1:
				   {
					   //关闭猫
					   if(Str.Find("^CLOSED^MODEM?^OK!") != -1)
					   {
						   
						   m_IsDialConnectting =       FALSE;
											   
						   if(AppInfo::Instance().m_WhichKind)//  -TRUE   变电站版本 -FALSE  电局版
						   {
							   
							   SelectSendString(m_sendkind,"+++",FALSE,FALSE,FALSE);     //而且收到连续三个+++, 之后3秒钟又没有任何数据, Modem就进入命令模式, 可以利用AT命令集进行配置
							   Sleep(3200);
							   SelectSendString(m_sendkind,"ATH0\r\n",FALSE,FALSE,FALSE);//断开电话连接
							   Sleep(500);	
							   SelectSendString(m_sendkind,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM复位（Reset），重新读取预存第0组的设定参数值。
							   Sleep(500);
							   
							   AutoAnswer(FALSE);	//ADD 20041221自动应答
							   
						   }
						   
						   status("【拔号网络已断开】");
						   ReceiveByteArray.RemoveAll();
						   m_Com.GetInput();
					   }
					   break;
				   }
			   case 2:
				   {
			
					   if(Str.Find("^CLOSED^INTERNET?^OK!")!= -1)
					   {	
						   m_IsConnect   =    FALSE;
						   SendContionStr = "BEGINS;MESSAGE:0:对方机器TCP／IP网络连接已经断开！;ENDS";
						   SendMessage(WM_EVENT, 4, 0);
						   Sleep(100);
						   OnCloseWinsock();
					   }
					   break;
				   }  
				   
				   //让其隐藏
				   OperationAnimation(FALSE);
				   StatusStr           =          "";
				   //如果和长沙在通讯
				   Received            =           0;	
				   SurrenderWindowMessage();
			   }
			   
			   break;
	  
		   }
	   case 29:
		   {
  			    //有一个定时器发驻留用
				if(m_IsAutoSending)
				{
					//显示状态栏信息
					SendContionStr.Format("BEGINS;MESSAGE:0: 远程驻留原已设定，\r\n请先取消再重新设置驻留！;ENDS");
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				//分解参数
                int    colum  =      0;
			 	CString  SqlStr,StrSql,str;
    			//参数放到数组中
				Str = Str.Right(Str.GetLength() - 11);	
						
				while(Str.Find(';') != -1)
				{
					
					k   =  Str.Find(';');
					
					if(k != -1)
					{
						
						if(colum < 109)
						{
							m_parameter[colum] =  atoi(Str.Left(k));
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//交出window控制权
						    colum++;
						}
						else
						{
                            break;

						}
				

					}
					
				}
				
				m_parameter[109]  = atoi(Str);

				//写入居民表、大用户表、变台表等表的参数
				WriteToAllAmeterParameter();

				//14种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压
			    //定时发驻留,定时读表标志
				for(int i = 0; i < 15; i++)
				{
					m_TimeSetLabel[i]  = FALSE;  
				}
	
				//有功电度
				if(m_parameter[93] > 0)
				{
					if(m_parameter[93] > 0  && m_parameter[94] > 0)
					{
						m_TimeSetLabel[0] = TRUE;
						m_TimeSetLabel[1] = TRUE;    //0－有功电度-单边累加值
					}
					else
					{
						m_TimeSetLabel[0] = TRUE;
					}
				}	
	
				//无功电度
				if(m_parameter[95] > 0)
				{
					if(m_parameter[95] > 0  && m_parameter[96] > 0)
					{
						m_TimeSetLabel[2] = TRUE;
						m_TimeSetLabel[3] = TRUE;    //0－无功电度-单边累加值
					}
					else
					{
						m_TimeSetLabel[2] = TRUE;   
					}
				}	
					
				//4－A相电流 5－B相电流 6－C相电流
				if(m_parameter[97] > 0)
				{
					m_TimeSetLabel[4] = TRUE;
					m_TimeSetLabel[5] = TRUE;
					m_TimeSetLabel[6] = TRUE;
				}

				//7－A相电压 8－B相电压 9－C相电压
				if(m_parameter[98] > 0)
				{
					m_TimeSetLabel[7] = TRUE;
					m_TimeSetLabel[8] = TRUE;
					m_TimeSetLabel[9] = TRUE;
				}

				//尖峰电量
				if(m_parameter[99] > 0)
				{
					m_TimeSetLabel[10] = TRUE;
				}
				
				//峰电量
				if(m_parameter[100] > 0)
				{
					m_TimeSetLabel[11] = TRUE;
				}
				
				//平电量
				if(m_parameter[101] > 0)
				{
					m_TimeSetLabel[12] = TRUE;
				}
				
				//谷电量
				if(m_parameter[102] > 0)
				{
					m_TimeSetLabel[13] = TRUE;
				}
				
				//功率因数	
				if(m_parameter[103] > 0)
				{
					m_TimeSetLabel[14] = TRUE;
				}
					
				//然后运行自动发驻留自动读数据
				//行号起始为0
				m_ListRows      =      0;
				//次数为0
				m_times         =      1;
				//自动发信息 
				m_IsAutoSending =   TRUE;	
				//提示信息
				SendContionStr.Format("BEGINS;MESSAGE:0:远程自动发驻留自动读数据设置成功!\r\n%s;ENDS",m_statusstr);
				//发送返回信息
				SendMessage(WM_EVENT, 4, 0);
				//停止执行此操作
				m_StartRead     = FALSE;  
				
				//得到发送协议的种类
	            SendMessage(WM_EVENT, 10, 0);

    			//时间
				CTime timet = CTime::GetCurrentTime();
				str.Format("【%4d-%02d-%02d %02d:%02d:%02d】设置定时驻留读表:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
			   	WriteToLog(str);

				//取消10分钟检查一次检查
				KillTimer(1);
				ShowDingShiButton(TRUE);                   //定时按钮置为TRUE	
	            
				m_ReadModuleTimes = 0;//读表次数设为0	
				//发驻留次数
	            m_SendGarrisonTimes=     0;
				m_parameter[105]  =     30;//间隔强制设置成30分钟
                str.Format("【定%d时驻留,间隔%d分钟,连读%d次,以后%d时连读%d天】",m_parameter[104],m_parameter[105],m_parameter[106],m_parameter[107],m_parameter[108]);
			    status(str);
				
				//为22协议加的，半点或整点才可用,10分钟检测一次
				//10分钟检测一次
				m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
				
				SetTimer(1,m_SettimerValues,NULL);//设置定时器,10分钟检查一次
				break;
								
			}
	   case 30:
		   {
			   //远程查询对方的驻留设置
			   if(!m_IsAutoSending)
			   {
				   SendContionStr = "BEGINS;MESSAGE:0:对方机器还没有设置定时发驻留读表!;ENDS";
				   //发送信息
				   SendMessage(WM_EVENT, 4, 0);
			   }
			   else
			   {
				   
				   CString ConStr,str;
				   ConStr  = "BEGINS;COMMAND:31:";
				   
				   for(int i = 0; i < 110; i ++)
				   {	
					   //初始化发驻留读表用的110个参数
					   str.Format("%d",m_parameter[i]);
					   ConStr = ConStr + str + ";";
				   }
				   
				   //参数个数
				   ConStr = ConStr + "ENDS";
				   SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE); 
			   }
			   break;
		   } 
	   case 31:
		   {
			   //分解参数
			   int    colum  =      0;
			   CString  SqlStr,StrSql,str;
			   //参数放到数组中
			   Str = Str.Right(Str.GetLength() - 11);	
			   
			   while(Str.Find(';') != -1)
			   {
				   
				   k   =  Str.Find(';');
				   
				   if(k != -1)
				   {
					   
					   if(colum < 109)
					   {
						   m_parameter[colum] =  atoi(Str.Left(k));
						   Str  = Str.Right(Str.GetLength() - k - 1);
						   SurrenderWindowMessage();//交出window控制权
						   colum++;
					   }
					   else
					   {
						   break;
						   
					   }
					   
					   
				   }
				   
			   }
			   
			   m_parameter[109] = atoi(Str);
			   
			   //写入居民表、大用户表、变台表等表的参数
			   WriteToAllAmeterParameter(); 
			   m_zhuliukinds       =     0;//0 按表计种类下驻留 1 按日期下驻留

			   if(!AppInfo::Instance().m_WhichKind)
			   {
					MessageBox(DecodeParameter(TRUE),"对方定时读表参数设置如下:");
			   }
			   break;
		   }
	   case 32:
		   { 
			   //参数放到数组中
			   Str = Str.Right(Str.GetLength() - 11);
			   MessageBox(Str," ",MB_OK|MB_ICONWARNING);
			   //断开拔号连接
			   DisConnect(1);  
			   break;
		   } 
	   case 33:
		   { 
			   //设置驻留时间,参数放到数组中
			   Str = Str.Right(Str.GetLength() - 11);
			   m_saveyears = atoi(Str);
			   SendContionStr.Format("BEGINS;MESSAGE:0:对方机器设置数据保存时间为%d年!;ENDS",m_saveyears);
			   SendMessage(WM_EVENT, 4, 0);
			   break;
		   } 
	   case 34:
		   { 
			   //查询驻留时间
			   SendContionStr.Format("BEGINS;MESSAGE:0:对方机器设置数据保存时间为%d年!;ENDS",m_saveyears);
			   SendMessage(WM_EVENT, 4, 0);
			   break;
		   }
	   case 35:
		   {
			   //执行网上传来的SQL语句  
			   //BEGINS;COMMAND:35:参数1;ENDS   
			   Str = Str.Right(Str.GetLength() - 11);
               Str = "UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE " + Str;
			   CDataBaseInstance::ExecuteDataBaseSQL(Str);
			   SendContionStr = "BEGINS;MESSAGE:0:远程机器销户成功！;ENDS";
			   SendMessage(WM_EVENT, 4, 0);
			   m_StartRead    = FALSE;
			   status("【销户成功】");
			   break;
		   }
       case 36:
		   {
			   //执行网上传来的SQL语句  
			   //BEGINS;COMMAND:36:参数1;ENDS   
			   Str = Str.Right(Str.GetLength() - 11);
               Str = "UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE " + Str;
			   CDataBaseInstance::ExecuteDataBaseSQL(Str);
			   SendContionStr =  "BEGINS;MESSAGE:0:远程机器取消销户成功！;ENDS";
			   SendMessage(WM_EVENT, 4, 0);
			   m_StartRead    =  FALSE;
			   status("【取消销户成功】");
			   break;
		   }  
	   case 37:
		   {
			   //执行动态监控批令，查是否和自动驻留冲突
			   BOOL m_CanReading  =        TRUE;
			   BYTE        m_day  =           0;
			   
			   Str         = Str.Right(Str.GetLength() - 11);
			   int    k    =  Str.Find(':');
			   
			   if(k != -1)
			   {	
				  
				   //范围
				   m_DynaicCheckStrCondition = Str.Left(k); 
				
				   Str  = Str.Right(Str.GetLength() - k - 1);
     			   
				   //记录个数
				   k    =  Str.Find(':');
				   
				   if(k != -1)
				   {
					   //检查两边记录的记录数是否一致
					   if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", m_DynaicCheckStrCondition))
					   {
						   //0 --- 数据不一致  1------参数传输错误 
						   SendErrorMessage(0);
						   return;
					   }		
					   
					   Str  =  Str.Right(Str.GetLength() - k - 1);
					   k    =  Str.Find(':');
					   
					   if(k != -1)
					   {
                           //监视时间点
						   m_shikedian = atoi(Str.Left(k));
						   
						   Str  =  Str.Right(Str.GetLength() - k - 1);
						   k    =  Str.Find(':');
						   
						   if(k != -1)
						   {
							   //读多长时间
							   m_readRangle = atoi(Str.Left(k));

							    Str  =  Str.Right(Str.GetLength() - k - 1);
						        k    =  Str.Find(':');

								if(k != -1)
								{
									//读表次数
									m_readchecktimes   =  atoi(Str.Left(k));
									Str                =  Str.Right(Str.GetLength() - k - 1);
                                    
									//累积有功电度
									if(atoi(Str.Left(1)) == 1)
									{
										m_SetLabel[0] = TRUE;
									}
									
									//手拉手总有功电度
									if(atoi(Str.Mid(1,1)) == 1)
									{
										m_SetLabel[1] = TRUE;
									}
									
									//累积无功电度
									if(atoi(Str.Mid(2,1)) == 1)
									{
										m_SetLabel[2] = TRUE;
									}
									
									//手拉手总无功电度
									if(atoi(Str.Mid(3,1)) == 1)
									{
										m_SetLabel[3] = TRUE;
									}
									
									//电流
									if(atoi(Str.Mid(4,1)) == 1)
									{
										m_SetLabel[4] = TRUE;
										m_SetLabel[5] = TRUE;
										m_SetLabel[6] = TRUE;
									}
									
									//电压
									if(atoi(Str.Mid(5,1)) == 1)
									{
										m_SetLabel[7] = TRUE;
										m_SetLabel[8] = TRUE;
										m_SetLabel[9] = TRUE;
									}
									
									//尖峰电量
									if(atoi(Str.Mid(6,1)) == 1)
									{
										m_SetLabel[10] = TRUE;
									}
									
									//峰电量
									if(atoi(Str.Mid(7,1)) == 1)
									{
										m_SetLabel[11] = TRUE;
									} 
									
									//平电量
									if(atoi(Str.Mid(8,1)) == 1)
									{
										m_SetLabel[12] = TRUE;
									}
									
									//谷电量
									if(atoi(Str.Mid(9,1)) == 1)
									{
										m_SetLabel[13] = TRUE;
									}
									
									//功率因数
									if(atoi(Str.Mid(10,1)) == 1)
									{
										m_SetLabel[14] = TRUE;
									}
									
									m_CheckReading     =        TRUE;//监视读表
								}

						   }
						   
					   }


				   }

			   }

			   if(!m_CheckReading)
			   {
				   SendContionStr =  "BEGINS;MESSAGE:0:远程机器接收指令错误！;ENDS";
				   SendMessage(WM_EVENT, 4, 0);
				   return;
			   }
			 

			   //如果在驻留期间
			   if(m_IsAutoSending)
			   {					
				   
				   CByteArray          m_TimeArray;//读表日期数组
				   
				   for(int i = 0; i < 31; i ++)
				   {
					   
					   //提出读表日期
					   if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
					   {
						   m_TimeArray.Add(i+1);
					   }
					   
				   }
				   
				   //如果没有读表日期则退出
				   if(m_TimeArray.GetSize() > 0)
				   {	
					   //检测各种时间	
					   long m_seconds = (m_readRangle * m_readchecktimes)*3600;//读多长时间
					   CTimeSpan                                ts;//时间间隙//时间
					   ts                   =            m_seconds;
					   CTime           timet = CTime::GetCurrentTime();
					   CTime            m_CurrentTime2 = timet + ts;//定义时间变量
					   BYTE        m_day1 = timet.GetDay();
					   BYTE        m_day2 = m_CurrentTime2.GetDay();
					   
					   if(m_day2 >= m_day1)
					   {
						   
						   for(int i = 0;i < m_TimeArray.GetSize();i ++)
						   {
							   
							   if(m_TimeArray[i] >= m_day1 && m_TimeArray[i] <= m_day2)
							   {
								   //记录冲突的
								   m_day = m_TimeArray[i];
								   m_CanReading  = FALSE;
								   break;
							   }
							   
						   }
						   
						   
					   }
					   else
					   {
						   //跨月
						   for(int i = 0;i < m_TimeArray.GetSize();i ++)
						   {
							   
							   if(m_TimeArray[i] <= m_day1 || m_TimeArray[i] >= m_day2)
							   {
								   //记录冲突的
								   m_day = m_TimeArray[i];
								   m_CanReading  = FALSE;
								   break;
							   }
							   
						   }
						   
						   
					   }
					   
				   }
				   
			   }
			   
			   if(!m_CanReading)
			   {
				   //对驻留读表有影响
				   SendContionStr.Format("远程机器动态监视读表成功！但此操作将影响%d日定时驻留读表！！\r\n如果执行有可能导制%d日驻留读不上数！按［STOP按钮停止］",m_day,m_day);
			   }
			   else
			   {
				   SendContionStr =  "BEGINS;MESSAGE:0:远程机器动态监视读表成功！;ENDS";
			   }  

			   SendMessage(WM_EVENT, 4, 0);
			 		 
			   //读此范围的模块
			   ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
			   ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
			   break;
		   
		   }

	   }
   
    }

}


//读写各项测试参数,处理各项参数
//CString title          列标题
//CString Result         结论
//CString ConStr         条件范围
//BYTE    orders         命令关键字
//BOOL    OnlyReadNot    TRUE  只读没有测试出相的模块
//                       FALSE 反之
//int     times          读每个模块的次数
//BOOL    OnlyOnce TRUE  好多表共用一个模块时只测试一次   FALSE 每个表都测试一次
//int     MaxIValue      最大值(为写参数时用)
//int     MinIValue      最小值
//int     intervals      间  隔
void CIFRMView::DisposeModuleParameter(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals)
{
	
	BYTE    LineNo           =        0;//线  号
	BYTE    PhaseNo          =        0;//相  别
	BYTE    StationNo        =        0;//手拉手变电站编码
	BYTE    MotherLine       =        0;//母线编号
	long    ModuleNo         =        0;//模块号
	long    Records          =        0;//记表项数
	double  CurrentValue     =        0;//开始读模块数据
	long    GetModuleNo      =        0;//中间变量
	long    fields           =        0;//记录数
	BYTE    m_AMMETERKIND    =        0;//表计种类
	BYTE    m_SUPPLYMODED    =        0;//供电方式 0-单边供电 1－站手拉手 2-线手拉手供电
	BYTE    m_PROTOCOL       =        0;//读表协议 71-73 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
    BYTE    m_SendAngle      =        0;//发送的角度 2005-04-07加 
	float   m_BeginValue     =        0;//电表初值 
	BYTE    BakMotherLine    =        0;//备用母线编号
	BYTE    BakLineNo        =        0;//备用线  号

	CString           m_ReadAmmeterType;//读表类型
 	
	m_StartRead              =     TRUE;//读停标志  
	
	CString   strSql,strValue,PhaseInfo;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	m_ListRows               =        0; 
	CString  m_ReadErrorStr,CondtionStr;
	
	//条件范围
	ConStr.TrimLeft();
	ConStr.TrimRight();
	
	//删除原来的数
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13列
	
	StatusStr.Format("正在%s，请稍侯...",Title);
    SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(TRUE);

	//如果DIALOGBAR可见的话则隐藏
	SendMessage(WM_EVENT, 6, 0);	
	
	//打开数据库
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
		
		//写列表标题
		SendMessage(WM_EVENT, 2, 0);
		
		//如果是想读全部数据
		if(ConStr == "ALL")
		{
            //只读没有测出相别的
			if(OnlyReadNot)
			{
				//范围条件
				CondtionStr = " USER_PHASE=3 AND USER_AMMETERKIND<=5";
				//记录个数
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//查询语句
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE USER_PHASE=3  AND USER_AMMETERKIND<=5";
			}
			else
			{
				//范围条件
				CondtionStr = " USER_AMMETERKIND<=5";
				//记录个数
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//查询语句
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE USER_AMMETERKIND<=5";
			}

		}
		else
		{
            
			//只读部份数据
			if(OnlyReadNot)//只读没有测出相别的
			{
				//范围条件
				CondtionStr = "(" + ConStr + ")  AND USER_PHASE=3  AND USER_AMMETERKIND<=5";
				//记录个数
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);  
				//查询语句       序号,读表类型,用户名称,用户编号,地址,模块号,电表号,线路名称,母线-线号-相别,变台号,类型,读表值,读表时间
    			strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE " + CondtionStr;
			}
			else
			{	
				//范围条件
				CondtionStr = "(" + ConStr + ") AND USER_AMMETERKIND<=5";
				//记录个数
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//查询语句
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE " + CondtionStr;
			}

		}

		//未读出数据查询语句
		m_ReadErrorStr = strSql   + " AND USER_READLABEL='NNNNNNNNNNNNNNN'";//15个N表示没有读出

		rs.Open(CRecordset::forwardOnly,strSql);
		//得到字段个数
		short nFields = rs.GetODBCFieldCount();
		rs.Close();
		
		//如果没有记录的话
		if(fields < 1)
		{
            db.Close();
		
			//传输结论
		//	SendContionStr = "BEGINS;MESSAGE:0:没有满足条件的数据或线、站总表直接从485口读数,不能处理!!!;ENDS";
		//	SendMessage(WM_EVENT, 4, 0);
			
			//状态栏信息
			StatusStr = "没有满足条件的数据或线、站总表直接从485口读数,不能处理!!!";
            SendMessage(WM_EVENT, 1, 0);
	
            //隐藏滚动条
			ShowProgressCtrl(FALSE);
			m_StartRead   =   FALSE;
	
			return;
		}
		
		//满足条件的赋值为-1,运行SQL语句,在原库中作标记,设置初始化标志
		strSql.Format("UPDATE TB_USER SET USER_READLABEL='NNNNNNNNNNNNNNN' WHERE %s",CondtionStr);
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);

		//滚动条范围
		SetProgressCtrlRange(0, fields,1);
			
		//循环次数
		for(int m_Current = MinIValue;m_Current <= MaxIValue;m_Current = m_Current + intervals)
		{
			
			//传送的值
			m_PassValue         = m_Current;
			
			//每个读times次
			for(int m_ReadTimes = 0;m_ReadTimes < times;m_ReadTimes ++)
			{
			
				//得到没有读出数据标志的记录数
				fields     = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr + " AND USER_READLABEL='NNNNNNNNNNNNNNN'");  
				
				if(fields <= 0)
				{
					//没有可读的记录了
					m_ReadTimes = times;
				    //没有满足条件的记录的话
					continue;
				}
				
			    //打开数据库数据
				rs.Open(CRecordset::forwardOnly,m_ReadErrorStr);

				//读用户信息
				for(int j = 0;j < fields; j ++)
				{
					
					//赋原始值
					CurrentValue = -1;
					
					//如果按了停止按钮
					if(!m_StartRead)
					{	
						
						if(rs.IsOpen())
						{
							rs.Close();
						}
						
						if(db.IsOpen())
						{
							db.Close();
						}
											
						//传输结论
						//SendContionStr = "BEGINS;MESSAGE:0:操作中途被停止!;ENDS";
						//SendMessage(WM_EVENT, 4, 0);
						
						//显示状态栏信息
						StatusStr = "【读数中途被停止】";
						SendMessage(WM_EVENT, 1, 0);
					    
						//隐藏滚动条
						ShowProgressCtrl(FALSE);
						return;
					}
					
					//序号
					strValue.Format("%d",m_ListRows + 1);
					m_StrArray[0].Format("%5s",strValue);
					
					//提示指令
					m_StrArray[1] =  Title;
					
					//字段数
					int i;
					for( i = 0; i < nFields; i++)
					{
						rs.GetFieldValue(int(i),strValue);
						strValue.TrimLeft();
						strValue.TrimRight();
						
						switch(i)
						{
						case 0:
							{
								//姓名
								m_StrArray[2] = strValue;
								break;
							}
						case 1:
							{ 
								//用户编号  
								m_StrArray[3] = strValue;
								break;
							}
						case 2:
							{ 
								//住址  
								m_StrArray[4] = strValue;
								break;
							}
						case 3:
							{  
								//模块号
								m_StrArray[5].Format("%8s",strValue);
								ModuleNo = atol(strValue);
								break;
							}
						case 4:
							{  
								//电表号
								m_StrArray[6].Format("%8s",strValue);
								break;
							}
						case 5:
							{  
								//母线号
								MotherLine = atoi(strValue); //add by 2004.10.21
								break;
							}
						case 6:
							{	
								//线路名称
								m_StrArray[7] = strValue;
								break;
							}
						case 7:
							{
								//线路编号
								LineNo = atoi(strValue);
								break;
							}
						case 8:
							{
								CString PhaseStr;
								//相
								switch(atoi(strValue))
								{
								case 0:
									{
										PhaseStr = "A相";
										PhaseNo = 0;
										break;
									}
								case 1:
									{
										PhaseStr = "B相";
										PhaseNo = 1;
										break;
									}
								case 2:
									{
										PhaseStr = "C相";
										PhaseNo = 2;
										break;
									}
								default:
									{
										PhaseStr = "未知";
										PhaseNo = atoi(strValue);
										break;
									}
								}
								m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
							
								//保存相信息
								if(PhaseNo < 3)
								{
								   PhaseInfo = m_StrArray[8];
								}
								break;
							}
						case 9:
							{
								//变台名称
								m_StrArray[9].Format("%s",strValue);
								break;
							}
						case 10:
							{
								//手拉手电站码
								StationNo    = m_handno;
								//电表初值
								m_BeginValue = float(atof(strValue));
								break;
							}
						case 11:
							{
								//表计种类
								m_AMMETERKIND = atoi(strValue);
								break;
							}
						case 12:
							{
								//供电方式
								m_SUPPLYMODED = atoi(strValue);
								break;
							}	
						case 13:
							{
								//读表协议 31-39或71-79 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
								m_PROTOCOL = atoi(strValue);

								if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
								{
									//转换指令
									switch(orders)
									{
									case 0xf4:
										{
											//用电状态
											if(ModuleNo%100 < 12)
											{
												//脉冲表
											}
											else
											{
												//485表
											}
											
											continue;
											break;
										}
									case 0x3c:
										{
										

											//停电次数
											if(ModuleNo%100 < 12)
											{
												//脉冲表	
												if(m_PROTOCOL == 22)
												{
													orders = 0x02;
												}
											
											}
											else
											{
												//485表
												if(m_PROTOCOL == 22)
												{
													orders = 0x79;
												}
												else
												{
													orders = 0x02;
												}
												
											}
											
											break;
										}
									case 0xf6:
										{
											//送电
											if(ModuleNo%100 < 12)
											{
												//脉冲表
												if(m_PROTOCOL == 22)
												{
													orders = 0x05;
												}
												else
												{
													orders = 0x01;
												}
											}
											else
											{
												//485表
												if(m_PROTOCOL == 22)
												{
													orders = 0x73;
												}
												else
												{
													orders = 0x04;
												}

											}
											
											break;
										}
									case 0xf8:
										{
											//停电
											if(ModuleNo%100 < 12)
											{
												
												if(m_PROTOCOL == 22)
												{
													//脉冲表
													orders = 0x03;
												}
												else
												{
													orders = 0x00;
												}

											}
											else
											{
												//485表	
												if(m_PROTOCOL == 22)
												{
													orders = 0x70;
												}
												else
												{
													orders = 0x05;
												}
												
											}
											
                                            break;
										} 
									case 0x02:
										{
											//测相读有功
											if(ModuleNo%100 < 12)
											{
												//脉冲表
												if(m_PROTOCOL == 22)
												{
													orders = 0x07;
												}
												else
												{
													orders = 0x03;
												}

											}
											else
											{
												//485表	
												if(m_PROTOCOL == 22)
												{
													orders = 0x5f;
												}
												else
												{
													orders = 0x1f;
												}

											}
											
											break;
										}
									case 0x48:
										{
											//DSP电流
											if(ModuleNo%100 < 12)
											{
												//脉冲表
												
											}
											else
											{
												//485表
												
											}
											continue;
											
											break;
										}
									case 0x44:
										{
											//读电流值
											if(ModuleNo%100 < 12)
											{
												//脉冲表
												
											}
											else
											{
												//485表
												
											}

											continue;
											
											break;
										}
									}
									
								}

								m_StrArray[8] = m_StrArray[8] + strValue + "]";
								break;
							}	
						case 14:
							{
								//读表的角度
								//m_SendAngle = atoi(strValue);
								//是否是星角连接,偏移角度,星角为30度
								if(IsDyConnect(m_StrArray[9]))
								{
									m_SendAngle = 6;//atoi(strValue); 5度一个档次
								}
								else
								{
									m_SendAngle = 0;
								}							
								break;
							}
						case 15:
							{
								//读表的类型
								strValue.TrimLeft();
								strValue.TrimRight();
								m_ReadAmmeterType = strValue;
								break;
							}	
						case 16:
							{
								//备用母线编号
								BakMotherLine = atoi(strValue);
								break;
							}	
						case 17:
							{
								//备用出线号
								BakLineNo     = atoi(strValue);
								break;
							}
							
						 }
							
					   }
						
						//好多表共用一个模块时，只测试一次时
						if(OnlyOnce == TRUE && abs(ModuleNo-GetModuleNo)<=16 &&  GetModuleNo > 0)
						{
							//好多表共用一个模块时，只测试一次时
							GetModuleNo    = ModuleNo;
							//提取线路、相信息
							m_StrArray[8]  = PhaseInfo;
							m_StrArray[11] = "";
						}
						
						//显示状态栏信息
						StatusStr.Format("正在%s[%d-%d],[%d],完成%.2f％,请稍侯...",Title,fields,m_ListRows + 1,ModuleNo,float(m_ListRows)*100/fields);
						SendMessage(WM_EVENT, 1, 0);
						
						//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
						//SendMessage(WM_EVENT, 4, 0);//发送数据
						
						//模块号不相等的话
						if(GetModuleNo != ModuleNo)
						{
							
							//不知道是哪相的话,每个相都测试一次
							if(PhaseNo > 2)
							{
								
								//相循环
								for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
								{
									
									//如果按了停止按钮
									if(m_StartRead == FALSE)
									{
										break;
									}
									
									switch(PhaseNo)
									{
									case 0:
										{	
											strValue.Format("正在%s,测试模块号(%d)A相,请稍侯...",m_StrArray[1],ModuleNo);
											break;
										}
									case 1:
										{
											strValue.Format("正在%s,测试模块号(%d)B相,请稍侯...",m_StrArray[1],ModuleNo);
											break;
										}
									case 2:
										{
											strValue.Format("正在%s,测试模块号(%d)C相,请稍侯...",m_StrArray[1],ModuleNo);
											break;
										}
									}
									
									//显示状态栏信息
									StatusStr =        strValue;
									SendMessage(WM_EVENT, 1, 0);
									
									if(m_SendAngle == 0)
									{
										CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine/*母线*/,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									else
									{
										//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
										CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine/*母线*/,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}

									if(m_PROTOCOL != 22)
									{
										//停电或送电,31,32,71,72协议回的数应为333333.33
										if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
										{
											CurrentValue = -1;
										}										
									}
									else
									{
										//22协议回的数为3.2
										if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
										{
											CurrentValue = -1;
										}
									}

									//如果是线手拉手，再读一次数据
									if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
									{

										if(m_SendAngle == 0)
										{
											CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
										}
										else
										{
											//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
											CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
										}
										
										if(m_PROTOCOL != 22)
										{

											//停电或送电,31,32,71,72协议回的数应为333333.33
											if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
											{
												
												CurrentValue = -1;

											}	
											
										}
										else
										{
											//22协议回的数为3.2
											if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
											{
												
												CurrentValue = -1;
											
											}

										}
										
										//如果在备用母线和备用出线上读出来
										if(int(CurrentValue) != -1)
										{
											MotherLine =   BakMotherLine;
											LineNo     =       BakLineNo;
										}
										
									}
									
									//如果读出的值大于或等于0		//if(CurrentValue >= 0)
									if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
									{
										
										//相
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A相",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B相",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C相",m_PROTOCOL);
												break;
											}
										}

										//保存相信息
										PhaseInfo = m_StrArray[8];
										
										//保存入数据库
										strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",PhaseNo,ModuleNo - 16,ModuleNo + 16);
										//运行SQL语句
										CDataBaseInstance::ExecuteDataBaseSQL(strValue); 

										//发送SQL语句,写进远程机器
									    //SendContionStr.Format("BEGINS;COMMAND:12:%s;ENDS",strValue);
									    //SendMessage(WM_EVENT, 4, 0);
										break;
									}
									
								}
								
								
							}
							else
							{
								//知道该相就读该相
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*母线*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
								
								SurrenderWindowMessage();
							
								if(m_PROTOCOL != 22)
								{
									//停电或送电,31,32,71,72协议回的数应为333333.33
									if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
									{
										CurrentValue = -1;
									}										
								}
								else
								{
									//22协议回的数为3.2
									if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
									{
										CurrentValue = -1;
									}
								}
								
								//如果是线手拉手，再读一次数据
								if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
								{

									if(m_SendAngle == 0)
									{
										CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									else
									{
										//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
										CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									
									if(m_PROTOCOL == 22)
									{
										//22协议回的数为3.2
										if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
										{
											CurrentValue = -1;
										}
																	
									}
									else if(m_PROTOCOL == 61 || m_PROTOCOL == 62 )
									{
										//停电或送电,31,32,71,72协议回的数应为333333.33
										if((orders == 0x04 || orders == 0x05 || orders == 0x01 || orders == 0x00)  && int(CurrentValue*100)!=32)
										{
											CurrentValue = -1;
										}		
									
									}
									else
									{
										//停电或送电,31,32,71,72协议回的数应为333333.33
										if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
										{
											CurrentValue = -1;
										}	


									}

									//如果在备用母线和备用出线上读出来
									if(int(CurrentValue) != -1)
									{
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A相",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B相",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C相",m_PROTOCOL);
												break;
											}
										}
										
										MotherLine = BakMotherLine;
										LineNo     =     BakLineNo;
									}
									
								}
								
							}
								
							//根据得到的值下结论
							if(int(CurrentValue) == -1)
							{	
								//用户库下滑一个记录
								rs.MoveNext();
								//继续向上执行
								continue;
							}
							else
							{	
								
								//模块几个表只用只读一个就够了
								if(OnlyOnce)
								{
									//读成功的标志
									strValue.Format("UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",ModuleNo - 16,ModuleNo + 16);
									//运行SQL语句
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);	//读成功的标志
								}
								else
								{   
									//读成功的标志
									strValue.Format("UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY' WHERE USER_MODULENO=%d",ModuleNo);
									//运行SQL语句
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								}

							}
								
						}

							
						//根据得到的值下结论
						if(CurrentValue >= 0 )
						{	
							
							//正确的话
		                    Beep(5000,400); 

    						//收到的值转换成对应的电流值
							if(orders == 0x44 && m_PROTOCOL!=22) 
							{
								CurrentValue = double(SwitchCurrentValue(float(CurrentValue)));
							}
							else if((orders == 0xf6 && m_PROTOCOL!=22) || ((orders == 0x05 || orders == 0x73) && m_PROTOCOL==22))
							{
								//送电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_ETSTATUS = '%s' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d","送电状态",ModuleNo - 16,ModuleNo + 16);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
							}
							else if((orders == 0xf8 && m_PROTOCOL!=22) || ((orders == 0x03 || orders == 0x70) && m_PROTOCOL == 22))
							{
								//停电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_ETSTATUS = '%s' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d","停电状态",ModuleNo - 16,ModuleNo + 16);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
							}
							
							//模块号赋回
							GetModuleNo = ModuleNo;
							strValue.Format("%.2f",CurrentValue);
							
							//写数成功后的返回值
							if(((orders == 0x3e || orders == 0x40 || orders == 0x46 || orders == 0x4A || orders == 0x4e || orders == 0x50 || orders == 0xf6 || orders == 0xf8) && m_PROTOCOL!=22) || ((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && m_PROTOCOL == 22))
							{
								m_StrArray[11] = "0x33";	   
							}
							else
							{	
								m_StrArray[11].Format("%12s",strValue);
							}
							
							//类型
							m_StrArray[10] = " " + Result;
							
							//读变台容量
							if(orders == 0x50)
							{
								
								strValue.TrimLeft();
								strValue.TrimRight();
								
								switch(atoi(strValue.Left(1)))
								{
								case 1:
									{
										m_StrArray[10] = "[30,49]kVA";
										break;
									}
								case 2:
									{
										m_StrArray[10] = "[50-99]kVA";
										break;
									}
								case 3:
									{
										m_StrArray[10] = "[100-199]kVA";
										break;
									}
								case 4:
									{
										m_StrArray[10] = "[200-299]kVA";
										break;
									}
								case 5:
									{
										m_StrArray[10] = "[300-399]kVA";
										break;
									}
								case 6:
									{
										m_StrArray[10] = "[400-599]kVA";
										break;
									}
								case 7:
									{
										m_StrArray[10] = "[600-9000]kVA";
										break;
									}
								}
								
							}
							
						}
						else
						{
							
							//回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好
							if(int(CurrentValue) == -2)
							{	
								
								//正确的话
		                        Beep(5000,400); 
								m_StrArray[11] = "故障1 ";
							}
							else
							{

								if(int(CurrentValue) == -3)
								{
								
									//正确的话
                        		    Beep(5000,400); 
 									m_StrArray[11] = "故障2 ";
								
								}

							}
							
							//类型
							m_StrArray[10] = Result;
						}
							
						//时间
						CTime timet = CTime::GetCurrentTime();	
						m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
						
//						DataStr.Format("BEGINS;DATAS:1:%s",m_ComeIntoDataName);
						
						//显示结果列表
						for(i = 0; i < 13; i++)
						{		
							m_StrArray[i].TrimLeft();
							m_StrArray[i].TrimRight();
							
							//数据格式对齐
							if(i == 0)
							{
								//序号
								if(m_StrArray[i].GetLength() < 5)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%5s",strValue);
								}
								
							}
							else if( i == 5)
							{   
								//模块号 
								if(m_StrArray[i].GetLength() < 8)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%8s",strValue);
								}
								
							}
							else if( i == 11)
							{   
								//读数的值
								if(m_StrArray[i].GetLength() < 12)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%12s",strValue);
								}
								
							}
							
							DataStr = DataStr + ";" + m_StrArray[i];
							
						}
						
						//显示列表数据
						SendMessage(WM_EVENT, 3, 0);
					//	DataStr = DataStr +  ";" + "ENDS";
						
						SetProgressCtrlSetIt();
						//行号自加
						m_ListRows++;
						
						//发送数据
					//	SendContionStr = DataStr;
					//	SendMessage(WM_EVENT, 4, 0);
				
						//用户库下滑一个记录
						rs.MoveNext();
							
                     }
					
					 //关闭数据库
					 if(rs.IsOpen())
					 {
						 rs.Close();
					 }
									 
				}
				//每个读times次结束
				
        }
		//循环次数结束 
		
		if(db.IsOpen())
		{
			db.Close();
		}
      		
    }
  
	//状态栏信息为空
	StatusStr = "                            ";
    SendMessage(WM_EVENT, 1, 0);
	
	//显示DialogBar
    //SendMessage(WM_EVENT, 7, 0);
	ShowProgressCtrl(FALSE);
	m_StartRead    =  FALSE;

}

//设置角度
//short generatrixno 母线编号
//short phase        相别 0 A相 1 B相 2 C相
//int   angles       角度
//BYTE  kinds  种类 0--信号强度 1－延迟角度
void CIFRMView::SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds)
{
	
	CString    PassStr;

    //电局版本//TRUE 变电站版本  FALSE电局版
	if(AppInfo::Instance().m_WhichKind == FALSE)
	{
	   	//  BEGINS;COMMAND:07:参数1:参数2;ENDS  07 设置信号强度   06 设置延迟角度
		//                    参数1---哪一相 0－A 1－B 2－C相  
		//                    参数2---角度大小   
		if(kinds == 0)
		{
			PassStr.Format("BEGINS;COMMAND:07:%d:%d:%d;ENDS",generatrixno,phase,angles);	//如果连接好的话
		}
		else
		{
			PassStr.Format("BEGINS;COMMAND:06:%d:%d:%d;ENDS",generatrixno,phase,angles);	//如果连接好的话
		}
		
		//设置角度大小
		if(SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE) == TRUE)
		{
			SurrenderWindowMessage();//交出window控制权
		//	Sleep(1000);
		}
		
		
	}
	else
	{
		
	   	CString    str;
		BYTE ORDER[15];
		
		//角度设置 
		ORDER[0]  = 0x51;
		ORDER[1]  = 0x52;//前导码
		
		switch(phase)
		{
		case 0:
			{  
				if(kinds == 0)
				{
					ORDER[2]  = 0x5c;//A相角度设置
				}
				else
				{		
					ORDER[2]  = 0xC0;//A相延迟角度
				}
				break;
				
			}
		case 1:
			{
				if(kinds == 0)
				{
					ORDER[2]  = 0x5d;//B相角度设置
				}
				else
				{
					ORDER[2]  = 0xC1;//B相延迟角度
				}
				break;
				
			}
		case 2:
			{
				if(kinds == 0)
				{
					ORDER[2]  = 0x5e;//c相角度设置
				}
				else
				{	
					ORDER[2]  = 0xC2;//c相延迟角度
				}
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
		if(PcSendToSCM(ORDER,31,0))
		{
			
			switch(phase)
			{
			case 0:
				{  
					if(kinds == 0)
					{
						str = "A相信号强度设置完毕!";
					}
					else
					{
						str = "A相延迟角度设置完毕!";
					}

					break;
					
				}
			case 1:
				{
					
					if(kinds == 0)
					{
						str = "B相信号强度设置完毕!";
					}
					else
					{
						str = "B相延迟角度设置完毕!";
					}

					break;
					
				}
			case 2:
				{
					
					if(kinds == 0)
					{
						str = "C相信号强度设置完毕!";
					}
					else
					{
						str = "C相延迟角度设置完毕!";
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
					if(kinds == 0)
					{
						str = "A相信号强度设置错误!";
					}
					else
					{
						str = "A相延迟角度设置错误!";
					}

					break;
					
				}
			case 1:
				{
					
					if(kinds == 0)
					{
						str = "B相信号强度设置错误!";
					}
					else
					{
						str = "B相延迟角度设置错误!";
					}

					break;
					
				}
			case 2:
				{
					
					if(kinds == 0)
					{
						str = "C相信号强度设置错误!";
					}
					else
					{
						str = "C相延迟角度设置错误!";
					}

					break;
				}

			}
		
		}
			
		//MESSAGE    显示消息对话框
		//格式为:
		//    a、BEGINS;MESSAGE:0:内容;ENDS 显示提示对话框
		//    b、BEGINS;MESSAGE:1:内容;ENDS 显示警告对话框
		PassStr.Format("BEGINS;MESSAGE:0:%s;ENDS",str);		
		
		//发送提示信息
		if(SelectSendString(m_sendkind,PassStr,TRUE,FALSE,TRUE) == TRUE)
		{
			status(str);
		}
		else
		{
			MessageBox(str," ",MB_OK|MB_ICONASTERISK);
		}
	
     }

}


//读取角度
//short generatrixno 母线编号
//short phase  相别 0 A相 1 B相 2 C相
void CIFRMView::ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds)
{
	
	CString             PassStr;
	
    //电局版本//TRUE 变电站版本  FALSE电局版
	if(AppInfo::Instance().m_WhichKind == FALSE)
	{
		
		//读角度大小
		//BEGINS;COMMAND:08:参数1:参数2;ENDS 
		//参数1---母线编号  
		//参数2---哪一相 0－A 1－B 2－C相      
		//  BEGINS;COMMAND:08:参数1:参数2;ENDS  08 读取信号强度   09 读取延迟角度
		//                    参数1---哪一相 0－A 1－B 2－C相  
		//                    参数2---角度大小   

		if(kinds == 0)
		{
			PassStr.Format("BEGINS;COMMAND:08:%d:%d;ENDS",generatrixno,phase);//如果连接好的话
		}
		else
		{
			PassStr.Format("BEGINS;COMMAND:09:%d:%d;ENDS",generatrixno,phase);//如果连接好的话
		}

	    SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
		
	}
	else
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
		if(PcSendToSCM(ORDER,31,0))
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
						str.Format("测无线模块C相电流电压错误！");
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
						str.Format("测无线模块C相电流电压错误！");
						break;
					}
				}
				
				break;
				
			}
				
		}
		
	}
	
	MessageBox(str," ",MB_OK|MB_ICONASTERISK);
	}
}

//检查当前是否有程序的运行
BOOL CIFRMView::CheckRunning()
{   
	//如果在传递数据或其它工作的话
	if(ReadMeterThread != NULL || m_StartRead == TRUE) 
	{
		MessageBox("正在执行其它操作,此次指令被放弃,请按\r\nSTOP按钮停止或等任务运行完毕再运行!"," ",MB_OK|MB_ICONWARNING);
		return TRUE;
	}
	
	return FALSE;
	
}

//TCP 服务器,设置端口
void CIFRMView::SetLocalServer(CString LocalHostAddress, int LocalPort)
{ 
	//IP 地址如：121.111.1.1
    VARIANT LocalHostPort_VT,LocalHostIP_VT;
	m_WinSocket.Close();
    	
	LocalHostPort_VT.vt    = VT_I2;//数据为整数
    LocalHostPort_VT.lVal  = LocalPort;
	
    LocalHostIP_VT.vt      = VT_BSTR;//数据为字符串
    LocalHostIP_VT.bstrVal = LocalHostAddress.AllocSysString();
	
	//TCP连接的 LocalPort 和 LocalIP。
	m_WinSocket.Bind(LocalHostPort_VT, LocalHostIP_VT);
	
	//开始监听
	m_WinSocket.Listen();
	
	status("【处于侦听状态】");
	
}

/*
GetState()值
常数                  值      描述 
sckClosed             0       缺省的。关闭 
sckOpen               1       打开 
sckListening          2       侦听 
sckConnectionPending  3       连接挂起 
sckResolvingHost      4       识别主机 
sckHostResolved       5       已识别主机 
sckConnecting         6       正在连接 
sckConnected          7       已连接 
sckClosing            8       同级人员正在关闭连接 
sckError              9       错误 
*/

//有请求连接到达时产生(服务器端)
void CIFRMView::OnConnectionRequestWinsock(long requestID) 
{	

	//检查控件的 State 属性是否为关闭的,如果不是,在接受新的连接之前先关闭此连接。
	if(m_WinSocket.GetState() != 0)
	{
		m_WinSocket.Close();
	}
	
	//	常数           值     描述 
	//sckTCPProtocol   0      缺省的。TCP 协议。 
	//sckUDPProtocol   1      UDP 协议。 
    m_WinSocket.SetProtocol(0); 
	
	//接受具有 requestID 参数的连接
	m_WinSocket.Accept(requestID);
	
	//连接标志
	m_IsConnect      = TRUE;

	//如果在原拔号成功状态下
	if(m_Com.GetCDHolding())
	{	
		 //关闭远程猫
		 SelectSendString(2, "BEGINS;COMMAND:32:【本地版正通过电话线与远程版在连接(忙)，网络连接断开】;ENDS",TRUE,FALSE,TRUE);
		
		 //TRUE 变电站版本  FALSE电局版
	     OnCloseWinsock();

		 status("【试图局域网连接，但电话占用，局域网连接失败】");
		 return;

	}

}

//创建 TCP 客户端
void CIFRMView::SettcpClient(CString RemoteHostAddress, int RemotePort)
{
	
	//  if(m_WinSocket.GetState() != 0)
	{
		m_WinSocket.Close();
	}
	
	//IP 地址如：121.111.1.1
	VARIANT RemoteHostPort_VT,RemoteHostIP_VT;
	
	RemoteHostPort_VT.vt    = VT_I2;//数据为整数
	RemoteHostPort_VT.lVal  = RemotePort;
	
	RemoteHostIP_VT.vt      = VT_BSTR;//数据为字符串
	RemoteHostIP_VT.bstrVal = RemoteHostAddress.AllocSysString();
	
	m_WinSocket.SetRemoteHost(RemoteHostAddress);
	m_WinSocket.SetRemotePort(RemotePort);
	
	//调用Connect方法,初始化连接。
	m_WinSocket.Connect(RemoteHostIP_VT,RemoteHostPort_VT);
	
}

//有数据到达时产生事件
void CIFRMView::OnDataArrivalWinsock(long bytesTotal) 
{
	long                  ix;
	int                  k,l;
	BYTE                 bit;
	CString   str,ReceiveStr;
	//接收字节数组
	COleVariant     recv_var;
	
	ReceiveByteArray.RemoveAll();
	
	//类型
	VARIANT            Vtype;
	Vtype.vt    =   VT_ERROR;
	
	//长度
	VARIANT           Maxlen;
	Maxlen.vt   =      VT_I4;
	Maxlen.lVal = bytesTotal;
	
	m_WinSocket.GetData(&recv_var, Vtype, Maxlen);//接收数据包
	
	if(recv_var.parray != NULL) 
	{
		
		for( ix = 0; ix < bytesTotal; ix ++)
		{
			
			SafeArrayGetElement(recv_var.parray,&ix,&bit);
			char a=*(char*)(&bit); 
			str.Format("%c",a); 
			ReceiveStr+=str;   
		
		}
				
		k = ReceiveStr.Find("ENDS");
		l = ReceiveStr.Find("BEGINS");

   		//有我们要的数据
		if(k != -1 && l != -1)
		{	
			/****************去掉头和尾的其它字符*********/
			ReceiveStr = ReceiveStr.Mid(l+7,k - l - 8);
			ReceiveStr.TrimLeft();
			ReceiveStr.TrimRight();
			AnalyseOrder(ReceiveStr);//分析传来的数据,对接收到的数据做必要处理
	
		}
		
	} 
	
}

BOOL CIFRMView::DestroyWindow() 
{	
    //m_WinSocket.Close();	
	return CFormView::DestroyWindow();
}

void CIFRMView::OnCloseWinsock() 
{   

	if(AppInfo::Instance().m_WhichKind )
	{
	   
		//如果是服务器版,在变电站内
		m_WinSocket.Close();
		
		Sleep(200);
		
		//重新启动服务器
		SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
	}
	else
	{
		m_WinSocket.Close();
	}
	
	//连接标志
	m_IsConnect   =    FALSE;

}




/************************************************************************
**    总格式:引导字BEGINS;命令字选项;*;*;*;*;*;*;ENDS 
**
**     MESSAGE    显示消息对话框
**          格式为:
**               a、BEGINS;MESSAGE:0:内容;ENDS 显示提示对话框
**               b、BEGINS;MESSAGE:1:内容;ENDS 显示警告对话框
**
**     DATAS      数据传递
**         收到的格式有两种:
**         a、BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
**         b、BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
**         c、BEGINS;DATAS:2:表名;读表结束;ENDS      数据传送结束标志
**         d、BEGINS;DATAS:3:StopData;停止;ENDS      设置停止按钮标记
** 
**                                      
**     SEND       发送数据(在列表中显示)
**          格式为:
**                   BEGINS;SEND:表名:查询条件;ENDS 要其传送满足条件的数据
** 												 
** 
**    COMMAND  执行命令
**    格式为:
**    1、BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  参数1---母线,参数2---相别,参数3---发送的时间单位数(8的倍数),参数4---发送的时间(字符形式) 执行发驻留命令     
**    2、BEGINS;COMMAND:01:参数1;ENDS              参数1---数据范围                       执行测试读表操作
**    3、BEGINS;COMMAND:02:参数1;ENDS              参数1---数据范围                       执行正式读表操作
**    4、BEGINS;COMMAND:03:参数1;ENDS              参数1---数据范围                       执行驻留读表操作
**    5、BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
**                         参数1---标题         参数2---结果                   参数3---条件范围
**    	                   参数4---命令字       参数5---是否只读相不定         参数6---次数        
**    	                   参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
**    	                   参数10--间隔         读写各项测试参数,处理各项参数
****************************************************************************/

//分析传输的指令，对接收到的数据做必要处理 
void CIFRMView::AnalyseOrder(CString OrderStr)
{
	
	int                k,l;
	CString            str;
	m_IfChangeData  = TRUE;//接收远程数据的标志
	
    //远程要其停止
	if(OrderStr.Find("DATAS:3:StopData") != -1)
	{ 
		//错误的次数赋为0
		m_GetErrors   =       0;
		
		for(BYTE i = 0; i < 10; i ++)
		{
			
			m_StartRead       =   FALSE;
			bStopped          =    TRUE;
			//监视读表
			m_CheckReading    =   FALSE;	
			
			//交出window控制权
			SurrenderWindowMessage();
			Sleep(250);
			
			if(ReadMeterThread == NULL)
			{
				break;
			}
			
		}
		//如果线程暂停
		
		if(ReadMeterThread != NULL  && m_Pause)
		{
			//启动线程退出
			ReadMeterThread->ResumeThread();
			m_Pause  =   FALSE;	
			
			//交出window控制权
			SurrenderWindowMessage();
			Sleep(500);
			//交出window控制权
			SurrenderWindowMessage();
			//如果线程暂停
		}
		
		//停止传送数据
		m_StopPassing    = TRUE;
		
		KillTimer(2);
		KillTimer(3);
		
		//演示或隐藏动画
		OperationAnimation(FALSE);
		//隐藏滚动条
		ShowProgressCtrl(FALSE);
		
		//交出window控制权
		SurrenderWindowMessage();
		//不可以接收数据了
		m_ReceiveOk    =   FALSE;
		status("              ");
		
	   /*
		//错误的次数赋为0
	    m_GetErrors   =       0;
		m_StartRead   =   FALSE;
		m_others      =   FALSE;

		//停止传送数据
	    m_StopPassing =    TRUE;
		//交出window控制权
		SurrenderWindowMessage();
		//停止定时读表
		KillTimer(2);
		//停止定时读表
		KillTimer(3);
		//演示或隐藏动画
		OperationAnimation(FALSE);
		Sleep(1000);
		*/
		return;
	}
	
	//远程要其停止自动发驻留自动读表
	if(OrderStr.Find("DATAS:4:StopData") != -1)
	{ 	
		
		//有读表的话，退出
		m_StartRead   =   FALSE;
        m_others      =   FALSE;

		KillTimer(1);
		KillTimer(2);
		KillTimer(3);

		//数组中日期下标参数赋为0
		m_statusstr     =       "";
		status("                         ");

		if(m_IsAutoSending)
		{
			m_IsAutoSending =    FALSE;
			SendContionStr  =    "BEGINS;MESSAGE:0:自动发驻留自动读表已取消!;ENDS";
			SendMessage(WM_EVENT, 4, 0);
			status("【自动发驻留读表已取消】");
			//交出window控制权
			SurrenderWindowMessage();

			//写入历史记录表,时间
			CString strs;
			CTime timet = CTime::GetCurrentTime();
			strs.Format("【%4d-%02d-%02d %02d:%02d:%02d】远程取消发定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			WriteToLog(strs);
			
			//定时按钮置为FALSE
			ShowDingShiButton(FALSE);
		}
		else
		{
			//远程查询对方的驻留设置
			SendContionStr = "BEGINS;MESSAGE:0:对方机器定时驻留设置为空！;ENDS";
			SendMessage(WM_EVENT, 4, 0);
		}
		return;

	}		
	
	//MESSAGE    显示消息对话框
	//格式为:
	//a、BEGINS;MESSAGE:0:内容;ENDS   显示提示对话框
	//b、BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
	k = OrderStr.Find("MESSAGE:");
	
	if(k != -1)
	{
		k = OrderStr.Find("MESSAGE:0");
		
		if(k != -1)
		{	  
			//显示消息字符
			str         = OrderStr.Right(OrderStr.GetLength() -10);
			
			//如果是电局版,弹出对话框，变电站版本则在状态栏中显示信息
			if(!AppInfo::Instance().m_WhichKind)
			{
				status("                     ");
				MessageBox( str," ",MB_OK|MB_ICONWARNING);
				m_StartRead          =    FALSE;
			}
			else
			{
				status(str);
			}
			
		}
		else
		{
			str = OrderStr.Right(OrderStr.GetLength() - 10);
			//状态栏显示信息
			status(str);
		}
		
	}
	
	//TRUE-变电站版本 FALSE-电局版,如果有其它操作或在传数据
	if(AppInfo::Instance().m_WhichKind)
	{

		//如果变电站正下了驻留命令1、在发驻留命令 2、在数据读表 
		if(ReadMeterThread != NULL)
		{
			//交出window控制权
		    SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS","【远程机器正处于读表或手拉手调制状态，忙】");
			SendMessage(WM_EVENT,4,0);
        	return;

		}

	}

	
	/***********传送的是数据,在列表中显示数据***********/
	//格式为:
	//    a、BEGINS;DATAS:0:表名;表结构;ENDS        数据库表的数据结构
	//    b、BEGINS;DATAS:1:表名;*;*;*;*;*;*;*;ENDS 数据库表的数据
	//    c、BEGINS;DATAS:2:表名;读表结束;ENDS      传送表结束
	//    d、BEGINS;DATAS:3:StopData;停止;ENDS      停止操作
	
	k = OrderStr.Find("DATAS:");
	
	if( k != -1)
	{	
		//显示实时数据
		RealTimeReceiveData(OrderStr);
	}
	else 
	{
		
		/***********是要求发送满足条件的数据***********/
		//格式为:
		//格式: BEGINS;SEND:0:表名:查询条件;ENDS   发送数据,在列表中显示数据,不是断点连接 
	
		k = OrderStr.Find("SEND:");
		
		if(k != -1)
		{
			
			k = OrderStr.Find(':');
			
			if( k != -1)
			{
				
				//去掉"SEND:"
				OrderStr = OrderStr.Right(OrderStr.GetLength()- k - 1);
				
				k = OrderStr.Find(':');
				
				if( k != -1)
				{
					
					l = atoi(OrderStr.Left(k));
					
					//去掉"0:"或"1:"
					OrderStr = OrderStr.Right(OrderStr.GetLength()- k - 1); 
					
					k = OrderStr.Find(':');
					if( k != -1)
					{
						
						//得到要传的表名, 得到所给的条件
						//发送给局里要求的数据,在列表中显示数据
						if(l == 0)
						{

							//提出符合条件的记录
							CString m_DataName,m_Condtion,m_filename,m_SqlStr;
                            m_DataName = OrderStr.Left(k);
							m_Condtion = OrderStr.Right(OrderStr.GetLength()- k - 1);
                            m_filename.Format("%s%s%s",GetFolder(),m_DataName,".TXT");
							
							long fields = CDataBaseInstance::GetAllRecordsCount(m_DataName,m_Condtion);
							
							m_Condtion.TrimLeft();
                            m_Condtion.TrimRight();

							if(m_Condtion == "ALL")
							{
								m_SqlStr.Format("SELECT * FROM %s",m_DataName);
							}
							else
							{
								m_SqlStr.Format("SELECT * FROM %s WHERE %s",m_DataName,m_Condtion);
							}
							
							if(fields > 0)
							{
								//告诉对方有多少数据
								WriteDataToTextFile(m_DataName,m_SqlStr,fields,m_filename);	
								//告诉对方没有数据
								SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS",m_DataName,fields);
					            SendMessage(WM_EVENT, 4, 0);
							}
							else
							{
								//告诉对方没有数据
								SendContionStr = "BEGINS;MESSAGE:0:对不起，对方表中没有满足此条件的数据信息!;ENDS";
								SendMessage(WM_EVENT, 4, 0);
							}

							//停止传送数据
	                        m_StopPassing = FALSE;
  							
						}

					}
					
				}
				
			}
			
		}
		else
		{
			
			/****************************  执行命令   **********************************
			COMMAND  执行命令
			格式为:
			1、BEGINS;变电站编号;COMMAND:00:参数1:参数2:参数3:参数4;ENDS  参数1---母线,参数2---相别,参数3---发送的时间单位数(8的倍数),参数4---发送的时间(字符形式) 执行发驻留命令    
			2、BEGINS;COMMAND:01:参数1;ENDS              参数1---数据范围                       执行测试读表操作
			3、BEGINS;COMMAND:02:参数1;ENDS              参数1---数据范围                       执行正式读表操作
			4、BEGINS;COMMAND:03:参数1;ENDS              参数1---数据范围                       执行驻留读表操作
			5、BEGINS;COMMAND:11:参数1;ENDS              参数1---数据范围                       执行送电操作
			6、BEGINS;COMMAND:05:参数1;ENDS              参数1---数据范围                       执行停电操作
			****************************************************************************/
			
			k = OrderStr.Find("COMMAND:");
			
			if(k != -1)
			{
				//执行命令
				CarryOutOrders(OrderStr);
			}
			
		}
		
	}
}


//分析拔号产生的提示
void CIFRMView::AnalyseDial(CString str)
{
	CStringArray m_StrArray;
    m_StrArray.Add("RING");
	m_StrArray.Add("检测到拔号振铃信号...           ");
	m_StrArray.Add("ERROR");
	m_StrArray.Add("无效命令，命令行错误...         "); 
	m_StrArray.Add("CONNECT");
    m_StrArray.Add("拔号连接成功！！！               ");
    m_StrArray.Add("NO DIALTONE");
	m_StrArray.Add("没有检测到拔号音，拔号失败...   ");
    m_StrArray.Add("BUSY");
	m_StrArray.Add("检测到忙音,对方线路忙，拔号失败...");
    m_StrArray.Add("NO ANSWER");
	m_StrArray.Add("拔的电话号无信号声，拔号失败... ");	
	
	for(int i = 0; i < m_StrArray.GetSize(); i = i + 2)
	{
        str.MakeUpper( );

		//查找相应的返回值
		if(str.Find(m_StrArray[i]) != -1)
		{	

			if(!AppInfo::Instance().m_WhichKind)
			{
				MessageBox(m_StrArray[i + 1]," ",MB_OK|MB_ICONASTERISK);
			}
			else
			{	
				CTime time = CTime::GetCurrentTime();	
				str.Format(" %d-%d-%d %d:%d:%d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				status(m_StrArray[i + 1] + str);
			}
			ReceiveByteArray.RemoveAll();
		}
		
	}

			
}

//连接建立好，可以进行通信时触发(客户端)
void CIFRMView::OnConnectWinsock() 
{
    //连接标志
	m_IsConnect      = TRUE;
}

//发生错误时发生
void CIFRMView::OnErrorWinsock(short Number, BSTR FAR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL FAR* CancelDisplay) 
{
	return;
}

//在发送数据期间出现
void CIFRMView::OnSendProgressWinsock(long bytesSent, long bytesRemaining) 
{
	// TODO: Add your control notification handler code here
	
}

//在完成一个发送操作时出现。
void CIFRMView::OnSendCompleteWinsock() 
{
	
}


//二进制方式发送字符串
//kinds           种类         0 串口发送 1 电话拔号发送 2 TCP/IP发送 m_sendkind
//Str             发送字符
//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
//BOOL m_CheckReturnValue 是否检测返回值,证明收到了
BOOL CIFRMView::SelectSendString(int kinds, CString Str, BOOL CheckConnected,BOOL AppearPrompt,BOOL m_CheckReturnValue)
{	
	return TRUE;
	

	switch(kinds)
	{
	case 0://串口发送
		{
			
			//要连接后才能发送
			if(CheckConnected)
			{
				
				if(m_Com.GetPortOpen())
				{
					
					//发驻留期间或驻留读表时不发信息
					if(m_IsAutoSending && m_others)
					{
						
						//只有此些信息才可以发送
						if(Str.Find("【远程机器正处于读表或手拉手调制状态，忙】") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("【本地版正与局域网远程版在连接(忙)，拔号连接将断开】") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("【本地版正通过电话线与远程版在连接(忙)，网络连接断开】") == -1 )
						{
							return FALSE;
						}
						
					}
                    
					BYTE                     bits;
					int            m_length   = 0;  //长度
					CString                  strs;
					//CRC检验值
					unsigned int  crc  =   0xffff;
					Str = Str.Mid(7,Str.GetLength() - 12);
					
					int Count   = Str.GetLength();
					
					//删除所有数据
					SendByteArray.RemoveAll();
					//第一位数，开始标志 0x68
					SendByteArray.Add(0x68);
					//第二位数，长度L低字节
					SendByteArray.Add(0x00); 
					//第三位数，长度L高字节
					SendByteArray.Add(0x00); 
					//第四位数, 0x68
					SendByteArray.Add(0x68);
					
					//给数组赋值
					for(int i  = 0; i < Count; i ++)
					{
						//每个字节的值
						if(Str.GetAt(i) == ' ')
						{
							bits =  '*';
						}
						else
						{
							bits =  Str.GetAt(i);
						}
						
						SendByteArray.Add(bits);
						//调用CRC检验
                        crc = Crc16( crc , bits );            
						
					}
					
					//长度,前四个不是数据
					m_length = SendByteArray.GetSize() - 4; 
					//长度L低字节 
					SendByteArray[1] = m_length%256;
					//长度L高字节
					SendByteArray[2] = m_length/256;; 
					//加CRC检验低位
					SendByteArray.Add(crc%256);	
					//加CRC检验高位
					SendByteArray.Add(crc/256);
					//结尾标志
					SendByteArray.Add(0x16);
					
					SurrenderWindowMessage();
					//发送数组时用
					m_Com.SetOutput(COleVariant(SendByteArray));
					m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加
					
					SurrenderWindowMessage();
					
					//如果是传送数据的话,不要求延时
					if(Str.Find("COMMAND:26")== -1 && Str.Find("COMMAND:25")== -1 && Str.Find("DATAS:3:")== -1)
					{
						
						//延迟时间
						for(int iii = 0; iii <= 20; iii++)
						{
							SurrenderWindowMessage();
							Sleep(10);
							SurrenderWindowMessage();
						}
						
					}

					return TRUE;
					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("和远程机器连接失败，请连接好再试！"," ",MB_OK|MB_ICONWARNING);
						//又可以接收指令
						m_StartRead = FALSE;
					}
					
					return FALSE;
					
				}
				
				
			}
			else
			{	
				//二进制方式发送
				m_Com.SetOutput(COleVariant(Str));//发送数据,发送ASCII字符数据
			//	m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加
			}

			break;
			
           
		}
	case 1://电话拔号发送
		{   
			if(CheckConnected)
			{

				//要连接后才能发送
				if(m_Com.GetCDHolding())
				{
				
					//错误次数超过PASS_TIMES，不发送
					if(m_PassErrortimes > PASS_TIMES)
					{
						return FALSE;
					}

					//发驻留期间或驻留读表时不发信息
					if(m_IsAutoSending && m_others)
					{
						
						//只有此些信息才可以发送
						if(Str.Find("【远程机器正处于读表或手拉手调制状态，忙】") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("【本地版正与局域网远程版在连接(忙)，拔号连接将断开】") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("【本地版正通过电话线与远程版在连接(忙)，网络连接断开】") == -1 )
						{
							return FALSE;
						}
						
					}
		
					BYTE                     bits;
					int            m_length   = 0;  //长度
					CString                  strs;
					//CRC检验值
					unsigned int  crc  =   0xffff;
					Str = Str.Mid(7,Str.GetLength() - 12);
					
					int Count   = Str.GetLength();
            					
					//删除所有数据
					SendByteArray.RemoveAll();
					//第一位数，开始标志 0x68
					SendByteArray.Add(0x68);
					//第二位数，长度L低字节
					SendByteArray.Add(0x00); 
					//第三位数，长度L高字节
					SendByteArray.Add(0x00); 
					//第四位数, 0x68
					SendByteArray.Add(0x68);
					
					//给数组赋值
					for(int i  = 0; i < Count; i ++)
					{
						//每个字节的值
						if(Str.GetAt(i) == ' ')
						{
							bits =  '*';
						}
						else
						{
							bits =  Str.GetAt(i);
						}
						
						SendByteArray.Add(bits);
						//调用CRC检验
                        crc = Crc16( crc , bits );            
						
					}
					
					//长度,前四个不是数据
					m_length = SendByteArray.GetSize() - 4; 
					//长度L低字节 
					SendByteArray[1] = m_length%256;
					//长度L高字节
					SendByteArray[2] = m_length/256;; 
					//加CRC检验低位
					SendByteArray.Add(crc%256);	
					//加CRC检验高位
					SendByteArray.Add(crc/256);
					//结尾标志
					SendByteArray.Add(0x16);
             
					for(int ii = 0 ; ii < 10; ii ++)
					{

						//当CTS线及CD线为高电平时才可发送，否则需等待。 
						if(m_Com.GetCTSHolding() &&  m_Com.GetCDHolding())
						{
							
							SurrenderWindowMessage();
							//发送数组时用
							m_Com.SetOutput(COleVariant(SendByteArray));
						    m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加
							
							SurrenderWindowMessage();

							//如果是传送数据的话,不要求延时
							if(Str.Find("COMMAND:26")== -1 && Str.Find("COMMAND:25")== -1 && Str.Find("DATAS:3:")== -1)
							{
								
								//延迟时间
								for(int iii = 0; iii <= 30; iii ++)
								{
									SurrenderWindowMessage();
									Sleep(10);
									SurrenderWindowMessage();
								}


							}

							//成功了则错误次数赋为0
							m_PassErrortimes = 0;

							return TRUE;

						}

						Sleep(100);
					
					}
					
					//错误次数相加
					m_PassErrortimes ++;
					
					StatusStr = "此桢数据发送错误！";
					SendMessage(WM_EVENT, 1, 0);

					return FALSE;
           					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("和远程机器连接失败，请连接好再试！"," ",MB_OK|MB_ICONWARNING);
						//又可以接收指令
						m_StartRead = FALSE;
					}
					
					return FALSE;
					
				}
				
				
			}
			else
			{	
				//二进制方式发送
				m_Com.SetOutput(COleVariant(Str));//发送数据,发送ASCII字符数据
			//	m_Com.SetOutBufferCount(0);      //清缓冲区的数据 2005-10-11加
			}
			break;
		}
	case 2://TCP/IP发送
		{   
			
			if(m_IsConnect)
			{

				//发驻留期间或驻留读表时不发信息
				if(m_IsAutoSending && m_others)
				{
					
					//只有此些信息才可以发送
					if(Str.Find("【远程机器正处于读表或手拉手调制状态，忙】") == -1 )
					{
						return FALSE;
					}
					
					if(Str.Find("【本地版正与局域网远程版在连接(忙)，拔号连接将断开】") == -1 )
					{
						return FALSE;
					}
					
					if(Str.Find("【本地版正通过电话线与远程版在连接(忙)，网络连接断开】") == -1 )
					{
						return FALSE;
					}
					
				}
				
				//要连接后才能发送
				m_WinSocket.SendData(COleVariant(Str));//发送数据 
				SurrenderWindowMessage();//交出window控制权 
				
				//要延时时间
				if(m_CheckReturnValue)
				{			
					//延时500毫秒
					Sleep(200);	
				}
		        SurrenderWindowMessage();
			}
			else
			{
				
                if(AppearPrompt)
				{
					MessageBox("和远程机器连接失败，请连接好再试！"," ",MB_OK|MB_ICONWARNING);
					//又可以接收指令
					m_StartRead = FALSE;
				}
				return FALSE;
				
			}
			break;
		}
		
	}
	
	SurrenderWindowMessage();//交出window控制权
   
	return TRUE;
}

//二进制方式发送
//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
BOOL CIFRMView::SelectSendCByteArray(int kinds,BOOL CheckConnected,BOOL AppearPrompt)
{
	switch(kinds)
	{
	case 0://串口发送
		{
			if(CheckConnected)
			{
				//要连接后才能发送
				if(m_Com.GetPortOpen())
				{
					
					m_Com.SetOutput(COleVariant(SendByteArray));
					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("串口没有打开，请先设置好串口参数再试!"," ",MB_OK|MB_ICONWARNING);
					}
					return FALSE;
					
				}
				
			}
			else
			{
				
				m_Com.SetOutput(COleVariant(SendByteArray));
				
			}
			break;
		}
	case 1://电话拔号发送
		{   
			if(CheckConnected)
			{
				
				//要连接后才能发送
				if(m_Com.GetCDHolding())
				{	
					//if(m_IsDialConnectting)
					m_Com.SetOutput(COleVariant(SendByteArray));
						
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("远程连接失败，请先连接好本地端和远程端再试!"," ",MB_OK|MB_ICONWARNING);
					}
					return FALSE;
				}
				
			}
			else
			{	
				
				m_Com.SetOutput(COleVariant(SendByteArray));
				
			}
			break;
		}
	case 2://TCP/IP发送
		{   
			
			if(CheckConnected)
			{
				
				//连接标志
	            if(m_IsConnect)
				{
				    //要连接后才能发送
				    m_WinSocket.SendData(COleVariant(SendByteArray));//发送连接信息
				}
				
			}
			else
			{
				
                if(AppearPrompt)
				{
					MessageBox("网络连接失败，请先连接好再试!"," ",MB_OK|MB_ICONWARNING);
				}
				return FALSE;
				
			}
			break;
		}
		
	}
	
	return TRUE;
	
}

//与长沙威远通信连接
void CIFRMView::AnalyseReceivedByteArray()
{
	
    //清除多余的数据,且检验数据
    if(!WipeOffSpilthData())
	{
		return;
	}
	
	//以0x10开头的为固定帧格式长度为6
	switch(ReceiveByteArray[0])
	{
	case 0x10://处理固定帧格式
		{   
			
			//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
			switch(ReceiveByteArray[1])
			{
		    case 0x48://主站召唤终端系统时钟
				{
					
					//发送回馈信息
					BYTE  SendByte[21];
					CString        STR;
					SendByte[19]   = 0;
					//系统时间处理
					SYSTEMTIME   systime;
					::GetLocalTime(&systime);
					
					SendByte[0]  = 0x68;
					SendByte[1]  = 0x0F;
					SendByte[2]  = 0x00;
					SendByte[3]  = 0x68;
					SendByte[4]  = 0x88;
					SendByte[5]  = 0xFF;
					SendByte[6]  = 0x48;
					SendByte[7]  = 0x01; 
					SendByte[8]  = 0x05;
					SendByte[9]  = ReceiveByteArray[2];
					SendByte[10] = ReceiveByteArray[3];
					SendByte[11] = 0x30;
					
					SendByte[12] = systime.wYear%100;                  //年
					SendByte[13] = BYTE(systime.wMonth);               //月
					SendByte[14] = BYTE(systime.wDay);                 //日
					SendByte[15] = BYTE(systime.wHour);                //时
					SendByte[16] = BYTE(systime.wMinute);              //分
					SendByte[17] = BYTE(systime.wSecond);              //秒
					SendByte[18] = BYTE(systime.wMilliseconds/10);    //毫秒
					STR.Format("%d年%d月%d日-%d:%d:%d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
				
					//时间转成BCD码
					int i;
					for( i = 12; i <= 18; i++)
					{
						SendByte[i] = SendByte[i]/10*16 + SendByte[i]%10;
					}
					
					SendByte[20] = 0x16;                               //结束标志
					//赋发送值
					SendByteArray.RemoveAll();
					
					for( i = 0; i < 21; i ++)
					{
						if(i >= 4 && i < 19)
						{
							//校验码
							SendByte[19] = SendByte[19] + SendByte[i];
						}
						SendByteArray.Add(SendByte[i]);
						
					}
					
					//二进制方式发送
					//kinds           种类  0-串口发送  1-电话拔号发送  2-TCP/IP发送m_sendkind
					//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
					//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
					SelectSendCByteArray(m_sendkind,TRUE,FALSE);
					status("主站召唤终端系统时钟，" + STR);
					break;
				}
			case 0x49:
				{
					//重复召唤终端的前一帧的数据
					m_LocalAddress = m_LocalAddress - m_EveryUnit;
				
					if(m_LocalAddress < 0 )
					{
						m_LocalAddress = 0;
					} 

				    //CString Datatime  传送>＝Datatime的数据
					//BYTE    Kinds     种类  0x11 电量  0x13电流电压
					//int     Start     起始位
					//int     N         终端数据库结构或瞬时功率电压电流
					if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
					{
						status("重复召唤终端的前一帧的数据成功!");
					}
					else
					{
                       status("重复召唤终端的前一帧的数据没有找到!");
					}
					//当前记录位置
					m_LocalAddress = m_LocalAddress + m_EveryUnit;
				
					break;
				}
			case 0x4A:
				{
					//主站召唤终端的后续数据
					//CString Datatime  传送>＝Datatime的数据
					//BYTE    Kinds     种类  0x11 电量  0x13电流电压
					//int     Start     起始位
					//int     N         终端数据库结构或瞬时功率电压电流
	                if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
					{
						status("主站召唤终端的后续数据成功!");
					}
					else
					{
                       status("主站召唤终端的后续数据没有找到!");
					}					//当前记录位置
					m_LocalAddress = m_LocalAddress + m_EveryUnit;
					break;
				}
				
			}
			//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
			//以0x10开头的为固定帧格式
			break;
		}
	case 0x68://处理可变帧格式
		{
			
			
			switch(ReceiveByteArray[4])
			{
		    case 0x46://主站设置终端系统时钟
				 {
					 /********************************************************/
					 //收到的数为BCD码,转成十进制的数
					 SYSTEMTIME systime;
					 CString       strs;
					 systime.wYear          = ReceiveByteArray[12]/16*10 + ReceiveByteArray[12]%16 + 2000;//年
					 systime.wMonth         = ReceiveByteArray[13]/16*10 + ReceiveByteArray[13]%16;       //月
					 systime.wDayOfWeek     = 0;
					 systime.wDay           = ReceiveByteArray[14]/16*10 + ReceiveByteArray[14]%16;       //日 
					 systime.wHour          = ReceiveByteArray[15]/16*10 + ReceiveByteArray[15]%16;       //时
					 systime.wMinute        = ReceiveByteArray[16]/16*10 + ReceiveByteArray[16]%16;       //分
                     systime.wSecond        = ReceiveByteArray[17]/16*10 + ReceiveByteArray[17]%16;       //秒
					 systime.wMilliseconds  = (ReceiveByteArray[18]/16*10 + ReceiveByteArray[18]%16)*100; //毫秒
                   
					 if(::SetLocalTime(&systime))
					 {
						 strs.Format("主站设置终端系统时钟成功: %d-%d-%d %d:%d:%d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
						 status(strs);
					     //发送回馈信息 0-成功执行,1-检验码不对,2-无数据
                         SendMessageToElectricOffice(0);
					 }
					 else
					 {
						 status("主站设置终端系统时钟失败!");
						//WriteToLog("主站设置终端系统时钟失败!");
					 }
					 break;
					 /********************************************************/
					 
				 }
			 case 0x4b://主站召唤终端的数据
				 {   
					 CString      str;

				     //0x11为电量  0x13为电流电压
				     if(ReceiveByteArray[11] == 0x11 || ReceiveByteArray[11] == 0x13)
					 {
						
						 m_EveryUnit = ReceiveByteArray[12]/16*10 + ReceiveByteArray[12]%16;//信息对象个数
						 //发送时间 >＝ 此日期的数据
                         HuNanZhaoHuanTime.Format("%4d-%02d-%02d %02d:%02d:%02d",ReceiveByteArray[13]/16*10 +ReceiveByteArray[13]%16 + 2000,ReceiveByteArray[14]/16*10+ReceiveByteArray[14]%16,ReceiveByteArray[15]/16*10+ReceiveByteArray[15]%16,ReceiveByteArray[16]/16*10+ReceiveByteArray[16]%16,ReceiveByteArray[17]/16*10+ReceiveByteArray[17]%16,0);
						 HuNanZhaoHuanOrder  = ReceiveByteArray[11];
						 
						 //当前传送后的位置
						 m_LocalAddress     =          0;
						 //CString Datatime  传送>＝Datatime的数据
						 //BYTE    Kinds     种类  0x11 电量  0x13电流电压
						 //int     Start     起始位
						 //int     N         终端数据库结构或瞬时功率电压电流
						 if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
						 {
							 
							 if(ReceiveByteArray[11] == 0x11)
							 {
								 str.Format("主站召分时电量数据:时间>=%s[%d个,成功]",HuNanZhaoHuanTime,m_EveryUnit);
							 }
							 else
							 {	
								 str.Format("主站召瞬时电流电压:时间>=%s[%d个,成功]",HuNanZhaoHuanTime,m_EveryUnit);
							 }

						 }
						 else
						 {   
							 if(ReceiveByteArray[11] == 0x11)
							 {
								 str.Format("主站召分时电量:时间>=%s[%d个,没有找到]",HuNanZhaoHuanTime,m_EveryUnit);
							 }
							 else
							 {	
								 str.Format("主站召瞬时电流电压:时间>=%s[%d个,没有找到]",HuNanZhaoHuanTime,m_EveryUnit);
							 }

						 }

						 status(str);
						 //当前位置
						 m_LocalAddress = m_LocalAddress + m_EveryUnit;
						 
					 }
					 break;
					 
				 }  
			 case 0x4E://密码验证
				 {
					 /*
                     if(ReceiveByteArray.GetSize() > 11)
					 {

						 if(ReceiveByteArray[11] == 0x70)
						 {
                              //发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					          SendMessageToElectricOffice(0);
							  status("密码验证成功!");
						 }
						 else
						 {
						      //发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					          SendMessageToElectricOffice(1);
							  status("密码验证失败!");
						 }

					 }
					 else
					 {
						 //发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					     SendMessageToElectricOffice(1);
						 status("密码验证失败!");
					 }
					 */
					 //发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					 SendMessageToElectricOffice(0);
					 status("密码验证成功!");
     				 break;
				 }
				 
				 
			 }
			 //以0x68开头的为可变帧格式
			 break;
			 
		  }
		  
    }
	
    //删除字节数组
    ReceiveByteArray.RemoveAll();
	
}

LRESULT CIFRMView::OnEvent(WPARAM wParam, LPARAM lParam)
{
	
	switch(wParam)
	{
	case 1:
		{
			//显示状态栏
			status(StatusStr);
			break;
		}
	case 2:
		{
			//显示列标题
			WriteListHeading();		
			break;
			
		}
	case 3:
		{
			//显示数据
		   	m_Grid.InsertRow(_T(" "), -1);
			m_Grid.Invalidate(); 
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
			#ifndef _WIN32_WCE
			   dwTextStyle |= DT_END_ELLIPSIS;
			#endif
		
			for (int col = 0; col < m_Grid.GetColumnCount(); col++)
			{ 

				GV_ITEM  Item;
				Item.mask    = GVIF_TEXT|GVIF_FORMAT;
				Item.row     = m_Grid.GetRowCount() - 1;//m_ListRows;
				Item.col     = col;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%s",(m_StrArray[col]));
				m_Grid.SetItem(&Item);
			}

			m_Grid.SetModified(FALSE,-1,-1);
			m_Grid.Invalidate();
		//	m_Grid.Refresh();
		//	SurrenderWindowMessage();
			break;
		}
	case 4:
		{
			//如果连接好的话
			//SelectSendString(m_sendkind,SendContionStr,TRUE,FALSE,TRUE);
			break;
		}
	case 5:
		{
			//如果连接好的话
			//SelectSendString(m_sendkind,SendContionStr,TRUE,FALSE,FALSE); 
			break;
		}
	case 6:
		{
			//隐藏DIALOGBAR
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);

			if(pMainFrm->m_wndMyDialogBar.IsWindowVisible())
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
			}
			m_DialogBarVisible     = FALSE;//TRUE;

			//重新布局
			pMainFrm->RecalcLayout();
			break;
		}
	case 7:
		{
			//显示DIALOGBAR
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);

			if(!pMainFrm->m_wndMyDialogBar.IsWindowVisible())
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			}	
			
			//重新布局
			pMainFrm->RecalcLayout();
			
			break;
		}
	case 8:
		{
			//册除读数线程
			if(ReadMeterThread != NULL)
			{
				delete ReadMeterThread;
				ReadMeterThread = NULL;
			}
			break;
		}
	case 9:
		{
			//重新布局
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);
			pMainFrm->m_wndMyDialogBar.Treeinitialize();
			pMainFrm->RecalcLayout();
			break;
		}
	case 10:
		{
		    break;
		}
	case 11:
		{
            CString        StrSql;
			StrSql = "DELETE FROM TB_HALTTIME";
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql); //删除驻留时间
			StrSql.Format("INSERT INTO TB_HALTTIME(HALTTIME_TIME) VALUES ('%4d-%02d-%02d %02d:%02d:%02d')",m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql); //保存驻留时间
			break;
		}
	case 12:
		{
           	//删除所有的数据
			m_Grid.DeleteAllItems();
			m_Grid.ShowWindow(SW_SHOW);		
			
			//是否显示历史数据
			m_IsHistory     =    FALSE;
			
			TRY { 
				m_Grid.SetFixedRowCount(1);
				m_Grid.SetRowCount(1);     //行
				m_Grid.SetColumnCount(13); //列
				//填充数据和行号
				CStringArray m_StrArrays;
				short         m_wide[13];
				m_StrArrays.SetSize(13);
				m_StrArrays[0]  = "序号";
				m_wide[0]       =  36;
				m_StrArrays[1]  = "读表类型";
				m_wide[1]       =  85;
				m_StrArrays[2]  = "用户名称";
				m_wide[2]       =  95;
				m_StrArrays[3]  = "用户编号";
				m_wide[3]       =  60;
				m_StrArrays[4]  = "地址";
				m_wide[4]       =  125;
				m_StrArrays[5]  = "模块号";
				m_wide[5]       =  60;
				m_StrArrays[6]  = "电表号";
				m_wide[6]       =  80;
				m_StrArrays[7]  = "线路名称";
				m_wide[7]       =  60;
				m_StrArrays[8]  = "母线-线-相-协议";
				m_wide[8]       =  96;
				m_StrArrays[9]  = "变台名称";
				m_wide[9]       =  65;
				m_StrArrays[10]  = "类型";
				m_wide[10]       =  60;
				m_StrArrays[11] = "读表值";
				m_wide[11]       =  75;
				m_StrArrays[12] = "时间";
				m_wide[12]       =  115;
				
				DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
               #ifndef _WIN32_WCE
				dwTextStyle |= DT_END_ELLIPSIS;
               #endif
				
				for (int col = 0; col < m_Grid.GetColumnCount(); col++)
				{ 
					GV_ITEM Item;
					Item.mask = GVIF_TEXT|GVIF_FORMAT;
					Item.row = 0;
					Item.col = col;
					Item.nFormat = dwTextStyle;
					Item.strText.Format("%s",(m_StrArrays[col]));
					m_Grid.SetItem(&Item);
					m_Grid.SetColumnWidth(col,m_wide[col]); 
				}
				
				//只读状态
				m_Grid.SetModified(FALSE,-1,-1);
				//标题
				m_Grid.m_title  = "";
				
				m_Grid.SetBkColor(RGB(255,255,255));
				
				m_Grid.Invalidate();
				m_Grid.Refresh();
			}
			CATCH (CMemoryException, e)
			{
				e->ReportError();
				e->Delete();
				return 0;
			}
			END_CATCH
	
			SurrenderWindowMessage();//交出window控制权
			break;
		}
	case 13:
		{
			CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			
			//处理过理的数据
			if(m_saveyears < 1)
			{
				DealOverTimeData(1);
			}
			else
			{
				DealOverTimeData(m_saveyears);
			}
			
			pMainFrm->m_wndMyDialogBar.InitializeCombo();
			break;
		}
	case 14:
		{
			//如果在连接状态时,强制退出线程
			if(m_IsConnect || m_Com.GetCDHolding())
			{
				
				if(ReadMeterThread != NULL)
				{
					//发驻留时间到了,如果原来在读表就退出读表
					m_StartRead    =   FALSE;
					//释放CPU时间
					SurrenderWindowMessage();
					Sleep(2000);
					//释放CPU时间
					SurrenderWindowMessage();
				}
				
			}
			
			//如果线程没有运行
			if(ReadMeterThread == NULL)
			{	
				//修改拔号或自动侦听状态
				ModifyDialInternetStatus();
				
			}
			break;
		}
	case 15:
		{
			//检测线路的运行状态,不在表中作标志
			CheckLineRun();
			break;
		}
	case 16:
		{
		         
			DWORD            dwStatus;

			if(ReadMeterThread != NULL)
			{
				
				VERIFY(::GetExitCodeThread(ReadMeterThread->m_hThread,&dwStatus));
				
				if(dwStatus == STILL_ACTIVE)
				{
					//如果为运行状态,则终止
					m_StartRead    =      FALSE;
					PostMessage(WM_EVENT,16, 0);
				}
				else
				{	
					//如果已经终止,则删除该线程
					delete ReadMeterThread;
					ReadMeterThread = NULL;
				}				
				
			}

			break;
		}
	case 17:
		{
			//测试无线模块电流电压
			CheckWireLess();
			break;
		}
	case 18:
		{
		    //处理无功补偿表补偿操作
            WuGongDeal("ALL");
			break;
		}
	case 19:
		{
		    //处理无功补偿表补偿结果
           	m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 1, m_StrArray[1]);	
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 10, m_StrArray[10]);
			m_Grid.Invalidate();
			m_Grid.Refresh();	
			
			//只读状态
			m_Grid.SetModified(FALSE,-1,-1);
            break;
		}
	case 20:
		{
			//得到发驻留信息的母线和协议种类
			GetSendZhuLiuInformation();
			break;
		}
	}
	return 0;
	
}

//清除多余的数据
BOOL CIFRMView::WipeOffSpilthData()
{
	//条件字符
	CString  Condtion,str;
	
	//变电站编号
	int         StationNo;
	
	long Size         =  ReceiveByteArray.GetSize();
	
   //以0x10开头的为固定帧格式长度为6
	switch(ReceiveByteArray[0])
	{
	case 0x10://处理固定帧格式
		{   
			
			//长度不对的话
			if(ReceiveByteArray.GetSize() != 6)
			{
				//删除字节数组
				ReceiveByteArray.RemoveAll();
				return  FALSE;
			}
			
			//记下变电站号
			LowAddress     =  ReceiveByteArray[2];
			HighAddress    =  ReceiveByteArray[3];
			
			//变电站编号
			StationNo = ReceiveByteArray[2] + ReceiveByteArray[3] * 256;
			Condtion.Format("atoi(USER_STATIONNO)=%d",StationNo);
			
			//写入日志
//			WriteToLog(Condtion);
			
			//判断是不是本站的信息
			//	if(CDataBaseInstance::GetAllRecordsCount("TB_USER",Condtion) < 1)
			{
				
				//校验和不对的话
				if((ReceiveByteArray[1] + ReceiveByteArray[2] + ReceiveByteArray[3])%256 != ReceiveByteArray[4])
				{
					//发送检验码错误
					//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					SendMessageToElectricOffice(1);
					//删除字节数组
					ReceiveByteArray.RemoveAll();
					return  FALSE;
				}
				
			}
			
			//以0x10开头的为固定帧格式
			break;
		}
	case 0x68://处理可变帧格式
		{
			
			//检验校验码,长度
			int length = ReceiveByteArray[1] + ReceiveByteArray[2] * 256;
			
			//长度错误的话
            if( length + 6 != ReceiveByteArray.GetSize())
			{
				//删除字节数组
				ReceiveByteArray.RemoveAll();
				return  FALSE;
				
			}
			
			//记下变电站号
			LowAddress     =   ReceiveByteArray[9];
			HighAddress    =  ReceiveByteArray[10];
			
			//变电站编号
			StationNo = ReceiveByteArray[9] + ReceiveByteArray[10] * 256;
			Condtion.Format("atoi(USER_STATIONNO)=%d",StationNo);
			
			//写入日志
//			WriteToLog(Condtion);
			
			//判断是不是本站的信息
			//if(CDataBaseInstance::GetAllRecordsCount("TB_USER",Condtion) < 1)
			{
				//校验码
				BYTE  CheckSum = 0;
				
				for(int i = 4; i < Size - 2; i++)
				{
                    CheckSum = CheckSum + ReceiveByteArray[i];
				}
				
				//校验和不对的话
				if(CheckSum != ReceiveByteArray[Size - 2])
				{
					
					//发送检验码错误
					//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
					SendMessageToElectricOffice(1);
					
					//删除字节数组
					ReceiveByteArray.RemoveAll();
					return  FALSE;
					
				}
				
			}
			break;
			
		}
		
	}
	return TRUE;
}


//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
void CIFRMView::SendMessageToElectricOffice(short kinds)
{
	SendByteArray.RemoveAll();
	SendByteArray.Add(0x10);
	switch(kinds)
	{
	case 0:
		{  
			//成功执行
			SendByteArray.Add(0x8b);
			break;
		}
	case 1:
		{
			//检验码不对
			SendByteArray.Add(0x85);
			break;
		}
	case 2:
		{
			//无数据
			SendByteArray.Add(0x89);
			break;
		}
		
	}
	SendByteArray.Add(LowAddress); //地址
	SendByteArray.Add(HighAddress);//地址
	
	SendByteArray.Add((SendByteArray[1] + LowAddress + HighAddress)%256);//校验码
	SendByteArray.Add(0x16);       //结束标志
	
	//二进制方式发送
	//kinds           种类  0-串口发送  1-电话拔号发送  2-TCP/IP发送m_sendkind
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	SelectSendCByteArray(m_sendkind,TRUE,FALSE);
}


//CString  m_address 12位地址
//short kinds     	//14种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10－尖峰电量 11－峰电量 12－谷电量 13－平电量 14-功率因数
float CIFRMView::ReadDataFrom485Com2(CString m_address,short kinds)
{
	
	//二进制方式
	COleVariant            varInput; 
	long                     ix,l,u;
	BYTE                   TempByte;
	CString                StrValue;
	float        GetValue   =    -1;
    BOOL     m_StartAdd     = FALSE;
	StrValue.Format("%s",m_address);
	int Length = StrValue.GetLength();
	
	//第二个口为读线总表和站总表专用485
	if(Ports[1] == FALSE || kinds == 1 || kinds == 3 || kinds > 15)
	{
		return -1;
	}
	
	//演示版本
	if(AppInfo::Instance().m_YanShi)
	{ 
		CTime time = CTime::GetCurrentTime();
		GetValue   = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01;//解码
		Sleep(500);
		return  GetValue;
	}
	
	//地址长度不够
	if(Length < 12)
	{

		for(int i = 0; i < 12 - Length; i ++)
		{
			StrValue = "0" + StrValue;
		}
	}
	
    SendByteArray.RemoveAll();
	//以唤醒接收方处于连接状态
	SendByteArray.Add(0xFE);
	SendByteArray.Add(0xFE);
	
	//指令开始
	SendByteArray.Add(0x68);
	
	//地址低在前，高在后
	int i;
	for( i = 0; i < 6; i++)
	{
		TempByte = atoi(StrValue.Right(2));
		SendByteArray.Add(TempByte/10*16 + TempByte%10);
		StrValue = StrValue.Left(StrValue.GetLength() - 2);
	}
	/*
	0x9010 -正向有功 + 0x33 低－》高
	9020   - 反向有功
	9110   - 正向无功
	9120   - 反向无功
	B611   - A电压  两个字节
	B612   - B电压
	B613   - C电压
	B621   - A电流 两个字节两位小数
	B622   - B电流
	B623   - C电流
	*/
	//有功      FE FE 68 16 66 17 00 00 00 68 01 02 43 C3 6C 16
	//无功      FE FE 68 16 66 17 00 00 00 68 01 02 43 C4 6D 16
	//电流:     68 AA AA AA AA AA AA 68 01 02 54 E9 0C 16 
	//回的数Rx: 68 59 00 00 00 00 00 68 81 04 54 E9 33 33 51 16 
	//电压Tx:   68 AA AA AA AA AA AA 68 01 02 44 E9 FC 16 
    //回的数Rx: 68 59 00 00 00 00 00 68 81 04 44 E9 63 35 73 16 
	SendByteArray.Add(0x68);
	SendByteArray.Add(0x01);
	SendByteArray.Add(0x02);
	
	
	switch(kinds)
	{
	case 0:
		{   
			//0－－－有功 
			SendByteArray.Add(0x43);
			SendByteArray.Add(0xC3);
			break;
		}
	case 2:
		{   
			//2－－－无功 
			SendByteArray.Add(0x43);
			SendByteArray.Add(0xC4);
			break;
		}
	case 4:
		{   
			/*
			B621   - A电流 两个字节两位小数
			B622   - B电流
			B623   - C电流
			*/
			//4－－－A相电流 
			SendByteArray.Add(0x54);
			SendByteArray.Add(0xE9);
			break;
		}	
	case 5:
		{   
			//5－－－B相电流 
			SendByteArray.Add(0x55);
			SendByteArray.Add(0xE9);
			break;
		}	
	case 6:
		{   
			//6－－－C相电流
			SendByteArray.Add(0x56);
			SendByteArray.Add(0xE9);
			break;
		}
	case 7:
		{   
		/*
		B611   - A电压  两个字节
		B612   - B电压
		B613   - C电压
			*/
			//7－－－A相电压
			SendByteArray.Add(0x44);
			SendByteArray.Add(0xE9);
			break;
		}
	case 8:
		{   
			//8－－－B相电压 
			SendByteArray.Add(0x45);
			SendByteArray.Add(0xE9);
			break;
		}
	case 9:
		{   
			//9－－－C相电压  
			SendByteArray.Add(0x46);
			SendByteArray.Add(0xE9);
			break;
		}
	case 10:
		{   
			//10－－－尖  
			SendByteArray.Add(0x44);
			SendByteArray.Add(0xC3);
			break;
		}	
	case 11:
		{   
			//11－－－峰  
			SendByteArray.Add(0x45);
			SendByteArray.Add(0xC3);
			break;
		}
	case 12:
		{   
			//12－－－平  
			SendByteArray.Add(0x46);
			SendByteArray.Add(0xC3);
			break;
		}
	case 13:
		{   
			//13－－－谷  
			SendByteArray.Add(0x47);
			SendByteArray.Add(0xC3);
			break;
		}
	case 14:
		{   
			//14－－－功率因数  
			SendByteArray.Add(0x83);
			SendByteArray.Add(0xE9);
			break;
		}
		
	}
	
	//检验码
	int Size    =  SendByteArray.GetSize();
	TempByte    =                        0;
	
	for( i = 2; i < Size; i ++)
	{
		TempByte = TempByte + SendByteArray[i];
	}
    SendByteArray.Add(TempByte);
	
	//结束标志
    SendByteArray.Add(0x16);
	
    Size    =  SendByteArray.GetSize();
	
	
	for( i = 0; i < Size; i ++)
	{
		StrValue.Format("SendByteArray[%d]=%0x",i,SendByteArray[i]);
		//	WriteToLog(StrValue);
	}
	
	
	//二进制方式发送
    m_485MsComm.SetOutput(COleVariant(SendByteArray));
	
	Sleep(600);
	
	ReceiveByteArray.RemoveAll();
	
	//取值计算
	varInput = m_485MsComm.GetInput();
	
	if(varInput.parray != NULL) 
	{ 
		
		//得到安全数组上界
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//得到安全数组下界
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//得到数组中数据值
		for(ix = l; ix <= u; ix ++)
		{
			
			SafeArrayGetElement(varInput.parray,&ix,&TempByte);
			
			if(TempByte == 0x68)
			{
				m_StartAdd = TRUE;
			}
			
			if(m_StartAdd)
			{
				ReceiveByteArray.Add(TempByte);
			}
			//StrValue.Format("%0x",TempByte);
			//WriteToLog(StrValue);
			
		}
		
	}
	
	//分析数据值
    Size    =  ReceiveByteArray.GetSize();
	if(Size > 0)
	{
        
		//找0x16结尾的位置
		for(ix = Size - 1; ix <= 0; ix--)
		{
			
			if(ReceiveByteArray[ix] == 0x16)
			{
				break;
			}
			
		}
		
		
		//查检验和
		TempByte = 0;
		
		for(i = 0; i < Size - 2; i++)
		{
			TempByte = TempByte + ReceiveByteArray[i];
		}
		
		//检验和相等的话
		if(TempByte == ReceiveByteArray[Size - 2])
		{
			
			if(ix > 4)
			{
				if(kinds >= 4 && kinds <= 6)
				{
					//电流
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16) + ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16) * 0.01);
				}
				else if(kinds >= 7 && kinds <= 9)
				{  
					//电压	
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16)*100 +  ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16));
				}	
				else if(kinds == 14)
				{
					//功率因数
					GetValue = float(int(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16)*100 +  ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16))/10)*0.01;
				}
				else
				{
					//有功无功
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16) * 10000 + ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16) * 100 + ((ReceiveByteArray[ix - 4] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 4] - 0x33)%16) + ((ReceiveByteArray[ix - 5] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 5] - 0x33)%16) * 0.01);
				}
			
			//	Beep(5000,400); 
			//	Beep(5000,400);	
				
			}
			
		}
		
	}
	
	/*
	//关闭串行端口
	if(m_485MsComm.GetPortOpen()) //打开串口   
	{
	m_485MsComm.SetPortOpen(FALSE);
	}
	*/
	return GetValue;
}

//电流转换成对应的值发出
BYTE CIFRMView::ConversionCurrentValue(BYTE Source)
{   
	
	BYTE GetValue    =   0;
	int Current[6]   = {20,30 ,40 ,50 ,60 ,70 };
	int DataValue[6] = {0xc8,0x12c,0x1a8,0x204,0x230,0x273};
	int i;
	//如电流是20A的话，发出的数为0xc8
	for( i = 0; i < 6; i ++)
	{
		
		if(Source <= Current[i])
		{
			if(i == 0)
			{
                GetValue = BYTE(DataValue[0]/10);
			}
			else if(i == 5)
			{
				GetValue = BYTE(DataValue[5]/10);
			}
			else
			{
                GetValue = BYTE((DataValue[i-1] + (Source - Current[i-1])*1.00/(Current[i] - Current[i -1])*(DataValue[i]-DataValue[i-1]))/10);
			}
			break;
		}
		
	}
	
	if(i > 5)
	{
		GetValue = BYTE(DataValue[0]/10);
	}
	
	return GetValue;
}

//收到的值转换成对应的电流值
float CIFRMView::SwitchCurrentValue(float DeValue)
{
	float m_Current  =   0;
	int   Current[6] = {20 ,30 ,40 ,50 ,60 ,70 };
	int DataValue[6] = {0xc8,0x12c,0x1a8,0x204,0x230,0x273};
	int i ;
	for( i = 0; i < 6; i ++)
	{
		
		if(DeValue <= DataValue[i])
		{
			
			if(i == 0)
			{
                m_Current  = float(Current[0]);
			}
			else if(i == 5)
			{
				m_Current  = float(Current[5]);
			}
			else
			{
                m_Current  = float(Current[i-1] + (DeValue - DataValue[i-1])*1.00/(DataValue[i] - DataValue[i -1])*(Current[i]-Current[i-1]));
			}
			break;
			
		}
		
	}
	
	if(i > 5)
	{
		m_Current = float(Current[5]);
	}
	return m_Current;
}

//得到手拉手信息
void CIFRMView::GetHandModuleInformation()
{
	
	CDatabase          db;
	CString        strSql;
	CString strValue = "";
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		
		//得到记录个数
		long fields = CDataBaseInstance::GetAllRecordsCount("TB_HAND","ALL"); 
		
		if(fields > 0)
		{
			
			strSql = "SELECT HAND_NO,HAND_STATIONNAME,HAND_STATUS FROM TB_HAND";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//手拉手编码
			rs.GetFieldValue((short)0,strValue);
			m_handno = atoi(strValue);
            
			//手拉手电站名称
            rs.GetFieldValue((short)1,strValue);
			
			//是否定时发送信号
			rs.GetFieldValue((short)2,strValue);
			strValue.TrimLeft();
			strValue.TrimRight();
            m_status  = atoi(strValue);
			
		}
		//关闭数据库
		rs.Close( );
		db.Close( );
	}
	
}

//检测有几个端口能用
void CIFRMView::GetComPorts()
{
	HANDLE				m_hComm;
    CString             ComStr;
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
		
		if (m_hComm == INVALID_HANDLE_VALUE)
		{
			Ports[i] = FALSE;
		}
		else
		{
			Ports[i] = TRUE;
			CloseHandle(m_hComm);
		}
		
	}
	
}

//设置定时器读表
void CIFRMView::SetTimersign()
{

	KillTimer(1);

	if(m_status)
	{

		//不在自动读表状态
		if(!m_IsAutoSending)
		{
			//设置10分钟一次
			SetTimer(1,m_SettimerValues,NULL);
    		OnTimer(1);
		}

	}
	else
	{

	    //不在自动读表状态
		if(!m_IsAutoSending)
		{
			//设置10分钟一次
			KillTimer(1);
   		}

	}

}


void CIFRMView::OnTimecheck() 
{ 
    //判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

    m_StartRead = TRUE;
	
	CTimeCheckDlg dlg;
	dlg.DoModal();

	m_StartRead = FALSE;
}

//设置时间
//格式: 年-月-日-时-分-秒
void CIFRMView::SetLocalTimes(CString times)
{	
	
    //定义变量
	CString       str[6];
	int    colum     = 0;
	int    k         = 0;
	
	//去空格
	times.TrimLeft();
	times.TrimRight();
	
	//以-为分隔符
	while(times.Find('-') != -1)
	{
		k   =  times.Find('-');
		if(k != -1)
		{
            str[colum] =  times.Left(k);
			times  = times.Right(times.GetLength() - k - 1);
			
			if(colum > 4)
			{
				break;
			}
			colum++;
		}
	}
	
	//秒
	str[5] = times;
	
	SYSTEMTIME systime;
	systime.wYear          = atoi(str[0]);      //年
	systime.wMonth         = atoi(str[1]);      //月
	systime.wDayOfWeek     =            0;
	systime.wDay           = atoi(str[2]);      //日 
	systime.wHour          = atoi(str[3]);      //时
	systime.wMinute        = atoi(str[4]);      //分
	systime.wSecond        = atoi(str[5]);      //秒
	systime.wMilliseconds  = 700;               //毫秒
	
	if(::SetLocalTime(&systime))
	{
		//AppInfo::Instance().m_WhichKind  -TRUE   变电站版本 -FALSE  电局版
		if(AppInfo::Instance().m_WhichKind)
		{
			//发送信息
		//	SendContionStr = "BEGINS;MESSAGE:1:远程设置时间完毕!;ENDS";
		//	SendMessage(WM_EVENT, 4, 0);
			return;
		}
		
	}
	
}

BOOL CIFRMView::SetRemoteTime(CString Str)
{
	//如果连接好的话
	return SelectSendString(m_sendkind,Str,TRUE,FALSE,TRUE);
}

void CIFRMView::KillAotoReadMeter()
{
	CString   ConStr;
	
	if(MessageBox("你想取消定时发驻留读表吗？","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//变电站版
		if(AppInfo::Instance().m_WhichKind == TRUE)
		{

			//有读表的话，退出
			m_StartRead = FALSE;
			
			//如果没有手拉手
			if(!m_status)
			{
				KillTimer(1);
			}

			KillTimer(2);
			KillTimer(3);
		
			//数组中日期下标参数赋为0
			m_statusstr     =    "";
			status("                         ");
			m_IsAutoSending =    FALSE;
			SendContionStr  =    "BEGINS;MESSAGE:0:自动发驻留自动读表已取消!;ENDS";
			SendMessage(WM_EVENT, 4, 0);
			status("【自动发驻留自动读表已取消】");
			
			//写入日志文件
			CString str;
			//时间
			CTime timet = CTime::GetCurrentTime();
			str.Format("【%4d-%02d-%02d %02d:%02d:%02d】取消发定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			WriteToLog(str);
			//定时按钮置为FALSE
	        ShowDingShiButton(FALSE);
		
		}
		else
		{
		    
			//电局版
			ConStr = "BEGINS;DATAS:4:StopData;停止;ENDS";
			
			if(SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE) == TRUE)
			{	
				
				//状态栏信息取消
				m_StartRead      =   FALSE;	
				m_statusstr      =      "";
				status("                         ");
				m_IsAutoSending  = FALSE;
				Sleep(1000);
				//定时按钮置为FALSE
				ShowDingShiButton(FALSE);
				
			}
		
			m_StartRead = FALSE;
			
			
		}
	
	}

}


//二进制模式接收数据
void CIFRMView::BinarySystemReceive()
{

	BYTE                      bit; 
	COleVariant          varInput; 
	long                 ix,k,l,u; 
	short       Received     =  0; //判段接收数据的种类	1 －本软件的接收 2－与湖南长沙来的通讯
	int i = 0, Size  = 0,m_length;
	CString                   str;
    //CRC值
    unsigned         crc = 0xffff;
	
	varInput  =  m_Com.GetInput();
	
	if(varInput.parray != NULL) 
	{ 
		
		//得到安全数组上界
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//得到安全数组下界
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//得到数组中数据值
		for(ix = l; ix <= u; ix ++)
		{
			
			SafeArrayGetElement(varInput.parray,&ix,&bit);
			
			//交出window控制权
			//SurrenderWindowMessage();
			
			//要连接后才能发送	//如果连接成功了的话short  m_sendkind;// 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_Com.GetCDHolding()
			if((m_Com.GetCDHolding() && m_sendkind == 1) || (m_Com.GetPortOpen() && m_sendkind == 0 ))//
			{
				
				ReceiveByteArray.Add(bit);
				
				//末位0x16检查,检查送来的数据是否满足条件
				if(bit == 0x16)
				{	
					
					//检验是否数据已全部接收完
					Size         =  ReceiveByteArray.GetSize();
					
					//检查是否有多余的数
					for( i = 0; i < Size; i ++)
					{
						
						//首位是0x68判断
						if(ReceiveByteArray[i] == 0x68)
						{
							
							//位数够的话
							if(Size - i > 3)
							{
								//长度要够
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 7 == Size - i))
								{
									Received = 1; //是本软件本地和远程之间的通讯
									break;
								}

                                //长度要够
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 6 == Size - i))
								{
									Received = 2; //是本软件和湖南长沙之间的通讯
									break;
								}

							}
							//位数够的话
							
						}
						//首位是0x68判断
						
						//首位是0x10判断,发送成功的标志
						if(ReceiveByteArray[i] == 0x10)
						{
							
							//位数够的话
							if(Size - i >= 5 )
							{
								
								//收到远程机器下达的停止信息
								if(ReceiveByteArray[i+1] == 0x8b && ReceiveByteArray[i+2] == 0x44 && ReceiveByteArray[i+3] == 0x44 && (ReceiveByteArray[i] + ReceiveByteArray[i+1] + ReceiveByteArray[i+2] + ReceiveByteArray[i+3])%256 == ReceiveByteArray[i+4] )
								{
                                	//接收字节清空
									ReceiveByteArray.RemoveAll();
									m_StartRead = FALSE;
									
									//停止定时读表
									KillTimer(1);	
									//演示或隐藏动画
			                        OperationAnimation(FALSE);
									return;
								}

								//收到湖南威胜的信号
								if((ReceiveByteArray[i+1] + ReceiveByteArray[i+2] + ReceiveByteArray[i+3])%256 == ReceiveByteArray[i+4] )//255
								{
								    Received        =          2; //是本软件和湖南长沙之间的通讯
									break;
								}
								
							}
							//位数够的话
							
						}
						//首位是0x10判断,发送成功的标志
						
					}
					//检查是否有多余的数
					
					
				}
			
				//末位0x16检查,送来的数据是否满足条件完毕
				
			}
			else
			{
				//没有拔通时,将字节转换为CString型变量
				char a = *(char*)(&bit);      
				str.Format("%c",a);	
				//如果在连接成功之前的值
				StatusStr = StatusStr + str;
				status(StatusStr);
				//分析拔号产生的提示
				AnalyseDial(StatusStr); 
				
			}
		
		}
		//取出数据
	}

	//根据传来的数据,分析其指令
	if(Received == 1) //是本软件本地和远程之间的通讯
	{	
		//找出0x68或0x10的位置
		if(i + 6 <= Size)
		{
			//删除0x68前多余的数据，前四位也删除，此时便是我们要的数据、CRC检验低位、CRC检验高位、结尾0X16
			for( k = 0; k < i + 4; k ++)
			{
				
				ReceiveByteArray.RemoveAt(0,1);
			}
			
		}
	
		bit      =     0;

  	    m_length = ReceiveByteArray.GetSize();
		
		//分析数据检验和,整个数据帧包括：数据、CRC检验低位、CRC检验高位、结尾0X16
		for( k = 0; k < m_length - 1 ; k ++)
		{	
			//测试时用
			//调用CRC检验
            crc = Crc16( crc , ReceiveByteArray[k]) ; 
		}
		
		//如果crc值不为0的话
		if(crc != 0)
		{
			//这一帧是错误的
			ReceiveByteArray.RemoveAll();
			return;
		}
	
		//如果检验和正确的话，清空字符
		m_strReceiveChar  = "";
		
		//拼成字符串形式
		for(ix = 0; ix < ReceiveByteArray.GetSize() - 3; ix ++)
		{
			
			bit = ReceiveByteArray[ix];
			
			
			//将字节转换为CString型变量 
			char a = *(char*)(&bit);       
            
			//如果是*号,则转成空格
			if( a == '*')
			{
				str = " ";
			}
			else
			{
				str.Format("%c",a);
			}
		
			//累加值 
			m_strReceiveChar += str;
			
		}
	  
		ReceiveByteArray.RemoveAll();

     	//分析数据,对接收到数据做必要处理
		m_strReceiveChar.TrimLeft();
		m_strReceiveChar.TrimRight();
		str   =     m_strReceiveChar;
		m_strReceiveChar    =     "";
        
		AnalyseOrder(str);

	}
	else if(Received  == 2)
	{
	
		//是本软件和湖南长沙之间的通讯
		//删除0x68前多余的数据
		for( k = 0; k < i ; k ++)
		{
			ReceiveByteArray.RemoveAt(0,1);
		}
		
		//与长沙威远通信连接
        AnalyseReceivedByteArray();
	}

}


//湖南威胜接收程序
void CIFRMView::HuNanWeiYuanReceive()
{

	BYTE                    bit; 
	COleVariant        varInput; 
	long                 ix,l,u; 
	BOOL       Received	= FALSE;	
	
	//要连接后才能发送
	if(m_Com.GetCDHolding() || m_Com.GetPortOpen())
	{
		
		varInput = m_Com.GetInput();
		
		if(varInput.parray != NULL) 
		{ 
		
			//得到安全数组上界
			SafeArrayGetLBound(varInput.parray,1,&l);
			
			//得到安全数组下界
			SafeArrayGetUBound(varInput.parray,1,&u);
			
			//得到数组中数据值
			for(ix = l; ix <= u; ix ++)
			{
				SafeArrayGetElement(varInput.parray,&ix,&bit);
				
				//如果太大的话，则三加删除字节数组
				if(ReceiveByteArray.GetSize() > 65536)
				{
					ReceiveByteArray.RemoveAll();
					
				}
				
				ReceiveByteArray.Add(bit);
				
				//末位0x16检查,检查送来的数据是否满足条件
				/***************************************/
				if(bit == 0x16)
				{	
					
					//检验是否数据已全部接收完
					long Size         =  ReceiveByteArray.GetSize();
					
					//检查是否有多余的数
					int i;
					for( i = 0; i < Size; i ++)
					{
						
						//首位是0x68判断
						if(ReceiveByteArray[i] == 0x68)
						{
							
							//位数够的话
							if(Size - i >= 3)
							{
								//长度要够
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 6 == Size - i))
								{
									Received = TRUE;
									break;
								}
								
							}
							
						}
						
						//首位是0x10判断
						if(ReceiveByteArray[i] == 0x10)
						{
							//是6位长的话
							if(Size - i == 6)
							{
								Received = TRUE;
								break;
							}
							
						}
						
					}
					
					
					//接收数据完毕，
					if(Received)
					{
						//找出0x68或0x10的位置
						if(i + 6 <= Size)
						{
							//删除0x68或0x10前多余的数据
							for(int k = 0; k < i; k ++)
							{
								
								ReceiveByteArray.RemoveAt(0,1);
								
							}

							break;
						}
						
					}
					
					
				}
				/***************************************/
				//末位0x16检查,送来的数据是否满足条件完毕
				
			}
			
		}
		
		//根据传来的数据,分析其指令
		if(Received)
		{	
			AnalyseReceivedByteArray();
		}
		
	}
	else
	{
		//清空缓冲区
		m_Com.GetInput();
	}
	
}

void CIFRMView::OnUpdateLstSave(CCmdUI* pCmdUI) 
{
   // pCmdUI->Enable(m_lists.IsWindowVisible() && m_lists.GetSelectedCount() > 0);
}


//0 --- 数据不一致  1------参数传输错误  2
void CIFRMView::SendErrorMessage(short kinds)
{
	switch(kinds)
	{
	case 0:
		{	
			//提示信息
            SendContionStr = "BEGINS;MESSAGE:0:请先更新两边数据，保持一致再操作!;ENDS";
			break;
		}
	case 1:
		{
			//提示信息
			SendContionStr = "BEGINS;MESSAGE:0:参数传输错误,请重新再传!;ENDS";
			break;
		}
	case 2:
		{
			return;
    //      SendContionStr = "BEGINS;MESSAGE:1:命令接收正确，正在执行相关指令!;ENDS";
			break;
		}
	}
	
	//发送返回信息
	SendMessage(WM_EVENT, 4, 0);

}

CString CIFRMView::GetStationNo()
{
	
	CDatabase            db;
	CString     Str = "";
	
	//记录个数
	long m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL");

	if(m_records <= 0)
	{
		return "";
	}

    //-USER_STATIONNO
	//打开数据库

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset        rs(&db);
		Str = "SELECT USER_STATIONNO FROM TB_USER ORDER BY USER_STATIONNO";
		rs.Open(CRecordset::forwardOnly,Str);
		
		//得到记录个数
		rs.GetFieldValue((short)0,Str);

		//去掉空格
        Str.TrimLeft();
		Str.TrimRight();

		//关闭数据库
		rs.Close( );
		db.Close( );				
	}

	return Str;

}


//定天读数据
void CIFRMView::OnAutoreadset() 
{ 
  

	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}	
	
	CString      ConStr,str;
	CAutoDateReadModuleDlg dlg;

	if(dlg.DoModal()== IDOK)
	{
		//变电站
		if(AppInfo::Instance().m_WhichKind)
		{
	
			//定时发驻留定时读表
			m_StartRead     =  TRUE;
			//行号起始为0
			m_ListRows      =     0;
			//次数为0
			m_times         =     1;
			//提示信息
			SendContionStr.Format("BEGINS;MESSAGE:0:远程自动发驻留自动读数据设置成功!\r\n%s;ENDS",m_statusstr);
			//发送返回信息
			SendMessage(WM_EVENT, 4, 0);

			//停止执行此操作
			m_StartRead     = FALSE;
			//时间
			CTime timet = CTime::GetCurrentTime();
			str.Format("【%4d-%02d-%02d %02d:%02d:%02d】设置定时驻留读表:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
			WriteToLog(str);
		
			//取消10分钟检查一次检查
			KillTimer(1);
			ShowDingShiButton(TRUE);//定时按钮置为TRUE	
			
			m_IsAutoSending   =  TRUE;//驻留状态标志
			
			//初始化电流
            InitializeCurrent();

			StatusStr.Format("【定%d时驻留,先间隔半小时读%d次,后间隔八小时读%d次】",m_parameter[104],m_parameter[106],m_parameter[108]);
			status(StatusStr);

			//为22协议加的，半点或整点才可用, 逢10的倍数分钟可用
			m_SettimerValues = ((10 - (timet.GetMinute()%10))*60 - timet.GetSecond())*1000;
			m_ReadModuleTimes   =     0;//读表次数设为0
			//发驻留次数
	        m_SendGarrisonTimes =     0;	
			m_zhuliukinds       =     0;//0 按表计种类下驻留 1 按日期下驻留
        	SetTimer(1,m_SettimerValues,NULL); //设置定时器,10分钟检查一次
		}
		else
        { 
			
			ConStr  = "BEGINS;COMMAND:29:";
					 
			for(int i = 0; i < 110; i ++)
			{	
				//初始化发驻留读表用的110个参数
				str.Format("%d",m_parameter[i]);
				ConStr = ConStr + str + ";";
			}
			
			//参数个数
			ConStr = ConStr + "ENDS";
			
			if(SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE) == TRUE)
			{				
    			//发没有发驻留变量
				m_IsAutoSending =  TRUE;
				//定时按钮置为TRUE
	            ShowDingShiButton(TRUE);
			}
			
    		m_StartRead     = FALSE;

		}
		
	}
}

void CIFRMView::OnBREAkSOMEDAY() 
{
    //取消定天发驻留读表
	KillAotoReadMeter();
}

void CIFRMView::OnUpdateOwemoney(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}


//发送用户数据库
void CIFRMView::OnPassuserdata() 
{
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

	BOOL  m_connectting = FALSE;

	switch(m_sendkind)
	{
	case 0:
		{
			m_connectting = m_Com.GetPortOpen();
			break;
		}
	case 1:	
		{
			m_connectting = m_Com.GetCDHolding();
			break;
		}
	case 2:	
		{
			m_connectting = m_IsConnect;
			break;
		}
	}

	if(m_connectting)
	{

		//得到对话条的所选条件
		if(!GetDialogBarStr())
		{
			return;
		}
	
		SurrenderWindowMessage();
		
		//传送用户数据从电局->变电站
		if(MessageBox("你想远程传送数据到变电站吗？"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
		
			//检查变电站的个数
			if(!CheckStations(m_ModuleFindContionStr))
			{
				return;
			}
				
			m_StartRead =  TRUE;

			//提出符合条件的记录
			CString m_filename,m_SqlStr;
			m_filename.Format("%s%s%s",GetFolder(),"TB_USER",".TXT");
			
			long fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
			
			if(m_ModuleFindContionStr == "ALL")
			{
				m_SqlStr.Format("SELECT * FROM %s","TB_USER");
			}
			else
			{
				m_SqlStr.Format("SELECT * FROM %s WHERE %s","TB_USER",m_ModuleFindContionStr);
			}
			
			if(fields > 0)
			{
				
				//告诉对方有多少数据
				WriteDataToTextFile("TB_USER",m_SqlStr,fields,m_filename);
				
				//告诉对方没有数据
				SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS","TB_USER",fields);
				SendMessage(WM_EVENT, 4, 0);
			}
			else
			{
				m_StartRead = FALSE;
				MessageBox("对不起，此表中没有满足此条件的数据信息!","警告",MB_OK|MB_ICONWARNING);
				return;
			}
		}

	}
	else
	{
		MessageBox("端口打开错误!","",MB_OK|MB_ICONWARNING);
		return;
	}
	
}

BOOL CIFRMView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	
	if (wParam == (WPARAM)m_Grid.GetDlgCtrlID())
    {
        *pResult = 1;
        GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;
        if (GVN_GETDISPINFO  == pDispInfo->hdr.code)
        {
			SetGridItem(pDispInfo);
			return TRUE;
        }
    }
	
	return CFormView::OnNotify(wParam, lParam, pResult);
}

void CIFRMView::SetGridItem(GV_DISPINFO *pDispInfo)
{
	
	//m_pMapFile->SetGridText(pDispInfo);
	if((pDispInfo->item.col ==0) && (pDispInfo->item.row != 0))
	{
	  //pDispInfo->item.iImage = rand()%m_ImageList.GetImageCount();
		pDispInfo->item.mask  |= (GVIF_IMAGE);
	}

	if((pDispInfo->item.col == 6) && (atoi(pDispInfo->item.strText) > 2000))
	{
		COLORREF clr = RGB( 128, 128,  128);
		pDispInfo->item.crBkClr = clr;             // or - m_Grid.SetItemBkColour(row, col, clr);
		pDispInfo->item.crFgClr = RGB(255,0,0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
		pDispInfo->item.mask |= (GVIF_BKCLR|GVIF_FGCLR);
	}
	
}

//得到对话条的所选条件
BOOL CIFRMView::GetDialogBarStr()
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//得到选择读表的条件
	m_ModuleFindContionStr = pMainFrm->m_wndMyDialogBar.SelectCondition();

	m_ModuleFindContionStr.TrimLeft();
	m_ModuleFindContionStr.TrimRight();
	
	if(m_ModuleFindContionStr.IsEmpty())
	{
		MessageBox("请选择数据范围,再运行!!"," ",MB_OK|MB_ICONWARNING);
		return  FALSE;
	}
	return TRUE;
}

void CIFRMView::OnUpdatePassuserdata(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}

void CIFRMView::OnUpdateShowdialogbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_DialogBarVisible == TRUE);
	pCmdUI->Enable(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0);
}

void CIFRMView::OnUpdatePhasetest(CCmdUI* pCmdUI) 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//得到选择读表的条件
   	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty()  && CRuntimeAccount::GetCurrentPrivilege() < 1);
	
}

void CIFRMView::OnUpdateTestreadtable(CCmdUI* pCmdUI) 
{	
	/*pCmdUI->Enable(FALSE);*/
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//选择条件
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}
	
}

void CIFRMView::OnRclickListss(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_POPUP); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_lists.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_LST_SAVE  , MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
		pPopupMenu->EnableMenuItem(ID_LST_SAVE  , MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);		
	*pResult = 0;
}


//树控件重新刷新一次
void CIFRMView::RefreshTree()
{
	//树控件重新刷新一次
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	//如果没有记录
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") <=  0)
	{
		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
		m_DialogBarVisible = FALSE;

	}
	else
	{
	
		pMainFrm->m_wndMyDialogBar.Treeinitialize();
		
		//DIALOGBAR是否可见
		if(m_DialogBarVisible)
		{

			pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
			pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			pMainFrm->RecalcLayout(TRUE);

		}

	}

	//重新布局
	pMainFrm->RecalcLayout();

}

void CIFRMView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);
	
}

void CIFRMView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	//不在自动驻留期间打印
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);
}

void CIFRMView::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	//不在自动驻留期间打印
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);	
}


void CIFRMView::OnUpdateHidedata(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(m_lists.IsWindowVisible());	
}

void CIFRMView::OnSavereportas() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	char szFilter[]	=	"工频畸变远程抄表EXCEL报告文件(*.CSV)|*.CSV|";
   	CFileDialog dlg(FALSE,"CSV","*.CSV",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	dlg.m_ofn.lpstrTitle="保存为:";
	
	if(dlg.DoModal() == IDOK)
	{
		//工频畸变远程抄表报告文件
		if(m_Grid.Save(dlg.GetPathName( ), ','/*数据分隔符*/))
		{	
			//置没有修改状态
			m_Grid.SetModified(FALSE,-1,-1);
		}
		status("成功保存完毕...");
		
	}
	
}

void CIFRMView::OnUpdateSavereportas(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(m_Grid.GetRowCount() > 0 && m_Grid.IsWindowVisible());	
}

//得到EXE文件目录
CString CIFRMView::GetFolder()
{
	CString Folder,filename;
	char   ExeFilePath[256];               //定义文件路径缓冲区  
   
	strcpy(ExeFilePath,__argv[0]);         //获取文件路径
	filename = AfxGetApp()->m_pszExeName;  //获取EXE程序名称

	Folder = ExeFilePath;                  //文件目录
	Folder = Folder.Left(Folder.GetLength() - filename.GetLength() - 4);//去文件名.EXE
	return Folder;
}


//得到文本文件行数
int CIFRMView::GetDataLines(CString FileName)
{
	char      s[300];
	FILE         *fp;
	int    lines = 0;
	if((fp=fopen(FileName,"r"))==NULL)
	{
		return  0;
	}
	else
	{
		while(!feof(fp))
		{
			fgets(s,300,fp);
			lines++;
		}
		fclose(fp);	
		return lines;
	}
}


//得到文本文件第*行的数据
CString CIFRMView::GetDataLineCString(CString FileName,int m_lines)
{
	CString  str = " ";	
	CFile         file;
	char        s[303];

	int          k = 0;

	if(file.Open(FileName,CFile::modeRead))
	{
		
		//一行最多存贮150个汉字
		if(file.GetLength() >= m_lines * 303 && file.GetLength()%303 == 0)
		{
			file.Seek((m_lines - 1)*303,CFile::begin);	
			file.Read(s,303);
			
			str  =  s;
			k    =  str.Find("\r\n");
		
			if(k != -1)
			{
				str = str.Left(k);
			}

		}
		file.Close();
	}	
	

	str.TrimLeft();
	str.TrimRight();
	return str;

}

//处理重复数据记录
//CString  m_DataName   表名
//CString  TxtFileName  导入文本文件
void CIFRMView::DealRepeatRecord(CString  m_DataName,CString TxtFileName)
{

	CString       m_DataNameTemp,SqlStr,Str;
    m_DataNameTemp     = m_DataName + "TMP";
	short   m_fileds   =                  0;

	//删除原来的有的临时表,有则删除原来的临时表
	//判断表是否存在
	if(IsCurveTableExist(m_DataNameTemp))
	{
		SqlStr.Format("DROP TABLE %s",m_DataNameTemp);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	}

	//生成临时表
    SqlStr.Format("SELECT * INTO %s FROM %s ",m_DataNameTemp,m_DataName);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	if(m_DataName == "TB_USER")
	{
		//如果是用户数据库
		SqlStr.Format("DELETE FROM %s","TB_USERTMP");
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	}

	//文本文件导入临时表
	SqlStr.Format("BULK INSERT IFRM..%s FROM '%s' WITH (DATAFILETYPE = 'char', FIELDTERMINATOR = ',', ROWTERMINATOR = '\n')",m_DataNameTemp,TxtFileName);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	//从临时表导入原来的数据
	if(m_DataName == "TB_USER")
	{
		
		//重复记录写入日志
		CDatabase     db;
		int   i    =   0;
		
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			CDaoDatabase* m_pDatabase = new CDaoDatabase();
			m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
			db.Close( );
			
			//公司级开始
			CDaoRecordset m_CompanySet(m_pDatabase);
			m_CompanySet.Open(dbOpenSnapshot,_T("Select a.USER_LINENAME,a.USER_TRANSFORMERNO,a.USER_MODULENO FROM TB_USER AS a,TB_USERTMP AS b WHERE a.USER_MODULENO=b.USER_MODULENO"));
			
			//寻找满足条件的记录
			while (!m_CompanySet.IsEOF())
			{
				i ++;

				if(i == 1)
				{
					WriteToLog("----------------------用户信息表中下列模块号重复被删除-----------------------");
					WriteToLog("    序号   线路名称                 变台名                             模块号");
				}

				SqlStr.Format("%6d      %16.16s        %16.16s         %16.16s",i,(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0)),(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1)),(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2)));
				WriteToLog(SqlStr);

				m_CompanySet.MoveNext();
			}
			m_CompanySet.Close();	
		
			if(i > 0)
			{
				 WriteToLog("---------------------------------------------------------------------------------");
			}
			
			delete m_pDatabase;
			m_pDatabase = NULL; 
	
		}

	 	//删除重复的数据
		SqlStr.Format("DELETE TB_USER FROM TB_USER AS a,TB_USERTMP AS b WHERE a.USER_MODULENO=b.USER_MODULENO");
	}	
	else
	{
		//删除原来的数据
		SqlStr.Format("DELETE FROM %s",m_DataName);
	}

	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	SqlStr.Format("INSERT %s SELECT DISTINCT * FROM %s",m_DataName,m_DataNameTemp);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	
	//删除临时表
	SqlStr.Format("DROP TABLE %s",m_DataNameTemp);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

}



void CIFRMView::OnUpdateRemotemodify(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}

//CString m_CondtionString  发送要满足的条件
//CString m_TableName       发送要满足的表名
//int     Start             起始位置
BOOL CIFRMView::SendRemoteData(CString m_CondtionString, CString m_TableName, int Start)
{
	
	CString   strSql,strValue;
    long        fields   =  0;
	BYTE                 bits;
	int       m_length    = 0;//长度
	unsigned int crc = 0xffff;//CRC检验值

	//打开数据库
	CDatabase             db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);

		//找适合条件的个数
		if(m_CondtionString == "ALL")
		{
		     strSql.Format("SELECT COUNT(*) FROM %s", m_TableName);
		}
		else
		{
			strSql.Format("SELECT COUNT(*) FROM %s WHERE %s", m_TableName,m_CondtionString);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		//记录个数
		fields = atol(strValue);   
		rs.Close();
		
		if(fields < 1 || Start >= fields || Start < 0)
		{	
			//关闭数据库
			db.Close( );

			//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
            SendMessageToElectricOffice(2);
			strSql.Format("%s表中无数据可取...",m_TableName);
			status(strSql);
			return  FALSE;
		}
		
    	//找适合条件的个数
		if(m_CondtionString == "ALL")
		{
		     strSql.Format("SELECT * FROM %s", m_TableName);
		}
		else
		{
			strSql.Format("SELECT * FROM %s WHERE %s", m_TableName,m_CondtionString);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到字段个数
		short nFields = rs.GetODBCFieldCount();

	//	status("正在提取相应的记录，请稍侯...");
	//	ShowProgressCtrl(TRUE);
	//	SetProgressCtrlRange(0, fields,1);
		
		//移到第一个记录
		rs.MoveFirst();

		rs.Move(Start, SQL_FETCH_ABSOLUTE);
        
		strSql = "";
		
		//字段数
		int i;
		for( i = 0; i < nFields; i++)
		{
			rs.GetFieldValue(int(i),strValue);
			strValue.TrimRight();

			if(i == nFields  - 1)
			{
				strSql = strSql + strValue;
			}
			else
			{
				strSql = strSql + strValue + ",";
			}
		}
		
		//关闭数据库
		rs.Close( );
		db.Close( );
		
		int Count   = strSql.GetLength();

		//删除所有数据
		SendByteArray.RemoveAll();
		//第一位数，开始标志 0x68
		SendByteArray.Add(0x68);
		//第二位数，长度L低字节
		SendByteArray.Add(0x00); 
        //第三位数，长度L高字节
		SendByteArray.Add(0x00); 
		//第四位数, 0x68
		SendByteArray.Add(0x68);
					
		//给数组赋值
		for( i  = 0; i < Count; i ++)
		{
			//每个字节的值
			if(strSql.GetAt(i) == ' ')
			{
				bits =  '*';
			}
			else
			{
				bits =  strSql.GetAt(i);
			}
		
			SendByteArray.Add(bits);
			
			//调用CRC检验
            crc = Crc16( crc , bits );            
		}
		
		//长度,前四个不是数据
		m_length = SendByteArray.GetSize() - 4; 
		//长度L低字节 
		SendByteArray[1] = m_length%256;
     	//长度L高字节
		SendByteArray[2] = m_length/256;; 
     	//加CRC检验低位
		SendByteArray.Add(crc%256);	
	    //加CRC检验高位
		SendByteArray.Add(crc/256);
		//结尾标志
		SendByteArray.Add(0x16);
		//发送数组时用
		m_Com.SetOutput(COleVariant(SendByteArray));
		strSql.Format("远程索取本地表%s第%d条记录成功...",m_TableName,Start);
		status(strSql);
	//	ShowProgressCtrl(FALSE);
	}
	return   TRUE;
}

//CString Datatime  传送>＝Datatime的数据
//BYTE    Kinds     种类  0x11 分时电量  0x13电流电压
//int     Start     起始位
//int     N         终端数据库结构或瞬时功率电压电流数据结构体个数
BOOL CIFRMView::SendHunNanHexData(CString Datatime, BYTE Kinds, int Start, int N)
{ 
	
	CString           strSql;
	CString         strValue;
    long        fields  =  0;
	BYTE               bytes;
	CString    DataAppear[9];     
	
	//打开数据库
	CDatabase             db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		Datatime.TrimLeft();
		Datatime.TrimRight();
		//和CRecordset连上
		CRecordset rs(&db);
		//找适合条件的个数
		strSql = "SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISON.GARRISON_HALTTIME >= '" + Datatime + "'";
		rs.Open(CRecordset::forwardOnly,strSql);
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		//记录个数
		fields = atol(strValue);   
		rs.Close();
		
		if(Kinds == 0x11)
		{   
			//电量分时表码
			ShowGridHead("模块编码,160;时间,160;有功,160;无功,160;模块号,160;");
		}
        else if(Kinds == 0x13)
		{  
			//0x13瞬时电流电压
			ShowGridHead("模块编码,120;时间,120;A相电流,70;B相电流,70;C相电流,70;A相电压,70;B相电压,70;C相电压,70;模块号,160;");
		}

		if(fields < 1 || Start >= fields)
		{	
			//关闭数据库
			db.Close( );
			//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
            SendMessageToElectricOffice(2);
			return  FALSE; 
		}
		
		//发送的字节清0
		SendByteArray.RemoveAll();
		
		//模块编码、驻留时间、有功、无功、A相电流、B相电流、C相电流、A相电压、B相电压、C相电压、模块号
		strSql = "SELECT TB_USER.USER_IDNO,TB_GARRISON.GARRISON_HALTTIME,TB_GARRISON.GARRISON_WORKDEGREE,TB_GARRISON.GARRISON_LOSEDEGREE,TB_GARRISON.GARRISON_ACURRENT,TB_GARRISON.GARRISON_BCURRENT,TB_GARRISON.GARRISON_CCURRENT,TB_GARRISON.GARRISON_AVOLTAGE,TB_GARRISON.GARRISON_BVOLTAGE,TB_GARRISON.GARRISON_CVOLTAGE,TB_USER.USER_MODULENO FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISON.GARRISON_HALTTIME >= '" + Datatime + "' ORDER BY TB_GARRISON.GARRISON_MODULENO";
		rs.Open(CRecordset::forwardOnly,strSql);
		//得到字段个数
		short nFields = rs.GetODBCFieldCount();
		status("正在提取相应的记录，请稍侯...");
		ShowProgressCtrl(TRUE);
		SetProgressCtrlRange(0, fields,1);
		
		//生成数据字节
		SendByteArray.Add(0x68);  //起始标志
      
		if(Kinds == 0x11)
		{   
			//电量分时表码
			SendByteArray.Add((8+N*(9+80))%256);//长度的低字节位//255
			SendByteArray.Add((8+N*(9+80))/256);//长度的高字节位//255
		}
        else if(Kinds == 0x13)
		{  
			//0x13瞬时电流电压
			SendByteArray.Add((8+N*(9+40))%256);//长度的低字节位//255
			SendByteArray.Add((8+N*(9+40))/256);//长度的高字节位//255
		}
		
		SurrenderWindowMessage();//交出window控制权

        SendByteArray.Add(0x68);            //中间字节
        SendByteArray.Add(0x88);            //中间字节
        SendByteArray.Add(0xff);            //中间字节
        SendByteArray.Add(0x01);            //中间字节
        SendByteArray.Add(N);               //数据结构个数
        SendByteArray.Add(0x05);            //中间字节
        SendByteArray.Add(0x00);            //终端低地址
        SendByteArray.Add(0x00);            //终端高地址
        SendByteArray.Add(Kinds);           //关键字0x11 或0x13
		
		//读用户信息
		for(int j = 0;j < fields; j ++)
		{
			
			if(j >= Start && j < Start + N)
			{
				
				SendByteArray.Add(0xA1);//有效标志	
				
				//字段数
				for(int i = 0; i < nFields; i++)
				{
					rs.GetFieldValue(int(i),strValue);
					strValue.TrimRight();
					//0x11 电量  0x13电流电压
					switch(i)
					{
					case 0:
						{
							//模块编码,2个字节
							DataAppear[0] = strValue;

							//add 2004.9.17
							bytes =  atoi(strValue)%100;
							bytes = (bytes/10)*16 + bytes%10;//转成BCD码
							SendByteArray.Add(bytes);
	                        bytes =  atoi(strValue)/100;
							bytes = (bytes/10)*16 + bytes%10;//转成BCD码
							SendByteArray.Add(bytes);
							break;
						}
					case 1:
						{  
							//驻留时间，6个字节
							//2004- 1- 1 16: 0: 0
							DataAppear[1] = strValue;
							int k = strValue.Find('-');
							if(k != -1)
							{
								//年
								bytes = atoi(strValue.Left(k)) - 2000;
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //加入年
								
								//月
								k = strValue.Find('-');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								strValue.TrimLeft();
								strValue.TrimRight();
								SendByteArray.Add(bytes);        //加入月
								
								//日
								k = strValue.Find(' ');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //加入日
								
								//时
								k = strValue.Find(':');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //加入时
								
								//分
								k = strValue.Find(':');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //加入分
								
								//秒
								bytes = atoi(strValue);
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //加入秒
								
							}
							break;
						}
					case 2:
						{
							//电量分时表码
							if(Kinds == 0x11)
							{
								DataAppear[2].Format(" %.2f",atof(strValue));
								//有功,4个字节，从低到高,再转成BCD码
								long DataValue = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节
								
								bytes        = (DataValue%1000000)/10000;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第三个低字节
								
								bytes       = (DataValue%100000000)/1000000;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第三个低字节
							}
							break;
						}
					case 3:
						{
							//电量分时表码
							if(Kinds == 0x11)
							{   
								DataAppear[3].Format(" %.2f",atof(strValue));

                                //无功,4个字节,再转成BCD码
								//前有4个，正向有功峰、正向有功平、正向有功谷、正向有功尖峰 4*4=16字节为0
								for(int jjj = 0; jjj < 16; jjj ++)
								{
									SendByteArray.Add(0x00);        //加16个空字节
								}
								
								//有功,4个字节，从低到高,再转成BCD码
								long DataValue = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节
								
								bytes        = (DataValue%1000000)/10000;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第三个低字节
								
								bytes       = (DataValue%100000000)/1000000;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第三个低字节
								
								//后有14个，如感性无功总、感性无功峰等14个量为空字节 4*14=56字节为0
								for( int jjj = 0; jjj < 56; jjj ++)
								{
									SendByteArray.Add(0x00);        //加16个空字节
								}
							}		
							break;
						}
					case 4:
						{
							//0x13瞬时电流电压 
							if(Kinds == 0x13)
							{  
								DataAppear[2].Format(" %.2f",atof(strValue));

								//前有12个，有功功率、A相有功功率、B相有功功率、C相有功功率等12个为空 空字节数为40－12＝28个
								for(int jjj = 0; jjj < 28; jjj ++)
								{
									SendByteArray.Add(0x00);        //加28个空字节
								}
								
								//A相电流
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节
							}
							break;
						}
					case 5:
						{
							//0x13瞬时电流电压
							if(Kinds == 0x13)
							{  
								
								DataAppear[3].Format(" %.2f",atof(strValue));
								//B相电流
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节

							}
							break;
						}
					case 6:
						{   
							//0x13瞬时电流电压
							if(Kinds == 0x13)
							{  
								
								DataAppear[4].Format(" %.2f",atof(strValue));
								//C相电流
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节

							}
							break;
						} 
					case 7:
						{
							
							//0x13瞬时电流电压
							if(Kinds == 0x13)
							{  
								DataAppear[5].Format(" %.1f",atof(strValue));//.2f
								//A相电压
								long DataValue  = long(atof(strValue)*10+0.5);//*10  
								bytes           =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节
							}
							break;
						}
					case 8:
						{
							//0x13瞬时电流电压
							if(Kinds == 0x13)
							{  
								
								DataAppear[6].Format(" %.1f",atof(strValue));
								//B相电压
								long DataValue  = long(atof(strValue)*10+0.5);
								bytes           =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节

							}
							break;
						}
					case 9:
						{
							//0x13瞬时电流电压
							if(Kinds == 0x13)
							{ 
								DataAppear[7].Format(" %.1f",atof(strValue));

								//C相电压
								long DataValue  = long(atof(strValue)*10+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第一个低字节
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//转成BCD码
								SendByteArray.Add(bytes);        //第二个低字节
							}
							break;
						}
					case 10:
						{
							//模块号
							if(Kinds == 0x11)
							{ 
								DataAppear[4]  = strValue;
                            }
							else if(Kinds == 0x13)
							{
                                DataAppear[8]  = strValue;
							}
							break;
						}
						
				   }
				   
			 }

			 //显示列表数据
			 if(Kinds == 0x11)
			 {   
				 //电量分时表码
				 AddlistItem(DataAppear, 5);
			 }
			 else if(Kinds == 0x13)
			 {	
				 //瞬时电流电压
				 AddlistItem(DataAppear, 9);
			 }
			 
		  }
		
		  //显示信息
		  strValue.Format("正在提取数据记录,完成%.2f％,请稍侯...",float(j)*100/fields);
		  status(strValue);
		  //记录下滑
		  SetProgressCtrlSetIt();
		  //用户库下滑一个记录
		  rs.MoveNext();

		  if(j > Start + N)
		  {
		     break;
		  }
	
		}
		//关闭数据库
		rs.Close( );
		db.Close( );
      
		/*
		//是否够了,不够填满数
		if(Start + N - fields > 0)
		{
			
			for(int ll = 0; ll < Start + N - fields; ll ++)
			{
				
				SendByteArray.Add(0xE1);//无效数据

				//0x11    电量
				if(Kinds == 0x11)
				{
					for(int jjj = 0 ; jjj < 88; jjj ++)
					{
						SendByteArray.Add(0x00);//无效数据
					}

				} 
				
				//0x13瞬时电流电压
				if(Kinds == 0x13)
				{
                   	for(int jjj = 0 ; jjj < 48; jjj ++)
					{
						SendByteArray.Add(0x00);//无效数据
					}

				}

			}

		}
		*/

		//add 2004.9.17
		if(Start + N - fields > 0)
		{
			
			if(Kinds == 0x11)
			{   
				//电量分时表码
				SendByteArray[1] = ((8+(fields-Start)*(9+80))%256);//长度的低字节位//255
				SendByteArray[2] = ((8+(fields-Start)*(9+80))/256);//长度的高字节位//255
		        SendByteArray[7] =  fields-Start;
			}
			else if(Kinds == 0x13)
			{  
				//0x13瞬时电流电压
				SendByteArray[1] = ((8+(fields-Start)*(9+40))%256);//长度的低字节位//255
				SendByteArray[2] = ((8+(fields-Start)*(9+40))/256);//长度的高字节位//255
				//数据结构个
				SendByteArray[7] =  fields-Start;
			}

		}
		//add 2004.9.17
    
		bytes = 0;

		//检验码
		for(int jjj = 0; jjj < SendByteArray.GetSize(); jjj ++)
		{
			if( jjj >= 4)
			{
			  
				bytes  = (bytes + SendByteArray[jjj])%256;//255

			}
		}
		
		SendByteArray.Add(bytes);//检验码
		SendByteArray.Add(0x16); //结束码
        SelectSendCByteArray(m_sendkind,TRUE,FALSE);//发送数据
		SendByteArray.RemoveAll();

	}
	status("                            ");
	ShowProgressCtrl(FALSE);
	return   TRUE;
}

//从威胜处获取最原始的数据
void CIFRMView::GetPriveteDataFromWs(CString  m_CsvFileName)
{

    CString                SqlStr,Strs;
	
	//显示状态栏信息
	StatusStr = "正在更新原始底库的数据，请稍等...";
	SendMessage(WM_EVENT, 1, 0);

	//删除威胜临时表数据
	CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USERTEMPWS");

	//从文本文件导入威胜数据
	SqlStr.Format("BULK INSERT IFRM..TB_USERTEMPWS FROM '%s' WITH (DATAFILETYPE = 'char', FIELDTERMINATOR = ',', ROWTERMINATOR = '\n')",m_CsvFileName);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);	

	
	//如果有范围的话,删除不在此范围的数据,
	if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE","ALL") > 0)
	{
	   CDataBaseInstance::ExecuteDataBaseSQL("DELETE TB_USERTEMPWS WHERE USER_MANAGENO NOT IN (SELECT USER_MANAGENO FROM TB_MANAGERANGE)");
	}
	
	//如果有新加的东东
	if(CDataBaseInstance::GetAllRecordsCount("TB_USERTEMPWS","ALL") > 0)
	{
		//处理威胜的库,统一表卡号
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USERTEMPWS SET USER_AMMETERNO=LEFT(USER_AMMETERNO,14)");
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USERTEMPWS SET USER_TRANSFORMERNO=REPLACE(USER_TRANSFORMERNO,'【台区】','')");//去字符“【台区】”
		//删除用户库表中的数据
		CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USER");
		//从威胜表中取数据
		//如果有范围的话
		CDataBaseInstance::ExecuteDataBaseSQL("INSERT TB_USER(USER_STATIONNO,USER_STATIONNAME,USER_MOTHERLINE,USER_LINENO,USER_LINENAME,USER_TRANSFORMERNO,USER_AMMETERNO,USER_MODULENO,USER_SUPPLYMODE,USER_IDNO,USER_MULTIPLE,USER_SENDANGLE,USER_PROTOCOL) SELECT DISTINCT USER_STATIONNO,USER_STATIONNAME,USER_MOTHERLINE,USER_LINENO,USER_LINENAME,USER_TRANSFORMERNO,USER_AMMETERNO,USER_MODULENO,USER_SUPPLYMODE,USER_IDNO,USER_MULTIPLE,USER_SENDANGLE,USER_PROTOCOL FROM TB_USERTEMPWS");
		//给供电局加上名称,相别不定
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USER SET USER_COMPANY='包头供电局',USER_PHASE=3,USER_AMMETERKIND=2,USER_INITIALVALUE=0.00 WHERE USER_COMPANY IS NULL");
		//给变台名称为空
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USER SET USER_TRANSFORMERNO='末命名变台' WHERE ltrim(RTrim(USER_TRANSFORMERNO))='<null>'");
	
	}

   //删除威胜临时表数据
	CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USERTEMPWS");
    
	//更新树控件
	SendMessage(WM_EVENT, 9, 0);
  
	//显示状态栏信息
	StatusStr = "更新原始底库数据完毕...";
	SendMessage(WM_EVENT, 1, 0);
}

void CIFRMView::ReplaceUserModuleID(int startNo)
{	
	//得到记录个数
	long fields = CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL"); 
				
	//如果没有满足条件的数据,返回
	if(fields <= 0)
	{					
		return;
	}
	
	//打开数据库
	CDatabase          db;
	CString        strSql;
	CString      strValue;	
	CString     fieldname;

    if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
    
		strSql = "SELECT USER_MODULENO FROM TB_USER";

		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		for(int j = 0;j < fields; j++)
		{
           
			rs.GetFieldValue((short)0,strValue);

	     	strSql.Format("Update TB_USER SET USER_IDNO=%d WHERE  USER_MODULENO=%d",startNo + j,atol(strValue));
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
			//库下滑一个记录
			rs.MoveNext();
		}
		
		//关闭数据库
		rs.Close( );
		db.Close( );
	}


}


//从服务器上取数据
void CIFRMView::GetDataFormMarketServer(CString m_address, CString m_loginname, CString m_password,CString m_StrFileName,int m_port)
{

	CInternetSession           ses;	
	CString   str,FileName,strtime;
	FILETIME       RemoteLastWrite;
    SYSTEMTIME          systemTime;
	
	//用户名
	m_loginname.TrimLeft();
    m_loginname.TrimRight();
    
	//密码
	m_password.TrimLeft();
    m_password.TrimRight();

	//服务器地址
    m_address.TrimLeft();
    m_address.TrimRight();

	CFtpConnection* pFTP;
	try
	{
		//显示状态栏信息
		StatusStr = "正在提取服务器数据...";
		SendMessage(WM_EVENT, 1, 0);
	
		//定用户名和密码
		pFTP = ses.GetFtpConnection(m_address,m_loginname,m_password,m_port,FALSE);
		

		if (pFTP) 
		{	
			//显示状态栏信息
		    StatusStr = "服务器连接成功...";
		    SendMessage(WM_EVENT, 1, 0);

			CFtpFileFind pFileFind(pFTP);
		
			//查找文件
			if(pFileFind.FindFile("/data/pub/" + m_StrFileName))//ykdocs.csv"))
			{	
			 
				pFileFind.FindNextFile();
				
				//调用GetLastWriteTime前先调用FindNextFile()一次
				pFileFind.GetLastWriteTime(&RemoteLastWrite);
				
				//转文件时间为系统时间
				::FileTimeToSystemTime(&RemoteLastWrite,&systemTime);
				
				strtime.Format("%d-%d-%d %d:%d:%d",systemTime.wYear,systemTime.wMonth,systemTime.wDay,systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
			
				//显示状态栏信息
		        StatusStr = "成功找到" + m_StrFileName + "文件，日期:" + strtime;
		        SendMessage(WM_EVENT, 1, 0);
			
				pFileFind.Close();

				//如果时间不同的话
				if(strtime != GetRefreshTime())
				{
					
					CFileFind  finder;
					FileName.Format("%s%s",GetFolder(),m_StrFileName);//"ykdocs.csv");
					
					//如果存在数据则添加入库
					if(finder.FindFile(FileName) != 0) 
					{ 
						//存在此文件的话则删除此文件
						::DeleteFile(FileName);
					}
					
					//拷贝文件到当前目录
					if (pFTP->GetFile("/data/pub/" + m_StrFileName,FileName))//ykdocs.csv"
					{
						delete pFTP;

						//显示状态栏信息
						StatusStr = "从服务器上取数据文件成功...";
						SendMessage(WM_EVENT, 1, 0);
					
						//处理数据
						GetPriveteDataFromWs(FileName);
					    //删除原来存的时间
						CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_REFRESHTIME");
	                    //时间存入时间更新库
						str.Format("INSERT INTO TB_REFRESHTIME(USER_REFRESHTIME) VALUES ('%s')",strtime);
                        CDataBaseInstance::ExecuteDataBaseSQL(str); 
						
						//如果有数据更新信息更新窗口
						CWnd* pt = CWnd::FindWindow(NULL,"数据更新信息");
						if(pt)
						{
							pt->SendMessage(WM_CLOSE,0,0);
						}
						
						//如果有FTP远程数据提取
						pt = CWnd::FindWindow(NULL,"FTP远程数据提取");
						if(pt)
						{
							pt->SendMessage(WM_CLOSE,0,0);
						}

						//显示结果
						CShowInfoDlg    dlg;
						dlg.DoModal();

					} 
					else
					{
						//显示状态栏信息
						StatusStr = "从服务器上取数据文件失败...";
						SendMessage(WM_EVENT, 1, 0);
					}

				}
				else
				{
					//显示状态栏信息
					StatusStr = "上次更新的用户数据信息已经是最新数据...";
					SendMessage(WM_EVENT, 1, 0);
				}

			}
			else
			{
				//显示状态栏信息
				StatusStr = "FTP服务器上找不到" + m_StrFileName + "文件...";
				SendMessage(WM_EVENT, 1, 0);
			}

		}

	}
	catch(CInternetException *pEx)
	{
		char m_szStatus[1024];
		pEx->GetErrorMessage(m_szStatus, sizeof(m_szStatus));
		//显示状态栏信息
		StatusStr = m_szStatus;
		SendMessage(WM_EVENT, 1, 0);
	    //status(m_szStatus);
		pEx->Delete();
	}

}


//得到数据更新的时间
CString CIFRMView::GetRefreshTime()
{  
	//打开数据库
	CDatabase         dbs;	
	CString      str = "";
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_REFRESHTIME","ALL") > 0)
	{
		
		if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//和CRecordset连上
			CRecordset   rs(&dbs);
				
			str = "SELECT * FROM TB_REFRESHTIME";
			
			rs.Open(CRecordset::forwardOnly,str);
		
			//得到记录个数
			rs.GetFieldValue((short)0,str);
			rs.Close();
			
			//关闭数据库
			dbs.Close();
		}

	}

	str.TrimLeft();
	str.TrimRight();
	
	//返回记录时间
	return str;   

}

//包头专用，封 2004.10.8 胡高明
void CIFRMView::OnUpdateNewreport(CCmdUI* pCmdUI) 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
    //pCmdUI->Enable(!m_BaoTouUse);	
}


void CIFRMView::OnGetdatafromlong() 
{
	//CFTPGetDataDlg                dlg;
	//dlg.m_port      =       m_port;
	//dlg.m_loginname =  m_loginname;
	//dlg.m_password  =   m_password;
	//dlg.m_FileName  = m_FtpFileName;//FTP文件名
	//dlg.DoModal();	
}

void CIFRMView::OnLocalmodify() 
{

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm); 
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

	if(m_UseInfoset->IsOpen())
	{
		m_UseInfoset->Close();
	}
	
	//数据库表是否打开
	if(m_UseInfoset->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{

		CUserInfoDlg dlg(m_UseInfoset.get(),0);
		dlg.m_filtercondtion = pMainFrm->m_wndMyDialogBar.SelectCondition();
	    dlg.m_IfAdding       = FALSE;
		dlg.DoModal();	
		
		//变台修改或增加了记录
		if(dlg.m_IfAdding == TRUE)
		{	
			//树控件重新刷新一次
			RefreshTree();
		}
		
	}

}

void CIFRMView::OnUpdateLocalmodify(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege()< 2);

}

void CIFRMView::OnUpdateAppearselectdata(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
}


//检查变电站的个数
BOOL CIFRMView::CheckStations(CString m_strsql)
{

	CDatabase          dbs;
	CString         StrSql;
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset rs(&dbs);
		//得到选择的变电站的个数
		StrSql.Format("SELECT COUNT(DISTINCT USER_STATIONNO) FROM TB_USER WHERE %s",m_strsql);
		rs.Open(CRecordset::forwardOnly,StrSql);
		//得到记录个数
		rs.GetFieldValue((short)0,StrSql);
		rs.Close();
		//关闭数据库
		dbs.Close();
		
		if(atoi(StrSql) > 1)
		{	
			MessageBox("你选择了多个变电站的数据，请选择单个变电站的数据发送！","警告",MB_OK|MB_ICONWARNING);
			return  FALSE;
		}
		
	}

	return TRUE;

}

//取消定时发驻留定时读表
void CIFRMView::OnUpdateBREAkSOMEDAY(CCmdUI* pCmdUI) 
{
	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{
			//串口
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	
			//电话
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//电话
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//连接标志
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}
}

//设置读的标志
void CIFRMView::SetDataReadLabel(CString m_range)
{
	
	CString StrSql,str = "";//先赋读表标志,Y 已读成功或不用读  N 没有读出的标志
	
	//14种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10－尖峰电量 11－峰电量 12－谷电量 13－平电量
	for(int i = 0; i < 15; i++)
	{
		
		if(m_SetLabel[i])
		{
			str = str + "N";
		}
		else
		{
			str = str + "Y";
		}
		
	}
	
	if(m_range == "ALL")
	{
        //设置读表标志
		StrSql.Format("UPDATE TB_USER SET USER_READLABEL='%s'",str);
	}
	else
	{
		//设置读表标志
		StrSql.Format("UPDATE TB_USER SET USER_READLABEL='%s' WHERE %s",str,m_range);
	}

	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
}



//显示定时读表的按钮
void CIFRMView::ShowDingShiButton(BOOL  IsShowWindows)
{	
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	if(IsShowWindows)
	{    
	
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHI);

	}
	else
	{		
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHINULL);
	}

}

//启动时自动应答
void CIFRMView::AutoAnswer(BOOL  ShowMessage)
{

	CString       str;
	CDatabase      db;
	str         =  "";
	short parameter[6];
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
       	str = "SELECT count(*) FROM TB_COMINFORMATION";
		rs.Open(CRecordset::forwardOnly,str);
		//得到记录个数
		rs.GetFieldValue((short)0,str);
		//记录个数
		long fields = atol(str); 
		rs.Close();
		
		if(fields <= 0)
		{
			db.Close( );
			return;
		}
		else
		{
			str = "SELECT * FROM TB_COMINFORMATION";
			
			rs.Open(CRecordset::forwardOnly,str);
			
			//得到字段个数
			short nFields = rs.GetODBCFieldCount();
			
			for(int i = 0; i < nFields; i++)
			{
				rs.GetFieldValue((short)i,str);
				str.TrimLeft();
				str.TrimRight();
				
				switch(i)
				{
				case 0:
					{
						//串口
					    parameter[0] = atoi(str);
						break;
					}
				case 1:
					{
						//波特率
						parameter[1] = atoi(str);
						break;
					}
				case 2:
					{
						//检验位
						parameter[2] = atoi(str);
						break;
					}
				case 3:
					{
						//数据位
						parameter[3] = atoi(str);
						break;
					}
				case 4:
					{
						//停止位
						parameter[4] = atoi(str);
						break;
					}
				case 5:
					{
						//自动应答
						parameter[5] = atoi(str);
						break;
					}
					
				}
				
			}
			
			//关闭数据库
			rs.Close( );
			db.Close( );


			//自动应答
			if(parameter[5] > 0)
			{

				/***************************************************************
				串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
				波特率 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
				检验位 0-无校验,1－奇校验,2－偶校验
				数据位 0-4     ,1-5      ,2-6      ,3-7    ,4-8
				停止位 0-1     ,1-1.5    ,2-2
				**************************************************************/
		
				OptionClick(parameter[0],parameter[1],parameter[2],parameter[3],parameter[4]);
				m_sendkind   =    1;
			
				//自动应答,如果没有连接通则返回TRUE
				//Connect(ShowMessage,TRUE);
			    Connect(ShowMessage,FALSE);
			}

		}
		
	}

}

//显示列表头
void CIFRMView::ShowGridHead(CString HeadStr)
{

	CString             Str;
	int               k = 0;
	CStringArray    ColName;
	CByteArray      ColWide;
	
	while(HeadStr.Find(';') != -1)
	{
		
		k   =  HeadStr.Find(';');
		
		if(k != -1)
		{
			Str =  HeadStr.Left(k);
			HeadStr  = HeadStr.Right(HeadStr.GetLength() - k - 1);

			k   =  Str.Find(',');
			
			if(k != -1)
			{
				
				ColName.Add(Str.Left(k));
				ColWide.Add(atoi(Str.Right(Str.GetLength() - k - 1)));
			}
			
		}
		
	}
	
	//删除所有的数据
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);

	TRY { 

		m_IsHistory    =     FALSE;//是否显示历史数据
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);                    //行
		m_Grid.SetColumnCount(ColName.GetSize()); //列
		
		//列表填数
		for (int col = 0; col < ColName.GetSize(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = 0;
			Item.col = col;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format("%s",(ColName[col]));
			m_Grid.SetItem(&Item);
			m_Grid.SetColumnWidth(col,ColWide[col]); 
		}
		
		m_Grid.SetModified(FALSE,-1,-1);
		
		m_Grid.SetBkColor(RGB(255,255,255));

		m_Grid.Invalidate();
		m_Grid.Refresh();

	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	END_CATCH
		
}


//演示或隐藏动画
void CIFRMView::OperationAnimation(BOOL m_starting)
{ 
	//得到所选的模块号
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	if(m_starting)
	{

		if (!pMainFrm->IsAnimationActive())
		{
			pMainFrm->StartAnimation(IDR_AVITEST);
		}

	}
	else
	{

		if (pMainFrm->IsAnimationActive())
		{
			pMainFrm->StopAnimation();
		}

	}

}


//本地删除模块
void CIFRMView::OnUpdateDeletemodule(CCmdUI* pCmdUI) 
{
    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
}

void CIFRMView::OnDeletemodule() 
{	
	CString            StrSql;

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

    StrSql.Format("你想删除所选择的模块用户信息数据[%d条]吗？",CDataBaseInstance::GetAllRecordsCount("TB_USER",pMainFrm->m_wndMyDialogBar.SelectCondition()));

	if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{	
		
		StrSql = "确认删除所选择的模块用户信息数据吗？\r\n警告：删除后用户信息数据不能恢复！！";
		
		if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			
			StrSql = "同时删除所选择的模块相关联的正式、驻留数据吗？\r\n警告：删除后数据不能恢复！！";
            
			if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
			{

				//删除相关驻留数据
				StrSql.Format("DELETE FROM TB_GARRISON WHERE GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
				//删除相关正式读表数据	
				StrSql.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);	
				//接线错误的模块
				StrSql.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);	
				//删除不在无功补偿表
				StrSql.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)");
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

			}		
			
			//删除用户信息
			StrSql.Format("DELETE FROM TB_USER WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
				
			if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") < 1)
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
				GetParentFrame()->RecalcLayout();
			}
			else
			{
				pMainFrm->m_wndMyDialogBar.Treeinitialize();
			}
		}
		//树控件重新刷新一次
	}

}

//超级管理员才有
void CIFRMView::OnUpdateAngleset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 1);
}

//高级用户以上
void CIFRMView::OnUpdateCommunication(CCmdUI* pCmdUI) 
{
 	
	pCmdUI->Enable(FALSE);
	return;

   	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(!m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 1:
		{	//电话拔号的标志,且是电局版的时候
	        pCmdUI->Enable(!m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 2:
		{   
			//连接标志
			pCmdUI->Enable(!m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	}
}

//高级用户以上CRegKey
void CIFRMView::OnUpdateDatapass(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(FALSE);
	return;

	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 1:
		{	
			//电话
			pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 2:
		{   
			//连接标志
			pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	}

}

//普通管理员以上才有
void CIFRMView::OnUpdateAutoreadset(CCmdUI* pCmdUI) 
{
   	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{				
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	//电话拔号
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//连接标志
			if(AppInfo::Instance().m_WhichKind)
			{
			    pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}

}

void CIFRMView::OnUpdateBreadorder(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 1  && !m_IsAutoSending);	
}

//产生BCH码
//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
void CIFRMView::Encode_Bch(BYTE g[],BYTE data[],BYTE m_kinds)
{
	int i,j,feedback,length = 63,k = 45;
	BYTE  bb[18];
	switch(m_kinds)
	{
	case 0:
		{	
			//0  Bch63_45_3
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
			length = 63;
			k      = 45;
			break;
		}
	case 1:
		{
			//1  Bch45_27_3
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
			length = 45;
			k      = 27;
			break;
		}
	case 2:
		{
			//2 BCH31_21_2
			g[0]   =    1;
			g[1]   =    0;
			g[2]   =    0;
			g[3]   =    1;
			g[4]   =    0;
			g[5]   =    1;
			g[6]   =    1;
			g[7]   =    0;
			g[8]   =    1;
			g[9]   =    1;
			g[10]  =    1;
			length =   31;
			k      =   21;
			break;
		}
	}



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

	//BUG 此一位没有参加BCH运算
	g[63] = data[45];

}


void CIFRMView::OnClosereport() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{      
		return;
	}
	
	//演示或隐藏动画
	OperationAnimation(FALSE);
	//隐藏滚动条
	ShowProgressCtrl(FALSE);

    //得到修改状态
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("报表已修改,保存报表文件吗?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
             
			OnSavereportas(); 
			m_Grid.SetModified(FALSE,-1,-1);
		}
	
	}
	
	//删除所有的数据
	m_Grid.DeleteAllItems();
	m_Grid.SetModified(FALSE,-1,-1);
	
	m_Grid.SetBkColor(RGB(128,128,128));

	m_Grid.Refresh();
	status("     ");

}

void CIFRMView::OnUpdateClosereport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.GetRowCount() > 0); 
	
}

void CIFRMView::OnTimesearch() 
{
   
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
		
	CString       PassStr;
	if(	AppInfo::Instance().m_WhichKind)
	{
		
		if(m_zhuliukinds == 0)
		{			
			//0 按表计种类下驻留 1 按日期下驻留
			MessageBox(DecodeParameter(TRUE),"按表计种类下驻留设置如下:");
		}
		else
		{
			//按日期解析参数
			MessageBox(ByDateDecodeParameter(),"按日期不同下驻留设置如下:");
			
		}

		
	}
	else
	{
		//远程查询对方的驻留设置
		PassStr    = "BEGINS;COMMAND:30:HALT;ENDS";
		m_TimeStrs = "";
		
		//如果连接好的话
		//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送 m_sendkind
		//Str             发送字符
		//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
		//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
		SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
	}

}

//相关性检验
double CIFRMView::CorrelationCheck(long SourceArray[], long DestArray[],int m_places)
{
    double           A,B,C,Pxy,sums;
	double        DestArrayBak[256];
	double       DestArrayBaks[256];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	for( i = 0; i < 256;i ++)
	{
		DestArrayBak[i]  = double(DestArray[i]);
	}

	//要移动位置
	if(m_places + 1 <= WM_NUMBERS/2)
	{
		
		//差值前移
		for( i = 0; i < 256;i ++)
		{
			
			//移动位置匹配
			if(i + (WM_NUMBERS/2 - m_places)*1 < 256)
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
		for( i = 0; i < 256;i ++)
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
		
		for( i = 0; i < 256;i ++)
		{
			DestArrayBak[i] = DestArrayBaks[i];
		}
		
	}
	else  if(m_places + 1 == WM_NUMBERS/2 + 1)
	{
		
		for( i = 0; i < 256;i ++)
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

	for(i = 0; i < 256;i ++)
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
}


//起始时间和结束时间
//long     m_Module     模块号
//CString  m_RightTime  此时时间
double CIFRMView::GetTestData(long m_Module,CString m_RightTime)
{	
	
	m_GetDataTimeStr.TrimLeft();
    m_GetDataTimeStr.TrimRight();

	if(m_GetDataTimeStr.IsEmpty())
	{
		return -1;
	}
	int i;

	for( i = 0 ; i < m_FileDataArray.GetSize(); i = i + 3)
	{

		if(atol(m_FileDataArray[i]) == m_Module)
		{
			break;
		}
	}

	if(i + 2 > m_FileDataArray.GetSize())
	{
		return -1;
	}


	short m_year,m_month,m_day,m_hour,m_minuter,m_second;
	long                                          kk1;
    m_year       =         atoi(m_GetDataTimeStr.Mid( 0,4));
    m_month      =         atoi(m_GetDataTimeStr.Mid( 5,2));
    m_day        =         atoi(m_GetDataTimeStr.Mid( 8,2));
    m_hour       =         atoi(m_GetDataTimeStr.Mid(11,2));
	m_minuter    =         atoi(m_GetDataTimeStr.Mid(14,2));
    m_second     =         atoi(m_GetDataTimeStr.Mid(17,2));
    CTime    time1(m_year,m_month,m_day,m_hour,m_minuter,m_second);
   
	m_year       =         atoi(m_RightTime.Mid( 0,4));
    m_month      =         atoi(m_RightTime.Mid( 5,2));
    m_day        =         atoi(m_RightTime.Mid( 8,2));
    m_hour       =         atoi(m_RightTime.Mid(11,2));
	m_minuter    =         atoi(m_RightTime.Mid(14,2));
    m_second     =         atoi(m_RightTime.Mid(17,2));
    CTime    time2(m_year,m_month,m_day,m_hour,m_minuter,m_second);
  
	//如果增长为0的话
	if(atof(m_FileDataArray[i + 2]) == 0)
	{
		return atof(m_FileDataArray[i + 1]);
	}
	
	CTimeSpan      ts1;
	if(time2 >=  time1)
	{
		ts1 = time2  -  time1;
		kk1 = ts1.GetTotalSeconds();
		return atof(m_FileDataArray[i + 1]) + kk1*atof(m_FileDataArray[i + 2])/(24*3600);
	}
	else
	{
		ts1 = time1  -  time2;
		kk1 = ts1.GetTotalSeconds();
		return atof(m_FileDataArray[i + 1]) - kk1*atof(m_FileDataArray[i + 2])/(24*3600);
	}

}


void CIFRMView::OnZhuliumodify() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}	
	
	// 驻留表
	if(m_GarrisonSet->IsOpen())
	{
		m_GarrisonSet->Close();
	}
	m_GarrisonSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks);
	
	CGarrisonDlg  dlg(m_GarrisonSet.get(),0);
	dlg.DoModal();
}

void CIFRMView::OnZhenshimodify() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}	
	
	// 数据表
	if(m_DataInfoSet->IsOpen())
	{
		m_DataInfoSet->Close();
	}
	m_DataInfoSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks);
	
	CDataInformationDlg  dlg(m_DataInfoSet.get(),0);
	dlg.DoModal();	
}


//判断表是否存在
BOOL CIFRMView::IsCurveTableExist(CString strTableName)
{ 
	//打开数据库
	CDatabase          db;
	CString        strSql;
    
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		
		strSql.Format("SELECT * FROM %s",strTableName);
		
		TRY
		{
			rs.Open(CRecordset::forwardOnly,strSql);
			//关闭数据库
			rs.Close( );
			db.Close( );
			return TRUE;
		}
		CATCH_ALL(e)
		{ 
			rs.Close( );
			db.Close( );
			e->Delete();
		}
		END_CATCH_ALL;
	}
    return FALSE;
}


//读远程驻留时间的内容
void CIFRMView::ReadRemoteTime()
{
	CString strValue,strSql;
    CDatabase            db;
	short     parameter[38];

    //没有记录则返回
	if(CDataBaseInstance::GetAllRecordsCount("TB_AUTOINFO","ALL") <= 0)
	{	
		return;
	}
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		
		strSql = "SELECT * FROM TB_AUTOINFO";
		rs.Open(CRecordset::forwardOnly,strSql);
		int j;
		//记录个数
		for( j = 0; j < 38; j ++)
		{
			//8个字段,电表种类编号
			rs.GetFieldValue((short)j,strValue);
			
			//初始化发驻留读表用的38个参数
			parameter[j] = atoi(strValue);
		}
		
		rs.Close( );
		//关闭数据库
		db.Close( );		
		
		//变电站发驻留的时间到供电局
		//格式：BEGINS;COMMAND:21:参数1;参数2;...参数38;ENDS 
		strSql  = "BEGINS;COMMAND:21:";
		
		//参数个数
		for( j = 0; j < 38; j ++)
		{
			//初始化发驻留读表用的38个参数
			strValue.Format("%d",parameter[j]);
			strSql = strSql + strValue + ";";
		}
		
		strSql = strSql + "ENDS";
		
		//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
		//Str             发送字符
		//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
		//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
		SelectSendString(m_sendkind, strSql,TRUE,TRUE,TRUE); 

	}

}

void CIFRMView::OnUpdateTimesearch(CCmdUI* pCmdUI) 
{

	// 0 串口发送 1 电话拔号发送 2 TCP/IP发送
	switch(m_sendkind)
	{ 
	case 0:
		{				
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && m_IsAutoSending);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	//电话拔号
			if(AppInfo::Instance().m_WhichKind)
			{
				//本地版
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2  && m_IsAutoSending);
			}
			else
			{
				//远程版
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//连接标志
			if(AppInfo::Instance().m_WhichKind)
			{
			    pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2  && m_IsAutoSending);
			}
			else
			{
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}

}

void CIFRMView::OnGetfile() 
{
	UpdateDataTable();
	//CConectStatus  dlg;
	//dlg.DoModal();

	/*
	CDataInto  dlg;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

		
	if(dlg.DoModal() == IDOK)
	{

	}
	
	if(m_GetDataFromFile)
	{
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGCHECK);
		pMainFrm->m_wndAboutButton.ShowWindow(SW_SHOW);
	}
	else
	{
        pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHINULL);
		pMainFrm->m_wndAboutButton.ShowWindow(SW_SHOW);
	}	
	*/
}

//询问是否要重加入数据
void CIFRMView::AskIfAddData(CString DataName,CString FileName)
{	
	
	CFileFind            finder; 

	//如果存在数据则添加入库
	if(finder.FindFile(FileName) != 0) 
	{ 
		
		if(DataName != "ZSDB_DATA" && DataName != "ZLDB_DATA" && DataName != "TB_HISTORYDATAS")
		{
			
            //本地版，远程传来的数据
			if(	AppInfo::Instance().m_WhichKind == TRUE)
			{
				
				//处理重复数据记录 m_DataName  表名,TxtFileName  导入文本文件
				DealRepeatRecord(DataName,FileName);
				
				//如果是用户数据表或变台表
				if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
				{
					//树控件重新刷新一次
					RefreshTree();
				}
				
				 //发送信息
				 SendContionStr.Format("BEGINS;MESSAGE:0:远程机器接收数据完毕,共添加数据记录%d条！\r\n注：遇到重复记录时先删除重复记录后添加！;ENDS",m_PassDataRecords);
			     SendMessage(WM_EVENT, 4, 0);
				
			}
			else
			{
				
				CString      data;
				data.Format("数据接收完毕，你想把远程传来的共计%d条数据记录，\r\n存入本地对应的库表中吗?",m_PassDataRecords);
				
				if(MessageBox(data,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
				{
					
					//处理重复数据记录 m_DataName   表名,TxtFileName  导入文本文件
					DealRepeatRecord(DataName,FileName);
                  
					//如果是用户数据表或变台表
					if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
					{
						//树控件重新刷新一次
						RefreshTree();
					}  
					
					MessageBox("远程传入数据存入本地数据表完毕！"," ",MB_OK);
					
				}
				
			}
			
		}
		//不是读模块生成的数的话
	
	}

}

//显示接收来的数据
void CIFRMView::AppearAccept(CString m_dataname)
{
	
	CString      StrSql,m_filename;
	CDatabase                   db;
	CStringArray         m_ColName;
	int            m_positions = 1;
	char                    s[300];

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
		StrSql.Format("SELECT * FROM %s",m_dataname);
		rs.Open(CRecordset::forwardOnly,StrSql);
		
		//得到字段个数
		short m_fileds = rs.GetODBCFieldCount();
		
		if(m_dataname ==  "TB_ELECTRICITY")
		{
			//用电种类和电价表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_ELECTRICITYS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_TRANSFORMER")
		{
			
			//变台信息数据表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_TRANSFORMERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_AMMETER")
		{
			
			//电表信息数据表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_AMMETERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_USER")
		{
			
			//用户信息库数据表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_USERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_GARRISON")
		{
			
			//驻留数据表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_GARRISONS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_REALTIME")
		{
			//正式读表数据表
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_REALTIMES[i + 1]);
			}
			
		}
		//关闭数据库
		rs.Close( );
		db.Close( );
		
		//删除所有的数据
		m_Grid.DeleteAllItems();
		m_Grid.ShowWindow(SW_SHOW);		
		
		TRY { 

			m_Grid.SetFixedRowCount(1);
			m_Grid.SetRowCount(1);           //行
			m_Grid.SetColumnCount(m_fileds); //列
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
            
            #ifndef _WIN32_WCE
			   dwTextStyle |= DT_END_ELLIPSIS;
            #endif
			int col;
			for ( col = 0; col < m_Grid.GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = 0;
				Item.col = col;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%s",m_ColName[col]);
				m_Grid.SetItem(&Item);
				m_Grid.SetColumnWidth(col,80); 
			}
			
			//读取文本文件数据
			m_filename   =  GetFolder() + m_dataname + ".TXT";
		      
			int m_lines  =  GetDataLines(m_filename);
			
			if(m_lines < 0)
			{
				return;
			}
            
			ShowProgressCtrl(TRUE);

			status("正在显示接收数据，请稍侯... ");
            SetProgressCtrlRange(0, m_lines,1);
	        
			FILE   *fp;
			if((fp=fopen(m_filename,"r"))!=NULL)
			{
				
				while(!feof(fp))
				{
					//如果为空则退出
					if(fgets(s,300,fp) == NULL)
					{
						break;
					}
					
					StrSql =   s;
					StrSql.TrimRight();
					StrSql.TrimLeft();

					//从文本文件中取数
					if(!StrSql.IsEmpty())
					{
						
						col  = 0;
						
						//以,为分隔符,分解字符串
						while(StrSql.Find(',') != -1)
						{				
							
							int 	k   =  StrSql.Find(',');
							
							if(k != -1)
							{
								
								m_ColName[col]  =  StrSql.Left(k);
								m_ColName[col].TrimLeft();
								m_ColName[col].TrimRight();
								
								if(m_ColName[col].GetLength() == 23 && m_ColName[col].Find("-")!=-1 && m_ColName[col].Find(":")!= -1)
								{
									m_ColName[col] = m_ColName[col].Left(19);
								}
								
								StrSql          =  StrSql.Right(StrSql.GetLength() - k - 1);
								
								if(col > m_fileds - 2)
								{
									break;
								}
								col++;
							}
							
						}
						
						m_ColName[col] =  StrSql;
						
						m_ColName[col].TrimLeft();
						m_ColName[col].TrimRight();
						
						if(m_ColName[col].GetLength() == 23 && m_ColName[col].Find("-")!=-1 && m_ColName[col].Find(":")!= -1)
						{
							m_ColName[col] = m_ColName[col].Left(19);
						}
						
						m_Grid.InsertRow(_T(" "), -1);
						m_Grid.Invalidate(); 
						
						for ( col = 0; col < m_Grid.GetColumnCount(); col++)
						{ 
							GV_ITEM  Item;
							Item.mask    = GVIF_TEXT|GVIF_FORMAT;
							Item.row     = m_Grid.GetRowCount() - 1;
							Item.col     = col;
							Item.nFormat = dwTextStyle;
							Item.strText.Format("%s",(m_ColName[col]));
							m_Grid.SetItem(&Item);
						}
						
						m_Grid.Invalidate();
						
						m_Grid.SetBkColor(RGB(255,255,255));

						m_Grid.Refresh();
						SurrenderWindowMessage();
						
					}	
					SetProgressCtrlSetIt();
				}
				
				//关闭文件指针
				fclose(fp);	

				m_Grid.SetModified(FALSE,-1,-1);
				m_Grid.AutoSize();
				status("显示接收数据完毕... ");
				ShowProgressCtrl(FALSE);
			}

		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
		END_CATCH
   }

}


void CIFRMView::OnUpdateDisconnect(CCmdUI* pCmdUI) 
{

	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(m_Com.GetPortOpen());
			break;
		}
	case 1:
		{	//电话拔号的标志,且是电局版的时候
			pCmdUI->Enable(m_Com.GetCDHolding());
			break;
		}
	case 2:
		{   
			//连接标志
			pCmdUI->Enable(m_IsConnect);
			break;
		}
	}
	
}

//断开连接
void CIFRMView::OnConnectsuccess() 
{
    DisConnect(m_sendkind);	
	
	if(!AppInfo::Instance().m_WhichKind)
	{
		KillTimer(3);
		//演示或隐藏动画
		OperationAnimation(FALSE);
		//隐藏滚动条
		ShowProgressCtrl(FALSE);
		//得到错误的次数
		m_GetErrors     =     0;
	
	}
				
}

//更新数据各种表结构
BOOL CIFRMView::UpdateDataTable()
{	
	//写上关程序时间
	CString      m_Sqlstr,str;
	CTime timet = CTime::GetCurrentTime();	    
	str.Format("【%4d-%02d-%02d %02d:%02d:%02d】软件运行",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	WriteToLog(str);

	//是否存在此表
	BOOL  m_IsExisting  = FALSE; 
	BOOL  m_Updateing   = FALSE;

	/*
	//修改用户数据表
	m_Sqlstr= "ALTER TABLE TB_USER ALTER COLUMN USER_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//增加主键
	m_Sqlstr= "ALTER TABLE TB_USER ADD PRIMARY KEY (USER_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	

	//修改驻留数据表
	m_Sqlstr= "ALTER TABLE TB_GARRISON ALTER COLUMN GARRISON_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//增加主键
	m_Sqlstr= "ALTER TABLE TB_GARRISON ADD PRIMARY KEY (GARRISON_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	
	//修改正式读表数据
	m_Sqlstr= "ALTER TABLE TB_REALTIME ALTER COLUMN REALTIME_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//增加主键
	m_Sqlstr= "ALTER TABLE TB_REALTIME ADD PRIMARY KEY (REALTIME_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	*/

	//修改原来的驻留时间字符串
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,6,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,6,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
    m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,9,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,9,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,12,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,12,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,15,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,15,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,18,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,18,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

	//包头的中间库

	{
		//如果不是包头的数据,则删除
        if(IsCurveTableExist("TB_MANAGERANGE"))
		{
			m_Sqlstr.Format("DROP TABLE TB_MANAGERANGE");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		} 
		
		if(IsCurveTableExist("TB_USERTEMPWS"))
		{
			m_Sqlstr.Format("DROP TABLE TB_USERTEMPWS");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}
		
		//如果没有无功补偿表
        if(!IsCurveTableExist("TB_WUGONG"))
		{

			m_Sqlstr.Format("CREATE TABLE [dbo].[TB_WUGONG] (\
				          [WUGONG_MODULE] [bigint] NOT NULL ,\
				          [WUGONG_SPACE]  [int]    NOT NULL \
				                            ) ON [PRIMARY]");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		
		}
		
		//如果没有无功补偿表
        if(!IsCurveTableExist("TB_WGUPDOWN"))
		{
			m_Sqlstr.Format("CREATE TABLE [dbo].[TB_WGUPDOWN] (\
								[WGUPDOWN_UP] [int] NOT NULL ,\
								[WGUPDOWN_DOWN] [int] NOT NULL ,\
								[WGUPDOWN_EVERYTIME] [smallint] NULL\
								) ON [PRIMARY]");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		} 
		
	}

	//如果没有接线错误表
    if(!IsCurveTableExist("TB_LINEERROR"))
	{
	   m_Sqlstr= "CREATE TABLE   [dbo].[TB_LINEERROR] (\
							[LINEERROR_MODULE]   [bigint]  NULL ,\
							[LINEERROR_READTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
							[LINEERROR_HALTTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
							[LINEERROR_KINDS]    [tinyint]  NULL \
							) ON [PRIMARY]";

		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	} 
	
	//如果没有换表信息表
    if(!IsCurveTableExist("TB_CHANGEAMMETER"))
	{
	   m_Sqlstr= "CREATE TABLE   [dbo].[TB_CHANGEAMMETER] (\
						[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,\
						[CHANGEAMMETER_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTAL] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NOT NULL ,\
						[CHANGEAMMETER_JFDL] [float] NOT NULL ,\
						[CHANGEAMMETER_FDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_PDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_GDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_UPDATETIME] [datetime] NOT NULL ,\
						[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL \
							) ON [PRIMARY]";

		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		//增加主键
		m_Sqlstr= "ALTER TABLE TB_CHANGEAMMETER ADD PRIMARY KEY (CHANGEAMMETER_MODULENO)";
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	}  
	
	//删除原来历史读表记录
	if(IsCurveTableExist("TB_HISTORYDATA"))
	{
		str.Format("Drop TABLE  %s","TB_HISTORYDATA");
		CDataBaseInstance::ExecuteDataBaseSQL(str);
	}

    //如果有换表信息
	if(IsCurveTableExist("TB_CHANGEAMMETER"))
	{
		
		if(GetFieldNumbers("TB_CHANGEAMMETER") != 22)
		{
			//删除原来的表
			m_Sqlstr.Format("DROP TABLE TB_CHANGEAMMETER");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

			//新生成表
			m_Sqlstr = "CREATE TABLE [dbo].[TB_CHANGEAMMETER] (\
						[CHANGEAMMETER_MODULENOOLD] [bigint] NOT NULL ,\
						[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,\
						[CHANGEAMMETER_NOOLD] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_WORKDEGREEOLD] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTALOLD] [float] NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTAL] [float] NULL ,\
						[CHANGEAMMETER_LOSEDEGREEOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTALOLD] [float] NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NULL ,\
						[CHANGEAMMETER_JFDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_JFDL] [float] NOT NULL ,\
						[CHANGEAMMETER_FDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_FDL] [float] NOT NULL ,\
						[CHANGEAMMETER_PDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_PDL] [float] NOT NULL ,\
						[CHANGEAMMETER_GDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_GDL] [float] NOT NULL ,\
						[CHANGEAMMETER_UPDATETIME] [datetime] NOT NULL ,\
						[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NOT NULL\
						) ON [PRIMARY]";

			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		
		}

	}

	//查用户表字段个数
	short m_fields = GetFieldNumbers("TB_USER");
	
	//如果小于34才升级
	if(m_fields < 35)
	{
		
		CProgressDlg pDialog(ID_PROGRESSDLGUPDATE);
		pDialog.Create(NULL);
		pDialog.SetRange(1,20);
		pDialog.SetStep(1);
		pDialog.SetPos(1);	 

		////////////////////1、用户信息//////////////////////////////
        m_Sqlstr = " 	CREATE TABLE [dbo].[TB_USER] (\
			[USER_COMPANY] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNO] [char] (5) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MOTHERLINE] [int] NULL ,\
			[USER_BAKMOTHERLINE] [int] NULL ,\
			[USER_LINENO] [int] NULL ,\
			[USER_BAKLINENO] [int] NULL ,\
			[USER_LINENAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TRANSFORMERNO] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MODULENO] [bigint] NULL ,\
			[USER_PHASE] [tinyint] NULL ,\
			[USER_NAME] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_NO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_OLDNO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ADDRESS] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_PHONE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ELECTRICITYKIND] [tinyint] NULL ,\
			[USER_AMMETERNO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_AMMETERKIND] [tinyint] NULL ,\
			[USER_INSTALLTIME] [datetime] NULL ,\
			[USER_SUPPLYMODE] [tinyint] NULL ,\
			[USER_INITIALVALUE] [float] NULL ,\
			[USER_MULTIPLE] [int] NULL ,\
			[USER_PROTOCOL] [tinyint] NULL ,\
			[USER_DESCRIBE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_READLABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TIMELABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ETSTATUS] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_IDNO] [int] NULL ,\
			[USER_AMMETERTYPE] [varchar] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_SENDANGLE] [tinyint] NULL ,\
			[USER_DOWNVALUE] [int] NULL ,\
        	[USER_UPVALUE]   [int] NULL, \
			[USER_RUNSTATUS] [tinyint] NULL,\
			[USER_ZHULABEL] [char] (93) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
        
		
		//用户信息
		if(ModifyDataTable("TB_USER",m_Sqlstr,1))
		{
           m_Sqlstr = "UPDATE TB_USER SET USER_RUNSTATUS=0";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   pDialog.StepIt();
		}
		else
		{
			pDialog.CheckCancelButton();
			MessageBox("模块用户信息表升级错误！！"," ",MB_OK|MB_ICONWARNING);
            return FALSE;
		}
	    
		///////////////////2、驻留表信息/////////////////////
	    m_IsExisting  = IsCurveTableExist("TB_GARRISON");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_GARRISON") != 19)
			{
				m_Updateing = TRUE;
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{

		   m_Sqlstr = "  CREATE TABLE [dbo].[TB_GARRISON] (\
			  [GARRISON_MODULENO] [bigint] NOT NULL ,\
			  [GARRISON_WORKDEGREE] [float] NULL ,\
			  [GARRISON_WORKDEGREETOTAL] [float] NULL ,\
			  [GARRISON_LOSEDEGREE] [float] NULL ,\
			  [GARRISON_LOSEDEGREETOTAL] [float] NULL ,\
			  [GARRISON_ACURRENT] [float] NULL ,\
			  [GARRISON_BCURRENT] [float] NULL ,\
			  [GARRISON_CCURRENT] [float] NULL ,\
			  [GARRISON_AVOLTAGE] [float] NULL ,\
			  [GARRISON_BVOLTAGE] [float] NULL ,\
			  [GARRISON_CVOLTAGE] [float] NULL ,\
			  [GARRISON_JFDL] [float] NULL ,\
			  [GARRISON_FDL] [float] NULL ,\
			  [GARRISON_PDL] [float] NULL ,\
			  [GARRISON_GDL] [float] NULL ,\
			  [GARRISON_GLYS] [float] NULL ,\
			  [GARRISON_TRANSCRIBETIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [GARRISON_PROTOCOL] [smallint] NOT NULL ,\
			  [GARRISON_HALTTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL \
			  ) ON [PRIMARY]";
	
			 //修改和新的数据表一样
			 if(ModifyDataTable("TB_GARRISON",m_Sqlstr,1))
			 {
				 pDialog.StepIt();
			 }
			 else
			 {
				 pDialog.CheckCancelButton();
				 MessageBox("驻留数据表升级错误！！"," ",MB_OK|MB_ICONWARNING);
				 return FALSE;
			 }
	
		}
		else
		{
			pDialog.StepIt();
		}
		
		////////////////////3、实时读表////////////////////////
        m_IsExisting  = IsCurveTableExist("TB_REALTIME");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_REALTIME") != 18)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 		CREATE TABLE [dbo].[TB_REALTIME] (\
				[REALTIME_MODULENO] [bigint] NOT NULL ,\
				[REALTIME_WORKDEGREE] [float] NULL ,\
				[REALTIME_WORKDEGREETOTAL] [float] NULL ,\
				[REALTIME_LOSEDEGREE] [float] NULL ,\
				[REALTIME_LOSEDEGREETOTAL] [float] NULL ,\
				[REALTIME_ACURRENT] [float] NULL ,\
				[REALTIME_BCURRENT] [float] NULL ,\
				[REALTIME_CCURRENT] [float] NULL ,\
				[REALTIME_AVOLTAGE] [float] NULL ,\
				[REALTIME_BVOLTAGE] [float] NULL ,\
				[REALTIME_CVOLTAGE] [float] NULL ,\
				[REALTIME_JFDL] [float] NULL ,\
				[REALTIME_FDL] [float] NULL ,\
				[REALTIME_PDL] [float] NULL ,\
				[REALTIME_GDL] [float] NULL ,\
				[REALTIME_GLYS] [float] NULL ,\
				[REALTIME_TRANSCRIBETIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
				[REALTIME_PROTOCOL] [smallint] NOT NULL \
				) ON [PRIMARY]";
			
			if(ModifyDataTable("TB_REALTIME",m_Sqlstr,1))
			{
				pDialog.StepIt();
			}
			else
			{
				pDialog.CheckCancelButton();
				MessageBox("实时读表数据表升级错误！！"," ",MB_OK|MB_ICONWARNING);
				return FALSE;
			}
		}
		else
		{
			pDialog.StepIt();
			
		}

		////////////////////4、电表数据信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_AMMETER");  //是否存在此表
        m_Updateing   =                           FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_AMMETER") != 4)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "CREATE TABLE [dbo].[TB_AMMETER] (\
		    [AMMETER_TYPE]         [char] (10) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
		    [AMMETER_MANUFACTURER] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		    [AMMETER_IMPULSE]      [int] NOT NULL ,\
		    [AMMETER_REMARK]       [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
		    ) ON [PRIMARY]";
			
			//修改和新的数据表一样
			if(ModifyDataTable("TB_AMMETER",m_Sqlstr,1))
			{
				pDialog.StepIt();	
			}
			else
			{
				pDialog.CheckCancelButton();
				MessageBox("电表数据信息表升级错误！！"," ",MB_OK|MB_ICONWARNING);
				return FALSE;
			}
			
			//增加主键
			m_Sqlstr= "ALTER TABLE TB_AMMETER ADD PRIMARY KEY (AMMETER_TYPE)";
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
			
			pDialog.StepIt();
		}
		else
		{
			pDialog.StepIt();
			pDialog.StepIt();
		}	

		///////////////////5、驻留时间/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_HALTTIME");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_HALTTIME") != 1)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_HALTTIME] (\
			[HALTTIME_TIME] [char] (19) COLLATE Chinese_PRC_CI_AS NOT NULL \
			) ON [PRIMARY] ";
			
			//修改和新的数据表一样
			ModifyDataTable("TB_HALTTIME",m_Sqlstr,0);
		}
	
		pDialog.StepIt();
		

		///////////////////6、手拉手信息/////////////////////

		m_IsExisting  = IsCurveTableExist("TB_HAND");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_HAND") != 3)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_HAND] (\
				[HAND_NO] [tinyint] NULL ,\
				[HAND_STATIONNAME] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[HAND_STATUS] [tinyint] NULL \
				) ON [PRIMARY]";
			//修改和新的数据表一样
			ModifyDataTable("TB_HAND",m_Sqlstr,0);
		}

		pDialog.StepIt();

		//////////////////////7、自动设置信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_Auto");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_Auto") != 110)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{

            m_Sqlstr = "CREATE TABLE [dbo].[TB_Auto] (";
			
			for(int i = 1; i <= 110; i ++)
			{
				if(i < 110)
				{
					str.Format("[Auto_Parameter%d] [tinyint] NULL,",i);
					m_Sqlstr = m_Sqlstr  + str;
				}
				else
				{
					str.Format("[Auto_Parameter%d] [tinyint] NULL",i);
					m_Sqlstr = m_Sqlstr  + str;
				}
				
			}
			
			m_Sqlstr = m_Sqlstr + ") ON [PRIMARY]";
			
					
			str.Format("Drop TABLE  %s","TB_Auto");
			CDataBaseInstance::ExecuteDataBaseSQL(str);//删除老表

			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);//建立新表
		
		}
	
		pDialog.StepIt();


        //////////////////////8、串口信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_COMINFORMATION");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_COMINFORMATION") != 6)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "CREATE TABLE [dbo].[TB_COMINFORMATION] (\
					  [COMINFORMATION_COM] [smallint] NULL ,\
					  [COMINFORMATION_BITS] [smallint] NULL ,\
					  [COMINFORMATION_CHECKBIT] [smallint] NULL ,\
					  [COMINFORMATION_DATABIT] [smallint] NULL ,\
					  [COMINFORMATION_STOPBIT] [smallint] NULL ,\
					  [COMINFORMATION_AUTOREPLY] [tinyint] NULL \
					  ) ON [PRIMARY]";
		
			//修改和新的数据表一样
			ModifyDataTable("TB_COMINFORMATION",m_Sqlstr,0);
		}
		pDialog.StepIt();
	  
	   //////////////////////9、居民电量信息/////////////////////

		m_IsExisting  = IsCurveTableExist("TB_DWELLERACCOUNT");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_DWELLERACCOUNT") != 10)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "	    CREATE TABLE [dbo].[TB_DWELLERACCOUNT] (\
			  [用户号] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [用户名] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [表号] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [上月指针] [float] NULL ,\
			  [本月指针] [float] NULL ,\
			  [电量] [float] NULL ,\
			  [优待电量] [float] NULL ,\
			  [优待电费] [float] NULL ,\
			  [电价] [float] NULL ,\
			  [合计] [float] NULL \
			  ) ON [PRIMARY]";
			
			//修改和新的数据表一样
			ModifyDataTable("TB_DWELLERACCOUNT",m_Sqlstr,0);
		}

		pDialog.StepIt();

	    //////////////////////10、用电种类信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITY");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITY") != 4)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "	CREATE TABLE [dbo].[TB_ELECTRICITY] (\
				[ELECTRICITY_NO] [tinyint] NOT NULL ,\
				[ELECTRICITY_KIND] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[ELECTRICITY_PRICE] [float] NOT NULL ,\
				[ELECTRICITY_REMARK] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";
				
			//修改和新的数据表一样
			ModifyDataTable("TB_ELECTRICITY",m_Sqlstr,0);
			
			// 加上主键
			m_Sqlstr= "ALTER TABLE TB_ELECTRICITY ADD PRIMARY KEY (ELECTRICITY_NO)";
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}

		pDialog.StepIt();
		
		//////////////////////11、用电线损信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITYLOSS");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITYLOSS") != 7)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "		CREATE TABLE [dbo].[TB_ELECTRICITYLOSS] (\
				[变台名称] [char] (26) COLLATE Chinese_PRC_CI_AS NULL ,\
				[容量] [int] NULL ,\
				[户数] [int] NULL ,\
				[本月供电量] [float] NULL ,\
				[本月售电量] [float] NULL ,\
				[损失电量] [float] NULL ,\
				[线损率] [float] NULL \
				) ON [PRIMARY]";
				
			//修改和新的数据表一样
			ModifyDataTable("TB_ELECTRICITYLOSS",m_Sqlstr,0);
		}

		pDialog.StepIt();
			
		///////////////////12、用电统计信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITYTOTAL");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITYTOTAL") != 6)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "		CREATE TABLE [dbo].[TB_ELECTRICITYTOTAL] (\
				[变台名称] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
				[电能表编号] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[上月读数] [float] NULL ,\
				[本月读数] [float] NULL ,\
				[倍率] [int] NULL ,\
				[电量] [float] NULL \
				) ON [PRIMARY]";
				
			//修改和新的数据表一样
			ModifyDataTable("TB_ELECTRICITYTOTAL",m_Sqlstr,0);
		}

        pDialog.StepIt();

        ///////////////////13、抄表清单信息/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_EXCERPTION");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_EXCERPTION") != 9)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = "	CREATE TABLE [dbo].[TB_EXCERPTION] (\
				[用户档案、名称、原户号] [char] (70) COLLATE Chinese_PRC_CI_AS NULL ,\
				[计量表编号] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[倍率] [int] NULL ,\
				[用电类别] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[类型] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[上次读数] [float] NULL ,\
				[本次读数] [float] NULL ,\
				[金额] [float] NULL ,\
				[电量] [float] NULL \
				) ON [PRIMARY]";
			 
			//修改和新的数据表一样
			ModifyDataTable("TB_EXCERPTION",m_Sqlstr,0);
		}

		pDialog.StepIt();
	
		////////////////////14、IP地址////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_IP");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_IP") != 2)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_IP] (\
				[IP_ADDRESS] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[IP_COMPUTER] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]	";
			//修改和新的数据表一样
			ModifyDataTable("TB_IP",m_Sqlstr,0);
		}
		pDialog.StepIt();

   		
		////////////////////15、电话管理////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_PHONE");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_PHONE") != 3)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_PHONE] (\
				[PHONE_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
				[PHONE_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
				[PHONE_PASSWORD] [varchar] (8) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_PHONE",m_Sqlstr,0);
		}
		pDialog.StepIt();
        
		////////////////////16、TB_REFRESHTIME////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_REFRESHTIME");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_REFRESHTIME") != 1)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_REFRESHTIME] (\
				[USER_REFRESHTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NOT NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_REFRESHTIME",m_Sqlstr,0);
		}

		pDialog.StepIt();

        ////////////////////17、变台信息//////////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_TRANSFORMER");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_TRANSFORMER") != 7)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			m_Sqlstr = " CREATE TABLE [dbo].[TB_TRANSFORMER] (\
				[TRANSFORMER_NO] [char] (40) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[TRANSFORMER_TYPE] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CAPACITY] [int] NULL ,\
				[TRANSFORMER_INSTALLTIME] [datetime] NULL ,\
				[TRANSFORMER_POSITION] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_OWNERSHIP] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CONNECTFORM] [tinyint] NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_TRANSFORMER",m_Sqlstr,0);
		}
		pDialog.StepIt();
        

	  ////////////////////18、TB_ZXACCOUNT//////////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ZXACCOUNT");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ZXACCOUNT") != 17)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			  m_Sqlstr = " 	CREATE TABLE [dbo].[TB_ZXACCOUNT] (\
					[用户号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[用户名] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
					[电量合计] [float] NULL ,\
					[电费合计] [float] NULL ,\
					[表计号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[安装类型] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[电费类别] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[表计倍率] [int] NULL ,\
					[上月表码] [float] NULL ,\
					[本月表码] [float] NULL ,\
					[表计电量] [float] NULL ,\
					[分类项目] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
					[电量] [float] NULL ,\
					[电价] [float] NULL ,\
					[电费] [float] NULL ,\
					[税金] [float] NULL ,\
					[合计] [float] NULL \
					) ON [PRIMARY]";
			  ModifyDataTable("TB_ZXACCOUNT",m_Sqlstr,0);
		}

	    pDialog.StepIt();

        ////////////////////19、TB_DateAuto按驻留日期设置自动驻留///////
 		m_IsExisting  = IsCurveTableExist("TB_DateAuto");  //是否存在此表
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_DateAuto") != 67)
			{
				m_Updateing = TRUE;
				m_Sqlstr.Format("DROP TABLE TB_DateAuto");//删除原来的表
				CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//如果要更新
		if(m_Updateing)
		{
			  m_Sqlstr = "CREATE TABLE [dbo].[TB_DateAuto] (";
   
			   for(int i = 1; i <= 67; i ++)
			   {

				   if(i < 67)
				   {
					   str.Format("[Auto_Parameter%d] [tinyint] NULL,",i);
					   m_Sqlstr = m_Sqlstr  + str;
				   }
				   else
				   {
					   str.Format("[Auto_Parameter%d] [tinyint] NULL",i);
					   m_Sqlstr = m_Sqlstr  + str;
				   }
				   
			   }
   
			   m_Sqlstr = m_Sqlstr + ") ON [PRIMARY]";	
			   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);//建立新表
		}

        pDialog.StepIt();
	
		//删除原来定时读表的表
		if(IsCurveTableExist("TB_AUTOINFO"))
		{
			 str.Format("Drop TABLE  %s","TB_AUTOINFO");
			 CDataBaseInstance::ExecuteDataBaseSQL(str);//删除老表
		}  
    
   }
   else
   {
	

   }
 
   //修改用户数据表
   m_Sqlstr= "ALTER TABLE TB_USER ALTER COLUMN USER_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
  
   m_Sqlstr= "ALTER TABLE TB_USER DROP PRIMARY KEY (USER_MODULENO) ";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

   //建立索引
   m_Sqlstr= "CREATE INDEX TB_USERINDEX ON TB_USER (USER_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //修改驻留数据表
   m_Sqlstr= "ALTER TABLE TB_GARRISON ALTER COLUMN GARRISON_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   //建立索引
   m_Sqlstr= "CREATE INDEX TB_GARRISONINDEX ON TB_GARRISON (GARRISON_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //修改正式数据
   m_Sqlstr= "ALTER TABLE TB_REALTIME ALTER COLUMN REALTIME_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   //建立索引
   m_Sqlstr= "CREATE INDEX TB_REALTIMEINDEX ON TB_REALTIME (REALTIME_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立电表索引
   m_Sqlstr= "CREATE INDEX TB_AMMETERINDEX ON TB_AMMETER (AMMETER_TYPE)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立自动驻留索引
   m_Sqlstr= "CREATE INDEX TB_AutoINDEX ON TB_Auto (Auto_Parameter1)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立换表模块索引
   m_Sqlstr= "CREATE INDEX TB_CHANGEAMMETERINDEX ON TB_CHANGEAMMETER (CHANGEAMMETER_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立自动驻留索引
   m_Sqlstr= "CREATE INDEX TB_DateAutoINDEX ON TB_DateAuto (Auto_Parameter1)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立手拉手索引
   m_Sqlstr= "CREATE INDEX TB_HANDINDEX ON TB_HAND (HAND_NO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立驻留日期索引
   m_Sqlstr= "CREATE INDEX TB_REFRESHTIMEINDEX ON TB_REFRESHTIME (USER_REFRESHTIME)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立驻留时间索引
   m_Sqlstr= "CREATE INDEX TB_HALTTIMEINDEX ON TB_HALTTIME (HALTTIME_TIME)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //建立变台索引
   m_Sqlstr= "CREATE INDEX TB_TRANSFORMERINDEX ON TB_TRANSFORMER (TRANSFORMER_NO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

   return TRUE;

}


//得到表字段的个数
short CIFRMView::GetFieldNumbers(CString m_DataName)
{	
	CDatabase              db;
	CString          m_Sqlstr;	
    short         nFields = 0;

    //打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);
		//检查用户数据表
		m_Sqlstr.Format("SELECT * FROM %s",m_DataName);
		rs.Open(CRecordset::forwardOnly,m_Sqlstr);
		//得到字段个数
		nFields = rs.GetODBCFieldCount( );
		rs.Close();
		db.Close();
	}
	
	return nFields;
}

//停电和送电处理
void CIFRMView::OnStoporsend() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CELECTDEALDlg          DLG;
	CString         PassStr;
	int   m_records   =   0;
	
	if(DLG.DoModal() == IDOK)
	{
		
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		
		//记录个数
		m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition());
	
		switch(DLG.m_radio)
		{
		case 0:
			{	
				PassStr.Format("你想查询所选择用户［%d户］的用电状态吗？",m_records);
				break;
			}
		case 1:
			{
				PassStr.Format("查询所选择用户［%d户］的停电次数吗？",m_records);
				break;
			}
		case 2:
			{
				PassStr.Format("送所选择用户［%d户］的用电吗？",m_records);
				break;
			}
		case 3:
			{
				PassStr.Format("停所选择用户［%d户］的用电吗？",m_records);
				break;
			}
		case 4:
			{
				PassStr.Format("所选择用户［%d户］销户吗？",m_records);
				break;
			}
		case 5:
			{
				PassStr.Format("所选择用户［%d户］取消销户吗？",m_records);
				break;
			}
		}
		
		if(MessageBox(PassStr," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	
		//送所选多户电,电局版本 TRUE 变电站版本  FALSE电局版
		if(AppInfo::Instance().m_WhichKind == FALSE)
		{	
			//停电操作
			//CString title        列标题
			//CString Result       结论
			//CString ConStr       条件范围
			//BYTE    orders       命令关键字
			//BOOL    OnlyReadNot  TRUE  只读没有测试出相的模块
			//                     FALSE 反之
			//int  times        读每个模块的次数
			//BOOL OnlyOnce TRUE  好多表共用一个模块时只测试一次   FALSE 每个表都测试一次
			//int  MaxIValue    最大值(为写参数时用)
			//int  MinIValue    最小值
			//int  intervals    间  隔
			
			//供电局要变电站执行停电操作命令
			//格式：BEGINS;变电站编号;COMMAND:04:参数1:参数2;ENDS
			switch(DLG.m_radio)
			{
			case 0:
				{
					//用电状态   
					//BEGINS;COMMAND:11:参数1:参数2:参数3:参数4:参数5:参数6:参数7:参数8:参数9:参数10;ENDS 
					//                  参数1---标题         参数2---结果                   参数3---条件范围
					//                  参数4---命令字       参数5---是否只读相不定         参数6---次数        
					//                  参数7---是否只读一次 参数8---最小值(也当发送时传数) 参数9---最大值  
					//                  参数10--间隔         读写各项测试参数,处理各项参数
					//                  参数11               满足条件记录个数
				    PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","用电状态","查询成功",pMainFrm->m_wndMyDialogBar.SelectCondition(),0xf4,FALSE,5,1,1,1,1,m_records);
					break;
				}
			case 1:
				{
					//模块停电次数
				    PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","停电次数","查询成功",pMainFrm->m_wndMyDialogBar.SelectCondition(),0x3C,FALSE,5,1,1,1,1,m_records);
					break;
				}
			case 2:
				{
					//送电
					PassStr.Format("BEGINS;COMMAND:05:%s:%d;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition(),m_records);
					break;
				}
			case 3:
				{
					//停电
					PassStr.Format("BEGINS;COMMAND:04:%s:%d;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition(),m_records);
					break;
				}
			case 4:
				{
					//销户
					PassStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			        CDataBaseInstance::ExecuteDataBaseSQL(PassStr);
					PassStr.Format("BEGINS;COMMAND:35:%s;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition());
					break;
				}
			case 5:
				{
					//取消销户
					PassStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			        CDataBaseInstance::ExecuteDataBaseSQL(PassStr);
					PassStr.Format("BEGINS;COMMAND:36:%s;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition());
					break;
				}

			}	
			
			//远程发送停电送电的指令
			SelectSendString(m_sendkind, PassStr, TRUE,TRUE,TRUE);
					
		}
		else
		{
			//停电送电操作  TRUE 变电站版  FALSE 电局版
			switch(DLG.m_radio)
			{
			case 0:
				{
					//
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","用电状态","查询成功",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf4,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 1:
				{
					//
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","停电次数","查询成功",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0x3C,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 2:
				{
					//送电操作
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","送电操作","送电成功",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf6,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 3:
				{
					//停电操作
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","停电操作","停电成功",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf8,FALSE,5,TRUE,1,1,1);
					break;
				}

			}
			
			if(DLG.m_radio <= 3)
			{
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
			}
			else
			{
				
				switch(DLG.m_radio)
				{
				case 4:
					{
						//销户
						SendContionStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
						CDataBaseInstance::ExecuteDataBaseSQL(SendContionStr);
						MessageBox("所选用户销户成功！","  ",MB_OK|MB_ICONASTERISK);
						break;
					}
				case 5:
					{	
						//取消销户
						SendContionStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
						CDataBaseInstance::ExecuteDataBaseSQL(SendContionStr);
						MessageBox("所选用户取消销户成功！","  ",MB_OK|MB_ICONASTERISK);
						break;
					}
				}
				
			}
			
		}
		
	}
	
}


void CIFRMView::OnUpdateStoporsend(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
	
}

void CIFRMView::EverySendInfo()
{
   WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	
	//如果有手拉手的话	
	if(m_status)
	{
		
		CByteArray  m_ByteSendOnce;	
		m_ByteSendOnce.Add(62);
		m_ByteSendOnce.Add(62);
		m_ByteSendOnce.Add(71);
		m_ByteSendOnce.Add(72);
		m_ByteSendOnce.Add(32);
		m_ByteSendOnce.Add(22);
		
		//能够发的标志
		m_StartRead    =  TRUE;
		
		//好多种协议，每一种都发一次
		for(int kk = 0; kk < m_ByteSendOnce.GetSize(); kk ++)
		{
			
			//母线二段
			for(int j = 0; j < 2; j++)
			{
				
				
				//三相别 ABC
				for(int i = 0; i < 3; i++)
				{
					
					if(!m_StartRead)
					{
						break;
					}
					
					//ABC三相发指令,一个模块号为0的信号
					switch(i)
					{
					case 0:
						{   
							StatusStr.Format("正在手拉手调制[%d]站第[%d]段母线A相，协议[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					case 1:
						{   
							StatusStr.Format("正在手拉手调制[%d]站第[%d]段母线B相，协议[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					case 2:
						{
							StatusStr.Format("正在手拉手调制[%d]站第[%d]段母线C相，协议[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					}
					
					//状态栏上显示信息
					SendMessage(WM_EVENT, 1, 0);
					
					//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
					//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
					//SendMessage(WM_EVENT, 5, 0);
					
					if(!(SendOrderToSCM(0/*模块号*/,m_handno/*手拉手电站码*/,j + 1/*母线*/,1/*线号*/, i/*相选择0A 1B 2C*/, 3/* 延时过0点数*/,0xC0/* 要什么东西,命令字*/,0/*可放时间或其它东西*/,m_ByteSendOnce[kk],0)))
					{
						Beep(300,400);
						Beep(300,400);
					}
					
					//等待时间
					BYTE  m_SendTimers  =    0;
					
					if(m_ByteSendOnce[kk] == 22)
					{
						m_SendTimers =  8;
					}
					else
					{
						m_SendTimers = (m_ByteSendOnce[kk]%10)*8;
					}
					
					for(BYTE jj = 0 ; jj < m_SendTimers; jj ++)
					{
						SurrenderWindowMessage();
						
						if(m_StartRead)
						{
							Sleep(1000);
						}
						else
						{
							break;
						}
						
					}	
					
					//发送的字符在远程机器上显示BEGINS;MESSAGE:1:内容;ENDS   状态栏显示信息
					//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS","");
					//SendMessage(WM_EVENT, 5, 0);	
					
				}
				
			}
			
		}
	
    }
		
		
	//如果要线路检测电流
	CTime timet = CTime::GetCurrentTime();
	
	if(timet.GetMinute() < 30)
	{
		//线路检测电流
		SendMessage(WM_EVENT, 15, 0);

		//无线模块电电流电压检测
//		SendMessage(WM_EVENT, 17, 0);	
		
		//检测无功补偿表操作
		SendMessage(WM_EVENT, 18, 0);

	}
	
//	m_StartRead = FALSE;

   TmpOnlyOneThreadRun.SetEvent();


}

void CIFRMView::OnUpdateDataappear(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
	
}

//算线损统计
void CIFRMView::BeginTotalLoss(CString m_Condtion,CString BeginTime,CString EndTime)
{	
	
	CDatabase                db;
	CString  m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,strsql;
	double         supplys,sales;
	int    doors       =       0;//户数
	int    m_records   =       0;//记录数
   
	//判断表是否存在
	if(IsCurveTableExist("TB_TOTLE"))
	{
		//删除原来的表
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
	}
	
	//生成临时表
    strsql.Format("SELECT * INTO TB_TOTLE FROM TB_USER WHERE %s",m_Condtion);
    CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);
		strsql = "SELECT count(*)  FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
		m_CompanySet.Open(dbOpenSnapshot,strsql);
		
		m_records = V_I4(&m_CompanySet.GetFieldValue(0));
        m_CompanySet.Close();
	
		strsql = "SELECT USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
        m_CompanySet.Open(dbOpenSnapshot,strsql);

	    ShowProgressCtrl(TRUE);
        SetProgressCtrlRange(0, m_records,1);
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
            m_STATIONNAME    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1));
            m_LINENAME       = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2));
            m_TRANSFORMERNO  = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(3));
			
			status("正在计算变台线损:" + m_TRANSFORMERNO);
			//供电量
			supplys = GetSubElc("SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE*TB_USER.USER_MULTIPLE)",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,0,BeginTime,EndTime);
			//售电量
			sales   = GetSubElc("SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE*TB_USER.USER_MULTIPLE)",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,1,BeginTime,EndTime);
			//变台下的户数某
			strsql.Format("USER_COMPANY='%s' AND USER_STATIONNAME='%s' AND USER_LINENAME='%s' AND USER_TRANSFORMERNO='%s' AND USER_AMMETERKIND<2 ",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO);
			//户数
			doors   = CDataBaseInstance::GetAllRecordsCount("TB_TOTLE",strsql);
			
			//如果下有用户，专变表下无用户
			if(doors > 0)
			{
				
				//如果供电量大于0
				if(supplys > 0)
				{
					strsql.Format("INSERT INTO TB_ELECTRICITYLOSS(户数,变台名称,容量,本月供电量,本月售电量,损失电量,线损率) VALUES (%d,'%s',%d,%.2f,%.2f,%.2f,%.2f)",doors,m_TRANSFORMERNO,SubCapability(m_TRANSFORMERNO),supplys,sales,supplys-sales,(supplys-sales)*100.0000/supplys);
				}
				else
				{	
					strsql.Format("INSERT INTO TB_ELECTRICITYLOSS(户数,变台名称,容量,本月供电量,本月售电量,损失电量) VALUES (%d,'%s',%d,%.2f,%.2f,%.2f)",doors,m_TRANSFORMERNO,SubCapability(m_TRANSFORMERNO),supplys,sales,supplys-sales);
				}
				
				CDataBaseInstance::ExecuteDataBaseSQL(strsql);

			}
		
			m_CompanySet.MoveNext();
            SetProgressCtrlSetIt();

		}

		m_CompanySet.Close();
		delete m_pDatabase;	
		
		//删除原来的表
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
		ShowProgressCtrl(FALSE);
	}

}


//得到某变台本身的总表值及下所有居民表和大用户表的和
//CString FieldName       所求字段名 TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName     公司名
//CString SubstationName  变电站名
//int     SubNo           变台号  
//CString LineName        线路名称
//CString SubNo           变台号
//short   kinds           种类 0－－－本身的表值 1－－下面所有居民表及大用户表的表和 
double CIFRMView::GetSubElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,CString SubNo,short kinds,CString BeginTime,CString EndTime)
{
    //打开数据库
	CString   strValue;
	CDatabase       db;	
	CString     strSql;
	double   sum1,sum2;
    sum1 = sum2    = 0;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		
		//和CRecordset连上
		CRecordset rs(&db);
	
		if(kinds == 0)
		{
			//某变台本身的表值
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4) ",Order,CompanyName,SubstationName,LineName,SubNo,BeginTime);
		}
		else
		{	
			//统计下面所有居民表及大用户表的表和
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND TB_USER.USER_AMMETERKIND<2 ",Order,CompanyName,SubstationName,LineName,SubNo,BeginTime);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		rs.GetFieldValue((short)0,strValue);
		sum1 = atof(strValue);
		rs.Close( );

		
		if(kinds == 0)
		{
			//某变台本身的表值
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4) ",Order,CompanyName,SubstationName,LineName,SubNo,EndTime);
		}
		else
		{	
			//统计下面所有居民表及大用户表的表和
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND TB_USER.USER_AMMETERKIND<2 ",Order,CompanyName,SubstationName,LineName,SubNo,EndTime);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		rs.GetFieldValue((short)0,strValue);
		sum2 = atof(strValue);
		rs.Close( );
		

		db.Close( );

		return sum2-sum1;
	}

	return 0;
}


//得到某一变台的容量
long CIFRMView::SubCapability(CString SubNo)
{   //打开数据库
	CDatabase         db;
	CString       strSql;
	CString     strValue = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		if(SubNo.IsEmpty())
		{
       	    strSql = "SELECT count(*) FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT count(*) FROM TB_TRANSFORMER WHERE TRANSFORMER_NO='%s'",SubNo);
			
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();
		
		if(SubNo.IsEmpty())
		{
       	    strSql = "SELECT TRANSFORMER_CAPACITY FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT TRANSFORMER_CAPACITY FROM TB_TRANSFORMER WHERE TRANSFORMER_NO='%s'",SubNo);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		for(int j = 0;j < fields; j++)
		{
			rs.GetFieldValue((short)0,strValue);
			strValue.TrimLeft();
			strValue.TrimRight();
			
			//库下滑一个记录
			rs.MoveNext();
		}
		
		//关闭数据库
		rs.Close( );
		db.Close( );
	}

	return atol(strValue);
}


//修改表的属性
BOOL CIFRMView::ModifyDataTable(CString m_TableName,CString m_TableSql,BOOL m_CheckRecords)
{

	//打开数据库
	CDatabase                             db;
	CString             m_Sqlstr,m_FieldName;
	int                             k,j,kkkk;
	CStringArray               TableColTitle;
    CStringArray     TableColTitleTempupdate;
    CStringArray               EqualColTitle;
	CString                              str;
	int                                    i;
	long     m_BeforeRecords, m_AfterRecords;
	m_BeforeRecords = m_AfterRecords    =  0;
	
	//////////////////////电表数据信息/////////////////////
	//判断表是否存在
	if(!IsCurveTableExist(m_TableName))
	{
		//不存在的话,则建立
		CDataBaseInstance::ExecuteDataBaseSQL(m_TableSql);
		return TRUE;
		
	}
	else
	{
		
		if(IsCurveTableExist("TEMPUPDAE"))
		{
			m_Sqlstr.Format("DROP FROM TEMPUPDAE");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}

		//之前的记录数
		m_BeforeRecords = CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL");
		//m_AfterRecords
		
		m_Sqlstr.Format("SELECT *  INTO TEMPUPDAE FROM %s",m_TableName);
	
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		m_Sqlstr.Format("Drop TABLE  %s",m_TableName);
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		//建立新的表
		CDataBaseInstance::ExecuteDataBaseSQL(m_TableSql);
	
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//和CRecordset连上
			CRecordset rs(&db );
			m_Sqlstr.Format("SELECT DISTINCT * FROM %s",m_TableName);
			rs.Open(CRecordset::forwardOnly,m_Sqlstr);
			
			//得到字段个数
			short nFields = rs.GetODBCFieldCount( );
			CODBCFieldInfo fieldinfo;
			
			for(int i = 0;i < nFields; i++)
			{
				//字段名
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_FieldName = fieldinfo.m_strName;
				m_FieldName.TrimLeft();
				m_FieldName.TrimRight();
				
				if(m_FieldName.Find("、") != -1  || m_FieldName.Find("-") != -1)
				{
					
					m_FieldName = "[" + m_FieldName + "]";
					
				}
				
				TableColTitle.Add(m_FieldName);
			}
			rs.Close( );
			
			//原来的表
			m_Sqlstr.Format("SELECT DISTINCT * FROM %s","TEMPUPDAE");
			rs.Open(CRecordset::forwardOnly,m_Sqlstr);
			
			//得到字段个数
			nFields = rs.GetODBCFieldCount( );
			
			for( i = 0;i < nFields; i++)
			{
				//字段名
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_FieldName = fieldinfo.m_strName;
				m_FieldName.TrimLeft();
				m_FieldName.TrimRight();
				
				if(m_FieldName.Find("、") != -1  || m_FieldName.Find("-") != -1)
				{
					
					m_FieldName = "[" + m_FieldName + "]";
					
				}
				
				TableColTitleTempupdate.Add(m_FieldName);
			}
			rs.Close( );
			db.Close( );
			
			//新表的字段数
			k  =  TableColTitle.GetSize();
			//老表的字段数
			j  =  TableColTitleTempupdate.GetSize();
			
			for(i = 0;i < j ;i ++)
			{
				
				for(int l = 0;l < k ;l ++)
				{
					
					//如果相等的话
					if(TableColTitle[l] == TableColTitleTempupdate[i])
					{
						
						//保存相同的字段名
						EqualColTitle.Add(TableColTitle[l]);
						
						if(TableColTitle[l].Find("、") != -1  || TableColTitle[l].Find("-") != -1)
						{
							m_FieldName = TableColTitle[l];
						}
						else
						{
							m_FieldName = "[" + TableColTitle[l] + "]";
						}
						
						kkkk = m_TableSql.Find(m_FieldName);
						
						
						//如果有此字符
						if(kkkk != -1)
						{
							str  = m_TableSql.Right(m_TableSql.GetLength() - kkkk - m_FieldName.GetLength());
							kkkk = str.Find("NULL");
							
							//如果有此字符
							if(kkkk != -1)
							{
								
								// 修改字段：
								// ALTER TABLE [表名] ALTER COLUMN [字段名] NVARCHAR (50) NULL
								str = str.Left(kkkk + 4);
								//WriteToLog("字段名:" + TableColTitle[l]);
								m_FieldName.Format("ALTER TABLE TEMPUPDAE ALTER COLUMN %s %s",TableColTitle[l],str);
								
								//WriteToLog(m_FieldName);
								//建立新的表
								CDataBaseInstance::ExecuteDataBaseSQL(m_FieldName);
								
							}
							
						}
						
					}
					
				}
				
			}
			
	   }
	
	   //找相同的字段
	   if(EqualColTitle.GetSize() > 0)
	   {
		   
		   str = "";
		   k   = EqualColTitle.GetSize();
		   
		   for(i = 0; i < k;i ++)
		   {
			   
			   if(i == k -1)
			   {
				   str = str + EqualColTitle[i];
			   }
			   else
			   {
				   str = str + EqualColTitle[i] + ",";
			   }
			   
		   }	
		   
		   //倒入数据内容
		   m_Sqlstr.Format("INSERT %s(%s) SELECT DISTINCT %s FROM TEMPUPDAE",m_TableName,str,str);
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
	   }
	   
	   //要检对升级前后的数据
	   if(!m_CheckRecords)
	   {  
		   //删除临时表
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   return TRUE;
	   }

	   //之前的记录数
	   m_AfterRecords = CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL");
		
	   //如果两种记录数相等的话
	   if(m_BeforeRecords == m_AfterRecords)
	   { 
		   //删除临时表
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   //成功修改
		   return  TRUE;
	   }
	   else
	   {
		   //不成功的话则还原成原来的数据库
		   if(IsCurveTableExist(m_TableName))
		   {
			   m_Sqlstr.Format("DROP TABLE  %s",m_TableName);
			   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr); 
		   }
		   
		   //还原数据库
		   m_Sqlstr.Format("SELECT *  INTO %s FROM TEMPUPDAE",m_TableName);
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
		   //删除临时表
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
		   //修改失败
		   return FALSE;
	   }

	}
}

void CIFRMView::OnUpdateListselect(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
	
}

//生成各种参数统计表
void CIFRMView::ComingIntoBeing(CString SqlStr,CString m_begin, CString m_End, BOOL m_yg, BOOL m_wg, BOOL m_jz, BOOL m_fz, BOOL m_gz, BOOL m_pz,  BOOL m_dy, BOOL m_dl)
{
	CString           Str;
	status("正在生成各种数据统计表，请稍侯...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
	
	if(IsCurveTableExist("TB_TOTAL"))
	{
		//删除原来的库表
		Str.Format("DROP TABLE TB_TOTAL");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	Str = "CREATE TABLE [dbo].[TB_TOTAL] (\
											[变台名称] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
											[用户编号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
											[用户姓名] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
											[原用户编号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
											[模块号]   [bigint] NULL ,\
											[倍率]     [int] NULL ,\
											[用电名称] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
											[上次有功] [float] NULL ,\
											[本次有功] [float] NULL ,\
											[有功差值] [float] NULL ,\
											[上次无功] [float] NULL ,\
											[本次无功] [float] NULL ,\
											[无功差值] [float] NULL ,\
											[上次峰值] [float] NULL ,\
											[本次峰值] [float] NULL ,\
											[峰值差]   [float] NULL ,\
											[上次谷值] [float] NULL ,\
											[本次谷值] [float] NULL ,\
											[谷差值]   [float] NULL ,\
											[上次平值] [float] NULL ,\
											[本次平值] [float] NULL ,\
											[平值差]   [float] NULL ,\
											[本次尖值] [float] NULL ,\
											[上次尖值] [float] NULL ,\
											[尖值差]   [float] NULL ,\
											[A相电压]  [float] NULL ,\
											[B相电压]  [float] NULL ,\
											[C相电压]  [float] NULL ,\
											[A相电流]  [float] NULL ,\
											[B相电流]  [float] NULL ,\
											[C相电流]  [float] NULL \
											) ON [PRIMARY]";
	
	//建立数据表
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	SetProgressCtrlSetIt();
	

	//此次读表，运行SQL语句用电类别
	Str.Format("INSERT TB_TOTAL(变台名称,用户编号,用户姓名,原用户编号,\
								模块号,倍率,用电名称,\
							   上次有功,本次有功,有功差值,\
							   上次无功,本次无功,无功差值,\
							   上次峰值,本次峰值, 峰值差,\
							   上次谷值,本次谷值,谷差值,\
							   上次平值,本次平值,平值差,\
							   本次尖值,上次尖值,尖值差,\
							   A相电压,B相电压,C相电压,\
							   A相电流,B相电流,C相电流)\
		               SELECT  RTRIM(LTRIM(a.USER_TRANSFORMERNO)),RTRIM(LTRIM(a.USER_NO)),RTRIM(LTRIM(a.USER_NAME)),RTRIM(LTRIM(a.USER_OLDNO)),a.USER_MODULENO,a.USER_MULTIPLE,f.ELECTRICITY_KIND,\
					           d.GARRISON_WORKDEGREE,e.GARRISON_WORKDEGREE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2),\
							   d.GARRISON_LOSEDEGREE,e.GARRISON_LOSEDEGREE,ROUND((e.GARRISON_LOSEDEGREE-d.GARRISON_LOSEDEGREE)*a.USER_MULTIPLE,2),\
							   d.GARRISON_FDL       ,e.GARRISON_FDL       ,ROUND((e.GARRISON_FDL       -d.GARRISON_FDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_GDL       ,e.GARRISON_GDL       ,ROUND((e.GARRISON_GDL       -d.GARRISON_GDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_PDL       ,e.GARRISON_PDL       ,ROUND((e.GARRISON_PDL       -d.GARRISON_PDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_JFDL      ,e.GARRISON_JFDL      ,ROUND((e.GARRISON_JFDL      -d.GARRISON_JFDL)*a.USER_MULTIPLE,2),\
                               e.GARRISON_AVOLTAGE  ,e.GARRISON_BVOLTAGE  ,e.GARRISON_CVOLTAGE,\
                               e.GARRISON_ACURRENT  ,e.GARRISON_BCURRENT  ,e.GARRISON_CCURRENT\
							   FROM TB_USER a ,TB_GARRISONBAK d,TB_GARRISONBAK e,TB_ELECTRICITY f WHERE (%s) AND f.ELECTRICITY_NO=a.USER_ELECTRICITYKIND AND d.GARRISON_MODULENO=a.USER_MODULENO AND e.GARRISON_MODULENO=a.USER_MODULENO  AND d.GARRISON_HALTTIME='%s' AND e.GARRISON_HALTTIME='%s'",SqlStr,m_begin,m_End);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

	//WriteToLog(Str);
    SetProgressCtrlSetIt();
	
	//有功
	if(!m_yg)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 上次有功,本次有功,有功差值";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//无功
	if(!m_wg)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 上次无功,本次无功,无功差值";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//峰
	if(!m_fz)
	{	
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 上次峰值,本次峰值,峰值差";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//谷
	if(!m_gz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 上次谷值,本次谷值,谷差值";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//平
	if(!m_pz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 上次平值,本次平值,平值差";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//尖
	if(!m_jz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN 本次尖值,上次尖值,尖值差";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//电压
	if(!m_dy)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN A相电压,B相电压,C相电压";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//电流
	if(!m_dl)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN A相电流,B相电流,C相电流";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  
}


//用电量报警
void CIFRMView::ElectricityWarning(CString SqlStr,CString m_begin, CString m_End)
{
	CString        Str,strValue;
	status("正在生成用电报警统计表，请稍侯...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
    
	m_begin.TrimLeft();
    m_End.TrimRight();

	int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
    CTimeSpan                     ts; 
	long       m_TotalSeconds  =   0;
    double     m_kx            =   0;//月份数

	//时间处理
	strValue  = m_begin;
	int k     = strValue.Find('-');
	//年
	m_years   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
    strValue.TrimLeft();
    strValue.TrimRight();

	//月
	k         = strValue.Find('-');
	m_months  = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
    strValue.TrimLeft();
    strValue.TrimRight();

	//日
	k         = strValue.Find(' ');
	m_days    = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//时
	k         = strValue.Find(':');
	m_hours   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//分
	k = strValue.Find(':');
	m_minutes = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//秒
	m_seconds = atoi(strValue);
    
	CTime m_begintime(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);//上次时间
   
	strValue  = m_End;
	k     = strValue.Find('-');
	//年
	m_years   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//月
	k         = strValue.Find('-');
	m_months  = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//日
	k         = strValue.Find(' ');
	m_days    = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//时
	k         = strValue.Find(':');
	m_hours   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//分
	k = strValue.Find(':');
	m_minutes = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//秒
	m_seconds = atoi(strValue);

	CTime m_endtime(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);//本次时间
    
	//时间差
	ts              =  m_endtime - m_begintime;
	m_TotalSeconds  =  ts.GetTotalSeconds();//时间差(秒)

	//换算月数
	m_kx            =  m_TotalSeconds*1.0000/(24*3600*30);
 
	if(m_kx <= 0)
	{
        return;
	}

	//表处理
	if(IsCurveTableExist("TB_WARN"))
	{
		//删除原来的库表
		Str.Format("DROP TABLE TB_WARN");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	Str = "CREATE TABLE [dbo].[TB_WARN] (\
			[变电站名称] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[线路名称] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[变台名称] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[模块号] [bigint] NULL ,\
			[用户编号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[原用户号] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[用户名称] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[用户地址] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[上次用电] [float] NULL ,\
			[本次用电] [float] NULL ,\
			[用电差] [float] NULL ,\
			[月报警下限] [int] NULL ,\
			[月报警上限] [int] NULL ,\
			[报警原因] [char] (16) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
		
	//建立数据表
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	SetProgressCtrlSetIt();
	
	//此次读表，运行SQL语句
	Str.Format("INSERT TB_WARN(变电站名称,线路名称,变台名称,模块号,用户编号,原用户号,用户名称,用户地址,上次用电,本次用电,用电差,月报警下限,月报警上限)\
		        SELECT a.USER_STATIONNAME,a.USER_LINENAME,a.USER_TRANSFORMERNO,\
					   a.USER_MODULENO,a.USER_NO,a.USER_OLDNO,a.USER_NAME,a.USER_ADDRESS,b.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE,a.USER_DOWNVALUE,a.USER_UPVALUE\
					   FROM TB_USER a ,TB_GARRISONBAK b,TB_GARRISONBAK c WHERE (%s) AND b.GARRISON_MODULENO=a.USER_MODULENO AND c.GARRISON_MODULENO=a.USER_MODULENO  AND b.GARRISON_HALTTIME='%s' AND c.GARRISON_HALTTIME='%s' AND a.USER_DOWNVALUE>=0 AND a.USER_UPVALUE>=0 AND ((c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)>(a.USER_UPVALUE*%f) OR (c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<(a.USER_DOWNVALUE*%f))",SqlStr,m_begin,m_End,m_kx,m_kx);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	
	SetProgressCtrlSetIt();
	Str.Format("UPDATE  TB_WARN SET 报警原因 = '读数大于设定上限' WHERE  (本次用电-上次用电)>(月报警上限*%f)",m_kx);
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	Str.Format("UPDATE  TB_WARN SET 报警原因 = '读表小于设定下限' WHERE  (本次用电-上次用电)<(月报警下限*%f)",m_kx);
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	//如果上限和下限都是空
	Str.Format("INSERT TB_WARN(变电站名称,线路名称,变台名称,模块号,用户编号,原用户号,用户名称,用户地址,上次用电,本次用电,用电差,月报警下限,月报警上限)\
		        SELECT a.USER_STATIONNAME,a.USER_LINENAME,a.USER_TRANSFORMERNO,\
					   a.USER_MODULENO,a.USER_NO,a.USER_OLDNO,a.USER_NAME,a.USER_ADDRESS,b.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE,a.USER_DOWNVALUE,a.USER_UPVALUE\
					   FROM TB_USER a ,TB_GARRISONBAK b,TB_GARRISONBAK c WHERE (%s) AND b.GARRISON_MODULENO=a.USER_MODULENO AND c.GARRISON_MODULENO=a.USER_MODULENO  AND b.GARRISON_HALTTIME='%s' AND c.GARRISON_HALTTIME='%s' AND a.USER_DOWNVALUE IS NULL AND a.USER_UPVALUE IS NULL AND ((c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<0.001 OR (c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<0.001)",SqlStr,m_begin,m_End);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

	Str = "UPDATE TB_WARN SET 报警原因 = '模块电表没有走数' WHERE  (本次用电-上次用电)<0.001";
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  
}


//检查当前的时间来确定定时读表的各种状态
//参数0 - 参数30  为居民表的参数读表日期
//参数31- 参数61  为大用户的参数读表日期 
//参数62- 参数92  为大用户的参数读表日期
//参数93- 参数102 为读表内容
//参数103         为读表时刻点
//检查定时的状态
//返回值 0-----没有  1----发驻留的时间  2-----读表的时间  3-无功补偿操作
short CIFRMView::CheckCurrentTime()
{   
//	CString                        m_SqlStr,str;
//	CTime m_CurrentTimes = CTime::GetCurrentTime();	 	
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   开始检测状态0",m_CurrentTimes.GetYear(),m_CurrentTimes.GetMonth(),m_CurrentTimes.GetDay(),m_CurrentTimes.GetHour(),m_CurrentTimes.GetMinute(),m_CurrentTimes.GetSecond());
//	WriteToLog(str);

	if(!m_IsAutoSending)
	{
		return 0;
	}	
	
/*	if(ReadMeterThread != NULL)
	{
		//挂起
		if(ReadMeterThread->SuspendThread() != 0xFFFFFFFF)
		{
			m_Pause  = TRUE;
		}
		else
		{
			m_Pause  = FALSE;
		}
		
	}
*/
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   开始检测状态1",m_CurrentTimes.GetYear(),m_CurrentTimes.GetMonth(),m_CurrentTimes.GetDay(),m_CurrentTimes.GetHour(),m_CurrentTimes.GetMinute(),m_CurrentTimes.GetSecond());
//	WriteToLog(str);
	
	//检测各种时间
	CTime                         m_CurrentTime;//定义时间变量
    CTimeSpan                                ts;//时间间隙
	CByteArray          m_TimeArray,m_TempArray;//读表日期数组
	int                        m_years,m_months;
	BYTE m_LastMonths,m_ThisMonths,m_NextMonths;
	int i;
	for( i = 0; i < 31; i ++)
	{
		
		//提出读表日期
		if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
		{

			m_TimeArray.Add(i+1);

		}

	}
	
	//如果没有读表日期则退出
    if(m_TimeArray.GetSize() <= 0)
	{

		if(ReadMeterThread != NULL  && m_Pause)
		{
			//启动线程
			ReadMeterThread->ResumeThread();
			m_Pause    =              FALSE;
		}

		return  0;
	}
	
	//提取当前时间
	m_CurrentTime  = CTime::GetCurrentTime(); 

	//得到上月最大天数
	m_LastMonths = GetMaxDays(0);

	//得到本月最大天数
	m_ThisMonths = GetMaxDays(1);

	//得到下月最大天数
	m_NextMonths = GetMaxDays(2);
	
  //m_SqlStr.Format("上月最大天数:%d,本月最大天数:%d,下月最大天数:%d",m_LastMonths,m_ThisMonths,m_NextMonths);
  //WriteToLog(m_SqlStr);
 
	//  如 1  4  28则组成 上月28 本月1  本月4  本月28 下月1号数组算时间间隔 
	//加上月最后一天日期
	if(m_TimeArray[m_TimeArray.GetSize()-1] <= m_LastMonths)
	{
	    m_TempArray.Add(m_TimeArray[m_TimeArray.GetSize()-1]);
	}
	else
	{
		m_TempArray.Add(m_LastMonths);
	}

	//本月的日期
	for(i = 0; i < m_TimeArray.GetSize(); i ++)
	{	
		
		//如果本月只有28或29天
		if(m_TimeArray[i] < m_ThisMonths)
		{
			m_TempArray.Add(m_TimeArray[i]);
		}
		else
		{
			m_TempArray.Add(m_ThisMonths);
			break;
		}
		
	}
	
	//加下月的最前一天的日期
	if(m_TimeArray[0] <= m_NextMonths)
	{
	   m_TempArray.Add(m_TimeArray[0]);
	}
	else
	{
		m_TempArray.Add(m_NextMonths);
	}

	//设置驻留读表标志
	SetGarrionLabel();
	
	//检查是否是应该发驻留
	for(i = 0 ; i < m_TempArray.GetSize() - 1; i ++)
	{	
		
		//此时的年和月份
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//上个月的时间
		if(i == 0)
		{	
			
			if(m_months > 1)
			{
				//月份加1
				m_months = m_months - 1;
			}
			else
			{
				//如果为1 月份，跨年
				m_years  = m_years - 1;
				m_months =          12;
			}

		}
		
		//起始时间
		CTime    m_Time1(m_years,m_months,m_TempArray[i],m_parameter[104],0,0);
		
		//此时的年和月份
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//下一个月的日期 
		if(i + 1 == m_TempArray.GetSize() - 1)
		{
           	
			if(m_months < 12)
			{
				//月份加1
				m_months = m_months + 1;
			}
			else
			{
				//如果为12 月份，跨年
				m_years  = m_years + 1;
				m_months =           1;
			}

		}
		
		//结束时间 
		CTime  m_Time2(m_years,m_months,m_TempArray[i+1],m_parameter[104],0,0);
		
		//中间时间	
		ts = m_Time2  -     m_Time1;
		ts = ts.GetTotalSeconds()/3*2;
		
		//中间时间
		CTime  m_MiddleTime = m_Time1 + ts;		
			
		//驻留m_Time2的时间范围[中间时间-----结束时间],驻留时间优先
		if((m_CurrentTime >= m_MiddleTime  && m_CurrentTime <= m_Time2))
		{
			//时间2和时间1的时间差
			ts  = m_Time2  - m_CurrentTime;
			
			if(ts.GetTotalSeconds() <= 86400 &&  ts.GetTotalSeconds() > 0)
			{	
				
				//半点或整点
				if(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0)
				{
					//发驻留时间到了,取得驻留时间
					m_AutoReadTime = m_Time2;
					
					if(ReadMeterThread != NULL  && m_Pause)
					{	
						//发驻留时间到了,如果原来在读表就退出读表
						m_StartRead       =      FALSE;
						//启动线程
						ReadMeterThread->ResumeThread();
						m_Pause  =                FALSE;
						
					}
					
					return   1;
				}
				else
				{
					switch(m_WgLess)
					{
						
					case 0:
						{
							//10分钟
							//无功补偿表操作
							return     3;
							break;
						}
					case 1:
						{
							//20分钟
							if(((m_CurrentTime.GetMinute()/10)%2) == 0)
							{
								//无功补偿表操作
								return     3;
							}
							
							break;
						}
				
					}

				}
				
			}
		
		}	
		
	}
 
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//启动
		ReadMeterThread->ResumeThread();
		m_Pause      =            FALSE;
	}
    
	if(ReadMeterThread == NULL && !(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0))
	{
		//无功补偿表操作
		switch(m_WgLess)
		{
			
		case 0:
			{
				//10分钟
				//无功补偿表操作
				return     3;
				break;
			}
		case 1:
			{
				//20分钟
				if(((m_CurrentTime.GetMinute()/10)%2) == 0)
				{
					//无功补偿表操作
					return     3;
				}
				
				break;
			}
		}
	
	}
	
	//半小时一读或整点
	return 2;
}



//检查当前的时间来确定定时读表的各种状态
//返回值 0-----没有  1----发驻留的时间  2-----读表的时间
short CIFRMView::ByDateCheckCurrentTime()
{
	
	if(!m_IsAutoSending)
	{
		return 0;
	}	
	
/*	if(ReadMeterThread != NULL)
	{
		//挂起成功
		if(ReadMeterThread->SuspendThread() != 0xffffffff)
		{
			m_Pause  = TRUE;
		}
		else
		{
			m_Pause = FALSE;
		}

	}
*/
	//检测各种时间
	CTime                         m_CurrentTime;//定义时间变量
    CTimeSpan                                ts;//时间间隙
	CByteArray          m_TimeArray,m_TempArray;//读表日期数组
    CString                        m_SqlStr,str;
	int                        m_years,m_months;
	BYTE m_LastMonths,m_ThisMonths,m_NextMonths;
	int i;
	for( i = 0; i < 31; i ++)
	{

		//提出读表日期
		if(m_DateReadParameter[2*i] > 0)
		{

			m_TimeArray.Add(i+1);

		}

	}
	
	//如果没有读表日期则退出
    if(m_TimeArray.GetSize() <= 0)
	{

		if(ReadMeterThread != NULL && m_Pause)
		{
			//启动线程
			ReadMeterThread->ResumeThread();
			m_Pause    =              FALSE;
		}

		return  0;
	}
	
	//提取当前时间
	m_CurrentTime  = CTime::GetCurrentTime(); 

	//得到上月最大天数
	m_LastMonths = GetMaxDays(0);

	//得到本月最大天数
	m_ThisMonths = GetMaxDays(1);

	//得到下月最大天数
	m_NextMonths = GetMaxDays(2);
	
  //m_SqlStr.Format("上月最大天数:%d,本月最大天数:%d,下月最大天数:%d",m_LastMonths,m_ThisMonths,m_NextMonths);
  //WriteToLog(m_SqlStr);
 
	//  如 1  4  28则组成 上月28 本月1  本月4  本月28 下月1号数组算时间间隔 
	//加上月最后一天日期
	if(m_TimeArray[m_TimeArray.GetSize()-1] <= m_LastMonths)
	{
	    m_TempArray.Add(m_TimeArray[m_TimeArray.GetSize()-1]);
	}
	else
	{
		m_TempArray.Add(m_LastMonths);
	}

	//本月的日期
	for(i = 0; i < m_TimeArray.GetSize(); i ++)
	{	
		
		//如果本月只有28或29天
		if(m_TimeArray[i] < m_ThisMonths)
		{
			m_TempArray.Add(m_TimeArray[i]);
		}
		else
		{
			m_TempArray.Add(m_ThisMonths);
			break;
		}
		
	}
	
	//加下月的最前一天的日期
	if(m_TimeArray[0] <= m_NextMonths)
	{
	   m_TempArray.Add(m_TimeArray[0]);
	}
	else
	{
		m_TempArray.Add(m_NextMonths);
	}

	//检查是否是应该发驻留
	for(i = 0 ; i < m_TempArray.GetSize() - 1; i ++)
	{	
		
		//此时的年和月份
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//上个月的时间
		if(i == 0)
		{	
			
			if(m_months > 1)
			{
				//月份加1
				m_months = m_months - 1;
			}
			else
			{
				//如果为1 月份，跨年
				m_years  = m_years - 1;
				m_months =          12;
			}

		}
		
		//起始时间
		CTime    m_Time1(m_years,m_months,m_TempArray[i],m_DateReadParameter[2*(m_TempArray[i]-1) + 1],0,0);
		
		//此时的年和月份
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//下一个月的日期 
		if(i + 1 == m_TempArray.GetSize() - 1)
		{
           	
			if(m_months < 12)
			{
				//月份加1
				m_months = m_months + 1;
			}
			else
			{
				//如果为12 月份，跨年
				m_years  = m_years + 1;
				m_months =           1;
			}

		}
		
		//结束时间 
		CTime  m_Time2(m_years,m_months,m_TempArray[i+1],m_DateReadParameter[2*(m_TempArray[i+1]-1) + 1],0,0);
	
		//中间时间	
		ts = m_Time2  -     m_Time1;
		ts = ts.GetTotalSeconds()/3*2;
		
		//中间时间
		CTime  m_MiddleTime = m_Time1 + ts;		
			
		//驻留m_Time2的时间范围[中间时间-----结束时间],驻留时间优先
		if((m_CurrentTime >= m_MiddleTime  && m_CurrentTime <= m_Time2))
		{
			//时间2和时间1的时间差
			ts  = m_Time2  - m_CurrentTime;
			
			if(ts.GetTotalSeconds() <= 86400 &&  ts.GetTotalSeconds() > 0)
			{	

				//半点或整点
				if(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0)
				{
					//发驻留时间到了,取得驻留时间
					m_AutoReadTime = m_Time2;
					
					if(ReadMeterThread != NULL  && m_Pause)
					{	
						//发驻留时间到了,如果原来在读表就退出读表
						m_StartRead       =      FALSE;
						//启动线程
						ReadMeterThread->ResumeThread();
						m_Pause           =      FALSE;
						
					}	
					
					//释放CPU时间
					SurrenderWindowMessage();
					Sleep(2000);
					//释放CPU时间
					SurrenderWindowMessage();
					
					//如果线程退出了
					if(ReadMeterThread == NULL)
					{
						//改写定时读表标志
						ByDateSetGarrisonRange(m_TempArray[i+1]);
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测值为1,发驻留(%4d-%02d-%02d %02d:%02d:%02d)",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
					WriteToLog(str);
					
					return   1;
				}
				else
				{
					switch(m_WgLess)
					{
						
					case 0:
						{
							//10分钟
							//无功补偿表操作
							return     3;
							break;
						}
					case 1:
						{
							//20分钟
							if(((m_CurrentTime.GetMinute()/10)%2) == 0)
							{
								//无功补偿表操作
								return     3;
							}
							
							break;
						}
				
					}

				}

			}
		
		}	
		
	}
 
	//如果线程是暂停的
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//启动
		ReadMeterThread->ResumeThread();
		m_Pause      =            FALSE;
	}
   
	if(ReadMeterThread == NULL && !(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0))
	{
		//无功补偿表操作
		switch(m_WgLess)
		{
			
		case 0:
			{
				//10分钟
				//无功补偿表操作
				return     3;
				break;
			}
		case 1:
			{
				//20分钟
				if(((m_CurrentTime.GetMinute()/10)%2) == 0)
				{
					//无功补偿表操作
					return     3;
				}
				
				break;
			}
		}
		
	}

	str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测值为2,读驻留",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	WriteToLog(str);

	return 2;
}


//写入居民表、大用户表、变台表等表的参数
void CIFRMView::WriteToAllAmeterParameter()
{
	CString m_SqlStr,str;

	//删除原来的数据
	m_SqlStr = "DELETE FROM TB_Auto";
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);

	//插入参数
	m_SqlStr = "INSERT INTO TB_Auto(";
	int i;
	for( i = 1; i <= 110; i++)
	{
		if(i < 110)
		{
		   str.Format("Auto_Parameter%d,",i);
		}
		else
		{		   
			str.Format("Auto_Parameter%d",i);
		}
		m_SqlStr = m_SqlStr + str;
	}

	m_SqlStr = m_SqlStr + ")  VALUES("; 
	
	for( i = 0; i < 109; i++)
	{
		str.Format("%d,",m_parameter[i]);
		m_SqlStr = m_SqlStr + str;
	}
	
	str.Format("%d",m_parameter[109]);
	m_SqlStr = m_SqlStr + str + ")";
  
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
}

//写入按日期设置参数的驻留
void CIFRMView::WriteToParameterByDate()
{
	CString m_SqlStr,str;

	//删除原来的数据
	m_SqlStr = "DELETE FROM TB_DateAuto";
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);

	//插入参数
	m_SqlStr = "INSERT INTO TB_DateAuto(";
	int i;
	for( i = 1; i <= 67; i++)
	{
		if(i < 67)
		{
		   str.Format("Auto_Parameter%d,",i);
		}
		else
		{		   
			str.Format("Auto_Parameter%d",i);
		}
		m_SqlStr = m_SqlStr + str;
	}

	m_SqlStr = m_SqlStr + ")  VALUES("; 
	
	for( i = 0; i < 66; i++)
	{
		str.Format("%d,",m_DateReadParameter[i]);
		m_SqlStr = m_SqlStr + str;
	}
	
	str.Format("%d",m_DateReadParameter[66]);
	m_SqlStr = m_SqlStr + str + ")";
  
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
}

//解晰参数  m_ReadRanage  FALSE 只分析读表日期  TRUE 还分析读表内容
CString CIFRMView::DecodeParameter(BOOL m_ReadRanage)
{
	
	CString    Str,m_GetDataStr,m_ReadData,m_timeevery;
	CString                    m_String[3];
	
	for(int j = 0; j < 3; j ++)
	{
		
		Str    =  m_GetDataStr = m_ReadData = "";
		
		for(int i = 0; i < 31; i ++)
		{
			
			if(m_parameter[j*31 + i] > 0)
			{
				Str.Format("%d",i + 1);
				m_GetDataStr = m_GetDataStr + Str + "   ";
			}
			
		}	
		
		//读表日期
		m_GetDataStr.TrimLeft();
		m_GetDataStr.TrimRight();
		
		switch(j)
		{
		case 0:
			{
                if(m_GetDataStr.IsEmpty())
				{
					m_String[0] = "【居 民 表】 \r\n  读表日期：<无> \r\n";
					
				}
				else
				{
					m_String[0].Format("【居 民 表】 \r\n  读表日期：[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		case 1:
			{	
				if(m_GetDataStr.IsEmpty())
				{
					m_String[1] = "【大用户表】 \r\n  读表日期：<无> \r\n";
					
				}
				else
				{
					m_String[1].Format("【大用户表】 \r\n  读表日期：[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		case 2:
			{	
				if(m_GetDataStr.IsEmpty())
				{
					m_String[2] = "【台变等表】 \r\n  读表日期：<无> \r\n";
				}
				else
				{
					m_String[2].Format("【台变等表】 \r\n  读表日期：[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		}
		
	}

	if(!m_ReadRanage)
	{
	   return m_String[0] + m_String[1] + m_String[2];
	}
    
	//读表内容
	Str   =  "【读表内容】\r\n";
	
	//有功电度
	if(m_parameter[93] > 0)
	{

		if(m_parameter[93] > 0  && m_parameter[94] > 0)
		{
			Str = Str +  "  当前站有功、总有功电度 ";
		}
		else
		{
			Str = Str +  "  有功电度 ";
		}

	}	
	
	//无功电度
	if(m_parameter[95] > 0)
	{

		if(m_parameter[95] > 0  && m_parameter[96] > 0)
		{
			Str = Str + "  当前站无功、总无功电度";	
		}
		else
		{
			Str = Str +  "  无功电度 ";	
		}

	}	
		
	//4－A相电流 5－B相电流 6－C相电流
	if(m_parameter[97] > 0)
	{
        Str = Str + "  A相、B相、C相电流值  ";
	}

	//7－A相电压 8－B相电压 9－C相电压
	if(m_parameter[98] > 0)
	{
        Str = Str + "  A相、B相、C相电压值  ";
	}

	//尖峰电量
	if(m_parameter[99] > 0)
	{
        Str = Str + "  尖峰电量  ";
	}
	
	//峰电量
	if(m_parameter[100] > 0)
	{
        Str = Str + "  峰电量  ";
	}
	
    //平电量
	if(m_parameter[101] > 0)
	{
        Str = Str + "  平电量  ";
	}
	
	//谷电量
	if(m_parameter[102] > 0)
	{
        Str = Str + "  谷电量  ";
	}
	
	//功率因数
	if(m_parameter[103] > 0)
	{
        Str = Str + "  功率因数  ";
	}

	//驻留时刻
    m_GetDataStr.Format("【驻留时刻】\r\n  %d时",m_parameter[104]);

	//扫描间隔,扫描次数
	if(m_parameter[109] > 0)
	{
		m_timeevery.Format("【读表次数】\r\n  先间隔半小时读表%d次,后间隔8小时读%d次\r\n【自动运行】\r\n  软件启动时自动启动按表计设置驻留参数",m_parameter[106],m_parameter[108]);
	}
	else
	{
		m_timeevery.Format("【读表次数】\r\n  先间隔半小时读表%d次,后间隔8小时读%d次\r\n【自动运行】\r\n  软件启动时不自动启动按表计设置驻留参数",m_parameter[106],m_parameter[108]);
	}
   
	return  m_String[0] + m_String[1] + m_String[2] + Str + "\r\n" + m_GetDataStr+ "\r\n" + m_timeevery;

}


//得到一个月的最大天数据  m_select= 0 上月 1 本月 2 下月
BYTE CIFRMView::GetMaxDays(BYTE m_select)
{
	CTime                 m_CurrentTime;//定义时间变量
    CTimeSpan                        ts;//时间间隙
	short              m_years,m_months;
	BYTE               m_days      =  0;
	
	//提取当前时间
	m_CurrentTime  = CTime::GetCurrentTime(); 

	m_years   =   m_CurrentTime.GetYear();
	m_months  =   m_CurrentTime.GetMonth();
	
	switch(m_select)
	{
	case 0:
		{
			//上月
			if(m_months > 1)
			{
				//月份加1
				m_months = m_months - 1;
			}
			else
			{
				//如果为1 月份，跨年
				m_years  = m_years - 1;
				m_months =          12;
			}
			
			break;
		}
	case 1:
		{
			//本月
			break;
		}
	case 2:
		{
			//下月
			if(m_months < 12)
			{
				//月份加1
				m_months = m_months + 1;
			}
			else
			{
				//如果为12 月份，跨年
				m_years  = m_years + 1;
				m_months =           1;
			}

			break;
		}
	}

	CTime    m_start(m_years,m_months,1,0,0,0);
  
	for(int i = 28; i <= 31; i ++)
	{
         ts             = i*86400;
		 CTime    m_end = m_start + ts;

		 if(m_end.GetMonth() != m_months)
		 {
			 //月的最大天数
			 m_days = i;
			 break;
		 }
	}

	return m_days;
}

//软件一启动就自动驻留读表时间
void CIFRMView::AutoGarrisonTime()
{
	
    CString               str;
	CDatabase              db;	
	int i;
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset   rs(&db );
		str = "SELECT * FROM TB_Auto";
		rs.Open(CRecordset::dynaset,str);
		
		if(rs.IsEOF())
		{
			//关闭数据库
		    rs.Close( );
		    db.Close( );
			return;
		}
		
		//读自动读表信息
		for(int i = 0; i < 110; i++)
		{
			rs.GetFieldValue((short)i,str);
			m_parameter[i] = atoi(str);
		}

		//关闭数据库
		rs.Close( );
		db.Close( );

		if(m_parameter[109] <= 0)
		{

	        for( i = 0; i < 110; i++)
			{
				m_parameter[i] = 0;
			}

			return;
		}
		
		//15种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数
		//定时发驻留,定时读表标志
		for( i = 0; i < 15; i++)
		{
			m_TimeSetLabel[i]  = FALSE;  
		}
		
		//有功电度
		if(m_parameter[93] > 0)
		{
			
			if(m_parameter[93] > 0  && m_parameter[94] > 0)
			{
				m_TimeSetLabel[0] = TRUE;
				m_TimeSetLabel[1] = TRUE;    //0－有功电度-单边累加值
			}
			else
			{
				m_TimeSetLabel[0] = TRUE;
			}
		
		}	
		
		//无功电度
		if(m_parameter[95] > 0)
		{
			
			if(m_parameter[95] > 0  && m_parameter[96] > 0)
			{
				m_TimeSetLabel[2] = TRUE;
				m_TimeSetLabel[3] = TRUE;    //0－无功电度-单边累加值
			}
			else
			{
				m_TimeSetLabel[2] = TRUE;   
			}

		}	
		
		//4－A相电流 5－B相电流 6－C相电流
		if(m_parameter[97] > 0)
		{
			m_TimeSetLabel[4] = TRUE;
			m_TimeSetLabel[5] = TRUE;
			m_TimeSetLabel[6] = TRUE;
		}
		
		//7－A相电压 8－B相电压 9－C相电压
		if(m_parameter[98] > 0)
		{
			m_TimeSetLabel[7] = TRUE;
			m_TimeSetLabel[8] = TRUE;
			m_TimeSetLabel[9] = TRUE;
		}
		
		//尖峰电量
		if(m_parameter[99] > 0)
		{
			m_TimeSetLabel[10] = TRUE;
		}
		
		//峰电量
		if(m_parameter[100] > 0)
		{
			m_TimeSetLabel[11] = TRUE;
		}
		
		//平电量
		if(m_parameter[101] > 0)
		{
			m_TimeSetLabel[12] = TRUE;
		}
		
		//谷电量
		if(m_parameter[102] > 0)
		{
			m_TimeSetLabel[13] = TRUE;
		}
		
		//功率因数	
		if(m_parameter[103] > 0)
		{
			m_TimeSetLabel[14] = TRUE;
		}
	
		//停止执行此操作
		m_StartRead      =  FALSE;
		//时间
		CTime timet = CTime::GetCurrentTime();
		str.Format("【%4d-%02d-%02d %02d:%02d:%02d】设置定时驻留读表:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
		WriteToLog(str);
		
		//取消10分钟检查一次检查
		KillTimer(1);

		ShowDingShiButton(TRUE);//定时按钮置为TRUE
		m_IsAutoSending    =          TRUE;//驻留状态标志
		m_ReadModuleTimes  =             0;//读表次数设为0
		m_SendGarrisonTimes=             0;//发驻留次数
	    m_IfChangeData     =          FALSE;             //修改接收数据标志
		m_parameter[105]   =             30;//间隔强制设置成30分钟
		m_zhuliukinds      =              0;//驻留种类 0 按表计种类 1 按日期设置

		StatusStr.Format("【定%d时驻留,先间隔半小时读%d次,后间隔八小时读%d次】",m_parameter[104],m_parameter[106],m_parameter[108]);
		status(StatusStr);
	
        //初始化电流
        InitializeCurrent();

		//为22协议加的，半点或整点才可用,10分钟一检测
		m_SettimerValues = ((10 - (timet.GetMinute()%10))*60 - timet.GetSecond())*1000;
		SetTimer(1,m_SettimerValues,NULL);//设置定时器,10分钟检查一次
	
	}

}


//设置驻留读表标志
void CIFRMView::SetGarrionLabel()
{
	//定时发驻留,15种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数
	for(int i = 0; i < 15; i++)
	{
		m_TimeSetLabel[i]  = FALSE;  
	}
	
	//有功电度
	if(m_parameter[93] > 0)
	{

		if(m_parameter[93] > 0  && m_parameter[94] > 0)
		{
			m_TimeSetLabel[0] = TRUE;
			m_TimeSetLabel[1] = TRUE;    //0－有功电度-单边累加值
		}
		else
		{
			m_TimeSetLabel[0] = TRUE;
		}

	}	
	
	//无功电度
	if(m_parameter[95] > 0)
	{
		
		if(m_parameter[95] > 0  && m_parameter[96] > 0)
		{
			m_TimeSetLabel[2] = TRUE;
			m_TimeSetLabel[3] = TRUE;    //0－无功电度-单边累加值
		}
		else
		{
			m_TimeSetLabel[2] = TRUE;   
		}
		
	}	
	
	//4－A相电流 5－B相电流 6－C相电流
	if(m_parameter[97] > 0)
	{
		m_TimeSetLabel[4] = TRUE;
		m_TimeSetLabel[5] = TRUE;
		m_TimeSetLabel[6] = TRUE;
	}
	
	//7－A相电压 8－B相电压 9－C相电压
	if(m_parameter[98] > 0)
	{
		m_TimeSetLabel[7] = TRUE;
		m_TimeSetLabel[8] = TRUE;
		m_TimeSetLabel[9] = TRUE;
	}
	
	//尖峰电量
	if(m_parameter[99] > 0)
	{
		m_TimeSetLabel[10] = TRUE;
	}
	
	//峰电量
	if(m_parameter[100] > 0)
	{
		m_TimeSetLabel[11] = TRUE;
	}
	
	//平电量
	if(m_parameter[101] > 0)
	{
		m_TimeSetLabel[12] = TRUE;
	}
	
	//谷电量
	if(m_parameter[102] > 0)
	{
		m_TimeSetLabel[13] = TRUE;
	}

	//功率因数	
	if(m_parameter[103] > 0)
	{
		m_TimeSetLabel[14] = TRUE;
	}

}

//初始化读表范围
void CIFRMView::InitializeGarrionReadRange()
{
	//条件选择, 读的表种类
	CString        str,m_SqlStr;
	m_AutoReadCondtionStr  = "";
	int j;			
	//生成条件，如果有居民表
	for( j = 0; j < 3; j ++)
	{
		
		//如果有读表日期
		if(m_parameter[j * 31 + m_AutoReadTime.GetDay() - 1] > 0)
		{
			//j = 0 居民表  1 大用户表  2 台变等表
			if( j == 2)
			{
				str.Format("USER_AMMETERKIND>=%d",j);
			}
			else
			{
				str.Format("USER_AMMETERKIND=%d",j);
			}
			
			m_AutoReadCondtionStr.TrimRight();
			m_AutoReadCondtionStr.TrimRight();
			
			if(m_AutoReadCondtionStr.IsEmpty())
			{
				m_AutoReadCondtionStr = m_AutoReadCondtionStr + str;
			}
			else
			{
				m_AutoReadCondtionStr = m_AutoReadCondtionStr + " OR " + str;
			}
			
		}
		
	}
	
	//WriteToLog("读表条件:" + m_AutoReadCondtionStr + "\r\n");
	//str.Format("GARRISON_HALTTIME='%4d-%02d-%02d %02d:%02d:%02d'",m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
    //WriteToLog("驻留时间:" + str + "\r\n");
	
	str = "";
	
	//15种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数
	for(j = 0; j < 15; j ++)
	{
		
		if(m_TimeSetLabel[j])
		{
			str = str + "N";
		}
		else
		{
			str = str + "Y";
		}
		
	}
	
	//所有模块定时读表标志全置为Y
	m_SqlStr.Format("UPDATE TB_USER SET USER_TIMELABEL='%s'","YYYYYYYYYYYYYYY");
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
	
	//符合条件的设置标志
	m_SqlStr.Format("UPDATE TB_USER SET USER_TIMELABEL='%s' WHERE %s",str,m_AutoReadCondtionStr);
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
	m_times  = 1;
}


//修改拔号或网络连接状态
void CIFRMView::ModifyDialInternetStatus()
{	
	//给对方提示
	SelectSendString(m_sendkind, "BEGINS;COMMAND:32:【检测30分钟内没有远程机器任何指令，本地版自动断开并开始驻留工作】;ENDS",TRUE,FALSE,TRUE);
	Sleep(300);

	//断开网络连接
	DisConnect(2);
	
	if(!m_IsConnect)
	{
		SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
	}
	
	//挂断拔号
	DisConnect(1);
	
	//拔号连接
	if(!m_Com.GetCDHolding())
	{
		
		//如果设置过自动应答
		if(CDataBaseInstance::GetAllRecordsCount("TB_COMINFORMATION","COMINFORMATION_AUTOREPLY=1") > 0)
		{  
			//自动应答
			AutoAnswer(FALSE);	          
		}
		
	}
	
}

//删除读表或发驻留线程
BOOL CIFRMView::DeleteViewThread()
{
	
	if(ReadMeterThread != NULL)
	{
		MessageBox("请先停止读表，然后再退出！"," ",MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	else
	{
	    m_StartRead  =     FALSE;
		//交出window控制权
	//	SurrenderWindowMessage();
	
		//写上关程序时间
		CString       str;
		CTime timet = CTime::GetCurrentTime();	    
		str.Format("【%4d-%02d-%02d %02d:%02d:%02d】软件退出",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	    WriteToLog(str);
	}

	return TRUE;
	
}


//处理过期数据，驻留表中＊年之前的数据，正式表中的数据
void CIFRMView::DealOverTimeData(int m_Years)
{
	
	CString            m_SqlStr,m_sql,m_filename;
	CTime     m_time   = CTime::GetCurrentTime();
	m_filename.Format("%s%s%4d_%02d_%02d_%02d%s",GetFolder(),"GARRISON_BAK_",m_time.GetYear(),m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),".TXT");
	
    m_SqlStr.Format("GARRISON_HALTTIME < '%4d-%02d-%02d %02d:%02d:%02d'",m_time.GetYear()-m_Years,m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),m_time.GetMinute(),m_time.GetSecond());

    long fields        =  CDataBaseInstance::GetAllRecordsCount("TB_GARRISON",m_SqlStr);
	m_sql              =  "SELECT * FROM TB_GARRISON WHERE " + m_SqlStr;
	
	if(fields  > 0)
	{
		//保存驻留表数据
		WriteDataToTextFile("TB_GARRISON",m_sql,fields,m_filename);
		
		//删除驻留表数据
		m_sql.Format("DELETE FROM TB_GARRISON WHERE %s",m_SqlStr);
		CDataBaseInstance::ExecuteDataBaseSQL(m_sql);
       
		//删除正式表数据
		m_SqlStr.Format("REALTIME_TRANSCRIBETIME < '%4d-%02d-%02d %02d:%02d:%02d'",m_time.GetYear()-m_Years,m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),m_time.GetMinute(),m_time.GetSecond());
	    m_sql.Format("DELETE FROM TB_REALTIME WHERE %s",m_SqlStr);
		CDataBaseInstance::ExecuteDataBaseSQL(m_sql);
	}

}

//kinds  0 设置驻留时间  1 查询驻留时间
void CIFRMView::DealOverTime(BYTE kinds)
{
	//电局版本
	CString       PassStr;

	if(!AppInfo::Instance().m_WhichKind)
	{
		
		if(kinds == 0)
		{
			//设置驻留时间
			PassStr.Format("BEGINS;COMMAND:33:%d;ENDS",m_saveyears);
		}
		else
		{
			//查询驻留时间
			PassStr = "BEGINS;COMMAND:34;ENDS";
		}	
			
		//远程发送调试参数的指令
		SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
	
	}
	else
	{	
		PassStr.Format("所有读表数据保存时间为%d年！",m_saveyears);
		MessageBox(PassStr," ",MB_OK|MB_ICONINFORMATION);
	}

}


void CIFRMView::OnCheckeqaul() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}	

	CString      str;
	str = "删除由于换表等原因引起的跟用户表不相关的模块的正式或驻留\r\n历史数据，这些数据被删除将不能恢复，删除这些记录吗？";

	if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
	
		//驻留数据
		str = "DELETE TB_GARRISON WHERE GARRISON_MODULENO NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER) AND GARRISON_MODULENO NOT IN (SELECT DISTINCT CHANGEAMMETER_MODULENOOLD FROM TB_CHANGEAMMETER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);

		//正式读表数据
		str = "DELETE TB_REALTIME WHERE REALTIME_MODULENO NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);
	
		//接线错误的模块
    	str = "DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE NOT IN (SELECT USER_MODULENO FROM TB_USER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);
		
		//删除无功补偿表
		str.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)");
		CDataBaseInstance::ExecuteDataBaseSQL(str);
      
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		pMainFrm->m_wndMyDialogBar.InitializeCombo();
		
		MessageBox("数据删除结束！"," ",MB_OK|MB_ICONASTERISK);
	}
	
}

//数据检验一致性
void CIFRMView::OnUpdateCheckeqaul(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);	
}

//相设为不定相
void CIFRMView::OnXiangchange() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CString         StrSql,str;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	StrSql.Format("所选用户模块[%d户]相都设为不定相吗？",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()));
	
	if(MessageBox(StrSql," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
	{
		return;
	}	
	
	StrSql.Format("Update TB_USER SET USER_PHASE=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
		
	//远程版发送改变相别的指令
	if(!AppInfo::Instance().m_WhichKind)//TRUE 变电站版本  FALSE电局版
	{
	   str.Format("BEGINS;COMMAND:19:%s;ENDS",StrSql);
	   SelectSendString(m_sendkind,str,TRUE,TRUE,TRUE);
	}

	MessageBox("所选模块相别修改完毕！","  ",MB_OK|MB_ICONASTERISK);
}

void CIFRMView::OnUpdateXiangchange(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//得到选择读表的条件pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
	
}

//检测当前母线出线是否有电流
//BYTE MotherLine 母线编号
//BYTE LineNo     线路编号
//BYTE Phase      相别
//m_SendInfo    TRUE 发送调制指令  FALSE 换线路
CString CIFRMView::CheckCurrentValue(BYTE MotherLine, BYTE LineNo,BOOL m_SendInfo)
{

	double m_ACurrentSum,m_BCurrentSum,m_CCurrentSum;
	double m_ACurrentAvgSum,m_BCurrentAvgSum,m_CCurrentAvgSum;
	m_ACurrentSum    = m_BCurrentSum    = m_CCurrentSum    = 0;
	m_ACurrentAvgSum = m_BCurrentAvgSum = m_CCurrentAvgSum = 0;

	CString                        str;
	str.Format("%10d|%10d|%10d",0,0,0);

	BYTE   ORDER[15];

	if(m_SendInfo)
	{
		//发送调制指令

		//向单片机发指令
		if(!SendOrderToSCM(13107115/*模块号*/,0/*手拉手电站码*/,MotherLine/*母线*/,LineNo/*线号*/, 1/*相选择0A 1B 2C*/,3, 0x02/* 要什么东西,命令字*/,0,71,0))
		{
			Beep(300,400);
			Beep(300,400);
		
		}
	
	}
	else
	{
		//切换线路
		//命令字从ORDER[0]到ORDER[4]单片机用
		ORDER[0]  = 0x51; //前导码
		ORDER[1]  = 0x52; //前导码
		ORDER[2]  = 0x5B; //触发命令 设置线路
		ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + 01;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
		ORDER[4]  =  3;
		// 延时过0点数   
		
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
		PcSendToSCM(ORDER,31,0);
	}

    SurrenderWindowMessage();

	//延时10豪秒
	Sleep(500);
    SurrenderWindowMessage();
	DataLen     =          0;

	//采集同步电流信号
	//unsigned short  *ai_buf = new unsigned short[15360];
	unsigned short  ai_buf[15360];
	memset(ai_buf,0,15360);

	//自采模式
    err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		return str;
	}
	
	//双缓冲模式
    err = AI_AsyncDblBufferMode(card, 0); 	
	
	if(err != 0)
	{
		return str;
	}

	//采集8通道的数据 0-A相电流 1－B相电流 2－C相电流 3-A相电压 4－B相电压 5－C相电压
	err = AI_ContScanChannels(card,2,AD_B_10_V,ai_buf,15360,(F64)100000,SYNCH_OP);
	
	if(err != 0)
	{
		return str;
	}

	//双缓冲区状态
	err = AI_AsyncDblBufferMode(card, 1);
	
	if(err != 0)
	{
		return str;
	}

	//改回外触发状态
	err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
	
	if(err != 0)
	{
		return str;
	}
	int i;
	//分析采集的数据
	for( i = 0; i < 12000; i++)
	{   	
 
		DataBuf[i] = ai_buf[i]/16;
		
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
	
		switch(i%3)
		{
		case 0:
			{
				//A相电流累加值
				m_ACurrentSum = m_ACurrentSum + DataBuf[i];
				break;
			}
		case 1:
			{
				//B相电流累加值
				m_BCurrentSum = m_BCurrentSum + DataBuf[i];
				break;
			}
		case 2:
			{
               //C相电流累加值
				m_CCurrentSum = m_CCurrentSum + DataBuf[i];
				break;
			}
			//减飘移
		}
	}

	//平均值  A
	m_ACurrentAvgSum = (m_ACurrentSum*1.00)/4000;
	m_BCurrentAvgSum = (m_BCurrentSum*1.00)/4000;
	m_CCurrentAvgSum = (m_CCurrentSum*1.00)/4000;
	
    m_ACurrentSum = m_BCurrentSum = m_CCurrentSum = 0;
	
	//分析采集的数据
	for( i = 0; i < 12000; i++)
	{   	
		
		switch(i%3)
		{
		case 0:
			{
				//A相电流累加值
				m_ACurrentSum = m_ACurrentSum + fabs(DataBuf[i] - m_ACurrentAvgSum);
				break;
			}
		case 1:
			{
				//B相电流累加值
				m_BCurrentSum = m_BCurrentSum + fabs(DataBuf[i] - m_BCurrentAvgSum);
				break;
			}
		case 2:
			{
				//C相电流累加值
				m_CCurrentSum = m_CCurrentSum + fabs(DataBuf[i] - m_CCurrentAvgSum);
				break;
			}
		}
		
	}

	str.Format("%10d|%10d|%10d",int(m_ACurrentSum/2),int(m_BCurrentSum/2),int(m_CCurrentSum/2));
	return str;

}


//检测当前母线出线是否有电流
//BYTE MotherLine 母线编号
//BYTE LineNo     线路编号
BOOL CIFRMView::CheckIfHaveCurrentValue(BYTE MotherLine, BYTE LineNo)
{

	//演示版
	if(AppInfo::Instance().m_YanShi)
	{
		return TRUE;
	}
	int i;
	double m_ACurrentSum,m_BCurrentSum,m_CCurrentSum;
	double m_ACurrentAvgSum,m_BCurrentAvgSum,m_CCurrentAvgSum;
	m_ACurrentSum    = m_BCurrentSum    = m_CCurrentSum    = 0;
	m_ACurrentAvgSum = m_BCurrentAvgSum = m_CCurrentAvgSum = 0;
    BOOL m_IfHaving  = FALSE;

	BYTE   ORDER[15];

	//切换线路
	//命令字从ORDER[0]到ORDER[4]单片机用
	ORDER[0]  = 0x51; //前导码
	ORDER[1]  = 0x52; //前导码
	ORDER[2]  = 0x5B; //触发命令 设置线路
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + 01;//合成字节 前2位为母线, 中间4位为线路号，后2位为相位值 01 A 02 B 03 C
	ORDER[4]  =  3;
	// 延时过0点数   
	
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
	PcSendToSCM(ORDER,31,0);

    SurrenderWindowMessage();

	//延时10豪秒
	Sleep(200);
    SurrenderWindowMessage();
	DataLen    =   0;

	//采集同步电流信号
	unsigned short  ai_buf[15360];
	memset(ai_buf,0,15360);

	//自采模式
    err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		return m_IfHaving;
	}
	
	//双缓冲模式
    err = AI_AsyncDblBufferMode(card, 0); 	
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//采集8通道的数据 0-A相电流 1－B相电流 2－C相电流 3-A相电压 4－B相电压 5－C相电压
	err = AI_ContScanChannels(card,2,AD_B_10_V,ai_buf,15360,(F64)100000,SYNCH_OP);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//双缓冲区状态
	err = AI_AsyncDblBufferMode(card, 1);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//改回外触发状态
	err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//分析采集的数据
	for( i = 0; i < 12000; i++)
	{   	
 
		DataBuf[i] = ai_buf[i]/16;
		
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
	
		switch(i%3)
		{
		case 0:
			{
				//A相电流累加值
				m_ACurrentSum = m_ACurrentSum + DataBuf[i];
				break;
			}
		case 1:
			{
				//B相电流累加值
				m_BCurrentSum = m_BCurrentSum + DataBuf[i];
				break;
			}
		case 2:
			{
               //C相电流累加值
				m_CCurrentSum = m_CCurrentSum + DataBuf[i];
				break;
			}
			//减飘移
		}
	}

	//平均值  A
	m_ACurrentAvgSum = (m_ACurrentSum*1.00)/4000;
	m_BCurrentAvgSum = (m_BCurrentSum*1.00)/4000;
	m_CCurrentAvgSum = (m_CCurrentSum*1.00)/4000;
	
    m_ACurrentSum = m_BCurrentSum = m_CCurrentSum = 0;
		
	
	//分析采集的数据
	for( i = 0; i < 12000; i++)
	{   	
		switch(i%3)
		{
		case 0:
			{
				//A相电流累加值
				m_ACurrentSum = m_ACurrentSum + fabs(DataBuf[i] - m_ACurrentAvgSum);
				break;
			}
		case 1:
			{
				//B相电流累加值
				m_BCurrentSum = m_BCurrentSum + fabs(DataBuf[i] - m_BCurrentAvgSum);
				break;
			}
		case 2:
			{
				//C相电流累加值
				m_CCurrentSum = m_CCurrentSum + fabs(DataBuf[i] - m_CCurrentAvgSum);
				break;
			}
		}
		
	}
  
	if(int(m_ACurrentSum/2) > 1000 || int(m_BCurrentSum/2) > 1000 || int(m_CCurrentSum/2) > 1000)//2000
	{
		m_IfHaving = TRUE;
	}
	
	return m_IfHaving;

}

//检测各线路运行状态
void CIFRMView::OnChecklinestatus() 
{  
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
	{
		//电流运行状态检测
		ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)5,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
		ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
	}
	else
	{
		MessageBox("数据表中没有线路可检测！"," ",MB_OK|MB_ICONWARNING);
	}

}

void CIFRMView::OnUpdateChecklinestatus(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
}

//检测线路的运行状态
void CIFRMView::CheckLineRun()
{

	CDatabase                   db;
	CString        str,MsgStr,str1;
    BYTE         MotherLine,LineNo;
	int                i    =  1,k;
    int      m_LineNumbers  =     0;
	BOOL     m_IfHaveElc    = FALSE;
	m_StartRead             =  TRUE;//读停标志
	CString           m_GetValue[3];
	float      m_addlinecurrent = 0;
		
	//删除所有的数据
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);		
	
	TRY { 
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);     //行
		m_Grid.SetColumnCount(8);  //列
		
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
       #ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
       #endif
		
		GV_ITEM       Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     =   0;
		Item.col     =   0;
		
		Item.nFormat = dwTextStyle;
		Item.strText.Format("%s","序号");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(0,80); 
		
		Item.col     =   1;
		Item.strText.Format("%s","母线编号");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(1,80); 
		
		Item.col     =   2;
		Item.strText.Format("%s","出线编号");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(2,80); 
		
		Item.col     =   3;
		Item.strText.Format("%s","测试对象");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(3,80);
		
		Item.col     =   4;
		Item.strText.Format("%s","A相电流");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(4,120);
		
		Item.col     =   5;
		Item.strText.Format("%s","B相电流");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(5,120);
		
		Item.col     =   6;
		Item.strText.Format("%s","C相电流");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(6,120);
		
		Item.col     =   7;
		Item.strText.Format("%s","测试时间");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(7,180);
		m_Grid.SetModified(FALSE,-1,-1);//只读状态
		m_Grid.m_title  = "";	//标题
		m_Grid.SetBkColor(RGB(255,255,255));
		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->Delete();
		return;
	}
	END_CATCH
		
	SurrenderWindowMessage();
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		SurrenderWindowMessage();
		
		//显示状态栏信息
		StatusStr = "正在测试线路运行状态，请稍侯...";
		SendMessage(WM_EVENT, 1, 0);
		
		//和CRecordset连上
		CRecordset  m_CompanySet(&db);	
		str.Format("SELECT USER_LINENAME,USER_MOTHERLINE,USER_LINENO FROM TB_USER GROUP BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO ORDER BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO");
		m_CompanySet.Open(CRecordset::dynaset,str);
		
		while(!m_CompanySet.IsEOF())
		{
			m_CompanySet.MoveNext();
		}
		
		//得到记录个数
		m_LineNumbers = m_CompanySet.GetRecordCount();
		
		if(m_LineNumbers < 1)
		{
			m_CompanySet.Close();
			db.Close();
			m_StartRead =   FALSE;	
			ShowProgressCtrl(FALSE);	//隐藏滚动条
			return;
		}
		
		//显示滚动条
		ShowProgressCtrl(TRUE);
		
		SetProgressCtrlRange(0, m_LineNumbers,1);
		
		if(!m_CompanySet.IsBOF())
		{
			m_CompanySet.MoveFirst();
		}

		//前3次电流往前移一次
		for(int i = 0; i < 96; i ++)
		{
			m_AllLineThreeCurrent[i] = m_AllLineThreeCurrent[32 + i];
		}

		i =   1;
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			
			SurrenderWindowMessage();
			SetProgressCtrlSetIt();
			SurrenderWindowMessage();
			
			if(	!m_StartRead)
			{
				break;
			}
			
			//线路名称
			m_CompanySet.GetFieldValue(short(0),str1);
			str1.TrimRight();
			str1 = str1 + "线路";
			
			//显示状态栏信息
			StatusStr = "正在检测线路" + str1 + "，请稍侯...";
			SendMessage(WM_EVENT, 1, 0);
			m_CompanySet.GetFieldValue(int(1),str);
			MotherLine  =  atoi(str);
			m_CompanySet.GetFieldValue(int(2),str);
			LineNo      =  atoi(str);;
			
			//演示版本
			if(AppInfo::Instance().m_YanShi)
			{
				//检测是否处于停电状态
				Sleep(1000);
				MsgStr.Format("%.2f|%.2f|%.2f",float(rand()/440000),float(rand()/440000),float(rand()/440000));//11000
			}
			else
			{
				//检测是否处于停电状态
				MsgStr =  CheckCurrentValue(MotherLine,LineNo,FALSE);
			}
			
			m_GetValue[0] =     "";
			m_GetValue[1] =     "";
			m_GetValue[2] =     "";
			m_IfHaveElc   =  FALSE;
			
			//分解MsgStr字符串
			k = MsgStr.Find("|");
			
			if( k != -1)
			{
				m_GetValue[0] = MsgStr.Left(k);
				MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
				
				k = MsgStr.Find("|");
				
				if( k != -1)
				{
					m_GetValue[1] = MsgStr.Left(k);
					MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
					m_GetValue[2] = MsgStr;
				}
				
			}
			
			for(int ll = 0; ll < 3; ll ++)
			{
				
				if(atol(m_GetValue[ll]) > 1000)
				{
					
					m_IfHaveElc  = TRUE;
					
				}				
				
			}

			//电流存档 MotherLine,LineNo
			m_addlinecurrent = atof(m_GetValue[0])/440000 + atof(m_GetValue[1])/440000 + atof(m_GetValue[2])/440000;//三相电流相加
	
			//存32条线路3次电流,各线路的电流值最多2*16=32 32*3 = 96 每条线路存4次电流
			m_AllLineThreeCurrent[3*32 + (MotherLine-1)*16 + (LineNo - 1)]	= 	m_addlinecurrent;
					
			CTime time    = CTime::GetCurrentTime();
			str.Format("%sifrm_%d_%02d_Three_Current_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
			k             =                  0;
			CFileFind                   finder;//是否有此文件
			
			//如果存在数据则添加入库
			if(finder.FindFile(str) != 0) 
			{ 
				k  = 1;
			}
			
			finder.Close();
			
			FILE *text;
			if((text = fopen(str,"a")) != NULL)
			{	
				
				if(k == 0)
				{
					//测试对象,A相电流,B相电流,C相电流,测试时间
					str.Format("测试对象,A相电流,B相电流,C相电流,测试时间\n");
					fputs(str,text);
				}
				
				str.Format("%s,%.2f,%.2f,%.2f,%4d-%02d-%02d %02d:%02d:%02d\n",str1,atof(m_GetValue[0])/440000,atof(m_GetValue[1])/440000,atof(m_GetValue[2])/440000,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				fputs(str,text);		
				fclose(text);
			}
			
			//显示数据
			m_Grid.InsertRow(_T(" "), -1);
			m_Grid.Invalidate(); 
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
			dwTextStyle |= DT_END_ELLIPSIS;
#endif
			
			GV_ITEM  Item;
			Item.mask    = GVIF_TEXT|GVIF_FORMAT;
			Item.row     = m_Grid.GetRowCount() - 1;
			
			//序号
			Item.col     = 0;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",i);
			m_Grid.SetItem(&Item);
			
			//母线编号
			Item.col     = 1;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",MotherLine);
			m_Grid.SetItem(&Item);
			
			//出线编号
			Item.col     = 2;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",LineNo);
			m_Grid.SetItem(&Item); 
			
			//线路名称
			Item.col     = 3;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%s",str1);
			m_Grid.SetItem(&Item);
			
			//A、B、C三相电流 
			for(int ll = 4; ll <= 6; ll ++)
			{
				Item.col     = ll;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%.2f",atof(m_GetValue[ll-4])/440000.00);
				m_Grid.SetItem(&Item);
			}
			
			//时间
			Item.col     =           7;
			Item.nFormat = dwTextStyle;
			
			Item.strText.Format("%4d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
			m_Grid.SetItem(&Item);
			
			if(!m_IfHaveElc)
			{	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   线路名称:%16s[%2d-%2d]  检测停电",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),str1,MotherLine,LineNo);
				WriteToLog(str);
			}
			
			m_Grid.SetModified(FALSE,-1,-1);
			m_Grid.Invalidate();
			
			i ++;			
			m_CompanySet.MoveNext();
	}
	
	m_CompanySet.Close();
	db.Close();
	
	if(m_StartRead)
	{ 
		StatusStr = "【检测结束】";
	}
	else
	{
		StatusStr = "【检测中断】";
	}	
	
	SendMessage(WM_EVENT, 1, 0);
	
	//隐藏滚动条
	ShowProgressCtrl(FALSE);
	
   }
	
//	m_StartRead  =   FALSE;

}

void CIFRMView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	//	SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

//定时处理发驻留读驻留
void CIFRMView::DingShiDeal()
{

	CString       str,strhalt;
	
	//检查时间是否到了发驻留时间,10分钟检查一次	,网络连接时接收远程命令
	if(Received == 2 )
	{
	    //如果和长沙在通讯或者没有驻留上的话
		return;
	}
	
	//如果有下列窗口打开则关闭
	CWnd* pt = CWnd::FindWindow(NULL,"电表信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}

	pt = CWnd::FindWindow(NULL,"变台数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"用户信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"驻留读表数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"正式读表数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"电表信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"电价信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"用电曲线分析处理");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	//如果还在测试读表或正式读表 m_others  FALSE 其它读表  TRUE  驻留读表
//	if(ReadMeterThread != NULL)
/*	if(ReadMeterThread != NULL)

	{	
		
		//如果是在测试读表或正式读表，
		while(!m_others)
		{
		SurrenderWindowMessage();
		Sleep(180);
//			return;
		}
		
	}
*/
/*	int HaveThreadRun = 0;
    MessageBox("检查:有线程运行吗？","  ",MB_OK);	
	while (ReadMeterThread != NULL)
	{ 
		Sleep(1000);
		HaveThreadRun++;
		if(HaveThreadRun > 60) 
		{
			HaveThreadRun = 0;
			MessageBox("目前有线程运行","  ",MB_OK);	
		}
	}
	HaveThreadRun = 0;
	MessageBox("CPU空闲","  ",MB_OK);
*/
//是否是单一版本,不是单一版本则检测串口或局域网
	/*
	if(!AppInfo::Instance().m_SingleBB) 
	{
		
		//如果在连接状态
		if(!m_IfChangeData)
		{
			//如果在连接状态时,强制退出线程
			SendMessage(WM_EVENT,14, 0);
		}
		else
		{
			//修改接收数据标志
			m_IfChangeData = FALSE;
			return;
		}
		
	}
	*/
	
	KillTimer(1);
	SetTimer(1,600000,NULL);         //设置定时器,10分钟检查一次
	
	int k_status        = CheckCurrentTime();

//	CTime m_CurrentTime = CTime::GetCurrentTime();	 	
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测状态结果:%d",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),k_status);
//	WriteToLog(str);

	//检查状态

	switch(k_status)
	{
	case 0:
		{
			//空闲时间,如果有手拉手的话	
			//if(ReadMeterThread == NULL)
			//{
				/*
				CTime m_CurrentTime = CTime::GetCurrentTime();	 	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测0",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	            WriteToLog(str);
				*/

				//调制信号或检测线路电流
/*				while (ReadMeterThread != NULL)
				{ 
				SurrenderWindowMessage();
					Sleep(180);
				}
*/
//	MessageBox("驻留0","  ",MB_OK);
//				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
			//}
			
			break;
		}
	case 1:
		{
			/*
             CTime m_CurrentTime = CTime::GetCurrentTime();	 	
			 str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测1发驻留",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	         WriteToLog(str);
			 */

			//发驻留时间到了,如果原来在读表就退出读表
/*			m_StartRead    =   FALSE;
	           
			//释放CPU时间
			SurrenderWindowMessage();
			Sleep(2000);
			//释放CPU时间
			SurrenderWindowMessage();
*/			
			//发驻留命令,每次二遍
//			if(ReadMeterThread == NULL)
//			{
/*			while (ReadMeterThread != NULL)
			{ 
				SurrenderWindowMessage();
				Sleep(180);
			}
*/
//	MessageBox("驻留1","  ",MB_OK);
			
				//写驻留时间日志时间
				CTime timet = CTime::GetCurrentTime();
				
				/*
				//驻留时间
				CTimeSpan                           ts;
				ts   =  m_AutoReadTime    -      timet;
				
				//还不到读表时间,如果在(0,10)分钟之间的话,不发等
				if(ts.GetTotalSeconds() < 600)
				{
					KillTimer(1);
					SetTimer(1,ts.GetTotalSeconds()*1000,NULL); //设置定时器,ts.GetTotalSeconds()秒后启动
				}
				*/
					
				//初始化读表范围
				InitializeGarrionReadRange();

				//读表次数置为0
				m_ReadModuleTimes =  0;	
				//发驻留次数
				m_SendGarrisonTimes ++;
				
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   第%4d次发[%4d-%02d-%02d %02d:%02d:%02d]定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_SendGarrisonTimes,m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
				WriteToLog(str);
				
				//启动发驻留线程
				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)6,m_Thread_PRIORITY+1,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				
//			}

			break;
		}
	case 2:
		{	 
			/*
			CTime m_CurrentTime = CTime::GetCurrentTime();	 	
			str.Format("%4d-%02d-%02d %02d:%02d:%02d   检测2读表",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	        WriteToLog(str);
			 */

			//读表时间到了,读表操作,且要发过驻留才可以
//			if(ReadMeterThread == NULL)
//			{
/*			while (ReadMeterThread != NULL)
			{ 
				SurrenderWindowMessage();
				Sleep(180);
			}
*/
//	MessageBox("驻留2","  ",MB_OK);
			//++
    			int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
				CTime  m_CurrentTime     =      CTime::GetCurrentTime();
				str                      =              GetZhuLiuTime();
				float             m_temp =                            0;
				CString                                    m_bakstrline;
			
				str.TrimLeft();
				str.TrimRight();
				
				//驻留时间为空,或读表次数够了
				if(str.IsEmpty() || m_ReadModuleTimes > (m_parameter[106] + m_parameter[108]) || CDataBaseInstance::GetAllRecordsCount("TB_USER", "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'") == 0)
				{
					//调制信号或检测线路电流
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
					return;
				}
				
				//驻留时间
				strhalt   = str;
				
				//时间处理
				int k     = str.Find('-');
				
				//年
				m_years   = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();

				//月
				k         = str.Find('-');
				m_months  = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//日
				k         = str.Find(' ');
				m_days    = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//时
				k         = str.Find(':');
				m_hours   = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//分
				k         = str.Find(':');
				m_minutes = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
			
				//秒
				m_seconds      = atoi(str);
				
				CTime            timebakks(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);
				m_AutoReadTime = timebakks;
				
				//时间间隙
				CTimeSpan                           ts;
				ts   =  m_CurrentTime - m_AutoReadTime;

				if(ts.GetTotalSeconds() < 0)
				{
					//调制信号或检测线路电流
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
					return;
				}
				else  if(ts.GetTotalSeconds() < 180)
				{

				
					//先读关口表,刚好到驻留时间点,前3分钟内读表
					if(m_ReadModuleTimes == 0)
					{
						
						//读关口表
						m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY' AND USER_AMMETERKIND>5";
						
						//发驻留次数
						m_SendGarrisonTimes   =   0;	
						str.Format("%4d-%02d-%02d %02d:%02d:%02d   读[%s]定时驻留关口表",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),strhalt);
						WriteToLog(str);
						
						KillTimer(1);
						SetTimer(1,5*60000,NULL); 
						
						//读表次数
						m_ReadModuleTimes = 0;
						
						//读驻留关口表
						ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL); 
						ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						
					}
					
					
				}
				else							
				{	
					
					//如果超过了三分钟,时间间隔改回,当前时间
					CTime timet = CTime::GetCurrentTime();
					
					//半点或整点才可用,10分钟检测一次
	                m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
					
					KillTimer(1);
					SetTimer(1,m_SettimerValues,NULL); 	
					
					//设置驻留读表标志
					SetGarrionLabel();
					
					//关口表不再读表
					CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_AMMETERKIND>4");
					
					m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					//发驻留次数
					m_SendGarrisonTimes   =   0;	
					
					if(m_ReadModuleTimes < m_parameter[106] - 1)
					{
						//如果半小时一次没有读完
						m_ReadModuleTimes        ++;    
					}
					else if(m_ReadModuleTimes == m_parameter[106] - 1)
					{
						//如果半小时一次刚好读完
						m_ReadModuleTimes        ++; 
						
						//记着先半小时一读读完的时间
						m_FirstReadOkTime = CTime::GetCurrentTime();

					}
					else 
					{
						
						//如果读表次数半点一读已经读完,要读8小时一次的读表
						ts   =  timet  - m_FirstReadOkTime ;
						
						//4小时检测电流，8小时必读 /4 是奇数的话
						k = (ts.GetTotalSeconds()+ 60)/14400;
						
						if(k > 0 && ((ts.GetTotalSeconds() + 60)%14400) < 1800)
						{
							
							if(k%2 == 1)
							{
								
								//4小时,测电流读表
								str         =      "";
								
								//检查32条线路的电流
								for(k = 0 ; k < 32; k ++)
								{	
									
                        			m_temp = m_AllLineThreeCurrent[k] + m_AllLineThreeCurrent[32 + k] + m_AllLineThreeCurrent[64 + k];
																	
									//4小时一检测电流大于10%的线路才读
									if((m_AllLineThreeCurrent[96 + k] >= (1.1*m_temp/3.0)) && (m_temp > 0.01))
									{
										
										m_bakstrline.Format("%4d-%02d-%02d %02d:%02d:%02d   4小时一检测，母线%d出线%d比原来大0.1倍电流(现%.2f-原%.2f)",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),(k/16) + 1,(k%16) + 1,m_AllLineThreeCurrent[96 + k],m_temp/3.0);
					                    WriteToLog(m_bakstrline);

										m_bakstrline.Format(" (USER_MOTHERLINE=%d AND USER_LINENO=%d) ", (k/16) + 1,(k%16) + 1);
										
										if(str.IsEmpty())
										{
											str = str  +  m_bakstrline;
										}
										else
										{
											str = str  + " OR " + m_bakstrline;
											
										}

										
									}
									
								}
								
								str.TrimLeft();
								str.TrimRight();

								if( !str.IsEmpty() )
								{
									
									//如果有电流
								//	m_ReadModuleTimes ++;    //4小时一的不算读表次数
									m_AutoReadCondtionStr = m_AutoReadCondtionStr + "AND  (" + str + ")";

								}
								else
								{
									
									str.Format("%4d-%02d-%02d %02d:%02d:%02d   4小时一检测，没有检测出有线路比以前超出10﹪的电流",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					                WriteToLog(str);
									
									//调制信号或检测线路电流
									ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
									ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
									return;
								}
								
								
							}
							else
							{
								//8小时直接读表
								m_ReadModuleTimes  ++;    //读表次数
							}
							
							
						}
						else
						{			
							
							//调制信号或检测线路电流
							ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
							return;
							
						}
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   第%4d次读[%s]定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_ReadModuleTimes,strhalt);
					WriteToLog(str);
					
					//驻留读表,同时线路电流检测
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				}
				
//			}
			
			break;
		}
	case 3:
		{
//			if(ReadMeterThread == NULL)
//			{
/*	while (ReadMeterThread != NULL)
	{ 
		SurrenderWindowMessage();
		Sleep(180);
	}
*/	
//			MessageBox("驻留3","  ",MB_OK);
				//无功补偿表操作
				SendContionStr       =  "ALL";
				ReadMeterThread      =  AfxBeginThread(WorkerThread,(LPVOID)15,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
//			}

			break;
		}
		
	}
			
}

//查找重复记录
void CIFRMView::OnFindrepeatrecords() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm); 
	//打开数据库
	CDatabase           db;
	CString         strSql;
	CString       strValue;
    int         fields = 0;
	
    if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		
		strSql.Format("SELECT * FROM TB_USER WHERE USER_MODULENO in (select USER_MODULENO from TB_USER group by USER_MODULENO  having count(*)>1) AND %s order by USER_MODULENO",pMainFrm->m_wndMyDialogBar.SelectCondition());
		rs.Open(CRecordset::dynaset,strSql);//CRecordset::forwardOnly
		
		if(rs.IsEOF())
		{
			//关闭数据库
			rs.Close( );
			db.Close( );
			MessageBox("没有找到重复记录！"," ",MB_OK|MB_ICONWARNING);
			return;
		}
		else
		{
			while (!rs.IsEOF())
			{
				rs.MoveNext();
			}
		
			fields = rs.GetRecordCount();//只能统计当前已经浏览过的纪录
		}	 
		
		rs.MoveFirst();
	    ShowProgressCtrl(TRUE);
		//范围
	    SetProgressCtrlRange(0, fields,1);

		//得到字段个数
		short nFields = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
		
		//删除所有的数据
		m_Grid.DeleteAllItems();
		
		TRY { 
			m_Grid.SetHeaderSort(TRUE);
			m_Grid.SetFixedRowCount(1);
			m_Grid.SetRowCount(fields + 1);	//行
			m_Grid.SetColumnCount(nFields); //列
			m_Grid.SetBkColor(RGB(255,255,255));
		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
		END_CATCH
			
	
		for(int i = 0;i < nFields; i++)
		{
			//字段名
			m_Grid.SetItemTextFmt(0, i, TB_USERS[2*i + 1]);//fieldinfo.m_strName
			m_Grid.SetColumnWidth(i,120);
		}
		
		status("正在读取重复记录，请稍侯...");
	
		//读数据信息 
		for(int j = 0; j < fields; j ++)
	   	{
			//字段数
			SurrenderWindowMessage();//交出window控制权
			
			for(int i = 0; i < nFields; i++)
			{
				
				rs.GetFieldValue(int(i),strValue);
				
				strValue.TrimLeft();
				strValue.TrimRight();
				
				//显示数据
				m_Grid.SetItemTextFmt(j + 1,i,strValue);
				
			}
			
			//库下滑一个记录
			rs.MoveNext();

			//滚动条下移
	        SetProgressCtrlSetIt();
		}
		
		//关闭数据库
		rs.Close( );
		db.Close( );
		
		m_Grid.ShowWindow(SW_SHOW);
		m_Grid.Invalidate();

		//隐滚动条
	    ShowProgressCtrl(FALSE);
		//置已修改状态
		m_Grid.SetModified(FALSE,-1,-1);
		status("                   ");

	}
	
}


void CIFRMView::OnUpdateFindrepeatrecords(CCmdUI* pCmdUI) 
{

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//选择条件
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}	
}

//等待时间点
BOOL CIFRMView::WaitShiKedian(BYTE m_shikedian)
{
	m_StartRead         = TRUE;
	int  m_waitfortimes =    0;
	
	while(1)
	{
		//时间
		CTime timet = CTime::GetCurrentTime();
		
		//时间点以内
		if(timet.GetMinute() < m_shikedian)
		{
			m_waitfortimes = m_shikedian*60 - timet.GetMinute()*60 - timet.GetSecond();
		}
		else
		{
			m_waitfortimes = m_shikedian*60  + (3600 - timet.GetMinute()*60 - timet.GetSecond());	
		}
		
		if(m_waitfortimes <= 2)
		{
			break;
		}

		//显示状态栏信息
		StatusStr.Format("【已读0次,共%d次,离下次监视读表%4d秒,请稍侯...】",m_readchecktimes,m_waitfortimes);
		SendMessage(WM_EVENT, 1, 0);
		
		//向远程发送信息
		SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
		SendMessage(WM_EVENT, 5, 0);
		
		//如果按了停止按钮
		if(!m_StartRead)
		{	
			return FALSE;
			break;
		}
		
		Sleep(500);
		
		//如果按了停止按钮
		if(!m_StartRead)
		{	
			return FALSE;
			break;
		}
		
		Sleep(500);
		
	}

	return TRUE;

}


//是否是星角连接
BOOL CIFRMView::IsDyConnect(CString m_StationName)
{

	CString       strValue;
	CDatabase           db;
	
	m_StationName.TrimLeft();
    m_StationName.TrimRight();

    //打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset    rs(&db );
		strValue.Format("SELECT TRANSFORMER_NO  FROM TB_TRANSFORMER WHERE RTRIM(LTRIM(TRANSFORMER_NO))='%s' AND TRANSFORMER_CONNECTFORM=1",m_StationName);
		rs.Open(CRecordset::dynaset,strValue);	
		
		if(rs.IsEOF())
		{	
			//关闭数据库
			rs.Close( );
			db.Close( );
			return FALSE;
		}
		
	   	//关闭数据库
		rs.Close( );
		db.Close( );
		return TRUE;

	}

	return  FALSE;

}

void CIFRMView::OnFautoreadset() 
{
    CZHULIUTIMESELECTDlg dlgs;
	dlgs.DoModal();
}

//按日期设置驻留参数
void CIFRMView::ByDateDingShiDeal()
{

	CString       str,strhalt;
	
	/*
	//检查时间是否到了发驻留时间,10分钟检查一次	,网络连接时接收远程命令
	if(Received == 2 )
	{
	    //如果和长沙在通讯或者没有驻留上的话
		return;
	}
	*/
	
	//如果有下列窗口打开则关闭
	CWnd* pt = CWnd::FindWindow(NULL,"电表信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}

	pt = CWnd::FindWindow(NULL,"变台数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"用户信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"驻留读表数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"正式读表数据信息");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"电表信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"电价信息登记表");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"用电曲线分析处理");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	//如果还在测试读表或正式读表 m_others  FALSE 其它读表  TRUE  驻留读表
/*	if(ReadMeterThread != NULL)
	{
		//如果是在测试读表或正式读表，
		if(!m_others)
		{	
			return;
		}
		
	}
*/
/*		while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}
*/
	//是否是单一版本,不是单一版本则检测串口或局域网
	/*
	if(!AppInfo::Instance().m_SingleBB) 
	{
		
		//如果在连接状态
		if(!m_IfChangeData)
		{
			//如果在连接状态时,强制退出线程
			SendMessage(WM_EVENT,14, 0);
		}
		else
		{
			//修改接收数据标志
			m_IfChangeData = FALSE;
			return;
		}
		
	}
	*/
	
	KillTimer(1);
    SetTimer(1,600000,NULL);         //设置定时器,10分钟检查一次

	//按驻留日期检测是否是驻留
	switch(ByDateCheckCurrentTime())
	{
	case 0:
		{
			//空闲时间,如果有手拉手的话	
//			if(ReadMeterThread == NULL)
//			{	
/*	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}
	*/			//调制信号或检测线路电流
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
//			}
			
			break;
		}
	case 1:
		{
//			m_StartRead    =   FALSE;
	           
			//释放CPU时间
			SurrenderWindowMessage();
			Sleep(2000);
			//释放CPU时间
			SurrenderWindowMessage();
						
			//发驻留命令,每次二遍
//			if(ReadMeterThread == NULL)
//			{
/*	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}			
*/				CTime timet = CTime::GetCurrentTime();
				
				/*
				CTimeSpan                          ts;
				ts   =  m_AutoReadTime    -     timet;
				
				if(ts.GetTotalSeconds() < 1800)
				{
					KillTimer(1);
					SetTimer(1,ts.GetTotalSeconds()*1000,NULL); //设置定时器,10分钟检查一次
				}
				*/
				
				//发驻留次数
				m_SendGarrisonTimes ++;	
				
				//读表次数置为0
				m_ReadModuleTimes  = 0;
				
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   第%4d次发[%4d-%02d-%02d %02d:%02d:%02d]定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_SendGarrisonTimes,m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
				WriteToLog(str);
				
				//启动发驻留线程
				ReadMeterThread                 =  AfxBeginThread(WorkerThread,(LPVOID)6,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
				
//			}

			break;
		}
	case 2:
		{	
			//读表时间到了,读表操作,且要发过驻留才可以
//			if(ReadMeterThread == NULL)
//			{
/*
	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}				
*/				//提取当前时间
				int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
				CTime  m_CurrentTime    =  CTime::GetCurrentTime();
				str                     =          GetZhuLiuTime();
				float            m_temp =                        0;
				CString                               m_bakstrline;
								
				str.TrimLeft();
				str.TrimRight();
				
				//驻留时间为空, 注几点用要注意=
				if(str.IsEmpty() || m_ReadModuleTimes > (m_DateReadParameter[63] + m_DateReadParameter[65]) || CDataBaseInstance::GetAllRecordsCount("TB_USER", "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'") == 0)
				{
					//调制信号或检测线路电流
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
					return;
				}
				
				//驻留时间
				strhalt = str;
				
				//时间处理
				int k     = str.Find('-');
				
				//年
				m_years   = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//月
				k         = str.Find('-');
				m_months  = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//日
				k         = str.Find(' ');
				m_days    = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//时
				k         = str.Find(':');
				m_hours   = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//分
				k = str.Find(':');
				m_minutes = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//秒
				m_seconds = atoi(str);
				
				CTime timebakkss(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);
				m_AutoReadTime = timebakkss;
				
				//时间间隙
				CTimeSpan                           ts;
				ts   =  m_CurrentTime - m_AutoReadTime;
				
				if(ts.GetTotalSeconds() < 0)
				{
					
					//调制信号或检测线路电流
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
					return;
					
				}
				else  if(ts.GetTotalSeconds() < 180)
				{
					
					if(m_ReadModuleTimes == 0)
					{
						
						//读关口表
						m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY' AND USER_AMMETERKIND>5";
						
						//发驻留次数
						m_SendGarrisonTimes   =   0;	
						str.Format("%4d-%02d-%02d %02d:%02d:%02d   读[%s]定时驻留关口表",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),strhalt);
						WriteToLog(str);
						
						KillTimer(1);
						SetTimer(1,5*60000,NULL); 
						
						//读表次数
						m_ReadModuleTimes = 0;
						
						//读驻留关口表
						ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
						ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
						
					}
					
					
				}
				else							
				{	
					
					//如果超过了三分钟,时间间隔改回
					CTime timet = CTime::GetCurrentTime();
					
					//半点或整点才可用,10分钟检测一次
	                m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
					
					KillTimer(1);
					SetTimer(1,m_SettimerValues,NULL); 			
					
					//所有的都读表
					for(int i = 0; i < 15; i ++)
					{
						m_TimeSetLabel[i]  = TRUE;  
					}
					
					//关口表不再读表
					CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_AMMETERKIND>4");
					
					m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					m_SendGarrisonTimes   =   0;	//发驻留次数
									
					if(m_ReadModuleTimes < m_DateReadParameter[63] - 1)
					{
						//如果半小时一次没有读完
						m_ReadModuleTimes        ++;    
					}
					else if(m_ReadModuleTimes == m_DateReadParameter[63] - 1)
					{
						//如果半小时一次刚好读完
						m_ReadModuleTimes        ++; 
						
						//记着先半小时一读读完的时间
						m_FirstReadOkTime = CTime::GetCurrentTime();
					}
					else 
					{
						
						//如果读表次数半点一读已经读完,要读8小时一次的读表
						ts   =  timet  - m_FirstReadOkTime ;
						
						//4小时检测电流，8小时必读 /4 是奇数的话
						k = (ts.GetTotalSeconds()+ 60)/14400;
						
						if(k > 0 && ((ts.GetTotalSeconds() + 60)%14400) < 1800)
						{
							
							if(k%2 == 1)
							{
									
								//4小时,测电流读表
								//m_AllLineThreeCurrent[128],存32条线路4次电流
								str         =      "";
								
								//检查32条线路的电流
								for(k = 0 ; k < 32; k ++)
								{	
									
							        m_temp = m_AllLineThreeCurrent[k] + m_AllLineThreeCurrent[32 + k] + m_AllLineThreeCurrent[64 + k];
									
									//4小时一检测电流大于10%的线路才读
									if((m_AllLineThreeCurrent[96 + k] >= 1.1*m_temp/3.0) && (m_temp > 0.01))
									{
										
										m_bakstrline.Format("%4d-%02d-%02d %02d:%02d:%02d   4小时一检测，母线%d出线%d比原来大10﹪电流(现%.2f-原%.2f)",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),(k/16) + 1,(k%16) + 1,m_AllLineThreeCurrent[96 + k],m_temp/3.0);
					                    WriteToLog(m_bakstrline);

										m_bakstrline.Format(" (USER_MOTHERLINE=%d AND USER_LINENO=%d) ", (k/16) + 1,(k%16) + 1);
										
										if(str.IsEmpty())
										{
											str = str   +  m_bakstrline;
										}
										else
										{
											str =  str  + " OR "  + m_bakstrline;
										}
										
									}
									
								}
								
								if(!str.IsEmpty())
								{
									
									//如果有电流
								//	m_ReadModuleTimes ++;    //4小时一的不算读表次数
									m_AutoReadCondtionStr = m_AutoReadCondtionStr + "AND  (" + str + ")";

								}
								else
								{
									
									str.Format("%4d-%02d-%02d %02d:%02d:%02d   4小时一检测，没有线路比以前超出10﹪电流的线路",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					                WriteToLog(str);
									
									//调制信号或检测线路电流
									ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
									ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
									return;
								}
								
								
							}
							else
							{
								//8小时直接读表
								m_ReadModuleTimes  ++;    //读表次数
							}
							
							
						}
						else
						{			
							
							//调制信号或检测线路电流
							ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
							return;
							
						}
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   第%4d次读[%s]定时驻留",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_ReadModuleTimes,strhalt);
					WriteToLog(str);
					
					//驻留读表,同时线路电流检测
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
								
				}				
				
//			}
			
			break;
		}
		 
	}
}


//设置驻留
void CIFRMView::StartZhuLiu()
{
	CString            str;
	m_StartRead     =  TRUE;  //定时发驻留定时读表
	m_ListRows      =     0;  //行号起始为0
	m_times         =     1;  //次数为0	
//	m_StartRead     = FALSE;  //停止执行此操作

	KillTimer(1);             //取消10分钟检查一次检查
	ShowDingShiButton(TRUE);  //定时按钮置为TRUE	
	m_IsAutoSending   =  TRUE;//驻留状态标志

	StatusStr.Format("【按日设置驻留,先间隔半小时读%d次,后间隔八小时读%d次】",m_DateReadParameter[63],m_DateReadParameter[65]);
	status(StatusStr);
    //时间
	CTime timet = CTime::GetCurrentTime();
  
	//初始化电流
    InitializeCurrent();

	//10分钟检测一次
	m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;

	m_ReadModuleTimes      =     0;    //读表次数设为0
	m_SendGarrisonTimes    =     0;    //发驻留次数
	m_zhuliukinds          =     1;//0 按表计种类下驻留 1 按日期下驻留
	
	//定时读表参数,读哪些项
	for(int i = 0; i < 15; i++)
	{
	    m_TimeSetLabel[i]  = TRUE;//定时读表标志
	}

	KillTimer(1);
	SetTimer(1,m_SettimerValues,NULL); //设置定时器,10分钟检查一次
	
}

void CIFRMView::OnUpdateFautoreadset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);	
}


//按日期解析参数
CString CIFRMView::ByDateDecodeParameter()
{
	CString        str,strbak;
	str       =     "【驻留时间】";
	int    j  =                      1;

	for(int ii = 0; ii < 31; ii ++)
	{

		if(m_DateReadParameter[2*ii] > 0)
		{
			if(j > 1)
			{
				strbak.Format("\r\n\r\n%2d、%2d号%2d点",j,ii+1,m_DateReadParameter[2*ii+1]);
			}
			else
			{
				strbak.Format("\r\n%2d、%2d号%2d点",j,ii+1,m_DateReadParameter[2*ii+1]);
			}

			str = str + strbak;
			str = str + "\r\n" + GetZhuLiuRanage(ii + 1);
			
			j ++;
		
		}

	}

	//扫描次数(3-7次)
	strbak.Format("\r\n【扫描次数】\r\n先每隔半小时扫描%d次",m_DateReadParameter[63]);
    str = str + strbak;
	//以后扫描次数(0-3次)
	strbak.Format("\r\n【后扫次数】\r\n后每隔八小时扫描%d次",m_DateReadParameter[65]);
    str = str + strbak;
    //是否一启动就自动驻留
	//pview->m_DateReadParameter[66] = m_autorun;

	if(m_DateReadParameter[66] == 1)
	{
	    strbak.Format("\r\n【自动启动】\r\n软件启动时按日驻留自动启动");
	}
	else
	{
	    strbak.Format("\r\n【自动启动】\r\n软件启动时按日驻留不启动");
	}
    
	str = str + strbak;
	
	return str;


}

//得到一驻留日的内容
CString CIFRMView::GetZhuLiuRanage(short m_date)
{
	CString          str,strsql,StrTemp,str1,str2,str3;
	str           =               "";
    CDatabase                     db;
	long             m_subs      = 0;
	BYTE             m_AmmerAter = 0;
	int                m_GetData = 0;

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
	   
		//和CRecordset连上
		CRecordset  m_CompanySet(&db);
    	strsql.Format("SELECT SUBSTRING(USER_ZHULABEL,%d,3) FROM TB_USER GROUP BY SUBSTRING(USER_ZHULABEL,%d,3) ORDER BY SUBSTRING(USER_ZHULABEL,%d,3)",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);//,(m_date-1)*15+1,(m_date-1)*15+1,(m_date-1)*15+1);	
		m_CompanySet.Open(CRecordset::forwardOnly,strsql);

		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{ 
			m_CompanySet.GetFieldValue(short(0),strsql);
			m_CompanySet.MoveNext();
			m_subs ++;
			
			if(m_subs > 1)
			{
				break;
			}			
		}

		//记录个数
		if(m_subs == 1)
		{

			strsql.TrimLeft();
			strsql.TrimRight();
            
			//转成数
			m_GetData = GetHexValue(strsql);
			m_GetData =      m_GetData%2048;
			
		    str       = "【读表范围】\r\n全部表\r\n";
			StrTemp   = "【读表内容】\r\n";
			str       =   str   +  StrTemp;

			//有功电度
			StrTemp = "";

			if((m_GetData>>9) == 3)//11
			{
               StrTemp = "有功、总有功电度";
			}
			else if((m_GetData>>9) == 2)//10
			{
               StrTemp = "有功电度";
			}

			//无功电度
			if(((m_GetData>>7)%4) == 3)//11
			{

				if(StrTemp.IsEmpty())
				{
                    StrTemp = "无功、总无功电度";
				}
				else
				{
					StrTemp = StrTemp + "、无功、总无功电度";
				}

			}
			else if(((m_GetData>>7)%4) == 2)
			{

				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "无功电度";
				}
				else
				{
					StrTemp = StrTemp + "、无功电度";

				}

			}

			//三相电流
            if(((m_GetData>>6)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "ABC三相电流";
				}
				else
				{
					StrTemp = StrTemp + "、ABC三相电流";
				}
				
			}

			//三相电压
            if(((m_GetData>>5)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "ABC三相电压";
				}
				else
				{
					StrTemp = StrTemp + "、ABC三相电压";
				}
				
			}
			
			//尖峰电量
            if(((m_GetData>>4)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "尖峰电量";
				}
				else
				{
					StrTemp = StrTemp + "、尖峰电量";
				}
				
			}
			
			//峰电量
            if(((m_GetData>>3)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "峰电量";
				}
				else
				{
					StrTemp = StrTemp + "、峰电量";
				}
				
			}
			
			//平电量
            if(((m_GetData>>2)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "平电量";
				}
				else
				{
					StrTemp = StrTemp + "、平电量";
				}
				
			}

		    //谷电量
            if(((m_GetData>>1)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "谷电量";
				}
				else
				{
					StrTemp = StrTemp + "、谷电量";
				}
				
			}
			
			//功率因素
            if(m_GetData%2 == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "功率因素";
				}
				else
				{
					StrTemp = StrTemp + "、功率因素";
				}
				
			}
			
			str = str +  StrTemp;

			
		}
		else
		{				
			m_CompanySet.Close();

			strsql.Format("SELECT USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND FROM TB_USER WHERE SUBSTRING(USER_ZHULABEL,%d,3)<>'000' GROUP BY USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND ORDER BY USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);	
			m_CompanySet.Open(CRecordset::forwardOnly,strsql);

			str     = "【读表范围】\r\n线路名称                       变台名称               读表内容      读表对象";

			//寻找满足条件的记录
			while (!m_CompanySet.IsEOF())
			{
				
				m_CompanySet.GetFieldValue(short(0),str1);
				m_CompanySet.GetFieldValue(short(1),str2);
				str2.TrimLeft();
				str2.TrimRight();

				m_CompanySet.GetFieldValue(short(2),strsql);
                strsql.TrimLeft();
				strsql.TrimRight();
				
				StrTemp   = "";
				
				//转成数
				m_GetData = GetHexValue(strsql);
				m_GetData =      m_GetData%2048;
						
				//有功电度
				StrTemp = "";
				
				if((m_GetData>>9) == 3)//11
				{
					StrTemp = "有功、总有功电度";
				}
				else if((m_GetData>>9) == 2)//10
				{
					StrTemp = "有功电度";
				}
				
				
				//无功电度
				if(((m_GetData>>7)%4) == 3)//11
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp = "无功、总无功电度";
					}
					else
					{
						StrTemp = StrTemp + "、无功、总无功电度";
					}
					
				}
				else if(((m_GetData>>7)%4) == 2)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "无功电度";
					}
					else
					{
						StrTemp = StrTemp + "、无功电度";
						
					}
					
				}
				
				//三相电流
				if(((m_GetData>>6)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "ABC三相电流";
					}
					else
					{
						StrTemp = StrTemp + "、ABC三相电流";
					}
					
				}
				
				//三相电压
				if(((m_GetData>>5)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "ABC三相电压";
					}
					else
					{
						StrTemp = StrTemp + "、ABC三相电压";
					}
					
				}
				
				//尖峰电量
				if(((m_GetData>>4)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "尖峰电量";
					}
					else
					{
						StrTemp = StrTemp + "、尖峰电量";
					}
					
				}
				
				//峰电量
				if(((m_GetData>>3)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "峰电量";
					}
					else
					{
						StrTemp = StrTemp + "、峰电量";
					}
					
				}
				
				//平电量
				if(((m_GetData>>2)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "平电量";
					}
					else
					{
						StrTemp = StrTemp + "、平电量";
					}
					
				}
				
				//谷电量
				if(((m_GetData>>1)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "谷电量";
					}
					else
					{
						StrTemp = StrTemp + "、谷电量";
					}
					
				}
				
				//功率因素
				if(m_GetData%2 == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "功率因素";
					}
					else
					{
						StrTemp = StrTemp + "、功率因素";
					}
					
				}
				
				m_CompanySet.GetFieldValue(int(3),strsql);
				m_AmmerAter = atoi(strsql);
				
				if(m_AmmerAter == 0)
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"居民表");
				}
				else  if(m_AmmerAter == 1)
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"大用户表");
				}
				else
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"台变表等");
				}
				
				str = str + "\r\n" + str3;
				

				m_CompanySet.MoveNext();
			
			}
			

		}

    	m_CompanySet.Close();
		db.Close();

    }

	return str;
}

//十六进字符转成数
int CIFRMView::GetHexValue(CString str)
{
    int iReturn = 0;

	int length = str.GetLength();
    for(int i = length - 1; i >= 0; i--)    
    {
		char cc =  str.GetAt(i);// str[i];

        if(cc >= '0' && cc <= '9')
            iReturn += int((cc - '0') * pow((double)16,length - i - 1));
        else if(cc >= 'a')
            iReturn += int((cc - 'a' + 10) * pow((double)16,length - i - 1));
        else 
            iReturn += int((cc - 'A' + 10) * pow((double)16,length - i - 1));
    }

    return iReturn ;
}

//自动启动按日期驻留
void CIFRMView::ByDateAutoGarrisonTime()
{
    CString               str;
	CDatabase              db;	
	int i;
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset   rs(&db );
		str = "SELECT * FROM TB_DateAuto";
		rs.Open(CRecordset::dynaset,str);
		
		if(rs.IsEOF())
		{
			//关闭数据库
		    rs.Close( );
		    db.Close( );
			return;
		}
		
		//读自动读表信息
		for( i = 0; i < 67; i++)
		{
			rs.GetFieldValue((short)i,str);
			m_DateReadParameter[i] = atoi(str);
		}

		//关闭数据库
		rs.Close( );
		db.Close( );

        if(m_DateReadParameter[66] > 0)
		{

			//15种类型的数据 a的值：0－有功电度-单边累加值 1－有功电度-表总值 2－无功电度-单边累加值 3－无功电度-表总值 4－A相电流 5－B相电流 6－C相电流 7－A相电压 8－B相电压 9－C相电压 10-尖峰电量 11-峰电量 12-谷电量 13－平电量 14-功率因数
			for( i = 0; i < 15; i++)
			{
				m_TimeSetLabel[i]  = TRUE;  
			}	
			
			//停止执行此操作
			m_StartRead      =  FALSE;
			
			//时间
			CTime timet = CTime::GetCurrentTime();//时间
			str.Format("【%4d-%02d-%02d %02d:%02d:%02d】按日设置驻留:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ByDateDecodeParameter());
			WriteToLog(str);
			
			//取消10分钟检查一次检查
			KillTimer(1);
			
			ShowDingShiButton(TRUE);//定时按钮置为TRUE
			m_IsAutoSending     =           TRUE;//驻留状态标志
			m_ReadModuleTimes   =              0;//读表次数设为0
			m_SendGarrisonTimes =              0;//发驻留次数
			m_IfChangeData      =          FALSE;             //修改接收数据标志
			m_zhuliukinds       =               1;//驻留种类 0 按表计种类 1 按日期设置

			StatusStr.Format("【按日设置驻留,先间隔半小时读%d次,后间隔八小时读%d次】",m_DateReadParameter[63],m_DateReadParameter[65]);
			status(StatusStr);
			
			//10分钟检测一次
	        m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
			
			SetTimer(1,m_SettimerValues,NULL);//设置定时器,10分钟检查一次

		}
	
	}
}

//设置按日期设置参数
void CIFRMView::ByDateSetGarrisonRange(BYTE m_date)
{
	CString          strsql,StrRange,str;
    CDatabase                         db;
	int                        m_GetData;
	
	//先把以前的全改成读完状态
	CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY'");
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
	   
		//和CRecordset连上
		CRecordset  m_CompanySet(&db);
    	strsql.Format("SELECT SUBSTRING(USER_ZHULABEL,%d,3) FROM TB_USER GROUP BY SUBSTRING(USER_ZHULABEL,%d,3) ORDER BY SUBSTRING(USER_ZHULABEL,%d,3)",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);	
		m_CompanySet.Open(CRecordset::forwardOnly,strsql);

		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{ 
			m_CompanySet.GetFieldValue(short(0),str);
			str.TrimLeft();
			str.TrimRight();

			//分析转成数
			m_GetData   = GetHexValue(str);
			m_GetData   =   m_GetData%2048;
    	    StrRange    =               "";

			if((m_GetData>>9) == 3)//11
			{
				StrRange = StrRange + "NN";
			}
			else if((m_GetData>>9) == 2)//10
			{
				StrRange = StrRange + "NY";
			}
			else
			{
				StrRange = StrRange + "YY";
			}

			//无功电度
			if(((m_GetData>>7)%4) == 3)//11
			{
				StrRange = StrRange + "NN";
			}
			else if(((m_GetData>>7)%4) == 2)
			{
				StrRange = StrRange + "NY";
			}
			else
			{
				StrRange = StrRange + "YY";
			}

			//三相电流
            if(((m_GetData>>6)%2) == 1)
			{
				StrRange = StrRange + "NNN";
			}
			else
			{
				StrRange = StrRange + "YYY";
			}

			//三相电压
            if(((m_GetData>>5)%2) == 1)
			{
				StrRange = StrRange + "NNN";
			}
			else
			{
				StrRange = StrRange + "YYY";
			}
			
			//尖峰电量
            if(((m_GetData>>4)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
			
			//峰电量
            if(((m_GetData>>3)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
			
			//平电量
            if(((m_GetData>>2)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
	
		    //谷电量
            if(((m_GetData>>1)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
		
			
			//功率因素
            if(m_GetData%2 == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
		
	        //替换	
			strsql.Format("UPDATE TB_USER SET USER_TIMELABEL='%s' WHERE SUBSTRING(USER_ZHULABEL,%d,3)='%s'",StrRange,(m_date-1)*3+1,str);
			CDataBaseInstance::ExecuteDataBaseSQL(strsql);

			m_CompanySet.MoveNext();
	
		}

		m_CompanySet.Close();
		db.Close();
	}

}

void CIFRMView::OnCancelautozhuliu() 
{
	CString     str;

	//取消自动驻留
	if(MessageBox("你想取消软件启动时就自动启动驻留此功能吗？","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//去按表计种类自动驻留
		if(IsCurveTableExist("TB_Auto"))
		{
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_Auto","ALL") > 0)
			{
				
				str.Format("UPDATE TB_Auto SET Auto_Parameter110=%d",0);
				CDataBaseInstance::ExecuteDataBaseSQL(str);
				
			}
			
		}

		//去按日期自动驻留
		if(IsCurveTableExist("TB_DateAuto"))
		{
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_DateAuto","ALL") > 0)
			{
				
				str.Format("UPDATE TB_DateAuto SET Auto_Parameter67=%d",0);
				CDataBaseInstance::ExecuteDataBaseSQL(str);
				
			}
			
		}


		m_parameter[109]        = 0;
		m_DateReadParameter[66] = 0;

		MessageBox("软件启动时启动驻留此功能已取消！"," ",MB_OK|MB_ICONASTERISK);

		
	}
	
}

//自动驻留
void CIFRMView::OnUpdateCancelautozhuliu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2 && (m_parameter[109]>0 || m_DateReadParameter[66]>0));	
}

//按小时检查电流大小，读表中调用
void CIFRMView::EveryHourCheckLine()
{
	if(!m_StartRead)
	{
        return;
	}
	
	//演示版
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	CDatabase                   db;
	CString        str,MsgStr,str1;
    BYTE         MotherLine,LineNo;
	int                          k;
	BOOL     m_IfHaveElc    = FALSE;
	CString           m_GetValue[3];

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		SurrenderWindowMessage();
		
		//显示状态栏信息
		StatusStr = "正在测试线路运行状态，请稍侯...";
		SendMessage(WM_EVENT, 1, 0);

		//和CRecordset连上
		CRecordset  m_CompanySet(&db);	
		str.Format("SELECT USER_LINENAME,USER_MOTHERLINE,USER_LINENO FROM TB_USER GROUP BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO ORDER BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO");
		m_CompanySet.Open(CRecordset::dynaset,str);
		
		//寻找满足条件的记录
      	while (!m_CompanySet.IsEOF())
		{
			
			SurrenderWindowMessage();

			if(	!m_StartRead)
			{
				break;
			}
			
			//线路名称
			m_CompanySet.GetFieldValue(short(0),str1);
			str1.TrimRight();
			str1 = str1 + "线路";
			
			//显示状态栏信息
		    StatusStr = "正在检测线路" + str1 + "，请稍侯...";
		    SendMessage(WM_EVENT, 1, 0);

          	m_CompanySet.GetFieldValue(int(1),str);
			MotherLine  =  atoi(str);

			m_CompanySet.GetFieldValue(int(2),str);
            LineNo      =  atoi(str);;
			
			//演示版本
			if(AppInfo::Instance().m_YanShi)
			{
				//检测是否处于停电状态
				Sleep(1000);
				MsgStr.Format("%.2f|%.2f|%.2f",float(rand()/440000),float(rand()/440000),float(rand()/440000));
			}
			else
			{
				//检测是否处于停电状态
				MsgStr =  CheckCurrentValue(MotherLine,LineNo,FALSE);
			}

			m_GetValue[0] =     "";
            m_GetValue[1] =     "";
            m_GetValue[2] =     "";
            m_IfHaveElc   =  FALSE;

			//分解MsgStr字符串
			k = MsgStr.Find("|");
			
			if( k != -1)
			{
				m_GetValue[0] = MsgStr.Left(k);
				MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);

				k = MsgStr.Find("|");
	            
				if( k != -1)
				{
					m_GetValue[1] = MsgStr.Left(k);
					MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
					m_GetValue[2] = MsgStr;
				}
				
			}

			for(int ll = 0; ll < 3; ll ++)
			{
				
				if(atol(m_GetValue[ll]) > 1000)
				{
					m_IfHaveElc  = TRUE;
				}				
				
			}
			
			//如果此线有电流
            if(((MotherLine-1)*15 + LineNo - 1) < 32)
			{

				//如果有电流
				if(m_IfHaveElc)
				{
					m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
				}
				else
				{
					m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
				}

			}
		
			CTime time    = CTime::GetCurrentTime();
			str.Format("%sifrm_%d_%02d_Three_Current_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
			k             =                  0;
			CFileFind                   finder;//是否有此文件
			
			//如果存在数据则添加入库
			if(finder.FindFile(str) != 0) 
			{ 
				k  = 1;
			}

			finder.Close();
								
			FILE *text;
			if((text = fopen(str,"a")) != NULL)
			{	
				
				if(k == 0)
				{
					//测试对象,A相电流,B相电流,C相电流,测试时间
					str.Format("测试对象,A相电流,B相电流,C相电流,测试时间\n");
                    fputs(str,text);
				}
				
				str.Format("%s,%.2f,%.2f,%.2f,%4d-%02d-%02d %02d:%02d:%02d\n",str1,atof(m_GetValue[0])/440000,atof(m_GetValue[1])/440000,atof(m_GetValue[2])/440000,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				fputs(str,text);

				fclose(text);
			}

			if(!m_IfHaveElc)
			{	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   线路名称:%16s[%2d-%2d]  检测停电",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),str1,MotherLine,LineNo);
				WriteToLog(str);
			}
			
			m_CompanySet.MoveNext();

		}
		
		m_CompanySet.Close();
		db.Close();
		
		StatusStr = "【电流检测结束】";
		SendMessage(WM_EVENT, 1, 0);	
		
		//检测无线模块电流电压
//		SendMessage(WM_EVENT, 17, 0);
    }

}

void CIFRMView::OnChangeammeter() 
{
    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	if(m_CCHANGEAMMETER->IsOpen())
	{
		m_CCHANGEAMMETER->Close();
	}
	
	//数据库表是否打开
	if(m_CCHANGEAMMETER->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CCHANGEAMMETERDlg dlg(m_CCHANGEAMMETER.get(),0);
		dlg.m_filtercondtion = "";
		
		dlg.DoModal();
		
		if(m_CCHANGEAMMETER->IsOpen())
		{
			m_CCHANGEAMMETER->Close();
		}
		
	}	
}

//初始化电流
void CIFRMView::InitializeCurrent()
{

	for(int ii = 0; ii < 128; ii ++)
	{
		m_AllLineThreeCurrent[ii] = 0;//存32条线路3次电流,各线路的电流值最多2*16=32 32*3 = 96 每条线路存3次电流
	}	
	
}

void CIFRMView::OnModifyprotcol() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	CString         StrSql;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	 CProtcoldlg   dlg;
	
	 if(dlg.DoModal() == IDOK)
	 {
		 
		 switch(dlg.m_kinds)
		 {
		 case 0:
			 {
				 //抄表协议
				 StrSql.Format("所选用户模块[%d户]抄表协议都改为%d协议吗？\r\n警告：修改此参数将会影响数据抄表！请慎重！",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 case 1:
			 {
				 //模块母线
 				 StrSql.Format("所选用户模块[%d户]母线编号都改为%d吗？\r\n警告：修改此参数将会影响数据抄表！请慎重！",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 case 2:
			 {
				 //模块出线
  				 StrSql.Format("所选用户模块[%d户]出线编号都改为%d吗？\r\n警告：修改此参数将会影响数据抄表！请慎重！",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 }

		 if(MessageBox(StrSql," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		 {
			 return;
		 }	
		 
		 switch(dlg.m_kinds)
		 {
		 case 0:
			 {
				 //抄表协议
				 StrSql.Format("Update TB_USER SET USER_PROTOCOL=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 case 1:
			 {
				 //模块母线
				 StrSql.Format("Update TB_USER SET USER_MOTHERLINE=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 case 2:
			 {
				 //模块出线
				 StrSql.Format("Update TB_USER SET USER_LINENO=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 }

		 CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
		 		 		 
		 MessageBox("所选模块抄表参数修改完毕！","  ",MB_OK|MB_ICONASTERISK);

	 }

}

//无线模块通信状态检测
void CIFRMView::OnWxcheckstatus() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	for(int i = 0; i < 6; i ++)
	{
	    m_TestParameter[i] = 0;
	}

	CTestCommDlg  dlg;

	if(dlg.DoModal() == IDOK)
	{	
		//如果DIALOGBAR可见的话则隐藏
    	SendMessage(WM_EVENT, 6, 0);

		m_TestParameter[0] = dlg.m_test1;
		m_TestParameter[1] = dlg.m_test2;
		m_TestParameter[2] = dlg.m_test3;
		m_TestParameter[3] = dlg.m_test4;
		m_TestParameter[4] = dlg.m_test5;
		m_TestParameter[5] = dlg.m_testtimes;
		//电流运行状态检测
		ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)14,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
		ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
	}

}

//检查通读状态,读A相是否成功
void CIFRMView::CheckTongXunStatus()
{
	//演示版
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE     ORDER[15];
	int m_SuccessTimes[4] = {0};
	int m_NoAnswers[4]    = {0};
	CString                 str;
  	m_StartRead             =  TRUE;//读停标志
    int     m_connecttimes  =     0;	


	//删除所有的数据
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);		
	
	TRY { 
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);     //行
		m_Grid.SetColumnCount(15);  //列
		
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
       #ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
       #endif
		
		GV_ITEM       Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     =   0;
		Item.col     =   0;
		
		Item.nFormat = dwTextStyle;
		Item.col     =   0;
		Item.strText.Format("%s","1段成功");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(0,70); 

		Item.col     =   1;
		Item.strText.Format("%s","1段末回");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(1,70); 
		
		Item.col     =   2;
		Item.strText.Format("%s","1段成功率");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(2,70); 
		
	
		Item.col     =   3;
		Item.strText.Format("%s","2段成功");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(3,70); 

		Item.col     =   4;
		Item.strText.Format("%s","2段末回");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(4,70); 

		Item.col     =   5;
		Item.strText.Format("%s","2段成功率");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(5,70);

		Item.col     =   6;
		Item.strText.Format("%s","3段成功");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(6,70); 

		Item.col     =   7;
		Item.strText.Format("%s","3段末回");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(7,70); 

		Item.col     =   8;
		Item.strText.Format("%s","3段成功率");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(8,70);

		Item.col     =   9;
		Item.strText.Format("%s","4段成功");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(9,70); 

		Item.col     =   10;
		Item.strText.Format("%s","4段末回");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(10,70); 

		Item.col     =   11;
		Item.strText.Format("%s","4段成功率");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(11,70);

		
		Item.col     =   12;
		Item.strText.Format("%s","总成功次");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(12,70); 
		
		Item.col     =   13;
		Item.strText.Format("%s","总末回次");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(13,70); 
		
		Item.col     =   14;
		Item.strText.Format("%s","总成功率");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(14,70);
		
		m_Grid.SetModified(FALSE,-1,-1);//只读状态
		m_Grid.m_title  = "";	//标题
		m_Grid.SetBkColor(RGB(255,255,255));
		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->Delete();
		return;
	}
	END_CATCH
		
	SurrenderWindowMessage();
			
	//显示滚动条
	ShowProgressCtrl(TRUE);
	//显示数据
	m_Grid.InsertRow(_T(" "), -1);
	m_Grid.Invalidate(); 
	
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
	dwTextStyle |= DT_END_ELLIPSIS;
#endif
	
	GV_ITEM  Item;
	Item.mask    = GVIF_TEXT|GVIF_FORMAT;
	Item.row     = m_Grid.GetRowCount() - 1;

	SetProgressCtrlRange(0,m_TestParameter[5],1);
	
	for(int i = 0; i < m_TestParameter[5]; i ++)
	{
		
		if(!m_StartRead)
		{
			break;
		}
		
		//4段母线
		for(int ii  = 0; ii < 4; ii ++)
		{
			

			if(m_TestParameter[0] == 0 && ii == 0)
			{
				continue;
			}

			if(m_TestParameter[1] == 0 && ii == 1)
			{
				continue;
			}

			
			if(m_TestParameter[2] == 0 && ii == 2)
			{
				continue;
			}

			if(m_TestParameter[3] == 0 && ii == 3)
			{
				continue;
			}

			m_connecttimes ++;

			//显示状态栏信息
			StatusStr.Format("正在测第%d(%d)次,第%d段母线,间隔%d秒无线通讯，稍侯...",i + 1,m_TestParameter[5],ii + 1,m_TestParameter[4]);
			SendMessage(WM_EVENT, 1, 0);

			ORDER[0]    = 0x51;//前导码
			ORDER[1]    = 0x52;
			ORDER[2]    = 0x58;//A相读信号角度
			ORDER[3]    = ii;  //母线
			ORDER[4]    = 0;
			ORDER[5]    = 0;
			ORDER[6]    = 0;
			ORDER[7]    = 0;
			ORDER[8]    = 0;
			ORDER[9]    = 0;
			ORDER[10]   = 0;
			ORDER[11]   = 0;
			ORDER[12]   = 0;
			ORDER[13]   = 0;

			SurrenderWindowMessage();
			m_angles  =         0xff;
			
			//向单片机发命令
			if(PcSendToSCM(ORDER,31,0))
			{
				
				Sleep(1000);
				
				if((m_angles != 0xff) && (m_angles > 0))
				{
					
					switch(ii)
					{
					case 0:
						{
					       m_SuccessTimes[0] ++;
						   break;
						}
					case 1:
						{
					       m_SuccessTimes[1] ++;
						   break;
						}
					case 2:
						{
					       m_SuccessTimes[2] ++;
						   break;
						}
					case 3:
						{
					       m_SuccessTimes[3] ++;
						   break;
						}
					}
					
				}
				
				if(m_angles == 0xff) 
				{

					switch(ii)
					{
					case 0:
						{
					       m_NoAnswers[0] ++;
						   break;
						}
					case 1:
						{
					       m_NoAnswers[1] ++;
						   break;
						}
					case 2:
						{
					       m_NoAnswers[2] ++;
						   break;
						}
					case 3:
						{
					       m_NoAnswers[3] ++;
						   break;
						}
					}
					
				}
				
			}	
			
			
			switch(ii)
			{
			case 0:
				{
					//1段成功次数
					str.Format("%7d",m_SuccessTimes[0]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 0, str);
					//1段末回次数
					str.Format("%7d",m_NoAnswers[0]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 1, str);

					//1段通讯成功率	
					if((i + 1 - m_NoAnswers[0]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[0]*1.00/(i + 1 - m_NoAnswers[0])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 2, str);
 					break;
				}
			case 1:
				{
					//2段成功次数
					str.Format("%7d",m_SuccessTimes[1]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 3, str);
					//2段末回次数
					str.Format("%7d",m_NoAnswers[1]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 4, str);

					//2段通讯成功率	
					if((i + 1 - m_NoAnswers[1]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[1]*1.00/(i + 1 - m_NoAnswers[1])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 5, str);
					break;
				}
			case 2:
				{
					//3段成功次数
					str.Format("%7d",m_SuccessTimes[2]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 6, str);
					//2段末回次数
					str.Format("%7d",m_NoAnswers[2]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 7, str);

					//2段通讯成功率	
					if((i + 1 - m_NoAnswers[2]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[2]*1.00/(i + 1 - m_NoAnswers[2])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 8, str);
					break;
				}
			case 3:
				{
					//4段成功次数
					str.Format("%7d",m_SuccessTimes[3]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 9, str);
					//4段末回次数
					str.Format("%7d",m_NoAnswers[3]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 10, str);
				
					//4段通讯成功率	
					if((i + 1 - m_NoAnswers[3]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[3]*1.00/(i + 1 - m_NoAnswers[3])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 11, str);
					break;
				}

			}
						
			//总成功次数
			str.Format("%7d",m_SuccessTimes[0] + m_SuccessTimes[1] + m_SuccessTimes[2] + m_SuccessTimes[3]);
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 12, str);
			
			//总末回次数
			str.Format("%7d",m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3]);
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 13, str); 
			
			//总通讯成功率
			if((m_connecttimes - (m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3])) > 0)
			{
				str.Format("%.3f",(m_SuccessTimes[0] + m_SuccessTimes[1] + m_SuccessTimes[2] + m_SuccessTimes[3])*100.00/(m_connecttimes - (m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3])));
			}
			else
			{
				str = "";
			}
			
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 14, str); 
				
			m_Grid.Invalidate();
			m_Grid.Refresh();
			
			SurrenderWindowMessage();
					
			if(m_TestParameter[4]  > 0)
			{

				for(int j = 0; j < 4*(m_TestParameter[4] -1); j ++)
				{
					
					Sleep(250);	
					SurrenderWindowMessage();
					
					if(!m_StartRead)
					{
						break;
					}
					
				}

			}
			
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}

		}

		if(!m_StartRead)
		{
			break;
		}

		SetProgressCtrlSetIt();
		SurrenderWindowMessage();
		
	}

	m_Grid.SetModified(FALSE,-1,-1);//只读状态

	if(m_StartRead)
	{ 
		StatusStr = "【检测结束】";
	}
	else
	{
		StatusStr = "【检测中断】";
	}	
	
	SendMessage(WM_EVENT, 1, 0);
	
	//隐藏滚动条
	ShowProgressCtrl(FALSE);
	
    m_StartRead  =   FALSE;

}


//换算电流值
int CIFRMView::ChangeIValue(BYTE m_Ivale)
{
	int m_ReturnValue = 0;

	if(m_Ivale <= 22)
	{
		m_ReturnValue =  m_Ivale*1.000/22*400;
	}
	else if(m_Ivale > 22 && m_Ivale <= 38)
	{
		m_ReturnValue =  400 + (m_Ivale-22)*1.000/(38-22)*(720  - 400);
	}
	else if(m_Ivale > 38 && m_Ivale <= 53)
	{
		m_ReturnValue =  720 + (m_Ivale-38)*1.000/(53-38)*(800  - 720);
	}
	else if(m_Ivale > 53 && m_Ivale <= 57)
	{
		m_ReturnValue =  800 + (m_Ivale-53)*1.000/(57-53)*(912  - 800);
	}
	else if(m_Ivale > 57 && m_Ivale <= 73)
	{
		m_ReturnValue =  912 + (m_Ivale-57)*1.000/(73-57)*(1200 - 912);
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

//测试无线模块电流电压
void CIFRMView::CheckWireLess()
{

	//演示版
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE             ORDER[15];
	int m_SuccessTimes =     0;
	CString           str,str1;
	CString             newstr;

	newstr          =   "";
		
	if(!m_StartRead)
	{
		return;
	}

	for(int jjj = 0; jjj < 6;  jjj ++)
	{
		
		if(!m_StartRead)
		{
			break;
		}
		
		//显示状态栏信息
		StatusStr.Format("正在测试第%d次无线通讯状态，请稍侯...",jjj + 1);
		SendMessage(WM_EVENT, 1, 0);
		int j;
		for( j = 0; j < 4; j ++)
		{
			
			Sleep(250);	
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}
			
		}
		
		SurrenderWindowMessage();
		
		ORDER[0]    = 0x51;//前导码
		ORDER[1]    = 0x52;
		
		switch(jjj)
		{
		case 0:
			{
				ORDER[2]    = 0xc6;//A相无线模模块
				ORDER[3]    =    0;//母线
				break;
			}
		case 1:
			{
				ORDER[2]    = 0xc7;//B相无线模模块	
				ORDER[3]    =    0;//母线
				break;
			}
		case 2:
			{
				ORDER[2]    = 0xc8;//C相无线模模块	
				ORDER[3]    =    0;//母线
				break;
			}
		case 3:
			{
				ORDER[2]    = 0xc6;//A相无线模模块
				ORDER[3]    =    1;//母线
				break;
			}
		case 4:
			{
				ORDER[2]    = 0xc7;//B相无线模模块	
				ORDER[3]    =    1;//母线
				break;
			}
		case 5:
			{
				ORDER[2]    = 0xc8;//C相无线模模块	
				ORDER[3]    =    1;//母线
				break;
			}
		}
		
		ORDER[4]    = 0;
		ORDER[5]    = 0;
		ORDER[6]    = 0;
		ORDER[7]    = 0;
		ORDER[8]    = 0;
		ORDER[9]    = 0;
		ORDER[10]   = 0;
		ORDER[11]   = 0;
		ORDER[12]   = 0;
		ORDER[13]   = 0;
		m_angles    = 0xff;
		
		//向单片机发命令
		if(PcSendToSCM(ORDER,31,0))
		{
			
			Sleep(50);
			
			if(m_angles != 0xff)
			{
				
				m_SuccessTimes ++;
				
			}
			
		}
		
		for( j = 0; j < 4; j ++)
		{
			
			Sleep(250);	
			
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}
			
		}
		
		//通讯成功次数
		if(m_angles == 0xff)
		{
			str = "通讯故障";
		}
		else
		{
			//前1位为电压    0  有  1无
			if(m_angles/128 > 0)
			{
				str.Format("无 %d",ChangeIValue(m_angles%128));
			}
			else
			{
				str.Format("有 %d",ChangeIValue(m_angles%128));
			}
			
		}	
		
		newstr = newstr + str + ",";
		
		SurrenderWindowMessage();
	}	
	
	//通讯成功次数
	str.Format("%d",m_SuccessTimes);
	newstr = newstr + str + ",";
		
	//总通讯次数
	str.Format("%d",6);
	newstr = newstr + str + ",";
		
	//通讯成功率
	str.Format("%.2f%s",m_SuccessTimes*1.00/6*100,"%");
	newstr = newstr + str + ",";
	
	CTime time    = CTime::GetCurrentTime();
	str.Format("%sifrm_%d_%02d_Wireless_Info_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
	BYTE   k         =               0;
	CFileFind                   finder;//是否有此文件
	
	//如果存在数据则添加入库
	if(finder.FindFile(str) != 0) 
	{ 
		k  = 1;
	}
	
	finder.Close();
	
	FILE *text;
	if((text = fopen(str,"a")) != NULL)
	{	
		
		if(k == 0)
		{
			fputs("1段A相电压电流,1段B相电压电流,1段C相电压电流,2段A相电压电流,2段B相电压电流,2段C相电压电流,通讯成功次数,总通讯次数,通讯成功率,测试时间\n",text);
		}
		
		str1.Format("%4d-%02d-%02d %02d:%02d:%02d\n",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		
		fputs(newstr + str1,text);		
		fclose(text);
	}
	
	SurrenderWindowMessage();
}

//检验当前的数据是否有效 m_kinds 0 可以和上次的数相等，1不能=
BOOL CIFRMView::CheckReadValueValid(long m_module,CString m_FieldName,double Currentvalue,CString m_zhutimeValue,BYTE m_kinds)
{
	CDatabase                    dbs;	
	CString                   strSql;
	double       m_tempvalue  =    0;
	int          m_days       =    0;
	BOOL         m_Successing = FALSE;

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset             rs(&dbs);
		strSql.Format("SELECT  count(*) FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d AND %s>= 0.01", m_module,m_module,m_FieldName);
//		strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_MODULENO=%d AND %s>= 0.01",m_module,m_FieldName); //IS NOT  NULL
//      WriteToLog(strSql);
		
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,strSql);
		rs.Close();

		if(atol(strSql) > 0)
		{			

			//GARRISON_WORKDEGREE
			strSql.Format("SELECT  %s,DATEDIFF(day,GARRISON_HALTTIME, '%s'),GARRISON_HALTTIME FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d", m_FieldName,m_zhutimeValue,m_module,m_module);
	        rs.Open(CRecordset::forwardOnly,strSql);

			//底值
			rs.GetFieldValue((short)0,strSql);
        //	WriteToLog(strSql);
    	//	WriteToLog("底值:" + strSql);			
			m_tempvalue = atof(strSql);
			
			//时间差天数
			rs.GetFieldValue((short)1,strSql);
			
		//	WriteToLog("时间差天数:" + strSql);

			m_days     = atoi(strSql);
			rs.Close();

		//	strSql.Format("差值:%f",Currentvalue - m_tempvalue);
		//	WriteToLog(strSql);
			if(m_days == 0)
			{
				m_days  =  1;
			}

			//可以等
			if(m_kinds == 0 || (m_days == 1 &&  m_kinds > 0))
			{
				//一天跑0~200度
				if(((Currentvalue - m_tempvalue) <= m_days*200) && ((Currentvalue - m_tempvalue) >= 0))
				{
					m_Successing = TRUE;
				}
			}
			else
			{
				//一天跑0~200度
				if(((Currentvalue - m_tempvalue) <= m_days*200) && ((Currentvalue - m_tempvalue) > 0))
				{
					m_Successing = TRUE;
				}
				
			}
			
		}
		else
		{
			m_Successing = TRUE;
		}

		//关闭数据库
		dbs.Close();	

	}
	
	return m_Successing; 

}


//全采三相电流读表数据,采集六通道
double CIFRMView::ReadSixChannelMeter(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/,BYTE Item/* 要什么东西*/,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/,CString m_AmmeterType/*脉冲表型号*/)
{
//	WriteToLog("[星角读表]");

	double  m_RetuenValue =  0;
	double  m_tempvalue   =  0;
	int     HalfCount  =     0;
	BOOLEAN bHalfReady = FALSE;
	bStopped           = FALSE;
	U32                  count;
	DataLen            =     0;
//	U16            overrunFlag;
	int     m_YanShiMillSecond;//延时
	//检测电流电压
	CString                str;
	BOOL m_changed     = FALSE;
	BYTE     k1  =  0,k2 =   1;

	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	
	if(!m_StartRead)
	{
		return -1;
	}
	
	//演示版本
	if(AppInfo::Instance().m_YanShi)
	{
		
		for(int jj = 0 ; jj < 7; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(1000);
			}
			else
			{
				break;
			}
			
		}
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		CTime time  = CTime::GetCurrentTime();
		
		if(Item == 0xf6 || Item==0xf8)
		{
			m_RetuenValue = 333333.33;
		}
		else if(Item == 0x38 || Item==0xB8)
		{
			m_RetuenValue = 0.98;
		}
		else
		{
			//返回值ModuleNum
			m_RetuenValue = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01 +  ModuleNum*0.001;
		}
		
	}
	else
	{
		unsigned short *ai_buf=NULL;
	    
		//开始采集数据
		memset(DataBuf,0,800000);
        memset(ReadBuff,0,1024);
		
		//如果打包读表
		if(m_QuickReading)
		{  	
			
			//存61、62协议485表快速读表的功率因素
			if(((Protocol/10) == 6) && (Item==0x07 || Item==0x06) && ((ModuleNum%100) > 12))
			{
				
				if(ModuleNum/100 < 20000)
				{

					//如果原来读出此表的值了
					if(m_QuickGlys[ModuleNum/100 - 1] >= 0)
					{

						return m_QuickGlys[ModuleNum/100 - 1];

					}
					
				}
				
			}
			
        	//71,72,73协议的脉冲,一次上来3个模块的数据，32位，每个模块10位，最大999，每次上来3个,61,62的485,功率因素和有功功率打包在一起
			if((((ModuleNum%100) <= 8) && (Item==0x02 || Item==0x82) && ((Protocol/10) == 7)) || ((Protocol/10) == 6 && ((ModuleNum%100) > 12) && (Item==0x1F || Item==0x1E)))
			{
				
				CTime     timet    = CTime::GetCurrentTime();
				str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
				
				//此模块是否能快速读表
				if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
				{	   
					
					//对比两个模块,71,72,73协议
					if((m_QuickModuleAddress/100 == ModuleNum/100) && ((Protocol/10) == 7))
					{
						
						//快速读表模块子表的范围
						if((m_QuickModuleAddress%100) >= 1 &&  (m_QuickModuleAddress%100) <= 3)
						{
							k1 = 1;
						}
						else if((m_QuickModuleAddress%100) >= 4 &&  (m_QuickModuleAddress%100) <= 6)
						{
							k1 = 2;
						}
						else if((m_QuickModuleAddress%100) >= 7 &&  (m_QuickModuleAddress%100) <= 8)
						{
							k1 = 3;
						} 
						
						//当时读表模块子表的范围
						if((ModuleNum%100) >= 1 &&  (ModuleNum%100) <= 3)
						{
							k2 = 1;
						}
						else if((ModuleNum%100) >= 4 &&  (ModuleNum%100) <= 6)
						{
							k2 = 2;
						}
						else if((ModuleNum%100) >= 7 &&  (ModuleNum%100) <= 8)
						{
							k2 = 3;
						}
						
						//两个在一个段
						if(k1 == k2) 
						{
							//AfxMessageBox("1");
							//m_QuickReadParameter[0] 最新有功电度读表值
							//m_QuickReadParameter[1] 有功电度底值
							//m_QuickReadParameter[2] 3200的倍数,直接算出值								   
							
							//读出的三个打包的值,前10位第一子表模块的值，中间10位第二子表模块的值，后面10位为第三子表模块的值
							if(m_QuickReadModuleValue >= 0)
							{
								
								switch((ModuleNum%10)%3)
								{
								case 1:
									{	  
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
										break;
									}
								case 2:
									{
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
										break;
									}
								case 0:
									{	
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
										break;
									}
								}
								
								//除以脉冲比+表底
								m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
								
							//	str.Format("模块号:%d,原来的值:%f,表底:%f,倍率:%f,\r\n新算出的值:%f,加表底:%f,第一子表:%d,第二子表:%d,第三子表:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
				            //  WriteToLog(str);
																						
								//算出的数大于或等于合理的话
								if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
								{
							//		WriteToLog("加表底大于等于原底数");
									return  m_RetuenValue;
								}
								
							//	WriteToLog("加表底小于原底数");
								
								
							}
							else
							{
								
								if(long(m_QuickReadModuleValue) < -1)
								{
									//没有驻留上数据
									return long(m_QuickReadModuleValue);
								}
								
							}									 
							
						}

					}
					else
					{
						  
						   m_changed              =  TRUE;
						   
						   if((Protocol/10) == 7)
						   {
							   m_QuickModuleAddress   =     0;//快速读表的地址
						       m_QuickReadModuleValue =    -1;
							  
							   if((ModuleNum%100 <= 3))
							   {
								   
								   //最前3个模块,子表地址为01,02,03
								   if(Item == 0x02)
								   {
									   Item = 0x0E;
								   }
								   else
								   {
									   Item = 0x8E;
								   }
								   
							   }
							   else if((ModuleNum%100 >= 4) && (ModuleNum%100 <= 6))
							   {
								   
								   //中间3个模块,子表地址为04,05,06
								   if(Item == 0x02)
								   {
									   Item = 0x10;
								   }
								   else
								   {
									   Item = 0x90;
								   }					   
								   
							   }
							   else 
							   {
								   //最后2个模块,子表地址为07,08
								   if(Item == 0x02)
								   {
									   Item = 0x12;
								   }
								   else
								   {
									   Item = 0x82;
								   }					   
								   
							   }
							   
							//   str.Format("协议：%d，快速读表模块号：%d，指令:%0x\r\n",Protocol,ModuleNum,Item);
							//   WriteToLog(str);
							   
						   }
						   else
						   {
							   //61,62协议
							   if(Item == 0x1F)
							   {
								   Item = 0x01;
							   }
							   else
							   {
								   Item = 0x00;
							   } 
							   
							//   str.Format("协议：%d，快速读表模块号：%d，指令:%0x\r\n",Protocol,ModuleNum,Item);
							//   WriteToLog(str);
							   
						   }
						   
					}
					   
				}
			    else
				{
				   m_QuickReadModuleValue     =              -1;
				   m_QuickModuleAddress       =       ModuleNum;//快速读表的地址
				}
			   
		   }		
			   
		}
		
		//向单片机发指令
		if(!SendOrderToSCM(ModuleNum/*模块号*/,StationNo/*手拉手电站码*/,MotherLine/*母线*/,LineNo/*线号*/, Phase/*相选择0A 1B 2C*/,3, Item/* 要什么东西,命令字*/,0,Protocol,m_SendAngle))
		{
		//	Beep(300,400);
		//	Beep(300,400);
		}
	
		//自采模式
		err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
		
		if(err != 0)
		{
			return -1;
		}
		
		//双缓冲模式
		err = AI_AsyncDblBufferMode(card, 1); 	
		
		if(err != 0)
		{
			return -1;
		}
		
		//各协议的延时控制
		switch(Protocol)
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

//		str.Format("抄表协议:%d,延时:%d毫秒",Protocol,m_YanShiMillSecond);
//		WriteToLog(str);

		//无线延时 1230毫秒 ，485延时610毫秒
		//延时处理
		m_YanShiMillSecond = m_YanShiMillSecond + 610;


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

			if(!m_StartRead)
			{
				return -1;
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
			return -1;
		}
		
		do
		{
			do
			{
				//半满
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);				
					
				CTimeSpan ts    = CTime::GetCurrentTime() - time0;
				
				if(Protocol != 22)
				{

					//如果不是22协议AI_ContStatus
					if(ts.GetTotalSeconds() > (Protocol%10)*11 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				else
				{	
					//如果是22协议
					if(ts.GetTotalSeconds() > 10 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				
			} while (!bHalfReady && !bClearOp);
			
			if(!m_StartRead)
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

				if(!m_StartRead)
				{
					bClearOp = TRUE;
				}
				
				CTimeSpan ts    = CTime::GetCurrentTime() - time0;
				
				//时间控制
				switch(Protocol)
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
				
				if(Protocol != 22)
				{
					
					//如果不是22协议
					if(ts.GetTotalSeconds() > (Protocol%10)*11 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						break;
					
					}
					
				}
				else
				{	
					
					//如果是22协议
					if(ts.GetTotalSeconds() > 10 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
			}
			
		
        }while (!bClearOp && !bStopped && m_StartRead);
	
		AI_AsyncClear(card, &count);
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		//返回值
		m_RetuenValue = DecodeSixChannel(ModuleNum,Protocol,Item,Phase);//解码

	}
	
	//快速读表
	if(m_QuickReading && m_changed)
	{	

		//如果数据大于0
		if(m_RetuenValue >= 0)
		{	
			
			//71,72,73协议
			if((Protocol/10) == 7)
			{	
				//71,72,73肪冲表
				m_QuickReadModuleValue =  long(m_RetuenValue);//三个模块的数据打在一起
				m_QuickModuleAddress   =            ModuleNum;//快速读表的地址
				
				//m_QuickReadParameter[0] 最新有功电度读表值
				//m_QuickReadParameter[1] 有功电度底值
				//m_QuickReadParameter[2] 3200的倍数,直接算出值

				switch((ModuleNum%10)%3)
				{
				case 1:
					{	  
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024;
						break;
					}
				case 2:
					{
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024;
						break;
					}
				case 0:
					{	
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024);	
						break;
					}
				}
				
				//除以脉冲比,得出新的数据值
				m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
				
			//	str.Format("模块号:%d,原来的值:%f,表底:%f,倍率:%f,\r\n新算出的值:%f,加表底:%f,第一子表:%d,第二子表:%d,第三子表:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
			//	WriteToLog(str);

				//算出的数大于
				if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
				{
			//		WriteToLog("加表底大于等于原底数");
					return  m_RetuenValue;
				}
				
			//	WriteToLog("加表底小于原底数");
		  	    
				m_RetuenValue          = - 1;
				m_QuickReadModuleValue = - 1;
				
			}
			else
			{
				//61,62,63协议485的才有快速读表,读出的二个打包的值,前7位为功率因素，后勤14位为有功电度,61,62
				long  m_TmepQuickReadModuleValue =  long(m_RetuenValue*10);
				m_tempvalue                      =  (m_TmepQuickReadModuleValue%(int(pow((double)2,14)))) * 0.1;
				float m_TempGlys                 =  (m_TmepQuickReadModuleValue/(int(pow((double)2,14)))) * 0.01;
				
				if(m_tempvalue <= 999.8  &&  m_TempGlys <= 1)
				{
					
					//m_QuickReadParameter[0] 最新有功电度读表值
					//m_QuickReadParameter[1] 有功电度底值
					//m_QuickReadParameter[2] 3200的倍数,直接算出值

					m_RetuenValue = long(m_QuickReadParameter[0] + 0.001)/1000*1000 + m_tempvalue;
					
					//算出的数大于或等于合理的话
					if(m_RetuenValue  >= m_QuickReadParameter[0])
					{
						//存61、62协议485表快速读表的功率因素 
						if(ModuleNum/100 < 20000)
						{
							m_QuickGlys[ModuleNum/100 - 1] = m_TempGlys;
						}
						
						return  m_RetuenValue;
					}
					
				}
				
				m_RetuenValue          = - 1;
			}
			
		}
		else
		{
			//读过此表，模块不支持此指点令
			m_QuickReadModuleValue     =   m_RetuenValue;
			m_QuickModuleAddress       =       ModuleNum;//快速读表的地址
		}
		
		
	}
	else
	{

		//1-12为脉冲表
		if(ModuleNum%100 <= 12 && m_RetuenValue > 0  && !m_AmmeterType.IsEmpty())
		{
			//默认脉冲率为3200，得折算值
			m_RetuenValue = m_RetuenValue* 3200.00/GetAmmeterImpulse(m_AmmeterType);
		}

	}
	
	//改回外触发状态
	AI_9111_Config(card,TRIG_EXT_STROBE,0,0);

    TmpOnlyOneThreadRun.SetEvent();

	return m_RetuenValue;
}


//星角变全采六通道解码,解6次－－－－－读表协议
double CIFRMView::DecodeSixChannel(long ModuleNum,BYTE Protocol,BYTE Item,BYTE m_phase)
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
	int i;
	for( i = 0; i < 6000;i ++)
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

	//存数据
	/*
	CFile   file;
	
	if(file.Open("c:\\tdata.txt",CFile::modeWrite | CFile::modeCreate))
	{			
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
	}
	*/
	//存数据

	//测试三相电压电流,从三相中找匹配值最大的结果
	for(int m_PhaseTest = 0; m_PhaseTest < 3; m_PhaseTest ++)
	{
		int i;
		//初始化过0点坐标
		for( i = 0; i < 1500; i ++)
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
				
				/*
				if(m_PhaseTest == 2)
				{
					str.Format("m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,相差:%d",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
					WriteToLog(str);
				}
				*/
				
				/*
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 10)
				{	
				
					str.Format("【电压过零点计算错误:m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,相差:%d】",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
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
		
		/**/
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
			
		}
	
	
				
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

	//	signstr.Format("位置：%d,值：%.2f",jj + 1,m_ppvalue);
	//	WriteToLog(signstr);
	}


//  signstr.Format("模块号：%d,相别：%d,第%d个波,角度：%d度,匹配位置：%d,匹配和值：%.2f，均值：%.2f",ModuleNum,m_pipeiplace/(3*m_maxpptimes),(m_pipeiplace%m_maxpptimes) + 1,5*int(pow((double)2,((m_pipeiplace%(3*m_maxpptimes))/m_maxpptimes))),m_pipeiplace,m_maxppvalue,float(m_maxppvalue/m_ByteRecords));
//  WriteToLog(signstr);
//	AfxMessageBox(signstr);


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

		/*
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
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow((double)2,m_ttts-1-jjj));
					
					}
				
				}

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\n十六进制为:"+ signstr + "\r\n");
		
				
		}
		*/
		
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
					dataValue = dataValue + double(TempSignalBit[10 + i]*pow((double)2,i));
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
		 if(DecodeBCH63394(TempSignalBit,FALSE))//纠码对的话
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
			 
			 //16进制解码
			 dataValue   =     0.00;
			 m_sums      =        0;
			 
			 //7位一检验和
			 for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			 {
				 
				 //数据位变成字节,7位一检验和 
				 for( i = 0;i < 7; i ++)
				 {  	
					 
					 m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow((double)2,6-i));
					 
				 }
				 
			 }
			 
			 //如果检验和对的话
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
				 
				 //算出值
				 for( i = 0; i < 21; i++)
				 {
					 dataValue = dataValue + double(SignalBit[18 + i]*pow((double)2,20-i));
				 }	
				 
				 if(SignalBit[38] == 1)
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
							 
						//	 CString ssss;
						//	 ssss.Format("读表值 = %f",dataValue/10);
						//	 WriteToLog(ssss);

							 //除以10
							 return dataValue/10;
						 }
						 
						 
					 }
					 
					 
				 }
				 
				 
			 }
			 
			 //检验和不对
			 dataValue =  -1;
			 
			 //str.Format("前校验和(0x)%0x,后校验和(0x)%0x,校验和不对！",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
			 //WriteToLog(str);
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
		 if(DecodeBCH63394(TempSignalBit,TRUE))
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
				 dataValue = dataValue + Signal[i] * 100000.00/pow((double)10,i);
				 
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
				 //只有485表才有电表故障,485电表通讯错误
				 return  -2;			
			 }
			 else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
			 {
				 //只有485表才有电表故障,电表故障2
				 return  -3;
			 }
			 else if(Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			 {
				 //读驻留时模块没有收到过驻留命令回的数
				 return  -4;
			 }	
			 else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			 {   
				 
				 //检验和
				 if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
				 {
					
				//	 WriteToLog("[检验和对]");

					 //485表为0不正常
					 if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
					 {	
						
					//	 CString                         ssss;
					//	 ssss.Format("读表值 = %f",dataValue);
					//	 WriteToLog(ssss);

						 return  -2;
					 }					 
					 
					 return  dataValue;
					 
				 }
				 
			//	 WriteToLog("[检验和不对]");
				 
				 return   -1;
				 
			 }
			 
			 return   -1;
			 
		 }
		 
	 }
	 
	 return dataValue;
}


//采集六通道相关性检验
double CIFRMView::CorrelationSixChannelCheck(long SourceArray[], long DestArray[],int K)
{
    double           A,B,C,Pxy,sums;
	int                           i;
   	A = B = C = Pxy = sums =  0.000;
	
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


//找过0点的位置,找10个点,有一半为负的话,先5个负,后5个正,k个点
int CIFRMView::FindZeroPoint(short m_CollectData[],int m_StartPlace,int k)
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

	return  m_dots;
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

void CIFRMView::OnWugongparameter() 
{
	CWuGongDlg  dlg;
	dlg.DoModal();	
}


//处理无功补偿表补偿操作
void CIFRMView::WuGongDeal(CString ConStr)
{
	BYTE    LineNo           =        0;//线  号
	BYTE    PhaseNo          =        0;//相  别
	BYTE    StationNo        =        0;//手拉手变电站编码
	BYTE    MotherLine       =        0;//母线编号
	long    ModuleNo         =        0;//模块号
	long    Records          =        0;//记表项数
	double  CurrentValue     =        0;//开始读模块数据
	long    GetModuleNo      =        0;//中间变量
	long    fields           =        0;//记录数
	BYTE    m_AMMETERKIND    =        0;//表计种类
	BYTE    m_SUPPLYMODED    =        0;//供电方式 0-单边供电 1－站手拉手 2-线手拉手供电
	BYTE    m_PROTOCOL       =        0;//读表协议 71-73 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
    BYTE    m_SendAngle      =        0;//发送的角度 2005-04-07加 
	float   m_BeginValue     =        0;//电表初值 
	BYTE    BakMotherLine    =        0;//备用母线编号
	BYTE    BakLineNo        =        0;//备用线  号
	CString           m_ReadAmmeterType;//读表类型 	
	m_StartRead              =     TRUE;//读停标志  
	BYTE                         orders;//无功补偿指令
	CString             strSql,str,strValue;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	m_ListRows               =        0; 
	CString                 CondtionStr;
	int                   READTIMES = 3;
	float                    m_Q,m_WGGL;//m_Q 功率因素，无功功率
	int                     m_QSUMS = 0;//电容量容量
	double         m_UpValue,m_DownValue;
    m_UpValue                =      0.8;
    m_DownValue              =      0.3;
	short           m_dokind =        0;//0 不做 1 投  2切
    double   	    m_Bvalue =        0;//(无功功率*倍数)/电容量容量; 
	double          m_Multiple =      0;//倍数
	short           m_RunStatus  =    0;//运行状态 

	StatusStrRead = StatusStr;
    CString                  WGFileName;
	//条件范围
	ConStr.TrimLeft();
	ConStr.TrimRight();
	
	//删除原来的数
	//m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13列
	
	StatusStr.Format("正在进行无功补偿表操作，请稍侯...");
    SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(TRUE);
	
	//如果DIALOGBAR可见的话则隐藏
	SendMessage(WM_EVENT, 6, 0);
	
	//如果是想读全部数据
	if(ConStr == "ALL")
	{
		CondtionStr = " USER_AMMETERKIND=5";
	}
	else
	{
		CondtionStr = "(" + ConStr + ") AND USER_AMMETERKIND=5";
	}
	
   	//打开数据库
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
		int i;
		//写列表标题
//		SendMessage(WM_EVENT, 2, 0);

		strSql      = "SELECT COUNT(*)  FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		fields   =  atoi(strValue);
		rs.Close();

		//如果没有记录的话
		if(fields < 1)
		{
            db.Close();
			//状态栏信息
			StatusStr = "【无功补偿操作结束】";
            SendMessage(WM_EVENT, 1, 0);
            //隐藏滚动条
//			ShowProgressCtrl(FALSE);
//			m_StartRead   =   FALSE;
			return;
		}
		
		CTime timet = CTime::GetCurrentTime();
		WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
		str.Format("【%4d-%02d-%02d %02d:%02d:%02d】无功补偿检测\r\n",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
		FILE *text;
		if((text = fopen(WGFileName,"a")) != NULL)
		{	
			fputs(str,text);		
			fclose(text);
		}
		
		strSql      = "SELECT WGUPDOWN_UP,WGUPDOWN_DOWN FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);
			m_UpValue       =     atof(strValue)/100.00;
			rs.GetFieldValue((short)1,strValue);
			m_DownValue     =     atof(strValue)/100.00;
		}	
		
		rs.Close();

		strSql      = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO,USER_MULTIPLE,USER_RUNSTATUS,b.WUGONG_SPACE FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);

		//得到字段个数
		short nFields = rs.GetODBCFieldCount();
		rs.Close();	
		
		//滚动条范围
		SetProgressCtrlRange(0, fields,1);
		//打开数据库数据
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		for(int j = 0;j < fields; j ++)
		{
			
			//赋原始值
			CurrentValue = -1;
			
			//如果按了停止按钮
			if(!m_StartRead)
			{	
				
				if(rs.IsOpen())
				{
					rs.Close();
				}
				
				if(db.IsOpen())
				{
					db.Close();
				}
				
				//显示状态栏信息
				StatusStr = "【读数中途被停止】";
				SendMessage(WM_EVENT, 1, 0);
				
				//隐藏滚动条
				ShowProgressCtrl(FALSE);
				return;
			}
			
			//序号
			strValue.Format("%d",m_ListRows + 1);
			m_StrArray[0].Format("%5s",strValue);
			
			//提示指令
			m_StrArray[1] =  "无功读表";
			
			//读出字段的名称开始
			for( i = 0; i < nFields; i++)
			{
				rs.GetFieldValue(int(i),strValue);

				strValue.TrimLeft();
				strValue.TrimRight();

				switch(i)
				{
				case 0:
					{
						//姓名
						m_StrArray[2] = strValue;
						break;
					}
				case 1:
					{ 
						//用户编号  
						m_StrArray[3] = strValue;
						break;
					}
				case 2:
					{ 
						//住址  
						m_StrArray[4] = strValue;
						break;
					}
				case 3:
					{  
						//模块号
						m_StrArray[5].Format("%8s",strValue);
						ModuleNo = atol(strValue);
						break;
					}
				case 4:
					{  
						//电表号
						m_StrArray[6].Format("%8s",strValue);
						break;
					}
				case 5:
					{  
						//母线号
						MotherLine = atoi(strValue); //add by 2004.10.21
						break;
					}
				case 6:
					{	
						//线路名称
						m_StrArray[7] = strValue;
						break;
					}
				case 7:
					{
						//线路编号
						LineNo = atoi(strValue);
						break;
					}
				case 8:
					{
						CString         PhaseStr;
						//相
						switch(atoi(strValue))
						{
						case 0:
							{
								PhaseStr = "A相";
								PhaseNo = 0;
								break;
							}
						case 1:
							{
								PhaseStr = "B相";
								PhaseNo = 1;
								break;
							}
						case 2:
							{
								PhaseStr = "C相";
								PhaseNo = 2;
								break;
							}
						default:
							{
								PhaseStr = "未知";
								PhaseNo = atoi(strValue);
								break;
							}
						}

						m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
						break;
					}
				case 9:
					{
						//变台名称
						m_StrArray[9].Format("%s",strValue);
						break;
					}
				case 10:
					{
						//手拉手电站码
						StationNo    = m_handno;
						//电表初值
						m_BeginValue = float(atof(strValue));
						break;
					}
				case 11:
					{
						//表计种类
						m_AMMETERKIND = atoi(strValue);
						break;
					}
				case 12:
					{
						//供电方式
						m_SUPPLYMODED = atoi(strValue);
						break;
					}	
				case 13:
					{
						//读表协议 31-39或71-79 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
						m_PROTOCOL    = atoi(strValue);
						orders        =           0x48;
						
						switch(m_PROTOCOL)
						{
						case 61:
							{
								
							}
						case 62:
							{
								orders = 0x03;
								break;
							}
						case 71:
							{
								
							}
						case 72:
							{
								
							}
						case 73:
							{
								orders = 0x48;
								break;
							}
						}
						
						m_StrArray[8] = m_StrArray[8] + strValue + "]";
						break;
					}	
				case 14:
					{
						//读表的角度,是否是星角连接,偏移角度,星角为30度
						if(IsDyConnect(m_StrArray[9]))
						{
							m_SendAngle = 6;
						}
						else
						{
							m_SendAngle = 0;
						}
						
						break;
					}
				case 15:
					{
						//读表的类型
						m_ReadAmmeterType = strValue;
						break;
					}	
				case 16:
					{
						//备用母线编号
						BakMotherLine = atoi(strValue);
						break;
					}	
				case 17:
					{
						//备用出线号
						BakLineNo     = atoi(strValue);
						break;
					}
				case 18:
					{
						//倍率
						m_Multiple     = atof(strValue);
						break;
					}	
				case 19:
					{
						//投切状态
						m_RunStatus    = atoi(strValue);
						break;
					}
				case 20:
					{
						//电容器容量
						m_QSUMS       = atoi(strValue);
						break;
					}
					
				 }
				 
              }			 
			  //读出字段的名称结束
			
			  CurrentValue =   -1;

			  //读表READTIMES次
			  for(int m_readtimes = 0; m_readtimes < READTIMES; m_readtimes ++)
			  {

				  if(int(CurrentValue) != -1)
				  {
					  break;
				  }

				  //显示状态栏信息
				  StatusStr.Format("正在第[%d]次操作无功补偿[%d(%d-%d)]完成%.2f％,稍侯...",m_readtimes + 1,ModuleNo,fields,m_ListRows + 1,float(m_ListRows)*100/fields);
				  SendMessage(WM_EVENT, 1, 0);	


				  //不知道是哪相的话,每个相都测试一次
				  if(PhaseNo > 2)
				  {				  
					  SurrenderWindowMessage();

					  //相循环
					  for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
					  { 
						  
						  if(int(CurrentValue) != -1)
						  {
							  break;
						  }

						  SurrenderWindowMessage();

						  //如果按了停止按钮
						  if(m_StartRead == FALSE)
						  {
							  break;
						  }
						  
						  switch(PhaseNo)
						  {
						  case 0:
							  {	
								  strValue.Format("正在%s,测试模块号(%d)A相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 1:
							  {
								  strValue.Format("正在%s,测试模块号(%d)B相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 2:
							  {
								  strValue.Format("正在%s,测试模块号(%d)C相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  }
						  
						  //显示状态栏信息
						  StatusStr =        strValue;
						  SendMessage(WM_EVENT, 1, 0);
						  
						  if(m_SendAngle == 0)
						  {
							  CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  else
						  {
							  //星角变读表,下发命令读数,下发命令读数,读一个实时的数
							  CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  
						  //分析结果是否合理
						  if(CurrentValue >= 0)
						  {
							  
							  if((m_PROTOCOL/10) == 6)
							  {
								  //61,62的协议
								  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
								  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
									  
							  }
							  else  if((m_PROTOCOL/10) == 7)
							  {
								  
								  //71,72的协议
								  m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //功率因素
								  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //无功功率
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
								  
							  }
							  
						  }
						  
						  SurrenderWindowMessage();
						  
						  //如果是线手拉手，再读一次数据
						  if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
						  {
							  
							  if(m_SendAngle == 0)
							  {
								  CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
							  else
							  {
								  //星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
								  CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
													  
							  //分析结果是否合理
							  if(CurrentValue >= 0)
							  {
								  
								  if((m_PROTOCOL/10) == 6)
								  {
									  //61,62的协议
									  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
									  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }
										  
								  }
								  else  if((m_PROTOCOL/10) == 7)
								  {
									  
									  //71,72的协议
									  m_Q     =   (int(CurrentValue*100)/10000)*0.001;   //功率因素
									  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;   //无功功率
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }

								  }
								  
							  }

						  }
							  
						  SurrenderWindowMessage();
						  
						  //如果读出的值大于或等于0	
						  if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
						  {
							  
							  //相
							  switch(PhaseNo)
							  {
							  case 0:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A相",m_PROTOCOL);
									  break;
								  }
							  case 1:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B相",m_PROTOCOL);
									  break;
								  }
							  case 2:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C相",m_PROTOCOL);
									  break;
								  }
							  }
							  
							  //保存入数据库
							  strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO= %d",PhaseNo,ModuleNo);
							  //运行SQL语句
							  CDataBaseInstance::ExecuteDataBaseSQL(strValue); 
							  break;
							  
						  }
							  

                     }
			 					  
					  
				}
				else
				{
					//知道该相就读该相
					CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*母线*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						
					//分析结果是否合理
					if(CurrentValue >= 0)
					{
						
						if((m_PROTOCOL/10) == 6)
						{
							//61,62的协议
							m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
							m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						else  if((m_PROTOCOL/10) == 7)
						{
							
							//71,72的协议
							m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //功率因素
							m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //无功功率
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						
					}
					
					SurrenderWindowMessage();
									
					//如果是线手拉手，再读一次数据
					if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
					{
						
						if(m_SendAngle == 0)
						{
							CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						else
						{
							//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
							CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						
						//分析结果是否合理
						if(CurrentValue >= 0)
						{
							
							if((m_PROTOCOL/10) == 6)
							{
								//61,62的协议
								m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
								m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{	
									MotherLine  =  BakMotherLine;//备用母线编号
	                                LineNo      =   BakLineNo;   //备用线号
									break;
								}
								
							}
							else  if((m_PROTOCOL/10) == 7)
							{
								
								//71,72的协议
								m_Q     =   (int(CurrentValue*100)/10000)*0.001;         //功率因素
								m_WGGL  =   (int(CurrentValue*100)%10000)*0.01;          //无功功率
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{
									MotherLine  =  BakMotherLine;//备用母线编号
	                                LineNo      =   BakLineNo;   //备用线号
									break;
								}
								
							}
							
						}
						
						SurrenderWindowMessage();

						//如果在备用母线和备用出线上读出来
						if(int(CurrentValue) != -1)
						{
							switch(PhaseNo)
							{
							case 0:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A相",m_PROTOCOL);
									break;
								}
							case 1:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B相",m_PROTOCOL);
									break;
								}
							case 2:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C相",m_PROTOCOL);
									break;
								}
							}
							
						}
						
					}
					
				}
			
            }
				
			//根据得到的值下结论
			if(int(CurrentValue) == -1)
			{	
				//用户库下滑一个记录
				rs.MoveNext();
				//继续向上执行
				continue;
			}
				
			Beep(5000,400); 
			
			//根据得到的值下结论
			if(CurrentValue >= 0 )
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("成功");
				strValue.Format("Q(%.2f),QG(%.2f)",m_Q,m_WGGL);
				m_StrArray[11]  =  strValue;
			}
			else
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("未成功");
				
				//回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好
				if(int(CurrentValue) == -2)
				{	
					//正确的话
					m_StrArray[11] = "故障1 ";
				}

				if(int(CurrentValue) == -3)
				{
					//正确的话
					m_StrArray[11] = "故障2 ";
				}					
				
			}
			
			//时间
			CTime timet = CTime::GetCurrentTime();	
			m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			
			//显示结果列表
			for( i = 0; i < 13; i++)
			{		
				m_StrArray[i].TrimLeft();
				m_StrArray[i].TrimRight();
				
				//数据格式对齐
				if(i == 0)
				{
					//序号
					if(m_StrArray[i].GetLength() < 5)
					{
						
						strValue = m_StrArray[i];
						m_StrArray[i].Format("%5s",strValue);

					}
					
				}
				else if( i == 5)
				{   
					//模块号 
					if(m_StrArray[i].GetLength() < 8)
					{

						strValue = m_StrArray[i];
						m_StrArray[i].Format("%8s",strValue);

					}
					
				}
				else if( i == 11)
				{   
					//读数的值
					if(m_StrArray[i].GetLength() < 12)
					{

						strValue = m_StrArray[i];
						m_StrArray[i].Format("%12s",strValue);

					}
					
				}
				
				DataStr = DataStr + ";" + m_StrArray[i];
			}
			
			//显示列表数据
			SendMessage(WM_EVENT, 3, 0);

			SurrenderWindowMessage();			
		
			//如果值为正
			if(CurrentValue >= 0 && m_StartRead)
			{
				//m_dokind   0 不做 1 投  2 切
				//61,62 送电 0x04  停电  0x05
                //71,72 送电 0xf6  停电  0xf8
                m_dokind =   0;
				
                if(m_QSUMS > 0)
				{
					
					m_Bvalue  = (m_WGGL*m_Multiple)/m_QSUMS;//(m_WGGL*倍数)/m_QSUMS; 
					
					//大于上限 1 投
					if(m_Bvalue >= m_UpValue)
					{
                        m_dokind =   1;
					}
					
					//小于下限 2 切
					if(m_Bvalue <= m_DownValue)
					{
                        m_dokind =   2;
					}
					
                }

				//要送不在送电状态,要停不在停电状态	 m_RunStatus  0 运行  1  停电
				if(((m_dokind == 1  && m_RunStatus != 0)  || (m_dokind == 2 && m_RunStatus != 1)) && (m_dokind > 0))
				{
					
					//分析是否投切,	投3次
					for(int yyy = 0; yyy < READTIMES; yyy ++)
					{
						
						SurrenderWindowMessage();
						
						if(m_dokind == 1)
						{
							//显示状态栏信息
							StatusStr.Format("正在第[%d]次对无功补偿模块[%d]投操作完成,稍侯...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);	
							
							if(m_PROTOCOL/10 == 6  && m_StartRead)
							{
								//送电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x04,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//送电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf6,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						else
						{
							//显示状态栏信息
							StatusStr.Format("正在第[%d]次对无功补偿模块[%d]切操作完成,稍侯...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);
							
							if(m_PROTOCOL/10 == 6  &&  m_StartRead)
							{
								//停电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x05,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//停电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf8,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						
						//如果返回成功
						if(int(CurrentValue) > 0)
						{
						
						 	CTime timet = CTime::GetCurrentTime();

							//修改送电、停电状态
							if(m_dokind == 1)
							{
								m_StrArray[1]  =  "无功投操作";	
								m_StrArray[10] =  "投成功";
								//送电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_DESCRIBE = '%s' WHERE USER_MODULENO= %d","无功补偿送电",ModuleNo);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("【%4d-%02d-%02d %02d:%02d:%02d】模块：%d    操作:无功补偿送电\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
															
							}
							else
							{
								m_StrArray[1]  =  "无功切操作";
								m_StrArray[10] =  "切成功";
								//停电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_DESCRIBE = '%s' WHERE USER_MODULENO=%d","无功补偿停电",ModuleNo);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("【%4d-%02d-%02d %02d:%02d:%02d】模块：%d    操作:无功补偿停电\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}	
							
							
							WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
						
							FILE *text;
							if((text = fopen(WGFileName,"a")) != NULL)
							{	
								fputs(str,text);		
								fclose(text);
							}

							SendMessage(WM_EVENT, 19, 0);
							Beep(5000,400);						
							break;

						}
						
					}
					
				}
				////////////////

			}

			SetProgressCtrlSetIt();

			//行号自加
			m_ListRows++;
			
			//用户库下滑一个记录
			rs.MoveNext();
			
		}
		  
	    //关闭数据库
	    if(rs.IsOpen())
		{
		   rs.Close();
		}
	  
	    //循环次数结束 
	    if(db.IsOpen())
		{
		   db.Close();
		}
		  
    }
	  
	//状态栏信息为空
	StatusStr = StatusStrRead;
	SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(FALSE);
//	m_StartRead    =  FALSE;
	  
}

//所有的无功表处理一次
void CIFRMView::ALLWuGongDeal()
{	
	//演示版
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE    LineNo           =        0;//线  号
	BYTE    PhaseNo          =        0;//相  别
	BYTE    StationNo        =        0;//手拉手变电站编码
	BYTE    MotherLine       =        0;//母线编号
	long    ModuleNo         =        0;//模块号
	long    Records          =        0;//记表项数
	double  CurrentValue     =        0;//开始读模块数据
	long    GetModuleNo      =        0;//中间变量
	long    fields           =        0;//记录数
	BYTE    m_AMMETERKIND    =        0;//表计种类
	BYTE    m_SUPPLYMODED    =        0;//供电方式 0-单边供电 1－站手拉手 2-线手拉手供电
	BYTE    m_PROTOCOL       =        0;//读表协议 71-73 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
    BYTE    m_SendAngle      =        0;//发送的角度 2005-04-07加 
	float   m_BeginValue     =        0;//电表初值 
	BYTE    BakMotherLine    =        0;//备用母线编号
	BYTE    BakLineNo        =        0;//备用线  号
	CString           m_ReadAmmeterType;//读表类型 	
	m_StartRead              =     TRUE;//读停标志  
	BYTE                         orders;//无功补偿指令
	CString         strSql,strValue,str;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	CString                 CondtionStr;
	int                   READTIMES = 3;
	float                    m_Q,m_WGGL;//m_Q 功率因素，无功功率
	int                     m_QSUMS = 0;//电容量容量
	double         m_UpValue,m_DownValue;
    m_UpValue                =      0.8;
    m_DownValue              =      0.3;
	short           m_dokind =        0;//0 不做 1 投  2切
    double   	    m_Bvalue =        0;//(无功功率*倍数)/电容量容量; 
	double          m_Multiple =      0;//倍数
	short           m_RunStatus  =    0;//运行状态 
	CString                  WGFileName;
		
	//删除原来的数
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13列
	
	StatusStr.Format("正在进行无功补偿表操作，请稍侯...");
    SendMessage(WM_EVENT, 1, 0);
	
	//如果DIALOGBAR可见的话则隐藏
	SendMessage(WM_EVENT, 6, 0);
	
	//如果是想读全部数据
	CondtionStr = " USER_AMMETERKIND=5";
	
   	//打开数据库
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);


		strSql      = "SELECT COUNT(*)  FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		fields   =  atoi(strValue);
		rs.Close();

		//如果没有记录的话
		if(fields < 1)
		{
            db.Close();
			//状态栏信息
			StatusStr = "  ";
            SendMessage(WM_EVENT, 1, 0);
           	return;
		}
		
		CTime timet = CTime::GetCurrentTime();
		str.Format("【%4d-%02d-%02d %02d:%02d:%02d】无功补偿检测\r\n",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
		WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
		
		FILE *text;
		if((text = fopen(WGFileName,"a")) != NULL)
		{	
			fputs(str,text);		
			fclose(text);
		}

		strSql      = "SELECT WGUPDOWN_UP,WGUPDOWN_DOWN FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);
			m_UpValue       =     atof(strValue)/100.00;
			rs.GetFieldValue((short)1,strValue);
			m_DownValue     =     atof(strValue)/100.00;
		}	
		
		rs.Close();

		strSql      = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO,USER_MULTIPLE,USER_RUNSTATUS,b.WUGONG_SPACE FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);

		//得到字段个数
		short nFields = rs.GetODBCFieldCount();
		rs.Close();	

		//打开数据库数据
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		for(int j = 0;j < fields; j ++)
		{
			
			//赋原始值
			CurrentValue = -1;
			
			//如果按了停止按钮
			if(!m_StartRead)
			{	
				
				if(rs.IsOpen())
				{
					rs.Close();
				}
				
				if(db.IsOpen())
				{
					db.Close();
				}
				
				//显示状态栏信息
				StatusStr = "【读数中途被停止】";
				SendMessage(WM_EVENT, 1, 0);
				return;
			}
			
			//序号
			m_StrArray[0].Format(" ");
			
			//提示指令
			m_StrArray[1] =  "无功读表";
			
			//读出字段的名称开始
			for(int i = 0; i < nFields; i++)
			{
				rs.GetFieldValue(int(i),strValue);

				strValue.TrimLeft();
				strValue.TrimRight();

				switch(i)
				{
				case 0:
					{
						//姓名
						m_StrArray[2] = strValue;
						break;
					}
				case 1:
					{ 
						//用户编号  
						m_StrArray[3] = strValue;
						break;
					}
				case 2:
					{ 
						//住址  
						m_StrArray[4] = strValue;
						break;
					}
				case 3:
					{  
						//模块号
						m_StrArray[5].Format("%8s",strValue);
						ModuleNo = atol(strValue);
						break;
					}
				case 4:
					{  
						//电表号
						m_StrArray[6].Format("%8s",strValue);
						break;
					}
				case 5:
					{  
						//母线号
						MotherLine = atoi(strValue); //add by 2004.10.21
						break;
					}
				case 6:
					{	
						//线路名称
						m_StrArray[7] = strValue;
						break;
					}
				case 7:
					{
						//线路编号
						LineNo = atoi(strValue);
						break;
					}
				case 8:
					{
						CString         PhaseStr;
						//相
						switch(atoi(strValue))
						{
						case 0:
							{
								PhaseStr = "A相";
								PhaseNo = 0;
								break;
							}
						case 1:
							{
								PhaseStr = "B相";
								PhaseNo = 1;
								break;
							}
						case 2:
							{
								PhaseStr = "C相";
								PhaseNo = 2;
								break;
							}
						default:
							{
								PhaseStr = "未知";
								PhaseNo = atoi(strValue);
								break;
							}
						}

						m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
						break;
					}
				case 9:
					{
						//变台名称
						m_StrArray[9].Format("%s",strValue);
						break;
					}
				case 10:
					{
						//手拉手电站码
						StationNo    = m_handno;
						//电表初值
						m_BeginValue = float(atof(strValue));
						break;
					}
				case 11:
					{
						//表计种类
						m_AMMETERKIND = atoi(strValue);
						break;
					}
				case 12:
					{
						//供电方式
						m_SUPPLYMODED = atoi(strValue);
						break;
					}	
				case 13:
					{
						//读表协议 31-39或71-79 意义[十位:3-各校验 7-BCH校验 个位:叠加次数]
						m_PROTOCOL    = atoi(strValue);
						orders        =           0x48;
						
						switch(m_PROTOCOL)
						{
						case 61:
							{
								
							}
						case 62:
							{
								orders = 0x03;
								break;
							}
						case 71:
							{
								
							}
						case 72:
							{
								
							}
						case 73:
							{
								orders = 0x48;
								break;
							}
						}
						
						m_StrArray[8] = m_StrArray[8] + strValue + "]";
						break;
					}	
				case 14:
					{
						//读表的角度,是否是星角连接,偏移角度,星角为30度
						if(IsDyConnect(m_StrArray[9]))
						{
							m_SendAngle = 6;
						}
						else
						{
							m_SendAngle = 0;
						}
						
						break;
					}
				case 15:
					{
						//读表的类型
						m_ReadAmmeterType = strValue;
						break;
					}	
				case 16:
					{
						//备用母线编号
						BakMotherLine = atoi(strValue);
						break;
					}	
				case 17:
					{
						//备用出线号
						BakLineNo     = atoi(strValue);
						break;
					}
				case 18:
					{
						//倍率
						m_Multiple     = atof(strValue);
						break;
					}	
				case 19:
					{
						//投切状态
						m_RunStatus    = atoi(strValue);
						break;
					}
				case 20:
					{
						//电容器容量
						m_QSUMS       = atoi(strValue);
						break;
					}
					
				 }
				 
              }			 
			  //读出字段的名称结束
			
			  CurrentValue =   -1;

			  //读表READTIMES次
			  for(int m_readtimes = 0; m_readtimes < READTIMES; m_readtimes ++)
			  {

				  if(int(CurrentValue) != -1)
				  {
					  break;
				  }

				  //显示状态栏信息
				  StatusStr.Format("正在第[%d]次操作无功补偿[%d],请稍侯...",m_readtimes + 1,ModuleNo);
				  SendMessage(WM_EVENT, 1, 0);	


				  //不知道是哪相的话,每个相都测试一次
				  if(PhaseNo > 2)
				  {				  
					  SurrenderWindowMessage();

					  //相循环
					  for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
					  { 
						  
						  if(int(CurrentValue) != -1)
						  {
							  break;
						  }

						  SurrenderWindowMessage();

						  //如果按了停止按钮
						  if(m_StartRead == FALSE)
						  {
							  break;
						  }
						  
						  switch(PhaseNo)
						  {
						  case 0:
							  {	
								  strValue.Format("正在%s,测试模块号(%d)A相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 1:
							  {
								  strValue.Format("正在%s,测试模块号(%d)B相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 2:
							  {
								  strValue.Format("正在%s,测试模块号(%d)C相,请稍侯...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  }
						  
						  //显示状态栏信息
						  StatusStr =        strValue;
						  SendMessage(WM_EVENT, 1, 0);
						  
						  if(m_SendAngle == 0)
						  {
							  CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  else
						  {
							  //星角变读表,下发命令读数,下发命令读数,读一个实时的数
							  CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  
						  //分析结果是否合理
						  if(CurrentValue >= 0)
						  {
							  
							  if((m_PROTOCOL/10) == 6)
							  {
								  //61,62的协议
								  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
								  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
									  
							  }
							  else  if((m_PROTOCOL/10) == 7)
							  {
								  
								  //71,72的协议
								  m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //功率因素
								  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //无功功率
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
								  
							  }
							  
						  }
						  
						  SurrenderWindowMessage();
						  
						  //如果是线手拉手，再读一次数据
						  if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
						  {
							  
							  if(m_SendAngle == 0)
							  {
								  CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
							  else
							  {
								  //星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
								  CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
													  
							  //分析结果是否合理
							  if(CurrentValue >= 0)
							  {
								  
								  if((m_PROTOCOL/10) == 6)
								  {
									  //61,62的协议
									  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
									  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }
										  
								  }
								  else  if((m_PROTOCOL/10) == 7)
								  {
									  
									  //71,72的协议
									  m_Q     =   (int(CurrentValue*100)/10000)*0.001;   //功率因素
									  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;   //无功功率
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }

								  }
								  
							  }

						  }
							  
						  SurrenderWindowMessage();
						  
						  //如果读出的值大于或等于0	
						  if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
						  {
							  
							  //相
							  switch(PhaseNo)
							  {
							  case 0:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A相",m_PROTOCOL);
									  break;
								  }
							  case 1:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B相",m_PROTOCOL);
									  break;
								  }
							  case 2:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C相",m_PROTOCOL);
									  break;
								  }
							  }
							  
							  //保存入数据库
							  strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO= %d",PhaseNo,ModuleNo);
							  //运行SQL语句
							  CDataBaseInstance::ExecuteDataBaseSQL(strValue); 
							  break;
							  
						  }
							  

                     }
			 					  
					  
				}
				else
				{
					//知道该相就读该相
					CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*母线*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						
					//分析结果是否合理
					if(CurrentValue >= 0)
					{
						
						if((m_PROTOCOL/10) == 6)
						{
							//61,62的协议
							m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
							m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						else  if((m_PROTOCOL/10) == 7)
						{
							
							//71,72的协议
							m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //功率因素
							m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //无功功率
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						
					}
					
					SurrenderWindowMessage();
									
					//如果是线手拉手，再读一次数据
					if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
					{
						
						if(m_SendAngle == 0)
						{
							CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						else
						{
							//星角变读表,下发命令读数,下发命令读数,读一个实时的数，值为－4没有收到过驻留,再读一次
							CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						
						//分析结果是否合理
						if(CurrentValue >= 0)
						{
							
							if((m_PROTOCOL/10) == 6)
							{
								//61,62的协议
								m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//功率因素
								m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //无功功率
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{	
									MotherLine  =  BakMotherLine;//备用母线编号
	                                LineNo      =   BakLineNo;   //备用线号
									break;
								}
								
							}
							else  if((m_PROTOCOL/10) == 7)
							{
								
								//71,72的协议
								m_Q     =   (int(CurrentValue*100)/10000)*0.001;         //功率因素
								m_WGGL  =   (int(CurrentValue*100)%10000)*0.01;          //无功功率
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{
									MotherLine  =  BakMotherLine;//备用母线编号
	                                LineNo      =   BakLineNo;   //备用线号
									break;
								}
								
							}
							
						}
						
						SurrenderWindowMessage();

						//如果在备用母线和备用出线上读出来
						if(int(CurrentValue) != -1)
						{
							switch(PhaseNo)
							{
							case 0:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A相",m_PROTOCOL);
									break;
								}
							case 1:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B相",m_PROTOCOL);
									break;
								}
							case 2:
								{
									m_StrArray[8].Format("[备%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C相",m_PROTOCOL);
									break;
								}
							}
							
						}
						
					}
					
				}
			
            }
				
			//根据得到的值下结论
			if(int(CurrentValue) == -1)
			{	
				//用户库下滑一个记录
				rs.MoveNext();
				//继续向上执行
				continue;
			}
				
			Beep(5000,400); 
			
			//根据得到的值下结论
			if(CurrentValue >= 0 )
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("成功");
				strValue.Format("Q(%.2f),QG(%.2f)",m_Q,m_WGGL);
				m_StrArray[11]  =  strValue;
			}
			else
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("未成功");
				
				//回的值为FEFEFE.FE,电表和模块的数据通讯线没有连好
				if(int(CurrentValue) == -2)
				{	
					//正确的话
					m_StrArray[11] = "故障1 ";
				}

				if(int(CurrentValue) == -3)
				{
					//正确的话
					m_StrArray[11] = "故障2 ";
				}					
				
			}
			
			//时间
			CTime timet = CTime::GetCurrentTime();	
			m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			
			SurrenderWindowMessage();			
		
			//如果值为正
			if(CurrentValue >= 0 )
			{
				//m_dokind   0 不做 1 投  2 切
				//61,62 送电 0x04  停电  0x05
                //71,72 送电 0xf6  停电  0xf8
                m_dokind =   0;
				
                if(m_QSUMS > 0)
				{
					
					m_Bvalue  = (m_WGGL*m_Multiple)/m_QSUMS;//(m_WGGL*倍数)/m_QSUMS; 
					
					//大于上限 1 投
					if(m_Bvalue >= m_UpValue)
					{
                        m_dokind =   1;
					}
					
					//小于下限 2 切
					if(m_Bvalue <= m_DownValue)
					{
                        m_dokind =   2;
					}
					
                }

				//要送不在送电状态,要停不在停电状态	 m_RunStatus  0 运行  1  停电
				if(((m_dokind == 1  && m_RunStatus != 0)  || (m_dokind == 2 && m_RunStatus != 1)) && (m_dokind > 0))
				{
					
					//分析是否投切,	投3次
					for(int yyy = 0; yyy < READTIMES; yyy ++)
					{
						
						SurrenderWindowMessage();
						
						if(m_dokind == 1)
						{
							//显示状态栏信息
							StatusStr.Format("正在第[%d]次对无功补偿模块[%d]投操作完成,稍侯...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);	
							
							if(m_PROTOCOL/10 == 6  && m_StartRead)
							{
								//送电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x04,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//送电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf6,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						else
						{
							//显示状态栏信息
							StatusStr.Format("正在第[%d]次对无功补偿模块[%d]切操作完成,稍侯...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);
							
							if(m_PROTOCOL/10 == 6  &&  m_StartRead)
							{
								//停电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x05,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//停电操作
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf8,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						
						//如果返回成功
						if(int(CurrentValue) > 0)
						{
							
							CTime timet = CTime::GetCurrentTime();

							//修改送电、停电状态
							if(m_dokind == 1)
							{
								//送电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_DESCRIBE = '%s' WHERE USER_MODULENO= %d","无功补偿送电",ModuleNo);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("【%4d-%02d-%02d %02d:%02d:%02d】模块：%d    操作:无功补偿送电\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}
							else
							{
								//停电,保存入数据库
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_DESCRIBE = '%s' WHERE USER_MODULENO=%d","无功补偿停电",ModuleNo);
								//运行SQL语句
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("【%4d-%02d-%02d %02d:%02d:%02d】模块：%d    操作:无功补偿停电\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}

							WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
							
							FILE *text;
							if((text = fopen(WGFileName,"a")) != NULL)
							{	
								fputs(str,text);		
								fclose(text);
							}

							Beep(5000,400);						
							break;

						}
						
					}
					
				}
				////////////////

			}

			//用户库下滑一个记录
			rs.MoveNext();
			
		}
		  
	    //关闭数据库
	    if(rs.IsOpen())
		{
		   rs.Close();
		}
	  
	    //循环次数结束 
	    if(db.IsOpen())
		{
		   db.Close();
		}
		  
    }
	  
	//状态栏信息为空
	StatusStr = "             ";
	SendMessage(WM_EVENT, 1, 0);  
}


void CIFRMView::OnWugongdeal() 
{
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}

    //得到对话条的所选条件
    if(!GetDialogBarStr())
	{
		return;
	}
	
	CMainFrame* pMainFrm =  (CMainFrame*) AfxGetApp()->m_pMainWnd;
	SendContionStr       =  pMainFrm->m_wndMyDialogBar.SelectCondition();
	ReadMeterThread      =  AfxBeginThread(WorkerThread,(LPVOID)15,m_Thread_PRIORITY,0,0,NULL); // 创建并运行
	ReadMeterThread->m_bAutoDelete  =  FALSE;//线程为手动删除
}

void CIFRMView::OnUpdateWugongdeal(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//选择条件
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}	
}

//得到无功的时间间隔
short CIFRMView::GetWGTimeEvery()
{
	CString  strSql,strValue;
	short      m_Result = 0;
	
   	//打开数据库
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);

		strSql      = "SELECT WGUPDOWN_EVERYTIME FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);	
			m_Result        =  atoi(strValue);//无功时间间隔
		}	
		
		rs.Close();
		db.Close();
	}

	return m_Result;

}



void CIFRMView::OnDrfromaccess() 
{	
	//判断是否有程序在运行
	if(CheckRunning())
	{
		return;
	}
	
	char szFilter[]="工频畸变远程抄表报告文件EXCEL文件(*.mdb)|*.mdb|";//USER.mdb
   	CFileDialog dlg(TRUE,"MDB","*.MDB",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	
	if(dlg.DoModal() == IDOK)
	{	

		DrFromAccessFile(dlg.GetPathName());
	
	}	
}


//从外部ACCESS库中数据导入进来
void CIFRMView::DrFromAccessFile(CString m_FileName)
{
	CDaoDatabase             db;	    //数据库
	CDaoTableDefInfo  tableinfo;
	BOOL               bSuccess;
	CFileFind             fFind;
	CDaoRecordset   RecSet(&db);		//记录集
	CString                 str;
	CString              SqlCmd;
	int    index      =       0;
	CStringArray     m_DataName;
    BOOL      m_finding = FALSE;
	int k        =            0;
	
	//查找是否存在此数据库文件USER.mdb
	bSuccess         =  fFind.FindFile(m_FileName);
	fFind.Close();
	
	if(bSuccess)
	{
		
		db.Open(m_FileName, TRUE, FALSE,_T(""));

		//得到表的名称
		while(index < db.GetTableDefCount())
		{
			db.GetTableDefInfo(index,tableinfo,AFX_DAO_ALL_INFO);

			if(!(tableinfo.m_lAttributes & dbSystemObject) && !(tableinfo.m_lAttributes & dbHiddenObject))
			{

				m_DataName.Add(tableinfo.m_strName);
			
			}

			index++;
		}
		
        //找是否有4个表
		for(int index = 0; index < m_DataName.GetSize(); index ++)
		{
		
			if(m_DataName[index].Find("TB_AMMETER") != -1 || m_DataName[index].Find("TB_ELECTRICITY") != -1 ||  m_DataName[index].Find("TB_TRANSFORMER") != -1 ||  m_DataName[index].Find("TB_USER") != -1)
			{
			
				m_finding = TRUE;
			
			}

		}
		
		if(!m_finding)
		{
			db.Close();
			MessageBox("此ACCESS数据表不是工频畸变抄表数据！！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//新建4个临时表
		//1、建TB_AMMETERBAK数据表
		if(IsCurveTableExist("TB_AMMETERBAK"))  //是否存在此表
		{
            SqlCmd.Format("DROP TABLE TB_AMMETERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

	
		SqlCmd = "CREATE TABLE [dbo].[TB_AMMETERBAK] (\
		    [AMMETER_TYPE]         [char] (10) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
		    [AMMETER_MANUFACTURER] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		    [AMMETER_IMPULSE]      [int] NOT NULL ,\
		    [AMMETER_REMARK]       [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
		    ) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		 
		 //2、建TB_ELECTRICITYBAK数据表
		if(IsCurveTableExist("TB_ELECTRICITYBAK"))  //是否存在此表
		{               
            SqlCmd.Format("DROP TABLE TB_ELECTRICITYBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = "	CREATE TABLE [dbo].[TB_ELECTRICITYBAK] (\
				[ELECTRICITY_NO] [tinyint] NOT NULL ,\
				[ELECTRICITY_KIND] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[ELECTRICITY_PRICE] [float] NOT NULL ,\
				[ELECTRICITY_REMARK] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";

         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);

        //3、建TB_TRANSFORMERBAK数据表
		if(IsCurveTableExist("TB_TRANSFORMERBAK"))  //是否存在此表
		{               
            SqlCmd.Format("DROP TABLE TB_TRANSFORMERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = " CREATE TABLE [dbo].[TB_TRANSFORMERBAK] (\
				[TRANSFORMER_NO] [char] (40) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[TRANSFORMER_TYPE] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CAPACITY] [int] NULL ,\
				[TRANSFORMER_INSTALLTIME] [datetime] NULL ,\
				[TRANSFORMER_POSITION] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_OWNERSHIP] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CONNECTFORM] [tinyint] NULL \
				) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		 
		//4、建TB_USERBAK数据表
		if(IsCurveTableExist("TB_USERBAK"))  //是否存在此表
		{               
            SqlCmd.Format("DROP TABLE TB_USERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = " 	CREATE TABLE [dbo].[TB_USERBAK] (\
			[USER_COMPANY] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNO] [char] (5) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MOTHERLINE] [int] NULL ,\
			[USER_BAKMOTHERLINE] [int] NULL ,\
			[USER_LINENO] [int] NULL ,\
			[USER_BAKLINENO] [int] NULL ,\
			[USER_LINENAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TRANSFORMERNO] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MODULENO] [bigint] NULL ,\
			[USER_PHASE] [tinyint] NULL ,\
			[USER_NAME] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_NO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_OLDNO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ADDRESS] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_PHONE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ELECTRICITYKIND] [tinyint] NULL ,\
			[USER_AMMETERNO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_AMMETERKIND] [tinyint] NULL ,\
			[USER_INSTALLTIME] [datetime] NULL ,\
			[USER_SUPPLYMODE] [tinyint] NULL ,\
			[USER_INITIALVALUE] [float] NULL ,\
			[USER_MULTIPLE] [int] NULL ,\
			[USER_PROTOCOL] [tinyint] NULL ,\
			[USER_DESCRIBE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_READLABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TIMELABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ETSTATUS] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_IDNO] [int] NULL ,\
			[USER_AMMETERTYPE] [varchar] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_SENDANGLE] [tinyint] NULL ,\
			[USER_DOWNVALUE] [int] NULL ,\
        	[USER_UPVALUE]   [int] NULL, \
			[USER_RUNSTATUS] [tinyint] NULL,\
			[USER_ZHULABEL] [char] (93) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);

		COleVariant          vars;	
		vars.ChangeType(VT_I4, 0);
		
		//处理TB_AMMETER数据,电表信息
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_AMMETER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//显示状态栏信息
			StatusStr.Format("正在从%s表中导入电表信息数据，请稍侯...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//显示滚动条
			SetProgressCtrlRange(0, index,1);

			//电表参数 TB_AMMETER
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_AMMETER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//显示状态栏信息,发送显示状态栏提示	
				StatusStr.Format("导入电表信息数据完成%.2f％,请稍侯...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);
              	
				SqlCmd = "INSERT INTO TB_AMMETERBAK(AMMETER_TYPE,AMMETER_MANUFACTURER,AMMETER_IMPULSE,AMMETER_REMARK) VALUES (";

				for(int i = 0; i < 4; i ++)
				{	
					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();
					
					if(i == 2)
					{	
						
						if(str.IsEmpty())
						{
							SqlCmd = SqlCmd      + "0,";
						}
						else
						{
							SqlCmd = SqlCmd + str + ",";
						}
						
					}
					else
					{
						
						if(i < 3)
						{
							SqlCmd = SqlCmd + "'" + str + "',";
						}
						else
						{
							SqlCmd = SqlCmd + "'" + str + "')";
						}
						
					}

				}
				
		//		WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//写入表
				k                       ++;
				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("导入电表信息数据完毕...");//,m_FileName);
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//显示滚动条

		}
	
		vars.ChangeType(VT_I4, 0);
		
		//处理TB_ELECTRICITYBAK数据表,电价信息
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_ELECTRICITY",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		index = vars.lVal;

		if(index > 0)
		{
			
			//显示状态栏信息
			StatusStr.Format("正在从%s表中导入电价信息数据，请稍侯...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//显示滚动条
			SetProgressCtrlRange(0, index,1);

			//电表参数 TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_ELECTRICITY",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//显示状态栏信息,发送显示状态栏提示	
				StatusStr.Format("导入导入电价数据完成%.2f％,请稍侯...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);

            	SqlCmd = "INSERT INTO TB_ELECTRICITYBAK(ELECTRICITY_NO,ELECTRICITY_KIND,ELECTRICITY_PRICE,ELECTRICITY_REMARK) VALUES (";
            
				for(int i = 0; i < 4; i ++)
				{
					SetProgressCtrlSetIt();

					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
					str.TrimRight();
					str.TrimLeft();

					switch(i)
					{
					case 0:
						{
						//	SqlCmd = SqlCmd  +  str + ",";
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}

							break;
						}
					case 1:
						{
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 2:
						{
							//SqlCmd = SqlCmd   + str + ",";
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}
							
							break;
						}
					case 3:
						{
							SqlCmd = SqlCmd + "'" + str + "')";
							break;
						}
						
					}
				
				}
			
			//	WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//写入表
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("导入电价信息数据完毕...");
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//显示滚动条

		}

        vars.ChangeType(VT_I4, 0);

		//处理TB_TRANSFORMERBAK数据表,变台信息数据
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_TRANSFORMER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//显示状态栏信息
			StatusStr.Format("正在从%s表中导入变台信息数据，请稍侯...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//显示滚动条
			SetProgressCtrlRange(0, index,1);

			//电表参数 TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_TRANSFORMER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//显示状态栏信息,发送显示状态栏提示	
				StatusStr.Format("导入导入变台信息数据完成%.2f％,请稍侯...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);

				//(TRANSFORMER_NO VARCHAR(40),TRANSFORMER_TYPE VARCHAR(10),TRANSFORMER_CAPACITY VARCHAR(4),TRANSFORMER_INSTALLTIME VARCHAR(8),TRANSFORMER_POSITION  VARCHAR(30),TRANSFORMER_OWNERSHIP VARCHAR(10),TRANSFORMER_CONNECTFORM  VARCHAR(1)
            	SqlCmd = "INSERT INTO TB_TRANSFORMERBAK(TRANSFORMER_NO,TRANSFORMER_TYPE,TRANSFORMER_CAPACITY,TRANSFORMER_INSTALLTIME,TRANSFORMER_POSITION,TRANSFORMER_OWNERSHIP,TRANSFORMER_CONNECTFORM) VALUES (";
            
				for(int i = 0; i < 7; i ++)
				{
					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();

					switch(i)
					{
					case 0:
						{
							//TRANSFORMER_NO
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 1:
						{
							//TRANSFORMER_TYPE
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 2:
						{
							//TRANSFORMER_CAPACITY	
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}

							//SqlCmd = SqlCmd   + str + ",";
							break;
						}
					case 3:
						{
							//TRANSFORMER_INSTALLTIME,时间处理
							CTime              m_BakTime(atoi(str.Mid(0,4)),atoi(str.Mid(4,2)),atoi(str.Mid(6,2)),0,0,0);
							str.Format("%4d-%02d-%02d %02d:%02d:%02d",m_BakTime.GetYear(),m_BakTime.GetMonth(),m_BakTime.GetDay(),m_BakTime.GetHour(),m_BakTime.GetMinute(),m_BakTime.GetSecond());
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 4:
						{
							//TRANSFORMER_POSITION
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 5:
						{
							//TRANSFORMER_OWNERSHIP
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 6:
						{
							//TRANSFORMER_CONNECTFORM
							SqlCmd = SqlCmd  + str +  ")";
							break;
						}
						
					}
				
				}
				
				//WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//写入表
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("导入变台信息数据完毕...");
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//显示滚动条

		}
		
        vars.ChangeType(VT_I4, 0);
		//处理TB_USERBAK数据表,变台信息数据
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_USER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//显示状态栏信息
			StatusStr.Format("正在从%s表中导入用户信息数据，请稍侯...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//显示滚动条
			SetProgressCtrlRange(0, index,1);

			//电表参数 TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_USER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//显示状态栏信息,发送显示状态栏提示	
				StatusStr.Format("导入导入用户信息数据完成%.2f％,请稍侯...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);
			
             	SqlCmd = "INSERT INTO TB_USERBAK(USER_COMPANY     ,USER_STATIONNO    ,USER_STATIONNAME    ,USER_MOTHERLINE  ,USER_BAKMOTHERLINE ,USER_LINENO     ,USER_BAKLINENO ,\
												 USER_LINENAME    ,USER_TRANSFORMERNO,USER_MODULENO       ,USER_PHASE       ,USER_NAME          ,USER_NO         ,USER_OLDNO     ,\
												 USER_ADDRESS     ,USER_PHONE        ,USER_ELECTRICITYKIND,USER_AMMETERNO   ,USER_AMMETERKIND   ,USER_INSTALLTIME,USER_SUPPLYMODE,\
												 USER_INITIALVALUE,USER_MULTIPLE     ,USER_PROTOCOL       ,USER_DESCRIBE    ,USER_READLABEL     ,USER_TIMELABEL  ,USER_ETSTATUS  ,\
												 USER_IDNO        ,USER_AMMETERTYPE  ,USER_SENDANGLE      ,USER_DOWNVALUE   ,USER_UPVALUE       ,USER_RUNSTATUS  ,USER_ZHULABEL  ) VALUES (";
				for(int i = 0; i < 35; i ++)
				{					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();

					//数值型
					if((i >= 3 && i <= 6) || (i==9) ||  (i==10) || (i==16) || (i==18) || (i==20) || (i==21) || (i==22) || (i==23) || (i>=30 && i<=33))
					{

						if(str.IsEmpty())
						{
							SqlCmd = SqlCmd      + "0,";
						}
						else
						{
							SqlCmd = SqlCmd + str + ",";
						}

					}
					else if(i == 19)
					{
						//USER_INSTALLTIME
						CTime              m_BakTime(atoi(str.Mid(0,4)),atoi(str.Mid(4,2)),atoi(str.Mid(6,2)),0,0,0);
						str.Format("%4d-%02d-%02d %02d:%02d:%02d",m_BakTime.GetYear(),m_BakTime.GetMonth(),m_BakTime.GetDay(),m_BakTime.GetHour(),m_BakTime.GetMinute(),m_BakTime.GetSecond());
						SqlCmd = SqlCmd + "'" + str + "',";
						
					}
					else if(i == 34)
					{
						SqlCmd = SqlCmd + "'" + str + "')";
					}
					else
					{
                        SqlCmd = SqlCmd + "'" + str + "',";
					}

				}

		//		WriteToLog(SqlCmd);
		//		AfxMessageBox(SqlCmd);

                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//写入表
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("导入用户信息数据完毕...");
			SendMessage(WM_EVENT, 1, 0);

			ShowProgressCtrl(FALSE);//显示滚动条
		}

		//从临时表中倒入数据
		StatusStr.Format("正从临时表中倒入数据，请稍侯...");
		SendMessage(WM_EVENT, 1, 0);

	    ShowProgressCtrl(TRUE);//显示滚动条
		SetProgressCtrlRange(0, 4,1);

		
		//删除TB_AMMETERBAK数据表
		if(IsCurveTableExist("TB_AMMETERBAK"))  //是否存在此表
		{
			//倒入电表数据
			SqlCmd = "INSERT INTO TB_AMMETER SELECT DISTINCT * FROM TB_AMMETERBAK WHERE AMMETER_TYPE NOT IN (SELECT AMMETER_TYPE FROM TB_AMMETER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
			SqlCmd.Format("DROP TABLE TB_AMMETERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}
	

		SetProgressCtrlSetIt();	
		
		//删除TB_ELECTRICITYBAK数据表
		if(IsCurveTableExist("TB_ELECTRICITYBAK"))  //是否存在此表
		{       
			//倒入电价数据
			SqlCmd = "INSERT INTO TB_ELECTRICITY SELECT DISTINCT * FROM TB_ELECTRICITYBAK WHERE ELECTRICITY_NO NOT IN (SELECT ELECTRICITY_NO FROM TB_ELECTRICITY)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
            SqlCmd.Format("DROP TABLE TB_ELECTRICITYBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

	
		SetProgressCtrlSetIt();
	
		//删除TB_TRANSFORMERBAK数据表
		if(IsCurveTableExist("TB_TRANSFORMERBAK"))  //是否存在此表
		{    
			//倒入变台数据
			SqlCmd = "INSERT INTO TB_TRANSFORMER SELECT DISTINCT * FROM TB_TRANSFORMERBAK WHERE TRANSFORMER_NO NOT IN (SELECT TRANSFORMER_NO FROM TB_TRANSFORMER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	           
            SqlCmd.Format("DROP TABLE TB_TRANSFORMERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}
	

		SetProgressCtrlSetIt();
		
		//删除TB_USERBAK数据表
		if(IsCurveTableExist("TB_USERBAK"))  //是否存在此表
		{  
			//倒入用户数据
			SqlCmd = "INSERT INTO TB_USER SELECT DISTINCT * FROM TB_USERBAK WHERE USER_MODULENO NOT IN (SELECT USER_MODULENO FROM TB_USER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);           
            SqlCmd.Format("DROP TABLE TB_USERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
			
			//树控件重新刷新一次
			RefreshTree();
		}	
		
		SetProgressCtrlSetIt();

		StatusStr.Format("【从ACCESS数据库中导入所有数据完毕】");
		SendMessage(WM_EVENT, 1, 0);
	    db.Close();

		ShowProgressCtrl(FALSE);//显示滚动条
	
	}
	
}

//快速读表时，得出当前的模块上数的最近的值和时间,61,62协议为485表,71,72协议为脉冲表
BOOL CIFRMView::TestIfCanQuickReadAmmeter(long module,CString  m_CurrentTime,CString  m_AmmeterType,BYTE m_protcol)
{	
	CDatabase                   dbs;	
	CString              strSql,str;
	int       m_days        =     0;
	int       k             =  3200;
	BOOL      m_CheckValue  = FALSE;
	double  m_tempvalue,m_InitValue;
	m_tempvalue  = m_InitValue =  0;

	//m_QuickReadParameter[0] 最新有功电度读表值
	//m_QuickReadParameter[1] 有功电度底值
	//m_QuickReadParameter[2] 3200的倍数

	for(int i = 0; i < 3; i ++)
	{
		m_QuickReadParameter[i] = 0;
	}

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset             rs(&dbs);
		//strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,module,module);
		strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s'),b.USER_INITIALVALUE FROM TB_GARRISON a,TB_USER b WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d AND b.USER_MODULENO=a.GARRISON_MODULENO",m_CurrentTime,module,module);
		rs.Open(CRecordset::forwardOnly,strSql);

		if(!rs.IsEOF())
		{
			//有功电度底值
			rs.GetFieldValue((short)0,strSql);			
			m_QuickReadParameter[0]   = atof(strSql);
			
			//和现在的时间差
			rs.GetFieldValue((short)1,strSql);
			m_days     =  atoi(strSql);
			
			//初始值
			rs.GetFieldValue((short)2,strSql);
			m_QuickReadParameter[1]   = atof(strSql);
		}

		rs.Close();
		
	    if(!m_AmmeterType.IsEmpty())
		{
			strSql.Format("SELECT AMMETER_IMPULSE FROM TB_AMMETER  WHERE RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);
			rs.Open(CRecordset::dynaset,strSql);	
			
			if(!rs.IsEOF())
			{
	    		rs.GetFieldValue((short)0,strSql);
				k =  atoi(strSql);
			}
			
			if(k == 0)
			{
				k = 3200;
			}
			
			rs.Close( );

		}	

		dbs.Close();
		
	}   
	
	if(BYTE(m_protcol/10) == 6)
	{
		//61,62协议为485表
		if(m_days < 20 && m_QuickReadParameter[0] > 0.01)
		{
			m_CheckValue = TRUE;
		}
		
	}
	else
	{
		//71,72协议为脉冲表
		m_QuickReadParameter[2] = k*1.00/3200;
		
		if(m_days/m_QuickReadParameter[2] < 20  && m_QuickReadParameter[0] > 0.01)
		{
			m_CheckValue = TRUE;
		}

	}
	
	return m_CheckValue;
}

//得到发驻留信息的母线和协议种类
void CIFRMView::GetSendZhuLiuInformation()
{	

	m_MotherLineArray.RemoveAll();
	m_ProtColArray.RemoveAll();

	CDatabase            db;
	CString             Str;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset        rs(&db);
		
		//母线
		//SELECT DISTINCT USER_MOTHERLINE,USER_PROTOCOL FROM TB_USER ORDER BY USER_MOTHERLINE ASC,USER_PROTOCOL DESC
		Str = "SELECT DISTINCT USER_MOTHERLINE FROM TB_USER";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //得到记录个数
		    rs.GetFieldValue((short)0,Str);
			m_MotherLineArray.Add(atoi(Str));
			rs.MoveNext();
		}

		rs.Close();

		//备用
		Str = "SELECT DISTINCT USER_BAKMOTHERLINE FROM TB_USER";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //得到记录个数
		    rs.GetFieldValue((short)0,Str);
			m_MotherLineArray.Add(atoi(Str));
			rs.MoveNext();
		}

		rs.Close();

		//协议SELECT DISTINCT a.USER_BAKMOTHERLINE,a.USER_PROTOCOL FROM TB_USER a, TB_USER b WHERE a.USER_BAKMOTHERLINE=b.USER_BAKMOTHERLINE AND b.USER_BAKMOTHERLINE> 0 ORDER BY a.USER_BAKMOTHERLINE ASC,a.USER_PROTOCOL DESC 
		Str = "SELECT DISTINCT USER_PROTOCOL FROM TB_USER ORDER BY USER_PROTOCOL DESC";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //得到记录个数
		    rs.GetFieldValue((short)0,Str);
			m_ProtColArray.Add(atoi(Str));
			rs.MoveNext();
		}

    	rs.Close();
		db.Close( );				
	}


}

//检查71协议485表快速读表是否成功
void CIFRMView::Check_71485_Protcol(long ModuleNum,BYTE m_order)
{
  	CDatabase                                    dbs;	
	CString                               strSql,str;
	int                 m_days         =           0;
	double    m_tempvalue1,m_tempvalue2,m_tempvalue3;
	m_tempvalue1 =  m_tempvalue2 = m_tempvalue3  = 0;
	CString                            m_CurrentTime;
	CTime  timet  =          CTime::GetCurrentTime();
    m_CurrentTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
    	CRecordset   rs(&dbs);

		//和CRecordset连上
		if(m_order == 0x64 || m_order == 0xF4)
		{	
			//峰，平，谷快速读表
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_FDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//驻留峰
			if(!rs.IsEOF())
			{
				//底值
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue1 = atof(strSql);
				
				//时间差天数
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[0] = m_tempvalue1 - (long(m_tempvalue1)%1000) + m_Quick71Value[0];

				//可以等
				if(m_days == 1)
				{					
					
					//一天跑0~200度,数据是否合理
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{	
						//可快速读485表
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{
					
					//一天跑0~200度
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{
						//可快速读485表
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//可快速读485表
				m_CanQuickRead71485   = FALSE;	
				
			}
			
			//驻留谷
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_PDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
				//平,底值
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue2 = atof(strSql);
				
				//时间差天数
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[1] = m_tempvalue2 - (long(m_tempvalue2)%1000) + m_Quick71Value[1];

				//可以等
				if(m_days == 1)
				{					
					
					//一天跑0~200度,数据是否合理
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{	
						//可快速读485表
						m_CanQuickRead71485   = FALSE;
					
					}
					
				}
				else
				{
					//一天跑0~200度
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{
						//可快速读485表
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//可快速读485表
				m_CanQuickRead71485   = FALSE;	
				
			}
			
			//驻留谷
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_GDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
				//谷值
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue3 = atof(strSql);
				
				//时间差天数
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[2] = m_tempvalue3 - (long(m_tempvalue3)%1000) + m_Quick71Value[2];

				//可以等
				if(m_days == 1)
				{	
					
					//一天跑0~200度,数据是否合理
					if(!(((m_Quick71Value[2] - m_tempvalue3) <= m_days*200) && ((m_Quick71Value[2] - m_tempvalue3) >= 0)))
					{	
						//可快速读485表
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{

					//一天跑0~200度
					if(!(((m_Quick71Value[2] - m_tempvalue3) <= m_days*200) && ((m_Quick71Value[2] - m_tempvalue3) >= 0)))
					{
						//可快速读485表
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//可快速读485表
				m_CanQuickRead71485   = FALSE;	
				
			}
		
		
		}
		else if(m_order == 0x66 || m_order == 0xF6)
		{
			//实时有功、无功,驻留有功、无功
			if(rs.IsOpen())
			{
				rs.Close();
			}

			strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);

			if(!rs.IsEOF())
			{
				//驻留有功
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue1 = atof(strSql);
				
				//时间差天数
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[0] = m_tempvalue1 - (long(m_tempvalue1)%10000) + m_Quick71Value[0];

				//可以等
				if(m_days == 1)
				{					
					//一天跑0~200度,数据是否合理
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{	
						//可快速读485表
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{
					//一天跑0~200度
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{
						//可快速读485表
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//可快速读485表
				m_CanQuickRead71485   = FALSE;	
				
			}

		    //驻留无功
			if(rs.IsOpen())
			{
				rs.Close();
			}

			strSql.Format("SELECT  GARRISON_LOSEDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
            rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
			
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue2 = atof(strSql);
				
				//时间差天数
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[1] = m_tempvalue2 - (long(m_tempvalue2)%10000) + m_Quick71Value[1];

				if(m_days == 1)
				{	
					
					//一天跑0~200度,数据是否合理
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{	
						//可快速读485表
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{

					//一天跑0~200度
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{
						//可快速读485表
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//可快速读485表
				m_CanQuickRead71485   = FALSE;	
				
			}
		
        }
		
	//	str.Format("命令(0x%0x),m_CanQuickRead71485=%d(1能快读,0不能)，表底:%.2f(快读m_Quick71Value[0]=%.2f),表底:%.2f(m_Quick71Value[1]=%.2f),表底:%.2f(m_Quick71Value[2]=%.2f)",m_order,m_CanQuickRead71485,m_tempvalue1,m_Quick71Value[0],m_tempvalue2,m_Quick71Value[1],m_tempvalue3,m_Quick71Value[2]);
	//	WriteToLog(str);
	  
		if(rs.IsOpen())
		{
			rs.Close();
		}
	
		if(dbs.IsOpen())
		{
			dbs.Close();
		}


	}

}
