//----------------------------
//tiny 2.5
//tinylistview.h - �������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"
#include "tinyheaderctrl.h"

namespace tiny{

class TINYListView: public TINYControlEx
{
protected:
	TINYHeaderCtrl _header;//������� (��� ������ LVS_REPORT)
protected:
	bool _AttachHeader();//���������� ������� � ������ LVS_REPORT
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool Attach(HWND hwnd);
	TINYHeaderCtrl* GetHeader();//�������� �����(�������)
	bool SetExtendedStyle(DWORD style);//���������� ����������� �����
	int InsertColumn(int index,LPCWSTR text,int w,int fmt/*������*/);//�������� �������
	int AddColumn(LPCWSTR text,int w,int fmt/*������*/);//�������� �������
	bool DeleteColumn(int index);//������� �������
	bool SetColumnW(int index,int w);//���������� ������ �������
	int InsertItem(int index,LPCWSTR text,int image);//�������� ����
	int AddItem(LPCWSTR text,int image);//�������� ����
	bool DeleteItem(int index);//������� ����
	//���������� �������
	//��������� ���� ����� ��� � SetItemText :)
	bool SetSubItem(int index,int subitem,LPCWSTR text);
	bool SetItemText(int index,int subitem,LPCWSTR text);//���������� ����� �����
	bool SetItemImage(int index,int subitem,int image);//���������� ������ ��������
	bool SetItemData(int index,int subitem,LPARAM data);//���������� �������� �����
	bool SetItemState(int index,UINT state);//���������� ��������� �����
	TINYStr GetItemText(int index,int subitem);//�������� ����� �����
	int GetItemImage(int index,int subitem);//�������� ������ ��������
	LPARAM GetItemData(int index,int subitem);//�������� �������� �����
	UINT GetItemState(int index);//�������� ��������� �����
	int GetItemCount();//�������� ���-�� ������
	bool SetImageList(TINYImageList *list);//���������� ���������
	//���������� ��������� ��� ��������� ������
	bool SetSmallImageList(TINYImageList *list);
	
};

};