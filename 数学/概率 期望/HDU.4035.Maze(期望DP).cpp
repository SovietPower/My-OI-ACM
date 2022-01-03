//46MS	3056K
//https://www.cnblogs.com/SovietPower/p/9638883.html
/*
$Description$
有一棵树，从1出发，在每个点有三种可能：
1. 概率$k_x$被杀死，回到1。
2. 概率$e_x$找到出口，走出迷宫。
3. 其余概率随机走一条该点连向的边。

求走出迷宫步数的期望。
$n\leq 10000$。
$Solution$
(直接)设$F(i)$为在$i$点走出迷宫的期望步数。答案就是$F(1)$。
令$p_i=1-k_i-e_i$，表示$i$点沿着边走的概率；$d_i=dgr[i]$，即点$i$度数。
每个点有三种状态，即$$F(i)=k_i\times F(1)+e_i\times 0+\frac{p_i}{d_i}\sum_{v=to[i]}(F(v)+1)$$
~~要高斯消元吗。。~~很重要的一点是图是一棵树。所以叶节点只由父节点（和$1$）转移而来，而父节点的转移中需要叶节点，我们尝试把叶节点的$F$带回去消掉父节点$F$中的什么东西。
对于叶节点：$$\begin{aligned}F(i)&=k_i\times F(1)+p_i\times(F(fa)+1)\\&=k_i\times F(1)+p_i\times F(fa)+p_i\end{aligned}$$
对于非叶节点：$$F(i)=k_i\times F(1)+\frac{p_i}{d_i}F(fa)+\frac{p_i}{d_i}\sum_{v=son[i]}F(v)+p_i$$
设$$F(i)=A_i\times F(1)+B_i\times F(fa)+C_i$$
把叶节点的$F(v)=A_v\times F(1)+B_v\times F(fa)+C_v$带到父节点的$F(i)$中：$$F(i)=k_i\times F(1)+\frac{p_i}{d_i}F(fa)+\frac{p_i}{d_i}\sum_{v=son[i]}(A_v\times F(1)+B_v\times F(i)+C_v))+p_i$$$$(1-\frac{p_i}{d_i}\sum_{v=son[i]}B_v)F(i)=(k_i+\frac{p_i}{d_i}\sum_v A_v)F(1)+\frac{p_i}{d_i}F(fa)+p_i+\frac{p_i}{d_i}\sum_v C_v$$
对于叶节点$v$，$A_v=k_v,B_v=C_v=p_v$。
然后可以由$v$得到$A_i,B_i,C_i$。
对于根节点，$F(1)=A_1\times F(1)+C_1$，即$F(1)=\frac{C_1}{1-A_1}$。

$A_1=1$或者存在$(1-\frac{p_i}{d_i}\sum_{v=son[i]}B_v)=1$时无解。（注意后一个）
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define eps 1e-9//small
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=10005;

int Enum,H[N],nxt[N<<1],to[N<<1],dgr[N];
double A[N],B[N],C[N],K[N],P[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
bool DFS(int x,int f)
{
	if(dgr[x]==1 && f)//链。。
	{
		A[x]=K[x], B[x]=C[x]=P[x];
		return 1;
	}
	double a=K[x],b=P[x]/dgr[x],c=P[x],d=0,p=b;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			if(!DFS(v,x)) return 0;
			a+=p*A[v], c+=p*C[v], d+=p*B[v];
		}
	if(fabs(1-d)<eps) return 0;
	A[x]=a/(1-d), B[x]=b/(1-d), C[x]=c/(1-d);
	return 1;
}

int main()
{
	for(int T=read(),i=1; i<=T; ++i)
	{
		Enum=0, memset(H,0,sizeof H), memset(dgr,0,sizeof dgr);
		int n=read();
		for(int i=1; i<n; ++i) AE(read(),read());
		for(int i=1; i<=n; ++i) K[i]=1.0*read()/100,P[i]=1-K[i]-(1.0*read()/100);
		printf("Case %d: ",i);
		if(DFS(1,0) && fabs(1.0-A[1])>eps) printf("%.5lf\n",C[1]/(1.0-A[1]));
		else puts("impossible");
	}
	return 0;
}
