/*
655ms	46000KB
$Description$
初始有一个空字符串，$n$次操作，每次在串的前面或后面加一个字符，求每次操作后字符串的循环节种数。
$s$的循环节$t$定义为：$s$由$k$个$t$组成或由$k$个$t$加$t$的一个前缀组成。
$n\leq 10^6$。
$Solution$
给定$s$和长度$k$，判断$s$是否有上述循环节 等价于 判断**是否有$s[1,n-k]==s[k+1,n]$**。哈希即可$O(1)$判断。

有个性质是：长度为$k$的循环节会在$k$时刻出现，若它在$k+t$时刻消失，则以后不会再出现。
因为多一个字符导致$k$循环节消失后，再在前面或后面加字符，它也不会再成为循环节。
所以先对最终串哈希。枚举循环节长度$k$，二分它消失的时刻$k+t$，使$[k,k+t]$的答案$+1$即可。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
#define seed 31
typedef long long LL;
typedef unsigned long long ull;
const int N=1e6+6;

int sum[N],L[N],R[N];
ull hs[N*3],pw[N];
char s[N*3];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline char Get()
{
	char c=gc(); while(!isalpha(c)) c=gc();
	return c;
}
inline ull Hash(int l,int r)
{
	return hs[r]-hs[l-1]*pw[r-l+1];
}
bool Check(int t,int k)
{
	return Hash(L[t],R[t]-k)==Hash(L[t]+k,R[t]);
}

int main()
{
	int n=read(),h=1e6+1,t=1e6+1;
	static char ss[5];
	for(int i=1; i<=n; ++i)
	{
		if(Get()=='a') scanf("%s",ss), s[t++]=ss[0]=='s'?ss[1]:ss[0];
		else scanf("%s",ss), s[--h]=ss[0]=='s'?ss[1]:ss[0];
		L[i]=h, R[i]=t-1;
	}

	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*seed;
	for(int i=h; i<t; ++i) hs[i]=hs[i-1]*seed+s[i]-'a';

	for(int i=1; i<=n; ++i)
	{
		int l=i,r=n,mid;
		while(l<r)
			if(Check(mid=l+r+1>>1,i)) l=mid;
			else r=mid-1;
		++sum[i], --sum[l+1];
	}
	for(int i=1; i<=n; ++i) sum[i]+=sum[i-1], printf("%d\n",sum[i]);

	return 0;
}
