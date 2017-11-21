#include<stdio.h>
#include<stdlib.h>

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

void pred2RB(rb *a, int k, int *pred){
	if(!a) return;
	if(a->v == k)
		if(a->l)
			pred = maxRB(a->l);
	else if(a->v > k)
		pred2RB(a->l, k, pre);
	else{
		pred = a->v;
		pred2RB(a->r, k, pre);
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
			succ = minRB(a->r);
	else if(a->v > k){
		succ = a->v;
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

void printRB(rb *a, char o){
	if(o == 'i'){		//in order
		if(a->l)
			printRB(a->l, o);
		if(a)
			printf("%d ", a->v);
		if(a->r)
			printRB(a->r, o);
	}
	else if(o == 'e'){	//pre order
		if(a)
			printf("%d ", a->v);
		if(a->l)
			printRB(a->l, o);
		if(a->r)
			printRB(a->r, o);
	}
	else if(o == 'o'){	//post order
		if(a->l)
			printRB(a->l, o);
		if(a->r)
			printRB(a->r, o);
		if(a)
			printf("%d ", a->v);
	}
}

void desalRB(rb *a){
	if(a->l)
		desalRB(a->l);
	if(a->r)
		desalRB(a->r);
	if(a)
		free(a);
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

void inserRB(rb **a, int k){
}

int main(){
	return 0;
}
