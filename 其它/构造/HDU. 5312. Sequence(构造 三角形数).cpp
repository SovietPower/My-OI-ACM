/*
748MS	2332Kb
$Description$
����$m$����$m$���ٿ��ɶ��ٸ�����$3n(n-1)+1\ (n\geq 1)$�������ɡ�
$T$�����ݡ�$m\leq10^9,\ T\leq10^4$��
$Solution$
> **�κ�һ���������������������/������������**��

���ٸ����ɿ��Կ�����������������Ϊ$A_n$������$3n(n-1)+1=6\times\frac{n(n-1)}{2}+1=6A_n+1$��
�����Ϊ$k$����$m=6(A_1+A_2+...+A_k)+k$��

* $k\geq 3$ʱ��$\sum A_i$�ɱ�ʾ����������$k=(m-1)\%6+1+6n\ (n\geq 0)$�����Դ𰸼�$(m-1)\%6+1$������$(m-1)\%6+1\geq 3$��
* $(m-1)\%6+1\lt 3$ʱ����$k=1��2$��ֱ������$1��2$�Ƿ���У������������$k+6\geq 3$һ�����С�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e4+5,INF=1e9;

int A[N];//19000
std::unordered_map<int,int> f;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int i=1; (A[i]=3*i*(i-1)+1)<=INF; ++i) f[A[i]]=1;

	for(int T=read(); T--; )
	{
		int n=read(),k=(n-1)%6+1;
		if(k==1) printf("%d\n",f.count(n)?1:7); //��Ҫдf[n]������ӵ�map/unordered_map���Ϊʲô�ŷ�����㣩 
		else if(k==2)
		{
			bool fg=0;
			for(int i=1,lim=n/2; A[i]<=lim; ++i)
				if(f.count(n-A[i])) {fg=1; break;} //ͬ�ϱ�дf[n-A[i]] 
			printf("%d\n",fg?2:8);
		}
		else printf("%d\n",k);
	}

	return 0;
}
