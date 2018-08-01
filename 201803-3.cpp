#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TYPE_C 0
#define TYPE_S 1
#define TYPE_I 2
#define TYPE_P 3
#define STR_S "<str>"
#define STR_I "<int>"
#define STR_P "<path>"
 
struct comp{
	int type;
	char *str;
	struct comp* next;
};
struct rule{
	char *name;
	char final;
	struct comp* comp;
	struct rule* next;
};
struct rule* init_rule(){
	struct rule* tmp = (struct rule*)malloc(sizeof(struct rule));
	tmp->next = NULL;
	tmp->comp = NULL;
	tmp->name = NULL;
	tmp->final = 0;
	return tmp;
}
struct comp* init_comp(){
	struct 	comp* tmpc = (struct comp*)malloc(sizeof(struct comp));
	tmpc->next = NULL;
	tmpc->str = NULL;
	tmpc->type = 0;
	return tmpc;
}


int str2typ(struct comp*cmp){
	if(cmp == NULL)return 0;
	if(cmp->str == NULL)return 0;
	if(!strcmp(STR_S,cmp->str))cmp->type = TYPE_S;
	else if(!strcmp(STR_I,cmp->str))cmp->type = TYPE_I;
	else if(!strcmp(STR_P,cmp->str))cmp->type = TYPE_P;
	else cmp->type = TYPE_C;
	//printf("type:%d\n",cmp->type);
}
int match(struct rule*tmp,struct rule*rule){
	if(tmp == NULL || rule == NULL)return 0;
	struct comp	**cp_t = &(tmp->comp),**cp_r = &(rule->comp);
	char *pc ;
	while(*cp_t!=NULL && *cp_r!=NULL){
		if((*cp_r)->type==TYPE_C){
			if(strcmp((*cp_r)->str,(*cp_t)->str))return 0;
			(*cp_t)->type=TYPE_C;
		}else if((*cp_r)->type==TYPE_S){
			pc = (*cp_t)->str;
			while((*pc)!=0){
				if(((*pc)>'9'||(*pc)<'0')&&((*pc)>'z'||(*pc)<'a')&&((*pc)>'A'||(*pc)<'Z')&&((*pc)!='-')&&((*pc)!='.')&&((*pc)!='_'))return 0;
				pc++;
			}
			(*cp_t)->type=TYPE_S;
		}else if((*cp_r)->type==TYPE_I){
			pc = (*cp_t)->str;
			while((*pc)!=0){
				if((*pc)>'9'||(*pc)<'0')return 0;
				pc++;
			}
			(*cp_t)->type=TYPE_I;
		}else{
			cp_r = &((*cp_r)->next);
			while(*cp_t!=NULL){
				pc = (*cp_t)->str;
				while((*pc)!=0){
					if(((*pc)>'9'||(*pc)<'0')&&((*pc)>'z'||(*pc)<'a')&&((*pc)>'A'||(*pc)<'Z')&&((*pc)!='-')&&((*pc)!='.')&&((*pc)!='_'))return 0;
					pc++;
				}
				(*cp_t)->type = TYPE_P;
				cp_t = &((*cp_t)->next);
			}
			break;
		}
		cp_t = &((*cp_t)->next);
		cp_r = &((*cp_r)->next);
	}
	if(*cp_t!=NULL || *cp_r!=NULL)return 0;
	if(tmp->final!=rule->final)return 0;
	tmp->name = rule->name;
	return 1;
}
int printurl(struct rule*tmp){
	if(tmp ==NULL)return 0;
	struct comp**pcp=&(tmp->comp);
	printf("%s ",tmp->name);
	while(*pcp!=NULL){
		switch((*pcp)->type){
			case TYPE_C:break;
			case TYPE_S:{
				printf("%s ",(*pcp)->str);
				break;
			}
			case TYPE_I:{
				printf("%d ",atoi((*pcp)->str));
				//printf("%s ",(*pcp)->str);
				break;
			}
			case TYPE_P:{
				printf("%s",(*pcp)->str);
				pcp = &((*pcp)->next);
				while(*pcp!=NULL){
					printf("/%s",(*pcp)->str);
					pcp = &((*pcp)->next);
				}
				printf("%c",tmp->final); 
				break;
			}
		}
		if(*pcp!=NULL)pcp = &((*pcp)->next);
	}
	printf("\n");
	return 0;
}

int main(){
	int m,n;
	char buff[101];
	scanf("%d %d",&n,&m);getchar();
	struct rule *rules=NULL;

	struct rule **pr = &rules,*tmp=NULL;
	struct comp **pcp,*tmpc;
	char *r_str=NULL,*r_name=NULL,*pcmp=NULL;
	for(int i=0;i<n;i++){
		
		gets(buff);
		
		tmp = init_rule();
				
		r_str = strtok(buff, " ");
	    r_name = strtok(NULL, " ");
	    
	    tmp->name = (char*)malloc(strlen(r_name));
	    strcpy(tmp->name,r_name);
	    
		if(buff[strlen(r_str)-1]=='/')tmp->final = '/';
	    
		pcp = &(tmp->comp);
	    pcmp = strtok(r_str, "/");
	    while (pcmp != NULL)
	    {
	    	
	    	tmpc = init_comp();
			
			tmpc->str = (char*)malloc(strlen(pcmp));
			strcpy(tmpc->str,pcmp);
			str2typ(tmpc);
			
			*pcp  = tmpc;
			pcp = &(tmpc->next);   
	        
			pcmp = strtok(NULL, "/");
	    }
	    
	    *pr = tmp;
	    pr = &(tmp->next);
	}

	for(int i=0;i<m;i++){
		gets(buff);
		if(strstr(buff,"//")!=NULL){
			printf("404\n");
			continue;
		}
		tmp = init_rule();
	    
	    if(buff[strlen(buff)-1]=='/')tmp->final = '/';

		pcp = &(tmp->comp);
	    pcmp = strtok(buff, "/");
	    while (pcmp != NULL)
	    {

	    	tmpc = init_comp();
			
			tmpc->str = (char*)malloc(strlen(pcmp));
			strcpy(tmpc->str,pcmp);
			
			*pcp  = tmpc;
			pcp = &(tmpc->next);   
	        
			pcmp = strtok(NULL, "/");
	    }
	    
	    pr = &(rules);
	    while((*pr)!=NULL){
	    	if(match(tmp,*pr)){
				printurl(tmp);	
				break;
			}
			pr = &((*pr)->next);
		}
		if(*pr == NULL)printf("404\n");
	}
	return 0;
}
