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

void printSL(node *high, int lvl){
	node *a = high;
	printf("%d\n", lvl);
	while(a != NULL){
		printf("|%s|", a->word);
		a = a->r;
	}
	printf("\n");
	if(high->d != NULL)
		printSL(high->d, ++lvl);
}

node *searchSL(node *high, char word[50], int lvl, int maxlvlcreated){
	printf("%p\n", (void *)high);
	printf("%s\n", word);
	printf("%s\n", high->word);

	printf("\t%s\n%s\t%s\t%s\n\t%s\n", 
			((high->u->word != NULL) && (high->u->word[0] != '\0')) ? high->u->word : "(nil)", 
			((high->l->word != NULL) && (high->l->word[0] != '\0')) ? high->l->word : "(nil)", 
			((high->word != NULL) && (high->word[0] != '\0')) ? high->word : "(nil)", 
			((high->r->word != NULL) && (high->r->word[0] != '\0')) ? high->r->word : "(nil)", 
			((high->d->word != NULL) && (high->d->word[0] != '\0')) ? high->d->word : "(nil)");

	printf("act%d max%d str%d\n", lvl, maxlvlcreated, strcmp(high->word, word));
	if((strcmp(high->word, word) == 0) && (lvl == maxlvlcreated)){
		printf("a\n");
		return high;
	}
	else if((strcmp(high->word, word) == 0) && (lvl != maxlvlcreated)){
		printf("b\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}

	else if((strcmp(high->word, word) < 0) && (high->r != NULL)){//a, b
		if((strcmp(high->r->word, word) < 0)){
			printf("c\n");
			return searchSL(high->r, word, lvl, maxlvlcreated);
		}
		else{
			printf("k\n");
			return high;
		}
	}
	else if((strcmp(high->word, word) < 0) && (lvl != maxlvlcreated) && (high->r == NULL)){
		printf("d\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) < 0) && (lvl == maxlvlcreated) && (high->r == NULL)){
		printf("e\n");
		return high;
	}

	else if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] != '\0')){//b, a
		printf("f\n");
		return searchSL(high->l->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] == '\0')){
		printf("g\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] != '\0')){
		printf("h\n");
		return searchSL(high->l, word, lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] == '\0')){
		printf("j\n");
		return high->l;
	}

	return high;
}

void criaacimaSL(node **high, int *maxlvlcreated){
	node *newzero;
	newzero = (node *)malloc(sizeof(node));
	clearNode(newzero);
	newzero->d = *high;
	*high = newzero;
	(*maxlvlcreated)++;
}

void insertSL(node **high, char word[50], char def[140], int *maxlvlcreated){
	node *a = searchSL(*high, word, 0, *maxlvlcreated);
	printf("%p\n", (void *)a);
	if(strcmp(a->word, word) == 0)
		printf("OPERCAO INVALIDA\n");
	else{
		int i = 0;
		node *newn;
		newn = (node *)malloc(sizeof(node));
		clearNode(newn);
		strcpy(newn->word, word);
		strcpy(newn->def, def);
		newn->l = a;
		newn->r = a->r;
		a->r = newn;
		if(newn->r != NULL)
			newn->r->l = newn;
		for(i = 1;; i++){//aqui q eu posso limitar a quantidade de SLs "i < 7"
			if(rand()%2){
				node *b;
				printf("i%d m%d\n", i, *maxlvlcreated);
				if(i > *maxlvlcreated)
					criaacimaSL(high, maxlvlcreated);
				printf("i%d m%d\n", i, *maxlvlcreated);
				a = searchSL(*high, word, 0, (*maxlvlcreated - i));
				b = searchSL(*high, word, 0, (*maxlvlcreated - i + 1));
				printf("aretornou|%s|\n", a->word);
				printf("bretornou|%s|\n", b->word);
				node *newa;
				newa = (node *)malloc(sizeof(node));
				clearNode(newa);
				strcpy(newa->word, word);
				strcpy(newa->def, def);
				newa->l = a;
				newa->r = a->r;
				a->r = newa;
				newa->d = b;
				b->u = newa;
				if(newa->r != NULL)
					newa->r->l = newn;
				printSL(*high, 0);
			}
			else
				break;
		}
	}
}

void deleteSL(node *high){
	node *a;
	if(high->d != NULL)
		deleteSL(high->d);
	while(high->r != NULL){
		a = high->r;
		free(high);
		high = a;
	}
	free(high);
}

int main(){
	char c, op, buffer[150], word[51] = {""}, def[141] = {""};
	int spc = 0, maxlvlcreated = -1, i = 0;
	node *high = NULL;
	criaacimaSL(&high, &maxlvlcreated);

	time_t t;
	srand((unsigned)time(&t));

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
				insertSL(&high, word, def, &maxlvlcreated);
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
				node *a = searchSL(high, word, 0, maxlvlcreated);
				if(a->r->word[0] != word[0])
					printf("OPERCAO INVALIDA\n");
				else
					printf("%s %s\n", a->word, a->def);
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
		for(i = 0; (c = getchar()) && (c != ' ') && (c != '\n') && (c != EOF); i++)
			if(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
				buffer[i] = c;
			else
				i--;
		buffer[i] = '\0';
		ungetc(c, stdin);
	}
	printSL(high, 0);
	deleteSL(high);
	return 0;
}
