#include<bits/stdc++.h>
using namespace std;

const int maxn=60005;
const int maxm=400000;
const int INF=0x3f3f3f3f;
int n,m;
int st,en;

struct Edge{
    int next;
    int to;
    int val;
} e[maxm*2];
int head[maxn];
int cur[maxn];
int dis[maxn];
int tot;



int dfs(int u,int flow) {
    if (u==en) {return flow;}
    for (int &i=cur[u];i!=-1;i=e[i].next){
        if ((dis[e[i].to] == dis[u]+1) && (e[i].val!=0)) {
            int di=dfs(e[i].to, min(flow, e[i].val));
            if (di>0) {
                e[i].val-=di;
                e[i^1].val+=di;
                return di;
            }
        }
    }
    return 0;
}


int bfs() {
    queue<int> Q;
    while (!Q.empty()) {Q.pop();}
    memset(dis,0,sizeof(dis));
    dis[st]=1;
    Q.push(st);
    do {
        int u=Q.front();
        Q.pop();
        for (int i=head[u];i!=-1;i=e[i].next) {
            if ((dis[e[i].to]==0) && (e[i].val>0)) {
                dis[e[i].to] = dis[u] +1;
                Q.push(e[i].to);
            }
        }
    } while (!Q.empty());
    if (dis[en]>0) {
        return 1;
    }
    return 0;
}

int Dinic(){
    int ans=0;
    while (bfs()) {
        for (int i=0;i<=n+m+2;i++) {
            cur[i]=head[i];
        }
        while (int d=dfs(st, INF)) {
            ans+=d;
        }
    }
    return ans;
}


inline void addedge(int x,int y,int c) {
    e[tot].next=head[x];
    head[x]=tot;
    e[tot].val=c;
    e[tot].to=y;
    tot++;
    e[tot].next=head[y];
    head[y]=tot;
    e[tot].to=x;
    e[tot].val=0;
    tot++;
    return ;
}


inline void init() {
    tot=0;
    for (int i=1;i<=n;i++) {
        head[i]=-1;
    }
}
