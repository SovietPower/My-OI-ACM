/*
数列的最大值保证<=50000(k)，可以直接用莫队。否则要离散化 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=5e4+5;

int n,m,k,size,A[N],times[N];
long long ans[N],now;
struct Ques
{
	int l,r,id;
	bool operator <(const Ques &a)const
	{
		return l/size==a.l/size ? r<a.r : l/size<a.l/size;
	}
}q[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Add(int p)
{
//	now-=times[A[p]]*times[A[p]];
	now+=2*times[A[p]]+1;//(n+1)^2 与 n^2 相差 2n+1
	++times[A[p]];
//	now+=times[A[p]]*times[A[p]];
}
void Subd(int p)
{
//	now-=times[A[p]]*times[A[p]];
	now-=2*times[A[p]]-1;//(n-1)^2 与 n^2 相差 -2n+1 = -(2n-1)
	--times[A[p]];
//	now+=times[A[p]]*times[A[p]];
}

int main()
{
	n=read(),m=read(),k=read();
	size=sqrt(n);
	for(int i=1;i<=n;++i)
		A[i]=read();
	for(int i=1;i<=m;++i)
		q[i].l=read(), q[i].r=read(), q[i].id=i;
	sort(q+1,q+1+m);
	for(int i=1,l=1,r=0;i<=m;++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l<ln)
			Subd(l++);
		while(l>ln)
			Add(--l);
		while(r<rn)
			Add(++r);
		while(r>rn)
			Subd(r--);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;++i)
		printf("%lld\n",ans[i]);

	return 0;
}
