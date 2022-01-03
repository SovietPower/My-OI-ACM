/*
62ms	9800KB
$Description$
����Ҫ�ø�����$n$�������ݻ�$m$�ܷɴ��е�ĳһЩ��ÿ�ܷɴ���Ҫ���ݻ�ǡ��һ�Ρ�
���������֣�1.�����ڸ����ļ����дݻ�һ�ܷɴ���2.���Դݻ�����$[l,r]$�е�һ�ܷɴ���3.�ݻٸ������ܷɴ��е�ǡ�����ܣ���֤����3�и��������зɴ���ͬ����
ĳЩ�������Կ��Բ��á�������ܴݻٷɴ���������
$Solution$
��Ȼ������������1�������ܼ��ϴ�С�����ƣ�����ֱ�����ߡ�����2��Ҫ���������ߣ���Ȼ�߶����Ż���
��������3��ǡ��2�ܵ����ƿ����Ȳ��ܣ���������������Ϊ2�ıߡ���������ֻƥ����һ�����������϶��Ǳ�����1��2ƥ�䣬�������ɡ�
�������������ֻ����ԭͼ������ıߣ�����ߴ���Ϊ���򻡵�������
Ȼ���ÿ����DFS��ÿ�������Դ��ͻ�������������ˣ�����ѿ��ߴ�����������
���ö������3������һ����
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
const int S=5005*2,N=5005*3,M=(150000+100000)*2,INF=0x3f3f3f3f;

int n,tot,Fr,To,A[5005],B[5005],C[5005],cnt[5005],son[S][2];
int src,des,Enum,cur[N],H[N],nxt[M],to[M],cap[M],fr[M],pre[N],num[N],lev[N];
std::vector<pr> ans,e[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, fr[Enum]=v;
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, fr[Enum]=u;//odd:u->v
}
//-----Segment Tree-----
#define ls son[x][0]
#define rs son[x][1]
#define lson son[x][0],l,m
#define rson son[x][1],m+1,r
void Build(int &x,int l,int r)
{
	if(l==r) {x=l; return;}
	x=++tot;
	int m=l+r>>1;
	Build(lson), Build(rson);
	AE(x,ls,INF), AE(x,rs,INF);
}
void Insert(int x,int l,int r,int L,int R,int s)
{
	if(L<=l && r<=R) {AE(s,x,1); return;}
	int m=l+r>>1;
	if(L<=m) Insert(lson,L,R,s);
	if(m<R) Insert(rson,L,R,s);
}
//-----ISAP-----
bool BFS()
{
	static int q[N];
	for(int i=0; i<=tot; ++i) lev[i]=tot+1;
	int h=0,t=1; lev[des]=0, q[0]=des;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==tot+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=tot;
}
inline int Augment()
{
	for(int i=des; i/*!=src*/; i=fr[pre[i]])//i
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=0; i<=tot; ++i)  ++num[lev[i]],cur[i]=H[i];
	int res=0,x=0;//src
	while(lev[src]<=tot)
	{
		if(x==des) res+=Augment(),x=0;//src
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=tot;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x/*!=src*/) x=fr[pre[x]];
		}
	}
	return res;
}
//-----DFS for Ans-----
bool DFS(int x)
{
	if(x==des) return 1;
	for(int i=0,l=e[x].size(); i<l; ++i)
//		if(i&1 && cap[i^1])//�ѱ��ؽ�����С�ܶ� 
		if(e[x][i].second)
		{
			if(!DFS(e[x][i].first)) continue;
			--e[x][i].second;
			if(!x/*==src*/) Fr=e[x][i].first;
			if(e[x][i].first==des) To=x;
			return 1;
		}
	return 0;
}
//-----Main-----
int main()
{
	#define S root,1,m
	n=read(); int m=read(),root=0;//n:weapons m:ships
	Enum=1, tot=m, Build(S), src=0, des=++tot;
	for(int i=1; i<=m; ++i) AE(i,des,1);

	for(int i=1,p=tot+1,opt,l,r; i<=n; ++i,++p)
		if(!(opt=read()))
		{
			AE(0,p,1);
			for(int k=read(); k--; AE(p,read(),1));
		}
		else if(opt==1)
			l=read(), r=read(), AE(0,p,1), Insert(S,l,r,p);
 		else
			AE(0,p,2), AE(p,A[i]=read(),1), AE(p,B[i]=read(),1), AE(p,C[i]=read(),1);
	int tmp=tot; tot+=n;
	int flow=ISAP();
	printf("%d\n",flow);

	for(int i=2; i<=Enum; i+=2) e[to[i]].push_back(mp(fr[i],cap[i]));
	for(int i=1; i<=flow; ++i)//weapon -> ship
		Fr=0, DFS(0), ans.push_back(mp(Fr-tmp,To)), ++cnt[Fr-tmp];
	int size=ans.size();//flow
	for(int i=1; i<=n; ++i)
		if(A[i] && cnt[i]==1)
			for(int j=0; j<size; ++j)
				if(ans[j].first!=i&&(ans[j].second==A[i]||ans[j].second==B[i]||ans[j].second==C[i]))
				{
					ans[j].first=i;
					break;
				}
	for(int i=0; i<size; ++i) printf("%d %d\n",ans[i].first,ans[i].second);

	return 0;
}
