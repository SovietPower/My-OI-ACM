/*
218ms	3100KB
$Description$
����һ����$n$���������½���������ߣ�����$n+1$���㣩��
$k$��ѯ��ÿ�θ���$g$����$h[i]$��ʾ$i$���ĸ߶ȣ����������$[l,r]$����$\frac{h[r]-h[l]}{r-l}\geq g$��$l,r$Ϊ����ʵ������
$n\leq 10^5, k\leq 50$��
$Solution$
����ֻ����$l,r$ȡ������������
��$[l,r]$��������������$\frac{h[r]-h[l]}{r-l}\geq g$����$h[r]-gr\geq h[l]-gl$����$A[i]=h[i]-gi$����ÿ�������ǰ��ʹ��$A[i]\geq A[j]$��$j$���ɡ�
���$l,r$Ϊʵ�������׷���$[l,r]$һ����ǡ�ð��� ֻȡ������ʱ�����������е�һ������������������죩����$l,r$������һ�����������������ʵ��˵�������߶ε�б�ʶ����ţ����б������������ȡ������һ�ߣ������һ�߸�����һ������Ҫȡ��һ�ߣ���
������ ��ɢ��+��״����/�߶���ά��������Сֵ ���ȡ������ʱ�Ĵ𰸣��ٶ����п��ܵ������������������켴�ɡ�
�����ʱ����ǽⷽ�̣����ʱ��$l$�����ȡ$p$
$$h_r-gr=h_l-(h_l-h_{l-1})p-g(l-p)\\A_r-A_l=(h_{l-1}-h_l+g)p\\p=\frac{A_r-A_l}{h_{l-1}-h_l+g}=\frac{A_r-A_l}{A_{l-1}-A_l}$$

������ʱͬ��
����֪������Ϊʲô���ԣ�WA on test 3��... �ɶ��ֵİȣ���
�������˳˸��� ����һ��hhh
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,INF=1e9;

int h[N],tmp[N],A[N],Ref[N];
struct Segment_Tree
{
	#define S N<<2
	int mn[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	void Build(int l,int r,int rt)
	{
		if(l==r) {mn[rt]=A[l]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	int Query(int l,int r,int rt,int v)
	{
		if(l==r) return l;
		int m=l+r>>1;
		if(mn[ls]<=v) return Query(lson,v);
		return Query(rson,v);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	for(c=gc();isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read()+1,Q=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	for(; Q--; )
	{
		int g=Read();
		for(int i=1; i<=n; ++i) Ref[i]=A[i]=h[i]-g*i;

		int ans=0; T.Build(1,n,1);
		for(int i=1; i<=n; ++i)
			ans=std::max(ans,i-(tmp[i]=T.Query(1,n,1,A[i])));
		if(!ans) {puts("-1"); continue;}

		double ans2=ans;
		for(int r=1,l; r<=n; ++r)
			if((l=tmp[r])>1 && r-l==ans && h[l-1]-h[l]+g!=0)//left
				ans2=std::max(ans2,r-l+1.0*(A[r]-A[l])/(h[l-1]-h[l]+g));
		for(int r=1,l; r<n; ++r)
			if(r-(l=tmp[r])==ans && h[r]-h[r+1]+g!=0)//right
				ans2=std::max(ans2,r-l+1.0*(A[r]-A[l])/(h[r]-h[r+1]+g));
		printf("%.9f\n",ans2);
	}

	return 0;
}
