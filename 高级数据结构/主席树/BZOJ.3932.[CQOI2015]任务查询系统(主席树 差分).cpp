/*
82080kb	3672ms
对于这一区间的操作，我们可以想到差分+前缀和(感觉也没什么别的了。。)。
同时对于本题我们能想到主席树，而主席树正是利用前一个节点建树的。
所以离散化、按时间排序，把操作拆成单点加和减即可。
另外优先级会有重，权值线段树是去重后的，所以要记录sz[](即有sz[]个该值 是sum[])并根据这个算出k个。
但是对于同一根节点每次修改必须新建logn个节点？是的，因为每改一个节点都不能和之前的路径共用，需要新建。
注意每个询问拆成了两个，空间是2nlogn！
longlong!
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,S=N*40;//size!

int n,m,cnt,ref[N],root[N];
struct Operation
{
	int p,val,tag;
	Operation() {}
	Operation(int _p,int _v,int _t):p(_p),val(_v),tag(_t) {}
	bool operator <(const Operation &a)const{
		return p<a.p;
	}
}q[N<<1];

namespace T
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,sz[S],son[S][2]; LL sum[S];
	inline void Update(int rt){
		sum[rt]=sum[lson]+sum[rson];
	}
	void Insert(int rt,int &y,int l,int r,int p,int v)
	{
		sz[y=++tot]=sz[rt]+v, sum[y]=sum[rt];
		if(l==r) sum[y]+=ref[p]*v;//别直接用p！
		else{
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p,v);
			else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p,v);
			Update(y);
		}
	}
	LL Query(int rt,int l,int r,int k)
	{
		if(l==r) return sz[rt]?sum[rt]/sz[rt]*k:0;
		if(sz[lson]==k) return sum[lson];
		else if(sz[lson]<k) return sum[lson]+Query(rson,(l+r>>1)+1,r,k-sz[lson]);
		else return Query(lson,l,l+r>>1,k);
	}
}

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(),m=read();
	int tot=n<<1;
	for(int s,e,i=0; i<n; ++i)
		s=read(),e=read(),ref[i+1]=read(),q[i<<1]=Operation(s,ref[i+1],1),q[i<<1|1]=Operation(e+1,ref[i+1],-1);
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	std::sort(q,q+tot), q[tot].p=m+1;
	for(int i=0; i<tot; ++i) q[i].val=Find(q[i].val);
	for(int i=1,now=0; i<=m; root[i+1]=root[i],++i)//m还是时间范围！
		while(q[now].p<=i/*&& now<tot*/)
			T::Insert(root[i]/*(赋值后)在root[i]的基础上建*/,root[i],1,cnt,q[now].val/*不在这写Find(q[].val)好像更快？*/,q[now].tag), ++now;
	int x,a,b,c; LL res=1;
	while(m--)
		x=read(),a=read(),b=read(),c=read(),printf("%lld\n",res=T::Query(root[x],1,cnt,1+(res*a%c+b)%c));

	return 0;
}
