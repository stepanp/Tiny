//------------------------------------------
//tiny 2.5
//tinycontrol.cpp - ������� ������ ���������
//� 2009-2010 Stepan Prokofjev
//------------------------------------------

#include "tinycontrol.h"

using namespace tiny;

//--------------
//����� ��������
//--------------

TINYControl::TINYControl() 
{
	_isctrl=true;//��� �������
}

bool TINYControl::Attach(HWND hwnd)
{
	if(TINYBaseWnd::Attach(hwnd)) return false;
	_SubClass();
	return true;
}

bool TINYControl::Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	//��������� HWND ������������� ����
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();

	//�������� ��������
	_hwnd=CreateWindowEx(exstyle,classname,text,
		WS_CHILD|WS_VISIBLE|style,
		x,y,w,h,hparent,0,GetModuleHandle(0),0);	
	if(!_hwnd) return false;

	TinySetDefaultFont(_hwnd);//��������� ������������ ������
	_SubClass();//�����������

	//������ ����������� oncreate
	oncreate(this,0);
	return true;
}
//�����������
void TINYControl::_SubClass()
{
	//���������� ��������� �� ��������� ������ � GWL_USERDATA
	SetWindowLong(_hwnd,GWL_USERDATA,LONG(this)/*��������� �� ��������� ������*/);
	//����������� ����
	_PrevProc=WNDPROC(SetWindowLong(_hwnd,GWL_WNDPROC,LONG(_WndProc)));	
}

LRESULT CALLBACK TINYControl::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//��������� ��������� �� ��������� ������
	TINYControl *ctrl=0;	
	ctrl=(TINYControl*)TinyGetPointer(hwnd);
	if(ctrl)//�������� ���������
	{
		//������ ������� ��������� ���������		
		LRESULT result=ctrl->_OnMessage(ctrl,message,wparam,lparam);
		//���� result �� ����� 0, �� ������� result
		if(result) return result;
	}
	return CallWindowProc(ctrl->_PrevProc,hwnd,message,wparam,lparam);
}


//--------------------------------------
//����� ������������ �������� (commctrl)
//--------------------------------------

bool TINYControlEx::Create(TINYBaseWnd *parent,DWORD icc,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	//������������� commctrl
	INITCOMMONCONTROLSEX init;
	init.dwSize=sizeof(INITCOMMONCONTROLSEX);
	init.dwICC=icc;
	InitCommonControlsEx(&init);
	return TINYControl::Create(parent,classname,text,exstyle,style,x,y,w,h);
}

//��������� ������������ ������ ��� ��������
bool tiny::TinySetDefaultFont(HWND hwnd)
{
	if(!SendMessage(hwnd,WM_SETFONT,
		WPARAM(HFONT(GetStockObject(DEFAULT_GUI_FONT))),LPARAM(TRUE))) return false;
	return true;
}