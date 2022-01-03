/*
2092kb	424ms
记所有元素的异或和为$s$，那么$x_1+x_2=x_1+x_1\ ^{\wedge}s$。
$s$是确定的。考虑从高位到低位枚举$s$的二进制位。若当前位$s$为$1$，则$x_1$是$0$是$1$贡献相同；否则$x_1$这一位必须是$1$（如果能是$1$）。这样可以满足$x_1+x_2$最大。
对于$x_1$最小的要求，就是在$s$为$1$时，$x_1$能取$0$就取$0$。
这种逐位$\text{xor}$的，考虑构造线性基。

原来的线性基是以从高位到低位为优先级的。而现在是，$s$为$0$的位优先级最高，其次高位优先级最高。
那么在把一个数插入到线性基里时，优先选$s$为$0$的位插入，然后再去尝试插入$s$为$1$的位。（如果第一次不能插入进去，说明不会对$s$为$0$的位产生影响啊，也就不会影响$x_1+x_2$最大了）
求$x_1$时令$s$为$0$的位尽量为$1$，其次$s$为$1$的位尽量为$0$即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 59
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

LL A[N],base[BIT+2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void Insert(LL x,LL s)
{
	for(int i=BIT; ~i; --i)
		if(!(s>>i&1) && x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return;}
	for(int i=BIT; ~i; --i)
		if(/*s>>i&1 &&*/ x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return;}
}

int main()
{
	const int n=read(); LL s=0;
	for(int i=1; i<=n; ++i) s^=A[i]=read();
	for(int i=1; i<=n; ++i) Insert(A[i],s);
	LL ans=0;
	for(int i=BIT; ~i; --i) if(!(s>>i&1) && !(ans>>i&1)) ans^=base[i];
	for(int i=BIT; ~i; --i) if(s>>i&1 && ans>>i&1) ans^=base[i];
	printf("%lld\n",ans);

	return 0;
}
