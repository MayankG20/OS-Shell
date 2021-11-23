#include<functions.h>

void pinfo(char arr[][LEN],intl k,char home_dir[]){
	char pathneeded[LEN];
	pid_t pd=getpid();
	// printf("aaya to shi %d\n",pd);
	if(k==0){
		sprintf(pathneeded,"/proc/%d/stat",pd);
	}
	else{
		strcpy(pathneeded,"/proc/");
		strcat(pathneeded,arr[1]);
		strcat(pathneeded,"/stat");
	}
	FILE *f1=fopen(pathneeded,"r");
	if(f1==NULL){
		perror("Error:");
		return;
	}
	else{
		if(k==0){
			printf("pid -- %d\n",pd);
		}
		else
			printf("pid -- %s\n",arr[1]);
		size_t sz=0;
		char data[256][64];
		intl i1=0;
		char *may=(char *)malloc(sizeof(char)*LEN);
		while(getline(&may,&sz,f1)!=-1){
			char *token=strtok(may," ");
			while(token!=NULL){
				strcpy(data[i1++],token);
				token=strtok(NULL," ");
			}
		}
		printf("Process status -- %s\n",data[2]);
		printf("Memory -- %s {Virtual Memory}\n",data[22]);
		pathneeded[strlen(pathneeded)-4]='\0';
		strcat(pathneeded,"exe");
		pathneeded[strlen(pathneeded)]='\0';
		// printf("%s\n",pathneeded);
		char data1[LEN];
		size_t len1;
		len1=readlink(pathneeded,data1,LEN-1);
		if(len1==-1){
			printf("Error:Not able to find executable for this process\n");
			return ;
		}
		char wrthome[LEN]="~";
		data1[len1]='\0';
		intl count1=0;
		// printf("data1 %s\n",data1);
		if(strstr(data1,home_dir)!=NULL){
			// char wrthome[LEN]="~";
			intl j=1;
			intl n=strlen(home_dir);
			// intl count1=0;
			for(intl i=n;i<strlen(data1);i++){
				if(data1[i]=='/'){
					count1=1;
				}
				wrthome[j++]=data1[i];
			}
			if(strcmp(data1,home_dir)==0){
				count1=1;
			}
		}
		if(count1==0)
			printf("Executable path -- %s\n",data1);
		else
			printf("Executable path -- %s\n",wrthome);
		free(may);
	}
}