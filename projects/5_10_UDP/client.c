#include"tcp_me.h"

int main(int argc,char* argv[])
{
    int sockf_id;

    //创建套接字
    sockf_id=socket(AF_INET,SOCK_DGRAM,0);
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

    struct sockaddr_in addr,client_addr;
    int len=sizeof(struct sockaddr_in);
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(CLIENT);
    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    char buf[100];
    char out[100];
    int recvbytes;

    if(bind(sockf_id,(struct sockaddr*)&client_addr,sizeof(struct sockaddr))==-1)
    {
        perror("fail to creat bind ");
        close(sockf_id);
        exit(1);
    }

    while(1)
    {
        printf("input: ");
        scanf("%s",buf);
        if(strcmp(buf,"quit")==0)
        {
            close(sockf_id);
            exit(0);
        }
        recvbytes=sendto(sockf_id,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr));
        if(recvbytes<0)
        {
            perror("send ");
            break;
        }
        else
        {
        }

        recvbytes=recvfrom(sockf_id,out,sizeof(out),0,(struct sockaddr*)&client_addr,&len);
        if(recvbytes>0)
        {
            out[recvbytes]='\0';
            printf("Sever Message : %s\n",out);
        }
        else
        {
            perror("recv");
            break;
        }




        
    }
    
    
    close(sockf_id);
    
    
    
    return 0;

}