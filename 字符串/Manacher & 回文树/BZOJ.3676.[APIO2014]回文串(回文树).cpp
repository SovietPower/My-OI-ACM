/*
35100kb	708ms
回文树模板题。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

struct Palindromic_Tree
{
	int las,tot,son[N][26],len[N],fail[N],val[N];
	char s[N];

	Palindromic_Tree() {tot=1, fail[0]=1, len[1]=-1, s[0]='$';}
	inline int Find(int x,int n)
	{
		while(s[n-len[x]-1]!=s[n]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		int p=Find(las,n);
		if(!son[p][c])
		{
			int np=++tot; fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
		}
		++val[las=son[p][c]];
	}
	void Solve()
	{
		scanf("%s",s+1); int n=strlen(s+1);
		for(int i=1; i<=n; ++i) Insert(s[i]-'a',i);
		LL ans=0;
		for(int i=tot; i>1; --i)
			val[fail[i]]+=val[i], ans=std::max(ans,1ll*val[i]*len[i]);
		printf("%lld\n",ans);
	}
}T;

int main()
{
	T.Solve();
	return 0;
}
