/*
483MS	1868K
$Description$ 
将$1,2,\cdots,n(n\leq 300)$依次入栈/出栈，并满足$m(m\leq 90000)$个形如$x$要在$y$之前出栈的限制，问合法的出栈序列有多少种。
$Solution$
没有限制就是个卡特兰数，但有了限制就要考虑好好DP了。。
序列的入栈&出栈顺序可以构成一棵二叉树，且每一棵子树中的点一定比该子树的根节点出栈早。
$f[i][j]$表示子树根节点为$i$，其中的点是$i\sim j$，$i+1\sim j$都比$i$出栈早。初始为:$f[i][i]=1$.
无限制的DP方程就是: $$f[i][j]=\sum_{k=i+1}^jf[i][k-1]*f[k][j]$$ 
(这个是倒着枚举$i$的)
如果有限制，直接在DP完$f[i][]$后把非法的$f[i][]$设成0就行了。。
如果$j$要在$k$前出栈($j<k$)，那么$f[j][k],f[j][k+1],\cdots$都是非法的($f[][]$当然是处理小的那个了)。
在$j>k$时，$f[k][1],\cdots,f[k][j-1]$是非法的。
最后的答案应是$f[0][n]$.
注意如果限制有$i$在$i$前，那么直接0。
好像可以在$f[][]$上差分做，不看了。。https://ksmeow.moe/numbers_hdu5181_sol/
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
const int N=305;

int n,L[N],R[N],f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int T=read(),m; bool flag;
	while(T--)
	{
		flag=0;
		n=read(),m=read();
		for(int i=0; i<=n; ++i) L[i]=0,R[i]=n+1;
		for(int x,y,i=1; i<=m; ++i)
		{
			x=read(),y=read();
			if(x<y) R[x]=std::min(R[x],y);
			else if(x>y) L[y]=std::max(L[y],x);
			else flag=1;
		}
		if(flag) {puts("0"); continue;}
		memset(f,0,sizeof f);
		for(int i=n; ~i; --i)
		{
			f[i][i]=1;
			for(int j=i+1; j<=n; ++j)
				for(int k=i+1; k<=j; ++k)
					(f[i][j]+=1ll*f[i][k-1]*f[k][j]%mod)%=mod;
			for(int j=1; j<L[i]; ++j) f[i][j]=0;
			for(int j=R[i]; j<=n; ++j) f[i][j]=0;
		}
		printf("%d\n",f[0][n]);
	}
	return 0;
}
