/*
$Description$
1堆石子有n个,两人轮流取.先取者第1次可以取任意多个，但不能全部取完.以后每次取的石子数不能超过上次取子数的2倍.取完者胜.问谁能赢.
$Solution$
斐波那契博弈(Fibonacci Nim)
结论: 后手必胜当且仅当石子数为Fibonacci数 
证明见: http://blog.csdn.net/dgq8211/article/details/7602807 
*/
#include <cstdio>
const int INF=0x7fffffff;

int cnt;
long long f[2333];
int Find(int x)
{
	int l=1,r=cnt-1,mid;
	while(l<r)
		if(f[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}

int main()
{
	f[0]=f[1]=1;
	for(cnt=2; f[cnt-1]<=INF; ++cnt) f[cnt]=f[cnt-1]+f[cnt-2];
	int n;
	while(scanf("%d",&n),n)
		puts(n==f[Find(n)]?"Second win":"First win");
	return 0;
}
