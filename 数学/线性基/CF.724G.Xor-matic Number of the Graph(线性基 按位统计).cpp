/*
343ms	11200KB
$Description$
给定一张带边权无向图。若存在u->v的一条路径使得经过边的边权异或和为s（边权计算多次），则称(u,v,s)为interesting triple。
求图中所有interesting triple中s的和。
$Solution$
同[WC2011]Xor，任意两点路径的Xor和是它们间(任意一条)简单路径的和Xor一些环的和。so可以先处理出环上的和，构造线性基。两点间的一条简单路径可以直接求个到根节点的dis[]。
有了各点的dis，然后考虑用组合逐位统计答案。统计dis在这位上为0/1的点数，令size为线性基上向量个数。
如果两个点的dis是一个0一个1，那么要在线性基上取一个0。若线性基在这一位上有1，则保留，在剩下的size-1个向量中任意组合，根据得到的结果可以确定这个1是否取，这样有不同的2^{size-1}种方案；如果这位没有1，那就是2^{size}种方案。
如果两个点dis同为1/0，那要取一个1，如果线性基在这一位有1，同上 有2^{size-1}种方案。
注意图可能不连通。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 59
#define mod (1000000007)
typedef long long LL;
const int N=1e5+5,M=4e5+5;

int n,m,Enum,H[N],nxt[M],to[M],cnt[2],t,pw[66],size;
LL len[M],dis[N],base[66],q[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(LL w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Insert(LL x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
		{
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
		}
}
void DFS(int x,int f)
{
	vis[x]=1, q[++t]=dis[x];
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]) dis[v]=dis[x]^len[i], DFS(v,x);
		else if(v!=f) Insert(dis[x]^dis[v]^len[i]);
}
LL Calc()
{
	LL ans=0;
	for(int i=Bit; ~i; --i)
	{
		bool flag=0; LL tmp;
		for(int j=0; j<=Bit; ++j)
			if(base[j]>>i&1) {flag=1; break;}
		cnt[0]=cnt[1]=0;
		for(int j=1; j<=t; ++j) ++cnt[q[j]>>i&1];
		if(!flag&&(!cnt[1]||!cnt[0])) continue;

		if(flag)
		{
			tmp=((1ll*cnt[0]*(cnt[0]-1)>>1)+(1ll*cnt[1]*(cnt[1]-1)>>1))%mod;
			ans+=1ll*tmp*pw[size-1]%mod*pw[i]%mod;
		}
		tmp=1ll*cnt[0]*cnt[1]%mod;
		if(flag) ans+=1ll*tmp*pw[size-1]%mod*pw[i]%mod;
		else ans+=1ll*tmp*pw[size]%mod*pw[i]%mod;
	}
	return ans%mod;
}

int main()
{
	n=read(), m=read(), pw[0]=1;
	for(int i=1; i<=Bit; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	while(m--) AddEdge(readll(),read(),read());
	LL ans=0;
	for(int i=1; i<=n; ++i)
		if(!vis[i]) memset(base,0,sizeof base), size=t=0, DFS(i,i), ans+=Calc();
	printf("%I64d",ans%mod);

	return 0;
}
