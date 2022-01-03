/*
77ms	2000KB
$Description$
令$S(n)$表示将$S$的十进制位重排序后的数，如$S(324)=234$，求$\sum_{i=1}^nS(i)$。
$n\leq 10^{700}$。
$Solution$
一个简单的做法是枚举$1\sim 9$每个数$k$，DP时维护$=k$、$\gt k$的数位各有多少个。复杂度是$O(100n^3)$。
观察一下$S$的形式，比如：$112333=111111+1111+111$，可以发现数位$1$的贡献是$\begin{matrix}\underbrace{11...1}\\6个1\end{matrix}$，数位$2$的贡献是$\begin{matrix}\underbrace{11...1}\\4个1\end{matrix}$...也就是$k$的贡献是$\begin{matrix}\underbrace{11...11}\\cnt个1\end{matrix}$，其中$cnt$是$\geq k$的数位个数。
所以DP时只需要维护$\geq k$的数位有多少个，求出方案数后乘$\begin{matrix}\underbrace{11...11}\\cnt个1\end{matrix}$就是贡献。
这样复杂度$O(100n^2)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=705;

char s[N];
int f[N][N];
LL val[N];

int DFS(int len,bool lim,int cnt,const int K)
{
	if(!lim && ~f[len][cnt]) return f[len][cnt];
	if(!len) return val[cnt];
	LL res=0;
	for(int i=0,up=lim?(s[len]-48):9; i<=up; ++i)
		res+=DFS(len-1,lim&&i==up,cnt+(i>=K),K);
	res%=mod;
	if(!lim) return f[len][cnt]=res;
	return res;
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	std::reverse(s+1,s+1+n);
	int t=1;
	for(int i=1; i<=n; ++i) val[i]=t, t=(t*10ll+1)%mod;

	LL ans=0;
	for(int k=1; k<=9; ++k)
		memset(f,0xff,sizeof f), ans+=DFS(n,1,0,k);
	printf("%lld\n",ans%mod);

	return 0;
}
