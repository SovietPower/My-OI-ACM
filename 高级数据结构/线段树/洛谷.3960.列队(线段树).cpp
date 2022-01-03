/*
1736ms	54284kb
先考虑一行的情况。每次操作为在序列中取出一个元素，然后放到取完后的第n个位置。如果我们预留n+q个位置，那这个操作就相当于线段树单点删除和单点加入。
扩展到多行。我们发现对最后一列的操作和对某一行的操作是相同的（取出一个，放到末尾一个）。
于是我们可以用n+1棵动态开点线段树维护。
有些细节：比如删除后不需要真插到线段树里。。用vector即可。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+4;

int n,m,R,root[N];
std::vector<LL> v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*18//*2
	#define lson son[x][0],l,m
	#define rson son[x][1],m+1,r
	int tot,son[S][2],sum[S];//不需要直接记区间点数啊== 记删除点数就行 
	#undef S

	int Delete(int &x,int l,int r,int p)
	{
		if(!x) x=++tot; ++sum[x];
		if(l==r) return l;
		int m=l+r>>1,tmp=m-l+1-sum[son[x][0]];
		if(tmp<p) return Delete(rson,p-tmp);
		return Delete(lson,p);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
LL Solve1(int x,LL tmp)
{
	int p=T.Delete(root[0],1,R,x);
	LL ans= p<=n?(LL)p*m:v[0][p-n-1];
	v[0].push_back(tmp?tmp:ans);
	return ans;
}
LL Solve2(int x,int y)
{
	int p=T.Delete(root[x],1,R,y);
	LL ans= p<m?(1ll*(x-1)*m+p):v[x][p-m];
	v[x].push_back(Solve1(x,ans));
	return ans;
}

int main()
{
	n=read(),m=read(); int Q=read(); R=std::max(n,m)+Q;
	for(int x,y; Q--; )
	{
		x=read(),y=read();
		if(y==m) printf("%lld\n",Solve1(x,0));
		else printf("%lld\n",Solve2(x,y));
	}
	return 0;
}
