/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：模仿文本编辑器
最后编译时间：
2018/10/03    模仿文本编辑器
*/

// Notebook.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Notebook.h"
using namespace std;

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hEditWnd;
HWND hWndMain;

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NOTEBOOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOTEBOOK));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(hWndMain, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTEBOOK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NOTEBOOK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass,
                            szTitle,
                            WS_OVERLAPPEDWINDOW,
                            0, 
                            0, 
                            800, 
                            600,
                            nullptr,
                            nullptr,
                            hInstance,
                            nullptr);
   hWndMain = hWnd;
   RECT rc;
   GetClientRect(hWnd, &rc);

   hEditWnd = CreateWindowA((LPCSTR)"Edit",
                           nullptr,
                           WS_CHILDWINDOW | WS_VISIBLE | WS_VSCROLL |
                           ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                           0,
                           0,
                           rc.right - rc.left,
                           rc.bottom - rc.top,
                           hWnd,
                           nullptr,//(HMENU)ID_EDITCHILD,
                           hInstance,
                           nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case ID_ACCSELECT:
            {
                int nLen = GetWindowTextLength(hEditWnd);
                SendMessageA(hEditWnd, EM_SETSEL, 0, nLen);
            }
                break;
            case ID_SAVE:
            {
                OPENFILENAMEA ofn;
                char szFile[260] = { 0 }; // buffer for file name
                //HANDLE hf;// file handle
                //Initialize OPENFILENAME
                ZeroMemory(&ofn, sizeof(OPENFILENAME));
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hWnd;
                ofn.hInstance = nullptr;
                ofn.lpstrCustomFilter = nullptr;
                ofn.nMaxCustFilter = 0;
                ofn.nFilterIndex = 0;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "All(*.*)\0*.*\0Text(*.TXT)\0*.TXT\0";
                ofn.lpstrTitle = nullptr;
                ofn.nFileOffset = 0;
                ofn.nFileExtension = 0;
                ofn.lpstrDefExt = nullptr;
                ofn.lCustData = 0;
                ofn.lpfnHook = 0;
                ofn.lpTemplateName = nullptr;
#if (_WIN32_WINNT >= 0x0500)
                ofn.pvReserved = nullptr;
                ofn.dwReserved = 0;
                ofn.FlagsEx = 0;
#endif // (_WIN32_WINNT >= 0x0500)
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = nullptr;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = nullptr;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                //GetSaveFileNameA(&ofn);
                if (GetSaveFileNameA(&ofn) != 0)
                {
                    //FILE *fp = nullptr;
                    ofstream fs;
                    fs.open(szFile, ios::binary);
                    if (!fs.is_open())
                    {
                        MessageBoxA(NULL, "文件保存出错", NULL, NULL);
                        return 0;
                    }
                    int nLen = GetWindowTextLength(hEditWnd);
                    char* pTemp = new char[nLen];
                    if (pTemp == nullptr)
                    {
                        MessageBoxA(NULL, "申请空间出错", NULL, NULL);
                        return 0;
                    }
                    SendMessageA(hEditWnd, WM_GETTEXT, nLen, (LPARAM)pTemp);
                    fs.write(pTemp, nLen);
                    /*fopen_s(&fp, szFile, "wb");
                    if (fp == nullptr)
                    {
                        MessageBoxA(NULL, "文件打开出错", NULL, NULL);
                        return 0;
                    }*/

                    /*if (fp != nullptr)
                    {
                        fclose(fp);
                    }*/
                    delete[] pTemp;
                    pTemp = nullptr;
                    fs.close();
                }
            }
                break;

            case ID_OPEN:
            {
                OPENFILENAMEA ofn;
                char szFile[260] = { 0 }; // buffer for file name
                //HANDLE hf;// file handle
                 //Initialize OPENFILENAME
                ZeroMemory(&ofn, sizeof(OPENFILENAME));
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hWnd;
                ofn.hInstance = nullptr;
                ofn.lpstrCustomFilter = nullptr;
                ofn.nMaxCustFilter = 0;
                ofn.nFilterIndex = 0;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "All(*.*)\0*.*\0Text(*.TXT)\0*.TXT\0";
                ofn.lpstrTitle = nullptr;
                ofn.nFileOffset = 0;
                ofn.nFileExtension = 0;
                ofn.lpstrDefExt = nullptr;
                ofn.lCustData = 0;
                ofn.lpfnHook = 0;
                ofn.lpTemplateName = nullptr;
#if (_WIN32_WINNT >= 0x0500)
                ofn.pvReserved = nullptr;
                ofn.dwReserved = 0;
                ofn.FlagsEx = 0;
#endif // (_WIN32_WINNT >= 0x0500)
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = nullptr;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = nullptr;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                // Display the Open dialog box. 
                if (GetOpenFileNameA(&ofn) != 0)
                {
                    //FILE *fp = nullptr;
                    //fopen_s(&fp, szFile, "rb+");
                    ifstream fs;
                    fs.open(szFile, ios::binary);
                    if (!fs.is_open())
                    {
                        MessageBoxA(NULL, "文件打开出错", NULL, NULL);
                        return 0;
                    }
                    /*if (fp == nullptr)
                    {
                        MessageBoxA(NULL, "文件打开出错", NULL, NULL);
                        return 0;
                    }*/
                    /*while (true)
                    {
                        char szBuf[256] = { 0 };
                        fread_s(szBuf, 256, 256, 1, fp);
                        SendMessageA(hEditWnd, WM_SETTEXT, 256,
                                    (LPARAM)szBuf);
                        if (feof(fp))
                        {
                            break;
                        }
                    }*/
                    string str;
                    while (!fs.eof())
                    {
                        char szBuf[256] = { 0 };
                        fs.read(szBuf, 256);
                        str = str + szBuf;
                    }
                    SendMessageA(hEditWnd, WM_SETTEXT, 256,
                        (LPARAM)str.c_str());
                    /*if (fp != nullptr)
                    {
                        fclose(fp);
                    }*/
                    fs.close();
                }
            }
                break;

            case ID_GETTIME:
            {
                SYSTEMTIME st = { 0 };
                GetLocalTime(&st);
                string strTime;
                string strTemp;
                strTemp = to_string(st.wYear);
                strTime = strTemp;
                strTime = strTime + "/";

                strTemp = to_string(st.wMonth);
                strTime = strTime + strTemp;
                strTime = strTime + "/";

                strTemp = to_string(st.wDay);
                strTime = strTime + strTemp;
                strTime = strTime + " ";

                strTemp = to_string(st.wHour);
                strTime = strTime + strTemp;
                strTime = strTime + ":";

                strTemp = to_string(st.wMinute);
                strTime = strTime + strTemp;
                strTime = strTime + ":";

                strTemp = to_string(st.wSecond);
                strTime = strTime + strTemp;
                SendMessageA(hEditWnd, WM_SETTEXT, 24,
                    (LPARAM)strTime.c_str());
            }
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
