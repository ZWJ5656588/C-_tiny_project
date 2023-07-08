// 实现菜单与用户界面的交互
// 对演讲比赛流程控制
// 对文件进行读写交互

#pragma once
#include"32.3 speakers.h"
#include<iostream>
#include<vector>
#include<deque>
#include<map>
#include<string>
#include<algorithm>
#include<ctime>
#include<functional>
#include<numeric>
#include<fstream>
using namespace std;

// 设计演讲管理类
class SpeechManager
{
public:
	// 构造函数
	SpeechManager();

	// 菜单界面
	void show_menu();

	// 退出功能
	void exit_system();

	// 初始化容器和成员属性
	void init_speech();

	// 创建12名选手
	void create_speakers();

	// 开始比赛 比赛整个流程的控制函数
	void startspeech();

	// 1.抽签
	void speech_draw();

	// 2.比赛
	void speech_contest();

	// 3.显示得分
	void show_score();

	// 4.保存比赛记录到文件中
	void save_record();

	// 读取记录
	void load_record();

	// 显示往届记录
	void show_record();

	// 清空文件
	void clear_record();

	// 析构函数
	~SpeechManager();

	// 成员属性
	// 保存第一轮比赛选手的容器（编号）
	vector<int>v1;

	// 晋级到第二轮选手的容器
	vector<int>v2;

	// 胜出前三名的容器
	vector<int>vVictory;

	// 存放编号以及对应选手的容器 因为选手编号不重复 所以使用map容器
	// int是选手编号 Speakers是选手对象
	map<int, Speakers>m_Speaker;
	 
	// 存放比赛的轮数
	int m_round;

	// 判断文件是否为空
	bool file_is_empty;

	// 存放往届记录的容器
	multimap<int, vector<string>>m_record;



	
};
