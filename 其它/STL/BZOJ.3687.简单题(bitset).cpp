/*
�����ͣ������뵽�����ͬһ�������ż�����൱��0 
��ai����������һ��ÿ���Ӽ��ͳ��ֶ��ٴΣ���Ȼֻ��Ҫ֪����������ż��������bitset 
bit[i]=0/1��ʾ�Ӽ���Ϊi������ż����/������ 
�и��򵥵�dp����: f[x+a[i]]+=f[x]
����һ��x��bit(ע��bit�ʹ����������Ӽ���)������ѡ��: ������ ��Ӧ��bitset�����bit<<x�������� ����bit 
��ô������������ �� bit = (bit << x) ^ bit 
*/
#include<cstdio>
#include<bitset>
const int N=2e6+5;

std::bitset<N> bit(1);//��0��һλ 

int main()
{
	int n,a,sum=0; scanf("%d",&n);
	while(n--)
		scanf("%d",&a), sum+=a, bit^=(bit<<a);
	int res=0;
	for(int i=0;i<=sum;++i)
		if(bit[i]) res^=i;
	printf("%d",res);

	return 0;
}
