// StationCommun.cpp : implementation file
//

#include "stdafx.h"

#include "StationCommunDlg.h"


#include "IFRMView.h"
#include "PhoneDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationCommun dialog
//MultiByteToWideChar IsTextUnicode

CStationCommunDlg::CStationCommunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStationCommunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStationCommun)
	m_Port       =   2500;
	m_telephone  = _T("");
	m_AutoAnswer =  FALSE;
	m_IfVoice    =   TRUE;
	//}}AFX_DATA_INIT
}


void CStationCommunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStationCommun)
	DDX_Control(pDX, IDC_PHONESELECT, m_PhoneSelect);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_STOPCOMBO, m_comstop);
	DDX_Control(pDX, IDC_DATACOMBO, m_comdata);
	DDX_Control(pDX, IDC_CHECKCOMBOX, m_comcheck);
	DDX_Control(pDX, IDC_COMBOPORT, m_comboport);
	DDX_Control(pDX, IDC_COMBOBIT, m_combobit);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Control(pDX, IDC_SSTAB, m_maintab);
	DDX_CBString(pDX, IDC_PHONESELECT, m_telephone);
	DDX_Check(pDX, IDC_AUTODIAL, m_AutoAnswer);
	DDX_Check(pDX, IDC_NOVOICE, m_IfVoice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStationCommunDlg, CDialog)
	//{{AFX_MSG_MAP(CStationCommun)
	ON_NOTIFY(NM_DBLCLK, IDC_COMPUTERS, OnDblclkComputers)
	ON_BN_CLICKED(IDC_NETSEARCH, OnNetsearch)
	ON_BN_CLICKED(IDC_REFRESHS, OnRefreshs)
	ON_BN_CLICKED(IDC_NETDELETE, OnNetdelete)
	ON_BN_CLICKED(IDC_DELETEPHONE, OnDeletephone)
	ON_BN_CLICKED(IDC_ADDPHONE, OnAddphone)
	ON_BN_CLICKED(IDC_AUTODIAL, OnAutodial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationCommun message handlers

BOOL CStationCommunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString         portstr;

	//串口为默认
	ShowButton(0);

	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_MODEM);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	//初始端口
	CIFRMView* pview   = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
  	m_comboport.ResetContent();

	for(int i = 0 ; i < 10 ; i ++)
	{
	   //第二个口为读线总表和站站总表专用 485  
       if(pview->Ports[i] == TRUE )
	   {
		   
		    portstr.Format("COM%d",i + 1);   
		   	//TCP/IP
		 	//TRUE 变电站版本  FALSE电局版
			if(m_WhichKind)
			{
				if( i != 1)
				{
			       m_comboport.AddString(portstr);
				}
			}
			else
			{
				//电局版
                m_comboport.AddString(portstr);
			}
	   }

	}

	//得到以前设置的参数
	GetComInfoParameter();
    
	//得到电话拔号信息
	GetAllPhoneInfo();

	//得到本机地址
	GetLocalAddress();
	
	//初始化网络
    GetAllIpAddress();
	//InitializeNet();

    CenterWindow();
	
	 //建立图标
	CBitmap *Computer = new    CBitmap;
	Computer->LoadBitmap(IDB_COMPUTER);
	m_imageList.Create(16, 16, ILC_COLOR16, 2, 2);
	m_imageList.Add(Computer, RGB(0, 0, 0,));
	delete Computer;

	UpdateData(FALSE);
	
	
	//TCP/IP
	if(m_PhoneSelect.GetCount() > 0)
	{
	
		m_PhoneSelect.SetCurSel(0);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStationCommunDlg::OnOK() 
{

	UpdateData(TRUE);
    CString    ComStr;
	int k      =    0;
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	//读数据种类
    pview->m_sendkind = m_maintab.GetTab();
	
	//如果是串口或拔号
	if(m_maintab.GetTab() == 0 || m_maintab.GetTab() == 1)
	{
		
		if(m_comboport.GetCurSel() != CB_ERR)
		{
			//索引号从0开始的
			m_comboport.GetLBText(m_comboport.GetCurSel(), ComStr);
		}
		else
		{
			MessageBox("串口选择错误！","警告",MB_OK|MB_ICONWARNING);
			return;
		} 
		
		k = ComStr.Find("M");
		if(k != -1)
		{
			k = atoi(ComStr.Right(ComStr.GetLength()- k - 1));
		}
		else
		{
			MessageBox("串口选择错误！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

	}
	
	switch(m_maintab.GetTab())
	{
	case 0:	
		{
			//串口
			//串  口 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
			//设置各种参数m_comboport.GetCurSel()
		   	pview->OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
    	  	
			//存各种参数
			SaveComInfoParameter();
			break;
		}
	case 1:	
		{
	        //电话号码
			//TRUE 变电站版本  FALSE电局版
			//设置各种参数
			pview->OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
			
			if(m_WhichKind)
			{
				//自动应答,如果没有连接则返回
				if(!pview->Connect(TRUE,m_IfVoice))
				{
					return;
				}
			}
			else
			{ 

				//拔号
				if(!m_telephone.IsEmpty())
				{

					int k = m_telephone.Find("‖");
        			m_telephone = m_telephone.Left(k);
					m_telephone.TrimLeft();
                    m_telephone.TrimRight();
					pview->Dial(m_telephone,m_IfVoice);
				  //pview->Dial(m_telephone,FALSE);
				}
				else
				{
					MessageBox("拔号电话号码不能为空!","警告",MB_OK|MB_ICONWARNING);
					return;
				}
						
			}

			//存各种参数
			SaveComInfoParameter();
			break;
		}
	case 2:	
		{
			//TCP/IP
		 	//TRUE 变电站版本  FALSE电局版
			if(m_WhichKind)
			{
		       
				//创建 TCP 服务端
				CString LocalHostAddress;	
				CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_LOCALADDRESS);
				IPAddr->GetWindowText(LocalHostAddress);
				LocalHostAddress.TrimLeft();
				LocalHostAddress.TrimRight();

				//地址不为空或"0.0.0.0"
				if(!LocalHostAddress.IsEmpty() && LocalHostAddress != "0.0.0.0")
				{
					pview->SetLocalServer(LocalHostAddress, m_Port);
				}
				else
				{	
					MessageBox("请先设置本机地址!","警告",MB_OK|MB_ICONWARNING);
					return;
				}

			}
			else
			{
				
				CString RemoteHostAddress;	
				CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
				IPAddr->GetWindowText(RemoteHostAddress);
				RemoteHostAddress.TrimLeft();
				RemoteHostAddress.TrimRight();

				//地址不为空或"0.0.0.0"
				if(!RemoteHostAddress.IsEmpty() && RemoteHostAddress != "0.0.0.0")
				{
					//创建 TCP 客户端
					RemoteHostAddress.TrimLeft();
					RemoteHostAddress.TrimRight();
			
					pview->SettcpClient(RemoteHostAddress, m_Port);
					
					//IP地址存入地址
					AddAddressToTable();

				}
				else
				{
					MessageBox("请先选择联机网址!","警告",MB_OK|MB_ICONWARNING);
					return;
				}
			
			}
			break;

		}

	}

	CDialog::OnOK();
}

void CStationCommunDlg::GetComInfoParameter()
{
	CString      str;
	CDatabase     db;
	CString   strSql;
	CString strValue;
	str        =  "";
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset  rs(&db);
       	strSql = "SELECT count(*) FROM TB_COMINFORMATION";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();
		
		if(fields <= 0)
		{
			
			m_combobit.SetCurSel(9);
			m_comboport.SetCurSel(0);
			m_comstop.SetCurSel(0);
			m_comdata.SetCurSel(4);
			m_comcheck.SetCurSel(0);
			m_AutoAnswer =    FALSE;
			
		}
		else
		{
			strSql = "SELECT * FROM TB_COMINFORMATION";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
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
						if(m_comboport.GetCount() > 0)
						{
							
							//如果
							if(atoi(str) > m_comboport.GetCount())
							{
								m_comboport.SetCurSel(0);
							}
							else
							{
								m_comboport.SetCurSel(atoi(str));
							}
							
						}
						break;
					}
				case 1:
					{
						//波特率
						m_combobit.SetCurSel(atoi(str));
						break;
					}
				case 2:
					{
						//检验位
						m_comcheck.SetCurSel(atoi(str));
						break;
					}
				case 3:
					{
						//数据位
						m_comdata.SetCurSel(atoi(str));
						break;
					}
				case 4:
					{
						//停止位
						m_comstop.SetCurSel(atoi(str));
						break;
					}
				case 5:
					{
						//自动应答
						m_AutoAnswer = atoi(str);
						break;
					}
					
				}
				
				
			}
			
			//关闭数据库
			rs.Close( );
			db.Close( );
			
		}
	
	}

}

//罗列网上邻居
void CStationCommunDlg::InitializeNet()
{
	
	CString      strTemp;	
	int    item    =   0;
	struct hostent *host;
	struct in_addr  *ptr;
	
	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);

	//向列表框中添加列
	List->DeleteAllItems( );       //删除列表中所有内容(行)
	while (List->DeleteColumn(0)); //删除列表中所有列

	// 设置list控件格式	
    List->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	List->SetImageList(&m_imageList, LVSIL_SMALL);
	
	//写入列标题
	List->InsertColumn(0, "IP地址", LVCFMT_LEFT, 170);
	List->InsertColumn(1, "计算机名称", LVCFMT_LEFT, 170);

	//找出计算机名称及IP地址
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);	
	DWORD dwScope = RESOURCE_CONTEXT;
	NETRESOURCE *NetResource = NULL;
	HANDLE hEnum; 
	WNetOpenEnum(dwScope, NULL, NULL, NULL, &hEnum);

	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1),&wsaData);

	if (hEnum)
	{
		DWORD Count = 0xFFFFFFFF;
		DWORD BufferSize = 2048;
		LPVOID Buffer  =  new   char[2048];
		WNetEnumResource(hEnum, &Count, Buffer, &BufferSize);
		NetResource = (NETRESOURCE*)Buffer;
		char               szHostName[200];
		for (unsigned int i = 0; i < BufferSize/sizeof(NETRESOURCE); i++, NetResource++)
		{

			if (NetResource->dwUsage == RESOURCEUSAGE_CONTAINER && NetResource->dwType == RESOURCETYPE_ANY)
			{

				if (NetResource->lpRemoteName)
				{
					CString strFullName = NetResource->lpRemoteName;
					char buf[512];
					if ( 0 == strFullName.Left(2).Compare("\\\\"))
					strFullName = strFullName.Right(strFullName.GetLength()-2);
					gethostname(szHostName, strlen( szHostName ));
					host = gethostbyname(strFullName);
					if (!host) continue;
					ptr = (struct in_addr *) host->h_addr_list[0];
					sprintf(buf, "%d.%d.%d.%d", ptr->S_un.S_un_b.s_b1, 
						ptr->S_un.S_un_b.s_b2, ptr->S_un.S_un_b.s_b3, ptr->S_un.S_un_b.s_b4);
					List->InsertItem(item++, buf, 0);
					List->SetItemText(item - 1, 1, strFullName);
				//	List->SetItemText(item - 1, 2, NetResource->lpComment);

				}

			}

		}
		delete Buffer;
		WNetCloseEnum(hEnum);
	}
	WSACleanup();
}


void CStationCommunDlg::OnDblclkComputers(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CEdit *Host = (CEdit *)GetDlgItem(IDC_HOST);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	int mark = List->GetSelectionMark();
	if(mark < 0)
	{
		return;
	}

	char buf[512];
	List->GetItemText(mark, 0, buf, sizeof(buf));
	IPAddr->SetWindowText(buf);
	List->GetItemText(mark, 1, buf, sizeof(buf));
	Host->SetWindowText(buf);	
	*pResult = 0;
}



void CStationCommunDlg::GetLocalAddress()
{
	
	struct hostent *host;
	struct  in_addr *ptr;
	char        buf[512];
	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_LOCALADDRESS);


	GetDlgItem(IDC_HOST)->GetWindowText(buf, sizeof(buf));
	host = gethostbyname(buf);
	
	if (!host) 
	{
		IPAddr->SetWindowText("0.0.0.0");
		return;
	}
	else
	{
		ptr = (struct in_addr *) host->h_addr_list[0];
		sprintf(buf, "%d.%d.%d.%d", ptr->S_un.S_un_b.s_b1, 
			ptr->S_un.S_un_b.s_b2, ptr->S_un.S_un_b.s_b3, ptr->S_un.S_un_b.s_b4);
		IPAddr->SetWindowText(buf);	
	}

}

BEGIN_EVENTSINK_MAP(CStationCommunDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CStationCommun)
	ON_EVENT(CStationCommunDlg, IDC_SSTAB, -600 /* Click */, OnClickSstab, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CStationCommunDlg::OnClickSstab(short PreviousTab) 
{
   //串口为默认
   ShowButton(m_maintab.GetTab());
}


//存拔号号码和端口参数
void CStationCommunDlg::SaveComInfoParameter()
{
	CDatabase  dbs;
	CString StrSql;

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	{	
	
		StrSql = "DELETE FROM TB_COMINFORMATION";
		dbs.ExecuteSQL(StrSql);
		StrSql.Format("INSERT INTO TB_COMINFORMATION(COMINFORMATION_COM,COMINFORMATION_BITS,COMINFORMATION_CHECKBIT,COMINFORMATION_DATABIT,COMINFORMATION_STOPBIT,COMINFORMATION_AUTOREPLY) VALUES (%d,%d,%d,%d,%d,%d)",m_comboport.GetCurSel(),m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel(),m_AutoAnswer);
		dbs.ExecuteSQL(StrSql);
		dbs.Close();
	}
	   
}


void CStationCommunDlg::OnNetsearch() 
{
	//查找网络邻居
	InitializeNet();
	CWnd* pt = GetDlgItem(IDC_NETDELETE);
	pt->EnableWindow(FALSE);
}

//得到库文件中存的IP地址
void CStationCommunDlg::GetAllIpAddress()
{

	CDatabase                        db;
	CString                      strSql;
	CString strValue,HostName,IPAddrStr;
	int  item             =           0;

	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);

	//向列表框中添加列
	List->DeleteAllItems( );       //删除列表中所有内容(行)
	while (List->DeleteColumn(0)); //删除列表中所有列

	List->SetImageList(&m_imageList, LVSIL_SMALL);
	
	//写入列标题
	List->InsertColumn(0, "IP地址", LVCFMT_LEFT, 170);
	List->InsertColumn(1, "计算机名称", LVCFMT_LEFT, 170);

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
       	strSql = "SELECT count(*) FROM TB_IP";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();

	    if(fields > 0)
		{

			strSql = "SELECT * FROM TB_IP";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//读用户信息
			for(int j = 0;j < fields; j++)
			{
                
				//地址去空格
				rs.GetFieldValue((short)0,IPAddrStr);
                
				IPAddrStr.TrimLeft();
				IPAddrStr.TrimRight();
                
				//主机去空格
				rs.GetFieldValue((short)1,HostName);
               	HostName.TrimLeft();
				HostName.TrimRight();
					
				List->InsertItem(item++, IPAddrStr, 0);
				List->SetItemText(item-1, 1, HostName);		

				//库下滑一个记录
				rs.MoveNext();

			}
			
			//关闭数据库
		    rs.Close( );

		}
		db.Close( );
	}

}

//得到库文件中存的IP地址
void CStationCommunDlg::OnRefreshs() 
{
    GetAllIpAddress();
	CWnd* pt = GetDlgItem(IDC_NETDELETE);
	pt->EnableWindow(TRUE);
}

void CStationCommunDlg::OnNetdelete() 
{   
    char buf[20];
   	CString      IPAddrStr,SqlStr;
	
	

	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	int mark = List->GetSelectionMark();
	if(mark < 0 )
	{
		return;
	}

	List->GetItemText(mark, 0, buf, sizeof(buf));
	IPAddrStr = buf;

	IPAddrStr.TrimLeft();
	IPAddrStr.TrimRight();

    if(MessageBox("你想删除列表中的" + IPAddrStr + "IP地址吗？","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		//有此IP地址,则删除此记录
		SqlStr.Format("DELETE FROM TB_IP WHERE IP_ADDRESS='%s'",IPAddrStr);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
		
		//得到库文件中存的IP地址
		GetAllIpAddress();  
	}

}

//得到电话拔号信息
void CStationCommunDlg::GetAllPhoneInfo()
{
	//打开数据库
	CDatabase           db;
	CString         strSql;
	CString       strValue;
	CString fieldname = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//和CRecordset连上
		CRecordset rs(&db );
	    strSql = "SELECT count(*) FROM TB_PHONE";
			
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();
		
		//删除原来的列表数据
		m_PhoneSelect.ResetContent();

		if(fields  > 0)
		{
      	    strSql = "SELECT PHONE_NO,PHONE_NAME FROM TB_PHONE";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//读用户信息
			for(int j = 0;j < fields; j++)
			{
				
				//电话号码
				rs.GetFieldValue((short)0,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
				strSql = strValue;	
				rs.GetFieldValue((short)1,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
				strSql = strSql + "‖" + strValue;
				
				//加入列表框
				m_PhoneSelect.AddString(strSql);
						
				//库下滑一个记录
				rs.MoveNext();

			}
		
			//关闭数据库
		    rs.Close( );
		
		}
		
		//如果个数大于0
		if(m_PhoneSelect.GetCount() > 0)
		{
			m_PhoneSelect.SetCurSel(0);
		}

		db.Close( );
	}

}


//删除电话记录
void CStationCommunDlg::OnDeletephone() 
{
	CString m_Phones,SqlStr;
	int                   k;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(m_PhoneSelect.GetCurSel() != CB_ERR)
	{
		m_PhoneSelect.GetLBText(m_PhoneSelect.GetCurSel(),m_Phones); 
        k = m_Phones.Find("‖");
        
		m_Phones = m_Phones.Left(k);
		
		if(MessageBox("你想删除列表中电话号话[" + m_Phones + "]吗？","询问",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
		   return;
		}

		//有此电话号码,则删除此记录
		SqlStr.Format("DELETE FROM TB_PHONE WHERE RTRIM(PHONE_NO)='%s'",m_Phones);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr); 

		//得到电话拔号信息
        GetAllPhoneInfo();
	}
	
}

void CStationCommunDlg::ShowButton(short kinds)
{	
	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    switch(kinds)
	{
	case 0:	
		{
			//串口
		    CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
						
			//电话
			pwnd = GetDlgItem(IDC_TELEPHONETXT);
			pwnd->ShowWindow(SW_HIDE);
            pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOST);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOSTTXT);
			pwnd->ShowWindow(SW_HIDE);
			
			pwnd = GetDlgItem(IDC_NETSEARCH);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_NETDELETE);
			pwnd->ShowWindow(SW_HIDE);
         	pwnd = GetDlgItem(IDC_REFRESHS);
			pwnd->ShowWindow(SW_HIDE);

	        pwnd = GetDlgItem(IDC_PHONESELECT);
			pwnd->ShowWindow(SW_HIDE); 
			pwnd = GetDlgItem(IDC_DELETEPHONE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_ADDPHONE);
			pwnd->ShowWindow(SW_HIDE);
			//自动应答参数
			pwnd = GetDlgItem(IDC_AUTODIAL);
			pwnd->ShowWindow(SW_HIDE);

	        pwnd = GetDlgItem(IDOK);
			pwnd->SetWindowText("连接");
	       	break;
		}
	case 1:	
		{
			//电话拔号
			CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_SHOW); 
			pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			
            //TRUE 变电站版本  FALSE电局版
	        //电话号码
	        if(!m_WhichKind)
			{
				pwnd = GetDlgItem(IDC_TELEPHONETXT);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_PHONESELECT);
				pwnd->ShowWindow(SW_SHOW); 
				pwnd = GetDlgItem(IDC_DELETEPHONE);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_ADDPHONE);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("拔号");
				//自动应答参数
				pwnd = GetDlgItem(IDC_AUTODIAL);
			    pwnd->ShowWindow(SW_HIDE);
               
			}
			else
			{ 
				pwnd = GetDlgItem(IDC_TELEPHONETXT);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_PHONESELECT);
				pwnd->ShowWindow(SW_HIDE); 
				pwnd = GetDlgItem(IDC_DELETEPHONE);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_ADDPHONE);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("自动应答");
				//自动应答参数
				pwnd = GetDlgItem(IDC_AUTODIAL);
			    pwnd->ShowWindow(SW_SHOW);	
			}
	        
			//拔号
		    if(!pview->m_Com.GetCDHolding())
			{
				pwnd = GetDlgItem(IDOK);
				pwnd->EnableWindow(TRUE);
			}
			else
			{
				pwnd = GetDlgItem(IDOK);
				pwnd->EnableWindow(FALSE);
			}

			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOST);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOSTTXT);
			pwnd->ShowWindow(SW_HIDE);

			pwnd = GetDlgItem(IDC_NETSEARCH);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_NETDELETE);
			pwnd->ShowWindow(SW_HIDE);
         	pwnd = GetDlgItem(IDC_REFRESHS);
			pwnd->ShowWindow(SW_HIDE);
			break;
		}
	case 2:	
		{
			//TCP/IP
		 	CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_HIDE);
						
			//电话
			pwnd = GetDlgItem(IDC_TELEPHONETXT);
			pwnd->ShowWindow(SW_HIDE);
            pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_SHOW);
		
			pwnd = GetDlgItem(IDC_PHONESELECT);
			pwnd->ShowWindow(SW_HIDE); 

			pwnd = GetDlgItem(IDC_DELETEPHONE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_ADDPHONE);
			pwnd->ShowWindow(SW_HIDE);	
			
			//自动应答参数
			pwnd = GetDlgItem(IDC_AUTODIAL);
			pwnd->ShowWindow(SW_HIDE);
		
			//TRUE 变电站版本  FALSE电局版
	      	if(!m_WhichKind)
			{	
				pwnd = GetDlgItem(IDC_IPADDRESS);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_IPADDRESSTXT);
				pwnd->ShowWindow(SW_SHOW);

				pwnd = GetDlgItem(IDC_HOST);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_HOSTTXT);
				pwnd->ShowWindow(SW_SHOW);

				pwnd = GetDlgItem(IDC_NETSEARCH);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_NETDELETE);
				pwnd->ShowWindow(SW_SHOW);
         		pwnd = GetDlgItem(IDC_REFRESHS);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("链接");
						
			}
			else
			{	
				pwnd = GetDlgItem(IDC_IPADDRESS);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_IPADDRESSTXT);
				pwnd->ShowWindow(SW_HIDE);

				pwnd = GetDlgItem(IDC_HOST);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_HOSTTXT);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_NETSEARCH);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_NETDELETE);
				pwnd->ShowWindow(SW_HIDE);
         		pwnd = GetDlgItem(IDC_REFRESHS);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("侦听");
		
			}
			break;
		}

	}
}



void CStationCommunDlg::AddAddressToTable()
{
	CString HostName,IPAddrStr,	SqlStr;
    
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//主机名
	CEdit *Host = (CEdit *)GetDlgItem(IDC_HOST);
	Host->GetWindowText(HostName);

	//远程地址
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
    IPAddr->GetWindowText(IPAddrStr);
   
	//去空格
	IPAddrStr.TrimLeft();
	IPAddrStr.TrimRight();
    HostName.TrimLeft();
	HostName.TrimRight();

    //查询条件,是否有此记录	
	SqlStr.Format("IP_ADDRESS='%s'",IPAddrStr);

	if(CDataBaseInstance::GetAllRecordsCount("TB_IP", SqlStr) < 1)
	{
		//没有此IP地址,则插入记录								
		SqlStr.Format("INSERT INTO TB_IP(IP_ADDRESS,IP_COMPUTER) VALUES ('%s','%s')",IPAddrStr,HostName);

	}
	else
	{	
		//有此IP地址,则覆盖记录
		SqlStr.Format("UPDATE TB_IP SET IP_ADDRESS = '%s',IP_COMPUTER='%s' WHERE IP_ADDRESS='%s'",IPAddrStr,HostName,IPAddrStr);
	}
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	
}

void CStationCommunDlg::OnAddphone() 
{
	CPhoneDlg  DLG;
	DLG.DoModal();
	//得到电话信息
	GetAllPhoneInfo();	
}

void CStationCommunDlg::OnAutodial() 
{
	CString    StrSql;
	m_AutoAnswer = !m_AutoAnswer;
	UpdateData(FALSE);
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_COMINFORMATION","ALL") > 0)
	{
		StrSql.Format("UPDATE TB_COMINFORMATION SET COMINFORMATION_AUTOREPLY=%d",m_AutoAnswer);
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}
}
