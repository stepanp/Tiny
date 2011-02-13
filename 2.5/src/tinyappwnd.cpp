//-----------------------------
//tiny 2.5
//tinyappwnd.cpp - ������� ����
//� 2009-2010 Stepan Prokofjev
//-----------------------------

#pragma once

#include "tinyappwnd.h"

using namespace tiny;

TINYAppWnd::TINYAppWnd()
{
	_oncustommsg.Connect(this,&TINYAppWnd::_OnCustomMsg);//��������� ��������� ���������
	//�����
	propcaption.Init(this,WS_CAPTION,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propsysmenu.Init(this,WS_SYSMENU,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propresize.Init(this,WS_THICKFRAME,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propminbox.Init(this,WS_MINIMIZEBOX,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propmaxbox.Init(this,WS_MAXIMIZEBOX,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	proptoolwnd.Init(this,WS_EX_TOOLWINDOW,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	prophelp.Init(this,WS_EX_CONTEXTHELP,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	proptopmost.Init(this,WS_EX_TOPMOST,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
}
//�������� ����
bool TINYAppWnd::Create(TINYBaseWnd* parent)
{
	return TINYBaseWnd::Create(parent,L"TINYAppWnd",0,0,
		LoadCursor(0,IDC_ARROW),//����������� ������
		0,WS_OVERLAPPEDWINDOW,0,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT);//������ �� ���������
}
//��������� ��������� ���������
LRESULT TINYAppWnd::_OnCustomMsg(TINYBaseWnd* wnd,TINYParams params)
{
	//��������� ���������
	TINYMSGPARAMS* msg=(TINYMSGPARAMS*)(params);

	//��������� ������������� � ������������ ������� ����
	if(msg->code==WM_GETMINMAXINFO)
	{
		//�������� ���������
		MINMAXINFO* minmax=(MINMAXINFO*)(msg->lparam);
		//���� �������� >0
		//������������� ������������ ������
		if(propmaxw) minmax->ptMaxTrackSize.x=propmaxw;
		if(propmaxh) minmax->ptMaxTrackSize.y=propmaxh;
		//������������� ����������� ������
		if(propminw) minmax->ptMinTrackSize.x=propminw;
		if(propminh) minmax->ptMinTrackSize.y=propminh;
	}
	return 0;
}