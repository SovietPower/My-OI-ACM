/*
36744kb	5548ms(没有O2用一堆vector就是慢...)
$Description$
给定一棵树，边有价值$v_i$，长度为$1$。求长度$len$在$[l,r]$间的路径，使得其$\frac{\sum val}{len}$最大。
$n\leq 10^5,\ v_i\leq 10^6$。

$Solution$
二分答案，然后判断是否存在一条长度在[L,R]的路径满足权值和非负。可以点分治。
对于（距当前根节点）深度为d的一条路径，可以用其它子树深度在[L-d,R-d]内的最大值更新。这可以用单调队列维护。
这需要子树中的点按dep排好序。可以用BFS，省掉sort。
直接这样的话，每次用之前的子树更新当前子树时，每次复杂度是$O(\max\{dep\})$的（之前子树中最大的深度）。能被卡成$O(n^2\log n)$。
可以再对每个点的所有子树按最大深度排序，从小的开始计算，这样复杂度就还是$O(\sum dep)$。总复杂度$O(n\log n\log v)$。
但是常数也比较大。
在二分前要先将点分树建出来（直接用vector存每个点作为根时它的整棵子树就行了）。
二分边界最好优化下。
最长链的2倍不足L就跳过。优化很明显...(8400->5500)
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-9
typedef long long LL;
const int N=1e5+5;
const double INF=1ll<<60;

int L,R,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],Min,root,sz[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int dep; LL dis;
};
struct Block//每个连通块 
{
	int mxd;
	std::vector<Node> vec;
	bool operator <(const Block &x)const
	{
		return mxd<x.mxd;
	}
};
std::vector<Block> bl[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Find_root(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			Find_root(v,x,tot), sz[x]+=sz[v], mx=std::max(mx,sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void BFS(int s,int rt,int sl)
{
	static int q[N],pre[N],dep[N];
	static LL dis[N];
	int h=0,t=0; q[t++]=s, pre[s]=rt, dep[s]=1, dis[s]=sl;
	bl[rt].push_back(Block());
	std::vector<Block>::iterator it=--bl[rt].end();
	while(h<t)
	{
		int x=q[h++]; it->vec.push_back((Node){dep[x],dis[x]});
		for(int i=H[x],v; i; i=nxt[i])
			if(!vis[v=to[i]]&&v!=pre[x])
				pre[v]=x, dep[v]=dep[x]+1, dis[v]=dis[x]+len[i], q[t++]=v;
	}
	it->mxd=dep[q[h-1]];
	std::reverse(it->vec.begin(),it->vec.end());//dep从大到小 保证匹配区间是递增的（递减的话边界不好找吧）。
}
void Solve(int x)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) BFS(v,x,len[i]);
	std::sort(bl[x].begin(),bl[x].end());
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, Find_root(v,x,sz[v]), Solve(root);
}
void Init(int n)
{
	Min=N, Find_root(1,1,n), Solve(root);
}
bool Check(int n,double X)
{
	static int q[N];
	static double mx[N];
	for(int i=1; i<=n; ++i) mx[i]=-INF;
	std::vector<Node>::iterator it2,ed2;
	std::vector<Block>::iterator it1,ed1;
	for(int s=1; s<=n; ++s)
	{
		if(!bl[s].size()||2*(--bl[s].end())->mxd<L) continue;//最长链的2倍不足L就跳过。优化很明显...
		bool vic=0;
		for(it1=bl[s].begin(),ed1=bl[s].end(); it1!=ed1; ++it1)
		{
			int mxd=it1->mxd,now=1,h=1,t=0;
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)//用当前子树的值和之前子树的链匹配 
			{
				int l=std::max(0,L-it2->dep),r=std::min(mxd,R-it2->dep);//当前链能匹配的路径区间 
				if(l>r) continue;
				while(now<=r)
				{
					while(h<=t && mx[q[t]]<mx[now]) --t;
					q[++t]=now++;
				}
				while(h<=t && q[h]<l) ++h;
				if(mx[q[h]]+it2->dis-X*it2->dep>eps) {vic=1; goto Skip;}
			}
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)//用当前子树更新状态，顺便判断一下是否有到根节点的满足条件的路径。
			{
				int d=it2->dep; mx[d]=std::max(mx[d],it2->dis-X*d);
				if(L<=d && d<=R && mx[d]>eps) {vic=1; goto Skip;}
			}
		}
		Skip: ;
		for(it1=bl[s].begin(),ed1=bl[s].end(); it1!=ed1; ++it1)
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)
				mx[it2->dep]=-INF;
		if(vic) return 1;
	}
	return 0;
}

int main()
{
	int n=read(),mn=1e6,mx=0; L=read(),R=read();
	for(int i=1,u,v,w; i<n; ++i) u=read(),v=read(),w=read(),AE(u,v,w),mn=std::min(mn,w),mx=std::max(mx,w);
	Init(n);
	double l=mn,r=mx,mid;
	for(int T=1; T<=31; ++T)
		if(Check(n,mid=(l+r)*0.5)) l=mid;
		else r=mid;
	printf("%.3lf\n",l);

	return 0;
}
