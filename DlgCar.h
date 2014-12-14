#if !defined(AFX_DLGCAR_H__9E02ECC0_3725_4ADB_82C5_C664361FE0EB__INCLUDED_)
#define AFX_DLGCAR_H__9E02ECC0_3725_4ADB_82C5_C664361FE0EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCar dialog

class CDlgCar : public CDialog
{
// Construction
public:
	CDlgCar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCar)
	enum { IDD = IDD_DIAL_CAR };
	int		m_carkind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCar)
	afx_msg void OnDone();
	afx_msg void OnHeavy();
	afx_msg void OnNormal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCAR_H__9E02ECC0_3725_4ADB_82C5_C664361FE0EB__INCLUDED_)
