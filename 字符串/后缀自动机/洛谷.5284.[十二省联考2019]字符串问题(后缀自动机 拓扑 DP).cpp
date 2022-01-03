/*
16102ms	127.4MB
暴力的话，由每个$A_i$向它能支配的$B_j$连边，再由$B_j$向它能匹配的$A_k$（是$A_k$的前缀）连边，拓扑DP就可以了。
正解就是优化建图方式。
把串反过来，$B_j$能匹配$A_k$就是$B_j$是$A_k$的后缀，换句话说$B_j$能匹配$parent$树中它子树的所有$A_k$。所以由每个$A_i,B_j$向$parent$树中连边即可。
但是如果没有$|A_i|\geq|B_j|$的限制，处在同一节点的$B_j$可能就不是$A_i$的后缀了。
我们对该节点上的串按长度排个序，$B_j$从小的向大的连边，$A_i$由最后一个$\leq$它的$B_j$向它连边，类似前缀和优化建图，就可以了。（注意建的是反图，这里说的是正向的边）
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define BIT 18
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,N2=N<<2,M=1e6+5;//N2=4n not 3n =-= M=m+na+nb+2n

int La[N],Ra[N],Lb[N],Rb[N],Enum,H[N2],nxt[M],to[M],dgr[N2],q[N2];
LL f[N2];
char s[N];
struct Node
{
	int len,p;
	bool operator <(const Node &a)const
	{
		return len<a.len||(len==a.len&&p>a.p);
	}
};
std::vector<Node> vec[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, ++dgr[v];
}
struct Suffix_Automaton
{
	#define S N<<1
	int bit,las,tot,son[S][26],fa[S],F[S][BIT+1],len[S],H[S],nxt[S],pos[S];
	#undef S
	inline void AE_Tree(int u,int v)
	{
		nxt[v]=H[u], H[u]=v;
	}
	inline int Find(int l,int p)
	{
		p=pos[p];
		for(int i=bit; ~i; --i) if(len[F[p][i]]>=l) p=F[p][i];
		return p;
	}
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void DFS1(int x,int dep)
	{
		bit=std::max(bit,dep);
		for(int i=1; 1<<i<=dep; ++i) F[x][i]=F[F[x][i-1]][i-1];
		for(int v=H[x]; v; v=nxt[v]) F[v][0]=x, DFS1(v,dep+1);
	}
	void DFS_Clear(int x,int dep)
	{
		for(int i=1; 1<<i<=dep; ++i) F[x][i]=0;
		for(int v=H[x]; v; v=nxt[v]) DFS_Clear(v,dep+1);
	}
	void Build(char *s,int n)
	{
		las=tot=bit=1;
		for(int i=1; i<=n; ++i) Insert(s[i]-'a'), pos[i]=las;
		for(int i=2; i<=tot; ++i) AE_Tree(fa[i],i);
		DFS1(1,1);
		int mx=bit; bit=1;
		while(1<<bit<mx) ++bit;
	}
	#define IsA(x) (x>tot&&x<=tot+na)
	void Build2(int na,int nb)
	{
		for(int i=1; i<=tot; ++i)
		{
			if(!vec[i].size()) {AE(fa[i],i); continue;}
			std::sort(vec[i].begin(),vec[i].end());
			const std::vector<Node> &v=vec[i];
			int las=fa[i];
			for(int j=0,l=v.size(); j<l; ++j)
			{
				int now=v[j].p; AE(las,now);
				if(!IsA(now)) las=now;
			}
			AE(las,i);
		}
	}
	void Clear()
	{
		DFS_Clear(1,1);
		for(int i=1; i<=tot; ++i) std::vector<Node>().swap(vec[i]);
		memset(H,0,tot+1<<2), memset(son,0,(sizeof son[0])*(tot+1));
	}
}sam;
#define GetLen(x) (x>tot&&x<=tot+na?Ra[x-tot]-La[x-tot]+1:0)
void Solve()
{
	scanf("%s",s+1);
	int len=strlen(s+1); std::reverse(s+1,s+len+1);
	sam.Build(s,len);

	int na=read(),tot=sam.tot;
	for(int i=1; i<=na; ++i) Ra[i]=len-read()+1,La[i]=len-read()+1;
	int nb=read();
	for(int i=1; i<=nb; ++i) Rb[i]=len-read()+1,Lb[i]=len-read()+1;
	for(int m=read(),u; m--; ) u=read(),AE(u+tot,read()+tot+na);
	for(int i=1,l; i<=na; ++i) l=Ra[i]-La[i]+1, vec[sam.Find(l,Ra[i])].push_back((Node){l,i+tot});
	for(int i=1,l; i<=nb; ++i) l=Rb[i]-Lb[i]+1, vec[sam.Find(l,Rb[i])].push_back((Node){l,i+tot+na});
	sam.Build2(na,nb);

	int Tot=tot+na+nb; int h=0,t=0;
	for(int i=1; i<=Tot; ++i) if(!dgr[i]) q[t++]=i, f[i]=GetLen(i);
	LL ans=0;
	while(h<t)
	{
		int x=q[h++]; ans=std::max(ans,f[x]);
		for(int i=H[x],v; i; i=nxt[i])
		{
			v=to[i], f[v]=std::max(f[v],f[x]);
			if(!--dgr[v]) f[v]+=GetLen(v), q[t++]=v;
		}
	}
	printf("%lld\n",t>=Tot?ans:-1ll);
	sam.Clear(), Enum=0, memset(H,0,Tot+1<<2), memset(dgr,0,Tot+1<<2), memset(f,0,Tot+1<<3);
}

int main()
{
	for(int T=read(); T--; Solve());
	return 0;
}
