/*
7996kb	596ms
下边的不对，要求恰好K个。。那就换一种方式，f定义不变，枚举填什么字符，去更新f并算出有哪些字符串可以匹配某个状态(见code吧...)。
预处理出有哪些字符串在第i位可以转移到某个字符c，dp时&一下状态即可。

错误思路(题意理解错，如果是'?'则无论如何都已匹配): f[i][s]表示当前第i位，匹配的字符串为s集合中的字符串，此时的方案数。
枚举长度、s、每个串，而s最多是C(15,7)=6435种，复杂度OK。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000003)
const int N=(1<<15)+3,L=55;

int n,K,bit[N],f[L][N],match[L][29];
char s[17][L];

int main()
{
	for(int i=1; i<(1<<15); ++i)
		for(int j=i; j; j>>=1) bit[i]+=j&1;
	int T; scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof f), memset(match,0,sizeof match);
		scanf("%d%d",&n,&K);
		for(int i=0; i<n; ++i) scanf("%s",s[i]);

		int len=strlen(s[0]),lim=1<<n;
		for(int i=0; i<len; ++i)
			for(int j=0; j<n; ++j)
				if(s[j][i]=='?') for(int k=0; k<26; ++k) match[i][k]|=(1<<j);//(1<<j)不是j！
				else match[i][s[j][i]-'a']|=(1<<j);//同上.
		f[0][lim-1]=1;
		for(int i=0; i<len; ++i)
			for(int j=0; j<lim; ++j)
				if(f[i][j])
					for(int k=0; k<26; ++k)//枚举下一位填字符k，这只是一种方案，所以是加不是乘！
						(f[i+1][j&match[i][k]]+=f[i][j])%=mod;
		int res=0;
		for(int i=0; i<lim; ++i)
			if(bit[i]==K) (res+=f[len][i])%=mod;
		printf("%d\n",res);
	}
	return 0;
}
