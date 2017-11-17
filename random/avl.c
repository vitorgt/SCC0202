#include<stdio.h>
#include<stdlib.h>

typedef struct _avl{
	int k;
	struct _avl *l, *r;
}avl;

void clearavl(avl *a){
	a->k = 0;
	a->l = NULL;
	a->r = NULL;
}

void inseravl(avl **a, int v){
	if(!(*a)){
		avl *newn = (avl *)malloc(sizeof(avl));
		clearavl(newn);
		newn->k = v;
		*a = newn;
	}
}

void printavl(avl *a, char o){
	if(o == 'i'){
		if(a->l)
			printavl(a->l, o);
		if(a)
			printf("%d ", a->k);
		if(a->r)
			printavl(a->r, o);
	}
	if(o == 'e'){
		if(a)
			printf("%d ", a->k);
		if(a->l)
			printavl(a->l, o);
		if(a->r)
			printavl(a->r, o);
	}
	if(o == 'o'){
		if(a->l)
			printavl(a->l, o);
		if(a->r)
			printavl(a->r, o);
		if(a)
			printf("%d ", a->k);
	}
}

int main(){
	avl *ward = NULL;
	inseravl(&ward, 100);
	printavl(ward, 'i');
	return 0;
}
