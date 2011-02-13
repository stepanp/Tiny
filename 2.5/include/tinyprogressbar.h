//-------------------------------
//tiny 2.5
//tinyprogressbar.h - �����������
//� 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYProgressBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetPos(int pos);//���������� �������
	int GetPos();//�������� �������
	int DeltaPos(int pos);//���������� ������� �� ���-�� �����
	int SetStep(int step);//���������� ��� ������������
	int GetStep();//�������� ��� ������������
	int StepIt();//������������ �� 1 ���
	void SetRange(int min,int max);//���������� ����������� � ������������ �������
	int GetMinRange();//�������� ����������� �������
	int GetMaxRange();//�������� ������������ �������
	//������� � XP
#if(_WIN32_WINNT>=0x0501)
	void SetMarquee(bool enable,int speed);//���/���� ������� ������� � ���������� � ��������
#endif
};

};