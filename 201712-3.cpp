#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define JAN "JAN"//0b000000000001
#define FEB "FEB"//0b000000000010
#define MAR "MAR"//0b000000000100
#define APR "APR"//0b000000001000
#define MAY "MAY"//0b000000010000
#define JUN "JUN"//0b000000100000
#define JUL "JUL"//0b000001000000
#define AUG "AUG"//0b000010000000
#define SEP "SEP"//0b000100000000
#define OCT "OCT"//0b001000000000
#define NOV "NOV"//0b010000000000
#define DEC "DEC"//0b100000000000

#define MON "MON"//0b0000001
#define TUE "TUE"//0b0000010
#define WED "WED"//0b0000100
#define THU "THU"//0b0001000
#define FRI "FRI"//0b0010000
#define SAT "SAT"//0b0100000
#define SUN "SUN"//0b1000000

int mon_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};

struct task{
	char cmd[100];
	short int month;
	int date;
	char weekday;
	int hour;
	long long int minute;	
};
struct time{
	int year;
	int month;
	int date;
	int hour;
	int minute;
};

struct time* int2time(long long int t){
	struct time* time = (struct time*)malloc(sizeof(struct time));
	time->year = t/100000000;
	time->month = t%100000000/1000000;
	time->date = t%1000000/10000;
	time->hour = t%10000/100;
	time->minute = t%100;
	return time;
}

long long int time2int(struct time* time){
	long long int t = 0;
	if(time == NULL)return 0;
	t = (long long int)time->year*100000000+(long long int)time->month*1000000+time->date*10000+time->hour*100+time->minute;
	return t;
}

int str2num(char**pb){
	char *p = *pb;
	int n=0;
	if(*p > '9'){
		for(int i=0;i<3;i++)*(p+i) = toupper(*(p+i));
		char tmp = *(p+3);
		*(p+3) = 0;
		if(!strcmp(p,JAN))n = 1;
		else if(!strcmp(p,FEB))n = 2;
		else if(!strcmp(p,MAR))n = 3;
		else if(!strcmp(p,APR))n = 4;
		else if(!strcmp(p,MAY))n = 5;
		else if(!strcmp(p,JUN))n = 6;
		else if(!strcmp(p,JUL))n = 7;
		else if(!strcmp(p,AUG))n = 8;
		else if(!strcmp(p,SEP))n = 9;
		else if(!strcmp(p,OCT))n = 10;
		else if(!strcmp(p,NOV))n = 11;
		else if(!strcmp(p,DEC))n = 12;
		else if(!strcmp(p,MON))n = 1;
		else if(!strcmp(p,TUE))n = 2;
		else if(!strcmp(p,WED))n = 3;
		else if(!strcmp(p,THU))n = 4;
		else if(!strcmp(p,FRI))n = 5;
		else if(!strcmp(p,SAT))n = 6;
		else if(!strcmp(p,SUN))n = 0;
		*(p+3) = tmp;
		*pb = p+3;
	}
	else{
		while(*p>='0'&&*p<='9'){
			n = n*10+(*p)-'0';
			p++;
		}
		*pb = p;	
	}
	return n;
}

long long int str2scale(char*pb){
	long long int m = 0;
	int s = 0,e=0;
	if(*pb == '*'){
		memset((void*)&m,0xff,sizeof(m));
	}else{
		while(*pb!=0){
			s = str2num(&pb);
			e=s;
			if(*pb == '-'){
				pb++;
				e = str2num(&pb);	
			}
			for(int i=s;i<=e;i++){
				m|=(long long int)1<<i;
			}
			if(*pb == ',')pb++;
		}
	}
	return m;
}

struct task* str2task(char*buff){
	struct task* task = (struct task*)malloc(sizeof(struct task));
	char *pb;
	pb = strtok(buff," ");
	task->minute = str2scale(pb);
	pb = strtok(NULL," ");
	task->hour = (int)str2scale(pb);
	pb = strtok(NULL," ");
	task->date = (int)str2scale(pb);
	pb = strtok(NULL," ");
	task->month = (short int)str2scale(pb);
	pb = strtok(NULL," ");
	task->weekday = (char)str2scale(pb);
	pb = strtok(NULL," ");
	strcpy(task->cmd,pb);
	return task;
}

void todo(struct time*t,int wd,struct task*task){
	if((task->month&((short int)1<<t->month))
	&&(task->date&(1<<t->date))
	&&(task->hour&(1<<t->hour))
	&&(task->minute&((long long int)1<<t->minute))
	&&(task->weekday&((char)1<<wd)))printf("%lld %s\n",time2int(t),task->cmd);
}

int execute(int ym,struct task**tasks,int n,int wd,struct time* s,struct time* e){
	int year = ym/12,month = ym%12;
	if(month == 0){
		year--;
		month = 12;
	}
	
	struct time *t = (struct time*)malloc(sizeof(struct time));
	t->year = year;
	t->month = month;
	t->date = 1;
	t->hour = 0;
	t->minute = 0;
	 
	int days = mon_day[month-1];	
	if(month == 2 && year%4 == 0)days++;
	
	int time = days*24*60;
	if(e!=NULL){
		if(e->year == year && e->month == month){
			time = ((e->date-1)*24*60+e->hour*60+e->minute);
		}		
		if(s->year == year && s->month == month){
			t = s;
			time -= ((s->date-1)*24*60+s->hour*60+s->minute); 
		}		
	}
	for(int i=0;i<time;i++){
		for(int j=0;j<n;j++){
			todo(t,wd,tasks[j]);	
		}
		t->minute++;
		if(t->minute == 60){
			t->minute = 0;
			t->hour++;
			if(t->hour == 24){
				t->hour = 0;
				t->date++;
				wd++;
				if(wd == 7)wd=0;
			}
		}
	}
	return wd;
}
int time2weekday(struct time*time){
	int k = time->year - 1970; 
	int wd = k*365+k/4+(k%4==3);
	for(int i=1;i<time->month;i++){
		wd+=mon_day[i-1];
		if(i==2 && (time->year%4 == 0))wd++;
	}
	wd += time->date;
	wd = (wd%7+3)%7;
	return wd;
}
int main(){
	char buff[101];
	int n;
	long long int s,e;
	scanf("%d %lld %lld",&n,&s,&e);
	gets(buff);
	
	struct time* start = int2time(s);
	struct time* end = int2time(e);
	
	struct task** tasks = (struct task**)malloc(sizeof(struct task*)*n);
	
	for(int i=0;i<n;i++){
		gets(buff);
		tasks[i] = str2task(buff);
	}
	
	int wd = time2weekday(start); 
	
	for(int i = start->year*12+start->month;i<=end->year*12+end->month;i++){
		if((i == start->year*12+start->month)||(i == end->year*12+end->month))wd = execute(i,tasks,n,wd,start,end);
		else wd = execute(i,tasks,n,wd,NULL,NULL);
	}

	return 0;
} 
