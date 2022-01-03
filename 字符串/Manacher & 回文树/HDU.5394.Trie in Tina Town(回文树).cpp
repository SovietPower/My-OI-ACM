/*
1092MS	151236K(fread) <- 7784MS	149280K
$Description$
给定一棵$Trie$。求$Trie$上所有回文串 长度乘以出现次数 的和。这里的回文串只能是从上到下的一条链。
节点数$n\leq 2\times 10^6$，字符集为`a,b,c,d`。

$Solution$
如果不是树，就是回文树模板。对于树，DFS $x$的每个儿子的时候都用在$x$处的$las$即可，也就是按深度存一个$las$数组，每次用$las[dep-1]$做$las$去插入即可。（也可以回溯的时候直接删节点）
每次插入产生的贡献怎么算。。？
令$ans[x]$表示$x$节点（状态）处的贡献，插入后到了$x$节点答案就加上$ans[x]$。
对于新建的$x$节点，$ans[x]=len[x]+ans[fail[x]]$（除了新产生的串，剩下的贡献就是$fail[x]$的状态的贡献了）。

加了`fread`之后惊呆了= =拿到了hdu上第一个rank1= =
果然不是我算法效率问题。。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 2000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e6+6;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

struct PAM
{
	int s[N],H[N],nxt[N],tot,las[N],son[N][4],len[N],fail[N];
	LL Ans,ans[N];
	char tmp[N];
	inline void Init()
	{
		las[0]=tot=1, fail[0]=1, len[1]=-1, s[0]=-1;
		memset(son[0],0,sizeof son[0]), memset(son[1],0,sizeof son[1]);
	}
	inline int Find(int x,int n)
	{
		while(s[n]!=s[n-len[x]-1]) x=fail[x];
		return x;
	}
	void Insert(int c,int n)
	{
		s[n]=c;
		int p=Find(las[n-1],n);
		if(!son[p][c])
		{
			int np=++tot;
			memset(son[np],0,sizeof son[np]);
			fail[np]=son[Find(fail[p],n)][c];
			son[p][c]=np, len[np]=len[p]+2;
			ans[np]=ans[fail[np]]+len[np];
		}
		Ans+=ans[las[n]=son[p][c]];
	}
	void DFS(int x,int dep)
	{
		for(int v=H[x]; v; v=nxt[v])
			Insert(tmp[v]-'a',dep), DFS(v,dep+1);
	}
	void Solve()
	{
		Init();
		const int n=read();
		for(int i=1; i<=n; ++i)
		{
			while(!isalpha(tmp[i]=gc()));
			int fa=read();
			nxt[i]=H[fa], H[fa]=i;
		}
		Ans=0, DFS(0,1), printf("%lld\n",Ans);
		memset(H,0,n+1<<2);
	}
}pam;

int main()
{
	for(int T=read(); T--; pam.Solve());
	return 0;
}
