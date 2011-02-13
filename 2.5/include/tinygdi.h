//----------------------------
//tiny 2.5
//tinygdi.h - ������� GDI � DC
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#pragma comment(lib,"Msimg32.lib")//��� ���������

namespace tiny{

class TINYDC;

//------------------
//������� ������ GDI
//------------------
class TINYGDIObject: public TINYObject
{
public:
	TINYGDIObject();
protected:
	HGDIOBJ _hobj;//������ GDI
public:
	HGDIOBJ GetHGDIOBJ();//�������� HGDIOBJ
	bool Attach(HGDIOBJ hobj);//������� � HGDIOBJ
	bool Delete();//������� ������ GDI
	operator HGDIOBJ();	
};

//------
//������
//------
class TINYBitmap: public TINYGDIObject
{
public:
	TINYBitmap();
	TINYBitmap(UINT bmp);
	TINYBitmap(int w,int h,int bpp,void *bits);
public:
	HBITMAP GetHBITMAP();//�������� HBTIMAP
	bool Create(int w,int h,int bpp/*���-�� ����� �� �������*/,
		void* bits/*��������� �� ������ ��������*/);
	bool LoadBitmap(UINT bmp);//��������� ������
	bool CreateCompatibleBitmap(TINYDC* dc,int w,int h);//������� ����������� ������
	int GetW();//�������� ������
	int GetH();//�������� ������
	operator HBITMAP();	
};

//-----
//�����
//-----
class TINYBrush: public TINYGDIObject
{
public:
	TINYBrush();
	TINYBrush(TINYBitmap* bmp);
	TINYBrush(COLORREF color);
public:
	HBRUSH GetHBRUSH();//�������� HBRUSH
	bool CreateBitmapBrush(TINYBitmap* bmp);//������� ����� �� �������
	bool CreateSolidBrush(COLORREF color);//������� ������� �����
	bool CreateSysColorBrush(int color);//������� ����� ���������� �����
	operator HBRUSH();	
};

//----
//����
//----
class TINYPen: public TINYGDIObject
{
public:
	TINYPen();
	TINYPen(int style,int w,COLORREF color);
public:
	HPEN GetHPEN();//�������� HPEN
	bool Create(int style,int w,COLORREF color);//������� ����
	operator HPEN();	
};

//-----
//�����
//-----
class TINYFont: public TINYGDIObject
{
public:
	HFONT GetHFONT();//�������� HFONT
	bool GetDefaultFont();//�������� ����������� �����
	//������� �����
	bool Create(LPCWSTR name,//L"Default" - ����������� �����
		int size,//0 - ����������� ������
		bool bold,//������
		bool italic=false,//���������
		bool underline=false,//������������
		bool strikeout=false);//�����������
	operator HFONT();
};

//------
//������
//------
class TINYRgn: public TINYGDIObject
{
public:
	HRGN GetHRGN();//�������� HRGN
	bool CreateRectRgn(RECT rect);//������� ������ �� �������
	bool CreateEllipticRgn(RECT rect);//������� �������� ������
	//������� ������ � ������������� ������
	bool CreateRoundRectRgn(RECT rect,
		int corw,//����������� ���� �� �����������
		int corh//����������� ���� �� ���������
		);
	bool CombineRgn(TINYRgn *rgn1,TINYRgn *rgn2,int mode);//���������� ������� 
	//bool SetToWindow(TINYBaseWnd *wnd);//���������� ������ ����
	operator HRGN();
};

//--
//DC
//--
class TINYDC: public TINYObject
{
protected:
	HDC _dc;//HDC
	PAINTSTRUCT _ps;
	HWND _parent;//������������ ����(��� Begin/EndPaint)
public:

	//������� DC
	HDC GetHDC();//�������� HDC
	bool Attach(HDC hdc);//������� � HDC
	bool CreateCompatibleDC(TINYDC *dc);//������� ����������� DC
	bool Delete();//������� DC
	bool Release(HWND wnd);//���������� DC
	bool GetDC(HWND hwnd);//�������� DC ����
	RECT GetClipBox();//�������� ������� DC
	bool BitBlt(int x,int y,int w,int h,
		TINYDC *src,int nx,int ny,DWORD mode);//����������� ����������
	bool BeginPaint(HWND parent/*������������ ����*/);//������ ���������
	bool EndPaint();//��������� ���������

	//������� ��������� ������
	bool TextOut(LPCWSTR text,int x,int y);//������� �����
	bool DrawText(LPCWSTR text,RECT rect,UINT format);//���������� �����
	bool SetTextColor(COLORREF color);//���������� ���� ������

	//������� ���������
	bool FillRect(RECT rect,TINYBrush* brush);//��������� �������
	//����������� �������
	bool FillGradient(RECT rect,
		COLORREF clrbegin,//���� ������ ���������
		COLORREF clrend,//���� ����� ���������
		bool vert//����������� ��� ������������� 
		);
	bool DrawRectangle(RECT rect);//���������� �������������
	//���������� ������������� � ������������� ������
	bool DrawRoundRect(RECT rect,
		int corw,//����������� ���� �� �����������
		int corh//����������� ���� �� ���������
		);
	bool DrawEllipse(RECT rect);//���������� ������
	bool DrawFocusRect(RECT rect);//���������� ����� ������

	//������� ��������� �����
	bool MoveTo(int x,int y);//������� �������
	bool LineTo(int x,int y);//���������� �����

	//������� ������ � ����� � �.�.
	bool SetPixel(int x,int y,COLORREF color);//���������� ���� �������
	COLORREF GetPixel(int x,int y);//�������� ���� �������
	bool SetBkColor(COLORREF color);//���������� ���� ����
	COLORREF GetBkColor();//�������� ���� ����
	bool SetBkMode(int mode);//���������� ����� ����(����������/������������)
	int GetBkMode();//�������� ����� ����(����������/������������)

	//������� ������ � ��������� GDI
	bool SelectObject(TINYGDIObject* obj);//������� ������
};

//--------------------------
//DC c ������� �������������
//--------------------------
class TINYDBDC: public TINYDC
{
protected:
	TINYDC _memdc;//������ ������
	TINYBitmap _membmp;//����������� ������ ��� ������� �������
public:
	TINYDC* GetMemDC();//�������� ������ ������
	bool InitDoubleBuffer();//������������� ������� ������������
	bool DrawDoubleBuffer();//���������� ������ ������
};

};