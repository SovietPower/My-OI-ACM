/*
421ms	23800KB
$Description$
给定两个大小为$n$的可重集合$A,B$，集合中的元素都在$[1,n]$内。你需要从这两个集合中各选一个非空子集，使它们的和相等。输出方案。
$n\leq10^6$。
$Solution$
求子集是假的...对两个集合按任意顺序求个前缀和，记为$SA_i,SB_i$。不妨假设$SA_n\leq SB_n$。
那么能发现，对于每个$SA_i\ (0\leq i\leq n)$，找出最大的$SB_j\leq SA_i$的$j$，$SA_i-SB_j$的取值范围是$[0,n-1]$（如果$\geq n$则可以移动$j$），只有$n$种。而$i$的取值有$n+1$种。由鸽巢原理，那么一定存在一对$i,i'\ (i\neq i')$，使得$SA_i-SB_j=SA_{i'}-SB_{j'}$。因为元素大于$0$，所以$j\neq j'$。
那么有$SA_i-SA_{i'}=SB_j-SB_{j'}$，就可以得到答案啦。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

LL sa[N],sb[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Solve(const int n,LL *sa,LL *sb,int &la,int &ra,int &lb,int &rb)
{
	static int vis[N],vis2[N];
	sb[n+1]=1ll<<60;
	memset(vis,0xff,sizeof vis);
	for(int i=0,j=0,v; i<=n; ++i)
	{
		while(sb[j+1]<=sa[i]) ++j;
		if(~vis[v=sa[i]-sb[j]]) {la=vis[v], ra=i, lb=vis2[v], rb=j; break;}
		vis[v]=i, vis2[v]=j;
	}
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) sa[i]=sa[i-1]+read();
	for(int i=1; i<=n; ++i) sb[i]=sb[i-1]+read();
	int la,ra,lb,rb;
	if(sa[n]>sb[n]) Solve(n,sb,sa,lb,rb,la,ra);
	else Solve(n,sa,sb,la,ra,lb,rb);
	printf("%d\n",ra-la);
	for(int i=la+1; i<=ra; ++i) printf("%d ",i); putchar('\n');
	printf("%d\n",rb-lb);
	for(int i=lb+1; i<=rb; ++i) printf("%d ",i); putchar('\n');

	return 0;
}
