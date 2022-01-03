/*
820kb	0ms
$Description$
�������ߵ����ֱ�Ϊ$n,m$����$n\times m$���ߵ���ȫ����ͼ����������������ģ$p$��
$n,m,p\leq 10^{18}$��
$Solution$
������ȫ����ͼ����ô�ڹ���Prufer����ʱ������ʣ�������㣬����ı��������������ϵģ�����������Ȼ������������ 
��ô����A��ɾ��m-1�Σ�ÿ�δ�n������ѡ��B��ɾ��n-1�Σ�ÿ�ζ����Դ�m������ѡ��so ans = n^{m-1}*m^{n-1} 
�𰸿��Ը������˳��ֱ�ӹ��� 
*/
#include <cstdio>
typedef long long LL;
LL n,m,p;

LL Mult(LL a,LL b)
{
	LL tmp=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return tmp<0?tmp+p:tmp;
}
LL FP(LL x,LL k)
{
	LL t=1;
	for(; k; k>>=1,x=Mult(x,x))
		if(k&1) t=Mult(t,x);
	return t;
}

int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	printf("%lld",Mult(FP(n,m-1),FP(m,n-1)));
	return 0;
}
