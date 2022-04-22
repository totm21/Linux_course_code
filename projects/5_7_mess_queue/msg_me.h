
/*
    最后更改：2022/4/22    cz
*/
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>


#define PATH "key.msg"
#define MSG_NUM 1234

#define MAX_SIZE 1024

struct msgbuf 
{
    long mtype;             //消息的类型
    char mtext[MAX_SIZE];   //消息正文
};