/*
312MS	1200K
$Description$
����$n,k,L$����ʾ����һ��$n$�����������ȫͼ��ÿ���ߵı�Ȩ��$[1,L]$֮�䡣���ж�����������ȫͼ���㣬$1$��$n$�����·Ϊ$k$��
$n,k\leq 12,\ L\leq10^9$��
$Solution$
���Ǳ�����ֱ��ö��$1$��ÿ��������·$d_i$�Ƕ��١�
���ڷ����������$d_i=d_j$����ô$i,j$֮��ı�Ȩ��㶨��������$d_i\lt d_j$����ô$i,j$֮��ı�Ȩ��С��$d_j-d_i$���Ҷ���$j$�����ٴ���һ��$i$����$d_i+e[i][j]=d_j$��
�����ĸ��Ӷ���$O(12^{13})$�ģ�$d_i\geq k$��ȫ��һ���㣩��

ע�⵽���ǲ������ľ���$d_i=x$�ĵ�����Щ�����Կ���ֱ��ö��$d_i=x$�ĵ��ж��ٸ���
$DFS$һ�£�����������ͺ��������Ӷ���$C_{n-1+k}^k$�ȣ�
**���壺**����Ҫǿ��$d_1=0,d_n=k$��
���ڵ�ǰ��$x$�������$t$����$d_i=x$������֮������������ߣ��������ǣ�$\prod_{i=0}^{t-1}L^i$������Ȼ��Ҫ�˸��������
Ȼ����$t$�����֮ǰ$m$�������ߣ������Ǵ���$d_i+e[i][j]=x$�����ƣ���ÿ����ģ���������$\prod_{i=1}^{m}(L-(x-d_i)+1)$���ݳ�һ�£��ټ���$\prod_{i=1}^{m}(L-(x-d_i))$���Ϳ�������
���Ҫ������·$\geq k$������Ҫ����������ڱ�Ȩ��Χ��xjb�����ɣ�������Ҫǡ��$=k$����
�������һ��$n$�����ߵķ��������ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
typedef long long LL;
const int N=15;

int n,K,L,C[N][N],now,d[N],pw[N];
LL Ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void DFS(int x,int coef)
{
	LL c1=1,c2=1;
	for(int i=1; i<=now; ++i) c1=c1*(L-x+d[i]+1)%mod, c2=c2*(L-x+d[i])%mod;
	LL c3=c1+mod-c2;
	if(x==K)
	{
		LL c=coef*c3%mod*pw[n-1-now]%mod;//n��������Ĺ��� 
		for(int i=now+1; i<n; ++i) c=c*c1%mod*pw[i-now-1]%mod;
		Ans+=c;
		return;
	}
	DFS(x+1,coef);
	int tmp=now,t=0;
	for(LL c=coef; now+1<n; )
		d[++now]=x, c=c*c3%mod*pw[t]%mod, ++t, DFS(x+1,c*C[n-1-now+t][t]%mod);
	now=tmp;
}

int main()
{
	C[0][0]=pw[0]=1;
	for(int i=1; i<=12; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int T=read(); T--; )
	{
		n=read(),K=read(),L=read();
		for(int i=1; i<=n; ++i) pw[i]=1ll*pw[i-1]*L%mod;
		Ans=0, d[now=1]=0, DFS(1,1), printf("%lld\n",Ans%mod);
	}

	return 0;
}
