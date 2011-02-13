//-------------------------------
//tiny 2.5
//tinyproperty.h - ����� ��������
//� 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny{

//--------------
//����� ��������
//--------------
template<typename T/*��� ��������*/>
class TINYProperty: public TINYObject
{
protected:

	//���� ����������
	typedef bool (TINYObject::*SetFunc)(T);//������
	typedef T (TINYObject::*GetFunc)();//������

protected:
	TINYObject *_pointer;//��������� �� ������, �������� ����������� ��������� �� �������
	//��������� �� �������
	SetFunc _set;
	GetFunc _get;
public:
	//������������� ��������
	template<class Class_T>
	void Init(TINYObject *pointer,//��������� �� ������, �������� ����������� ��������� �� �������
		bool (Class_T::*set)(T),//������
		T (Class_T::*get)()//������
		)
	{
		//���������� ����������
		_pointer=pointer;
		_set=reinterpret_cast<SetFunc>(set);
		_get=reinterpret_cast<GetFunc>(get);
	}
	//�������� ������������
	void operator=(const T& t)
	{
		//����� �������
		(_pointer->*_set)(t);
	}
	//�������� T
	operator T() const
	{
		//����� �������
		return (_pointer->*_get)();
	}
};


//--------------
//�������� �����
//--------------
class TINYStyleProperty: public TINYProperty<DWORD>
{
protected:
	DWORD _style;//�����, ��������������� ���������
public:
	//������������� ��������
	template<class Class_T>
	void Init(TINYObject *pointer,//��������� �� ������, �������� ����������� ��������� �� �������
		DWORD style,//�����
		bool (Class_T::*set)(DWORD),//������
		DWORD (Class_T::*get)()//������
		)
	{
		//���������� �����
		_style=style;
		TINYProperty<DWORD>::Init(pointer,set,get);
	}
	//�������� ������������ ��� bool
	void operator=(const bool value)
	{
		//���� value true, �� ��������� �����
		if(value) (_pointer->*_set)((_pointer->*_get)()|_style);
		//����� ������� �����
		else (_pointer->*_set)((_pointer->*_get)()&~_style);
	}
	//�������� bool
	operator bool() const
	{
		//���� ����� ���������� ������� true
		if((_pointer->*_get)()&_style) return true;
		else return false;
	}
private:
	//��������� ��������� ��� DWORD
	void operator=(const DWORD& value) {}
	operator DWORD() const {return 0;}
};

//�������� ���� �������
typedef TINYProperty<bool> TINYBoolProperty;//bool
typedef TINYProperty<TINYStr> TINYStrProperty;//TINYStr - ������
typedef TINYProperty<int> TINYIntProperty;//int
typedef TINYProperty<TINYIcon> TINYIconProperty;//TINYIcon - ������


};