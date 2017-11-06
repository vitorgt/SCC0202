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
		printf("\t%s\n%s\t%s\t%s\n\t%s\n", 
				((a->u->word != NULL) && (a->u->word[0] != '\0')) ? a->u->word : "(nil)", 
				((a->l->word != NULL) && (a->l->word[0] != '\0')) ? a->l->word : "(nil)", 
				((a->word != NULL) && (a->word[0] != '\0')) ? a->word : "(nil)", 
				((a->r->word != NULL) && (a->r->word[0] != '\0')) ? a->r->word : "(nil)", 
				((a->d->word != NULL) && (a->d->word[0] != '\0')) ? a->d->word : "(nil)");
		a = a->r;
	}
	printf("\n");
	a = high;
	printf("%d\n", lvl);
	while(a != NULL){
		printf("|%s|", a->word);
		a = a->r;
	}
	printf("\n");
	if(high->d != NULL)
		printSL(high->d, ++lvl);
}

void printxSL(node *high, int lvl){
	node *a = high;
	printf("%d\n", lvl);
	while(a != NULL){
		printf("|%p(%s)|", (void *)a, a->word);
		a = a->r;
	}
	printf("|%p(%s)|", (void *)a, a->word);
	printf("\n");
	if(high->d != NULL)
		printxSL(high->d, ++lvl);
}

node *searchSL(node *high, char word[50], int lvl, int maxlvlcreated){
	//printf("%p\n", (void *)high);
	//printf("%s\n", word);
	//printf("%s\n", high->word);
	//printf("act%d max%d str%d\n", lvl, maxlvlcreated, strcmp(high->word, word));
	if((strcmp(high->word, word) == 0) && (lvl == maxlvlcreated)){
		//printf("a\n");
		return high;
	}
	else if((strcmp(high->word, word) == 0) && (lvl != maxlvlcreated)){
		//printf("b\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}

	else if((strcmp(high->word, word) < 0) && (high->r != NULL)){//a, b
		//printf("c\n");
		return searchSL(high->r, word, lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) < 0) && (lvl != maxlvlcreated) && (high->r == NULL)){
		//printf("d\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) < 0) && (lvl == maxlvlcreated) && (high->r == NULL)){
		//printf("e\n");
		return high;
	}

	else if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] != '\0')){//b, a
		//printf("f\n");
		return searchSL(high->l->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) > 0) && (lvl != maxlvlcreated) && (high->l->word[0] == '\0')){
		//printf("g\n");
		return searchSL(high->d, word, ++lvl, maxlvlcreated);
	}
	else if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] != '\0')){
		if(word[1] != '\0'){
			//printf("h\n");
			return searchSL(high->l, word, lvl, maxlvlcreated);
		}
		else{
			if(high->l->word[0] == word[0]){
				//printf("k\n");
				return high->l;
			}
			else if(high->word[0] == word[0]){
				//printf("k\n");
				return high;
			}
		}
	}
	else if((strcmp(high->word, word) > 0) && (lvl == maxlvlcreated) && (high->l->word[0] == '\0')){
		if(word[1] != '\0'){
			//printf("j\n");
			return high->l;
		}
		else{
			if(high->l->word[0] == word[0]){
				//printf("k\n");
				return high->l;
			}
			else if(high->word[0] == word[0]){
				//printf("k\n");
				return high;
			}
		}
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
				//printf("i%d m%d\n", i, *maxlvlcreated);
				if(i > *maxlvlcreated)
					criaacimaSL(high, maxlvlcreated);
				a = searchSL(*high, word, 0, (*maxlvlcreated - i));
				b = searchSL(*high, word, 0, (*maxlvlcreated - i + 1));
				//printxSL(*high, 0);
				//printf("aretornou|%p(%s)|\n", (void*)a, a->word);
				//printf("bretornou|%p(%s)|\n", (void*)b, b->word);
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
					newa->r->l = newa;
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
		printf("OPERCAO INVALIDA\n");
}

void changeSL(node *high, char word[50], char def[140], int maxlvlcreated){
	node *a = searchSL(high, word, 0, maxlvlcreated);
	if(strcmp(a->word, word) != 0)
		printf("OPERCAO INVALIDA\n");
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
	criaacimaSL(&high, &maxlvlcreated);

	time_t t;
	srand((unsigned)time(&t));

	while((c = getchar())){
		if(c == EOF || c == '\n'){
			if(c == EOF)
				break;
			if(spc == 1){
				strcpy(word, buffer);
				//printf("word %s\n", word);
			}
			else if(spc > 2){
				strcat(def, " ");
				strcat(def, buffer);
				//printf("def %s\n", def);
			}
			if(op == 'n'){		//iNsercao
				insertSL(&high, word, def, &maxlvlcreated);
			}
			else if(op == 'l'){	//aLteracao
				changeSL(high, word, def, maxlvlcreated);
			}
			else if(op == 'e'){	//rEmocao
				removeSL(high, word, maxlvlcreated);
			}
			else if(op == 'u'){	//bUsca
				a = searchSL(high, word, 0, maxlvlcreated);
				if(strcmp(a->word, word) != 0)
					printf("OPERCAO INVALIDA\n");
				else
					printf("%s %s\n", a->word, a->def);
			}
			else if(op == 'm'){//iMpressao
				a = searchSL(high, word, 0, maxlvlcreated);
				if(a->word[0] != word[0])
					printf("OPERCAO INVALIDA\n");
				else
					while(a->word[0] == word[0]){
						printf("%s %s\n", a->word, a->def);
						a = a->r;
					}
			}
			else{
				printf("OPERCAO INVALIDA\n");
			}
			spc = 0;
			def[0] = '\0';
			op = '\0';
		}
		else if(c == 'i' || c == 'a' || c == 'r' || c == 'b')
			ungetc(c, stdin);
		else if(c == ' '){
			spc++;
			if(spc == 1){
				op = buffer[1];
				//printf("op %c\n", op);
			}
			else if(spc == 2){
				strcpy(word, buffer);
				//printf("word %s\n", word);
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
	//printxSL(high, 0);
	deleteSL(high);
	return 0;
}
