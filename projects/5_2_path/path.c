
/*
    最后更改：2022/4/22       cz
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
int main(int argc,char *argv[])
{
    char *name;
    char value[50];
    if(argc==2)
    {
        time_t time_;
        time_=time(NULL);
        char * str=ctime(&time_);
        strcpy(value,str);
    }
    else if(argc==3)
    {
        strcpy(value,argv[2]);
    }
    else
    {
        printf("Incorrect parameter format\n");
        return 0;
    }
    name=argv[1];
    if(!setenv(name,value,1))
    {
        printf("modify successfully\n");
        printf("%s\n",getenv(name));
    }
    else
    {
        printf("fail to modify\n");
    }
    return 0;
}