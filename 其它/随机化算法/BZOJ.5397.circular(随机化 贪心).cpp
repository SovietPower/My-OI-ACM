/*
3656kb	280ms
（下标从$0\sim m-1$）拆环为链，对于原线段$[l,r]$，若$l\leq r$就拆成两个线段$[l,r],[l+m-1,r+m-1]$，否则拆成一个线段$[l,r+m-1]$。（这样枚举的时候限制所选线段在一个$m$区间内就行了）
考虑暴力。直接枚举是否一定选某个线段$i$，然后贪心选其它的即可（限制所选线段在$[l_i,l_i+m-1]$内）。复杂度$O(n^2)$或$O(n^2\log n)$。
假设最优答案是$x$。若$x\leq\sqrt n$，那么每次最多会选$x$次。
若$x\gt\sqrt n$，那么每次随机一个线段都会有$\frac xn$的概率选中最优解。所以我们随机$\frac nx+$次可能就差不多了。
但是我们也不知道$x$，写第一种好像也很麻烦。那就用第二个随机的那种做法好了。
设随机的次数是$k$，那么复杂度是$O(kn)$的。
往大了取好了。事实上取$k=2$就可以过这道题惹=v=。
虽然其实正确性并没有保证=v=...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define Rand() (rand()<<16|rand())
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int L[N],R[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r;
	bool operator <(const Node &x)const
	{
		return r<x.r;
	}
}A[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Calc(int x,int n,int m,int tot)
{
	int ans=0;
	for(int i=1,now=0,l=L[x],r=l+m; i<=tot; ++i)
		if(A[i].l>=l && A[i].r<=r && A[i].l>=now)
			now=A[i].r, ++ans;
	return ans;
}

int main()
{
	srand(1002330);
	const int m=read()-1,n=read(); int tot=0;
	for(int i=1; i<=n; ++i)
	{
		int l=L[i]=read(),r=R[i]=read();//我刚开始竟然没读L[i] WA n次=-= 
		if(l<=r) A[++tot]=(Node){l,r}, A[++tot]=(Node){l+m,r+m};
		else A[++tot]=(Node){l,r+m};
	}
	std::sort(A+1,A+1+tot);
	int ans=0;
//	for(int k=2,i=1; i<=n; i+=n/k) ans=std::max(ans,Calc(i,n,m,tot));//也可过...
	for(int k=100; k--; ) ans=std::max(ans,Calc(Rand()%n+1,n,m,tot));
	printf("%d\n",ans);

	return 0;
}
