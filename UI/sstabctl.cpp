// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "sstabctl.h"

// Dispatch interfaces referenced by this interface



/////////////////////////////////////////////////////////////////////////////
// CSSTabCtl

IMPLEMENT_DYNCREATE(CSSTabCtl, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CSSTabCtl properties

/////////////////////////////////////////////////////////////////////////////
// CSSTabCtl operations

unsigned long CSSTabCtl::GetBackColor()
{
	unsigned long result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


void CSSTabCtl::SetRefFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CSSTabCtl::GetForeColor()
{
	unsigned long result;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetForeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CSSTabCtl::GetCaption()
{
	CString result;
	InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CSSTabCtl::GetEnabled()
{
	BOOL result;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CSSTabCtl::GetHWnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetHWnd(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CSSTabCtl::GetTabsPerRow()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTabsPerRow(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CSSTabCtl::GetTabs()
{
	short result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTabs(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CSSTabCtl::GetRows()
{
	short result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetRows(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CSSTabCtl::GetTab()
{
	short result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTab(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CSSTabCtl::GetTabOrientation()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTabOrientation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


void CSSTabCtl::SetPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CSSTabCtl::SetRefPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CSSTabCtl::GetShowFocusRect()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetShowFocusRect(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CSSTabCtl::GetWordWrap()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetWordWrap(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CSSTabCtl::GetStyle()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

float CSSTabCtl::GetTabHeight()
{
	float result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTabHeight(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CSSTabCtl::GetTabMaxWidth()
{
	float result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetTabMaxWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CSSTabCtl::GetMousePointer()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetMousePointer(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


void CSSTabCtl::SetMouseIcon(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CSSTabCtl::SetRefMouseIcon(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CSSTabCtl::GetOLEDropMode()
{
	long result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CSSTabCtl::SetOLEDropMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CSSTabCtl::OLEDrag()
{
	InvokeHelper(0x610, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


void CSSTabCtl::SetTabPicture(short Index, LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, newValue);
}

void CSSTabCtl::SetRefTabPicture(short Index, LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 Index, newValue);
}

BOOL CSSTabCtl::GetTabVisible(short Index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Index);
	return result;
}

void CSSTabCtl::SetTabVisible(short Index, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, bNewValue);
}

BOOL CSSTabCtl::GetTabEnabled(short sIndex)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		sIndex);
	return result;
}

void CSSTabCtl::SetTabEnabled(short sIndex, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sIndex, bNewValue);
}

CString CSSTabCtl::GetTabCaption(short sIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		sIndex);
	return result;
}

void CSSTabCtl::SetTabCaption(short sIndex, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 sIndex, lpszNewValue);
}