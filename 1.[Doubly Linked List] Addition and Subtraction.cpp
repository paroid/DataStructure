#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
#define MAX 500   // the max length of the input string

// By ChKo  软信0801 陈科  20083563

class node{			// class node
public:
	node(int num=0);
	bool ins(node *after);    //insert after *after
	int data;
	node *pre,*next;	 	  // pointer	
};

node::node(int num){		
	data=num;	
}
bool node::ins(node *af){		//insert
	next=af->next;
	pre=af;
	af->next->pre=this;
	af->next=this;
	return 1;	
}

class list{				// class list
public:
	list();
	bool read();		//get data to construct list
	friend list operator+(const list &a,const list &b);  // overdrive the operator +
	void show();		// show the data 
	node *head;			// the head
	bool flag;			// negative 1  positive 0
	int len;			// the number of nodes
};
list::list(){			//constructor
	head=new node(0);	// put 0 to the head
	head->pre=head;		// circle
	head->next=head;
	len=0;
	flag=0;	
}
bool list::read(){	// get the data
	char s[MAX];	// get by string 
	cin>>s;
	int f=0,i,l=strlen(s),tem=0;
	if(s[0]=='-'){		// get the flag
		flag=1;
		f++;	
	}	
	i=l-1;
	l=1;
	while(i>=f){		// convert
		tem=tem*10+s[i]-48;
		if(!(l++%4)){
			tem=(tem%10)*1000+((tem%100)/10)*100+((tem%1000)/100)*10+tem/1000; //reverse
			node *p=new node(tem);
			p->ins(head->pre);			
			len++;
			i--;
			tem=0;
			l=1;
		}	
		i--;
	}
	if(tem){	// store the remain
		i=1;
		int mt=0;
		while(i++<l){
			mt=mt*10+tem%10;
			tem/=10;	
		}
		node *p=new node(mt);
		p->ins(head->pre);
		len++;
	}
	
}
void list::show(){
	int i=0;
	bool conti=0;
	if(flag)
		cout<<"-";
	node *p=head->pre;
	if(p==head->next){  // only 1 node
		cout<<p->data<<endl;
		p=p->pre;
		i++;
	}
	else{
		bool ty=0;
		
		while(p!=head->next){
			if(p->data)
				conti=1;
			if(!conti){
				p=p->pre;
				continue;
			}				
			if(ty)
				cout<<setfill('0')<<setw(4)<<p->data;
			else{
				cout<<p->data;   // first node no need of setfill
				ty=1;	
			}
			cout<<",";
			p=p->pre;
			i++;
		}
		// the last one no of need ','
		cout<<setfill('0')<<setw(4)<<head->next->data<<endl;
	}
}
list operator+(const list &a,const list &b){
		list c;
		if(!a.flag^b.flag){    // same flag   add
			c.flag=a.flag;
			bool f=0;
			int t=a.len-b.len,tem,cf=0,i=t>0?b.len:((t=b.len-a.len),f=1,a.len);
			node *p1,*p2; 
			if(!f)
				p1=a.head->next,p2=b.head->next;
			else
				p1=b.head->next,p2=a.head->next;
			while(i--){        // add
				tem=cf+p1->data+p2->data;
				cf=tem/10000;
				node *p=new node(tem%10000);
				p->ins(c.head->pre);
				p1=p1->next;
				p2=p2->next;
			}
			while(t--){  // deal with the remain
				tem=cf+p1->data;
				cf=tem/10000;
				node *p=new node(tem%10000);
				p->ins(c.head->pre);
				p1=p1->next;	
			}		
			if(cf){		// if  add 1 more
				node *p=new node(1);
				p->ins(c.head->pre);	
			}
		}
		else{  // not bad ! I need to compare first
			bool who;
			if(a.len!=b.len)
				who=a.len>b.len?0:1;
			else{ // damn sure
					node *p1=a.head->pre,*p2=b.head->pre;
					int i=a.len;
					while(i--){
						if(p1->data!=p2->data)
							break;
						p1=p1->pre;
						p2=p2->pre;
					}
					if(p1==a.head&&p2==b.head){ // zero
						node *p=new node(0);
						p->ins(c.head->pre);
						return c;
					}
					who=(p1->data>p2->data)?0:1;  // mark the big one
				}
					// sub
			int tem,cf=0,t=a.len-b.len,i=t>0?b.len:((t=b.len-a.len),a.len);
			node *p1,*p2;
			if(!who)   // let the big one be the p1
				p1=a.head->next,p2=b.head->next;
			else
				p1=b.head->next,p2=a.head->next;			
			while(i--){
				tem=cf+p1->data-p2->data;	//sub
				cf=tem<0?(tem+=10000,-1):0; // set cf
				node *p=new node(tem);
				p->ins(c.head->pre);
				p1=p1->next;
				p2=p2->next;
			}
			while(t--){		// deal with the remain
				tem=cf+p1->data;
				cf=tem<0?(tem+=10000,-1):0;
				node *p=new node(tem%10000);
				p->ins(c.head->pre);
				p1=p1->next;	
			}
			c.flag=a.flag^who?1:0; // set the flag
		}
		return c;
}
int main(){
	list a,b;
	a.read();
	b.read();
	list c(a+b);
	cout<<"\nSum = ";
	c.show();
	cout<<endl;
	system("pause");
	return 0;
}
