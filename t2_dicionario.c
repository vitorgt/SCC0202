#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int main(){
	char c, op, *buffer, def[140];
	int spc = 0, ondepor = 0;
	node zero, in;
	clearNode(&zero);
	clearNode(&in);

	while(c = getchar()){
		if(c == EOF || c == '\n'){
			if(spc == 1){
				spc = 0;
				printf("word %s\n", buffer);
				//node.def = buffer;
			}
			else if(spc > 2){
				spc = 0;
				strcat(def, " ");
				strcat(def, buffer);
				printf("fimdef %s\n", def);
				def[0] = '\0';
				//node.def = buffer;
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
				printf("word %s\n", buffer);
				//node.word = buffer;
			}
			else if(spc > 2){
				if(spc > 3)
					strcat(def, " ");
				strcat(def, buffer);
			}
		}
		scanf("%ms", &buffer);
	}
	free(buffer);
	return 0;
}
