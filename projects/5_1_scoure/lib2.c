#include"lib.h"

void calculate(Student *students,int n)
{
    for(int i=0;i<n;i++)
    {
        students[i].sum=students[i].ch+students[i].math;
        students[i].ave=students[i].sum/2.0;
        
    }
    return ;
}