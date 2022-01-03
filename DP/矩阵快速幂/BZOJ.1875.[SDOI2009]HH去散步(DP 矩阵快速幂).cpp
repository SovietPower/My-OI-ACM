/*
1368kb	2900ms
比较容易想到用f[i][j]表示走了i步后到达j点的方案数，但是题目要求不能走上一条走过的边 
如果这样表示是不好转移的 
可以考虑边，f[i][j]表示走了i步后到达第j条边的方案数，那么有 f[i][j] = ∑f[i-1][k] (边k能直接到达边j) 
只要不走反向边，就保证了不会走上一条边了 
步数很大，而这个方程显然是可以通过矩阵快速幂加速转移的 
求初始边矩阵的t-1次方幂t'，然后用系数矩阵(与src相连的边)乘以t'，即为走了t条边后的方案数 
(这个系数矩阵是为了只保留矩阵中起点是src的路径)
最终答案为所有与des相连的边的dp值 
一条边肯定要拆成两条有向边 
注意异或运算级比!=还低。。
O((2m)^3logt)=5e7 得卡卡常  (为什么自带大常数)
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod 45989//真的略快 
const int N=150;//,mod=45989;

int n,m,K,src,des,Enum,H[70],nxt[N],to[N];
struct Matrix
{
	int A[N][N];
//	void Clear() {memset(A,0,sizeof A);}
	Matrix operator *(const Matrix &a)const
	{
		Matrix res;
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=m; ++j)
			{
				res.A[i][j]=0;
				for(int k=1; k<=m; ++k)
					(res.A[i][j]+=A[i][k]*a.A[k][j])%=mod;
			}
		return res;
//		for(int i=1; i<=m; ++i)
//			for(int k=1; k<=m; ++k)
//				if(A[i][k])//优化技巧 先枚举k 于是可以判是否为0 -> 于是更慢了-- 应该是洛谷评测的问题吧。。
//					for(int j=1; j<=m; ++j)
//						res.A[i][j]+=A[i][k]*a.A[k][j]%mod,
//						res.A[i][j]>=mod ? res.A[i][j]-=mod : 0;
	}
}S,tmp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
Matrix FP(Matrix x,int k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}

int main()
{
	Enum=1;
	n=read(),m=read(),K=read(),src=read(),des=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
	m=Enum;
	for(int i=H[src]; i; i=nxt[i]) S.A[1][i]=1;//拿1做起点 感觉好玄学啊。。
	for(int i=2; i<=m; ++i)
		for(int j=H[to[i]]; j; j=nxt[j])//与边i直接相邻的边即边的端点所连的边 
			if(i!=(j^1)) tmp.A[i][j]=1;//++tmp.A[i][j];//这个是不需要+的，因为已经把每条边都拆了 
//			if(i^j^1) tmp.A[i][j]=1;
	tmp=FP(tmp,K-1);
	S=S*tmp;
	int res=0;
	for(int i=H[des]; i; i=nxt[i]) res+=S.A[1][i^1];//起点到 能到终点的边 
	printf("%d",res%mod);

	return 0;
}
