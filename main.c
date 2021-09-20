#include "headers.h"
#include "promt.h"
#include "ls.h"
#include "command.h"
#include "pinfo.h"
#include "piping.h"
#include "redirection.h"
#include "env.h"
char check2[1000];
char prev[1000];
int checkpipe(char *buffer)
{
	int p=0;
	char *token;
	token=strtok(buffer,"|");
	while(token!=NULL)
	{
		p++;
		token=strtok(NULL,"|");
	}
	p--;
	return p;
}
int checkredir(char *word, char ops[5][5])
{
  int c;
  c = 0;
  for (int i = 0; i < strlen(word); i++)
  {
    if (word[i] == '<')
	{
      strcpy(&ops[c][0], "<");
	  c=c+1;
	}
    else if (word[i] == '>')
    {
	  if( (i + 1) < strlen(word) && word[i + 1] == '>')
	  {
      strcpy(&ops[c][0], ">>");
      i++;
	  c=c+1;
	  }
	  else
	  {
		strcpy(&ops[c][0], ">");
		c=c+1;
	  }
	  
    }
      
  }

  return c;
}
void execute(char *buffer)
{
	char *buffer2;
	char dir[1000],check[1000];
	getcwd(dir,sizeof(dir));
	getcwd(check,sizeof(check));
	strcpy(check2,check);
	buffer2=(char *)malloc(1000*sizeof(char));
	strcpy(buffer2,buffer);
			char *token = strtok(buffer," ");
			//printf("%s\n",buffer);

			if(!strcmp(token,"cd"))
			{
				token=strtok(NULL," ");
				if(!strcmp(token,"~"))
				{
					getcwd(prev,sizeof(prev));
					chdir(check);
					getcwd(dir,sizeof(dir));
				}
				else if(!strcmp(token,"-"))
				{
					char temp[1000];
					printf("%s\n",prev);
					strcpy(temp,prev);
					getcwd(prev,sizeof(prev));
					chdir(temp);

					
				}
				else
				{
					char temp[1000];
					getcwd(temp,sizeof(temp));
					if(chdir(token)<0)
					{

						perror(token);
					}
					else
					{
						strcpy(prev,temp);
					}
					
					
					getcwd(dir,sizeof(dir));
				}
			}
			else if(!strcmp(token,"pwd"))
			{
				printf("%s\n",dir);
			}
			else if(!strcmp(token,"echo"))
			{
				while(token != NULL)
				{
					token=strtok(NULL," ");
					if(token != NULL)
						printf("%s ",token);
				}
				printf("\n");
			}
			else if(!strcmp(token,"ls"))
			{
				dols(buffer2);
			}
			else if(!strcmp(token,"pinfo"))
			{
				pinfo(buffer2);
			}
			else if(!strcmp(token,"setenv"))
			{
				senv(buffer2);
			}
			else if(!strcmp(token,"unsetenv"))
			{
				unsenv(buffer2);
			}
			else if(!strcmp(token,"overkill"))
				overkill();
			else
			{
				run(buffer2);
			}

}
int main()
{
	getcwd(prev,sizeof(prev));
	char *buffer,*buffer2,*all;
	buffer=(char *)malloc(1000*(sizeof(char)));
	buffer2=(char *)malloc(1000*(sizeof(char)));
	all=(char *)malloc(1000*(sizeof(char)));
	size_t size=1000;
	char dir[1000],check[1000];
	int i,j,k,t;
	for(i=0;i<1000;i++)
	{
		dir[i]='\0';
		buffer[i]='\0';
		check[i]='\0';
		buffer2[i]='\0';
	}
	getcwd(dir,sizeof(dir));
	getcwd(check,sizeof(check));
	while(1)
	{
		signal(SIGCHLD,handler);
		//if(a==1)
		//	promt(check);
		promt(check);

		if(getline(&all,&size,stdin)==-1)
		{
			printf("\n");
		return 0;
		}
		char *token2;
		k=0;
		char *input[100];
		token2=strtok(all,";");
		while(token2!=NULL)
		{
			input[k]=token2;
			token2=strtok(NULL,";");
			k++;
		}
		
		for(t=0;t<k;t++)
		{
			
			strcpy(buffer,input[t]);
			if(buffer[strlen(buffer)-1]=='\n')
				buffer[strlen(buffer)-1]='\0';
			int p;
			char ops[5][5];
			char *buffer3,*buffer4,*buffer5;
			buffer3=(char *)malloc(1000*sizeof(char));
			buffer4=(char *)malloc(1000*sizeof(char));
			strcpy(buffer3,buffer);
			strcpy(buffer4,buffer);
			buffer5=(char *)malloc(1000*sizeof(char));
			strcpy(buffer5,buffer);
			p=checkpipe(buffer);
			if(p==0)
			{
				int c;
				c=checkredir(buffer3,ops);
				if(c!=0)
				{
					redirect(buffer4,ops,c);

				}
				else
				{
					if(!strcmp(buffer5,"quit"))
					{
						return 0;
					}
					execute(buffer5);
				}
				

			}
			else
			{
				piping(buffer5);
				
			}
		
			
			
		}
	}


}

