//----------------------------
//tiny 2.5
//tinylistbox.cpp - ��������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinylistbox.h"

using namespace tiny;

bool TINYListBox::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
					 int x,int y,int w,int h)
{
	return TINYControl::Create(parent,L"LISTBOX",0,
		exstyle,LBS_HASSTRINGS|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT|style,
		x,y,w,h);
}
//�������� ����
int TINYListBox::InsertItem(int index,LPCWSTR text)
{
	if(!SendMessage(_hwnd,LB_INSERTSTRING,WPARAM(index),LPARAM(text))) return false;
	return true;
}
//�������� ����
int TINYListBox::AddItem(LPCWSTR text)
{
	return InsertItem(-1,text);
}
//������� ����
bool TINYListBox::DeleteItem(int index)
{
	if(!SendMessage(_hwnd,LB_DELETESTRING,WPARAM(index),0)) return false;
	return true;
}
//�������� ���-�� ������
int TINYListBox::GetCount()
{
	return SendMessage(_hwnd,LB_GETCOUNT,0,0);
}
//�������� ����
bool TINYListBox::SetSel(int index)
{
	if(!SendMessage(_hwnd,LB_SETCURSEL,WPARAM(index),0)) return false;
	return true;
}
//�������� ������� ���������� ����
int TINYListBox::GetSel()
{
	return SendMessage(_hwnd,LB_GETCURSEL,0,0);
}
//���������� �������������� ��������
bool TINYListBox::SetItemData(int index,LPARAM data)
{
	if(!SendMessage(_hwnd,LB_SETITEMDATA,WPARAM(index),data)) return false;
	return true;
}
//�������� �������������� ��������
LPARAM TINYListBox::GetItemData(int index)
{
	return SendMessage(_hwnd,LB_GETITEMDATA,WPARAM(index),0);
}
//��������
bool TINYListBox::Clear()
{
	if(!SendMessage(_hwnd,LB_RESETCONTENT,0,0)) return false;
	return true;
}
//���������� ����� �����
bool TINYListBox::SetItemText(int index,LPCWSTR text)
{
	LPARAM data=GetItemData(index);//��������� �������������� �������� �����
	if(!DeleteItem(index)) return false;//������� ����
	if(!InsertItem(index,text)) return false;//�������� ����� ����
	//���������� �������������� �������� �����
	return SetItemData(index,data);
}
//�������� ����� �����
TINYStr TINYListBox::GetItemText(int index)
{
	wchar_t *text=new wchar_t[GetItemTextLen(index)];
	SendMessage(_hwnd,LB_GETTEXT,WPARAM(index),LPARAM(text));
	TINYStr str=text;
	delete[] text;
	return str;
}
//�������� ����� ������ �����
int TINYListBox::GetItemTextLen(int index)
{
	return SendMessage(_hwnd,LB_GETTEXTLEN,WPARAM(index),0);
}
//�������� ������ ����� �� �����������
int TINYListBox::GetItemFromPoint(int x,int y)
{
	return SendMessage(_hwnd,LB_ITEMFROMPOINT,0,MAKELPARAM(x,y));
}

//������� ��������� ���������� ������ (LBS_MULTIPLESEL)
//�������� ���-�� ���������� ������ 
int TINYListBox::GetMultiSelCount()
{
	return SendMessage(_hwnd,LB_GETSELCOUNT,0,0);
}
//�������� ����
bool TINYListBox::SetMultiSel(int index,bool sel/*��������/����� ��������*/)
{
	if(!SendMessage(_hwnd,LB_SETSEL,WPARAM(sel),LPARAM(index))) return false;
	return true;
}
//��������� ������� �� ����
bool TINYListBox::CheckMultiSel(int index)
{
	if(!SendMessage(_hwnd,LB_GETSEL,WPARAM(index),0)) return false;	
	return true;
}
//�������� ������ �������� ���������� ������
TINYArr<int> TINYListBox::GetMultiSel()
{
	int count=GetMultiSelCount();//���-�� ���������� ������
	//�������� ������� �������� �� ���-�� ������
	TINYArr<int> items(count);
	//��������� ������ ��������� ���������� ������
	SendMessage(_hwnd,LB_GETSELITEMS,
		WPARAM(count),LPARAM(items.GetPointer()));
	return items;
}
//����� ���������
bool TINYListBox::ClearMultiSel()
{
	return SetMultiSel(-1,false);
}