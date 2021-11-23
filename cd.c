#include<functions.h>

void changedir(char arr[][LEN],char home_dir[],intl k){
	// printf("%s\n",arr[1]);
	if(arr[1][0]=='~' || k==0){
		intl x=chdir(home_dir);
		if(x!=0){
			perror("Error");
		}
		intl m=strlen(arr[1]);
		if(m>1){
			// printf("ajfd\n");
			intl i;
			for(intl i=0;i<m-2;i++){
				arr[1][i]=arr[1][i+2];
			}
			arr[1][i]='\0';
			changedir(arr,home_dir,k);
		}
	}
	else if(k==1 && !strlen(arr[1])){
		intl x=chdir(home_dir);
		if(x!=0){
			perror("Error");
		}
	}
	else if(k==1 && arr[1][0]=='/'){
		intl x=chdir(arr[1]);
		if(x!=0)
			perror("Error:");
	}
	else{
		char cwd_name[LEN];
		getcwd(cwd_name,LEN);
		strcat(cwd_name,"/");
		strcat(cwd_name,arr[1]);
		intl x=chdir(cwd_name);
		if(x!=0){
			perror("Error");
		}
	}
}
