//by paroid

#include<iostream>
#include<string>
using namespace std;
#define MAX 200		// expression length
#define LEN 100    	//stack length

void gray(int n,bool *code){	// ȡ����һ��  00...000 -  1000...
	int t=0,i;
	for (i=0;i<n;t+=code[i++]);
	if (t&1)
		for (n--;!code[n];n--);
	code[n-1]^=1;
}

template<class type> class Stack{    // template stack
public:
	Stack(int len=LEN);
	void pop(type &e);
	void push(type e);
	bool emp();
	type getop();
private:
	type *data;
	int len;
	int top;
};
template<class type> Stack<type>::Stack<type>(int length){
	data=new type[length];
	len=length;
	top=0;
}
template<class type> void Stack<type>::pop(type &e){
	if(top)
		e=data[--top];
}
template<class type> void Stack<type>::push(type d){
	data[top++]=d;
}
template<class type> bool Stack<type>::emp(){
	if(top)
		return false;
	else
		return true;
}
template<class type> type Stack<type>::getop(){
	return data[top-1];
}
char con(char op){     // priority level test
	switch(op){
		case '|':
			return 1;
		case '&':
			return 2;
		case '^':
			return 3;
		case '~':
			return 4;
		default:
			return 0;
	}
}

class tree{				// binary tree
public:
	tree(char c,tree *l=NULL,tree *r=NULL);
	bool fall(int n,char *m=NULL,bool *val=NULL);
	char name;
	tree *lc,*rc;
};
tree::tree(char c,tree *l,tree *r){	// constructor
	name=c,lc=l,rc=r;
}

bool tree::fall(int n,char *m,bool *val){	// calculate the value
		int i;
		if(!con(name)){
			if(name=='1')
				return 1;
			i=0;
			while(i<n && (m[i++]!=name));
			return 	val[i-1];
		}
		else{
			if(name=='^')
				return lc->fall(n,m,val)^rc->fall(n,m,val);
			else if(name=='&')
				return lc->fall(n,m,val)&rc->fall(n,m,val);
			else
				return lc->fall(n,m,val)|rc->fall(n,m,val);
		}
	}

class Esp{     // Expression calculate  class
public:
	Esp(char *s);
	void cal(bool all=0);
	void change(char *s);
private:
	char esp[MAX];
};

Esp::Esp(char *s){
	strcpy(esp,s);
}

void Esp::change(char *s){
	strcpy(esp,s);
}

void Esp::cal(bool all){   // calculate
	if(esp[0]==' ')
		return;
	char tem[2*MAX];
	int l=strlen(esp),i,j;
	Stack<char> op;   // operator stack
	//  turn into suffixal expression
	for(i=0,j=0;i<l;i++){
		if(' '==esp[i]) // neglect the space
			continue;
		else if('('==esp[i]||')'==esp[i]){  // the brackets
			if('('==esp[i])
				op.push('(');
			else{
				while(op.getop()!='(')
					op.pop(tem[j++]);
				char suck;
				op.pop(suck);  // suck the '('
			}
		}
		else{
			if(esp[i]!='&'&&esp[i]!='|'&&esp[i]!='~'&&esp[i]!='^')
				tem[j++]=esp[i];
			else{
				while(op.getop()!='('&&!op.emp()&&(con(esp[i])<=con(op.getop())))
					op.pop(tem[j++]);
				op.push(esp[i]);
			}
		}
	}
	while(!op.emp())
		op.pop(tem[j++]);
	tem[j]='\0';
	//get the virable list
	l=strlen(tem);
	char *m=new char[l];
	for(i=0,j=0;i<l;i++){
		if(!con(tem[i])){
			int k;
			for(k=0;k<j;k++)
				if(m[k]==tem[i])
					break;
			if(k==j)
				m[j++]=tem[i];
		}
	}
	m[j]='\0';
	int num=j;
	// construct  the binary tree
	Stack <tree *> ck;
	for(i=0;i<l;i++){
		if(!con(tem[i])){
			tree *p=new tree(tem[i]);
			ck.push(p);
		}
		else if(tem[i]=='~'){
			tree *a=new tree('1'),*p,*r;
				ck.pop(p);
				r=new tree('^',a,p);
				ck.push(r);
			}
			else{
				tree *a,*b,*r;
				ck.pop(a);
				ck.pop(b);
				r=new tree(tem[i],b,a);
				ck.push(r);
			}
	}
	tree *p;
	ck.pop(p);
	int mar=1;
	bool *f_val=new bool[num],tem_f(0);
	memset(f_val,0,sizeof(f_val));
	mar<<=num;
	if(all)
		cout<<m<<endl;
 	for(i=0;i<mar;i++){		// 0 ~ 2^num-1

		if(all)
			for(j=0;j<num;j++)
				cout<<f_val[j];
		bool res=p->fall(num,m,f_val);
		if(all)
			cout<<" --- "<<res<<endl;
		if(!i)
			tem_f=res;
		else if(!all&&tem_f!=res)	// just test
			break;
		gray(num,f_val);
	}
	if(!all&&i==mar){	//test  if forever
		if(tem_f)
			cout<<"True forever"<<endl;
		else
			cout<<"False forever"<<endl;
	}
	else if(!all){
		char ch;
		cout<<"Satisfactible"<<endl;
		cout<<"Set the value?  <y/n> "<<endl;
		cin>>ch;
		while(ch=='Y'||ch=='y'){    // set value by client
			string vv;
			cout<<"input the value in order: \n"<<m<<endl;
			cin>>vv;
			for(i=0;i<num;i++)
			f_val[i]=vv[i]-'0';
			cout<<"the result: "<<p->fall(num,m,f_val)<<endl;
			cout<<"once again? <y/n>"<<endl;
			cin>>ch;
		}
	}
}
int main(){
	char s[MAX];
	while(1){
		cout<<"Input the expression "<<endl;
		cin.sync();		// clear the cache
		cin.getline(s,MAX);
		Esp exp(s);  // update the Esp
		exp.cal(1);		 // output  <0> test  <1> check all
		exp.cal(0)
	}
	return 0;
}

