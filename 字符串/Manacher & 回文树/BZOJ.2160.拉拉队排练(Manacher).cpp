/*
13516kb	220ms
$Description$
求给定字符串中 最长的k个回文串长度的乘积(要求回文串长度为奇数)；若奇数长度回文串不足k个则输出-1.(len<=10^6,k<=10^12)
$Solution$
只计算奇数长度的回文串，于是不需要在每两个之间加入字符，只需在字符串首尾添加字符。
对于每个位置计算出ex[i](回文半径)，那么就有1~i+ex[i](中的奇数)长度的回文串，需要计数即区间+1 
由于只需要最后得到cnt[]数组(对应长度回文串的个数)，可以将区间加差分，最后前缀和。
从大到小枚举长度 逐个乘就好了 
*/
#include <cstdio>
#include <algorithm>
#define rg register
#define mod 19930726
typedef long long LL;
const int N=1e6+7;

int n,ex[N];
LL K,cnt[N];
char s[N];

void Manacher()
{
	int mx=0,id;
	for(int i=1; i<=n; ++i)
	{
		if(i<mx) ex[i]=std::min(ex[2*id-i],mx-i);
		else ex[i]=1;
		while(s[i-ex[i]]==s[i+ex[i]]) ++ex[i];
		if(i+ex[i]>mx) mx=i+ex[id=i];
		--cnt[2*ex[i]];
	}
//	for(int i=1; i<=n; ++i) printf("%d ",ex[i]);putchar('\n');
}
LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	scanf("%d%lld%s",&n,&K,s+1);
	s[0]='$', s[n+1]='%', Manacher();
	cnt[1]=n;
	for(int i=2; i<=n; ++i) cnt[i]+=cnt[i-1];
//	for(int i=1; i<=n; ++i) printf("%I64d ",cnt[i]);putchar('\n');
	LL res=1;
	for(int i=n&1?n:n-1; i>0; i-=2)
		if(cnt[i])
			if(K>cnt[i]) res=res*FP(i,cnt[i])%mod, K-=cnt[i];
			else {res=res*FP(i,K)%mod, K=0; break;}
	if(K) printf("-1");
	else printf("%lld",res);

	return 0;
}
