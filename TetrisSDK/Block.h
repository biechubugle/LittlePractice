/*
������Ա��������
���뻷����vs2015
����Ŀ�ģ�����������
������ʱ�䣺
2018/8/17   ���
*/

#pragma once
class CBlock
{
public:
    CBlock();
    ~CBlock();
    char* GetBlock();//��ȡһ�ַ���ķ��ص�ַ
    char* ChangeBlock();//�¸�������״
    char* GetNowBlock();//��ȡ��ǰ����
    void SetNextBlock();//����¸���״����
    void SetBlock(CBlock &NextBlock);//���ָ������
private:
    char *m_szBlock;
    int m_iBlockType = 0;
    int m_iBlockShape = 0;
};

