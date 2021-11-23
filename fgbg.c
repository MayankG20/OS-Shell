#include<functions.h>

extern char procinf[LEN][LEN];
extern char procinf1[LEN][LEN];

extern intl index1[LEN];
extern intl index2[LEN];

extern intl sizeofstructarr;
extern intl sizeofvirtualarr;

extern char concatstr[LEN];

pid_t z=0;

void signalnumber(int sig_num){

	if(z>0){
		kill(z,sig_num);
	}
	z=0;
	
}

intl execcmd(char cmd[][LEN],intl k){
	pid_t pid;
	if((pid=fork())<0){
		printf("Error:Not able to fork the process\n");
		return 0;
	}
	else if(pid==0){
		// printf("cmd[k] is %s",cmd[k-1]);
		char *maya[k+2];
		for(intl a=0;a<=k;a++){
			maya[a]=cmd[a];
		}
			maya[k+1]= NULL;
		// printf("")
		if(cmd[k][0]=='&'){
			setpgid(0,0);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);	
		}
		intl x1=execvp(cmd[0],maya);
		if(x1==-1)
				printf("Not a valid command\n");
		return 0;
		// exit(0);
	}
	else{
		signal(SIGINT,signalnumber);
		signal(SIGTSTP,signalnumber);
		if(cmd[k][0]!='&'){
			// printf("anfn\n");
			z=pid;
			int sta1;
			waitpid(pid,&sta1,WUNTRACED);
			if(WIFEXITED(sta1)!=1){
				intl n4=strlen(concatstr);
			
				concatstr[n4]='\0';
				intl count1=0;

				for(intl i=0;i<sizeofstructarr;i++){
					if(index1[i]==-1){
						procinf[i][0]='\0';
						strcpy(procinf[i],concatstr);
						// printf("%s\n",procinf[i]);
						index1[i]=pid;
						// printf("i is %lld\n",i);
						printf("%s with pid %lld gets open in the background\n",procinf[i],index1[i]);
						count1=1;
						break;
					}
				}
				if(count1==0){
					intl i4=sizeofstructarr;
					procinf[i4][0]='\0';
					strcpy(procinf[i4],concatstr);
					// printf("%s\n",procinf[i]);
					index1[i4]=pid;
					// printf("i is %lld\n",i);
					printf("%s with pid %lld gets open in the background\n",procinf[i4],index1[i4]);
					// count1=1;
					sizeofstructarr++;
				}
				procinf1[sizeofvirtualarr][0]='\0';
				strcpy(procinf1[sizeofvirtualarr],concatstr);
				index2[sizeofvirtualarr]=pid;
				sizeofvirtualarr++;
			}
		}
		else{
			intl n4=strlen(concatstr);
			
			concatstr[n4-2]='\0';
			intl count1=0;

			for(intl i=0;i<sizeofstructarr;i++){
				if(index1[i]==-1){
					procinf[i][0]='\0';
					strcpy(procinf[i],concatstr);
					// printf("%s\n",procinf[i]);
					index1[i]=pid;
					// printf("i is %lld\n",i);
					printf("%s with pid %lld gets open in the background\n",procinf[i],index1[i]);
					count1=1;
					break;
				}
			}
			if(count1==0){
				intl i4=sizeofstructarr;
				procinf[i4][0]='\0';
				strcpy(procinf[i4],concatstr);
				// printf("%s\n",procinf[i]);
				index1[i4]=pid;
				// printf("i is %lld\n",i);
				printf("%s with pid %lld gets open in the background\n",procinf[i4],index1[i4]);
				// count1=1;
				sizeofstructarr++;
			}
			procinf1[sizeofvirtualarr][0]='\0';
			strcpy(procinf1[sizeofvirtualarr],concatstr);
			index2[sizeofvirtualarr]=pid;
			sizeofvirtualarr++;
		}
		return 1;
	}
}

