/*
$Description$
1��ʯ����n��,��������ȡ.��ȡ�ߵ�1�ο���ȡ��������������ȫ��ȡ��.�Ժ�ÿ��ȡ��ʯ�������ܳ����ϴ�ȡ������2��.ȡ����ʤ.��˭��Ӯ.
$Solution$
쳲���������(Fibonacci Nim)
����: ���ֱ�ʤ���ҽ���ʯ����ΪFibonacci�� 
֤����: http://blog.csdn.net/dgq8211/article/details/7602807 
*/
#include <cstdio>
const int INF=0x7fffffff;

int cnt;
long long f[2333];
int Find(int x)
{
	int l=1,r=cnt-1,mid;
	while(l<r)
		if(f[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}

int main()
{
	f[0]=f[1]=1;
	for(cnt=2; f[cnt-1]<=INF; ++cnt) f[cnt]=f[cnt-1]+f[cnt-2];
	int n;
	while(scanf("%d",&n),n)
		puts(n==f[Find(n)]?"Second win":"First win");
	return 0;
}
