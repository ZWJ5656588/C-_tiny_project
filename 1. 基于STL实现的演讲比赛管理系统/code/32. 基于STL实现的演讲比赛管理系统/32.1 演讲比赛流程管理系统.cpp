
# include "32.2 speech manager.h"

// 面向对象的方式写 一个对象封装成一个模块.h

class Myprint
{
public:
	void operator()(const pair<int,Speakers>p)
	{
		cout << "选手编号" << p.first << " 姓名: " << p.second.m_Name << " 分数：" << p.second.m_Score[0] << endl;

	}
};

int main()
{
	// 设置随机种子
	srand((unsigned int)time(NULL));

	SpeechManager s1;
	
	int choice = 0; // 接收用户输入

	while (true)
	{
		s1.show_menu();

		cout << "输入您的选择：" << endl;
		cin >> choice; // 接收用户输入

		switch (choice)
		{
		case 1:  // 开始比赛
			s1.startspeech();
			break;
		case 2:  // 查看记录
			s1.show_record();
			break;
		case 3:  // 清空记录
			s1.clear_record();
			break;
		case 0:  // 退出系统
			s1.exit_system();
			break;
		default:  // 清屏
			system("cls");;
			break;
		}

		// 测试12名选手的创建
		/*for (map<int, Speakers>::iterator it = s1.m_Speaker.begin(); it != s1.m_Speaker.end(); it++)
		{
			cout << "选手编号" << it->first << " 姓名: " << it->second.m_Name << " 分数：" << it->second.m_Score[0] << endl;

		}

		// 法二 ：
		cout << "\n" << endl;

		for_each(s1.m_Speaker.begin(), s1.m_Speaker.end(), Myprint());  // Myprint()仿函数中遍历的是对组pair<int,Speakers>*/
	}
	
}