/*
6196kb	340ms
���ĳ���ܹ�׬Ǯ����ôһ��������������ϵĽ�ȯȫ������ͬ�����ĳ��Ҫ��һ���������Ǯ���⡣
��ô��$f_i$��ʾ����$i$����ӵ�е����Ǯ������ʱ����û���κν�ȯ��������ѡ��ʲô�����ɣ�$f_i=f_{i-1}$��Ҳ���Դ�֮ǰ��ĳһ��$j$��$f_j$��Ǯ���ȯ���ڵ�$i$��ȫ�������õ�$j$�����Ϣ��һ�����˶���$A,B$���Ϳ��Եõ���$i$�����˶���Ǯ��
������$f_i=\max\{f_{i-1},\ A_i\frac{f_jk_j}{A_jk_j+B_j}+B_i\frac{f_j}{A_jk_j+B_j}\}$��
�Ѻ����ǲ���д��ֱ�ߵ���ʽ��$\frac{f_i}{B_i}-\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j}=\frac{f_j}{A_jk_j+B_j}$����$x_j=\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j},\ y_j=\frac{A_i}{B_i}*\frac{f_j}{A_jk_j+B_j}$��$\frac{f_i}{B_i}-\frac{A_i}{B_i}x_j=y_j$��Ҫ����$k=-\frac{A_i}{B_i}$��ֱ��ȥ��$(x_j,y_j)$ʹ�ýؾ����Ҳ����ά����͹�ǡ�
��$x$��ÿ�����ߵ㲻�ǵ����ģ�����Ҫƽ����/CDQ����ȥά��͹����
**ƽ������**
�ڵ㰴$x$����ÿ���ڵ�ά������ߵ���ұߵ��б��$lk,rk$�������ϵĽڵ㶼��͹���ϵģ�͹���ڲ��ľͲ�Ҫ�ˣ�
�����µľ��ߵ�$x$��ֱ���Ȳ��뵽ƽ�����С�
Ȼ��$x$ת������������ߵ�һ������$x$����͹���ĵ㣺����ǰ��$y$��ǰһ�����б��$lk\gt k(x,y)$����ô���$y$�ұ߻�����͹���ϵĵ㣬�ͼ��������ң�û�оͽ�������������$lk\lt k(x,y)$����Ӧ���������ҡ�
���ұߵ�һ������$x$����͹���ĵ�ͬ��
������$x$����͹�����棬��$lk(x)<rk(x)$����Ҫ��$x$��ƽ������ɾ����
��ѯ�͸���б��ֱ�Ӳ�ѯ���ž��ߵ��ˡ�
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
