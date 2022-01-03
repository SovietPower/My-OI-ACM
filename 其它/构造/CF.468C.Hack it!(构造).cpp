/*
$Description$
令$f(x)$表示整数$x$在十进制下各个数位的数字之和。给定$a$，求两个整数$l,r$，使得$\sum_{i=l}^rf(i)\equiv0\ (\mathbb{mod}\ a)$。
$1\leq a\leq10^{18},\ 1\leq l\leq r\leq10^{200}$，保证存在解。
$Solution$
考虑一个简单的性质：$f(x+10^y)=f(x)+1,\ x\lt10^y$。
不妨令$INF=10^{18}$，设$\sum\limits_{i=0}^{INF-1}f(i)\equiv p\ (\mathbb{mod}\ a)$。
由上面的性质可知，$\sum\limits_{i=1}^{INF}f(i)=p-f(0)+f(INF)=p+1$。
同理还有：$\sum\limits_{i=2}^{INF+1}f(i)=p+2...\ \sum\limits_{i=k}^{INF+k-1}f(i)=p+k$（都是模$a$意义下）。
然后就可以构造出$a=p+a-p=\sum\limits_{i=a-p}^{INF+a-p-1}f(i)$。所以令$l=a-p,\ r=10^{18}+a-p-1$就可以啦。
有个问题是求$\sum_{i=0}^{10^{18}-1}f(i)\ \mathbb{mod}\ a$。展开一下：$$\begin{aligned}\sum_{i=0}^{10^{18}-1}f(i)&=(1+2+...+9)10^{17}+10\times\sum_{i=0}^{10^{17}-1}f(i)\\&=45\times10^{17}+10(45\times10^{16}+10\times\sum_{i=0}^{10^{15}-1}f(i))\\&=...\\&=18\times45\times10^{17}=81\times10^{18}\end{aligned}$$

这样就做完啦。

还有个做法是，考虑有$\sum\limits_{i=1+x}^{10^y+x}f(i)-\sum\limits_{i=1}^{10^y}f(i)=x,\ x\lt10^y$。枚举$y$，如果有$a-\sum\limits_{i=0}^{10^y}<10^y$，令$x$等于这个数，就有$\sum\limits_{i=1+x}^{10^y+x}f(i)=\sum\limits_{i=0}^{10^y}+a-\sum\limits_{i=0}^{10^y}=a$了。
需要预处理一下$\sum_{i=1}^{10^y}f(i)$，因为是上限$10$的幂所以算一下每个数出现次数即可（或者像上面一样直接算）。
*/
#include <cstdio>
typedef long long LL;
const LL INF=1e18;

int main()
{
	LL a; scanf("%I64d",&a);
	LL l=a-INF*9%a*9%a;
	printf("%I64d %I64d\n",l,INF+l-1);

	return 0;
}
