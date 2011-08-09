//----------------------------
//tiny 2.5
//tinyapp.cpp - ����������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinyapp.h"

using namespace tiny;

TINYApp *tiny::THIS_APP=0;//���������� ��������� �� ����������

TINYApp::TINYApp() {THIS_APP=this;}//��������� �������� �� ��������� ���������� � THIS_APP

//WinMain
int APIENTRY WinMain(HINSTANCE hinst,HINSTANCE prev,LPSTR cmd,int showcmd)
{
	if(!THIS_APP) return 0;//�������� ��������� �� ����������
	InitCommonControls();//��� ����������� �������� � �� � ������������ ����������
	return THIS_APP->OnInit(cmd,showcmd);//������ �������������
}
//������ ����� ���������
int TINYApp::Run()
{
	MSG msg;
	//���� ���������
	while(GetMessage(&msg,0,0,0)!=0)
	{
		TINYBaseWnd* wnd=TinyGetPointer(msg.hwnd);
		//������������� �����������
		if(!wnd || !TranslateAccelerator(msg.hwnd,wnd->GetAccel(),&msg))
		{
			//������������� ���������
			//� ������� �� � _WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
//�����
void TINYApp::Quit(int code)
{
	PostQuitMessage(code);
}
