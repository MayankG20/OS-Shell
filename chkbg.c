#include<functions.h>

// char procinf[LEN][LEN];
// intl index1[LEN];
// intl sizeofstructarr;

extern char procinf[LEN][LEN];

extern intl index1[LEN];
extern intl index2[LEN];

extern intl sizeofstructarr;
extern intl sizeofvirtualarr;

void chkbg(){
	int pd,status;
	while((pd = waitpid(-1,&status, WNOHANG))>0){
		if(WIFEXITED(status)){
			// printf("123\n");
			// printf("size is %lld\n",sizeofstructarr);
			for(intl i=0;i<sizeofstructarr; i++){
				// printf("%lld %lld\n",procinform[i].pid,pd);
				if(index1[i]==pd){
					// free(procinform[i].itsname);
					// sizeofstructarr-=1;
					fprintf(stderr, "%s with pid %lld exited normally\n",procinf[i],index1[i]);
					index1[i]=-1;
					// index2[i]=-1;
					break;
				}
			}
			for(intl i=0;i<sizeofvirtualarr;i++){
				if(index2[i]==pd){
					index2[i]=-1;
					break;
				}
			}
		}
		else if(WIFSIGNALED(status)){	
			// printf("123\n");
			// printf("size is %lld\n",sizeofstructarr);
			for(intl i=0;i<sizeofstructarr; i++){
				// printf("i and pd and index1[i] are %lld %d %lld\n",i,pd,index1[i]);
				if(index1[i]==pd){
					// printf("pd and i are %d %lld\n",pd,i);
					// free(procinform[i].itsname);
					// sizeofstructarr-=1;
					fprintf(stderr, "%s with pid %lld terminated by a signal\n",procinf[i],index1[i]);
					index1[i]=-1;
					// index2[i]=-1;
					break;
				}
			}
			for(intl i=0;i<sizeofvirtualarr;i++){
				if(index2[i]==pd){
					index2[i]=-1;
					break;
				}
			}
		}
	}
}
void remfromlist(intl pd1){
	for(intl i=0;i<sizeofstructarr; i++){
		// printf("i and pd and index1[i] are %lld %d %lld\n",i,pd,index1[i]);
		if(index1[i]==pd1){
			// printf("pd and i are %d %lld\n",pd,i);
			// free(procinform[i].itsname);
			// sizeofstructarr-=1;
			// fprintf(stderr, "%s with pid %lld terminated by a signal\n",procinf[i],index1[i]);
			index1[i]=-1;
			// index2[i]=-1;
			break;
		}
	}
	for(intl i=0;i<sizeofvirtualarr;i++){
		if(index2[i]==pd1){
			index2[i]=-1;
			break;
		}
	}
}