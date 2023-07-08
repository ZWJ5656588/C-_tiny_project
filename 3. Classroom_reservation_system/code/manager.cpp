#include "manager.h"

// 类外初始化静态成员变量
int Manager::stu_num = 0;

int Manager::teach_num = 0;

// 默认构造
Manager::Manager()
{

}

// 有参构造
Manager::Manager(string name, string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;

	// 构造函数中进行初始化容器操作 获取文件中的老师，学生的信息 并打印出人数
	// 在构造函数时初始化 为了后续调用查看接口
	this->initVector();

	// 初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE,  ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_size)
	{
		vCpu.push_back(com);
	}
	ifs.close();
	cout << "the number of computer rooms is " << vCpu.size() <<endl;

}

// 打印信息
template<typename T>
void printInfo(const T &t, const int select)
{
	
	if constexpr (std::is_same_v<T,Student>) //与if不同 constexpr在编译阶段进行判断模板类型 C++17扩展功能
	{
		Manager::stu_num++;
		cout << "type " << select 
		<<" num " << Manager::stu_num <<" student " 
		<<"id is " <<t.m_Id << " , "
		<< "name is " << t.m_Name 
		<<endl;
	}
	else if constexpr (std::is_same_v<T,Teacher>)
	{
		Manager::teach_num++;
		cout << "type " << select
		<< " num " << Manager::teach_num << " teacher "
		<< "id is " << t.m_empId<< " , "
		<< "name is " << t.m_Name 
		<<endl;
	}
}


// 选择菜单
void Manager::operMenu()
{
        cout << "Welcome Manager:" << this->m_Name <<  "Login!" <<endl;
    	cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        1. ADD ACCOUNT         |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        2. LOOK UP ACCOUNT     |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        3. LOOK UP ROOM        |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        4. CLEAR RESERVATION   |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|        0. LOG OUT             |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "Input your choice: ";

}

// 添加账号
void Manager::addPerson()
{
	while(true)
	{
		cout << "Please input the type of account" << endl;
		cout << "1. add sudent" << endl;
		cout << "2. add teacher" << endl;
		cout << "else number is end add" <<endl;

		string fileName; // 操作的文件名
		string tip; // 提示id号
		string errotip; // 重复提示

		ofstream ofs; // 写入文件的对象

		int select = 0;
		cin >> select; //接收用户的选项

		if (select == 1)
		{
			// 添加的是学生
			fileName = STUDENT_FILE;
			tip = "Please input student id:";
			errotip = "student id dulplicate,again please";
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "Please input teacher id:";
			errotip = "teacher id dulplicate,again please";
		}
		else
		{
			break;
		}

		// 利用追加的方式 写文件(文件写入的方式默认是覆盖)
		ofs.open(fileName,ios::out | ios::app);
		
		int id; //学号或者职工号
		string name; //姓名
		string pwd; //密码

		while (true)
		{
			// 输出一下写入类型提示
			cout << tip <<endl;
			cin >> id;  // 将对应类型的id添加到变量中

			if(id == 0)
			{
				cout << " return last page,please select again ";
				return;
			}

			// 判断是否重复
			bool ret = checkRepeat(id,select);
			if (ret) // 有重复
			{
				cout << errotip << endl;
			}
			else
			{
				break;
			}	

		}

		cout << "Please input name:" << endl;
		cin >> name;

		cout << "Please input password" << endl;
		cin >> pwd;

		// 向文件中添加数据
		ofs << id <<" "<< name << " " << pwd << " " << endl;
		cout << "add success!";
		system("pause");
		system("cls");

		// 再次更新容器 把本次添加的内容立即push到容器中
		this -> initVector();


		return;
	}
}

// 查看账户
void Manager::showPerson()
{
    cout << "Please select for looking up " << endl;
	cout << "1. looking up all students" << endl;
	cout << "2. looking up all teachers" << endl;

	int select = 0; // 接收用户选择
	cin >> select;

	if (select == 1)
	{
		// 查看学生
		cout << "all students info as follow:" <<endl;
		// bind函数作为参数绑定适配器，std::placeholders::_1为占位参数
		for_each(vSt.begin(),vSt.end(),std::bind(printInfo<Student>,std::placeholders::_1,select));
		Manager::stu_num = 0;
	}
	if (select == 2)
	{
		// 查看老师
		for_each(vTe.begin(),vTe.end(),std::bind(printInfo<Teacher>,std::placeholders::_1,select));
		Manager::teach_num = 0;
	}
}

// 查看机房信息
void Manager::showComputer()
{
    cout << "computerRoom info as follow " << endl;
}

// 清空预约记录
void Manager::clear()
{
    ofstream ofs(ORDER_FILE, ios::trunc);  // 清空之后再打开文件
	ofs.close();

	cout << "clear sucessfully" << endl;
	system("pause");
	system("cls");

}

// 初始化存储容器
void Manager::initVector()
{
	// 确保文件清空状态
	vSt.clear();
	vTe.clear(); 
	// 读取信息 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "failed load fail" << endl;
		return;
	}

	Student stu;
	while(ifs >> stu.m_Id && ifs >> stu.m_Name && ifs >> stu.m_Pwd)
	{
		vSt.push_back(stu);
	}

	cout << "number of students now: " << vSt.size() << endl;
	ifs.close();

	// 读取信息 老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "failed load fail" << endl;
		return;
	}

	Teacher teach;
	while(ifs >> teach.m_empId && ifs >> teach.m_Name && ifs >> teach.m_Pwd)
	{
		vTe.push_back(teach);
	}

	cout << "number of teachers now: " << vTe.size() <<endl;
	ifs.close();
}

// 检测重复 成员函数
bool Manager::checkRepeat(int id, int type)
{
	// id是检测的职工号 type是检测的对象(老师或者学生)
	if (type == 1)
	{
		// Manager内的成员函数
		// 检测学生
		for (auto &it : vSt)
		{
			if (id == it.m_Id)
			{
				return true;
			}
		}
		
	}
	else
	{
		// 检测老师
		for (auto &it : vTe)
		{
			if(id == it.m_empId)
			{
				return true;
			}
		}
	}

	return false;
	
}