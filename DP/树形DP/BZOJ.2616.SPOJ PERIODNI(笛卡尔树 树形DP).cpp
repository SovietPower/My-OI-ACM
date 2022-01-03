/*
9636kb	516ms
ֱ�۵��뷨�ǹ����ѿ�������ÿ��ȡ��Сֵλ�û��ֵ����ߣ���������DP�������������ӵ������ǻ���Ӱ��ġ�
��$f[i][j]$��ʾ��$i$���ڵ㣬����$j$�����ķ�������
��$v$��$i$��һ�����ӣ������������ֵ�ת�ƣ���$$f'[i][j]=\sum_{k\leq j}f[v][j-k]f[i][k]$$

�����������׺󣬶���$i$�ڵ����ľ��Σ���߶���$h$�����$w$����$$f'[i][j]=\sum_{k\leq j}f[i][j-k]\cdot k!C_h^kC_{w-j+k}^k$$

Ȼ���ok�������Ӷ���$O(n^2k)$�������Խ��ѿ��������Ա���$n^2$��
$O(n)$���ѿ�����������ά��һ������ջ��ջ��Ԫ���ǵ�ǰ�����ұߵ�һ������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define C(n,m) (1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod)//n<m
#define gc() getchar()
typedef long long LL;
const int N=504,M=1e6+5;
const LL LIM=5e18;

int m,h[N],sk[N],fa[N],son[N][2],f[N][N],fac[M],ifac[M];//M!!!

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int DFS(int x)
{
	static int g[N];
	if(!x) return 0;
//	f[x][0]=1;
//	for(int i=0; i<2; ++i)
//		if(son[x][i])
//		{
//			int v=son[x][i],szv=DFS(v);
//			for(int j=0,v1; j<=sz; ++j)
//				if((v1=f[x][j]))
//					for(int k=0,v2; k<=szv&&j+k<=m; ++k)
//						if((v2=f[v][k]))
//							g[j+k]+=1ll*v1*v2%mod, Mod(g[j+k]);
//			sz+=szv;
//			for(int j=std::min(sz,m); ~j; --j) f[x][j]=g[j], g[j]=0;
//		}
	int ls=son[x][0],rs=son[x][1],a=DFS(ls),b=DFS(rs),m=::m;
	for(int i=0,v1; i<=a; ++i)
		if((v1=f[ls][i]))
			for(int j=0,v2; j<=b&&i+j<=m; ++j)
				if((v2=f[rs][j]))
					f[x][i+j]+=1ll*v1*v2%mod, Mod(f[x][i+j]);
	int h=::h[x]-::h[fa[x]],w=a+b+1;//sz
	for(int i=std::min(w,m); ~i; --i)
	{
		LL tmp=0;
		for(int j=0; j<=i&&j<=h; ++j) tmp+=1ll*f[x][i-j]*fac[j]%mod*C(h,j)%mod*C(w-i+j,j), tmp>=LIM&&(tmp%=mod);
		f[x][i]=tmp%mod;
	}
	return w;
}

int main()
{
	int n=read(),m=read(),mx=n; ::m=m;//mx=max(hi,n)!
	for(int i=1; i<=n; ++i) mx=std::max(mx,h[i]=read());

	fac[0]=1;
	for(int i=1; i<=mx; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[mx]=FP(fac[mx],mod-2);
	for(int i=mx; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;

	int top=0; h[sk[0]=0]=0;//���-1Ҫ�Ļ�����mdzz��dfs�õ�h[fa[root]]��
	for(int i=1; i<=n; ++i)
	{
		while(h[sk[top]]>h[i])
		{
			int a=sk[top--];
			if(h[sk[top]]>h[i]) son[fa[a]=sk[top]][1]=a;
			else son[fa[a]=i][0]=a;
		}
		sk[++top]=i;
	}
	while(top>1) fa[sk[top]]=sk[top-1], son[sk[top-1]][1]=sk[top], --top;
	int root=sk[1];
	f[0][0]=1, DFS(root), printf("%d\n",f[root][m]);

	return 0;
}
