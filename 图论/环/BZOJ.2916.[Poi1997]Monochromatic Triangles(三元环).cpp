/*
1120kb	40ms
$Description$
n个点的完全图，其中有m条边用红边相连，其余边为蓝色。求其中三边同色的三角形个数。
$Solution$
直接求同色 除了n^3 不会。。
三角形总数是C(n,3)，考虑求不同色三角形个数。如果一个点连着两条不同颜色的边，那么这一定是个不同色三角形。
如果点i连出的红边数为x，那么连出蓝边n-1-x，形成的不同色三角形个数就是x(n-1-x).
因为同一个不同色三角形会被枚举两次，so $Ans=C(n,3)-\frac{1}{2}\sum_{i=1}^nout[i]*(n-1-out[i])$
感觉和这道坑着的题思路比较像 http://codeforces.com/contest/434/problem/E 
*/
#include <cstdio>
#include <cctype>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1005;

int n,m,red[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), m=read();
	while(m--) ++red[read()], ++red[read()];
	long long ans=0;
	for(int i=1; i<=n; ++i) ans+=1ll*red[i]*(n-1-red[i]);
	printf("%lld\n",1ll*n*(n-1)*(n-2)/6-(ans>>1));

	return 0;
}
