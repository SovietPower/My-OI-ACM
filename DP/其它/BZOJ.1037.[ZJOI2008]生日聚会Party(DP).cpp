/*
44504kb	156ms
f[i][j][a][b]，表示当前已有i个男生、j个女生，前面这一段(更前面的保证满足)男生至多比女生多a人，女生最多比男生多b人。
如果当前选择男生，f[i+1][j][a+1][b-1]+=f[i][j][a][b]；否则f[i][j+1][a-1][b+1]+=f[i][j][a][b]。注意一下边界。
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
	for(int i=0; i<=n; ++i)//要到n。
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
