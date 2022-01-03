/*
6952kb	6680ms
$Description$
����һ������$k$����һ��·����ʹ��$\left|\frac{·������}{����}-k\right|$��С�������Сֵ��
$n\leq 5\times 10^5,\ k\leq 10^{13}$��
$Solution$
��$val_i$��ÿ���ߵı�Ȩ��$s$�Ǳ�Ȩ�ͣ�$t$�Ǿ���������$k$�Ǹ�����$k$��
�ڵ���ε�ʱ����ִ�$x$����$|\frac st-k|=x$���ж��Ƿ�������$|\frac st-k|<x$��
��Ϊ�Ǿ���ֵ�������������
1. $\frac st-k\geq 0\to \sum val_i-k\geq 0$��
�ж��Ƿ���$\frac st-k< x\to\quad s-t*k<t*x\to\quad\sum val_i-k<t*x$��
2. $\frac st-k<0\to\sum val_i-k<0$��
�ж��Ƿ���$\frac st-k>-x\to\quad s-t*k>-t*x\to\quad \sum val_i-k>-t*x$

�ȶ�ÿ���ߵı�Ȩ$val_i$����һ��$k$��
�Ե�һ�����Ϊ�����������Ƿ��������·��$i,j$��ʹ��$s_i+s_j\geq 0$����$s_i+s_j<t_i*x+t_j*x$��
��$DFS$�õ�������·����Ϣ��һ����Ԫ��$(s,t,anc)$����ʾһ��·����Ȩֵ�͡�����������·�������Ŀ�����������·��ƴ������ʱ��������ͬһ����������
Ȼ���������Ԫ�鰴$s$��С���������Ǵ�С����ö��$i$����һ������$s_i+s_j\geq 0$��$j$��λ��һ���ǵ����ݼ��ģ�$j$���棨$i$֮ǰ����·�������㡣
����ά������$pair$����ʾ����$s_k-t_k*x$��С�ġ����Բ�ͬ��������Ԫ��$A,B$���ҵ���һ��$s_p>0$��λ��$p$����$i=p,j=p-1$��Ȼ������$i$��ö�٣�����һ��$A,B$��Ȼ��$j$Ҳ������ǰ�ƶ�˳�����$A,B$�Ϳ����ˡ�ÿ�ζ���$i$���Ͱ�$A,B$��$k$����$i$���һ�¿��Ƿ��������$s_k-t_k*x<t_i*x-s_i$��
���忴����ɣ�

����������Ͷ���$x$��ʱ��������$check$�ж�$x$��$\frac st -k\geq 0$����$-x$��$\frac st-k<0$���Ƿ���һ�����о����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<LL,int>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e4+5;
const LL INF=1ll<<60;

int cnt,Enum,H[N],nxt[N<<1],to[N<<1],Min,root,sz[N];
LL Ans,len[N<<1];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	LL s; int t,anc;
	inline bool operator <(const Node &x)const
	{
		return s<x.s;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(LL w,int u,int v)
{
	Ans=std::min(Ans,std::abs(w));//abs!!!
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int fa,LL s,int dep,int anc)
{
	A[++cnt]=(Node){s,dep,anc};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) DFS(v,x,s+len[i],dep+1,anc);
}
inline void Upd(pr &x,pr &y,pr now)
{
	if(now.first<y.first)
	{
		if(now.first<x.first)
		{
			if(now.second!=x.second) y=x;
			x=now;
		}
		else if(now.second!=x.second) y=now;
	}
}
bool Check1(LL k,int pos,int cnt)
{
	pr x(INF,0),y(INF,0); A[0].s=-INF;
	for(int i=pos,j=pos-1; i<=cnt; ++i)
	{
		while(A[i].s+A[j].s>=0) Upd(x,y,mp(A[j].s-k*A[j].t,A[j].anc)), --j;
		if((x.second==A[i].anc?y.first:x.first)+A[i].s<k*A[i].t) return 1;
		Upd(x,y,mp(A[i].s-k*A[i].t,A[i].anc));
	}
	return 0;
}
bool Check2(LL k,int pos,int cnt)
{//s>-tx -> -s<tx
	pr x(INF,0),y(INF,0); A[cnt+1].s=INF;
	for(int i=pos-1,j=pos; i; --i)
	{
		while(A[i].s+A[j].s<0) Upd(x,y,mp(-A[j].s-k*A[j].t,A[j].anc)), ++j;
		if((x.second==A[i].anc?y.first:x.first)-A[i].s<k*A[i].t) return 1;
		Upd(x,y,mp(-A[i].s-k*A[i].t,A[i].anc));
	}
	return 0;
}
void Solve(int x)
{
	vis[x]=1, A[cnt=1]=(Node){0,0,0};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v,x,len[i],1,v);
	int p=1; std::sort(A+1,A+1+cnt), A[cnt+1].s=0;
	while(A[p].s<0) ++p;
	LL l=1,r=Ans,mid;//�ж��Ƿ���ڱ�AnsС�Ĵ� ��Χ��1~Ans����UOJ��������ǿ=-=��
	while(l<=r)
		if(Check1(mid=l+r>>1,p,cnt)||Check2(mid,p,cnt)) Ans=mid-1, r=mid-1;
		else l=mid+1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, FindRoot(v,x,sz[v]), Solve(root);
}

int main()
{
	const int n=read(); const LL K=readll();//readll!!
	Ans=INF;//���� ������Solve()ǰ�� = = 
	for(int i=1; i<n; ++i) AE(readll()-K,read(),read());
	Min=N, FindRoot(1,1,n), Solve(root);
	printf("%lld\n",Ans);

	return 0;
}
