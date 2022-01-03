//820kb	104ms
//猴子之间的打架是棵无根树，有n^{n-2}种可能；同时n-1个过程的排列是(n-1)! 
#include <cstdio>
const int mod=9999991;

int FP(long long x,int k)
{
	long long t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	int n; scanf("%d",&n);
	long long res=1;
	for(int i=2; i<n; ++i) res*=i, res>=mod?res%=mod:0;
	printf("%d",(int)(FP(n,n-2)*res%mod));

	return 0;
}
