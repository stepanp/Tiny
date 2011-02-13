//----------------------------
//tiny 2.5
//tinyevent.h - ����� �������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"

namespace tiny{

class TINYBaseWnd;

//��� ����������
typedef LPARAM TINYParams;

//-------------
//����� �������
//-------------
class TINYEvent: public TINYObject
{
	//���� ���������� �� �����������
	typedef LRESULT (TINYObject::*Handler)(TINYBaseWnd* /*��������� �� ���� �����������*/,TINYParams/*���������*/);//������� ����������
	typedef void (TINYObject::*NotifyHandler)();//���������� ��� ���������

public:
	TINYEvent();
protected:
	TINYObject* _ptr;//��������� �� ������ ������, �������� ����������� ����������
	Handler _handler;//��������� �� ����������
	NotifyHandler _ntfhandler;//��������� �� ���������� ��� ����������
public:
	//����������� ����������� � �������
	template<class Class_T>
	bool Connect(TINYObject* ptr,LRESULT (Class_T::*handler)(TINYBaseWnd*,TINYParams))
	{
		if(!ptr || !handler) return false;
		//���������� ����������
		_ptr=ptr;
		//�������������� Class_T::*Handler � TINYObject::*Handler
		_handler=reinterpret_cast<Handler>(handler);
		_ntfhandler=0;
		return true;	
	}
	template<class Class_T>
	bool Connect(TINYObject* ptr,void (Class_T::*ntfhandler)())
	{
		if(!ptr || !ntfhandler) return false;
		//���������� ����������
		_ptr=ptr;
		_handler=0;
		//�������������� Class_T::*NotifyHandler � TINYObject::*NotifyHandler
		_ntfhandler=reinterpret_cast<NotifyHandler>(ntfhandler);
		return true;	
	}	
	void Disconnect();//���������� �����������
	//��������, ����� �� ����������
	//���������� 0 ���� �� �����
	//1, ���� ����� ������� ����������
	//2, ���� ����� ���������� ��� ����������
	int IsConnected();
	LRESULT operator()(TINYBaseWnd* wnd,TINYParams params);//�������� ������ �������
};

//-------------------
//����� ����� �������
//-------------------
class TINYEventMap: public TINYObject
{
protected:
	TINYArr<TINYEvent> _events;//������ �������
	TINYArr<UINT> _keys;//������ ������
public:
	template<class Class_T>
	bool Connect(TINYObject* ptr,UINT key,LRESULT (Class_T::*handler)(TINYBaseWnd*,TINYParams))
	{
		if(!ptr || !handler) return false;

		//�������� ������� ������� � ����� ������
		int index=GetEventIndex(key);
		//���� ������� � ����� ������ ��� ���� � �����, �� �������� �����
		if(index>-1) return _events[index].Connect(ptr,handler);

		//����� �������� � �����
		_keys.Add(key);
		//�������� ������ �������
		TINYEvent nevent;
		nevent.Connect(ptr,handler);
		_events.Add(nevent);
		return true;
	}
	template<class Class_T>
	bool Connect(TINYObject* ptr,UINT key,void (Class_T::*ntfhandler)())
	{
		if(!ptr || !ntfhandler) return false;

		//�������� ������� ������� � ����� ������
		int index=GetEventIndex(key);
		//���� ������� � ����� ������ ��� ���� � �����, �� �������� �����
		if(index>-1) return _events[index].Connect(ptr,ntfhandler);

		//����� �������� � �����
		_keys.Add(key);
		//�������� ������ �������
		TINYEvent nevent;
		nevent.Connect(ptr,ntfhandler);
		_events.Add(nevent);
		return true;
	}
	bool Disconnect(UINT key);//��������� ���������� �� �����
	//�������� ������ ������� �� �����
	//���� ������� � ����� ������ ���, ������ -1
	int GetEventIndex(UINT key);
	LRESULT operator()(TINYBaseWnd* wnd,UINT key,TINYParams params);//��������� ������ ������� �� �����
};

};