#include<functions.h>

char cwd1_name[LEN];
char home_dir[LEN];

char procinf[LEN][LEN];
char procinf1[LEN][LEN];

intl index1[LEN];
intl index2[LEN];

char hist[20][LEN];
char arr[LEN];

intl sizeofstructarr;
intl sizeofvirtualarr;

int size1;
intl inparr;

char hisloc[LEN];

extern char stringforup[LEN];
extern void signalnumber(int sig_num);
extern pid_t z;

void maketilda(char arr[],intl x){
	intl n=strlen(arr);
	char *temp;
	temp=strrchr(arr,'/');
	n-=strlen(temp);
	arr[n]='\0';
	strcat(cwd1_name,"/");
	strcat(cwd1_name,arr);
	chdir(cwd1_name);
	getcwd(home_dir,LEN);
}

int main(int argc,char** argv){
	intl count1=1;
	char cwd_name[LEN];
	getcwd(cwd1_name,LEN);
	strcpy(cwd_name,cwd1_name);
	intl x=strlen(cwd_name);
	maketilda(argv[0],x);
	// printf("%s\n",home_dir);
	chdir(cwd_name);
	intl n=strlen(home_dir);
	
	for(intl i=0;i<LEN;i++){
		index1[i]=-1;
		index2[i]=-1;
	}
	sizeofstructarr=0;
	sizeofvirtualarr=0;

	strcpy(hisloc,home_dir);
	strcat(hisloc,"/History.txt");

	FILE* fd;
	fd=fopen(hisloc,"a+");
	ssize_t read=0;
	size_t len=0;
	char * line=NULL;
	size1=0;
	while((read=getline(&line,&len,fd))!=-1){
		if(strcmp(line,"\n")){
			char *token1=strtok(line,"\t\n ");
			strcpy(hist[size1],token1);
			strcat(hist[size1++],"\n");
		}
	}
	fclose(fd);

	while(count1){
		chkbg();
		z=0;
		signal(SIGINT,signalnumber);
		signal(SIGTSTP,signalnumber);
		printprompt(n,home_dir);
		
		// count1=0;
		if(inparr==0)
			fgets(arr,LEN,stdin);
		if(inparr==1){
			printf("%s",arr);
			inparr=0;
		}
		
		// printf("%s",arr);
		// char *tokena=strtok(arr,"\n");
		intl n7=strlen(arr);
		intl countofup=0;
		if(n7>2 && arr[0]==27 && arr[1]==91 && arr[2]==65){
			for(intl i=0;i<n7-2;i++){
				if(arr[i]==27 && arr[i+1]==91 && arr[i+2]==65){
					countofup++;
				}
			}
			strcpy(arr,hist[size1-countofup]);
			inparr=1;
			continue;
		}
		if(strcmp(arr,hist[size1-1]))
			strcpy(hist[size1++],arr);	

		char eachcmd[LEN][LEN];
		intl leng=strlen(arr);
		arr[leng-1]='\0';
		intl r1=0;
		char *ecmd=strtok(arr,";");
		while(ecmd!=NULL){
			strcpy(eachcmd[r1++],ecmd);
			ecmd=strtok(NULL,";");
		}
		intl m1=0;
		while(m1<r1){
			chkbg();
			// printf("eachcmd is %s\n",eachcmd[m1]);
			count1=solve_piping(eachcmd[m1]);
			m1++;
		}
	}
}
