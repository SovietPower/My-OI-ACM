/*
608ms	1828KB
$Description$
����a,b,x,p����[1,x]������n*a^n ��b (mod p) ��n�ĸ�����1<=a,b<p, p<=1e6+3, x<=10^{12}.
$Solution$
�߽�ܴ�p�Ƚ�С��Ϊ����������������ʽ����û��ѭ���ڡ�
�ɷ���С���� a^{p-1} ��a^0 ��1(mod p)��a^n��ѭ����(һ��)Ϊp-1��n%p ��ѭ����(һ��)Ϊp 
���� n*a^n һ���г�Ϊp(p-1)��ѭ���� 
��n=k(p-1)+y����ôn*a^n ��[k(p-1)+y]*a^{k(p-1)+y} ��[k(p-1)+y]*a^y (mod p)
����ԭ��ʽ�ӿ��Ի�����n���� k(p-1)+y ��y-k ��b*a^{-y} (mod p)
��ô k ��y-b*a^{-y} (mod p)(��ô������������С��k������ʽ��ֵ)
��ʱ1<=y<p���������ǿ���ö��y�õ�һ��k��Ȼ�������һ��n=k(p-1)+y��
��Ϊѭ���ڳ�����p(p-1)������ֻ��Ҫ�����Ͻ��ڻ��ж��ٸ�p(p-1)���� 
*/
#include <cstdio>
typedef long long LL;

LL a,b,p,x;

LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
LL inv(LL x){
	return FP(x,p-2);
}

int main()
{
	scanf("%I64d%I64d%I64d%I64d",&a,&b,&p,&x);
	LL res=0,P=p*(p-1);
	for(int y=1; y<p; ++y)
	{
		LL k=(y-b*inv(FP(a,y))%p+p)%p;
		LL n=(p-1)*k+y;//ע���ⲽ��Ҫȡģ 
		if(n<=x) res+=(x-n)/P+1;
	}
	printf("%I64d",res);

	return 0;
}
