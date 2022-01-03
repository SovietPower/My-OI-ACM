/*
748MS	2332Kb
$Description$
给定$m$。求$m$最少可由多少个形如$3n(n-1)+1\ (n\geq 1)$的数构成。
$T$组数据。$m\leq10^9,\ T\leq10^4$。
$Solution$
> **任何一个数可由最多三个三角数/三角形数构成**。

最少个构成可以考虑下三角形数（记为$A_n$），而$3n(n-1)+1=6\times\frac{n(n-1)}{2}+1=6A_n+1$。
假设答案为$k$，有$m=6(A_1+A_2+...+A_k)+k$。

* $k\geq 3$时，$\sum A_i$可表示任意数，有$k=(m-1)\%6+1+6n\ (n\geq 0)$，所以答案即$(m-1)\%6+1$，且有$(m-1)\%6+1\geq 3$。
* $(m-1)\%6+1\lt 3$时，有$k=1或2$，直接特判$1或2$是否可行，如果不可行那$k+6\geq 3$一定可行。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e4+5,INF=1e9;

int A[N];//19000
std::unordered_map<int,int> f;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int i=1; (A[i]=3*i*(i-1)+1)<=INF; ++i) f[A[i]]=1;

	for(int T=read(); T--; )
	{
		int n=read(),k=(n-1)%6+1;
		if(k==1) printf("%d\n",f.count(n)?1:7); //不要写f[n]。。会加到map/unordered_map里（我为什么才发现这点） 
		else if(k==2)
		{
			bool fg=0;
			for(int i=1,lim=n/2; A[i]<=lim; ++i)
				if(f.count(n-A[i])) {fg=1; break;} //同上别写f[n-A[i]] 
			printf("%d\n",fg?2:8);
		}
		else printf("%d\n",k);
	}

	return 0;
}
