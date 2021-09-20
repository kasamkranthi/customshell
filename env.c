#include "headers.h"
#include "env.h"
void unsenv(char *buffer)
{
    char *token;
    token=strtok(buffer," ");
    char *args[100];
    int n=0;
    while(token!=NULL)
    {
        args[n]=token;
        token=strtok(NULL," ");
        n++;

    }

    if (n == 1)
        fprintf(stderr,"unsetenv: Too few arguments\n");

    else
    {
        int i;
        for ( i = 1; i < n;)
        {
            if (unsetenv(args[i]) < 0)
                perror("Error in unsetenv");
            i=i+1;
        }
    }
}

void senv(char *buffer)
{
    char *token;
    token=strtok(buffer," ");
    char *args[100];
    int n=0;
    while(token!=NULL)
    {
        args[n]=token;
        token=strtok(NULL," ");
        n++;

    }

    if (n == 1 || n==2 || n==3)
    {
        if(n==1)
            fprintf(stderr,"setenv: Too few arguments\n");
        if(n==2)
        {
        if (setenv(args[1], "", 1) < 0)
            perror("Error in setenv");
        }
        if(n==3)
        {
             if (setenv(args[1], args[2], 1) < 0)
            perror("Error in setenv");
        }
    }
        

    else
        fprintf(stderr,"setenv: Too many arguments");
}


