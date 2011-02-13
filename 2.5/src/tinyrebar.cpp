//----------------------------
//tiny 2.5
//tinyrebar.cpp - �����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinyrebar.h"

using namespace tiny;


bool TINYReBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_COOL_CLASSES,REBARCLASSNAME,0,0,
		CCS_NOPARENTALIGN|//�� �����������
		CCS_NODIVIDER|//��� ������� ������
		WS_CLIPCHILDREN|//����� �� �������
		RBS_BANDBORDERS,//���������� ����� �������
		0,0,0,0);
}
//�c������ ����
bool TINYReBar::InsertBand(int index,TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h)
{
	//�������� �����
	REBARBANDINFO band;
	band.cbSize=80;//��� ������ ������ ��� ��
	band.fMask=
		RBBIM_STYLE|
		RBBIM_TEXT|
		RBBIM_CHILD|
		RBBIM_CHILDSIZE|
		RBBIM_SIZE;
	band.fStyle=
		RBBS_CHILDEDGE|//����� ������ ��������
		style;
	band.lpText=LPWSTR(text);
	band.cyMinChild=h;//����������� ������
	band.cxMinChild=w;//����������� ������
	band.cx=w;//������
	HWND hchild=child->GetHWND();
	if(!hchild) return false;
	band.hwndChild=hchild;//������� � �����
	//���������� ����� � �����
	if(!SendMessage(_hwnd,RB_INSERTBAND,WPARAM(index),LPARAM(&band))) return false;
	return true;
}
//�������� ����
bool TINYReBar::AddBand(TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h)
{
	return InsertBand(-1,child,style,text,w,h);
}
//������� ����
bool TINYReBar::DeleteBand(int index)
{
	if(!SendMessage(_hwnd,RB_DELETEBAND,WPARAM(index),0)) return false;
	return true;
}
//����������� ����
bool TINYReBar::MoveBand(int index,int nindex)
{
	if(!SendMessage(_hwnd,RB_MOVEBAND,WPARAM(index),LPARAM(nindex))) return false;
	return true;
}
//������/�������� ����
bool TINYReBar::ShowBand(int index,bool show)
{
	if(!SendMessage(_hwnd,RB_SHOWBAND,WPARAM(index),LPARAM(show))) return false;
	return true;
}
//�������� ���-�� ������
int TINYReBar::GetBandCount()
{
	return SendMessage(_hwnd,RB_GETBANDCOUNT,0,0);
}