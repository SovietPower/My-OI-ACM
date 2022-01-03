//1660ms	229.72MB
//靠出现次数大于1没判。。我说呢。。
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=(1e6+5)*2;

struct Suffix_Automaton
{
	int tot,las,fa[N],len[N],son[N][26],right[N],A[N],tm[N];
	char s[N>>1];

	void Insert(int c)
	{
		int np=++tot,p=las; len[las=np]=len[p]+1;
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
		right[np]=1;
	}
	void Solve()
	{
		scanf("%s",s+1);
		int l=strlen(s+1); tot=las=1;
		for(int i=1; i<=l; ++i) Insert(s[i]-'a');

		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=l; ++i) tm[i]+=tm[i-1];
		for(int i=tot; i; --i) A[tm[len[i]]--]=i;

//		for(int p=1,i=1; i<=l; ++i) ++right[p=son[p][s[i]-'a']];
		for(int i=tot,x=A[i]; i; --i,x=A[i]) right[fa[x]]+=right[x];
		long long res=0;
		for(int i=2; i<=tot; ++i)
			if(right[i]>1) res=std::max(res,1ll*right[i]*len[i]);
		printf("%lld",res);
	}
}sam;

int main()
{
	sam.Solve();
	return 0;
}
