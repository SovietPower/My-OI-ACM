/*
38448kb	2488ms
这是一种错误的暴力BFS（扩展的时候没有更新扩展的点）。但是加个random_shuffle好像也不知道能怎么卡？
预处理每个点能到的区间$[l,r]$。
对于$i,i+1$的一扇门，如果钥匙在$i$的右边，连边$i\to i+1$，表示从$i$出发到不了$i+1$；否则连边$i+1\to i$。没有门的话就缩成一个点。
如果存在边$i\to j$，那么$j$的区间包含$i$，而$i$肯定不包含$j$。从无入度的点暴力扩展，对于它能到的点用它更新一下然后再暴力扩展，复杂度是$O(n)$的。
还有一种做法是[这个](https://www.cnblogs.com/mjtcn/p/10424510.html)，感觉也有些妙，复杂度也是$O(n)$。

另外直接对每个点$DFS$加上记忆化，写的巧一点好像也是$O(n)$的（我表示卡不掉）。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

int pos[N],L[N],R[N],A[N];
std::vector<int> vec[N];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool BFS1(int t,int s)
{
	int l=s,r=s;
	while(t<l||t>r)
	{
		bool f=0;
		while(!pos[r]||(pos[r]<=r&&pos[r]>=l)) f=1, ++r;
		while(!pos[l-1]||(pos[l-1]<=r&&pos[l-1]>=l)) f=1, --l;
		if(!f) break;
	}
	return t>=l&&t<=r;
}
void Subtask1(int n,int m,int Q)
{
	while(Q--) puts(BFS1(read(),read())?"YES":"NO");
}
void Subtask2(int n,int m,int Q)
{
	for(int i=1; i<n; ++i) if(pos[i]) vec[pos[i]].push_back(i);
	L[1]=1, R[1]=n, q.push(N);
	for(int x=2; x<n; ++x)
	{
		if(pos[x-1])
		{
			L[x]=x;
			for(int i=L[x-1]; i<x; ++i)
				for(int j=0,l=vec[i].size(); j<l; ++j) q.push(vec[i][j]);
			while(q.top()<x) q.pop();
			R[x]=q.top();
		}
		else L[x]=L[x-1], R[x]=R[x-1];
	}
	for(int s,t; Q--; ) s=read(),t=read(),puts(L[s]<=t&&t<=R[s]?"YES":"NO");
}
void BFS2(int s)
{
	int l=s,r=s;
	while(1)
	{
		bool f=0;
		while(!pos[r]||(pos[r]<=r&&pos[r]>=l))
		{
			f=1, ++r;
			if(L[r]) l=std::min(l,L[r]), r=std::max(r,R[r]);
		}
		while(!pos[l-1]||(pos[l-1]<=r&&pos[l-1]>=l))
		{
			f=1, --l;
			if(L[l]) l=std::min(l,L[l]), r=std::max(r,R[l]);
		}
		if(!f) break;
	}
	L[s]=l, R[s]=r;
}

int main()
{
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);

	const int n=read(),m=read(); int Q=read();
	bool f=1;
	for(int i=1,x; i<=m; ++i)
	{
		x=read(), pos[x]=read();
		if(pos[x]>x) f=0;
	}
	pos[n]=N, pos[0]=N;
	if(1ll*n*m<=1e7) return Subtask1(n,m,Q),0;
	if(f) return Subtask2(n,m,Q),0;
	for(int i=1; i<=n; ++i) A[i]=i;
	std::random_shuffle(A+1,A+n+1);//mt199...
	for(int i=1,x=A[i]; i<=n; x=A[++i]) BFS2(x);
	for(int s,t; Q--; ) s=read(),t=read(),puts(L[s]<=t&&t<=R[s]?"YES":"NO");

	return 0;
}
