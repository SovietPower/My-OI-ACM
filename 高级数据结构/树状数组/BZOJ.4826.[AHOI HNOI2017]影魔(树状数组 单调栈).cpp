/*
25340kb	2440ms
��$x$��ߵ�һ��������ĵ�Ϊ$L$���ұߵ�һ��������ĵ�Ϊ$R$���������������
1. ��������$[L,R]$����Ϊ$P1$��
2. ������˵���$L$���Ҷ˵���$x+1\sim R-1$�����䣬�𰸸���$P2$��
3. ������˵���$L+1\sim x-1$���Ҷ˵���$R$�����䣬��Ҳ����$P2$��
�����ﲻ������$[L,x]$��$[x,R]$�Ĺ��ף������������㡣����

Ȼ�������ߣ���ѯ�ʰ��Ҷ˵��������ֻ��$1,3$�����������$R$������ÿ����Ӧ��Χ�ڵ���˵���Ϲ��׼��ɡ�����ʵ�������һ����˵���$[q_l,q_r]$�ڵĺͣ��������ڴ��Ǹ��µ�$R$ʱ������$[q_l,q_r]$�ĺ͡�
���ڵ�$2$������Ƚ��鷳��Ҫ���$O(n)$������ӣ�
���ǰ����������ӡ�ע�⵽�Ҷ˵���$p$��ͳ��$L$�Ĺ���$P2$������$L$�����Ҷ˵���$p$ʱ�Ĺ��׼�$P2$��һ���ģ����ԾͿ�����$L$��������$x+1\sim R-1$��$P2$��
�����Ļ���˵�Ĺ��׿��ܻ���㣬���µ�$L-1$��ʱ����$[q_l,q_r]$��ѯ�ʼ�ȥ$[q_l,q_r]$�ĺͼ��ɡ�

��һ����ⷽʽ��
Ҳ���Կ��ǰ�$[l,r]$�Ĺ��׿���ƽ���ϵĵ�$(l,r)$��ͬ�����ߣ����ֻ��$1,3$���ں�����$R$���Ķ�Ӧ������϶�Ӧ�Ĵ𰸣�ѯ��$[l,r]$���Ǻ������궼��$[l,r]$�ľ��εĺ͡�
����$2$��ͬ����ķ����������$L$������Ӧ�Ҷ˵���Ϲ��ס���Ȼ$(x,y)$��$(y,x)$�Ĺ�����ͬ�������൱�ڰ�ԭ�Ⱥ��ŵĳ���������ŵġ�ע�⵽ÿ��ѯ�ʶ��ǶԽ�����$y=x$�ϵ������Σ�������ô���ǶԵġ�

���ֶ���ͬ��������ӡ�������ͣ�������״���顣
���Ӷ�$O(n\log n)$��

�������$[i,i+1]$��������Ĵ�û��ͳ�Ƶ������ϼ��ɡ�

�ټ򵥼�һ��**��״���������޸ġ��������**��
���������޸ĵ����ѯ��ά���������$d_i$��ǰ׺�ͣ���ô$$\begin{aligned}sum[1..p]&=\sum_{i=1}^p\sum_{j=1}^id_j\\&=\sum_{i=1}^p(p-i+1)d_i\\&=(p+1)\sum_{i=1}^pd_i-\sum_{i=1}^pi\cdot d_i\end{aligned}$$

ά��$d_i$��$i\cdot d_i$��ǰ׺�ͼ��ɣ������޸ľ���������һ��ĵ��㡣��Ҫ���...����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int A[N],sk[N],L[N],R[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,p,id,val;
	bool operator <(const Quries &x)const
	{
		return p<x.p;
	}
}q[N<<1];
struct Opt
{
	int l,r,p,val;
	bool operator <(const Opt &x)const
	{
		return p<x.p;
	}
}opt[N*3];
struct BIT
{
	int n,t1[N]; LL t2[N];
	#define lb(x) (x&-x)
	inline void Add(int p,int v)
	{
		for(int v2=p*v; p<=n; p+=lb(p)) t1[p]+=v,t2[p]+=v2;
	}
	inline void Modify(int l,int r,int v)
	{
		Add(l,v), Add(r+1,-v);
	}
	inline LL Query2(int x)
	{
		LL res1=0,res2=0;
		for(int p=x; p; p^=lb(p)) res1+=t1[p],res2+=t2[p];
		return res1*(x+1)-res2;
	}
	inline LL Query(int l,int r)
	{
		return Query2(r)-Query2(l-1);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	static LL Ans[N];

//	freopen("sf.in","r",stdin);
//	freopen("sf.out","w",stdout);

	const int n=read(),Q=read(),P1=read(),P2=read(),Q2=Q<<1;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1,l,r,t=0; i<=Q; ++i)
		l=read(), r=read(), Ans[i]+=(r-l)*P1, q[++t]=(Quries){l,r,l-1,i,-1}, q[++t]=(Quries){l,r,r,i,1};
	std::sort(q+1,q+1+Q2);

	int top=0; A[sk[0]=0]=INF;
	for(int i=1; i<=n; ++i)
	{
		while(A[sk[top]]<=A[i]) R[sk[top--]]=i;
		L[i]=sk[top], sk[++top]=i;
	}
	while(top) R[sk[top--]]=n+1;

	int tot=0;
	for(int i=1; i<=n; ++i)
	{
		int l=L[i],r=R[i];
		if(l&&r<=n) opt[++tot]=(Opt){l,l,r,P1};
		if(l&&i+1<r) opt[++tot]=(Opt){i+1,r-1,l,P2};//����˵�Ż���������� 
		if(l+1<i&&r<=n) opt[++tot]=(Opt){l+1,i-1,r,P2};
	}
	std::sort(opt+1,opt+1+tot);

	T.n=n, opt[tot+1].p=N, q[Q2+1].p=N;
	int nq=1,no=1;
	while(!q[nq].p) ++nq;//!
	for(int i=1; i<=n&&nq<=Q2; ++i)
	{
		while(opt[no].p==i) T.Modify(opt[no].l,opt[no].r,opt[no].val), ++no;
		while(q[nq].p==i) Ans[q[nq].id]+=q[nq].val*T.Query(q[nq].l,q[nq].r), ++nq;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
