/*
502ms	868kB
���ִ𰸡����Ž���Ǵ������ң�ÿ������һ��������Ҫ�Ĳ��������ҡ�
Ҫע��ÿ��Ҫ��һ������һ�����ӣ��������$n-1$ʱ������$n$������Ͳ�������һ����$n$��
��Ϊд������WA��n�Ρ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool Check(int n,LL m,LL pur)
{
	LL need=0;
	for(int i=1; i<=n; ++i)
	{
		LL need2=(pur+A[i]-1)/A[i];
		need2-=need+1;
		if(need2<=0) i!=n?(--m):(!need2/*����һ����n*/&&--m), need2=0;
		else m-=need2*2+1;
		if(m<0) return 0;
		need=need2;
	}
	return 1;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(); LL m; scanf("%lld",&m);
		for(int i=1; i<=n; ++i) A[i]=read();
		LL l=0,r=1e17,mid,ans=0;
		while(l<=r)
			if(Check(n,m,mid=l+r>>1)) ans=mid, l=mid+1;
			else r=mid-1;
		printf("%lld\n",ans);
	}

	return 0;
}
