#if !defined(AFX_DISPLAYWAVEWIN_H__44942A9F_549C_45C5_833A_272DCE6CDDB8__INCLUDED_)
#define AFX_DISPLAYWAVEWIN_H__44942A9F_549C_45C5_833A_272DCE6CDDB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayWaveWin.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDisplayWaveWin window

class CDisplayWaveWin : public CStatic
{
// Construction
public:
	CDisplayWaveWin();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWaveWin)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ClearAllData();
	void NewDataInAnalyze(int *pValue, int nCount);
	int          nCount;
	int iCurPoint,iCurPointBk;
	int  m_nTotalPoints;
	int nHeight, nWidth;
	double        m_fDy;
	void NewDataIn(unsigned short *pValue, UINT nCount);
	int m_pCh0YValues[80000],m_pCh1YValues[80000],m_pCh2YValues[80000];
	int m_pCh3YValues[80000],m_pCh4YValues[80000],m_pCh5YValues[80000];
	int m_pCh8YValues[80000],m_pCh9YValues[80000],m_pCh10YValues[80000];
	COLORREF m_Color[3];
	UINT m_nCh0CurPoints,m_nCh1CurPoints,m_nCh2CurPoints;
	UINT m_nCh3CurPoints,m_nCh4CurPoints,m_nCh5CurPoints;
	UINT m_nCh8CurPoints,m_nCh9CurPoints,m_nCh10CurPoints;
	UINT m_nY0;
	CRect m_rectClient;
	BOOL m_bDisplayOn;
	BOOL m_bIsFirst;
	virtual ~CDisplayWaveWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayWaveWin)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYWAVEWIN_H__44942A9F_549C_45C5_833A_272DCE6CDDB8__INCLUDED_)
