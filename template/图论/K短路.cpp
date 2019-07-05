#include<cstdio>
#include<cstring>
using namespace std;
const long long mod=998244353;
const int maxn=1E6+10;
long long a[maxn][2];
long long cnt[2];
long long f[maxn][2];
long long g[maxn][2];
long long n,K;

long long getAns(int w) {
	int pre=-1;
	int len=0;
	long long ans=1;
	for (int i=1;i<=cnt[w];i++) {
		if (a[i][w]==-1) {
			len++;
		} else {
			if (pre==-1) {
				ans=ans*g[len][1]%mod;
			} else {
				if (pre==a[i][w]) {
					ans=ans*f[len][1]%mod;
				} else {
					ans=ans*f[len][0]%mod;
				}
			}
			pre=a[i][w];
			len=0;
		}
	}
	if (pre==-1) {
		ans=ans*g[len][0]%mod;
	} else {
		ans=ans*g[len][1]%mod;
	}
	return ans;
}

int main() {
	scanf("%I64d%I64d", &n,&K);
	cnt[0]=cnt[1]=0;
	for (int i=1;i<=n;i++) {
		long long x;
		scanf("%I64d", &x);
		a[++cnt[i&1]][i&1]=x;
	}
	memset(f,0,sizeof(f));
	f[0][0]=1;
	f[0][1]=0;
	f[1][0]=K-2;
	f[1][1]=K-1;
	for (int i=2;i<=n;i++) {
		f[i][0]=(f[i-1][1]+(K-2)*f[i-1][0]%mod)%mod;
		f[i][1]=(K-1)*f[i-1][0]%mod;
	}
	g[0][0]=1;
	g[0][1]=1;
	g[1][0]=K;
	g[1][1]=K-1;
	for (int i=2;i<=n;i++) {
		g[i][0]=g[i-1][0]*(K-1)%mod;
		g[i][1]=g[i-1][1]*(K-1)%mod;
	}
	
	long long ans = getAns(0)*getAns(1)%mod;
	printf("%I64d\n", ans);
	return 0;
}

/*
20 5
-1 1 -1 2 -1 3 -1 4 -1 5 -1 1 -1 2 -1 3 -1 4 -1 5

*/
