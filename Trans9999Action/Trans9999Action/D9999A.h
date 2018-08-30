#pragma once
//#include "BaseForm.h"

// CD9999A dialog

class CD9999A : public CDialogEx
{
	DECLARE_DYNAMIC(CD9999A)

public:
	CD9999A(CWnd* pParent = NULL);   // standard constructor
	virtual ~CD9999A();

// Dialog Data
	enum { IDD = IDD_DIALOG_D9999A };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
