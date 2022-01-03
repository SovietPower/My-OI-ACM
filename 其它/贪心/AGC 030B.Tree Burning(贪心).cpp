/*
8ms	4608KB
$Description$
��һ����Ϊ$L$�Ļ���������$n$����������ֱ�Ϊ$a_i$����ʼʱ��ԭ�㡣
ÿ�������ѡ��˳ʱ�����ʱ���ߵ���һ��û�б��յ�������ͣ�����λ�ã�Ȼ���յ���������ظ���һ����ֱ�������������յ���
���ߵ���·���������Ƕ��١�
$n\leq2\times10^5,\ a_i,L\leq10^9$��

$Solution$
��Ĳ˰�QAQ ��ʱ�����������

��˳ʱ����һ��Ϊ$L$����ʱ����һ��Ϊ$R$��
�����뷨��$LRLRLR...$�����ߡ�����Ȼ�з����������������ֱ���$1,\ L-1$����
��ʵ����$LLLLRLR...$��$RRRLRLR...$���������߷���û�����ˡ�������֤��û��~~��ż�Ȼ��ʼ�������ˣ��ͱȼ�����һ�������߸��Űɣ�~~��
ǰ׺�ͺ�׺��Ԥ����һ�£�ö�ٸտ�ʼ~~��������~~����$LRLR...$��λ�þͿ����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
LL Solve(const int n,const int L)
{
	static LL pre[N],suf[N];
	for(int i=1; i<=n; ++i) pre[i]=pre[i-1]+A[i];
	for(int i=n; i; --i) suf[i]=suf[i+1]+L-A[i];
	LL ans=A[n];
	for(int i=1,p; i<n; ++i)
		p=i+((n-i)>>1), (n-i)&1 ? ans=std::max(ans,(suf[p+2]+pre[p]-pre[i]+A[i])*2+L-A[p+1]) : ans=std::max(ans,(suf[p+1]+pre[p-1]-pre[i]+A[i])*2+A[p]);
	return ans;
}

int main()
{
	const int L=read(),n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	LL ans=Solve(n,L);
	std::reverse(A+1,A+1+n);
	for(int i=1; i<=n; ++i) A[i]=L-A[i];
	ans=std::max(ans,Solve(n,L));
	printf("%lld\n",ans);

	return 0;
}
