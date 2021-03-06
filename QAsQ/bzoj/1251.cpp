#include<bits/stdc++.h>
using namespace std;

struct Info{
    int ma;
    int size;
    Info(int m = 0){
        ma = m,size = 1;
    }
    void addIt(int x){
        ma += x;
    }
};

Info operator + (const Info & L,const Info & R){
    Info ret(max(L.ma,R.ma));
    ret.size = L.size + R.size;
    return ret;
}

const int maxn = 112345;

struct Node{
    int son[2],fa;
    int v,add;
    bool flp;
    Info info;
    int & l(){return son[0];}
    int & r(){return son[1];}
    void out(){
        printf("(lr=%d,%d v=%d siz=%d infov=%d add=%d flp=%d)",l(),r(),v,info.size,info.ma,add,flp);
    }
    Node(int val=0){
        l() = r() = fa = -1;
        v = val;
        info = Info(val);
        add = 0;
        flp = false;
    }
    void addIt(int val){
        v += val;
        add += val;
        info.addIt(val);
    }
    void maintain();
    void push_down();
}node[maxn];

void out(int st){
    printf("id = %d :",st);
    node[st].out();
    cerr<<"["<<endl;
    if(node[st].l()!=-1) out(node[st].l());
    if(node[st].r()!=-1) out(node[st].r());
    cerr<<"]"<<endl;
}
void Node::push_down(){
    if(add != 0){
        if(l()!=-1) node[l()].addIt(add); 
        if(r()!=-1) node[r()].addIt(add); 
        add = 0;
    }
    if(flp){
        swap(l(),r());
        if(l()!=-1) node[l()].flp ^= 1;
        if(r()!=-1) node[r()].flp ^= 1;
        flp = false;
    }
}

void Node::maintain(){
    info = Info(v);
    if(l()!=-1) info = node[l()].info + info;
    if(r()!=-1) info = info + node[r()].info;
   // out();
  //  cout<<endl;
}

int ori(int st){
    int fa = node[st].fa;
    if(fa==-1) return -1;
    return st == node[fa].r();
}

void setc(int st,int sn,int d){
    if(st != -1){
        node[st].son[d] = sn;
        node[st].maintain();
    }
    if(sn != -1) node[sn].fa = st;
}

void zg(int x){
    int st = node[x].fa,p = -1;

    node[st].push_down();
    node[x].push_down();

    int d = ori(x),dst = ori(st);
    if(st!=-1) p=node[st].fa;
    setc(st,node[x].son[d^1],d);
    setc(x,st,d^1);
    setc(p,x,dst);
}

int root;
#define f(x) (node[x].fa)
void splay(int x,int fa=-1){
    while(f(x) != fa){
        if(f(f(x)) == fa) zg(x);
        else{
           if(ori(x)==ori(f(x))) zg(f(x));
           else zg(x);
           zg(x);
        }
    }
    if(fa==-1)
         root = x;
}

int ider[maxn];

int pos;
int build(int l,int r){
    int st = pos++;
    int m = (l + r) >> 1;
    node[st] = Node(0);
    ider[m] = st;
    if(l<m) setc(st,build(l,m-1),0);
    if(m<r) setc(st,build(m+1,r),1);
    return st;
}

int build(int n){
    pos = 0;
    return build(0,n+1);
}

int getid(int v,int st){
    node[st].push_down();
    int l = node[st].l();
    int lsize = 1 + (l==-1?0:node[l].info.size);
    if(v == lsize) return st;
    int d = v > lsize;
    if(d) v -= lsize;
    return getid(v,node[st].son[d]);
}

int getseg(int l,int r){
    l--,r++;
    l = getid(l+1,root),r = getid(r+1,root);
    splay(r);
    splay(l,r);
    return node[l].r();
}

int main(){
    int T;
    int n,m;
    while(~scanf("%d %d",&n,&m)){
        root = build(n);
        int l,r,v;
        int ord;
        while(m--){
            scanf("%d %d %d",&ord,&l,&r);
            int pos = getseg(l,r); 
            if(ord == 1){
                scanf("%d",&v);
                node[pos].addIt(v);
            }
            else{
                if(ord == 2){
                    node[pos].flp ^= 1;
                }
                else{
                    printf("%d\n",node[pos].info.ma);
                }
            }
        }
    }
    return 0;
}
