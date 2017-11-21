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

void predeRB(rb *a, int k){
	if(minRB(a) < k){
	}
	else
		printf("erro\n");
}

void sucesRB(rb *a, int k){
	if(maxRB(a) > k){
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
	while(a->r)
		a = a->r;
	return a->v;
}

int minRB(rb *a){
	while(a->l)
		a = a->l;
	return a->v;
}

void inserRB(rb **a, int k){
}

int main(){
	return 0;
}
