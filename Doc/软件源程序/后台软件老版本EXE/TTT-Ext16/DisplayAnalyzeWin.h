#if !defined(AFX_DISPLAYANALYZEWIN_H__9074247C_A9DD_48BA_A03C_A726A73625B8__INCLUDED_)
#define AFX_DISPLAYANALYZEWIN_H__9074247C_A9DD_48BA_A03C_A726A73625B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayAnalyzeWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayAnalyzeWin window

class CDisplayAnalyzeWin : public CStatic
{
// Construction
public:
	CDisplayAnalyzeWin();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayAnalyzeWin)
	//}}AFX_VIRTUAL

// Implementation
public:
//	void NewDataInAnalyze(unsigned short *pValue,UINT nCount);
	void NewDataIn(int *pValue,UINT nCount);
	BOOL     m_bIsFirst;
	CRect  m_rectClient;
	int nHeight, nWidth;
	UINT          m_nY0;
	UINT    m_nCycleNum;
	UINT m_nCh1CurPoints;
	int m_pCh1YValues[80000];
	int    m_Splice[80000];//叠加数组
	int    m_SpliceUp[80000];//向上所有的波叠加
    int    m_SpliceDown[80000];//向下所有的波叠加
    int m_PiPaiWave[80000];//匹配波
    int  m_niheWave[80000];//拟合曲线
	int      m_temp[80000];
	virtual ~CDisplayAnalyzeWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayAnalyzeWin)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYANALYZEWIN_H__9074247C_A9DD_48BA_A03C_A726A73625B8__INCLUDED_)
