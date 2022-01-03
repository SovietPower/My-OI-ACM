/*
764ms	97900KB
$Description$
��$n$�����ؼ��ϣ���ʼ��Ϊ�ա���$q$�β��������������֣�
$1\ x\ v$������$x$�����ϸ�ֵΪ$\{v\}$��
$2\ x\ y\ z$���ѵ�$x$��������Ϊ��$y$���������$z$�����ϵĲ���
$3\ x\ y\ z$���ѵ�$x$��������Ϊ$\{\gcd(a,b)|a\in y,b\in z\}$��
$4\ x\ v$��ѯ�ʵ�$x$�������У�����$v$���ִ���ģ$2$���ֵ��
$n\leq10^5,\ q\leq10^6$�����ֵ��������־�Ϊ��������$\leq7000$��
$Solution$
�ȿ��ǵ��������ƾ���Ĳ�����δ�������õ�������$FFT$�ķ��������������ת���ɶ�Ӧλ�õġ���ֵ���ֱ�������㡣
��$x$λ�ô�����ȥά������$x$�ĳ��ִ���������ά��$x$���б����ĳ��ִ����������Ϳ��ԶԲ�ͬλ�õĵ�ֵ�ֱ�ά����$\gcd$���������
����$y$������$x$�ı�����$a$����$z$������$x$�ı�����$b$������ô�������֮��$x$�ı�������$a*b$�����������$a,b$������λ�õ�ֵ����Ӱ�죩��
����ʵ�֣���Ϊֻ��Ҫ�ж���ż�ԣ���һ����СΪ$7000$��$bitset\ A_i$������������$A_y\ ^{\wedge}A_z$���ӣ�������������$A_y\&A_z$���ˣ���
���ǲ�ѯ��ʱ����Ҫ�ݳ⣺$Ans=A_x-A_{2x}-A_{3x}+A_{6x}$...ע�⵽�ݳ�ϵ��ֻ��$\mu=1$��$-1$����$1\equiv-1(mod\ 2)$������ֱ�Ӱ�$\mu(i*x)\neq0$����Щλ���ϵ�ֵ�������ͺã�Ҳ����ȫ��������ģ$2$��
����ÿ�β����ĸ��Ӷȶ���$O(\frac{7000}{w})$��
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=7001;

int mu[N];
std::bitset<M> A[N],ori[M],Mu[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Init()
{
	static int P[M>>3];
	static bool notP[M];
	mu[1]=1;
	for(int i=2,cnt=0; i<M; ++i)
	{
		if(!notP[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=P[j]*i)<M; ++j)
		{
			notP[v]=1;
			if(!(i%P[j])) break;
			mu[v]=-mu[i];
		}
	}
}

int main()
{
	Init();
	for(int i=1; i<M; ++i)
		for(int j=i; j<M; j+=i)
			ori[j][i]=1, Mu[i][j]=(mu[j/i]!=0);

	for(int n=read(),q=read(),x,y,z,v; q--; )
		switch(read())
		{
			case 1: x=read(),v=read(),A[x]=ori[v]; break;
			case 2: x=read(),y=read(),z=read(),A[x]=A[y]^A[z]; break;
			case 3: x=read(),y=read(),z=read(),A[x]=A[y]&A[z]; break;
			case 4: x=read(),v=read(),putchar(48+((A[x]&Mu[v]).count()&1)); break;
		}
	return 0;
}
