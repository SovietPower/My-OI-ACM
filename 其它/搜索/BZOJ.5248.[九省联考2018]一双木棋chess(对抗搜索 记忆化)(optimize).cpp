/*
6504kb	2576ms
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
