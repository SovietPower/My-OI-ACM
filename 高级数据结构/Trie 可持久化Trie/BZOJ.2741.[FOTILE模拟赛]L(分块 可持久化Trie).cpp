/*
11020kb	8232ms
首先记sum为前缀异或和，那么区间s[l,r]=sum[l-1]^sum[r]。即一个区间异或和可以转为求两个数的异或和。
那么对[l,r]的询问即求[l-1,r]中某两个数异或的最大值。
区间中某一个数和已知的一个数异或的最大值可以用可持久化Trie O(logv)求出。所以尽量确定一个数，再在区间中求最大值。
而且数据范围提醒我们可以分块。
用head[i]表示第i块的开头位置，Max(l,r,x)表示x与[l,r]中某一个数异或的最大值，f[i][j]表示从第i块的开始到位置j，某两个数异或的最大值是多少。
那么 f[i][j] = max(f[i-1][j-1], Max(head[i], j-1, A[j]))。可以在$O(nsqrt(n)logv)$时间内预处理。（A[]是前缀和）
查询的时候，设x表示l后面的第一块，若l,r在同一块里，则 ans = Max(l, r, A[i]), i∈[l,r]。（对啊 和自己异或也没什么意义）
否则 ans = max(f[x][r], Max(l, r, A[i]))，i∈[l,begin[x]-1]。
对[1,r]的询问，可能会有同上一题一样的边界问题（可以异或0）？把A[0]=0也试一遍就行了。。
复杂度同样$O(qsqrt(n)logv)$。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000//为什么50000WA+TLE啊 QAQ 
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 30
typedef long long LL;
const int N=12005,M=111;

int root[N],A[N],bel[N],H[N],f[M][N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*32
	int tot,son[S][2],sz[S];
	void Insert(int x,int y,int v)
	{
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c]=++tot, son[x][c^1]=son[y][c^1];
			x=tot, y=son[y][c];
			sz[x]=sz[y]+1;
		}
	}
	int Query(int x,int y,int v)
	{
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[y][c]]-sz[son[x][c]]>0)
				x=son[x][c], y=son[y][c], res|=1<<i;
			else
				c^=1, x=son[x][c], y=son[y][c];
		}
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i)
		bel[i]=(i-1)/size+1, T.Insert(root[i]=++T.tot,root[i-1],A[i]=A[i-1]^read());//^不是+ == 

	H[1]=1;
	for(int i=2,lim=bel[n]; i<=lim; ++i) H[i]=H[i-1]+size;
	for(int i=1,lim=bel[n]; i<=lim; ++i)
		for(int j=H[i]+1,rtl=root[H[i]-1]; j<=n; ++j)
			f[i][j]=std::max(f[i][j-1],T.Query(rtl,root[j-1],A[j]));

	for(int l,r,x,y,ans=0; Q--; )
	{
		x=((LL)read()+ans)%n+1, y=((LL)read()+ans)%n+1;//read()%n+ans%n 都可能爆int。。and LL要在括号里面。。
		l=std::min(x,y), r=std::max(x,y);
		--l, ans=0;
		if(bel[l]==bel[r])
			for(int i=l,rtl=root[std::max(0,l-1)],rtr=root[r]; i<=r; ++i)
				ans=std::max(ans,T.Query(rtl,rtr,A[i]));
		else
		{
			ans=f[bel[l]+1][r];
			for(int i=l,lim=H[bel[l]+1]-1,rtl=root[std::max(0,l-1)],rtr=root[r]; i<=lim; ++i)
				ans=std::max(ans,T.Query(rtl,rtr,A[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
