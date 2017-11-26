#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _rb{
	int v;//value
	char c;//color 0 BLACK; 1 RED
	struct _rb *l, *r, *p;//left, right, parent
}rb;

void repaiRB(rb *, rb *);

void clearRB(rb *a){
	a->v = 0;
	a->c = 0;
	a->l = NULL;
	a->r = NULL;
	a->p = NULL;
}

void desalRB(rb *a){
	if(a){
		desalRB(a->l);
		desalRB(a->r);
		free(a);
	}
}

rb *uncleRB(rb *x){
	if(x)
		if(x->p)
			if(x->p->p){
				if(x->p == x->p->p->l)
					return x->p->p->r;
				else
					return x->p->p->l;
			}
	return NULL;
}

int maxRB(rb *a){
	if(a){
		while(a->r)
			a = a->r;
		return a->v;
	}
	else
		return -1;
}

int minRB(rb *a){
	if(a){
		while(a->l)
			a = a->l;
		return a->v;
	}
	else
		return -1;
}

void succeRB(rb* a){
	rb *b = NULL;
	b = a->r;
	if(b)
		printf("%d\n", minRB(b));
	else{
		b = a->p;
		while(a == b->r){
			a = b;
			b = b->p;
		}
		if(b->p == NULL){
			printf("erro\n");
			return;
		}
		printf("%d\n", b->v);
	}
}

void predeRB(rb* a){
	rb *b = NULL;
	b = a->l;
	if(b)
		printf("%d\n", maxRB(b));
	else{
		b = a->p;
		while(a == b->l){
			if(b->p == NULL){
				printf("erro\n");
				return;
			}
			a = b;
			b = b->p;
		}
		printf("%d\n", b->v);
	}
}

void printRB(rb *a, char o, int fla){
	if(a){
		if(o == 'e'){		//pre order
			if(a->c)
				printf("\e[31m%3d ", a->v);
			else
				printf("\e[0m%3d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\e[0m\n", (void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
			printRB(a->l, o, fla);
			printRB(a->r, o, fla);
		}
		else if(o == 'o'){	//post order
			printRB(a->l, o, fla);
			printRB(a->r, o, fla);
			if(a->c)
				printf("\e[31m%3d ", a->v);
			else
				printf("\e[0m%3d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\e[0m\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
		}
		else{			//in order
			printRB(a->l, o, fla);
			if(a->c)
				printf("\e[31m%3d ", a->v);
			else
				printf("\e[0m%3d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\e[0m\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
			printRB(a->r, o, fla);
		}
	}
}

void priall(rb *ward, int fla){
	printRB(ward,'i', fla);
	printf("\n");
	//printRB(ward,'e', fla);
	//printf("\n");
	//printRB(ward,'o', fla);
	//printf("\n");
}

void inserBST(rb *a, rb *newn){
	while(1)
		if(a)
			if(a->v > newn->v)
				if(a->l)
					a = a->l;
				else{
					a->l = newn;
					newn->p = a;
					break;
				}
			else
				if(a->r)
					a = a->r;
				else{
					a->r = newn;
					newn->p = a;
					break;
				}
		else
			break;
}

void lroteRB(rb *x){
	rb *y = x->r;
	x->r = y->l;
	y->l = x;
	y->p = x->p;
	x->p = y;
	if(y->p){
		if(x == y->p->l)
			y->p->l = y;
		else
			y->p->r = y;
	}
}

void rroteRB(rb* x){
	rb *y = x->l;
	x->l = y->r;
	y->r = x;
	y->p = x->p;
	x->p = y;
	if(y->p){
		if(x == y->p->l)
			y->p->l = y;
		else
			y->p->r = y;
	}
}

void inserRB(rb **a, int k){
	printf("\tinserindo %d\n", k);
	rb *newn = NULL;
	newn = (rb *)malloc(sizeof(rb));
	clearRB(newn);
	newn->v = k;
	newn->c = 1;
	if(!(*a))
		*a = newn;
	else{
		inserBST(*a, newn);
		priall(*a, 1);
		repaiRB(newn, *a);
	}
	while((*a)->p)
		(*a) = (*a)->p;
	(*a)->c = 0;
	priall(*a, 1);
}

void fixr3RB(rb *x, rb *u, rb *a){
	x->p->c = 0;
	u->c = 0;
	x->p->p->c = 1;
	repaiRB(x->p->p, a);
}

void fixr4RB(rb *x, rb *p, rb *g, rb *a){
	int flag = 1;
	if(g->l)
		if(x == g->l->r){
			lroteRB(p);
			x = x->l;
			flag = 0;
		}
	if(g->r && flag)
		if(x == g->r->l){
			rroteRB(p);
			x = x->r;
		}

	if(x == p->l)
		rroteRB(g);
	else
		lroteRB(g);
	p->c = 0;
	g->c = 1;
}

void repaiRB(rb *x, rb *a){
	printf("\treparando %d\n", x->v);
	priall(a, 1);
	if(!(x->p))
		x->c = 0;
	else if(!(x->p->c))
		return;//se o pai for negro nao ha problema
	else if(x->p->p){//se tem avo
		rb *u = uncleRB(x);
		if(u){//se tem tio
			if(u->c)//se o tio for vermelho
				fixr3RB(x, u, a);
			else
				fixr4RB(x, x->p, x->p->p, a);
		}
		else if(x->p->c)
			fixr4RB(x, x->p, x->p->p, a);
	}
	priall(a, 1);
}

int main(){
	time_t t;
	srand((unsigned)time(&t));
	rb *ward = NULL;
	int i = 0;
	inserRB(&ward, 276);
	inserRB(&ward, 781);
	inserRB(&ward, 142);
	inserRB(&ward, 785);
	inserRB(&ward, 290);
	inserRB(&ward, 329);
	inserRB(&ward, 931);
	inserRB(&ward, 719);
	inserRB(&ward, 494);
	inserRB(&ward, 451);
	//for(; i < 200; i++)
		inserRB(&ward, rand()%1000);
	priall(ward, 0);
	desalRB(ward);
	printf("\e[0m ");
	return 0;
}
