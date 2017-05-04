#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define WinW 400
#define WinH 200
#define edit1 1
#define btn1 2



HINSTANCE DllInjectinst;

HWND parent;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

void initControl(HWND, UINT, WPARAM, LPARAM);
int CALLBACK EnumFontFamProc(ENUMLOGFONT,NEWTEXTMETRIC,DWORD,LPARAM);



#endif // MAIN_H_INCLUDED
