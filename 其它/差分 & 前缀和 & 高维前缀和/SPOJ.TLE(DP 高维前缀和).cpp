/*
$Description$
给定长为$n$的数组$c_i$和$m$，求长为$n$的序列$a_i$个数，满足：$c_i\not\mid a_i,\quad a_i\&a_{i+1}=0$。
$n\leq 50，m\leq 15，0\leq a_i<2^m，0<c_i\leq 2^m$.
$Solution$
DP。限制都是与值有关的，所以令$f_i$表示以$i$这个数结尾的序列$a$的个数。
转移即$f_i=\sum_{j,i\&j=0}f_j$。$i\&j=0$需要$3^n$枚举补集的子集，但是还可以写成$i\&(\sim j)=i$，即$i$是$\sim j$的子集。所以先把上一次的DP数组下标反转，就可以用高维前缀和优化枚举超集了。
（或者枚举子集的补集，就把DP数组反转，即令$f_i=f_{\sim i}，$然后枚举$i$的子集更新$f_i$）
对于$c_i\not\mid a_i$的限制，每次转移完将下标为$c_i$倍数的$f_i$置为$0$即可。
这样转移$n$次就可以了。复杂度$O(nm2^m)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 1000000000
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=(1<<15)+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	static int f[N],tmp[N];

	for(int T=read(); T--; )
	{
		int n=read(),m=read(),lim=(1<<m)-1;
		memset(f,0,sizeof f);
		f[0]=1;
		for(int i=1; i<=n; ++i)
		{
//			for(int s=0; s<=lim; ++s) tmp[s^lim]=f[s];
//			for(int s=0; s<=lim; ++s) f[s]=tmp[s];
			for(int s=0; s<=lim; s+=2) std::swap(f[s],f[s^lim]);
			for(int j=0; j<m; ++j)
				for(int s=0; s<=lim; ++s)
					if(!(s>>j&1)) Add(f[s],f[s|(1<<j)]);
			int ci=read();
			for(int j=0; j<=lim; j+=ci) f[j]=0;
		}
		LL ans=0;
		for(int i=0; i<=lim; ++i) ans+=f[i];
		printf("%d\n",(int)(ans%mod));
	}
	return 0;
}
