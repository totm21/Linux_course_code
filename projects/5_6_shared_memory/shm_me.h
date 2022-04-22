
/*
    最后更改：2022/4/22       cz
*/
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdbool.h>
#include<string.h>

#define KEY_T 1234
#define SIZE_STR 1024

struct node
{
    char str[SIZE_STR];
};
