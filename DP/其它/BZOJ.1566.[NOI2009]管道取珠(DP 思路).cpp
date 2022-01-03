/*
2816kb	1072ms
����$a_i^2$��ʲô���壺�����˷ֱ����ԭ���У�ʹ�õõ���������ж�Ϊ$i$�ķ�������$\sum a_i^2$�������˵õ������������ͬ�ķ�������
$f[i][j][k]$��ʾ��һ�����Ϲܵ�ȡ���˵�$i$�����¹ܵ�ȡ���˵�$j$���򣬵ڶ������Ϲܵ�ȡ���˵�$k$���򣬵ķ�������ת�ƺܼ򵥡�
���Ӷ�$O(n^3)$��
*/
#include <cstdio>
#include <algorithm>
#define mod 1024523
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=505;

int main()
{
	static int f[2][N][N];
	static char A[N],B[N];
	int n,m; scanf("%d%d",&n,&m);
	scanf("%s%s",A+1,B+1);
	std::reverse(A+1,A+1+n), std::reverse(B+1,B+1+m);
	A[n+1]='?', B[m+1]='!';
	int p=0; f[p][0][0]=1;
	for(int i=0; i<=n; ++i,p^=1)
		for(int j=0; j<=m; ++j)
			for(int k=0,v; k<=n; ++k)
				if((v=f[p][j][k]))
				{
					if(A[i+1]==A[k+1]) Add(f[p^1][j][k+1],v);
					if(A[i+1]==B[i+j-k+1]) Add(f[p^1][j][k],v);
					if(B[j+1]==A[k+1]) Add(f[p][j+1][k+1],v);//p���䰡���ճ����ȣ�
					if(B[j+1]==B[i+j-k+1]) Add(f[p][j+1][k],v);
					if(i+j==n+m) return printf("%d\n",f[p][m][n]),0;
					f[p][j][k]=0;
				}
	puts("Miaomiaomiao?");

	return 0;
}
