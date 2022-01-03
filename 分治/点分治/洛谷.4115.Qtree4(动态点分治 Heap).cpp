/*
$Description$
给定一棵边带权的树，初始时所有点为白色。两种操作：1. 反转某点的颜色； 2. 询问树中最远的两个白色节点的距离（只有一个则为0）。
$n\leq 10^5,\ m\leq 2\times10^5$。
$Solution$
将每次Solve的重心root连起来，会形成一个深度为logn的树，就叫它点分树吧。。
我们对每个root维护两个东西: 它管辖的子树中所有白点到它上一层(点分树中的fa[x])的距离(记为h1)，以及它的所有子树中h1的最大值、次大值(这样就有答案了)(记为h2) 
要能随时插入与删除距离，同时要取最值，用堆维护即可。删除用额外一个堆实现。
需要有一个堆Ans统计答案，由每个root的h2去更新Ans。
修改时一个点只会影响其所有祖先节点(有logn个)，而且只需要修改值即可(不关心具体路径)，于是直接用堆实现，复杂度O(log^2n) 
还需要查询任意两点间的距离，dis[a]+dis[b]-2*dis[lca]即可，用RMQ以O(1)查LCA(括号序空间是2倍的).

注意堆修改时一定要先消除它在其它堆里的贡献heap.top，修改完再加入heap.top。
另外在访问每个点x时在h2[x]中加入0，因为2个点才可以对答案有贡献，x初始为白点是合法的。同时在把它变为黑点时直接可以删0，避免讨论。
最远边权是负的时答案应是0。
能用链分治 或 线段树+括号序列（边权需为1）做，快非常多。
补了括号序列的做法：https://www.cnblogs.com/SovietPower/p/10333155.html。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=3e5;

int n,Min,root,sz[N],Enum,H[N],to[N<<1],nxt[N<<1],val[N<<1],fa[N];
int dis[N],lg[N<<1],tm,cnt,id[N],A[N<<1][18],pos[N];//RMQ for LCA(感觉写的好麻烦--)
bool sta[N],vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Heap
{
	std::priority_queue<int> h,d;
	inline void Insert(int x){
		h.push(x);
	}
	inline void Delete(int x){
		d.push(x);
	}
	inline int Size(){
		return h.size()-d.size();
	}
	inline void Fix(){
		while(d.size() && h.top()==d.top()) h.pop(),d.pop();
	}
	inline int Top(){
		Fix(); return h.top();
	}
	inline void Pop(){
		Fix(), h.pop();
	}
	inline int Sec(){
		int t=Top(); h.pop();//注意必要的地方要fix 
		int t2=Top(); h.push(t);
		return t2;
	}
	inline int Two(){
		int t=Top(); h.pop();//注意必要的地方要fix 
		int t2=Top(); h.push(t);
		return t+t2;
	}
	void Change(int x,bool s){
		if(s) Delete(x);
		else Insert(x);
	}
}h1[N],h2[N],Ans;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void pre_DFS(int x,int f)
{
	int t=++tm; A[pos[x]=++cnt][0]=t, id[t]=x;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f)
			dis[to[i]]=dis[x]+val[i], pre_DFS(to[i],x), A[++cnt][0]=t;//访问完一棵子树时再加上 
}
void Init_RMQ()
{
	for(int i=2; i<=cnt; ++i) lg[i]=lg[i>>1]+1;//lg[]大小2N 
	for(int j=1; j<=lg[cnt]; ++j)
		for(int i=cnt-(1<<j-1); i; --i)//cnt-(1<<j-1) not n-(1<<j-1)!
			A[i][j]=std::min(A[i][j-1],A[i+(1<<j-1)][j-1]);
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f,int d,Heap &h)
{//初始全白 都加进去 
	h.Insert(d);
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f)
			DFS(to[i],x,d+val[i],h);
}
inline void Add_Ans(Heap &h){
//	if(h.Size()>=2) Ans.Insert(h.Top()+h.Sec());
	if(h.Size()>=2) Ans.Insert(h.Two());
}
inline void Del_Ans(Heap &h){
//	if(h.Size()>=2) Ans.Delete(h.Top()+h.Sec());
	if(h.Size()>=2) Ans.Delete(h.Two());
}
void Solve(int x)
{
	vis[x]=1, h2[x].Insert(0);
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]])
		{
			Heap tmp; DFS(v,x,val[i],tmp);
			Min=N, Get_root(v,x,sz[v]), fa[root]=x;
			h1[root]=tmp;//h1[root]
			h2[x].Insert(tmp.Top());
			Solve(root);
		}
	Add_Ans(h2[x]);
}
int LCA(int l,int r)
{
	if(l>r) std::swap(l,r);
	int k=lg[r-l+1];
	return id[std::min(A[l][k],A[r-(1<<k)+1][k])];
}
int Calc_dis(int a,int b){
	return dis[a]+dis[b]-2*dis[LCA(pos[a],pos[b])];
}
void Change(int x,bool s)
{
	Del_Ans(h2[x]), h2[x].Change(0,s), Add_Ans(h2[x]);
	for(int now=x; fa[now]; now=fa[now])
	{
		Del_Ans(h2[fa[now]]);//!
		if(h1[now].Size()) h2[fa[now]].Delete(h1[now].Top());//更改前先删除 
		h1[now].Change(Calc_dis(x,fa[now]),s);//变得dis是x与fa[now]的，不是now与fa[now]的。。mdzz 
		if(h1[now].Size()) h2[fa[now]].Insert(h1[now].Top());
		Add_Ans(h2[fa[now]]);
	}
}
inline char get(){
	char c=gc();
	while(c!='A'&&c!='C') c=gc();
	return c;
}

int main()
{
	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	pre_DFS(1,-1), Init_RMQ();
	Min=N, Get_root(1,-1,n), Solve(root);
	int m=read(),x,white=n;char opt[3];
	while(m--)
	{
//		scanf("%s",opt);
		if(/*opt[0]*/get()=='C') x=read(),Change(x,sta[x]^=1),white+=sta[x]?-1:1;
		else if(!white) puts("They have disappeared.");
		else printf("%d\n",white>1?std::max(0,Ans.Top()):0);
	}
	return 0;
}
