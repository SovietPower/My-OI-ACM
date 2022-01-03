/*
0MS	1260K
��ͷDP�����ڱ�������ֻ��Ҫ��¼֮ǰ$m$�����ӵ�$m+1$����ͷ�Ƿ���ڡ�
ת��ʱ������ߡ��ϱ��Ƿ��в�ͷ���ۡ���λ�������д�ĺܷ��㡣
��Ϊ���DP����ѹѹά����Ҳ����д�ĺò�ֱ��=-=���������Ǵ���һ������ת�ƣ������һ�н�״̬����һλת����һ�С����Կ�������Ĵ��롣
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=12;

LL f[2][(1<<N)+2];//m+1
bool mp[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Work(int x,int y,int lim,LL *f,LL *g)
{
	if(mp[x][y])
		for(int s=0,p1=1<<y-1,p2=1<<y; s<lim; ++s)
		{
			f[s^p1^p2]+=g[s];
			if((s>>y-1&1)!=(s>>y&1)) f[s]+=g[s];
		}
	else
		for(int s=0,p1=1<<y-1,p2=1<<y; s<lim; ++s)
			if(!(s&p1) && !(s&p2)) f[s]=g[s];
			else f[s]=0;
}

int main()
{
	for(int T=1,T2=read(); T<=T2; ++T)
	{
		int n=read(),m=read(),l1=1<<m,l2=1<<m+1;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j) mp[i][j]=read();
		int p=0; memset(f[p],0,sizeof f[p]);
		f[p][0]=1;
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=m; ++j)
			{
				p^=1, memset(f[p],0,sizeof f[p]);
				Work(i,j,l2,f[p],f[p^1]);
			}
			if(i!=n)
			{
				p^=1, memset(f[p],0,sizeof f[p]);
				for(int s=0; s<l1; ++s) f[p][s<<1]=f[p^1][s];
			}
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",T,f[p][0]);//f[n][m][0]
	}
	return 0;
}
