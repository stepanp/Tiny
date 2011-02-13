//----------------------------
//tiny 2.5
//tinytoolbar.cpp - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinytoolbar.h"

using namespace tiny;


TINYToolBar::TINYToolBar()
{
	//���������� ��� ����������� ���������
	//AddMessage(WM_NOTIFY,&TINYToolBar::_OnToolTip);
}

bool TINYToolBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_BAR_CLASSES,TOOLBARCLASSNAME,0,0,
		CCS_NOPARENTALIGN|//�� �����������
		CCS_NODIVIDER|//��� ������� ������
		CCS_NORESIZE|//�� ������ ������ �������������
		TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|//���������� ���	
		TBSTYLE_TOOLTIPS,//����������� ��������� �� �������
		0,0,0,25);
}
//���������� ����������� �����
bool TINYToolBar::SetExtendedStyle(DWORD style)
{
	if(!SendMessage(_hwnd,TB_SETEXTENDEDSTYLE,0,LPARAM(style))) return false;
	return true;
}
//�������� ������
bool TINYToolBar::InsertButton(int index,DWORD style,DWORD state,int nimage,
							LPCWSTR text,LPCWSTR tip,UINT id)
{
	//�������� ������
	TBBUTTON btn;
	btn.fsState=BYTE(state);
	btn.fsStyle=BYTE(style);
	btn.iBitmap=nimage;
	btn.iString=INT_PTR(text);
	btn.idCommand=id;
	btn.dwData=DWORD_PTR(tip);//����������� ���������
	//���������� ������
	if(!SendMessage(_hwnd,TB_INSERTBUTTON,WPARAM(index),LPARAM(&btn))) return false;
	return true;
}
//�������� ������
bool TINYToolBar::AddButton(DWORD style,DWORD state,int nimage,LPCWSTR text,LPCWSTR tip,UINT id)
{
	return InsertButton(-1,style,state,nimage,text,tip,id);
}
//������� ���������
bool TINYToolBar::InsertSeparator(int index)
{
	return InsertButton(index,BTNS_SEP,0,0,0,0,0);
}
//�������� ���������
bool TINYToolBar::AddSeparator()
{
	return InsertSeparator(-1);
}
//������� ������
bool TINYToolBar::DeleteButton(int index)
{
	if(!SendMessage(_hwnd,TB_DELETEBUTTON,WPARAM(index),0)) return false;
	return true;
}
//����������� ������
bool TINYToolBar::MoveButton(int index,int nindex/*����� ������ ������*/)
{
	if(!SendMessage(_hwnd,TB_MOVEBUTTON,WPARAM(index),LPARAM(index))) return false;
	return true;
}
//���������� ��������� ������
bool TINYToolBar::SetButtonState(int id,DWORD state)
{
	if(!SendMessage(_hwnd,TB_SETSTATE,WPARAM(id),LPARAM(MAKELONG(state,0)))) return false;
	return true;
}
//�������� ��������� ������
DWORD TINYToolBar::GetButtonState(int id)
{
	return SendMessage(_hwnd,TB_GETSTATE,WPARAM(id),0);
}
//��������/��������� ������
bool TINYToolBar::EnableButton(int id,bool enable)
{
	if(!SendMessage(_hwnd,TB_ENABLEBUTTON,WPARAM(id),LPARAM(enable))) return false;
	return true;
}
//��������/������ ������
bool TINYToolBar::ShowButton(int id,bool show)
{
	bool ishow=show;
	if(show) ishow=false;
	else ishow=true;
	if(!SendMessage(_hwnd,TB_HIDEBUTTON,WPARAM(id),LPARAM(ishow))) return false;
	return true;
}
//���������� ���������
bool TINYToolBar::SetImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//���������� ��������� ��� ������������ ������
bool TINYToolBar::SetHotImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETHOTIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//���������� ��������� ��� ����������� ������
bool TINYToolBar::SetDisbaleImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETDISABLEDIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//���������� ������ �������������
void TINYToolBar::AutoSize()
{
	SendMessage(_hwnd,TB_AUTOSIZE,0,0);
}
//�������� ���-�� ������
int TINYToolBar::GetButtonCount()
{
	return SendMessage(_hwnd,TB_BUTTONCOUNT,0,0);
}
//�������� ������
TBBUTTON TINYToolBar::GetButton(int index)
{
	TBBUTTON btn;
	SendMessage(_hwnd,TB_GETBUTTON,WPARAM(index),LPARAM(&btn));
	return btn;
}

//���������� ��� ����������� ���������
LRESULT TINYToolBar::_OnToolTip(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	if(LPNMHDR(lparam)->code==TTN_GETDISPINFO)
	{
		LPTOOLTIPTEXT tip=LPTOOLTIPTEXT(lparam);
		tip->hinst=GetModuleHandle(0);
		//��������� id ������
		int id=tip->hdr.idFrom;
		//����� ������ � ����� id
		for(int i=0;i<GetButtonCount();i++)
		{
			TBBUTTON btn=GetButton(i);
			//���� id ��������� �� �������� ���������
			//��� ���� ������
			if(btn.idCommand==id)
			{
				tip->lpszText=LPWSTR(btn.dwData);	
				break;
			}
		}	
	}
	return 0;
}