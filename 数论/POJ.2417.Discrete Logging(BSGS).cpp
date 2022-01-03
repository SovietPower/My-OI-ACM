/*
BSGS���a^x ��b(mod p)(pΪ������a,p����) 
��a^(p-1) ��1(mod p)�ɵã�x��ÿp����һѭ���� 
�ʱ����Ļ�ö�ٷ�Χ����0~p-1 
���ֿ�˼�����õ����棬ȡm=ceil(sqrt(p-1)) 
�򷽳̿���дΪa^(im) ��b*a^j(mod p) 
��ʱi,j���Ǹ���p����ģ����԰�����ö��jԤ�������map�� 

ע�⣺����a,p���ʻ����ܻ����޽���� 
ö��i��(a^m)^i��ÿ�γ�a^m����Ҫ��� 
Ҫ��intһֱҪתlonglong��ȡģ�Ļ�����ֱ����longlong��TLEn�Ρ���
map����һ�ȡ���
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
