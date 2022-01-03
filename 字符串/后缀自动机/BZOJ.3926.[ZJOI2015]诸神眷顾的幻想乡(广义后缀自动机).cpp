/*
221660kb	2580ms
要对多个串同时建立SAM，有两种方法：
1.将所有串拼起来，中间用分隔符隔开，插入字符正常插入即可。
2.在这些串的Trie上建SAM。实际上并不需要建Trie，还是只需要正常插入（因为本来就差不多？）。在要插入下一个串时需把las重新设为root。这就是广义后缀自动机。
对于本题，因为叶节点最多只有20个（别理解错了啊喂），以这些叶节点分别为根，DFS整棵树建Tire（当然原图就是），这样所有子串就在Trie上某条路径中。这样就成了求不同子串的个数。
当然还是不需要建Trie，依次插入SAM即可。如果当前有要插入点的转移，则不再新建np，而是直接用son[p][c]做np。否则会有很多重复节点（虽然不影响正确性吧）。
每次插入一个字符，其产生的子串一共有len[i]个（就是以它为右端点的后缀），不同的子串则有len[i]-len[fa[i]]个。所有节点的贡献求和即为答案。
注意会有20次建SAM，空间要够！还有longlong。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+7,S=N*20*2;

int n,C,A[N],dgr[N],Enum,H[N],nxt[N<<1],to[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Suffix_Automaton
{
	int tot,las,fa[S],son[S][11],len[S];
	void Init(){
		tot=las=1;
	}
	int Insert(int p,int c)
	{
		int las;
		if(son[p][c])
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) las=q;
			else
			{
				int nq=++tot; len[las=nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=nq;//不要想当然写fa[p]=nq q就代表np了 
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		else
		{
			int np=++tot; len[las=np]=len[p]+1;
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
					fa[nq]=fa[q], fa[np]=fa[q]=nq;
					for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
				}
			}
		}
		return las;
	}
	void Calc()
	{
		long long ans=0;
		for(int i=2; i<=tot; ++i) ans+=(long long)(len[i]-len[fa[i]]);
		printf("%lld\n",ans);
	}
}sam;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f,int rt)
{
	int t=sam.Insert(rt,A[x]);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,t);
}

int main()
{
	n=read(), C=read(), sam.Init();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=n; ++i) if(dgr[i]==1) DFS(i,i,1);
	sam.Calc();

	return 0;
}
