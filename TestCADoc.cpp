// TestCADoc.cpp : implementation of the CTestCADoc class
//

#include "stdafx.h"
#include "TestCA.h"

#include "TestCADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestCADoc

IMPLEMENT_DYNCREATE(CTestCADoc, CDocument)

BEGIN_MESSAGE_MAP(CTestCADoc, CDocument)
	//{{AFX_MSG_MAP(CTestCADoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCADoc construction/destruction

CTestCADoc::CTestCADoc()
{
	// TODO: add one-time construction code here

}

CTestCADoc::~CTestCADoc()
{
}

BOOL CTestCADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestCADoc serialization

void CTestCADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_saved_lanes1.Serialize(ar);
	m_saved_lanes2.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTestCADoc diagnostics

#ifdef _DEBUG
void CTestCADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestCADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
	dc<<"Memory Set Error!";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestCADoc commands

void CTestCADoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
}

void CTestCADoc::InitDocument()
{	
	const int _time = ((CTestCAApp*)AfxGetApp())->GetTime();
	try{
		m_saved_lanes1.SetSize(_time);
		m_saved_lanes2.SetSize(_time);
	}
	catch(CMemoryException e){

	}
	for(int t = 0; t < _time; t++){
		try{
			m_saved_lanes1[t] = new Saved_Lane();
			m_saved_lanes2[t] = new Saved_Lane();
		}
		catch(CMemoryException e){
	
		}
	}
}

void CTestCADoc::DelDocument()
{
	const int _time = ((CTestCAApp*)AfxGetApp())->GetTime();
	for(int t = 0; t < _time; t++){
		delete m_saved_lanes1[t];
		delete m_saved_lanes2[t];
	}

	m_saved_lanes1.RemoveAll();
	m_saved_lanes2.RemoveAll();


}
