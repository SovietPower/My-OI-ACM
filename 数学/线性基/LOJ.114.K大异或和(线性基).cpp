/*
如何求线性基中第K小的异或和？好像不太好做。
如果我们在线性基内部Xor一下，使得从高到低位枚举时，选base[i]一定比不选base[i]大(存在base[i])。
这可以重构一下线性基，从高到低位枚举i，如果base[i]在第j位(j<i)有值，那么Xor一下base[j]。
比如 1001(3)与0001(0)，同时选0,3只比3要小；重构后是 1000(3)和0001(0)，这样同时选0,3比只选0或3都要大。
这样将K二进制分解后就可以直接对应上线性基对应位的选择了。要存base[i]有值的i。
需要注意如果线性基中表示的向量不足n个，说明一定存在一组向量满足线性相关关系，即存在Xor和为0的情况。这样要使K减1。
判断是K>=(1<<size)，线性基和的个数是2^{size}-1(不算0)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 51
typedef long long LL;
const int N=1e5+5;

int n,size,cnt;
LL base[69],b2[69];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Insert(LL x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
}
inline LL Query(LL K)
{
	LL ans=0;
	for(int i=cnt; ~i; --i)
		if(K>>i & 1) ans^=b2[i];
	return ans;
}
void Rebuild()
{
	for(int i=Bit; ~i; --i)
		for(int j=i-1; ~j; --j)
			if(base[i]>>j & 1) base[i]^=base[j];
	for(int i=0; i<=Bit; ++i) if(base[i]) b2[cnt++]=base[i];
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) Insert(read());
	Rebuild();
	for(int Q=read(); Q--; )
	{
		LL K=read()-(size!=n);//别在for里开int啊mmp 
		printf("%lld\n",(K>=(1ll<<size))?-1ll:Query(K));
	}
	return 0;
}
