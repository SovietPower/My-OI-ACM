/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e5+5;

int cnt[N],pos[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),m=read(),K=read();

		memset(cnt,0,n+1<<2);
		memset(pos,0,n+1<<2);
		pos[K]=1;

		for(int i=1; i<=m; ++i)
		{
			int u=read(),v=read();
			if(pos[u]) ++cnt[u];
			if(pos[v]) ++cnt[v];
			
			int x=cnt[u],y=cnt[v],a=pos[u],b=pos[v];
			if(pos[u])
				if(!pos[v]) pos[v]=1, cnt[v]=x-1;
				else cnt[v]=std::min(cnt[v],x-1);
			std::swap(u,v), x=y;
			if(b)
				if(!pos[v]) pos[v]=1, cnt[v]=x-1;
				else cnt[v]=std::min(cnt[v],x-1);
			
//			std::swap(u,v), printf("%d %d  %d %d\n",cnt[u],cnt[v],pos[u],pos[v]);
		}
		for(int i=1; i<=n; ++i)
			printf("%d%c",pos[i]?cnt[i]:-1," \n"[i==n]);
	}
	

	return 0;
}
