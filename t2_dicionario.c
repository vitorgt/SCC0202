#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct _node{
	char word[50], def[140];
	struct _node *l, *u, *d, *r;
}node;

/*
   Em Skip lists eh comum definir o primeiro elemento como -inf e coloca-lo em todos os niveis, como estamos lidando com caracteres podemos definir -inf como 0 (zero) sem perda de generalidade
   */

void clearNode(node *n){
	int i = 0;
	for(; i < 50; i++){
		n->word[i] = '\0';
		n->def[i] = '\0';
	}
	for(; i < 140; i++)
		n->def[i] = '\0';
	n->l = NULL;
	n->u = NULL;
	n->d = NULL;
	n->r = NULL;
}

node *searchSL(node *high, char word[50], int lvl, int maxlvlcreated){
	printf("%p\n", (void *)high);
	printf("%s\n", word);
	printf("%s\n", high->word);
	printf("act%d max%d str%d\n", lvl, maxlvlcreated, strcmp(high->word, word));
	if((strcmp(high->word, word) == 0) && (lvl == maxlvlcreated)){
		printf("a\n");
		return high;
	}
	if((strcmp(high->word, word) == 0) && (lvl != maxlvlcreated)){
		printf("b\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}

	if((strcmp(high->word, word) < 0) && (high->r != NULL)){//a, b
		printf("c\n");
		return searchSL(high->r, word, lvl, maxlvlcreated);
	}
	if((strcmp(high->word, word) < 0) && (lvl != maxlvlcreated) && (high->r == NULL)){
		printf("d\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	if((strcmp(high->word, word) < 0) && (lvl == maxlvlcreated) && (high->r == NULL)){
		printf("e\n");
		return high;
	}

	if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] != '\0')){//b, a
		printf("f\n");
		return searchSL(high->l->d, word, ++lvl, maxlvlcreated);
	}
	if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] == '\0')){
		printf("g\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] != '\0')){
		printf("h\n");
		return searchSL(high->l, word, lvl, maxlvlcreated);
	}
	if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] == '\0')){
		printf("j\n");
		return high->l;
	}

	return high;
}

void insertSL(node **high, char word[50], char def[140], int *maxlvlcreated){
	node *a = searchSL(*high, word, 0, *maxlvlcreated);
	printf("%p\n", (void *)a);
	if(strcmp(a->word, word) == 0)
		printf("OPERCAO INVALIDA\n");
	else{
		node *newn;
		newn = (node *)malloc(sizeof(node));
		clearNode(newn);
		strcpy(newn->word, word);
		strcpy(newn->def, def);
		newn->l = a;
		newn->r = a->r;
		a->r = newn;

		time_t t;
		srand((unsigned)time(&t));
		printf("%d\n", rand());
		if(rand()%2){

		}
	}
}

void test(node *n, node *a){
	strcpy(n->word, "urauliteiro");
	strcpy(n->def, "cbwucikja");
	a->r = n;
	n->l = a;
}

int main(){
	char c, op, buffer[150], word[51] = {""}, def[141] = {""};
	int spc = 0, maxlvlcreated = 0, i = 0;
	node zero, *high;
	clearNode(&zero);
	high = &zero;

	node tra;
	clearNode(&tra);
	test(&tra, &zero);

	while((c = getchar())){
		if(c == EOF || c == '\n'){
			if(spc == 1){
				strcpy(word, buffer);
				printf("word %s\n", word);
			}
			else if(spc > 2){
				strcat(def, " ");
				strcat(def, buffer);
				printf("def %s\n", def);
				def[0] = '\0';
			}
			spc = 0;
			if(op == 'n'){//iNsercao
				//insertSL(&high, word, def, &maxlvlcreated);
			}
			else if(op == 'l'){//aLteracao
			}
			else if(op == 'e'){//rEmocao
			}
			else if(op == 'u'){//bUsca
				node *a = searchSL(high, word, 0, maxlvlcreated);
				if(strcmp(a->word, word) != 0)
					printf("OPERCAO INVALIDA\n");
				else
					printf("%s %s\n", a->word, a->def);
			}
			else if(op == 'm'){//iMpressao
			}
			else{
				printf("OPERCAO INVALIDA\n");
			}
			if(c == EOF)
				break;
		}
		else if(c == 'i' || c == 'a' || c == 'r' || c == 'b')
			ungetc(c, stdin);
		else if(c == ' '){
			spc++;
			if(spc == 1){
				op = buffer[1];
				printf("op %c\n", op);
			}
			else if(spc == 2){
				strcpy(word, buffer);
				printf("word %s\n", word);
			}
			else if(spc == 3){
				strcpy(def, buffer);
			}
			else{
				strcat(def, " ");
				strcat(def, buffer);
			}
		}
		for(i = 0; (c = getchar()) && (c != ' ') && (c != '\n') && (c != EOF); i++){
			if(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
				buffer[i] = c;
		}
		buffer[i] = '\0';
		ungetc(c, stdin);
	}
	return 0;
}
