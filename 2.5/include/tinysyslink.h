//----------------------------
//tiny 2.5
//tinysyslink.h - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinystatic.h"
#include "tinygdi.h"

namespace tiny{

class TINYSysLink: public TINYControl
{
public:
	TINYSysLink();
protected:
	bool _visited,//�������� �� ������
		_enablevis;//�������� ��������� ������
public:
	bool Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool EnableVisiting(bool enable);//�������� ��������� ������
	bool GetEnableVisiting();//������ �������� �� ��������� ������
	bool SetVisited(bool visited);//���������� �������� �� ������
	bool GetVisited();//������ �������� �� ������
	//����������� ���������
	LRESULT OnColor(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);//WM_CTLCOLORSTATIC
	LRESULT OnMouseUp(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);//WM_LBUTTONUP
};

};