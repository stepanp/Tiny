//-----------------------------
//tiny 2.5
//tinystatusbar.cpp - ���������
//� 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinystatusbar.h"

using namespace tiny;

bool TINYStatusBar::Attach(HWND hwnd)
{
	if(!TINYBaseWnd::Attach(hwnd)) return false;
	//���-�� ������
	int count=GetPartCount();
	int *wparts=new int[count];
	//��������� ������
	if(!SendMessage(_hwnd,SB_GETPARTS,
		WPARAM(count),LPARAM(wparts))) return false;
	_parts.Clear();
	_parts.Resize(count);
	//���������� �������
	int allw=0;
	for(int i=0;i<count;i++)
	{
		//���������������� ������
		allw=allw+wparts[i];
		TINYSTATUS part;
		part.w=allw;
		//��������� ������
		wchar_t *text=new wchar_t[MAX_PATH];
		GetPartText(i,text);
		part.text=text;
		delete[] text;
		//��������� ������
		part.icon=GetPartIcon(i);
		//���������� �����
		part.hide=false;
		//����������� �����
		_parts[i]=part;
	}
	return true;
}
bool TINYStatusBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_BAR_CLASSES,STATUSCLASSNAME,0,0,
		SBARS_SIZEGRIP|//�������� � ���� ����
		0,0,0,0,0);
}
//�������� �����
bool TINYStatusBar::InsertPart(int index,int w,LPCWSTR text,HICON icon)
{
	int count=_parts.GetCount();
	//����������� �������
	if(index<-1) return false;
	int nindex=0;
	if((index==-1)||(index>count)) nindex=count;
	else nindex=index;
	//���������� ��������� TINYSTATUS
	TINYSTATUS part;
	part.w=w;
	part.text=text;
	part.icon=icon;
	part.hide=true;
	//���������� ����� � ������
	_parts.Insert(nindex,part);
	//�������� �����
	return _UpdateParts();
}
//�������� �����
bool TINYStatusBar::AddPart(int w,LPCWSTR text,HICON icon)
{
	return InsertPart(-1,w,text,icon);
}
//�������� �����
bool TINYStatusBar::_UpdateParts()
{
	int count=_parts.GetCount();
	if(!count) return false;
	//�������� ������� �����
	int *wparts=new int[count];
	int allw=0;
	//����������� ������
	for(int i=0;i<count;i++)
	{
		if(_parts[i].hide)//���� ����� ������, �� ����������
		{
			allw=allw+_parts[i].w;
			wparts[i]=allw;
		}
	}
	//��������� ������
	if(!SendMessage(_hwnd,SB_SETPARTS,WPARAM(count),LPARAM(wparts))) return false;
	delete[] wparts;
	//��������� ������ ������ � ���������
	for(int i=0;i<count;i++)
	{
		if(!SetPartText(i,_parts[i].text)) return false;
		if(!SetPartIcon(i,_parts[i].icon)) return false;
	}
	return true;		
}
//������� �����
bool TINYStatusBar::DeletePart(int index)
{
	if(!_CheckIndex(index)) return false;
	_parts.Delete(index);
	return _UpdateParts();
}
//����������� �����
bool TINYStatusBar::MovePart(int index,int nindex)
{
	if(!_CheckIndex(index)) return false;
	//����������� �����
	TINYSTATUS part=_parts[index];
	_parts.Delete(index);//������� �����
	//�������� � ����� �����
	InsertPart(nindex,
		part.w,
		part.text,
		part.icon);
	return _UpdateParts();
}
//������/�������� �����
bool TINYStatusBar::ShowPart(int index,bool show)
{
	if(!_CheckIndex(index)) return false;
	_parts[index].hide=!show;
	return _UpdateParts();
}
//��������� �������� �� �����
bool TINYStatusBar::GetShowPart(int index)
{
	if(!_CheckIndex(index)) return false;
	return !_parts[index].hide;
}
//������� ��� �����
bool TINYStatusBar::Clear()
{
	//������� ������ � ����������
	int *wparts=new int[1];
	wparts[0]=0;
	if(!SendMessage(_hwnd,SB_SETPARTS,WPARAM(1),LPARAM(wparts))) return false;
	delete[] wparts;
	//������� ������� ������
	_parts.Clear();
	return true;
}
//�������� ���-�� ������
int TINYStatusBar::GetPartCount()
{
	return SendMessage(_hwnd,SB_GETPARTS,0,0);
}
//���������� ������ �����
bool TINYStatusBar::SetPartW(int index,int w)
{
	if((!_CheckIndex(index))||(w<0)) return false;
	_parts[index].w=w;
	return _UpdateParts();
}
//�������� ������ �����
int TINYStatusBar::GetPartW(int index)
{
	if(!_CheckIndex(index)) return false;
	return _parts[index].w;
}
//���������� ������ ��� �����
bool TINYStatusBar::SetPartIcon(int index,HICON icon)
{
	if(!SendMessage(_hwnd,SB_SETICON,WPARAM(index),LPARAM(icon))) return false;
	return true;
}
//�������� ������ �����
HICON TINYStatusBar::GetPartIcon(int index)
{
	return HICON(SendMessage(_hwnd,SB_GETICON,WPARAM(index),0));
}
//���������� ����� �����
bool TINYStatusBar::SetPartText(int index,PCWSTR text)
{
	if(!SendMessage(_hwnd,SB_SETTEXT,MAKEWPARAM(index,0),LPARAM(text))) return false;
	return true;
}
//�������� ����� �����
int TINYStatusBar::GetPartText(int index,LPWSTR text)
{
	return SendMessage(_hwnd,SB_GETTEXT,WPARAM(index),LPARAM(text));
}
//�������� ����� ������
int TINYStatusBar::GetPartTextLen(int index)
{
	return SendMessage(_hwnd,SB_GETTEXTLENGTH,WPARAM(index),0);
}
//�������� �������
bool TINYStatusBar::_CheckIndex(int index)
{
	if((index<-1)||(index>_parts.GetCount())) return false;
	return true;
}