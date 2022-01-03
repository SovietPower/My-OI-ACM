/*
73240kb	2496ms
SAM求字符串的最小循环表示。 
因为从根节点出发可以得到所有子串，所以每次找字典序最小的一个出边走即可。因为长度问题把原串再拼接在后面一次。
需要用map存转移。复杂度O(nlogn)。
当然还有O(n)的最小表示法。
*/
#include <map>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(3e5+5)*4;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Suffix_Automaton
{
	int n,s[N],las,tot,fa[N],len[N];
	std::map<int,int> son[N];

	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=len[p]+1;
		for(; p&&!son[p].count(c); p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, son[nq]=son[q];
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		n=read(), las=tot=1;
		for(int i=1; i<=n; ++i) Insert(s[i]=read());
		for(int i=1; i<=n; ++i) Insert(s[i]);
	}
	void Solve()
	{
		std::map<int,int>::iterator it;
		for(int i=1,p=1; i<=n; ++i)
			it=son[p].begin(), p=it->second, printf("%d ",it->first);//别混了map的first(转移)与second(son)啊 
	}
}sam;

int main()
{
	sam.Build(), sam.Solve();
	return 0;
}
