//----------------------------
//tiny 2.5
//tinyimagelist.h - ���������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinygdi.h"
#include <shlobj.h>
#pragma comment(lib,"shell32")

namespace tiny{

class TINYImageList: public TINYObject
{
protected:
	HIMAGELIST _hlist;
public:
	HIMAGELIST GetHIMAGELIST();//�������� HIMAGELSIT
	bool Create(DWORD flags,int w,int h);
	int AddIcon(HICON icon);//�������� ������
	int AddBitmap(HBITMAP bmp);//�������� ������
	//�������� ������ � ������
	int AddMasked(HBITMAP bmp,
		COLORREF mask=RGB(255,0,255)//���� �����(������)
		);
	int GetCount();//�������� ���-�� ��������
	bool Delete(int index);//������� ��������
	bool Clear();//��������
	HICON GetIcon(int index);//������� ������
};

};