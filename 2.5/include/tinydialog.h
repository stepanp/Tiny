//----------------------------
//tiny 2.5
//tinydialog.h - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYDialog: public TINYBaseWnd
{
public:
	bool Create(TINYBaseWnd *parent,UINT dialog);
	HWND GetItemHWND(UINT id);//�������� HWND ��������
	void End();//������� ������
	TINYStr GetItemText(UINT id);//�������� ����� ��������
	bool SetItemText(LPCWSTR text,UINT id);//���������� ����� ��������
	int GetItemTextLen(UINT id);//�������� ����� ������ ��������
	int GetItemCheck(UINT id);//��������� ����� �� �������
	bool SetItemCheck(UINT id,int check);//���������� �������
	int GetItemInt(UINT id);//�������� �������� ��������
	bool SetItemInt(int value,UINT id);//���������� �������� ��������
protected:
	//������� �������
	static INT_PTR CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
};

};