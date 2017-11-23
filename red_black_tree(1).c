#include"red_black_tree.h"

rb_red_blk_tree*RBTreeCreate(int(*CompFunc)(constvoid*,constvoid*),
		void(*DestFunc)(void*),
		void(*InfoDestFunc)(void*),
		void(*PrintFunc)(constvoid*),
		void(*PrintInfo)(void*)){
	rb_red_blk_tree*newTree;
	rb*temp;

	newTree = (rb_red_blk_tree*)SafeMalloc(sizeof(rb_red_blk_tree));
	newTree->Compare = CompFunc;
	newTree->DestroyKey = DestFunc;
	newTree->PrintKey = PrintFunc;
	newTree->PrintInfo = PrintInfo;
	newTree->DestroyInfo = InfoDestFunc;

	/*seethecommentintherb_red_blk_treestructureinred_black_tree.h*/
	/*forinformationonNULLandroot*/
	temp = newTree->NULL = (rb*)SafeMalloc(sizeof(rb));
	temp->p = temp->l = temp->r = temp;
	temp->c = 0;
	temp->key = 0;
	temp = newTree->root = (rb*)SafeMalloc(sizeof(rb));
	temp->p = temp->l = temp->r = newTree->NULL;
	temp->key = 0;
	temp->c = 0;
	return(newTree);
}

void lroteRB(rb *x){
	rb* y;
	y = x->r;
	x->r = y->l;
	if(y->l)
		y->l->p = x;
	y->p = x->p;
	if(x == x->p->l)
		x->p->l = y;
	else
		x->p->r = y;
	y->l = x;
	x->p = y;
}

void rroteRB(rb* y){
	rb* x;
	x = y->l;
	y->l = x->r;
	if(x->r)
		x->r->p = y;
	x->p = y->p;
	if(y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;
	x->r = y;
	y->p = x;
}

void TreeInsertHelp(rb_red_blk_tree*tree,rb*z){
	rb*x;
	rb*y;
	rb*NULL = tree->NULL;
	z->l = z->r = NULL;
	y = tree->root;
	x = tree->root->l;
	while(x != NULL){
		y = x;
		if(1 == tree->Compare(x->key,z->key)){/*x.key>z.key*/
			x = x->l;
		}else{/*x,key <=  z.key*/
			x = x->r;
		}
	}
	z->p = y;
	if((y == tree->root)||
			(1 == tree->Compare(y->key,z->key))){/*y.key>z.key*/
		y->l = z;
	}else{
		y->r = z;
	}
}

rb *RBTreeInsert(rb_red_blk_tree*tree,void*key){
	rb*y;
	rb*x;
	rb*newNode;
	x = (rb*)SafeMalloc(sizeof(rb));
	x->key = key;
	TreeInsertHelp(tree,x);
	newNode = x;
	x->c = 1;
	while(x->p->c){/*usesentinelinsteadofcheckingforroot*/
		if(x->p == x->p->p->l){
			y = x->p->p->r;
			if(y->c){
				x->p->c = 0;
				y->c = 0;
				x->p->p->c = 1;
				x = x->p->p;
			}else{
				if(x == x->p->r){
					x = x->p;
					lroteRB(tree,x);
				}
				x->p->c = 0;
				x->p->p->c = 1;
				rroteRB(tree,x->p->p);
			}
		}else{/*caseforx->p == x->p->p->r*/
			y = x->p->p->l;
			if(y->c){
				x->p->c = 0;
				y->c = 0;
				x->p->p->c = 1;
				x = x->p->p;
			}else{
				if(x == x->p->l){
					x = x->p;
					rroteRB(tree,x);
				}
				x->p->c = 0;
				x->p->p->c = 1;
				lroteRB(tree,x->p->p);
			}
		}
	}
	tree->root->l->c = 0;
	return(newNode);
}

void TreeSuccessor(rb* a){
	rb* *b = NULL;
	b = a->r;
	if(b){
		while(b->l)
			b = b->l;
		printf("%d\n", b->v);
	}
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

void TreePredecessor(rb* a){
	rb* *b = NULL;
	b = a->l;
	if(b){
		while(b->r)
			b = b->r;
		printf("%d\n", b->v);
	}
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
