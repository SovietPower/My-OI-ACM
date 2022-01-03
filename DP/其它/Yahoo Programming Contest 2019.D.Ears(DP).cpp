/*
4ms	640KB
�����Ϊ$S$���յ�Ϊ$T$���߹������ĵ���$L$����ҵĵ���$R$��
��ô�����ᱻ�ֳ�����Σ�
$0\sim L-1$������$0$�Σ�
$L\sim S-1$������ż���Σ�
$S\sim T$�����������Σ�
$T+1\sim R$������ż���Σ�
$R+1\sim\infty$������$0$�Ρ�
�ڶ��κ͵��Ķο��Ծ���$0$�Σ�Ҳ���ǿ���û�еڶ��λ���ĶΣ���ע������ǵڶ�/��/�Ķ�$A_i=0$�Ļ����л��ѡ�
$f[i][j]$��ʾ��$i$�㣬���ڵ�$j$�Σ�����С���ѡ�ת�ƺܼ򵥡�
���Ӷ�$O(n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(); LL f[5]={0};
	for(int i=1; i<=n; ++i)
	{
		int ai=read();
		LL mn=f[0]; f[0]=f[0]+ai;
		mn=std::min(mn,f[1]), f[1]=mn+(ai?ai&1:2);
		mn=std::min(mn,f[2]), f[2]=mn+(ai?ai+1&1:1);
		mn=std::min(mn,f[3]), f[3]=mn+(ai?ai&1:2);
		mn=std::min(mn,f[4]), f[4]=mn+ai;
	}
	printf("%lld\n",std::min(f[2],std::min(f[3],f[4])));

	return 0;
}
