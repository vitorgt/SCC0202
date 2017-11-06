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

void createaboveSL(node **high, int *maxlvlcreated){
	node *newzero;
	newzero = (node *)malloc(sizeof(node));
	clearNode(newzero);
	newzero->d = *high;
	*high = newzero;
	(*maxlvlcreated)++;
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

node *searchSL(node *high, char word[50], int lvl, int maxlvlcreated){
	if(strcmp(high->word, word) == 0)//a, a
		if(lvl != maxlvlcreated)
			return searchSL(high->d, word, ++lvl, maxlvlcreated);
		else
			return high;

	else if(strcmp(high->word, word) < 0)//a, b
		if(high->r != NULL)
			return searchSL(high->r, word, lvl, maxlvlcreated);
		else
			if(lvl != maxlvlcreated)
				return searchSL(high->d, word, ++lvl, maxlvlcreated);
			else
				return high;

	else//b, a
		if(lvl != maxlvlcreated)
			return searchSL(high->l->d, word, ++lvl, maxlvlcreated);
		else
			return high->l;
}

void insertSL(node **high, char word[50], char def[140], int *maxlvlcreated){
	int i = 0;
	node *a = searchSL(*high, word, 0, *maxlvlcreated);
	node *underneath;
	if(strcmp(a->word, word) == 0)
		printf("OPERACAO INVALIDA\n");
	else{
		node *newbase;
		newbase = (node *)malloc(sizeof(node));
		clearNode(newbase);
		strcpy(newbase->word, word);
		strcpy(newbase->def, def);
		newbase->l = a;
		newbase->r = a->r;
		a->r = newbase;
		if(newbase->r != NULL)
			newbase->r->l = newbase;
		underneath = newbase;
		for(i = 1;; i++){//aqui q eu posso limitar a quantidade de SLs "i < 7"
			if(rand()%2){
				if(i > *maxlvlcreated)
					createaboveSL(high, maxlvlcreated);
				a = searchSL(*high, word, 0, (*maxlvlcreated - i));
				node *newabove;
				newabove = (node *)malloc(sizeof(node));
				clearNode(newabove);
				strcpy(newabove->word, word);
				strcpy(newabove->def, def);
				newabove->l = a;
				newabove->r = a->r;
				a->r = newabove;
				newabove->d = underneath;
				underneath->u = newabove;
				if(newabove->r != NULL)
					newabove->r->l = newabove;
				underneath = newabove;
			}
			else
				break;
		}
	}
}

void removeSL(node *high, char word[50], int maxlvlcreated){
	node *a = searchSL(high, word, 0, maxlvlcreated);
	if(strcmp(a->word, word) == 0){
		while(a->u != NULL){
			high = a->u;
			a->l->r = a->r;
			if(a->r != NULL)
				a->r->l = a->l;
			free(a);
			a = high;
		}
		a->l->r = a->r;
		if(a->r != NULL)
			a->r->l = a->l;
		free(a);
	}
	else
		printf("OPERACAO INVALIDA\n");
}

void changeSL(node *high, char word[50], char def[140], int maxlvlcreated){
	node *a = searchSL(high, word, 0, maxlvlcreated);
	if(strcmp(a->word, word) != 0)
		printf("OPERACAO INVALIDA\n");
	else{
		while(a->u != NULL){
			strcpy(a->word, word);
			strcpy(a->def, def);
			a = a->u;
		}
		strcpy(a->word, word);
		strcpy(a->def, def);
	}
}

int main(){
	char c, op, buffer[150], word[51] = {""}, def[141] = {""};
	int spc = 0, maxlvlcreated = -1, i = 0;
	node *high = NULL, *a;
	createaboveSL(&high, &maxlvlcreated);

	time_t t;
	srand((unsigned)time(&t));

	while((c = getchar())){
		if((c == EOF || c == '\n')){
			if(op){
				if(spc == 1)
					strcpy(word, buffer);
				else if(spc > 2){
					strcat(def, " ");
					strcat(def, buffer);
				}
				if(op == 'n')		//iNsercao
					insertSL(&high, word, def, &maxlvlcreated);
				else if(op == 'l')	//aLteracao
					changeSL(high, word, def, maxlvlcreated);
				else if(op == 'e')	//rEmocao
					removeSL(high, word, maxlvlcreated);
				else if(op == 'u'){	//bUsca
					a = searchSL(high, word, 0, maxlvlcreated);
					if(strcmp(a->word, word) != 0)
						printf("OPERACAO INVALIDA\n");
					else
						printf("%s %s\n", a->word, a->def);
				}
				else if(op == 'm'){//iMpressao
					a = searchSL(high, word, 0, maxlvlcreated);
					a = a->r;
					if(a->word[0] != word[0])
						printf("NAO HA PALAVRAS INICIADAS POR %c\n", word[0]);
					else
						while(a->word[0] == word[0]){
							printf("%s %s\n", a->word, a->def);
							a = a->r;
						}
				}
				else{
					printf("OPERACAO INVALIDA\n");
				}
				spc = 0;
				def[0] = '\0';
				op = '\0';
			}
			if(c == EOF)
				break;
		}
		else if(c == 'i' || c == 'a' || c == 'r' || c == 'b')
			ungetc(c, stdin);
		else if(c == ' '){
			spc++;
			if(spc == 1)
				op = buffer[1];
			else if(spc == 2)
				strcpy(word, buffer);
			else if(spc == 3)
				strcpy(def, buffer);
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
	deleteSL(high);
	return 0;
}
