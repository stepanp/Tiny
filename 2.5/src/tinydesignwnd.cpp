//------------------------------------
//tiny 2.5
//tinydesignwnd.h - ���� ��� ���������
//� 2009-2010 Stepan Prokofjev
//------------------------------------

#include "tinydesignwnd.h"

using namespace tiny;

//���������� ��������� ����
void TINYDesignWnd::SetDesignParams(LPCWSTR text,UINT icon,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	SetText(text);//���������� �����
	if(icon)
	{
		SetIcon(TINYIcon(icon));//���������� ������� ������
		SetSmallIcon(TINYIcon(icon,16,16));//���������� ��������� ������
	}
	AddStyle(style);//���������� �����
	AddExStyle(exstyle);//���������� ����������� �����
	int _x,_y,_w,_h;
	//���� ��������� �� ���������(CW_USEDEFAULT) �� �������� ������, 
	//����� ���������� �����
	if(x==CW_USEDEFAULT) _x=GetX(); else _x=x;
	if(y==CW_USEDEFAULT) _y=GetY(); else _y=y;
	if(w==CW_USEDEFAULT) _w=GetW(); else _w=w;
	if(h==CW_USEDEFAULT) _h=GetH(); else _h=h;
	//���������� ������ � ���������
	MoveWindow(this->GetHWND(),_x,_y,_w,_h,TRUE);
	Update();//�������� ����
}