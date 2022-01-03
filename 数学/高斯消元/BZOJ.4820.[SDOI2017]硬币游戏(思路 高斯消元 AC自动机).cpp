/*
4460kb	192ms(常数大点...结果跑的和哈希差不多)
$Description$
有$n$个长为$m$的字符集只有H,T的串。随机生成字符串，每次等概率生成H或T放在末尾，如果其中出现了$n$个串中的一个则结束。对每个串，输出随机生成的串以它结尾的概率。
$n,m\leq 300$。
$Solution$
建出AC自动机，每个点向两个儿子连边，可以得到一张有向图。参照 [[SDOI2012]走迷宫] 可以得到一个$Tarjan$+高斯消元的$O((nm)^3)$的做法。（理论有$60$分啊但是第$5.6$个点WA了smg）
其实$O((nm)^3)$就是 [[JSOI2009]有趣的游戏]...只需建出AC自动机一遍高斯消元即可，比上面那个不知道好写到哪里去。。

$40$分的做法问题在于状态（变量）太多。考虑把类似的状态合并成一个。
假设现在一共有两个串$TTH$和$HTT$，两个串的终止节点分别记作$A,B$，没有经过终止节点的状态记作$N$。
$N$加上$TTH$一定会终止，但是在逐字符加上$TTH$时可能有其它情况：$N$的后缀与$TT$相连在$B$终止、$N$的后缀与$T$相连在$B$终止......总起来就是：$$NTTH=A+BH+BTH$$

其中$BH$就表示$N$在$B$处终止，但多出来$H$。
因为$N$中出现$B$的概率就是$p(B)$，再在后面加特定的$k$个字符，概率就是$p(B)\times\frac{1}{2^k}$。
所以有：$$p(N)\times\frac18=p(A)+p(B)\times\frac12+p(B)\times\frac14\\0.125p(N)=p(A)+0.75p(B)$$

扩展到多个串，记$pre_{i,k}$表示$s_i$长度为$k$的前缀，$suf_{i,k}$表示$s_i$长度为$k$的后缀，那么$$p(N+s_i)=p(s_i)+\sum_{j=1}^n\sum_{k=1}^m[pre_{i,k}=suf_{j,k}]\frac{1}{2^{m-k}}p(s_j)=\frac{1}{2^m}p(N)$$

这样我们就可以得到$n$个方程了，但是有$n+1$个变量，剩下的一个方程就是$\sum_{i=1}^np_i=1$。就可以高斯消元了。
复杂度$O(n^3+n^2m)$。

求任意两个串之间所有公共前后缀，可以哈希或KMP或者AC自动机。
对$fail$什么的忘的差不多了...具体写一下。
**哈希：**没什么好说的。。前后缀哈希就把字符串看成一个$P$进制数好了。（向$Kelin\ dalao$学一波orz）
**KMP：**对每个$a$串求出$fail$数组，拿$s_a$在$s_b$上匹配，最后的$j$指针位置就是$s_a$最长的等于$s_b$后缀的前缀，然后$j$不断跳$fail[j]$并统计答案即可。（注意若$a=b$会计算$p(s_a)$一次，也可以先$j=fail[j]$一次）
**AC自动机：** AC自动机上每个点向能走到它的串连一条边。然后从$s_b$的终止节点不断跳$fail$，所有经过节点$x$上连出的边$s_a$，都表示$s_a$长$len_x$的前缀和$s_b$的后缀相同。
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=305,M=N*N;

double pw2[N],A[N][N],Ans[N];

struct AC_Automaton
{
	int tot,len[M],son[M][2],fail[M],q[M],H[M],Enum,nxt[M],to[M],ed[N];
	char s[N];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	void Insert(int n,int id)
	{
		scanf("%s",s);
		int x=0;
		for(int i=0,c; i<n; ++i)
		{
			if(!son[x][c=s[i]=='H']) len[son[x][c]=++tot]=len[x]+1;
			x=son[x][c], AE(x,id);
		}
		ed[id]=x;
	}
	void Build()
	{
		int h=0,t=0;
		if(son[0][0]) q[t++]=son[0][0];//, fail[son[0][0]]=0;
		if(son[0][1]) q[t++]=son[0][1];//, fail[son[0][1]]=0;
		while(h<t)
		{
			int x=q[h++];
			for(int i=0,v; i<2; ++i)
				if((v=son[x][i])) fail[v]=son[fail[x]][i], q[t++]=v;
				else son[x][i]=son[fail[x]][i];
		}
	}
	void Calc(int id,int m)
	{
		for(int x=ed[id]; x; x=fail[x])
			for(int i=H[x]; i; i=nxt[i])
				A[to[i]][id]+=pw2[m-len[x]];
	}
}ac;

void Gauss(int n)
{
	for(int j=0; j<n; ++j)
	{
		int mx=j;
		for(int i=j+1; i<n; ++i) if(fabs(A[mx][j])<fabs(A[i][j])) mx=i;
		if(mx!=j) for(int k=j; k<=n; ++k) std::swap(A[mx][k],A[j][k]);
		for(int i=j+1; i<n; ++i)
			if(A[i][j])//还是不要写>eps了= = 
			{
				double t=A[i][j]/A[j][j];
				for(int k=j; k<=n; ++k) A[i][k]-=t*A[j][k];
			}
	}
	for(int i=n-1; ~i; --i)
	{
		for(int j=i+1; j<n; ++j) A[i][n]-=A[i][j]*Ans[j];
		Ans[i]=A[i][n]/A[i][i];
	}
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	pw2[0]=1;
	for(int i=1; i<=m; ++i) pw2[i]=pw2[i-1]*0.5;
	for(int i=1; i<=n; ++i) ac.Insert(m,i);
	ac.Build();
	for(int i=1; i<=n; ++i) ac.Calc(i,m);
	for(int i=1; i<=n; ++i) A[0][i]=1, A[i][0]=-pw2[m];
	A[0][n+1]=1, Gauss(n+1);
	for(int i=1; i<=n; ++i) printf("%.10lf\n",Ans[i]);

	return 0;
}
