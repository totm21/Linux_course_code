#include"tcp_me.h"

int main(int argc,char* argv[])
{
    int sockf_id;

    //创建套接字
    sockf_id=socket(AF_INET,SOCK_STREAM,0);
    //错误处理
    if(sockf_id==-1)
    {
        perror("fail to creat socket ");
        exit(1);
    }

    struct sockaddr_in serv_addr;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERVPORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(serv_addr.sin_zero),8);

    if(connect(sockf_id,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
    {
        perror("fail to connect ");
        exit(1);
    }

    char buf[100];
    int recvbytes;

    if((recvbytes=recv(sockf_id,buf,100,0))==-1)
    {
        perror("fail to recv ");
        exit(1);
    }
    
    buf[recvbytes]='\0';
    
    printf("Received : %s",buf);
    
    
    close(sockf_id);
    
    
    
    return 0;

}