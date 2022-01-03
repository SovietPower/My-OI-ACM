/*
62ms	35500KB
$Description$
����$n$��������$a_i$�����ж��ٸ�������$a_{i_1},a_{i_2},...,a_{i_k}$������$a_{i_1},a_{i_2},...,a_{i_k}$ $and$����Ϊ$0$��
$n\leq10^6,\quad 0\leq a_i\leq10^6$��
$Solution$
������ݷ�Χ�������ǰ�λ�ݳ⣺
��$g_x$��ʾ$x$�Ķ����Ʊ�ʾ��$1$�ĸ�����$f_x$��ʾ�ж��ٸ�$a_i$����$a_i\&x=x$��
��Ҫ��ѡ����������������$and$��Ϊ$x$����ôֻ�ܴ���$f_x$������ѡ��
����$Ans=\sum_{x=0}^{lim}(-1)^{g_x}(2^{f_x}-1)$��
��ô�����$f_x$��
$a_i\&x=x$����$x$��$a_i$���Ӽ������Զ�$f_x$ö�ٳ������¼��ɡ����Ӷ�$O(2^nn)$��
ע����Ϊд����������Ҫ��������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mod 1000000007
#define lb(x) (x&-x)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=3e6+5;

int bit[N],pw[N],f[N];
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
	int n=read(),lim=0;
	for(int t,i=1; i<=n; ++i) ++f[t=read()],lim=std::max(lim,t);
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	for(int i=0; 1<<i<=lim; ++i)
		for(int s=0; s<=lim; ++s)
			if(!(s>>i&1)) Add(f[s],f[s|(1<<i)]);
	LL ans=0;
	for(int i=1; i<=lim; ++i) bit[i]=bit[i^lb(i)]^1;
	for(int i=0; i<=lim; ++i) ans+=bit[i]?mod-pw[f[i]]+1:pw[f[i]]-1;
	printf("%I64d\n",ans%mod);

	return 0;
}
