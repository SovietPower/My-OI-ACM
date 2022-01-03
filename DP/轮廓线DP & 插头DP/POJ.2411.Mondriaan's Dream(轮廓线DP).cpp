/*
388K	16MS
���⣺����1*2�ľ�����ȫ����n*m�����̵ķ�������
������DP������DFSԤ������Щ״̬��ת�Ƶ���Щ״̬���Ͳ���ÿ��$2^m$ö���ˡ��������Ӷ�$O(nm2^m)$��
һ�����뿴�˰�Сʱ����ʮ�ָо������� ���Լ������̱�ʾ����=-=��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=11;

LL f[2][(1<<N)+1];

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m),n&&m)
	{
		if(n*m&1) {puts("0"); continue;}
		if(n<m) std::swap(n,m);
		int lim=(1<<m)-1,p=1;
		memset(f[p],0,sizeof f[p]);
		f[p][lim]=1;
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
			{
				p^=1; memset(f[p],0,sizeof f[p]);
				for(int s=0; s<=lim; ++s)
				{
					f[p][s^(1<<j)]+=f[p^1][s];
					if(j && s>>j&1 && !((s>>j-1)&1)) f[p][s|(1<<j-1)]+=f[p^1][s];
				}
			}
		printf("%lld\n",f[p][lim]);
	}
	return 0;
}
