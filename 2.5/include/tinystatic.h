//----------------------------
//tiny 2.5
//tinystatic.h - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYStatic: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetIcon(HICON icon);//���������� ������
	HICON GetIcon();//�������� ������
	bool SetBitmap(HBITMAP bmp);//���������� ������
	HBITMAP GetBitmap();//�������� ������
	bool SetCursor(HCURSOR cursor);//���������� ������
	HCURSOR GetCursor();//�������� ������
};

};