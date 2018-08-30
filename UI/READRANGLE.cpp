// READRANGLE.cpp : implementation file
//

#include "stdafx.h"
#include <cmath>



#include "IFRMView.h"
#include "READRANGLE.h"
#include "TRansformerdisppearDlg.h"
#include "DataBaseInstance.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CREADRANGLE dialog


CREADRANGLEDlg::CREADRANGLEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CREADRANGLEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CREADRANGLE)
	m_radio1       =    0;
	m_radio3       =    0;
	m_radio4       =    0;
	m_Isygdd       =  TRUE;
	m_Iswgdd       = FALSE;
	m_IsSanCurrent = FALSE;
	m_IsSanVoltage = FALSE;
	m_Isjfdd       = FALSE;
	m_Isfdd        = FALSE;
	m_Ispdd        = FALSE;
	m_Isgdd        = FALSE;
	m_Isglls       = FALSE;
	//}}AFX_DATA_INIT
}


void CREADRANGLEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREADRANGLE)
	DDX_Control(pDX, IDC_SPIN, m_spin);
	DDX_Radio(pDX, IDC_RADIO5, m_radio1);
	DDX_Radio(pDX, IDC_RADIO22, m_radio3);
	DDX_Radio(pDX, IDC_RADIO28, m_radio4);
	DDX_Check(pDX, IDC_CHECK101, m_Isygdd);
	DDX_Check(pDX, IDC_CHECK102, m_Iswgdd);
	DDX_Check(pDX, IDC_CHECK103, m_IsSanCurrent);
	DDX_Check(pDX, IDC_CHECK104, m_IsSanVoltage);
	DDX_Check(pDX, IDC_CHECK105, m_Isjfdd);
	DDX_Check(pDX, IDC_CHECK106, m_Isfdd);
	DDX_Check(pDX, IDC_CHECK107, m_Ispdd);
	DDX_Check(pDX, IDC_CHECK108, m_Isgdd);
	DDX_Check(pDX, IDC_CHECK109, m_Isglls);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CREADRANGLEDlg, CDialog)
	//{{AFX_MSG_MAP(CREADRANGLE)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREADRANGLE message handlers

void CREADRANGLEDlg::OnRadio5() 
{	
	CWnd* pt = GetDlgItem(IDOK);
	pt->EnableWindow(TRUE);
}

void CREADRANGLEDlg::OnRadio41() 
{	
	CWnd* pt = GetDlgItem(IDOK);
	pt->EnableWindow(FALSE);

	CTRansformerdisppearDlg  dlg;

	if(dlg.DoModal() == IDOK)
	{
		m_GetSubRangeStr = dlg.m_GetSubRangeStr;
		m_GetSubNameStr  = dlg.m_GetSubNameStr;
		pt->EnableWindow(TRUE);
	}

}



BOOL CREADRANGLEDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString         Str;
	
	OnRadio5();

	//驻留时间点(0-23点)
	m_spin.SetRange(0,23);

	if(m_days == 0)
	{
		Str.Format("所有日期读表范围、内容及驻留时刻点设置");
	}
	else
	{
		Str.Format("【%d】号读表范围、内容及驻留时刻点设置",m_days);
	}
	
	SetWindowText(Str);
    CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CREADRANGLEDlg::OnOK() 
{
    UpdateData(TRUE);	
	CString          str,strsql;
	int          m_BitValue = 0;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//有功、无功、三相电流、三相电压、尖峰电量、峰电量、平电量、谷电量、功率因素
	if(!(m_Isygdd || m_Iswgdd || m_IsSanCurrent || m_IsSanVoltage || m_Isjfdd || m_Isfdd || m_Ispdd || m_Isgdd || m_Isglls))
	{
		MessageBox("请选择驻留读表内容！","警告",MB_OK|MB_ICONWARNING);
		return;
	}

	//检查时间有效性
	if(m_days  == 1)
	{
		
		//如果第31天有设置
		if(pview->m_DateReadParameter[60] > 0)
		{
			
			//如果第一天时间点大于最后一天时间点
			if(m_spin.GetPos() < (pview->m_DateReadParameter[61]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n31号的驻留时间点为:%2d点，\r\n两时间间隔小于24小时，请重设！",m_spin.GetPos(),pview->m_DateReadParameter[61]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//如果是小月时，30号
		if(pview->m_DateReadParameter[58] > 0)
		{
			
			//如果第一天时间点大于最后一天时间点
			if(m_spin.GetPos() < (pview->m_DateReadParameter[59]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n30号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，请重设！",m_spin.GetPos(),pview->m_DateReadParameter[59]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//如果是小月时，29号
		if(pview->m_DateReadParameter[56] > 0)
		{
			
			//如果第一天时间点大于最后一天时间点
			if(m_spin.GetPos() < (pview->m_DateReadParameter[57]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n29号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，请重设！",m_spin.GetPos(),pview->m_DateReadParameter[57]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//如果是小月时，28号
		if(pview->m_DateReadParameter[54] > 0)
		{
			
			//如果第一天时间点大于最后一天时间点
			if(m_spin.GetPos() < (pview->m_DateReadParameter[55]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n28号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，请重设！",m_spin.GetPos(),pview->m_DateReadParameter[55]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}
		
	}
	else if(m_days == 31)
	{
		
		//如果第一天有设置
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//最后一天,如果最后一天时间点如果大于第一天时间点
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n31号的驻留时间点为:%2d点，\r\n两时间间隔小于24小时，重设！",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}
	else if(m_days == 30)
	{
		
		//如果第一天有设置
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//最后一天,如果最后一天时间点如果大于第一天时间点
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n30号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，重设！",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}
	else if(m_days == 29)
	{
		
		//如果第一天有设置
		if(pview->m_DateReadParameter[0] > 0)
		{

			//最后一天,如果最后一天时间点如果大于第一天时间点
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n29号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，重设！",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}	
	else if(m_days == 28)
	{
		
		//如果第一天有设置
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//最后一天,如果最后一天时间点如果大于第一天时间点
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1号的驻留时间点为:%2d点，\r\n28号的驻留时间点为:%2d点，\r\n小月时两时间间隔小于24小时，重设！",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}


	//如果小于前一天
	if(pview->m_DateReadParameter[2*(m_days-2)] > 0)
	{
		
		if(m_spin.GetPos() < (pview->m_DateReadParameter[2*(m_days-2)+1]))
		{
			str.Format("%2d号的驻留时间点设置为:%2d点，\r\n%2d号的驻留时间点设置为:%2d点，\r\n两时间间隔小于24小时，重设！",m_days-1,pview->m_DateReadParameter[2*(m_days-2) + 1],m_days,m_spin.GetPos());
			MessageBox(str," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
	}
	
	//如果大于后一天
	if(pview->m_DateReadParameter[2*m_days] > 0)
	{
		
		if(m_spin.GetPos() > pview->m_DateReadParameter[2*m_days+1])
		{
			str.Format("%2d号的驻留时间点设置为:%2d点，\r\n%2d号的驻留时间点设置为:%2d点，\r\n两时间间隔小于24小时，重设！",m_days+1,pview->m_DateReadParameter[2*m_days+1],m_days,m_spin.GetPos());
			MessageBox(str," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
	}
	

	str    =      "【读表对象】\r\n";
 
	//读表对象
	if(m_radio1 ==1)
	{
		str = str + m_GetSubNameStr;
	}
	else
	{
		str = str + "所有线路所有表";
	}
	
	m_AppearStr = m_AppearStr + str + "\r\n";
	
	str    =      "【读表内容】\r\n";
	
	//读表内容

	
	m_ReadRangeStr = "";

	//有功
	if(m_Isygdd)
	{
		
		if(m_radio3 == 0)
		{
			m_BitValue = m_BitValue + int(pow((double)2,10));
			str        = str + "有功电度  ";
		}
		else
		{	
			m_BitValue = m_BitValue + int(pow((double)2,10)) + int(pow((double)2,(int)9));
			str        = str + "有功、总有功电度  ";
		}

	}


	//无功
	if(m_Iswgdd)
	{
		
		if(m_radio4 == 0)
		{	
			m_BitValue = m_BitValue + int(pow((double)2,8));
			str        = str + "无功电度  ";
		}
		else
		{	
			m_BitValue = m_BitValue + int(pow((double)2,8))+ int(pow((double)(int)2,(int)7));
			str        = str + "无功、总无功电度  ";
		}

	}

    
	//ABC三相电流
	if(m_IsSanCurrent)
	{
		m_BitValue = m_BitValue + int(pow((double)2,6));
		str        = str + "ABC三相电流  ";
	}

	
	//ABC三相电压
	if(m_IsSanVoltage)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,5));
		str        = str + "ABC三相电压  ";
	}
	
	
	//尖峰电量
	if(m_Isjfdd)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,4));
		str        = str + "尖峰电量  ";
	}


	//峰电量
	if(m_Isfdd)
	{
		m_BitValue = m_BitValue + int(pow((double)2,3));
		str        = str + "峰电量  ";
	}


    //平电量
	if(m_Ispdd)
	{
		m_BitValue = m_BitValue + int(pow((double)2,2));
		str        = str     + "平电量  ";
	}


    //谷电量
	if(m_Isgdd)
	{	
		m_BitValue = m_BitValue + int(pow((double)(int)2,(int)1));
		str        = str  +    "谷电量  ";
	}  
	
	
	//功率因素
	if(m_Isglls)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,0));
		str            = str + "功率因素  ";
	} 

    m_ReadRangeStr.Format("%03x",m_BitValue);

	m_AppearStr = m_AppearStr + str + "\r\n";

	str.Format("【驻留时刻】 \r\n%2d点",m_spin.GetPos());
	m_AppearStr = m_AppearStr + str + "\r\n";
	
    
	if(m_days == 0)
	{
		//所有日期读表范围、内容及驻留时刻点设置
		for(int i = 0; i < 31; i ++)
		{
			pview->m_DateReadParameter[2*i + 1]     = m_spin.GetPos();
		}

	}
	else
	{
	  	//号读表范围、内容及驻留时刻点设置
		pview->m_DateReadParameter[2*(m_days-1)    ] =               1;
		pview->m_DateReadParameter[2*(m_days-1) + 1] = m_spin.GetPos();

		//初始化当时状态为空
		strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')",(m_days-1)*3+1,"000");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);

		//如果为空则为全
        if(m_radio1 == 0)
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')",(m_days-1)*3+1,m_ReadRangeStr);
		}
		else
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')  WHERE %s",(m_days-1)*3+1,m_ReadRangeStr,m_GetSubRangeStr);
		}	
        
    	CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	}

	CDialog::OnOK();
}
