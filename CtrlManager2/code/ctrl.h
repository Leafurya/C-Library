#ifndef _ctrls__h_
#define _ctrls__h_

#include <windows.h>

void CreateCtrlFont();

#define CTRL_SIGNINCTRLS	1

#define CTRL_SIGNIN_BT_CONFIRM	100
#define CTRL_SIGNIN_BT_SIGNUP	101
#define CTRL_SIGNIN_ED_ID		102
#define CTRL_SIGNIN_ED_PWD		103

typedef struct _signinctrls{
	HWND btConfirm;
	HWND btSignup;
	HWND edId;
	HWND edPwd;
	HWND stId;
	HWND stPwd;
}SigninCtrls;

void CreateSigninCtrls(void *c,HWND hWnd,HINSTANCE hInst);
void MoveSigninCtrls(void *c,RECT rect);

#define CTRL_SIGNUPCTRLS		2

#define CTRL_SIGNUP_BT_CONFIRM	200
#define CTRL_SIGNUP_BT_CANCEL	201
#define CTRL_SIGNUP_ED_ID		202
#define CTRL_SIGNUP_ED_PWD		203
#define CTRL_SIGNUP_ED_REPWD	204
#define CTRL_SIGNUP_BT_IDCHECK	205

typedef struct _signupctrls{
	HWND btConfirm;
	HWND btCancel;
	HWND edId;
	HWND edPwd;
	HWND edRepwd;
	HWND btIdcheck;
	HWND stId;
	HWND stPwd;
	HWND stRepwd;
}SignupCtrls;

void CreateSignupCtrls(void *c,HWND hWnd,HINSTANCE hInst);
void MoveSignupCtrls(void *c,RECT rect);

#endif

