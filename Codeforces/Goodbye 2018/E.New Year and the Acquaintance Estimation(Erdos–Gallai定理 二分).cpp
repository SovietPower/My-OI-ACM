/*
187ms	8200KB
~~话说E只要看出是Erdos–Gallai定理然后想到二分，就是裸题么...？~~
题意就是，输出$d_{n+1}$等于多少时，度数序列$d_1,d_2,...,d_{n+1}$可简单图化。
考虑枚举$d_{n+1}$。给定一个度数序列判断其是否合法可以用Erdos–Gallai定理，复杂度$O(n)$。所以现在的复杂度是$O(n^2)$的。
根据样例我们还可以猜想并验证：
1. 由握手定理（就是无向图中所有点的度数之和为偶数），$d_{n+1}$的奇偶性可以确定。
2. 满足条件的$d_{n+1}$一定是一段连续的区间。
所以我们就可以二分了。
二分要得到的是某段区间，分别二分左右端点，但还需要讨论一下。
令$n=n+1$，写一下Erd?s–Gallai定理的式子：$$\sum_{i=1}^kd_i\leq k(k-1)+\sum_{i=k+1}^n\min(d_i,k)$$
二分$n$的度数$d_n=mid$，然后$sort$一下度数序列。
从小到大枚举$k$的时候，记$left$为左式的值，$right$为右式的值。若一直有$left\leq right$，显然$mid$可行。
否则若$left>right$，我们要么减小$left$，要么增大$right$。而唯一能改变的就是$n$的度数$mid$。
所以现在若$mid\geq d_k$（影响左式），我们可以减小$mid$使得序列合法，也就是答案偏大。
若$mid<d_k$（影响右式），可以增大$mid$，也就是答案偏小。
可以确定答案偏大偏小，就可以二分出区间了。复杂度$O(n\log n)$。
[经过一些预处理也可以做到$O(n)$](http://codeforces.com/contest/1091/submission/47777020)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Check(const int n,const int mid)
{
	static int d[N];
	static LL sum[N];
	A[n]=-1;
	for(int i=1,p=1; i<=n; ++i) d[i]=(p==i&&mid>A[p])?mid:A[p++], sum[i]=sum[i-1]+d[i];
	LL vl,vr;
	for(int k=1,p=n; k<=n; ++k)
	{
		while(p>k && d[p]<k) --p;
		vl=sum[k], vr=1ll*k*(k-1)+1ll*(std::max(p,k)-k)*k+sum[n]-sum[std::max(p,k)];
		if(vl>vr) return mid<d[k]?-1:1;
	}
	return 0;
}

int main()
{
	int n=read(),parity=0;
	for(int i=1; i<=n; ++i) parity^=(A[i]=read())&1;
	std::sort(A+1,A+1+n,std::greater<int>());

	int l=0,r=n-parity>>1,L=0,R=-1,mid;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)>=0) L=mid, r=mid-1;
		else l=mid+1;
	l=0,r=n-parity>>1;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)<=0) R=mid, l=mid+1;
		else r=mid-1;

	if(L>R) puts("-1");
	else for(int i=L; i<=R; ++i) printf("%d ",i*2+parity);

	return 0;
}
