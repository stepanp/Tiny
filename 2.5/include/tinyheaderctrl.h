//-----------------------------
//tiny 2.5
//tinybuttons.h - ����� �������
//� 2009-2010 Stepan Prokofjev
//-----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"

namespace tiny{

class TINYHeaderCtrl: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	int InsertItem(int index,LPCWSTR text,int w,int fmt);//�������� ����
	int AddItem(LPCWSTR text,int w,int fmt);//�������� ����
	bool SetItemText(int index,LPCWSTR text);//���������� �����
	bool SetItemImage(int index,int image);//���������� ������ ��������
	bool SetItemData(int index,LPARAM data);//���������� �������� �����
	bool SetItemFormat(int index,int fmt);//���������� ������ �����
	TINYStr GetItemText(int index);//�������� ����� �����
	int GetItemImage(int index);//�������� ������ ��������
	LPARAM GetItemData(int index);//�������� �������� �����
	int GetItemFormat(int index);//�������� ������ �����
	int GetItemCount();//�������� ���-�� ������
	bool SetImageList(TINYImageList *list);//���������� ���������
	
};


};