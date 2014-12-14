// TestCA.h : main header file for the TESTCA application
//

#if !defined(AFX_TESTCA_H__318BA32B_3A1A_4F98_9D02_5F6D91B5106C__INCLUDED_)
#define AFX_TESTCA_H__318BA32B_3A1A_4F98_9D02_5F6D91B5106C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCAApp:
// See TestCA.cpp for the implementation of this class
//

class CTestCAApp : public CWinApp
{
private:
	int m_irec;
	int m_iMAX_V;
	int m_idist;
	int m_itime;
	int m_ik;
	int m_iMAX_HV;
public:
	int GetK();
	void SetK(int k);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int GetRec() const;
	void SetRec(int rec);
	int GetMAX_V() const;
	void SetMAX_V(int v);
	void SetDist(int d);
	void SetTime(int t);
	int GetDist() const;
	int GetTime() const;
	void SetMax_HV(int v);
	int GetMax_HV() const;
	
	CTestCAApp();
public:
	//记录出错的迭代信息
	int errorrec0;
	int errorrec1;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCAApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestCAApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCA_H__318BA32B_3A1A_4F98_9D02_5F6D91B5106C__INCLUDED_)
