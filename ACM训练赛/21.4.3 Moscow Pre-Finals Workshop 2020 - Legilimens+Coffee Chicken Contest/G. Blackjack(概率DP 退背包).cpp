/*
358ms	4000KB
$Description$
给定$a,b,n$和$n$个数。从$n$个数中依次取一个数，直到当前取的数的和$sum\gt a$。若此时$sum>b$则输，否则赢。求$n$个数随机排列的情况下赢的概率。
$n,a,b\leq 500$。
$Solution$
问题在于如何表示任意一种排列，感觉是个套路。
$f[i][j][k]$表示前$i$个数，选了其中$j$个，选的数的和为$k$的概率。则当前排列中含前$i$个数的$j$个数。所以：
$$f[i][j][k]=f[i-1][j][k]+f[i-1][j-1][k-A[i]]*\frac{j}{n-(j-1)}$$

注意要乘$j$！因为不乘$j$还是按顺序取的，不表示所有排列，乘$j$即在运算中乘了$j!$，表示取了$j$个数的所有排列的情况。

注意这是个加法的背包，所以可以[退背包](https://www.cnblogs.com/SovietPower/p/9826829.html#b-%E9%80%89%E6%8B%A9%E9%A2%98dp-%E6%9C%9F%E6%9C%9B-%E9%80%80%E8%83%8C%E5%8C%85)，即：
$$f[i-1][j][k]=f[i][j][k]-f[i-1][j-1][k-A[i]]*\frac{j}{n-(j-1)}$$

枚举第$i$个数，令它作为最后选中的数，然后退背包使它的贡献从$f[n]$中删去。
那么$A_i$作为最后选中的数且合法的情况即为：
$$\sum_{j=0}^{n-1}\sum_{k,k<a\&k+A_i\in(a,b]}\frac{f'[j][k]}{n-j}$$

注意要除以$n-j$！即当前已选了$j$个限定$i$为最后一个的概率。
系数的细节也太容易漏了。

复杂度$O(n^3)$。

**PS：**CF上除法还挺快的... 不需要存$\frac1i$的数组变成乘法。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=505;

int A[N];
double f[N][N],g[N][N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read(),a=read(),b=read();
	for(int i=1; i<=n; ++i) A[i]=read();

	f[0][0]=1;
	for(int i=1,sum=0; i<=n; ++i)
	{
		sum=std::min(sum+A[i],b);
		for(int j=i,t=A[i]; j; --j)
			for(int k=sum; k>=t; --k)
				f[j][k]+=f[j-1][k-t]*j/(n-j+1);
	}
	double ans=0;
	for(int i=1; i<=n; ++i)
	{
		memcpy(g,f,sizeof f);
		for(int j=1,t=A[i]; j<n; ++j)
			for(int k=t; k<=b; ++k)
				g[j][k]-=g[j-1][k-t]*j/(n-j+1);
		for(int j=0,t=A[i]; j<n; ++j)
			for(int k=0; k<=a && k+t<=b; ++k)
				if(k+t>a) ans+=g[j][k]/(n-j);
	}
	printf("%.10f\n",ans);

	return 0;
}
