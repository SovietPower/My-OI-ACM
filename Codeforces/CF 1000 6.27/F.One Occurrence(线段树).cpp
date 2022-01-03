/*
421ms	29184KB(Rank1��233)
$Description$
����һ����Ϊn�����У����ѯ��[l,r]��ֻ����һ�ε������������һ������(û�����0)��
$Solution$
��las[i],nxt[i]�ֱ�ΪA[i]��һ�Ρ���һ�γ��ֵ�λ�ã���������[l,r]�������׵��ҽ���las[i]<l && r<nxt[i]����Ҳ����A[i]���[las[i]+1,nxt[i]-1]�������ס���Ӧ�ÿ������߶��������޸ġ�
��ѯ�����ߣ����Ҷ˵�����ö�ٵ�ǰ��i��Ϊ�Ҷ˵㣬���߶���ά��[1,i]��las[p]��С��λ��p��
��ô���min{las[p]}<l��pΪ�����֮һ�������޽⡣
��ǰA[i]�ĳ��ֻ�����1(las[las[i]])~las[i]��las[i]�Ĺ��ף�ֱ�ӽ��߶�����las[i]��ֵ(las[las[i]])��ΪINF���ɡ�
��֪��ֱ��Ī��+set�ܲ��ܹ������������˵�Ī��(��Ȩֵ�ֿ�/vector)�о�setӦ��û���⡣
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e5+5,INF=10000000;

int n,Q,A[N],pre[N],las[N],Ans[N];
struct Ques{
	int l,r,id;
	inline bool operator <(const Ques &x)const{
		return r<x.r;
	}
}q[N];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int n,Min,Val,mn[N<<2],val[N<<2];
	inline void Update(int rt)
	{
		if(mn[lson]<mn[rson]) mn[rt]=mn[lson], val[rt]=val[lson];
		else mn[rt]=mn[rson], val[rt]=val[rson];
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) mn[rt]=las[l], val[rt]=A[l];
		else
		{
			int m=l+r>>1;
			Build(ToL), Build(ToR);
			Update(rt);
		}
	}
	void Modify(int l,int r,int rt,int p)//Modify t[p] to INF
	{
		if(l==r) mn[rt]=INF;
		else
		{
			int m=l+r>>1;
			if(p<=m) Modify(ToL,p);
			else Modify(ToR,p);
			Update(rt);
		}
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R){
			if(mn[rt]<Min) Min=mn[rt], Val=val[rt];
		}
		else
		{
			int m=l+r>>1;
			if(L<=m) Query(ToL,L,R);
			if(m<R) Query(ToR,L,R);
		}
	}
	int Get_Ans(int l,int r)
	{
		Min=INF, Query(1,n,1,l,r);
		return Min<l?Val:0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	T.n=n=read();
	for(int i=1; i<=n; ++i) las[i]=pre[A[i]=read()], pre[A[i]]=i;
	T.Build(1,n,1);
	Q=read();
	for(int i=1; i<=Q; ++i) q[i].l=read(), q[i].r=read(), q[i].id=i;
	std::sort(q+1,q+1+Q), q[Q+1].r=n+1;
	for(int i=1,now=1; i<=n&&now<=Q; ++i)
	{
		if(las[i]) T.Modify(1,n,1,las[i]);
		while(/*now<=Q &&*/q[now].r==i) Ans[q[now].id]=T.Get_Ans(q[now].l,i), ++now;
	}
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]);

	return 0;
}
