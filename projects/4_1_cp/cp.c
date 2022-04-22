
/*
    最后更改：2022/4/22    cz
*/
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    
    
    if(argc<3)
    {
        printf("parameter error!\n");
        return 0;
    }
    int file_source,file_goal;
    file_source=open(argv[1],O_RDONLY);
    if(file_source==-1)
    {
        printf("file does not exist!\n");
    }
    else
    {
        int *file_goal=(int *)malloc(sizeof(int)*(argc-2));
        mode_t old_mode=umask(0000);
        for(int i=0;i<argc-2;i++)
        {
            file_goal[i]=open(argv[2+i],O_CREAT|O_WRONLY,0777);
        }
        umask(old_mode);
        int empty=0;
        char str[51]={0};
        do
        {
            empty=read(file_source,str,50);
            str[empty]='\0';
            for(int i=0;i<argc-2;i++)
            {
                write(file_goal[i],str,empty);
            }
        }while(empty);
        for(int i=0;i<argc-2;i++)
        {
            close(file_goal[i]);
        }
        close(file_source);
    }
    return 0;
}