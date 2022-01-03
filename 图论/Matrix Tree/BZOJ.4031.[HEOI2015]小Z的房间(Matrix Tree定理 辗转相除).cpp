//864kb	64ms
/*
$Description$
给定n*m的格状矩形，每个格子是一个房间或者是一个柱子。一开始时，相邻的格子之间都有墙隔着。
打破墙，使得所有房间形成一棵树。不能打破柱子周围和边界的墙。求方案数，模$10^9$。
$n,m\leq 9$。
$Solution$
裸的Matrix Tree定理。练习一下用辗转相除解行列式。(因为模数不是质数，所以不能直接乘逆元来高斯消元。需要辗转相除。)
注意题目是将所有房间(这些才是点)连成一棵树，墙非节点，即行列式中只存在表示房间的点。否则就很可能无解了。。
*/
#include <cstdio>
#include <algorithm>
#define mod (1000000000)
const int N=103,way[3]={1,0,1};

int n,m,A[N][N],id[12][12];
char mp[12][12];

void Solve(int n)
{
	for(int i=1; i<n; ++i)
		for(int j=1; j<n; ++j) (A[i][j]+=mod)%=mod;//先变成正的！
	int f=1,res=1;
	for(int j=1; j<n; ++j)
	{
		for(int i=j+1; i<n; ++i)
			while(A[i][j])
			{//利用A[j][j]将A[i][j]变为0，(A[j][j],A[i][j]) -> (a,b) -> (b,a%b).
				int t=A[j][j]/A[i][j];
				for(int k=j; k<n; ++k) A[j][k]=(A[j][k]-1ll*t*A[i][k]%mod+mod)%mod;
				for(int k=j; k<n; ++k) std::swap(A[i][k],A[j][k]);
				f^=1;//行列式是(0)否(1)变号。
			}
		if(!A[j][j]) {res=0; break;}
		res=1ll*res*A[j][j]%mod;//将行列式化为下三角行列式后，对角线上的元素相乘即为行列式的值。
	}
	printf("%d",f?res:(mod-res)%mod);
}

int main()
{
	scanf("%d%d",&n,&m);
	int cnt=0;
	for(int i=0; i<n; ++i) scanf("%s",mp[i]);
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(mp[i][j]=='.') id[i][j]=cnt++;//!
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(mp[i][j]=='.')
				for(int u=id[i][j],v,xn,yn,d=0; d<2; ++d)
					if((xn=i+way[d])<n&&(yn=j+way[d+1])<m&&mp[xn][yn]=='.')
						v=id[xn][yn],--A[u][v],--A[v][u],++A[u][u],++A[v][v];
	Solve(cnt);
	return 0;
}
