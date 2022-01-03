/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=1e5+5,M=1e4+5;

struct Node
{
	int x,y,valx,valy;
}A[N];
int B[N];
std::vector<int> vx[N],vy[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool cmpx(int a,int b)
{
	return A[a].x<A[b].x;
}
bool cmpy(int a,int b)
{
	return A[a].y<A[b].y;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i)	A[i]=(Node){read()+M,read()+M,0,0};
	for(int i=1; i<=n; ++i) vx[A[i].x].push_back(i), vy[A[i].y].push_back(i);

	for(int i=5; i<=20005; ++i)
		if(vx[i].size()>1)
		{
			int t=0;
			for(auto j:vx[i]) B[++t]=j;
			std::sort(B+1,B+1+t,cmpy);

			LL sum=0; int y0=A[B[1]].y;
			for(int j=1; j<=t; ++j) sum+=std::abs(A[B[j]].y-y0);
			sum%=mod;
			int cnt1=0,cnt2=t,las=y0; LL now=0;
			for(int j=1; j<=t; ++j)
			{
				sum=sum+1ll*(cnt1-cnt2)*(A[B[j]].y-las)%mod, sum=(sum%mod+mod)%mod;
				las=A[B[j]].y, --cnt2, ++cnt1;
				A[B[j]].valx=sum;
			}
		}
	for(int i=5; i<=20005; ++i)
		if(vy[i].size()>1)
		{
			int t=0;
			for(auto j:vy[i]) B[++t]=j;
			std::sort(B+1,B+1+t,cmpx);

			LL sum=0; int x0=A[B[1]].x;
			for(int j=1; j<=t; ++j) sum+=std::abs(A[B[j]].x-x0);
			sum%=mod;
			int cnt1=0,cnt2=t,las=x0; LL now=0;
			for(int j=1; j<=t; ++j)
			{
				sum=sum+1ll*(cnt1-cnt2)*(A[B[j]].x-las)%mod, sum=(sum%mod+mod)%mod;
				las=A[B[j]].x, --cnt2, ++cnt1;
				A[B[j]].valy=sum;
			}
		}

	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=1ll*A[i].valx*A[i].valy%mod;
	printf("%lld\n",ans%mod);

	return 0;
}/*
6
1 3
3 2
3 5
3 3
4 5
4 3
*/
