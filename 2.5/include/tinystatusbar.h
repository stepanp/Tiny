//----------------------------
//tiny 2.5
//tinystatusbar.h - ���������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

//��������� ����� ����������
struct TINYSTATUS
{
	int w;//������
	LPCWSTR text;//�����
	HICON icon;//������
	bool hide;//�������� �����
};

class TINYStatusBar: public TINYControlEx
{
protected:
	TINYArr<TINYSTATUS> _parts;//������ ������
	bool _UpdateParts();//�������� �����
	bool _CheckIndex(int index);//�������� �������
public:
	bool Attach(HWND hwnd);
	bool Create(TINYBaseWnd *parent);
	bool InsertPart(int index,int w,LPCWSTR text,HICON icon);//�������� �����
	bool AddPart(int w,LPCWSTR text,HICON icon);//�������� �����
	bool DeletePart(int index);//������� �����
	bool MovePart(int index,int nindex);//����������� �����
	bool ShowPart(int index,bool show);//������/�������� �����
	bool GetShowPart(int index);//��������� �������� �� �����
	bool Clear();//������� ��� �����
	int GetPartCount();//�������� ���-�� ������
	bool SetPartW(int index,int w);//���������� ������ �����
	int GetPartW(int index);//�������� ������ �����
	bool SetPartIcon(int index,HICON icon);//���������� ������ ��� �����
	HICON GetPartIcon(int index);//�������� ������ �����
	bool SetPartText(int index,PCWSTR text);//���������� ����� �����
	int GetPartText(int index,LPWSTR text);//�������� ����� �����
	int GetPartTextLen(int index);//�������� ����� ������
};

};
