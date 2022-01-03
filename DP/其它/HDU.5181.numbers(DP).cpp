/*
483MS	1868K
$Description$ 
��$1,2,\cdots,n(n\leq 300)$������ջ/��ջ��������$m(m\leq 90000)$������$x$Ҫ��$y$֮ǰ��ջ�����ƣ��ʺϷ��ĳ�ջ�����ж����֡�
$Solution$
û�����ƾ��Ǹ��������������������ƾ�Ҫ���Ǻú�DP�ˡ���
���е���ջ&��ջ˳����Թ���һ�ö���������ÿһ�������еĵ�һ���ȸ������ĸ��ڵ��ջ�硣
$f[i][j]$��ʾ�������ڵ�Ϊ$i$�����еĵ���$i\sim j$��$i+1\sim j$����$i$��ջ�硣��ʼΪ:$f[i][i]=1$.
�����Ƶ�DP���̾���: $$f[i][j]=\sum_{k=i+1}^jf[i][k-1]*f[k][j]$$ 
(����ǵ���ö��$i$��)
��������ƣ�ֱ����DP��$f[i][]$��ѷǷ���$f[i][]$���0�����ˡ���
���$j$Ҫ��$k$ǰ��ջ($j<k$)����ô$f[j][k],f[j][k+1],\cdots$���ǷǷ���($f[][]$��Ȼ�Ǵ���С���Ǹ���)��
��$j>k$ʱ��$f[k][1],\cdots,f[k][j-1]$�ǷǷ��ġ�
���Ĵ�Ӧ��$f[0][n]$.
ע�����������$i$��$i$ǰ����ôֱ��0��
���������$f[][]$�ϲ�����������ˡ���https://ksmeow.moe/numbers_hdu5181_sol/
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
const int N=305;

int n,L[N],R[N],f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int T=read(),m; bool flag;
	while(T--)
	{
		flag=0;
		n=read(),m=read();
		for(int i=0; i<=n; ++i) L[i]=0,R[i]=n+1;
		for(int x,y,i=1; i<=m; ++i)
		{
			x=read(),y=read();
			if(x<y) R[x]=std::min(R[x],y);
			else if(x>y) L[y]=std::max(L[y],x);
			else flag=1;
		}
		if(flag) {puts("0"); continue;}
		memset(f,0,sizeof f);
		for(int i=n; ~i; --i)
		{
			f[i][i]=1;
			for(int j=i+1; j<=n; ++j)
				for(int k=i+1; k<=j; ++k)
					(f[i][j]+=1ll*f[i][k-1]*f[k][j]%mod)%=mod;
			for(int j=1; j<L[i]; ++j) f[i][j]=0;
			for(int j=R[i]; j<=n; ++j) f[i][j]=0;
		}
		printf("%d\n",f[0][n]);
	}
	return 0;
}
