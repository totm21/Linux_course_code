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
    struct sockaddr_in my_addr;
    int val=1;
    setsockopt(sockf_id,SOL_SOCKET,SO_REUSEADDR,(char*)&val,sizeof(val));

    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVPORT);
    my_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(my_addr.sin_zero),8);

    if(bind(sockf_id,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
    {
        perror("fail to creat bind ");
        exit(1);
    }

    int backlog=10;
    if(listen(sockf_id,backlog)==-1)
    {
        perror("fail to listen ");
        exit(1);
    }

    int client_fd;
    struct sockaddr_in remote_addr;
    int sin_size;

    sin_size=sizeof(struct sockaddr_in);

    while(1)
    {
        if((client_fd=accept(sockf_id,(struct sockaddr*)&remote_addr,&sin_size))==-1)
        {
            perror("fail to accept ");
            exit(1);
        }

        printf("received a connection from %s\n",inet_ntoa(remote_addr.sin_addr));

        if(send(client_fd,"Hello,you are connected!\n",26,0)==-1)
        {
            perror("fail to send ");
            close(client_fd);
        }

        close(client_fd);
        printf("sleep(5) start \n");
        sleep(5);
        printf("sleep(5) end \n");

    }
    close(sockf_id);


    return 0;

}