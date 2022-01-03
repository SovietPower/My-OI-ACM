/*
$Description$
Tang,Jiang两人轮流写数，若A在写了X，则B只能写Y，满足1<=Y-X<=k。最先写数的T只能写[1,k]内的数。第一个写的数>=N的lose，问最后的winner。
$Solution$
看做取N-1个石子，每次最多取K个，就是个巴什博弈了 
*/
#include <cstdio>

int main()
{
	int n,k;
	while(scanf("%d%d",&n,&k),n&&k)
		puts((n-1)%(k+1)?"Tang":"Jiang");
	return 0;
}
