/*
332K 0MS
$Description$
һ��1~INF������������n�����ӣ���������Pi������ֻ�������ߣ����ܿ�Խ���ӣ��Ҳ���Խ��(<1)������ÿ�ο��Խ�����һ�����ƶ������������ƶ�һ����λ������/���ֻ�Ӯ���Ƿ��޽⡣
$Solution$
���ȿ��������������� 
����һ������ô�ƶ�ǰ�ߵ����ӣ����ֶ����ƶ���������ͬ���ľ���ʹ�����������Ӽ������� 
ͬʱ�������Ӿ������ֹ�������������� 
�����뵽�����������Ӽ����Ϊʯ������һ��Nim��Ϸ 
����չ��n�����ӣ�
**�������**������ÿһ�Կ���һ��Nim��Ϸ 
��������Ϊ����ʱ��Ҫ����һ�����Ӻ͵�1����һ�� 
״̬�����޵� �����޽� 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

int A[1005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int t=read(),n,res,i;
	while(t--)
	{
		n=read();
		for(i=1; i<=n; ++i) A[i]=read();
		std::sort(A+1,A+1+n);
		if(n&1)
			for(res=A[1]-1,i=2; i<=n; i+=2)
				res^=(A[i+1]-A[i]-1);
		else
			for(res=0,i=1; i<=n; i+=2)
				res^=(A[i+1]-A[i]-1);
		puts(res?"Georgia will win":"Bob will win");
	}
	return 0;
}
