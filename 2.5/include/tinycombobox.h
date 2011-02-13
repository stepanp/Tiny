//----------------------------
//tiny 2.5
//tinycombobox.h - ���������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYComboBox: public TINYControl
{
public:
	TINYComboBox();
	//�������
	TINYEvent oncloseup,//��� �������� ������
		ondropdown,//��� ��������� ������
		oneditchange,//��� ��������� �����
		onselchange,//��� ��������� ���������
		onselect;//��� ������ ������
public:
	bool Create(TINYBaseWnd *parent);
	bool InsertItem(int index,LPCWSTR text);//�������� ����
	bool AddItem(LPCWSTR text);//�������� ����
	bool DeleteItem(int index);//������� ����
	int GetCount();//�������� ���-�� ������
	bool SetSel(int index);//�������� ����
	int GetSel();//�������� ������� ���������� ����
	bool SetItemData(int index,LPARAM data);//���������� �������������� ��������
	LPARAM GetItemData(int index);//�������� �������������� ��������
	bool Clear();//��������
	TINYStr GetItemText(int index);//�������� ����� �����
	int GetItemTextLength(int index);//�������� ����� ������ �����
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//��������� ��������� ������

};

};