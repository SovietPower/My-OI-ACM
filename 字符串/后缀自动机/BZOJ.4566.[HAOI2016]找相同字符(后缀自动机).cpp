/*
52776kb	1500ms
$Description$
给定两个字符串，求它们有多少个相同子串。相同串的位置不同算多个。
$Solution$
对一个串建SAM。因为要统计不同位置个数，所以匹配一个点的贡献为(val[i]=(len[i]-len[fa[i]])*|right[i]|)+val[fa[i]]+val[fa[fa[i]]]...
然后另一个串在SAM上走。维护当前已匹配的长度l，则当前贡献为val[fa[i]]+(l-len[fa[i]])*|right[i]|。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],A[N],tm[N],right[N];
	LL val[N];
	char s[N];

	void Insert(int c)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, right[np]=1;
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
	void Build()
	{
		las=tot=1;
		scanf("%s",s); int l=strlen(s);
		for(int i=0; i<l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];
		for(int i=1; i<=tot; ++i) val[i]=1ll*(len[i]-len[fa[i]])*right[i];
		for(int i=2,x=A[2]; i<=tot; x=A[++i]) val[x]+=val[fa[x]];
	}
	void Query()
	{
		scanf("%s",s);
		LL ans=0;
		for(int p=1,now=0,c,i=0,l=strlen(s); i<l; ++i)
		{
			if(son[p][c=s[i]-'a']) ++now, p=son[p][c];
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
			ans+=val[fa[p]]+1ll*(now-len[fa[p]])*right[p];
		}
		printf("%lld",ans);
	}
}sam;

int main()
{
	sam.Build(), sam.Query();
	return 0;
}
