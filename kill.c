#include<functions.h>

extern char procinf1[LEN][LEN];
extern intl index2[LEN];
extern intl sizeofvirtualarr;

void killjob(intl jn,intl sn){
	intl jn1=findpid(jn);
	if(jn1==-1){
		printf("Enter the valid job number\n");
	}
	else{
		// printf("jn1 is %lld\n",jn1);
		intl err=kill(jn1,sn);
		if(err==-1){
			perror("Error");
		}
		else{
			printf("Signal %lld is sent to process with job number %lld(pid %lld)\n",sn,jn,jn1);
		}
	}
}

void overkill(){
	intl i,j;
	j=sizeofvirtualarr+1;
	for(i=0;i<=j;i++){
		if(index2[i]!=-1){
			kill(index2[i],9);
		}
	}
}