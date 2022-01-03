//树状数组实现的是单点加 区间求和，采用值域分块可以$O(1)$修改$O(sqrt(n))$查询 
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=2e6;

int n,m,size,Ans1[N*10],Ans2[N*10],A[N],tm[N],bel[N],sum1[500],sum2[500];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Ask
{
	int l,r,a,b,id;
	bool operator <(const Ask &a)const
	{
		return l/size==a.l/size ? r<a.r : l/size<a.l/size;//更快 WTF 
//		return l/size==a.l/size?((l-1)/size&1 ? r>a.r : r<a.r):l/size<a.l/size;
	}
}q[N*10];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Query(int *s,int l,int r,bool f)
{
	int res=0,tmp=std::min(r,bel[l]*size);
	for(int i=l; i<=tmp; ++i) res+= f?(tm[i]>0):tm[i];
	if(bel[l]!=bel[r])
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			res+= f?(tm[i]>0):tm[i];
	for(int i=bel[l]+1; i<bel[r]; ++i) res+=s[i];
	return res;
}
void Add(int p)
{
	if(++tm[p]==1) ++sum2[bel[p]];
	++sum1[bel[p]];
}
void Subd(int p)
{
	if(!--tm[p]) --sum2[bel[p]];
	--sum1[bel[p]];
}

int main()
{
	n=read(), m=read(), size=sqrt(n);//size=n/sqrt(m*2/3) //也没有更快 数组大小还要注意 
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1, A[i]=read();
	for(int i=1; i<=m; ++i) q[i].l=read(),q[i].r=read(),q[i].a=read(),q[i].b=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int l=1,r=0,ln,rn,i=1; i<=m; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l<ln) Subd(A[l++]);
		while(l>ln) Add(A[--l]);
		while(r<rn) Add(A[++r]);
		while(r>rn) Subd(A[r--]);
		Ans1[q[i].id]=Query(sum1,q[i].a,q[i].b,0), Ans2[q[i].id]=Query(sum2,q[i].a,q[i].b,1);
	}
	for(int i=1; i<=m; ++i) printf("%d %d\n",Ans1[i],Ans2[i]);

	return 0;
}
