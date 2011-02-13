//----------------------------------
//tiny 2.5
//tinybasewnd.h - ������� ����� ����
//� 2009-2010 Stepan Prokofjev
//----------------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"
#include "tinystr.h"
#include "tinymisc.h"
#include "tinyproperty.h"
#include "tinyevent.h"
#include "tinygdi.h"

namespace tiny{

#define TINY_MESSAGE WM_APP+200

class TINYBaseWnd;

//��������� ���������� ���������
struct TINYMSGPARAMS
{
	UINT code;//���������
	WPARAM wparam;
	LPARAM lparam;
};

//��������� ��� �����
struct TINYPADDING
{
	TINYPADDING()
	{
		//��������� �����
		left=top=right=bottom=0;
	}
	TINYPADDING(int _left,int _top,int _right,int _bottom)
	{
		left=_left;
		top=_top;
		right=_right;
		bottom=_bottom;
	}
	//������� �����
	int left,top,right,bottom;
};

class TINYBaseWnd: public TINYObject
{
public:
	TINYBaseWnd();
protected:
	HWND _hwnd;//HWND ����
	bool _isctrl;//���� ����� ������������ �� TINYControl = true, ����� false
	HACCEL _acc;//����������� (������� �������)
public:
	//��������
	TINYStrProperty proptext;//�����
	TINYIntProperty propx;//�
	TINYIntProperty propy;//Y
	TINYIntProperty propw;//������
	TINYIntProperty proph;//������
	TINYIconProperty propicon;//������� ������
	TINYIconProperty propsmicon;//��������� ������ (16�16)
	//�����
	TINYStyleProperty proptabstop,//��� ����� ���� ����� ���������� ����� �� Tab
		propvscroll,//������������ ������
		prophscroll,//�������������� ������
		propclientedge,//���������� �����
		propstaticedge,//��������� �����
		propwindowedge,//�������� �����
		proptransparent,//���������� ����
		propacceptfiles;//��������� ����� ����� Drag&Drop
	bool propdoublebuf;//������� �����������
	COLORREF propbkcolor;//���� ����
	//�������
	TINYEvent oncreate,//��� ��������
		ondestroy,//��� �����������
		onsize,//��� �������
		onpaint,//��� ���������
		onmousemove,//��� �������� ����
		onlbtndown,//��� ������� ����� ������
		onlbtnup,//��� ���������� ���� ������
		ontimer;//��� ������������ �������
	//����� �������
	TINYEventMap onmessage,//����� ���������
		oncommand,//����� ������
		onmenu,//����� ������ ����
		onacc,//����� ������ �������������
		onnotify;//����� �����������
	//������� ��� ��������� ��������� ��������� � ���������
	TINYEvent _oncustommsg,//��� ������� ���������
		_oncustomcmd,//��� ������� �������
		_oncustomntf;//��� �������  �����������
public:
	HWND GetHWND();//�������� HWND ����
	HACCEL GetAccel();//�������� �����������
	bool SetAccel(HACCEL acc);//���������� �����������
	//�������� ����
	bool Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		HICON icon,HCURSOR cursor,DWORD exstyle,DWORD style,UINT wndstyle,
		int x,int y,int w,int h);
	bool Attach(HWND hwnd);//������� � HWND
	bool IsCtrl();//���� ����� ������������ �� TINYControl ����������� true, ����� false

	//������� ����
	bool Destroy();//���������� ����
	bool Show(int ncmd);//�������� ����
	bool Update();//�������� ������� ���������� �������
	//�������� ����
	bool Redraw(UINT flags);
	bool Redraw(RECT *uprect,//������� ��� ����������
		HRGN uprgn,//������ ��� ����������
		UINT flags);
	bool SetText(TINYStr text);//���������� ����� ����
	TINYStr GetText();//�������� ����� ����
	int GetTextLen();//�������� ����� ������ ����
	TINYBaseWnd* GetParent();//�������� ��������� �� ����� ������������� ����
	bool SetParent(TINYBaseWnd* parent);//���������� ������������ ����
	TINYStr GetClassName();//�������� �������� ������

	//������� ��� ������ �� �������
	bool AddStyle(DWORD style);//�������� �����
	bool DelStyle(DWORD style);//������� �����
	bool AddExStyle(DWORD style);//�������� ���������� �����
	bool DelExStyle(DWORD style);//������� ���������� �����
	bool SetStyle(DWORD style);//���������� �����
	DWORD GetStyle();//�������� �����
	bool SetExStyle(DWORD style);//���������� ���������� �����
	DWORD GetExStyle();//�������� ���������� �����

	//������� ��� ������ � �������
	bool SetIcon(TINYIcon icon);//���������� ������� ������
	bool SetSmallIcon(TINYIcon icon);//���������� ������� ������
	TINYIcon GetIcon();//�������� ������� ������
	TINYIcon GetSmallIcon();//�������� ��������� ������

	//������� ��� ������ � ���������� � ��������� ����
	TINYRect GetRect();//�������� ������� ����
	TINYRect GetClientRect();//�������� ���������� ������� ����
	bool SetSize(int w,int h);//���������� ������� ����
	bool SetW(int w);//���������� ������
	bool SetH(int h);//���������� ������
	int GetW();//�������� ������
	int GetH();//�������� ������
	bool Move(int x,int y);	//����������� ����
	bool SetX(int x);//���������� X
	bool SetY(int y);//���������� Y
	int GetX();//�������� �
	int GetY();//�������� Y

	//��� ������������ ������� ���� �������� ��������� WM_TIMER
	bool StartTimer(UINT id,UINT time);//��������� ������
	bool StopTimer(UINT id);//���������� ������

	bool Top();//�� �������� ����
	bool Bottom();//�� ������ ����
	bool SetZOrder(TINYBaseWnd* wndafter);//���������� z-���������

public:
	operator HWND();

protected:
	//������� �������
	static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
	//������� ��������� ���������
	LRESULT _OnMessage(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);

};

TINYBaseWnd* TinyGetPointer(HWND hwnd);//�������� TINYBaseWnd* �� HWND

};