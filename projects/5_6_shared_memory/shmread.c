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
        //映射
        void *point=shmat(internal_id,NULL,0);
        if(point==(void*)-1)
        {
            perror("fail to link ");
        }
        else
        {
            struct node* share=(struct node*)point;
            printf("shm id = %d : %s\n",internal_id,share->str);
            int resu=shmdt(share);
            if(resu==-1)
            {
                perror("fail to close ");
            }
        }
    }
}