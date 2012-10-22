#include<iostream>
#include<time.h>
#define MAX 1000
#define _cmp_  >
using namespace std;

class heap{
public:
	heap(int l=MAX);
	void init();
	void ins(int e);
	bool del(int &e);
	int *h,n,cmp,mov;
};
heap::heap(int l){
	h=new int[l];
}
void heap::init(){
	n=0,cmp=0,mov=0;
}
void heap::ins(int e){
	int p;
	for (p=++n;p>1&& e _cmp_ h[p>>1];h[p]=h[p>>1],p>>=1,cmp++,mov++);
	h[p]=e;
	mov++;
}
bool heap::del(int &e){
	if (!n) return 0;
	int p,c;
	for (e=h[p=1],c=2;c<n&& h[c+=(c<n-1&& h[c+1] _cmp_ h[c])] _cmp_ h[n];h[p]=h[c],p=c,c<<=1,cmp+=2,mov++);
	h[p]=h[n--];
	mov++;
	return 1;
}

int main(){
	int t=200;
	heap he(t+1);
	he.init();
	srand((unsigned)time(NULL));
	for(int i=0;i<t;i++)
		he.ins(rand()%t+1);
	for(int i=1;i<=t;i++){
		cout<<he.h[i]<<" ";
		if(!(i&15))	cout<<endl;
	}
	for(int i=0;i<t;i++){
		he.del(he.h[0]);
		he.h[he.n+1]=he.h[0];
	}
	cout<<"\n\ntotal_cmp: "<<he.cmp<<"  total_mov: "<<he.mov<<endl<<endl;
	for(int i=1;i<=t;i++){
		cout<<he.h[i]<<" ";
		if(!(i&15))	cout<<endl;
		}
	cout<<endl;
	system("pause");
	return 0;
}
