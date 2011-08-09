//----------------------------
//tiny 2.5
//tinyapp.h - ����������
//� 2009-2010 Stepan Prokofjev
///----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYApp: public TINYObject
{
public:
	TINYApp();
	virtual int OnInit(LPSTR cmd,int showcmd)=0;//�������������
	int Run();//������ ����� ���������
	void Quit(int code=0);//�����
};

extern TINYApp *THIS_APP;//���������� ��������� �� ����������

};