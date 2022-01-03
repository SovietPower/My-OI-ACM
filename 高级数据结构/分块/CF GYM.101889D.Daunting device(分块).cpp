/*
202ms	1400KB
$Description$
$n$个位置，初始每个位置颜色都为$1$。
$m$次操作，每次给定$p,x$，计算当前有多少个位置颜色为$p$，并用答案计算出给定区间$[l,r]$，将$[l,r]$染色为$x$。
最后输出出现次数最多的颜色的出现次数。
$Solution$
考虑暴力分块，每个块维护一个标记$tag_i$，若$tag_i\neq 0$表示块$i$颜色均为$tag_i$，否则颜色不统一。
修改时对于$tag_i\neq 0$的块可以$O(1)$更新$tag$，否则需要$O(\sqrt n)$暴力更新。更新的时候$O(1)$维护一下颜色出现次数$sum$。
考虑一下复杂度。每次暴力更新都会使$tag=0$的块变为统一颜色的块，而每次操作最多产生$2$个$tag=0$的块，所以暴力更新的总复杂度为$O(2n\sqrt n)$，非暴力更新总复杂度$O(n\sqrt n)$。
注意分块右端点是`min(n,bel[R]*size)`（右端点的边界问题）！
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,B=316;

int n,size,A[N],sum[N],bel[N],tag[N];
int CNT=0;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Modify(int l,int r,int c)
{
	++CNT;
	for(int i=l; i<=r; ++i) --sum[A[i]], A[i]=c;
}
void Cover(int l,int r,int c)
{
	for(int i=bel[l]+1; i<bel[r]; ++i)
		if(tag[i]) sum[tag[i]]-=size, sum[c]+=size, tag[i]=c;
		else Modify((i-1)*size+1,i*size,0), sum[c]+=size, tag[i]=c;
	int L=bel[l],t=std::min(r,L*size);
	if(tag[L])
	{
		for(int i=(L-1)*size+1,x=tag[L]; i<l; ++i) A[i]=x;
		for(int i=r+1,x=tag[L],lim=L*size; i<=lim; ++i) A[i]=x;
		sum[tag[L]]-=t-l+1, sum[c]+=t-l+1;
		tag[L]=0, Modify(l,t,c);
	}
	else Modify(l,t,c), sum[c]+=t-l+1;
	int R=bel[r];
	if(L!=R)
	{
		if(tag[R])
		{
			for(int i=r+1,t=std::min(n,R*size)/*对n取min!!!*/,x=tag[R]; i<=t; ++i) A[i]=x;
			sum[tag[R]]-=r-(R-1)*size, sum[c]+=r-(R-1)*size;
			tag[R]=0, Modify((R-1)*size+1,r,c);
		}
		else Modify((R-1)*size+1,r,c), sum[c]+=r-(R-1)*size;
	}
}

int main()
{
	int n=read(),C=read(),m=read(); size=sqrt(n), ::n=n;
	sum[1]=n;
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1;
	int cnt=bel[n];
	for(int i=1; i<=cnt; ++i) tag[i]=1;
	for(; m--; )
	{
		int S=sum[read()],x=read(),A=read(),B=read(),l=(A+1ll*S*S)%n+1,r=(A+1ll*(S+B)*(S+B))%n+1;
		l>r&&(std::swap(l,r),0), Cover(l,r,x);
	}
	int ans=sum[1];
	for(int i=2; i<=C; ++i) sum[i]>ans&&(ans=sum[i]);
	printf("%d\n",ans);

	return 0;
}
