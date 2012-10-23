#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAXN 1000


int a[MAXN],c[MAXN],n;

int lowbit(int p){
    return p&(p^(p-1));
}

void modify(int p,int delta){
    while(p<=n){
        c[p]+=delta;
        p+=lowbit(p);
    }
}

int getsum(int p){
    int res=0;
    while(p){
        res+=c[p];
        p-=lowbit(p);
    }
    return res;
}

void init(){
    for(int i=1;i<=n;i++)
        modify(i,a[i]);
}


int main(){
    ifstream fin("in");
    ofstream fout("out");

    fin>>n;
    for(int i=1;i<=n;i++)
        fin>>a[i];

    init();

    modify(1,1);
    for(int i=1;i<=n;i++)
        fout<<c[i]<<" ";
    fout<<endl;

    for(int i=1;i<=n;i++)
        fout<<getsum(i)<<" ";
    fout<<endl;


    return 0;
}

//two dimension
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAXN 1000


int a[MAXN][MAXN],c[MAXN][MAXN],n,m;

int lowbit(int p){
    return p&(p^(p-1));
}

void modify(int x,int y,int delta){
    int t;
    while(x<=m){
        t=y;
        while(t<=n){
            c[x][t]+=delta;
            t+=lowbit(t);
        }
        x+=lowbit(x);
    }
}

int getsum(int x,int y){
    int res=0,t;
    while(x){
        t=y;
        while(t){
            res+=c[x][t];
            t-=lowbit(t);
        }
        x-=lowbit(x);
    }
    return res;
}

void init(){
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            modify(i,j,a[i][j]);
}


int main(){
    ifstream fin("in");
    ofstream fout("out");

    fin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            fin>>a[i][j];

    init();

    //modify(1,1);
    /*for(int i=1;i<=n;i++)
      fout<<c[i]<<" ";
      fout<<endl;*/

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            fout<<getsum(i,j)<<" ";
        fout<<endl;
    }


    return 0;
}

