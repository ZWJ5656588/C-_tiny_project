/*- 在整个系统中，有三种身份，分别为：学生代表、老师以及管理员
 - 三种身份有其共性也有其特性，因此我们可以将三种身份抽象出一个身份基类identity
- 在头文件下创建Identity.h文件

*/
#pragma once
#include <iostream>
using namespace std;

// 身份抽象类
class Identity
{
public:
	// 纯虚函数实现多态 每个身份有不同的操作菜单
	virtual void operMenu() = 0;


	// 三种身份均有用户名和密码
	string m_Name; // 用户名
	string m_Pwd;  // 密码
};