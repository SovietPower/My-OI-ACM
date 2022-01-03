/*
80ms	25MB
将模式串s复制一遍，在母串的SAM上匹配，记录以每个位置作为后缀所能匹配的最大长度mx[i]。
如果mx[i]>=l（模式串长），那么它在母串里作为一个"循环相似旋律"出现过。
从该处匹配点往上跳，找到离parent树根节点最近的满足len[p]>=l的位置p，出现次数就是|right[p]|。
模式串复制后可能得到两个相同的循环串，不能重复统计，所以要打标记。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;

struct Suffix_Automaton
{
	int las,tot,fa[N],son[N][26],len[N],A[N],tm[N],right[N],vis[N];
	char s[N];

	Suffix_Automaton() {tot=las=1;}
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
		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;
		for(int i=tot,x=A[i]; i; x=A[--i]) right[fa[x]]+=right[x];
	}
	int Calc(int p,int l,int id)
	{
		for(; len[fa[p]]>=l; p=fa[p]);
		return vis[p]==id?0:(vis[p]=id,right[p]);
	}
	void Query()
	{
		static int Index=0;
		++Index;
		scanf("%s",s+1); int l=strlen(s+1);
		for(int i=1; i<=l; ++i) s[i+l]=s[i];
		int ans=0;
		for(int c,now=0,p=1,i=1; i<=l<<1; ++i)
		{
			if(son[p][c=s[i]-'a']) p=son[p][c], ++now;
			else
			{
				for(; p&&!son[p][c]; p=fa[p]);
				if(!p) p=1, now=0;
				else now=len[p]+1, p=son[p][c];
			}
			if(now>=l) ans+=Calc(p,l,Index);
		}
		printf("%d\n",ans);
	}
}sam;


int main()
{
	sam.Build();
	int n; scanf("%d",&n);
	while(n--) sam.Query();
	return 0;
}
