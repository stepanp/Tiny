//---------------------------------
//tiny 2.5
//tinyprogressbar.cpp - �����������
//� 2009-2010 Stepan Prokofjev
//---------------------------------

#include "tinyprogressbar.h"

using namespace tiny;

bool TINYProgressBar::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	if(!TINYControlEx::Create(parent,0,PROGRESS_CLASS,0,exstyle,style,x,y,w,h)) return false;
	//������� ����� PBS_MARQUEE, ���� �� �� ������ ��� ��������
	if(style!=(style|PBS_MARQUEE)) DelStyle(PBS_MARQUEE);
	return true;
}
//���������� �������
bool TINYProgressBar::SetPos(int pos)
{
	if(!SendMessage(_hwnd,PBM_SETPOS,WPARAM(pos),0)) return false;
	return true;
}
//�������� �������
int TINYProgressBar::GetPos()
{
	return SendMessage(_hwnd,PBM_GETPOS,0,0);
}
//���������� ��� ������������
int TINYProgressBar::SetStep(int step)
{
	return SendMessage(_hwnd,PBM_SETSTEP,WPARAM(step),0);
}
//�������� ��� ������������
int TINYProgressBar::GetStep()
{
	//������������� ����� ���, �������� ������
	int step=SendMessage(_hwnd,PBM_SETSTEP,WPARAM(0),0);
	//���������� ������� ������
	SendMessage(_hwnd,PBM_SETSTEP,WPARAM(step),0);
	return step;
}
//���������� ������� �� ���-�� �����
int TINYProgressBar::DeltaPos(int pos)
{
	return SendMessage(_hwnd,PBM_DELTAPOS,WPARAM(pos),0);
}
//������������ �� 1 ���
int TINYProgressBar::StepIt()
{
	return SendMessage(_hwnd,PBM_STEPIT,0,0);
}
//���������� ����������� � ������������ �������
void TINYProgressBar::SetRange(int min,int max)
{
	SendMessage(_hwnd,PBM_SETRANGE32,WPARAM(min),LPARAM(max));
}
//�������� ����������� �������
int TINYProgressBar::GetMinRange()
{
	return SendMessage(_hwnd,PBM_GETRANGE,WPARAM(TRUE),0);
}
//�������� ������������ �������
int TINYProgressBar::GetMaxRange()
{
	return SendMessage(_hwnd,PBM_GETRANGE,WPARAM(FALSE),0);
}
//������� � XP
#if(_WIN32_WINNT>=0x0501)
//���/���� ������� ������� � ���������� � ��������
void TINYProgressBar::SetMarquee(bool enable,int speed)
{
	SendMessage(_hwnd,PBM_SETMARQUEE,WPARAM(enable),LPARAM(speed));
}
#endif