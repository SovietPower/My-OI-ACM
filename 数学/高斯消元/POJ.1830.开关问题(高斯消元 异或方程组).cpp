/*
每个开关只有两种状态，设X[i]表示是否操作开关i，A[i][j]表示i,j间影响关系，B[i]表示i应该的结果 
显然我们需要使每个i满足 ( ∑_{j} X[j]*A[i][j] ) % 2 = B[i] 
求这个方程自由元Xi的个数ans，那么方案数便是2^ans 
%2可以用^代替，不难看出 B[i]=st[i]^ed[i] 
如果X[j]=1，假设j会影响i，那么X[j]*A[i][j]这一项应为1，所以A[i][j]应=1 输入别反！
注意A[i][i]=1 
将系数矩阵化为上三角形式后，剩下的系数全为0的行数就是自由元的个数；
如果某一行系数全为零，增广矩阵最后一列对应行的值不为0，则无解 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=31;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Gauss
{
	int n;
	bool A[N][N];
	void Init()
	{
		memset(A,0,sizeof A);
		n=read();
		for(int i=0; i<n; ++i) A[i][n]=read();
		for(int i=0; i<n; ++i) A[i][n]^=read();
		for(int i=0; i<n; ++i) A[i][i]=1;
		int a,b;
		while(a=read(),b=read(),a&&b) A[b-1][a-1]=1;//a,b别反！
	}
	void Solve()
	{
		int r=0,c=0;
		while(r<n && c<n)
		{
			int mxrow=r;
			for(int i=r+1; i<n; ++i)
				if(A[i][c]>A[mxrow][c]) mxrow=i;
			if(!A[mxrow][c]) {++c; continue;}
			if(mxrow!=r) std::swap(A[r],A[mxrow]);
			for(int i=r+1; i<n; ++i)
				if(A[i][c])
					for(int j=c; j<=n; ++j)
						A[i][j]^=A[r][j];
			++r, ++c;
		}//从r往后的行的矩阵元素都为0 
		for(int i=r; i<n; ++i)//某一行系数全为0但最后一列不为0 
			if(A[i][n]) {puts("Oh,it's impossible~!!"); return;}
		printf("%d\n",1<<(n-r));
	}
}g;

int main()
{
	int t=read();
	while(t--) g.Init(), g.Solve();
	return 0;
}
