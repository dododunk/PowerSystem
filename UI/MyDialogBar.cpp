// MyDialogBar.cpp : implementation file
#include "stdafx.h"

#include "MyDialogBar.h"

#include "MainFrm.h"
#include "IFRMView.h"
#include "ProgressDlg.h"
#include "SearchDlg.h"
#include "ShowDataDlg.h"
#include "TimeSelectDlg.h"
#include "RuntimeAccount.h"
#include "DataBaseInstance.h"
#include "AppInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar dialog


CMyDialogBar::CMyDialogBar()
{
	//{{AFX_DATA_INIT(CMyDialogBar)	
	m_FindCString     =_T("");
	m_radio2          =     0;
	m_synchronization =  TRUE;
	m_combkinds       =     0;
	m_check1          =  TRUE;
	m_check2          = FALSE;
	m_check9          = FALSE;
	m_check5          = FALSE;
	m_check6          = FALSE;
	m_check7          = FALSE;
	m_check8          = FALSE;
	m_check11         = FALSE;
	m_check10         = FALSE;
	m_check12         = FALSE;
	m_check3          = FALSE;
	m_check4          = FALSE;
	m_radio1          =     0;
	m_radio4          =     0;
	m_check13         = FALSE;
	//}}AFX_DATA_INIT
}


void CMyDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialogBar)
	DDX_Control(pDX, IDC_APPEARCOMBO, m_AppearList);
	DDX_Control(pDX, IDC_LISTCOMBO, m_list);
	DDX_Control(pDX, IDC_COMBO, m_SelectKind);
	DDX_Text(pDX, IDC_FINDSTRING, m_FindCString);
	DDX_Radio(pDX, IDC_RADIO16, m_radio2);
	DDX_Control(pDX, IDC_DATATREE, m_datatree);
	DDX_Control(pDX, IDC_SSTABDATA, m_SSTabData);
	DDX_Check(pDX, IDC_SYNCHRONIZATION, m_synchronization);
	DDX_CBIndex(pDX, IDC_COMBOKINDS, m_combkinds);	
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK34, m_check9);
	DDX_Check(pDX, IDC_CHECK35, m_check5);
	DDX_Check(pDX, IDC_CHECK36, m_check6);
	DDX_Check(pDX, IDC_CHECK37, m_check7);
	DDX_Check(pDX, IDC_CHECK38, m_check8);
	DDX_Check(pDX, IDC_CHECK39, m_check11);
	DDX_Check(pDX, IDC_CHECK40, m_check10);
	DDX_Check(pDX, IDC_CHECK41, m_check12);
	DDX_Check(pDX, IDC_CHECK7, m_check3);
	DDX_Check(pDX, IDC_CHECK8, m_check4);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO38, m_radio4);
	DDX_Check(pDX, IDC_CHECK44, m_check13);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialogBar, CInitDialogBar)
	//{{AFX_MSG_MAP(CMyDialogBar)
	ON_NOTIFY(TVN_SELCHANGED, IDC_DATATREE, OnSelchangedDatatree)
	ON_NOTIFY(NM_RCLICK, IDC_DATATREE, OnRclickDatatree)
	ON_CBN_CLOSEUP(IDC_COMBO, OnCloseupCombo)
	ON_EN_SETFOCUS(IDC_FINDSTRING, OnSetfocusFindstring)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SYNCHRONIZATION, OnSynchronization)
	
	ON_COMMAND(ID_LISTSELECT, OnListselect)
	ON_CBN_CLOSEUP(IDC_APPEARCOMBO, OnCloseupAppearcombo)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO38, OnRadio38)
	ON_BN_CLICKED(IDC_RADIO37, OnRadio37)
	ON_CBN_CLOSEUP(IDC_LISTCOMBO, OnCloseupListcombo)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar message handlers
BOOL CMyDialogBar::OnInitDialogBar()
{
	// Support for DDX mechanism
	// If you do not want DDX then
	// do not call base class
	CInitDialogBar::OnInitDialogBar();

//	SetWindowPos(&wndTop,30,30,200,800,NULL);
	m_SelectKind.SetCurSel(0);
   	m_AppearList.SetCurSel(0);

	//不是显示选择条件的记录
    m_IsRightDataAppear    = TRUE;
	m_GetSelectCondtionStr =   "";

	ShowTab(0);
	m_SSTabData.SetTab(0);
	
	m_TimeRangeStr = "所有";
	
	CWnd* pt = GetDlgItem(IDC_LISTCOMBO);

	if(pt)
	{
		pt->ShowWindow(SW_HIDE);
	}

	m_DSCondition = "ALL";
 	return TRUE;
}

void CMyDialogBar::Treeinitialize()
{

	HICON             hicon[14];
	CDatabase                db;
	CString     str,strs,strSql; 
	CString    strtemp1,strtemp2;
 
    //删除所有的项
	m_datatree.DeleteAllItems();

	//删除图像列表
	m_imageList.DeleteImageList();
    m_imgState.DeleteImageList();
	
	m_imageList.Create(28,28,ILC_COLOR32,8,8);
 	m_imageList.SetBkColor(RGB(255,255,255));//RGB(128,128,128));//RGB(0xFF, 0xFF, 0xE0));//RGB(255,255,255));//

	//非模对话框
	CProgressDlg pDialog(ID_PROGRESSDLGTITLE);
	pDialog.Create(NULL);

    hicon[ 0]  = AfxGetApp()->LoadIcon(IDI_COMPANY);            //公司
    hicon[ 1]  = AfxGetApp()->LoadIcon(IDI_SUB);                //变电站
	hicon[ 2]  = AfxGetApp()->LoadIcon(IDI_LINE);               //线路
    hicon[ 3]  = AfxGetApp()->LoadIcon(IDI_TRANS);              //变台
    hicon[ 4]  = AfxGetApp()->LoadIcon(IDI_MODULE);             //模块
    hicon[ 5]  = AfxGetApp()->LoadIcon(IDI_BIGMODULE);          //大用户  
	hicon[ 6]  = AfxGetApp()->LoadIcon(IDI_SUBTOTALMODULE);     //台公变总表
    hicon[ 7]  = AfxGetApp()->LoadIcon(IDI_SUBSALEMODULE);      //变台分表
  	hicon[ 8]  = AfxGetApp()->LoadIcon(IDI_ZSUBTOTALMODULE);    //台专变总表
	hicon[ 9]  = AfxGetApp()->LoadIcon(IDI_COMPENSATEMODULE);   //无功补偿表
    hicon[10]  = AfxGetApp()->LoadIcon(IDI_LSALEMODULE);        //线路售电表
	hicon[11]  = AfxGetApp()->LoadIcon(IDI_LTOTALMODULE);       //线路供电表
	hicon[12]  = AfxGetApp()->LoadIcon(IDI_ZSALEMODULE);        //电站销电表
	hicon[13]  = AfxGetApp()->LoadIcon(IDI_ZTOLTALMODULE);      //电站站总表

	//加载图标
	for( int i = 0; i < 14;i ++)
	{
        m_imageList.Add(hicon[i]);
	}
	

	m_imgState.Create(IDB_BITMAP_STATE,13, 1, RGB(0xFF, 0xFF, 0xE0));//RGB(0xFF, 0xFF, 0xE0)RGB(255,255,255));

	m_datatree.SetImageList(&m_imageList,TVSIL_NORMAL);//TVSIL_SMALL
    
	//m_datatree.SetBkColor(RGB(128,128,128));
	m_datatree.SetBkColor(RGB(255,255,255));//RGB(128,128,128));//RGB(0xFF, 0xFF, 0xE0));

	m_datatree.SetImageList(&m_imgState,TVSIL_STATE);

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{

		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
      	db.Close( );
		
		//公司级开始
	    CDaoRecordset m_CompanySet(m_pDatabase);
	   	m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT USER_COMPANY from TB_USER order by USER_COMPANY"));
      
		//寻找满足条件的记录
      	while (!m_CompanySet.IsEOF())
		{
	 		
			HTREEITEM hFirst = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0)),0,0,TVI_ROOT,TVI_LAST);
		//	m_datatree.SetItemState( hFirst, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
		    
			//变电所级开始 
    		 CDaoRecordset m_SubStaitonSet(m_pDatabase);
			
			 strSql.Format("SELECT DISTINCT USER_STATIONNAME from TB_USER WHERE USER_COMPANY='%s'",V_I4(&m_CompanySet.GetFieldValue(0)));

			 m_SubStaitonSet.Open(dbOpenSnapshot,strSql);
			 
			 while (!m_SubStaitonSet.IsEOF())
			 {
				 
				  HTREEITEM hSecond = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_SubStaitonSet.GetFieldValue(0)),1,1,hFirst,TVI_LAST);
				  {
                      
					  //加变电站总电表
                      strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=9 AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
				 	  AddAllKindAmmeter(strSql,hSecond,13);
					  
					  //加变电站售电表
					  strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=8 AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
					  AddAllKindAmmeter(strSql,hSecond,12); 
					  										  
					  //线路级开始
					  CDaoRecordset m_LinesSet(m_pDatabase);
					  strSql.Format("Select DISTINCT USER_LINENAME from TB_USER WHERE USER_COMPANY='%s' AND USER_STATIONNAME='%s' AND USER_AMMETERKIND<8",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
					  m_LinesSet.Open(dbOpenSnapshot,strSql);

					  while (!m_LinesSet.IsEOF())
					  {
						  
						  HTREEITEM hThird = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_LinesSet.GetFieldValue(0)),2,2,hSecond,TVI_LAST);
						  {
							  
								  //加上线路总表
								  strSql.Format("USER_AMMETERKIND=7  AND USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  AddAllKindAmmeter(strSql,hThird,11);
								  
								  //加上线路售电表
								  strSql.Format("USER_AMMETERKIND=6  AND USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  AddAllKindAmmeter(strSql,hThird,10);

								  //变台级开始
								  CDaoRecordset m_DeviceSet(m_pDatabase);
								  strSql.Format("Select DISTINCT USER_TRANSFORMERNO from TB_USER WHERE USER_AMMETERKIND<=5 AND USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  m_DeviceSet.Open(dbOpenSnapshot,strSql);

								  while (!m_DeviceSet.IsEOF())
								  {
									  strSql.Format("USER_AMMETERKIND<=5 AND TRANSFORMER_NO='%s'",V_I4(&m_DeviceSet.GetFieldValue(0)));
									  strSql = "";
									  str    = (LPTSTR)(LPCTSTR)V_I4(&m_DeviceSet.GetFieldValue(0));
									  str.TrimLeft();
									  str.TrimRight();
									  
									  if(str.GetLength() == 1)
									  {
										  str = " " +str;
									  }
									  
									  strSql = str  + strSql ;
									  
									  //加模块
									  HTREEITEM hFourth = m_datatree.InsertItem(strSql,3,3,hThird,TVI_LAST);
									  {
																				  
											  strSql.Format("Select DISTINCT USER_MODULENO,USER_AMMETERKIND from TB_USER WHERE USER_AMMETERKIND<=5  AND USER_TRANSFORMERNO='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s' AND USER_COMPANY='%s'",V_I4(&m_DeviceSet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)),V_I4(&m_CompanySet.GetFieldValue(0)));

											  //模块
											  CDaoRecordset m_Module(m_pDatabase);
											  
											  m_Module.Open(dbOpenSnapshot,strSql);
											  
											  if(!m_Module.IsEOF())
											  {

												  m_Module.MoveLast(); 
												  
												  //范围
												  pDialog.SetRange(1,m_Module.GetRecordCount() + 1);
												  
												  //步长
												  pDialog.SetStep(1);
												  
												  //起始位置
												  pDialog.SetPos(1);	 
												  
												  m_Module.MoveFirst();
												  
												  while (!m_Module.IsEOF())
												  { 
													  //滑动
													  pDialog.StepIt();
													  
													  switch(V_I4(&m_Module.GetFieldValue(1)))
													  {
													  case 0:
														  {
															  HTREEITEM hFifth = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0)),4,4,hFourth,TVI_LAST);
															  break;
														  }
													  case 1:
														  {
															  strs = (LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0));
															  strs = strs + "【大用户表】";
															  HTREEITEM hFifth = m_datatree.InsertItem(strs,5,5,hFourth,TVI_LAST);
															  break;
														  }
													  case 2:
														  {   
															  strs = (LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0));
															  strs = strs + "【台公变总表】";
															  HTREEITEM hFifth = m_datatree.InsertItem(strs,6,6,hFourth,TVI_LAST);
															  break;
														  }	
													  case 3:
														  {   
															  strs = (LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0));
															  strs = strs + "【台变分表】";
															  HTREEITEM hFifth = m_datatree.InsertItem(strs,7,7,hFourth,TVI_LAST);
															  break;
														  } 
													  case 4:
														  {   
															  strs = (LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0));
															  strs = strs + "【台专变总表】";
															  HTREEITEM hFifth = m_datatree.InsertItem(strs,8,8,hFourth,TVI_LAST);
															  break;
														  } 
													  case 5:
														  {   
															  strs = (LPTSTR)(LPCTSTR)V_I4(&m_Module.GetFieldValue(0));
															  strs = strs + "【无功补偿表】";
															  HTREEITEM hFifth = m_datatree.InsertItem(strs,9,9,hFourth,TVI_LAST);
															  break;
														  }
														  
													  }
													  m_Module.MoveNext();
													  //m_datatree.Expand(hFifth,TVE_EXPAND);
												  }
												  
											  }
											  m_Module.Close();
											  //模块完
										
										  
									  }
									  m_DeviceSet.MoveNext();
									  //m_datatree.Expand(hFourth,TVE_EXPAND);
									  
								  }
								  m_DeviceSet.Close();
								  //变台完
	 
							  }
							  m_LinesSet.MoveNext();
							  //									  m_datatree.Expand(hThird,TVE_EXPAND);
								  
						 }

						 m_LinesSet.Close();
     					 //线路级完

				  }
				  m_SubStaitonSet.MoveNext();
//				  m_datatree.Expand(hSecond,TVE_EXPAND); 

			 }
			 m_SubStaitonSet.Close();
			//变电所级完 


			m_CompanySet.MoveNext();
//			m_datatree.Expand(hFirst,TVE_EXPAND); 
		}
		m_CompanySet.Close();	
    	//公司级完

		delete m_pDatabase;
		m_pDatabase = NULL;

	//	m_datatree.SelectSetFirstVisible(m_datatree.GetRootItem());//SetFocus();

		//查出数据算出个数
		if(m_synchronization)
		{
			//initializeFieldInfo("TB_USER","ALL",0,0);
		}
	
    }
}

//按模块范围找
void CMyDialogBar::FindModule(HTREEITEM hSelectedItem,int image,int m_SmallModule,int m_BigModule)
{	
	
	int temp        =     0;
	int temp1       =     0;
	
	HTREEITEM hChildItem,hBrotherItem;
	
	//查找子节点，没有就结束
	hChildItem = m_datatree.GetChildItem(hSelectedItem);
	
	if(hChildItem != NULL)
	{
		
		//	m_datatree.Expand(hChildItem, TVE_EXPAND);
		
		//查找适合条件的记录
		if(m_datatree.GetItemImage(hChildItem,temp,temp1))
		{
			
			if(temp1 == image || (image == 0  && temp1 > 3))
			{
				
				//查找模块号
				if(atol(m_datatree.GetItemText(hChildItem)) >= m_SmallModule && atol(m_datatree.GetItemText(hChildItem)) <= m_BigModule)
				{
					//模块种类
					switch(m_combkinds)
					{
					case 0:
						{
							//所有表
							m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
							m_bFinding = TRUE;
							break;
						}
					case 1:	
						{
							//脉冲表
							if(atol(m_datatree.GetItemText(hChildItem))%100 <= 12)
							{
								m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
								m_bFinding = TRUE;
							}
							break;
						}
					case 2:	
						{
							//485表
							if(atol(m_datatree.GetItemText(hChildItem))%100 > 12)
							{
								m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
								m_bFinding = TRUE;
							}
							break;
						}
						
						
						/* 
						m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
						m_bFinding = TRUE;
						*/
						
					}
					
				}
				
			}
			
			//再递归处理子节点的子节点和兄弟节点
			FindModule(hChildItem,image,m_SmallModule,m_BigModule);
			
			//处理子节点的兄弟节点和其子节点
			hBrotherItem = m_datatree.GetNextSiblingItem(hChildItem);
			
			while (hBrotherItem)
			{ 
				
				//m_datatree.Expand(hBrotherItem, TVE_EXPAND);
				
				//查找适合条件的记录
				if(m_datatree.GetItemImage(hBrotherItem,temp,temp1))
				{
					//如果 是所有模块号的话则要求图片索引号大于3,才是模块号
					if(temp1 == image || (image == 0  && temp1 > 3))
					{
						
						//查找模块号
						if(atol(m_datatree.GetItemText(hBrotherItem)) >= m_SmallModule && atol(m_datatree.GetItemText(hBrotherItem)) <= m_BigModule)
						{
							//模块种类
							switch(m_combkinds)
							{
							case 0:
								{
									//所有表
									m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
									m_bFinding = TRUE;
									break;
								}
							case 1:
								{   
									if(atol(m_datatree.GetItemText(hBrotherItem))%100 <= 12)
									{
										m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
										m_bFinding = TRUE;
									}
									break;
								}
							case 2:
								{	
									if(atol(m_datatree.GetItemText(hBrotherItem))%100 > 12)
									{	
										m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
										m_bFinding = TRUE;
									}
									break;
								}
							}
							
						}
						
					}
					
				}
				
				//再递归处理子节点的兄弟节点的子节点和兄弟节点
				FindModule(hBrotherItem,image,m_SmallModule,m_BigModule);
				hBrotherItem = m_datatree.GetNextSiblingItem(hBrotherItem);
				
			} 

		}
		
	}
	
}

//按项查找 
void CMyDialogBar::FindItem(HTREEITEM hSelectedItem,int image)
{

	int temp        =     0;
	int temp1       =     0;
	
	HTREEITEM hChildItem,hBrotherItem;
	
	//查找子节点，没有就结束
	hChildItem = m_datatree.GetChildItem(hSelectedItem);

	if(hChildItem != NULL)
	{
	    
		//查找适合条件的记录
		if(m_datatree.GetItemImage(hChildItem,temp,temp1))
		{
		      
		    //m_datatree.Expand(hChildItem, TVE_EXPAND);
			
			if(temp1 == image || image == 0)
			{

				m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
				m_bFinding = TRUE;

			}

		}
		
		//再递归处理子节点的子节点和兄弟节点
		FindItem(hChildItem,image);
		
		//处理子节点的兄弟节点和其子节点
		hBrotherItem = m_datatree.GetNextSiblingItem(hChildItem);

		while (hBrotherItem)
		{ 
		 //   m_datatree.Expand( hBrotherItem, TVE_EXPAND);

            //查找适合条件的记录
			if(m_datatree.GetItemImage(hBrotherItem,temp,temp1))
			{

				if(temp1 == image || image == 0)
				{
					
					m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
					m_bFinding = TRUE;
				}
				
				
			}

		    //再递归处理子节点的兄弟节点的子节点和兄弟节点
			FindItem(hBrotherItem,image);
			hBrotherItem = m_datatree.GetNextSiblingItem(hBrotherItem);

		} 

	}

}

//得到选择条件
CString CMyDialogBar::SelectCondition()
{  

	//第一级公司级
	HTREEITEM               hBootItem,hFirstItem; 
	HTREEITEM hSecondItem,hThirdItem,hFourthItem;
	
	//有一部份
    CString         str1,str2,str3,str4;
	CString str5,str6,str7,str8,strtemp;
    CString                          tr;
	int                      temp,temp1;
	
	hBootItem  = m_datatree.GetRootItem();
	
	if(hBootItem == NULL)
	{
		return "";
	}
	
	//第二级变电站
	if(m_datatree.ItemHasChildren(hBootItem))
	{	
		hFirstItem = m_datatree.GetChildItem(hBootItem);
		
		str1 = "";
		str6 = ""; 
		
		do
		{ 
			
			//第三级，线路级
			if(m_datatree.ItemHasChildren(hFirstItem) && (m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
			{	
				str2 = "";
				str5 = "";
				hSecondItem = m_datatree.GetChildItem(hFirstItem);
				do
				{
					
					//第四级，变台号级
					if(m_datatree.ItemHasChildren(hSecondItem) && (m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					{	
						str3 = "";
						str4 = "";
						hThirdItem = m_datatree.GetChildItem(hSecondItem);
						do
						{
							
							//第五级，模块号级
							if(m_datatree.ItemHasChildren(hThirdItem) && (m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{	
								str7 = str8 = "";
								hFourthItem = m_datatree.GetChildItem(hThirdItem);
								do
								{
									if((m_datatree.GetItemState(hFourthItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
									{
										
										tr = m_datatree.GetItemText(hFourthItem);
										tr.TrimLeft();
										tr.TrimRight();
										int k = tr.Find("【"); 
										if(k != -1)
										{
											tr = tr.Left(k);
										}
										
										str8 = str8 + "USER_MODULENO="  + tr;
										
										//str8 = str8 + "USER_MODULENO="  + m_datatree.GetItemText(hFourthItem);
										
										str8.TrimRight();
										str7 = str7 + str8;
										str8 = " OR ";
										
									}
									
								}while( (hFourthItem = m_datatree.GetNextSiblingItem(hFourthItem)) != NULL );
								
							}	
							//第五级完
							
							//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  变台
							if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{
								
								tr = m_datatree.GetItemText(hThirdItem);
								tr.TrimLeft();
								tr.TrimRight();
								int k = tr.Find("【"); 
								if(k != -1)
								{
									tr = tr.Left(k);
								}
								
								/////////////
								//得到图处索引号
								m_datatree.GetItemImage(hThirdItem,temp,temp1);
								
								//有两种情况
								if(temp1 > 3)
								{
									
									//是线路的供电表或售电表,而不是变台名称
									str4 = str4 + "(USER_MODULENO="  +  tr;
								}
								else
								{
									//是变台名称
									str4 = str4 + "(USER_TRANSFORMERNO="  + "'" + tr + "'";
								}
								
								
								str4.TrimRight();
								str3 = str3 + str4;
								str4 = " OR ";
								
								if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
								{
									str3 =  str3 + " AND (" + str7 + "))";
								}
								else
								{
									//得到图处索引号
									m_datatree.GetItemImage(hThirdItem,temp,temp1);
									
									//有两种情况
									if(temp1 > 3)
									{
										str3 =  str3 + ")";
									}
									else
									{
										str3 =  str3 + " AND USER_AMMETERKIND<=5)";
									}
									
								}
								
							}
							
							
						}while( (hThirdItem = m_datatree.GetNextSiblingItem(hThirdItem)) != NULL );
						
					 }	
					 //第四级完
					 
					 //nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  线路
					 if((m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					 {
						 //得到图处索引号
						 m_datatree.GetItemImage(hSecondItem,temp,temp1);
						 
						 //有两种情况
						 if(temp1 > 3)
						 {							 
							 //是变电站的供电表或售电表,而不是线路名称
							 strtemp.Format("%d",atol(m_datatree.GetItemText(hSecondItem)));
							 //str5 = str5 + "(USER_MODULENO="  +  strtemp;
							 str5 = str5 + "USER_MODULENO="  +  strtemp;
							 
						 }
						 else
						 {
							 //是线路名称
							 str5 = str5 + "(USER_LINENAME="  +  "'" + m_datatree.GetItemText(hSecondItem) + "'" ;
							 
						 }
						 
						 str5.TrimRight();
						 str2 = str2 + str5;
						 str5 = " OR "; 
						 
						 str3.TrimLeft();
						 str3.TrimRight();
						 
						 if(!str3.IsEmpty())
						 {
							 
							 if((m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
							 {
								 str2 =  str2 + " AND (" + str3 + "))";
							 }
							 else
							 {
								 str2 =  str2 + ")";
							 }
							 
							 
						 }
						 
					 }
					 
					 
				   }while( (hSecondItem = m_datatree.GetNextSiblingItem(hSecondItem)) != NULL );
						
						
				  }
				  
				  //nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  变电站
				  if((m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
				  {
					  
					  str6 = str6 + "(USER_STATIONNAME="  + "'" + m_datatree.GetItemText(hFirstItem) + "'";
					  str6.TrimRight();
					  str1 = str1 + str6;
					  str6 = " OR ";
					  
					  str2.TrimLeft();
					  str2.TrimRight();
					  
					  if(!str2.IsEmpty())
					  {
						  
						  if((m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
						  {
							  str1 =  str1 + " AND (" + str2 + "))";
						  }
						  else
						  {
							  str1 = str1 + ")";
						  }
						  
					  }
					  
				  }
				  
				  //第三级完
				  
				  
			}while( (hFirstItem = m_datatree.GetNextSiblingItem(hFirstItem)) != NULL );
			
			
		}	
		//第二级完
		
		return str1;
		
}


void CMyDialogBar::OnSelchangedDatatree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	
	HTREEITEM  hSelected = pNMTreeView->itemNew.hItem;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

    CString           str;
	
	if(hSelected != NULL)
	{
		hSelectedItem = hSelected;

	  	CString              tr;
		int               m,n,k;
		VARIANT        position;
		position.vt   =   VT_I4;//记录位置
		m_datatree.GetItemImage(hSelectedItem,m,n);
	
		switch(n)
		{
		case 0:
			{	
		    	str                    = "ALL";
                m_GetSelectCondtionStr = "ALL";
                m_IsRightDataAppear    =  TRUE;//是显示选择条件的记录
				break;
			}
		case 1:
			{
				//变电站名称
				str.Format("USER_STATIONNAME='%s'", m_datatree.GetItemText(hSelectedItem));
				m_GetSelectCondtionStr      =  str;
                m_IsRightDataAppear         = TRUE;//是显示选择条件的记录
				break;
			}
		case 2:
			{
				//线路名称
				str.Format("USER_STATIONNAME='%s' AND USER_LINENAME='%s' AND USER_AMMETERKIND<=5",m_datatree.GetItemText(m_datatree.GetParentItem(hSelected)),m_datatree.GetItemText(hSelectedItem));
				m_GetSelectCondtionStr     =  str;
                m_IsRightDataAppear        = TRUE;//是显示选择条件的记录
				break;
			}
		case 3:
			{
				//变台
			    tr = m_datatree.GetItemText(hSelectedItem);
								
				tr.TrimLeft();
				tr.TrimRight();
			    k = tr.Find("【"); 
			    if(k != -1)
				{
				   tr = tr.Left(k);
				}
				
				//变台名称
				str.Format("USER_STATIONNAME='%s' AND USER_LINENAME='%s' AND USER_TRANSFORMERNO='%s' AND USER_AMMETERKIND<=5",m_datatree.GetItemText(m_datatree.GetParentItem(m_datatree.GetParentItem(hSelected))),m_datatree.GetItemText(m_datatree.GetParentItem(hSelected)),tr);
               	m_GetSelectCondtionStr = str;
				
				//是显示选择条件的记录
                m_IsRightDataAppear  = TRUE;
	            break;

			}
		}


		if(n >= 4)
		{       
			
			//模块号
			int j = 0;
			do
			{
				m_datatree.Expand(hSelected,TVE_EXPAND);
				j ++; 

			}while( (hSelected = m_datatree.GetPrevSiblingItem(hSelected)) != NULL );
			
			//如果同步显示数据
			if(m_synchronization)
			{
	
				//数据位置,是显示选择条件的记录
				if(m_IsRightDataAppear)
				{
					position.lVal = j + 1; 
					
					if(m_synchronization)
					{	
						//下翻数据记录	
						CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
						ASSERT_VALID(pMainFrm);
						pMainFrm->m_wndMyDialogData.ScrollRecord(position);
					}

				}

			}
			
			tr = m_datatree.GetItemText(hSelectedItem);
			tr.TrimLeft();
			tr.TrimRight();
			k = tr.Find("【"); 
			if(k != -1)
			{
			   tr = tr.Left(k);
			}
			
		//	m_GetModuleCondtion.Format("USER_MODULENO=%s", tr);
			
		}
		else
		{
			
			//显示当前树下的所有模块,如果同步显示数据
			if(m_synchronization)
			{	
				position.lVal =       2;
				initializeFieldInfo("当前树枝下",str,3,position);//显示数据
				m_GetModuleCondtion = "";
			}

		}
	
    }

  	*pResult = 0;		
	
}

void CMyDialogBar::OnRclickDatatree(NMHDR* pNMHDR, LRESULT* pResult) 
{  	   
	
	//pt->m_WhichKind-------TRUE 变电站版本  FALSE电局版
    CIFRMApp* pt = (CIFRMApp*)AfxGetApp();
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	CMenu  obMenu;	
    if(AppInfo::Instance().m_WhichKind)
	{
		obMenu.LoadMenu(IDR_LOCALTREEMENU); //本地
	}
	else
	{	
		

		{
			obMenu.LoadMenu(IDR_REMOTEGREEMENU);
		}
	}

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	//得到当前的位置
	CPoint obCursorPoint = (0, 0);
	

	GetCursorPos(&obCursorPoint);
	
	m_ModuleFindContionStr = SelectCondition();

    //没有选择什么模块
	if(m_ModuleFindContionStr.IsEmpty())
	{	
		pPopupMenu->EnableMenuItem(ID_LISTSELECT, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_PHASETEST, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_TESTREADTABLE , MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_REMOTEMODIFY, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_APPEARSELECTDATA, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_LOCALMODIFY, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_XIANGCHANGE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_MODIFYPROTCOL, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_DELETEMODULE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_STOPORSEND, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_OWEMONEY, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	    pPopupMenu->EnableMenuItem(ID_FINDREPEATRECORDS, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	    pPopupMenu->EnableMenuItem(ID_WUGONGDEAL, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 


	}
	else
	{	
		pPopupMenu->EnableMenuItem(ID_TESTREADTABLE, MF_BYCOMMAND | MF_ENABLED);
        pPopupMenu->EnableMenuItem(ID_OWEMONEY, MF_BYCOMMAND | MF_ENABLED);
        pPopupMenu->EnableMenuItem(ID_FINDREPEATRECORDS, MF_BYCOMMAND | MF_ENABLED);
        pPopupMenu->EnableMenuItem(ID_WUGONGDEAL, MF_BYCOMMAND | MF_ENABLED);

		//如果是超级管理员
        if(CRuntimeAccount::GetCurrentPrivilege() < 1)
		{
			pPopupMenu->EnableMenuItem(ID_PHASETEST, MF_BYCOMMAND      | MF_ENABLED);
		}
		else
		{
			pPopupMenu->EnableMenuItem(ID_PHASETEST, MF_BYCOMMAND      | MF_GRAYED | MF_DISABLED);
		}

		//如果是管理员以上
		if(CRuntimeAccount::GetCurrentPrivilege() < 2)
		{    
			pPopupMenu->EnableMenuItem(ID_STOPORSEND,    MF_BYCOMMAND | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_REMOTEMODIFY , MF_BYCOMMAND  | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_DELETEMODULE , MF_BYCOMMAND  | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_LOCALMODIFY ,  MF_BYCOMMAND  | MF_ENABLED); 
			pPopupMenu->EnableMenuItem(ID_XIANGCHANGE ,  MF_BYCOMMAND  | MF_ENABLED); 
			pPopupMenu->EnableMenuItem(ID_MODIFYPROTCOL, MF_BYCOMMAND  | MF_ENABLED); 

		}
		else
		{	
			pPopupMenu->EnableMenuItem(ID_REMOTEMODIFY , MF_BYCOMMAND  | MF_GRAYED | MF_DISABLED);
			pPopupMenu->EnableMenuItem(ID_DELETEMODULE , MF_BYCOMMAND  | MF_GRAYED | MF_DISABLED);
			pPopupMenu->EnableMenuItem(ID_LOCALMODIFY ,  MF_BYCOMMAND  | MF_GRAYED | MF_DISABLED); 
			pPopupMenu->EnableMenuItem(ID_XIANGCHANGE ,  MF_BYCOMMAND  | MF_GRAYED | MF_DISABLED); 
			pPopupMenu->EnableMenuItem(ID_MODIFYPROTCOL, MF_BYCOMMAND  | MF_GRAYED | MF_DISABLED); 

		}

	} 

	//发送数据
	if(!AppInfo::Instance().m_WhichKind && !m_ModuleFindContionStr.IsEmpty())
	{   
		//远程版	
		pPopupMenu->EnableMenuItem(ID_PASSUSERDATA ,MF_BYCOMMAND | MF_ENABLED);
	
		if(CRuntimeAccount::GetCurrentPrivilege()< 2)
		{
			pPopupMenu->EnableMenuItem(ID_APPEARSELECTDATA,MF_BYCOMMAND | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_LOCALMODIFY ,    MF_BYCOMMAND | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_XIANGCHANGE ,    MF_BYCOMMAND | MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_MODIFYPROTCOL ,  MF_BYCOMMAND | MF_ENABLED);

		}
		else
		{
			pPopupMenu->EnableMenuItem(ID_APPEARSELECTDATA,MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
			pPopupMenu->EnableMenuItem(ID_LOCALMODIFY ,    MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
			pPopupMenu->EnableMenuItem(ID_XIANGCHANGE ,    MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
			pPopupMenu->EnableMenuItem(ID_MODIFYPROTCOL,   MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		}

	}
	else
	{	
		//本地版
		pPopupMenu->EnableMenuItem(ID_PASSUSERDATA, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}

    //弹出菜单条
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);		

	*pResult = 0;
}

void CMyDialogBar::OnCloseupCombo() 
{
	UpdateData(TRUE);
    int  image      =     0;
    m_bFinding      = FALSE;
	CString             str;

	if(m_radio2 > 0 && hSelectedItem == NULL)
	{
		MessageBox("请先选择目标项，再查找！","  ",MB_OK|MB_ICONASTERISK);
		return;
	}
	
	//从图片索引号找	
	switch(m_SelectKind.GetCurSel())
	{
	case 0:
		{   
			//全部表
			image = 0;
			break;
		}
	case 1:
		{   
			//居民表
			image = 4;
			break;
		}
	case 2:
		{   
			//大用户表
			image = 5;
			break;
		}
	case 3:
		{
			//台公娈总表
			image = 6;
			break;
		}
	case 4:
		{
			//台变分表
			image = 7;
			break;
		}
	case 5:
		{
			//台专娈总表
			image = 8;
			break;
		}
	case 6:
		{
			//无功补偿表
			image = 9;
			break;
		}
	case 7:
		{
			//线路售电表
			image = 10;
			break;
		}
	case 8:
		{
			//线路供电表
			image = 11;
			break;
		}
	case 9:
		{
			//电站售电表
			image = 12;
			break;
		}
	case 10:
		{
			//电站供电表
			image = 13;
			break;
		}
	case 11:
		{

			CSearchDlg      dlg;
			dlg.m_showbuttons  =   FALSE;
			dlg.SetDataBaseName("TB_USER");
			
			CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
			if(dlg.DoModal() == IDOK)
			{
				dlg.m_totalsql.TrimLeft();
                dlg.m_totalsql.TrimRight();

				if(dlg.m_totalsql.IsEmpty())
				{
    				//按项查找
					FindItem(m_datatree.GetRootItem(),0);			 
					return;
				}

				long m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",dlg.m_totalsql);
			
				if(m_records > 0)
				{
					FindCondtionModule(dlg.m_totalsql,m_records);

					VARIANT        position;
					position.vt   =   VT_I4;//记录位置
					position.lVal =       2;
					//回树控件状态
					ShowTab(0);
					m_SSTabData.SetTab(0);
         			//同步显示数据
					initializeFieldInfo("查找到",dlg.m_totalsql,3,position);//显示数据
					
				}
				else
				{
					MessageBox("此枝下找不到满足条件的相应模块！","",MB_OK|MB_ICONWARNING);//提示:
				}

			}

			return;
			break;
		}

	}
	
	m_datatree.Expand(m_datatree.GetRootItem(), TVE_EXPAND);
	

	switch(m_radio2)
	{
	case 0:
		{
			//根目录下找
			switch(m_combkinds)
			{
			case 0:
				{
					FindItem(m_datatree.GetRootItem(),image);
					break;
				}
			case 1:
				{
					//根目录下所有脉冲表范围内找
					FindImpluseOr485Module(m_datatree.GetRootItem(),image,0);
					break;
				}
			case 2:
				{	
					//根目录下所有485表范围内找
					FindImpluseOr485Module(m_datatree.GetRootItem(),image,1);
					break;
				}
			}
			break;
		}
	case 1:
		{
			//按项查找
			switch(m_combkinds)
			{
			case 0:
				{
					FindItem(hSelectedItem,image);
					break;
				}
			case 1:
				{
					//当前枝下所有脉冲表范围内找
					FindImpluseOr485Module(hSelectedItem,image,0);
					break;
				}
			case 2:
				{	
					//当前枝下所有485表范围内找
					FindImpluseOr485Module(hSelectedItem,image,1);
					break;
				}
			}

			break;
		}
	case 2:
		{
			//按模块号范围找
			int m_smallvalue,m_bigvalue;
			
			m_FindCString.TrimLeft();
			m_FindCString.TrimRight();
			
			if(m_FindCString.IsEmpty())
			{
				MessageBox("模块号值不能为空，请先输入模块号值！","",MB_OK|MB_ICONWARNING);
				return;
			}
			
			int start = m_FindCString.Find('-');
			if( start > 0)
			{
				m_smallvalue = atoi(m_FindCString.Left(start));
				m_bigvalue   = atoi(m_FindCString.Right(m_FindCString.GetLength()- start -1));
			}
			else
			{
				m_smallvalue = atoi(m_FindCString);
				m_bigvalue   = atoi(m_FindCString);
			}
			
			//按模块号查找
			FindModule(hSelectedItem,image,m_smallvalue,m_bigvalue);
			break;
		}
	}
		
		
	if(!m_bFinding)
	{

		if(m_radio2 < 2)
		{
			MessageBox("此枝下找不到满足条件的相应模块！\r\n提示：请到上级查找试试！","",MB_OK|MB_ICONWARNING);//提示:
		}
		else
		{
			
			if(hSelectedItem != m_datatree.GetRootItem())
			{
				
				if(MessageBox("当前枝下找不到满足条件的模块，从根枝往下找吗？"," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
				{
                   return;
				}

				//按模块号范围找
				int m_smallvalue,m_bigvalue;
				
				m_FindCString.TrimLeft();
				m_FindCString.TrimRight();
				
				if(m_FindCString.IsEmpty())
				{
					MessageBox("模块号值不能为空，请先输入模块号值！","",MB_OK|MB_ICONWARNING);
					return;
				}
				
				int start = m_FindCString.Find('-');
				if( start > 0)
				{
					m_smallvalue = atoi(m_FindCString.Left(start));
					m_bigvalue   = atoi(m_FindCString.Right(m_FindCString.GetLength()- start -1));
				}
				else
				{
					m_smallvalue = atoi(m_FindCString);
					m_bigvalue   = atoi(m_FindCString);
				}
				
				//按模块号查找
				FindModule(m_datatree.GetRootItem(),image,m_smallvalue,m_bigvalue);

				if(!m_bFinding)
				{
					MessageBox("找不到满足条件的相应模块！","",MB_OK|MB_ICONWARNING);//提示:
					return;
				}
					
			}
			else
			{
				MessageBox("找不到满足条件的相应模块！","",MB_OK|MB_ICONWARNING);
			}

			
		}
	}
	
	if(m_bFinding)
	{	
		
		VARIANT        position;
		position.vt   =   VT_I4;//记录位置
		position.lVal =       2;

		ShowTab(0);
		m_SSTabData.SetTab(0);
		m_ModuleFindContionStr = SelectCondition();//条件选择
		//显示当前树下的所有模块,如果同步显示数据
		initializeFieldInfo("查找到",m_ModuleFindContionStr,3,position);//显示数据
		m_GetModuleCondtion = "";
	}
	
}

void CMyDialogBar::OnSetfocusFindstring() 
{
	UpdateData(TRUE);
	m_radio2   =   2;
	UpdateData(FALSE);
}

void CMyDialogBar::AddAllKindAmmeter(CString condtion,HTREEITEM Item,int n)
{
	//打开数据库
	CDatabase            db;
	CString      str,strSql;
	
	//记录个数
	long    fields    = 0;
	
	switch(n)
	{
	case 5:
		{
			str = "【大用户表】";
			break;
		}
	case 6:
		{   
			str = "【台公变总表】";//【台变总表】
			break;
		}
	case 7:
		{   
			str = "【台变分表】";
			break;
		}
	case 8:
		{   
			str = "【台专变总表】";
			break;
		}
	case 9:
		{   
			str = "【无功补偿表】";
			break;
		}
	case 10:
		{
			str = "【线售电表】";
			break;
		}	
	case 11:
		{
			str = "【线供电表】";
			break;
		}
	case 12:
		{
			str = "【站售电表】";
			break;
		}
	case 13:
		{
			str = "【站供电表】";
			break;
		}
	}

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		strSql.Format("SELECT USER_MODULENO FROM TB_USER WHERE %s",condtion);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		while(!rs.IsEOF())
		{
			
			rs.GetFieldValue((short)0,strSql);
			
			strSql.TrimLeft();
			strSql.TrimRight();
			
			if(!strSql.IsEmpty())
			{
				strSql = strSql + str;
			}
			
			//加入树列表
			m_datatree.InsertItem(strSql,n,n,Item,TVI_LAST);
			
			//库下滑一个记录
			rs.MoveNext();
		}
	
		//关闭数据库
		rs.Close( );
		db.Close( );
	}
	
}




BEGIN_EVENTSINK_MAP(CMyDialogBar, CInitDialogBar)
    //{{AFX_EVENTSINK_MAP(CMyDialogBar)
	ON_EVENT(CMyDialogBar, IDC_SSTABDATA, -600 /* Click */, OnClickSstabdata, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()





void CMyDialogBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
   /*
	CBrush brush(RGB(224,223,227));//160,180,220;RGB(128,128,128)
    CRect          rect;
    GetClientRect(rect);
    dc.FillRect(&rect,&brush);

	
	CDC dcImage;
    if (!dcImage.CreateCompatibleDC(&dc))
		return;
	
	CRect m_Rect;
	GetClientRect(&m_Rect);
	
	CBitmap m_bitmap;
	
    if (!m_bitmap.LoadBitmap(IDB_BACK))
	  return;
  
    BITMAP bm;
    m_bitmap.GetBitmap( &bm );
    CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
    dc.StretchBlt(0,0,m_Rect.Width(),m_Rect.Height(),&dcImage,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);	
    dcImage.SelectObject(pOldBitmap);
	*/

}

HBRUSH CMyDialogBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CInitDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);
	
    /*
    if(nCtlColor == CTLCOLOR_STATIC )
	{
	    pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	*/

	return hbr;
}

//删除所有选择的列表
void CMyDialogBar::DeleteAllSelectTree()
{	
	
	//第一级公司级
	HTREEITEM   hBootItem; 
	HTREEITEM  hFirstItem; 
	HTREEITEM hSecondItem;
    HTREEITEM  hThirdItem;
	HTREEITEM hFourthItem;
	CString           str;

	//有一部份
 	hBootItem  = m_datatree.GetRootItem();
	{
		//第二级变电站
		if(m_datatree.ItemHasChildren(hBootItem))
		{	
			
			hFirstItem = m_datatree.GetChildItem(hBootItem);

			do
			{ 
				  
				  //第三级，线路级
				  if(m_datatree.ItemHasChildren(hFirstItem) && (m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
				  {	
					     
						//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  变电站
						if((m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
						{
							 m_datatree.DeleteItem(hFirstItem);//用于删除某一结点
							 continue;
						}
					  
				        //第三级完
					    hSecondItem = m_datatree.GetChildItem(hFirstItem);
						do
						{
						
							  //nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  线路
							  if((m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
							  {
								  m_datatree.DeleteItem(hSecondItem);//用于删除某一结点
							      continue;
							  }

						      //第四级，变台号级
							  if(m_datatree.ItemHasChildren(hSecondItem) && (m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							  {	
								 
									hThirdItem = m_datatree.GetChildItem(hSecondItem);
									do
									{
										  //nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  线路
										  if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
										  {
											  m_datatree.DeleteItem(hThirdItem);//用于删除某一结点
											  continue;
										  }

                                       	  //第五级，模块号级
										  if(m_datatree.ItemHasChildren(hThirdItem) && (m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
										  {	
										
												hFourthItem = m_datatree.GetChildItem(hThirdItem);
												do
												{
													if((m_datatree.GetItemState(hFourthItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
													{
														m_datatree.DeleteItem(hFourthItem);//用于删除某一结点
													}
																	
												}while( (hFourthItem = m_datatree.GetNextSiblingItem(hFourthItem)) != NULL );
														
										  }	
           								  //第五级完
																		 
																					
									}while( (hThirdItem = m_datatree.GetNextSiblingItem(hThirdItem)) != NULL );
                                   
							  }	
							  //第四级完
                             
							
							 

						}while( (hSecondItem = m_datatree.GetNextSiblingItem(hSecondItem)) != NULL );
						
											
				  }
				  
								
			}while( (hFirstItem = m_datatree.GetNextSiblingItem(hFirstItem)) != NULL );
						
		}	
		//第二级完
	}
	
	m_datatree.SetItemState(m_datatree.GetRootItem(), INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
	
	
    if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
	{
		//查出数据算出个数
//		initializeFieldInfo("TB_USER","ALL",0,0);
		str.Format("记录个数［%d］，模块个数［%d］",CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL"),CDataBaseInstance::Getmoduls("ALL"));
//		m_dbgrid.SetCaption(str);
	}

}

//按条件找记录
void CMyDialogBar::FindCondtionModule(CString str,long m_Records)
{	
	//打开数据库
	CDatabase     db;	
	CString   SqlStr;

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);
		if(str == "ALL")
		{
			SqlStr = "SELECT USER_MODULENO FROM TB_USER";
		}
		else
		{
			SqlStr = "SELECT USER_MODULENO FROM TB_USER WHERE " + str;
		}
		rs.Open(CRecordset::forwardOnly,SqlStr);
		
		//读用户信息,找出模块号
		for(int j = 0;j < m_Records; j++)
		{
			rs.GetFieldValue((short)0,SqlStr);
			//按模块号查找
	        FindModule(m_datatree.GetRootItem(),0,atol(SqlStr),atol(SqlStr));
			//库下滑一个记录
			rs.MoveNext();
		}
    	rs.Close();
		//关闭数据库
		db.Close();
	}
}



void CMyDialogBar::ShowTab(short kinds)
{
	
	switch(kinds)
	{
	case 0:
		{
			//当前列表
			CWnd* pt = GetDlgItem(IDC_DATATREE);
			pt->ShowWindow(SW_SHOW); 

			//模块查找
			pt = GetDlgItem(IDC_SYNCHRONIZATION);
			pt->ShowWindow(SW_HIDE);
 			pt = GetDlgItem(IDC_STATIC5);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC6);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC7);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO16);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO17);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO4);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_FINDSTRING);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC4);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_COMBO);
            pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_COMBOKINDS);
            pt->ShowWindow(SW_HIDE);
            pt = GetDlgItem(IDC_STATIC3);
            pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC10);
            pt->ShowWindow(SW_HIDE);
		    pt = GetDlgItem(IDC_STATIC12);
            pt->ShowWindow(SW_HIDE);
	
			//数据浏览
			pt = GetDlgItem(IDC_STATIC20);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC21);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC23);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO38);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO37);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_LISTCOMBO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC25);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK37);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK38);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK35);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK36);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK7);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK8);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK34);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK40);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK39);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK44);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK41);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_APPEARCOMBO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC28);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC29);
			pt->ShowWindow(SW_HIDE);
			break;
		}
	case 1:
		{	
			//树控件
			CWnd* pt = GetDlgItem(IDC_DATATREE);
			pt->ShowWindow(SW_HIDE);
			//模块查找 
			pt = GetDlgItem(IDC_STATIC12);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SYNCHRONIZATION);
			pt->ShowWindow(SW_SHOW);	
			pt = GetDlgItem(IDC_STATIC5);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC6);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC7);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO16);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO17);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO4);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_FINDSTRING);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC2);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC4);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_COMBO);
            pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_COMBOKINDS);
            pt->ShowWindow(SW_SHOW);
            pt = GetDlgItem(IDC_STATIC3);
            pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC10);
            pt->ShowWindow(SW_SHOW);

			//数据显示
			pt = GetDlgItem(IDC_STATIC20);
			pt->ShowWindow(SW_HIDE);
	        pt = GetDlgItem(IDC_STATIC21);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC23);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO38);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO37);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_LISTCOMBO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC25);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK37);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK38);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK35);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK36);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK7);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK8);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK34);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK40);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK39);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK44);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_CHECK41);
			pt->ShowWindow(SW_HIDE);	
			pt = GetDlgItem(IDC_APPEARCOMBO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC28);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC29);
			pt->ShowWindow(SW_HIDE);
	       	break;
		}
	case 2:
		{	
			//树控件
			CWnd* pt = GetDlgItem(IDC_DATATREE);
			pt->ShowWindow(SW_HIDE);
	        pt = GetDlgItem(IDC_STATIC12);
			pt->ShowWindow(SW_HIDE);
			//模块查找
			pt = GetDlgItem(IDC_SYNCHRONIZATION);
			pt->ShowWindow(SW_HIDE);	
			pt = GetDlgItem(IDC_STATIC5);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC6);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC7);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO16);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO17);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO4);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_FINDSTRING);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC4);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_COMBO);
            pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_COMBOKINDS);
            pt->ShowWindow(SW_HIDE);
            pt = GetDlgItem(IDC_STATIC3);
            pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC10);
            pt->ShowWindow(SW_HIDE);
		
			//数据显示
			pt = GetDlgItem(IDC_STATIC20);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC21);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO1);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO2);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC23);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO38);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO37);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_LISTCOMBO);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC25);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK37);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK38);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK1);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK35);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK2);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK36);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK7);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK8);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK34);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK40);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK39);
			pt->ShowWindow(SW_SHOW);
        	pt = GetDlgItem(IDC_CHECK44);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_CHECK41);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_APPEARCOMBO);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC28);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC29);
			pt->ShowWindow(SW_SHOW);
			break;
		}

	}

}

void CMyDialogBar::OnClickSstabdata(short PreviousTab) 
{
    ShowTab(m_SSTabData.GetTab());
	
	//初始化列表
	if(m_SSTabData.GetTab() == 2)
	{
		InitializeCombo();
		m_radio1   =    1;
		m_radio4   =    1;	
		CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
	    pt->ShowWindow(SW_SHOW);
		
		//如果没有选择列
		if(m_list.GetCurSel() != LB_ERR)
		{
			//找到时间值
			m_list.GetLBText(m_list.GetCurSel(),m_DSCondition);
			m_DSCondition.TrimLeft();
			m_DSCondition.TrimRight();
			m_TimeRangeStr = m_DSCondition;	
		}

		UpdateData(FALSE);

	}

}


void CMyDialogBar::OnSynchronization() 
{
    UpdateData(TRUE);

	
}


void CMyDialogBar::FindImpluseOr485Module(HTREEITEM hSelectedItem,int image,BYTE kinds)
{	

	int temp        =     0;
	int temp1       =     0;

	HTREEITEM hChildItem,hBrotherItem;
	
	//查找子节点，没有就结束
	hChildItem = m_datatree.GetChildItem(hSelectedItem);

	if(hChildItem != NULL)
	{
	    
	//	m_datatree.Expand(hChildItem, TVE_EXPAND);
		//查找适合条件的记录
		if(m_datatree.GetItemImage(hChildItem,temp,temp1))
		{
		
			if(temp1 == image || (image == 0  && temp1 > 3))
			{
				
				switch(kinds)
				{
				case 0:
					{
						if(atol(m_datatree.GetItemText(hChildItem))%100 <= 12)
						{
							m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
							m_bFinding = TRUE;
						}
						break;
					}
				case 1:
					{
						if(atol(m_datatree.GetItemText(hChildItem))%100 > 12)
						{
							m_datatree.SetItemState(hChildItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
							m_bFinding = TRUE;
						}
						break;
					}
				}
		
			}

		}
		
		//再递归处理子节点的子节点和兄弟节点
		FindImpluseOr485Module(hChildItem,image,kinds);
		
		//处理子节点的兄弟节点和其子节点
		hBrotherItem = m_datatree.GetNextSiblingItem(hChildItem);

		while (hBrotherItem)
		{ 
			
		//	m_datatree.Expand( hBrotherItem, TVE_EXPAND);
		    
            //查找适合条件的记录
			if(m_datatree.GetItemImage(hBrotherItem,temp,temp1))
			{
				//如果 是所有模块号的话则要求图片索引号大于3,才是模块号
				if(temp1 == image || (image == 0  && temp1 > 3))
				{
					
					switch(kinds)
					{
					case 0:
						{
							if(atol(m_datatree.GetItemText(hBrotherItem))%100 <= 12)
							{
								m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
								m_bFinding = TRUE;
							}
							break;
						}
					case 1:
						{
							if(atol(m_datatree.GetItemText(hBrotherItem))%100 > 12)
							{
								m_datatree.SetItemState(hBrotherItem, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK, TRUE);
								m_bFinding = TRUE;
							}
							break;
						}
					}
					
				}
				
			}

		    //再递归处理子节点的兄弟节点的子节点和兄弟节点
			FindImpluseOr485Module(hBrotherItem,image,kinds);
			hBrotherItem = m_datatree.GetNextSiblingItem(hBrotherItem);
		} 

	}

}

//显示数据
void CMyDialogBar::initializeFieldInfo(CString m_title,CString m_totalsql,int columns,VARIANT  position)
{
    //得到DIALOGBAR上的变量
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	pMainFrm->m_wndMyDialogData.initializeFieldInfo(m_title,m_totalsql,columns,position);
}

void CMyDialogBar::OnListselect() 
{	
	VARIANT        position;
    position.vt   =   VT_I4;//记录位置
    position.lVal =       2;
	//显示所选择模块
	initializeFieldInfo("所选模块为",SelectCondition(),3,position);//显示数据
}



//提出时间列表框
void CMyDialogBar::InitializeCombo()
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
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT GARRISON_HALTTIME from TB_GARRISON order by GARRISON_HALTTIME "));
		m_list.ResetContent();
	
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_list.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//公司级完
		
		delete m_pDatabase;
		m_pDatabase = NULL; 

		if(m_list.GetCount() >0)
		{
			//m_list.SetCurSel(0);
			m_list.SetCurSel(m_list.GetCount()-1);
		}
	
	}
 
    //如果是正式读表
	if(m_radio1 == 0)
	{
		CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
		pt->ShowWindow(SW_HIDE);
	}

}


void CMyDialogBar::OnCloseupAppearcombo() 
{
	UpdateData(TRUE);
	CShowDataDlg    dlg;
	CString      Str;

	switch(m_AppearList.GetCurSel())
	{
	case 0:
		{
			dlg.m_Kinds        =         1;        //显示读上来的数据
			dlg.m_Select[0]    =  m_check1;        //有功电度
			dlg.m_Select[1]    =  m_check2;        //无功电度
			dlg.m_Select[2]    =  m_check3;        //ABC三相电流
			dlg.m_Select[3]    =  m_check4;        //ABC三相电压
			dlg.m_Select[4]    =  m_check5;        //手拉手有功总
			dlg.m_Select[5]    =  m_check6;        //手拉手无功总
			dlg.m_Select[6]    =  m_check7;        //模块号
			dlg.m_Select[7]    =  m_check8;        //用户名及地址
			dlg.m_Select[8]    =  m_check9;        //尖峰电量
			dlg.m_Select[9]    =  m_check10;       //峰电量
			dlg.m_Select[10]   =  m_check11;       //谷电量
			dlg.m_Select[11]   =  m_check12;       //平电量
			dlg.m_Select[12]   =  m_check13;       //功率因数
			dlg.m_TableKinds   = m_radio1;         //表种类
			dlg.m_Condtion     = SelectCondition();//选择条件
			dlg.m_TimeRange    = m_DSCondition;    //时间范围
			dlg.m_TimeRangeStr = m_TimeRangeStr;   //时间范围字符
			break;
		}
	case 1:
		{
			dlg.m_Kinds        =               0; //显示没有读上来的模块
			dlg.m_TableKinds   =         m_radio1; //表种类
			dlg.m_Condtion     = SelectCondition();//选择条件
			dlg.m_TimeRange    =    m_DSCondition; //时间范围
			dlg.m_TimeRangeStr =   m_TimeRangeStr; //时间范围字符
			break;
		}

	}

	dlg.DoModal();
}

void CMyDialogBar::OnRadio1() 
{
	UpdateData(TRUE);
    
	//不能删除数据
	CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
	pt->ShowWindow(SW_HIDE);
  	OnRadio38();  
	m_radio4 = 0;
	UpdateData(FALSE);
}

void CMyDialogBar::OnRadio2() 
{	
	//时间查询出来
	UpdateData(TRUE);
	InitializeCombo();
	OnRadio37();
	m_radio4 = 1;
	UpdateData(FALSE);	
}

void CMyDialogBar::OnRadio38() 
{	
	CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
	pt->ShowWindow(SW_HIDE);
	m_TimeRangeStr = "所有";
	m_DSCondition  = "ALL";	

	UpdateData(TRUE);
}

void CMyDialogBar::OnRadio37() 
{	

	if(m_radio1 == 0)
	{
		
		CTimeSelectDlg       dlg;
		CString m_BeginStr,m_EndStr;
		
		CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
		pt->ShowWindow(SW_HIDE);
		
		if(dlg.DoModal() == IDOK)
		{    
			m_BeginStr.Format("%4d-%02d-%02d %02d:%02d:%02d",dlg.m_Begin.GetYear(),dlg.m_Begin.GetMonth(),dlg.m_Begin.GetDay(),0,0,0);
			m_EndStr.Format("%4d-%02d-%02d %02d:%02d:%02d",dlg.m_End.GetYear(),dlg.m_End.GetMonth(),dlg.m_End.GetDay(),0,0,0);
			m_DSCondition.Format("TB_REALTIME.REALTIME_TRANSCRIBETIME>='%s' AND TB_REALTIME.REALTIME_TRANSCRIBETIME<='%s'",m_BeginStr,m_EndStr);
			m_TimeRangeStr.Format("%s－%s",m_BeginStr,m_EndStr);
		
		}
		else
		{
			m_radio4 = 0;
			UpdateData(FALSE);
		}

	}
	else
	{
		CWnd* pt = GetDlgItem(IDC_LISTCOMBO);
		pt->ShowWindow(SW_SHOW);
		
		//如果没有选择列
		if(m_list.GetCurSel() == LB_ERR)
		{
			return;
		}
		
		//找到时间值
		m_list.GetLBText(m_list.GetCurSel(),m_DSCondition);
		m_DSCondition.TrimLeft();
		m_DSCondition.TrimRight();
		m_TimeRangeStr = m_DSCondition;	
	}	

}

void CMyDialogBar::OnCloseupListcombo() 
{
	UpdateData(TRUE);
	
	//如果没有选择列
	if(m_list.GetCurSel() == LB_ERR)
	{
		return;
	}

	//找到时间值
	m_list.GetLBText(m_list.GetCurSel(),m_DSCondition);
	m_DSCondition.TrimLeft();
	m_DSCondition.TrimRight();
	m_TimeRangeStr = m_DSCondition;		
}

