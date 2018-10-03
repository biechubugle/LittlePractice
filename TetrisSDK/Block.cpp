/*
������Ա��������
���뻷����vs2015
����Ŀ�ģ��������д
������ʱ�䣺
2018/8/17   ���
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
    //�����������͵�

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
    //������һ���͵�

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
    //������L�͵�

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
    //��L��

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
    //����������

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
    //z��

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
    //��z�ͣ�һ��7��
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

//��ȡһ�ַ���ķ��ص�ַ
char* CBlock::GetBlock()
{
    srand((unsigned)time(NULL));
    m_iBlockType = rand() % 7;
    m_iBlockShape = rand() % 4;
    m_szBlock = (char *)szBox + m_iBlockType * 16 * 4 + m_iBlockShape * 16;
    return m_szBlock;
}
//�¸�������״
char * CBlock::ChangeBlock()
{
    int iTemp = (m_iBlockShape + 1) % 4;
    return (char *)szBox + m_iBlockType * 16 * 4 + iTemp * 16;
}
//��ȡ��ǰ����
char* CBlock::GetNowBlock()
{
    return m_szBlock;
}
//����¸���״����
void CBlock::SetNextBlock()
{
    m_iBlockShape = (m_iBlockShape + 1) % 4;
    m_szBlock = (char *)szBox + m_iBlockType * 16 * 4 + m_iBlockShape * 16;
}
//���ָ������
void CBlock::SetBlock(CBlock &NextBlock)
{
    m_iBlockType = NextBlock.m_iBlockType;
    m_iBlockShape = NextBlock.m_iBlockShape;
    m_szBlock = NextBlock.m_szBlock;
}
