/*
每行每列不能超过2个棋子，求方案数 
前面行对后面行的影响只有 放了0个、1个、2个 棋子的列数，与排列方式无关 
所以设f[i][j][k]表示前i行，放了0个棋子的有j列，放了1个棋子的有k列，则放了2个棋子的为(m-j-k)列 
则放棋子一共可分为6种情况 
不放棋子：1.f[i+1][j+2][k] += f[i][j][k]
放一个棋子：2.放在没有棋子的那一列 f[i+1][j-1][k+1] += f[i][j][k]*j
			3.放在有棋子的那一列 f[i+1][j][k-1] += f[i][j][k]*k
放两个棋子：4.都放在没有棋子的两列 f[i+1][j-2][k+2] += f[i][j][k]*C(j,2)
			5.都放在有一个棋子的两列 f[i+1][j][k-2] += f[i][j][k]*C(k,2)
			6.一个放在没有棋子的一列，一个放在有一个棋子的一列 f[i+1][j-1][k] += f[i][j][k]*j*k
或用f[i][j][k]表示第i行，放了1个棋子的有j列，放了2个棋子的有k列，没放棋子的有(m-j-k)列 
*/
#include<cstdio>
using namespace std;
const int N=105,mod=9999973;

int n,m;
long long f[N][N][N];//long long!

inline int C(int n)//C(n,2)
{
	return n*(n-1)>>1;
}
//inline void Add(int /&n,int b)
//{
//	n+=b;
//	n-= n>=mod?mod:0;
//}

int main()
{
	scanf("%d%d",&n,&m);
	f[0][m][0]=1;
//	f[0][0][0]=1;
	for(int i=0;i<n;++i)
		for(int j=0;j<=m;++j)
			for(int k=0;k+j<=m;++k)
				if(f[i][j][k])//0是无意义的 
				{
//					f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%mod;
//					if(m-k-j>=1) f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k]*(m-k-j))%mod;
//					if(j) f[i+1][j-1][k+1]=(f[i+1][j-1][k+1]+f[i][j][k]*j)%mod;
//					if(m-k-j>=2) f[i+1][j+2][k]=(f[i+1][j+2][k]+f[i][j][k]*C(m-k-j))%mod;
//					if(j>=2) f[i+1][j-2][k+2]=(f[i+1][j-2][k+2]+f[i][j][k]*C(j))%mod;
//					if(m-k-j>=1 && j>=1) f[i+1][j][k+1]=(f[i+1][j][k+1]+f[i][j][k]*(m-k-j)*j)%mod;
					//注意 && j>=1!虽然能得到一个j，但条件中必须有一个j 
					f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%mod;//不放不会增加不放棋子的列数! 
					if(j>=1) f[i+1][j-1][k+1]=(f[i+1][j-1][k+1]+f[i][j][k]*j%mod)%mod;
					if(k>=1) f[i+1][j][k-1]=(f[i+1][j][k-1]+f[i][j][k]*k%mod)%mod;
					if(j>=2) f[i+1][j-2][k+2]=(f[i+1][j-2][k+2]+f[i][j][k]*C(j)%mod)%mod;
					if(k>=2) f[i+1][j][k-2]=(f[i+1][j][k-2]+f[i][j][k]*C(k)%mod)%mod;
					if(j>=1 && k>=1) f[i+1][j-1][k]=(f[i+1][j-1][k]+f[i][j][k]*j*k%mod)%mod;
					//跑得慢。。懵逼 
				}
	long long res=0;
	for(int i=0;i<=m;++i)//枚举不放的列 
		for(int j=0;i+j<=m;++j)//枚举放一个的列 
			res=(res+f[n][i][j])%mod;//两种确定，第三种列也确定 
	printf("%lld",res);

	return 0;
}
