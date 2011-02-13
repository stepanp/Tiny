//----------------------------
//tiny 2.5
//tinytrackbar.cpp - �������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinytrackbar.h"

using namespace tiny;

bool TINYTrackBar::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	if(!TINYControlEx::Create(parent,0,TRACKBAR_CLASS,0,exstyle,style,x,y,w,h)) return false;
	//������� ����� TBS_BOTH, ���� �� �� ������ ��� ��������
	if(style!=(style|TBS_BOTH)) DelStyle(TBS_BOTH);
	return true;
}
//���������� �������
bool TINYTrackBar::SetPos(int pos)
{
	if(!SendMessage(_hwnd,TBM_SETPOS,WPARAM(TRUE),LPARAM(pos))) return false;
	return true;
}
//�������� �������
int TINYTrackBar::GetPos()
{
	return SendMessage(_hwnd,TBM_GETPOS,0,0);
}
//���������� ����������� � ������������ �������
void TINYTrackBar::SetRange(int min,int max)
{
	SendMessage(_hwnd,TBM_SETRANGE,WPARAM(TRUE),MAKELPARAM(min,max));
}
//�������� ����������� �������
int TINYTrackBar::GetMinRange()
{
	return SendMessage(_hwnd,TBM_GETRANGEMIN,0,0);
}
//�������� ������������ �������
int TINYTrackBar::GetMaxRange()
{
	return SendMessage(_hwnd,TBM_GETRANGEMAX,0,0);
}
//���������� �����
bool TINYTrackBar::SetTick(int pos)
{
	if(!SendMessage(_hwnd,TBM_SETTIC,0,LPARAM(pos))) return false;
	return true;
}
//�������� ������� �����
int TINYTrackBar::GetTick(int index)
{
	return SendMessage(_hwnd,TBM_GETTIC,WPARAM(index),0);
}
//���������� ������� ����� �� ��������
bool TINYTrackBar::SetTickFrequency(int freq)
{
	if(!SendMessage(_hwnd,TBM_SETTICFREQ,WPARAM(freq),0)) return false;
	return true;
}
//���������� ������� ��������
bool TINYTrackBar::SetBuddies(TINYBaseWnd *left,TINYBaseWnd *right)
{
	if((!left)||(!right)) return false;
	//���������� ����� �������
	SendMessage(_hwnd,TBM_SETBUDDY,WPARAM(TRUE),LPARAM(left->GetHWND()));
	//���������� ������ �������
	SendMessage(_hwnd,TBM_SETBUDDY,WPARAM(FALSE),LPARAM(right->GetHWND()));
	return true;
}
//�������� ����� �������
TINYBaseWnd* TINYTrackBar::GetLeftBuddy()
{
	HWND hwnd=HWND(SendMessage(_hwnd,TBM_GETBUDDY,WPARAM(TRUE),0));
	if(!hwnd) return 0;
	return TinyGetPointer(hwnd);
}
//�������� ������ �������
TINYBaseWnd* TINYTrackBar::GetRightBuddy()
{
	HWND hwnd=HWND(SendMessage(_hwnd,TBM_GETBUDDY,WPARAM(FALSE),0));
	if(!hwnd) return 0;
	return TinyGetPointer(hwnd);
}