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
        close(sockf_id);
        exit(1);
    }

    struct sockaddr_in client_addr,addr;
    int len = sizeof(struct sockaddr_in);
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(CLIENT);
    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    char str[100];
    while(1)
    {
        int resu=recvfrom(sockf_id,str,sizeof(str),0,(struct sockaddr*)&addr,&len);
        //printf("%d\n",resu);
        if(resu>0)
        {
            str[resu]='\0';
            printf("You got a message (%s) from %s\n",str,inet_ntoa(addr.sin_addr));
            resu=sendto(sockf_id,str,strlen(str),0,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_in));
            if(resu<0)
            {
                perror("send error ");
                break;
            }
            else
            {

            }

        }
        else
        {
            perror("recv ");
            break;
        }
    }

    close(sockf_id);


    return 0;

}