
/*
    最后更改：2022/4/22    cz
*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>

//长字符串解析拆分(包含去除多余空格)   
int split_str(char* str,char** str_group);



int main(int argc,char* argv[])
{
    pid_t id;
    char str[64];
    char* cmd[64];

    while(1)
    {
        pid_t pid=getpid();
        printf("%d$",pid);
        fgets(str,64,stdin);
        if(strcmp(str,"exit\n")==0)
        {
            break;
        }
        if(strcmp(str,"logout\n")==0)
        {
            break;
        }

        char **str_group=(char**)malloc(sizeof(char*)*32);
        for(int i=0;i<32;i++)
        {
            str_group[i]=(char*)malloc(sizeof(char)*32);
        }

        split_str(str,str_group);

        /*

        //字符串解析测试 ----暂时没什么问题
        int point_traversal=0;
        while(str_group[point_traversal]!=NULL)
        {
            printf("%s\n",str_group[point_traversal++]);
        }

        */
        

        //申请新进程
        pid_t id=fork();

        if(id<0)
        {
            //进程创建失败  程序结束
            printf("Process creation failure！\n");
            return 0;
        }
        else if(id==0)
        {
            //子进程 新进程执行相应指令

            char path[32]="/bin/";
            strcat(path,str_group[0]); 

            //printf("%s %s %s\n",path,str_group[0],str_group[1]);


            //此部分为指令具体实现   具体分为两种：1.系统调用(直接调用execv)  2.非系统调用   
            if(strcmp(str_group[0],"cat")==0)
            {
                execv(path,str_group);
            }
            else if(strcmp(str_group[0],"ls")==0)
            {   
                execv(path,str_group);
            }
            else if(strcmp(str_group[0],"ps")==0)
            {
                execv(path,str_group);
            }
            else
            {
                printf("unknown command\n");
            }


            //子进程结束  回归父进程  等待新指令
            return 0;
        }
        else
        {

            //等待子进程结束
            wait(NULL);

            //堆资源释放
            for(int i=0;i<32;i++)
            {
                if(str_group[i]!=NULL)
                {
                    free(str_group[i]);
                }
                else
                {
                    break;
                }
            }
            free(str_group);

        }
        
        
    
    }
    return 0;
}


int split_str(char* str,char**str_group)
{
    int str_len=strlen(str);
    int point_str=0,point_str_bit=0;
    int i=-1;
    while(str[++i]==' ');
    for(;i<str_len-1;i++)
    {
        if(str[i]==' ')
        {
            if(str[i-1]==' ')
            {
                continue;
            }
            str_group[point_str][point_str_bit]='\0';
            point_str++;
            point_str_bit=0;
        }
        else
        {
            str_group[point_str][point_str_bit++]=str[i];
        }
    }
    str_group[point_str++][point_str_bit]='\0';
    
    for(;point_str<32;)
    {
        free(str_group[point_str]);
        str_group[point_str++]=NULL;
    }
    
    
    return point_str;
}

