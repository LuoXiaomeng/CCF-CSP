#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
int win(int*panel){
	if(panel[0] != 0 && panel[0] == panel[1] && panel[0] == panel[2])return -2*panel[0]+3;
	if(panel[3] != 0 && panel[3] == panel[4] && panel[3] == panel[5])return -2*panel[3]+3;
	if(panel[6] != 0 && panel[6] == panel[7] && panel[6] == panel[8])return -2*panel[6]+3;
	if(panel[0] != 0 && panel[0] == panel[3] && panel[0] == panel[6])return -2*panel[0]+3;
	if(panel[1] != 0 && panel[1] == panel[4] && panel[1] == panel[7])return -2*panel[1]+3;
	if(panel[2] != 0 && panel[2] == panel[5] && panel[2] == panel[8])return -2*panel[2]+3;
	if(panel[0] != 0 && panel[0] == panel[4] && panel[0] == panel[8])return -2*panel[0]+3;
	if(panel[2] != 0 && panel[2] == panel[4] && panel[2] == panel[6])return -2*panel[2]+3;
	for(int i=0;i<9;i++){
		if(panel[i]==0)return 2;
	}
	return 0;
}
int alice_best(int *panel);
int bob_best(int *panel){
	int winner=0,score=0,tmp;
	if((winner = win(panel))<2){
		for(int i=0;i<9;i++){
			if(panel[i]==0)score++;
		}
		score++;
		return score*winner;
	}
	score = 11;
	for(int i=0;i<9;i++){
		if(panel[i]==0){
			panel[i]=2;
			tmp = alice_best(panel);
			if(tmp<score)score = tmp;
			panel[i]=0;
		}
	}
	return score;
}
int alice_best(int *panel){
	int winner=0,score=0,tmp;
	if((winner = win(panel))<2){
		for(int i=0;i<9;i++){
			if(panel[i]==0)score++;
		}
		score++;
		return score*winner;
	}
	score = -11;
	for(int i=0;i<9;i++){
		if(panel[i]==0){
			panel[i]=1;
			tmp = bob_best(panel);
			if(tmp>score){
				score = tmp;
			}
			panel[i]=0;
		}
	}
	return score;
}
int main(){
	int n,panel[9];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		memset((void*)panel,0,sizeof(panel));
		for(int j=0;j<9;j++){
			scanf("%d",panel+j);
		}
		printf("%d\n",alice_best(panel));
	}
	return 0;
}
