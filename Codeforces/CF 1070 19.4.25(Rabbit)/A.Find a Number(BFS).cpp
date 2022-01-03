/*
124ms	32100KB
先要想到令$f[i][j]$表示模$d$余数为$i$，数位和为$j$的最小数。状态数是OK的。
然后每次转移就是在后面加上$0\sim 9$这些数字，用BFS转移就可以保证当前数最小了。复杂度$O(10ds)$。
当然还有其它奇奇怪怪的DP方法。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=503,M=5003;

bool vis[N][M];
struct Node
{
	int r,sum;
};
struct Path
{
	int r,sum;
	char c;
}pre[N][M];

void BFS(const int d,const int s)
{
	std::queue<Node> q;
	q.push((Node){0,0}), vis[0][0]=1;
	while(!q.empty())
	{
		Node x=q.front(); q.pop();
		if(!x.r && x.sum==s) return;
		for(int i=0; i<10; ++i)
		{
			int r=(x.r*10+i)%d, sum=x.sum+i;
			if(sum<=s && !vis[r][sum])
				pre[r][sum]=(Path){x.r,x.sum,char(i+48)}, vis[r][sum]=1, q.push((Node){r,sum});
		}
	}
}
void Output(int d,int s)
{
	if(pre[d][s].c) Output(pre[d][s].r,pre[d][s].sum), pc(pre[d][s].c);
}

int main()
{
	int d,s; scanf("%d%d",&d,&s);
	BFS(d,s);
	if(vis[0][s]) Output(0,s);
	else puts("-1");

	return 0;
}
