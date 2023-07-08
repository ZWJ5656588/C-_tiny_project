#pragma once
#include <iostream>
using namespace std;
#include"globalfile.h"
#include<fstream>
#include<map>
#include<string>

class OrderFile
{
public:
    // 构造函数
    OrderFile();

    // 更新预约记录
    void updateOrder();

    //记录所有预约信息的容器 key记录条数 value记录具体减值对信息
    map<int,map<string,string>>m_orderData;

    //记录预约的条数
    int m_Size;
};
