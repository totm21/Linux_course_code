
/*
    最后更改：2022/4/22       cz
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    char *month[]={"jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    time_t time_;
    struct  tm* time_struct;

    time(&time_);
    time_struct=localtime(&time_);
    
    char time[120]={0};
    int time_len=0;

    time_len=strftime(time,120,"%c",time_struct);

    //printf("%s\n",time);
    
    mode_t old_mode=umask(0000);
    int f_change;
    f_change=open("out.txt",O_CREAT|O_WRONLY,0777);
    if(f_change!=-1)
    {
        write(f_change,time,time_len);
        close(f_change);
    }
    umask(old_mode);
    
    return 0;
}