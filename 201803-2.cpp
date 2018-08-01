#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<malloc.h>
struct ball{
	int pos;
	int dir;
};
int chgdir(struct ball*b){
	if(b->dir == 1)b->dir = -1;
	else b->dir = 1;
	return 0;		
}
int mov(struct ball*b,int l){
	b->pos=b->pos+b->dir;
	if((b->pos==0)||(b->pos==l)){
		chgdir(b);
	}
	return b->pos;
}
int main(){
	int n,l,t,a;
	scanf("%d %d %d",&n,&l,&t);
	struct ball **bs = (struct ball **)malloc(sizeof(struct ball*)*n);
	int *axi = (int*)malloc(sizeof(int)*(l+1));
	memset((void*)axi,0,(l+1)*sizeof(int));
	for(int i=0;i<n;i++){
		scanf("%d",&a);
		bs[i] = (struct ball*)malloc(sizeof(struct ball));
		if(a<l)bs[i]->dir=1;
		else bs[i]->dir=-1;
		bs[i]->pos=a;
		axi[a]++;
	}
	for(int i=0;i<t;i++){
		for(int j=0;j<n;j++){
			axi[bs[j]->pos]--;
			axi[mov(bs[j],l)]++;
		}
		for(int j=0;j<n;j++){
			if(axi[bs[j]->pos]>1)chgdir(bs[j]);
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",bs[i]->pos);
	}
	return 0;
}
