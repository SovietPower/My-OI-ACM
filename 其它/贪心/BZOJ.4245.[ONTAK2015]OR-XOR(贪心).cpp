/*
5508kb	768ms
�Ӹߵ���λ̰�ģ��жϴ𰸵ĸ�λ�ܷ�Ϊ0��
��һ��ǰ׺��sum���������λ���𰸵���һλ����Ϊ0���ҽ������ٴ���m��λ������sum[i]����һλ��Ϊ0��
ע��sum[n]��һλ����Ϊ0��
���ȷ����λΪ0�����λΪ1��sum[i]�Ͳ�����ѡ�����������Ҷ˵㣩��
������һ������λ���ɡ����Ӷ�$O(n\log a)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;
const LL LIM=(1ll<<61)-1ll;

int n,m;
bool ban[N];
LL sum[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool OK(int bit)
{
	if(sum[n]>>bit&1) return 0;
	int cnt=0;
	for(int i=1; i<=n; ++i)
		if(!ban[i]&&!(sum[i]>>bit&1))
			if(++cnt==m) break;
	if(cnt<m) return 0;
	for(int i=1; i<=n; ++i)
		if(sum[i]>>bit&1) ban[i]=1;
	return 1;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]^read();
	if(m==1) return printf("%lld\n",sum[n]),0;

	LL ans=0;
	for(int i=60; ~i; --i) if(!OK(i)) ans|=1ll<<i;
	printf("%lld\n",ans);

	return 0;
}
