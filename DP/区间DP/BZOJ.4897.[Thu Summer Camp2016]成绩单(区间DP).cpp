/*
29392kb	1952ms
$Description$
��������$a_n$��$A,B$��ÿ�δ�������ɾ��������һ�Σ�����Ϊ$A+B*(\max-\min)^2$��ɾ����ʣ������ǰ�ơ���ɾ�����С���ۡ�
$n\leq 50,a_i\leq 1000$��
$Solution$
��Ȼ�Ǹ�����DP����$f[l][r]$��ʾȫ����������$[l,r]$����С���ѡ�
��Ϊ�ǿ���ͨ��ɾ�������Ӵ���ɾ�����еģ����Բ�����ֱ��ת�ơ�������ֻ�������Сֵ�йأ���������$g[l][r][j][k]$��ʾ������$[l,r]$�е���ɾ��ֻʣ��Ȩֵ��$[j,k]$�е�������С���ѣ�Ҳ������ʣ��������СֵΪ$j$�����ֵΪ$k$�����һ��ȡ��$[j,k]$��Щ����ɾ������$[l,r]$����Ϊ�˷���ת��ǿ���Ҷ˵�$r$������ͬ�����������һ��ɾ����
Ȼ��$f,g$�Ϳ��Ի���ת���ˣ�$g[l][r][\min(val_r,j)][\max(val_r,k)]=\min\{g[l][i][j][k]+f[i+1][r-1]\}$��$f[l][r]=\min\{f[l][i]+g[i+1][r][j][k]+Cost(j,k)\}$��
���Ӷ�$O(n^5)$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define Sqr(x) ((x)*(x))
typedef long long LL;
const int N=52;

int w[N],ref[N],f[N][N],g[N][N][N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	const int n=read(),A=read(),B=read();
	for(int i=1; i<=n; ++i) w[i]=ref[i]=read();
	std::sort(ref+1,ref+1+n);
	int cnt=std::unique(ref+1,ref+1+n)-ref-1;
	for(int i=1; i<=n; ++i) w[i]=std::lower_bound(ref+1,ref+1+cnt,w[i])-ref;

	memset(f,0x3f,sizeof f), memset(g,0x3f,sizeof g);
	for(int i=1; i<=n; ++i) f[i][i]=A, f[i][i-1]=0, g[i][i][w[i]][w[i]]=0;
	f[n+1][n]=0;
	for(int len=1; len<n; ++len)
		for(int l=1,r; (r=l+len)<=n; ++l)
		{
			for(int i=l; i<r; ++i)
				for(int j=1; j<=cnt; ++j)
					for(int k=j,nj=std::min(j,w[r]),nk; k<=cnt; ++k)
						nk=std::max(k,w[r]), g[l][r][nj][nk]=std::min(g[l][r][nj][nk],g[l][i][j][k]+f[i+1][r-1]);
			for(int i=l-1; i<r; ++i)
				for(int j=1; j<=cnt; ++j)
					for(int k=j; k<=cnt; ++k)
						f[l][r]=std::min(f[l][r],f[l][i]+g[i+1][r][j][k]+A+B*Sqr(ref[k]-ref[j]));
//						f[l][r]=std::min(f[l][r],g[l][i][j][k]+f[i+1][r]+A+B*Sqr(ref[k]-ref[j]));
		}
	printf("%d\n",f[1][n]);

	return 0;
}
