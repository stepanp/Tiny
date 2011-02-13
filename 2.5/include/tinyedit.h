//----------------------------
//tiny 2.5
//tinyedit.h - ����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYEdit: public TINYControl
{
public:
	TINYEdit();
public:
	//��������
	TINYStyleProperty propnumber,//������� ������ �����
		proppassword,//�������� ������� �����������
		propreadonly,//������ ������
		propuppercase,//��� ������ � ������� ��������
		proplowercase,//��� ������ � ������ ��������
		propautovscroll,//������������ ����������
		propautohscroll,//�������������� ����������
		propnohidesel;//�� �������� ���������
	//�������
	TINYEvent onchange;//��� ���������
public:
	bool Create(TINYBaseWnd *parent);
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//��������� ��������� ������
};

};