# include "32.2 speech manager.h"

// �������ݽ�������

SpeechManager::SpeechManager()
{
	// ��ʼ������������
	init_speech();

	// ����12��ѡ��
	create_speakers();

	// ��ȡ�����¼ ��ʼ����
	load_record();
}



void SpeechManager::show_menu()
{
	cout << "*********************************************" << endl;
	cout << "************* ��ӭ�μ��ݽ����� **************" << endl;
	cout << "************* 1. ��ʼ�ݽ�����  **************" << endl;
	cout << "************* 2. �鿴�����¼  **************" << endl;
	cout << "************* 3. ��ձ�����¼  **************" << endl;
	cout << "************* 0. �˳���������  **************" << endl;
	cout << "*********************************************" << endl;

}

// ��ʼ������ʵ�� �����ÿ�
void SpeechManager::init_speech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_round = 1;       // ��ʼ��һ��
	this->m_record.clear();  // ��մ����¼������ 
}

// ����12���ݽ�ѡ��ʵ��
void SpeechManager::create_speakers()
{
	// ��������
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.length(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		// ͨ��Speakers���󴴽�ѡ��
		Speakers sp;
		sp.m_Name = name;

		// ���ֵ÷־���ֵΪ0
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		// ����ѡ�ֱ�� 
		this->v1.push_back(i + 10001);

		// ѡ�ֱ���Լ���Ӧѡ�� ���뵽map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

// ��ʼ��������ʵ�� �����������̿���
void SpeechManager::startspeech()
{
	// ��һ�ֱ���
	// 1.��ǩ
	this->speech_draw();

	// 2.����
	this->speech_contest();

	// 3.��ʾ�������
	this->show_score();

	// �ڶ��ֱ���
	this->m_round++;

	// 1.��ǩ
	this->speech_draw();

	// 2.����
	this->speech_contest();

	// 3.��ʾ���ս��
	this->show_score();

	// 4.���������ļ���
	this->save_record();

	// ���ñ��� ��ȡ��¼
	// ��ʼ������������
	this->init_speech();

	// ����12��ѡ��
	this->create_speakers();

	// ��ȡ�����¼ ��ʼ����
	this->load_record();

	cout << "����������˽����� " << endl;
	system("pause");
	system("cls");

}

// 1. ��ǩ
void SpeechManager::speech_draw()
{
	cout << "�� << " << this->m_round << " >> �ֱ���ѡ�����ڳ�ǩ " << endl;
	cout << "-----------------------------------" << endl;
	cout << "��ǩ���ݽ���˳������: " << endl;

	if (this->m_round == 1)
	{
		// ��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		// �ڶ��ֱ���
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


// 2. ��������ʵ��
void SpeechManager::speech_contest()
{
	cout <<"������������ " << "��" << this->m_round << " �ֱ�����ʽ��ʼ ������������" << "\n" << endl;

	// ׼����ʱ���� ���С��ɼ�
	multimap<double, int, greater<double>> group_score;

	int num = 0; // ��¼���� ÿ������һ��

	vector<int>v_src; // ����ѡ�ֵ���ʱ���� ��Ϊ�����ǵ�һ�ֻ��ߵڶ���
	if (this->m_round == 1)
	{
		v_src = v1; // ��ֵ����
	}
	else
	{
		v_src = v2;
	}

	// ��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		// ��ί��� ����ȥ��ͷβ���� ������˫������deque
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // ��ȡ60��100�����������
			// ���Դ��� ���ʮ�����зֱ�Ĵ��
			// cout << score << " ";
			d.push_back(score);
		}

		// �Ӵ�С������� ʹ���ڽ���������greater<double>()
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();    // ȥ����ͷ�
		d.pop_front();   // ȥ����߷�

		// ʹ��numeric�е�acculate�㷨������Ԫ�غ� ���������ֵ
		double sum = accumulate(d.begin(), d.end(), 0.0);   // �ܷ� 0.0����ʼ�ۼ�ֵ
		double avg = sum / (double)d.size();				// ƽ����

		// ��ӡƽ����
		//cout << "���Ϊ: " << *it << " ����: " << this->m_Speaker[*it].m_Name << " ��ȡƽ����: " << avg;


		// ��ƽ���ַ��뵽m_Speakers(map����)��
		// map��������[]   ͨ�� element[key] = value ȡֵ
		this->m_Speaker[*it].m_Score[this->m_round - 1] = avg;

		// ��ƽ�������ݷ���С��������
		group_score.insert(make_pair(avg, *it)); // key�ǵ÷�,value��ѡ�־����� �����Զ�����keyֵ����
		// չʾС���г�Ա������
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group_score.begin(); it != group_score.end(); it++)
			{
				cout << "��ţ� " << it->second << " ����: " << this->m_Speaker[it->second].m_Name << " �ɼ��� " << it->first << endl;
			}

			// С�������Ҫ���
			// group_score.clear();  ����debug group_score����Ҫ�Ѽ�¼��ǰ��������v2��Ӧ�����
			cout << endl;

			// ȡ�߸���С���ǰ����
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

			// С�������Ҫ���
			group_score.clear();
		
		}
	}
	cout << "������������ " << "��" << this->m_round << " �ֱ������� ������������"  << endl;

	system("pause");

}


// 3. ��ʾ�÷ֺ���ʵ��
void SpeechManager::show_score()
{


	cout << "������������ " << "��" << this->m_round << " �ֽ���������� ������������" << endl;
	
	vector<int>vv;
	if (this->m_round == 1)
	{
		vv = this->v2;
		for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
		{
			cout << "��ţ� " << *it << " ����; " << this->m_Speaker[*it].m_Name << " ������" << this->m_Speaker[*it].m_Score[this->m_round - 1] << endl;
		}
	}
	else
	{
		vv = this->vVictory;
		for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
		{
			cout << "��ţ� " << *it << " ����; " << this->m_Speaker[*it].m_Name << " ������" << this->m_Speaker[*it].m_Score[this->m_round - 1] << endl;
		}
	}

	system("pause");

	this->show_menu();
}

// ����ǰ������ʤ�߼�¼���ļ���
void SpeechManager::save_record()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);   // ��׷�ӵķ�ʽд�ļ�

	// ��ÿ��ѡ�ֵ�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << "," << endl;  // ȡ���ڶ��ֵ����ճɼ� csv�ļ��ö��ŷָ�
	}
	ofs << "\n" << endl;

	// �ر�
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;

	// �����ļ���Ϊ�յ�״̬
	this->file_is_empty = false;


}

// ��ȡ�����¼
void SpeechManager::load_record()
{
	ifstream ifs("speech.csv", ios::in); // ���ļ�

	// �ж��ļ��Ƿ�򿪳ɹ�
	// �ļ����������
	if (!ifs.is_open())
	{
		this->file_is_empty = true;
		//cout << "�ļ�������" << endl;  // ������
		ifs.close();
		return;
	}

	// �ļ���յ����
	char ch;
	ifs >> ch;
	if (ifs.eof())  // ��ifs.eof()Ϊ�� ���ʾ�Ѿ������ļ�β��
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->file_is_empty = true;
		return;
	}

	// �ļ���Ϊ��
	this->file_is_empty = false;

	ifs.putback(ch); // �������ȡ���ĵ����ַ� �Ż��� �ļ�ָ������

	string data; // ��ȡÿ���ַ���

	int index = 0;

	while (ifs >> data) // һ��һ�ж� ���µ�data��
	{
		/*10004,88.6125,
		10006,85.4375,
		10001,84.075,


		10003,87.175,
		10012,83.4,
		10004,82.8375,
						*/

		vector<string>v; // ��������ʤ������ ÿһ��ָ�������ַ���

		int pos = -1; // �鵽","λ�õı���
		int start = 0; // ��ʼ���ҵ�λ��

		while (true) {
			pos = data.find(",", start);
			if (pos == -1)
			{
				// û���ҵ�
				break;
			}
			// �ҵ� ��ȡ���Ӵ� ֮�����������
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			
			v.push_back(temp);

			start = pos + 1;

			
		}
		this->m_record.insert(pair<int, vector<string>>(index, v));

		// �����¼����
		index++;
		

	}

	ifs.close();
	
}

// ��ʾ�����¼
void SpeechManager::show_record()
{
	// �ж��ļ�Ϊ�ջ��߲�����
	if (this->file_is_empty)
	{
		cout << "�ļ�Ϊ�ջ����ļ�������" << endl;
	}
	else
	{
		// �������ÿһ��Ĺ��Ǽ���
		for (multimap<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
		{
			if (it->first % 3 == 0)
				cout << "��" << it->first / 3 + 1 << "��ھ���ţ� " << it->second[0] <<"  ";
			else if (it->first % 3 == 1)
			{
				cout << "��" << it->first / 3 + 1 << "���Ǿ���ţ� " << it->second[0] << "  ";
			}
			else
			{
				cout << "��" << it->first / 3 + 1 << "�켾����ţ� " << it->second[0] << endl;

			}
		}
	}

}


// ����ļ�
void SpeechManager::clear_record()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	
	int select = 0;

	cin >> select;

	if (select == 1)
	{
		// ȷ����� ������ļ�����
		ofstream ofs("speech.csv", ios::trunc); //trunc�򿪷�ʽ �ļ������� ��ɾ�����ݲ����´���
		ofs.close();

		// �������������
		// ��ʼ�����������Լ���
		this->init_speech();

		this->create_speakers();

		this->load_record();

		cout << "����ɹ�!" << endl;

	}
	system("pause");
	system("cls");

}



void SpeechManager::exit_system()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); // exit(0)��ϵͳ����� �˳�Ӧ�ó���ɾ����Ӧ�õĽ��̣���������״̬���ظ�OS
}



SpeechManager::~SpeechManager()
{
	


}
