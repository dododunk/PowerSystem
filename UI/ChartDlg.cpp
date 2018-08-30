// OWEMONEY.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "ChartDlg.h"


#include "IFRMView.h"
#include "DIBAPI.H"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COWEMONEY dialog

CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
   : CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COWEMONEY)
	m_radio1      =      0;
	m_title       = _T("");
	m_showlegend  =   TRUE;
	m_check1      =   TRUE;
	m_check3      =   FALSE;
	m_check4      =   FALSE;
	m_xtitle      = _T("");
	m_ytitle      = _T("");	
	m_showlabel   =  FALSE;
	m_showstasline = FALSE;
	m_showvalue   =   TRUE;
	m_showxlabel  =  FALSE;
	m_datakinds   =      0;
	m_multile = _T("");
	m_Ismultiple = FALSE;
	//}}AFX_DATA_INIT

	for(int i = 0; i < 13; i ++)
	{
		if(i == 0)
		{
			SELECT[i]  = TRUE;
		}
		else
		{
			SELECT[i]  = FALSE;
		}
	}

	BeginTime   = "";
	EndTime     = "";
}


void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COWEMONEY)
	DDX_Control(pDX, IDC_USERCOMBO, m_UserCombox);
	DDX_Control(pDX, IDC_ENDTIME, m_listend);
	DDX_Control(pDX, IDC_BEGINTIME, m_listbegin);
	DDX_Control(pDX, IDC_MSCHART, m_Chart);
	DDX_Control(pDX, IDC_DBGRIDS, m_dbgrids);
	DDX_Control(pDX, IDC_REMOTEDATACTLS, m_remotedatactrls);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Check(pDX, IDC_SHOWLEGEND, m_showlegend);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK7, m_check3);
	DDX_Check(pDX, IDC_CHECK8, m_check4);
	DDX_Text(pDX, IDC_XTITLE, m_xtitle);
	DDX_Text(pDX, IDC_YTITLE, m_ytitle);
	DDX_Check(pDX, IDC_SHOWLABEL, m_showlabel);
	DDX_Check(pDX, IDC_SHOWSTASLINE, m_showstasline);
	DDX_Check(pDX, IDC_SHOWVALUE, m_showvalue);
	DDX_Check(pDX, IDC_SHOWXLABEL, m_showxlabel);
	DDX_Radio(pDX, IDC_RADIO4, m_datakinds);
	DDX_Text(pDX, IDC_MULTIPLE, m_multile);
	DDX_Check(pDX, IDC_CHECK3, m_Ismultiple);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(COWEMONEY)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SAVEBMP, OnSavebmp)
	ON_BN_CLICKED(IDC_PRINTBMP, OnPrintbmp)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_SHOWLEGEND, OnShowlegend)
	ON_BN_CLICKED(IDC_SETTITLE, OnSettitle)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_SETXTITLE, OnSetxtitle)
	ON_BN_CLICKED(IDC_SETYTITLE, OnSetytitle)
	ON_BN_CLICKED(IDC_SHOWLABEL, OnShowlabel)
	ON_BN_CLICKED(IDC_SHOWSTASLINE, OnShowstasline)
	ON_CBN_SELCHANGE(IDC_BEGINTIME, OnSelchangeBegintime)
	ON_CBN_SELCHANGE(IDC_ENDTIME, OnSelchangeEndtime)
	ON_BN_CLICKED(IDC_SHOWVALUE, OnShowvalue)
	ON_BN_CLICKED(IDC_CHECK34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK40, OnCheck40)
	ON_BN_CLICKED(IDC_CHECK41, OnCheck41)
	ON_BN_CLICKED(IDC_CHECK42, OnCheck42)
	ON_BN_CLICKED(IDC_CHECK43, OnCheck43)
	ON_BN_CLICKED(IDC_SHOWXLABEL, OnShowxlabel)
	ON_CBN_SELCHANGE(IDC_USERCOMBO, OnSelchangeUsercombo)
	ON_BN_CLICKED(IDC_CHECK45, OnCheck45)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COWEMONEY message handlers


void CChartDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}


void CChartDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CChartDlg::OnDestroy() 
{
	
	CDialog::OnDestroy();
   	
}


BOOL CChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_TOTAL);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	

	//得到DIALOGBAR上的变量
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	GetAllUSERInfo(pMainFrm->m_wndMyDialogBar.SelectCondition());

	//找出驻留时间列表
	InitializeCombo(0);
	//显示列表数据
	OnSelchangeUsercombo();
    //窗口居中
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartDlg::initialize(short m_kinds)
{

	CString    Sqlstr,str;
  
	//没有选项
	if(BeginTime.IsEmpty() || EndTime.IsEmpty())
	{
		MessageBox("没有找到可显示数据！","警告",MB_OK|MB_ICONWARNING);
		return;
	}

	switch(m_kinds)
	{
	case 0:
		{
			//得到用户表的所有字段
			str = "SELECT TB_USER.USER_STATIONNAME AS 变电站名称,TB_USER.USER_LINENAME AS 线路名称,TB_USER.USER_TRANSFORMERNO AS 变台名称,TB_USER.USER_NO AS 用户编号,TB_USER.USER_NAME AS 用户名,TB_USER.USER_ADDRESS AS 用户地址,TB_GARRISON.GARRISON_MODULENO AS 模块号";
			
			//有功电度
			if(SELECT[0])
			{
				str = str + ",TB_GARRISON.GARRISON_WORKDEGREE AS 有功电度";
			}
			
			//无功电度
			if(SELECT[1])
			{
				str = str + ",TB_GARRISON.GARRISON_LOSEDEGREE AS 无功电度";
			}
			
			//A相电流
			if(SELECT[2])
			{
				str = str + ",TB_GARRISON.GARRISON_ACURRENT AS A相电流";
			}	
			
			//B相电流
			if(SELECT[3])
			{
				str = str + ",TB_GARRISON.GARRISON_BCURRENT AS B相电流";
			}
			
			//C相电流
			if(SELECT[4])
			{
				str = str + ",TB_GARRISON.GARRISON_CCURRENT AS C相电流";
			}
			
			//A相电压
			if(SELECT[5])
			{
				str = str + ",TB_GARRISON.GARRISON_AVOLTAGE AS A相电压";
			}
			
			//B相电压
			if(SELECT[6])
			{
				str = str + ",TB_GARRISON.GARRISON_BVOLTAGE AS B相电压";
			}
			
			//C相电压
			if(SELECT[7])
			{
				str = str + ",TB_GARRISON.GARRISON_CVOLTAGE AS C相电压";
			}	
			
			//尖峰电量
			if(SELECT[8])
			{
				str = str + ",TB_GARRISON.GARRISON_JFDL AS 尖峰电量";
			}
			
			//尖峰电量
			if(SELECT[9])
			{
				str = str + ",TB_GARRISON.GARRISON_FDL AS 峰电量";
			}
			
			//平电量
			if(SELECT[10])
			{
				str = str + ",TB_GARRISON.GARRISON_PDL AS 平电量";
			}	
			
			//谷电量
			if(SELECT[11])
			{
				str = str + ",TB_GARRISON.GARRISON_GDL AS 谷电量";
			}	
			
			//功率因素
			if(SELECT[12])
			{
				str = str + ",TB_GARRISON.GARRISON_GLYS AS 功率因素";
			}
			
			str = str + ",TB_GARRISON.GARRISON_HALTTIME AS 驻留时间 FROM TB_USER,TB_GARRISON ";
			Sqlstr.Format("%s WHERE TB_USER.USER_MODULENO=TB_GARRISON.GARRISON_MODULENO AND %s AND TB_GARRISON.GARRISON_HALTTIME>='%s' AND TB_GARRISON.GARRISON_HALTTIME<='%s' ORDER BY TB_GARRISON.GARRISON_HALTTIME ASC",str,m_RangeStr,BeginTime,EndTime);
			break;
		}
	case 1:
		{
			
			//显示动态监控数据
			str = "SELECT TB_USER.USER_STATIONNAME AS 变电站名称,TB_USER.USER_LINENAME AS 线路名称,TB_USER.USER_TRANSFORMERNO AS 变台名称,TB_USER.USER_NO AS 用户编号,TB_USER.USER_NAME AS 用户名,TB_USER.USER_ADDRESS AS 用户地址,TB_REALTIME.REALTIME_MODULENO AS 模块号";
			
			//有功电度
			if(SELECT[0])
			{
				str = str + ",TB_REALTIME.REALTIME_WORKDEGREE AS 有功电度";
			}
			
			//无功电度
			if(SELECT[1])
			{
				str = str + ",TB_REALTIME.REALTIME_LOSEDEGREE AS 无功电度";
			}
			
			//A相电流
			if(SELECT[2])
			{
				str = str + ",TB_REALTIME.REALTIME_ACURRENT AS A相电流";
			}	
			
			//B相电流
			if(SELECT[3])
			{
				str = str + ",TB_REALTIME.REALTIME_BCURRENT AS B相电流";
			}
			
			//C相电流
			if(SELECT[4])
			{
				str = str + ",TB_REALTIME.REALTIME_CCURRENT AS C相电流";
			}
			
			//A相电压
			if(SELECT[5])
			{
				str = str + ",TB_REALTIME.REALTIME_AVOLTAGE AS A相电压";
			}
			
			//B相电压
			if(SELECT[6])
			{
				str = str + ",TB_REALTIME.REALTIME_BVOLTAGE AS B相电压";
			}
			
			//C相电压
			if(SELECT[7])
			{
				str = str + ",TB_REALTIME.REALTIME_CVOLTAGE AS C相电压";
			}	
			
			//尖峰电量
			if(SELECT[8])
			{
				str = str + ",TB_REALTIME.REALTIME_JFDL AS 尖峰电量";
			}
			
			//尖峰电量
			if(SELECT[9])
			{
				str = str + ",TB_REALTIME.REALTIME_FDL AS 峰电量";
			}
			
			//平电量
			if(SELECT[10])
			{
				str = str + ",TB_REALTIME.REALTIME_PDL AS 平电量";
			}	
			
			//谷电量
			if(SELECT[11])
			{
				str = str + ",TB_REALTIME.REALTIME_GDL AS 谷电量";
			}	
			
			//功率因素
			if(SELECT[12])
			{
				str = str + ",TB_REALTIME.REALTIME_GLYS AS 功率因素";
			}
			
			str = str + ",TB_REALTIME.REALTIME_TRANSCRIBETIME AS 抄表时间 FROM TB_USER,TB_REALTIME ";
			Sqlstr.Format("%s WHERE TB_USER.USER_MODULENO=TB_REALTIME.REALTIME_MODULENO AND %s AND TB_REALTIME.REALTIME_TRANSCRIBETIME>='%s' AND TB_REALTIME.REALTIME_TRANSCRIBETIME<='%s' AND TB_REALTIME.REALTIME_PROTOCOL=100 ORDER BY TB_REALTIME.REALTIME_TRANSCRIBETIME ASC",str,m_RangeStr,BeginTime,EndTime);
			break;
		}
	}

	m_remotedatactrls.SetDataSourceName(_T("ifrm"));
    m_remotedatactrls.SetSql(Sqlstr);
	m_remotedatactrls.SetUserName(_T("admin"));
	m_remotedatactrls.SetPassword(_T(""));
	m_remotedatactrls.SetCursorDriver(2);
	m_remotedatactrls.SetReadOnly(TRUE);
	m_remotedatactrls.Refresh();

	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor=m_remotedatactrls.GetDSCCursor();
	ASSERT(pCursor!=NULL);
	m_dbgrids.SetDataSource(pCursor); //bind the grid
	m_dbgrids.BindProperty(0x9, &m_remotedatactrls);
	m_dbgrids.SetEditActive(FALSE);
	m_dbgrids.Scroll(2, 0);
}




void CChartDlg::OnSavebmp() 
{

	char szFilter[]="图形BMP文件(*.BMP)|*.BMP||";
   	CFileDialog dlg(FALSE,"BMP","*.BMP",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	dlg.m_ofn.lpstrTitle="保存为";
	
	if(dlg.DoModal() == IDOK)
	{
	
		EmptyClipboard();
		
		m_Chart.EditCopy();
		
		CloseClipboard();

		HBITMAP    m_bitmap;
		CDIBSectionLite bmp;
          
		//打开剪贴板
		if(OpenClipboard())
		{
			
			m_bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		
			bmp.SetBitmap(m_bitmap,NULL);
			bmp.Save(dlg.GetPathName());
			CloseClipboard(); 
			
		}
	
		//存成BMP文件
		//WndToBmpFile(pDC,dlg.GetPathName());
	}

}

void CChartDlg::WndToBmpFile(CDC* pDC,CString BmpFile)
{
	
	//it will capture a wnd image and save it into a bmp file
	CBitmap bmp,*pOldBmp;
	CRect           rect;
	CWnd*           pWnd;
	BOOL     flg  =    0;
	CPalette         pal;
	LOGPALETTE*      pLp;
	
	if(pDC == NULL)               //if pDC is NULL return
	{
		return ;
	}
	
	pWnd = pDC->GetWindow();      //Get Window of PDC
	
	pWnd->GetClientRect(&rect); //Get dimension of Window
	
	if(BmpFile.IsEmpty())
		return ;
	
	CDC memdc;
	
	memdc.CreateCompatibleDC(pDC);  //Make Compatible DC for memdc
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
    //Create Compatible DDB
	pOldBmp=memdc.SelectObject(&bmp);
	memdc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	
	//The following code will detect whether the BMP uses a Raster
	//palette or not.
	
	if(pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		int nSize;
		nSize = sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256;
		pLp   = (LOGPALETTE*) new BYTE[nSize];
		pLp->palVersion    = 0x300;
		pLp->palNumEntries = GetSystemPaletteEntries(pDC->m_hDC,0,255,pLp->palPalEntry);
		pal.CreatePalette(pLp);
		
		delete [] pLp;
	}
	memdc.SelectObject(pOldBmp);
	
	// will convert bitmap from DDB to DIB see DDBToDIB()
	HANDLE hDIB = DDBToDIB(bmp,BI_RGB,&pal);
	if(hDIB==NULL)
	{
		return ;
	}
	
	CFile        file;
	CFileException fe;
    // 打开文件
	if (!file.Open(BmpFile, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		MessageBox("数据指针存成图形文件错误!","警告：",MB_OK|MB_ICONWARNING);
		return;
	}
	
	// 尝试调用SaveDIB保存图像
	TRY
	{
		// 尝试保存图像
		SaveDIB(HDIB(hDIB), file);
		// 关闭文件
		file.Close();
		if (hDIB != NULL)
		{
			// 清除DIB对象
			::GlobalFree((HGLOBAL) hDIB);
		}
	}
	CATCH (CException, eSave)
	{
		// 失败
		file.Abort();
		MessageBox("数据指针存成图形文件错误!","警告：",MB_OK|MB_ICONWARNING);
	}
	END_CATCH
	
}


HANDLE CChartDlg::DDBToDIB(CBitmap &bitmap, DWORD dwCompression,CPalette *pPal)
{
	BITMAP              bm;
	BITMAPINFOHEADER    bi;
	LPBITMAPINFOHEADER  lpbi;
	DWORD               dwLen;
	HANDLE              hDIB;
	HANDLE              handle;
	HDC                 hDC;
	HPALETTE            hPal;
	
	
	ASSERT( bitmap.GetSafeHandle() );
	
	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;
	
	// If a palette has not been supplied, use default palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	
	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);
	
	// Initialize the bitmap infoheader
	bi.biSize          = sizeof(BITMAPINFOHEADER);
	bi.biWidth         = bm.bmWidth;
	bi.biHeight        = bm.bmHeight;
	bi.biPlanes        = 1;
	bi.biBitCount      = bm.bmPlanes * bm.bmBitsPixel;
    //bm.bmPlanes    * bm.bmBitsPixel;
	bi.biCompression   = dwCompression;
	bi.biSizeImage     = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed       = 0;
	bi.biClrImportant  = 0;
	
	// Compute the size of the infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);
	
	// We need a device context to get the DIB from
	hDC = ::GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	
	// Allocate enough memory to hold bitmap infoheader and
	// color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);
	
	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	
	*lpbi = bi;
	
	// Call GetDIBits with a NULL lpBits param, so the device
	// driver will calculate the biSizeImage field
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L,
		(DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);
	
	bi = *lpbi;
	
	// If the driver did not fill in the biSizeImage field, then
	// compute it
	// Each scan line of the image is aligned on a DWORD (32bit)
	// boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31)
			& ~31) / 8) * bi.biHeight;
		
		// If a compression scheme is used, the result may in fact
		// be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}
	
	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	
	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
        0L,                        // Start scan line
        (DWORD)bi.biHeight,        // # of scan lines
        (LPBYTE)lpbi               // address for bitmap bits
        + (bi.biSize + nColors * sizeof(RGBQUAD)),
        (LPBITMAPINFO)lpbi,        // address of bitmapinfo
        (DWORD)DIB_RGB_COLORS);    // Use RGB for color table
	
	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);
	
	return hDIB;
}



void CChartDlg::OnPrintbmp() 
{
	
	CFileFind    finder;
	HBITMAP    m_bitmap;
	CDIBSectionLite bmp;

	EmptyClipboard();
	m_Chart.EditCopy();
	CloseClipboard();

	//打开剪贴板
	if(OpenClipboard())
	{
		
		m_bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		
		bmp.SetBitmap(m_bitmap,NULL);
		bmp.Save("C:\\temp000.bmp");
		
		EmptyClipboard();
		CloseClipboard(); 
		
	}

  
	//找不到此文件
	if(!finder.FindFile("C:\\temp000.bmp"))
	{
        MessageBox("位图不能生成BMP文件!","  ",MB_OK|MB_ICONWARNING);
		return ;
	}

    //打开此BMP文件
	WinExec( "mspaint.exe C:\\temp000.BMP",SW_SHOWMAXIMIZED);
   
	/*
	PROCESS_INFORMATION procinfo; //进程的信息
	char* chPar="MSPAINT.EXE C:\\temp000.BMP";

	STARTUPINFO stinfo;	
	memset(&stinfo, 0, sizeof(STARTUPINFO));
	stinfo.cb = sizeof(STARTUPINFO);
	stinfo.dwFlags = STARTF_USESHOWWINDOW;
	stinfo.wShowWindow = SW_SHOWMAXIMIZED;//SW_SHOWDEFAULT;//"MSPAINT.EXE C:\\temp000.BMP"
	
	BOOL isOK;
	isOK = CreateProcess(NULL,chPar,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&stinfo,&procinfo);
	if(isOK)
	{
		DWORD result = WaitForSingleObject(procinfo.hThread,INFINITE);//10000);
	}
	else
	{
		MessageBox("画图进程启动失败!","警告",MB_OK|MB_ICONWARNING);
	}
	*/
	


}

//SqlStr       条    件
//BeginTime    开始时间
//EndTime      结束时间
void CChartDlg::ShowChart(CString SqlStr, CString BeginTimes, CString EndTimes,short m_kinds)
{
	long      ModuleNo;
	CString        str;
	
	//数据个数
	long m_DataRecords;
    
	UpdateData(TRUE);
	
	//打开数据库,找出模块号
	CDatabase      dbs;	
	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset rs(&dbs);
		
		/*************找出符合条件的模块号****************/
		SqlStr = "SELECT USER_MODULENO,USER_MULTIPLE,USER_NAME FROM TB_USER WHERE " + SqlStr;
		
		rs.Open(CRecordset::forwardOnly,SqlStr);
		
		rs.GetFieldValue((short)0,str);
		ModuleNo = atol(str);
		m_title = "[" + str + "]"; 
		//倍率
		rs.GetFieldValue((short)1,str);
		str.TrimLeft();
        str.TrimRight();

		if(atoi(str) == 0)
		{
			m_multile = "1";
		}
		else
		{
			m_multile = str;
		}

		rs.GetFieldValue((short)2,str);
		rs.Close();
		
		
		str.TrimLeft();
        str.TrimRight();
        
		switch(m_kinds)
		{
		case 0:
			{
		       m_title = str + "用电曲线分析表" + m_title;
			   break;
			}
		case 1:
			{
				m_title = str + "动态监控数据曲线" + m_title;
				break;
			}
		}
		
		m_Chart.SetTitleText(" " + m_title + " ");
		UpdateData(FALSE);
		
		/*************找出符合条件的模块号结束****************/
		switch(m_kinds)
		{
		case 0:
			{
				//显示驻留数据
				SqlStr.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME>='%s' AND GARRISON_HALTTIME<='%s'",ModuleNo,BeginTime,EndTime);
				m_DataRecords = CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", SqlStr);
				break;
			}
		case 1:
			{
				//显示动态监视数据
				SqlStr.Format("REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s' AND REALTIME_PROTOCOL=100",ModuleNo,BeginTime,EndTime);
				m_DataRecords = CDataBaseInstance::GetAllRecordsCount("TB_REALTIME", SqlStr);
				break;
			}
		}
			
		//如果数据个数大于0
		if(m_DataRecords > 0)
		{
			m_StrArray.SetSize(m_DataRecords);
			
			CMakeArray<float> m_pMakeArray;
			
			//生成二维数组
			float **data = m_pMakeArray.MakeTwoArray(m_DataRecords,13);
			data[0][0]     =                            0;
			
			switch(m_kinds)
			{
			case 0:
				{
			       SqlStr =  "SELECT  GARRISON_WORKDEGREE,GARRISON_LOSEDEGREE,GARRISON_ACURRENT,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_JFDL,GARRISON_FDL,GARRISON_PDL,GARRISON_GDL,GARRISON_GLYS,GARRISON_HALTTIME FROM TB_GARRISON WHERE " + SqlStr + " order by GARRISON_HALTTIME";
				   break;
				}
			case 1:
				{
   			        SqlStr =  "SELECT  REALTIME_WORKDEGREE,REALTIME_LOSEDEGREE,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_JFDL,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL,REALTIME_GLYS,REALTIME_TRANSCRIBETIME FROM TB_REALTIME WHERE " + SqlStr + " AND REALTIME_PROTOCOL=100 order by REALTIME_TRANSCRIBETIME";
					break;
				}
			}

			rs.Open(CRecordset::forwardOnly,SqlStr);
			
			//读用户信息，找出模块号
			for(int k = 0;k < m_DataRecords; k++)
			{
				
				//得到数据值
				rs.GetFieldValue((short)0,str);

				//有功
				if(m_Ismultiple)
				{
					//有倍率
					data[k][0] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					
					data[k][0] = float(atof(str));
				}

				//无功
				rs.GetFieldValue((short)1,str);
			
				if(m_Ismultiple)
				{
					//有倍率
					data[k][1] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][1] = float(atof(str));
				}
				
				//A相电流
				rs.GetFieldValue((short)2,str);
				
				if(m_Ismultiple)
				{
					data[k][2] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][2] = float(atof(str));
				}

				//B相电流
				rs.GetFieldValue((short)3,str);
                
				if(m_Ismultiple)
				{
					data[k][3] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][3] = float(atof(str));
				}

				//C相电流
				rs.GetFieldValue((short)4,str);
				
				if(m_Ismultiple)
				{
					data[k][4] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][4] = float(atof(str));
				}
				
				//5,6,7分别为ABC三相电压
				rs.GetFieldValue((short)5,str);
				data[k][5] = float(atof(str));
				
				rs.GetFieldValue((short)6,str);
				data[k][6] = float(atof(str));
				
				rs.GetFieldValue((short)7,str);
				data[k][7] = float(atof(str));
				
			    //尖峰电量
				rs.GetFieldValue((short)8,str);
				
				if(m_Ismultiple)
				{
					data[k][8] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][8] = float(atof(str));
				}
				
				rs.GetFieldValue((short)9,str);
				
				//峰电量
				if(m_Ismultiple)
				{
					data[k][9] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][9] = float(atof(str));
				}
				
				rs.GetFieldValue((short)10,str);
	           
				//平电量
				if(m_Ismultiple)
				{
					data[k][10] = float(atof(str))*float(atof(m_multile));	
				}
				else
				{
					data[k][10] = float(atof(str));	
				}
				
				rs.GetFieldValue((short)11,str);
	           
				//谷电量
				if(m_Ismultiple)
				{
					data[k][11] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][11] = float(atof(str));
				}
				
				rs.GetFieldValue((short)12,str);
				//功率因素
				data[k][12] = float(atof(str));

				rs.GetFieldValue((short)13,str);
				
				m_StrArray[k] = str;
				//库下滑一个记录
				rs.MoveNext();
				
			}
			rs.Close();
			
			SetChartDataValue(data,m_DataRecords,13);
			
			//删除二维数组
			m_pMakeArray.DelTwoArray(data,m_DataRecords);
			
		}
		else
		{
		
			m_StrArray.SetSize(1);
			
			CMakeArray<float> m_pMakeArray;
			
			//生成二维数组
			float **data = m_pMakeArray.MakeTwoArray(1,13);
			data[0][0]     =        0;
			data[0][1]     =        0;
			data[0][2]     =        0;
			data[0][3]     =        0;
			data[0][4]     =        0;
			data[0][5]     =        0;
			data[0][6]     =        0;
			data[0][7]     =        0;
			data[0][8]     =        0;
			data[0][9]     =        0;
			data[0][10]    =        0;
			data[0][11]    =        0;
			data[0][12]    =        0;
            
			m_StrArray[0] = "无";
			SetChartDataValue(data,1,13);

			//删除二维数组
			m_pMakeArray.DelTwoArray(data,m_DataRecords);

		}
			
		//关闭数据库
		dbs.Close();
	}

}



void CChartDlg::InitializeCombo(short m_kinds)
{   
	//打开数据库
	CDatabase     db;
	CString   strSql;

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);

		switch(m_kinds)
		{
		case 0:
			{
				m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT GARRISON_HALTTIME from TB_GARRISON order by GARRISON_HALTTIME "));
				break;
			}
		case 1:
			{		
				m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT REALTIME_TRANSCRIBETIME from TB_REALTIME WHERE REALTIME_PROTOCOL=100 order by REALTIME_TRANSCRIBETIME"));
				break;
			}
		}

		m_listbegin.ResetContent();
		m_listend.ResetContent();
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_listbegin.AddString(strSql);
			m_listend.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//公司级完
		
		delete m_pDatabase;
		m_pDatabase = NULL; 

		//没有选项
		if(m_listbegin.GetCount() > 0  && m_listend.GetCount() > 0)
		{

			m_listbegin.SetCurSel(0);
		    m_listend.SetCurSel(m_listend.GetCount()-1);
			
			//得到起始时间和结束时间
			m_listbegin.GetLBText(0,BeginTime);
			m_listend.GetLBText(m_listend.GetCount() - 1,EndTime);

			BeginTime.TrimLeft();
			BeginTime.TrimRight();
			
			EndTime.TrimLeft();
			EndTime.TrimRight();
		}
		
	}
	
}

void CChartDlg::SetChartDataValue(float** data,int Rows,int Cols)
{

	short LineNo[13];
   
	int   j  =    0;
	int   l  =    0;
	
	LineNo[0]  =  0;
	
	//从13条线里找有哪几条
	for(int i = 0; i < 13; i++)
	{

		if(SELECT[i])
		{
			//记下是哪条线
			LineNo[j] = i;
			j++;
		}
		
	}



    //设置线条数，j条曲线
	m_Chart.SetColumnCount(j); 
	
	//从13条线里找有哪几条
	for( int i = 0; i < 13; i++)
	{

		if(SELECT[i])
		{
		
			l++;

			m_Chart.SetColumn(l);
			
			//设置列标题
			switch(i+1)
			{
			case 1:
				{
					m_Chart.SetColumnLabel("有功电度");
					break;
				}
			case 2:
				{
					m_Chart.SetColumnLabel("无功电度");
					break;
				}
			case 3:
				{
					m_Chart.SetColumnLabel("A相电流");
					break;
				}
			case 4:
				{
					m_Chart.SetColumnLabel("B相电流");
					break;
				}
			case 5:
				{
					m_Chart.SetColumnLabel("C相电流");
					break;
				}
			case 6:
				{
					m_Chart.SetColumnLabel("A相电压");
					break;
				}
			case 7:
				{
					m_Chart.SetColumnLabel("B相电压");
					break;
				}
			case 8:
				{
					m_Chart.SetColumnLabel("C相电压");
					break;
				}
			case 9:
				{
					m_Chart.SetColumnLabel("尖峰电量");
					break;
				}
			case 10:
				{
					m_Chart.SetColumnLabel("峰电量");
					break;
				}
			case 11:
				{
					m_Chart.SetColumnLabel("平电量");
					break;
				}
			case 12:
				{
					m_Chart.SetColumnLabel("谷电量");
					break;
				}
			case 13:
				{
					m_Chart.SetColumnLabel("功率因素");
					break;
				}
				
			}
			
		}
		
	}


	//每条线的点数
	m_Chart.SetRowCount(Rows);

	for(int k = 0; k < j; k++)
	{

		//定到此条直线，编号从1开始
		m_Chart.SetColumn(k + 1);

		// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
		// 0: 不显示	1: 显示在柱状图外
		// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
		m_Chart.GetPlot().GetSeriesCollection().GetItem(k+1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(m_showvalue);
		
		//显示点标记
		m_Chart.GetPlot().GetSeriesCollection().GetItem(k+1).GetDataPoints().GetItem(-1).GetMarker().SetVisible(m_showlabel);
		
		//赋此条线的点值
		for(int i = 0; i < Rows; i++)
		{
            
			//设置X轴行标题
			m_Chart.SetRow(i + 1);
		    m_Chart.SetRowLabel(m_StrArray[i]);
			//赋数据值
			m_Chart.GetDataGrid().SetData(i + 1, k + 1,data[i][LineNo[k]], 0);

			if(!m_showxlabel)
			{
				m_Chart.SetRowLabel("");
			}
		
		}

	}

	m_Chart.SetShowLegend(m_showlegend);
	

	m_StrArray.FreeExtra();
	m_StrArray.RemoveAll();
 	
	m_Chart.Refresh();
}


void CChartDlg::OnRadio1() 
{
    m_Chart.SetChartType(3);
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio2() 
{
    m_Chart.SetChartType(2);
//	m_Chart.GetPlot().GetView3d().Set(365,0);//float Rotation, float Elevation) 10,100
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio3() 
{
    m_Chart.SetChartType(1);
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio8() 
{
    m_Chart.SetChartType(0);
	m_Chart.Refresh();		
}

//显示图例 
void CChartDlg::OnShowlegend() 
{

	if(m_Chart.GetShowLegend())
	{
		m_Chart.SetShowLegend(FALSE);
	}
	else
	{
		m_Chart.SetShowLegend(TRUE);
		
	}
	m_Chart.Refresh();

}

//设置标题
void CChartDlg::OnSettitle() 
{
    UpdateData(TRUE);
	m_title.TrimLeft();
	m_title.TrimRight();
	m_Chart.SetTitleText(" " + m_title + " ");
	m_Chart.Refresh();
}

void CChartDlg::OnCheck1() 
{
   
   //有功电度
   SELECT[0] = !SELECT[0];

   //表数据刷新一次
   MsChartAppear();
   
}

void CChartDlg::OnCheck2() 
{
	//无功电度
   SELECT[1] = !SELECT[1];
   //表数据刷新一次
   MsChartAppear();
	
}

void CChartDlg::OnCheck7() 
{
   //A相电流
   SELECT[2] = !SELECT[2];
   //表数据刷新一次
   MsChartAppear();
}

void CChartDlg::OnCheck8() 
{
   //A相电压
   SELECT[5] = !SELECT[5];
   //表数据刷新一次
   MsChartAppear();
}

//X轴标题
void CChartDlg::OnSetxtitle() 
{
    UpdateData(TRUE);
	m_xtitle.TrimLeft();
	m_xtitle.TrimRight();
	VARIANT var;
	m_Chart.GetPlot().GetAxis(0,var).GetAxisTitle().SetText(m_xtitle);			// X轴名称
	m_Chart.Refresh();	
}

//Y轴标题
void CChartDlg::OnSetytitle() 
{
    UpdateData(TRUE);
	VARIANT         var;
	m_ytitle.TrimLeft();
	m_ytitle.TrimRight();
	m_Chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText(m_ytitle);			// y轴名称
	m_Chart.Refresh();	
	
}

//点标记处理
void CChartDlg::OnShowlabel() 
{

	UpdateData(TRUE);

	for(int j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		for(int i = 1; i <= m_Chart.GetPlot().GetSeriesCollection().Count();i ++)
		{
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetMarker().SetVisible(m_showlabel);
		
		}

	}
  	
}

//显示统计线
void CChartDlg::OnShowstasline() 
{
	
    UpdateData(TRUE);
	
	for(int  j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		if(m_showstasline)
		{	  
			//显示各条统计曲线
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetStatLine().SetFlag(31);
			
		}
		else
		{	
			//隐藏各条统计曲线
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetStatLine().SetFlag(0);
		}
		
	}
      	
}

void CChartDlg::MsChartAppear()
{

	int   j     =       0;
	CString           str;
	CString        StrSql;
	
	//没有时间范围
	if(BeginTime.IsEmpty() || EndTime.IsEmpty())
	{
		return;
	}

	//从8条线里找有哪几条
	for(int i = 0; i < 13; i++)
	{
		
		if(SELECT[i] == TRUE)
		{
			j++;
		}
		
	}
	
	//没有选择线
	if( j  <= 0)
	{
		
		return;
		
	}
	else
	{
		//显示图型
		ShowChart(m_RangeStr, BeginTime,EndTime,m_datakinds);
		initialize(m_datakinds);
	}
	
}


void CChartDlg::OnSelchangeBegintime() 
{
   if(m_listbegin.GetCurSel() != CB_ERR)
   {
	   //得到起始的时间
	   m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
	   BeginTime.TrimLeft();
	   BeginTime.TrimRight();
	   MsChartAppear();	  
	   initialize(m_datakinds);
   }
	   
}

void CChartDlg::OnSelchangeEndtime() 
{
   if(m_listend.GetCurSel() != CB_ERR)
   {
	   
	   //得到结束的时间
	   m_listend.GetLBText(m_listend.GetCurSel(),EndTime);
	   EndTime.TrimLeft();
	   EndTime.TrimRight();
	   MsChartAppear();
	   initialize(m_datakinds);
   }

}

void CChartDlg::OnShowvalue() 
{
    UpdateData(TRUE);
	
	for(int  j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		//定到此条直线，编号从1开始
		m_Chart.SetColumn(j);
		
		if(m_showvalue)
		{	  
			
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
			
			
		}
		else
		{	
			// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
			// 0: 不显示	1: 显示在柱状图外
			// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(0);
		}
		
	}
	
}

void CChartDlg::OnCheck34() 
{
   //B相电流
   SELECT[3] = !SELECT[3];
   //表数据刷新一次
   MsChartAppear();	

}

void CChartDlg::OnCheck39() 
{
   //C相电流
   SELECT[4] = !SELECT[4];
   //表数据刷新一次
   MsChartAppear();	
}

void CChartDlg::OnCheck37() 
{
   //B相电压
   SELECT[6] = !SELECT[6];
   //表数据刷新一次
   MsChartAppear();	
}

void CChartDlg::OnCheck38() 
{
   //C相电压
   SELECT[7] = !SELECT[7];
   //表数据刷新一次
   MsChartAppear();	
}

void CChartDlg::OnCheck40() 
{
	//尖峰电量
	SELECT[8] = !SELECT[8];
	//表数据刷新一次
	MsChartAppear();		
}

void CChartDlg::OnCheck41() 
{
	//峰电量
	SELECT[9] = !SELECT[9];
	//表数据刷新一次
	MsChartAppear();		
}

void CChartDlg::OnCheck42() 
{
	//平电量
	SELECT[10] = !SELECT[10];
	//表数据刷新一次
	MsChartAppear();		
}

void CChartDlg::OnCheck43() 
{
	//谷电量 
	SELECT[11] = !SELECT[11];
	//表数据刷新一次
	MsChartAppear();		
}

void CChartDlg::OnShowxlabel() 
{
	UpdateData(TRUE);
	//表数据刷新一次
	MsChartAppear();		
}

//得到所选择的用户信息
void CChartDlg::GetAllUSERInfo(CString StrSql)
{
	//打开数据库
	CDatabase           db;
	CString            Str,InsertStr;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//和CRecordset连上
		CRecordset rs(&db );
	    Str.Format("SELECT count(*) FROM TB_USER WHERE %s",StrSql);
			
		rs.Open(CRecordset::forwardOnly,Str);
		
		//得到记录个数
		rs.GetFieldValue((short)0,Str);
		
		//记录个数
		long fields = atol(Str); 
		rs.Close();
		
		//删除原来的列表数据
		m_UserCombox.ResetContent();

		if(fields  > 0)
		{
      	    Str.Format("SELECT USER_MODULENO,USER_NAME FROM TB_USER WHERE %s",StrSql);
			
			rs.Open(CRecordset::forwardOnly,Str);
			
			//读用户信息
			for(int j = 0;j < fields; j++)
			{
				InsertStr = "";
				rs.GetFieldValue((short)0,Str);//模块号
				Str.TrimLeft();
				Str.TrimRight();
				InsertStr = Str;
				
				rs.GetFieldValue((short)1,Str);//用户名
				Str.TrimLeft();
				Str.TrimRight();
				InsertStr = InsertStr + "‖" + Str;
				
				//加入列表框
				m_UserCombox.AddString(InsertStr);
						
				//库下滑一个记录
				rs.MoveNext();

			}
		
			//关闭数据库
		    rs.Close( );
		
		}
		
		//如果个数大于0
		if(m_UserCombox.GetCount() > 0)
		{
			m_UserCombox.SetCurSel(0);
		}

		db.Close( );
	}

}

void CChartDlg::OnSelchangeUsercombo() 
{	
	
	CString          StrSql;
	int                   k;
	
	
	if(m_UserCombox.GetCurSel() != CB_ERR)
	{

		m_UserCombox.GetLBText(m_UserCombox.GetCurSel(),StrSql);
	    k = StrSql.Find("‖");

		if( k != -1)
		{
			m_RangeStr.Format("TB_USER.USER_MODULENO=%d",atoi(StrSql.Left(k)));
			//在列表中显示出数据
			initialize(m_datakinds);
			//显示图型
			ShowChart(m_RangeStr,BeginTime,EndTime,m_datakinds);
			OnShowstasline();
		}
        
		StrSql = StrSql.Left(k);
	}

}

void CChartDlg::OnCheck45() 
{
	//谷电量 
	SELECT[12] = !SELECT[12];
	//表数据刷新一次
	MsChartAppear();		
}

void CChartDlg::OnRadio4() 
{
	UpdateData(TRUE);
	//找出驻留时间列表
	InitializeCombo(0);
	//显示列表数据
	OnSelchangeUsercombo();	
}

void CChartDlg::OnRadio6() 
{
	UpdateData(TRUE);
	//找出驻留时间列表
	InitializeCombo(1);
	//显示列表数据
	OnSelchangeUsercombo();		
}

void CChartDlg::OnCheck3() 
{
	UpdateData(TRUE);
	OnSelchangeUsercombo();

}
