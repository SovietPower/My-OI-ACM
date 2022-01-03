/*
109ms	13300KB
$Description$
��άƽ���ϸ���$n$�����Σ���������ƽ����$x$������޳�ֱ�ߣ�ʹ����ֱ�ߴ����ľ�������ࣨ����ֱ�ߴ���ͬһ������ֻ��һ�������󴩹����ε����������
$Solution$
����$x$������û�õġ����ֻ���߶ζ˵����ã�������ɢ����$2n$���㣨$n$���߶Σ�ȡ����ʹ�����߶���ࣩ��
Ȼ�����ǿ���ö��ѡ��ÿһ�������ڵ�λ�á���ֻҪ�ܱ�֤����λ�ò����㾭���õ���߶μ��ɡ�
��ֻҪ�߶����ͺ��ˡ�����������һ����˵�ʱ�����߶μ����߶����������һ����ά��һ��ȫ�����ֵ��ok��
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N],L[N],R[N],sum[N];
std::vector<int> vec[N];
struct Segment_Tree
{
	#define S N<<2
	int mx[S],tag[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define Upd(rt,v) mx[rt]+=v, tag[rt]+=v
	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Upd(rt,1); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R);
		if(m<R) Modify(rson,L,R);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Find(int r,int x)
{
	int l=1,mid;
	while(l<r)
		if(A[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	int m=read(),cnt=0;
	for(int i=1; i<=m; ++i)
		read(), A[++cnt]=R[i]=read(), read(), A[++cnt]=L[i]=read();
	std::sort(A+1,A+1+cnt);
	int tmp=cnt; cnt=1;
	for(int i=2; i<=tmp; ++i) if(A[i]!=A[i-1]) A[++cnt]=A[i];
	int n=cnt;
	for(int i=1; i<=m; ++i) L[i]=Find(cnt,L[i]), R[i]=Find(cnt,R[i]);
	for(int i=1; i<=m/*m!!!!*/; ++i) ++sum[L[i]], --sum[R[i]+1], vec[L[i]].push_back(R[i]);
	for(int i=1; i<=n; ++i) sum[i]+=sum[i-1];

	int res=1;
	for(int i=n; i; --i)
	{
		res=std::max(res,sum[i]+T.mx[1]);
		for(auto j:vec[i]) T.Modify(1,n,1,i,j);
	}
	printf("%d\n",res);

	return 0;
}
