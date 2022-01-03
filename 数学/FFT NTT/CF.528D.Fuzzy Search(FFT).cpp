//467ms	22900KB
//http://www.cnblogs.com/SovietPower/p/8993572.html
/*
$Descripiton$
　　给出文本串S和模式串T和k，S,T为DNA序列(只含$A,T,G,C$)。对于S中的每个位置$i$，只要$s[i-k]\sim s[i+k]$中有一个位置匹配了字符$c$，那么就认为$i$可以匹配$c$。求S中有多少位置匹配了T。

$Solution$
　　题意一直不很明白。。~~(→\_→这就是你颓了一下午一晚上写了一道题的理由？)~~
　　匹配当然是连续的，即若位置$i$匹配，则$S[i+j]=T[j]\ (0\leq j<m)$。
　　我们枚举每个字符c，算出每个位置的$F[j]$，表示当前匹配字符c，$s[j]\sim s[j+m-1]$ 能够和 $T[0]\sim T[m-1]$ 匹配的有多少个。
　　令$f[i]=[位置i可以和当前字符c匹配],g[i]=[\ T[i]==c\ ]$，那么
$$F[j]=\sum_{i=0}^{m-1}f[j+i]*g[i]$$
　　一个位置$i$满足4个字符的$f[i]$之和等于$len(T)$，$i$才是一个合法的位置。(怎么可能$>len(T)$还有T本身限制呢→_→)
　　同上一题，反转$g[\ ]$吧，那么
$$F[j]=\sum_{i=0}^{m-1}f[j+i]*g[m-1-i]=G[m-1+j]$$
　　FFT算就行了。
　　$f[i]$的预处理一遍前缀和就行啊。。
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=524300;//2^{19}=524288
const double PI=acos(-1);

int n,m,k,sum[200005],id[150],cnt[N];
char s[200005],t[200005];
struct Complex
{
	double x,y;
	Complex() {}
	Complex(double x,double y):x(x),y(y) {}
	Complex operator + (const Complex &a)const{
		return Complex(x+a.x, y+a.y);
	}
	Complex operator - (const Complex &a)const{
		return Complex(x-a.x, y-a.y);
	}
	Complex operator * (const Complex &a)const{
		return Complex(x*a.x-y*a.y, x*a.y+y*a.x);
	}
}f[N],g[N];

void FFT(Complex *a,int lim,int opt)
{
	for(int i=0,j=0; i<lim; ++i)
	{
		if(i>j) std::swap(a[i],a[j]);
		for(int l=lim>>1; (j^=l)<l; l>>=1);
	}
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Complex Wn(cos(2.0*PI/i),opt*sin(2.0*PI/i)),t;
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+mid+k]=a[j+k]-(t=w*a[j+mid+k]),
				a[j+k]=a[j+k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;//!
}
void Solve(int x,int lim)
{
	memset(sum,0,sizeof sum);
	for(int i=0; i<=n; ++i)
		if(id[s[i]]==x) ++sum[std::max(0,i-k)], --sum[std::min(n+1,i+k+1)];
	for(int i=1; i<=n; ++i) sum[i]+=sum[i-1];

	for(int i=0; i<=n; ++i) f[i]=Complex((sum[i]>0),0);
	for(int i=n+1; i<lim; ++i) f[i]=Complex(0,0);//Don't forget to clear it.
	for(int i=0; i<=m; ++i)	g[m-i]=Complex(id[t[i]]==x,0);
	for(int i=m+1; i<lim; ++i) g[i]=Complex(0,0);
	FFT(f,lim,1), FFT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=f[i]*g[i];
	FFT(f,lim,-1);

	for(int i=0; i<=n; ++i) cnt[i]+=int(f[m+i].x+0.5);
}

int main()
{
	scanf("%d%d%d%s%s",&n,&m,&k,s,t), --n, --m;
	id['A']=0, id['T']=1, id['G']=2, id['C']=3;
	int lim=1;
	while(lim <= n+m) lim<<=1;
	for(int i=0; i<4; ++i) Solve(i,lim);
	int ans=0;
	for(int i=0; i<=n; ++i) if(cnt[i]==m+1) ++ans;	
	printf("%d",ans);

	return 0;
}
