/*
924kb	32ms

*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=55,M=N*N<<1,INF=0x3f3f3f3f;

int src,des,Enum,H[N],nxt[M],to[M],fr[M],cap[M],pre[N],lev[N];
char s[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=w;
}
inline void AE2(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	for(int i=0; i<des; ++i) lev[i]=des+1;
	int h=0,t=1; q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1]) lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[0]<=des;
}
inline int Augment()
{
	int mn=INF;
	for(int i=des; i; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	static int num[N],cur[N];
	if(!BFS()) return 0;
	memset(num,0,sizeof num);
	for(int i=0; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int res=0,x=0;
	while(lev[0]<=des)
	{
		if(x==des) x=0, res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		src=0, des=n+1;
		int a1=read()+1,a2=read()+1,an=read(),b1=read()+1,b2=read()+1,bn=read();
		for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);

		Enum=1, memset(H,0,n+2<<2);
		for(int i=1; i<=n; ++i)
			for(int j=i+1; j<=n; ++j)
				switch(s[i][j])
				{
					case 'O': AE(i,j,1); break;
					case 'N': AE(i,j,INF); break;
				}
		AE2(src,a1,an), AE2(src,b1,bn), AE2(a2,des,an), AE2(b2,des,bn);
		if(ISAP()!=an+bn) {puts("No"); continue;}

		Enum=1, memset(H,0,n+2<<2);
		for(int i=1; i<=n; ++i)
			for(int j=i+1; j<=n; ++j)
				switch(s[i][j])
				{
					case 'O': AE(i,j,1); break;
					case 'N': AE(i,j,INF); break;
				}
		AE2(src,a1,an), AE2(src,b2,bn), AE2(a2,des,an), AE2(b1,des,bn);
		if(ISAP()!=an+bn) {puts("No"); continue;}
		puts("Yes");
	}
	return 0;
}
