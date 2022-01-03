/*
896kb	6816ms
A+B+A是KMP的形式，于是固定左端点，对于每个位置i，若fail[i]所能到的点k中(k=fail[fail[fail[...]]])，有满足len(l~k)+len(i-k+l-1,i)<len(l,i)，且len(l~k)>=K，则i满足条件 
每个位置仅计算一次 就很好做了 
O(n^2) 也能过。。
*/
#include <cstdio>
#include <cstring>
const int N=15010;

int n,K,res,fail[N];
char s[N];

void KMP(int p)
{
	fail[p]=p-1;
	for(int k,j,i=p+1; i<=n; ++i)
	{
		j=fail[i-1];
		while(j>=p && s[i]!=s[j+1]) j=fail[j];
		k=fail[i]= s[i]==s[j+1]?j+1:p-1;
		while(i-p+1<=2*(k-p+1)) k=fail[k];
		if(k-p+1>=K) ++res;
	}
}

int main()
{
	scanf("%s%d",s+1,&K), n=strlen(s+1);
	for(int i=1; i<=(n-2*K); ++i) KMP(i);//别去了等号。。
	printf("%d",res);

	return 0;
}
