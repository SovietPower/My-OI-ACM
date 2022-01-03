/*
30740kb	612ms
$Description$
给定n个串和K，求每个串中有多少个子串是这n个串中至少K个串的子串。
$Solution$
同上题，我们可以算出每个节点所代表的串出现在了几个串中；而且我们知道，对于每个节点i，它代表的串的数量为len[i]-len[fa[i]]。
建立广义后缀自动机，预处理每个节点的cnt。每个节点的val可以根据cnt是否>=K设为len[i]-len[fa[i]]或0。
我们要求的是所有子串，所以如果统计val[i]，也要算上val[fa[i]],val[fa[fa[i]]]...直接建出parent树从上到下DFS更新每个点。
对于每个要求答案的串，在SAM上走一遍并累加所有经过节点的更新后的val即可。
求答案的时候因为不能存串，so用个链表/vector存下所有经过点来。
我并不想看100+行的SA。。
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;//∑len <= 1e5 ?

struct Suffix_Automaton
{
	int n,K,las,tot,fa[N],son[N][26],len[N],cnt[N],bef[N],Enum,H[N],nxt[N],to[N];//parent树空间是2n啊 
	LL val[N];
	char s[N>>1];
	std::vector<int> v[N>>1];

	void Init(int nn){
		n=nn, scanf("%d",&K), las=tot=1;
	}
	inline void AddEdge(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	void Insert(int now,int c)
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
				int nq=++tot;
				len[nq]=len[p]+1, bef[nq]=bef[q], cnt[nq]=cnt[q];
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
		v[now].push_back(np);
		for(; bef[np]!=now&&np; np=fa[np])
			++cnt[np], bef[np]=now;
	}
	void Build(int now)
	{
		scanf("%s",s), las=1;//las=1啊！ 
		for(int i=0,l=strlen(s); i<l; ++i)
			Insert(now,s[i]-'a');
	}
	void DFS(int x)
	{
		val[x]+=val[fa[x]];
		for(int i=H[x]; i; i=nxt[i]) DFS(to[i]);
	}
	void Solve()
	{
		for(int i=2; i<=tot; ++i)
		{
			AddEdge(fa[i],i);
			if(cnt[i]<K) val[i]=0;
			else val[i]=len[i]-len[fa[i]];
		}
		DFS(1);
		for(int i=1; i<=n; ++i)
		{
			LL res=0;
			for(int j=0,l=v[i].size(); j<l; ++j)
				res+=val[v[i][j]];
			printf("%lld ",res);
		}
	}
}sam;

int main()
{
	int n; scanf("%d",&n), sam.Init(n);
	for(int i=1; i<=n; ++i) sam.Build(i);
	sam.Solve();
	return 0;
}
