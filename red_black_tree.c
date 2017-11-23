rb* inserRB(rb **ward, int v){
	rb *y = NULL, *x = NULL, *newn = NULL;

	x = (rb*)malloc(sizeof(rb));
	x->k = v;

	inserBST(ward, v);
	newn = x;
	x->c = 1;
	while(x->p->c){
		if(x->p == x->p->p->l){
			y = x->p->p->r;
			if(y->c){
				x->p->c = 0;
				y->c = 0;
				x->p->p->c = 1;
				x = x->p->p;
			}
			else{
				if(x == x->p->r){
					x = x->p;
					lroteRB(tree,x);
				}
				x->p->c = 0;
				x->p->p->c = 1;
				rroteRB(tree,x->p->p);
			}
		}
		else{
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
	(*ward)->l->c = 0;
	return(newn);

}
