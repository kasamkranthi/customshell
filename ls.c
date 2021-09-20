#include "headers.h"
#include "ls.h"

int is_a_filter(const struct dirent *p)
{
	if((p->d_name)[0]=='.')
	{
		return false;
	}
	else
		return true;
}

char *time_as_req(time_t tmp)
{
	char *buff;
	buff=(char *)malloc(100*sizeof(char));
	struct tm * tm_tmp = localtime(&tmp);
	strftime(buff,100,"%b %d %H: %M",tm_tmp);
	return buff;
}

int lexi_sort(const struct dirent **a, const struct dirent **b)
{
	int p;
	p=strcasecmp((*a)->d_name,(*b)->d_name);
	if(p==0)
		return 0;
	if(p>0)
		return 1;
	if(p<0)
		return -1;
}

char *path(char * parent_path,char *file_name)
{
	char *absol_path=malloc(100*sizeof(char));
	if(!(file_name[0]=='/'))
	{
		strcpy(absol_path,parent_path);
		strcat(absol_path,"/");
		strcat(absol_path,file_name);
		return absol_path;
		
	}
	else
	{
		return file_name;
	}
}

char *detecting_parent(char *cwd_name)
{
	int tmp;
	int i;
	char *parent;
	for(i=strlen(cwd_name)-1;i>=0;i--)
	{
		if(cwd_name[i]=='/')
		{
			tmp=i;
			break;
		}
	}
	parent=(char *)malloc(tmp*sizeof(char));
	strncpy(parent,cwd_name,tmp);
	return parent;
}

int check_fordot(const struct dirent *a)
{
	if(!strncmp(a->d_name,".",1))
		return 0;
	else
		return 1;
}



void display_long(struct dirent **dir_list,int cnt,char *parent_path)
{   struct stat tmp_stat;
	int i;
    stat(parent_path,&tmp_stat);
    printf("total %ld\n",tmp_stat.st_nlink);



    for(i=0;i<cnt;i++)
    {
	struct stat cur_stat;
	struct dirent *cur_dir = dir_list[i];
	char type;
    stat(path(parent_path,cur_dir->d_name),&cur_stat);
	char permissions[9];
    if(S_ISDIR(cur_stat.st_mode))
    type='d';
    else if(S_ISLNK(cur_stat.st_mode))
    type ='l';
    else
    type = '-';

    permissions[0]=(cur_stat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[1]=(cur_stat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[2]=(cur_stat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[3]=(cur_stat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[4]= (cur_stat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[5]= (cur_stat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[6]=(cur_stat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[7]= (cur_stat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[8]= (cur_stat.st_mode & S_IXOTH) ? 'x' : '-';
	
	long long int file_sz,no_of_links;
    struct passwd *p;
	p=getpwuid(cur_stat.st_uid);
    struct group  *g;
    g=getgrgid(cur_stat.st_gid);
    char *username = p->pw_name;
    char *groupname= g->gr_name;

    file_sz= cur_stat.st_size;
	char *tm_as_req = time_as_req(cur_stat.st_mtime);
    no_of_links= cur_stat.st_nlink;


    printf("%c%s %lld %s %s %lld %s %s\n",type,permissions,no_of_links,username,groupname,file_sz,tm_as_req,cur_dir->d_name);
    }
    printf("\n");

}

void display_short(struct dirent **dir_list,int cnt,char *parent_path)
{
	int i;
	for(i=0;i<cnt;i++)
	{
		printf("%s\n",dir_list[i]->d_name);
	}
	printf("\n");
}




void dols(char arr[])
{
    char buf[1000];
    int i,pieces;
    bool is_a=false, is_l=false;
    getcwd(buf,sizeof(buf));
    char* input[100];
    char* token;
    char* dirs[25];
    int no_of_dirs=0;
    token=strtok(arr," ");
    i=0;
    while(token!=NULL)
    {
	    input[i]=token;
	    token=strtok(NULL," ");
	    i++;

    }
    pieces=i;
    int j;
    for(i=1;i<pieces;i++)
    {
	    if(!strcmp(input[i],"-l"))
	    {
		    is_l=true;
	    }
	    else if(!strcmp(input[i],"-a"))
            {
                    is_a=true;
            }
	    else if(!strcmp(input[i],"-la"))
            {
                    is_l=true;
		    is_a=true;
            }
	    else if(!strcmp(input[i],"-al"))
            {
		    is_a=true;
                    is_l=true;
            }
	    else if(strlen(input[i])==1 && (!strcmp(input[i],".")))
	    {
		    dirs[no_of_dirs]=buf;
	    }
	    else if(strlen(input[i])==2 && (!strcmp(input[i],"..")))
	    {
		    dirs[no_of_dirs]=buf;
		    for(j=strlen(dirs[no_of_dirs])-1;j>0;j--)
		    {
			    if(dirs[no_of_dirs][j]!='/')
				    dirs[no_of_dirs][j]='\0';
			    else
				    break;
		    }
		    dirs[no_of_dirs][j]='\0';
	    }
	    else
	    {
		    dirs[no_of_dirs]=input[i];
	    	no_of_dirs++;
	    }
    }
    if(!no_of_dirs)
    {
	    dirs[no_of_dirs]=buf;
	    no_of_dirs++;
    }
    for(i=0;i<no_of_dirs;i++)
    {
	    int no_of_files;
	    struct dirent **dir_list;
	    if(is_a && is_l)
	    {
		    no_of_files=scandir(path(buf,dirs[i]),&dir_list,NULL,&lexi_sort);
		    display_long(dir_list,no_of_files,dirs[i]);
	    }
	    if(is_a && !is_l)
            {
                    no_of_files=scandir(path(buf,dirs[i]),&dir_list,NULL,&lexi_sort);
                    display_short(dir_list,no_of_files,dirs[i]);
            }
	    if(!is_a && is_l)
            {
                    no_of_files=scandir(path(buf,dirs[i]),&dir_list,&is_a_filter,&lexi_sort);
                    display_long(dir_list,no_of_files,dirs[i]);
            }
	    if(!is_a && !is_l)
            {
                    no_of_files=scandir(path(buf,dirs[i]),&dir_list,&is_a_filter,&lexi_sort);
                    display_short(dir_list,no_of_files,dirs[i]);
            }

	    if(no_of_files<0)
	    {
		    char temp[]="ls cannot access  ";
		    strcat(temp,dirs[i]);
		    perror(temp);
	    }
    }


}
