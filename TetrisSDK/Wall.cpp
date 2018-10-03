/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：墙类编写
最后编译时间：
2018/8/17   完成
*/

#include "Wall.h"

//初始化墙
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
