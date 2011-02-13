//----------------------------
//tiny 2.5
//tinylayout.h - �����������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"
#include "tinybasewnd.h"

namespace tiny{

#define TINY_SIZE_AUTO 0//������ �������� ��������������� �������������

class TINYLayout;

//��������� �������� ������������
struct TINYLAYOUTITEM
{
	TINYBaseWnd* wnd;//��������� �� ����
	TINYLayout* layout;//��������� �� �����������
	int size;//������ ��������(������/������)
};

class TINYLayout: public TINYObject
{
public:
	TINYLayout();
protected:
	TINYBaseWnd* _parent;//������������ ����
	TINYLayout* _layout;//������������ �����������
	TINYArr<TINYLAYOUTITEM> _items;//������ ���������
	bool _vert;//�������������� ��� ������������
	TINYPADDING _padding;//����
	int _spacing;//���������� ����� ����������
public:
	//��������
	TINYProperty<TINYPADDING> proppadding;//����
	TINYIntProperty	propspacing;//���������� ����� ����������
public:
	bool Create(TINYBaseWnd* parent,bool vert/*�������������� ��� ������������*/);
	bool Create(TINYLayout* parent,bool vert/*�������������� ��� ������������*/);
	int AddWnd(TINYBaseWnd* wnd,int size=TINY_SIZE_AUTO);//�������� ����
	int AddLayout(TINYLayout* layout,int size=TINY_SIZE_AUTO);//�������� �����������
	int AddSeparator(int size=TINY_SIZE_AUTO);//�������� �����������
	bool SetWnd(int index,TINYBaseWnd* wnd);//���������� ����
	TINYBaseWnd* GetWnd(int index);//�������� ����
	bool SetLayout(int index,TINYLayout* layout);//���������� �����������
	TINYLayout* GetLayout(int index);//�������� �����������
	bool SetSeparator(int index);//���������� �����������
	bool SetItemSize(int index,int size);//����������� ������ ��������
	int GetItemSize(int index);//�������� ������ ��������
	void DeleteItem(int index);//������� �������
	void MoveItem(int index,int nindex);//����������� �������
	void SwapItems(int index,int nindex);//�������� �������� �������
	void Align(int x,int y,int w,int h);//��������������� ����
	bool Update();//�������� �����������
	//������� ��� �������
	bool SetPadding(TINYPADDING padding);//���������� ����
	TINYPADDING GetPadding();//�������� ����
	bool SetSpacing(int spacing);//���������� ���������� ����� ����������
	int GetSpacing();//�������� ���������� ����� ����������
public:
	void OnAlign();//���������� ������������
};

};