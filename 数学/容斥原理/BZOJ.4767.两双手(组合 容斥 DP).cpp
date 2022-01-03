/*
4736kb	448ms
$Description$
棋盘上$(0,0)$处有一个棋子。棋子只有两种走法，分别对应向量$(A_x,A_y),(B_x,B_y)$。同时棋盘上有$n$个障碍点$(x_i,y_i)$，棋子在任何时刻都不能跳到障碍点。
求棋子从$(0,0)$跳到$(E_x,E_y)$的方案数。答案对$10^9+7$取模。
$Solution$
注意到$A_x*B_y-A_y*B_x\neq0$，即两向量不共线，从某个点走到另一个点，两种方式分别所用次数$x,y$是确定的。即求该方程组的非负整数解：$$\left\{\begin{array}{lr}A_x*x+B_x*y=X_i\\A_y*x+B_y*y=Y_i\end{array}\right.$$
同网格图方案数，从某个点以两种方式分别走$x,y$步到达另一个点，这样的方案数为$\binom{x+y}{x}$。
将每个点表示成这样的$x,y$（从$(0,0)$出发到达该点两种方式分别所需步数）后，任意两点所需的步数就是$x_i-x_j,y_i-y_j$了。方案数同样可以用组合数求。
然后就可以排序后容斥了。
$f(i)$表示在$i$之前不经过任何障碍点，到达障碍点$i$的方案数。记$cnt(i,j)$表示从障碍点$i$到$j$的方案数。将起点视为障碍点$0$，那么$$f(i)=cnt(0,i)-\sum_{j=1}^{i-1}f(j)*cnt(j,i)$$
将终点视为第$n+1$个障碍点，答案就是$f(n+1)$了。
复杂度$O(n^2)$。
因为$A_x,A_y,B_x,B_y$可能有负数，所以要走的步数是$n^2$级别的（比如$(1,0),(-500,1)$）。组合数要$n+m$所以上界要到$2n^2$。
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
	if(!b||a%b) {x=-1; return;}//判0。。
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
		if(!(x<0||y<0||x>Ex||y>Ey)) p[++cnt]=(Point){x,y};//需要走更多步的不会相交（否则排序还出问题？）
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
