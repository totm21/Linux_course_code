#include"msg_me.h"

int main(int argc,char* argv[])
{

    if(argc==2)
    {
        //生成key值
        key_t point=ftok(PATH,MSG_NUM);
        //错误处理 输出原因 程序结束
        if(point==-1)  
        {
            perror("Generate failure ");
            return 0;
        }

        //创建消息队列
        int msg_id=msgget(point,IPC_CREAT);
        //错误处理 输出原因 程序结束
        if(msg_id==-1)
        {
            perror("fail to create");
            return 0;
        }
        else
        {
            //发送信息
            struct msgbuf mess;
            mess.mtype=1;
            strncpy(mess.mtext,argv[1],MAX_SIZE);
            int resu=msgsnd(msg_id,(void*)&mess,MAX_SIZE,0);
            if(resu==-1)
            {
                perror("fail to send ");
                return 0;
            }
            else
            {
                printf("\" %s \" success send for msg id: %d \n",argv[1],msg_id);
            }
        }
    }
    return 0;

}