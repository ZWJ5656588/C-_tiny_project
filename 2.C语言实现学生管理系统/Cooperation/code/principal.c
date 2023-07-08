#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getch.h>
#include "principal.h"
#include "system.h"
#include "teacher.h"
#include "student.h"

char G_pri_sec[50] = "123";
//char pri_secret[50] = {}; //密码副本
static int find_max_id(void)   //自动生成编号
{
	int sign=0,max=89999999; //编号从90000000开始
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id!=0)
		{
			if(G_teacher_on[i].id>max)
			{
				max=G_teacher_on[i].id;
			}
			sign++;
			if(sign>=G_teacher_on_len)//避免无效操作
			{
				break;
			}
		}
	}
	sign=0;
	for(int i=0;i<TEACHER_OFF_MAX;i++)
	{
		if(G_teacher_off[i].id!=0)
		{
			if(G_teacher_off[i].id>max)
			{
				max=G_teacher_off[i].id;
			}
			sign++;
			if(sign>=G_teacher_off_len)
			{
				break;
			}
		}
	}
	return max;
}

int find_teacher(int id) //寻找在职教师
{
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
int find_teacher_off(int id) //寻找离职教师
{
	for(int i=0;i<TEACHER_OFF_MAX;i++)
	{
		if(G_teacher_off[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
static void code(void)
{
	int k = strcmp("123",G_pri_sec);//检测是否第一次登录
	if(k==0)
	{
		
		first_code(k,G_pri_sec);
		printf("修改成功\n");
		sleep(2);
	}	
	
	int flag=0;
	char ch=0;
	char buff[12]={};
	while(1)              //校长可以失误无数次
	{
		system("clear");
		BUFF_CLEAR;
		flag=0;
		printf("请输入密码\n");
		while((ch = getch()) != '\n')
		{
			if(ch == 127 && flag!=0)		//读取到退格，并且还有位置可以退
			{
				flag--;
				printf("\b \b");
			}else if(flag<12 && ch!=127)	//限制写入位数为11位以下，并且没有读到退格键
			{
				buff[flag++] = ch;
				putchar('*');
			}
		}
		buff[flag] = '\0';
		encryption(1,buff);
		if(strcmp(G_pri_sec,Plaintext) == 0) //密码比对
		{
			printf("\n登录成功！\n");
			sleep(2);
			break;
		
		}
		else
		{
			printf("\n密码错误\n");
			sleep(1);
		}
	}
}

void show_teacher_on(void)  //显示在职教师
{
	system("clear");
	for(int i =0; i<G_teacher_on_len+G_teacher_off_len; i++)  //只遍历已有人物数据
	{
		if(G_teacher_on[i].id)
		{
			printf("姓名: %s\n性别: %c\n工号:%d\n", 
			G_teacher_on[i].name,G_teacher_on[i].sex,G_teacher_on[i].id);
			printf("-------------------\n");
		}
	}
	printf("输入任意键继续..");
	BUFF_CLEAR;
	getchar();
}

void show_teacher_off(void) //显示离职教师
{
	system("clear");
	for(int i =0; i<G_teacher_off_len; i++)
	{
		printf("姓名: %s\n性别: %c\n工号:%d\n", 
		G_teacher_off[i].name,G_teacher_off[i].sex,G_teacher_off[i].id);
		printf("-------------------\n");
	}
	printf("输入任意键继续..");
	BUFF_CLEAR;
	getchar();
}

void add_teacher(void)
{
	BUFF_CLEAR;
	system("clear");
	int k = 0;   //空位标志位
	printf("1.单个添加\n2.批量添加\n请输入你的选择：\n");
	int ch = 0, next_id = find_max_id();  //找到当前工号位置，为自动生成工号做准备
	int back = 0;  //检测输入是否成功标志位
	while(1)
	{
		back = scanf("%d", &ch);
		if(back == 0 || (ch != 1 && ch!= 2))
		{
			BUFF_CLEAR;
			printf("输入非法！请重新输入\n");
		}
		else
		{
			break;	
		}
	}
	
	char n_tea[50] = {};
	if(ch == 1)
	{
		while(G_teacher_on[k].id) 
		{
			if(k<TEACHER_ON_MAX-1)//防止越界
			{
				k++;//寻找空位
			}
			else if(k == TEACHER_ON_MAX-1)
			{
				printf("系统繁忙..\n");
				sleep(2);
				return;
			}
		}
		while(1)
		{
			printf("请输入教师的姓名\n");
			fgets_t(n_tea,50);
			if(strlen(n_tea)<20)    
			{
				strcpy(G_teacher_on[k].name,n_tea); 
				break;
			}
			else
			{
				printf("名字非法！\n");	
			}
		}
		while(1)
		{
			printf("请输入教师的性别m/w（仅第一个字符有效）\n");
			fgets_t(n_tea,50);
			if(n_tea[0]=='m' || n_tea[0]=='M' || n_tea[0]=='w' || n_tea[0]=='W')
			{
				G_teacher_on[k].sex = n_tea[0]; 
				break;
			}
			else
			{
				printf("性别非法！\n");			
			}
		}
		strcpy(G_teacher_on[k].secret,"123");      //初始化新成员信息
		G_teacher_on[k].id = ++next_id;
		G_teacher_on_len += 1;
		printf("添加成功！\n");
	}
	if(ch == 2)  //批量导入教师
	{	
		BUFF_CLEAR;
		printf("\n请输入需要导入的文件路径，注意：文件格式为姓名 性别\n");
		system("ls");
		char path[30] = {};  
		scanf("%s", path);
		FILE* frp = fopen(path,"r");
		if(frp == NULL)
		{
			printf("读取文件失败！\n");
			sleep(3);
			return;
		}
		int k1 = 0;
		Teacher tp = {}; //中转结构体
		while(fscanf(frp,"%s %c",tp.name,&tp.sex) == 2)
		{
			strcpy(tp.secret,"123");
			tp.id = ++next_id;
	
			while(G_teacher_on[k1].id) 
			{
				if(k1<TEACHER_ON_MAX-1)//防止越界
				{
					k1++;//寻找空位
				}
				else if(k1 == TEACHER_ON_MAX-1)
				{
					printf("系统繁忙..\n");
					sleep(2);
					return;
				}
			}
			memcpy(&G_teacher_on[k1],&tp,sizeof(Teacher)); //数据传送
			G_teacher_on_len++;
		}
		fclose(frp);
		frp = NULL;
		printf("批量导入成功！\n");
	}
	printf("输入任意建继续..");
	BUFF_CLEAR;
	getchar();
}

void del_teacher(void)
{
	BUFF_CLEAR;
	system("clear");
	printf("请输入工号：\n");
	int num = 0;
	while(1 != scanf("%d", &num))
	{
		BUFF_CLEAR;
		printf("输入非法！请重新输入\n");	
	}
	int k = find_teacher(num);
	if(k == -1)
	{
		printf("没有此教师！\n");
		sleep(3);
		return;
	}
	printf("请再次输入要删除教师工号：\n");
	int num1 = 0;
	while(1 != scanf("%d", &num1))
	{
		BUFF_CLEAR;
		printf("输入非法！请重新输入\n");	
	}
	if(num1 != num)  //工号确认
	{
		printf("输入工号不匹配，请稍后再试..\n");
		sleep(3);
		return;
	}
	//将在职教师信息拷贝到离职教师信息
	memcpy(&G_teacher_off[G_teacher_off_len],&G_teacher_on[k],sizeof(Student));
	G_teacher_off_len += 1;   //人物数量更新
	G_teacher_on[k].id = 0;
	G_teacher_on_len -= 1;
	printf("删除成功！\n");
	printf("输入任意建继续..");
	BUFF_CLEAR;
	getchar();
}

void unlock_teacher(void)
{
	BUFF_CLEAR;
	system("clear");
	printf("请输入工号：");
	int num = 0;
	while(1 != scanf("%d", &num))
	{
		BUFF_CLEAR;
		printf("输入非法！请重新输入\n");	
	}
	int k = find_teacher(num);
	if(k == -1)
	{
		printf("没有此教师！\n");
		sleep(3);
		return;
	}
	G_teacher_on[k].flag = 0;  //标志位复原
	printf("解锁成功！\n");
	printf("输入任意建继续..");
	BUFF_CLEAR;
	getchar();
}

void reset_teacher(void)
{
	BUFF_CLEAR;
	system("clear");
	printf("请输入工号：");
	int new_id = 0;
	while(1 != scanf("%d", &new_id))
	{
		BUFF_CLEAR;
		printf("输入非法！请重新输入\n");	
	}
	int k = find_teacher(new_id);
	if(k == -1)
	{
		printf("没有此教师！\n");
		sleep(3);
		return;
	}
	
	first_code(0,G_teacher_on[k].secret);
	
	G_teacher_on[k].flag = 0; //重置密码也要重置标志位
	printf("重置成功！\n");
	printf("输入任意建继续..");
	BUFF_CLEAR;
	getchar();
}
	

void reset_me(void)
{
	system("clear");
	first_code(0,G_pri_sec);
	printf("重置成功！\n");
	printf("输入任意建继续..");
	BUFF_CLEAR;
	getchar();
}

void main_principal(void)
{
	system("clear");
	code();//进入密码系统
	system("clear");
	while(1)
	{
		BUFF_CLEAR;
		system("clear");
		printf("---------欢迎进入校长系统---------\n\n");
		printf("请选择您需要的功能\n");
		printf("1.显示所有在职教师   2.显示所有离职教师\n");
		printf("3.添加教师           4.删除教师\n");
		printf("5.重置教师密码       6.解锁教师帐号\n");
		printf("7.重置自己密码       0.退出系统\n");
		
		int choice = 0;
		while(1 != scanf("%d", &choice))
		{
			BUFF_CLEAR;
			printf("输入违法！请重新输入\n");	
		}
		switch(choice)
		{
			case 1:
				show_teacher_on();
				break;

			case 2:
				show_teacher_off();
				break;

			case 3:
				add_teacher();
				break;

			case 4:
				del_teacher();
				break;

			case 5:
				reset_teacher();
				break;

			case 6:
				unlock_teacher();
				break;

			case 7:
				reset_me();
				break;

			case 0:
				return;

			default:
				printf("无效指令！\n");
				sleep(2);
				break;
		}
	}
}
