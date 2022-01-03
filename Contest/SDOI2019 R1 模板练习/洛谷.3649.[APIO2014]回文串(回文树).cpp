//110ms	34876KB
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

struct PAM
{
	int tot,las,fail[N],len[N],val[N],son[N][26];
	char s[N];
	PAM() {tot=1, las=0, fail[0]=1, len[1]=-1, s[0]='$';}
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
		for(int x=tot; x>1; --x)
			ans=std::max(ans,1ll*val[x]*len[x]), val[fail[x]]+=val[x];
		printf("%lld\n",ans);
	}
}pam;

int main()
{
	pam.Solve();
	return 0;
}
