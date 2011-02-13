//----------------------------------------
//tiny 2.5
//tinycontrol.h - ������� ������ ���������
//� 2009-2010 Stepan Prokofjev
//----------------------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

//--------------
//����� ��������
//--------------
class TINYControl: public TINYBaseWnd
{
public:
	TINYControl();
protected:
	WNDPROC _PrevProc;//������� ������� ��� ������������
public:
	bool Attach(HWND hwnd);
	bool Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
	void _SubClass();//����������� ����
protected:
	//������� �������
	static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
};


//--------------------------------------
//����� ������������ �������� (commctrl)
//--------------------------------------
class TINYControlEx: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,DWORD icc,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
};

//��������� ������������ ������ ��� ��������
bool TinySetDefaultFont(HWND hwnd);

};