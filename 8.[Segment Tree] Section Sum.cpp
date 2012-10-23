#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAXN 1000

//segment tree for array sum
int tree[MAXN],n;

void insert(int p,int delta){
    while(p){
        tree[p]+=delta;
        p>>=1;
    }
}

int count(int p,int l,int r,int a,int b){
    if(l==a && r==b)    
        return tree[p];
    int m=(l+r)/2;
    if(b<=m)
        return count(2*p,l,m,a,b);
    if(a>=m+1)
        return count(2*p+1,m+1,r,a,b);
    return count(2*p,l,m,a,m)+count(2*p+1,m+1,r,m+1,b);
}

int upperBound(int p){
    int t=1;
    while(p>t)
        t<<=1;
    return t;
}

int main(){
    ifstream fin("in");
    ofstream fout("out");

    fin>>n;
    int tmp,up=upperBound(n);
    for(int i=1;i<=n;i++){
        fin>>tmp;
        insert(up-1+i,tmp);
    }
    for(int i=1;i<up+n;i++)
        cout<<tree[i]<<" ";
    cout<<endl;

    while(1){
        int i,j;
        cin>>i>>j;
        cout<<count(1,1,up,i,j)<<endl;
    }

    return 0;
}



