CC=gcc
BIN=project
OBJ=../bin/system.o ../bin/teacher.o ../bin/main.o ../bin/student.o ../bin/principal.o
FLAG=-Wall-Werror-DDEBUG
STD=-std=gnu99

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

../bin/main.o:main.c system.h student.h teacher.h principal.h
	gcc -c main.c -o ../bin/main.o 
../bin/student.o:student.c student.h teacher.h system.h
	gcc -c student.c -o ../bin/student.o
../bin/teacher.o:teacher.c teacher.h system.h student.h principal.h
	gcc -c teacher.c -o ../bin/teacher.o
../bin/principal.o:principal.c principal.h system.h teacher.h
	gcc -c principal.c -o ../bin/principal.o
../bin/system.o:system.c system.h student.h teacher.h principal.h
	gcc -c system.c -o ../bin/system.o

clean:
	rm $(BIN) ../bin/main.o ../bin/student.o ../bin/teacher.o ../bin/principal.o ../bin/system.o

