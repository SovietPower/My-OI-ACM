/*
0ms	0MB
$Description$
������Ϊn������A�����ж���S������0<=S<2^{60}���Ҷ�������i��[1,n-1]��a[i]^S<=a[i+1]^S��
n<=20��
$Solution$
���Ƕ���a,b������ЩS����a^S<=b^S��
�ҳ�a^b�����λ1��Ҳ����a,b��ͬ�����λ���������һλa��0��b��1����ôS��һλ������0������S��һλ������1��
����ÿ��a[i]^S<=a[i+1]^Sʵ������������S��ĳһλ����������������������ˡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define BIT 59
typedef long long LL;
const int N=66;

int ban[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	memset(ban,0xff,sizeof ban);
	int n=read(); LL las=read();
	for(int i=2; i<=n; ++i)
	{
		LL now=read(),s=now^las;
		for(int j=BIT; ~j; --j)
		{
			if(!(s>>j&1)) continue;
			if(las>>j&1)
				if(!ban[j]) return puts("0"),0;
				else ban[j]=1;
			else
				if(ban[j]==1) return puts("0"),0;
				else ban[j]=0;
			break;
		}
		las=now;
	}
	LL ans=1;
	for(int i=BIT; ~i; --i) if(ban[i]==-1) ans<<=1ll;
	printf("%lld\n",ans);

	return 0;
}
