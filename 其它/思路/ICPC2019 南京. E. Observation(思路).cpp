/*
1261ms	20MB
$Description$
令$f(d)$表示空间中到原点距离为$d$的整点个数，给定$L,R,k,p$，求
$$\sum_{d=L}^Rf(d)\ \mathbb{xor}\ k\mod p$$

$L,R\leq 10^{13},R-L+1\leq 10^6$。

$Solution$
必然是找规律。[OEIS](http://oeis.org/A016725)可以直接找到规律，或者打表。

$f$都是$6$的倍数，令$g(x)=\frac{f(x)}{6}$，可以发现$g(x)$为积性函数，即$g(\prod p_i^{k^i})=\prod g(p_i^{k_i})$。
列出$g(p)\ （p为质数）$可以知道，若$p\%4=1$，$g(p)=p$；若$p\%4=3$，$g(p)=p+2$。
再看$g(p^2)\ （p为质数）$可以知道，若$p\%4=1$，$g(p^2)=p^2$；若$p\%4=3$，$g(p^2)=p^2+h(p)$，其中$h(p)=8k$，$k$是$p$为第几个$\%4=3$的质数![/whl](https://img2020.cnblogs.com/blog/1143196/202009/1143196-20200905001111605-807403868.png)。
考虑如何更好地表示$h(p)$。
由OEIS结论可发现$(p-1)h(p)=2(p^2-1)$，即$g(p^2)=p^2+\frac{2(p^2-1)}{p-1}$，且该结论对$p^k$同样成立。
所以
$$f(p^k)=\begin{cases}1,&p=2\\p^k,&p\%4=1\\p^k+\frac{2(p^k-1)}{p-1},&p\%4=3\end{cases}$$

求出$\sqrt n$以内的质数，对每个数就可以$O(\log n)$分解质因数求了。
复杂度$O(Tn\log n)$。

PS：注意`&`的运算优先级比`==`低。。`&`运算要加括号！
$ans$求和过程中最多是$10^6$个$2\times 10^{13}$的数，所以还是要取模！
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=3162300,M=1e6+5;
const LL LIM=2e18;

int cnt,P[230000];
bool not_P[N];

inline LL read()
{
	LL now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Init(const int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt && i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Solve()
{
	static LL A[M],f[M];

	LL L=read(),R=read(),K=read(),mod=read(),ans=0;
	if(!L) ans+=K, ++L;
	int n=(int)(R-L+1);
	for(int i=1; i<=n; ++i) A[i]=i+L-1,f[i]=1;

	for(int i=1,lim=::cnt; i<=lim&&P[i]<=R; ++i)
	{
		int p=P[i];
		LL now=L/p*p; now<L&&(now+=p);
		for(now-=L-1; now<=n; now+=p)
		{
			LL pk=1;
			while(!(A[now]%p)) A[now]/=p, pk*=p;
			if(p==2) pk=1;
			else if((p&3)==3) pk+=2*(pk-1)/(p-1);
			f[now]*=pk;
		}
	}
	for(int i=1; i<=n; ++i)
	{
		if((A[i]&3)==3) f[i]*=(A[i]+2);//本身/剩下为大质数 
		else f[i]*=A[i];
		ans+=((f[i]*6)^K)%mod;
		ans>=LIM&&(ans%=mod);//取模！ 
	}
	printf("%lld\n",ans%mod);
}

int main()
{
	Init(N-2);
	for(int T=read(); T--; Solve());

	return 0;
}
