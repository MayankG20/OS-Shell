#include<functions.h>

extern char procinf1[LEN][LEN];
extern intl index2[LEN];
extern intl sizeofvirtualarr;

void jobsinf(){
	intl i,j;
	j=0;
	for(i=0;i<sizeofvirtualarr;i++){
		if(index2[i]!=-1){
			char pathreq[LEN];
			// printf("pid is %lld\n",index2[i]);
			sprintf(pathreq,"/proc/%lld/status",index2[i]);
			FILE *fd1=fopen(pathreq,"r");
			if(fd1==NULL){
				// printf("Right Now there are no jobs to show\n");
				continue;
			}
			j++;
			size_t sz=0;
			char status[LEN];
			intl i1=0;
			char *may=(char *)malloc(sizeof(char)*LEN);
			while(getline(&may,&sz,fd1)!=-1){
				i1++;
				if(i1==3){
					intl j1=0;
					char *token=strtok(may," ");
					while(token!=NULL && j1<3){
						strcpy(status,token);
						token=strtok(NULL," ");
						i1++;
					}
				}
			}
			intl n4=strlen(status);
			intl j2=0;
			char sta[LEN];
			for(intl i2=1;i2<n4;i2++){
				if(status[i2]==')')
					break;
				else
					sta[j2++]=status[i2];
			}
			// status[n4]='\0';
			printf("[%lld] %s [%lld] %s",j,procinf1[i],index2[i],status);
		}
	}
}