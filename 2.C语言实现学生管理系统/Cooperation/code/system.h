#ifndef SYSTEM_H
#define SYSTEM_H
				

#define DEBUG_H

#ifdef DEBUG
	#define debug(...)	printf(__VA_ARGS__)
#else
	#define debug(...)
#endif


#define error(...)	printf("%s:%s %d %m%s %s %s",__FILE__,__FUNCTION__,__LINE__,__VA_ARGS__,__DATE__,__TIME__)

#define BUFF_CLEAR stdin->_IO_read_ptr = stdin->_IO_read_end	//清空缓存区

#define STU_ON_MAX			100
#define STU_OFF_MAX			100
#define TEACHER_ON_MAX		100
#define TEACHER_OFF_MAX		100

char *fgets_t(char*str,int len);	//fgets的完善，将'\n''\0'合并为'\0'
int landing(const char* key,int *count);		//三次登录验证函数

void load_data(void);
void write_data(void);

void sys_init(void);
void sys_release(void);

#endif
