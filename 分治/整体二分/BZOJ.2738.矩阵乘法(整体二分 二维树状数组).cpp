/*
4680ms	17.75MB
整体二分。把求序列第K小的树状数组改成二维树状数组就行了。
初始答案区间有点大，离散化一下。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define lb(x) ((x)&-(x))
//#define gc() getchar()
#define MAXIN 60000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=505,M=60005+N*N;

int n,m,Q,cnt,A[N*N],Ans[60005];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Operation
{
	int K,x1,y1,x2,y2,pos;//K=0: Modify (x1,y1):=pos
	Operation() {}
	Operation(int K,int x1,int y1,int x2,int y2,int pos):K(K),x1(x1),y1(y1),x2(x2),y2(y2),pos(pos) {}
}q[M],q1[M],q2[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace T
{
	int n,t[N][N];

	inline void Modify(int x,int y,int v)
	{
		for(int i=x; i<=n; i+=lb(i))
			for(int j=y; j<=n; j+=lb(j)) t[i][j]+=v;
	}
	inline void Clear(int x,int y)
	{
		for(int i=x; i<=n; i+=lb(i))
			for(int j=y; j<=n; j+=lb(j))
				if(t[i][j]) t[i][j]=0; else break;
	}
	inline int Query(int x,int y)
	{
		int res=0;
		for(int i=x; i; i^=lb(i))
			for(int j=y; j; j^=lb(j)) res+=t[i][j];
		return res;
	}
	inline int Query_Area(Operation q){//prefix sum
		return Query(q.x2,q.y2)-Query(q.x1-1,q.y2)-Query(q.x2,q.y1-1)+Query(q.x1-1,q.y1-1);
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t) return;
	if(l==r){
		for(int i=h; i<=t; ++i) if(q[i].K) Ans[q[i].pos]=A[l];
		return;
	}
	bool goon=0;
	for(int i=h; i<=t; ++i) if(q[i].K) {goon=1; break;}
	if(!goon) return;

	int mid=l+r>>1, midV=A[mid], t1=0, t2=0;
	for(int i=h; i<=t; ++i)
		if(q[i].K)
		{
			int tmp=T::Query_Area(q[i]);//这样好像少做几次加法！但是多copy两个int。。（你够了→_→）
			if(tmp>=q[i].K) q1[t1++]=q[i];
			else q[i].K-=tmp, q2[t2++]=q[i];
		}
		else
		{
			if(q[i].pos<=midV) T::Modify(q[i].x1,q[i].y1,1), q1[t1++]=q[i];
			else q2[t2++]=q[i];
		}
	for(int i=0; i<t1; ++i) if(!q1[i].K) T::Clear(q1[i].x1,q1[i].y1);
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	T::n=n=read(), m=read(), Q=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) q[++Q]=Operation(0,i,j,0,0,A[Q]=read());

	std::sort(A+1,A+1+Q), cnt=1;
	for(int i=2; i<=Q; ++i) if(A[i]!=A[i-1]) A[++cnt]=A[i];

	for(int x1,y1,x2,y2,i=1; i<=m; ++i)
		x1=read(),y1=read(),x2=read(),y2=read(),q[++Q]=Operation(read(),x1,y1,x2,y2,i);
	Solve(1,cnt,1,Q);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
