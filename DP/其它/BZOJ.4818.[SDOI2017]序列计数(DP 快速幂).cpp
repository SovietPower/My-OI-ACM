/*
30120kb	2680ms
���ȱ���DP��$f[i][j][0/1]$��ʾ��ǰ�ǵ�$i$�������������ĺ�ģ$P$Ϊ$j$����û�г��ֹ������ķ�������
���Ƿ���ÿһ�ε�ת�ƶ���һ���ġ�
����û�е���ά$0/1$���������DP����$f[i]$��$f[i]$��ϣ��õ��ľ���$f[2\times i]$��$i$��DP��Ľ����$i$��DP��Ľ����ϣ�����$2\times i$��DP��Ľ�����������У�$f[2\times i][(j+k)\%p]=\sum\limits_{j=0}^{P-1}\sum\limits_{k=0}^{P-1}f[i][j]\times f[i][k]$��
������ά�������˼�ǣ���û�г��ֹ��������ݳ�һ�£���û��ʹ��������DP�����Ľ������ȥ��һ������������DP�����Ľ�������Ǵ��ˡ�
���ԾͿ��Ա���/�����ݣ�������Ҫ��������ݣ���һ��DP��$O(p^2)$�ģ����Ӷ�$O(m+p^2\log n)$��

��ʵ��[[SDOI2015]����ͳ��](https://www.luogu.org/problemnew/show/P3321)�Ƚ��������кܶ���д��ѭ�����������ȷʵ�����Ż���$O(m+p\log p\log n)$������������Ȼ�ò���...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 20170408
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=2e7+5,M=102;

bool notP[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Init(const int n)
{
	static int cnt,P[N>>3];
	notP[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&1ll*i*P[j]<=n; ++j)//LL!
		{
			notP[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Mult(int *f,int *g,int P)
{
	static int res[M];
	memset(res,0,sizeof res);
	for(int i=0; i<P; ++i)
		if(f[i])
			for(int j=0,v; j<P; ++j)
				if(g[j])
					v=i+j>=P?i+j-P:i+j, Add(res[v],1ll*f[i]*g[j]%mod);
	memcpy(f,res,sizeof res);
}
int Solve(int k,int m,int P)
{
	static int x[M],t[M];
	memset(x,0,sizeof x);
	for(int i=1; i<=m; ++i) if(notP[i]) Add(x[i%P],1);//++ not =1!!
	memcpy(t,x,sizeof x);
	for(--k; k; k>>=1,Mult(x,x,P))
		if(k&1) Mult(t,x,P);
	return t[0];
}

int main()
{
	const int n=read(),m=read(),P=read();
	Init(m);
	int t=Solve(n,m,P);
	for(int i=1; i<=m; ++i) notP[i]=1;
	printf("%d\n",(Solve(n,m,P)+mod-t)%mod);

	return 0;
}
