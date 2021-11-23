#include<functions.h>

intl stdin_fd;
intl stdout_fd;

void printprompt(intl n,char home_dir[]){
	char sys_name[LEN];
	char usr_name[LEN];
	char cwd_name[LEN];
	gethostname(sys_name,LEN);
	getlogin_r(usr_name,LEN);
	getcwd(cwd_name,LEN);
	// printf("%s %s\n",cwd_name,home_dir);
	if(strstr(cwd_name,home_dir)!=NULL){
		char wrthome[LEN]="~";
		intl j=1;
		intl count1=0;
		for(intl i=n;i<strlen(cwd_name);i++){
			if(cwd_name[i]=='/'){
				count1=1;
			}
			wrthome[j++]=cwd_name[i];
		}
		if(strcmp(cwd_name,home_dir)==0){
			count1=1;
		}
		if(count1==1)
			printf("\033[01;31m<%s@%s\033[22;36m:%s>",usr_name,sys_name,wrthome);
		else
			printf("\033[01;31m<%s@%s\033[22;36m:%s>",usr_name,sys_name,cwd_name);
	}
	else{
		printf("\033[01;31m<%s@%s\033[22;36m:%s>",usr_name,sys_name,cwd_name);
	}	
}



