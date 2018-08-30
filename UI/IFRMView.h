// IFRMView.h : interface of the CIFRMView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include <windows.h>                                       
#include <iostream> 
#include "afxmt.h"
#include "resource.h"
#include "mscomm.h"
#include "mswinsockcontrol.h"
//}}AFX_INCLUDES

#include "MyListCtrl.h"
#include "gridctrl.h"
#include "MutiTreeCtrl.h"
#include "memory"

#define WM_EVENT WM_USER+7

#if !defined(AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_)
#define AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIFRMCntrItem;

//总共发送次数
#define   PASS_TIMES     35
#define   WM_NUMBERS     81

class CTransformRecordset    ;
class CAmetterRecordset      ;
class CUseInfoRecordSet      ;
class CGarrisonRecordSet     ;
class CDataInfoRecordSet     ;
class CPriceSet              ;
class CCHANGEAMMETERSet         ;//换表模块
class CIFRMApp;

class CIFRMView : public CFormView
{
protected: // create from serialization only
	CIFRMView();
	DECLARE_DYNCREATE(CIFRMView)
	//CDataListCtrl	m_list;	
public:
	//{{AFX_DATA(CIFRMView)
	enum { IDD = IDD_IFRM_FORM };
	CListCtrl               m_lists;
	CMSComm	                  m_Com;
	CMSWinsockControl	m_WinSocket;
	CMSComm	            m_485MsComm;
	//}}AFX_DATA
	
	// Attributes
public:

	// m_pSelection holds the selection to the current CIFRMCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CIFRMCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.
	
	// TODO: replace this selection mechanism with one appropriate to your app.
	CIFRMCntrItem* m_pSelection;
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFRMView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL
	
	// Implementation
public:	
	BOOL m_CanQuickRead71485;
	BOOL                        m_QuickReading; //打包读表
	void DrFromAccessFile(CString  m_FileName);
    short                    m_WgLess;//无功的时间间隔 0---10分钟 1---20分钟 2---30分钟
	void WuGongDeal(CString   ConStr);
	void         CheckTongXunStatus();
	void                StartZhuLiu();
	BYTE      m_DateReadParameter[67];//按驻留日期设置驻留参数 格式：62(31个*号*点)，1(读表间隔)、1(*次)、1(以后＊点一读)、1(读＊天),1(是否自动驻留) = 62 + 5 = 67
	CString m_DynaicCheckStrCondition;
	BOOL           m_CheckReading;
	BOOL WaitShiKedian(BYTE m_shikedian);
	BYTE	          m_shikedian;
	BYTE		     m_readRangle;
	BYTE	 	 m_readchecktimes;
	CEvent		TmpOnlyOneThreadRun;
	BOOL                  m_Pause;//线程暂停标志
	CString        m_dbConnectStr;
	void           CheckLineRun();
	void DealOverTime(BYTE kinds);
	BYTE              m_saveyears;
	BOOL      m_DoubleConnected;
	short     m_PassErrortimes;
	BOOL      DeleteViewThread();
	void      ModifyDialInternetStatus();
	BOOL      m_IfChangeData;//接收远程数据的标志
	BOOL      m_others;
	CString   DecodeParameter(BOOL m_ReadRanage);
	void      WriteToAllAmeterParameter();
	void      WriteToParameterByDate();//写入按日期设置参数的驻留
	short     m_parameter[110];
    void      ComingIntoBeing(CString SqlStr,CString m_begin, CString m_End, BOOL m_yg, BOOL m_wg, BOOL m_jz, BOOL m_fz, BOOL m_gz, BOOL m_pz,  BOOL m_dy, BOOL m_dl);
    void      ElectricityWarning(CString SqlStr,CString m_begin, CString m_End);//用电量报警
	void      BeginTotalLoss(CString m_Condtion,CString BeginTime,CString EndTime);
	void      EverySendInfo();
	BOOL      UpdateDataTable();
	int       m_GetErrors;
	int       m_CurrentPassPostions;
	int       m_PassDataRecords;
	CString   m_PassDataFileName;
	CString   m_GetDataTimeStr;
	BOOL      m_GetDataFromFile;
	CStringArray m_FileDataArray;
	COLORREF  m_BackRgbValue;
	int       m_SetRecycleTime;
	int       m_Recycles;
	short     m_AutoReadParameter[160];//灵活定时读表的参数 前0－30为居民表 31－61为大用户选择 62－92为变电表 93－123为线路表 124－154为电站表 155 表示几点读表 156有功［值0－没有选择值 1－选择单边累加 2－选择单边累加及总值］157无功［值0－没有选择值 1－选择单边累加 2－选择单边累加及总值］158电流［0 没有选 1选］ 159电压［0 没有选 1选］
	void      SetDataReadLabel(CString m_range);
	
	BOOL      m_IsDialConnectting;    //拔号连接的标志
	CString   m_FtpFileName;
	void      GetDataFormMarketServer(CString m_address, CString m_loginname, CString m_password,CString m_StrFileName,int m_port);
    //CString  m_DataName  表名,CString  TxtFileName  导入文本文件
	void      DealRepeatRecord(CString  m_DataName,CString TxtFileName);
	void      SetGridItem(GV_DISPINFO *pDispInfo);
	BOOL      m_DialogBarVisible;
	CGridCtrl m_Grid;
	//初始化列表
	void      InitGrid(CString table,CString BeginTime,CString EndTime);
	
    
	CString   m_ModuleFindContionStr;
	//1、电价数据表操作
	CStringArray TB_ELECTRICITYS;
	//2、变台信息数据表操作
	CStringArray TB_TRANSFORMERS;
	//3、电表信息数据表操作
	CStringArray TB_AMMETERS;
	//4、用户信息库数据表操作
	CStringArray TB_USERS;
	//5、驻留数据表操作
	CStringArray  TB_GARRISONS;
	//6、数据表操作
	CStringArray  TB_REALTIMES;
    //7、换表信息
	CStringArray  TB_CHANGEAMMETERS;
	//服务器地址、用户名、密码
	CString          m_address;
	CString        m_loginname;
	CString         m_password;
	int                 m_port;

	BOOL     m_IsAutoSending;
	void     SurrenderWindowMessage();
	void     KillAotoReadMeter();
	CString  m_TimeStrs;
	BOOL     SetRemoteTime(CString    Str);
	void     SetLocalTimes(CString  times);
	void     SetTimersign();
	CString  m_AutoReadCondtionStr;
	//是否定时发送信号
	BOOL     m_status;
	//连接标志
	BOOL     m_IsConnect; //网络连接的标志
	BOOL     Ports[15];
	//得到数据更新的时间
    CString GetRefreshTime();

	//滑动杆下滑
	void   SetProgressCtrlSetIt();
	void   ShowProgressCtrl(BOOL m_IsShow);
	void   status(CString strname);

	BYTE   m_handno;
	//得到手拉手编码
    void   GetHandModuleInformation();
	void   SettcpClient(CString RemoteHostAddress,int RemotePort);
	void   SetLocalServer(CString LocalHostAddress, int LocalPort);
	BOOL   m_SetLabel[15];     //读哪些项
    BOOL   m_TimeSetLabel[15]; //定时读表标志
   	short  m_sendkind;         //0 串口发送 1 电话拔号发送 2 TCP/IP发送
	BOOL   m_StartRead;
	BOOL   m_DayOrYear[2];     //每日一读还是每月一读
	//设置角度
	//short generatrixno 母线编号
	//short phase        相别 0 A相 1 B相 2 C相
	//int   angles       角度
	//BYTE  kinds  种类 0--信号强度 1－延迟角度
	void SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds);

	//读取角度
	//short generatrixno 母线编号
    //short phase        相别   0 A相 1 B相 2 C相
    void   ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds);
	
	
	//title           对话框标题
    //IfWriteData     是否写入数据库 FALSE---不写 TRUE---写
    //WhichTable      哪个表         0----数据表  1----驻留表
    //constr          条件 ALL 所有
	//recycles        循环次数
	//Settimes        每二次时间间隔
	//m_ReadKinds     0---普通读表   1----手工读 
    void   FiveDataChuLi(CString title,BOOL  SELECT[],BOOL IfWriteData, int WhichTable, CString constr,int recycles,int Settimes,BYTE m_ReadKinds);
	
	//处理参数
    void   DisposeModuleParameter(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals);

    //运行SQL语句
	

	//生成抄表数据
	void   FormChaoBiaoData(CString SqlStr,CString BeginTime,CString EndTime);
    
	//发驻留时间命令
	void   SendBreadorder(CTime  m_iBroadTime,int times);
	void   WriteDataToExcelFile(CString dataname,CString Sqlstr,long records,CString filename);
	BOOL   PcSendToSCM(BYTE ORDER[],BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/);
	int    m_iBandPassPoints;
	void   WriteToLog(CString Str);
	BOOL   WriteDataToTextFile(CString dataname,CString Sqlstr,long records,CString filename);
	void   DisConnect(short kinds);
	BOOL   Connect(BOOL  ShowMessage,BOOL IfVoice);
	void   Dial(CString m_strPhoneNumber,BOOL IfVoice);
	CString m_strReceiveChar;
	/***************************************************************
	串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
	波特率 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000
	检验位 0-无校验,1－奇校验,2－偶校验
	数据位 0-4     ,1-5      ,2-6      ,3-7    ,4-8
	停止位 0-1     ,1-1.5    ,2-2
	//HexSend  TRUE  二进制方式传送 FALSE 文本方式传送
	****************************************************************/
    void   OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex);
	double ReadMeter(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/,BYTE Item/* 要什么东西*/,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/,CString m_AmmeterType/*脉冲表型号*/);
	//全采三相电流读表数据,采集六通道
    double ReadSixChannelMeter(long ModuleNum/*模块号*/,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo/*线号*/, BYTE Phase/*相选择0A 1B 2C*/,BYTE Item/* 要什么东西*/,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/,CString m_AmmeterType/*脉冲表型号*/);

	void   WriteP9111_CHANNEL_DOPort(int value);
	void   SetProgressCtrlRange(int ups,int downs,int steps);

	std::shared_ptr<CTransformRecordset>    m_TransformpSet;
	std::shared_ptr<CAmetterRecordset>      m_AmetterSet;
	std::shared_ptr<CUseInfoRecordSet>      m_UseInfoset;
	std::shared_ptr<CGarrisonRecordSet>     m_GarrisonSet;
	std::shared_ptr<CDataInfoRecordSet>     m_DataInfoSet;
	std::shared_ptr<CPriceSet>              m_PriceSet;
	std::shared_ptr<CCHANGEAMMETERSet>         m_CCHANGEAMMETER;//换表模块

	//给线程的条件
	CString                 SendContionStr;
	BOOL    SendOrderToSCM(long ModuleNum,BYTE StationNo/*手拉手电站码*/,BYTE MotherLine/*母线*/,BYTE LineNo,BYTE Phase,BYTE ZeroDots,BYTE Item,int status,BYTE Protocol/*读表协议*/,BYTE m_SendAngle/*发送的角度*/);
	CString                 StatusStr;
	CString                 StatusStrRead;
	
	//判断表是否存在
    BOOL   IsCurveTableExist(CString strTableName);

	//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
	//Str             发送字符
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	//BOOL m_CheckReturnValue 是否检测返回值,证明收到了
	BOOL  SelectSendString(int kinds, CString Str, BOOL CheckConnected,BOOL AppearPrompt,BOOL m_CheckReturnValue);

	//自动读表定的时间
	CTime             m_AutoReadTime;
	int          m_SendGarrisonTimes;

	CIFRMApp*                  Apppt;
	BOOL              CheckRunning();

	//次数
	int                      m_times;
	virtual ~CIFRMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CIFRMView)
	afx_msg void OnDestroy();
	
    afx_msg void OnSize(UINT nType, int cx, int cy);
	
	
	
	afx_msg void OnTestreadtable();
	afx_msg void OnBreadorder();
	afx_msg void OnTranformer();
	afx_msg void OnUserinfo();
	afx_msg void OnAmmeterinfo();
	afx_msg void OnCommunication();
	afx_msg void OnStoprun();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOwemoney();
	afx_msg void OnOnCommMscomm();
	
	afx_msg void OnOpenreportfile();
	afx_msg void OnPrice();
	afx_msg void OnDatapass();
	afx_msg void OnUpdateConnectsuccess(CCmdUI* pCmdUI);
	afx_msg void OnStopexam();
	afx_msg void OnAngleset();
	afx_msg void OnPaint();
	afx_msg void OnPhasetest();
	afx_msg void OnConnectionRequestWinsock(long requestID);
	afx_msg void OnDataArrivalWinsock(long bytesTotal);
	afx_msg void OnCloseWinsock();
	afx_msg void OnConnectWinsock();
	afx_msg void OnErrorWinsock(short Number, BSTR FAR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL FAR* CancelDisplay);
	afx_msg void OnSendProgressWinsock(long bytesSent, long bytesRemaining);
	afx_msg void OnSendCompleteWinsock();
	afx_msg void OnTimecheck();
	afx_msg void OnUpdateLstSave(CCmdUI* pCmdUI);
	afx_msg void OnAutoreadset();
	afx_msg void OnBREAkSOMEDAY();
	afx_msg void OnUpdateOwemoney(CCmdUI* pCmdUI);
	afx_msg void OnPassuserdata();
	afx_msg void OnUpdatePassuserdata(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowdialogbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePhasetest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTestreadtable(CCmdUI* pCmdUI);
	afx_msg void OnRclickListss(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHidedata(CCmdUI* pCmdUI);
	afx_msg void OnSavereportas();
	afx_msg void OnUpdateSavereportas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemotemodify(CCmdUI* pCmdUI);
	
	
	
	afx_msg void OnUpdateNewreport(CCmdUI* pCmdUI);
	
	afx_msg void OnGetdatafromlong();
	afx_msg void OnLocalmodify();
	afx_msg void OnUpdateLocalmodify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppearselectdata(CCmdUI* pCmdUI);
	
	afx_msg void OnUpdateBREAkSOMEDAY(CCmdUI* pCmdUI);
	afx_msg void OnReportfont();
	afx_msg void OnUpdateDeletemodule(CCmdUI* pCmdUI);
	afx_msg void OnDeletemodule();
	afx_msg void OnUpdateAngleset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommunication(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatapass(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAutoreadset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBreadorder(CCmdUI* pCmdUI);
	afx_msg void OnClosereport();
	afx_msg void OnUpdateClosereport(CCmdUI* pCmdUI);
	afx_msg void OnTimesearch();
	afx_msg void OnZhuliumodify();
	afx_msg void OnZhenshimodify();
	afx_msg void OnUpdateTimesearch(CCmdUI* pCmdUI);
	afx_msg void OnGetfile();
	afx_msg void OnUpdateDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnConnectsuccess();
	afx_msg void OnStoporsend();
	afx_msg void OnUpdateStoporsend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDataappear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateListselect(CCmdUI* pCmdUI);
	afx_msg void OnCheckeqaul();
	afx_msg void OnUpdateCheckeqaul(CCmdUI* pCmdUI);
	afx_msg void OnXiangchange();
	afx_msg void OnUpdateXiangchange(CCmdUI* pCmdUI);
	afx_msg void OnChecklinestatus();
	afx_msg void OnUpdateChecklinestatus(CCmdUI* pCmdUI);
	afx_msg void OnFindrepeatrecords();
	afx_msg void OnUpdateFindrepeatrecords(CCmdUI* pCmdUI);
	afx_msg void OnFautoreadset();
	afx_msg void OnUpdateFautoreadset(CCmdUI* pCmdUI);
	afx_msg void OnCancelautozhuliu();
	afx_msg void OnUpdateCancelautozhuliu(CCmdUI* pCmdUI);
	afx_msg void OnChangeammeter();
	afx_msg void OnModifyprotcol();
	afx_msg void OnWxcheckstatus();
	afx_msg void OnWugongparameter();
	afx_msg void OnWugongdeal();
	afx_msg void OnUpdateWugongdeal(CCmdUI* pCmdUI);
	afx_msg void OnDrfromaccess();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
    afx_msg LRESULT OnEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void Check_71485_Protcol(long ModuleNum,BYTE m_order);
	double m_Quick71Value[4];
	CByteArray      m_MotherLineArray;
	CByteArray      m_ProtColArray;
	void  GetSendZhuLiuInformation();

	float         m_QuickGlys[100000];
	long        m_QuickModuleAddress;//快速读表的地址
	long      m_QuickReadModuleValue;//快速读表的值
	double   m_QuickReadParameter[3];
	BOOL  TestIfCanQuickReadAmmeter(long module,CString  m_CurrentTime,CString  m_AmmeterType,BYTE m_protcol);
	short GetWGTimeEvery();
	//所有的无功表处理一次
    void ALLWuGongDeal();

	//找过0点的位置,找10个点,有一半为负的话,先5个负,后5个正,k个点
    int FindZeroPoint(short m_CollectData[],int m_StartPlace,int k);
    //采集六通道相关性检验
    double CorrelationSixChannelCheck(long SourceArray[], long DestArray[],int K);
    //检验当前的数据是否有效 m_kinds 0 可以和上次的数相等，1不能=
    BOOL CheckReadValueValid(long m_module,CString m_FieldName,double Currentvalue,CString m_zhutimeValue,BYTE m_kinds);
	//换算电流值
    int ChangeIValue(BYTE m_Ivale);
	void CheckWireLess();
	CTime m_FirstReadOkTime;
	void InitializeCurrent();
	float  m_AllLineThreeCurrent[128];//存32条线路4次电流
	BYTE   m_All_Line_Current[32];//各线路是否有电流，值 0 没有电流 1 有电流  2 没有检测
	void   EveryHourCheckLine();
	//检测当前母线出线是否有电流
	//BYTE MotherLine 母线编号
	//BYTE LineNo     线路编号
	BOOL CheckIfHaveCurrentValue(BYTE MotherLine, BYTE LineNo);
	void ByDateSetGarrisonRange(BYTE m_date);
	DWORD         m_Thread_PRIORITY;//线程的级别
	//十六进字符转成数
    int GetHexValue(CString str);
	void ByDateAutoGarrisonTime();
	CString GetZhuLiuRanage(short m_date);
	CString ByDateDecodeParameter();
	BYTE m_zhuliukinds;
	short ByDateCheckCurrentTime();//按日期检测是否是发驻留
	void  ByDateDingShiDeal();
	BOOL IsDyConnect(CString m_StationName);
	void DingShiDeal();
	BYTE         m_CollectNos;//纠码个数
	BYTE    m_CollectPlace[2];//纠码位置
	CString CheckCurrentValue(BYTE MotherLine,BYTE LineNo,BOOL m_SendInfo);
	CString GetFileFolderPass;
	BYTE    m_ReadModuleTimes;
    void DealOverTimeData(int m_Years); //处理过期数据，驻留表中＊月之前的数据，正式表中的数据
	long m_SettimerValues;
	void InitializeGarrionReadRange();
	void SetGarrionLabel();
	void AutoGarrisonTime();
	BYTE GetMaxDays(BYTE m_select);
	short       CheckCurrentTime();
	BOOL ModifyDataTable(CString m_TableName,CString m_TableSql,BOOL m_CheckRecords);
	long    SubCapability(CString SubNo);
	//得到某变台本身的总表值及下所有居民表和大用户表的和
	//CString FieldName       所求字段名 TB_Garrison.有功电度
	//CString CompanyName     公司名
	//CString SubstationName  变电站名
	//int     SubNo           变台号  
	//CString LineName        线路名称
	//CString     SubNo           变台号
	//short   kinds           种类 0－－－本身的表值 1－－下面所有居民表及大用户表的表和
	double GetSubElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,CString SubNo,short kinds,CString BeginTime,CString EndTime);

	CString m_DingShiString;
	//查表得到脉冲表的脉冲率
    int GetAmmeterImpulse(CString m_AmmeterType);
	//得到表字段的个数
    short GetFieldNumbers(CString m_DataName);
	BOOL m_StopPassing;
	void AppearAccept(CString m_dataname);
	void AskIfAddData(CString DataName,CString FileName);
	//得到文本文件第*行的数据
    CString GetDataLineCString(CString FileName,int m_lines);
	//CString m_CondtionString  发送要满足的条件
	//CString m_TableName       发送要满足的表名
	//int  Start     起始位
	BOOL   SendRemoteData(CString m_CondtionString, CString m_TableName, int Start);
	void   ReadRemoteTime();
	//相关性检验
    double CorrelationCheck(long SourceArray[], long DestArray[],int m_places);
	//产生BCH码
	//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
    void    Encode_Bch(BYTE g[],BYTE data[],BYTE m_kinds);
	BOOL    m_IsHistory;
	void    OperationAnimation(BOOL m_starting);
	void    ShowGridHead(CString  HeadStr);
	void    AutoAnswer(BOOL  ShowMessage);
	void    ShowDingShiButton(BOOL  IsShowWindows);
	short   Received;//判段接收数据的种类	1 －本软件的接收 2－与湖南长沙来的通讯
	BOOL    CheckStations(CString m_strsql);
	void    ReplaceUserModuleID(int startNo);
	void    GetPriveteDataFromWs(CString  m_CsvFileName);
	BYTE    HuNanZhaoHuanOrder;
	CString HuNanZhaoHuanTime;
	BOOL    SendHunNanHexData(CString Datatime,BYTE Kinds,int Start,int N);
	//得到文本文件行数
    int    GetDataLines(CString FileName);
	CString         GetFolder();
//	CString  m_ComeIntoDataName;
	void          RefreshTree();
	BOOL            m_ReceiveOk;
	BOOL      GetDialogBarStr();
	CString      GetStationNo();
	void SendErrorMessage(short kinds);
	CString         m_statusstr;
	void  BinarySystemReceive();//二进制方式接收,转成字符串
    void  HuNanWeiYuanReceive();//湖南威远的接收程序
	void  GetComPorts();
	float SwitchCurrentValue(float DeValue);
	BYTE  ConversionCurrentValue(BYTE Source);
	float ReadDataFrom485Com2(CString m_address,short kinds);
    void  SendMessageToElectricOffice(short kinds);//发送回馈信息 0-成功执行,1-检验码不对,2-无数据
    BOOL  WipeOffSpilthData();                     //清除多余的数据
	int   m_LocalAddress;
	void  AnalyseReceivedByteArray();              //传送的起始位置和个数

	//kinds           种类 0 串口发送 1 电话拔号发送 2 TCP/IP发送m_sendkind
	//CheckConnected  是否要连接   TRUE 要连接后才能发送 FALSE 不要求
	//AppearPrompt    是否显示提示 TRUE 显示提示         FALSE 不显示提示
	BOOL  SelectSendCByteArray(int kinds,BOOL CheckConnected,BOOL AppearPrompt);
	void  AnalyseDial(CString str);
	void  AnalyseOrder(CString OrderStr);

    short          m_EveryUnit;
	BYTE            LowAddress; //变电站低地址
    BYTE           HighAddress; //变电站高地址
    CByteArray     SendByteArray;//接收字节数组，发送字节数组
	CByteArray  ReceiveByteArray;
	long           m_PassRecords;
	CStatusBar*          pStatus;
	CStringArray      m_StrArray; 
	int                 m_angles;//角度值
	void    CarryOutOrders(CString Str);
	void    AddlistItem(CString m_StrArray[], int n);
	BOOL    StopRunning();
	void    WriteListHeading();
	void    SendOfficeBreadorder(int generatrix,int times,int m_iBroadTime,BYTE m_Potocol,CString NewTime);
	CString m_ZhuLiuTime;
	CString GetZhuLiuTime();
	BOOL    DecodeBCH63394(BYTE recd[],BOOL m_Is63394);
	BOOL    DecodeBCH31212(BYTE recd[]);
	int     m_iChSelect;
	BYTE    m_PassValue;
	//long ModuleNo  模块号
    //int times      读表次数
    //int mode       写表模式 //0 error,1 right
    void    WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode);
	long    m_ListRows;
	CString ReceiveStr;
	BOOL    IsFirstReceived;
	void    RealTimeReceiveData(CString str);
    double  Decode(long ModuleNum,BYTE Protocol,BYTE Item);  //解码
	//全采六通道解码,解6次－－－－－读表协议
    double DecodeSixChannel(long ModuleNum,BYTE Protocol,BYTE Item,BYTE m_phase);
	double  GetTestData(long m_Module,CString m_RightTime);//CString m_RightTime 此时时间
};

#ifndef _DEBUG  // debug version in IFRMView.cpp
inline CIFRMDoc* CIFRMView::GetDocument()
{ return (CIFRMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_)
