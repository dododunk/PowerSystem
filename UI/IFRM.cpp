// IFRM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "IFRM.h"
#include "MainFrm.h"
#include "IFRMDoc.h"

#include "IFRMView.h"
#include "CreditsDlg.h"
#include "PassWordDlg.h"
#include "HyperLink.h" 
#include "RuntimeAccount.h"
#include "AppInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp

BEGIN_MESSAGE_MAP(CIFRMApp, CWinApp)
	//{{AFX_MSG_MAP(CIFRMApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp construction

CIFRMApp::CIFRMApp()
{
	AppInfo::Instance().m_WhichKind        =  FALSE; //TRUE  变电站版本   MessageBeep                   FALSE 电局版
	AppInfo::Instance().m_2000Users        =  FALSE; //TRUE 2000用户   TRUE用户数不受限制
	AppInfo::Instance().m_AutoRunning      =  TRUE;  //TRUETRUE是否一启动就自动运行
	AppInfo::Instance().m_SingleBB         =  TRUE; //FALSE是否是单一版本
	AppInfo::Instance().m_YanShi           =  FALSE; //FALSETRUE; //是否是演示版本
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFRMApp object

CIFRMApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CIFRMApp initialization

BOOL CIFRMApp::InitInstance()
{

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    
//	AfxMessageBox(m_pszAppName);

	//此程序只能运行一次，用互斥量来判断程序是否已运行
    HANDLE m_hMutex = CreateMutex(NULL,TRUE, m_pszAppName); 
   
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{ 
		//::MessageBox("发现有相同此软件已经正在运行！"," ",MB_OK|MB_ICONWARNING);
		//AfxMessageBox("发现有相同此软件正在运行！",MB_OK, 0 );
		return FALSE; 
	}


	//设置对话框背景和文本颜色
	//SetDialogBkColor(RGB(221,221,221),RGB(0,0,0));	//160,180,220
	
	//SetDialogBkColor(RGB(0xFF, 0xFF, 0xE0),RGB(0, 0,0));
	//SetDialogBkColor(RGB(0,255,255), RGB(0, 0,255));
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
    
	//是否一启动就自动运行
	
	if(!AppInfo::Instance().m_AutoRunning)
	{
		CPassWordDlg  password;

		password.m_SingleBB = AppInfo::Instance().m_SingleBB;

		if(password.DoModal() != IDOK)
		{
			return  FALSE;
		}
		
		//版本种类 0 远程    1 本地
		AppInfo::Instance().m_WhichKind  = password.m_softkind; 
		//权利等级划分0 ---超级 1-普超 2-普用 3-过客
		//m_RightGrade = password.m_userkind;	

	}
	else
	{
		//版本种类 0 远程    1 本地
		AppInfo::Instance().m_WhichKind  = 1; 
		//权利等级划分0 ---超级 1-普超 2-普用 3-过客
		//chh m_RightGrade = 0;	
	}

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.
    

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIFRMDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CIFRMView));
	
	/*pDocTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));*/
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	CString   UseName,TitleName;
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);

	switch(CRuntimeAccount::GetCurrentPrivilege())
	{
	case 0:
		{
			UseName = "高级管理员";
			break;
		}
	case 1:
		{
			UseName = "普通管理员";
			break;
		}
	case 2:
		{
			UseName = "高级用户";
			break;
		}
	case 3:
		{
			UseName = "普通用户";
			break;
		}
	}
	
	if(AppInfo::Instance().m_WhichKind)//选择哪种表 //TRUE 变电站版本  FALSE电局版
	{
		
		//m_2000Users  TRUE 2000用户 FALSE 用户数不受限制
		if(AppInfo::Instance().m_2000Users)
		{
		
			TitleName.Format("工频畸变远程抄表系统1.90f本地版-[2000用户-%s]",UseName);
		
		}
		else
		{
			
			TitleName.Format("工频畸变远程抄表系统1.90f版-[%s]",UseName);//本地
		
		}
		
	}
	else
	{	
		
		//m_2000Users  TRUE 2000用户 FALSE 用户数不受限制
		if(AppInfo::Instance().m_2000Users)
		{  
			TitleName.Format("工频畸变远程抄表系统1.90f远程版-[2000用户-%s]",UseName);
		}
		else
		{	
			TitleName.Format("工频畸变远程抄表系统1.90f远程版-[%s]",UseName);
		}
		
	}
	
	//是否是演示版本
	if(AppInfo::Instance().m_YanShi)
	{
		m_pMainWnd->SetWindowText(TitleName + "---演示版");
	}
	else
	{
		m_pMainWnd->SetWindowText(TitleName);
	}
	
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	
	//Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_mail;
	CHyperLink	m_address;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddress();
	afx_msg void OnEmail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL, m_mail);
	DDX_Control(pDX, IDC_ADDRESS, m_address);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_ADDRESS, OnAddress)
	ON_BN_CLICKED(IDC_EMAIL, OnEmail)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// App command to run the dialog
void CIFRMApp::OnAppAbout()
{
	//显示开始界面
    CCreditsDlg  dlg;
	dlg.DoModal();
	//CAboutDlg aboutDlg;
	//aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_mail.SetURL(_T("mailto:market@incomep.com"));
	m_mail.SetUnderline(CHyperLink::ulAlways);

	m_address.SetURL(_T("http://www.incomep.com"));
	m_address.SetUnderline(CHyperLink::ulAlways);
	
	return TRUE;  
}

void CAboutDlg::OnAddress() 
{
	// TODO: Add your control notification handler code here
	
}

void CAboutDlg::OnEmail() 
{
	// TODO: Add your control notification handler code here
	
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
