#include "headers.h"
#include "pinfo.h"
void pinfo(char buf[])
{
	char *token;
	token=strtok(buf," ");
	char* input[100];
	int i=0;
	while(token!=NULL)
	{
		input[i]=token;
		token=strtok(NULL," ");
		i++;
	}
	if(i==1)
	{
		int current_pid,temp;
		char buff[1024]="~/a.out";
		FILE *f;
		char status[1000],memory[1000],process_status[1000],act_mem[1000];
		f=fopen("/proc/self/status","r");

		for(temp=0;temp!=1;)
		{
			fgets(status,1000,f);
			temp++;
		}
		fscanf(f,"%s %s",status,process_status);
		for(;1;)
		{
			fgets(memory,1000,f);
			if(strstr(memory,"VmPeak"))
			{
				break;
			}
		}
		current_pid=getpid();
		fscanf(f,"%s %s",memory,act_mem);
                printf("Pid -- %d\nProcess Status -- %s\nmemory -- %s\nExecutable path -- %s\n", current_pid,process_status,act_mem,buff);
                fclose(f);

        }
	else
	{
		int temp=0,buflen=1024;
		char temp1[1024]="/proc/";
		strcat(temp1,input[1]);
		char temp2[1024]="/proc/";
		strcat(temp2,input[1]);
		strcat(temp1,"/status");
		strcat(temp2,"/cmdline");
		char memory[1000],process_status[1000],act_mem[1000],status[1000],buff[1024];
		FILE *file;
		file=fopen(temp2,"r");
		if(file==NULL)
			perror(input[1]);
		else
		{
		fgets(buff,1024,file);
		fclose(file);
		file=fopen(temp1,"r");
		for(temp=0;temp!=1;)
		{
                        fgets(status,1000,file);
			temp++;
		}
                fscanf(file,"%s %s",memory,process_status);
                for(;1;)
                {
                        fgets(memory,1000,file);
                        if(strstr(memory,"VmPeak"))
                        {
                                break;
                        }
                }
                fscanf(file,"%s %s",status,act_mem);
               printf("Pid -- %s\nProcess Status -- %s\nmemory -- %s\nExecutable path -- %s\n", input[1],process_status,act_mem,buff);
                fclose(file);
		}

        }
}




		
