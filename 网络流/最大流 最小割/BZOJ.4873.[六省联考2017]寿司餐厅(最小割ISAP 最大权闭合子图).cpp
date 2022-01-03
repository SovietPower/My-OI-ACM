/*
2240kb	148ms
���Ὠͼ���������Ȩ�պ���ͼ�ͷ������ǻ����쿼�귢�ַ��������ԡ���Ӳ�ǰ����䵥�������ˣ�û������С��������ƹ�ϵ��
����: ���Ȩ�պ���ͼ.
�����Ҫȡһ�����䣬��ô�����һ���������еĶ�ȡһ�飬��һ��ֻȡһ�顣
��: ѡ(i,j)(i<j)��ѡ(i+1,j)��(i,j-1)��ѡ(i,i)��ѡid[i]��
��Դ����ÿ��ȨֵΪ����������Ȩֵ�ıߣ���ÿ��ȨֵΪ��������������Ȩֵ����ֵ�ı�(�谭����������һ��)��
��ÿ����˾iֱ�Ӵ�������(i,i)������D[i,i]-id[i]����������/Դ�����ߣ���˾��id[i]��INF�ıߣ�id[i]������m*id^2�ıߡ�
Ans = ��Ȩ�� - ����� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5,M=7e4+5,INF=0x3f3f3f3f;

int n,m,src,des,Enum,cur[N],H[N],nxt[M],fr[M],to[M],cap[M],lev[N],num[N],que[N],pre[N];
int id[105][105],A[105],d[105][105],exist[1005];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=src; i<des; ++i) lev[i]=des+1;
	que[0]=des, lev[des]=0; int h=0,t=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);     
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn;
	return mn;
}
long long ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) cur[i]=H[i],++num[lev[i]];
	int x=src; long long res=0;
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
	n=read(),m=read(),Enum=1;
	int cnt=n;
	for(int i=1; i<=n; ++i) id[i][i]=i;
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j) id[i][j]=++cnt;
	src=0, des=cnt+n+1;
	for(int i=1; i<=n; ++i)
	{
		A[i]=read();
		if(m && !exist[A[i]]) exist[A[i]]=++cnt,AddEdge(cnt,des,/*m**/A[i]*A[i]);
		if(m) AddEdge(i,exist[A[i]],INF);
	}
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; ++j) d[i][j]=read();
	long long res=0;
	for(int t,i=1; i<=n; ++i)
		(t=d[i][i]-A[i])>0 ? res+=t,AddEdge(src,i,t) : AddEdge(i,des,-t);
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
		{
			AddEdge(id[i][j],id[i+1][j],INF), AddEdge(id[i][j],id[i][j-1],INF);
			d[i][j]>0 ? res+=d[i][j],AddEdge(src,id[i][j],d[i][j]) : AddEdge(id[i][j],des,-d[i][j]);
		}
	printf("%lld",res-ISAP());

	return 0;
}
