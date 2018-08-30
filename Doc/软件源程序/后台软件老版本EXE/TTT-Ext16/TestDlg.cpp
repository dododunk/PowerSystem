// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "TestDlg.h"
#include "TTT.h"
#include "TTTDoc.h"
#include "TTTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_A  =   10;
	m_B  =   10;
	m_X0 =    0;
	m_X1 = 10240;
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_DFA, m_A);
	DDX_Text(pDX, IDC_DFB, m_B);
	DDX_Text(pDX, IDC_X0, m_X0);
	DDX_Text(pDX, IDC_X1, m_X1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnOK() 
{
	UpdateData(TRUE);

	//保存文件对话框
	char szFilter[]="文本文件(*.TXT)|*.TXT||";
    CFile      file;

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

		for(int i = m_X0; i < m_X1; i ++)
		{
			file.Seek(0,CFile::current);
			str.Format("%5d",int(m_A*sin(2*3.1415926/1000*i) + m_B*sin(2*3.1415926/4400*i)));
			//str.Format("%5d",int(m_A*sin(2*3.1415926/1000*i) + m_B*sin(2*3.1415926/2000*i)));
			str = str + "\r\n";
			file.Write(str,7);
		}

		file.Close();

		MessageBox("数据文件已成功保存!","确定",MB_OK);
		CDialog::OnOK();

	}	

}
