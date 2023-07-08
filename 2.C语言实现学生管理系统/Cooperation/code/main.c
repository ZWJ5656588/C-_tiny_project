/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "system.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"

//帐号学生为1xxxxxxx
//老师	9xxxxxxx
//

#if 0
void main_teacher()
{
	printf("%s\n",__func__);
}
void main_student()
{
	printf("%s\n",__func__);
}
void main_principal()
{
	printf("%s\n",__func__);
}
#endif


int main(int argc,const char* argv[])
{
	sys_init();
	for(;;)
	{
		system("clear");
		printf("欢迎使用员工管理系统\n");
		printf("请输入您的帐号8位或admin(q退出)：");
		char id[20];
		fgets_t(id,20);
		//scanf("%s",id);
		if(strcmp(id,"admin")==0)	//判断为校长id
		{
			main_principal();
			write_data();
		}
		if(strlen(id)==8)
		{
			if(id[0]=='9' && atoi(id)>89999999 && atoi(id)<100000000)//判断为教师id
			{
				main_teacher(atoi(id));
				write_data();
			}else if(isdigit(id[0]) && atoi(id)>9999999 && atoi(id)<90000000)//判断为学生id,10000000-90000000(不含)
			{
				main_student(atoi(id));
				write_data();
			}
		}else if(strlen(id)==1 && id[0]=='q')
		{
			printf("欢迎下次使用\n");
			break;
		}
	}
	sys_release();
	return 0;
}
