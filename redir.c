#include<functions.h>

extern char home_dir[LEN];

char pip[LEN];
char rd1[LEN];
char wr1[LEN];
void trim(char ar1[],intl x){
	intl i=0,j=0;
	while(i<strlen(ar1) && (ar1[i]==' ' || ar1[i]=='\t')) i++;
	while(i<strlen(ar1) && ar1[i]!=' ' && ar1[i]!='\t'){
		if(x==0)
			rd1[j++]=ar1[i];
		else
			wr1[j++]=ar1[i];
		i++;
	}
}

intl solve_redir(char arr[]){
	// printf("arr is %s\n",arr);
	intl n1=strlen(arr);
	intl i,j;
	// read[0]='\0';
	// write[0]='\0';
	char read[LEN];
	char write[LEN];
	intl read_fd=-1,write_fd=-1;
	for(i=n1-1;i>=0;i--){
		if(arr[i]=='<'){
			j=i+1;
			char rd[n1];
			// char rd1[n1];
			while(j<n1 && arr[j]!='>'){
				rd[j-i-1]=arr[j];
				j++;
			}
			rd[j-i-1]='\0';
			// printf("rd is %s\n",rd);
			trim(rd,0);
			// printf("rd1 is %s\n",rd1);
			intl n2=strlen(rd1);
			intl m1=0;
			for(intl k=0;k<n2;k++){
				if(rd1[k]=='~'){
					for(intl r1=0;r1<strlen(home_dir);r1++){
						read[m1++]=home_dir[r1];
					}
				}
				else{
					read[m1++]=rd1[k];
				}
			}
			read[m1]='\0';
			printf("read file is %s\n",read);
			// if(i>0 && cmd[i-1]=='>'){
				// 
			// }
			struct stat may;
			if(stat(read,&may)==-1){
				perror(read);
				return 1;
			}
			if(!S_ISREG(may.st_mode)){
				fprintf(stderr,"Error: %s is not a regular file\n",read);
				return 1;
			}
			read_fd=open(read,O_RDONLY);
			if(read_fd==-1){
				perror(read);
				return 1;
			}
			dup2(read_fd,0);
			break;
		}
	}
	for(i=n1-1;i>=0;i--){
		if(arr[i]=='>'){
			j=i+1;
			char wr[n1];
			// char wr1[n1];
			while(j<n1 && arr[j]!='<'){
				wr[j-i-1]=arr[j];
				j++;
			}
			wr[j-i-1]='\0';
			trim(wr,1);
			intl n2=strlen(wr1);
			intl m1=0;
			for(intl k=0;k<n2;k++){
				if(wr1[k]=='~'){
					for(intl r1=0;r1<strlen(home_dir);r1++){
						write[m1++]=home_dir[r1];
					}
				}
				else{
					write[m1++]=wr1[k];
				}
			}
			write[m1]='\0';
			printf("write file is %s\n",write);
			if(i>0 && arr[i-1]=='>'){
				write_fd=open(write,O_WRONLY|O_CREAT|O_APPEND,0644);
			}
			else
				write_fd=open(write,O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if(write_fd==-1){
				perror(write);
				return 1;
			}
			dup2(write_fd,1);
			break;
		}
	}
	i=0;
	while(i<n1 && arr[i]!='>' && arr[i]!='<'){
		pip[i]=arr[i];
		i++;
	}
	pip[i]='\0';
	intl ret=exec_cmd();
	dup2(stdin_fd,0);
	dup2(stdin_fd,1);
	if(read_fd!=-1)
		close(read_fd);
	if(write_fd!=-1)
		close(write_fd);
	return ret;
}