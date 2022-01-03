/*
刚开始一看$O(n^2)$，就想枚举起点然后模拟。。（mdzz）
无脑区间DP。。
$f[i][j][0/1]$表示合并完$i\sim j$区间，现在颜色是$c_i/c_j$的最小花费。转移特判一下即可。
或者先去掉相邻的重复元素，直接$f[i][j]$表示合并完$i\sim j$区间的最小花费。如果$c_i=c_j$，$f[i][j]=f[i+1][j-1]+1$；否则$f[i][j]=\min(f[i+1][j],\ f[i][j-1])+1$。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=5005;

int A[N],f[N][N][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool Check(int n)
{
	for(int i=1; i<=n; ++i) if(A[i]!=A[1]) return 0;
	puts("0");
	return 1;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(Check(n)) return 0;
	memset(f,0x3f,sizeof f);
	for(int i=1; i<=n; ++i) f[i][i][0]=f[i][i][1]=0;
	for(int l=1; l<n; ++l)
		for(int i=1; i+l<=n; ++i)
		{
			int j=i+l;
			f[i][j][0]=std::min(f[i][j-1][0]+2-2*(A[i]==A[j]),std::min(f[i][j-1][1]+2-(A[j-1]==A[j])-(A[i]==A[j]),std::min(f[i+1][j][0]+1-(A[i]==A[i+1]),f[i+1][j][1]+1-(A[j]==A[i]))));
			f[i][j][1]=std::min(f[i][j-1][0]+1-(A[i]==A[j]),std::min(f[i][j-1][1]+1-(A[j-1]==A[j]),std::min(f[i+1][j][0]+2-(A[i]==A[i+1])-(A[i]==A[j]),f[i+1][j][1]+2-2*(A[j]==A[i]))));
		}
	printf("%d\n",std::min(f[1][n][0],f[1][n][1]));

	return 0;
}
