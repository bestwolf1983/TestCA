#pragma once

// CDlgD 对话框

class CDlgD : public CDialog
{
	DECLARE_DYNAMIC(CDlgD)

public:
	CDlgD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgD();

// 对话框数据
	enum { IDD = IDD_DLG_D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
};
