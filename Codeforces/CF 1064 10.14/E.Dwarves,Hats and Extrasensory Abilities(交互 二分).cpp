/*
�����뵽���ݵ����ɫ�����϶��ֵ���ѯ��λ�á�
����$2^{30}>10^9$��$30$�ζ���Ҫ���¡���
���ǿ�����ѯ��һ�ζ˵㣨$0$��$10^9$��������Ķ����ٸ�������ж�λ�ã�����29�ζ�������
pretestֱ��$30$�ζ��ֶ����Թ����𡣡���������1e9����ô��ʱ�;��ÿ������ء���
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e6+5;

inline char Get(int p)
{
	static char s[233];
	printf("10 %d\n",p), fflush(stdout);
	scanf("%s",s); return s[0];
}

int main()
{
	int n; scanf("%d",&n);
	int s=Get(0),l=0,r=1e9,mid;
	for(int i=1; i<n; ++i)
	{
		mid=l+r>>1;
		if(Get(mid)==s) l=mid;
		else r=mid;
	}
	printf("9 %d 11 %d\n",l,l+1), fflush(stdout);

	return 0;
}
