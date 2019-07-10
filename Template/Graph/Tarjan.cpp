#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1000000;
const int maxm=1000000;

struct Edge{
    int u;
    int v;
    int next;
} edge[maxm];
int tot;
int head[maxn];
int dfn[maxn];
int low[maxn];
int vis[maxn];
int col[maxn]; //强连通分量染色块
int stack[maxn];
int top;
int clk;
int coln; //强连通分量个数

inline void init(int n) {
    for (int i=1;i<=n;i++) {
        low[i]=0;
        dfn[i]=0;
        vis[i]=false;
        head[i]=0;
    }
    top=0;
    tot=0;
    clk=0;
    coln=0;
}

inline void addedge(int x,int y) {
    edge[++tot].next=head[x];
    edge[tot].u=x;
    edge[tot].v=y;
    head[x]=tot;
}

void tarjan(int x) {
    clk++;
    dfn[x]=clk;
    low[x]=clk;
    top++;
    stack[top]=x;
    vis[x]=true;
    for (int p=head[x]; p!=0; p=edge[p].next) {
        int u=x;
        int v=edge[p].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if (vis[v]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[x]==low[x]) {
        coln++;
        do {
            vis[stack[top]]=false;
            col[stack[top]]=coln;
            top--;
        }while (stack[top+1]!=x);
    }
}
