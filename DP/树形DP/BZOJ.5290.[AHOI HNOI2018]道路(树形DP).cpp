/*
3044kb	264ms
在儿子那统计贡献，不是在父亲那统计啊！！！（这样的话不写这个提高DP写记忆化都能过= =）
然后就令$f[x][a][b]$表示在$x$节点上面有$a$条不修的公路$b$条不修的铁路的最小花费，在叶节点处统计贡献，转移的时候枚举不修哪个即可。
对于$f$数组第一维可以卡卡空间，把不用的标号回收，同一时刻只会有$80+$个有用节点。

注意如果叶子节点设成负值，用数组$id[x]$的时候要注意！！！（访问数组负下标）
O2真是神奇，洛谷LOJ开O2过了，在BZOJ连WA= =。还以为是数组大小的问题，但其实是$C$数组开大后调用$id$负下标就访问到$C$的额外空间里去了（我会不用指针写负数组啦）（虽然不敢写）。
然而神奇的O2优化都不需要开大$C$数组也能过=-=。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e4+5;

int n,son[N][2],A[N],B[N],C[N],id[N];
LL f[82][42][42];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void DFS(int x,int a,int b)
{
	static int tot=0,top=0,sk[N];
	int now=top?sk[top--]:++tot; id[x]=now;
	if(x>=n)
	{
		int A=::A[x],B=::B[x],C=::C[x];
		for(int i=0; i<=a; ++i)
			for(int j=0; j<=b; ++j) f[now][i][j]=1ll*C*(A+i)*(B+j);
		return;
	}
	int ls=son[x][0],rs=son[x][1];
	DFS(ls,a+1,b), DFS(rs,a,b+1);
	ls=id[ls], rs=id[rs];
	for(int i=0; i<=a; ++i)
		for(int j=0; j<=b; ++j)
			f[now][i][j]=std::min(f[ls][i+1][j]+f[rs][i][j],f[ls][i][j]+f[rs][i][j+1]);
	sk[++top]=ls, sk[++top]=rs;
}

int main()
{
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);

	int n=read(); ::n=n;
	for(int i=1,s,t; i<n; ++i) s=read(),t=read(),son[i][0]=s<0?n-1-s:s,son[i][1]=t<0?n-1-t:t;
	for(int i=n,l=n+n; i<l; ++i) A[i]=read(),B[i]=read(),C[i]=read();
	DFS(1,0,0), printf("%lld\n",f[id[1]][0][0]);

	return 0;
}
