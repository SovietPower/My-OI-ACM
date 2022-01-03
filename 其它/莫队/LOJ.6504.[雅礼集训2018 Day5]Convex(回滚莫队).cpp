/*
6527ms	8292K
莫队。发现只需要维护前驱后继就可以了。
但是加入一个点需要找到它当前的前驱后继，很麻烦还带个$\log$。
但是如果只有删除某个点，只需要更新一下它的前驱后继即可。
用回滚莫队就好惹。
撤销，即重新加入点时，按顺序把每个点的前驱后继改回来即可。

不需要求斜率=-=
`atan2(y,x)`：返回点$(x,y)$与$x$轴正半轴的夹角。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=150005;

int bel[N],L[N],R[N],A[N];
LL Now,Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const
	{
		return bel[l]==bel[x.l]?r>x.r:l<x.l;
	}
}q[N];
struct Vec
{
	int x,y; double k;
	Vec(int y=0,int x=0):x(x),y(y) {k=atan2(y,x);}//x,y读反了调半小时=-= 
	LL operator *(const Vec &a)const {return 1ll*x*a.y-1ll*y*a.x;}
}p[N];
typedef Vec Point;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline bool cmp(int a,int b)
{
	return p[a].k<p[b].k;
}
void Add(int x)
{
	int l=L[x],r=R[x];
	R[l]=x, L[r]=x;
}
void Delete(int x)
{
	int l=L[x],r=R[x];
	Now+=p[l]*p[r]-p[l]*p[x]-p[x]*p[r], R[l]=r, L[r]=l;
}

int main()
{
	const int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i) p[i]=Point(read(),read()),bel[i]=(i-1)/size+1,A[i]=i;
	std::sort(A+1,A+1+n,cmp);
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);
	for(int i=1,now=1; i<=bel[n]&&now<=Q; ++i)
	{
		if(bel[q[now].l]!=i) continue;
		int Ln=(i-1)*size+1,l=Ln,r=n,las=0,beg=0;
		Now=0;
		for(int j=1,pos; j<=n; ++j)
			if(A[j]>=Ln)
			{
				pos=A[j];
				if(las) Now+=p[las]*p[pos], L[pos]=las, R[las]=pos, las=pos;
				else beg=las=pos;
			}
		R[las]=beg, L[beg]=las, Now+=p[las]*p[beg];
		while(bel[q[now].l]==i)
		{
			while(r>q[now].r) Delete(r--);
			LL tmp=Now;
			while(l<q[now].l) Delete(l++);
			Ans[q[now++].id]=Now, Now=tmp;
			while(l>Ln) Add(--l);
		}
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
