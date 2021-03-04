#include <windows.h>
#include <doublebuffer.h> 
#include <stdio.h>

#include "ctrlmanager.h"
#include "ctrl.h"

LRESULT CALLBACK MainWndProc(HWND,UINT,WPARAM,LPARAM);

HWND mainWnd;
RECT mainRect;
HINSTANCE g_hInst;
LPSTR mainWndClass="mainWndClass";

CtrlManager cm;
SigninCtrls sic;
SignupCtrls suc;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)MainWndProc;
	WndClass.lpszClassName=mainWndClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	AllocConsole();
	freopen("COIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	hWnd=CreateWindow(mainWndClass,mainWndClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,500,500,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	FreeConsole();

	return Message.wParam;
}
	void DrawMainWnd(HDC dbDC,RECT rt){
		TextOut(dbDC,10,10,"hello",5);
	}
LRESULT CALLBACK MainWndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch(iMessage) {
		case WM_CREATE:
			//Create ctrl manager
			InitCtrlManager(&cm,&mainRect);
			//
			
			CreateCtrlFont();
			
			mainWnd=hWnd;
			//Create ctrl groups
			CreateSigninCtrls(&sic,hWnd,g_hInst);
			CreateSignupCtrls(&suc,hWnd,g_hInst);
			//
			
			//Regist ctrl groups
			RegistCtrlGroup(&cm,&sic,CTRL_SIGNINCTRLS,sizeof(SigninCtrls),MoveSigninCtrls);
			RegistCtrlGroup(&cm,&suc,CTRL_SIGNUPCTRLS,sizeof(SignupCtrls),MoveSignupCtrls);
			//
			
			//Set first ctrl group
			SetNowCtrlGroup(&cm,CTRL_SIGNINCTRLS);
			//
			
			SendMessage(hWnd,WM_SIZE,0,0);
			return 0;
		case WM_SIZE:
			if(wParam!=SIZE_MINIMIZED){
				GetClientRect(hWnd,&mainRect);
				CallMoveFunc(cm,mainRect);
			}
			return 0;
		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
				DoubleBuffer(hdc,mainRect,DrawMainWnd);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_COMMAND:
			switch(wParam){
				case CTRL_SIGNIN_BT_SIGNUP:
					ChangeCtrlGroup(&cm,CTRL_SIGNUPCTRLS);
					break;
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
