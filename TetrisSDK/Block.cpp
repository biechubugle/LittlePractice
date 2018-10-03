/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：方块类编写
最后编译时间：
2018/8/17   完成
*/

#include "Block.h"
#include <cstdlib>
#include <ctime>

const char szBox[][4] = 
{
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    //以上是土字型的

    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,

    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    //以上是一字型的

    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    //以上是L型的

    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    //反L型

    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    //以上是田型

    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
    //z型

    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    //反z型，一共7种
};

CBlock::CBlock()
{
    m_iBlockType = 0;
    m_iBlockShape = 0;
    m_szBlock = (char *)szBox;
}

CBlock::~CBlock()
{
}

//获取一种方块的返回地址
char* CBlock::GetBlock()
{
    srand((unsigned)time(NULL));
    m_iBlockType = rand() % 7;
    m_iBlockShape = rand() % 4;
    m_szBlock = (char *)szBox + m_iBlockType * 16 * 4 + m_iBlockShape * 16;
    return m_szBlock;
}
//下个方块形状
char * CBlock::ChangeBlock()
{
    int iTemp = (m_iBlockShape + 1) % 4;
    return (char *)szBox + m_iBlockType * 16 * 4 + iTemp * 16;
}
//获取当前方块
char* CBlock::GetNowBlock()
{
    return m_szBlock;
}
//变成下个形状方块
void CBlock::SetNextBlock()
{
    m_iBlockShape = (m_iBlockShape + 1) % 4;
    m_szBlock = (char *)szBox + m_iBlockType * 16 * 4 + m_iBlockShape * 16;
}
//变成指定方块
void CBlock::SetBlock(CBlock &NextBlock)
{
    m_iBlockType = NextBlock.m_iBlockType;
    m_iBlockShape = NextBlock.m_iBlockShape;
    m_szBlock = NextBlock.m_szBlock;
}
