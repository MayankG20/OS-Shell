#include<functions.h>

void pwd(intl n,char home_dir[]){
	char cwd_name[LEN];
	getcwd(cwd_name,LEN);
	if(strstr(cwd_name,home_dir)!=NULL){
		char wrthome[LEN]="~";
		intl j=1;
		for(intl i=n;i<strlen(cwd_name);i++){
			wrthome[j++]=cwd_name[i];
		}
		printf("%s\n",wrthome);
	}
	else{
		printf("%s\n",cwd_name);
	}
}
