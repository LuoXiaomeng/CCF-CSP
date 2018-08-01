#include<stdio.h>
int count=0;
int score(int n){
	switch(n){
		case 0:return 0;
		case 1:{count=0;return 1;}
		case 2:return (2+2*(count++));
	}
}
int main(){
	int n=0,s=0;
	do{
		scanf("%d",&n);
		s+=score(n);
		
	}while(n!=0);
	printf("%d",s);
	return 0;
}
