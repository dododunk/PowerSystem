
#pragma once


typedef CWinFormsDialog<System::Windows::Forms::PropertyGrid> CPropertyGridHoldDlg;


class CPropertiesView : public CDockablePane
{
// 构造
public:
	CPropertiesView();


	BEGIN_DELEGATE_MAP(CPropertiesView)
		EVENT_DELEGATE_ENTRY(OnChanged,System::Object^ ,PowerBenchSharpLib::NodeEventArgs^ )
	END_DELEGATE_MAP()

	 void OnChanged(System::Object^ Sender,PowerBenchSharpLib::NodeEventArgs^  eventargs);
// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
	
	}

protected:
	CPropertyGridHoldDlg m_dlg;

// 实现
public:
	virtual ~CPropertiesView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	
	
	
	
	
	
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	
	
};

