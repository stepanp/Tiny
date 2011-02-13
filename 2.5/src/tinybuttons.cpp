//----------------------------------------
//tiny 2.5
//tinybuttons.cpp - ������, ������� � �.�.
//� 2009-2010 Stepan Prokofjev
//----------------------------------------

#include "tinybuttons.h"

using namespace tiny;


//------
//������
//------
TINYButton::TINYButton()
{
	_oncustomcmd.Connect(this,&TINYButton::_OnCustomCmd);//��������� ��������� ������
}
bool TINYButton::Create(TINYBaseWnd *parent)
{
	return TINYControl::Create(parent,L"BUTTON",0,0,0,0,0,100,25);
}
//��������� ��������� ������
LRESULT TINYButton::_OnCustomCmd(TINYBaseWnd* wnd,TINYParams params)
{
	//��������� �������
	TINYMSGPARAMS* cmd=(TINYMSGPARAMS*)(params);

	if(cmd->code==BN_CLICKED) onclick(wnd,0);
	return 0;
}

//-------
//�������
//-------
TINYCheckBox::TINYCheckBox()
{
	propcheck.Init(this,&TINYCheckBox::SetCheck,&TINYCheckBox::GetCheck);
}

bool TINYCheckBox::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_AUTOCHECKBOX);
}
//���������� �������
bool TINYCheckBox::SetCheck(bool check)
{
	int value=0;
	if(check) value=1;
	if(!SendMessage(_hwnd,BM_SETCHECK,value,0)) return false;
	return true;
}
//��������� �������
bool TINYCheckBox::GetCheck()
{
	if(SendMessage(_hwnd,BM_GETCHECK,0,0)==1) return true;
	return false;
}

//-----------
//�����������
//-----------

bool TINYRadioButton::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_AUTORADIOBUTTON);
}

//--------
//��������
//--------

bool TINYGroupBox::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_GROUPBOX);
}
