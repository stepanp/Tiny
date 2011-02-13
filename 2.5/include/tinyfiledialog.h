//---------------------------------------------
//tiny 2.5
//tinyfiledialog.h - ������ ��������/����������
//� 2009-2010 Stepan Prokofjev
//---------------------------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYFileDialog: public TINYObject
{
protected:
	OPENFILENAME ofn;//��������� �������
	wchar_t namebuf[MAX_PATH];//����� ����� �����
public:
	void Create(TINYBaseWnd *parent,LPCWSTR filter,DWORD flags);
	bool DoOpen();//������� ������ ��������
	bool DoSave();//������� ������ ����������
	TINYStr GetFilename();//�������� ��� �����
};


};