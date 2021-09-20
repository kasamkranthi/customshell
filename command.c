#include "headers.h"
#include "command.h"
#include "promt.h"
int pids[100];
char pid_arrays[100][100];
int size;

void overkill()
{  
   for(int i=0;i<size;i++)
   {
	      kill(pids[i],SIGKILL);

   }


}
void handler()
{
	//printf("I came here\n");
	while(true)
	{
	char *pr_name;
	int corpse,status;
		//printf("1\n");
		corpse=waitpid((pid_t)-1, &status, WNOHANG);
		if(corpse>0)
		{
			int i;
			for(i=0;i<size;i++)
			{
				if(pids[i]==corpse)
					break;
			}

			//printf("%s\n",pid_arrays[i]);
			if(i<size)
			{
				printf("\n%s with pid %d exited normally\n",pid_arrays[i],pids[i]);
			}
			//promt(check2);
		//return 1;	
		}
		else
		{
			return ;
		}
		//printf("done\n");
	}
	
}

void run(char buffer[])
{
	//printf("%s\n",buffer);
	int i,child;
	size=0;
	char buffer2[1000];
	strcpy(buffer2,buffer);
	//printf("%s\n",buffer2);
	//int pids[100];
	//int *pid_arrays[100];
	char *input[100];
	char* token = strtok(buffer, " "); 
	i=0;
	//printf("%s\n",buffer);

	while (token != NULL) { 
		input[i]=token;
		i++; 
		token = strtok(NULL, " "); 
	}
	//printf("%s",input[1]);

	if(strcmp(input[i-1],"&")) 
	{
		child=fork();
		input[i]=NULL;
		if(child==0)
		{
			int check;
			check=execvp(input[0],input);
			if(check<0)
			{
				printf("%s: command not found\n",input[0]);
			}
		}
		else
		{
			wait(NULL);
			//printf("child is executed\n");
		}

	}
	else
	{
		input[i-1]=NULL;

		child=fork();
		int check;

		if(child==0)
		{
			setpgid(0,0);
			check=execvp(input[0],input);
			if(check<0)
			{
				printf("%s command not found\n",buffer2);
			}
		}
		else
		{

			for(i=strlen(buffer2);i>0;i--)
                                if(buffer2[i]=='&')
                                        buffer2[i]='\0';
			printf("started %s, with pid %d\n",buffer2,child);
			
			pids[size]=child;
			strcpy(pid_arrays[size],buffer2);
			size++;
		}
	}

}
