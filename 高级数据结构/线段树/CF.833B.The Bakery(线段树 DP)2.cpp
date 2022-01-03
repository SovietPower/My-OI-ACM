/*
624ms 9400KB ����һ����˶��� 
����:��n�����������Ϊk�Σ�ÿ�ε�ֵΪ��һ�ε��ܹ��������࣬�������ֵ�Ƕ��� 
DP����f[i][j]��ʾ��ǰ��i �ֳ���j��(��j�ݰ���i) 
��ö��ǰ�ߵĶϵ�k���� 
	f[i][j]=max{f[k][j-1]+val(k+1,1)}
val(a,b)��ʾ[a,b]�������ļ�ֵ(��������) 
O(n^2*k)
�ڶ�ά���Թ��������Ż�����ֻ�������ö�ټ��� 
�Ż���val()�Ĺ��� 
val���������������йأ����Զ���a[i]���ڼ���[1,las[a[i]]]��val[]ʱ��a[i]�����������ף�
����[las[a[i]]+1,i]����valʱ��a[i]����1�Ĺ��� 
����f[k](k��[1,las[a[i]]-1])ʱ��������a[i]�Ĺ��ף�
����f[k](k��[las[a[i]],i-1])����ʱ��a[i]������������(k������ǲ��ں�һ���������) 
���������+1��Ȼ���ѯ����ֵ������f[i] 
����ӡ������ѯ����ֵ -> �߶��� 
ע��1.���Դ�f[0]���� 
2.��ѯλ�����һ��ѭ���Ĺ�ϵ 

�����߶���������д��...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==IN &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson node[rt].ls
#define rson node[rt].rs
const int N=35005,MAXIN=5e6;

int n,k,A[N],f[N],las[N],tmp[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int ls,rs,maxv,tag;
	}node[N<<1];
	inline void PushUp(int rt)
	{
		node[rt].maxv=std::max(node[lson].maxv,node[rson].maxv);
	}
	inline void PushDown(int rt)
	{
		node[lson].maxv+=node[rt].tag, node[rson].maxv+=node[rt].tag;
		node[lson].tag+=node[rt].tag, node[rson].tag+=node[rt].tag;
		node[rt].tag=0;
	}
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].tag=0;
		if(l==r) { node[p].ls=node[p].rs=-1,node[p].maxv=f[l]; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m);
		node[p].rs=tot, Build(m+1,r);
		PushUp(p);
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			++node[rt].maxv, ++node[rt].tag;
			return;
		}
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(l,m,lson,L,R);
		if(m<R) Modify(m+1,r,rson,L,R);
		PushUp(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return node[rt].maxv;
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(l,m,lson,L,R),Query(m+1,r,rson,L,R));
			else return Query(l,m,lson,L,R);
		else return Query(m+1,r,rson,L,R);
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("D.in","r",stdin);
#endif

	n=read(),k=read();
	for(int i=1;i<=n;++i)
		A[i]=read(), las[i]=tmp[A[i]], tmp[A[i]]=i;
//	for(int i=1;i<=n;++i) printf("%d %d\n",A[i],las[i]);
	for(int i=1;i<=k;++i)
	{
		t.tot=0, t.Build(0,n);
		for(int j=i;j<=n;++j)
			t.Modify(0,n,0,las[j],j-1),f[j]=t.Query(0,n,0,i-1,j-1);
	}
	printf("%d",f[n]);

	return 0;
}
