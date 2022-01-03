/*
7ms	2048KB
$Description$
坐标轴正半轴上有$n$个垃圾，位置分别是$x_i$。在原点处有一个垃圾桶。一个机器人要从原点出发，将所有垃圾带到垃圾桶（原点）处。
机器人可以在坐标轴上任意移动。当路过一个垃圾时，可以选择花费$X$的能量捡起垃圾，也可以不管它。一旦捡起就不能放下，除非回到原点将其扔掉。回到原点时可以花费$X$的能量将自己携带的垃圾全部扔掉。当机器人携带$k$件垃圾时，每走一单位距离会花费$(k+1)^2$的能量。
给定$n,X$及每个垃圾的坐标，求机器人扔掉所有垃圾的最小能量花费。
$n\leq10^5,\ 0<x_1<...<x_n\leq10^9,\ X\leq10^9$。

$Solution$
先把捡起和放下垃圾的花费去掉。枚举分$k$次扔垃圾，那么这部分花费就是$(n+k)\times X$。
考虑某一次取了从左到右是$a,b,c,d$这四个位置的垃圾的花费：$d+4(d-c)+9(c-b)+16(b-a)+25a$，化简后是$5d+5c+7b+9a$。也就是代价和位置有关，且最远和次远位置的系数是$5$，更近的位置的系数是$7,9,11...$。
显然应该令这$k$次扔垃圾中，最远和次远的位置是最远的$2k$个点，然后依次往靠近原点的位置分系数即可。
枚举$k$，每次选$k$个共选$\frac nk$次，复杂度$O(n\ln n)$。

注意一些很劣的方案会使结果爆`long long`，要特判。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

LL s[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read(); LL X=read(),ans=X*n;
	for(int i=1,a; i<=n; ++i) s[i]=s[i-1]+(a=read()), ans+=5ll*a;
	for(int k=1; k<n; ++k)
	{
		LL tmp=X*k;
		for(int i=n,j,t=1; i; i=j,++t)
		{
			j=std::max(i-k,0);
			tmp+=(s[i]-s[j])*std::max(5ll,t*2+1ll);
			if(tmp>ans) break;
		}
		ans=std::min(ans,tmp);
	}
	printf("%lld\n",ans+X*n);

	return 0;
}
