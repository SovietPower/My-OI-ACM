/*
6504kb	2932ms
**[Update] 19.2.9**

首先棋子的放置情况是阶梯状的。
其次，无论已经放棋子的格子上哪些是黑棋子哪些是白棋子，之前得分如何，两人在剩下的棋盘上操作，结束时棋盘的状态也就是得分仍是确定的。
（记忆化不和先前的得分有关系啊，想清楚。）
也就是我们可以记忆化。由上面的分析可知，我们只需要知道每一行现在放了多少个棋子了。事实上这种状态确实不是很多。
搜索的时候是个极大极小搜索，记先手与后手的得分差，先手会最大化这个差，后手会最小化这个差。

-----
**之前写的：**
每种局面一定是一个阶梯状的样子，这就是一个状态。我们可以将每行有多少个棋子存下来，用一个m+1进制的n位数表示，longlong可以存，于是可以用map记忆化。
转移时枚举放每个棋子即可。

-----
根据组合数学的某些知识，状态数为$C(n+m,n)$，没问题(搜的时候看一下状态数也是不多的)。
考试时被$O(nm)$。。的错误思路限制了，也不知道怎么处理对抗搜索，于是就没写搜索(考前还立flag搜索的省选题不好出不会出吧)，mdzz。
用轮廓线DP状压也可以。不过O2 1.5s随便过。
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
