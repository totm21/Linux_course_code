#include"lib.h"

int main()
{
    Student *students;
    int student_number;
    printf("Please enter number of people\n");
    scanf("%d",&student_number);
    input(&students,student_number);
    //printf("%f\n",students[0].ch);
    calculate(students,student_number); 
    output(students,student_number);
    return 0;
}