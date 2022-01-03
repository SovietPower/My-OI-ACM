/*
896kb	6816ms
A+B+A��KMP����ʽ�����ǹ̶���˵㣬����ÿ��λ��i����fail[i]���ܵ��ĵ�k��(k=fail[fail[fail[...]]])��������len(l~k)+len(i-k+l-1,i)<len(l,i)����len(l~k)>=K����i�������� 
ÿ��λ�ý�����һ�� �ͺܺ����� 
O(n^2) Ҳ�ܹ�����
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
	for(int i=1; i<=(n-2*K); ++i) KMP(i);//��ȥ�˵Ⱥš���
	printf("%d",res);

	return 0;
}
