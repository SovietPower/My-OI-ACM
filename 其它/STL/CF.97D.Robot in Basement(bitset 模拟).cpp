/*
934ms	0KB
������ô�����������������з��ϰ�������ȫ���ϻ����ˣ�Ȼ��ö��ÿһ����ö��ÿ���������ƶ���һ����ֱ�����л����˶��ڳ���λ�á����Ӷ���$O(nmk)$�ġ�
��ô�Ż��أ�ע�⵽ÿ���ƶ��������л�����һ����ͬһ�������ƶ���������ֻ����ÿ��λ�����Ƿ��л����ˡ�
������`bitset`�Ż�ÿ���ƶ����Ѹ��ӱ�úź������ƶ�������������$m$λ�������߾�����������һλ...
���и������ǣ������˲������ϰ����ߡ����ǿ����Ȱ����ߵĻ������߹�ȥ��Ȼ��ѻ�ײǽ�Ļ����˲�������
���Ӷ�$O(\frac{nmk}{w})$��
*/
#include <cstdio>
#include <bitset>
#include <cstring>
const int N=153;

std::bitset<N*N> can,ban,now;

int main()
{
	static char s[100005];
	int n,m,K,pos=0; scanf("%d%d%d",&n,&m,&K);
	for(int i=1,now=0; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j,++now)
		{
			s[j]=='#'?ban[now]=1:can[now]=1;
			if(s[j]=='E') pos=now;
		}
	}
	if(can.count()==1&&can[pos]==1) return putchar('0'),0;
	now=can; scanf("%s",s+1);
	for(int i=1,l=K; i<=l; ++i)
	{
		switch(s[i])
		{
			case 'U': now=(now>>m&can)|(now&(ban<<m)); break;
			case 'D': now=(now<<m&can)|(now&(ban>>m)); break;
			case 'L': now=(now>>1&can)|(now&(ban<<1)); break;
			case 'R': now=(now<<1&can)|(now&(ban>>1)); break;
		}
		if(now.count()==1&&now[pos]==1) return printf("%d\n",i),0;
	}
	puts("-1");

	return 0;
}
