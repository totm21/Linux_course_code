
/*
    最后更改：2022/4/22       cz
*/
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<wait.h>
#include<string.h>
#include<stdbool.h>

#define KEY_ID 1234
#define SEM_NUM 3

#define SEM_ADD true
#define SEM_SUB false

//公用体定义
union semun  
{  
    int val;                        /*   value   for   SETVAL   */  
    struct semid_ds *buf;           /*   buffer   for   IPC_STAT,   IPC_SET   */          
    unsigned short *array;          /*   array   for   GETALL,   SETALL   */  
    /*   Linux   specific   part:   */  
    struct seminfo *__buf;          /*   buffer   for   IPC_INFO   */  
};

//创建或者获取信号量
int semaphore_get_id(key_t id,int number);

//初始化第index个信号量值为data
int semaphore_init(int semaphore_id,int index,int data);

//获取第index个信号量
int semaphore_get_value(int semaphore_id,int index);

//删除该信号量
int semaphore_del(int semaphore_id);

//对第index个信号量进行操作
int semaphore_opera(int semaphore_id,int index,bool flag);

int main(int argc,char* argv[])
{
    if(argc==1)
    {
        //信号量操作
        pid_t pid_id=fork();

        if(pid_id==0)
        {
            //子进程
            int semaphore_id=semaphore_get_id(KEY_ID,SEM_NUM);
            if(semaphore_id==-1)
            {
                
                perror("fail to get,because ");
                return 0;
            }
            else
            {
                //初始化
                int resu=semaphore_init(semaphore_id,0,1);
                if(resu==-1)
                {
                    perror("fail to init,because ");
                }

                //获取并显示
                printf("sem[0].val= %d \n",semaphore_get_value(semaphore_id,0));

                //p操作  -1
                resu=semaphore_opera(semaphore_id,0,SEM_SUB);
                if(resu!=0)
                {
                    //失败
                }
                else
                {

                    printf("sem[0].val= %d \n",semaphore_get_value(semaphore_id,0));
                    //等待5s
                    printf("sleep 5s\n");
                    sleep(5);
                    //v操作 +1
                    resu=semaphore_opera(semaphore_id,0,SEM_ADD);
                    if(resu!=0)
                    {
                        //失败
                    }
                    else
                    {
                        printf("sem[0].val= %d \n",semaphore_get_value(semaphore_id,0));
                    }

                }




            }

        }
        else if(pid_id>0)
        {
            //父进程
            wait(NULL);
        }
        else
        {
            //失败

        }

    }
    else if(argc==2)
    {
        //细致操作

        
        if(strcmp(argv[1],"del")==0) //删除该信号量
        {
            
            int semaphore_id=semaphore_get_id(KEY_ID,SEM_NUM);
            if(semaphore_id!=-1)
            {

                //获取成功,开始删除
                int resu=semaphore_del(semaphore_id);
                if(resu==-1)
                {
                    perror("fail to delete,because ");
                    return 0;
                }
                else
                {
                    printf("success to delete : %d\n",semaphore_id);
                }
            }

            
        }

    }

    return 0;
}







int semaphore_get_id(key_t id,int number)
{
    return semget(id,number,IPC_CREAT);
}

int semaphore_init(int semaphore_id,int index,int data)
{
    union semun operat;
    operat.val=data;
    return semctl(semaphore_id,index,SETVAL,operat);
}

int semaphore_get_value(int semaphore_id,int index)
{
    union semun operat;
    return semctl(semaphore_id,index,GETVAL,operat);
}


int semaphore_del(int semaphore_id)
{
    union semun operat;
    return semctl(semaphore_id,0,IPC_RMID,operat);
}

int semaphore_opera(int semaphore_id,int index,bool flag)
{
    if(flag)
    {
        printf("V begin\n");
    }
    else
    {
        printf("P begin\n");
    }
    struct sembuf opera;
    opera.sem_num=index;
    if(flag)
    {
        opera.sem_op=1;
    }
    else
    {
        opera.sem_op=-1;
    }
    opera.sem_flg=SEM_UNDO;
    int resu=semop(semaphore_id,&opera,1);
    if(flag)
    {
        printf("V end\n");
    }
    else
    {
        printf("P end\n");
    }
    return resu;
}




