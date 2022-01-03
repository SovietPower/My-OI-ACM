/*
15MS	1508K
$Description$
给定$n$个串和$L$，求长度不超过$L$且至少含有$n$个串中的一个的字符串有多少个。
$n\leq 5,\ L\lt 2^{31},\ 串长\leq 5$。字符集为小写字母。

$Solution$
其实就是[[JSOI2007]文本生成器](https://www.cnblogs.com/SovietPower/p/8978642.html)加强版。
对$n$个串建AC自动机。
考虑串长较短时，令$f[i][j]$表示当前构造了$i$个字符，匹配位置在自动机的$j$节点。
则：
$$f[i][j]=\sum_{k\in pre[j]}f[i-1][k]+26\cdot f[i-1][j]\cdot \big[end[j]=1\big]$$

其中$pre[j]$表示$son$连向$j$节点的节点集合，$end[j]$表示$j$是否是$n$个串中某个串的终止节点。都在建AC自动机时处理。
答案就是$\sum_{i=1}^{L}\sum_{end[j]=1}f[i][j]$。


因为DP是与$i$无关的线性递推，所以可以矩阵快速幂。
因为要对$i$求和，所以矩阵加一行表示对$f[i-1][j]$和$sum_{i-1}$的求和（注意这一行只有$end[j]=1$的位置才是$1$）。
构造出$(tot+1)\cdot(tot+1)$的转移矩阵，快速幂即可（$tot$为AC自动机节点数）。
复杂度$O(n^3\log L)$，$n$为AC自动机节点数$25$。

同样可以先算不合法的方案数（DP式子稍微变一下，矩阵快速幂），用总方案数$\sum_{i=1}^L26^i$减掉（同样可以矩阵快速幂，或者Exgcd求$2^{64}$逆元）。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef unsigned long long ull;
const int N=55,S=26;

ull f[N*10][N];
char s[N];
struct AC_Automaton
{
	int tot,q[N],end[N],fail[N],son[N][S];
	std::vector<int> pre[N];
	void Init()
	{
		memset(end,0,tot+1<<2);
		memset(son,0,(tot+1)*S*4);
		for(int i=0; i<=tot; ++i) pre[i].clear();
		tot=0;
	}
	void Insert(char *s)
	{
		int l=strlen(s+1),u=0;
		for(int i=1,c; i<=l; ++i)
		{
			if(!son[u][c=s[i]-'a']) son[u][c]=++tot;
			u=son[u][c];
		}
		end[u]=1;
	}
	void Build()
	{
		int h=0,t=0;
		for(int i=0; i<S; ++i)
			if(son[0][i]) fail[son[0][i]]=0, q[t++]=son[0][i];
		while(h<t)
		{
			int x=q[h++];
			end[x]|=end[fail[x]];
			for(int v,i=0; i<S; ++i)
				if(son[x][i])
					fail[v=son[x][i]]=son[fail[x]][i], q[t++]=v;
				else son[x][i]=son[fail[x]][i];
		}
		for(int i=0; i<=tot; ++i)
			if(!end[i])
				for(int j=0; j<S; ++j)
					pre[son[i][j]].pb(i);
	}
}ac;

struct Matrix
{
	int n;
	ull a[N][N];
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
				ull t=0;
				for(int k=0; k<n; ++k)
					t+=a[i][k]*x.a[k][j];
				res.a[i][j]=t;
			}
		return res;
	}
};

Matrix FP(Matrix x,int k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}

int main()
{
	int n,L;
	while(~scanf("%d%d",&n,&L))
	{
		ac.Init();
		while(n--) scanf("%s",s+1), ac.Insert(s);
		ac.Build();

//Brute Force
//		memset(f,0,sizeof f);
//		f[0][0]=1;
//		int tot=ac.tot;
//		for(int i=1; i<=L; ++i)
//			for(int j=0; j<=tot; ++j)
//			{
//				if(ac.end[j]) f[i][j]=f[i-1][j]*26;
//				for(auto v:ac.pre[j])
//					f[i][j]+=f[i-1][v];
//			}
//		ull Ans=0;
//		for(int i=1; i<=L; ++i)
//			for(int j=0; j<=tot; ++j)
//				if(ac.end[j]) Ans+=f[i][j];
//		printf("%llu\n\n",Ans);

		Matrix A; A.Init(ac.tot+2);
		int n=ac.tot+1;
		for(int i=0; i<n; ++i)
		{
			if(ac.end[i]) A.a[i][i]=26;
			for(auto v:ac.pre[i]) ++A.a[i][v];
		}
		for(int i=0; i<n; ++i)
			if(ac.end[i]) A.a[n][i]=1;
		A.a[n][n]=1;
		A=FP(A,L);

		ull res=A.a[n][0];
		for(int i=0; i<n; ++i) if(ac.end[i]) res+=A.a[i][0];
		printf("%llu\n",res);
	}

	return 0;
}
