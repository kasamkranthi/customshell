#include "headers.h"
#include "piping.h"
#include "redirection.h"

void piping(char *buffer)
{
    int i;
    int num;
    char *tokens[100];
    char *token;
    i=0;
    token=strtok(buffer,"|");
    while(token!=NULL)
    {
        tokens[i]=token;
        token=strtok(NULL,"|");
        i++;

    }
    num=i;
    int in;
    int out;
    in = 0;
    out = 1;

    for ( i = 0; i < num; i++)
    {

        int p[2];
        char *buffer2,*buffer3;
         pipe(p);
        pid_t pid = fork();
        buffer2=(char *)malloc(1000*sizeof(char));
         buffer3=(char *)malloc(1000*sizeof(char));
       
        if (pid < 0)
        {
            fprintf(stderr, "Error in forking");
        }
        else if (pid == 0)
        {
            int c;
            dup2(in, 0);
            char ops[5][5];
            strcpy(buffer2,tokens[i]);
            if (i != num - 1)
                dup2(p[1], 1);

            close(p[0]);

            strcpy(buffer3,tokens[i]);

            c = checkredir(tokens[i], ops);
            if (c != 0)
            {
                redirect(buffer2, ops, c); 
            }
            else execute(buffer3);
            exit(1);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            out = p[1];
            in = p[0];
        }
    }

}