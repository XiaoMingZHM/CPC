#include<cstdio>
using namespace std;

double l,r;
double L,R;

int main() {
	scanf("%lf%lf", &l,&r);
	scanf("%lf%lf", &L,&R);
	double x=(L+R)/2;
	double y=(x+l)/2;
	double ans=0;
	if (x<=l) {
		ans=0;
	} else if (y<r) {
		ans=(x/2-l/2)*(x/2-l/2)/(r-l);
	} else {
		ans=(x-r);
	}
	printf("%.4f\n",ans);
	return 0;
}
