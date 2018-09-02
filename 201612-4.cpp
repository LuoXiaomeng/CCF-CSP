#include<stdio.h>
#include<stdlib.h>
int n;
int t[1000];
int st[1001]={0};
int rc[1000][1000] = {0};
int cut(int b,int e,int d){
	if(e-b==1)return t[b]*d;
	if(rc[b][e]!=0)return rc[b][e]+d*(st[e]-st[b]);
	int sum=2147483647,tmp;
	for(int i=b+1;i<e;i++){
		if((tmp = cut(b,i,d+1)+cut(i,e,d+1))<sum)sum = tmp;
	}
	rc[b][e] = sum-d*(st[e]-st[b]);
	return sum;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&t[i]);
		st[i+1]=st[i]+t[i];
	}
	printf("%d",cut(0,n,0));
	return 0;
} 
