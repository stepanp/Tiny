//------------------------------------
//tiny 2.5
//tinydesignwnd.h - ���� ��� ���������
//� 2009-2010 Stepan Prokofjev
//------------------------------------

#pragma once

#include "tinyappwnd.h"

//������� ��� �����������
#define TINY_GEN_CTRLS(TINYDesignWnd)//������ ���������� ���������
#define TINY_GEN_CTRLS_END//����� ���������� ���������
#define TINY_GEN_CREATE(TINYDesignWnd)//������ �������� ���������
#define TINY_GEN_CREATE_END//����� �������� ���������

namespace tiny{

class TINYDesignWnd: public TINYAppWnd
{
public:
	//���������� ��������� ����
	void SetDesignParams(LPCWSTR text,UINT icon,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
};

};