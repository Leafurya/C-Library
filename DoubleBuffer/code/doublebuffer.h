#ifndef _doublebuffer__h_
#define _doublebuffer__h_

#include <windows.h>

void DoubleBuffer(HDC hdc,RECT rt,void *(DrawFunc)(HDC,RECT));

#endif
