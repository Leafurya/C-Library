#ifndef _ctrlmanager__h_
#define _ctrlmanager__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <windows.h>

void ChangeCtrls(void *pNewCtrls,RECT rt);
void InitCtrlManager(void *pNowCtrls);
void ShowCtrls(void *ctrls);
void HideCtrls(void *ctrls);
char MoveCtrls(RECT rt);
void DestroyCtrls(void *ctrls);

#ifdef __cplusplus
}
#endif
#endif
