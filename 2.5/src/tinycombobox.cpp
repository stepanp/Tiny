//----------------------------
//tiny 2.5
//tinycombobox.cpp - ���������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinycombobox.h"

using namespace tiny;

TINYComboBox::TINYComboBox()
{
	_oncustomcmd.Connect(this,&TINYComboBox::_OnCustomCmd);//��������� ��������� ������
}

bool TINYComboBox::Create(TINYBaseWnd *parent)
{
	return TINYControl::Create(parent,L"COMBOBOX",0,0,CBS_HASSTRINGS,0,0,100,21);
}
//�������� ����
bool TINYComboBox::InsertItem(int index,LPCWSTR text)
{
	if(!SendMessage(_hwnd,CB_INSERTSTRING,WPARAM(index),LPARAM(text))) return false;
	return true;
}
//�������� ����
bool TINYComboBox::AddItem(LPCWSTR text)
{
	return InsertItem(-1,text);
}
//������� ����
bool TINYComboBox::DeleteItem(int index)
{
	if(!SendMessage(_hwnd,CB_DELETESTRING,WPARAM(index),0)) return false;
	return true;
}
//�������� ���-�� ������
int TINYComboBox::GetCount()
{
	return SendMessage(_hwnd,CB_GETCOUNT,0,0);
}
//�������� ����
bool TINYComboBox::SetSel(int index)
{
	if(!SendMessage(_hwnd,CB_SETCURSEL,WPARAM(index),0)) return false;
	return true;
}
//�������� ������� ���������� ����
int TINYComboBox::GetSel()
{
	return SendMessage(_hwnd,CB_GETCURSEL,0,0);
}
//���������� �������������� ��������
bool TINYComboBox::SetItemData(int index,LPARAM data)
{
	if(!SendMessage(_hwnd,CB_SETITEMDATA,WPARAM(index),data)) return false;
	return true;
}
//�������� �������������� ��������
LPARAM TINYComboBox::GetItemData(int index)
{
	return SendMessage(_hwnd,CB_GETITEMDATA,WPARAM(index),0);
}
//��������
bool TINYComboBox::Clear()
{
	if(!SendMessage(_hwnd,CB_RESETCONTENT,0,0)) return false;
	return true;
}
//�������� ����� �����
TINYStr TINYComboBox::GetItemText(int index)
{
	wchar_t *text=new wchar_t[GetItemTextLength(index)];
	SendMessage(_hwnd,CB_GETLBTEXT,WPARAM(index),LPARAM(text));
	TINYStr str=text;
	delete[] text;
	return str;
}
//�������� ����� ������ �����
int TINYComboBox::GetItemTextLength(int index)
{
	return SendMessage(_hwnd,CB_GETLBTEXTLEN,WPARAM(index),0);
}
//��������� ��������� ������
LRESULT TINYComboBox::_OnCustomCmd(TINYBaseWnd* wnd,TINYParams params)
{
	//��������� �������
	TINYMSGPARAMS* cmd=(TINYMSGPARAMS*)(params);

	//����� ������������ �������
	switch(cmd->code)
	{
	case CBN_CLOSEUP:
		oncloseup(wnd,0);
		break;
	case CBN_DROPDOWN:
		ondropdown(wnd,0);
		break;
	case CBN_EDITCHANGE:
		oneditchange(wnd,0);
		break;
	case CBN_SELCHANGE:
		onselchange(wnd,0);
		break;
	case CBN_SELENDOK:
		onselect(wnd,0);
		break;
	}
	return 0;
}