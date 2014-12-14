// lane.h: interface for the lane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANE_H__80597823_F090_4976_9DA7_0DCC3BBD9602__INCLUDED_)
#define AFX_LANE_H__80597823_F090_4976_9DA7_0DCC3BBD9602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include "changeable_cell.h"
class simworld;
class CBmp;

class lane  
{
public:
	lane(int nLaneid);
	virtual ~lane();
protected:
	int isave;
	char *buf ;
	unsigned char* bitbuf;
	int laneid;
	int icount;
	double drate;
public:
	vector<changeable_cell*> cells;
	int car_count;
public:
//	void savebitmap(LPCTSTR szBMPFileName,BYTE* pbit);
	friend class simworld;
	bool savetrace(char* p , const char *name) ;	
	void initlane(const int d);

	bool is_generate_car();
	bool is_accelerate();
	int getgap( int index );
	void saveBuf( int d );

	int getlaneid();
	void setlaneid(int id);

	int SetLaneK(const int k);
	int SetLaneQ(const int q);
protected:
	CBmp *pbmp;	

public:
	// 仿真结束时记录速度信息
	bool saverecord();
};
class CBmp{
private:
	LPBITMAPINFO lpbmih;
	BITMAPFILEHEADER bmfh;

	HDC hdc,hdcMem;
	HBITMAP hBitMap ;
	CBitmap *pBitMap;
	CDC *pMemDC;
	BYTE *pBits;	
	
	int iWidth;
	int iHeight;
	int iPixel;

public:
	CBmp(int width,int height)
		:lpbmih(NULL),pBitMap(NULL),pMemDC(NULL),pBits(NULL){
		//设置初始信息
		iWidth = width;
		iHeight = height;
		iPixel = 16;

		hdc = NULL;
		hdcMem = NULL;
		hBitMap = NULL;

		//图形格式参数
		lpbmih = new BITMAPINFO;
		lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		lpbmih->bmiHeader.biWidth = iWidth;
		lpbmih->bmiHeader.biHeight = iHeight;
		lpbmih->bmiHeader.biPlanes = 1;
		lpbmih->bmiHeader.biBitCount = iPixel;
		lpbmih->bmiHeader.biCompression = BI_RGB;
		lpbmih->bmiHeader.biSizeImage = 0;
		lpbmih->bmiHeader.biXPelsPerMeter = 0;
		lpbmih->bmiHeader.biYPelsPerMeter = 0;
		lpbmih->bmiHeader.biClrUsed = 0;
		lpbmih->bmiHeader.biClrImportant = 0;
		

		hdc = CreateIC(TEXT("DISPLAY"),NULL,NULL,NULL);
		hdcMem = CreateCompatibleDC(hdc);
		hBitMap = CreateDIBSection(hdcMem,lpbmih,DIB_RGB_COLORS,(void **)&pBits,NULL,0);
		pBitMap = new CBitmap;
		pBitMap->Attach(hBitMap);
		pMemDC = new CDC;
		pMemDC->Attach(hdcMem);
		pMemDC->SelectObject(pBitMap);

		CRect rc(0,0,iWidth,iHeight);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->FillSolidRect(&rc,RGB(255,255,255));
		
		//设置文件头结构
		*((char *)&bmfh.bfType) = 'B';
		*(((char *)&bmfh.bfType) + 1) = 'M';
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) ;
		bmfh.bfSize = bmfh.bfOffBits + (iWidth * iHeight) * iPixel / 8;
	}
	~CBmp(){
		pMemDC->DeleteDC();
		delete pMemDC; pMemDC = NULL;
		delete pBitMap; pBitMap = NULL;
		delete lpbmih; lpbmih = NULL;
	}
	void SaveImg(char* filename){
		CFile file;
		if(file.Open(filename,CFile::modeWrite | CFile::modeCreate))
		{
			file.Write(&bmfh,sizeof(BITMAPFILEHEADER));
			file.Write(&(lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER));
			file.Write(pBits,((iWidth * iHeight) * iPixel / 8));
			file.Close();
		}
	}
	void DrawBmpLine(POINT p1,POINT p2,UINT v){
		//p1.x *= 2;
		//p1.y *= 2;
		//p2.x *= 2;
		//p2.y *= 2;
		DWORD linestyle[] = {0x00000000,0x000A0A0A,0x00505050,0x00323232,0x00969696,0x00B4B4B4};
	//	UINT linewidth[] = { 6,5,4,3,2,1 };
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, linestyle[v]);
		CPen *oldPen = pMemDC->SelectObject(&pen); 
		pMemDC->MoveTo(p1);
		pMemDC->LineTo(p2);
		pMemDC->SelectObject(oldPen); 
		pen.DeleteObject();
		oldPen = NULL;		
		
	}
};
#endif // !defined(AFX_LANE_H__80597823_F090_4976_9DA7_0DCC3BBD9602__INCLUDED_)
