#if !defined(AFX_DIALOGRUN_H__9E6AD438_6ABA_4DA3_8C61_AF7825073F05__INCLUDED_)
#define AFX_DIALOGRUN_H__9E6AD438_6ABA_4DA3_8C61_AF7825073F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogRun dialog

class CDialogRun : public CDialog
{
// Construction
public:

	CDialogRun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogRun)
	enum { IDD = IDD_DIALOG1 };
	int		m_iradio;
	UINT	m_urate;
	int		m_timeset;
	int		m_vset;
	int		m_rec;
	int		m_kset;
	int		m_vset2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRun)
	virtual void OnOK();
	afx_msg void OnRadio2();
	afx_msg void OnRadio1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGRUN_H__9E6AD438_6ABA_4DA3_8C61_AF7825073F05__INCLUDED_)
