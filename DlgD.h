#pragma once

// CDlgD �Ի���

class CDlgD : public CDialog
{
	DECLARE_DYNAMIC(CDlgD)

public:
	CDlgD(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgD();

// �Ի�������
	enum { IDD = IDD_DLG_D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
};
