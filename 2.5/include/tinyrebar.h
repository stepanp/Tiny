//----------------------------
//tiny 2.5
//tinyrebar.h - �����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYReBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent);
	//�c������ ����
	bool InsertBand(int index,TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h);
	bool AddBand(TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h);//�������� ����
	bool DeleteBand(int index);//������� ����
	bool MoveBand(int index,int nindex);//����������� ����
	bool ShowBand(int index,bool show);//������/�������� ����
	int GetBandCount();//�������� ���-�� ������
};

};