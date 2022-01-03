/*
$Description$
����������$n,m$��ÿ�ο���ʹn��һ��ʹn��2����������Ҫ���ٴο���ʹn����m��
$Solution$
��������BFS����DP���У�����O(n)�ġ��и��ŵ�������
�����ǿ���ģ����ǿ���m���n�������ֲ�����1��m+=1��2�ǵ�mΪż��ʱ��m/=2��
Ҫ�����ٵĴ���ʹ��m<=n��
��Ϊm�������ٳ��Զ����ȳ��Զ��ټ�һ�εõ��Ľ����һ���ģ����ܳ��Ͳ��ӡ�������O(logn)����ˡ�
����n��m�����Ʋ������ʰ��������Ʋ��о����Ե��ưɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),ans=0;
	for(; m>n; m>>=1, ++ans)
		if(m&1) ++m, ++ans;
	printf("%d\n",ans+n-m);

	return 0;
}
