#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getch.h>
#include "student.h"
#include "teacher.h"
#include "system.h"

int Student_on_len = 0;   //在校学生数量
int Student_off_len = 0; //离校学生数量

Student* G_student = NULL;   //在校学生信息
Student* G_student_off = NULL; //离校学生信息
Student* G_student_cp = NULL;  //排序副本
static int code(int);
static double S_score[9]; //平均分，最高分，最低分存储
//static char scc_secret[50]={};   //接收密码
char Plaintext[50]={};//存储加密后密码的数组是

void encryption(int choose,char* scc_secret)  //密码加密
{
    int i = 0, devi = 2;//偏移值
    int count=0;//后面用strlen统计字符串长度
    
    while(1)
    {
        if(choose==1)
        {
            count=strlen(scc_secret);//统计字符串长度以便后面循环用
            for(i=0;i<count;i++)
            {
                Plaintext[i]=scc_secret[i]+i+devi;//开始对密码进行加密这里设置的偏移量n自己设置移动量
            }
            Plaintext[i]='\0';//加密新的明文到\0
        }
        /*else if(choose==2)//第二个是解密明文
        {
            count=strlen(text);
            for(i=0;i<count;i++)
            {
                Plaintext[i]=G_student[]-i-n;//把原数减回来，得到初始密码
            }
            text[i]='\0';
            printf("解密后：%s\n",text);
        }
        */
        break;
	}
}
void first_code(int k, char* key)  //修改密码
{
	int num = 0;
	char secret[25] = {};
	while(k==0)                    //防止再次修改为初始密码
	{
		printf("请输入新密码\n");
		while(1)
		{
			fgets_t(secret,25);
			num = strlen(secret);
			if(num>11 || num<3)
			{
				printf("请重新输入3-11位密码：\n");	
			}
			else
			{
				break;
			}
		}

		encryption(1,secret);        //密码加密

		strcpy(key,Plaintext);       
		k = strcmp("123",secret);    //防止再次修改为初始密码
	}
}

int sort(double score, int k)  //遍历排名
{
	int s = 1;
	for(int i = 0; i<Student_on_len+Student_off_len; i++)
	{
		if(G_student[i].score[k]>score && G_student[i].id)  //有成绩比自己高时，排名增加
		{
			s++;
		}
	}
	return s;
}
int score_s(void) //遍历计算平均分，最高分，最低分              //初代版本
{
	double sum[3]={},max[3]= {},min[3]={200,200,200};
	int k = 0;
	for(int i=0;i<Student_on_len+Student_off_len;i++)
	{
		for(int j=0; j<3; j++)
		{
			if(G_student[i].score[j]>max[j] && G_student[i].id)  //最高分
			{
				max[j] = G_student[i].score[j];
			}
			if(G_student[i].score[j]<min[j] && G_student[i].id)  //最低分
			{
				min[j] = G_student[i].score[j];
			}
			sum[j] += G_student[i].score[j];
		}
		if(G_student[i].id) k++;
	}
	for(int i=0;i<3;i++)
	{
		sum[i] /= k;   //平均分
	}
	S_score[0]=sum[0],S_score[1]=sum[1],S_score[2]=sum[2];  //数据存储
	S_score[3]=max[0],S_score[4]=max[1],S_score[5]=max[2];
	S_score[6]=min[0],S_score[7]=min[1],S_score[8]=min[2];
	FILE* fwp = fopen("sort_score","w");
	if(fwp == NULL)
	{
		printf("系统繁忙，请稍后..\n");
		return 1;
	}
	fprintf(fwp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",   //写入文件，不更新学生时，直接读取，更快
	S_score[0],S_score[1],S_score[2],S_score[3],S_score[4],S_score[5],S_score[6],S_score[7],S_score[8]);
	fclose(fwp);
	fwp = NULL;
	return 0;
}
void cp_student(void)         //获取在校学生信息副本，方便后续排名
{
	G_student_cp = (Student*)calloc(sizeof(Student),Student_on_len);
	int i = 0,cnt = 0;//记录有效学生数量
	for(i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id)
		{
			memcpy(&G_student_cp[cnt],&G_student[i],sizeof(Student));
			cnt++;
		}
		if(cnt == Student_on_len) //避免无效操作
		{
			break;
		}	
	}
}
int compare1(const void *s1, const void *s2)  //语文
{
	Student* ss1 = (Student*)s1;
	Student* ss2 = (Student*)s2;
	if(ss1->score[0]>ss2->score[0])
	{
		return -1;
	}else if(ss1->score[0]<ss2->score[0])
	{
		return 1;
	}else
	{
		return 0;
	}
}
int compare2(const void *s1, const void *s2) //数学
{
	Student* ss1 = (Student*)s1;
	Student* ss2 = (Student*)s2;
	if(ss1->score[1]>ss2->score[1])
	{
		return -1;
	}else if(ss1->score[1]<ss2->score[1])
	{
		return 1;
	}else
	{
		return 0;
	}
}
int compare3(const void *s1, const void *s2)//英语
{
	Student* ss1 = (Student*)s1;
	Student* ss2 = (Student*)s2;
	if(ss1->score[2]>ss2->score[2])
	{
		return -1;
	}else if(ss1->score[2]<ss2->score[2])
	{
		return 1;
	}else
	{
		return 0;
	}
}
void qsort_score(int i)//i为0 1 2
{
	if(i != 0 && i!=1&&i!=2)
	{
		return;
	}
	if(i==0)
	{
		qsort(G_student_cp,Student_on_len,sizeof(Student),compare1);
	}
	if(i==1)
	{
		qsort(G_student_cp,Student_on_len,sizeof(Student),compare2);
	}
	if(i==2)
	{
		qsort(G_student_cp,Student_on_len,sizeof(Student),compare3);
	}
}
void show_score(int std_id)  //学生分数查询
{	
	system("clear");
	int fail_f = score_s(); //当文件操作出错时，及时结束
	if(fail_f)
	{
		return;
	}
	double stu_score[9] = {}; //成绩存储
	FILE* frp = fopen("sort_score","r");
	if(frp == NULL)
	{
		printf("系统繁忙，请稍后..\n");
		return;
	}
	//读取文件
	fscanf(frp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&stu_score[0],&stu_score[1],&stu_score[2],
	&stu_score[3],&stu_score[4],&stu_score[5],&stu_score[6],&stu_score[7],&stu_score[8]);

	printf("\t姓名：%s\t学号：%d\n",G_student[std_id].name,G_student[std_id].id);

	printf("语文：%.1lf 排名：%d 科目平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[0],sort(G_student[std_id].score[0],0),stu_score[0],
	stu_score[3],stu_score[6]);

	printf("数学：%.1lf 排名：%d 科目平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[1],sort(G_student[std_id].score[1],1),stu_score[1],
	stu_score[4],stu_score[7]);

	printf("英语：%.1lf 排名：%d 科目平均分:%.1lf 最高分:%.1lf 最低分：%.1lf\n",
	G_student[std_id].score[2],sort(G_student[std_id].score[2],2),stu_score[2],
	stu_score[5],stu_score[8]);
	
	fclose(frp); //安全操作
	frp = NULL;
	printf("输入任意键继续..");
	BUFF_CLEAR;
	getchar();
}
void show_score1()  //单科全部成绩排名
{
	cp_student();//获取副本
	int choose = 0;
	printf("0.语文 1.数学 2.英语\n");
	printf("请输入你想看的科目：");
	int num = 0;
	for(;;)
	{
		num = scanf("%d", &choose);
		if(num == 0 || (choose != 0 && choose != 1 && choose != 2))
		{
			BUFF_CLEAR;
			printf("输入违法，请重试\n");
		}
		else
		{
			break;
		}
		//BUFF_CLEAR;	
	} 
	qsort_score(choose); //排名
	system("clear");
	for(int i=0;i<Student_on_len;i++)
	{
		printf("\t%.1lf\n", G_student_cp[i].score[choose]);
	}
	free(G_student_cp); //安全操作
	G_student_cp = NULL;
	BUFF_CLEAR;
	printf("输入任意键继续..");
	getchar();
}
void show_mes(int std_id) //学生信息查询
{
	system("clear");
	printf("姓名: %s\n性别: %c\n学号：%d\n", 
	G_student[std_id].name,G_student[std_id].sex,G_student[std_id].id);
	printf("输入任意键继续..");
	BUFF_CLEAR;
	getchar();
}

void change_sec(int std_id)  //修改密码
{
	system("clear");
	first_code(0,G_student[std_id].secret);
	
	printf("修改成功！\n");
	printf("输入任意键继续..");
	getchar();
}

void main_student(int stu_id)
{
	system("clear");
	int std_id = find_student(stu_id); //根据学号获取对应结构体中的信息

	if(code(std_id))  //进入密码系统，如果出错就返回主界面
	{
		return;
	}

	int choice = 0;
	while(1)
	{
		BUFF_CLEAR;
		system("clear");
		printf("--------欢迎进入学生系统--------\n\n");
		printf("请选择您需要的功能\n");
		printf("1.查看个人信息 2.查看个人成绩\n");
		printf("3.修改密码     4.查看详细成绩\n");
		printf("0.退出系统\n");

		while(1 != scanf("%d", &choice))
		{
			BUFF_CLEAR;
			printf("输入非法！请重新选择\n");
		}

		switch(choice)
		{
			case 1: 
				show_mes(std_id);	
				break;

			case 2:
				show_score(std_id);
				break;

			case 3:
				change_sec(std_id);
				break;
				
			case 4:
				show_score1();
				break;
	
			case 0:
				return;

			default:
				printf("无效指令，请重新输入\n");
				sleep(2);
		}
	}
}
static int code(int std_id)  //密码系统
{
	system("clear");
	if(std_id == -1)
	{
		printf("没有此学生！\n");
		sleep(3);
		return 1;
	}

	int k = strcmp("123",G_student[std_id].secret);  //判断是否初次登录标志
                                            
	if(k==0)                        
	{
		first_code(k,G_student[std_id].secret);
		printf("修改成功！\n");
		sleep(2);
	}

	if(G_student[std_id].flag == 3 )                     //检测标志位是否已锁定
	{
		printf("您的帐号已锁定，请联系老师解锁！\n");
		sleep(3);
		return 1;
	}

	system("clear");
	if(0 == landing(G_student[std_id].secret,&G_student[std_id].flag))
	{
		printf("您的帐号已锁定，请联系老师解锁！\n");
		sleep(3);
		return 1;
	}

	return 0;
}


