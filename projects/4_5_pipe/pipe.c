
/*
    最后更改：2022/4/22    cz
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{

    if(argc==2)
    {
        if(strcmp(argv[1],"creat")==0)
        {
            int point=mkfifo("fifo",0777);        
            if(point==-1)
            {
                printf("Create a failure\n");
            }
            else
            {
                printf("Create a successful\n");
            }
        }
        else if(strcmp(argv[1],"delete")==0)
        {
            int point=unlink("fifo");        
            if(point==-1)
            {
                printf("delete a failure\n");
            }
            else
            {
                printf("delete a successful\n");
            }
        }
        else if(strcmp(argv[1],"read")==0)
        {
            char str[128];
            int point=open("fifo",O_RDONLY);
            if(point==-1)
            {
                printf("Open a failure\n");
                return 0;
            }
            read(point,str,128);
            printf("%s\n",str);
            close(point);
        }
    }
    else if(argc==3)
    {
        if(strcmp(argv[1],"creat")==0)
        {
            int point=mkfifo(argv[2],0777);        
            if(point==-1)
            {
                printf("Create a failure\n");
            }
            else
            {
                printf("Create a successful\n");
            }
        }
        else if(strcmp(argv[1],"delete")==0)
        {
            int point=unlink(argv[2]);        
            if(point==-1)
            {
                printf("delete a failure\n");
            }
            else
            {
                printf("delete a successful\n");
            }
        }
        else if(strcmp(argv[1],"write")==0)
        {
            int point=open("fifo",O_WRONLY);
            if(point==-1)
            {
                printf("Open a failure\n");
                return 0;
            }
            write(point,argv[2],strlen(argv[2]));
            close(point);
        }
        else if(strcmp(argv[1],"read")==0)
        {
            char str[128];
            int point=open(argv[2],O_RDONLY);
            if(point==-1)
            {
                printf("Open a failure\n");
                return 0;
            }
            read(point,str,128);
            printf("%s\n",str);
            close(point);
        }

    }
    else if(argc==4)
    {
        if(strcmp(argv[1],"write")==0)
        {
            int point=open(argv[2],O_WRONLY);
            if(point==-1)
            {
                printf("Open a failure\n");
                return 0;
            }
            write(point,argv[3],strlen(argv[3]));
            close(point);
        }
    }


    int point=mkfifo("pipefile",0777);
    if(point==-1)
    {
        printf("Create a failure,Try again\n");
        unlink("pipefile");
        point=mkfifo("pipefile",0777);
        if(point==-1)
        {
            printf("attempt failed,program end\n");
            return 0;
        }
    }

    unlink("pipefile");

    return 0;
}

