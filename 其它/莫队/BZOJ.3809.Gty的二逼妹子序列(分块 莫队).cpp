/*
25832 kb  26964 ms
莫队+树状数组：增加/删除/查询 都是O(logn)的，总时间复杂度O(m*sqrt(n)*logn)，卡不过 
莫队+分块：这样查询虽然变成了sqrt(n)，但是修改是O(1)的 
考虑对权值进行分块 
细节... 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5,M=1e6+5;

int n,m,A[N],size,Ans[M],belong[N],times[N],bloans[N];
struct Ques
{
	int l,r,a,b,id;
	bool operator <(const Ques &x)const
	{
		return belong[l]==belong[x.l] ? r<x.r : l<x.l;
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

int Query(int l,int r)
{
	int res=0,t=min(r,belong[l]*size);
	for(int i=l;i<=t;++i)
		if(times[i]) ++res;
	if(belong[l]!=belong[r])
		for(int i=(belong[r]-1)*size+1;i<=r;++i)
			if(times[i]) ++res;
	for(int i=belong[l]+1;i<belong[r];++i)
		res+=bloans[i];
	return res;
}
inline void Add(int p)
{
	if(!times[p]) ++bloans[belong[p]];
	++times[p];
}
inline void Subd(int p)
{
	--times[p];
	if(!times[p]) --bloans[belong[p]];
}

int main()
{
	n=read(),m=read();size=sqrt(n);
	for(int i=1;i<=n;++i)
		A[i]=read(), belong[i]=(i-1)/size+1;
	for(int i=1;i<=m;++i)
		q[i].l=read(), q[i].r=read(), q[i].a=read(), q[i].b=read(), q[i].id=i;
	sort(q+1,q+1+m);
	for(int i=1,l=1,r=0;i<=m;++i)
	{
		while(l<q[i].l) Subd(A[l++]);
		while(l>q[i].l) Add(A[--l]);
		while(r<q[i].r) Add(A[++r]);
		while(r>q[i].r) Subd(A[r--]);
		Ans[q[i].id]=Query(q[i].a,q[i].b);
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",Ans[i]);

	return 0;
}/*
10 10
4 4 5 1 4 1 5 1 2 1
5 9 1 2
3 4 7 9
4 4 2 5
2 3 4 7
5 10 4 4
3 9 1 1
1 4 5 9
8 9 3 3
2 2 1 6
8 9 1 4
*/
