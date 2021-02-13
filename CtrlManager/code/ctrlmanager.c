#include "ctrlmanager.h"

#include <windows.h>

HWND *nowCtrls=0;

char MoveCtrls(RECT rt){
	void (*MoveFunc)(void *,RECT)=0;
	if(nowCtrls!=0){
		MoveFunc=(void(*)(void*,RECT))(*nowCtrls);
		MoveFunc(nowCtrls,rt);
		return 1;
	}
	return 0;
}
void ShowCtrls(void *ctrls){
	int i;
	HWND *c=(HWND *)ctrls;
	long long ctrlCount=(long long)*(c+1);
	for(i=2;i<ctrlCount+2;i++){
		ShowWindow(c[i],SW_SHOW);
	}
}
void HideCtrls(void *ctrls){
	int i;
	HWND *c=(HWND *)ctrls;
	long long ctrlCount=(long long)*(c+1);
	for(i=2;i<ctrlCount+2;i++){
		ShowWindow(c[i],SW_HIDE);
	}
}
void ChangeCtrls(void *pNewCtrls,RECT rt){
	HWND *newCtrls=(HWND *)pNewCtrls;
	HideCtrls(nowCtrls);
	ShowCtrls(newCtrls);
	nowCtrls=newCtrls;
	MoveCtrls(rt);
}
void InitCtrlManager(void *pNowCtrls){
	nowCtrls=pNowCtrls;
	ShowCtrls(nowCtrls);
}
void DestroyCtrls(void *ctrls){
	int i;
	HWND *c=(HWND *)ctrls;
	long long ctrlCount=(long long)*(c+1);
	for(i=2;i<ctrlCount+2;i++){
		DestroyWindow(c[i]);
	}
}
