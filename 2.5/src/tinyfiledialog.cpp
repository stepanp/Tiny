//-----------------------------------------------
//tiny 2.5
//tinyfiledialog.cpp - ������ ��������/����������
//� 2009-2010 Stepan Prokofjev
//-----------------------------------------------

#include "tinyfiledialog.h"

using namespace tiny;

void TINYFileDialog::Create(TINYBaseWnd *parent,LPCWSTR filter,DWORD flags)
{
	ZeroMemory(namebuf,MAX_PATH);//�������� ����� ���� �����
	ZeroMemory(&ofn,sizeof(OPENFILENAME));//�������� ��������� �������
	//���������� ��������� �������
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFile=namebuf;//����� ���� �����
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter=filter;//������
	ofn.nFilterIndex=0;//������ ���������� ������� �� ���������
	ofn.Flags=OFN_EXPLORER|flags;
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	ofn.hwndOwner=hparent;//HWND ������������� ����
}
//������� ������ ��������
bool TINYFileDialog::DoOpen()
{
	if(!GetOpenFileName(&ofn)) return false;
	return true;
}
//������� ������ ����������
bool TINYFileDialog::DoSave()
{
	if(!GetSaveFileName(&ofn)) return false;
	return true;
}
//�������� ��� �����
TINYStr TINYFileDialog::GetFilename()
{
	TINYStr str=namebuf;
	return str;
}