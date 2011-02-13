//---------------------------------
//tiny 2.5
//tinymisc.h - ������ ������ ������
//� 2009-2010 Stepan Prokofjev
//---------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny
{

//------
//������
//------
class TINYIcon: public TINYObject
{
public:
	TINYIcon();
	TINYIcon(UINT icon);
	TINYIcon(UINT icon,int w,int h);
protected:
	HICON _hicon;
public:
	HICON GetHICON();//�������� HICON
	void Attach(HICON icon);//������� HICON
	bool LoadIcon(UINT icon);//��������� ������
	bool LoadIconEx(UINT icon,int w,int h);//��������� ������ �� �������
	bool Destroy();//���������� ������
	operator HICON();
};

//----
//����
//----
class TINYRect: public TINYObject
{
public:
	TINYRect();
	TINYRect(TINYRect& rect);
	TINYRect(RECT& rect);
	TINYRect(int x,int y,int w,int h);
public:
	int x,y,w,h;
public:
	//��������� �����������
	TINYRect& operator=(TINYRect& rect);
	TINYRect& operator=(RECT& rect);
	operator RECT();
};

};

