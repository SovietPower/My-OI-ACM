//#include <ctime>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
#define Vec std::vector<int>
#define Vec_pr std::vector<pr>
typedef long long LL;
const int N=1e5+7,Max=1e5;

int cnt[N],sum[N];
std::vector<int> fac[N-3];
//std::vector<pr> v[N-3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Calc(int n)
{
	for(int i=1,m=sqrt(n); i<=m; ++i)
		if(!(n%i))
		{
			++cnt[n], fac[n].push_back(i);
			if(i*i!=n) ++cnt[n], fac[n].push_back(n/i);
		}
	std::sort(fac[n].begin(),fac[n].end());
}
void Pre()
{
	for(int i=1; i<=Max; ++i) Calc(i);
//	int mx=1;
//	for(int i=1; i<=Max; ++i) if(cnt[i]>cnt[mx]) mx=i;
//	std::sort(cnt+1,cnt+1+Max);
//	for(int i=N; i>=Max-200; --i) printf("%d:%d\n",i,cnt[i]);
//	printf("%d %d\n",mx,cnt[mx]);
}
void Get(int x,int y)
{
	const Vec &vx=fac[x], &vy=fac[y];
	for(int i=0,lim=cnt[x]; i<lim; ++i)
	{
		int l=0,r=cnt[y]-1,mid,val=vx[i];
		while(l<r)
		{
			if(vy[mid=l+r>>1]<val) l=mid+1;
			else r=mid;
		}
		sum[i]=cnt[y]-l;
//		printf("Get:x:%d i:%d fac:%d sum:%d\n",x,i,fac[x][i],sum[i]);
	}
	for(int i=cnt[x]-2; ~i; --i) sum[i]+=sum[i+1];
}
void Calc(int x,int y)
{
	long long ans=0;
	const Vec &vx=fac[x], &vy=fac[y];
	for(int i=0,lim=cnt[x]; i<lim; ++i)
	{
		int l=0,r=cnt[y]-1,mid,val=vx[i];
		while(l<r)
		{
			if(vy[mid=l+r>>1]<val) l=mid+1;
			else r=mid;
		}
//		printf("Calc:x:%d i:%d fac:%d l:%d sum:%d\n",x,i,fac[x][i],l,sum[l]);
		ans+=sum[l];
	}
	printf("%I64d\n",ans);
}

int main()
{
	freopen("1.in","r",stdin);
//	freopen("my.out","w",stdout);

//	int Time=clock();
	Pre();// printf("One:%d\n\n",clock()-Time);
	int T=read(),A,B,C,a[5];
	while(T--)
	{
//		A=read(), B=read(), C=read();
		a[1]=read(), a[2]=read(), a[3]=read();
		std::sort(a+1,a+4), A=a[1], B=a[2], C=a[3];
		Get(B,C), Calc(A,B);
//		printf("%I64d\n",1ll*cnt[A]*cnt[B]*cnt[C]);
	}
//	printf("\nEnd:%d\n",clock()-Time);

	return 0;
}
