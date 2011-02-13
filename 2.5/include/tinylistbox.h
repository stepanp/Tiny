//----------------------------
//tiny 2.5
//tinylistbox.h - ��������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYListBox: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	int InsertItem(int index,LPCWSTR text);//�������� ����
	int AddItem(LPCWSTR text);//�������� ����
	bool DeleteItem(int index);//������� ����
	int GetCount();//�������� ���-�� ������
	bool SetSel(int index);//�������� ����
	int GetSel();//�������� ������� ���������� ����
	bool SetItemData(int index,LPARAM data);//���������� �������������� ��������
	LPARAM GetItemData(int index);//�������� �������������� ��������
	bool Clear();//��������
	bool SetItemText(int index,LPCWSTR text);//���������� ����� �����
	TINYStr GetItemText(int index);//�������� ����� �����
	int GetItemTextLen(int index);//�������� ����� ������ �����
	int GetItemFromPoint(int x,int y);//�������� ������ ����� �� �����������

	//������� ��������� ���������� ������ (LBS_MULTIPLESEL)
	int GetMultiSelCount();//�������� ���-�� ���������� ������ 
	bool SetMultiSel(int index,bool sel/*��������/����� ��������*/);//�������� ����
	bool CheckMultiSel(int index);//��������� ������� �� ����
	TINYArr<int> GetMultiSel();//�������� ������ �������� ���������� ������
	bool ClearMultiSel();//����� ���������
};

};