/*
2480kb	264ms
二维$DP$显然。尝试换成一维，令$f[i]$表示，强制把$i$放到$a_i$位置去，现在能匹配的最多数目。
那么$f[i]=\max\{f[j]\}+1$，其中$j<i,\ a_j<a_i,\ j-a_j\leq i-a_i$。就是三维偏序，可以$CDQ$。

这三个不等式很相似，再观察一下，发现由$a_i>a_j,\ i-a_i\geq j-a_j$就可以推出$i>j$。
所以只要满足两个条件就可以了，即二维偏序。
同时转移比较特殊，按$i-a_i$从小到大排序（第二关键字为$a_i$从小到大），求$a_i$的$LIS$即可。

注意其实还有个条件是$j-a_j\geq 0$。要判。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int A[N],id[N],sk[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(int x,int y)
{
	return x-A[x]==y-A[y]?A[x]<A[y]:x-A[x]<y-A[y];
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(sk[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read(), id[i]=i;
	std::sort(id+1,id+1+n,cmp);
	int top=0; sk[0]=-1;
	for(int i=1,a=A[id[1]]; i<=n; a=A[id[++i]])
		if(id[i]-a>=0)//j-a[j]>=0！
			if(a>sk[top]) sk[++top]=a;
			else sk[Find(a,top)]=a;
	printf("%d\n",top);

	return 0;
}
