/*
������Ա��������
���뻷����vs2015
����Ŀ�ģ�ǽ���д
������ʱ�䣺
2018/8/17   ���
*/

#include "Wall.h"

//��ʼ��ǽ
CWall::CWall()
{
    int i = 0, j = 0;
    for (; i < 16; i++)
    {
        for (j = 0; j < 12; j++)
        {
            if (15 == i || 0 == j || 11 == j)
            {
                m_szWall[i][j] = 1;
            }
            else
            {
                m_szWall[i][j] = 0;
            }
        }
    }
}

CWall::~CWall()
{
}

char *CWall::GetWall()
{
    return (char *)m_szWall;
}
