/*
区间DP，f[i][j]表示消掉i~j需要的最少珠子数。
枚举方法一样，处理一下端点可以碰撞消除的情况就行。
不合并同色的话，我只能过7个点了，但是某些数据能过。。比如:12 1 1 2 2 3 3 2 2 2 4 4 2 = 3. 
注意颜色还可能是非正数。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=505;

int n,col[N],f[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	memset(f,0x3f,sizeof f);
	for(int i=1; i<=n; ++i) f[i][i]=2;
	for(int i=2; i<=n; ++i)//处理i>j的f[i][j]，方便下面特判时len=2的情况。
		for(int j=1; j<i; ++j) f[i][j]=1;
	for(int len=1; len<n; ++len)
		for(int i=1; i+len<=n; ++i)
		{
			int j=i+len;
			if(col[i]==col[j])//消除后再碰撞消除 
			{
				if(len==1) f[i][j]=1;
				else if(col[i]==col[i+1] && col[j-1]==col[j]) f[i][j]=f[i+2][j-2];
				else if(col[i]==col[i+1]) f[i][j]=f[i+2][j-1];
				else if(col[j-1]==col[j]) f[i][j]=f[i+1][j-2];
				else f[i][j]=f[i+1][j-1]+1;
			}
			for(int k=i; k<j; ++k)
				f[i][j]=std::min(f[i][j],f[i][k]+f[k+1][j]);
//			printf("(%d,%d):%d\n",i,j,f[i][j]);
		}
	printf("%d",f[1][n]);

	return 0;
}/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17
0 1 0 0 1 1 0 1 0 1  1  0  0  1  1  0  0
*/
