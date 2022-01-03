/*
2096kb	728ms
首先题目要求输出精确的小数，由下面的推导可知答案要么是整数，要么是一位小数$.5$，不会是$.25,\ .125$什么的。
对$k$讨论，先以$k=2$为例，假设期望异或和是$S$，把它二进制拆分，每一位记为$b_i=0/1$，那么答案是$(b_02^0+b_12^1+...+b_m2^m)(b_02^0+b_12^1+...+b_m2^m)=b_0b_02^0+b_0b_12^1+b_0b_22^2+...b_mb_m2^{m+m}$$=\sum_i\sum_jb_ib_j2^{i+j}$。
那么对于$b_i,b_j$，它的贡献是$\frac{P}{2^n}\times2^{i+j}$，$P$是$i,j$两位都为$1$的方案数。
那么用$b_{i,j}$表示第$i$个数二进制拆分后的第$j$位，$x_i$表示这个数是否存在于选出的集合中，求$i,j$位都为$1$的方案数，可以列个方程组：
$$\begin{matrix}x_1b_{1,0}\oplus x_2b_{2,0}\oplus...\oplus x_nb_{n,0}=0/1\\x_1b_{1,0}\oplus x_2b_{2,0}\oplus...\oplus x_nb_{n,0}=0/1\\\dots\\x_1b_{1,i}\oplus x_2b_{2,i}\oplus...\oplus x_nb_{n,i}=1\\\dots\\x_1b_{1,j}\oplus x_2b_{2,j}\oplus...\oplus x_nb_{n,j}=1\\\dots\\x_1b_{1,m}\oplus x_2b_{2,m}\oplus...\oplus x_nb_{n,m}=0/1\end{matrix}$$

（个人感觉这里除去$i,j$的方程的右式应该是$0/1$吧，那篇博客里写的是$0$）
解这个方程组，可以发现只会有$t\leq k$个$x_i$是有唯一解的，其它$n-t$个$x_i$都有两解。所以方案数为$2^{n-t}$，贡献就为$2^{i+j-t}$。
当$i\neq j$时，$i+j\geq1,\ t\leq2$，所以$2^{i+j-t}\geq0.5$。
当$i=j$时，$i+j\geq0,\ t\leq1$，依旧有$2^{i+j-t}\geq0.5$。
扩展到$k\geq2$的情况，设选出的位有$k'$位是互不相同的，设为$i,j,l...$，那么方程组中右式为$1$的等式有$k'$个，且$i+j+l+...\geq0+1+2+...=\frac{k(k-1)}{2}\geq k-1\geq t-1$，所以$i+j+l+...-t\geq-1$，贡献$2^{i+j+l+...-t}\geq0.5$。
$k=1$时，显然也成立。
综上，答案要么是整数，要么是一位小数$.5$。

-----
其次要注意的是数据范围。答案小于$2^{63}$，那么似乎就有$a_i^k\lt2^{63}$，$a_i\lt\frac{2^{63}}{k}$。
但是个人认为，比如$k=1$，$a_i\lt2^{63}$，但是存在$2^{63}\leq a_i\lt2^{64}$也是可以的，因为毕竟是求平均值，多一位还是可能被拉低到下一位去的。所以应该是$a_i\lt\frac{2^{64}}{k}$（$k=1$需要`unsigned long long`）。
然而没见到有人这么写的（写范围的都是$a_i\lt\frac{2^{63}}{k}$）...那我就不知道为啥都开的`unsigned long long`了。
看了下数据，确实最大值是`18446727131960884031`$>2^{63}$。（答案是$2^{63}-0.5$ 233好强大）

-----
考虑怎么做。对$k$分别求解。

$k=1$：
对每一位分别考虑。设某一位为$1$的数有$t$个，为$0$的有$n-t$个，那么选出奇数个该位为$1$的方案数是：$\sum_{i\ is\ odd}C_n^i2^{n-t}$，偶数个的方案数是$\sum_{i\ is\ even}C_n^i2^{n-t}$。
而$C_n^1+C_n^3+C_n^5+...=2^{n-1}=C_n^0+C_n^2+C_n^4...$
也就是选出该位为$1$的数的个数为奇数和偶数的概率是一样的。那么只要$t\geq0$，该位为$1$为$0$的概率是一样的。
所以求一下哪些位上出现过$1$，加起来除以$2$就好了。

$k=2$：
上面说了答案可以写成$\sum_i\sum_jb_ib_j2^{i+j}$。可以直接$\log^2$枚举$i,j$。
$b_i$为$1$的概率和$k=1$时的情况一样，如果存在一个数第$i$位为$1$，那么就是$\frac12$，否则是$0$。所以如果存在数第$i$位不为$0$且存在数第$j$位不为$0$，那么贡献就是$\frac14\times2^{i+j}$。
需要注意的是如果每个数$i,j$位都相同且至少存在一个数满足$i,j$位不为$1$，那么$i,j$为$1$是同时出现的，概率是$\frac12$。

$k\geq3$：
此时$a_i\lt2^{22}$，线性基中的元素个数不超过$22$，所以可以直接$2^{cnt}$枚举线性基中元素集合（设线性基元素个数为$cnt$）。
线性基中每个子集出现的概率都是$2^n\times2^{n-cnt}=\frac{1}{2^{cnt}}$，求出子集异或和$x^k$后除一下即可。
需要注意的是除$2^{cnt}$之前$x^k$是可以超过$2^{63}$的。需要把$x$表示成$\lfloor\frac{x}{2^{cnt}}\rfloor\times2^{cnt}+x\%2^{cnt}$。
因为有$\lfloor\frac{x^k}{2^{cnt}}\rfloor\times x+\lfloor\frac{(x^k\%2^{cnt})\times x}{2^{cnt}}\rfloor=\lfloor\frac{x^{k+1}}{2^{cnt}}\rfloor$。
> 证明：令$x^k=a\times2^{cnt}+b\ (b<2^{cnt})$，那么等式左边$=ax+\lfloor\frac{bx}{2^{cnt}}\rfloor$，等式右边$=\lfloor\frac{x^k\times x}{2^{cnt}}\rfloor=\lfloor\frac{ax2^{cnt}+bx}{2^{cnt}}\rfloor=ax+\lfloor\frac{bx}{2^{cnt}}\rfloor=左式$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5;

ull A[N];
int cnt,base[30],b[30];
char IN[MAXIN],*SS=IN,*TT=IN;

inline ull read()
{
	ull now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Subtask1(int n)
{
	ull ans=0;
	for(int i=1; i<=n; ++i) ans|=A[i];
	printf("%llu",ans>>1);
	if(ans&1) printf(".5");
	putchar('\n');
}
void Subtask2(int n)
{
	ull x=0,y=0;
	for(int a=0; a<32; ++a)
	{
		bool f1=0;
		for(int i=1; i<=n; ++i) if(A[i]>>a&1) {f1=1; break;}
		if(!f1) continue;
		for(int b=0; b<32; ++b)
		{
			bool f2=0;
			for(int i=1; i<=n; ++i) if(A[i]>>b&1) {f2=1; break;}
			if(!f2) continue;
			bool f3=0;
			for(int i=1; i<=n; ++i) if((A[i]>>a&1)^(A[i]>>b&1)) {f3=1; break;}
			if(a+b-f3-1>=0) x+=1ull<<a+b-f3-1;
			else ++y;//+0.5
		}
	}
	printf("%llu",x+=y>>1);
	if(y&1) printf(".5");
	putchar('\n');
}
inline void Insert(int x)
{
	for(int i=21; ~i; --i)
		if(x>>i&1)
			if(base[i]) x^=base[i];
			else {b[cnt++]=base[i]=x; break;}
}
void Subtask3(int n,int K)
{
	for(int i=1; i<=n; ++i) Insert(A[i]);
	ull ansx=0,ansy=0;
	const int lim=1<<cnt;
	for(int s=0; s<lim; ++s)
	{
		ull val=0,x=0,y=1;
		for(int i=0; i<cnt; ++i) s>>i&1&&(val^=b[i]);
		for(int i=1; i<=K; ++i)
			x*=val, y*=val, x+=y>>cnt, y&=lim-1;
		ansx+=x, ansy+=y;
	}
	ansx+=ansy>>cnt, ansy&=lim-1;
	printf("%llu",ansx);
	if(ansy) printf(".5");
	putchar('\n');
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(K==1) Subtask1(n);
	else if(K==2) Subtask2(n);
	else Subtask3(n,K);

	return 0;
}
