#include "ShowTetris.h"

#include <iostream>
#include <stdlib.h>
#include "Wall.h"

using namespace std;

CShowTetris::CShowTetris()
{
}

CShowTetris::~CShowTetris()
{
}

void CShowTetris::ShowTetris(CWall &Wall)//打印墙内情况
{
    int i = 0, j = 0;
    system("cls");

    for (; i < 16; i++)
    {
        for (j = 0; j < 12; j++)
        {
            //1代表墙，2代表可移动方块，3代表不可移动方块
            if (1 == Wall.GetWall()[i * 12 + j]
                || 2 == Wall.GetWall()[i * 12 + j]
                || 3 == Wall.GetWall()[i * 12 + j])
            {
                cout << "■";
            }
            else
            {
                cout << "□";
            }
        }
        cout << endl;
    }
}

void CShowTetris::ShowTetris(CWall &Wall, CBlock BlockNext, 
                             HWND hWnd, HINSTANCE hinstance, HICON BlockIcon)//打印墙内情况
{
    int i = 0, j = 0;
    int nX = 0;
    int nY = 0;
    RECT rc;
    HDC hdc;
    //PAINTSTRUCT ps;
    
    HDC hMemDC; //内存DC
    //1 获取原始DC
    hdc = GetDC(hWnd);

    //2 根据原始DC创建一个兼容内存DC
    hMemDC = CreateCompatibleDC(hdc);
    if (hMemDC == NULL) {
        ReleaseDC(hWnd, hdc);
        return;
    }

    //将memDC的内容拷贝给hDC
    GetClientRect(hWnd, &rc);
    int nWidth = rc.right - rc.left;
    int nHeight = rc.bottom - rc.top;

    //3 创建一个兼容位图
    HBITMAP memBM = CreateCompatibleBitmap(hdc, nWidth, nHeight);
    SelectObject(hMemDC, memBM);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, nWidth, nHeight);
    //画出墙和方块
    for (; i < 16; i++)
    {
        for (j = 0; j < 12; j++)
        {
            //1代表墙，2代表可移动方块，3代表不可移动方块
            if (1 == Wall.GetWall()[i * 12 + j]
                || 2 == Wall.GetWall()[i * 12 + j]
                || 3 == Wall.GetWall()[i * 12 + j])
            {
                DrawIcon(hMemDC, nX, nY, BlockIcon);
            }
            nX += 34;
        }
        nX = 0;
        nY += 34;
    }
    nX = 450;
    nY = 150;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (1 == BlockNext.GetNowBlock()[i * 4 + j])
            {
                DrawIcon(hMemDC, nX, nY, BlockIcon);
            }
            nX += 34;
        }
        nX = 450;
        nY += 34;
    }

    BOOL bRet = BitBlt(hdc, 0, 0, nWidth, nHeight,
        hMemDC, 0, 0, SRCCOPY);
    if (!bRet)
    {
        DeleteDC(hMemDC);
        ReleaseDC(hWnd, hdc);
        return;
    }
    ValidateRect(hWnd, &rc);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hdc);
}

void CShowTetris::ShowNextBlock(CBlock &BlockNext)//打印下个方块
{
    int i = 0, j = 0;
    cout << "下个方块为：" << endl;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (1 == BlockNext.GetNowBlock()[i * 4 + j])
            {
                cout << "■";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void CShowTetris::ShowNextBlock(HWND hWnd)//打印下个方块
{
    RECT rc;
    HDC hdc;
    char szBuff[] = "下个方块为：";
    hdc = GetDC(hWnd);
    rc.left = 450;
    rc.right = 550;
    rc.top = 100;
    rc.bottom = 300;
    DrawTextA(hdc,
            szBuff,
            strlen(szBuff),
            &rc,
            DT_LEFT);
    ValidateRect(hWnd, &rc);
    ReleaseDC(hWnd, hdc);
}

void CShowTetris::ShowFraction(int iFraction)//显示分数
{
    cout << "目前分数为:" << iFraction << endl;
}

void CShowTetris::ShowFraction(int iFraction, HWND hWnd)//显示分数
{
    RECT rc;
    HDC hdc;
    char szBuff[24] = "分数为:";
    char szBuff2[16] = { 0 };
    _itoa(iFraction, szBuff2, 10);
    for (int i = 0; szBuff2[i] != '\0'; i++)
    {
        szBuff[i + 7] = szBuff2[i];
    }
    hdc = GetDC(hWnd);
    rc.left = 450;
    rc.right = 550;
    rc.top = 350;
    rc.bottom = 450;
    DrawTextA(hdc,
        szBuff,
        strlen(szBuff),
        &rc,
        DT_LEFT);
    ValidateRect(hWnd, &rc);
    ReleaseDC(hWnd, hdc);
}

//游戏结束界面
void CShowTetris::ShowGameOver()
{
    cout << "游戏结束！" << endl;
}