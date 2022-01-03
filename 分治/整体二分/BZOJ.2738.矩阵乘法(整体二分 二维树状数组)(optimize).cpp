/*
6980kb	10584ms
4224ms	7.23MB
整体二分。把求序列第K小的树状数组改成二维树状数组就行了。
因为这题是一开始给点，之后询问，so可以先处理该区间值在l~mid的修改，再处理询问。即二分标准可以直接用点的标号。
结构体的赋值可以改为赋值操作的编号。（~~这样内存没那么连续？~~想多了你）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define lb(x) ((x)&-(x))
//#define gc() getchar()
#define MAXIN 60000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=505,M=60005;

int n,m,Ans[M],q[M],q1[M],q2[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Point
{
	int x,y,val;
	Point() {}
	Point(int x,int y,int val):x(x),y(y),val(val) {}
	bool operator <(const Point &a)const{
		return val<a.val;
	}
}pt[N*N];
inline int read();
struct Operation//Query
{
	int K,x1,y1,x2,y2;
	inline void Input(){
		x1=read(),y1=read(),x2=read(),y2=read(),K=read();
	}
}op[M];

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
		for(int i=h; i<=t; ++i) Ans[q[i]]/*[op[q[i]].pos]*/=pt[l].val;
		return;
	}
	int mid=l+r>>1, t1=0, t2=0;
	for(int i=l; i<=mid; ++i) T::Modify(pt[i].x,pt[i].y,1);
	for(int now,tmp,i=h; i<=t; ++i)
	{
		now=q[i], tmp=T::Query_Area(op[now]);
		if(tmp>=op[now].K) q1[t1++]=now;
		else op[now].K-=tmp, q2[t2++]=now;
	}
	for(int i=l; i<=mid; ++i) T::Clear(pt[i].x,pt[i].y);
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	T::n=n=read(), m=read();
	int tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) pt[++tot]=Point(i,j,read());
	std::sort(pt+1,pt+1+tot);

	for(int i=1; i<=m; ++i) q[i]=i, op[i].Input();
	Solve(1,tot,1,m);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
