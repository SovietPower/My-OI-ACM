/*
����$n=3$��$p=[1,2,3,1,3,2,2,1,3,2,3,1,3,1,2,3,2,1]$��������������ͣ����ǲ£������зֳ�$n$�Σ�Ҳ�����Բ�ͬ����ͷ������Ϊһ�Σ���Щ�εĴ���һ���ġ�������$n=3$���Ƿֳ�$[1,2,3,1,3,2]��[2,1,3,2,3,1]��[3,1,2,3,2,1]$���Σ�
��ʵ��Ҳȷʵ�������������������α��磺$2,n,...1,3,1,...,n$������֮��Ҳ�β��ɺϷ��ӶΡ�
������������ֻ������ô����ĳ������ͷ�����еĴ𰸣�����$[1,2,3,1,3,2]$�����ٳ�$n$���Ǵ��ˡ�
���ǲ��ǿ��Ե��Ƶġ�Ҳ���Ǽ�������֪��$n-1$ʱ�Ĵ�$f_{n-1}$����ô��$f_n$��
��$n=4$��˵�����Ǵ�ʱ��$4$��ͷ�����У�������ÿ��$3$������ǰ�����һ��$4$��ƴ��һ��
��Ȼ���ǿ��Եõ�$3!$�ֺϷ��ӶΡ���$f_3$�е�ÿ�ַ�������$n=4$ʱҲ���ܺ�һ��$4$��ɺϷ����ӶΣ�дһд��������Ψ��������$4,3,2,1$�������Ρ������У�$f_n=\left[f_{n-1}+(n-1)!-1\right]*n$��
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define mod 998244353
typedef long long LL;
typedef unsigned long long ull;
const int N=1e6+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
//bool Check(int *p,int n)
//{
//	for(int i=1; i<=n; ++i) if(p[i]!=i) return 0;
//	return 1;
//}
//void Work(int n)
//{
//	static int A[10000004],p[15];
//	for(int i=1; i<=n; ++i) p[i]=i;
//	int t=0;
//	do
//	{
//		for(int i=1; i<=n; ++i) A[++t]=p[i];
//		std::next_permutation(p+1,p+1+n);
//	}while(!Check(p,n));
//	int ans=0;
//	for(int i=1; i<=t; ++i)
//	{
//		int s=0;// n<=4 && printf("%d ",A[i]);
//		for(int j=i; j-i+1<=n && j<=t; ++j)
//			s+=A[j], j-i+1==n && s==n*(n+1)/2 && (++ans);
//		if(n<=5 && i+n-1<=t) printf("%lld ",s);
//	}
//	puts("");
//	printf("%d:%d t:%d\n",n,ans,t);
//}

int fac[N],A[N];

int main()
{
//	for(int i=1; i<=9; ++i) Work(i);
	int n=read();
	fac[0]=1, A[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1; i<=n; ++i) A[i]=1ll*i*A[i-1]%mod+1;
	A[n]=(A[n]+mod-fac[n]-1)%mod;
	LL ans=1ll*n*fac[n]%mod-A[n];
	printf("%d\n",(int)(ans%mod+mod)%mod);

	return 0;
}
