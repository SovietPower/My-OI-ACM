/*
6196kb	340ms
如果某天能够赚钱，那么一定会在这天把手上的金券全卖掉。同样如果某天要买，一定会把所有钱花光。
那么令$f_i$表示到第$i$天所拥有的最多钱数（此时手上没有任何金券），可以选择什么都不干，$f_i=f_{i-1}$；也可以从之前的某一天$j$花$f_j$的钱买金券，在第$i$天全卖掉。用第$j$天的信息算一下买了多少$A,B$，就可以得到第$i$天卖了多少钱。
所以有$f_i=\max\{f_{i-1},\ A_i\frac{f_jk_j}{A_jk_j+B_j}+B_i\frac{f_j}{A_jk_j+B_j}\}$。
把后面那部分写成直线的形式：$\frac{f_i}{B_i}-\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j}=\frac{f_j}{A_jk_j+B_j}$，令$x_j=\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j},\ y_j=\frac{A_i}{B_i}*\frac{f_j}{A_jk_j+B_j}$，$\frac{f_i}{B_i}-\frac{A_i}{B_i}x_j=y_j$。要求用$k=-\frac{A_i}{B_i}$的直线去切$(x_j,y_j)$使得截距最大，也就是维护上凸壳。
但$x$即每个决策点不是单调的，就需要平衡树/CDQ分治去维护凸包。
**平衡树：**
节点按$x$排序。每个节点维护与左边点和右边点的斜率$lk,rk$。（树上的节点都是凸包上的，凸包内部的就不要了）
对于新的决策点$x$，直接先插入到平衡树中。
然后将$x$转到根。先找左边第一个能与$x$构成凸包的点：若当前点$y$与前一个点的斜率$lk\gt k(x,y)$，那么如果$y$右边还有在凸包上的点，就继续向右找（没有就结束）。否则若$lk\lt k(x,y)$，则应继续往左找。
找右边第一个能与$x$构成凸包的点同理。
最后，如果$x$就在凸包里面，即$lk(x)<rk(x)$，就要把$x$从平衡树中删掉。
查询就根据斜率直接查询最优决策点了。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-9
typedef long long LL;
const int N=1e5+5;
const double INF=1ll<<60;

double f[N],X[N],Y[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline double read()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c)&&c!='.';c=gc());
	for(;isdigit(c);x=x*10+c-'0',c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=(c-'0')*y,y*=0.1,c=gc());
	return x;
}
inline double GetK(int i,int j)
{
	return fabs(X[i]-X[j])<eps?INF:(Y[i]-Y[j])/(X[i]-X[j]);
}
struct SPLAY
{
	#define ls son[x][0]
	#define rs son[x][1]
	int root,tot,fa[N],son[N][2];
	double lk[N],rk[N];

	void Rotate(int x,int &k)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(a==k) k=x;
		else son[b][son[b][1]==a]=x;
		fa[a]=x, fa[x]=b, fa[son[x][r]]=a, son[a][l]=son[x][r], son[x][r]=a;
	}
	void Splay(int x,int &k)
	{
		while(x!=k)
		{
			int a=fa[x];
			if(a!=k) son[a][1]==x^son[fa[a]][1]==a?Rotate(x,k):Rotate(a,k);
			Rotate(x,k);
		}
	}
	int Find(double k)
	{
		int x=root;
		while(x)
		{
			if(lk[x]>=k && rk[x]<=k) return x;
			if(lk[x]<k) x=son[x][0];
			else x=son[x][1];
		}
		return x;
	}
	int Pre(int x)
	{
		int y=son[x][0],res=y;
		while(y)
		{
			if(lk[y]>=GetK(x,y)) res=y, y=son[y][1];
			else y=son[y][0];
		}
		return res;
	}
	int Nxt(int x)
	{
		int y=son[x][1],res=y;
		while(y)
		{
			if(rk[y]<=GetK(x,y)) res=y, y=son[y][0];
			else y=son[y][1];
		}
		return res;
	}
	void Insert(int x,double xx)
	{
		int f=0,p=x; x=root;
		while(x) f=x, x=son[x][xx>X[x]];
		x=p, fa[x]=f, son[f][xx>X[f]]=x;
		Splay(x,root);
	}
	void Maintain(int x)
	{
		if(ls)
		{
			int y=Pre(x);
			Splay(y,ls), son[y][1]=0;
			lk[x]=rk[y]=GetK(x,y);
		}
		else lk[x]=INF;
		if(rs)
		{
			int y=Nxt(x);
			Splay(y,rs), son[y][0]=0;
			rk[x]=lk[y]=GetK(x,y);
		}
		else rk[x]=-INF;
		if(lk[x]<=rk[x])
		{
			int y=rs;
			fa[root=ls]=0, son[root][1]=y, fa[y]=root;
			rk[root]=lk[y]=GetK(root,y);
		}
	}
}T;

int main()
{
	int n=read(); f[0]=read();
	for(int i=1; i<=n; ++i)
	{
		double A=read(),B=read(),Rate=read();
		int j=T.Find(-A/B);
		f[i]=std::max(f[i-1],A*X[j]+B*Y[j]);
		Y[i]=f[i]/(A*Rate+B), X[i]=Y[i]*Rate;
		T.Insert(i,X[i]), T.Maintain(i);
	}
	printf("%.3lf\n",f[n]);

	return 0;
}
