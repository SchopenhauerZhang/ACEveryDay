#include<bits/stdc++.h>
using namespace std;

const int maxn = 212345;

struct Node{
    int fa,son[2];
    int siz;
    void init(){
        fa = son[0] = son[1] = 0;
        siz = 1;
    }
    void maintain();
}node[maxn];

void Node::maintain(){
    siz = 1 + node[son[0]].siz + node[son[1]].siz;
}

int ori(int st){ 
    if(node[st].fa < 0) return 0;
    return st == node[node[st].fa].son[1]; 
}

void setc(int st,int sn,int d){
    if(st > 0) node[st].son[d] = sn; 
    if(sn > 0) node[sn].fa     = st;
    if(st > 0) node[st].maintain();
}

void zg(int x){ 
    int st = node[x].fa;
    int p = node[st].fa;
    int d = ori(x) , dst=ori(st);

    setc(st,node[x].son[d^1],d);
    setc(x,st,d^1);
    setc(p,x,dst);
}

void splay(int x){
    #define f(x) (node[x].fa)
    while(f(x) > 0) {
        if(f(f(x)) <= 0) zg(x);
        else{ 
            if(ori(x) == ori(f(x))) 
                zg(f(x));
            else 
                zg(x);
            zg(x);
        }
    }
}

void access(int x){
    splay(x);
    while(node[x].fa < 0){
        int fa = -node[x].fa;
        splay(fa);
        node[node[fa].son[1]].fa *= -1;
        setc(fa,x,1);
        splay(x);
    }
}

int fndroot(int x){
    access(x);
    while(node[x].son[0]) 
        x = node[x].son[0];
    splay(x);
    return x;
}

void link(int st,int x){
    access(x);
    node[x].fa = -st;
    access(x);
}
void cut(int x){
    access(x);
    node[node[x].son[0]].fa = 0;
    node[x].son[0] = 0;
}

int main(){
    int n,m;
    scanf("%d",&n);
    for(int i = 0 ; i <= n ; i++) 
        node[i].init(); 
    node[0].siz = 0;

    int x;
    for(int i = 1 ; i <= n; i ++){
        scanf("%d",&x);
        if(i + x <= n) 
            link(i+x,i);
    }
    scanf("%d",&m);
    int ord,v;
    while(m--){
        scanf("%d %d",&ord,&x);
        x++;
        if(ord == 1){
            access(x);
            printf("%d\n",node[node[x].son[0]].siz + 1);
        }
        else{
            scanf("%d",&v);
            cut(x);
            if(x + v <= n)
                link(x+v,x);
        }
    }
    return 0;
}
