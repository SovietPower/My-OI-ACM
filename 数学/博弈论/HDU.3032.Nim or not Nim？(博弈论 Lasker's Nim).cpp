/*
$Description$
�ж��ʯ��, ÿ�ο��Խ�����һ��������������߽���һ�ѷֳɷǿյ�����, �������һ��ʯ�ӵ���ʤ������˭����ʤ����
$Solution$
Lasker's Nim��Ϸ 
������������SG�����������
���ȣ�����(1)��Nim��Ϸûʲô���𣬶���һ��ʯ����Ϊk�ĵ���˵����̿���Ϊ0��k-1��
������(2)ʵ�����ǰ�һ����Ϸ�ֳ���������Ϸ����������Ϸ�ĺ�Ϊ��������Ϸ��SG����ֵ�����
����ĳһ�����SG����Ҫ�������ĺ�̣����ĺ�̾�Ӧ��Ϊ ��ǰ�����ܲ��������е�һ��Ϸ���Լ���ǰ���������ֳܷɵĶ����һ��Ϸ ����Ϸ�ĺ͡�
���磬״̬3�ĺ��Ϊ0,1,2,(1^2=3)����SGֵΪ4 
ͨ�������Եõ����ۣ� 
if(x%4 == 0) sg(x)=x-1;
if(x%4 == 1||2) sg(x)=x;
if(x%4 == 3) sg(x)=x+1;
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int SG(int x)
{
	if(!(x%4)) return x-1;
	else if(x%4==3) return x+1;
	return x;
}

int main()
{
	int t,n,res; scanf("%d",&t);
	while(t--)
	{
		n=read(), res=0;
		while(n--) res^=SG(read());
		puts(res?"Alice":"Bob");
	}
	return 0;
}
