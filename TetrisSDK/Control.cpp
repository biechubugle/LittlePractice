/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：控制类编写
最后编译时间：
2018/8/17   完成
*/

#include <windows.h>
#include <conio.h>
#include "ShowTetris.h"
#include "Control.h"
#include "Block.h"
#include "Wall.h"

int CControl::m_iFraction = 0; 
int CControl::m_iRunTime = 2000;
int CControl::m_iGameOver = 1;

CControl::CControl()
{
    m_iTempBlockRow = 0;
    m_iTempBlockCol = 4;
}

CControl::~CControl()
{
}
//将方块放到墙内
void CControl::InitBlock(CWall &Wall, CBlock &Block)
{
    int i = 0, j = 0;
    if (1 == IsMove(Wall, Block, m_iTempBlockRow, m_iTempBlockCol))
    {
        m_iGameOver = 0;
        return;
    }
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (1 == Block.GetNowBlock()[i * 4 + j])
            {
                Wall.GetWall()[(m_iTempBlockRow + i) * 12 + j + m_iTempBlockCol] = 2;
            }
        }
    }
}
//能否移动方块，返回1不行，0可以
int CControl::IsMove(CWall &Wall, CBlock &Block, int iTempBlockRow, int iTempBlockCol)
{
    int i = 0, j = 0;
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            //判断是否和墙重合，以及是否和之前落下的重合
            if (1 == Block.GetNowBlock()[i * 4 + j]
                && (1 == Wall.GetWall()[(iTempBlockRow + i) * 12 + j + iTempBlockCol]
                   || 3 == Wall.GetWall()[(iTempBlockRow + i) * 12 + j + iTempBlockCol]))
            {
                return 1;
            }
        }
    }
    return 0;
}
//能否旋转方块
int CControl::IsRotate(CWall &Wall, CBlock &Block)
{
    int i = 0, j = 0;
    char * szBlockTemp = Block.ChangeBlock();
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            //判断旋转是否和墙重合，以及是否和之前落下的重合
            if (1 == szBlockTemp[i * 4 + j]
                && (1 == Wall.GetWall()[(m_iTempBlockRow + i) * 12 + j + m_iTempBlockCol]
                    || 3 == Wall.GetWall()[(m_iTempBlockRow + i) * 12 + j + m_iTempBlockCol]))
            {
                return 1;
            }
        }
    }
    return 0;
}
//消除方块
void CControl::EliminateBlock(CWall &Wall)
{
    int i = 0, j = 0, iCount = 0, iNum[16] = { 0 }, iNumber = 0;
    //将满了的行记录下来
    for (i = 14; i >= 0; i--)
    {
        iCount = 0;
        for (j = 1; j < 11; j++)
        {

            if (3 == Wall.GetWall()[i * 12 + j])
            {
                iCount++;
            }
        }
        if (10 == iCount)
        {
            iNum[i] = 1;
            m_iFraction += 10;
        }
    }
    //将满行上面的非满行赋值给满行的
    for (i = 14; i >= 0; i--)
    {
        if (1 == iNum[i])//某一行被填满了
        {
            for (j = i; 1 == iNum[j]; j--);//找到第一个没满的
            for (iCount = i; j >= 0; j--, iCount--)//将之后的依次下移
            {
                for (iNumber = 1; iNumber < 11; iNumber++)
                {
                    Wall.GetWall()[iCount * 12 + iNumber] = Wall.GetWall()[j * 12 + iNumber];
                }
            }
        }
    }
}
//固定方块
void CControl::FixBlock(CWall &Wall)
{
    int i = 0, j = 0;
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (2 == Wall.GetWall()[(m_iTempBlockRow + i) * 12 + m_iTempBlockCol + j])
            {
                Wall.GetWall()[(m_iTempBlockRow + i) * 12 + m_iTempBlockCol + j] = 3;
            }
        }
    }
    m_iTempBlockRow = 0;
    m_iTempBlockCol = 4;
}
//清理掉移动残留的方块
void CControl::ClearBlock(CWall &Wall)
{
    int i = 0, j = 0;
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (2 == Wall.GetWall()[(m_iTempBlockRow + i) * 12 + m_iTempBlockCol + j]
                && m_iTempBlockRow + i < 15
                && m_iTempBlockCol + j < 11)
            {
                Wall.GetWall()[(m_iTempBlockRow + i) * 12 + m_iTempBlockCol + j] = 0;
            }
        }
    }
}

//旋转方块
void CControl::MoveUp(CWall &Wall, CBlock &Block)
{
    if (0 == IsRotate(Wall, Block))
    {
        Block.SetNextBlock();
        ClearBlock(Wall);//消除移动痕迹
        InitBlock(Wall, Block);//将方块新的位置放到数组中
    }
}
//向下移动
void CControl::MoveDown(CWall &Wall, CBlock &Block, CBlock &BlockNext)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow + 1, m_iTempBlockCol))//判断能否向下移动
    {
        ClearBlock(Wall);//消除移动痕迹
        m_iTempBlockRow++;//向下移动
        InitBlock(Wall, Block);//将方块新的位置放到数组中
    }
    else
    {
        FixBlock(Wall);//如果不能移动就将其固定
        EliminateBlock(Wall);//消行
        Block.SetBlock(BlockNext);//现在方块变成之前预告的
        InitBlock(Wall, Block);//新方块放入墙内
        BlockNext.GetBlock();//随机一个新方块
    }
}

//向左移动
void CControl::MoveLeft(CWall &Wall, CBlock &Block)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow, m_iTempBlockCol - 1))//判断能否向左移动
    {
        ClearBlock(Wall);//消除移动痕迹
        m_iTempBlockCol--;//向左移动
        InitBlock(Wall, Block);//将方块新的位置放到数组中
    }
}

//向右移动
void CControl::MoveRight(CWall &Wall, CBlock &Block)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow, m_iTempBlockCol + 1))//判断能否向右移动
    {
        ClearBlock(Wall);//消除移动痕迹
        m_iTempBlockCol++;//向右移动
        InitBlock(Wall, Block);//将方块新的位置放到数组中
    }
}

int CControl::GetFraction()//获取目前分数
{
    return m_iFraction;
}

int CControl::GetRunTime()//获取下落速度
{
    return m_iRunTime;
}

void CControl::SetRunTime(int iRunTime)//更改下落速度
{
    m_iRunTime = iRunTime;
}

int CControl::GetGameOver()//获取是否游戏结束
{
    return m_iGameOver;
}

void CControl::Run()//运行
{

    //获取当前时间
    DWORD dwStart = GetTickCount();
    DWORD dwEnd = dwStart;
    char ch = '\0';//接受用户输入的
                   //初始化墙
    CWall Wall;
    //初始化第一个方块
    CBlock BlockNow;
    BlockNow.GetBlock();
    //初始化第一个方块位置
    InitBlock(Wall, BlockNow);
    //显示
    CShowTetris ShowTetris;
    ShowTetris.ShowTetris(Wall);
    //随机下个方块
    CBlock BlockNext;
    BlockNext.GetBlock();
    //移动方块
    while (1)
    {
        //加快速度
        if (GetFraction() > 50)
        {
            SetRunTime(1500);
        }
        if (GetFraction() > 100)
        {
            SetRunTime(1000);
        }
        if (GetFraction() > 200)
        {
            SetRunTime(750);
        }
        //检查是否有键盘输入
        if (_kbhit())
        {
            ch = _getch();
            switch (ch)
            {
            case 'W':
            case 'w':
                MoveUp(Wall, BlockNow);
                break;
            case 'S':
            case 's':
                MoveDown(Wall, BlockNow, BlockNext);
                if (0 == GetGameOver())
                {
                    ShowTetris.ShowGameOver();
                    goto END_GAME;
                }
                break;
            case 'A':
            case 'a':
                MoveLeft(Wall, BlockNow);
                break;
            case 'D':
            case 'd':
                MoveRight(Wall, BlockNow);
                break;
            }
        }
        dwEnd = GetTickCount();
        if (dwEnd - dwStart >= GetRunTime())
        {
            //每隔多长时间下落一次
            //Sleep(GetRunTime());
            dwStart = dwEnd;
            MoveDown(Wall, BlockNow, BlockNext);
            if (0 == GetGameOver())
            {
                ShowTetris.ShowGameOver();
                goto END_GAME;
            }
        }
        ShowTetris.ShowTetris(Wall);
        ShowTetris.ShowNextBlock(BlockNext);
        ShowTetris.ShowFraction(GetFraction());
    }
END_GAME:
    system("pause");
    return;
}