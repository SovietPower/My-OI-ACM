//2.04s	25.05MB 没以前跑得快...自闭了 
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=1e6+5;

int size,bel[N],val[N],bloans[N],times[N],Ans[M];
//char IN[MAXIN],*SS=IN,*TT=IN;
struct Queries
{
	int l,r,a,b,id;
	bool operator <(const Queries &x)const
	{
		return bel[l]==bel[x.l]?r<x.r:l<x.l;
	}
}q[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void Add(int x)
{
	!times[x]&&(++bloans[bel[x]]), ++times[x];
}
inline void Subd(int x)
{
	--times[x], !times[x]&&(--bloans[bel[x]]);
}
inline int Query(int l,int r)
{
	int res=0;
	for(int i=bel[l]+1; i<bel[r]; ++i) res+=bloans[i];
	for(int i=l,t=std::min(bel[l]*size,r); i<=t; ++i) res+=(times[i]!=0);
	if(bel[l]!=bel[r]) for(int i=(bel[r]-1)*size+1; i<=r; ++i) res+=(times[i]!=0);
	return res;
}

int main()
{
	const int n=read(),m=read(),size=sqrt(n); ::size=size;
	for(int i=1; i<=n; ++i) val[i]=read(), bel[i]=(i-1)/size+1;
	for(int i=1; i<=m; ++i) q[i]=(Queries){read(),read(),read(),read(),i};
	std::sort(q+1,q+1+m);
	for(int i=1,l=1,r=0; i<=m; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Add(val[--l]);
		while(r<rn) Add(val[++r]);
		while(l<ln) Subd(val[l++]);
		while(r>rn) Subd(val[r--]);
		Ans[q[i].id]=Query(q[i].a,q[i].b);
	}
	for(int i=1; i<=m; printf("%d\n",Ans[i++]));

	return 0;
}
