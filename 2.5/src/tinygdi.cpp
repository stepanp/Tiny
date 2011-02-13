//------------------------------
//tiny 2.5
//tinygdi.cpp - ������� GDI � DC
//� 2009-2010 Stepan Prokofjev
//------------------------------

#include "tinygdi.h"

using namespace tiny;

//------------------
//������� ������ GDI
//------------------

TINYGDIObject::TINYGDIObject() {_hobj=0;}
//�������� HGDIOBJ
HGDIOBJ TINYGDIObject::GetHGDIOBJ() {return _hobj;}
//������� � HGDIOBJ
bool TINYGDIObject::Attach(HGDIOBJ hobj)
{
	HGDIOBJ gdiobj=hobj;
	if(!gdiobj) return false;
	Delete();//������� ���������� ������ GDI
	_hobj=gdiobj;
	return true;
}
//������� ������ GDI
bool TINYGDIObject::Delete()
{
	if(_hobj) if(!DeleteObject(_hobj)) return false;
	return true;
}
TINYGDIObject::operator HGDIOBJ() {return _hobj;}

//------
//������
//------

TINYBitmap::TINYBitmap() {}
TINYBitmap::TINYBitmap(UINT bmp) {LoadBitmap(bmp);}
TINYBitmap::TINYBitmap(int w,int h,int bpp,void *bits) {Create(w,h,bpp,bits);}
//�������� HBTIMAP
HBITMAP TINYBitmap::GetHBITMAP() {return HBITMAP(GetHGDIOBJ());}
bool TINYBitmap::Create(int w,int h,int bpp/*���-�� ����� �� �������*/,
						void* bits/*��������� �� ������ ��������*/)
{
	return Attach(CreateBitmap(w,h,1,bpp,bits));
}
//��������� ������
bool TINYBitmap::LoadBitmap(UINT bmp)
{
	return Attach(::LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(bmp)));
}
//������� ����������� ������
bool TINYBitmap::CreateCompatibleBitmap(TINYDC* dc,int w,int h)
{
	if(!dc) return false;
	return Attach(::CreateCompatibleBitmap(dc->GetHDC(),w,h));
}
//�������� ������
int TINYBitmap::GetW() 
{
	BITMAP bmp;
	GetObject(GetHBITMAP(),sizeof(BITMAP),&bmp);//�������� �������� BITMAP
	return bmp.bmWidth;
}
//�������� ������
int TINYBitmap::GetH() 
{
	BITMAP bmp;
	GetObject(GetHBITMAP(),sizeof(BITMAP),&bmp);//�������� �������� BITMAP
	return bmp.bmHeight;
}
TINYBitmap::operator HBITMAP() {return GetHBITMAP();}

//-----
//�����
//-----

//�������� HBRUSH
TINYBrush::TINYBrush() {}
TINYBrush::TINYBrush(TINYBitmap* bmp) {CreateBitmapBrush(bmp);}
TINYBrush::TINYBrush(COLORREF color) {CreateSolidBrush(color);}
HBRUSH TINYBrush::GetHBRUSH() {return HBRUSH(GetHGDIOBJ());}
//������� ����� �� �������
bool TINYBrush::CreateBitmapBrush(TINYBitmap* bmp)
{
	if(!bmp) return false;
	return Attach(CreatePatternBrush(bmp->GetHBITMAP()));
}
//������� ������� �����
bool TINYBrush::CreateSolidBrush(COLORREF color)
{
	return Attach(::CreateSolidBrush(color));
}
//������� ����� ���������� �����
bool TINYBrush::CreateSysColorBrush(int color)
{
	return Attach(GetSysColorBrush(color));
}
TINYBrush::operator HBRUSH() {return GetHBRUSH();}

//----
//����
//----

TINYPen::TINYPen() {}
TINYPen::TINYPen(int style,int w,COLORREF color) {Create(style,w,color);}
//�������� ����
HPEN TINYPen::GetHPEN() {return HPEN(GetHGDIOBJ());}
//������� ����
bool TINYPen::Create(int style,int w,COLORREF color)
{
	return Attach(CreatePen(style,w,color));
}
TINYPen::operator HPEN() {return GetHPEN();}

//-----
//�����
//-----

//�������� HFONT
HFONT TINYFont::GetHFONT() {return HFONT(GetHGDIOBJ());}
//�������� ����������� �����
bool TINYFont::GetDefaultFont()
{
	return Attach(HFONT(GetStockObject(DEFAULT_GUI_FONT)));
}
//������� �����
bool TINYFont::Create(LPCWSTR name,//L"Default" - ����������� �����
		int size,//0 - ����������� ������
		bool bold,//������
		bool italic,//���������
		bool underline,//������������
		bool strikeout)//�����������
{
	//������� ������
	DWORD weight=FW_NORMAL;//����������
	if(bold) weight=FW_BOLD;//������
	return Attach(CreateFont(size,0,0,0,weight,
		DWORD(italic),DWORD(underline),DWORD(strikeout),
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		name));
}
TINYFont::operator HFONT() {return GetHFONT();}

//------
//������
//------

//�������� HRGN
HRGN TINYRgn::GetHRGN() {return HRGN(GetHGDIOBJ());}
//������� ������ �� �������
bool TINYRgn::CreateRectRgn(RECT rect)
{
	return Attach(::CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom));
}
//������� �������� ������
bool TINYRgn::CreateEllipticRgn(RECT rect)
{
	return Attach(::CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom));
}
//������� ������ � ������������� ������
bool TINYRgn::CreateRoundRectRgn(RECT rect,
		int corw,//����������� ���� �� �����������
		int corh//����������� ���� �� ���������
		)
{
	return Attach(::CreateRoundRectRgn(rect.left,rect.top,rect.right,rect.bottom,
		corw,corh));
}
//���������� ������� 
bool TINYRgn::CombineRgn(TINYRgn *rgn1,TINYRgn *rgn2,int mode)
{
	HRGN hrgn1=0;
	HRGN hrgn2=0;
	if(rgn1) hrgn1=rgn1->GetHRGN();
	if(rgn2) hrgn2=rgn2->GetHRGN();
	if(::CombineRgn(GetHRGN(),hrgn1,hrgn2,mode)==ERROR) return false;
	return true;
}
//���������� ������ ����
/*bool TINYRgn::SetToWindow(TINYBaseWnd *wnd)
{
	if(!wnd) return false;
	if(!SetWindowRgn(wnd->GetHWND(),GetHRGN(),TRUE)) return false;
	return true;
}*/
TINYRgn::operator HRGN() {return GetHRGN();}



//--
//DC
//--

//������� DC
//�������� HDC
HDC TINYDC::GetHDC()
{
	return _dc;
}
//������� � HDC
bool TINYDC::Attach(HDC hdc)
{
	if(!hdc) return false;
	_dc=hdc;
	return true;
}
//������� ����������� DC
bool TINYDC::CreateCompatibleDC(TINYDC *dc)
{
	HDC cmpdc=0;
	if(dc) cmpdc=dc->GetHDC();
	return Attach(::CreateCompatibleDC(cmpdc));
}
//������� DC
bool TINYDC::Delete()
{
	if(!DeleteDC(_dc)) return false;
	return true;
}
//���������� DC
bool TINYDC::Release(HWND wnd)
{
	if(!wnd) return false;
	if(!ReleaseDC(wnd,_dc)) return false;
	return true;
}
//�������� DC ����
bool TINYDC::GetDC(HWND hwnd)
{
	return Attach(::GetDC(hwnd));
}
//�������� ������� DC
RECT TINYDC::GetClipBox()
{
	RECT rect;
	::GetClipBox(_dc,&rect);
	return rect;
}
//����������� ����������
bool TINYDC::BitBlt(int x,int y,int w,int h,
		TINYDC *src,int nx,int ny,DWORD mode)
{
	if(!src) return false;
	if(!::BitBlt(_dc,x,y,w,h,src->GetHDC(),nx,ny,mode)) return false;
	return true;
}
//������ ���������
bool TINYDC::BeginPaint(HWND parent/*������������ ����*/)
{
	if(!parent) return false;
	_parent=parent;//���������� ��������� �� ������������ ����(��� EndPaint)
	return Attach(::BeginPaint(parent,&_ps));
}
//��������� ���������
bool TINYDC::EndPaint()
{
	if(!_parent) return false;
	if(!::EndPaint(_parent,&_ps)) return false;
	return true;
}

//������� ��������� ������
//������� �����
bool TINYDC::TextOut(LPCWSTR text,int x,int y)
{
	if(!::TextOut(_dc,x,y,text,lstrlen(text))) return false;
	return true;
}
//���������� �����
bool TINYDC::DrawText(LPCWSTR text,RECT rect,UINT format)
{
	if(!::DrawText(_dc,text,-1,&rect,format)) return false;
	return true;
}
//���������� ���� ������
bool TINYDC::SetTextColor(COLORREF color)
{
	if(!::SetTextColor(_dc,color)) return false;
	return true;
}

//������� ���������
//��������� �������
bool TINYDC::FillRect(RECT rect,TINYBrush* brush)
{
	if(!brush) return false;
	if(!::FillRect(_dc,&rect,brush->GetHBRUSH())) return false;
	return true;
}
//����������� �������
bool TINYDC::FillGradient(RECT rect,
		COLORREF clrbegin,//���� ������ ���������
		COLORREF clrend,//���� ����� ���������
		bool vert//����������� ��� ������������� 
		)
{
	TRIVERTEX tvx[2];
	//��������� ����
	tvx[0].x=rect.left;
	tvx[0].y=rect.top;
	tvx[0].Red=COLOR16(GetRValue(clrbegin)<<8);
	tvx[0].Green=COLOR16(GetGValue(clrbegin)<<8);
	tvx[0].Blue=COLOR16(GetBValue(clrbegin)<<8);
	tvx[0].Alpha=0;
	//�������� ����
	tvx[1].x=rect.right;
	tvx[1].y=rect.bottom;
	tvx[1].Red=COLOR16(GetRValue(clrend)<<8);
	tvx[1].Green=COLOR16(GetGValue(clrend)<<8);
	tvx[1].Blue=COLOR16(GetBValue(clrend)<<8);
	tvx[1].Alpha=0;

	GRADIENT_RECT grect;
	grect.UpperLeft=0;
	grect.LowerRight=1;
	
	ULONG mode;
	if(vert) mode=GRADIENT_FILL_RECT_V;
	else mode=GRADIENT_FILL_RECT_H;

	if(!GradientFill(_dc,tvx,2,&grect,1,mode)) return false;
	return true;
}

//���������� �������������
bool TINYDC::DrawRectangle(RECT rect)
{
	if(!Rectangle(_dc,rect.left,rect.top,rect.right,rect.bottom)) return false;
	return true;
}
//���������� ������������� � ������������� ������
bool TINYDC::DrawRoundRect(RECT rect,
		int corw,//����������� ���� �� �����������
		int corh//����������� ���� �� ���������
		)
{
	if(!RoundRect(_dc,rect.left,rect.top,rect.right,rect.bottom,
		corw,corh)) return false;
	return true;
}
//���������� ������
bool TINYDC::DrawEllipse(RECT rect)
{
	if(!Ellipse(_dc,rect.left,rect.top,rect.right,rect.bottom)) return false;
	return true;
}
//���������� ����� ������
bool TINYDC::DrawFocusRect(RECT rect)
{
	if(!::DrawFocusRect(_dc,&rect)) return false;
	return true;
}

//������� ��������� �����
//���������� �����
bool TINYDC::LineTo(int x,int y)
{
	::LineTo(_dc,x,y);
	return true;
}
bool TINYDC::MoveTo(int x,int y)
{
	if(!::MoveToEx(_dc,x,y,0)) return false;
	return true;
}

//������� ������ � ����� � �.�.
//���������� ���� �������
bool TINYDC::SetPixel(int x,int y,COLORREF color)
{
	if(::SetPixel(_dc,x,y,color)==-1||ERROR_INVALID_PARAMETER) return false;
	return true;
}
//�������� ���� �������
COLORREF TINYDC::GetPixel(int x,int y)
{
	return ::GetPixel(_dc,x,y);
}
//���������� ���� ����
bool TINYDC::SetBkColor(COLORREF color)
{
	if(::SetBkColor(_dc,color)==CLR_INVALID) return false;
	return true;
}
//�������� ���� ����
COLORREF TINYDC::GetBkColor()
{
	return ::GetBkColor(_dc);
}
//���������� ����� ����(����������/������������)
bool TINYDC::SetBkMode(int mode)
{
	if(!::SetBkMode(_dc,mode)) return false;
	return true;
}
//�������� ����� ����(����������/������������)
int TINYDC::GetBkMode()
{
	return ::GetBkMode(_dc);
}

//������� ������ � ��������� GDI
//������� ������
bool TINYDC::SelectObject(TINYGDIObject* obj)
{
	if(!obj) return false;
	if(!::SelectObject(_dc,obj->GetHGDIOBJ())) return false;
	return true;
}

//--------------------------
//DC c ������� �������������
//--------------------------

//�������� ������ ������
TINYDC* TINYDBDC::GetMemDC()
{
	return &_memdc;
}
//������������� ������� ������������
bool TINYDBDC::InitDoubleBuffer()
{
	//�������� ������������ DC
	if(!_memdc.CreateCompatibleDC(this)) return false;
	//��������� �������� DC
	RECT rect=GetClipBox();
	//�������� ������������ �������
	_membmp.CreateCompatibleBitmap(this,rect.left+rect.right,rect.top+rect.bottom);
	_memdc.SelectObject(&_membmp);
	//����������� ����������� ��������� ������ � ������
	return _memdc.BitBlt(0,0,rect.left+rect.right,rect.top+rect.bottom,
		this,0,0,SRCCOPY);
}
//���������� ������ ������
bool TINYDBDC::DrawDoubleBuffer()
{
	//��������� �������� DC
	RECT rect=GetClipBox();
	//����������� ����������� ������� ������ � ��������
	if(!BitBlt(0,0,rect.left+rect.right,rect.top+rect.bottom,
		&_memdc,0,0,SRCCOPY)) return false;
	//�������� �������
	if(!_membmp.Delete()) return false;
	//�������� ������� ������
	return _memdc.Delete();
}