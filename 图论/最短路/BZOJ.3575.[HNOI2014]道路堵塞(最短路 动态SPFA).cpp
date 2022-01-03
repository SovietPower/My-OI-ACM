/*
18720kb	3244ms
$Description$
����һ������ͼ��һ��$1$��$n$�����·�����������·�ϵ�ÿ���ߣ���ɾ�������ߺ�$1$��$n$�����·�Ƕ��١�
$Solution$
ö��ɾÿ����Ȼ�������·��Ȼ���С�������ô����֮ǰ�����·��һЩ��Ϣ��
����ɾ��һ���ߺ�����·��$1$�����·����ĳ����$x$��Ȼ�����$x$�������·�ϵ�ĳ��$y$��֮��һ������$y$��$n$�����·�ߵ�$n$��
$n$Ҳ�����·�ϵĵ㣬��$x$һ���ᵽ��ĳ��$y$�������·����$n$����ʱ�Ϳ�����$y$��ֱ�Ӹ���$Ans$��
���Ƿ�����$y$����ֵ���Ը�������$y$֮ǰ���·�ıߵ�$Ans$��
�����öѰ����ֵ��$y$ǰ���������·�ıߵı��$id$�������������ǰɾ�ı�$i$���ڵ��ڶѶ���$id$���Ϳ���ֱ���öѶ��Ĵ��ˡ�����ֱ��$pop$���Ѷ���
�������ǰ��������·��ɾ����ÿ����һ����$(u,v)$��ֵʱ����$dis[v]$��Ȼ���$v$�ټ������SPFA�����ˡ�
ÿ��SPFA����Ҫ���$dis$��$dis$�ǵݼ��ġ�
��Ȼ���⸴�Ӷ���ѧ��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=2e5+5;

int Enum,H[N],nxt[M],fr[M],to[M],len[M],dis[N],dt[N],A[N],pre[N];
bool ban[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int pos,val;
	bool operator <(const Node &x)const
	{
		return val>x.val;
	}
};
std::priority_queue<Node> hp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
void SPFA(int s)
{
	static bool inq[N];
	static std::queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(!ban[i]&&dis[v=to[i]]>dis[x]+len[i])
			{
				dis[v]=dis[x]+len[i];
				if(pre[v]) hp.push((Node){pre[v],dis[v]+dt[pre[v]]});
				else if(!inq[v]) inq[v]=1, q.push(v);
			}
	}
}

int main()
{
	int n=read(),m=read(),l=read();
	for(int i=1; i<=m; ++i) AE(read(),read(),read());
	for(int i=1,id; i<=l; ++i)
	{
		A[i]=id=read();
		ban[id]=1, pre[to[id]]=i;
	}
	for(int i=l-1; i; --i) dt[i]=dt[i+1]+len[A[i+1]];

	memset(dis,0x3f,sizeof dis);
	dis[1]=0, SPFA(1);
	for(int i=1,id; i<=l; ++i)
	{
		while(!hp.empty()&&hp.top().pos<i) hp.pop();
		if(hp.empty()) puts("-1");
		else printf("%d\n",hp.top().val);
		id=A[i], dis[to[id]]=dis[fr[id]]+len[id];
		SPFA(to[id]);
	}

	return 0;
}
