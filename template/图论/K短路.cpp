#include<cstdio>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 10000;
const int maxm = 1000000;
const int INF = 1E9+9;

struct Edge{
	int u,v;
	int w;
	int next;
} edge[maxm],revedge[maxm];
int head[maxn],revhead[maxn];
int tot;
int vis[maxn];

struct ANode{
	int v;
	int f,g;
	bool operator < (const ANode &a) const {
		if (f==a.f) {return g>a.g;} 
		else {return f>a.f;}
	}
};

struct Node{
	int index;
	int dis;
	bool operator < (const Node &a) const {
		return dis>a.dis;
	}
} node[maxn];

inline void init(int n) {
	for (int i=1;i<=n;i++) {
		head[i]=0;
		revhead[i]=0;
		node[i].index=i;
		node[i].dis=INF;
		vis[i]=false;
	} tot=0;
} 

inline void addedge(int x,int y,int w) {
	tot++;
	edge[tot].next=head[x];
	edge[tot].u=x;
	edge[tot].v=y;
	edge[tot].w=w;
	head[x]=tot;
	revedge[tot].next=revhead[y];
	revedge[tot].u=y;
	revedge[tot].v=x;
	revedge[tot].w=w;
	revhead[y]=tot;
}

priority_queue<Node> q;
void dijkstra(int x, int n) {
    for (int i=1;i<=n;i++) {
        vis[i]=false;
        node[i].dis=INF;
    }
    while (!q.empty()) {
        q.pop();
    }
    node[x].dis=0;
    q.push(node[x]);
    while (!q.empty()) {
        Node top_node=q.top();
        int u=top_node.index;
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u]=true;
        for (int p=revhead[u];p!=0;p=revedge[p].next) {
            int v=revedge[p].v;
            if (node[v].dis>node[u].dis+revedge[p].w) {
                node[v].dis=node[u].dis+revedge[p].w;
                q.push(node[v]);
            }
        }
    }
}

int Astar(int src, int des, int k) {
	int cnt = 0;
	priority_queue<ANode> Q;
	if(src == des) k++;
	if(node[src].dis == INF) return -1;
	ANode t, tt;
	t.v = src;
	t.g = 0;
	t.f = t.g + node[src].dis;
	Q.push(t);
	while(!Q.empty()){
		tt = Q.top();
		Q.pop();
		if(tt.v == des) {
			cnt++;
			if(cnt == k) return tt.g;
		}
		for(int i = head[tt.v]; i != 0; i = edge[i].next){
			t.v = edge[i].v;
			t.g = tt.g + edge[i].w;
			t.f = t.g + node[t.v].dis;
			Q.push(t);
		}
	}
	return -1;
}

int main() {
	int n,m;
	while (~scanf("%d%d", &n,&m)) {
		init(n);
		for (int i=1;i<=m;i++) {
			int x,y,w;
			scanf("%d%d%d", &x,&y,&w);
			addedge(x,y,w);
		}
		int st,en,k;
		scanf("%d%d%d", &st,&en,&k);
		dijkstra(en,n);
		int ans=Astar(st,en,k);
		printf("%d\n", ans);
	}
	return 0;
}
