/*
46ms	10100KB
从后往前对最后一个字符串$p_n$的前后缀是否相同讨论一下。具体看[这里](https://www.cnblogs.com/mjtcn/p/10424484.html)吧不想写了= =
可以像上面那样递归去做，也可以从$p_1$往后递推。因为用到的是某个字符的最长连续子串，所以令$f[i][j]$表示$p_1\cdot p_2\cdot...\cdot p_i$中$j$字符的最长连续长度，转移时判一下$p_{i+1}$是否都是由$j$字符构成的，是就用$len\times(f[i][j]+1)+f[i][j]$更新，否则用$1+j字符的最长前后缀$更新（$p_{i-1}$中含$j$字符才能转移）。
复杂度$O(\sum|p_i|)$（递归）或$O(26\sum|p_i|)$（递推）（然而前者常数比较大）。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define S 26
typedef long long LL;
const int N=1e5+5;

int f[N][S],pre[S],suf[S];
char s[N];

void Solve(int *f)
{
	scanf("%s",s+1);
	int l=strlen(s+1);
	for(int j=0; j<S; ++j)
	{
		int mx=0;
		for(int i=1,cnt=0; i<=l; ++i)
			if(s[i]==j+'a') mx=std::max(mx,++cnt);
			else cnt=0;
		f[j]=mx, pre[j]=suf[j]=0;
		for(int i=1; i<=l; ++i)
			if(s[i]==j+'a') ++pre[j];
			else break;
		for(int i=l; i; --i)
			if(s[i]==j+'a') ++suf[j];
			else break;
	}
}

int main()
{
	int n; scanf("%d",&n);
	Solve(f[1]);
	for(int i=2; i<=n; ++i)
	{
		Solve(f[i]);
		int l=strlen(s+1);
		for(int j=0; j<S; ++j)
			if(f[i-1][j])
				if(pre[j]!=l) f[i][j]=std::max(f[i][j],pre[j]+suf[j]+1);
				else f[i][j]=std::max(f[i][j],l*(f[i-1][j]+1)+f[i-1][j]);
	}
	int ans=0;
	for(int i=0; i<S; ++i) ans=std::max(ans,f[n][i]);
	printf("%d\n",ans);

	return 0;
}
