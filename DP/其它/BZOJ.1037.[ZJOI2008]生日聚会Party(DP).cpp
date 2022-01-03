/*
44504kb	156ms
f[i][j][a][b]����ʾ��ǰ����i��������j��Ů����ǰ����һ��(��ǰ��ı�֤����)���������Ů����a�ˣ�Ů������������b�ˡ�
�����ǰѡ��������f[i+1][j][a+1][b-1]+=f[i][j][a][b]������f[i][j+1][a-1][b+1]+=f[i][j][a][b]��ע��һ�±߽硣
*/
#include <cstdio>
#include <algorithm>
#define mod (12345678)
#define Mod(x) (x>=mod)&&(x-=mod)
const int N=152;

int main()
{
	static int f[N][N][22][22];
	int n,m,K; scanf("%d%d%d",&n,&m,&K);
	f[0][0][0][0]=1;
	for(int i=0; i<=n; ++i)//Ҫ��n��
		for(int j=0; j<=m; ++j)
			for(int a=0; a<=K; ++a)
				for(int v,b=0; b<=K; ++b)
					if(v=f[i][j][a][b])
					{
						int &boy=f[i+1][j][a+1][std::max(0,b-1)], &girl=f[i][j+1][std::max(0,a-1)][b+1];
						boy+=v, Mod(boy);
						girl+=v, Mod(girl);
					}
	int ans=0;
	for(int i=0; i<=K; ++i,ans%=mod)
		for(int j=0; j<=K; ++j) ans+=f[n][m][i][j];
	printf("%d\n",ans);

	return 0;
}
