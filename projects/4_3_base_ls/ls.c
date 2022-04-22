
/*
    最后更改：2022/4/22    cz
*/
#include<sys/stat.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<dirent.h>

typedef struct FILE_MESSAGE
{
    char *file_name;
    char file_type;
    bool file_user_r;
    bool file_user_w;
    bool file_user_x;
    bool file_group_r;
    bool file_group_w;
    bool file_group_x;
    bool file_other_r;
    bool file_other_w;
    bool file_other_x;
    unsigned int file_link_number;
    char* file_user_name;
    char* file_group_name;
    long file_size;
    struct tm * file_last_time;
}message;

void ls_dir(char * name);
char file_type_identification(char * name);
void ls_l(char * name);
void print(message file);
void ls_l_dir(char * name);


int main(int argc,char *argv[])
{
    if(argc==1)
    {
        char name[2]=".";    
        ls_dir(name);
    }
    else if(argc==2)
    {  
        if(!strcmp(argv[1],"-l"))
        {
            char name[2]=".";    
            ls_l_dir(name);
        } 
        else
        {
            ls_dir(argv[1]);
        }
    }
    else if(argc==3)
    {
        ls_l_dir(argv[2]);
    }
}

void ls_dir(char * name)
{
    DIR *dir;
    dir=opendir(name);
    if(dir!=NULL)
    {
        struct dirent * dir_message;
        bool flag_n=false;
        do
        {
            dir_message=readdir(dir);
            if(dir_message!=NULL)
            {
                if(strcmp(dir_message->d_name,"..")==0||strcmp(dir_message->d_name,".")==0)
                {
                    continue;
                }
                else
                {
                    //printf("%s|\n",dir_message->d_name);
                    char new_name[256]="";
                    if(!strcmp(name,"0"))
                    {
                        strcpy(new_name,name);
                        strcat(new_name,"/");
                    }
                    strcat(new_name,dir_message->d_name);
                    printf("%s ",new_name);
                    flag_n=true;
                    //ls_l(new_name);
                }
            }
        }while(dir_message);
        if(flag_n)
        {
            printf("\n");
        }

    }
    else
    {
        printf("File opening failure!\n");
    }
    return ;
}



char file_type_identification(char * name)
{
    struct stat file_message;
    int result;
    result=stat(name,&file_message);
    if(result!=0)
    {
        printf("File not found!\n");
    }

    if(S_ISREG(file_message.st_mode))
    {
        return '-';
    }
    else if(S_ISDIR(file_message.st_mode))
    {
        return 'd';
    }
    else if(S_ISBLK(file_message.st_mode))
    {
        return 'b';
    }
    else if(S_ISCHR(file_message.st_mode))
    {
        return 'c';
    }
    else if(S_ISFIFO(file_message.st_mode))
    {
        return 'p';
    }
    else if(S_ISSOCK(file_message.st_mode))
    {
        return 's';
    }
    else if(S_ISLNK(file_message.st_mode))
    {
        return 'l';
    }
}

void ls_l(char * name)
{
    struct stat file_message;
    int result;
    result=stat(name,&file_message);
    /*
    //此处会出现result==-1的情况  但不影响程序运行   
    if(result==-1)
    {
        perror("file ");
        printf("File not found!\n");
    }
    */

    message conversion_results;

    conversion_results.file_name=name;

    if(S_ISREG(file_message.st_mode))
    {
        conversion_results.file_type='-';
    }
    else if(S_ISDIR(file_message.st_mode))
    {
        conversion_results.file_type='d';
    }
    else if(S_ISBLK(file_message.st_mode))
    {
        conversion_results.file_type='b';
    }
    else if(S_ISCHR(file_message.st_mode))
    {
        conversion_results.file_type='c';
    }
    else if(S_ISFIFO(file_message.st_mode))
    {
        conversion_results.file_type='p';
    }
    else if(S_ISSOCK(file_message.st_mode))
    {
        conversion_results.file_type='s';
    }
    else if(S_ISLNK(file_message.st_mode))
    {
        conversion_results.file_type='l';
    }

    /*
    if(conversion_results.file_type=='d')
    {
        ls_l_dir(name);
        return ;
    }
    */

    if(file_message.st_mode&S_IRUSR)
    {
        conversion_results.file_user_r=true;
    }
    else
    {
        conversion_results.file_user_r=false;
    }

    if(file_message.st_mode&S_IWUSR)
    {
        conversion_results.file_user_w=true;
    }
    else
    {
        conversion_results.file_user_w=false;
    }

    if(file_message.st_mode&S_IXUSR)
    {
        conversion_results.file_user_x=true;
    }
    else
    {
        conversion_results.file_user_x=false;
    }



    if(file_message.st_mode&S_IRGRP)
    {
        conversion_results.file_group_r=true;
    }
    else
    {
        conversion_results.file_group_r=false;
    }

    if(file_message.st_mode&S_IWGRP)
    {
        conversion_results.file_group_w=true;
    }
    else
    {
        conversion_results.file_group_w=false;
    }

    if(file_message.st_mode&S_IXGRP)
    {
        conversion_results.file_group_x=true;
    }
    else
    {
        conversion_results.file_group_x=false;
    }




    if(file_message.st_mode&S_IROTH)
    {
        conversion_results.file_other_r=true;
    }
    else
    {
        conversion_results.file_other_r=false;
    }

    if(file_message.st_mode&S_IWOTH)
    {
        conversion_results.file_other_w=true;
    }
    else
    {
        conversion_results.file_other_w=false;
    }

    if(file_message.st_mode&S_IXOTH)
    {
        conversion_results.file_other_x=true;
    }
    else
    {
        conversion_results.file_other_x=false;
    }

    conversion_results.file_link_number=file_message.st_nlink;

    conversion_results.file_user_name=(getpwuid(file_message.st_uid)->pw_name);

    conversion_results.file_group_name=(getgrgid(file_message.st_gid)->gr_name);

    conversion_results.file_size=file_message.st_size;

    file_message.st_mtime++;

    conversion_results.file_last_time=localtime((time_t*)(&file_message.st_mtime));

    print(conversion_results);
    return;
}

void print(message file)
{
    printf("%c",file.file_type);
    if(file.file_user_r)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if(file.file_user_w)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if(file.file_user_x)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if(file.file_group_r)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if(file.file_group_w)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if(file.file_group_x)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if(file.file_other_r)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if(file.file_other_w)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if(file.file_other_x)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    printf(" %d %s %s %ld ",file.file_link_number,file.file_user_name,file.file_group_name,file.file_size);
    printf("%dmonth ",file.file_last_time->tm_mon+1);
    printf("%d ",file.file_last_time->tm_mday);
    printf("%d:",file.file_last_time->tm_hour);
    printf("%d ",file.file_last_time->tm_min);
    printf("%s\n",file.file_name);
    return ;
}

void ls_l_dir(char * name)
{
    DIR *dir;
    dir=opendir(name);
    if(dir!=NULL)
    {
        struct dirent * dir_message;
        do
        {
            dir_message=readdir(dir);
            if(dir_message!=NULL)
            {
                if(strcmp(dir_message->d_name,"..")==0||strcmp(dir_message->d_name,".")==0)
                {
                    continue;
                }
                else
                {
                    //printf("%s|\n",dir_message->d_name);
                    char new_name[256]="";
                    if(!strcmp(name,"0"))
                    {
                        strcpy(new_name,name);
                        strcat(new_name,"/");
                    }
                    strcat(new_name,dir_message->d_name);
                    ls_l(new_name);
                }
            }
        }while(dir_message);
    }
    return ;
}