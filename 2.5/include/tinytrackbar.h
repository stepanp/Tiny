//----------------------------
//tiny 2.5
//tinytrackbar.h - �������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYTrackBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetPos(int pos);//���������� �������
	int GetPos();//�������� �������
	void SetRange(int min,int max);//���������� ����������� � ������������ �������
	int GetMinRange();//�������� ����������� �������
	int GetMaxRange();//�������� ������������ �������
	bool SetTick(int pos);//���������� �����
	int GetTick(int index);//�������� ������� �����
	bool SetTickFrequency(int freq);//���������� ������� �����
	bool SetBuddies(TINYBaseWnd *left,TINYBaseWnd *right);//���������� ������� ��������
	TINYBaseWnd* GetLeftBuddy();//�������� ����� �������
	TINYBaseWnd* GetRightBuddy();//�������� ������ �������
};

};