/*
852kb	0ms
$Description$
求一个字典序最小、长为$2^k$的串（环），使得所有长为$k$的01串都在其中出现过。
$Solution$
所有长为$k$的01串一共有$2^k$个，所以每一位都要有一个新的01串。
每个01串可以去掉第一位最后加上一个0/1得到新的01串。对所有串建图，因为一定存在欧拉回路，直接暴力跑个欧拉回路即可。
*/
#include <cstdio>
const int N=(1<<11)+5;

int all,ans[N];
bool vis[N];

bool DFS(int x,int t)
{
	if(vis[x]) return 0;
	vis[x]=1, ans[t]=x&1;
	if(t==all+1) return 1;
	if(DFS((x<<1)&all,t+1)) return 1;
	if(DFS(((x<<1)&all)|1,t+1)) return 1;
	vis[x]=0;
	return 0;
}

int main()
{
	int k; scanf("%d",&k);
	all=(1<<k)-1, printf("%d ",all+1), DFS(0,1);//DFS(all-1,1);
	for(int i=1; i<k; ++i) putchar('0');
	for(int i=1; i<=all-k+2; ++i) putchar(ans[i]+'0');
	return 0;
}
