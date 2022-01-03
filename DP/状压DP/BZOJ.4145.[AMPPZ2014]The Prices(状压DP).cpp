/*
27452kb	5284ms
�Ƚ����״ѹDP��
�տ�ʼд�鷳��...
$f[i][s]$��ʾ������ǰ$i$���̵꣬������Ʒ״̬Ϊ$s$����С���ѡ�
����д��һ��һ��ȥ$i$�̵��$f[i]$��$f[i][s]=f[i-1][s]+dis[i]$����Ȼ���ٺͲ�ȥ$i$�̵��$f[i-1]$ȡ��$\min$��
���Ӷ���$O(nm2^m)$��...

�����Ż�������$f[s]$��ʾ��ĳ���̵���$s$���ϵ���Ʒ����С���ۡ�Ȼ����$g[s]$��ʾ���������̵���$s$���ϵ���С���ۣ���$g[s]=\min(f[s],g[s']+f[s\ \text{xor}\ s'])$��
���Ӷ�$O(n2^m+3^m)$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define lb(x) (x&-x)
#define gc() getchar()
typedef long long LL;
const int N=103,M=16;

int dis[N],cost[N][M+1],f[N][(1<<M)+1],ref[(1<<M)+1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),lim=(1<<m)-1;
	for(int i=0; i<m; ++i) ref[1<<i]=i;
	for(int i=1; i<=n; ++i)
		for(int j=(dis[i]=read(),0); j<m; ++j) cost[i][j]=read();
	memset(f,0x3f,sizeof f), f[0][0]=0;
	for(int i=1; i<=n; ++i)
	{
		for(int s=0; s<=lim; ++s) f[i][s]=f[i-1][s]+dis[i];
		for(int s=0; s<lim; ++s)
		{
			for(int ss=s^lim,j; ss; ss^=lb(ss))
			{
				j=ref[lb(ss)];
				f[i][s|(1<<j)]=std::min(f[i][s|(1<<j)],f[i][s]+cost[i][j]);
			}
		}
		for(int s=0; s<=lim; ++s) f[i][s]=std::min(f[i][s],f[i-1][s]);
	}
	printf("%d\n",f[n][lim]);

	return 0;
}
