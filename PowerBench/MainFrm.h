
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ActionEnum.h"
#include "AmmeterView.h"

#include "OutputWnd.h"
#include "PropertiesView.h"

#include "Resource.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
};

class  CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	BOOL RunAction(ActionEnum actionID);

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CAmmeterView         m_wndAmmeterView;
	
	COutputWnd        m_wndOutput;
	CPropertiesView    m_PropertiesView;
	COutlookBar       m_wndNavigationBar;
public:
	BEGIN_DELEGATE_MAP(CMainFrame)
		EVENT_DELEGATE_ENTRY(OnSelected,System::Object^ ,PowerBenchSharpLib::SelectItemEventArgs^ )
	END_DELEGATE_MAP()

	void OnSelected(System::Object^ Sender,PowerBenchSharpLib::SelectItemEventArgs^ eventargs);

//private:
	//void OnChanged(System::Object Sender,System::EventHandler<Tigera::LibCommon::TiEventArgs<System::Object^>^ >^ eventargs);
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
public:
	afx_msg void OnMenuFrameparse();
	afx_msg void OnMenuNetworkConfig();
	afx_msg void OnMenuNetListen();
	afx_msg void OnMenuNetConnect();
	afx_msg void OnSelfTest();
	afx_msg void OnOutterSetting();
	afx_msg void OnMenuOutpowerTest();
	afx_msg void OnMenuCurrentcommutest();
	afx_msg void OnUsagehisQuery();
};


