#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+5;

pr Ans[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
//	static int P1[N],P2[N];
//	int n=read(),cnt1=0,cnt2=0;
//	for(int i=2; 1ll*i*i<=n; ++i)
//		if(!(n%i)) P1[++cnt1]=i;
//	if(!cnt1) return puts("NO"),0;
//	for(int i=2; 1ll*i*i<=n-1; ++i)
//		if(!((n-1)%i)) P2[++cnt2]=i;
//	if(!cnt2) return puts("NO"),0;

	static int fac[N];
	int n=read(),cnt=0;
	for(int i=2; 1ll*i*i<=n; ++i)
		if(!(n%i)) fac[++cnt]=i, fac[++cnt]=n/i;
	if(!cnt) return puts("NO"),0;

//	printf("cnt:%d\n",cnt);
	std::sort(fac+1,fac+1+cnt);
	int x=n-1,tot=0;
	for(int i=cnt; i; --i)
	{
		if(x<fac[i]) continue;
		int p=x/fac[i],b=n/fac[i];
		int t=0;
		while()
		if(x-p*fac[i]<fac[1]) continue;
		x-=p*fac[i];
		printf("fac:%d x:%d p:%d b:%d\n",fac[i],x,p,b);
		while(p>=b) Ans[++tot]=mp(b-1,b), p-=b-1;
		if(p) Ans[++tot]=mp(p,b);
	}
	if(x) puts("NO");
	else
	{
		puts("YES"); printf("%d\n",tot);
		for(int i=1; i<=tot; ++i) printf("%d %d\n",Ans[i].first,Ans[i].second);
	}

	return 0;
}
