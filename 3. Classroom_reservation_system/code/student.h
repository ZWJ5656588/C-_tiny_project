#pragma once
#include "identity.h"
#include <string>
#include <vector>
#include "computerRoom.h"
#include <fstream>
#include "globalfile.h"
#include "order_file.h"
using namespace std;


class Student : public Identity
{
public:
	// 默认构造
	Student();

	// 有参构造 学号 姓名 密码
	Student(int id, string name, string pwd);

	// 菜单界面
	virtual void operMenu();

	// 申请预约
	void applyOrder();

	// 查看自身预约
	void showMyOrder();

	// 查看所有预约
	void showAllrder();

	// 取消预约
	void cancelOrder();

	// 学生学号
	int m_Id;

	// 机房容器
	vector<ComputerRoom> vComStu;
};