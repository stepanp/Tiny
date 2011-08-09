//--------------------------------------
//tiny 2.5
//tinybuttons.h - ������, ������� � �.�.
//� 2009-2010 Stepan Prokofjev
///--------------------------------------

#pragma once

#include "tinybase.h"

namespace tiny{


//------
//������
//------
class TINYButton: public TINYControl
{
public:
	TINYButton();
	//�������
	TINYEvent onclick;//��� �����
public:
	bool Create(TINYBaseWnd *parent);
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//��������� ��������� ������

};

//-------
//�������
//-------
class TINYCheckBox: public TINYButton
{
public:
	TINYCheckBox();
	//��������
	TINYBoolProperty propcheck;//����� �� �������
public:
	bool Create(TINYBaseWnd *parent);
	bool SetCheck(bool check);//���������� �������
	bool GetCheck();//��������� �������

};

//-----------
//�����������
//-----------
class TINYRadioButton: public TINYCheckBox
{
public:
	bool Create(TINYBaseWnd *parent);
};

//--------
//��������
//--------
class TINYGroupBox: public TINYButton
{
public:
	bool Create(TINYBaseWnd *parent);
};

};