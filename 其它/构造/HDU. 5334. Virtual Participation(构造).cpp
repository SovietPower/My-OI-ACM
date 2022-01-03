/*
124MS	1384Kb
$Description$
给定$K$。构造一个字符集大小没有限制、长度不超过$10^5$的字符串，使得不同的子串个数恰好为$K$。
$K\leq 10^9$。
$Solution$
**做法1：**
考虑简单的$\begin{matrix}\underbrace{111...1}\\a_1个\end{matrix}\begin{matrix}\underbrace{222...2}\\a_2个\end{matrix}\begin{matrix}\underbrace{333....}\\a_3个..\end{matrix}$，$\sum a_i=n$，则不同子串数为：$C_{n+1}^2-\sum_{a_i\geq 2} C_{a_i}^2$。
不妨先求出最小的$n$使得$C_{n+1}^2\geq K$。令$x=C_{n+1}^2-K$，有一个结论是**“任何一个数可由最多三个三角数构成”**，所以从大到小找出构成$x$的$C_{a_i}^2\ (a_i\geq 2)$即可。剩下$L-\sum a_i$的数直接补$4\ 5\ 6\ 7\ 8...$。
网上有个题解是从小到大找，似乎是会超过三个的（不满足结论）。

细节：$K$较小如$K=4$时（实测只有$K=4$或$K=16$），$\sum a_i$会大于$n$（因为$C_n^2$增长不够快还是？）。所以$K$较小时需特判，直接输出$K$个$1$就ok。

**[做法2](https://blog.csdn.net/jtjy568805874/article/details/47174185)：**
直接考虑构造$\begin{matrix}\underbrace{111...1}\\a个\end{matrix}\begin{matrix}\underbrace{222...2}\\b个\end{matrix}\begin{matrix}\underbrace{111...1}\\c个\end{matrix}$，令$a\geq c$，则子串数为$ab+bc+ac+a+b$。
条件为$ab+bc+ac+a+b=K$即$(a+c+1)(b+c+1)=K+(c+1)^2$，枚举$c+1$和$a$，保证$a\geq c$且$a+b+c\leq 10^5$即可找到解。
$K$较大的时候，这个枚举效率似乎就不如**做法1**了。
*/
#include <bits/stdc++.h>
#define pc putchar
#define pb emplace_back
typedef long long LL;
const int N=1e5+5;

int main()
{
	int K;
	while(~scanf("%d",&K))
	{
		if(K<=1000)//(K==4||K==16)
		{
			printf("%d\n",K);
			for(int i=1; i<=K; ++i) printf("%d%c",1," \n"[i==K]);
			continue;
		}
		int l=1,r=44721,mid;
		while(l<r)
			if(mid=l+r>>1,mid*(mid+1)/2>=K) r=mid;
			else l=mid+1;

		int n=l,x=n*(n+1)/2-K;
		std::vector<int> vec;
		while(x)
		{
			int l=1,r=sqrt(2*x)+1,mid,ans=1;
			while(l<=r)
				if(mid=l+r>>1,mid*(mid-1)/2<=x) ans=mid,l=mid+1;
				else r=mid-1;
			vec.pb(ans), x-=ans*(ans-1)/2;
		}
		int now=1,f=0; printf("%d\n",n);
		for(auto t:vec)
		{
			for(int i=1; i<=t; ++i)
				if(f) printf(" %d",now);
				else f=1, printf("%d",now);
			++now, n-=t;
		}
		while(n--)
			if(f) printf(" %d",now++);
			else f=1, printf("%d",now++);
		pc('\n');
	}

	return 0;
}
