/*
$Description$
Tang,Jiang��������д������A��д��X����Bֻ��дY������1<=Y-X<=k������д����Tֻ��д[1,k]�ڵ�������һ��д����>=N��lose��������winner��
$Solution$
����ȡN-1��ʯ�ӣ�ÿ�����ȡK�������Ǹ���ʲ������ 
*/
#include <cstdio>

int main()
{
	int n,k;
	while(scanf("%d%d",&n,&k),n&&k)
		puts((n-1)%(k+1)?"Tang":"Jiang");
	return 0;
}
