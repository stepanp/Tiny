//----------------------------
//tiny 2.5
//tinyarr.h - ������
//� 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyarr.h"
#include "tinyobject.h"

namespace tiny{

template<typename T/*wchar_t ��� char*/>
class TINYStr_T: public TINYArr<T>
{
public:
	TINYStr_T() {};
	TINYStr_T(const T* str)
	{
		CopyStr(str);	
	}
	//����� � ������
	TINYStr_T(int value)
	{
		wchar_t* str=new wchar_t[MAX_PATH];
		if(_itow_s(value,str,MAX_PATH,10)==0) CopyStr(str);
		delete[] str;
	}
public:
	//���������� ������
	void Append(TINYStr_T<T>& str)
	{
		int clen,nlen,len;
		clen=GetLen();//����� ������� ������
		nlen=str.GetLen();//����� �������������� ������
		len=clen+nlen+1;//����� ����� ����� + 0 � �����
		//��������� �������
		Resize(len);
		//����������� ���������
		for(int i=0;i<nlen;i++) _t[clen+i]=str[i];
		//0 � �����
		_t[len-1]=0;	
	}
	void Append(const T* str)
	{
		int clen,nlen,len;
		clen=GetLen();//����� ������� ������
		nlen=lstrlen(str);//����� �������������� ������
		len=clen+nlen+1;//����� ����� ����� + 0 � �����
		//��������� �������
		Resize(len);
		//����������� ���������
		for(int i=0;i<nlen;i++) _t[clen+i]=str[i];	
		//0 � �����
		_t[len-1]=0;	
	}
	//����������� ���������� ������
	void CopyStr(const T* str)
	{
		int len=lstrlen(str)+1;//����� ������ + 0 � �����
		//�������� ����� ������
		T *temp=new T[len];
		//����������� ������ � ������
		for(int i=0;i<len-1;i++) temp[i]=str[i];
		//��������� ���� � �����
		temp[len-1]=0;
		//�������� �������
		if(_t) delete[] _t;
		//������� ���������
		_t=temp;
		//������ ������� ����� ����� ������
		_count=len;	
	}
	//�������� ������
	bool Compare(const T* str)
	{
		if(!_count || lstrlen(str)!=_count-1/*���� ����� �� ���������*/) return false;
		//������� ���� ��������
		for(int i=0;i<_count-1;i++)
		{
			//��������� ��������
			if(_t[i]!=str[i]) return false;
		}
		return true;
	}
	//�������� ����� ������
	int GetLen()
	{
		if(_count) return _count-1;
		else return 0;
	}
	//������������� � �����
	int ToInt()
	{
		if(_count<0 || !_t) return 0;
		return _wtoi(_t);	
	}
	//�������� ������
	const T* c_str() {return _t;}
	//�������� ����������� ������
	TINYStr_T<T>& operator=(const T* str)
	{
		CopyStr(str);
		return *this;	
	}
	//��������� ��������
	TINYStr_T<T>& operator+(TINYStr_T<T>& str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+(const T* str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+=(TINYStr_T<T>& str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+=(const T* str)
	{
		Append(str);
		return *this;	
	}
	//�������� ���������
	bool operator==(TINYStr_T<T>& str) {return Compare(str);}
	bool operator==(const T* str) {return Compare(str);}
	operator const T*() {return c_str();}
};

typedef TINYStr_T<wchar_t> TINYStr;

};