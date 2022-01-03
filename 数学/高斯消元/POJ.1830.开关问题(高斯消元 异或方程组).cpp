/*
ÿ������ֻ������״̬����X[i]��ʾ�Ƿ��������i��A[i][j]��ʾi,j��Ӱ���ϵ��B[i]��ʾiӦ�õĽ�� 
��Ȼ������Ҫʹÿ��i���� ( ��_{j} X[j]*A[i][j] ) % 2 = B[i] 
�������������ԪXi�ĸ���ans����ô����������2^ans 
%2������^���棬���ѿ��� B[i]=st[i]^ed[i] 
���X[j]=1������j��Ӱ��i����ôX[j]*A[i][j]��һ��ӦΪ1������A[i][j]Ӧ=1 ����𷴣�
ע��A[i][i]=1 
��ϵ������Ϊ��������ʽ��ʣ�µ�ϵ��ȫΪ0��������������Ԫ�ĸ�����
���ĳһ��ϵ��ȫΪ�㣬����������һ�ж�Ӧ�е�ֵ��Ϊ0�����޽� 
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
		while(a=read(),b=read(),a&&b) A[b-1][a-1]=1;//a,b�𷴣�
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
		}//��r������еľ���Ԫ�ض�Ϊ0 
		for(int i=r; i<n; ++i)//ĳһ��ϵ��ȫΪ0�����һ�в�Ϊ0 
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
