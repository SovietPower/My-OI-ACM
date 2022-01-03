/*
每个[l,r]的询问中又多了[a,b]值的限制。原先now是所有种类的个数，所以用 莫队+树状数组做 
两问，维护两个树状数组 
O(m*sqrt(n)*logn)
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5,M=1e6+5;

int n,m,size,A[N],t1[N],t2[N],times[N],Ans1[M],Ans2[M];
struct Ques
{
	int l,r,a,b,id;
	bool operator <(const Ques &x)const
	{
		return l/size==x.l/size ? r<x.r : l/size<x.l/size;
	}
}q[M];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

inline int lb(int x)
{
	return x&-x;
}
void Update(int p,int v,int *t)
{
	while(p<=n)
		t[p]+=v, p+=lb(p);
}
int Query(int p,int *t)
{
	int res=0;
	while(p)
		res+=t[p], p-=lb(p);
	return res;
}
void Add(int p)
{
	Update(A[p],1,t1);
	if(!times[A[p]]) Update(A[p],1,t2);
	++times[A[p]];
}
void Subd(int p)
{
	Update(A[p],-1,t1);
	--times[A[p]];
	if(!times[A[p]]) Update(A[p],-1,t2);
}

int main()
{
	freopen("ahoi2013_homework.in","r",stdin);
	freopen("ahoi2013_homework.out","w",stdout);

	n=read(),m=read();
	size=sqrt(n);
	for(int i=1;i<=n;++i)
		A[i]=read();
	for(int i=1;i<=m;++i)
		q[i].l=read(), q[i].r=read(), q[i].a=read(), q[i].b=read(), q[i].id=i;
	sort(q+1,q+1+m);
	for(int l=1,r=0,i=1;i<=m;++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l<ln) Subd(l++);
		while(l>ln) Add(--l);
		while(r<rn) Add(++r);
		while(r>rn) Subd(r--);
		Ans1[q[i].id]=Query(q[i].b,t1)-Query(q[i].a-1,t1),//注意值的区间是[a,b]不是[l,r] 
		Ans2[q[i].id]=Query(q[i].b,t2)-Query(q[i].a-1,t2);
//		printf("%d:%d %d ans1:%d ans2:%d\n",q[i].id,ln,rn,Ans1[q[i].id],Ans2[q[i].id]);
	}
	for(int i=1;i<=m;++i)
		printf("%d %d\n",Ans1[i],Ans2[i]);

	fclose(stdin);fclose(stdout);
	return 0;
}
