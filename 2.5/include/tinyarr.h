//-------------------------------
//tiny 2.5
//tinyarr.h - ������������ ������
//� 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny{

template<typename T>
class TINYArr: public TINYObject
{
public:
	TINYArr()
	{
		_t=0;
		_count=0;	
	}
	TINYArr(int size/*��������� ������*/) 
	{
		_t=new T[size];
		_count=size;
	}
	TINYArr(const TINYArr<T>& arr)
	{
		_t=0;
		Copy(arr);
	}
	~TINYArr() {if(_t) delete[] _t;}
protected:
	T *_t;//������
	int _count;//������ �������
public:
	//�������� �������
	int Add(T t)
	{
		//�������� ������ �������
		//�������� �� 1 ������� ������
		T*temp=new T[_count+1];
		//����������� ��������� � ����� ������
		for(int i=0;i<_count;i++) temp[i]=_t[i];
		//�������� ������� �������
		if(_t) delete[] _t;
		//������� ���������
		_t=temp;
		//���������� ������ ��������
		_t[_count]=t;
		//���������� ������� ������� �� 1
		_count++;
		return _count-1;//������� ������ ������ �������
	}
	//�������� �������
	int Insert(int index,T t)
	{
		//�������� ������ �������
		//�������� �� 1 ������� ������
		T*temp=new T[_count+1];
		//����������� ���������, �� index � ����� ������
		for(int i=0;i<index;i++) temp[i]=_t[i];
		//������� ������ ��������
		temp[index]=t;
		//����������� ��������� ���������
		for(int i=index+1;i<_count+1;i++) temp[i]=_t[i-1];
		//�������� ������� �������
		if(_t) delete[] _t;
		//������� ���������
		_t=temp;
		//���������� ������� ������� �� 1
		_count++;
		return index;//������� ������ ������ �������
	}
	//������� �������
	void Delete(int index)
	{
		//�������� ������ �������
		//�������� �� 1 ������� ������
		T*temp=new T[_count-1];
		//����������� ���������, �� index � ����� ������
		for(int i=0;i<index;i++) temp[i]=_t[i];
		//����������� ��������� ���������
		for(int i=index;i<_count;i++) temp[i]=_t[i+1];
		//�������� ������� �������
		delete[] _t;
		//������� ���������
		_t=temp;
		//���������� ������� ������� �� 1
		_count;
	}
	//����������� �������
	void Move(int index,int nindex)
	{
		//��������� �������
		T temp=_t[index];
		//���� ������� ����� ��������� �����
		if(index<nindex)
		{
			//�������� �������� ����
			for(int i=index;i<nindex;i++) _t[i]=_t[i+1];
			//��������� ����������� �������
			_t[nindex]=temp;		
		}
		//���� ������� ����� ��������� ����
		if(index>nindex)
		{
			//�������� �������� �����
			for(int i=nindex;i>index;i--) _t[i]=_t[i-1];
			//��������� ����������� �������
			_t[nindex]=temp;		
		}	
	}
	//�������� �������� �������
	void Swap(int index,int nindex)
	{
		//��������� �������
		T temp=_t[index];
		//������ �������
		_t[index]=_t[nindex];
		_t[nindex]=temp;	
	}
	//�������� ������
	void Clear()
	{
		if(_t) delete[] _t;
		_t=0;
		_count=0;
	}
	//�������� ������ �������
	void Resize(int size)
	{
		//�������� ������ �������
		T*temp=new T[size];
		int count;//���-�� ���������� ���������
		//���� ������ ������ ������ ������,
		//�� ���������� size ���������
		if(_count>size) count=size;
		else count=_count;//����� ���������� ��� ��������
		//����������� ��������� � ����� ������
		for(int i=0;i<count;i++) temp[i]=_t[i];
		//�������� ������� �������
		if(_t) delete[] _t;
		//������� ���������
		_t=temp;
		_count=size;	
	}
	//����������� ���������� ������� �������
	void Copy(const TINYArr<T>& arr)
	{
		int count=arr.GetCount();
		//�������� ������ �������
		T *temp=new T[count];
		//��������� ��������� �� ������
		T* t=arr.GetPointer();
		//����������� ���������
		for(int i=0;i<count;i++) temp[i]=t[i];
		//�������� ������� �������
		if(_t) delete[] _t;
		//������� ���������
		_t=temp;
		_count=count;
	}
	//�������� ������
	int GetCount() const {return _count;}
	//�������� �������
	T Get(int index) {return _t[index];}
	T& operator[](int index) {return _t[index];}
	//�������� ��������� �� ��� ������
	T* GetPointer() const {return _t;}
	//�������� �����������
	TINYArr<T>& operator=(const TINYArr<T>& arr) 
	{
		Copy(arr);
		return *this;
	}
};

};