#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
	char name[20];
	char sex;
	int id;
	char secret[12];
	double score[3];
	int flag;//0-2表示输入错误了多少次，存档，三次锁定
}Student;

extern Student* G_student;
extern Student* G_student_off;
extern Student* G_student_cp;
extern int Student_on_len;
extern int Student_off_len;
extern char Plaintext[50];

void main_student(int id);
void encryption(int,char*);
void first_code(int,char*);

#endif//STUDENT_H
