#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getch.h>
#include "system.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"


//处理导入文件等问题

const static char* student_on_path="../source/student_on_data.txt";
const static char* student_off_path="../source/student_off_data.txt";
const static char* teacher_on_path="../source/teacher_on_data.txt";
const static char* teacher_off_path="../source/teacher_off_data.txt";
const static char* admin_path="../source/admin_data.txt";


/*******************************************************************************
*	以下为文件加载函数，分别导入在校学生，离校学生，在校老师，离校老师，校长的数据文件
*
********************************************************************************/
//加载读取在校学生数据
void load_stu_on(void)
{
	FILE* frp1=fopen(student_on_path,"r");
	if(frp1==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载在校学生个数
	fscanf(frp1,"%d",&Student_on_len);
	fgetc(frp1);
	for(int i=0;i<Student_on_len;i++)
	{
		fscanf(frp1,"%s %c %d %s %lf %lf %lf %d ",G_student[i].name,&G_student[i].sex,&G_student[i].id,G_student[i].secret,\
		&G_student[i].score[0],&G_student[i].score[1],&G_student[i].score[2],&G_student[i].flag);
	}
	fclose(frp1);
}

//加载读取离校学生数据
void load_stu_off(void)
{
	FILE* frp2=fopen(student_off_path,"r");
	if(frp2==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载离校学生个数
	fscanf(frp2,"%d",&Student_off_len);
	fgetc(frp2);
	for(int i=0;i<Student_off_len;i++)
	{
		fscanf(frp2,"%s %c %d %s %lf %lf %lf %d ",G_student_off[i].name,&G_student_off[i].sex,&G_student_off[i].id,G_student_off[i].secret,\
		&G_student_off[i].score[0],&G_student_off[i].score[1],&G_student_off[i].score[2],&G_student_off[i].flag);
	}
	fclose(frp2);
}

//加载读取在校老师数据
void load_teaher_on(void)
{
	FILE* frp3=fopen(teacher_on_path,"r");
	if(frp3==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载在校教师个数
	fscanf(frp3,"%d",&G_teacher_on_len);
	fgetc(frp3);
	for(int i=0;i<G_teacher_on_len;i++)
	{
		fscanf(frp3,"%s %c %d %s %d ",G_teacher_on[i].name,&G_teacher_on[i].sex,&G_teacher_on[i].id,G_teacher_on[i].secret,&G_teacher_on[i].flag);
	}
	fclose(frp3);
}

//加载读取离校老师数据
void load_teaher_off(void)
{
	FILE* frp4=fopen(teacher_off_path,"r");
	if(frp4==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	//加载离校教师个数
	fscanf(frp4,"%d",&G_teacher_off_len);
	fgetc(frp4);
	for(int i=0;i<G_teacher_off_len;i++)
	{
		fscanf(frp4,"%s %c %d %s %d ",G_teacher_off[i].name,&G_teacher_off[i].sex,&G_teacher_off[i].id,G_teacher_off[i].secret,\
		&G_teacher_off[i].flag);
	}
	fclose(frp4);
}

//加载校长密码
void load_pri(void)
{
	FILE* frp5=fopen(admin_path,"r");
	if(frp5==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}

	fscanf(frp5,"%s",G_pri_sec);
	fclose(frp5);
}

/*******************************************************************************
*	以下为文件写入函数，分别写入在校学生，离校学生，在校老师，离校老师，校长的数据文件
*
********************************************************************************/

//写入在校学生数据
void write_stu_on(void)
{
	FILE* fwp1=fopen(student_on_path,"w");
	if(fwp1==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	
	fprintf(fwp1,"%d\n",Student_on_len);
	int cnt=Student_on_len;
	for(int i=0;i<STU_ON_MAX;i++)
	{
		if(G_student[i].id !=0)
		{
			cnt--;
			fprintf(fwp1,"%s %c %d %s %lf %lf %lf %d\n",G_student[i].name,G_student[i].sex,G_student[i].id,G_student[i].secret,\
		G_student[i].score[0],G_student[i].score[1],G_student[i].score[2],G_student[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp1);
}

//写入离校学生数据
void write_stu_off(void)
{
	FILE* fwp2=fopen(student_off_path,"w");
	if(fwp2==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}

	fprintf(fwp2,"%d\n",Student_off_len);
	int cnt=Student_off_len;
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_student_off[i].id !=0)
		{
			cnt--;
			fprintf(fwp2,"%s %c %d %s %lf %lf %lf %d\n",G_student_off[i].name,G_student_off[i].sex,G_student_off[i].id,G_student_off[i].secret,\
		G_student_off[i].score[0],G_student_off[i].score[1],G_student_off[i].score[2],G_student_off[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp2);
}

//写入在校教师数据
void write_teacher_on(void)
{
	FILE* fwp3=fopen(teacher_on_path,"w");
	if(fwp3==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	
	fprintf(fwp3,"%d\n",G_teacher_on_len);
	int cnt=G_teacher_on_len;
	for(int i=0;i<TEACHER_ON_MAX;i++)
	{
		if(G_teacher_on[i].id !=0)
		{
			cnt--;
			fprintf(fwp3,"%s %c %d %s %d\n",G_teacher_on[i].name,G_teacher_on[i].sex,G_teacher_on[i].id,G_teacher_on[i].secret,\
		G_teacher_on[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp3);
}

//写入离校教师个数
void write_teacher_off(void)
{
	FILE* fwp4=fopen(teacher_off_path,"w");
	if(fwp4==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	
	fprintf(fwp4,"%d\n",G_teacher_off_len);
	int cnt=G_teacher_off_len;
	for(int i=0;i<STU_OFF_MAX;i++)
	{
		if(G_teacher_off[i].id !=0)
		{
			cnt--;
			fprintf(fwp4,"%s %c %d %s %d\n",G_teacher_off[i].name,G_teacher_off[i].sex,G_teacher_off[i].id,G_teacher_off[i].secret,\
		G_teacher_off[i].flag);
		}
		if(cnt==0)
		{
			break;
		}
	}
	fclose(fwp4);
}

//写入校长密码
void write_pri()
{
	FILE* fwp5=fopen(admin_path,"w");
	if(fwp5==NULL)
	{
		printf("%s 文件打开失败\n",__func__);
		return;
	}
	
	fprintf(fwp5,"%s",G_pri_sec);
	fclose(fwp5);
}

/*******************************************************************************
*		以下为引出接口的函数实现
*
********************************************************************************/
//加载所有的数据
void load_data(void)
{
	load_stu_on();
	load_stu_off();
	load_teaher_on();
	load_teaher_off();
	load_pri();
}

//写入所有数据
void write_data(void)
{
	write_stu_on();
	write_stu_off();
	write_teacher_on();
	write_teacher_off();
	write_pri();
	debug("文件写入成功\n");
}

void sys_init(void)
{
	G_student = (Student*)calloc(sizeof(Student),STU_ON_MAX);			//在校学生缓存区
	G_student_off = (Student*)calloc(sizeof(Student),STU_OFF_MAX);		//离校学生
	G_teacher_on = (Teacher*)calloc(sizeof(Teacher),TEACHER_ON_MAX);	//在校学生缓存区
	G_teacher_off = (Teacher*)calloc(sizeof(Teacher),TEACHER_OFF_MAX);	//离校学生
	if(G_student==NULL || G_student_off==NULL || G_teacher_on==NULL || G_teacher_off==NULL)
	{
		printf("系统升级中，请稍候登录……\n");
		exit(0);
	}
	load_data();
	
#if 0
	Student s1={"wangxin",'M',19061333,"123",97,94,87,0};
	Student s2={"ypj",'M',19064853,"123",65,21,66,0};
	
	Teacher t1={"zhang",'w',90014545,"123",0};
	Teacher t2={"wang",'m',90004545,"123",0};
	
	memcpy(&G_student[0],&s1,sizeof(Student));
	memcpy(&G_student[1],&s1,sizeof(Student));
	memcpy(&G_student_off[0],&s2,sizeof(Student));
	memcpy(&G_teacher_on[0],&t1,sizeof(Student));
	memcpy(&G_teacher_off[0],&t2,sizeof(Student));
	write_data();
#endif

}


//释放堆内存数据
void sys_release(void)
{
	if(G_student != NULL)
	{
		free(G_student);
		G_student = NULL;
	}
	if(G_student_off != NULL)
	{
		free(G_student_off);
		G_student_off = NULL;
	}
	if(G_teacher_on != NULL)
	{
		free(G_teacher_on);
		G_teacher_on = NULL;
	}
	if(G_teacher_off != NULL)
	{
		free(G_teacher_off);
		G_teacher_off = NULL;
	}
	
}

/*******************************************************************************
*		其他工具函数实现
*
********************************************************************************/



/*******************************************************************************
*	输入str：数组首地址
*	输入len：数组长度
*	输出：数组首地址
*	功能：fgets进阶版，去除fgets读入的'\0'
********************************************************************************/
char *fgets_t(char*str,int len)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓存区
	fgets(str,len,stdin);
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清空缓存区

	for(int i=1;i<len;i++)
	{
		if(str[i]=='\n')
		{
			str[i] = '\0';
		}
	}
	return str;
}

/*******************************************************************************
*	输入key：对应工号的密码
*	输出：是否锁定账户，若成功登录返回1,不成功则返回0
*	功能：三次登录验证
********************************************************************************/
int landing(const char* key,int *count)
{
	int flag=0;
	char ch=0;
	char buff[12]={};
	
	while(1)
	{
		flag=0;
		printf("请输入密码，您还有%d次机会！\n",3-*count);
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
		buff[flag] = '\0';					//完善字符串
		encryption(1,buff);					//密码加密
		if(strcmp(key,Plaintext) == 0)
		{
			printf("\n登录成功！\n");
			*count=0;
			sleep(1);
			return 1;
		}else
		{
			*count+=1;
			write_data();
			printf("\n密码错误，重新输入\n");
		}
		if(*count == 3)
		{
			return 0;
		}
	}
}


/*******************************************************************************
*	文件读取测试
********************************************************************************/

#if 0

int main()
{
	G_student = malloc(sizeof(Student)*Student_on_len);
	strcpy(G_student[0].name,"ypj");
	G_student[0].sex='m';
	G_student[0].id=19061335;
	strcpy(G_student[0].secret,"piop454879");
	G_student[0].score[0]=85;
	G_student[0].score[1]=83;
	G_student[0].score[2]=82;
	G_student_off = malloc(sizeof(Student)*Student_off_len);
	memcpy(G_student_off,G_student,sizeof(Student));
	write_data();
	open_data();
	for(int i=0;i<Student_on_len;i++)
	{
		printf("%s %c %d %s %lf %lf %lf\n",G_student[i].name,G_student[i].sex,G_student[i].id,G_student[i].secret,\
		G_student[i].score[0],G_student[i].score[1],G_student[i].score[2]);	
	}
}

#endif

