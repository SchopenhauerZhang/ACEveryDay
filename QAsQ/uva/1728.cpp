#include<bits/stdc++.h>
using namespace std;

const int maxn = 11234,INF = 0x3f3f3f3f;
#define LL long long 

#define root 1,1,n
#define Now int o,int l,int r
#define lson o<<1,l,m
#define rson o<<1|1,m+1,r
#define Mid int m = (l + r)>>1

int ma[maxn*4],mi[maxn*4],lazy[maxn*4];
int arr[maxn];

void seter(int o,int v){
    lazy[o] = min(lazy[o],v);
    mi[o] = min(mi[o],v);
}

void push_down(Now){
    if(l != r){
        seter(o<<1,lazy[o]);
        seter(o<<1|1,lazy[o]);
    }
    lazy[o] = INF;
}

int query(Now,int pos){
    if(l == r){
        return mi[o];
    }
    if(lazy[o] != INF) push_down(o,l,r);
    Mid;
    if(pos <= m) 
        return query(lson,pos);
    else 
        return query(rson,pos);
}

int handle(Now,int ul,int ur,int v){
    if(ul <= l && r <= ur){
        seter(o,v);
        return ma[o];
    }
    if(lazy[o] != INF) push_down(o,l,r);
    int ret = 0;
    Mid;
    if(ul <= m) ret = max(ret,handle(lson,ul,ur,v)); 
    if(m+1<=ur) ret = max(ret,handle(rson,ul,ur,v)); 
    return ret;
} 

void segInit(Now){
    lazy[o] = mi[o] = INF;
    if(l == r){
        ma[o] = arr[l];
        return;
    }
    Mid;
    segInit(lson),segInit(rson);
    ma[o] = max(ma[o<<1],ma[o<<1|1]);
}

vector<int> edge[maxn];
int fa[maxn],son[maxn],siz[maxn];
int deep[maxn],top[maxn],tid[maxn];
int _cnt;

void dffs(int st,int Fa,int Deep){
    siz[st] = 1,deep[st] = Deep;
    fa[st] = Fa,son[st] = -1;
    for(auto x : edge[st]){
        if(x == Fa) continue;
        dffs(x,st,Deep+1);
        siz[st] += siz[x];
        if(son[st] == -1 || siz[son[st]] < siz[x])
            son[st] = x;
    }
}

void dfss(int st,int Top){
    top[st] = Top,tid[st] = _cnt++;
    if(son[st] != -1) dfss(son[st],Top);
    for(auto x : edge[st]){
        if(son[st] != x &&  fa[st] != x) 
            dfss(x,x);
    }
}

void splite(){
    _cnt = 1;
    dffs(1,-1,1);
    dfss(1,1);
}

int n;
int handle(int x,int y,int v){
    int ix,iy;
    ix = iy = 0;
    int tx = top[x],ty = top[y];
    while(tx != ty){
        if(deep[tx] < deep[ty])
            swap(tx,ty),swap(x,y),swap(ix,iy);
        ix = max(handle(root,tid[tx],tid[x],v),ix);
        x = fa[tx],tx = top[x];
    }
    if(deep[x] < deep[y])
        swap(x,y);
    return max(max(ix,iy),handle(root,tid[y]+1,tid[x],v));
}

int x[maxn],y[maxn],v[maxn];

int main(){
    int T,m;
    scanf("%d",&T);
    int icase = 1;
    while(T-- && ~scanf("%d %d",&n,&m)){
        LL ans = 0;
        for(int i=1;i<=n;i++) edge[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d %d %d",&x[i],&y[i],&v[i]);
            edge[x[i]].push_back(y[i]);
            edge[y[i]].push_back(x[i]);
        }
        splite();
        for(int i=1;i<n;i++){
            if(deep[x[i]] < deep[y[i]]) swap(x[i],y[i]);
            arr[tid[x[i]]] = v[i];
        }
        segInit(root);
        int l,r,w;
        for(int i=n;i<=m;i++){
            scanf("%d %d %d",&l,&r,&w);
            int ops =  w - handle(l,r,w);
            ans -= 1ll * i;
            ans += 1ll * i * i * ops;
        }
        for(int i=1;i<n;i++){
            int temp = query(root,tid[x[i]]);
            if(temp == INF) temp = -1;
            else temp = temp - v[i];
            ans += 1ll * i * temp;
            ans -= 1ll * i * i;
        }
        printf("Case %d: %lld\n",icase++,ans); 
    }
    return 0;
}
