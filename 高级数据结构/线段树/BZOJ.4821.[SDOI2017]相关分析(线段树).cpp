/*
25744kb	4992ms
恶心的拆式子。。然后就是要维护$\sum x_i,\ \sum y_i,\ \sum x_iy_i,\ \sum x_i^2$。
操作三可以看成初始化一遍，然后同操作二。
对于操作二的$S,T$：
$\sum x_i,\ \sum y_i$就是区间加。
$xy\to(x+S)(y+T)\to xy+xT+yS+ST$，维护了区间和后，直接加上$xT+yS+ST$即可。
$x^2\to(x+S)^2\to x^2+2Sx+S^2$，同上。
除了恶心点，都很简单。注意一下标记下传顺序。

注意会爆`long long`，要用`double`存。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int x[N],y[N];
LL sum[N],sum2[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int tags[S],tagt[S];
	double X,Y,XY,XX,x[S],y[S],xy[S],xx[S],initx[S],initxx[S];
	bool init[S];
	#undef S
	#define Set(rt) tags[rt]=tagt[rt]=0, x[rt]=y[rt]=initx[rt], xx[rt]=xy[rt]=initxx[rt], init[rt]=1
	#define Upd(rt,s,t,l) xy[rt]+=x[rt]*t+y[rt]*s+1.0*(l)*s*t, xx[rt]+=x[rt]*(s<<1)+1.0*(l)*s*s, x[rt]+=1.0*(l)*s, y[rt]+=1.0*(l)*t, tags[rt]+=s, tagt[rt]+=t
	#define Update(rt) x[rt]=x[ls]+x[rs], y[rt]=y[ls]+y[rs], xy[rt]=xy[ls]+xy[rs], xx[rt]=xx[ls]+xx[rs]
	inline void InitQuery() {X=Y=XY=XX=0;}
//	inline void Print(int rt) {printf("Print: rt:%d x:%lld y:%lld xy:%lld xx:%lld\n",rt,x[rt],y[rt],xy[rt],xx[rt]);}
//	void BuildInit(int l,int r,int rt)
//	{
//		if(l==r) {initx[rt]=inity[rt]=l, initxy[rt]=initxx[rt]=1.0*l*l; return;}
//		int m=l+r>>1;
//		BuildInit(lson), BuildInit(rson);
//		initx[rt]=initx[ls]+initx[rs], inity[rt]=inity[ls]+inity[rs], initxy[rt]=initxy[ls]+initxy[rs], initxx[rt]=initxx[ls]+initxx[rs];
//	}
	void Build(int l,int r,int rt)
	{
		initx[rt]=sum[r]-sum[l-1], initxx[rt]=sum2[r]-sum2[l-1];
		if(l==r) {x[rt]=::x[l], y[rt]=::y[l], xy[rt]=x[rt]*y[rt], xx[rt]=x[rt]*x[rt]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	inline void PushDown(int rt,int m)
	{
		int l=ls,r=rs;
		if(init[rt])
			Set(l), Set(r), init[rt]=0;
		if(tags[rt]||tagt[rt])
			Upd(l,tags[rt],tagt[rt],(m-(m>>1))), Upd(r,tags[rt],tagt[rt],(m>>1)), tags[rt]=tagt[rt]=0;
	}
	void Init(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Set(rt); return;}
		PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Init(lson,L,R);
		if(m<R) Init(rson,L,R);
		Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int s,int t)
	{
		if(L<=l && r<=R) {Upd(rt,s,t,r-l+1); return;}
		PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,s,t);
		if(m<R) Modify(rson,L,R,s,t);
		Update(rt);
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			X+=x[rt], Y+=y[rt], XY+=xy[rt], XX+=xx[rt];
			return;
		}
		PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Query(lson,L,R);
		if(m<R) Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	freopen("relative.in","r",stdin);
	freopen("relative.out","w",stdout);

	const int n=read(); int m=read();
	for(int i=1; i<=n; ++i) x[i]=read();
	for(int i=1; i<=n; ++i) y[i]=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+i, sum2[i]=sum2[i-1]+1ll*i*i;

	#define S 1,n,1
	T.Build(S);
	for(int l,r,s,t; m--; )
		switch(read())
		{
			case 1:
			{
				l=read(), r=read(), T.InitQuery(), T.Query(S,l,r);
				double xba=T.X/(r-l+1), yba=T.Y/(r-l+1), up=T.XY-yba*T.X, down=T.XX-xba*T.X;
				printf("%.10lf\n",up/down); break;
			}
			case 2:
			{
				l=read(), r=read(), s=read(), t=read();
				T.Modify(S,l,r,s,t); break;
			}
			case 3:
			{
				l=read(), r=read(), s=read(), t=read();
				T.Init(S,l,r), T.Modify(S,l,r,s,t); break;
			}
		}

	return 0;
}
