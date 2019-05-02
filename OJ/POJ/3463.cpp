#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1E6;
const long long INF=1E18;

struct Edge{
	int to;
	int next;
	long long w;
} a[maxn];

struct Node{
	int index;
	long long weight;
	Node(){}
	Node (int x,long long y) {
		this->index=x;
		this->weight=y;
	}
	bool operator < (const Node x) const {
		return weight>x.weight;
	}
};

long long weight[maxn];
int head[maxn];
long long f[maxn];
int vis[maxn];
int tot;
int n,m;

inline void init() {
	for (int i=1;i<=n;i++) {
		vis[i]=0;
		f[i]=INF;
		head[i]=0;
	}
	tot=0;
}

inline void addedge(int x,int y,long long w) {
	tot++;
	a[tot].next=head[x];
	a[tot].to=y;
	a[tot].w=w;
	head[x]=tot;
}

priority_queue<Node> q;

void Dijkstra(int S) {
	while (!q.empty()) {q.pop();}
	Node node = Node(S,0);
	q.push(node);
	f[S]=0;
	while (!q.empty()) {
		node=q.top();
		q.pop();
		int u=node.index;
		if (vis[u]==true) {
			continue;
		}
		vis[u]=true;
		
		for (int p=head[u];p!=0;p=a[p].next) {
			int v=a[p].to;
			if ((f[u]+a[p].w)<f[v]) {
				f[v]=f[u]+a[p].w;
				node=Node(v,f[v]);
				q.push(node);
			}
		}
	}
}


int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n,&m);
		init();
		for (int i=1;i<=n;i++) {
			scanf("%lld", &weight[i]);
		}
		for (int i=1;i<=m;i++) {
			int x,y;
			long long z;
			scanf("%d%d%lld", &x,&y,&z);
			addedge(x,y,z);
			addedge(y,x,z);
		}
		Dijkstra(1);
		long long ans=0;
		for (int i=2;i<=n;i++) {
			if (f[i]!=INF) {
				ans+=f[i]*weight[i];
			} else {
				ans=-1;
				break;
			}
		}
		if (ans>=0) {
			printf("%lld\n", ans);
		} else {
			printf("No Answer\n");
		}
	}
} 
