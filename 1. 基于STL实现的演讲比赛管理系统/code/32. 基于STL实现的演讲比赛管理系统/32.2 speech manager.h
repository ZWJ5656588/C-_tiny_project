// ʵ�ֲ˵����û�����Ľ���
// ���ݽ��������̿���
// ���ļ����ж�д����

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

// ����ݽ�������
class SpeechManager
{
public:
	// ���캯��
	SpeechManager();

	// �˵�����
	void show_menu();

	// �˳�����
	void exit_system();

	// ��ʼ�������ͳ�Ա����
	void init_speech();

	// ����12��ѡ��
	void create_speakers();

	// ��ʼ���� �����������̵Ŀ��ƺ���
	void startspeech();

	// 1.��ǩ
	void speech_draw();

	// 2.����
	void speech_contest();

	// 3.��ʾ�÷�
	void show_score();

	// 4.���������¼���ļ���
	void save_record();

	// ��ȡ��¼
	void load_record();

	// ��ʾ�����¼
	void show_record();

	// ����ļ�
	void clear_record();

	// ��������
	~SpeechManager();

	// ��Ա����
	// �����һ�ֱ���ѡ�ֵ���������ţ�
	vector<int>v1;

	// �������ڶ���ѡ�ֵ�����
	vector<int>v2;

	// ʤ��ǰ����������
	vector<int>vVictory;

	// ��ű���Լ���Ӧѡ�ֵ����� ��Ϊѡ�ֱ�Ų��ظ� ����ʹ��map����
	// int��ѡ�ֱ�� Speakers��ѡ�ֶ���
	map<int, Speakers>m_Speaker;
	 
	// ��ű���������
	int m_round;

	// �ж��ļ��Ƿ�Ϊ��
	bool file_is_empty;

	// ��������¼������
	multimap<int, vector<string>>m_record;



	
};
