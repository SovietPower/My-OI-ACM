/*
$Description$
��n���� m����ֽ��ÿ�������һЩ��ֽ����һ���˿��Ժ�����һ���˽���������ֽ��������ֻ�����ظ�����ֽ����һ���˽�������û�е���ֽ��������һ��������ж�������ֽ��
$Solution$
���մ�Ϊ��ֽ���࣬��ô�ͽ�ÿ����ֽ��T������Ϊ1�ıߣ���ֽ��ԴΪ��һ���˻�����������ֽ����ôֱ���Ե�һ������ΪS��������Aj��j��ֽ��������(S->j,Aj) 
���������ˣ���ôʵ����ֽ������ 
���������������ڵ�i����(i>1)����������iû�е���ֽ���룬����i�㣬�����ص���Ҫ������ֽ(������ֽi��Ҫ��1������) 
���Զ��ڳ���1���������i��������û�е���ֽj����(j->i,1)����i����ӵ��������1����ֽj(i->j,A[i][j]-1) 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=40,M=400,INF=0x3f3f3f3f;

int n,m,sum[N],src,des,cur[N],Enum,H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1];
int pre[N],lev[N],q[N],num[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], fr[Enum]=u, H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], fr[Enum]=v, H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=src; i<des; ++i) lev[i]=des+1;
	lev[des]=0, q[0]=des; int h=0,t=1;
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
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,res+=Augment();
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
	int T=read();
	for(int kase=1; kase<=T; ++kase)
	{
		Enum=1, memset(H,0,sizeof H);
		n=read(),m=read(), src=1, des=n+m+1;
		for(int i=1; i<=m; ++i) AddEdge(i+n,des,1);
		memset(sum,0,sizeof sum);
		for(int i=read(); i; --i) ++sum[read()];
		for(int i=1; i<=m; ++i)
			if(sum[i]) AddEdge(src,i+n,sum[i]);
		for(int i=2; i<=n; ++i)
		{
			memset(sum,0,sizeof sum);
			for(int j=read(); j; --j) ++sum[read()];
			for(int j=1; j<=m; ++j)
				if(!sum[j]) AddEdge(j+n,i,1);
				else if(sum[j]>1) AddEdge(i,j+n,sum[j]-1);
		}
		printf("Case #%d: %d\n",kase,ISAP());
	}
	return 0;
}
