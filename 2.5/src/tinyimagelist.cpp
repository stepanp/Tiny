//-----------------------------
//tiny 2.5
//tinyimagelist.cpp - ���������
//� 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinyimagelist.h"

using namespace tiny;

//�������� HIMAGELSIT
HIMAGELIST TINYImageList::GetHIMAGELIST()
{
	return _hlist;
}
bool TINYImageList::Create(DWORD flags,int w,int h)
{
	_hlist=ImageList_Create(w,h,flags,0,0);
	if(_hlist) return false;
	return true;
}
//�������� ������
int TINYImageList::AddIcon(HICON icon)
{
	return ImageList_AddIcon(_hlist,icon);
}
//�������� ������
int TINYImageList::AddBitmap(HBITMAP bmp)
{
	return ImageList_Add(_hlist,bmp,0);
}
//�������� ������ � ������
int TINYImageList::AddMasked(HBITMAP bmp,COLORREF mask)
{
	return ImageList_AddMasked(_hlist,bmp,mask);
}
//������� ��������
bool TINYImageList::Delete(int index)
{
	if(!ImageList_Remove(_hlist,index)) return false;
	return true;
}
//�������� ���-�� ��������
int TINYImageList::GetCount()
{
	return ImageList_GetImageCount(_hlist);
}
//��������
bool TINYImageList::Clear()
{
	return Delete(-1);
}
//������� ������
HICON TINYImageList::GetIcon(int index)
{
	return ImageList_GetIcon(_hlist,index,ILD_NORMAL);
}