/*
$Description$
һ��������n-1�Է��޳Է�����������һ�����ӵ����࣬ÿһ�Ի�Ϊ���޹�ϵ���˱����������ӵ����ࡣ������Щ������֮�����ڡ�ͨ�顱��ϵ��ͨ���ϵ��������Ů֮�䣬ͬ��֮��Ҳ�С�������治��������ͨ���ϵ���ˡ��ж��Ƿ���ڿ��е��������������ڵĻ����������ͬһ�ŵ��ˡ�
$Solution$
ÿ�Է�ֻ����һ������������һ�ߣ���������2-SAT��ʼ״̬ 
����0��ʾ�����1��ʾ���� 
��ô�����й�ϵ��u,v(i'��ʾ������һ��)��Ӧ������u->v',v->u'����������i'��ʾ�������(����һ��)��������u'->v,v'->u 
��Ϊ���������v�й�ϵ���ͻ�����1(u')->v'�������ͬ������һ���ˣ�����������v�й�ϵ������0(u)->v'(ͬ������һ��)�Ƿ������߹���� 
��ì�ܵ�������й�ϵ������ͬ��������棬����2-SAT����Ŀ��н����������� 
����������Ҫ�������࣬����0->1����ʾ����ѡ0��һ��ѡ1������ѡ�����Ľ������������� 
ÿ�Է򸾾��Ƕ����ģ�Ҳ�����Ա𡣡��������һ����ʾi����һ���ͱ�ʾi' 
�������ʱֻҪ���������Ⱦɫ��ͬ�ľͿ����� 
��bel[i]����i��Ҫ�� ע��������������ͳһ 
�����е��벻���ס���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005,M=1e5+5;

int n,m,Enum,H[N],nxt[M],to[M],sk[N],top,cnt,bel[N],low[N],dfn[N],id;
int num,head[N],snxt[N],sto[N],conf[N],dgr[N]/*indgree*/,col[N],q[N];//conflict
bool ins[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline void AddEdge2(int u,int v){
	++dgr[v], sto[++num]=v, snxt[num]=head[u], head[u]=num;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}
bool Topo()
{
	for(int i=0; i<n<<1; i+=2)
		if(bel[i]==bel[i^1]) return 0;
		else conf[bel[i]]=bel[i^1],conf[bel[i^1]]=bel[i];
	num=0, memset(head,0,sizeof head),
	memset(col,0,sizeof col), memset(dgr,0,sizeof dgr);
	for(int x=0; x<n<<1; ++x)
		for(int i=H[x]; i; i=nxt[i])
			if(bel[x]!=bel[to[i]]) AddEdge2(bel[to[i]],bel[x]);
	int h=0,t=0;
	for(int i=1; i<=cnt; ++i)
		if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		int x=q[h++];
		if(!col[x]) col[x]=1,col[conf[x]]=2;
		for(int i=head[x]; i; i=snxt[i])
			if(!--dgr[sto[i]]) q[t++]=sto[i];
	}
	return 1;
}

int main()
{
	while(n=read(),m=read(),n&&m)
	{
		id=top=cnt=Enum=0, memset(H,0,sizeof H);
		memset(dfn,0,sizeof dfn);
		char c,d; int a,b,s,t;
		while(m--)
		{
			scanf("%d%c %d%c",&a,&c,&b,&d);
//			s= c=='h'?a<<1:a<<1|1;//WA�����ʾ��man��2a����������Ҳ��man ��2a+1=1 
			s= c=='w'?a<<1:a<<1|1;
			t= d=='w'?b<<1:b<<1|1;
			AddEdge(s,t^1), AddEdge(t,s^1);
		}
		AddEdge(0,1);
		for(int i=0; i<n<<1; ++i)
			if(!dfn[i]) Tarjan(i);
		if(Topo())
		{
			for(int i=1; i<n; ++i)
				if(col[bel[i<<1]]==1) printf("%dh ",i);
				else printf("%dw ",i);
			putchar('\n');
		}
		else puts("bad luck");
	}
	return 0;
}
