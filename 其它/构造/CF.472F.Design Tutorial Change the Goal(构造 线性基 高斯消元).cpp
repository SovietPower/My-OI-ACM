/*
46ms	3100KB
$Description$
给定两个长为$n$的数组$x_i,y_i$。每次你可以选定$i,j$，令$x_i=x_i\ \mathbb{xor}\ x_j$（$i,j$可以相等）。要求若干次操作后使得$x$变成$y$，输出方案。操作次数不能多于$10^6$，无解输出$-1$。
$n\leq10^4,\ 0\leq x_i,y_i\leq10^9$。
$Solution$
考虑异或的两个基本性质：
1. 异或是可逆的，逆运算就是它本身。
2. 可以交换两个数：`a^=b,b^=a,a^=b`。
考虑线性基。构造出$x$的线性基，如果$y$中存在元素不能被$x$表示出来，那么无解。
我们发现对于不在线性基中的元素$x_i$，得到$y_i$是很容易的，只需要求一下在线性基中$\mathbb{xor}$出$y_i$需要异或哪些数。
对于在线性基中的元素，设有$t$个，它们之间不是很好做。把$t$个$x_i$对应的$y_i$需要$\mathbb{xor}$哪些基写成一个$t$位二进制数。由第二个性质，我们可以高斯消元将这个$t\times t$的矩阵消成一个上三角矩阵，这样从高位到低位做不同基之间就互不影响了，我们可以$\mathbb{xor}$出这个矩阵。
而由第一个性质，将高斯消元的过程反过来操作这个上三角矩阵，就可以还原回$y$数组。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define BIT 29
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=10005,M=BIT+2;

int x[N],y[N],base[M],is_base[N],b[M],sx[M],sy[N];
std::vector<pr> ans,opt;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) x[i]=read();
	for(int i=1; i<=n; ++i) y[i]=read();
	for(int i=1; i<=n; ++i)
	{
		is_base[i]=-1;
		for(int j=BIT,s=0; ~j; --j)
			if(x[i]>>j&1)
				if(base[j]) x[i]^=x[base[j]], s^=sx[j];
				else
				{
					is_base[i]=j, base[j]=i, sx[j]=s|(1<<j);
					break;
				}
	}
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		int s=0;
		for(int j=BIT; ~j; --j)
			if(y[i]>>j&1)
				if(base[j]) y[i]^=x[base[j]], s^=sx[j];
				else return puts("-1"),0;
		if(~is_base[i]) {b[cnt]=i, sy[cnt++]=s; continue;}//可以等于0啊。。
		ans.push_back(mp(i,i));
		for(int j=BIT; ~j; --j) if(s>>j&1) ans.push_back(mp(i,base[j]));
	}
	for(int i=0; i<cnt; ++i)
	{
		int s=sy[i]; sy[i]=0;
		for(int j=0; j<cnt; ++j) if(s>>is_base[b[j]]&1) sy[i]|=1<<j;
	}
	for(int i=0; i<cnt; ++i)
	{
		if(!(sy[i]>>i&1))
			for(int j=i+1; j<cnt; ++j)
				if(sy[j]>>i&1)
				{
					opt.push_back(mp(b[i],b[j]));
					opt.push_back(mp(b[j],b[i]));
					opt.push_back(mp(b[i],b[j]));
					std::swap(sy[i],sy[j]);
					break;
				}
		if(sy[i]>>i&1)
			for(int j=i+1; j<cnt; ++j)
				if(sy[j]>>i&1)
					opt.push_back(mp(b[j],b[i])), sy[j]^=sy[i];
	}
	for(int i=0; i<cnt; ++i)
	{
		if(!(sy[i]>>i&1)) ans.push_back(mp(b[i],b[i]));
		for(int j=i+1; j<cnt; ++j)
			if(sy[i]>>j&1) ans.push_back(mp(b[i],b[j]));
	}
	std::reverse(opt.begin(),opt.end());
	for(auto v:opt) ans.push_back(v);
	printf("%d\n",ans.size());
	for(auto v:ans) printf("%d %d\n",v.first,v.second);

	return 0;
}
