//----------------------------
//tiny 2.5
//tinyappwnd.h - ������� ����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYAppWnd: public TINYBaseWnd
{
public:
	TINYAppWnd();
public:
	//��������
	int propmaxw,//������������ ������
		propmaxh,//������������ ������
		propminw,//����������� ������
		propminh;//����������� ������
	//�����
	TINYStyleProperty propcaption,//���������
		propsysmenu,//��������� ���� �� ���������
		propresize,//����� ��������� ����
		propminbox,//������ "��������" � ���������
		propmaxbox,//������ "����������" � ���������
		proptoolwnd,//��������� ������
		prophelp,//������ "?" � ���������
		proptopmost;//������ ���� ����
public:
	bool Create(TINYBaseWnd* parent);
	LRESULT _OnCustomMsg(TINYBaseWnd* wnd,TINYParams params);//��������� ��������� ���������
};

};