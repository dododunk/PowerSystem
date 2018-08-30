
// PowerBenchView.h : CPowerBenchView 类的接口
//

#pragma once

#include "resource.h"
class CPowerBenchDoc;

class CBaseForm;
class CPowerBenchView : public CFormView
{
public: // 仅从序列化创建
	CPowerBenchView();
protected:
	DECLARE_DYNCREATE(CPowerBenchView)

public:
	enum{ IDD = IDD_POWERBENCH_FORM };

// 特性
public:
	CPowerBenchDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

	/////////////////////
	CBaseForm* m_pChildTransForm;

// 实现
public:
	virtual ~CPowerBenchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void CenterChildTransForm();

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PostNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // PowerBenchView.cpp 中的调试版本
inline CPowerBenchDoc* CPowerBenchView::GetDocument() const
   { return reinterpret_cast<CPowerBenchDoc*>(m_pDocument); }
#endif

