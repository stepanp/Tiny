//----------------------------
//tiny 2.5
//tinymenu.cpp - ����
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinymenu.h"

using namespace tiny;

//----
//����
//----
bool TINYMenu::Create() {return Attach(CreateMenu());}
bool TINYMenu::Create(UINT menu)
{
	if(!menu) return false;
	return Attach(LoadMenu(GetModuleHandle(0),MAKEINTRESOURCE(menu)));	
}
//������� �� HMENU
bool TINYMenu::Attach(HMENU menu)
{
	if(!menu) return false;
	_menu=menu;
	MENUINFO mi;
	mi.cbSize=sizeof(MENUINFO);
	mi.fMask=MIM_MENUDATA;
	mi.dwMenuData=ULONG_PTR(this);//���������� ��������� �� ������ ������
	if(!SetMenuInfo(_menu,&mi)) return false;
	return true;
}
//�������� HMENU
HMENU TINYMenu::GetHMENU() {return _menu;}
//���������� ���� ����
bool TINYMenu::SetToWindow(TINYBaseWnd *wnd)
{
	if(!wnd) return false;
	if(!SetMenu(wnd->GetHWND(),_menu)) return false;
	return true;
}
//�������� ����� ����
bool TINYMenu::InsertItem(int index,LPCWSTR text,UINT id,TINYMenu* submenu)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STRING|MIIM_ID|MIIM_SUBMENU;
	mi.dwTypeData=LPWSTR(text);
	mi.wID=id;
	if(submenu) mi.hSubMenu=submenu->GetHMENU();//�������� HMENU ��� �������
	else mi.hSubMenu=0;
	if(!InsertMenuItem(_menu,index,TRUE,&mi)) return false;
	return true;
}
//�������� ����� ����
bool TINYMenu::AddItem(LPCWSTR text,UINT id,TINYMenu* submenu)
{
	return InsertItem(-1,text,id,submenu);
}
//������� ����� ����
bool TINYMenu::DeleteItem(int index)
{
	if(!DeleteMenu(_menu,index,MF_BYPOSITION)) return false;
	return true;
}
//�������� �������
TINYMenu* TINYMenu::GetSubMenu(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_SUBMENU;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	HMENU menu=mi.hSubMenu;
	//��������� TINYMenu* �� HMENU
	MENUINFO mni;
	mni.cbSize=sizeof(MENUINFO);
	mni.fMask=MIM_MENUDATA;
	GetMenuInfo(menu,&mni);
	return (TINYMenu*)(mni.dwMenuData);
}
//���������� �������
bool TINYMenu::SetSubMenu(int index,TINYMenu* submenu)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_SUBMENU;
	if(submenu)	mi.hSubMenu=submenu->GetHMENU();//�������� HMENU ��� �������
	else mi.hSubMenu=0;
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;
}
//�������� ���������
DWORD TINYMenu::GetItemState(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STATE;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	return mi.fState;
}
//���������� ���������
bool TINYMenu::SetItemState(int index,DWORD state)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STATE;
	mi.fState=state;
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;	
}
//���������� �������������� ��������
bool TINYMenu::SetItemData(int index,LPARAM data)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_DATA;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	mi.dwItemData=ULONG_PTR(data);
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;
}
//�������� �������������� ��������
LPARAM TINYMenu::GetItemData(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_DATA;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	return mi.dwItemData;
}


//----------------
//����������� ����
//----------------
bool TINYPopupMenu::Create() {return Attach(CreatePopupMenu());}
//������� �� ��������
bool TINYPopupMenu::Create(UINT menu)
{
	if(!menu) return false;
	HMENU tmenu;
	tmenu=LoadMenu(GetModuleHandle(0),MAKEINTRESOURCE(menu));
	tmenu=::GetSubMenu(tmenu,0);//�������� �������	
	return Attach(tmenu);
}
//�������� ���������
bool TINYPopupMenu::InsertSeparator(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_TYPE;
	mi.fType=MFT_SEPARATOR;
	if(!InsertMenuItem(_menu,index,TRUE,&mi)) return false;
	return true;
}
//�������� ���������
bool TINYPopupMenu::AddSeparator() {return InsertSeparator(-1);}
//������������ ����
bool TINYPopupMenu::EnableItem(int index,bool enable)
{
	DWORD state;
	if(enable) state=MFS_ENABLED;
	else state=MFS_DISABLED|MFS_GRAYED;
	return SetItemState(index,state);
}
//��������� ����������� �� ����� ����
bool TINYPopupMenu::GetEnableItem(int index)
{
	if(GetItemState(index)&MFS_ENABLED) return true;
	return false;
}
//��������� �������
bool TINYPopupMenu::CheckItem(int index,bool check)
{
	DWORD state;
	if(check) state=MFS_CHECKED;
	else state=MFS_UNCHECKED;
	return SetItemState(index,state);
}
//��������� �������
bool TINYPopupMenu::GetCheckItem(int index)
{
	if(GetItemState(index)&MFS_CHECKED) return true;
	return false;
}
//�������� ����
bool TINYPopupMenu::Track(TINYBaseWnd *parent,int x,int y)
{
	int nx,ny;
	//���� x � y ����� -1
	//�� �������� ���� � ������� �������
	if((x==-1)&&(y==-1))
	{
		//��������� ������� ������� 
		POINT point;
		GetCursorPos(&point);
		nx=point.x;
		ny=point.y;
	}else{
		nx=x; 
		ny=y;
	}
	if(!parent) return false;
	HWND hparent=parent->GetHWND();	
	if(!TrackPopupMenu(_menu,TPM_LEFTALIGN|TPM_VERTICAL,nx,ny,0,hparent,0)) return false;
	return true;
}