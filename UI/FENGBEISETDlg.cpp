// FENGBEISET.cpp : implementation file
//

#include "stdafx.h"



#include "IFRMView.h"
#include "FENGBEISETDlg.h"
#include "READRANGLE.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFENGBEISET dialog


CFENGBEISETDlg::CFENGBEISETDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFENGBEISETDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFENGBEISET)
	m_AppearStrs = _T("");
	//}}AFX_DATA_INIT
}


void CFENGBEISETDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFENGBEISET)
	DDX_Text(pDX, IDC_APPEARSTR, m_AppearStrs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFENGBEISETDlg, CDialog)
	//{{AFX_MSG_MAP(CFENGBEISET)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON24, OnButton24)
	ON_BN_CLICKED(IDC_BUTTON29, OnButton29)
	ON_BN_CLICKED(IDC_BUTTON34, OnButton34)
	ON_BN_CLICKED(IDC_BUTTON39, OnButton39)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON25, OnButton25)
	ON_BN_CLICKED(IDC_BUTTON30, OnButton30)
	ON_BN_CLICKED(IDC_BUTTON35, OnButton35)
	ON_BN_CLICKED(IDC_BUTTON40, OnButton40)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON36, OnButton36)
	ON_BN_CLICKED(IDC_BUTTON41, OnButton41)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON27, OnButton27)
	ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	ON_BN_CLICKED(IDC_BUTTON37, OnButton37)
	ON_BN_CLICKED(IDC_BUTTON42, OnButton42)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFENGBEISET message handlers

BOOL CFENGBEISETDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd*        pt;

	if(!m_Result[0])
	{
		pt = GetDlgItem(IDC_BUTTON1);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[1])
	{
		pt = GetDlgItem(IDC_BUTTON14);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[2])
	{
		pt = GetDlgItem(IDC_BUTTON19);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[3])
	{
		pt = GetDlgItem(IDC_BUTTON24);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[4])
	{
		pt = GetDlgItem(IDC_BUTTON29);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[5])
	{
		pt = GetDlgItem(IDC_BUTTON34);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[6])
	{
		pt = GetDlgItem(IDC_BUTTON39);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[7])
	{
		pt = GetDlgItem(IDC_BUTTON10);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[8])
	{
		pt = GetDlgItem(IDC_BUTTON15);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[9])
	{
		pt = GetDlgItem(IDC_BUTTON20);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[10])
	{
		pt = GetDlgItem(IDC_BUTTON25);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[11])
	{
		pt = GetDlgItem(IDC_BUTTON30);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[12])
	{
		pt = GetDlgItem(IDC_BUTTON35);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[13])
	{
		pt = GetDlgItem(IDC_BUTTON40);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[14])
	{
		pt = GetDlgItem(IDC_BUTTON11);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[15])
	{
		pt = GetDlgItem(IDC_BUTTON16);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[16])
	{
		pt = GetDlgItem(IDC_BUTTON21);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[17])
	{
		pt = GetDlgItem(IDC_BUTTON26);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[18])
	{
		pt = GetDlgItem(IDC_BUTTON31);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[19])
	{
		pt = GetDlgItem(IDC_BUTTON36);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[20])
	{
		pt = GetDlgItem(IDC_BUTTON41);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[21])
	{
		pt = GetDlgItem(IDC_BUTTON12);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[22])
	{
		pt = GetDlgItem(IDC_BUTTON17);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[23])
	{
		pt = GetDlgItem(IDC_BUTTON22);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[24])
	{
		pt = GetDlgItem(IDC_BUTTON27);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[25])
	{
		pt = GetDlgItem(IDC_BUTTON32);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[26])
	{
		pt = GetDlgItem(IDC_BUTTON37);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[27])
	{
		pt = GetDlgItem(IDC_BUTTON42);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[28])
	{
		pt = GetDlgItem(IDC_BUTTON13);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[29])
	{
		pt = GetDlgItem(IDC_BUTTON18);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[30])
	{
		pt = GetDlgItem(IDC_BUTTON23);
		pt->EnableWindow(FALSE);
	}	m_AppearStrs   = "";
	CString         str,str1;
	str = str1 =   "";

	for(int i = 0 ; i < 31; i ++)
	{
		
		if(m_Result[i])
		{

			str1.Format("%2d",i + 1);
			
			if(str.IsEmpty())
			{
				str = str + str1;
			}
			else
			{
				str = str + "、" + str1 ;
			}
			
		}
		
	}

	m_AppearStrs = "【应设驻留日期】" + str ;

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFENGBEISETDlg::OnButton1() 
{
	//分设置1号
	CREADRANGLEDlg dlg;
	dlg.m_days     =   1;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[0]            = " 1号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
	}
	
}

void CFENGBEISETDlg::OnButton14() 
{
	//分设置2号
	CREADRANGLEDlg dlg;
	dlg.m_days     =  2;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[1]            = " 2号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}		
}

void CFENGBEISETDlg::OnButton19() 
{
	//分设置3号
	CREADRANGLEDlg dlg;
	dlg.m_days     =   3;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[2]            = " 3号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton24() 
{
	//分设置4号
	CREADRANGLEDlg     dlg;
	dlg.m_days     =  4;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[3]            = " 4号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton29() 
{
	//分设置5号
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   5;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[4]            = " 5号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton34() 
{
	//分设置6号
	CREADRANGLEDlg     dlg;
	dlg.m_days     =  6;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[5]            = " 6号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton39() 
{
	//分设置7号
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   7;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[6]            = " 7号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton10() 
{
	//分设置8号
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   8;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[7]            = " 8号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton15() 
{
	//分设置9号
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   9;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[8]            = " 9号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
	   	//刷新显示
		Refresh();
		
	}
				
}

void CFENGBEISETDlg::OnButton20() 
{
	//分设置10号
	CREADRANGLEDlg      dlg;
	dlg.m_days     =  10;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[9] = "10号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton25() 
{
	//分设置11号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  11;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[10] = "11号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton30() 
{
	//分设置12号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  12;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[11] = "12号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton35() 
{
	//分设置13号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  13;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[12] = "13号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton40() 
{
	//分设置14号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  14;	
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[13] = "14号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton11() 
{
	//分设置15号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  15;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[14] = "15号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
	    //刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton16() 
{
	//分设置16号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  16;	

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[15] = "16号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
	    //刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton21() 
{
	//分设置17号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  17;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[16] = "17号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton26() 
{
	//分设置18号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  18;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[17] = "18号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton31() 
{
	//分设置19号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  19;	
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[18] = "19号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton36() 
{
	//分设置20号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  20;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[19] = "20号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton41() 
{
	//分设置21号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  21;

	if(dlg.DoModal() == IDOK)
	{
		
	    m_AppearStr[20] = "21号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton12() 
{
	//分设置22号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  22;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[21] = "22号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton17() 
{
	//分设置23号
	CREADRANGLEDlg  dlg;
	dlg.m_days      =  23;	

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[22] = "23号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton22() 
{
	//分设置24号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  24;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[23] = "24号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton27() 
{
	//分设置25号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  25;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[24] = "25号驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton32() 
{
	//分设置26号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  26;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[25] = "26驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton37() 
{
	//分设置27号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  27;	

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[26] = "27驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
	  	//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton42() 
{
	//分设置28号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  28;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[27] = "28驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton13() 
{
	//分设置29号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  29;

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[28]= "29驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton18() 
{
	//分设置30号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  30;	

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[29]= "30驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton23() 
{
	//分设置31号
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  31;	

	if(dlg.DoModal() == IDOK)
	{	
		m_AppearStr[30]= "31驻留读表设置如下:\r\n" + dlg.m_AppearStr;
		
		//刷新显示
		Refresh();
		
	}	
}

//刷新显示
void CFENGBEISETDlg::Refresh()
{
	m_AppearStrs   = "";
	CString         str,str1,str3,strsql;
    str = str1 =   "";
	
	int j  =        1;

	for(int i = 0 ; i < 31; i ++)
	{
		
		//显示要设置的日期
		if(m_Result[i])
		{

			str1.Format("%2d",i + 1);
			
			if(str3.IsEmpty())
			{
				str3 = str3 + str1;
			}
			else
			{
				str3 = str3 + "、" + str1 ;
			}
			
		}

		//显示已设置的日期
		if(!m_AppearStr[i].IsEmpty())
		{

			str1.Format("%2d",i + 1);

			if(str.IsEmpty())
			{
				str = str + str1;
			}
			else
			{
				str = str + "、" + str1 ;
			}

			str1.Format("%2d、%s",j,m_AppearStr[i] + "\r\n");

			m_AppearStrs = m_AppearStrs + str1;
			
			j ++;

		}
		
	}

	m_AppearStrs = "【应设驻留日期】" + str3 + "\r\n" + "【已设驻留日期】" +  str + "\r\n\r\n详细设置如下：\r\n" + m_AppearStrs;

	UpdateData(FALSE);
}

void CFENGBEISETDlg::OnOK() 
{
    BOOL m_Passing  =  TRUE;
	CString             str;
	int i = 0;
	for( i = 0 ; i < 31; i ++)
	{
		
		//显示要设置的日期
		if(m_Result[i])
		{
			//显示已设置的日期
			if(m_AppearStr[i].IsEmpty())
			{
				m_Passing = FALSE;
				break;
			}
			
		}
		
	}

	//检查是否通过
	if(!m_Passing)
	{
		str.Format("【%d】号驻留参数没有设置好！！",i + 1);
		MessageBox(str,"警告",MB_OK|MB_ICONWARNING);
		return;
	}

	
	CDialog::OnOK();
}
