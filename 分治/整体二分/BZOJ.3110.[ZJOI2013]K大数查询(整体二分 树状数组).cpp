/*
4976KB	1220MS
$Description$
��$n$�����ؼ�����ʼΪ�ա�$m$�β�����
1. ��$x$���뵽$[l,r]$�Ŀ��ؼ��У�
2. ��ѯ$[l,r]$�Ŀ��ؼ��У���$k$������Ƕ��١�
$n,m\leq 5\times 10^4,\ k\lt 2^{63}$��
$Solution$
�����������ǵ�KС(������״����)�����K�����תΪ���n-K+1С�����������������һ��n��
ע�⵽�������ľ���ֵ<=N�����������Ĵ�С��ϵ������ ��K����ǵ�KС�ˡ�������A[i]��Ϊn-A[i]�������ʱ��Ҳ��Ϊn-Ans[i]��
�������һ����C����ֱ�����߶�������ӡ�����״����ά������С�ܶࡣ
n*m=2.5*1e9 > MAX_INT Ҳ��û˭�ˡ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define lb(x) (x&-x)
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=50005;

int n,m,A[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
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
	int n;
	LL sum1[N],sum2[N];

	inline void Modify(int p,int v)
	{
		for(int i=p; i<=n; i+=lb(i))
			sum1[i]+=v, sum2[i]+=p*v;
	}
	inline void Modify_Range(int l,int r,int v){
		Modify(l,v), Modify(r+1,-v);
	}
	inline LL Query(int p)
	{
		LL res1=0,res2=0;
		for(int i=p; i; i^=lb(i))
			res1+=sum1[i], res2+=sum2[i];
		return res1*(p+1)-res2;
	}
	inline LL Query_Range(int l,int r){
		return Query(r)-Query(l-1);
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t) return;
	if(l==r){
		for(int i=h; i<=t; ++i) if(q[i].K) Ans[q[i].pos]=l;
		return;
	}
	bool goon=0;//��ѯ��ʱֱ��return��
	for(int i=h; i<=t; ++i) if(q[i].K) {goon=1; break;}
	if(!goon) return;

	int mid=l+r>>1, t1=0, t2=0;
	for(int i=h; i<=t; ++i)
		if(q[i].K)
		{
			LL tmp=T::Query_Range(q[i].l,q[i].r);
			if(tmp>=q[i].K) q1[t1++]=q[i];
			else q[i].K-=tmp, q2[t2++]=q[i];
		}
		else
		{
			if(q[i].pos<=mid) T::Modify_Range(q[i].l,q[i].r,1), q1[t1++]=q[i];
			else q2[t2++]=q[i];
		}
	for(int i=0; i<t1; ++i) if(!q1[i].K) T::Modify_Range(q1[i].l,q1[i].r,-1);//q1��_��
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	T::n=n=read(), m=read(); int tot=0;
	for(int l,r,i=1; i<=m; ++i)
		if(read()==1) l=read(), r=read(), q[i]=Operation(0,l,r,n-read());
		else l=read(), r=read(), q[i]=Operation(readll(),l,r,++tot);
	Solve(-N,N,1,m);
	for(int i=1; i<=tot; ++i) printf("%d\n",n-Ans[i]);

	return 0;
}
