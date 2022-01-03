/*
1700kb	200ms
�ȿ����ܷ�ϻ�Ϊ������Ȼ�ǿ��Եģ���Ϊ��Ҳ���������������ƽ�ơ���������ö�ٶϵ�$k$����ʾ$k$��$k+1$֮�䲻������ҡ�
��$d_i=a_i-aver$����ʾ$i$��Ҫ��$i-1$�Ľ��������$d_i$�����ɸ������ľͱ�ʾ$i-1$��$i$ $d_i$����ң�����Ȼû��Ҫ�ٱ�ʾ$i-1$��$i$�Ľ����������
�����ٶ�$d_i$���ǰ׺��$s_i$��$|s_i|$�ͱ�ʾ$i$λ����ת�ֶ��ٽ�ҡ�ע����Ϊ�Ǿ�������$s_n=0$��
��ôö�ٶϵ�$k$�󣬴���$\sum_{i=k+1}^n|s_i-s_k|+\sum_{i=1}^k|s_i+s_n-s_k|$������ȻҪ�Ӿ���ֵ����_�������������͵ľ���ֵ��
��Ϊ$s_n=0$�������������$\sum_{i=1}^n|s_i-s_k|$��$s_k$ȡ��λ��ʱ����С���������ƶ�����ɸ���Ĵ��ۣ���
��ֱɵ�˰�QAQ���������ô��������ô��ʱ�䰡����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define abs(x) (x<0?-(x):x)
typedef long long LL;
const int N=1e6+5;

int A[N];
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
	int n=read(); LL aver=0;
	for(int i=1; i<=n; ++i) aver+=A[i]=read();
	aver/=n;
	for(int i=1; i<=n; ++i) A[i]=A[i]-aver+A[i-1];
	std::nth_element(A+1,A+(n+1>>1),A+n+1);
	LL ans=0;
	for(int i=1,mid=A[n+1>>1]; i<=n; ++i) ans+=abs(A[i]-mid);
	printf("%lld\n",ans);

	return 0;
}
