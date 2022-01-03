/*
14964kb	3036ms
题意: 将树划分为k个连通块，要求每个连通块大小相同。输出可能的大小。
结论: 满足条件时颜色的节点数为k，当且仅当有n/k个节点满足它的子树是k的倍数(显然还有k|n)。
证明就不证了，说下理解(然而也说不清楚。。)。
比如一个点的子树大小为x*k，如果满足上述条件，即这棵子树(包含根节点)一定有x个点子树大小为k的倍数，且把sz[]为k的点依次删去，最后肯定能删掉整棵子树。
因为它就x*k那么大。。说不清楚啊。。想想应该是合理的。
因为父节点编号一定比子节点小，更新sz[]时倒序循环一遍即可，不需要DFS。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define XXX (19940105)
const int N=1200005;

int n,fa[N],sz[N],num[N],cnt,p[10005],lim[10005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=2; i<=n; ++i) if(!(n%i)) p[++cnt]=i,lim[cnt]=n/i;//if(i*i!=n) p[++cnt]=n/i;//这样可以枚举到sqrt(n)?
	for(int T=1; T<=10; ++T)
	{
		memset(sz,0,sizeof sz), memset(num,0,sizeof num);;
		for(int i=2; i<=n; ++i) fa[i]=T==1?read():((fa[i]+XXX)%(i-1)+1);//read()不怂233.
		for(int i=n; i; --i) sz[fa[i]]+=(++sz[i]);
		for(int i=1; i<=n; ++i) ++num[sz[i]];
		printf("Case #%d:\n1\n",T);//判掉1也行。
		for(int t,i=1; i<=cnt; ++i)
		{
			t=0;//子树sz为x*p[i]的节点个数 
			for(int j=1; j<=lim[i]; ++j) t+=num[j*p[i]];
			if(t*p[i]==n) printf("%d\n",p[i]);
		}
	}
	return 0;
}
