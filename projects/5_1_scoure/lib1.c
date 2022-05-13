#include"lib.h"


void input(Student **students,int n)
{
    *students=(Student*)malloc(sizeof(Student)*n);
    for(int i=0;i<n;i++)
    {
        printf("please input %d student-name:",i+1);
        scanf("%s",students[i]->name);
        //scanf("%s",students[i]->name);
        printf("please input %d student-age:",i+1);
        scanf("%d",&(*students)[i].age);
        printf("please input %d student-ch:",i+1);
        scanf("%f",&(*students)[i].ch);
        printf("please input %d student-math:",i+1);
        scanf("%f",&(*students)[i].math);
    }
    return ;
}