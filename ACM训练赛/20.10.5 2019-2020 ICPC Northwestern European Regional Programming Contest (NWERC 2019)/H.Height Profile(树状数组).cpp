/*
936ms	2000KB
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
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-(x))
	void Clear()
	{
		for(int i=1; i<=n; ++i) t[i]=INF;
	}
	void Modify(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]=std::min(t[p],v);
	}
	int Query(int p)
	{
		int res=INF;
		for(; p; p^=lb(p)) res=std::min(t[p],res);
		return res;
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
int Find(LL v,int r)
{
	int l=1,mid;
	while(l<r)
		if(Ref[mid=l+r>>1]<v) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	int n=read()+1,Q=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	for(; Q--; )
	{
		int g=Read();
		for(int i=1; i<=n; ++i) Ref[i]=A[i]=h[i]-g*i;
		std::sort(Ref+1,Ref+1+n);
		int cnt=1;
		for(int i=2; i<=n; ++i) if(Ref[i]!=Ref[i-1]) Ref[++cnt]=Ref[i];
		for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);

		int ans=-1;
		T.n=cnt, T.Clear();
		for(int i=1; i<=n; ++i)
			ans=std::max(ans,i-(tmp[i]=T.Query(A[i]))), T.Modify(A[i],i);
		if(ans==-1) {puts("-1"); continue;}

		double ans2=ans;
		for(int r=1,l; r<=n; ++r)
			if((l=tmp[r])>1 && r-l==ans && h[l-1]-h[l]+g!=0)//left
				ans2=std::max(ans2,r-l+1.0*(Ref[A[r]]-Ref[A[l]])/(h[l-1]-h[l]+g));
		for(int r=1,l; r<n; ++r)
			if(r-(l=tmp[r])==ans && h[r]-h[r+1]+g!=0)//right
				ans2=std::max(ans2,r-l+1.0*(Ref[A[r]]-Ref[A[l]])/(h[r]-h[r+1]+g));
		printf("%.9f\n",ans2);

//		for(int i=1,t; i<=n; ++i)
//			if((t=tmp[i])>1 && i-t==ans)
//			{
//				double l=t-1,r=t,mid;
//				while(l+eps<r)
//				{
//					mid=(l+r)*0.5;
//					if(h[i]-h[t]+(h[t]-h[t-1])*(1-mid)>=g*(i-mid)) ans2=std::max(ans2,i-mid), r=mid;
//					else l=mid;
//				}
//			}
//		for(int i=1,t; i<n; ++i)
//			if(i-(t=tmp[i])==ans)
//			{
//				double l=i,r=i+1,mid;
//				while(l+eps<r)
//				{
//					mid=(l+r)*0.5;
//					if(h[i]-h[t]+(h[i+1]-h[i])*mid>=g*(mid-t)) ans2=std::max(ans2,mid-t), l=mid;
//					else r=mid;
//				}
//			}
	}

	return 0;
}
