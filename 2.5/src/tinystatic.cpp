//----------------------------
//tiny 2.5
//tinystatic.cpp - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinystatic.h"

using namespace tiny;

bool TINYStatic::Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	return TINYControl::Create(parent,L"Static",text,exstyle,style,x,y,w,h);
}
//���������� ������
bool TINYStatic::SetIcon(HICON icon)
{
	if(!SendMessage(_hwnd,STM_SETICON,WPARAM(icon),0)) return false;
	return true;
}
//�������� ������
HICON TINYStatic::GetIcon()
{
	return HICON(SendMessage(_hwnd,STM_GETICON,0,0));
}
//���������� ������
bool TINYStatic::SetBitmap(HBITMAP bmp)
{
	if(!SendMessage(_hwnd,STM_SETIMAGE,WPARAM(IMAGE_BITMAP),LPARAM(bmp))) return false;
	return true;
}
//�������� ������
HBITMAP TINYStatic::GetBitmap()
{
	return HBITMAP(SendMessage(_hwnd,STM_GETIMAGE,WPARAM(IMAGE_BITMAP),0));
}
//���������� ������
bool TINYStatic::SetCursor(HCURSOR cursor)
{
	if(!SendMessage(_hwnd,STM_SETIMAGE,WPARAM(IMAGE_CURSOR),LPARAM(cursor))) return false;
	return true;
}
//�������� ������
HCURSOR TINYStatic::GetCursor()
{
	return HCURSOR(SendMessage(_hwnd,STM_GETIMAGE,WPARAM(IMAGE_CURSOR),0));
}

