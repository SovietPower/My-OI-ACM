/*
27068kb	364ms
�����kС�����ǿ����뵽��ϯ����Ȼ�����Ǿ�̬�ģ���ô֧���޸ģ�
��̬����ϯ��������ǰ׺��+��������ģ���ô����ÿ��λ���ϵ�ÿ��������һ���㣬����״������¡�
������״����Ĺ��̣������ʱ��ÿ��һ��λ���������ϯ���в����������
��ѯʱ��������ѯ��Ҫ���ʵ�����ϯ����������deltaΪ���д��µ����ĺ͵Ĳ�ֵ���ı�ڵ�ʱ���е���ϯ�����ʽڵ㶼�䡣
ÿ����״��������logn������ÿ�����ı�logn���㡣ʱ��ռ临�Ӷȶ�ΪO(nlog^2n).
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lb(x) (x)&-(x)
const int N=1e4+5,S=N*220,MAXIN=1e5;

int n,Q,A[N],cnt,ref[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Operation{ //������ɢ�� 
	int l,r,K;//l=0:Modify r:pos K:val
	Operation() {}
	Operation(int l,int r,int k):l(l),r(r),K(k) {}
}q[N];
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
namespace T
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,son[S][2],sz[S],root[N],totl,totr,ql[N],qr[N];
	void Insert(int &rt,int l,int r,int p,int v)
	{
		if(!rt) rt=++tot;
		sz[rt]+=v;//��Ȼֱ�����Լ�������ϸģ�����Ҫ�ٸ��ƺܶ��ظ��ڵ㡣
		if(l<r){
			int m=l+r>>1;
			if(p<=m) Insert(lson,l,m,p,v);
			else Insert(rson,m+1,r,p,v);
		}
	}
	void Modify(int p,int v,int delta){
		while(p<=n)
			Insert(root[p],1,cnt,v,delta),p+=lb(p);
	}
	int Query(int l,int r,int k)
	{
		if(l==r) return ref[l];
		int delta=0;
		for(int i=1; i<=totl; ++i) delta-=sz[son[ql[i]][0]];
		for(int i=1; i<=totr; ++i) delta+=sz[son[qr[i]][0]];
		if(delta>=k){
			for(int i=1; i<=totl; ++i) ql[i]=son[ql[i]][0];
			for(int i=1; i<=totr; ++i) qr[i]=son[qr[i]][0];
			return Query(l,l+r>>1,k);
		}
		else{
			for(int i=1; i<=totl; ++i) ql[i]=son[ql[i]][1];
			for(int i=1; i<=totr; ++i) qr[i]=son[qr[i]][1];
			return Query((l+r>>1)+1,r,k-delta);
		}
	}
	int Kth(int l,int r,int k)
	{//����l-1.
		totl=totr=0;
		for(--l; l; l^=lb(l)) ql[++totl]=root[l];//�����
		for(; r; r^=lb(r)) qr[++totr]=root[r];
		return Query(1,cnt,k);
	}
}
inline char Get(){
	char c=gc();while(c!='Q'&&c!='C') c=gc();
	return c;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(),Q=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	int t=n;
	for(int l,r,k,i=1; i<=Q; ++i)
		if(Get()=='Q') l=read(),r=read(),k=read(), q[i]=Operation(l,r,k);
		else r=read(),k=read(), q[i]=Operation(0,r,k),ref[++t]=k;

	std::sort(ref+1,ref+1+t), cnt=1;
	for(int i=2; i<=t; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];

	for(int i=1; i<=n; ++i) T::Modify(i,A[i]=Find(A[i]),1);
	for(int i=1; i<=Q; ++i)
		if(!q[i].l) T::Modify(q[i].r,A[q[i].r],-1), T::Modify(q[i].r,A[q[i].r]=Find(q[i].K),1);
		else printf("%d\n",T::Kth(q[i].l,q[i].r,q[i].K));
	return 0;
}
