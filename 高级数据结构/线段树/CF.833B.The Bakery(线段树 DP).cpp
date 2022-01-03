/*
592ms 8400KB
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
3.���ı��ռ�...

�����߶���������д��...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==IN &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
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
	int maxv[N<<2],tag[N<<2];
	inline void PushUp(int rt)
	{
		maxv[rt]=std::max(maxv[rt<<1],maxv[rt<<1|1]);
	}
	inline void PushDown(int rt)
	{
		maxv[rt<<1]+=tag[rt], maxv[rt<<1|1]+=tag[rt];
		tag[rt<<1]+=tag[rt], tag[rt<<1|1]+=tag[rt];
		tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=0;
		if(l==r) {maxv[rt]=f[l]; return;}
		int m=l+r>>1;
		Build(l,m,rt<<1), Build(m+1,r,rt<<1|1);
		PushUp(rt);
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			++maxv[rt], ++tag[rt];
			return;
		}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(l,m,rt<<1,L,R);
		if(m<R) Modify(m+1,r,rt<<1|1,L,R);
		PushUp(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return maxv[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(l,m,rt<<1,L,R),Query(m+1,r,rt<<1|1,L,R));
			else return Query(l,m,rt<<1,L,R);
		else return Query(m+1,r,rt<<1|1,L,R);
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
		t.Build(0,n,1);
		for(int j=i;j<=n;++j)
			t.Modify(0,n,1,las[j],j-1),f[j]=t.Query(0,n,1,i-1,j-1);
	}
	printf("%d",f[n]);

	return 0;
}
