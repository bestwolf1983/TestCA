// TestCAView.h : interface of the CTestCAView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCAVIEW_H__DA80DA50_36E5_432D_9127_9DD2913916DA__INCLUDED_)
#define AFX_TESTCAVIEW_H__DA80DA50_36E5_432D_9127_9DD2913916DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "simworld.h"
#include "TestCADoc.h"
#include "UIConfig.h"
#include "DlgCar.h"
#include "DlgD.h"

class simworld;

class CTestCAView : public CView
{
public:
	BOOL IsSetting;
	CDlgCar* pcar_setting;
public:
	CUIConfig UI;
protected: // create from serialization only
	CTestCAView();
	DECLARE_DYNCREATE(CTestCAView)

// Attributes
public:
	CTestCADoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCAView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsMB;
	CFont m_font;
	UINT m_utimerate;
	UINT m_utimepassed;
	void EndSim();
	void BeginSim(simworld* p_simworld);
	virtual ~CTestCAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestCAView)
	afx_msg void OnRun1();
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnSetcar();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSet();
public:
	afx_msg void OnSetd();
	BOOL IsD;
public:
	afx_msg void OnUpdateStca(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TestCAView.cpp
inline CTestCADoc* CTestCAView::GetDocument()
   { return (CTestCADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCAVIEW_H__DA80DA50_36E5_432D_9127_9DD2913916DA__INCLUDED_)
