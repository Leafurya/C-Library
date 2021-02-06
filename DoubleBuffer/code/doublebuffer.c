#include "doublebuffer.h"

typedef struct buffer_{
	HDC MemDC;
	HBITMAP bit,oldbit;
}MEMBUF;

	void MInitMem(MEMBUF *bfm,HDC hdc,RECT rt){
		bfm->MemDC=CreateCompatibleDC(hdc);
		bfm->bit=CreateCompatibleBitmap(hdc,rt.right,rt.bottom);
		bfm->oldbit=SelectObject(bfm->MemDC,bfm->bit);
	}
	void MShowDeleteMem(MEMBUF *bfm,HDC hdc,RECT rt){
		BitBlt(hdc,0,0,rt.right,rt.bottom,bfm->MemDC,0,0,SRCCOPY);
		DeleteObject(SelectObject(bfm->MemDC,bfm->oldbit));
		DeleteDC(bfm->MemDC);
	}
void DoubleBuffer(HDC hdc,RECT rt,void *(DrawFunc)(HDC,RECT)){
	MEMBUF bfm;
	
	MInitMem(&bfm,hdc,rt);
	
	DrawFunc(bfm.MemDC,rt);
	
	MShowDeleteMem(&bfm,hdc,rt);
}


