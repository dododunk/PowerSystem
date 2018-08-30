// ChangeFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "ChangeFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeFileDlg dialog


CChangeFileDlg::CChangeFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeFileDlg)
	m_xishu = 10000;
	//}}AFX_DATA_INIT
}


void CChangeFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeFileDlg)
	DDX_Text(pDX, IDC_XISHU, m_xishu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeFileDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeFileDlg)
	ON_BN_CLICKED(ID_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_SOURCEFILE, OnSourcefile)
	ON_BN_CLICKED(IDC_DESTFILE, OnDestfile)
	ON_BN_CLICKED(IDC_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeFileDlg message handlers

void CChangeFileDlg::OnClose() 
{
	CDialog::OnCancel();	
}

void CChangeFileDlg::OnSourcefile() 
{
	//打开文件对话框
	char szFilter[]="文本文件(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{
		CWnd* ptt = GetDlgItem(IDC_SOURCESTATIC);
		ptt->SetWindowText(dlg.GetPathName());
    	m_Sourefile = dlg.GetPathName();
	}	
}

void CChangeFileDlg::OnDestfile() 
{
  //保存文件对话框
	char szFilter[]="文本文件(*.TXT)|*.TXT||";

   	CFileDialog dlg(FALSE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	
	if(dlg.DoModal() == IDOK)
	{
		CWnd* ptt = GetDlgItem(IDC_DESTSTATIC);
		ptt->SetWindowText(dlg.GetPathName());	
		m_Destfile = dlg.GetPathName();
	}
	
}


void CChangeFileDlg::OnChange() 
{
    UpdateData(TRUE);
    CFile            file;
	CString     Str,m_str;
	char           s[120];
	FILE              *fp;	
	int             k = 0;
	long            i = 0;

	m_Destfile.TrimLeft();
	m_Destfile.TrimRight();
	m_Sourefile.TrimLeft();
	m_Sourefile.TrimRight();

	if(m_Sourefile.IsEmpty())
	{
		MessageBox("请选择USB采集数据源文件！！","确定",MB_OK);
		return;
	}

	if(m_Destfile.IsEmpty())
	{
		MessageBox("请选择要保存的TTT文件！！","确定",MB_OK);
		return;
	}

	if((fp=fopen(m_Sourefile,"r"))==NULL)
	{
		Str.Format("%sUSB采集数据源文件打开错误！！",m_Sourefile);
		MessageBox(Str,"确定",MB_OK);
		return;
	}
	
	if(!file.Open(m_Destfile,CFile::modeWrite | CFile::modeCreate))
	{	
		Str.Format("生成%sTTT文件错误！！",m_Sourefile);
		MessageBox(Str,"确定",MB_OK);
		return;
	}

	file.Seek(0,CFile::begin);

	CWnd* pt = GetDlgItem(IDC_SOURCEFILE);
	pt->EnableWindow(FALSE);
	pt  =   GetDlgItem(IDC_DESTFILE);
	pt->EnableWindow(FALSE);
	pt  =   GetDlgItem(ID_CLOSE);
	pt->EnableWindow(FALSE);
	pt  =   GetDlgItem(IDC_CHANGE);
	pt->EnableWindow(FALSE);
	
	while(!feof(fp))
	{
		i ++;
		fgets(s,120,fp);

		if(i > 3)
		{
		
			Str       =  s;
		
			Str.TrimLeft();
			Str.TrimRight();
	        
			if(Str.GetLength() > 7)
			{
				Str = Str.Right(7);
			}
			

		    if(atof(Str) < 0)
			{
				m_str.Format("%6d",int(atof(Str)*m_xishu - 0.1));
			}
			else
			{
				m_str.Format("%6d",int(atof(Str)*m_xishu + 0.1));
			}
					
			m_str = m_str + "\r\n";
			file.Write(m_str,8);
			
		}

	}
	
    file.Close();
	fclose(fp);
	
	pt = GetDlgItem(IDC_SOURCEFILE);
	pt->EnableWindow(TRUE);
	pt  =   GetDlgItem(IDC_DESTFILE);
	pt->EnableWindow(TRUE);
	pt  =   GetDlgItem(ID_CLOSE);
	pt->EnableWindow(TRUE);
	pt  =   GetDlgItem(IDC_CHANGE);
	pt->EnableWindow(TRUE);
	
	Str.Format("生成%sTTT文件结束！！",m_Sourefile);
	MessageBox(Str," ",MB_OK);

}

BOOL CChangeFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Destfile  =  "";
	m_Sourefile =  "";	
	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}
