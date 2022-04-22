
/*
    此版线程不安全  慎重
    后续安全版本请等待作者阅读完源码再更新
    
    最后更改：2022/4/22       cz
*/

#include<pthread.h>
#include<unistd.h>
#include<stdio.h>

void *read_pthread(void* arg);
void *write_pthread(void* arg);

typedef struct NODE
{
    pthread_rwlock_t *rwlock_id;
    int* read_numbr;
    int* write_numbr;    
    int* index;
}node;

int main()
{
    //200个线程号
    pthread_t read_id[100]={0};
    pthread_t write_id[100]={0};

    //记录当前获得锁的数量
    int read_numbr=0;
    int write_number=0;

    int indexs[100];

    for(int i=0;i<100;i++)
    {
        indexs[i]=i;
    }
    
    //创建读写锁
    pthread_rwlock_t rwlock_id;
    pthread_rwlock_init(&rwlock_id,NULL);
    
    //100个传递参数
    node temporary[100];

    //传参赋值
    for(int i=0;i<100;i++)
    {
        temporary[i].index=indexs+i;
        temporary[i].read_numbr=&read_numbr;
        temporary[i].write_numbr=&write_number;
        temporary[i].rwlock_id=&rwlock_id;
    }

    printf("Reader Num : %d ; Writer Num : %d ;\n",rwlock_id.__data.__readers,rwlock_id.__data.__writers);

    //创建100个读进程 100个写进程
    for(int i=0;i<100;i++)
    {
        pthread_create(read_id+i,NULL,read_pthread,(void*)&temporary[i]);
        pthread_create(write_id+i,NULL,write_pthread,(void*)&temporary[i]);
    }

    for(int i=0;i<100;i++)
    {
        pthread_join(read_id[i],NULL);
        pthread_join(write_id[i],NULL);
    }

    pthread_rwlock_destroy(&rwlock_id);

    printf("Resources have been released\n");

    return 0;
}



void *read_pthread(void* arg)
{
    node* data=(node*)arg;

    pthread_rwlock_rdlock(data->rwlock_id);

    (*data->read_numbr)++;

    printf("Reader ID : %02d ; Reader Num : %d ; Writer Num : %d ;\n",*data->index,*data->read_numbr,*data->write_numbr);

    //sleep(1);
    usleep(50);

    (*data->read_numbr)--;

    pthread_rwlock_unlock(data->rwlock_id);


    return NULL;

}

void *write_pthread(void* arg)
{
    node* data=(node*)arg;

    int retu=pthread_rwlock_wrlock(data->rwlock_id);

    (*data->write_numbr)++;

    printf("Write  ID : %02d ; Reader Num : %d ; Writer Num : %d ;\n",*data->index,*data->read_numbr,*data->write_numbr);

    //sleep(1);

    (*data->write_numbr)--;

    retu=pthread_rwlock_unlock(data->rwlock_id);

    return NULL;

}

