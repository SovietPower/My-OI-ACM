#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=450,M=5e4+5,INF=0x3f3f3f3f,MAXIN=1e5;

int n,m,src,des,H[N],cur[N],Enum,nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],q[N],lev[N],num[N],pre[N];
//char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=src; i<des; ++i) lev[i]=des+1;
	q[0]=des, lev[des]=0;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i^1] && lev[to[i]]==des+1)
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	for(int i=des; i!=src; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int res=0,x=src;
	while(lev[src]<=des)
	{
		if(x==des) res+=Augment(),x=src;
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
			++num[lev[x]=mn+1];
			cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	n=read(),m=read();
	Enum=1, src=0, des=n+m+1;
	int sum=0,v;
	for(int i=1; i<=n; ++i) v=read(),AddEdge(src,i,v),sum+=v;
	for(int i=1; i<=m; ++i) AddEdge(i+n,des,read());
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			AddEdge(i,j+n,1);
	if(ISAP()!=sum) putchar('0');
	else
	{
		puts("1");
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=H[i]; j; j=nxt[j])
				if(!cap[j]) printf("%d ",to[j]-n);
	}
	return 0;
}
