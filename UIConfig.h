// UIConfig.h: interface for the CUIConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_)
#define AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUIConfig  
{
public:
	CUIConfig();
	virtual ~CUIConfig();
public:
	void SetCar(CPoint point, int carkind,CDC* pDC);
	BOOL DrawLane(CDC* pDC,UINT laneid);
	BOOL DrawCell(CDC* pDC,UINT laneid, int t);
	//С�ͳ���
	int* ar_cars1;
	int* ar_cars2;
	//�س���
	vector<POINT> ptHeavyCar;
	//�������
	vector<int> iDetector;
private:
	BOOL InitLaneInterface();
	//lanes[2]�������������Ľ�������
	CRect lanes[2];
	//��¼ÿ��Ԫ�����λ�õĵ�λ�壬����ÿ��Ԫ�������Ͻ�����
	POINT* ptcells1;
	POINT* ptcells2;

public:
	void SetDetector(CPoint point, CDC* pDC);
public:
	// �������������е�Ԫ
	void ClearAll(void);
};

#endif // !defined(AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_)
