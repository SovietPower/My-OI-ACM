/*
4736kb	448ms
$Description$
������$(0,0)$����һ�����ӡ�����ֻ�������߷����ֱ��Ӧ����$(A_x,A_y),(B_x,B_y)$��ͬʱ��������$n$���ϰ���$(x_i,y_i)$���������κ�ʱ�̶����������ϰ��㡣
�����Ӵ�$(0,0)$����$(E_x,E_y)$�ķ��������𰸶�$10^9+7$ȡģ��
$Solution$
ע�⵽$A_x*B_y-A_y*B_x\neq0$���������������ߣ���ĳ�����ߵ���һ���㣬���ַ�ʽ�ֱ����ô���$x,y$��ȷ���ġ�����÷�����ķǸ������⣺$$\left\{\begin{array}{lr}A_x*x+B_x*y=X_i\\A_y*x+B_y*y=Y_i\end{array}\right.$$
ͬ����ͼ����������ĳ���������ַ�ʽ�ֱ���$x,y$��������һ���㣬�����ķ�����Ϊ$\binom{x+y}{x}$��
��ÿ�����ʾ��������$x,y$����$(0,0)$��������õ����ַ�ʽ�ֱ����貽������������������Ĳ�������$x_i-x_j,y_i-y_j$�ˡ�������ͬ���������������
Ȼ��Ϳ���������ݳ��ˡ�
$f(i)$��ʾ��$i$֮ǰ�������κ��ϰ��㣬�����ϰ���$i$�ķ���������$cnt(i,j)$��ʾ���ϰ���$i$��$j$�ķ��������������Ϊ�ϰ���$0$����ô$$f(i)=cnt(0,i)-\sum_{j=1}^{i-1}f(j)*cnt(j,i)$$
���յ���Ϊ��$n+1$���ϰ��㣬�𰸾���$f(n+1)$�ˡ�
���Ӷ�$O(n^2)$��
��Ϊ$A_x,A_y,B_x,B_y$�����и���������Ҫ�ߵĲ�����$n^2$����ģ�����$(1,0),(-500,1)$���������Ҫ$n+m$�����Ͻ�Ҫ��$2n^2$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=505,M=500000;

int Ax,Ay,Bx,By,f[N],fac[M+2],ifac[M+2];
struct Point
{
	int x,y;
	bool operator <(const Point &a)const{
		return x==a.x?y<a.y:x<a.x;
	}
}p[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
void Calc(int yi,int xi,int &x,int &y)
{
	int a=xi*By-yi*Bx,b=Ax*By-Ay*Bx;
	if(!b||a%b) {x=-1; return;}//��0����
	int c=xi*Ay-yi*Ax,d=Bx*Ay-By*Ax;
	if(!d||c%d) {x=-1; return;}
	x=a/b, y=c/d;
}
inline int C(int n,int m)
{
	if(n<0||m<0) return 0;//return C(n+m,n)
	return 1ll*fac[n+m]*ifac[n]%mod*ifac[m]%mod;
}

int main()
{
	fac[0]=fac[1]=1;
	for(int i=2; i<=M; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[M]=FP(fac[M],mod-2);
	for(int i=M-1; ~i; --i) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;

	int Ex=read(),Ey=read(),n=read(),cnt=0;
	Ax=read(), Ay=read(), Bx=read(), By=read();

	Calc(Ey,Ex,Ex,Ey);
	if(Ex<0||Ey<0) return puts("0"),0;
	p[++cnt]=(Point){Ex,Ey};

	for(int x,y; n--; )
	{
		Calc(read(),read(),x,y);
		if(!(x<0||y<0||x>Ex||y>Ey)) p[++cnt]=(Point){x,y};//��Ҫ�߸��ಽ�Ĳ����ཻ���������򻹳����⣿��
	}
	n=cnt, std::sort(p+1,p+1+n);

	for(int i=1; i<=n; ++i)
	{
		Point now=p[i]; LL tmp=C(now.x,now.y);
		if(!tmp) continue;
		for(int j=1; j<i; ++j)
			tmp+=mod-1ll*f[j]*C(now.x-p[j].x,now.y-p[j].y)%mod;
		f[i]=(int)(tmp%mod);
	}
	printf("%d\n",f[n]);

	return 0;
}
