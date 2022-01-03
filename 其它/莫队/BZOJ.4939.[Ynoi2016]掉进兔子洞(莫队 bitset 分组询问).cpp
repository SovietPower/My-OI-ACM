/*
309796kb	58456ms
删掉的数即三个区间数的并，想到bitset；查多个区间的数，想到莫队。
考虑bitset的每一位如何对应每个数的不同出现次数。只要离散化后不去重，每次记录time就可以了。
但是如果对所有询问开一个bitset会MLE。但是我们可以开M个bitset，每次处理N次询问。
注意莫队修改时要先Add后Subd，否则tm在中间会出现负值导致RE。原来更新顺序会这样...
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=25000;

int n,m,bel[N],ref[N],A[N],ans[M+3],L[N],R[N],cnt[N];
bool vis[M+3];
std::bitset<N> now,f[M+3];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[(M+3)*3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x)
{
	int l=1,r=n,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline void Add(int x)
{
	now[x+cnt[x]]=1, ++cnt[x];
}
inline void Subd(int x)
{
	--cnt[x], now[x+cnt[x]]=0;
}
void Solve(int tot)
{
	memset(vis,0,sizeof vis);//...
	memset(cnt,0,sizeof cnt);
	int t=0;
	for(int i=0,l1,r1,l2,r2,l3,r3; i<tot; ++i)
	{
		vis[i]=0;
		l1=read(),r1=read(),l2=read(),r2=read(),l3=read(),r3=read();
		q[t++]=(Quries){l1,r1,i}, q[t++]=(Quries){l2,r2,i}, q[t++]=(Quries){l3,r3,i};
		ans[i]=r1-l1+r2-l2+r3-l3+3;
	}
	std::sort(q,q+t), now.reset();
	for(int i=0,l=1,r=0; i<t; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Add(A[--l]);
		while(r<rn) Add(A[++r]);
		while(l<ln) Subd(A[l++]);
		while(r>rn) Subd(A[r--]);
		if(!vis[q[i].id]) f[q[i].id]=now, vis[q[i].id]=1;
		else f[q[i].id]&=now;
	}
	for(int i=0; i<tot; ++i) printf("%d\n",ans[i]-f[i].count()*3);
}

int main()
{
	n=read(), m=read(); int size=sqrt(n);
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read(),bel[i]=i/size;
	std::sort(ref+1,ref+1+n);
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
	while(m>=M) Solve(M),m-=M;
	if(m) Solve(m);

	return 0;
}
