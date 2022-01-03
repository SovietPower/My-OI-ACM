/*
设f[i]为到i的期望得分，c[i]为到i的期望连续长度 
则若s[i]=='x',f[i]=f[i-1], c[i]=0
	s[i]=='0',f[i]=f[i-1]+2*c[i-1]+1, c[i]=c[i-1]+1
(因为 (l+1)^2 = l^2+2l+1 -> (l+1)^2-l^2 = 2l+1,连续长度+1会对答案多贡献2l+1)
(有点疑惑为什么是c[i-1]...不过写出来确实是。每一次+2l+1 实际已经与前面已有的连续长度 构成(l+1)^2 的贡献
 也就是说，当有'o'时，对答案的贡献是线性的)
	s[i]=='?',f[i]=f[i-1]+(2*c[i-1]+1)/2, c[i]=(c[i-1]+1)/2
(两种可能性均等，所以都是1/2的)
*/
#include<cstdio>
using namespace std;
const int N=3e5+5;

int n;
double f[N],c[N];//continuation
char s[N];

int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;++i)
		if(s[i]=='x')
			f[i]=f[i-1], c[i]=0;
		else if(s[i]=='o')
			f[i]=f[i-1]+2.0*c[i-1]+1, c[i]=c[i-1]+1;
		else
			f[i]=f[i-1]+c[i-1]+0.5, c[i]=0.5*c[i-1]+0.5;
	printf("%.4lf",f[n]);

	return 0;
}
