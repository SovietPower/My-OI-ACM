/*
$Description$
一个$n\times n$的非负整数矩阵$A$，保证$A_{i,i}=0$。现在你要对每个$i$求$\min_{j\neq i}A_{i,j}$(每一行除$A_{i,i}$的最小值)。你可以进行不超过$20$次询问，每次询问你给出下标集合$\{w_1,w_2,\ldots,w_k\}$，交互库会对每个$i$返回$\min_{j=1}^kA_{i,w_j}$(每一行给出列的最小值)。
$n\leq 1000$。
$Solution$
常见思路：$i\neq j$即$i,j$至少有一位不同。
对每一位枚举$0/1$，求所有下标该位为$0/1$的最小值。对于每个$i$把与其某位不同的数全部取$\min$即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,A[N][13][2],tag[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Query(int s,int bit)
{
	int t=0;
	for(int i=1; i<=n; ++i) if(tag[i]==s) ++t;
	printf("%d\n",t);
	for(int i=1; i<=n; ++i) if(tag[i]==s) printf("%d ",i);
	putchar('\n'); fflush(stdout);
	for(int i=1; i<=n; ++i) A[i][bit][s]=read();
}

int main()
{
	n=read();
	for(int i=0; 1<<i<=n; ++i)//从0啊→_→
	{
		for(int j=1; j<=n; ++j) if(j>>i&1) tag[j]=1;
		Query(0,i), Query(1,i);
		for(int j=1; j<=n; ++j) tag[j]=0;
	}
	puts("-1");//看格式→_→先-1，输出到一行 
	for(int i=1; i<=n; ++i)
	{
		int ans=1e9;
		for(int bit=0; 1<<bit<=n; ++bit)
			ans=std::min(ans,A[i][bit][(i>>bit&1)^1]);
		printf("%d ",ans);
	}
	fflush(stdout);

	return 0;
}
