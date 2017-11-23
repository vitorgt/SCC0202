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
				printf("\e[31m%3d ", a->v);
			else
				printf("\e[0m%3d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n", (void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
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
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
		}
		else{			//in order
			printRB(a->l, o, fla);
			if(a->c)
				printf("\e[31m%3d ", a->v);
			else
				printf("\e[0m%3d ", a->v);
			if(fla)
				printf("|%9p||l:%9p||r:%9p||p:%9p|\n",(void*)a,(void*)a->l,(void*)a->r,(void*)a->p);
			printRB(a->r, o, fla);
		}
	}
}

void priall(rb *ward, int fla){
	printRB(ward,'i', fla);
	printf("\n");
	printRB(ward,'e', fla);
	printf("\n");
	printRB(ward,'o', fla);
	printf("\n");
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

void rroteRB(rb **b){
	printf("\tRDEBUG\n");
	printf("a");
	printRB(*b,'i',1);
	rb *a = (*b)->l;
	(*b)->l = a->r;
	if(a->r)
		a->r->p = (*b);
	a->p = (*b)->p;
	if((void*)((*b)->p)){
		if(*b == (*b)->p->l)
			(*b)->p->l = a;
		else
			(*b)->p->r = a;
	}
	a->r = (*b);
	(*b)->p = a;
	printf("b");
	printRB(*b,'i',1);
	*b = a;
	printf("c");
	printRB(*b,'i',1);
}

void lroteRB(rb **a){
	printf("\tLDEBUG\n");
	printf("a");
	printRB(*a,'i',1);
	rb *b = (*a)->r;
	(*a)->r = b->l;
	if(b->l)
		b->l->p = (*a);
	b->p = (*a)->p;
	if((void*)((*a)->p)){
		if(*a == (*a)->p->l)
			(*a)->p->l = b;
		else
			(*a)->p->r = b;
	}
	b->l = (*a);
	(*a)->p = b;
	printf("b");
	printRB(*a,'i',1);
	*a = b;
	printf("c");
	printRB(*a,'i',1);
}

void inserRB(rb **a, int k){
	rb *newn = NULL, *x = NULL, *y = NULL;
	newn = (rb *)malloc(sizeof(rb));
	clearRB(newn);
	newn->v = k;
	newn->c = 1;
	if(!(*a))
		*a = newn;
	else{
		inserBST(*a, newn);
		x = newn;
		while(x->c){
			printRB(*a,'i',1);
			if(x && x->p && x->p->p){
				if(x->p == x->p->p->l){
					y = x->p->p->r;
					if(y){
						if(y->c){
							x->p->c = 0;
							y->c = 0;
							x->p->p->c = 1;
							x = x->p->p;
						}
						else{
							if(x == x->p->r){
								x = x->p;
								lroteRB(&(x));
							}
							x->c = 0;
							x->p->c = 1;
							rroteRB(&(x->p));
						}
					}
					else break;
				}
				else if(x->p == x->p->p->r){
					y = x->p->p->l;
					if(y){
						if(y->c){
							x->p->c = 0;
							y->c = 0;
							x->p->p->c = 1;
							x = x->p->p;
						}
						else{
							if(x == x->p->l){
								x = x->p;
								rroteRB(&(x));
							}
							x->c = 0;
							x->p->c = 1;
							lroteRB(&(x->p));
						}
					}
					else break;
				}
				else break;
			}
			else break;
		}
		/*
		   while(x->c){
		   if(x->p->p){
		   if(x->p == x->p->p->l){
		   y = x->p->p->r;
		   if(y->c){
		   x->p->c = 0;
		   y->c = 0;
		   x->p->p->c = 1;
		   x = x->p->p;
		   }
		   else{
		   }
		   }
		   else{
		   }
		   }
		   }*/
	}
	(*a)->c = 0;
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
	for(; i < 200; i++)
		inserRB(&ward, rand()%1000);

	priall(ward, 0);
	desalRB(ward);
	return 0;
}
