//----------------------------
//tiny 2.5
//tinysyslink.cpp - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinysyslink.h"

using namespace tiny;

TINYSysLink::TINYSysLink()
{
	//AddReflectMessage(WM_CTLCOLORSTATIC,&TINYSysLink::OnColor);//WM_CTLCOLORSTATIC
	//AddMessage(WM_LBUTTONUP,&TINYSysLink::OnMouseUp);//WM_LBUTTONUP
	//��������� ��-���������
	_visited=false;//������ �� ��������
	_enablevis=true;//�������� ��������� ������
}

bool TINYSysLink::Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	//��������� ������ �������
	WNDCLASS wndc;
	GetClassInfo(GetModuleHandle(0),L"Static",&wndc);
	//���������� ������ � ���� ����
	wndc.hCursor=LoadCursor(0,IDC_HAND);
	wndc.lpszClassName=L"TINYSysLink";
	//���������������� ����� �����
	RegisterClass(&wndc);
	//������� ������� �� ������ ������ ������
	if(!TINYControl::Create(parent,L"TINYSysLink",text,exstyle,style|WS_TABSTOP
		|SS_NOTIFY//������������ �������� ����
		,x,y,w,h)) return false;
	//���������� ������������ �����
	LOGFONT font;
	//�������� LOGFONT ������������ ������
	if(!GetObject(HFONT(GetStockObject(DEFAULT_GUI_FONT)),
		sizeof(font),LPVOID(&font))) return false;
	font.lfUnderline=TRUE;//������������
	//���������� ����� ��������
	if(!SendMessage(_hwnd,WM_SETFONT,
		WPARAM(CreateFontIndirect(&font)),LPARAM(TRUE))) return false;
	return true;
}
//�������� ����� ����� ��� ���������
bool TINYSysLink::EnableVisiting(bool enable)
{
	bool ret=_enablevis;//��������� ���������� ���������
	_enablevis=enable;
	return ret;//������� ���������� ���������
}
//������ �������� �� ����� ����� ��� ���������
bool TINYSysLink::GetEnableVisiting() {return _enablevis;}
//���������� �������� �� ������
bool TINYSysLink::SetVisited(bool visited)
{
	bool ret=_visited;//��������� ���������� ���������
	_visited=visited;
	//������������ ����
	RedrawWindow(_hwnd,0,0,RDW_INVALIDATE);
	return ret;//������� ���������� ���������
}
//������ �������� �� ������
bool TINYSysLink::GetVisited() {return _visited;}

//����������� ���������
//WM_CTLCOLORSTATIC
LRESULT TINYSysLink::OnColor(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	if(wnd==this)//������������� ������ ��� �������� ��������
	{
		//�������� ���� ������ � ���� ��� ������
		TINYDC dc;
		dc.Attach(HDC(wparam));
		//���� ������
		if(_visited) dc.SetTextColor(RGB(128,0,128));//���� ���������� ������(purple)
		else dc.SetTextColor(GetSysColor(COLOR_HOTLIGHT));//������� ���� �����
		dc.SetBkColor(GetSysColor(COLOR_BTNFACE));//���� ���� ������
		TINYBrush brush;
		brush.CreateSysColorBrush(COLOR_BTNFACE);//���� ����
		return LRESULT(brush.GetHBRUSH());
	}else return 0;
}
//WM_LBUTTONUP
LRESULT TINYSysLink::OnMouseUp(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//���� ��������� ������ ��������
	//�� �������� ���� ������
	if(_enablevis) _visited=true;
	//������������ ����
	RedrawWindow(_hwnd,0,0,RDW_INVALIDATE);
	return 0;
}