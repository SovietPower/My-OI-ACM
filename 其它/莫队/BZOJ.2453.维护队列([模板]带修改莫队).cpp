/*
���޸�Ī��: ��ͨĪ�ӵ���չ�����ɴ�[l,r,t]��ôת�Ƶ�[l+1,r,t],[l,r+1,t],[l,r,t+1]ȥ���� 
���ڵ�ǰ���ڵ�����ά��һ��vis[l~r]=1,���޸�ֵʱ�����Ƿ��ڵ�ǰ�������޸ļ��ɡ� 
���СȡO(n^{2/3})���������ΰ���˵����ڿ顢�Ҷ˵����ڿ顢�޸Ĵ���(ʱ��) 
���Ӷ�ΪO(n^{5/3}) 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;

int n,m,size,bel[N],A[N],Now,tm[N*100],las[N],Ans[N];
bool vis[N*100];
struct Ask
{
	int l,r,id,t;
	Ask() {}
	Ask(int l,int r,int id,int t): l(l),r(r),id(id),t(t) {} ;
	bool operator <(const Ask &a)const
	{
		if(bel[l]==bel[a.l]) return bel[r]==bel[a.r]?t<a.t:r<a.r;
		return l<a.l;
	}
}qa[N];
struct Modify
{
	int pos,val,bef;
	Modify() {}
	Modify(int p,int v,int b): pos(p),val(v),bef(b) {} ;
}qm[1005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Calc(int p)
{
	if(vis[p])
		if(!--tm[A[p]]) --Now;
		else ;
	else if(++tm[A[p]]==1) ++Now;
	vis[p]^=1;
}
void Change(int p,int v)
{
	if(vis[p]) Calc(p), A[p]=v, Calc(p);//(��ǰλ��)�ڵ�ǰ���������У��Ƚ�ԭ��ֵɾ�������޸ġ���� 
	else A[p]=v;//���ڷ��������У�ֱ�Ӹĵ����� 
}

int main()
{
	n=read(),m=read(),size=pow(n,0.667);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1, las[i]=A[i]=read();
	int na=0,nm=0; char opt[3];
	for(int a,b,i=1; i<=m; ++i)
	{
		scanf("%s",opt),a=read(),b=read();
		if(opt[0]=='Q') qa[++na]=Ask(a,b,na,nm);
 		else qm[++nm]=Modify(a,b,las[a]),las[a]=b;
	}
	std::sort(qa+1,qa+1+na);
	for(int l=1,r=0,t=0,i=1; i<=na; ++i)
	{
		while(t<qa[i].t) ++t,Change(qm[t].pos,qm[t].val);
		while(t>qa[i].t) Change(qm[t].pos,qm[t].bef),--t;
		while(l<qa[i].l) Calc(l++);//����ֱ�Ӵ���A[p] vis[]��ĳλ�õı�� 
		while(l>qa[i].l) Calc(--l);
		while(r<qa[i].r) Calc(++r);
		while(r>qa[i].r) Calc(r--);
		Ans[qa[i].id]=Now;
	}
	for(int i=1; i<=na; ++i) printf("%d\n",Ans[i]);

	return 0;
}
