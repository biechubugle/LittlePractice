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

void CShowTetris::ShowTetris(CWall &Wall)//��ӡǽ�����
{
    int i = 0, j = 0;
    system("cls");

    for (; i < 16; i++)
    {
        for (j = 0; j < 12; j++)
        {
            //1����ǽ��2������ƶ����飬3�������ƶ�����
            if (1 == Wall.GetWall()[i * 12 + j]
                || 2 == Wall.GetWall()[i * 12 + j]
                || 3 == Wall.GetWall()[i * 12 + j])
            {
                cout << "��";
            }
            else
            {
                cout << "��";
            }
        }
        cout << endl;
    }
}

void CShowTetris::ShowTetris(CWall &Wall, CBlock BlockNext, 
                             HWND hWnd, HINSTANCE hinstance, HICON BlockIcon)//��ӡǽ�����
{
    int i = 0, j = 0;
    int nX = 0;
    int nY = 0;
    RECT rc;
    HDC hdc;
    //PAINTSTRUCT ps;
    
    HDC hMemDC; //�ڴ�DC
    //1 ��ȡԭʼDC
    hdc = GetDC(hWnd);

    //2 ����ԭʼDC����һ�������ڴ�DC
    hMemDC = CreateCompatibleDC(hdc);
    if (hMemDC == NULL) {
        ReleaseDC(hWnd, hdc);
        return;
    }

    //��memDC�����ݿ�����hDC
    GetClientRect(hWnd, &rc);
    int nWidth = rc.right - rc.left;
    int nHeight = rc.bottom - rc.top;

    //3 ����һ������λͼ
    HBITMAP memBM = CreateCompatibleBitmap(hdc, nWidth, nHeight);
    SelectObject(hMemDC, memBM);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, nWidth, nHeight);
    //����ǽ�ͷ���
    for (; i < 16; i++)
    {
        for (j = 0; j < 12; j++)
        {
            //1����ǽ��2������ƶ����飬3�������ƶ�����
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

void CShowTetris::ShowNextBlock(CBlock &BlockNext)//��ӡ�¸�����
{
    int i = 0, j = 0;
    cout << "�¸�����Ϊ��" << endl;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (1 == BlockNext.GetNowBlock()[i * 4 + j])
            {
                cout << "��";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void CShowTetris::ShowNextBlock(HWND hWnd)//��ӡ�¸�����
{
    RECT rc;
    HDC hdc;
    char szBuff[] = "�¸�����Ϊ��";
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

void CShowTetris::ShowFraction(int iFraction)//��ʾ����
{
    cout << "Ŀǰ����Ϊ:" << iFraction << endl;
}

void CShowTetris::ShowFraction(int iFraction, HWND hWnd)//��ʾ����
{
    RECT rc;
    HDC hdc;
    char szBuff[24] = "����Ϊ:";
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

//��Ϸ��������
void CShowTetris::ShowGameOver()
{
    cout << "��Ϸ������" << endl;
}