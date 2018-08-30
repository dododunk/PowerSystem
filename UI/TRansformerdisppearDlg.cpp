// TRansformerdisppear.cpp : implementation file
//

#include "stdafx.h"

#include "TRansformerdisppearDlg.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRansformerdisppear dialog


CTRansformerdisppearDlg::CTRansformerdisppearDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTRansformerdisppearDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTRansformerdisppear)
	m_IsDaYongFu = FALSE;
	m_IsBT     =  TRUE;
	m_IsJuMin  = FALSE;
	//}}AFX_DATA_INIT
}


void CTRansformerdisppearDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTRansformerdisppear)
	DDX_Control(pDX, IDC_DATATREE, m_datatree);
	DDX_Check(pDX, IDC_CHECK2, m_IsDaYongFu);
	DDX_Check(pDX, IDC_CHECK3, m_IsBT);
	DDX_Check(pDX, IDC_CHECK1, m_IsJuMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTRansformerdisppearDlg, CDialog)
	//{{AFX_MSG_MAP(CTRansformerdisppear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTRansformerdisppear message handlers
//初始化树控件
void CTRansformerdisppearDlg::Initialize()
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
                      
					  //加变电站供电表
                      strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=9  AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
				 	  AddAllKindAmmeter(strSql,hSecond,13);
					  
					  //加变电站售电表
					  strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=8  AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
					  AddAllKindAmmeter(strSql,hSecond,12); 
					  
										  
					  //线路级开始
					  CDaoRecordset m_LinesSet(m_pDatabase);
					  strSql.Format("Select DISTINCT USER_LINENAME from TB_USER WHERE USER_COMPANY='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
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
								  strSql.Format("Select DISTINCT USER_TRANSFORMERNO from TB_USER WHERE USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  m_DeviceSet.Open(dbOpenSnapshot,strSql);

								  while (!m_DeviceSet.IsEOF())
								  {
									  
									  strSql.Format("TRANSFORMER_NO='%s'",V_I4(&m_DeviceSet.GetFieldValue(0)));
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
									  
									  m_DeviceSet.MoveNext();
									  //m_datatree.Expand(hFourth,TVE_EXPAND);
									  
								  }
								  m_DeviceSet.Close();
								  //变台完
	 
							  }
							  m_LinesSet.MoveNext();
							//m_datatree.Expand(hThird,TVE_EXPAND);
								  
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

    }

}


void CTRansformerdisppearDlg::AddAllKindAmmeter(CString condtion,HTREEITEM Item,int n)
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
			str = "【台公变总表】";
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



BOOL CTRansformerdisppearDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//初始化树控件
	Initialize();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//得到选择条件
CString CTRansformerdisppearDlg::SelectCondition()
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
								//	if(temp1 > 3)
									{
										str3 =  str3 + ")";
									}
								//	else
									{
								//		str3 =  str3 + " AND USER_AMMETERKIND<3)";
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

void CTRansformerdisppearDlg::OnOK() 
{

	UpdateData(TRUE);
	CString  strtemp;

    m_GetSubRangeStr = SelectCondition();
    m_GetSubRangeStr.TrimLeft();
	m_GetSubRangeStr.TrimRight();

	if(m_GetSubRangeStr.IsEmpty())
	{
		MessageBox("请选择要驻留读表的变台！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	strtemp = "";

	if(!(m_IsBT || m_IsJuMin || m_IsDaYongFu))
	{
		MessageBox("请选择驻留读表的对象！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	m_GetSubNameStr = GetSelectSubName();

	
//	m_GetSubNameStr = "《读表范围》\r\n" + GetSelectSubName();

//	m_GetSubNameStr = m_GetSubNameStr + "《读表对象》\r\n";

	//居民表
	if(m_IsJuMin)
	{
		
		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND = 0";
		}
		else
		{
			
			strtemp = strtemp + " OR USER_AMMETERKIND = 0";
		}
		
	//	m_GetSubNameStr = m_GetSubNameStr + "居民表  ";
		
	}
	
	
	//大用户表
	if(m_IsDaYongFu)
	{
		
		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND = 1";
		}
		else
		{
			strtemp = strtemp + " OR USER_AMMETERKIND = 1";
		}

	//	m_GetSubNameStr = m_GetSubNameStr + "大用户表  ";
		
	}
	
	//变台
    if(m_IsBT)
	{

		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND > 1";
		}
		else
		{
			strtemp = strtemp + " OR USER_AMMETERKIND > 1";
		}
		
//		m_GetSubNameStr = m_GetSubNameStr + "变台等  ";

	}

	m_GetSubRangeStr = "(" + m_GetSubRangeStr  + ") AND (" + strtemp + ")";
	CDialog::OnOK();

}



//得到选择变台名称
CString CTRansformerdisppearDlg::GetSelectSubName()
{  

	//第一级公司级
	HTREEITEM               hBootItem,hFirstItem; 
	HTREEITEM               hSecondItem,hThirdItem;
	
	//有一部份
    CString                m_SubNameStr,tr,str,tr1,tr2;
	str                =                    "";

	hBootItem  = m_datatree.GetRootItem();
	
	if(hBootItem == NULL)
	{
		return "";
	}

	m_SubNameStr = "线路名称          变台名称               读表对象";

	//居民表
	if(m_IsJuMin)
	{
		str = str + "居民表";
	}
	
	
	//大用户表
	if(m_IsDaYongFu)
	{

		if(str.IsEmpty())
		{
			str = str + "大用户表";
		}
		else
		{
			str = str + "、大用户表";
		}

	}
	
	//变台
    if(m_IsBT)
	{	
		if(str.IsEmpty())
		{
			str = str + "变台等";
		}
		else
		{	
			str = str + "、变台等";
		}
	}
	
	//第二级变电站
	if(m_datatree.ItemHasChildren(hBootItem))
	{	
		hFirstItem = m_datatree.GetChildItem(hBootItem);
		
		do
		{ 
			
			//第三级，线路级
			if(m_datatree.ItemHasChildren(hFirstItem) && (m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
			{	
			
				hSecondItem = m_datatree.GetChildItem(hFirstItem);
				do
				{
					
					//第四级，变台号级
					if(m_datatree.ItemHasChildren(hSecondItem) && (m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					{	
						
						hThirdItem = m_datatree.GetChildItem(hSecondItem);

						/*
						if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
						{
							tr  = m_datatree.GetItemText(hSecondItem)  + m_datatree.GetItemText(hThirdItem);
							AfxMessageBox(tr);

							m_SubNameStr = m_SubNameStr + tr  + "\r\n";
						}
						*/

						do
						{
							
							
							//第五级，模块号级
							/*
							if(m_datatree.ItemHasChildren(hThirdItem) && (m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{	
							
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
										
										
										tr  = m_datatree.GetItemText(hThirdItem)  + tr ;
										m_SubNameStr = m_SubNameStr + tr;
										//str8 = str8 + "USER_MODULENO="  + m_datatree.GetItemText(hThirdItem);
										
									
										
									}
								
									
								}while( (hFourthItem = m_datatree.GetNextSiblingItem(hFourthItem)) != NULL );
								
							}	
							//第五级完
							*/
							
							//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择  变台
						
							if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
							{
								tr1  = m_datatree.GetItemText(hSecondItem);
								tr2 = m_datatree.GetItemText(hThirdItem);

								tr1.TrimLeft();
								tr1.TrimRight();
								
								tr2.TrimLeft();
								tr2.TrimRight();

								tr.Format("%20s    %20s    %16s",tr1,tr2,str);
								tr.TrimLeft();
						    	tr.TrimRight();
								
								/*
								int k = tr.Find("【"); 
								if(k != -1)
								{
									tr = tr.Left(k);
								}
								*/
								
								/////////////
								//得到图处索引号
								//m_datatree.GetItemImage(hThirdItem,temp,temp1);
								
								//有两种情况
								//if(temp1 > 3)
								{
									
									//是线路的供电表或售电表,而不是变台名称
									//str4 = str4 + "(USER_MODULENO="  +  tr;
								}
								//else
								{
									//是变台名称
								//	str4 = str4 + "(USER_TRANSFORMERNO="  + "'" + tr + "'";
								}

							//	tr  =   + tr ;
								m_SubNameStr = m_SubNameStr + "\r\n" + tr ;
								
															
							}
							
							
							
						}while( (hThirdItem = m_datatree.GetNextSiblingItem(hThirdItem)) != NULL );

					
						
					 }	
					 //第四级完
					 
							 
				   }while( (hSecondItem = m_datatree.GetNextSiblingItem(hSecondItem)) != NULL );
						
						
				  }
				  
				 //第三级完
				  
				  
			}while( (hFirstItem = m_datatree.GetNextSiblingItem(hFirstItem)) != NULL );
			
			
		}	
		//第二级完
		
		return m_SubNameStr;
		
}