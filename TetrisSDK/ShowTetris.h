#pragma once

#include <Windows.h>
#include <string>
#include "Wall.h"
#include "Block.h"

class CShowTetris
{
public:
    CShowTetris();
    ~CShowTetris(); 
    void ShowTetris(CWall &Wall);//��ӡǽ�����
    void ShowTetris(CWall &Wall, CBlock BlockNext, HWND hWnd, HINSTANCE hinstance, HICON BlockIcon);//��ӡǽ�����
    void ShowNextBlock(CBlock &BlockNext);//��ӡ�¸�����
    void ShowNextBlock(HWND hWnd);//��ӡ�¸�����
    void ShowFraction(int iFraction);//��ʾ����
    void ShowFraction(int iFraction, HWND hWnd);//��ʾ����
    void ShowGameOver();//��Ϸ��������
};

