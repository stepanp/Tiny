//----------------------------
//tiny 2.5
//tinylayout.cpp - �����������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinylayout.h"

using namespace tiny;

TINYLayout::TINYLayout()
{
	proppadding.Init(this,&TINYLayout::SetPadding,&TINYLayout::GetPadding);
	propspacing.Init(this,&TINYLayout::SetSpacing,&TINYLayout::GetSpacing);
	//��������� �����
	_padding=TINYPADDING(0,0,0,0);
}
bool TINYLayout::Create(TINYBaseWnd* parent,bool vert/*�������������� ��� ������������*/) 
{
	if(!parent) return false;
	_parent=parent;
	_layout=0;
	_vert=vert;
	return true;
}
bool TINYLayout::Create(TINYLayout* parent,bool vert/*�������������� ��� ������������*/)
{
	if(!parent) return false;
	_parent=0;
	_layout=parent;
	_vert=vert;
	return true;
}
//�������� ����
int TINYLayout::AddWnd(TINYBaseWnd* wnd,int size)
{
	if(!wnd) return -1;
	TINYLAYOUTITEM item;
	item.wnd=wnd;
	item.layout=0;
	item.size=size;
	return _items.Add(item);
}
//�������� �����������
int TINYLayout::AddLayout(TINYLayout* layout,int size)
{
	if(!layout) return -1;
	TINYLAYOUTITEM item;
	item.wnd=0;
	item.layout=layout;
	item.size=size;
	return _items.Add(item);
}
//�������� �����������
int TINYLayout::AddSeparator(int size)
{
	TINYLAYOUTITEM item;
	item.wnd=0;
	item.layout=0;
	item.size=size;
	return _items.Add(item);
}
//���������� ����
bool TINYLayout::SetWnd(int index,TINYBaseWnd* wnd)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=wnd;
	_items[index].layout=0;	
	return true;
}
//�������� ����
TINYBaseWnd* TINYLayout::GetWnd(int index)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return 0;
	return _items[index].wnd;
}
//���������� �����������
bool TINYLayout::SetLayout(int index,TINYLayout* layout)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=0;
	_items[index].layout=layout;	
	return true;
}
//�������� �����������
TINYLayout* TINYLayout::GetLayout(int index)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return 0;
	return _items[index].layout;
}
//���������� �����������
bool TINYLayout::SetSeparator(int index)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=0;
	_items[index].layout=0;
	return true;
}
//����������� ������ ��������
bool TINYLayout::SetItemSize(int index,int size)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return false;
	_items[index].size=size;
	return true;
}
//�������� ������ ��������
int TINYLayout::GetItemSize(int index)
{
	//���� ������ ������� �� ������� �������
	if(index<0 && index>=_items.GetCount()) return -1;
	return _items[index].size;
}
//������� �������
void TINYLayout::DeleteItem(int index) {_items.Delete(index);}
//����������� �������
void TINYLayout::MoveItem(int index,int nindex) {_items.Move(index,nindex);}
//�������� �������� �������
void TINYLayout::SwapItems(int index,int nindex) {_items.Swap(index,nindex);}
//��������������� ����
void TINYLayout::Align(int x,int y,int w,int h)
{
	int count=_items.GetCount();//���-�� ���������
	int acount=0;//���-�� ��������� � TINY_SIZE_AUTO
	int allsize=0;//����� ������ ��������� ��� TINY_SIZE_AUTO
	int alast=-1;//������ ���������� �������� � TINY_SIZE_AUTO

	//��������� ���-�� ��������� � TINY_SIZE_AUTO
	//� ������ ������� ��������� ��� TINY_SIZE_AUTO
	for(int i=0;i<count;i++)
	{
		if(_items[i].size==TINY_SIZE_AUTO) 
		{
			acount++;//���-�� ��������� � TINY_SIZE_AUTO
			alast=i;///��������� ������ ���������� �������� � TINY_SIZE_AUTO
		}
		else allsize+=_items[i].size;//����� ������ ��������� ��� TINY_SIZE_AUTO
	}

	//������ �������� � TINY_SIZE_AUTO
	int asize=0;
	//���������� � ������� �������� � ������ �����
	int ax=x+_padding.left;
	int ay=y+_padding.top;
	int aw=w-_padding.right-_padding.left;
	int ah=h-_padding.bottom-_padding.top;
	//���������� ����� ����������
	int aspacing=_spacing*(count-1);

	//������������ �����������
	if(_vert)
	{
		//������ �������� � TINY_SIZE_AUTO
		if(acount) 
		{
			asize=(ah-allsize)/acount;
			//��������� ���������� ����� ����������
			asize-=_spacing-_spacing/acount;
		}

		//���������� ��������
		for(int i=0;i<count;i++)
		{
			TINYBaseWnd* wnd=_items[i].wnd;
			TINYLayout* layout=_items[i].layout;

			//����� ������� ��������
			int size;
			if(_items[i].size==TINY_SIZE_AUTO)
			{
				size=asize;//�������������� ������
				//��������� ����������� �������
				if(i==alast) size+=ah-allsize-(asize*acount)-aspacing;
			}
			else size=_items[i].size;//�������� ������



			//���� �������
			if(wnd)
			{
				//��������� �������
				wnd->Move(ax,ay);
				wnd->SetSize(aw,size);			
			}
			//���� �����������
			if(layout)
			{
				//������� ����� Align() ������������
				layout->Align(ax,ay,aw,size);
			}	

			//�������� ���������� �������� � ������ ���������
			ay+=size+_spacing;
		}	
	}else{
		//�������������� �����������
	
		//������ �������� � TINY_SIZE_AUTO
		if(acount) 
		{
			asize=(aw-allsize)/acount;
			//��������� ���������� ����� ����������
			asize-=_spacing-_spacing/acount;
		}

		//���������� ��������
		for(int i=0;i<count;i++)
		{
			TINYBaseWnd* wnd=_items[i].wnd;
			TINYLayout* layout=_items[i].layout;

			//����� ������� ��������
			int size;
			if(_items[i].size==TINY_SIZE_AUTO)
			{
				size=asize;//�������������� ������
				//��������� ����������� �������
				if(i==alast) size+=aw-allsize-(asize*acount)-aspacing;
			}
			else size=_items[i].size;//�������� ������

			//���� �������
			if(wnd)
			{
				//��������� �������
				wnd->Move(ax,ay);
				wnd->SetSize(size,ah);			
			}
			//���� �����������
			if(layout)
			{
				//������� ����� Align() ������������
				layout->Align(ax,ay,size,ah);
			}
			//�������� ���������� �������� � ������ ���������
			ax+=size+_spacing;
		}	
	}
}
//�������� �����������
bool TINYLayout::Update()
{
	if(!_parent) return false;
	
	//���� �������� �������� �����
	if(_parent) 
	{
		RECT rect=_parent->GetClientRect();
		//������� ����� Align() � ��������� ���������� ������� �������������� ���� 
		Align(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top);
	}
	//���� �������� �������� ������������� ������� ������������ ����� Update()
	if(_layout) return _layout->Update();
	return true;
}
//������� ��� �������
//���������� ����
bool TINYLayout::SetPadding(TINYPADDING padding)
{
	_padding=padding;
	return Update();//�������� �����������
}
//�������� ����
TINYPADDING TINYLayout::GetPadding() {return _padding;}
//���������� ���������� ����� ����������
bool TINYLayout::SetSpacing(int spacing)
{
	_spacing=spacing;
	return Update();//�������� �����������
}
//�������� ���������� ����� ����������
int TINYLayout::GetSpacing() {return _spacing;}
//���������� ������������
void TINYLayout::OnAlign()
{
	Update();
}