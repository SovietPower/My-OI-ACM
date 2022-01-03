/*
$Description$
数轴上有n个骑士，分别位于1,2,3,...,n，它们的移动速度相同，初始移动方向已知。当两个骑士相遇时，各有50%的概率获胜，失败的骑士就死了。
当骑士移动到0,n+1位置时方向会反转。求最右边的骑士最后存活的概率。
$Solution$
题目中速度、时间都是无关紧要的。第n个骑士若要赢，一定是打败了左边所有存活的骑士。
那么设$f[i][j]$表示前i个骑士中有j个骑士存活的概率。
考虑怎么求。第i个骑士如果向左，那它应把前i-1个骑士中k-j个向右的骑士都打败(然后go_die->1/2)，才能剩下j个.
即$f[i][j]=\sum_{k=j}^{i-1}f[i-1][k]*(\frac{1}{2})^{k-j+1}$ 
把$k=j$时的分离出来，可以化简为$$f[i][j]=\frac{1}{2}*(f[i-1][j]+f[i][j+1])$$ 
如果骑士i向右，那么$$f[i][j]=f[i-1][j-1]$$ 
但是如果只有一个骑士向右，还可能是它打败了左边所有骑士，到0点折回的。
所以给每个$f[i][1]+=\sum_{j=1}^{i-1}f[i-1][j]*(\frac{1}{2})^j$ 
即$$(f[i][1]+=\frac{1}{2}*(f[i-1][1]+f[i][2]))=f[i-1][1]+f[i][2]$$ 
$Ans=\sum_{i=1}^{n-1}f[n-1][i]*(\frac{1}{2})^i$，即$$Ans=\frac{f[n][1]}{2}$$ 
注意骑士n是要强制向左走的（本来就是）。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define inv (500000004)
#define mod (1000000007)//除以2全都化为乘逆元(题目要求)，这样也能直接用整数 
const int N=1005;

int n,f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int T=read();
	for(int cas=1; cas<=T; ++cas)
	{
		memset(f,0,sizeof f);
		n=read(), read();
		f[1][1]=1;
		for(int i=2; i<=n; ++i)
		{
			if(read()&&i!=n)
				for(int j=1; j<=i; ++j)
					f[i][j]=f[i-1][j-1];
			else{
				for(int j=i-1; j>1; --j)
					f[i][j]=1ll*inv*(f[i-1][j]+f[i][j+1])%mod;
				f[i][1]=(f[i-1][1]+f[i][2])%mod;
			}
		}
		printf("Case #%d: %I64d\n",cas,1ll*f[n][1]*inv%mod);
	}
	return 0;
}
