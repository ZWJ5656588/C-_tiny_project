#ifndef TEACHER_H
#define TEACHER_H

typedef struct Teacher{
	char name[20];
	char sex;
	int id;
	char secret[12];
	int flag;//0-2表示输入错误了多少次，存档，三次锁定
}Teacher;


extern Teacher *G_teacher_on;	//当成数组用，最大开辟空间	TEACHER_ON_MAX 100
extern Teacher *G_teacher_off;	//当成数组用，最大开辟空间	TEACHER_OFF_MAX 100
extern int G_teacher_on_len;	//存储的在校老师长度，调试时初始化为1
extern int G_teacher_off_len;	//存储的离校老师长度，调试时初始化为1

int find_student(int id);		//按照id查找student，找到返回下标，没找到返回-1
int find_student_off(int id);	//按照id查找student，找到返回下标，没找到返回-1

void main_teacher(int id);

#endif
