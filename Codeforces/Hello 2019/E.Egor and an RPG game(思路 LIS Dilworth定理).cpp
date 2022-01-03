/*
358ms	3600KB
$Description$
��$k$��ʾ��һ������$A_i$���ֳ����ɸ�������ݼ������У����������и�������Сֵ����$f(n)$��ʾ����$1...n$�������У�$k$�����ֵ�����е���...���������ٵ����л������У�$f(n)$������$1$��$n$���������������������Ǹ�������
$T$��ѯ�ʣ�ÿ�θ���һ��$1...n$������$A_i$������Ҫ����ֳ�$k\leq f(n)$�ε�����ݼ������в������������Ҫ��$k$��С��ֻ��$\leq f(n)$����
$T,\sum n\leq10^5$��

$Solution$
���ȿ���$f(n)$�Ƕ��١�
�����һЩ���б�������е������$\{1, 3, 2, 6, 5, 4, 10, 9, 8, 7, 15, 14, 13, 12, 11\}$��$k=5$���ܷ���$k$����������$\frac{i(i+1)}{2}\leq n$��������$i$��
�������ǲ�$f(n)=k$������$k$����������$\frac{k(k+1)}{2}\leq n$����������
��ʵ��ȷʵ����֤����Ҳ���Ƕ�������$n<\frac{k'(k'+1)}{2}$�����ܽ����зֳɲ�����$k'-1$�����������С�

��$LIS$Ϊ��ʱ������������У���$|LIS|\geq k'$��ɾ��$LIS$�����ʱ$n-|LIS|<\frac{k'(k'+1)}{2}-k'=\frac{(k'-1)k'}{2}$����Ȼ��һ��ͬ���Ĺ�ģ��С�����⡣
����$|LIS|\leq k'-1$����$Dilworth$����$��С������=�����$�������о���$�½������и���=����������г���\leq k'-1$��������$i<j,A_i>A_j$���������$i\to j$�����������$LIS$������һ��·�����½������У�
���Դ�ʱ���Խ����зֳɲ�����$k'-1$���½������С�

֤���ˡ���Ҳ�ǹ��񡣡���֪����Ŀ��ܵ����������ÿ��ˡ���

���$|LIS|$���½�������ʱ����$f[i]$��ʾ��$i$��β��$LIS$���ȣ���$f[i]$��ͬ��λ�û��ֵ�ͬһ���������оͿ����ˡ�����Ȼ��Щ���ǵݼ��ģ�
���Ӷ�$O(n\sqrt{n}\log n)$����Ҫ$O(\sqrt{n})$��$LIS$����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int tot,A[N],f[N];
std::vector<int> ans[N];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res=std::max(res,t[p]);
		return res;
	}
	inline void Modify(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]=std::max(t[p],v);
	}
	inline void Clear(int p)
	{
		for(; p<=n; p+=lb(p))
			if(!t[p]) break;
			else t[p]=0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Solve(int n)
{
	static bool vis[N];
	int mx=0;
	for(int i=1; i<=n; ++i) mx=std::max(mx,f[i]=T.Query(A[i]-1)+1), T.Modify(A[i],f[i]);
	for(int i=1; i<=n; ++i) T.Clear(A[i]);
	int l=1,r=sqrt(n*2),mid;
	while(l<r)//k(k+1)/2<=n (k+1)(k+2)/2>n
		if(mid=l+r>>1,mid*(mid+1)>n*2) r=mid;//���ܻᱬint������k���Ͻ���sqrt(2n)��
		else l=mid+1;
	int k=l;
	if(mx>=k)
	{
		++tot;
		for(int i=n,now=mx,v=N; i; --i)
			if(f[i]==now && A[i]<v)
				--now, v=A[i], vis[i]=1, ans[tot].push_back(A[i]);
		std::reverse(ans[tot].begin(),ans[tot].end());
		int cnt=0;
		for(int i=1; i<=n; ++i)
			if(!vis[i]) A[++cnt]=A[i];
			else vis[i]=0;
		if(cnt) Solve(cnt);
	}
	else
	{
		for(int i=1; i<=n; ++i) ans[tot+f[i]].push_back(A[i]);
		tot+=mx;
	}
}

int main()
{
	for(int Tot=read(); Tot--; )
	{
		const int n=read(); T.n=n;
		for(int i=1; i<=n; ++i) A[i]=read();
		tot=0, Solve(n);
		printf("%d\n",tot);
		for(int i=1; i<=tot; ++i,putchar('\n'))
		{
			printf("%d",ans[i].size());
			for(int j=0,l=ans[i].size(); j<l; ++j) printf(" %d",ans[i][j]);
			ans[i].clear();
		}
	}
	return 0;
}
