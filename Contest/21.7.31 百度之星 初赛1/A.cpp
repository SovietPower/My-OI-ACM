/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Sum(x,v) x+v>=mod?x+v-mod:x+v
typedef long long LL;
const int N=105;

int coef[N];

struct Edge{
	int v,w;
};
std::vector<Edge> e[N];

struct Complex
{
	int x,y;
	Complex(int x=0,int y=0):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(Sum(x,a.x), Sum(y,a.y));}
//	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex((1ll*x*a.x+1ll*y*a.y)%mod, (1ll*x*a.y+1ll*y*a.x)%mod);}
};
struct Matrix
{
	int n;
	Complex a[N][N];
	void Init(int _n)
	{
		n=_n;
		memset(a,0,sizeof a);
	}
	Matrix operator *(const Matrix &x)
	{
		Matrix res; res.n=n;
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
			{
				Complex t(0,0);
				for(int k=0; k<n; ++k)
					t=t+a[i][k]*x.a[k][j];
				res.a[i][j]=t;
			}
		return res;
	}
}mat;
Matrix FP(Matrix x,int k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}
int FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

signed main()
{
	for(int T=read(); T--; )
	{
		int n=read(),m=read(),K=read();
		for(int i=1,u,v,w; i<=m; ++i)
			u=read()-1, v=read()-1, w=read(),
			e[u].pb(Edge{v,w}), e[v].pb(Edge{u,w});

		mat.Init(n);

		for(int i=0; i<n; ++i) coef[i]=FP(e[i].size(),mod-2);
		for(int i=0; i<n; ++i)
		{
			for(auto E:e[i])
			{
				if(E.w) mat.a[i][E.v]=Complex(0,coef[E.v]);
				else mat.a[i][E.v]=Complex(coef[E.v],0);
			}
		}
		mat=FP(mat,K);
		
		printf("%d\n",mat.a[n-1][0].y);

		for(int i=0; i<n; ++i) std::vector<Edge>().swap(e[i]);
	}

	return 0;
}
