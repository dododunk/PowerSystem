#pragma once
#include "afxwin.h"
#pragma warning(disable: 4482)

//template<int TResourceID>
class CBaseForm :
	public CDialogEx
{
public:
	DECLARE_DYNAMIC(CBaseForm)
	enum ShowInPos
	{
		Center = 0,
		FixPos = 1,
	};
	virtual CString GetTitle()  const = 0;
	
	
	CBaseForm(UINT nIDTemplate,CWnd* pParent = NULL);
	virtual ~CBaseForm(void);
	int GetResult() const
	{
		return m_result;
	}


	BOOL ShowInView(CFormView* pParent,CBaseForm::ShowInPos pos = CBaseForm::ShowInPos::Center);

	//在父窗口进行resize时，调整
	int FitInResize()
	{
		return 0;
	}


	/*CSize GetDlgRectFromResouce() const 
	{
		return GetDlgRectFromResource(TResourceID);
	}
*/

	//not good...
	static CSize GetDlgRectFromResource(int ResourceDlgID,HMODULE hmodule = GetModuleHandle(NULL));
protected:
	CFormView* pParent;
	int m_result;

private:
	CBaseForm(const CBaseForm& objectSrc);              // no implementation
	void operator=(const CBaseForm& objectSrc);       // no implementation
};

