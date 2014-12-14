#pragma once


// CDigSet 对话框

class CDigSet : public CDialog
{
	DECLARE_DYNAMIC(CDigSet)

public:
	CDigSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDigSet();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 元胞格数
	int m_dist;
};
