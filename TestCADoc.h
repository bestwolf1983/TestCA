// TestCADoc.h : interface of the CTestCADoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCADOC_H__9A23A0D6_2A0A_4A40_8AAF_5E637DDFF04C__INCLUDED_)
#define AFX_TESTCADOC_H__9A23A0D6_2A0A_4A40_8AAF_5E637DDFF04C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Saved_Lane.h"

class CTestCADoc : public CDocument
{
protected: // create from serialization only
	CTestCADoc();
	DECLARE_DYNCREATE(CTestCADoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCADoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestCADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void DelDocument();
	void InitDocument();
	CTypedPtrArray<CObArray, Saved_Lane*> m_saved_lanes1;
	CTypedPtrArray<CObArray, Saved_Lane*> m_saved_lanes2;

// Generated message map functions
protected:
	//{{AFX_MSG(CTestCADoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCADOC_H__9A23A0D6_2A0A_4A40_8AAF_5E637DDFF04C__INCLUDED_)
