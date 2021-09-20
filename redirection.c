#include "headers.h"
#include "redirection.h"

void redirect(char *word, char ops[5][5], int num)
{
    int index,j;
    index=0;
    char files[5][10000];
    j = num;
    int i;
    for (i = strlen(word); i >= 0; i--)
    {
        if (word[i] == '<')
        {
            if (i + 1 < strlen(word))
            {
                if(word[i + 1] != '\0')
                {
                strcpy(files[j], &word[i + 1]);
                j=j-1;
                }
            }
            word[i] = '\0';
        }
        if (word[i] == '>')
        {
            if (i + 1 < strlen(word) )
            {
                if(word[i + 1] != '\0')
                {
                strcpy(files[j], &word[i + 1]);
                j=j-1;
                }
                word[i]='\0';
            }
            word[i] = '\0';
        }
    }
   
    int in;
    int out;
     strcpy(files[0], word);
    pid_t pid = fork();
    int status;

    if (pid < 0)
    {
        fprintf(stderr, "Error in forking");
    }
    else if (pid == 0)
    {
        int i;
        for (i = 0; i < num; i++)
        {
            int temp;
            temp = 0;
            while (files[i+1][temp] == ' ')
            {
                temp=temp+1;
            }
            int j;
            for ( j = temp; j < strlen(files[i + 1])+1; j++)
            {
                int temp2;
                temp2=j-temp;
                files[i + 1][temp2] = files[i + 1][j];
            }
            int k;
            k=strlen(word);
            while (files[i+1][k - 1] == ' ')
            { 
                files[i+1][k - 1] = '\0';
                j=j+1;
                k=strlen(word);
            }

            if (strcmp(ops[i], "<") == 0)
            {
                
                char *token;
                int k;
                token = strtok(files[i+1]," ");
                k=i+1;
                strcpy(files[k],token);
                in = open(files[i + 1], O_RDONLY);
                if (in >= 0)
                {
                     dup2(in, 0);
                    close(in);
                    
                }

                else
                {
                   fprintf(stderr, "Error opening file %s\n", files[i + 1]);
                    exit(0);
                }
            }

            else
            {
                if (strcmp(ops[i], ">") == 0)
                {
                
                    close(out);
                     char *token;
                     int k;
                token = strtok(files[i+1]," ");
                k=i+1;
                strcpy(files[k],token);
                    out = open(files[i + 1],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
                    int j;
                     if (out >= 0)
                    {
                        dup2(out, 1);
                        close(out);
                        
                    }
                    else
                    {
                     fprintf(stderr, "Error opening file %s", files[i + 1]);
                     exit(0);   
                    }
                }
                else
                {

                     char *token;
                     int k;
                token = strtok(files[i+1]," ");
                k=i+1;
                strcpy(files[k],token);
                
                    out = open(files[i + 1], O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    int j;
                     if (out >= 0)
                    {
                         dup2(out, 1);
                        close(out);
                        
                    }
                    else
                    {
                        fprintf(stderr, "Error opening file %s", files[i + 1]);
                        exit(0);
                       
                    }

                }

            }
        }
        execute(files[0]);
        exit(0);
    }

    else
    {
        while (wait(&status) != pid);
    }
}