/*
0.08s	27M
$Description$
求最多10个串的LCS。
$Solution$
类比上题，对一个串建SAM，我们可以逐串地求出其在每个节点所能匹配的最大长度mx[i]。
对于每个点i，所有串的mx[i]的最小值即为在点i n个串的LCS长度。枚举所有点即可。
这需要把每个点都匹配一遍求mx[]。因为fa[p]是p的上一个后缀，所有(部分)匹配了p一定可以完全匹配fa[p]，而匹配p时不会沿p到根去更新一遍mx[]。
所以每匹配一个串，要按len从大到小(自叶子向根)更新一遍，即如果p(有部分)匹配了，那么mx[fa[p]]就可以更新为len[fa[p]].
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+7;

char s[N>>1];
struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],mx[N],ans[N],tm[N],A[N];
	void Insert(int c)
	{
		int p=las,np=++tot; len[las=np]=ans[np]=len[p]+1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; ans[nq]=len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build(char *s)
	{
		las=tot=1; int l=strlen(s);
		for(int i=0; i<l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
	}
	void Match(char *s)
	{
		memset(mx,0,sizeof mx);
		for(int now=0,p=1,c,i=0,l=strlen(s); i<l; ++i,mx[p]=std::max(mx[p],now))
			if(son[p][c=s[i]-'a']) p=son[p][c], ++now;
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
		for(int x,i=tot; i; --i)
			if(mx[x=A[i]]&&fa[x]) mx[fa[x]]=len[fa[x]];
		for(int i=1; i<=tot; ++i) ans[i]=std::min(ans[i],mx[i]);
	}
	void Query()
	{
		int res=0;
		for(int i=1; i<=tot; ++i) res=std::max(res,ans[i]);
		printf("%d",res);
	}
}sam;

int main()
{
	scanf("%s",s), sam.Build(s);
	while(~scanf("%s",s)) sam.Match(s);
	sam.Query();
	return 0;
}
