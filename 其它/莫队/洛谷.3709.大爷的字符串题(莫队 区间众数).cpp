/*
1630ms	6.86MB
这不就是个求区间众数的次数么，还不强制在线，值域分块与莫队都可做，用的莫队。
发现从区间减掉一个数，如果它是答案，好像很难处理？
但是答案要么不变要么就-1啊，记一下出现x次的有多少个数不就行了。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,m,A[N],ref[N],bel[N],Ans,tm[N],cnt[N],ans[N];
struct Quries
{
	int l,r,id;
//	Quries() {}
//	Quries(int l,int r,int id):l(l),r(r),id(id) {}//写了竟然影响下面了。。
	bool operator <(const Quries &x)const{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline void Add(int p)
{
	--cnt[tm[p]], Ans=std::max(Ans,++tm[p]), ++cnt[tm[p]];
}
inline void Subd(int p)
{
	if(!--cnt[tm[p]] && Ans==tm[p]) --Ans;
	--tm[p], ++cnt[tm[p]];
}

int main()
{
	n=read(), m=read();
	int size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=i/size;
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n); int cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);

	for(int i=1; i<=m; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+m);
	for(int l=1,r=0,i=1; i<=m; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l<ln) Subd(A[l++]);
		while(l>ln) Add(A[--l]);
		while(r<rn) Add(A[++r]);
		while(r>rn) Subd(A[r--]);
		ans[q[i].id]=Ans;
	}
	for(int i=1; i<=m; ++i) printf("%d\n",-ans[i]);

	return 0;
}
