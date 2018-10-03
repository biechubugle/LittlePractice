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
    void ShowTetris(CWall &Wall);//打印墙内情况
    void ShowTetris(CWall &Wall, CBlock BlockNext, HWND hWnd, HINSTANCE hinstance, HICON BlockIcon);//打印墙内情况
    void ShowNextBlock(CBlock &BlockNext);//打印下个方块
    void ShowNextBlock(HWND hWnd);//打印下个方块
    void ShowFraction(int iFraction);//显示分数
    void ShowFraction(int iFraction, HWND hWnd);//显示分数
    void ShowGameOver();//游戏结束界面
};

