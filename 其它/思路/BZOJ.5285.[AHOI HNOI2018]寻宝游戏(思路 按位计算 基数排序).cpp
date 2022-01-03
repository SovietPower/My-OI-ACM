/*
940kb	820ms
ͬ����λ���ǣ�����$m=1$��
����Ҫ��һ��$01$����$\&$��$|$��ע�⵽����������$x$��$x\&0=0$��$x\&1=x$��$x|0=x$��$x|1=1$��Ҳ����$\&1$��$|0$û��Ӱ�죬��$\&0$��$|1$�൱��ֱ�Ӹ�ֵ��
���Ҫ���������$1$��������Ҫ��ĳ��$1$ǰ����$|$������֮���λ��ֻ��$1$ǰ��$\&$��$0$ǰ��$|$�����������$0$��ͬ���ҵ�ĳ��$0$��ǰ����$\&$������λ�õ�$1$ǰ��$\&$��$0$ǰ��$|$��
��`&`=1��`|`=0��Ȼ���������=$y$���Ӻ���ǰ�ǴӸ�λ����λ�������$x>y$�������$1$�����$x<y$�����$0$���ܺ���⣬��ΪҪ�ҵ��Ӻ���ǰ��һ����ͬ��λ�ã��������뵽...����
��Ϊ��ʼ��$0$����$x=y$�ǽ��Ҳ��$0$��
Ҳ����˵����һλҪ����$1$������$y<x$��Ҫ����$0$����$y\geq x$��
��չ��$m$λ������ÿһ��ѯ�ʾͿ��Եõ�$m$�������Ĳ���ʽ����������$l\leq y<r$���𰸾���$r-l$��

��ô������ˣ�����ֱ��ʵ�����������е��鷳...
�����Ƚ�$m$��$x$��С�������򣬶���ѯ��$s$��`for`һ���ҵ�$s_i=1$��λ������С��$x$����$r$����`for`һ���ҵ�$s_i=0$��λ��������$x$����$l$���𰸾���$\max(r-l,0)$��ע���ʼ$l=0,r=2^m$...����
���Ի�������Ȼ������~~`sort`���ǻ��~~...�о���׺�����ѧ��= =
ÿ���Ե�ǰ��$0$��$1$Ϊ��һ�ؼ��֣�֮ǰ������Ϊ�ڶ��ؼ��֣���һ��SA�İ��Ӿͺ���...

���Ӷ�$O((n+q)m)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=5005;

int rk[N],tmp[N],pw[N],x[N],X[N],s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void Read(int n)
{
	register char c=gc(); while(c!='0'&&c!='1') c=gc();
	s[1]=c-48;
	for(int i=2; i<=n; s[i++]=gc()-48);
}

int main()
{
//	freopen("hunt.in","r",stdin);
//	freopen("hunt.out","w",stdout);

	int n=read(),m=read(),Q=read();
	pw[1]=1;
	for(int i=2; i<=n+1; ++i) pw[i]=pw[i-1]<<1, Mod(pw[i]);
	int *rk=::rk,*tmp=::tmp;
	for(int i=1; i<=m; ++i) rk[i]=i;
	for(int i=1,tm[2]; i<=n; ++i)
	{
		tm[0]=0, tm[1]=m, Read(m);
		for(int j=1; j<=m; ++j) s[j]?Add(x[j],pw[i]):++tm[0];
		for(int j=m; j; --j) tmp[tm[s[rk[j]]]--]=rk[j];
		std::swap(rk,tmp);
	}
	for(int i=1; i<=m; ++i) X[i]=x[rk[i]];//rk[i]=j �ŵ�i������j��SA���sa...��
	X[m+1]=pw[n+1];
	while(Q--)
	{
		Read(m); int L=0,R=m+1;//Init: L=0, R=2^n(nλ��������)
		for(int i=1; i<=m; ++i) if(s[rk[i]]) {R=i; break;}
		for(int i=m; i; --i) if(!s[rk[i]]) {L=i; break;}
		printf("%d\n",R<L?0:(X[R]-X[L]+mod)%mod);
	}

	return 0;
}
