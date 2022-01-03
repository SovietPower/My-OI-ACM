/*
6504kb	2932ms
**[Update] 19.2.9**

�������ӵķ�������ǽ���״�ġ�
��Σ������Ѿ������ӵĸ�������Щ�Ǻ�������Щ�ǰ����ӣ�֮ǰ�÷���Σ�������ʣ�µ������ϲ���������ʱ���̵�״̬Ҳ���ǵ÷�����ȷ���ġ�
�����仯������ǰ�ĵ÷��й�ϵ�������������
Ҳ�������ǿ��Լ��仯��������ķ�����֪������ֻ��Ҫ֪��ÿһ�����ڷ��˶��ٸ������ˡ���ʵ������״̬ȷʵ���Ǻܶࡣ
������ʱ���Ǹ�����С����������������ֵĵ÷ֲ���ֻ�����������ֻ���С������

-----
**֮ǰд�ģ�**
ÿ�־���һ����һ������״�����ӣ������һ��״̬�����ǿ��Խ�ÿ���ж��ٸ����Ӵ���������һ��m+1���Ƶ�nλ����ʾ��longlong���Դ棬���ǿ�����map���仯��
ת��ʱö�ٷ�ÿ�����Ӽ��ɡ�

-----
���������ѧ��ĳЩ֪ʶ��״̬��Ϊ$C(n+m,n)$��û����(�ѵ�ʱ��һ��״̬��Ҳ�ǲ����)��
����ʱ��$O(nm)$�����Ĵ���˼·�����ˣ�Ҳ��֪����ô����Կ����������Ǿ�ûд����(��ǰ����flag������ʡѡ�ⲻ�ó��������)��mdzz��
��������DP״ѹҲ���ԡ�����O2 1.5s������
*/
#include <map>
#include <cstdio>
#include <algorithm>
#define INF (0x3f3f3f3f)
typedef long long LL;
const int N=12;

int n,m,A[N][N],B[N][N],num[N];
LL End;
std::map<LL,int> mp;

bool Unzip(LL sta)
{
	int sum=0;
	for(int i=n; i; --i) sum+=(num[i]=sta%(m+1)), sta/=(m+1);
	return sum&1;
}
LL Zip()
{
	LL res=0;
	for(int i=1; i<=n; ++i) res=res*(m+1)+num[i];
	return res;
}
//void P()
//{
//	for(int i=1; i<=n; ++i) printf("%d ",num[i]);
//	putchar('\n');putchar('\n');
//}
int DFS(LL sta)
{
	if(mp.find(sta)!=mp.end()) return mp[sta];
	if(sta==End) return 0;
	bool type=Unzip(sta);//0:A:max 1:B:min
	int res=type?INF:-INF;
	if(num[1]<m)
	{
		++num[1];
		if(type) res=std::min(res,DFS(Zip())-B[1][num[1]]);
		else res=std::max(res,DFS(Zip())+A[1][num[1]]);
		--num[1];
	}
	for(int i=2; i<=n; ++i)
		if(num[i-1]>num[i])
		{
			++num[i];
			if(type) res=std::min(res,DFS(Zip())-B[i][num[i]]);
			else res=std::max(res,DFS(Zip())+A[i][num[i]]);
			--num[i];
		}
	return mp[sta]=res;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&A[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&B[i][j]);
	for(int i=1; i<=n; ++i) num[i]=m; End=Zip();
	DFS(0);
	printf("%d",mp[0]);

	return 0;
}
