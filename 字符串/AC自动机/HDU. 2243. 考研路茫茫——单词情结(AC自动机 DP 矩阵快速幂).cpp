/*
15MS	1508K
$Description$
����$n$������$L$���󳤶Ȳ�����$L$�����ٺ���$n$�����е�һ�����ַ����ж��ٸ���
$n\leq 5,\ L\lt 2^{31},\ ����\leq 5$���ַ���ΪСд��ĸ��

$Solution$
��ʵ����[[JSOI2007]�ı�������](https://www.cnblogs.com/SovietPower/p/8978642.html)��ǿ�档
��$n$������AC�Զ�����
���Ǵ����϶�ʱ����$f[i][j]$��ʾ��ǰ������$i$���ַ���ƥ��λ�����Զ�����$j$�ڵ㡣
��
$$f[i][j]=\sum_{k\in pre[j]}f[i-1][k]+26\cdot f[i-1][j]\cdot \big[end[j]=1\big]$$

����$pre[j]$��ʾ$son$����$j$�ڵ�Ľڵ㼯�ϣ�$end[j]$��ʾ$j$�Ƿ���$n$������ĳ��������ֹ�ڵ㡣���ڽ�AC�Զ���ʱ����
�𰸾���$\sum_{i=1}^{L}\sum_{end[j]=1}f[i][j]$��


��ΪDP����$i$�޹ص����Ե��ƣ����Կ��Ծ�������ݡ�
��ΪҪ��$i$��ͣ����Ծ����һ�б�ʾ��$f[i-1][j]$��$sum_{i-1}$����ͣ�ע����һ��ֻ��$end[j]=1$��λ�ò���$1$����
�����$(tot+1)\cdot(tot+1)$��ת�ƾ��󣬿����ݼ��ɣ�$tot$ΪAC�Զ����ڵ�������
���Ӷ�$O(n^3\log L)$��$n$ΪAC�Զ����ڵ���$25$��

ͬ���������㲻�Ϸ��ķ�������DPʽ����΢��һ�£���������ݣ������ܷ�����$\sum_{i=1}^L26^i$������ͬ�����Ծ�������ݣ�����Exgcd��$2^{64}$��Ԫ����
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
