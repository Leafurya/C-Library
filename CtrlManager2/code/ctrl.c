#define ORIGINAL
#include "ctrl.h"

int fontSize=12;
char *fontName=(char *)"굴림";
HFONT font;

void CreateCtrlFont(){
	font=CreateFont(fontSize,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,fontName);
}
	
	void SetFontEach(HWND c,HFONT font){
		SendMessage(c,WM_SETFONT,(WPARAM)font,MAKELPARAM(TRUE,0));
	}
	void SetFontAll(HWND *c,int size,HFONT font){
		int i;
		int count=size/sizeof(HWND);
		for(i=0;i<count;i++){
			SendMessage(c[i],WM_SETFONT,(WPARAM)font,MAKELPARAM(TRUE,0));
		}
	}

void CreateSigninCtrls(void *ctrls,HWND hWnd,HINSTANCE hInst){
	SigninCtrls *c=(SigninCtrls *)ctrls;
	
	c->btConfirm=CreateWindow("button","확인",WS_CHILD|WS_BORDER,0,0,0,0,hWnd,(HMENU)CTRL_SIGNIN_BT_CONFIRM,hInst,NULL);
	c->btSignup=CreateWindow("button","회원가입",WS_CHILD|WS_BORDER,0,0,0,0,hWnd,(HMENU)CTRL_SIGNIN_BT_SIGNUP,hInst,NULL);
	
	c->edId=CreateWindow("edit",NULL,WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,0,0,0,0,hWnd,(HMENU)CTRL_SIGNIN_ED_ID,hInst,NULL);
	c->edPwd=CreateWindow("edit",NULL,WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|ES_PASSWORD,0,0,0,0,hWnd,(HMENU)CTRL_SIGNIN_ED_PWD,hInst,NULL);
	
	c->stId=CreateWindow("static","아이디:",WS_CHILD|SS_CENTER,0,0,0,0,hWnd,(HMENU)0,hInst,NULL);
	c->stPwd=CreateWindow("static","비밀번호:",WS_CHILD|SS_CENTER,0,0,0,0,hWnd,(HMENU)0,hInst,NULL);
	
	SetFontAll((HWND *)c,sizeof(SigninCtrls),font);
}
void MoveSigninCtrls(void *ctrls,RECT rect){
	SigninCtrls *c=(SigninCtrls *)ctrls;
	int btW=70,btH=30,edW=100,edH=20,stH=fontSize+2;
	int margin=10;
	
	MoveWindow(c->btConfirm,10,10,btW,btH,TRUE);
	MoveWindow(c->btSignup,10,btH+margin+10,btW,btH,TRUE);
	
	MoveWindow(c->stId,(rect.right/2)-(edW/2)-50,(rect.bottom/2)-(margin/2+edH/2+stH/2),50,stH,TRUE);
	MoveWindow(c->edId,(rect.right/2)-(edW/2),(rect.bottom/2)-(margin/2+edH),edW,edH,TRUE);
	
	MoveWindow(c->stPwd,(rect.right/2)-(edW/2)-62,(rect.bottom/2)+(margin/2+edH/2-stH/2),62,stH,TRUE);
	MoveWindow(c->edPwd,(rect.right/2)-(edW/2),(rect.bottom/2)+(margin/2),edW,edH,TRUE);
}

void CreateSignupCtrls(void *ctrls,HWND hWnd,HINSTANCE hInst){
	SignupCtrls *c=(SignupCtrls *)ctrls;
	
	c->btConfirm=CreateWindow("button","확인",WS_CHILD|WS_BORDER,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_BT_CONFIRM,hInst,NULL);
	c->btCancel=CreateWindow("button","취소",WS_CHILD|WS_BORDER,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_BT_CANCEL,hInst,NULL);
	
	c->edId=CreateWindow("edit",NULL,WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_ED_ID,hInst,NULL);
	c->edPwd=CreateWindow("edit",NULL,WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|ES_PASSWORD,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_ED_PWD,hInst,NULL);
	c->edRepwd=CreateWindow("edit",NULL,WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|ES_PASSWORD,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_ED_REPWD,hInst,NULL);
	
	c->btIdcheck=CreateWindow("button","아이디 중복확인",WS_CHILD|WS_VISIBLE|WS_BORDER,0,0,0,0,hWnd,(HMENU)CTRL_SIGNUP_BT_IDCHECK,hInst,NULL);
	
	c->stId=CreateWindow("static","아이디:",WS_CHILD|SS_CENTER,0,0,0,0,hWnd,(HMENU)0,hInst,NULL);
	c->stPwd=CreateWindow("static","비밀번호:",WS_CHILD|SS_CENTER,0,0,0,0,hWnd,(HMENU)0,hInst,NULL);
	c->stRepwd=CreateWindow("static","비밀번호 확인:",WS_CHILD|SS_CENTER,0,0,0,0,hWnd,(HMENU)0,hInst,NULL);
	
	SetFontAll((HWND *)c,sizeof(SignupCtrls),font);
}
void MoveSignupCtrls(void *ctrls,RECT rect){
	SignupCtrls *c=(SignupCtrls *)ctrls;
	int btW=70;
	int btH=30;
	int edW=100;
	int edH=20;
	int stH=fontSize+2;
	int margin=10;
	
	MoveWindow(c->btConfirm,10,10,btW,btH,TRUE);
	MoveWindow(c->btCancel,10,btH+margin+10,btW,btH,TRUE);
	MoveWindow(c->btIdcheck,10,btH+margin+10,btW,btH,TRUE);
	
	MoveWindow(c->stId,(rect.right/2)-(edW/2)-50,(rect.bottom/2)-(edH+margin+(stH/2)),50,stH,TRUE);
	MoveWindow(c->edId,(rect.right/2)-(edW/2),(rect.bottom/2)-((edH/2)+margin+edH),edW,edH,TRUE);
	MoveWindow(c->btIdcheck,(rect.right/2)+((edW/2)+margin),(rect.bottom/2)-((edH/2)+margin+edH),100,edH,TRUE);
	
	MoveWindow(c->stPwd,(rect.right/2)-(edW/2)-62,(rect.bottom/2)-(stH/2),62,stH,TRUE);
	MoveWindow(c->edPwd,(rect.right/2)-(edW/2),(rect.bottom/2)-(edH/2),edW,edH,TRUE);
	
	MoveWindow(c->stRepwd,(rect.right/2)-(edW/2)-90,(rect.bottom/2)+(edH+margin-(stH/2)),90,stH,TRUE);
	MoveWindow(c->edRepwd,(rect.right/2)-(edW/2),(rect.bottom/2)+((edH/2)+margin),edW,edH,TRUE);
}
