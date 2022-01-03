/*
7ms	2048KB
$Description$
����������������$n$��������λ�÷ֱ���$x_i$����ԭ�㴦��һ������Ͱ��һ��������Ҫ��ԭ�������������������������Ͱ��ԭ�㣩����
�����˿������������������ƶ�����·��һ������ʱ������ѡ�񻨷�$X$����������������Ҳ���Բ�������һ������Ͳ��ܷ��£����ǻص�ԭ�㽫���ӵ����ص�ԭ��ʱ���Ի���$X$���������Լ�Я��������ȫ���ӵ�����������Я��$k$������ʱ��ÿ��һ��λ����Ứ��$(k+1)^2$��������
����$n,X$��ÿ�����������꣬��������ӵ�������������С�������ѡ�
$n\leq10^5,\ 0<x_1<...<x_n\leq10^9,\ X\leq10^9$��

$Solution$
�ȰѼ���ͷ��������Ļ���ȥ����ö�ٷ�$k$������������ô�ⲿ�ֻ��Ѿ���$(n+k)\times X$��
����ĳһ��ȡ�˴�������$a,b,c,d$���ĸ�λ�õ������Ļ��ѣ�$d+4(d-c)+9(c-b)+16(b-a)+25a$���������$5d+5c+7b+9a$��Ҳ���Ǵ��ۺ�λ���йأ�����Զ�ʹ�Զλ�õ�ϵ����$5$��������λ�õ�ϵ����$7,9,11...$��
��ȻӦ������$k$���������У���Զ�ʹ�Զ��λ������Զ��$2k$���㣬Ȼ������������ԭ���λ�÷�ϵ�����ɡ�
ö��$k$��ÿ��ѡ$k$����ѡ$\frac nk$�Σ����Ӷ�$O(n\ln n)$��

ע��һЩ���ӵķ�����ʹ�����`long long`��Ҫ���С�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

LL s[N];
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
	const int n=read(); LL X=read(),ans=X*n;
	for(int i=1,a; i<=n; ++i) s[i]=s[i-1]+(a=read()), ans+=5ll*a;
	for(int k=1; k<n; ++k)
	{
		LL tmp=X*k;
		for(int i=n,j,t=1; i; i=j,++t)
		{
			j=std::max(i-k,0);
			tmp+=(s[i]-s[j])*std::max(5ll,t*2+1ll);
			if(tmp>ans) break;
		}
		ans=std::min(ans,tmp);
	}
	printf("%lld\n",ans+X*n);

	return 0;
}
