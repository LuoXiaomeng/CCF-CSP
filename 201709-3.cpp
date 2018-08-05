#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRING 0
#define OBJECT 1
#define O_STR "STRING"
#define O_OBJ "OBJECT"
#define O_NON "NOTEXIST"

struct key {
	char type;
	char str[80];

	char s_value[80];
	struct key* k_value;

	struct key* next;
};

char* str2str(char*pb, char*pn) {
	while (*(pb++) != '\"');
	while (*pb != '\"') {
		if (*pb == '\\')pb++;
		*(pn++) = *(pb++);
	}
	*pn = 0;
	pb++;
	return pb;
}
char* str2obj(char *pb, struct key** dst);
char* str2key(char *pb, struct key** dst) {
	struct key *key = (struct key*)malloc(sizeof(struct key));
	key->next = NULL;

	pb = str2str(pb, key->str);

	while (*(pb++) != ':');
	while (*pb == ' ')pb++;
	if (*pb == '\"') {
		key->type = STRING;
		pb = str2str(pb, key->s_value);
	}
	else if (*pb == '{') {
		key->type = OBJECT;
		pb = str2obj(pb, &(key->k_value));
	}
	*dst = key;
	return pb;
}
char* str2obj(char *pb, struct key** dst) {
	struct key* obj = NULL, **key = &obj;
	while (*pb != '}') {
		if (*pb == '\"') {
			pb = str2key(pb, key);
			key = &((*key)->next);
		}
		else pb++;
	}
	pb++;
	*dst = obj;
	return pb;
}
struct key* str2rst(char *buff, struct key*obj) {
	char*pk = strtok(buff, ".");
	while (pk != NULL) {
		while (obj != NULL && strcmp(obj->str, pk))obj = obj->next;
		if (obj == NULL)return NULL;
		pk = strtok(NULL, ".");
		if (pk != NULL) {
			if (obj->type == OBJECT)obj = obj->k_value;
			else return NULL;
		}
	}
	return obj;
}
int main() {
	char buff[8000];
	int m, n;
	scanf("%d %d", &n, &m);
	gets(buff);

	struct key *obj = NULL, *rst;

	for (int i = 0; i<n; i++) {
		gets(buff + strlen(buff));
	}

	str2obj(buff, &obj);

	for (int i = 0; i<m; i++) {
		gets(buff);
		rst = str2rst(buff, obj);

		if (rst == NULL) printf("%s\n", O_NON);
		else if (rst->type == STRING) printf("%s %s\n", O_STR, rst->s_value);
		else if (rst->type == OBJECT) printf("%s\n", O_OBJ);
	}
	return 0;
}
