//by paroid

#include<iostream>
#include<string>
#include<time.h>
using namespace std;

#define _cmp_ >

class tnode{
public:
	tnode(int v,string n,string in,tnode *l=NULL,tnode *r=NULL,tnode *p=NULL);
	void show();
	int tel;
	string name,info;
	tnode *lc,*rc,*par;
};
tnode::tnode(int v,string n,string in,tnode *l,tnode *r,tnode *p){
	tel=v,name=n,info=in,lc=l,rc=r,par=p;
}

void tnode::show(){
	if(lc)
		lc->show();
	cout<<"TEL: "<<tel<<"   -Name: "<<name<<"   -Info: "<<info<<endl;
	if(rc)
		rc->show();
}

class tree{
public:
	tree(tnode *r=NULL);
	bool ins(tnode *no);  // insert
	bool search(int key,tnode *&pos);	// search
	bool del(int key);     // delete
	tnode *root;
	int total;
};

tree::tree(tnode *r){
	root=r,total=0;
}

bool tree::ins(tnode *no){	// insert node
	if(!root){
		root=no;
		return total+++1;
	}
	tnode *p=root,*tem=root;
	bool lr(0);
	while(tem){
		if(tem->tel==no->tel)
			return 1;
		if(tem->tel _cmp_ no->tel)
			tem=tem->lc,lr=0;
		else
			tem=tem->rc,lr=1;
		if(tem)
			p=tem;
	}
	if(lr)
		p->rc=no;
	else
		p->lc=no;
	no->par=p;
	return total+++1;
}

bool tree::search(int key,tnode *&pos){	// search the node with telue key
	if(!root)
		return 0;
	tnode *p=root;
	while(p){
		if(p->tel==key){
			pos=p;
			return 1;
		}
		if(p->tel _cmp_ key)
			p=p->lc;
		else
			p=p->rc;
	}
	return 0;
}

bool tree::del(int key){	// delete the node with telue key
	tnode *p;
	if(!search(key,p))
		return 0;
	if(!p->rc){		// only L-child
		if(p==root){
			root=p->lc;
			delete p;
			return total--+1;
		}
		tnode *tem=p;
		if(p->par->lc==p)
			p->par->lc=p->lc;
		else
			p->par->rc=p->lc;
		if(p->lc)
			p->lc->par=p->par;
		delete tem;
		return total--;
	}
	else if(!p->lc){	// only R-child
		if(p==root){
			root=p->rc;
			delete p;
			return total--+1;
		}
		tnode *tem=p;
		if(p->par->lc==p)
			p->par->lc=p->rc;
		else
			p->par->rc=p->rc;
		if(p->rc)
			p->rc->par=p->par;
		delete tem;
		return total--;
	}
	else {		// random delete
		srand((unsigned)time(NULL));
		if(rand()&1){ // delete L
			tnode *q=p,*s=p->lc;
			while(s->rc){
				q=s;
				s=q->rc;
			}
			p->tel=s->tel,p->name=s->name,p->info=s->info; //copy
			if(q!=p)
				q->rc=s->lc;
			else
				q->lc=s->lc;
			if(s->lc)
				s->lc->par=q;
			delete s;
		}
		else{	// delete R
			tnode *q=p,*s=p->rc;
			while(s->lc){
				q=s;
				s=q->lc;
			}
			p->tel=s->tel,p->name=s->name,p->info=s->info; //copy
			if(q!=p)
				q->lc=s->rc;
			else
				q->rc=s->rc;
			if(s->rc)
				s->rc->par=q;
			delete s;
		}
		return total--;
	}
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	tree tt;
	tnode *p;
	int v;
	string str,name;
	for(int i=0;i<11;i++){
		cin>>v>>name>>str;
		p=new tnode(v,name,str);
		tt.ins(p);
	}
	tt.root->show();
	system("pause");
	return 0;
}

