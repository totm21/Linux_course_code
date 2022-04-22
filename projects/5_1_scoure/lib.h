
/*
    最后更改：2022/4/22    cz
*/
#include<stdlib.h>
#include<stdio.h>

#ifndef _LIB_H_
#define _LIB_H_

typedef struct STUDENT
{
    char name[32];
    int age;
    float math;
    float ch;
    float sum;
    float ave;
}Student;

void input(Student **students,int n);
void calculate(Student *students,int n);
void output(Student *students,int n);



#endif