/*
6504kb	2576ms
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
#include <unordered_map>
typedef long long LL;
const int N=13,INF=1<<30;

int n,m,A[N][N],B[N][N],sta[N];
std::unordered_map<LL,int> f;

LL Zip()
{
	LL s=0;
	for(int i=1; i<=n; ++i) s=s*N+sta[i];
	return s;
}
//int Unzip(LL s)
//{
//	int cnt=0;
//	for(int i=n; i; --i) cnt+=sta[i]=s%N, s/=N;
//	return cnt;
//}
int DFS(LL s,int cnt)
{
	if(cnt==n*m) return 0;
	if(f.count(s)) return f[s];
	int res;
	if(cnt&1)//B
	{
		++cnt, res=INF;
		for(int i=1; i<=n; ++i)
			if(sta[i]<m && sta[i-1]>sta[i])
				++sta[i], res=std::min(res,DFS(Zip(),cnt)-B[i][sta[i]]), --sta[i];
	}
	else//A
	{
		++cnt, res=-INF;
		for(int i=1; i<=n; ++i)
			if(sta[i]<m && sta[i-1]>sta[i])
				++sta[i], res=std::max(res,DFS(Zip(),cnt)+A[i][sta[i]]), --sta[i];
	}
	return f[s]=res;
}

int main()
{
//	freopen("chess.in","r",stdin);
//	freopen("chess.out","w",stdout);

	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&A[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) scanf("%d",&B[i][j]);
	for(int i=1; i<=n; ++i) sta[i]=0;
	sta[0]=INF, sta[1]=1, printf("%d\n",DFS(Zip(),1)+A[1][1]);

	return 0;
}
