#include<functions.h>

extern char procinf1[LEN][LEN];
extern intl index2[LEN];
extern intl sizeofvirtualarr;

intl findpid(intl k){
	intl i,j=0;
	intl count1=-1;
	for(i=0;i<sizeofvirtualarr;i++){
		if(index2[i]!=-1){
			j++;
			if(j==k){
				count1=index2[i];
				break;
			}
		}
	}
	return count1;
}