//------------------------------
//tiny 2.5
//tinytrayicon.h - ������ � ����
//� 2009-2010 Stepan Prokofjev
//------------------------------

#pragma once

#include "tinybase.h"
#include <shellapi.h>
#pragma comment (lib,"shlwapi.lib")

namespace tiny{

#define TINY_TRAYICON TINY_MESSAGE+2//��������� �� ������ � ����

class TINYTrayIcon: public TINYObject
{
protected:
	NOTIFYICONDATA _data;
public:
	bool Create(TINYBaseWnd *parent,HICON icon,LPCWSTR tip,UINT id);
	bool Delete();//������ ������ �� ����
	bool Modify(HICON icon,LPCWSTR tip);//�������� ������ ������
};

};