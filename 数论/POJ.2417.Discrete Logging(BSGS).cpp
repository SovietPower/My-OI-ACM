/*
BSGS求解a^x ≡b(mod p)(p为质数且a,p互质) 
由a^(p-1) ≡1(mod p)可得，x是每p个数一循环的 
故暴力的话枚举范围就是0~p-1 
将分块思想运用到上面，取m=ceil(sqrt(p-1)) 
则方程可以写为a^(im) ≡b*a^j(mod p) 
此时i,j都是根号p级别的，可以把右项枚举j预处理放入map里 

注意：就算a,p互质还可能会有无解情况 
枚举i是(a^m)^i，每次乘a^m，不要想错 
要是int一直要转longlong再取模的话不如直接用longlong，TLEn次。。
map慢的一比。。
*/
#include<map>
#include<cmath>
#include<cstdio>
#define LL long long

LL a,b,p;
std::map<LL,int>ref;

LL Fast_Pow(LL x,LL k)
{
	LL t=1;
	for(;k;k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
int gcd(int x,int y)
{
	return y?gcd(y,x%y):x;
}
void BSGS()
{
	if(gcd(a,p)!=1) {puts("no solution"); return;}
//	if(!(a%p)) {puts("no solution"); return;}
	ref.clear();
	int m=ceil(sqrt(p-1));
	LL tmp=b%p,AM;
	for(int j=0;j<=m;++j, tmp=tmp*a%p) ref[tmp]=j;
	AM=Fast_Pow(a,m), tmp=AM;
	for(int i=1;i<=m;++i, tmp=tmp*AM%p)
		if(ref[tmp]) {printf("%d\n",(1LL*i*m-ref[tmp])%p); return;}
	puts("no solution");
}
int main()
{
	while(~scanf("%lld%lld%lld",&p,&a,&b)) BSGS();
	return 0;
}
