#include<functions.h>

extern char home_dir[LEN];

intl solve_piping(char eachcmd[]){
	// printf("%s is\n",eachcmd);
	char pipe1[LEN][LEN];
	char *pp=strtok(eachcmd,"|");
	intl r2=0;
	while(pp!=NULL){
		strcpy(pipe1[r2++],pp);
		pp=strtok(NULL,"|");
	}

	int pipe_fd[2];
	stdin_fd=dup(0);
	stdout_fd=dup(1);

	if(r2==1){
		return solve_redir(pipe1[r2-1]);
	}
	intl m2=0;
	while(m2<r2){
		// printf("m2 and r2 are %lld %lld\n",m2,r2);
		if(m2!=0){
			close(pipe_fd[1]);//closing write file descriptor
			// stdin_fd=dup(0);
			if(dup2(pipe_fd[0],0) ==-1){
				perror("Error1");
			}
			close(pipe_fd[0]);
		}
		if(m2!=r2-1){
			if(pipe(pipe_fd) == -1){
				perror("Error2");
			}
			// stdout_fd=dup(1);
			if(dup2(pipe_fd[1],1)==-1)
				perror("Error3");
			// printf("fs;alf\n");
		}
		intl pid=fork();
		int st;
		if(pid == -1){
			dup2(stdin_fd,0);
			dup2(stdout_fd,1);
			perror("Error4");
			return 1;
		}
		else if(pid==0){
			solve_redir(pipe1[m2]);
			exit(0);
		}
		else{
			waitpid(pid,&st,WUNTRACED);
			dup2(stdin_fd,0);
			dup2(stdout_fd,1);
		}
		m2++;
	}
	return 1;
}
