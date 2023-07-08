#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "teacher.h"
#include "system.h"
#include "student.h"
#include "principal.h"

Teacher *G_teacher_on;
Teacher *G_teacher_off;

int G_teacher_on_len=0;
int G_teacher_off_len=0;

static int find_max_id(void)
{
	int sign=0,max=19059999;
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id!=0)
		{
			if(G_student[i].id>max)
			{
				max=G_student[i].id;
			}
			sign++;
			if(sign>=Student_on_len)
			{
				break;
			}
		}
	}
	sign=0;
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id!=0)
		{
			if(G_student_off[i].id>max)
			{
				max=G_student_off[i].id;
			}
			sign++;
			if(sign>=Student_off_len)
			{
				break;
			}
		}
	}
	return max;
}
int find_student(int id)//查找在校学生，成功返回下标，失败返回-1
{
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id==id)
		{
			return i;
		}
	}
	return -1;
}
int find_student_off(int id)//查找离校学生，成功返回下标，失败返回-1
{
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id==id)
		{
			return i;
		}
	}
	return -1;
}


/**************************
*
*主代码如下
*佛祖保佑不出bug
*
**************************/
void add_new_student(void)
{
	Student s={};
	int ch=0,maxid=find_max_id();
	char buff[25];
	int temp=find_student(0);	//查找空余位置，失败返回-1
	if(temp == -1)
	{
		printf("系统升级维护，请稍候……\n");
		sleep(1);
		return;
	}
	printf("1、单个添加\n2、批量添加\n请输入你的选择：");
	while(1)
	{
		while(1 !=scanf("%d",&ch))
		{
			BUFF_CLEAR;
			printf("输入非法，重新输入\n");
			printf("1、单个添加\n2、批量添加\n请输入你的选择：");
		}

		if(ch==1)
		{
			while(1)
			{
				printf("\n请输入学生的姓名(长度最大19)：");
				fgets_t(buff,25);
				if(strlen(buff)<20)
				{
					strcpy(s.name,buff);
					break;
				}else
				{
					printf("长度非法！想搞我？\n");
				}
			}
			while(1)
			{
				printf("\n请输入学生的性别m/w(仅第一个字符有效)：");
				fgets_t(buff,25);
				if(buff[0]=='m' || buff[0]=='M'||buff[0]=='W'||buff[0]=='w')
				{
					s.sex = buff[0];
					break;
				}else
				{
					printf("乱搞？给我重新输！\n");
				}
			}
			
			strcpy(s.secret,"123");	//自动生成默认密码
			s.id=++maxid;			//自动生成学号
			memcpy(&G_student[temp],&s,sizeof(Student));
			Student_on_len++;
			printf("添加成功……\n");
			sleep(3);
			break;
		}else if(ch==2)					//批量导入学生名单
		{
			printf("请选择需要导入的文件路径，文件格式：姓名 性别\n");
			system("ls");
			char path[30]={};
			
			fgets_t(path,30);
			//scanf("%s",path);			//输入批量处理路径
			FILE* frp = fopen(path,"r");
			if(frp==NULL)
			{
				printf("没有这个文件，导入失败\n");
				sleep(1);
				return;
			}
			while(2 == fscanf(frp,"%s %c",s.name,&s.sex))
			{
				temp = find_student(0);	//查找空余位置，失败返回-1
				if(temp == -1)
				{
					printf("批量导入失败……\n");
					fclose(frp);
					sleep(1);
					return;
				}
				strcpy(s.secret,"123");
				s.id=++maxid;
				memcpy(&G_student[temp],&s,sizeof(Student));
				Student_on_len++;
			}
			fclose(frp);
			printf("批量导入成功……\n");
			sleep(1);
			break;
		}
	}
	
}

void del_student(void)
{
	int id,id1,temp;
	char buff[12];
	printf("\n请输入需要删除的学生学号(8位)：");
	while(1!=scanf("%d",&id))
	{
		BUFF_CLEAR;
		printf("输入有误，重新输\n");
		printf("\n请输入需要删除的学生学号(8位)：");
	}

	temp = find_student(id);
	if(temp==-1)
	{
		printf("学生不存在\n");
		sleep(3);
		return;
	}
	printf("\n请再次输入学号确认：");
	while(1!=scanf("%d",&id1))
	{
		BUFF_CLEAR;
		printf("输入有误，重新输\n");
		printf("\n请再次输入学号确认：");
	}

	if(id!=id1)
	{
		printf("删除失败\n");
		sleep(1);
		return;
	}
	memcpy(&G_student_off[find_student_off(0)],&G_student[temp],sizeof(Student));//将删除后的数据存入
	G_student[temp].id=0;
	Student_on_len--;
	Student_off_len++;
	printf("学生删除成功\n");
	sleep(3);
}

void search_student(void)
{
	char name[20]={};
	int ch=0,cnt=0,count=0;
	for(;;)
	{
		printf("1、姓名查找\n2、学号查找\n请输入你的选择(离校学生不在查找范围内)：");
		//debug("s_on=%d\ns_off=%d\n",Student_on_len,Student_off_len);
		while(1!=scanf("%d",&ch))
		{
			BUFF_CLEAR;
			printf("输入非法，重新输\n");
			printf("1、姓名查找\n2、学号查找\n请输入你的选择(离校学生不在查找范围内)：");
		}

		if(ch==1)
		{
			printf("\n请输入学生的姓名：");
			fgets_t(name,20);
			//scanf("%s",name);
			printf("%20s\t性别\t学号\t\t语文\t数学\t外语\n","姓名");
			for(int i=0;i<STU_ON_MAX;i++)
			{
				if(G_student[i].id !=0)
				{
					cnt++;
					if(strstr(G_student[i].name,name) != NULL)
					{
						count++;
						printf("%20s\t%c\t%d\t%.2lf\t%.2lf\t%.2lf\n",\
						G_student[i].name,\
						G_student[i].sex,\
						G_student[i].id,\
						G_student[i].score[0],G_student[i].score[1],G_student[i].score[2]);
					}
					if(cnt>=Student_on_len)
					{
						printf("查找结束,找到了%d个结果\n",count);
						sleep(3);
						return;
					}
				}
			}
		}else if(ch==2)
		{
			printf("\n请输入学生的学号：");
			int id=0,temp;
			if(1!=scanf("%d",&id))
			{
				BUFF_CLEAR;
				printf("输入数据无效，查找失败\n");
				sleep(1);
				return;
			}

			if((temp=find_student(id))!=-1)
			{
				printf("%20s\t性别\t学号\t\t语文\t数学\t外语\n","姓名");
				printf("%20s\t%c\t%d\t%.2lf\t%.2lf\t%.2lf\n",\
						G_student[temp].name,\
						G_student[temp].sex,\
						G_student[temp].id,\
						G_student[temp].score[0],G_student[temp].score[1],G_student[temp].score[2]);
				printf("查找结束\n");
				sleep(3);
				return;
			}else
			{
				printf("没有该学生\n");
				sleep(2);
				return;
			}
		}else
		{
			printf("选择非法，查找失败\n");
			sleep(1);
			return;
		}
	}	
}
void change_student(void)//修改学生信息
{
	int id;
	int choise=0;
	printf("输入需要修改学生的学号：");
	if(1!=scanf("%d",&id))		//id输入
	{
		BUFF_CLEAR;
		printf("输入有误，修改失败\n");
		printf("按任意键继续……\n");
		getchar();
		return;
	}
	int ox=find_student(id);
	if(ox==-1)					//id查找
	{
		printf("没有这个人\n");
		printf("按任意键继续……\n");
		BUFF_CLEAR;
		getchar();
		return;
	}

	printf("1,修改学生基础信息\n2,修改学生成绩\n请输入选择");
	
	while(1 != scanf("%d",&choise))	//选择有效性判断
	{
		BUFF_CLEAR;
		printf("输入非法，请重新输入\n");
		printf("1,修改学生基础信息\n2,修改学生成绩\n请输入选择");
	}
	
	char buff[25];	//临时存放姓名，性别，密码
	
	if(choise==1)
	{
		while(1)		//姓名输入
		{
			printf("请输入修改后的学生姓名(最大19)");
			fgets_t(buff,25);
			if(strlen(buff)>19)		//名字长度有效性判断
			{
				printf("名字长度超过限制(19)，重新输入\n");
				continue;
			}
			strcpy(G_student[ox].name,buff);
			break;
		}
		while(1)		//性别输入
		{
			printf("请输入修改后的学生姓别w/m(第一个字符有效)：");
			fgets_t(buff,25);
			if(buff[0]=='m' || buff[0]=='M'||buff[0]=='W'||buff[0]=='w')
			{
				G_student[ox].sex = buff[0];
				break;
			}else
			{
				printf("乱搞？给我重新输！\n");
			}
		}
		/*
		while(1)	//学生密码
		{
			printf("请输入修改后的学生密码(3-11)");
			fgets_t(buff,25);
			if(strlen(buff)>11 || strlen(buff)<3)
			{
				printf("密码长度不合格，重新输入\n");
				continue;
			}
			strcpy(G_student[ox].secret,buff);
			break;
		}
		*/

		printf("修改成功\n");
		
	}else if(choise==2)
	{
		printf("请输入修改后的学生成绩，语文，数学，外语：");
		while(3 != scanf("%lf %lf %lf",&G_student[ox].score[0],&G_student[ox].score[1],&G_student[ox].score[2]))
		{
			BUFF_CLEAR;
			printf("输入有误，重新输入\n");
			printf("请输入修改后的学生成绩，语文，数学，外语：");
		}
		G_student[ox].score[0] = G_student[ox].score[0]>100?100:G_student[ox].score[0];
		G_student[ox].score[1] = G_student[ox].score[1]>100?100:G_student[ox].score[1];
		G_student[ox].score[2] = G_student[ox].score[2]>100?100:G_student[ox].score[2];
		G_student[ox].score[0] = G_student[ox].score[0]<0?0:G_student[ox].score[0];
		G_student[ox].score[1] = G_student[ox].score[1]<0?0:G_student[ox].score[1];
		G_student[ox].score[2] = G_student[ox].score[2]<0?0:G_student[ox].score[2];
		printf("修改成功\n");
		
	}else
	{
		printf("选择无效\n");
	}
	sleep(1);
}

void add_score_student(void)
{
	printf("\n1,单个录入\n2,批量录入\n请输入选择");
	int choise=0;
	//scanf("%d",&choise);
	while(1 != scanf("%d",&choise))
	{
		BUFF_CLEAR;
		printf("输入非法，请重新输入\n");
		printf("\n1,单个录入\n2,批量录入\n请输入选择");
	}
	if(choise==1)
	{
		int id;
		printf("输入需要修改学生的学号：");
		if(1!=scanf("%d",&id))
		{
			BUFF_CLEAR;
			printf("输入有误，成绩录入失败\n");
			return;
		}
		
		int ox=find_student(id);
		if(ox==-1)
		{
			printf("没有这个人\n");
		}else
		{
			printf("请输入修改后的学生成绩，语文，数学，外语：");
			while(3 != scanf("%lf %lf %lf",&G_student[ox].score[0],&G_student[ox].score[1],&G_student[ox].score[2]))
			{
				BUFF_CLEAR;
				printf("输入有误，重新输入\n");
				printf("请输入修改后的学生成绩，语文，数学，外语：");
			}
			G_student[ox].score[0] = G_student[ox].score[0]>100?100:G_student[ox].score[0];
			G_student[ox].score[1] = G_student[ox].score[1]>100?100:G_student[ox].score[1];
			G_student[ox].score[2] = G_student[ox].score[2]>100?100:G_student[ox].score[2];
			G_student[ox].score[0] = G_student[ox].score[0]<0?0:G_student[ox].score[0];
			G_student[ox].score[1] = G_student[ox].score[1]<0?0:G_student[ox].score[1];
			G_student[ox].score[2] = G_student[ox].score[2]<0?0:G_student[ox].score[2];
			printf("修改成功\n");
		}
	}else if(choise == 2)
	{
		printf("请选择需要导入的文件路径，文件格式：学号 语文 数学 英语:\n");
		system("ls");
		char path[30]={};
		Student s={};
		//scanf("%s",path);			//输入批量处理路径
		fgets_t(path,30);
		FILE* frp = fopen(path,"r");
		if(frp==NULL)
		{
			printf("文件不存在，录入失败\n");
			sleep(2);
			return;
		}
		int des=0;
		while(4 == fscanf(frp,"%d %lf %lf %lf",&s.id,&s.score[0],&s.score[1],&s.score[2]))
		{
			//debug("%d\n",s.id);
			des=find_student(s.id);
			if(des != -1)
			{
				s.score[0] = s.score[0]>100?100:s.score[0];
				s.score[0] = s.score[0]<0?0:s.score[0];
				G_student[des].score[0] = s.score[0];
				
				s.score[1] = s.score[1]>100?100:s.score[1];
				s.score[1] = s.score[1]<0?0:s.score[1];
				G_student[des].score[1] = s.score[1];
				
				s.score[2] = s.score[2]>100?100:s.score[2];
				s.score[2] = s.score[2]<0?0:s.score[2];
				G_student[des].score[2] = s.score[2];
			}
			fgetc(frp);
		}
		fclose(frp);
		printf("批量修改成绩成功……\n");
	}else
	{
		printf("无效输入\n");
	}
	sleep(1);
}

void reset_sec_student(void)
{
	int id,temp=0;
	printf("输入需要重置密码学生的学号：");
	while(1 != scanf("%d",&id))
	{
		BUFF_CLEAR;
		printf("大哥别乱输了，快过不了验收了\n");
		printf("输入需要重置密码学生的学号：");
	}
	temp = find_student(id);
	if(temp==-1)
	{
		printf("没有这个人\n");
	}else
	{
		strcpy(G_student[temp].secret,"123");
		G_student[temp].flag=0;
		printf("重置成功\n");
	}
	sleep(1);
}
void show_on_student(void)
{
	int cnt=0;
	printf("在校学生信息：\n");

	printf("%20s\t性别\t学号\t\t语文\t数学\t外语\n","姓名");
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id!=0)
		{
			cnt++;
			printf("%20s\t%c\t%d\t%.2lf\t%.2lf\t%.2lf\n",\
						G_student[i].name,\
						G_student[i].sex,\
						G_student[i].id,\
						G_student[i].score[0],G_student[i].score[1],G_student[i].score[2]);
		}
		if(cnt>=Student_on_len)
		{
			break;
		}
	}
	printf("按任意键继续……\n");
	BUFF_CLEAR;
	getchar();
	//sleep(5);
}
void show_off_student(void)
{
	int cnt=0;
	printf("离校学生信息：\n");
	printf("%20s\t性别\t学号\t\t语文\t数学\t外语\n","姓名");
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id!=0)
		{
			cnt++;
			printf("%20s\t%c\t%d\t%.2lf\t%.2lf\t%.2lf\n",\
						G_student_off[i].name,\
						G_student_off[i].sex,\
						G_student_off[i].id,\
						G_student_off[i].score[0],G_student_off[i].score[1],G_student_off[i].score[2]);
		}
		if(cnt>=Student_off_len)
		{
			break;
		}
	}
	printf("按任意键继续……\n");
	BUFF_CLEAR;
	getchar();

}

void deblocking(void)
{
	int id;
	printf("请输入需要解锁的帐号：");
	if(1 != scanf("%d",&id))
	{
		BUFF_CLEAR;
		printf("帐号输入非法，解锁失败\n");
		sleep(1);
		return;
	}
	int temp = find_student(id);
	if(temp == -1)
	{
		printf("差无此人\n");
		sleep(1);
		return;
	}
	G_student[temp].flag=0;		//	解锁帐号
	printf("解锁成功\n");
	sleep(1);
}
int signin(int id)
{
	int count=3;
	char key[20]={};
	if(find_teacher(id)==-1)
	{
		printf("帐号不存在,请重新登录\n");
		sleep(3);
		return 0;
	}
	if(G_teacher_on[find_teacher(id)].flag == 3)
	{
		printf("密码锁定，联系校长\n");
		sleep(3);
		return 0;
	}

	if(strcmp(G_teacher_on[find_teacher(id)].secret,"123")==0)//首次登录修改密码
	{
		char s[20];
		while(1)
		{
			printf("第一次登录，请输入修改后的密码(3-11)：");
			fgets_t(s,20);
			
			if(strlen(s)>11 || strlen(s)<3 )
			{
				printf("密码长度非法……\n");
				continue;
			}
			encryption(1,s);
			strcpy(G_teacher_on[find_teacher(id)].secret,Plaintext);
			system("clear");
			break;
		}	
	}
	
	if(0 == landing(G_teacher_on[find_teacher(id)].secret,&G_teacher_on[find_teacher(id)].flag))
	{
		printf("密码锁定，联系校长……\n");
		sleep(3);
		return 0;
	}
	return 1;
}

void (*func[])(void)={
	add_new_student,
	del_student,
	search_student,
	change_student,
	add_score_student,
	reset_sec_student,
	show_on_student,
	show_off_student,
	deblocking,
};
void main_teacher(int id)
{
	if(signin(id)==0)
	{
		return;
	}
	
	int  choise=0;
	while(1)
	{
		system("clear");
		printf("----------教师管理系统-----------\n\n");
		printf("\t1、添加学生\n");
		printf("\t2、删除学生\n");
		printf("\t3、查找学生\n");
		printf("\t4、修改学生信息\n");
		printf("\t5、录入学生成绩\n");
		printf("\t6、重置学生密码\n");
		printf("\t7、显示所有在校学生信息\n");
		printf("\t8、显示所有退出学生信息\n");
		printf("\t9、解锁学生帐号\n");
		printf("\t0、退出登录\n");
		printf("------------------------------\n");
		printf("请输入选项：");
		
		while(1 != scanf("%d",&choise))
		{
			BUFF_CLEAR;
			printf("输入非法，请重新选择\n");
		}
		if(choise == 0)
		{
			printf("退出登录\n");
			sleep(1);
			return;
		}
		if(choise>0 && choise<10)
		{
			func[choise-1]();
		}
	}
}
			 
