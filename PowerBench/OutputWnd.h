
#pragma once
#include <list>
/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口

class FixlinesList
{
public:
	FixlinesList();
	CString& ToCString() const;
	void AddString(const CString& data);
	void SetLineNum(int linenum);
private: 
	int m_linenum;
		
	std::list<CString> m_datas;
};

class COutputEdit : public CEdit
{
// 构造
public:
	COutputEdit();

// 实现
public:
	void AddString(const CString& data);
	virtual ~COutputEdit();
	FixlinesList m_datas;

protected:
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};


typedef CWinFormsDialog<PowerBenchSharpLib::UCAmmetersOpe> CUCAmmetersOpeHoldDlg;
class COutputWnd : public CDockablePane
{
// 构造
public:

	BEGIN_DELEGATE_MAP(COutputWnd)
		EVENT_DELEGATE_ENTRY(OnLogMsg,System::Object^ ,PowerBenchSharpLib::LogEventArgs^ )
		EVENT_DELEGATE_ENTRY(OnLogMsg1,System::Object^ ,exportapi::LogEventArgs^ )
	END_DELEGATE_MAP()
	 void OnLogMsg(System::Object^ ,PowerBenchSharpLib::LogEventArgs^ );
	 void OnLogMsg1(System::Object^ ,exportapi::LogEventArgs^ );
	 
	COutputWnd();
	static void WriteLog(const CString& msg);
//private: 
	static COutputWnd* pInstance ;//= NULL;;

	void UpdateFonts();

	PowerBenchSharpLib::UCAmmetersOpe^ GetHoldControl();
// 特性
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputEdit m_wndOutputLog;
	COutputEdit m_wndOutputDebug;
	COutputEdit m_wndOutputFind;
	//CUCAmmetersOpeHoldDlg m_ctrl;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

