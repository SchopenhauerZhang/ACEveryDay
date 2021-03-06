/* ***********************************************
Author        :guanjun
Created Time  :2016/6/28 14:50:20
File Name     :1023.cpp
************************************************ */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <list>
#include <deque>
#include <stack>
#define ull unsigned long long
#define ll long long
#define mod 90001
#define INF 0x3f3f3f3f
#define maxn 10010
#define cle(a) memset(a,0,sizeof(a))
const ull inf = 1LL << 61;
const double eps=1e-5;
using namespace std;
priority_queue<int,vector<int>,greater<int> >pq;
struct Node{
	int x,y;
};
struct cmp{
    bool operator()(Node a,Node b){
        if(a.x==b.x) return a.y> b.y;
        return a.x>b.x;
	}
};

bool cmp(int a,int b){
    return a>b;
}
char s[30];
int n,k,num,mark;
int vis[30];
void dfs(string s,int cnt){
	if(cnt==n){
		num++;
		cout<<s<<endl;
		if(num==k)mark=1;
		return ;
	}
	if(mark)return ;
	for(int i=0;i<n;i++){
		if(!vis[i]){
			vis[i]=1;
			dfs(s+char(i+'A'),cnt+1);
			vis[i]=0;
		}
	}
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    //freopen("out.txt","w",stdout);
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case %d:\n",t);
		cin>>n>>k;
		cle(vis);
		num=mark=0;
		dfs("",0);
	}
    return 0;
}
