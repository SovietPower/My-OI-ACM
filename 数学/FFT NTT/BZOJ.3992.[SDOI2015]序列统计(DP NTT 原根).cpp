/*
1876kb	3684ms(��ô��ô����...)
$Description$
����$n,m,x$�ͼ���$S$����$\prod_{i=1}^na_i\equiv x\ (mod\ m)$�ķ�����������$a_i\in S$��
$n\leq10^9��3\leq m\leq 8000��m��������1\leq x\leq m-1$��
$Solution$
��$f_{i,j}$��ʾ��ǰѡ��$i$�������˻�ģ$m$Ϊ$j$�ķ�������$g_i=[i\in S]$��
ת�ƾ��ǣ�
$$f_{i,a*b\%m}=\sum f_{i-1,a}*g_b$$
ÿ��ת����һ���ģ����Կ��Կ����ݼ��㣬��$f_{2i,a*b\%m}=\sum f_{i,a}*f_{i,b}$��
��Ȼ��$n$�Ż�����$\log n$��������ת�Ƹ��ӶȻ���$O(m^2)$�ġ�
���Ƿ��֣�ֻҪ�ܰ�$a*b\%m$д��$(a+b)\%m$������һ��ѭ���������ʽ�ˡ�
�ѳ˷���ɼӷ������뵽ȡ������ͬ����ģ�����¿�����[��ɢ����](https://www.cnblogs.com/SovietPower/p/10044472.html)��
ȡ$m$��һ��ԭ��$g$��$g,g^2,...,g^{m-1}$��ģ$m$�����»�����ͬ���������ǿ���������$g^A\equiv a\ (mod\ m)$��������$A$���滻��$a$����$a$ģ$m$��ָ��$I(a)$��������Ψһ�ġ�
��ô$a*b\equiv g^A*g^B\equiv g^{A+B}\equiv g^{(A+B)\%\varphi(m)}\ (mod\ m)$��
����ת�ƾͳ��ˣ�
$$f_{i,(A+B)\%(m-1)}=\sum f_{i-1,A}*g_B$$
��$g_{A+B}=\sum f_{i-1,A}*g_B$����ô$f_{i,j\%(m-1)}=g_j+g_{j+m-1}$��
������$NTT$�Ż���
ͬ����ÿһ�ε�ת�ƻ���һ���ģ����ɿ����ö���ʽ�����ݡ�
���Ӷ�$O(m\log m\log n)$��
��Ȼȡ$g^0,g^1,...,g^{m-2}$Ҳ�У���Ϊ����ʽ�±���$0$��ʼ����Щ��
���������������$0$Ҫ���к��Ե�����
��Ϊ��ѭ���������ÿ�ο����ݳ˵�ʱ����Ҫ��$f$�������Ҳ����һ��Ҫ��$NTT$��ϵ����ʾ������һֱ�õ�ֵ��ʾ�������������ɣ���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define G 3
#define invG 334845270
#define mod 1004535809
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define Mul(x,y) (1ll*x*y%mod)
typedef long long LL;
const int N=32500;

int inv,I[N],x[N],t[N],rev[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k,int p)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%p)
		if(k&1) t=1ll*t*x%p;
	return t;
}
int Get_root(int P)
{
	static int p[10005];
	int cnt=0,t=P-1;
	for(int i=2; i*i<=t; ++i)
		if(!(t%i))
		{
			p[++cnt]=i;
			while(!(t%i)) t/=i;
		}
	if(t>1) p[++cnt]=t;
	for(int x=2; ; ++x)
	{
		bool ok=1;
		for(int i=1; i<=cnt; ++i) if(FP(x,(P-1)/p[i],P)==1) {ok=0; break;}
		if(ok) return x;
	}
	return 1;
}
void Pre(int m)
{
	int g=Get_root(m);
	for(int i=0,pw=1; i<m-1; ++i) I[pw]=i, pw=1ll*pw*g%m;//g^i=pw -> I(pw)=i
}
void NTT(int *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1,Wn=FP(~opt?G:invG,(mod-1)/i,mod);
		for(int j=0; j<lim; j+=i)
			for(int k=j,w=1,t; k<j+mid; ++k,w=1ll*w*Wn%mod)
				a[k+mid]=a[k]-(t=1ll*a[k+mid]*w%mod)+mod, Mod(a[k+mid]),
				a[k]+=t, Mod(a[k]);
	}
	if(opt==-1) for(int i=0,inv=::inv; i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}
void Mult1(int *f,int n,int lim)//x*x������һ��NTT�� 
{
	NTT(f,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*f[i]%mod;
	NTT(f,lim,-1);
	for(int i=0; i<n; ++i) f[i]=f[i]+f[i+n], Mod(f[i]);//f[i+m-1]
	for(int i=n; i<lim; ++i) f[i]=0;//!
}
void Mult2(int *a,int *b,int *res,int n,int lim)
{
	static int f[N],g[N];
	memset(f,0,sizeof f), memset(g,0,sizeof g);
	memcpy(f,a,n<<2), memcpy(g,b,n<<2);
	NTT(f,lim,1), NTT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*g[i]%mod;
	NTT(f,lim,-1);
	for(int i=0; i<n; ++i) res[i]=f[i]+f[i+n], Mod(res[i]);//f[i+m-1] //Ҫ��֤res��n������Ϊ0 
}

int main()
{
	static int x[N],res[N];
	int n=read(),m=read(),X=read(),S=read();
	Pre(m), --m;//0~m-1

	int lim=1,l=-1;
	while(lim<=m+m-2) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	inv=FP(lim,mod-2,mod);

	for(int i=1,s; i<=S; ++i) s=read(), s&&(++x[I[s]]);//++f[1][s]
	res[I[1]]=1;//f[0][1]=1
	for(int k=n; k; k>>=1,Mult1(x,m,lim))
		if(k&1) Mult2(res,x,res,m,lim);
	printf("%d\n",res[I[X]]);

	return 0;
}
