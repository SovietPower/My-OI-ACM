/*
1016kb	160ms
$Description$
给定一个集合A，将 所有子集中的所有数的异或和(包括空集) 从小到大排序，求一个数K在其中的排名（保证出现）。
$Solution$
构造出线性基，然后只保留线性基中存在数的位。
类似数位DP，对K二进制分解，如果K的当前位为1，那么先不选这一位，则后面的i-1位任意选择都比K小，且有2^i种方案（包括空集），加给答案。
但是在不去重的情况下，每个数可能出现多次。如果线性基的大小为size，原集合大小为n，那么线性基中 每个数都出现了2^{n-size}次。
因为存在n-size个数，它们在线性基中可以唯一表示出来。那么对于一个数x，从这n-size个数中任选一些Xor，总有唯一的方案使得在线性基中再异或后仍为x。
所以答案再乘上2^{n-size}就行了。
注意对K分解是在线性基上存在数的对应位上分解。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 30
#define mod 10086
#define Double(x) ((x+=mod)>=mod)&&(x-=mod)

int n,size,base[36],cnt,A[36];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1, x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
inline void Insert(int x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) Insert(read());
	int K=read();
	for(int i=0; i<=Bit; ++i) if(base[i]) A[cnt++]=i;
	int ans=0;
	for(int i=0; i<cnt; ++i)
		if(K>>A[i] & 1) ans+=1<<i;
	printf("%d\n",(ans%mod*FP(2,n-size)%mod+1)%mod);//排名加1啊→_→

	return 0;
}
