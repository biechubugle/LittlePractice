/*
������Ա��������
���뻷����vs2015
����Ŀ�ģ�����������
������ʱ�䣺
2018/8/17   ���
*/

#pragma once
#include "Block.h"
#include "Wall.h"

class CControl
{
public:
    CControl();
    ~CControl();
    void InitBlock(CWall &Wall, CBlock &Block);//������ŵ�ǽ��
    int IsMove(CWall &Wall, CBlock &Block, int iTempBlockRow, int iTempBlockCol); //�ܷ��ƶ����飬����1���У�0����
    int IsRotate(CWall &Wall, CBlock &Block);//�ܷ���ת����
    void EliminateBlock(CWall &Wall);//��������
    void FixBlock(CWall &Wall);//�̶�����
    void ClearBlock(CWall &Wall);//������ƶ������ķ���
    void MoveUp(CWall &Wall, CBlock &Block);//��ת����
    void MoveDown(CWall &Wall, CBlock &Block, CBlock &BlockNext);//�����ƶ�
    void MoveLeft(CWall &Wall, CBlock &Block);//�����ƶ�
    void MoveRight(CWall &Wall, CBlock &Block);//�����ƶ�
    int GetFraction();//��ȡĿǰ����
    int GetRunTime();//��ȡ�����ٶ�
    void Run();//����
    void SetRunTime(int iRunTime);//���������ٶ�
    int GetGameOver();//��ȡ�Ƿ���Ϸ����
private:
    int m_iTempBlockRow;
    int m_iTempBlockCol;
    static int m_iFraction;
    static int m_iRunTime;
    static int m_iGameOver;
};

