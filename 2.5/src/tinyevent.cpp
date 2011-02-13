//-----------------------------
//tiny 2.5
//tinyevent.cpp - ����� �������
//� 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinyevent.h"

using namespace tiny;

//-------------
//����� �������
//-------------

TINYEvent::TINYEvent()
{
	//��������� ����������
	_ptr=0;
	_handler=0;
	_ntfhandler=0;
}
//���������� �����������
void TINYEvent::Disconnect()
{
	//��������� ����������
	_ptr=0;
	_handler=0;	
	_ntfhandler=0;
}
//��������, ����� �� ����������
//���������� 0 ���� �� �����
//1, ���� ����� ������� ����������
//2, ���� ����� ���������� ��� ����������
int TINYEvent::IsConnected()
{
	if(_ptr && _handler && !_ntfhandler) return 1;
	if(_ptr && !_handler && _ntfhandler) return 2;
	return 0;
}
//�������� ������ �������
LRESULT TINYEvent::operator()(TINYBaseWnd* wnd,TINYParams params)
{
	if(IsConnected()==1)
	{
		return (_ptr->*_handler)(wnd,params);
	}
	else if(IsConnected()==2)
	{
		(_ptr->*_ntfhandler)();
	}
	return 0;
}

//-------------------
//����� ����� �������
//-------------------

//��������� ���������� �� �����
bool TINYEventMap::Disconnect(UINT key)
{
	//�������� ������� ������� � ����� ������
	int index=GetEventIndex(key);

	//���� ������� � ����� ������ ����
	if(index>-1)
	{
		//�������
		_events.Delete(index);
		return true;
	}
	return false;
}
//�������� ������ ������� �� �����
//���� ������� � ����� ������ ���, ������ -1
int TINYEventMap::GetEventIndex(UINT key)
{
	int count=_keys.GetCount();//���-�� ������
	//������� ������
	for(int i=0;i<count;i++) if(_keys[i]==key) return i;
	return -1;
}
//�������� ������ ������� �� �����
LRESULT TINYEventMap::operator()(TINYBaseWnd* wnd,UINT key,TINYParams params)
{
	//�������� ������� ������� � ����� ������
	int index=GetEventIndex(key);

	//����� ����������� �������
	if(index>-1) return _events[index](wnd,params);
	return 0;		
}