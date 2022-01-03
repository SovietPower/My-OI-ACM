/*
1284ms	565MB
��άƫ�򣬶�ÿһάά��bitset����ʾ�Ķ�Ϊ1�������󣩣�Ȼ��5��bitset���������ܵõ����ˡ�
����ʵ�ֿ�����5*n��bitset�����������ǰ׺�͡�
���Ӷ�$O(n^2/w)$�������Ǳ������Ż�����
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
const int N=30005;

int rk[N][5],pos[N];
std::bitset<N> bit[5][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i)
		for(int j=0; j<5; ++j) rk[i][j]=read();
	for(int j=0; j<5; ++j)
	{
		for(int i=1; i<=n; ++i) pos[rk[i][j]]=i;
		for(int i=2; i<=n; ++i)
			bit[j][i]=bit[j][i-1], bit[j][i].set(pos[i-1]);
	}
	std::bitset<N> ans;
	for(int i=1; i<=n; ++i)
	{
		ans.set();
		for(int j=0; j<5; ++j) ans&=bit[j][rk[i][j]];
		printf("%d\n",ans.count());
	}

	return 0;
}
