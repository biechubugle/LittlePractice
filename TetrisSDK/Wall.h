/*
编译人员：刘逸翔
编译环境：vs2015
编译目的：墙类声明
最后编译时间：
2018/8/17   完成
*/

#pragma once

class CWall
{
public:
    CWall();
    ~CWall();
    char *GetWall();
private:
    char m_szWall[16][12];
};

