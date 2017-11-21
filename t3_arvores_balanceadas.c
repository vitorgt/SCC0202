#include<stdio.h>
#include<stdlib.h>

typedef struct _rb{
	int v;//value
	char c;//color 0 BLACK; 1 RED
	struct _rb *l, *r, *p;//left, right, parent
}rb;

void clearrb(rb *a){
	a->v = 0;
	a->c = 0;
	a->l = NULL;
	a->r = NULL;
	a->p = NULL;
}

void prederb(rb *a){
	if(a->p)
		printf("%d\n", a->p->v);
	else
		printf("erro\n");
}

void printrb(rb *a, char o){
	if(o == 'i'){//in order
		if(a->l)
			printrb(a->l, o);
		if(a)
			printf("%d ", a->v);
		if(a->r)
			printrb(a->r, o);
	}
	else if(o == 'e'){//pre order
		if(a)
			printf("%d ", a->v);
		if(a->l)
			printrb(a->l, o);
		if(a->r)
			printrb(a->r, o);
	}
	else if(o == 'o'){//post order
		if(a->l)
			printrb(a->l, o);
		if(a->r)
			printrb(a->r, o);
		if(a)
			printf("%d ", a->v);
	}
}

void desalrb(rb *a){
	if(a->l)
		desalrb(a->l);
	if(a->r)
		desalrb(a->r);
	if(a)
		free(a);
}

void inserrb(rb **a, int k){
	
}

int main(){
	
	return 0;
}
