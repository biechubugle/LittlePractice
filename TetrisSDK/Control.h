/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：控制类声明
最后编译时间：
2018/8/17   完成
*/

#pragma once
#include "Block.h"
#include "Wall.h"

class CControl
{
public:
    CControl();
    ~CControl();
    void InitBlock(CWall &Wall, CBlock &Block);//将方块放到墙内
    int IsMove(CWall &Wall, CBlock &Block, int iTempBlockRow, int iTempBlockCol); //能否移动方块，返回1不行，0可以
    int IsRotate(CWall &Wall, CBlock &Block);//能否旋转方块
    void EliminateBlock(CWall &Wall);//消除方块
    void FixBlock(CWall &Wall);//固定方块
    void ClearBlock(CWall &Wall);//清理掉移动残留的方块
    void MoveUp(CWall &Wall, CBlock &Block);//旋转方块
    void MoveDown(CWall &Wall, CBlock &Block, CBlock &BlockNext);//向下移动
    void MoveLeft(CWall &Wall, CBlock &Block);//向左移动
    void MoveRight(CWall &Wall, CBlock &Block);//向右移动
    int GetFraction();//获取目前分数
    int GetRunTime();//获取下落速度
    void Run();//运行
    void SetRunTime(int iRunTime);//更改下落速度
    int GetGameOver();//获取是否游戏结束
private:
    int m_iTempBlockRow;
    int m_iTempBlockCol;
    static int m_iFraction;
    static int m_iRunTime;
    static int m_iGameOver;
};

