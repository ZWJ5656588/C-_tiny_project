
# include "32.2 speech manager.h"

// �������ķ�ʽд һ�������װ��һ��ģ��.h

class Myprint
{
public:
	void operator()(const pair<int,Speakers>p)
	{
		cout << "ѡ�ֱ��" << p.first << " ����: " << p.second.m_Name << " ������" << p.second.m_Score[0] << endl;

	}
};

int main()
{
	// �����������
	srand((unsigned int)time(NULL));

	SpeechManager s1;
	
	int choice = 0; // �����û�����

	while (true)
	{
		s1.show_menu();

		cout << "��������ѡ��" << endl;
		cin >> choice; // �����û�����

		switch (choice)
		{
		case 1:  // ��ʼ����
			s1.startspeech();
			break;
		case 2:  // �鿴��¼
			s1.show_record();
			break;
		case 3:  // ��ռ�¼
			s1.clear_record();
			break;
		case 0:  // �˳�ϵͳ
			s1.exit_system();
			break;
		default:  // ����
			system("cls");;
			break;
		}

		// ����12��ѡ�ֵĴ���
		/*for (map<int, Speakers>::iterator it = s1.m_Speaker.begin(); it != s1.m_Speaker.end(); it++)
		{
			cout << "ѡ�ֱ��" << it->first << " ����: " << it->second.m_Name << " ������" << it->second.m_Score[0] << endl;

		}

		// ���� ��
		cout << "\n" << endl;

		for_each(s1.m_Speaker.begin(), s1.m_Speaker.end(), Myprint());  // Myprint()�º����б������Ƕ���pair<int,Speakers>*/
	}
	
}