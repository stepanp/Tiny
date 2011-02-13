//----------------------------
//tiny 2.5
//tinytoolbar.h - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"

namespace tiny{

class TINYToolBar: public TINYControlEx
{
public:
	TINYToolBar();
public:
	bool Create(TINYBaseWnd *parent);
	//���������� ����������� �����
	bool SetExtendedStyle(DWORD style);
	//�������� ������
	bool InsertButton(int index,DWORD style,DWORD state,int nimage,
							LPCWSTR text,LPCWSTR tip,UINT id);
	//�������� ������
	bool AddButton(DWORD style,DWORD state,int nimage,LPCWSTR text,LPCWSTR tip,UINT id);
	bool InsertSeparator(int index);//������� ���������
	bool AddSeparator();//�������� ���������
	bool DeleteButton(int index);//������� ������
	bool MoveButton(int index,int nindex/*����� ������ ������*/);//����������� ������
	bool SetButtonState(int id,DWORD state);//���������� ��������� ������
	DWORD GetButtonState(int id);//�������� ��������� ������
	bool EnableButton(int id,bool enable);//��������/��������� ������
	bool ShowButton(int id,bool show);//��������/������ ������
	bool SetImageList(TINYImageList *list);//���������� ���������
	//���������� ��������� ��� ������������ ������
	bool SetHotImageList(TINYImageList *list);
	//���������� ��������� ��� ����������� ������
	bool SetDisbaleImageList(TINYImageList *list);
	void AutoSize();//���������� ������ �������������
	int GetButtonCount();//�������� ���-�� ������
	TBBUTTON GetButton(int index);//�������� ������

protected:
	//���������� ��� ����������� ���������
	LRESULT _OnToolTip(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);
};

};