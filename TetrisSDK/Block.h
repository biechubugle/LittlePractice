/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：方块类声明
最后编译时间：
2018/8/17   完成
*/

#pragma once
class CBlock
{
public:
    CBlock();
    ~CBlock();
    char* GetBlock();//获取一种方块的返回地址
    char* ChangeBlock();//下个方块形状
    char* GetNowBlock();//获取当前方块
    void SetNextBlock();//变成下个形状方块
    void SetBlock(CBlock &NextBlock);//变成指定方块
private:
    char *m_szBlock;
    int m_iBlockType = 0;
    int m_iBlockShape = 0;
};

