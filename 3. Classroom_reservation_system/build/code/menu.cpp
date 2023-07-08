#include "identity.h"
#include <iostream>
#include <fstream>
#include <string>
#include "globalfile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
using namespace std;

// 主菜单进行与用户的交互

// 进入管理员子菜单界面 操作管理员的接口
void managerMenu(Identity * &manager) // 要修改指针 传入引用
{
	while(true)
	{
		// 调用管理员子菜单
		manager -> operMenu();  // 多态写法，父类指针指向子类

		// 将父类指针转为子类指针 调用子类其他接口
		Manager *man = (Manager*)manager;

		int select = 0;
		// 接收用户选项
		cin >> select;

		if (select == 1) //添加账号
		{
			cout << "add account" << endl;
			man->addPerson();
		}
		else if (select == 2) // 查看账号
		{
			cout << "looking up account" << endl;
			man -> showPerson();
		}
		else if (select == 3) // 查看机房
		{
			cout << "look up room" << endl;
			man -> showComputer();
		}
		else if (select == 4) // 清空预约
		{
			cout << "clear reservation" <<endl;
			man -> clear();
		}
		else
		{
			delete man; // 销毁堆区对象
			man = nullptr;
			manager = nullptr;
			system("pause");
			system("cls");
			cout << "log out success";
			return;
		}

	}

}

// 进入学生子菜单界面函数
void studentMenu(Identity* &student)
{
	while (true)
	{
		// 调用学生子菜单
		student -> operMenu();

		Student * stu = (Student*) student;

		int select = 0; // 用户选择
		cin >> select;

		if (select == 1)
		{
			// 先把student.h中的=对应的功能接口函数写上 之后再实现
			stu -> applyOrder();  // 申请预约

		}
		else if (select == 2)
		{
			stu ->showMyOrder();  // 查看我的预约信息
		}
		else if (select == 3)
		{ 
			stu -> showAllrder(); // 查看所有预约信息

		}
		else if (select == 4)
		{	
			stu -> cancelOrder();  // 取消预约
		}
		else
		{
			// 注销登录 把student指针delete掉
			delete student;
			cout << "log out successfully" << endl;
			system("pause");
			system("cls");
			return ;
		}
		
	}
}


// 进入老师子菜单界面函数
void teacherMenu(Identity* &teacher)
{

}




// 登录功能实现 参数1 操作文件名 参数2 操作身份类型
void loginIn(string filename, int type)
{
	// 父类指针 用于指向子类对象
	Identity* person = nullptr;

	// 读文件
	ifstream ifs;
	ifs.open(filename,ios::in);

	// 判断文件是否存在
	if(!ifs.is_open())
	{
		cout << "no file" <<endl;
		ifs.close();
		return;
	}

	// 准备接受用户信息
	int id = 0; // 职工号或者学号
	string name;
	string pwd;

	// 判断身份
	if (type == 1 )
	{
		cout << "Please input your stu id:" << endl;
		cin >> id;
		cout << "Please input your name:" << endl;
		cin >> name;
		cout << "Please enter your password:" << endl;
		cin >> pwd;
		// 学生身份验证
		int fId; // 从文件中读取的id号
		string fName; // 从文件中获取姓名
		string fPwd; // 从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			// 与用户输入的信息·做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "stu log in success!" << endl;
				system("pause");
				system("cls");
				// person父类指针指向子类对象 多态的写法
				person = new Student(id, name, pwd);
				
				// 进入学生身份的子菜单
				studentMenu(person);

			}
			
		}
	}
	else if (type == 2 )
	{
		cout << "Please input your staff id:" << endl;
		cin >> id;
		cout << "Please input your password:" << endl;
		cin >> pwd;
		cout << "Please enter your password:" << endl;
		cin >> pwd;
		int fId; // 从文件中读取的id号
		string fName; // 从文件中获取姓名
		string fPwd; // 从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd )
			{
				cout << "tach log in success!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name,pwd);

				// 进入教师菜单
				teacherMenu(person);

			}

		} 
	}
	else if (type == 3)
	{
		// 管理员身份验证
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "Manager confirm success!" << endl;
				system("pause");
				system("cls");

				person = new Manager(name,pwd);
				managerMenu(person);
			}
		}
		
	}

	cout << "login failed again please!" << endl;
	system("pause");
	system("cls");

}


int main()
{

	int select = 0;

	while (true)
	{

		cout << "======================  WELCOME SYSTEM FOR RESERVE  =====================" << endl;
		cout << "Please select your identity!";
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.  STUDENT          |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.  TEACHER          |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.  MANAGER          |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.   EXIT            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "Input your choice: ";


		cin >> select; //接受用户选择

		switch (select)
		{
		case 1:  //学生身份
			loginIn(STUDENT_FILE,1);
			break;
		case 2:  //老师身份
			loginIn(TEACHER_FILE,2);
			break;
		case 3:  //管理员身份
			loginIn(ADMIN_FILE,3);
			break;
		case 0:  //退出系统
			cout << "welcome next use" << endl;
			system("pause");
			return 0;  // 结束程序
			break;
		default:
			cout << "erro input again please!" << endl;
			system("pause");
			system("cls");  // 清屏
			break;
		}

	}

	return 0;
}