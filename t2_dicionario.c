#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct _node{
	char word[50], def[140];//palavra de ate 50 carateres e definicao de ate 140
	struct _node *l, *u, *d, *r;//ponteiros para esquerda, cima, baixo e direita
}node;

/*
   Em Skip lists eh comum definir o primeiro elemento como -inf e coloca-lo em todos os niveis, como estamos lidando com caracteres podemos definir -inf como 0 (zero) sem perda de generalidade
 */

void clearNode(node *n){//inicializacao de nodos
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

void createaboveSL(node **ward, int *maxlvlcreated){//cria um nivel acima de todos
	node *newzero;
	newzero = (node *)malloc(sizeof(node));
	clearNode(newzero);
	newzero->d = *ward;//o novo sentinela->d aponta para o sentina atual
	*ward = newzero;//o novo sentinela vira o sentinela atual
	(*maxlvlcreated)++;
}

void deleteSL(node *ward){//deleta a SkipList inteira
	node *a;
	if(ward->d != NULL)//se tiver nodos abaixo chama a deleteSL de novo para a linha de baixo
		deleteSL(ward->d);
	while(ward != NULL){//enquanto o da direita nao for nulo 
		a = ward->r;//a guarda o endereco do proximo da direita
		free(ward);//libera o atual
		ward = a;//o sentinela recebe o proximo da direita
	}
}

node *searchSL(node *ptr, char word[50], int lvl, int maxlvlcreated){//procura o elemento com a mesma palavra ou se nao achar retorna o anterior a ela alfabeticamente
	if(strcmp(ptr->word, word) == 0)//se for a mesma palavra
		if(lvl != maxlvlcreated)//se ainda nao for o nivel maximo ja criado
			return searchSL(ptr->d, word, ++lvl, maxlvlcreated);//desce
		else
			return ptr;//retorna o ponteiro encontrado

	else if(strcmp(ptr->word, word) < 0)//strcmp(a, b)//se a palavra no ponteiro for alfabeticamente menor que a que sera inserida
		if(ptr->r != NULL)//se o proximo da direita nao for nulo
			return searchSL(ptr->r, word, lvl, maxlvlcreated);//vai pra direira
		else
			if(lvl != maxlvlcreated)//se ainda nao for o nivel maximo ja criado
				return searchSL(ptr->d, word, ++lvl, maxlvlcreated);//desce
			else
				return ptr;//retorna o ponteiro encontrado

	else//strcmp(b, a)//se a palavra no ponteiro for alfabeticamente maior que a que sera inserida
		if(lvl != maxlvlcreated)//se ainda nao for o nivel maximo ja criado
			return searchSL(ptr->l->d, word, ++lvl, maxlvlcreated);//volta para a esquerda e desce
		else
			return ptr->l;//retorna o da esquerda
}

void insertSL(node **ward, char word[50], char def[140], int *maxlvlcreated){//insere elementos na SkipList
	int i = 0, first = 1;
	node *a = NULL, *underneath = NULL;
	for(i = 0; rand()%2 || first; i++){//se o rand deixar cria niveis acima mas sempre entra uma vez pelo menos a primeira
		if(i > *maxlvlcreated)//se o nivel que for criar ainda nao existir
			createaboveSL(ward, maxlvlcreated);//crio um acima
		a = searchSL(*ward, word, 0, (*maxlvlcreated - i));//procuro na SL do comeco ate o nivel i onde colocar o novo node
		/*
		   a recebe o endereco da busca pela palavra a ser inserida
		   se ela ainda nao estiver na SkipList retornara um ponteiro para onde ela deve ser colocada em ordem alfabetica
		   se ela ja estiver mostra operacao invalida
		 */
		if(strcmp(a->word, word) == 0){
			printf("OPERACAO INVALIDA\n");
			break;
		}
		node *newnode;
		newnode = (node *)malloc(sizeof(node));//aloca e limpa o novo nodo
		clearNode(newnode);
		strcpy(newnode->word, word);//coloco as informacoes 
		strcpy(newnode->def, def);
		newnode->l = a;//manipulacoes de ponteiros
		newnode->r = a->r;
		a->r = newnode;
		newnode->d = underneath;//o pontiero para baixo do novo nodo recebe o debaixo
		if(underneath != NULL)
			underneath->u = newnode;
		if(newnode->r != NULL)
			newnode->r->l = newnode;
		underneath = newnode;//o ponteiro para o debaixo recebe o novo nodo caso seja criado algum acima desse novo
		first = 0;
	}
}

void removeSL(node *ward, char word[50], int maxlvlcreated){//remove elementos da SL
	node *a = searchSL(ward, word, 0, maxlvlcreated);
	if(strcmp(a->word, word) == 0)//se achar o nodo com a mesma palavra
		while(a != NULL){//enquanto a nao for nulo
			ward = a->u;//uso o ponteiro sentinela (sem altera-lo pq aqui ele eh apenas uma copia do original) para guardar o endereco de cima
			a->l->r = a->r;//manipulacao de ponteiros
			if(a->r != NULL)
				a->r->l = a->l;
			free(a);//libera a
			a = ward;//a recebe o ponteiro guardado
		}
	else//se nao achar
		printf("OPERACAO INVALIDA\n");
}

void changeSL(node *ward, char word[50], char def[140], int maxlvlcreated){//altera a definicao de uma palavra
	node *a = searchSL(ward, word, 0, maxlvlcreated);
	if(strcmp(a->word, word) != 0)//se nao achar a palavra na SL
		printf("OPERACAO INVALIDA\n");
	else
		while(a != NULL){//enquanto a nao for nulo
			strcpy(a->def, def);//altera a definicao
			a = a->u;//a recebe o de cima
		}
}

int main(){
	char c, op, buffer[150], word[51] = {""}, def[141] = {""};//definicoes
	int spc = 0, maxlvlcreated = -1, i = 0;//spc = contador de espacos lidos; maxlvlcreated = nives de skiplists criados
	node *ward = NULL, *a;//ward = sentinela
	createaboveSL(&ward, &maxlvlcreated);//cria a primeira lista

	time_t t;
	srand((unsigned)time(&t));//defino a seed do rand

	while((c = getchar())){
		if((c == EOF || c == '\n')){
			if(op){//se tiver alguma operacao a ser realizada
				if(spc == 1)//se na linha so tem um espaco
					strcpy(word, buffer);//agora tenho que tratar uma palavra
				else if(spc > 2){//se tiver mais que dois agora tenho que tratar uma definicao
					strcat(def, " ");
					strcat(def, buffer);
				}
				if(op == 'n')		//iNsercao
					insertSL(&ward, word, def, &maxlvlcreated);//chama a funcao insere
				else if(op == 'l')	//aLteracao
					changeSL(ward, word, def, maxlvlcreated);//chama a funcao altera
				else if(op == 'e')	//rEmocao
					removeSL(ward, word, maxlvlcreated);//chama a funcao remove
				else if(op == 'u'){	//bUsca
					a = searchSL(ward, word, 0, maxlvlcreated);//chama a funcao busca
					if(strcmp(a->word, word) != 0)//se nao encontrar a palavra
						printf("OPERACAO INVALIDA\n");
					else//se encontrar
						printf("%s %s\n", a->word, a->def);
				}
				else if(op == 'm'){//iMpressao
					a = searchSL(ward, word, 0, maxlvlcreated);//chama a funcao busca
					a = a->r;
					/*
					   como nao existem palavras de um unico char a busca vai retornar um nodo antes
					   vou um nodo pra frente
					 */
					if(a->word[0] != word[0])//se o char inicial nao for o procurado
						printf("NAO HA PALAVRAS INICIADAS POR %c\n", word[0]);
					else
						while(a->word[0] == word[0]){//enquanto o char inicial for igual ao pedido
							printf("%s %s\n", a->word, a->def);//imprime
							a = a->r;//vai para a proxima a direita
						}
				}
				else{//se nao reconhecer a  operacao 
					printf("OPERACAO INVALIDA\n");
				}
				spc = 0;//zera o contador de espacos que tem na linha
				op = '\0';//zera a operacao
			}
			if(c == EOF)
				break;
		}
		else if(c == 'i' || c == 'a' || c == 'r' || c == 'b')//o primeiro getchar pega um char da primeira operacao
			ungetc(c, stdin);//entao devolvo ele
		else if(c == ' '){
			spc++;//aumenta o contador de espacos que tem a linha
			if(spc == 1)//se for um tenho que tratar uma operacao
				op = buffer[1];
			else if(spc == 2)//se for dois tenho que tratar uma palavra
				strcpy(word, buffer);
			else if(spc == 3)//se for tres comeco a tratar uma definicao
				strcpy(def, buffer);
			else{//se forem acima de tres coloco um espaco no final e concateno as palavras que vao entrando na definicao
				strcat(def, " ");
				strcat(def, buffer);
			}
		}
		for(i = 0; (c = getchar()) && (c != ' ') && (c != '\n') && (c != EOF); i++)//pego os chars da entrada 
			if(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))//se forem letras 
				buffer[i] = c;//entra para o buffer
			else
				i--;
		buffer[i] = '\0';//concluo o buffer
		ungetc(c, stdin);//devolvo o ' ', '\n' e o EOF para serem lidos na proxima iteracao do while
	}
	deleteSL(ward);//libera a SkipList
	return 0;
}
