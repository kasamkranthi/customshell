#include "headers.h"
#include "promt.h"
#include "command.h"
void promt(char present[])
{
    char *username;
    char *hostname;
    char dir[1000];

    getcwd(dir,sizeof(dir));
    //printf("%s\n",dir);
    //char present[1000];
    char printer[1000];
    int i,j;
    for(int i=0;i<1000;i++)
    {
        //present[i]='\0';
        printer[i]='\0';
    }
    //getcwd(present,sizeof(present));
	username=(char *)malloc(100*sizeof(char));
    hostname=(char *)malloc(100*sizeof(char));
    gethostname(hostname,100);
	username=getlogin();
    if(strcmp(dir,present)==0)
    {
        printer[0]='~';
        printf("<%s@%s:%s> ",username,hostname,printer);
        
    }
    else
    {
        for(i=0;i<strlen(present);i++)
        {
            if(present[i]!=dir[i])
                break;
        }
        if(i==strlen(present))
        {
            printer[0]='~';
            for(j=1;i<strlen(dir);i++,j++)
            {
                printer[j]=dir[i];
            }
            printf("<%s@%s:%s> ",username,hostname,printer);
        }
        else
            printf("<%s@%s:%s> ",username,hostname,dir);
    }
    
    
    for(int i=0;i<strlen(printer);i++)
        printer[i]='\0';
	
}