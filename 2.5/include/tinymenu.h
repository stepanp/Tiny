//----------------------------
//tiny 2.5
//tinymenu.h - ����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

//----
//����
//----
class TINYMenu: public TINYObject
{
protected:
	HMENU _menu;
public:
	bool Create();
	bool Create(UINT menu);//������� �� ��������
	bool Attach(HMENU menu);//������� �� HMENU
	HMENU GetHMENU();//�������� HMENU
	bool SetToWindow(TINYBaseWnd *wnd);//���������� ���� ����
	bool InsertItem(int index,LPCWSTR text,UINT id,TINYMenu* submenu);//�������� ����� ����
	bool AddItem(LPCWSTR text,UINT id,TINYMenu* submenu);//�������� ����� ����
	bool DeleteItem(int index);//������� ����� ����
	TINYMenu* GetSubMenu(int index);//�������� �������
	bool SetSubMenu(int index,TINYMenu* submenu);//���������� �������	
	DWORD GetItemState(int index);//�������� ���������
	bool SetItemState(int index,DWORD state);//���������� ���������
	bool SetItemData(int index,LPARAM data);//���������� �������������� ��������
	LPARAM GetItemData(int index);//�������� �������������� ��������
};

//----------------
//����������� ����
//----------------
class TINYPopupMenu: public TINYMenu
{
public:
	bool Create();
	bool Create(UINT menu);//������� �� ��������
	bool InsertSeparator(int index);//�������� ���������
	bool AddSeparator();//�������� ���������
	bool EnableItem(int index,bool enable);//������������ ����
	bool GetEnableItem(int index);//��������� ����������� �� ����� ����
	bool CheckItem(int index,bool check);//��������� �������
	bool GetCheckItem(int item);//��������� �������
	bool Track(TINYBaseWnd *parent,int x=-1,int y=-1);//�������� ����
};

};