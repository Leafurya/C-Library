#include "ctrlmanager.h"
#include <stdlib.h>

void InitCtrlManager(CtrlManager *cm,RECT *rt){
	cm->ctrlGroups=NULL;
	cm->ctrlGroupCount=0;
	cm->nowGroup=NULL;
	cm->rect=rt;
}
void RegistCtrlGroup(CtrlManager *cm,void *ctrlGroup,int groupId,int size,void (*MoveFunc)(void *,RECT)){
	int *cgc=&cm->ctrlGroupCount;
	
	if(cm->ctrlGroups!=NULL){
		cm->ctrlGroups=(CtrlGroup *)realloc(cm->ctrlGroups,sizeof(CtrlGroup)*(*cgc+1));
	}
	else{
		cm->ctrlGroups=(CtrlGroup *)malloc(sizeof(CtrlGroup));
	}
	
	cm->ctrlGroups[*cgc].groupId=groupId;
	cm->ctrlGroups[*cgc].ctrlCount=(size/sizeof(HWND));
	cm->ctrlGroups[*cgc].ctrls=(HWND *)ctrlGroup;
	cm->ctrlGroups[*cgc].MoveFunc=MoveFunc;
	
	*cgc+=1;
}
char ChangeCtrlGroup(CtrlManager *cm,int groupId){
	CtrlGroup *newCtrlGroup;
	
	if(cm->nowGroup!=0){
		newCtrlGroup=GetCtrlGroupById(*cm,groupId);
		if(newCtrlGroup!=0){
			HideCtrlGroup(*cm->nowGroup);
			ShowCtrlGroup(*newCtrlGroup);
			newCtrlGroup->MoveFunc(newCtrlGroup->ctrls,*cm->rect);
			cm->nowGroup=newCtrlGroup;
			return 0;
		}
	}
	return -1;
}
void ShowCtrlGroup(CtrlGroup cg){
	int i;
	for(i=0;i<cg.ctrlCount;i++){
		ShowWindow(cg.ctrls[i],SW_SHOW);
	}
}
void HideCtrlGroup(CtrlGroup cg){
	int i;
	
	for(i=0;i<cg.ctrlCount;i++){
		ShowWindow(cg.ctrls[i],SW_HIDE);
	}
}
CtrlGroup *GetCtrlGroupById(CtrlManager cm,int groupId){
	int i;
	CtrlGroup *cg=0;
	
	for(i=0;i<cm.ctrlGroupCount;i++){
		if(cm.ctrlGroups[i].groupId==groupId){
			cg=&cm.ctrlGroups[i];
			break;
		}
	}
	return cg;
}
char CallMoveFunc(CtrlManager cm,RECT rt){
	if(cm.nowGroup!=0){
		cm.nowGroup->MoveFunc(cm.nowGroup->ctrls,rt);
		return 0;
	}
	return -1;
}
void DestroyCtrlManager(CtrlManager *cm){
	int i,j;
	
	for(i=0;i<cm->ctrlGroupCount;i++){
		for(j=0;j<cm->ctrlGroups[i].ctrlCount;j++){
			DestroyWindow(cm->ctrlGroups[i].ctrls[j]);
		}
	}
	free(cm->ctrlGroups);
}
void SetNowCtrlGroup(CtrlManager *cm,int id){
	cm->nowGroup=GetCtrlGroupById(*cm,id);
	ShowCtrlGroup(*cm->nowGroup);
}
