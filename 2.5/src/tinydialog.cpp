//----------------------------
//tiny 2.5
//tinydialog.cpp - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinydialog.h"

using namespace tiny;

bool TINYDialog::Create(TINYBaseWnd *parent,UINT dialog)
{
	//�������� ��������� �� ����� ������������� ����
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	//�������� �������
	if(!DialogBoxParam(GetModuleHandle(0),MAKEINTRESOURCE(dialog),hparent,_WndProc,
		LPARAM(this)/*��������� �� ��������� ������*/)) return false;
	return true;
}
//�������� HWND ��������
HWND TINYDialog::GetItemHWND(UINT id)
{
	return GetDlgItem(_hwnd,id);
}
//������� ������
void TINYDialog::End()
{
	EndDialog(_hwnd,TRUE);
}
//�������� ����� ��������
TINYStr TINYDialog::GetItemText(UINT id)
{
	wchar_t *text=new wchar_t[GetItemTextLen(id)+1];
	GetDlgItemText(_hwnd,id,text,GetItemTextLen(id)+1);
	TINYStr str=text;
	delete[] text;
	return str;
}
//���������� ����� ��������
bool TINYDialog::SetItemText(LPCWSTR text,UINT id)
{
	if(!SetDlgItemText(_hwnd,id,text)) return false;
	return true;
}
//�������� ����� ������ ��������
int TINYDialog::GetItemTextLen(UINT id)
{
	return GetWindowTextLength(GetDlgItem(_hwnd,id));
}
//��������� ����� �� �������
int TINYDialog::GetItemCheck(UINT id)
{
	return IsDlgButtonChecked(_hwnd,id);
}
//���������� �������
bool TINYDialog::SetItemCheck(UINT id,int check)
{
	if(!CheckDlgButton(_hwnd,id,check)) return false;
	return true;
}
//�������� �������� ��������
int TINYDialog::GetItemInt(UINT id)
{
	return GetDlgItemInt(_hwnd,id,0,0);
}
//���������� �������� ��������
bool TINYDialog::SetItemInt(int value,UINT id)
{
	if(!SetDlgItemInt(_hwnd,id,value,0)) return false;
	return true;
}

//������� �������
INT_PTR CALLBACK TINYDialog::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	TINYDialog *dlg=0;
	if(message==WM_INITDIALOG)
	{
		//��������� ��������� �� ��������� ������
		dlg=(TINYDialog*)(lparam);
		dlg->_hwnd=hwnd;//���������� HWND
		//���������� ��������� �� ��������� ������ � GWL_USERDATA ����
		SetWindowLong(hwnd,GWL_USERDATA,LONG(dlg));
		//������ ������� ��������� ���������
		dlg->_OnMessage(dlg,message,wparam,lparam);
		return TRUE;
	}
	//��������� ��������� �� ��������� ������ �� GWL_USERDATA
	dlg=(TINYDialog*)TinyGetPointer(hwnd);
	if(dlg)//�������� ���������
	{
		//������ ������� ��������� ���������
		dlg->_OnMessage(dlg,message,wparam,lparam);
	}
	return FALSE;
}