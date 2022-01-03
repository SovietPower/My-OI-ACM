/*
$Description$
������ѡȡ���ཻ����������ʹ�þ����ĵ�ĵ�Ȩ�����
$Solution$
����ֱ���ϵĵ��Ǻܿ��ܶ�Ҫѡ�ģ��ܺ�֤������ֱ����һ����ͬһ�����������԰�ֱ����������ѡ������������һ������
ֱ������������λ�ò�һ�������ڵģ����������ŵģ���Ϊ��Ȼ�ܳ�Ϊֱ���ͱ������е�ĳ��������(��ʲô��Ϲд��...�ɺ���)��
so��ֱ����ά��ǰ׺��׺���ֵ��ע��ֱ����Ϊͬһ������Ȼ�ǿ��ܵġ�
Ȼ�������ֱ���ϵ��ÿ��������ѡ��һ��Ȩֵ����������������DP����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,V,fa[N],q[N],A[N],Enum,H[N],to[N<<1],nxt[N<<1];
LL D,f[N][2],sum[N],pre[N],suf[N];
bool mark[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,LL d)
{
	if((d+=A[x])>D) D=d, V=x;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) fa[to[i]]=x, DFS(to[i],d);
}
void DP(int x,int fa)
{
	LL v1=0, v2=0, v3=0;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DP(v,x); v3=std::max(v3,f[v][1]);
			if(v1<f[v][0]) v2=v1, v1=f[v][0];
			else if(v2<f[v][0]) v2=f[v][0];
		}
	f[x][0]=A[x]+v1, f[x][1]=std::max(v3,v1+v2+A[x]);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	DFS(1,0), D=0, fa[V]=0, DFS(V,0);
	int t=0;
	for(int x=V; x; x=fa[x]) q[++t]=x, sum[t]=sum[t-1]+A[x], mark[x]=1;
	LL ans=0;
	for(int i=1,x=q[1]; i<=t; x=q[++i])
	{
		LL res=0;
		for(int j=H[x],v; j; j=nxt[j])
			if(!mark[v=to[j]]) DP(v,x), res=std::max(res,f[v][0]/*0!*/), ans=std::max(ans,f[v][1]+sum[t]);
		f[x][1]=res, pre[i]=std::max(sum[i]+res,pre[i-1]);
	}
	for(int i=t,x=q[i]; i; x=q[--i])
	{
		suf[i]=std::max(sum[t]-sum[i-1]+f[x][1],suf[i+1]);
		ans=std::max(ans,pre[i-1]+suf[i]);
	}
	printf("%I64d\n",ans);

	return 0;
}
