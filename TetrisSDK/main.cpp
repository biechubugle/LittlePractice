/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：俄罗斯方块
最后编译时间：
2018/10/01    俄罗斯方块
*/

#include <Windows.h>
#include <tchar.h>
#include <string>
#include "resource.h"
#include "Control.h"
#include "ShowTetris.h"

HINSTANCE hInst;
HWND hWnd;
HWND hMindWnd;
HICON BlockIcon;
POINT ptMouse;
CControl Con;
CBlock BlockNow;
CBlock BlockNext;
CWall Wall;
CShowTetris ShowTetris;
int nConut = 0;//时间间隔计数器
int nDownCount = 4;//下落计数器

ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    ATOM atom = MyRegisterClass(hInstance);
    if (atom == 0)
    {
        return 0;
    }
    BlockNow.GetBlock();
    Con.InitBlock(Wall, BlockNow);
    BlockNext.GetBlock();
    BlockIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLOCK));
    hWnd = CreateWindowEx(NULL,
        _T("Tetris"),
        _T("Tetris"),
        WS_EX_LAYERED | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0,
        0,
        800,
        600,
        NULL,
        NULL,
        hInst,
        NULL);
    hMindWnd = hWnd;

    if (hWnd == NULL)
    {
        return 0;
    }

    //显示窗口
    ShowWindow(hWnd, SW_SHOW);

    //更新
    UpdateWindow(hWnd);
    //创建自动下落的定时器
    SetTimer(hWnd, 10001, 250, NULL);
    //消息循环
    //线程拥有消息队列
    MSG msg;
    while (GetMessage(&msg,
        NULL,
        0,
        0) > 0)
    {
        //派发消息
        DispatchMessage(&msg);
    }
    return 0;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    memset(&wcex, 0, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    hInst = hInstance;
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WMPAINTPRACTICE);
    wcex.lpszClassName = _T("Tetris");
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        ShowTetris.ShowTetris(Wall, BlockNext, hWnd, hInst, BlockIcon);
        ShowTetris.ShowNextBlock(hWnd);
        ShowTetris.ShowFraction(Con.GetFraction(), hWnd);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER:
    {
        nConut++;
        if (Con.GetFraction() >= 50)
        {
            nDownCount = 3;
        }
        else if(Con.GetFraction() >= 100)
        {
            nDownCount = 2;
        }
        else if (Con.GetFraction() >= 150)
        {
            nDownCount = 1;
        }

        if(nConut >= nDownCount)
        {
            nConut = 0;
            Con.MoveDown(Wall, BlockNow, BlockNext);
            if (0 == Con.GetGameOver())
            {
                //MessageBox(hWnd, _T("游戏结束"), _T("游戏结束"), MB_OK);
                exit(1);
            }
            /*if (Con.GetFraction() > 10)
            {
                SetTimer(hMindWnd, 1001, 10, NULL);
            }*/
            RECT rc;
            GetClientRect(hWnd, &rc);
            InvalidateRect(hWnd, &rc, TRUE); 
        }
    }
    break;
    case WM_KEYDOWN:
    {
        if (wParam == 'A')
        {
            //OutputDebugString("A");
            Con.MoveLeft(Wall, BlockNow);
        }
        if (wParam == 'W')
        {
            Con.MoveUp(Wall, BlockNow);
        }
        if (wParam == 'S')
        {
            Con.MoveDown(Wall, BlockNow, BlockNext);
        }
        if (wParam == 'D')
        {
            Con.MoveRight(Wall, BlockNow);
            if (0 == Con.GetGameOver())
            {
                //MessageBox(hWnd, _T("游戏结束"), _T("游戏结束"), MB_OK);
                exit(1);
            }
        }
        RECT rc;
        GetClientRect(hWnd, &rc);
        InvalidateRect(hWnd, &rc, TRUE);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}