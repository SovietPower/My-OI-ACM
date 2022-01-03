/*
1284kb	5160ms
这种题当然要黑白染色。。
两种颜色的格子数可能相同，也可能差1。记$n1/n2$为黑/白格子数，$s1/s2$为黑/白格子权值和。
如果$n1\neq n2$，假设$n1>n2$，因为每次是同时给两种颜色+1，所以最后的差也只能是$s1-s2$($s1>s2$)，个数只差1，所以也只能都变成$s1-s2$。(注意需满足$s1-s2\geq A_{max}$)
如果$n1=n2$，假设$x$合法（所有数可以变成$x$），那么$x+1$也合法，因为黑白可以两两配对并加一。
即可以二分最终的数$x$。
二分图匹配模型，二分后边的容量就可以确定了。最大流是$(x*tot-s1-s2)/2$或者源点汇点都满流则合法。
最终数的上限肯定不是$A_{max}$。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1700,M=N<<3;
const LL INF=1e14;

int n,m,src,des,A[N],Enum,H[N],cur[N],nxt[M],fr[M],to[M],pre[N],lev[N],num[N];
LL cap[M];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}//我可能有毒 
#define AddEdge(u,v,w) to[++Enum]=v,fr[Enum]=u,nxt[Enum]=H[u],H[u]=Enum,cap[Enum]=w,to[++Enum]=u,fr[Enum]=v,nxt[Enum]=H[v],H[v]=Enum,cap[Enum]=0
bool BFS()
{
	static int q[N];
	for(int i=src; i<des; ++i) lev[i]=des+1;
	lev[des]=0, q[0]=des; int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i^1] && lev[to[i]]==des+1) lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
inline LL Augment()
{
	LL mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
LL ISAP()
{
	if(!BFS()) return 0ll;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src; LL res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src, res+=Augment();
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
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}
bool Check(LL x,LL s1,LL s2)
{
	Enum=1, memset(H,0,sizeof H);
	int tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			++tot;
			if((i+j)&1)
			{
				AddEdge(src,tot,x-A[tot]);//, sum+=x-A[tot];
				if(i<n) AddEdge(tot,tot+m,INF);//边是有向的，不能容量都为INF啊mdzz 
				if(j<m) AddEdge(tot,tot+1,INF);
			}
			else
			{
				AddEdge(tot,des,x-A[tot]);
				if(i<n) AddEdge(tot+m,tot,INF);//white->black！
				if(j<m) AddEdge(tot+1,tot,INF);
			}
		}
	return (ISAP()<<1ll)==(x*tot-s1-s2);//ISAP()==sum;
}

int main()
{
	for(int T=read(); T--; )
	{
		n=read(), m=read(), src=0, des=n*m+1;
		int tot=0,mx=0; LL s1=0,s2=0;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				mx=std::max(mx,A[++tot]=read()),(i+j)&1?(s2+=A[tot]):(s1+=A[tot]);//s1,s2别反。。
		if(tot&1) printf("%lld\n",(/*s1>s2&&*/s1-s2>=mx&&Check(s1-s2,s1,s2))?(((s1-s2)*tot-s1-s2)>>1ll):-1ll);
		else if(s1!=s2) puts("-1");
		else
		{	
			LL l=mx,r=INF,mid;
			while(l<r)
			{
				if(Check(mid=l+r>>1,s1,s2)) r=mid;
				else l=mid+1;
			}
			printf("%lld\n",l<INF?(1ll*(tot>>1)*l-s1/*(1ll*tot*l-s1-s2)>>1ll*/):-1ll);
		}
	}
	return 0;
}
