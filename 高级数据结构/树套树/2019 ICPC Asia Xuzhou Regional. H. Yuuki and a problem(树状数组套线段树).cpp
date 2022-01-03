/*
1144ms	486.4MB
$Description$
������Ϊ$n$������$A_i$�����ֲ�����
1. ��ĳ����$A_i$�޸�Ϊ$v$��
2. ��ѯ������$[l,r]$�ڵ���������ɵ���С�����������$v$��ָ����һ��$[l,r]$���Ӽ�$s$ʹ$s$�ĺ͵���$v$����
$n,A_i\leq 2\times10^5$��
$Solution$
[BZOJ(CodeChef)ԭ����������]��/whl
�ȿ���ѯ�ʡ�������$[l,r]$���Ѿ�������ɵ���Ϊ$[1,v]$��$[l,r]$����С�Ĵ���$v$����Ϊ$mx$����$mx>v+1$������Ĵ𰸼�Ϊ$v+1$������$mx=v+1$��$v$���Ը���Ϊ$Sum(1,v+1)$��$[l,r]$��ֵ��$[1,v+1]$���������ĺͣ��������ظ��������̡�
��$mx$��ʱ�������$Sum(1,v+1)$����$Sum=mx$����Ȼ$mx>v+1$������$mx=v+1$��
���׷���$v$ÿ����������$v+1$����������̿�������ϯ��ʵ�֡����Բ�ѯ���Ӷ�Ϊ$O(\log V\log n)$��
�����޸ģ��ĳ�[���޸���ϯ������״��������ϯ����]����״�������߶����Ϳ����ˡ����Ӷ�$O(n\log V\log^2n)$��
������޸���ϯ�������߶���дÿ��λ��ά��һ��ǰ׺�ͼ��ɣ���ѯ�ǵ����ѯ������̫�������鷳��д��/whl��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,V=2e5;

int A[N];
struct President_Tree
{
	#define S N*155//N*18*18*2 //ע��MLE����
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,son[S][2];
	LL pre[S];
	#define R(x) (rs?rs:(rs=++tot))
	void Insert(int &x,int l,int r,int p)
	{
		!x&&(x=++tot);
		if(l==r) {pre[x]+=l; return;}
		int m=l+r>>1; p<=m?(pre[R(x)]+=p,Insert(lson,p)):Insert(rson,p);
	}
	void Delete(int &x,int l,int r,int p)
	{
//		!x&&(x=++tot);
		if(l==r) {pre[x]-=l; return;}
		int m=l+r>>1; p<=m?(pre[R(x)]-=p,Delete(lson,p)):Delete(rson,p);
	}
	LL Query(int x,int l,int r,int p)
	{
		if(!x) return 0;
		if(l==r) return pre[x];
		int m=l+r>>1; return pre[x]+(p<=m?Query(lson,p):Query(rson,p));
	}
};
struct BIT
{
	President_Tree T;
	int n,root[N];
	std::vector<int> vl,vr;
	#define lb(x) (x&-(x))
	void Modify(int p,int a,int v)
	{
		for(; p<=n; p+=lb(p))
		{
			if(a) T.Delete(root[p],1,V,a);
			T.Insert(root[p],1,V,v);
		}
	}
	void Query0(int l,int r)
	{
		vl.clear(), vr.clear();
		for(int p=r; p; p^=lb(p)) vr.emplace_back(p);
		for(int p=l-1; p; p^=lb(p)) vl.emplace_back(p);		
	}
	LL Query(int v)
	{
		LL res=0;
		for(auto p:vr) res+=T.Query(root[p],1,V,v);
		for(auto p:vl) res-=T.Query(root[p],1,V,v);
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

int main()
{
	int n=read(),Q=read(); T.n=n;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) T.Modify(i,0,A[i]);
	for(int p,v; Q--; )
	{
		if(read()==1) p=read(),v=read(),T.Modify(p,A[p],v),A[p]=v;
		else
		{
			LL v=0; int l=read(),r=read(); T.Query0(l,r);//��״����ڵ����������� 
			while(1)
			{
				LL s=T.Query((int)std::min(LL(V),v+1));//����Ҫ��ɢ�� 
				if(s==v) break;
				v=s;
			}
			printf("%lld\n",v+1);
		}
	}

	return 0;
}
