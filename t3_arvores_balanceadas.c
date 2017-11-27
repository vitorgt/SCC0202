//8m38.378s+48m41.623s+35m4.664s

#include<stdio.h>
#include<stdlib.h>

typedef struct _rb{
	int v;//value
	char c;//color 0 BLACK; 1 RED
	struct _rb *l, *r, *p;//left, right, parent
}rb;

void clearRB(rb *a){//limpa os campos dos nos
	a->v = 0;
	a->c = 0;
	a->l = NULL;
	a->r = NULL;
	a->p = NULL;
}

void desalRB(rb *a){//desaloca a arvore inteira
	if(a){
		desalRB(a->l);
		desalRB(a->r);
		free(a);
	}
}

int maxRB(rb *a){
	if(a){//se a for nao nulo
		while(a->r)//enquanto existirem filhos para a direita
			a = a->r;//a recebe o filho da direita
		return a->v;//por fim a tera o no mais a direita da arvore (max)
	}
	else//se a for nulo
		return -1;//retorna erro
}

int minRB(rb *a){//similar ao maximo porem para a esquerda
	if(a){
		while(a->l)
			a = a->l;
		return a->v;
	}
	else
		return -1;
}

rb *searcRB(rb *a, int k){//procura o endereco do no com dada chave
	while(a){//enquanto a for nao nulo
		if(a->v == k)//se for o valor procurado
			return a;
		else if(a->v > k)//se o no atual tiver uma chave maior que a procurada
			a = a->l;//vai para a esquerda
		else//senao vai para a direita
			a = a->r;
	}
	return NULL;
}

void succeRB(rb *ward, int k){//imprime o sucessor de uma dada chave
	if(k >= maxRB(ward)){//se a chave procurada for maior ou igual ao maximo da arvore nao tem sucessor
		printf("erro\n");
		return;
	}
	rb *a = searcRB(ward, k);//procura seu enderesso
	if(!a){//se retornar nulo
		printf("erro\n");
		return;
	}
	rb *b = NULL;
	b = a->r;
	if(b)//se tiver filho para a direita
		printf("%d\n", minRB(b));
	else{
		b = a->p;//sobe
		while(a == b->r){//enquanto a for o filho da direita de b
			a = b;
			b = b->p;//sobe
		}
		if(!(b->p)){//se atingir a raiz
			printf("erro\n");
			return;
		}
		printf("%d\n", b->v);
	}
}

void predeRB(rb *ward, int k){//similar ao sucessor porem com direcoes inversas
	if(k <= minRB(ward)){
		printf("erro\n");
		return;
	}
	rb *a = searcRB(ward, k);
	if(!a){
		printf("erro\n");
		return;
	}
	rb *b = NULL;
	b = a->l;
	if(b)
		printf("%d\n", maxRB(b));
	else{
		b = a->p;
		while(a == b->l){
			if(!(b->p)){
				printf("erro\n");
				return;
			}
			a = b;
			b = b->p;
		}
		printf("%d\n", b->v);
	}
}

void printRB(rb *a, char o){//imprime a arvore (ou subarvore)
	if(a){
		if(o == 'e'){		//pre order
			if(a->c)//se for vermelho
				printf("\e[31m%d ", a->v);//imprime vermelho
			else
				printf("\e[0m%d ", a->v);
			printRB(a->l, o);
			printRB(a->r, o);
		}
		else if(o == 'o'){	//post order
			printRB(a->l, o);
			printRB(a->r, o);
			if(a->c)
				printf("\e[31m%d ", a->v);
			else
				printf("\e[0m%d ", a->v);
		}
		else{			//in order
			printRB(a->l, o);
			if(a->c)
				printf("\e[31m%d ", a->v);
			else
				printf("\e[0m%d ", a->v);
			printRB(a->r, o);
		}
	}
}

void inserBST(rb *a, rb *newn){//insercao em arvore binaria de busca
	while(1)
		if(a)//se a raiz dada nao for nula
			if(a->v > newn->v)//se o no a ser colocado for menor
				if(a->l)//se existir filho para a direita
					a = a->l;//vai para a direita e reitera
				else{//se nao tiver filho para a esquerda
					a->l = newn;//coloca o novo no aqui
					newn->p = a;
					break;//finalizado
				}
			else//similar acima
				if(a->r)
					a = a->r;
				else{
					a->r = newn;
					newn->p = a;
					break;
				}
		else//se a raiz dada for nula
			break;
}

void lroteRB(rb *x, rb **a){//rotacao para a esquerda
	rb *y = x->r;//y recebe o filho da direita de x
	x->r = y->l;//direita de x recebe esquerda de y
	if(y->l)//se y tiver filho pra esquerda
		y->l->p = x;//o pai do filho da esquerda de y recebe x
	y->p = x->p;//o pai de y agora aponta para o pai de x
	if(!(x->p))//se x nao tiver pai (raiz)
		*a = y;//muda a raiz da arvore para y
	else if(x == x->p->l)//se tem pai e x eh filho da esquerda
		x->p->l = y;//o filho da esquerda do pai de x agora eh y
	else//se tem pai e x eh filho da direita
		x->p->r = y;//o filho da direita do pai de x agora eh y
	y->l = x;//o filho da esquerda de y recebe x
	x->p = y;//o pai de x agora eh y
}

void rroteRB(rb* x, rb **a){//similar a rotacao acima
	rb *y = x->l;
	x->l = y->r;
	if(y->r)
		y->r->p = x;
	y->p = x->p;
	if(!(x->p))	
		*a = y;
	else if(x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	y->r = x;
	x->p = y;
}

void fixupRB(rb *z, rb **a){//conserta o balanceamento e a coloracao da arvore
	while(z->p){//enquanto z tiver pai
		if(z->p->c){//se o pai for vermelho
			rb *y = NULL;
			if(z->p->p){//se tiver avo
				if(z->p == z->p->p->l){//se o pai for filho esquerdo
					y = z->p->p->r;//y recebe o tio de z (filho direito do avo nesse caso)
					if(y && y->c){//se o tio nao for nulo e for vermelho
						z->p->c = 0;//pai de z fica preto
						y->c = 0;//tio de z fica preto
						z->p->p->c = 1;//avo de z fica vermelho
						z = z->p->p;//z recebe seu avo e reitera
					}
					else if(z == z->p->r){//(se nao tiver tio ou for preto) e z for filho direito
						z = z->p;//z recebe seu pai
						lroteRB(z, a);//rotacao esquerda em z
						z->p->c = 0;//pai do novo z fica preto
						z->p->p->c = 1;//seu avo fica vermelho
						rroteRB(z->p->p, a);//roda para a direita o avo de z
					}
					else{//(se nao tiver tio ou for preto) e z for filho esquerdo
						z->p->c = 0;//pai de z fica preto
						z->p->p->c = 1;//seu avo fica vermelho
						rroteRB(z->p->p, a);//roda o avo de z para a direita
					}
				}
				else{//se o pai for filho direito (similar acima)
					y = z->p->p->l;
					if(y && y->c){
						z->p->c = 0;
						y->c = 0;
						z->p->p->c = 1;
						z = z->p->p;
					}
					else if(z == z->p->l){
						z = z->p;
						rroteRB(z, a);
						z->p->c = 0;
						z->p->p->c = 1;
						lroteRB(z->p->p, a);
					}
					else{
						z->p->c = 0;
						z->p->p->c = 1;
						lroteRB(z->p->p, a);
					}
				}
			}
			else//se nao tiver avos
				break;
		}
		else//se o pai for preto
			break;
	}
	(*a)->c = 0;//repinta a raiz de preto
}

void inserRB(rb **a, int k){//insere em arvore vermelho e preto
	rb *newn = NULL;
	newn = (rb *)malloc(sizeof(rb));
	clearRB(newn);//esvazia o novo no
	newn->v = k;//recebe os dados
	newn->c = 1;//pinta de vermalho
	if(!(*a))//se a raiz for nula (primeiro caso)
		*a = newn;
	else{
		inserBST(*a, newn);//insere em ABB normal
		fixupRB(newn, a);//rebalanceia e repinta
	}
	while((*a)->p)//se a raiz tiver pais (nao eh mais a raiz)
		(*a) = (*a)->p;//sobe o ponteiro da raiz
	(*a)->c = 0;//repinta a raiz de preto
}

int main(){
	int n = 0, i = 0, o = 0, in = 0;//declaracoes
	rb *ward = NULL;
	scanf("%d\n", &n);//escaneia a quantidade de operacoes
	for(i = 0; i < n; i++){
		scanf("%d", &o);//escaneia a operacao
		if(o == 1){//insercao
			scanf("%d\n", &in);
			inserRB(&ward, in);
			o = 0;
			in = 0;
		}
		else if(o == 2){//sucessor
			scanf("%d\n", &in);
			succeRB(ward, in);
			o = 0;
			in = 0;
		}
		else if(o == 3){//predecessor
			scanf("%d\n", &in);
			predeRB(ward, in);
			o = 0;
			in = 0;
		}
		else if(o == 4){//maximo
			printf("%d\n", maxRB(ward));
			o = 0;
		}
		else if(o == 5){//minimo
			printf("%d\n", minRB(ward));
			o = 0;
		}
		else if(o == 6){//imprime pre ordem
			printRB(ward, 'e');
			printf("\n");
			o = 0;
		}
		else if(o == 7){//imprime em ordem
			printRB(ward, 'i');
			printf("\n");
			o = 0;
		}
		else if(o == 8){//imprime pos ordem
			printRB(ward, 'o');
			printf("\n");
			o = 0;
		}
		else//operacao nao reconhecida
			printf("erro\n");
	}
	desalRB(ward);//desaloca toda a arvore
	return 0;
}
