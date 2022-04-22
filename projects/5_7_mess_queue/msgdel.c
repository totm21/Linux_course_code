#include"msg_me.h"

int main(int argc,char* argv[])
{
    //生成key值
    key_t point=ftok(PATH,MSG_NUM);
    //错误处理 输出原因 程序结束
    if(point==-1)  
    {
        perror("Generate failure ");
        return 0;
    }

    //获取消息队列
    int msg_id=msgget(point,IPC_CREAT);
    //错误处理 输出原因 程序结束
    if(msg_id==-1)
    {
        perror("fail to get ");
        return 0;
    }

    //删除操作
    int resu=msgctl(msg_id,IPC_RMID,0);
    if(resu==-1)
    {
        perror("fail to delete ");
    }
    else if(resu==0)
    {
        printf("deleted msg id = %d \n",msg_id);
    }
    return 0;
}