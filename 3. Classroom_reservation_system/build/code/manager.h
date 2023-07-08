#include "identity.h"
#include <string>
#include <fstream>
#include "globalfile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include <functional>
#include "computerRoom.h"

class Manager : public Identity{
public:
	// 默认构造
	Manager();

	// 有参构造
	Manager(string name, string pwd);  

	// 选择菜单
 	void operMenu();

	// 添加账号
	void addPerson();

	// 查看账户
	void showPerson();

	// 查看机房信息
	void showComputer();

	// 清空预约记录
	void clear();

	//初始化容器 这个容器用来获取学生或者老师信息
	void initVector();

	// 检测重复
	bool checkRepeat(int id, int type);

	// 学生容器
	vector<Student>vSt;

	// 老师容器
	vector<Teacher>vTe;

	// 机房信息
	vector<ComputerRoom> vCpu;

	// 学生注册顺序
	static int stu_num;

	// 老师注册顺序
	static int teach_num;


};

template<typename T>
void printInfo(const T &t, const int select);
