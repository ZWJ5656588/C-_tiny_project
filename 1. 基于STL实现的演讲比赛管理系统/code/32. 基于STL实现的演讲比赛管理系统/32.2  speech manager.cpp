# include "32.2 speech manager.h"

// 创建的演讲管理类

SpeechManager::SpeechManager()
{
	// 初始化容器和属性
	init_speech();

	// 创建12名选手
	create_speakers();

	// 获取往届记录 初始界面
	load_record();
}



void SpeechManager::show_menu()
{
	cout << "*********************************************" << endl;
	cout << "************* 欢迎参加演讲比赛 **************" << endl;
	cout << "************* 1. 开始演讲比赛  **************" << endl;
	cout << "************* 2. 查看往届记录  **************" << endl;
	cout << "************* 3. 清空比赛记录  **************" << endl;
	cout << "************* 0. 退出比赛程序  **************" << endl;
	cout << "*********************************************" << endl;

}

// 初始化函数实现 容器置空
void SpeechManager::init_speech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_round = 1;       // 初始第一轮
	this->m_record.clear();  // 清空储存记录的容器 
}

// 创建12名演讲选手实现
void SpeechManager::create_speakers()
{
	// 名称种子
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.length(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		// 通过Speakers对象创建选手
		Speakers sp;
		sp.m_Name = name;

		// 两轮得分均赋值为0
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		// 创建选手编号 
		this->v1.push_back(i + 10001);

		// 选手编号以及对应选手 放入到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

// 开始比赛函数实现 比赛整个流程控制
void SpeechManager::startspeech()
{
	// 第一轮比赛
	// 1.抽签
	this->speech_draw();

	// 2.比赛
	this->speech_contest();

	// 3.显示晋级结果
	this->show_score();

	// 第二轮比赛
	this->m_round++;

	// 1.抽签
	this->speech_draw();

	// 2.比赛
	this->speech_contest();

	// 3.显示最终结果
	this->show_score();

	// 4.保存结果到文件中
	this->save_record();

	// 重置比赛 获取记录
	// 初始化容器和属性
	this->init_speech();

	// 创建12名选手
	this->create_speakers();

	// 获取往届记录 初始界面
	this->load_record();

	cout << "本届比赛到此结束！ " << endl;
	system("pause");
	system("cls");

}

// 1. 抽签
void SpeechManager::speech_draw()
{
	cout << "第 << " << this->m_round << " >> 轮比赛选手正在抽签 " << endl;
	cout << "-----------------------------------" << endl;
	cout << "抽签后演讲的顺序如下: " << endl;

	if (this->m_round == 1)
	{
		// 第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		// 第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
	cout << "-----------------------------------" << endl;
	system("pause");
	cout << endl;

}


// 2. 比赛函数实现
void SpeechManager::speech_contest()
{
	cout <<"—————— " << "第" << this->m_round << " 轮比赛正式开始 ——————" << "\n" << endl;

	// 准备临时容器 存放小组成绩
	multimap<double, int, greater<double>> group_score;

	int num = 0; // 记录人数 每六个人一组

	vector<int>v_src; // 比赛选手的临时容器 因为可能是第一轮或者第二轮
	if (this->m_round == 1)
	{
		v_src = v1; // 赋值操作
	}
	else
	{
		v_src = v2;
	}

	// 遍历所有选手进行比赛
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		// 评委打分 由于去除头尾分数 所以用双端数组deque
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // 获取60—100的随机浮点数
			// 测试代码 输出十个裁判分别的打分
			// cout << score << " ";
			d.push_back(score);
		}

		// 从大到小排序分数 使用内建函数对象greater<double>()
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();    // 去除最低分
		d.pop_front();   // 去除最高分

		// 使用numeric中的acculate算法求容器元素和 进而求出均值
		double sum = accumulate(d.begin(), d.end(), 0.0);   // 总分 0.0是起始累加值
		double avg = sum / (double)d.size();				// 平均分

		// 打印平均分
		//cout << "编号为: " << *it << " 姓名: " << this->m_Speaker[*it].m_Name << " 获取平均分: " << avg;


		// 将平均分放入到m_Speakers(map容器)中
		// map容器重载[]   通过 element[key] = value 取值
		this->m_Speaker[*it].m_Score[this->m_round - 1] = avg;

		// 将平均分数据放入小组容器中
		group_score.insert(make_pair(avg, *it)); // key是得分,value是选手具体编号 方便自动进行key值排序
		// 展示小组中成员的名次
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group_score.begin(); it != group_score.end(); it++)
			{
				cout << "编号： " << it->second << " 姓名: " << this->m_Speaker[it->second].m_Name << " 成绩： " << it->first << endl;
			}

			// 小组的容器要清空
			// group_score.clear();  这里debug group_score容器要把记录的前三名传给v2才应该清空
			cout << endl;

			// 取走各个小组的前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator mit = group_score.begin(); mit != group_score.end() && count < 3; mit++, count++)
			{
				if (this->m_round == 1)
				{
					v2.push_back(mit->second);
				}
				else
				{
					vVictory.push_back(mit->second);
				}
			}

			// 小组的容器要清空
			group_score.clear();
		
		}
	}
	cout << "—————— " << "第" << this->m_round << " 轮比赛结束 ——————"  << endl;

	system("pause");

}


// 3. 显示得分函数实现
void SpeechManager::show_score()
{


	cout << "—————— " << "第" << this->m_round << " 轮晋级情况如下 ——————" << endl;
	
	vector<int>vv;
	if (this->m_round == 1)
	{
		vv = this->v2;
		for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
		{
			cout << "编号： " << *it << " 姓名; " << this->m_Speaker[*it].m_Name << " 分数：" << this->m_Speaker[*it].m_Score[this->m_round - 1] << endl;
		}
	}
	else
	{
		vv = this->vVictory;
		for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
		{
			cout << "编号： " << *it << " 姓名; " << this->m_Speaker[*it].m_Name << " 分数：" << this->m_Speaker[*it].m_Score[this->m_round - 1] << endl;
		}
	}

	system("pause");

	this->show_menu();
}

// 保存前三名获胜者记录到文件中
void SpeechManager::save_record()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);   // 用追加的方式写文件

	// 将每个选手的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << "," << endl;  // 取出第二轮的最终成绩 csv文件用逗号分隔
	}
	ofs << "\n" << endl;

	// 关闭
	ofs.close();
	cout << "记录已经保存" << endl;

	// 更改文件不为空的状态
	this->file_is_empty = false;


}

// 读取往届记录
void SpeechManager::load_record()
{
	ifstream ifs("speech.csv", ios::in); // 读文件

	// 判断文件是否打开成功
	// 文件不存在情况
	if (!ifs.is_open())
	{
		this->file_is_empty = true;
		//cout << "文件不存在" << endl;  // 测试用
		ifs.close();
		return;
	}

	// 文件清空的情况
	char ch;
	ifs >> ch;
	if (ifs.eof())  // 若ifs.eof()为真 则表示已经读到文件尾部
	{
		//cout << "文件为空" << endl;
		this->file_is_empty = true;
		return;
	}

	// 文件不为空
	this->file_is_empty = false;

	ifs.putback(ch); // 将上面读取到的单个字符 放回来 文件指针重置

	string data; // 读取每个字符串

	int index = 0;

	while (ifs >> data) // 一行一行读 都堵到data中
	{
		/*10004,88.6125,
		10006,85.4375,
		10001,84.075,


		10003,87.175,
		10012,83.4,
		10004,82.8375,
						*/

		vector<string>v; // 存放历届的胜者数据 每一届分割出留个字符串

		int pos = -1; // 查到","位置的变量
		int start = 0; // 开始查找的位置

		while (true) {
			pos = data.find(",", start);
			if (pos == -1)
			{
				// 没有找到
				break;
			}
			// 找到 截取出子串 之后放入容器中
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			
			v.push_back(temp);

			start = pos + 1;

			
		}
		this->m_record.insert(pair<int, vector<string>>(index, v));

		// 放入记录容器
		index++;
		

	}

	ifs.close();
	
}

// 显示往届记录
void SpeechManager::show_record()
{
	// 判断文件为空或者不存在
	if (this->file_is_empty)
	{
		cout << "文件为空或者文件不存在" << endl;
	}
	else
	{
		// 遍历输出每一届的冠亚季军
		for (multimap<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
		{
			if (it->first % 3 == 0)
				cout << "第" << it->first / 3 + 1 << "届冠军编号： " << it->second[0] <<"  ";
			else if (it->first % 3 == 1)
			{
				cout << "第" << it->first / 3 + 1 << "届亚军编号： " << it->second[0] << "  ";
			}
			else
			{
				cout << "第" << it->first / 3 + 1 << "届季军编号： " << it->second[0] << endl;

			}
		}
	}

}


// 清空文件
void SpeechManager::clear_record()
{
	cout << "是否确定清空文件？" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	
	int select = 0;

	cin >> select;

	if (select == 1)
	{
		// 确认清空 先清除文件内容
		ofstream ofs("speech.csv", ios::trunc); //trunc打开方式 文件若存在 则删除内容并重新创建
		ofs.close();

		// 再清除容器内容
		// 初始化容器和属性即可
		this->init_speech();

		this->create_speakers();

		this->load_record();

		cout << "清除成功!" << endl;

	}
	system("pause");
	system("cls");

}



void SpeechManager::exit_system()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); // exit(0)是系统级别的 退出应用程序，删除该应用的进程，并将结束状态返回给OS
}



SpeechManager::~SpeechManager()
{
	


}
