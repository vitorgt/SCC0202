#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _rb{
	int v;//value
	char c;//color 0 BLACK; 1 RED
	struct _rb *l, *r, *p;//left, right, parent
}rb;

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

void pred2RB(rb *a, int k, int *pred){
	if(!a) return;
	if(a->v == k)
		if(a->l)
			*pred = maxRB(a->l);
		else return;
	else if(a->v > k)
		pred2RB(a->l, k, pred);
	else{
		*pred = a->v;
		pred2RB(a->r, k, pred);
	}
}

void pred1RB(rb *a, int k){
	if(minRB(a) > k){
		int pred = -1;
		pred2RB(a, k, &pred);
		printf("%d\n", pred);
	}
	else
		printf("erro\n");
}

void succ2RB(rb *a, int k, int *succ){
	if(!a) return;
	if(a->v == k)
		if(a->r)
			*succ = minRB(a->r);
		else return;
	else if(a->v > k){
		*succ = a->v;
		succ2RB(a->l, k, succ);
	}
	else
		succ2RB(a->r, k, succ);
}

void succ1RB(rb *a, int k){
	if(maxRB(a) > k){
		int succ = -1;
		succ2RB(a, k, &succ);
		printf("%d\n", succ);
	}
	else
		printf("erro\n");
}

void printRB(rb *a, char o, int fla){
	if(a){
		if(o == 'e'){		//pre order
			if(a->c)
				printf("\e[31m%d ", a->v);
			else
				printf("\e[0m%d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n", (void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
			printRB(a->l, o, fla);
			printRB(a->r, o, fla);
		}
		else if(o == 'o'){	//post order
			printRB(a->l, o, fla);
			printRB(a->r, o, fla);
			if(a->c)
				printf("\e[31m%d ", a->v);
			else
				printf("\e[0m%d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
		}
		else{			//in order
			printRB(a->l, o, fla);
			if(a->c)
				printf("\e[31m%d ", a->v);
			else
				printf("\e[0m%d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
			printRB(a->r, o, fla);
		}
	}
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

void rroteRB(rb **a){
	if(*a){
		rb *b = NULL;
		b = (*a)->l;
		b->p = (*a)->p;
		(*a)->p = b;
		(*a)->l = b->r;
		b->r = (*a);
		*a = b;
	}
}

void lroteRB(rb **a){
	if(*a){
		rb *b = NULL;
		b = (*a)->r;
		b->p = (*a)->p;
		(*a)->p = b;
		(*a)->r = b->l;
		b->l = (*a);
		*a = b;
	}
}

void inserRB(rb **a, int k){
	rb *newn = NULL;//, *s = *a;
	newn = (rb *)malloc(sizeof(rb));
	clearRB(newn);
	newn->v = k;
	newn->c = 1;
	if(!(*a))
		*a = newn;
	else{
		inserBST(*a, newn);
	}
	(*a)->c = 0;
}

void priall(rb *ward, int fla){
	printRB(ward,'i', fla);
	printf("\n");
	printRB(ward,'e', fla);
	printf("\n");
	printRB(ward,'o', fla);
	printf("\n");
}

int main(){
	time_t t;
	srand((unsigned)time(&t));
	rb *ward = NULL;
	int i = 0;
	for(; i < 200; i++)
		inserRB(&ward, rand()%1000);

	priall(ward, 0);
/*	lroteRB(&(ward->l));
	priall(ward, 1);
	rroteRB(&(ward->r));

	priall(ward, 1);
*/
	desalRB(ward);
	return 0;
}
