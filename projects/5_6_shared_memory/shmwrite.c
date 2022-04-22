#include"shm_me.h"



int main(int argc,char* argv[])
{
    if(argc==2)
    {
        //创建共享内存
        int internal_id=shmget(KEY_T,sizeof(struct node),IPC_CREAT);
        if(internal_id==-1)
        {
            perror("fail to create ");
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
                strncpy(share->str,argv[1],SIZE_STR);
                int resu=shmdt(share);
                if(resu==-1)
                {
                    perror("fail to close ");
                }
                else
                {
                    printf("shm id = %d\n",internal_id);
                }
            }
        }
    }
    return 0;
}