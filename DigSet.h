#pragma once


// CDigSet �Ի���

class CDigSet : public CDialog
{
	DECLARE_DYNAMIC(CDigSet)

public:
	CDigSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDigSet();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Ԫ������
	int m_dist;
};
