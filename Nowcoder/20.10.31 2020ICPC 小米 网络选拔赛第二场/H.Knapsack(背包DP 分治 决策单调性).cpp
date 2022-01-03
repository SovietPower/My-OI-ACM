/*
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=4e5+5;

LL f[2][N];
std::vector<LL> vec[105];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve(int l,int r,int s,int t,int lim,int V,int x,int now)
{
	if(l>r) return;
	int m=l+r>>1,p=m;
	for(int i=std::min(m-1,t); i>=s&&m-i-1<lim; --i)
		if(x+m*V<N && f[now][x+m*V]<f[now^1][x+i*V]+vec[V][m-i-1])
			p=i, f[now][x+m*V]=f[now^1][x+i*V]+vec[V][m-i-1];
	Solve(l,m-1,s,p,lim,V,x,now), Solve(m+1,r,p,t,lim,V,x,now);
}

int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1,x; i<=n; ++i) x=read(),vec[x].push_back(read());
		int now=0,las=1;
		for(int i=1,lim; i<=100; ++i)
			if((lim=vec[i].size()))
			{
				std::sort(vec[i].begin(),vec[i].end(),std::greater<int>());
				for(int j=1; j<lim; ++j) vec[i][j]+=vec[i][j-1];
				now^=1;
				for(int j=0; j<=m; ++j) f[now][j]=f[now^1][j];
				for(int j=0; j<i; ++j) Solve(0,(m-j)/i,0,(m-j)/i,lim,i,j,now);
				for(int j=1; j<=m; ++j) f[now][j]=std::max(f[now][j],f[now][j-1]);
			}
		printf("%lld\n",f[now][m]);
		for(int i=1; i<=100; ++i) std::vector<LL>().swap(vec[i]);
		for(int i=0; i<=m; ++i) f[0][i]=0;
		for(int i=0; i<=m; ++i) f[1][i]=0;
	}

	return 0;
}
