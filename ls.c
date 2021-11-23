#include<functions.h>

void lskrle(char arr[][LEN],intl k,char home_dir[]){
	intl flag_a=0,flag_l=0;
	char pathgiven[LEN];
	getcwd(pathgiven,LEN);
	strcat(pathgiven,"/");
	char pathtemp[LEN];
	strcpy(pathtemp,pathgiven);
	for(intl i=0;i<=k;i++){
		if(!strcmp(arr[i],"-l")){
			flag_l=1;
		}
		else if(!strcmp(arr[i],"-a")){
			flag_a=1;
		}
		else if(!strcmp(arr[i],"-la") || !strcmp(arr[i],"-al")){
			flag_a=1;
			flag_l=1;
		}
		else if(strcmp(arr[i],"ls")){
			// printf("Yha kaise bhai\n");
			if(arr[i][0]=='~' || (arr[i][0]=='.' && arr[i][1]=='/')){
				// strcat(pathgiven,home_dir);
				intl x1=strlen(arr[i]);
				for(intl j=0;j<x1-2;j++){
					arr[i][j]=arr[i][j+2];
				}
				arr[i][x1-2]='\0';
				if(x1>1)
					strcat(pathgiven,arr[i]);
			}
			else if(arr[i][0]!='/'){
				// strcat(pathgiven,home_dir);
				strcat(pathgiven,arr[i]);
			}
			else{
				pathgiven[0]='\0';
				strcat(pathgiven,arr[i]);
			}
		}
	}
	DIR *may;
	
	intl x2=strlen(pathgiven);
	// printf("%s\n",pathgiven);
	chdir(pathgiven);
	getcwd(pathgiven,LEN);
	
	// if(x2==0)
	// 	strcpy(pathgiven,"./");
	// printf("%s\n",pathgiven);
	may=opendir(pathgiven);
	if(may==NULL){
		printf("Error:No such Directory exists\n");
	}
	else{
		struct dirent *insidedir;
		insidedir = readdir(may);
		while(insidedir !=NULL){
			struct stat st;
			if(stat(insidedir->d_name,&st) == 0){
				intl x1=0;
				if(st.st_mode & S_IFDIR ){
					x1=1;
				}
				else if(st.st_mode & S_IFREG){
					x1=0;
				}
				else
					x1=-1;
				if(flag_l==1){
					char dir_path[LEN];
					strcpy(dir_path,pathgiven);
					
					if(pathgiven[x2-1]!='/')
						strcat(dir_path,"/");
					strcat(dir_path,insidedir->d_name);
					char *permisn=(char *)malloc(11*sizeof(char));
					if(x1==0){
						permisn[0]='-';
					}
					else if(x1==1){
						permisn[0]='d';
					}
					else if(S_ISLNK(st.st_mode))
						permisn[0]='l';
					else
						permisn[0]='s';
					permisn[1]= (st.st_mode & S_IRUSR) ? 'r' : '-';
					permisn[2]= (st.st_mode & S_IWUSR) ? 'w' : '-';
					permisn[3]= (st.st_mode & S_IXUSR) ? 'x' : '-';

					permisn[4]= (st.st_mode & S_IRGRP) ? 'r' : '-';
					permisn[5]= (st.st_mode & S_IWGRP) ? 'w' : '-';
					permisn[6]= (st.st_mode & S_IXGRP) ? 'x' : '-';

					permisn[7]= (st.st_mode & S_IROTH) ? 'r' : '-';
					permisn[8]= (st.st_mode & S_IWOTH) ? 'w' : '-';
					permisn[9]= (st.st_mode & S_IXOTH) ? 'x' : '-';

					permisn[10]='\0';

					char *tym=(char *)malloc(sizeof(char)*50);
					strftime(tym,50,"%b %d %H:%M",localtime(&st.st_mtime));
					// printf("%d %d\n",flag_a,flag_l);
					if(flag_a || (!flag_a && insidedir->d_name[0]!='.'))
						printf("\033[22;36m%s\t%d\t%s\t%s\t%d\t%s\t",permisn,(int)st.st_nlink,getpwuid(st.st_uid)->pw_name, getgrgid(st.st_gid)->gr_name, (int)st.st_size, tym);

					free(permisn);
					free(tym);
				}
				if(x1==0){
					if(flag_a)
						printf("\033[22;37m%s\n",insidedir->d_name);
					else{
						if(insidedir->d_name[0]!='.')
							printf("\033[22;37m%s\n",insidedir->d_name);
					}
				}
				else if(x1==1){
					if(flag_a)
						printf("\033[01;32m%s\n",insidedir->d_name);
					else{
						if(insidedir->d_name[0]!='.')
							printf("\033[01;32m%s\n",insidedir->d_name);
					}
				}
				else{
					if(flag_a)
						printf("\033[01;37m%s\n",insidedir->d_name);
					else{
						if(insidedir->d_name[0]!='.')
							printf("\033[01;37m%s\n",insidedir->d_name);
					}
				}
				// printf("%lld \n",x1);
				insidedir = readdir(may);
			}
			else{
				// insidedir =readdir(may);
				// continue;
				// perror("Error:");
				insidedir = readdir(may);
				// exit(EXIT_FAILURE);
			}
		}
		// printf("\n");
		closedir(may);
	}
	chdir(pathtemp);
}

