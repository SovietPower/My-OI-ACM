/*
249ms	73800KB
$Description$
��n���㡣����Q����Ŀ����ѡ�񣨱߶�������ߣ�ÿ�θ���t,u,v/lr,w����
t==1����һ��u->v�ıߣ�����w��
t==2����u��[l,r]������һЩ�����ߣ�ÿ�λ���w��
t==3����[l,r]������һЩ����u���ߣ�ÿ�λ���w��
�����ʹ������s�����i(1<=i<=n)����С���ѡ�
$Solution$
���ѿ���ÿ���ߵı�Ȩ��ȫ�����Ͽ������ֱ�������·��
����������������뵽�߶���������
ԭn�������ǻ���������������(u->[l,r],w)����ô�������޸�һ����u�����[l,r]�Ľڵ�����ȨΪw�ıߡ�
��ֻ��������ȥ��ȴ�ز���n�����ϡ����԰�ÿ�����������Ҷ�������ȨΪ0�ıߣ�����[l,r]�Ľڵ�ͻ���ĺ�[l,r]��Щ����������ֱ�Ӵ�������Щ�㣩��
��Ϊ������ߣ���������[l,r]->u������Ҫ��һ���߶�����ɡ�
���ˡ��߶����ڵ��n+1��ţ�Ҷ�ڵ�ֱ����1~n��źܷ��㣬�Բ���1����ֱ�����ߡ�
Ҫ�����нڵ�겻ͬ�ĺţ��Ͳ���struct��װ�ˡ�
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
//#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<LL,int>
typedef long long LL;
const int N=100005*9,M=100005*(8+34);//M=8N+2Qlogn
const LL INF=0x3f3f3f3f3f3f3f3fll;//longlong!

int Enum,H[N],nxt[M],to[M],len[M],tot,son[N][2];
LL dis[N];
std::priority_queue<pr> q;
//char IN[MAXIN],*SS=IN,*TT=IN;
#define AddEdge(u,v,w) (to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,len[Enum]=w)//()���õ���Ŀ����� 
#define lson son[x][0]
#define rson son[x][1]
void Build2(int &x,int l,int r)
{
	if(l==r) {x=l; return;}
	x=++tot;
	Build2(lson,l,l+r>>1), Build2(rson,(l+r>>1)+1,r);
	AddEdge(x,lson,0), AddEdge(x,rson,0);
}
void Build3(int &x,int l,int r)
{
	if(l==r) {x=l; return;}
	x=++tot;
	Build3(lson,l,l+r>>1), Build3(rson,(l+r>>1)+1,r);
	AddEdge(lson,x,0), AddEdge(rson,x,0);
}
void Modify(int l,int r,int x,int L,int R,int t,int u,int w)
{
	if(L<=l && r<=R)
	{
		t==2?AddEdge(u,x,w):AddEdge(x,u,w);
		return;
	}
	int m=l+r>>1;
	if(L<=m) Modify(l,m,lson,L,R,t,u,w);//not rt<<1!
	if(m<R) Modify(m+1,r,rson,L,R,t,u,w);
}

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra(int s)
{
	static bool vis[N];
	memset(dis,0x3f,sizeof dis);
	dis[s]=0, q.push(mp(0,s));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
				dis[v]=dis[x]+len[i], q.push(mp(-dis[v],v));
	}
}

int main()
{
	int n=read(),Q=read(),S=read(),rt2,rt3;
	tot=n, Build2(rt2,1,n), Build3(rt3,1,n);
	for(int t,u,v,l,r,w; Q--; )
	{
		if((t=read())==1) u=read(),v=read(),w=read(),AddEdge(u,v,w);
		else u=read(),l=read(),r=read(),w=read(),Modify(1,n,t==2?rt2:rt3,l,r,t,u,w);
	}
	Dijkstra(S);
	for(int i=1; i<=n; ++i) printf("%I64d ",dis[i]==INF?-1ll:dis[i]);

	return 0;
}
