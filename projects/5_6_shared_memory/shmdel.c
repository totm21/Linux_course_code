#include"shm_me.h"


int main(int argc,char* argv[])
{
    //获得共享内存
    int internal_id=shmget(KEY_T,sizeof(struct node),IPC_CREAT);
    if(internal_id==-1)
    {
        perror("fail to get ");
    }
    else
    {
        int resu=shmctl(internal_id,IPC_RMID,0);
        if(resu==-1)
        {
            perror("fail to delete ");
        }
        else
        {
            printf("shm %d deleted\n",internal_id);
        }
    }
    return 0;
}