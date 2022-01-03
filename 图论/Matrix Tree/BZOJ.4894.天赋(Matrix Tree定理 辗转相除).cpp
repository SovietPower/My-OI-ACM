/*
1184kb	1608ms
求有向图生成树个数。矩阵树定理，复习下。
和无向图不同的是，度数矩阵改为入度矩阵/出度矩阵，分别对应外向树/内向树。删掉第i行第i列表示以i为根节点的生成树个数，所以必须删掉第1行第1列。
*/
#include <cstdio>
#include <algorithm>
#define mod (1000000007)
const int N=305;

int n,A[N][N];
char s[N];

void Gauss(int n)
{
	bool f=0;
//	for(int i=1; i<n; ++i)
//		for(int j=1; j<n; ++j) A[i][j]=(A[i][j]+mod)%mod;
	for(int j=1; j<n; ++j)
		for(int i=j+1; i<n; ++i)
			while(A[i][j])
			{
				int t=A[j][j]/A[i][j];
				for(int k=j; k<n; ++k)
					A[j][k]=(A[j][k]-1ll*A[i][k]*t%mod+mod)%mod, std::swap(A[j][k],A[i][k]);
				f^=1;
			}
	int ans=f?-1:1;
	for(int i=1; i<n; ++i) ans=1ll*ans*A[i][i]%mod;
	printf("%d",(ans+mod)%mod);//may be negative
}

int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; ++i)
	{
		scanf("%s",s);
		for(int j=0; j<n; ++j)
			if(s[j]=='1') ++A[j][j], --A[i][j];//directed graph
	}
	Gauss(n);

	return 0;
}
