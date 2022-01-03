/*
整体二分求的是第K小(利用树状数组)。求第K大可以转为求第n-K+1小，但是这样好像得求一个n。
注意到所有数的绝对值<=N，将所有数的大小关系反过来 第K大就是第K小了。所有数A[i]改为n-A[i]，输出的时候也改为n-Ans[i]。
区间加入一个数C可以直接用线段树区间加。
n*m=2.5*1e9 > MAX_INT 也是没谁了。。
标记永久化替代PushDown可以减小常数，但是怎么不对exm？
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=50005;

int n,m,A[N],Ans[N];
struct Operation
{
	LL K; int l,r,pos;//K!=0:Query [l,r] K;	K=0:Add [l,r] pos.
	Operation() {}
	Operation(LL K,int l,int r,int p):K(K),l(l),r(r),pos(p) {}
}q[N],q1[N],q2[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL readll()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
namespace T
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1

	LL sum[N<<2],all[N<<2];

	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		sum[rt]+=1ll*v*(R-L+1);
		if(L<=l && r<=R) all[rt]+=v;
		else
		{
			int m=l+r>>1;
			if(L<=m) Modify(ToL,L,m,v);
			if(m<R) Modify(ToR,m+1,R,v);
		}
	}
	LL Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return sum[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return 1ll*all[rt]*(R-L+1)+Query(ToL,L,R)+Query(ToR,L,R);
			else return 1ll*all[rt]*(R-L+1)+Query(ToL,L,R);
		return 1ll*all[rt]*(R-L+1)+Query(ToR,L,R);
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t) return;
	if(l==r){
		for(int i=h; i<=t; ++i) if(q[i].K) Ans[q[i].pos]=l;
		return;
	}
	bool goon=0;//无询问时直接return。
	for(int i=h; i<=t; ++i) if(q[i].K) {goon=1; break;}
	if(!goon) return;

	int mid=l+r>>1, t1=0, t2=0;
	for(int i=h; i<=t; ++i)
		if(q[i].K)
		{
			LL tmp=T::Query(1,n,1,q[i].l,q[i].r);
			if(tmp>=q[i].K) q1[t1++]=q[i];
			else q[i].K-=tmp, q2[t2++]=q[i];
		}
		else
		{
			if(q[i].pos<=mid) T::Modify(1,n,1,q[i].l,q[i].r,1), q1[t1++]=q[i];
			else q2[t2++]=q[i];
		}
	for(int i=0; i<t1; ++i) if(!q1[i].K) T::Modify(1,n,1,q1[i].l,q1[i].r,-1);//q1
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	n=read(), m=read(); int tot=0;
	for(int l,r,i=1; i<=m; ++i)
		if(read()==1) l=read(), r=read(), q[i]=Operation(0,l,r,n-read());
		else l=read(), r=read(), q[i]=Operation(readll(),l,r,++tot);
	Solve(-N,N,1,m);
	for(int i=1; i<=tot; ++i) printf("%d\n",n-Ans[i]);

	return 0;
}
