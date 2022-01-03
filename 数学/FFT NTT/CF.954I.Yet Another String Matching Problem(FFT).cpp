/*
686ms	63900KB(1653ms	18800KB)
$Description$
对于两个串$a,b$，每次你可以选择一种字符，将它在两个串中全部变为另一种字符。定义$dis(a,b)$为使得$a,b$相等所需的最小修改次数。
给定两个串$S,T$，对于$S$中所有长为$|T|$的子串$S'$，输出$dis(S',T)$。
$1\leq|T|\leq|S|\leq125000$，字符集为$a\sim f$。
$Solution$
考虑$dis(a,b)$怎么求。用一个并查集，依次枚举$a_i,b_i$，如果$a_i\neq b_i$且$a_i,b_i$还不在一个集合内，就将它们合并，$dis$++。
（也可以考虑建一张无向图，在$a_i,b_i$间连边。因为每个连通块最后都要变成同一个字符，所以$dis=节点数(6)-连通块数$）
考虑枚举每一个位置$i\in[0,|S|-|T|]$，我们需要对每个$j\in[0,|T|-1]$，都判一下是否需要合并$S_{i+j},T_j$，复杂度是$O(|S||T|)$的。但事实上我们只需要判断，这$6$种字符之间，是否在同一位置上出现过两种不同字符就可以了（然后尝试把它们合并）。
也就是枚举两种不同的字符$a,b$，判一下它们在哪些位置同时出现了（$S_i=a$而$T_i=b$）。
令$f_i=[S_i=a],\ g_i=[T_i=b]$，$F(x)=\sum_{i=0}^{|T|-1}f_{x+i}g_i$。$F(x)$可以用$FFT$求出。
若$F(x)\neq0$，那么$a,b$就在同一位置出现了，而且是在$x$处的子串中。枚举$x$时尝试合并一下$a,b$就可以了。
这样复杂度$O(36n\log n+36n\alpha(n))$+FFT的大常数。$CF$比较轻松过，$BZOJ$就算了。。
当然有很多可以优化的地方，比如减少$f,g$的$FFT$次数（1653ms->686ms）。
$CF$上还有两种更优的做法，没太看懂。。
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=(1<<18)+5;
const double PI=acos(-1);

int rev[N],fa[6];
char S[N],T[N];
bool neq[N][6][6];
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}f[6][N],g[6][N],F[N];

void FFT(Complex *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1; Complex Wn(cos(PI/mid),opt*sin(PI/mid));
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0),t;
			for(int k=j; k<j+mid; ++k,w=w*Wn)
				a[k+mid]=a[k]-(t=w*a[k+mid]), a[k]=a[k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	scanf("%s%s",S,T);
	int n=strlen(S),m=strlen(T),lim=1,l=-1;
	while(lim<=n+m) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	std::reverse(T,T+m);//!

	for(int a=0; a<6; ++a)//!
	{
		const char aa=a+97;
		for(int i=0; i<n; ++i) f[a][i]=Complex(S[i]==aa,0);
		for(int i=0; i<m; ++i) g[a][i]=Complex(T[i]==aa,0);
		FFT(f[a],lim,1), FFT(g[a],lim,1);
	}
	for(int a=0; a<6; ++a)
		for(int b=0; b<6; ++b)
		{
			if(a==b) continue;
//			for(int i=0; i<lim; ++i) f[i].x=f[i].y=g[i].x=g[i].y=0;
//			for(int i=0; i<n; ++i) f[i]=Complex(S[i]==a,0);
//			for(int i=0; i<m; ++i) g[i]=Complex(T[i]==b,0);
//			FFT(f,lim,1), FFT(g,lim,1);
			for(int i=0; i<lim; ++i) F[i]=f[a][i]*g[b][i];
			FFT(F,lim,-1);
			for(int i=0; i<n; ++i) neq[i][a][b]=(int)(F[m+i-1].x+0.5);
		}
	for(int i=0; i<=n-m; ++i)
	{
		for(int j=0; j<6; ++j) fa[j]=j;
		int ans=0;
		for(int j=0; j<6; ++j)
			for(int k=0; k<6; ++k)
				if(neq[i][j][k]&&Find(j)!=Find(k)) ++ans,fa[fa[j]]=fa[k];
		printf("%d ",ans);
	}

	return 0;
}
