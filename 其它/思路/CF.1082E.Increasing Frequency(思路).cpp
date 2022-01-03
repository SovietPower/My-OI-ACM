/*
31ms	6700KB
$Description$
����$n$�����������ѡ��һ�����佫���Ƕ����ϻ��ȥ����һ������������������������ж��ٸ������ڸ�����$C$��
$n\leq5\times10^5$��
$Solution$
�ȼ�һ����ʾ$C$�ĸ�����ǰ׺��$sum_i$��
ѡ���޸ĵ�����$[l,r]$һ������$A_l=A_r$�Ҷ�����$A_l$���$C$����������ö���Ҷ˵㣬��ÿ��Ȩֵ�������ǡ�
��ô$A_r$Ҫô����ǰ��ĳ������$A_r$����ת�ƹ�����Ҫô$l$ֱ�ӵ���$r$��
���Լ�$mx_{a_i}$Ϊ֮ǰ$a_i$�����������ף���ô$$mx_{a_i}=\max\{\ mx_{a_i}+1,\ \ sum_{i-1}+1\}$$
$Ans=\max\{mx_{a_i}+sum_n-sum_i\}$��forһ���������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N],sum[N],mx[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	const int n=read(),C=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+((A[i]=read())==C);
	int ans=0; const int sn=sum[n];
	for(int i=1; i<=n; ++i)
		mx[A[i]]=std::max(mx[A[i]],sum[i-1])+1, ans=std::max(ans,mx[A[i]]+sn-sum[i]);
	printf("%d\n",ans);

	return 0;
}
