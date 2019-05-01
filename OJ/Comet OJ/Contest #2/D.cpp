#include <cstdio>
using namespace std;
const long long mod=998244353;
const int maxn=4005;
struct node{
    int from;
    int to;
    int next;
} a[maxn<<1];
int head[maxn];
long long ans[maxn];
long long pow[maxn];
long long cnt[maxn][maxn];
long long ava[maxn];
int tot;
int n;

inline void init() {
    for (int i=1;i<=2*n;i++) {
        head[i]=0;
        ans[i]=0;
    } tot=0;
    pow[0]=1;
    for (int i=1;i<=2*n;i++) {
        pow[i]=pow[i-1]*2%mod;
    }
}

inline void addedge(int x,int y) {
    tot++;
    a[tot].from=x;
    a[tot].to=y;
    a[tot].next=head[x];
    head[x]=tot;
}

void dfs(int x,int fa, int dep, int dye ) {
    if (x<=n) {
        ava[dep]++;
        cnt[dye][dep]++;
    }
    for (int p=head[x];p!=0;p=a[p].next) {
        int y=a[p].to;
        if (y==fa) {
            continue;
        }
        dfs(y,x,dep+1,dye);
    }
}
int main() {
    scanf("%d", &n);
    init();
    for (int i=1;i<n;i++) {
        int x,y;
        scanf("%d%d", &x,&y);
        addedge(x,n+i);
        addedge(n+i,y);
        addedge(y,n+i);
        addedge(n+i,x); //解决在半径为奇数时的判重问题，将一个边拆成两个。
    }
    for (int i=1;i<=2*n-1;i++) {
        for (int j=0;j<=2*n-1;j++) {
            ava[j]=0;
        }
        int dye=0;
        long long sum=0;
        if (i<=n) { //判定中点是否在树上
            ava[0]++;
            sum=1;
        }
        for (int j=head[i];j!=0;j=a[j].next) {
            dye++;
            for (int k=1;k<=2*n-1;k++) {
                cnt[dye][k]=0;
            }
            dfs(a[j].to,a[j].from,1,dye);
        }
        for (int j=1;j<n;j++) {
            long long tmp = pow[ava[j]]-1;
            for (int k=1;k<=dye;k++) {
                tmp= (tmp-(pow[cnt[k][j]]-1)+mod)%mod; //删去只选择了一个分支的情况
            }
            ans[j]=(ans[j]+(tmp*pow[sum]%mod))%mod;
            sum+=ava[j];
        }
    }
    for (int i=1;i<n;i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
