//------------------------------------
//tiny 2.5
//tinybasewnd.cpp - ������� ����� ����
//� 2009-2010 Stepan Prokofjev
//------------------------------------

#include "tinybasewnd.h"

using namespace tiny;

TINYBaseWnd::TINYBaseWnd()
{
	//������������� �������
	proptext.Init(this,&TINYBaseWnd::SetText,&TINYBaseWnd::GetText);
	propx.Init(this,&TINYBaseWnd::SetX,&TINYBaseWnd::GetX);
	propy.Init(this,&TINYBaseWnd::SetY,&TINYBaseWnd::GetY);
	propw.Init(this,&TINYBaseWnd::SetW,&TINYBaseWnd::GetW);
	proph.Init(this,&TINYBaseWnd::SetH,&TINYBaseWnd::GetH);
	propicon.Init(this,&TINYBaseWnd::SetIcon,&TINYBaseWnd::GetIcon);
	propsmicon.Init(this,&TINYBaseWnd::SetSmallIcon,&TINYBaseWnd::GetSmallIcon);
	//�����
	proptabstop.Init(this,WS_TABSTOP,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propvscroll.Init(this,WS_VSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	prophscroll.Init(this,WS_HSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propclientedge.Init(this,WS_EX_CLIENTEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propstaticedge.Init(this,WS_EX_STATICEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propwindowedge.Init(this,WS_EX_WINDOWEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	proptransparent.Init(this,WS_EX_TRANSPARENT,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propacceptfiles.Init(this,WS_EX_ACCEPTFILES,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	//����������� ���� ����
	propbkcolor=GetSysColor(COLOR_BTNFACE);

	_isctrl=false;//�� ������������ �� TINYControl
}

//�������� HWND ����
HWND TINYBaseWnd::GetHWND() {return _hwnd;}
//�������� �����������
HACCEL TINYBaseWnd::GetAccel() {return _acc;}
//���������� �����������
bool TINYBaseWnd::SetAccel(HACCEL acc)
{
	if(!acc) return false;
	_acc=acc;
	return true;
}
//�������� ����
bool TINYBaseWnd::Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
				HICON icon,HCURSOR cursor,DWORD exstyle,DWORD style,UINT wndstyle,
				int x,int y,int w,int h)
{
	WNDCLASSEX wndc;
	wndc.lpszClassName=classname;//�������� ������
	wndc.cbSize=sizeof(WNDCLASSEX);
	wndc.lpfnWndProc=WNDPROC(_WndProc);//������� ���������
	wndc.cbClsExtra=0;
	wndc.cbWndExtra=0;
	wndc.hbrBackground=0;
	wndc.hInstance=GetModuleHandle(0);
	wndc.hCursor=cursor;//������
	wndc.style=wndstyle;//����� ����
	//��������� ������
	wndc.hIcon=icon;
	wndc.hIconSm=0;
	//��������� ����
	wndc.lpszMenuName=0;
	//����������� ������ ����
	RegisterClassEx(&wndc);
	//�������� ��������� �� ����� ������������� ����
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	//�������� ����
	_hwnd=CreateWindowEx(exstyle,classname,text,
	style|WS_CLIPCHILDREN,x,y,w,h,
	hparent,0,GetModuleHandle(0),
	this/*�������� ��������� �� ��������� ������ � ������� �������*/);
	if(!_hwnd) return false;
	return true;
}
//������� � HWND
bool TINYBaseWnd::Attach(HWND hwnd)
{
	if(!hwnd) return false;
	_hwnd=hwnd;
	//���������� ��������� �� ��������� ������
	SetWindowLong(_hwnd,GWL_USERDATA,LONG(this));
	return true;
}
//���� ����� ������������ �� TINYControl ����������� true, ����� false
bool TINYBaseWnd::IsCtrl() {return _isctrl;}

//������� ����
//���������� ����
bool TINYBaseWnd::Destroy()
{
	if(!DestroyWindow(_hwnd)) return false;
	return true;
}
//�������� ����
bool TINYBaseWnd::Show(int ncmd)
{
	if(!ShowWindow(_hwnd,ncmd)) return false;
	return true;
}
//�������� ������� ���������� �������
bool TINYBaseWnd::Update()
{
	if(!UpdateWindow(_hwnd)) return false;
	return true;
}
//�������� ����
bool TINYBaseWnd::Redraw(UINT flags)
{
	return Redraw(0,0,flags);
}
bool TINYBaseWnd::Redraw(RECT *uprect,//������� ��� ����������
		HRGN uprgn,//������ ��� ����������
		UINT flags)
{
	if(!RedrawWindow(_hwnd,uprect,uprgn,flags)) return false;
	return true;
}
//���������� ����� ����
bool TINYBaseWnd::SetText(TINYStr text)
{
	if(!SetWindowText(_hwnd,text)) return false;
	return true;
}
//�������� ����� ����
TINYStr TINYBaseWnd::GetText()
{
	wchar_t *text=new wchar_t[GetTextLen()+1];
	GetWindowText(_hwnd,text,GetTextLen()+1);
	TINYStr str=text;
	delete[] text;
	return str;
}
//�������� ����� ������ ����
int TINYBaseWnd::GetTextLen()
{
	return GetWindowTextLength(_hwnd);	
}
//�������� ��������� �� ����� ������������� ����
TINYBaseWnd* TINYBaseWnd::GetParent()
{
	return TinyGetPointer(::GetParent(_hwnd));
}
//���������� ������������ ����
bool TINYBaseWnd::SetParent(TINYBaseWnd* parent)
{
	HWND hparent;
	if(!parent) hparent=0;
	else hparent=parent->GetHWND();
	if(!::SetParent(_hwnd,hparent)) return false;
	return true;
}
//�������� �������� ������
TINYStr TINYBaseWnd::GetClassName()
{
	wchar_t* text=new wchar_t[MAX_PATH];
	//�������� �������� ������
	::GetClassName(_hwnd,text,MAX_PATH);
	TINYStr str=text;
	delete[] text;
	return str;
}

//������� ��� ������ �� �������
//�������� �����
bool TINYBaseWnd::AddStyle(DWORD style)
{
	return SetStyle(GetStyle()|style);
}
//������� �����
bool TINYBaseWnd::DelStyle(DWORD style)
{
	return SetStyle(GetStyle()&~style);
}
//�������� ���������� �����
bool TINYBaseWnd::AddExStyle(DWORD style)
{
	return SetExStyle(GetExStyle()|style);
}
//������� ���������� �����
bool TINYBaseWnd::DelExStyle(DWORD style)
{
	return SetExStyle(GetExStyle()&~style);
}
//���������� �����
bool TINYBaseWnd::SetStyle(DWORD style)
{
	if(!SetWindowLong(_hwnd,GWL_STYLE,style)) return false;
	return true;
}
//�������� �����
DWORD TINYBaseWnd::GetStyle()
{
	return GetWindowLong(_hwnd,GWL_STYLE);
}
//���������� ���������� �����
bool TINYBaseWnd::SetExStyle(DWORD style)
{
	if(!SetWindowLong(_hwnd,GWL_EXSTYLE,style)) return false;
	return true;
}
//�������� ���������� �����
DWORD TINYBaseWnd::GetExStyle()
{
	return GetWindowLong(_hwnd,GWL_EXSTYLE);
}

//������� ��� ������ � �������
//���������� ������� ������
bool TINYBaseWnd::SetIcon(TINYIcon icon)
{
	//������������� ������� ������
	SendMessage(_hwnd,WM_SETICON,ICON_BIG,LPARAM(icon.GetHICON()));
	return true;
}
//���������� ��������� ������
bool TINYBaseWnd::SetSmallIcon(TINYIcon icon)
{
	//������������� ��������� ������
	SendMessage(_hwnd,WM_SETICON,ICON_SMALL,LPARAM(icon.GetHICON()));
	return true;
}
//�������� ������� ������
TINYIcon TINYBaseWnd::GetIcon()
{
	//��������� ������
	HICON hicon=HICON(SendMessage(_hwnd,WM_GETICON,ICON_BIG,0));
	//���� ������ ���, �� ��������� ������ �� ������ ����
	if(!hicon)
	{
		//��������� ���������� � ������
		WNDCLASSEX wndc;
		GetClassInfoEx(GetModuleHandle(0),GetClassName(),&wndc);
		//��������� ������
		hicon=wndc.hIcon;
	}
	TINYIcon icon;
	icon.Attach(hicon);
	return icon;
}
//�������� ��������� ������
TINYIcon TINYBaseWnd::GetSmallIcon()
{
	//��������� ������
	HICON hicon=HICON(SendMessage(_hwnd,WM_GETICON,ICON_SMALL,0));
	//���� ������ ���, �� ��������� ������ �� ������ ����
	if(!hicon)
	{
		//��������� ���������� � ������
		WNDCLASSEX wndc;
		GetClassInfoEx(GetModuleHandle(0),GetClassName(),&wndc);
		//��������� ������
		hicon=wndc.hIconSm;
	}
	TINYIcon icon;
	icon.Attach(hicon);
	return icon;
}

//������� ��� ������ � ���������� � ��������� ����
//�������� ������� ����
TINYRect TINYBaseWnd::GetRect()
{
	return TINYRect(GetX(),GetY(),GetW(),GetH());
}
//�������� ���������� ������� ����
TINYRect TINYBaseWnd::GetClientRect()
{
	RECT rect;
	::GetClientRect(_hwnd,&rect);
	return rect;
}
//���������� ������� ����
bool TINYBaseWnd::SetSize(int w,int h)
{
	if(!SetWindowPos(_hwnd,0,0,0,w,h,
		SWP_NOMOVE|SWP_NOZORDER)) return false;
	return true;
}
//���������� ������
bool TINYBaseWnd::SetW(int w)
{
	return SetSize(w,GetH());
}
//���������� ������
bool TINYBaseWnd::SetH(int h)
{
	return SetSize(GetW(),h);
}
//�������� ������
int TINYBaseWnd::GetW()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	return rect.right-rect.left;
}
//�������� ������
int TINYBaseWnd::GetH()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	return rect.bottom-rect.top;
}
//����������� ����
bool TINYBaseWnd::Move(int x,int y)
{
	if(!SetWindowPos(_hwnd,0,x,y,0,0,
		SWP_NOSIZE|SWP_NOZORDER)) return false;
	return true;
}
//���������� X
bool TINYBaseWnd::SetX(int x)
{
	return Move(x,GetY());
}
//���������� Y
bool TINYBaseWnd::SetY(int y)
{
	return Move(GetX(),y);
}
//�������� �
int TINYBaseWnd::GetX()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	//���� � ���� ���� ��������,
	//�� ������������� ����������
	TINYBaseWnd* parent=GetParent();
	if(parent)
	{
		POINT point;
		point.x=rect.left;
		point.y=rect.top;
		ScreenToClient(parent->GetHWND(),&point);	
		return point.x;
	}
	return rect.left;
}
//�������� Y
int TINYBaseWnd::GetY()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	//���� � ���� ���� ��������,
	//�� ������������� ����������
	TINYBaseWnd* parent=GetParent();
	if(parent)
	{
		POINT point;
		point.x=rect.left;
		point.y=rect.top;
		ScreenToClient(parent->GetHWND(),&point);	
		return point.y;
	}
	return rect.top;
}

//��� ������������ ������� ���� �������� ��������� WM_TIMER
//��������� ������
bool TINYBaseWnd::StartTimer(UINT id,UINT time)
{
	if(!SetTimer(_hwnd,id,time,0)) return false;
	return true;
}
//���������� ������
bool TINYBaseWnd::StopTimer(UINT id)
{
	if(!KillTimer(_hwnd,id)) return false;
	return true;
}
//�� �������� ����
bool TINYBaseWnd::Top()
{
	if(!SetWindowPos(_hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}
//�� ������ ����
bool TINYBaseWnd::Bottom()
{
	if(!SetWindowPos(_hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}
//���������� z-���������
bool TINYBaseWnd::SetZOrder(TINYBaseWnd* wndafter)
{
	if(!wndafter) return false;
	if(!SetWindowPos(_hwnd,wndafter->GetHWND(),
		0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}

TINYBaseWnd::operator HWND() {return GetHWND();}

//������� �������
LRESULT CALLBACK TINYBaseWnd::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	TINYBaseWnd *wnd=0;
	if(message==WM_NCCREATE)
	{
		//��������� ��������� �� ��������� ������ �� LPCREATESTRUCT
		wnd=(TINYBaseWnd*)LPCREATESTRUCT(lparam)->lpCreateParams;
		if(wnd)
		{
			wnd->_hwnd=hwnd;//���������� HWND
			//���������� ��������� �� ��������� ������ � GWL_USERDATA ����
			SetWindowLong(hwnd,GWL_USERDATA,LONG(wnd));
			//������ ������� ��������� ���������
			wnd->_OnMessage(wnd,message,wparam,lparam);
		}
	}
	//��������� ��������� �� ��������� ������ �� GWL_USERDATA
	wnd=TinyGetPointer(hwnd);
	if(wnd)//�������� ���������
	{
		//������ ������� ��������� ���������
		LRESULT result=wnd->_OnMessage(wnd,message,wparam,lparam);
		//���� result �� ����� 0 �� ������� result
		if(result) return result;
	}
	return DefWindowProc(hwnd,message,wparam,lparam);
}

//������� ��������� ���������
LRESULT TINYBaseWnd::_OnMessage(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//��������� ���������
	TINYMSGPARAMS msg;
	msg.code=message;
	msg.wparam=wparam;
	msg.lparam=lparam;
	//������������ ��������
	LRESULT ret=0;

	//---------------------------
	//��������� reflect-���������
	//---------------------------
	TINYBaseWnd* rwnd=0;//��������� �� ����, �� �������� ������ reflect-���������
	switch(message)
	{
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
	case WM_VKEYTOITEM:
	case WM_CHARTOITEM:
	case WM_HSCROLL:
	case WM_VSCROLL:
		//�������� ��������� �� lparam
		rwnd=TinyGetPointer(HWND(lparam));
		break;
	case WM_DRAWITEM:
	case WM_MEASUREITEM:
	case WM_COMPAREITEM:
	case WM_DELETEITEM:
		//�������� ��������� �� id �� wparam
		if(wparam) rwnd=TinyGetPointer(GetDlgItem(*wnd,wparam));
		break;
	case WM_PARENTNOTIFY:
		//�������� ��������� �� lparam
		//���� wparam ����� WM_CREATE ��� WM_DESTROY
		if(LOWORD(wparam)==WM_CREATE||WM_DESTROY) rwnd=TinyGetPointer(HWND(lparam));
		break;
	}

	if(rwnd)
	{
		//����� ����������� ��������� ��������� ���������
		ret=rwnd->_oncustommsg(rwnd,TINYParams(&msg));
		//���� ������ �� 0, ������� ��������
		if(ret) return ret;

		//����� ����������� ��������� �� �����
		return rwnd->onmessage(rwnd,message,TINYParams(&msg));	
	}

	//����� ����������� ��������� ��������� ���������
	ret=_oncustommsg(wnd,TINYParams(&msg));
	//���� ������ �� 0, ������� ��������
	if(ret) return ret;

	//����� ����������� ��������� �� �����
	ret=onmessage(wnd,message,TINYParams(&msg));
	if(ret) return ret;

	//----------------------------
	//��������� �������� ���������
	//----------------------------
	switch(message)
	{
	case WM_CREATE:
		return oncreate(wnd,0);
	case WM_DESTROY:
		return ondestroy(wnd,0);
	case WM_SIZE:
		return onsize(wnd,TINYParams(&msg));
	case WM_PRINT:
	case WM_PAINT:
	{
		//-------------------
		//��������� ���������
		//-------------------

		//���� ���������� onpaint �� ����� - �� ������������
		if(!onpaint.IsConnected()) return 0;

		TINYDBDC dc;
		//���� � wparam ������ HDC, �� ����������� ��� � dc
		if(wparam) dc.Attach(HDC(wparam));
		//����� ������� BeginPaint
		else dc.BeginPaint(*wnd);

		LRESULT ret=0;//������������ ��������

		//���� ������� ���������� ��������
		if(propdoublebuf)
		{
			//�������� ������� �����������
			dc.InitDoubleBuffer();

			//������� ���������� onpaint
			ret=onpaint(wnd,TINYParams(dc.GetMemDC())/*��������� �� ������ ������*/);

			//���������� ������ �����		
			dc.DrawDoubleBuffer();
		}else{
			//���� �� ��������

			//������� ���������� onpaint
			ret=onpaint(wnd,TINYParams(&dc)/*�������� �� DC*/);
		}
		
		//���� ������ BeginPaint, ��������� ���������
		if(wparam) dc.EndPaint();
		//��������� DC
		else dc.Release(*this);

		return ret;
	}
	case WM_ERASEBKGND:
	{
		//���� ��� �������, �� ��� �� ���������
		if(wnd->IsCtrl()) return 0;

		//���� ���������� onpaint �����, �� �� ����������� ���
		if(onpaint.IsConnected()) return TRUE;

		TINYDC dc;
		//�������� DC
		dc.Attach(HDC(wparam));

		//��������� ��� ������ propbkcolor
		TINYBrush brush(propbkcolor);
		dc.FillRect(GetClientRect(),&brush);

		//�������
		dc.Release(*wnd);
		brush.Delete();
		return TRUE;
	}
	case WM_MOUSEMOVE:
		return onmousemove(wnd,0);
	case WM_LBUTTONDOWN:
		return onlbtndown(wnd,0);
	case WM_LBUTTONUP:
		return onlbtnup(wnd,0);
	case WM_TIMER:
		return ontimer(wnd,TINYParams(wparam));
	case WM_COMMAND:
	{
		//----------------
		//��������� ������
		//----------------

		UINT code=HIWORD(wparam);//��� �������
		UINT id=LOWORD(wparam);//Id ��������

		if(lparam==0)
		{
			//---------------------
			//��������� ������ ����
			//---------------------
			if(HIWORD(wparam)==0) onmenu(wnd,id,0);

			//------------------------------
			//��������� ������ �������������
			//------------------------------
			if(HIWORD(wparam)==1) onacc(wnd,id,0);

		}else{
			//--------------------------
			//��������� ��������� ������
			//--------------------------

			//��������� ��������� �� �������, �� �������� ������ �������
			TINYBaseWnd* ctrl=TinyGetPointer(HWND(lparam));

			if(ctrl)
			{
				//��������� �������
				TINYMSGPARAMS cmd;
				cmd.code=code;//��� �������
				cmd.wparam=0;
				cmd.lparam=0;

				//����� ����������� ��������� ��������� ������
				ctrl->_oncustomcmd(ctrl,TINYParams(&cmd));

				//����� ����������� ������� �� �����
				ctrl->oncommand(ctrl,code,0);
			}
		}		
		return 0;
	}
	case WM_NOTIFY:
	{
		//---------------------
		//��������� �����������
		//---------------------

		//��������� �� �������, �� �������� ������ �����������
		TINYBaseWnd* ctrl=TinyGetPointer(LPNMHDR(lparam)->hwndFrom);
		UINT code=LPNMHDR(lparam)->code;//��� �����������

		if(ctrl) 
		{
			//��������� �����������
			TINYMSGPARAMS ntf;
			ntf.code=code;//��� �����������
			ntf.wparam=0;
			ntf.lparam=lparam;

			//����� ����������� ��������� ��������� �����������
			ret=ctrl->_oncustomntf(ctrl,TINYParams(&ntf));
			if(ret) return ret;

			//����� ����������� ����������� �� �����
			return ctrl->onnotify(ctrl,code,TINYParams(lparam));
		}
	}
	}
	return 0;
}

//�������� TINYBaseWnd* �� HWND
TINYBaseWnd* tiny::TinyGetPointer(HWND hwnd)
{
	if(!hwnd) return 0;
	//��������� TINYBaseWnd* �� ���� UserData ����
	return (TINYBaseWnd*)GetWindowLong(hwnd,GWL_USERDATA);
}