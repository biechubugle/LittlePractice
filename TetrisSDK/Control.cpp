/*
������Ա��������
���뻷����vs2015
����Ŀ�ģ��������д
������ʱ�䣺
2018/8/17   ���
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
//������ŵ�ǽ��
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
//�ܷ��ƶ����飬����1���У�0����
int CControl::IsMove(CWall &Wall, CBlock &Block, int iTempBlockRow, int iTempBlockCol)
{
    int i = 0, j = 0;
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            //�ж��Ƿ��ǽ�غϣ��Լ��Ƿ��֮ǰ���µ��غ�
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
//�ܷ���ת����
int CControl::IsRotate(CWall &Wall, CBlock &Block)
{
    int i = 0, j = 0;
    char * szBlockTemp = Block.ChangeBlock();
    for (; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            //�ж���ת�Ƿ��ǽ�غϣ��Լ��Ƿ��֮ǰ���µ��غ�
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
//��������
void CControl::EliminateBlock(CWall &Wall)
{
    int i = 0, j = 0, iCount = 0, iNum[16] = { 0 }, iNumber = 0;
    //�����˵��м�¼����
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
    //����������ķ����и�ֵ�����е�
    for (i = 14; i >= 0; i--)
    {
        if (1 == iNum[i])//ĳһ�б�������
        {
            for (j = i; 1 == iNum[j]; j--);//�ҵ���һ��û����
            for (iCount = i; j >= 0; j--, iCount--)//��֮�����������
            {
                for (iNumber = 1; iNumber < 11; iNumber++)
                {
                    Wall.GetWall()[iCount * 12 + iNumber] = Wall.GetWall()[j * 12 + iNumber];
                }
            }
        }
    }
}
//�̶�����
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
//������ƶ������ķ���
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

//��ת����
void CControl::MoveUp(CWall &Wall, CBlock &Block)
{
    if (0 == IsRotate(Wall, Block))
    {
        Block.SetNextBlock();
        ClearBlock(Wall);//�����ƶ��ۼ�
        InitBlock(Wall, Block);//�������µ�λ�÷ŵ�������
    }
}
//�����ƶ�
void CControl::MoveDown(CWall &Wall, CBlock &Block, CBlock &BlockNext)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow + 1, m_iTempBlockCol))//�ж��ܷ������ƶ�
    {
        ClearBlock(Wall);//�����ƶ��ۼ�
        m_iTempBlockRow++;//�����ƶ�
        InitBlock(Wall, Block);//�������µ�λ�÷ŵ�������
    }
    else
    {
        FixBlock(Wall);//��������ƶ��ͽ���̶�
        EliminateBlock(Wall);//����
        Block.SetBlock(BlockNext);//���ڷ�����֮ǰԤ���
        InitBlock(Wall, Block);//�·������ǽ��
        BlockNext.GetBlock();//���һ���·���
    }
}

//�����ƶ�
void CControl::MoveLeft(CWall &Wall, CBlock &Block)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow, m_iTempBlockCol - 1))//�ж��ܷ������ƶ�
    {
        ClearBlock(Wall);//�����ƶ��ۼ�
        m_iTempBlockCol--;//�����ƶ�
        InitBlock(Wall, Block);//�������µ�λ�÷ŵ�������
    }
}

//�����ƶ�
void CControl::MoveRight(CWall &Wall, CBlock &Block)
{
    if (0 == IsMove(Wall, Block, m_iTempBlockRow, m_iTempBlockCol + 1))//�ж��ܷ������ƶ�
    {
        ClearBlock(Wall);//�����ƶ��ۼ�
        m_iTempBlockCol++;//�����ƶ�
        InitBlock(Wall, Block);//�������µ�λ�÷ŵ�������
    }
}

int CControl::GetFraction()//��ȡĿǰ����
{
    return m_iFraction;
}

int CControl::GetRunTime()//��ȡ�����ٶ�
{
    return m_iRunTime;
}

void CControl::SetRunTime(int iRunTime)//���������ٶ�
{
    m_iRunTime = iRunTime;
}

int CControl::GetGameOver()//��ȡ�Ƿ���Ϸ����
{
    return m_iGameOver;
}

void CControl::Run()//����
{

    //��ȡ��ǰʱ��
    DWORD dwStart = GetTickCount();
    DWORD dwEnd = dwStart;
    char ch = '\0';//�����û������
                   //��ʼ��ǽ
    CWall Wall;
    //��ʼ����һ������
    CBlock BlockNow;
    BlockNow.GetBlock();
    //��ʼ����һ������λ��
    InitBlock(Wall, BlockNow);
    //��ʾ
    CShowTetris ShowTetris;
    ShowTetris.ShowTetris(Wall);
    //����¸�����
    CBlock BlockNext;
    BlockNext.GetBlock();
    //�ƶ�����
    while (1)
    {
        //�ӿ��ٶ�
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
        //����Ƿ��м�������
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
            //ÿ���೤ʱ������һ��
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