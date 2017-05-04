#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include"main.h"

TCHAR szClassName[ ] = _T("Win");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    DllInjectinst = hThisInstance;
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = CreateSolidBrush(RGB(255,255,255));

    if (!RegisterClassEx (&wincl))
        return 0;

    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    parent = CreateWindowEx (
           0,
           szClassName,
           _T("DllInjection"),
           WS_OVERLAPPEDWINDOW &~ WS_MAXIMIZEBOX &~ WS_SIZEBOX, /* default window */
           (x-WinW)/2,       /* Windows decides the position */
           (y-WinH)/2,       /* where the window ends up on the screen */
           WinW,                 /* The programs width */
           WinH,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    ShowWindow (parent, nCmdShow);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}



LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            initControl(hwnd,message,wParam,lParam);
            break;
        case WM_COMMAND:
            switch(HIWORD(wParam))
            {
                case BN_CLICKED:
                    switch(LOWORD(wParam))
                    {
                        case btn1:
                            OPENFILENAME ofn;      // 公共对话框结构。
                            TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。
                            // 初始化选择文件对话框。
                            ZeroMemory(&ofn, sizeof(OPENFILENAME));
                            ofn.lStructSize = sizeof(OPENFILENAME);
                            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_EXPLORER;
                            ofn.hInstance = DllInjectinst;
                            ofn.hwndOwner = hwnd;
                            ofn.lpstrFile = szFile;
                            ofn.lpstrFile[0] = '\0';
                            ofn.nMaxFile = sizeof(szFile);
                            ofn.lpstrFilter = "Dll(*.dll)\0*.dll\0All(*.*)\0*.*\0\0";
                            ofn.nFilterIndex = 1;
                            ofn.lpstrFileTitle = NULL;
                            ofn.lpstrTitle = "选择动态链接库";
                            ofn.nMaxFileTitle = 0;
                            ofn.lpstrInitialDir = NULL;
                            //ofn.lpTemplateName =  MAKEINTRESOURCE(ID_TEMP_DIALOG);
                            if(GetOpenFileName(&ofn))
                            {
                                HWND edit = GetDlgItem(hwnd,edit1);
                                SetWindowText(edit,szFile);

                            }
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void initControl(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    HWND edit = CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|ES_AUTOHSCROLL|ES_READONLY,10,10,300,30,hwnd,(HMENU)edit1,DllInjectinst,NULL);
    HWND btn = CreateWindow("BUTTON","open",WS_CHILD|WS_VISIBLE|BS_FLAT,325,10,60,30,hwnd,(HMENU)btn1,DllInjectinst,NULL);
    RECT rect;
    GetClientRect(edit,&rect);
    OffsetRect(&rect,6,4);
    SendMessage(edit,EM_SETRECT,0,(LPARAM)&rect);
}


