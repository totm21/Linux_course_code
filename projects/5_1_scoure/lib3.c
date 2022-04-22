#include"lib.h"

void output(Student *students,int n)
{
    printf("name      age  ch     math   sum    ave    \n");
    for(int i=0;i<n;i++)
    {
        printf("%-10s%-5d%-7.2f%-7.2f%-7.2f%-7.2f\n",students[i].name,students[i].age,students[i].ch,students[i].math,students[i].sum,students[i].ave);
    }
    return ;
}