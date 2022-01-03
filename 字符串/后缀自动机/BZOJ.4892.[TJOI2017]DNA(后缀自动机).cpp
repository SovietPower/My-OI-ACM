/*
9224kb	1624ms
$Description$
给出两个串$S,T$，求$T$在$S$中出现了多少次。出现是指。可以有$3$次（$3$个字符）不匹配（修改使其匹配）。
$Solution$
一个套路的做法是构造多项式，对每个字符c单独考虑，$f[i]=[S[i]可匹配c],g[i]=[T[i]==c]$。
然后$F=f*g$，可以得到每个位置往后长m的串中有多少个位置S,T都匹配了c。如果某个位置匹配字符数>=m-3，则以它为左端点的串可行。
FFT/NTT实现，常数好也许能过。
SA做法：枚举S的每个位置i，设当前匹配T匹配到j，得到两个串的ht数组后我们可以$O(1)$求出LCP(suf[i],suf[j])，直接j+=LCP就行了。
如果某个位置不匹配，可以至多用3次机会直接跳过去。所以实际枚举j的次数只有5。
复杂度$O(Tn\log n)$。
SAM做法：得到parent树后，直接在上面DFS，如果能匹配则走，不能匹配则用一次次数。走了m步则加上该点的贡献(出现过多少次)。
复杂度$O(Tn)$。
还有某种神奇的Hash做法。。好像复杂度比较优。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

struct Suffix_Automaton
{
	int n,Ans,tot,las,son[N][4],fa[N],len[N],cnt[N],tm[N],A[N],ref[233];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, cnt[np]=1;
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
		tot=las=1;
		ref['A']=0, ref['T']=1, ref['G']=2, ref['C']=3;
		memset(tm,0,sizeof tm);//! 你前缀和了→_→
		memset(cnt,0,sizeof cnt), memset(son,0,sizeof son);

		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(ref[s[i]]);
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[i]; i; x=A[--i]) cnt[fa[x]]+=cnt[x];
	}
	void DFS(int x,int use,int l)
	{
		if(l==n) return (void)(Ans+=cnt[x]);
		for(int i=0; i<4; ++i)
			if(son[x][i])
				if(ref[s[l]]==i) DFS(son[x][i],use,l+1);
				else if(use<3) DFS(son[x][i],use+1,l+1);
	}
	void Query()
	{
		scanf("%s",s), n=strlen(s);
		Ans=0, DFS(1,0,0), printf("%d\n",Ans);
	}
}sam;

int main()
{
	int T; scanf("%d",&T);
	while(T--) sam.Build(), sam.Query();
	return 0;
}
