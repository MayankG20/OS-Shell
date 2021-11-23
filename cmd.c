#include<functions.h>

extern char hist[20][LEN];
extern char home_dir[LEN];
extern char pip[LEN];
extern int size1;
extern char arr[LEN];
extern intl inparr;
char concatstr[LEN];
char stringforup[LEN];
extern char hisloc[LEN];
extern void signalnumber(int sig_num);
extern pid_t z;

intl strtoint(char arr[]){
	intl tot=0;
	intl n=strlen(arr);
	for(intl i=0;i<n;i++){
		intl j=arr[i]-'0';
		// printf("j is %lld\n",j);
		if(i==0){
			tot+=j;
		}
		else if(i==1){
			tot+=(j*10);
		}
	}
	return tot;
}

intl exec_cmd(){
	// pid_t shellpid=getpid();
	// printf("pip is %s\n",pip);
	// char uparr[5]="^[[A";
	char cmd[LEN][LEN];
	intl count1=1;
	intl k=0,j=0;
	intl count2=0;
	for(intl i=0;i<strlen(pip);i++){
		// printf("%c",pip[i]);
		if((pip[i]==' ' || pip[i]=='\t') && i>0 && (pip[i-1]!=' ' && pip[i-1]!='\t')){
			cmd[k][j]='\0';
			// printf("%s ",cmd[k]);
			k++;
			j=0;
		}
		else if(pip[i]!=' ' && pip[i]!='\t'){
			cmd[k][j++]=pip[i];
			count2=1;
		}
	}
		// m2++;
	// printf("k is %lld\n",k);
	cmd[k][j]='\0';
	if(j==0)
		k-=1;
	// printf("k is %lld and cmd[k] is %s\n",k,cmd[k]);
	// printf("%s\n",cmd[0]);
	if(count2==0)
		return 1;
	if(size1==20){
		for(intl i=0;i<19;i++){
			strcpy(hist[i],hist[i+1]);
		}
		size1=19;
	}
	char tempstr[LEN]="";
	strcpy(concatstr,tempstr);
	// concatstr[]="";
	for(intl i=0;i<=k;i++){
		strcat(concatstr,cmd[i]);
		if(i!=k){
			strcat(concatstr," ");
		}
	}
	intl n4=strlen(concatstr);
	concatstr[n4]='\0';
	FILE *fd;
	if(!strcmp(cmd[0],"cd")){
		// printf("Pitega tu\n");
		changedir(cmd,home_dir,k);
	}
	else if(!strcmp(cmd[0],"quit")){
		fd=fopen(hisloc,"w+");
		for(intl i=0;i<size1;i++){
			if(i!=0){
				fd=fopen(hisloc,"a+");
			}
			fputs(hist[i],fd);
			// fputs("\n",fd);
			fclose(fd);
		}
		count1=0;
	}
	else if(!strcmp(cmd[0],"pwd")){
		char cwd_name[LEN];
		getcwd(cwd_name,LEN);
		printf("%s\n",cwd_name);
	}
	else if(!strcmp(cmd[0],"echo")){
		for(intl i=1;i<=k;i++)
			printf("%s ",cmd[i]);
		printf("\n");
	}
	else if(!strcmp(cmd[0],"ls")){
		lskrle(cmd,k,home_dir);
	}
	else if(!strcmp(cmd[0],"pinfo")){
		// printf("aa bhi ja\n");
		pinfo(cmd,k,home_dir);
	}
	else if(!strcmp(cmd[0],"history")){
		if(k==0){
			if(size1>10){
				intl j3=0;
				while(j3++<10){
					printf("%s",hist[size1-j3]);
				}
			}
			else{
				intl j3=0;
				while(j3++<size1){
					printf("%s",hist[size1-j3]);
				}
			}
		}
		else{
			intl j4=strtoint(cmd[1]);
			// printf("%lld\n",j4);
			intl j3=0;
			while(j3++<j4){
				printf("%s",hist[size1-j3]);
			}
		}
	}
	else if(!strcmp(cmd[0],"setenv")){
		if(k==0 || k>2){
			printf("Error:Check number of arguments\n");
		}
		else{
			if(k==1){
				if(setenv(cmd[1],"",1)==-1)
					perror("setenv is not executed\n");
			}
			else
				if(setenv(cmd[1],cmd[2],1)==-1)
					perror("setenv is not executed");
		}
	}
	else if(!strcmp(cmd[0],"unsetenv")){
		if(k==0){
			printf("Error:Check No. of arguments\n");
		}
		else{
			if(unsetenv(cmd[1])==-1)
				perror("unsetenv is not executed\n");
		}
	}
	else if(!strcmp(cmd[0],"jobs")){
		jobsinf();
	}
	else if(!strcmp(cmd[0],"kjob")){
		if(k>2 || k<1){
			printf("Check number of arguments\n");
		}
		else{
			intl a1=atoi(cmd[1]);
			intl a2=atoi(cmd[2]);
			killjob(a1,a2);
		}
	}
	else if(!strcmp(cmd[0],"bg")){
		if(k!=1){
			printf("Check number of arguments\n");
		}
		else{
			intl jn=atoi(cmd[1]);
			int er=findpid(jn);
			if(er==-1){
				printf("Job number is not valid\n");
			}
			else{
				kill(er,SIGCONT);
			}
		}
	}
	else if(!strcmp(cmd[0],"fg")){
		if(k!=1){
			printf("Check number of arguments\n");
		}
		else{
			int spid=getpid();
			intl jn=atoi(cmd[1]);
			// printf("jn is %lld\n",jn);
			int er=findpid(jn);
			// printf("er is %lld\n",er);
			if(er==-1){
				printf("Job number is not valid\n");
			}
			else{
				int sta;
				signal(SIGTTOU, SIG_IGN);
				signal(SIGTTIN, SIG_IGN);
			    tcsetpgrp(0,getpgid(er));
			    kill(er,SIGCONT);
			    waitpid(er,&sta,WUNTRACED);
			    tcsetpgrp(0,spid);
			    signal(SIGTTOU,SIG_DFL);
			    signal(SIGTTOU,SIG_DFL);
			    remfromlist(er);
			}
		}
	}
	else if(!strcmp(cmd[0],"overkill")){
		overkill();
	}
	else{
		// printf("executing command\n");
		count1=execcmd(cmd,k);	
	}
	return count1;
	// printf("i1 and size1 are %lld %lld\n",i1,size1);
	// pip=strtok(NULL,";");
}