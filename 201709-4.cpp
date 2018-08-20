#include<stdio.h>

int n,m,cnt=0;

int arrv[1001][1001]={{0}};
int mrk_arrv[1001]={0};
int cnt_arrv[1001]={0};
char arrv_link[1001][1001]={{0}};

char to_link[1001][1001]={{0}};
//
int link[1001][1001] ={{0}};
int link_cnt[1001]={0};

void sndmsg(int from,int dst,int msg){
	if(arrv_link[dst][msg]!=0)return;
	arrv[dst][cnt_arrv[dst]]=msg;
	cnt_arrv[dst]++;
	arrv_link[dst][msg]=1;
	if(to_link[msg][dst]!=0)return;
	to_link[msg][dst]=1;
	return;
}
int main(){
	scanf("%d %d",&n,&m);
	int a,b;
	for(int i=0;i<m;i++){
		scanf("%d %d",&a,&b);
		link[a][link_cnt[a]]=b;
		link_cnt[a]++;
	}
	for(int i=1;i<n+1;i++){
		sndmsg(i,i,i);
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<n+1;j++){
			while(arrv[j][mrk_arrv[j]]!=0){
				for(int k=0;k<link_cnt[j];k++){
					sndmsg(j,link[j][k],arrv[j][mrk_arrv[j]]);
				}
				mrk_arrv[j]++; 
			} 
		}
	}
	for(int i=1;i<n+1;i++){
		for(int j=1;j<n+1;j++){
			if(!arrv_link[i][j] && to_link[i][j])cnt_arrv[i]++;
		} 
		if(cnt_arrv[i]==n){
			cnt++;
			//printf("%d\n",i);	
		}
	}
	printf("%d",cnt);
	return 0;
} 
