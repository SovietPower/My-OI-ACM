/*
42700kb	6968ms
树形DP，考虑子节点对父节点的贡献。 
设f[x][i][j]表示当前为x，用i个x去合成上一层装备，花费为j的最大价值。
由子节点转移时 是一个分组背包，需要一个辅助数组g[i][j]表示前i棵子树花费为j能贡献给x的最大价值。
那么 $g[i][j] = max{g[i-1][j-k]+f[v][l*need[x]][k]}$。$need[x]$为x需要子节点v的个数，$l$为合成x的个数，这个同样需要枚举。
那么对于每个$l$，可以枚举用多少个x合成上一层，更新f，即 $f[x][i][j] = max{g[all][j]+val[x]*(l-i)}$。($g$已经是要求合成$l$个x的价值)
处理完一棵子树，就可以简单地背包一下最大价值了。。
费用流显然做不了嘛。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=53,M=2002,INF=0x3f3f3f3f;

int n,m,Enum,H[N],nxt[N],to[N],need[N],dgr[N],val[N],cost[N],num[N],Ans[M],f[N][101][M],g[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, need[Enum]=w;
}
void dfs(int x)
{
	if(!H[x]){
		num[x]=std::min(num[x],m/cost[x]);
		for(int i=0; i<=num[x]; ++i)
			for(int j=i; j<=num[x]; ++j)//限制不是 j*cost[x]<=m。。还有num[]限制。
				f[x][i][j*cost[x]]=(j-i)*val[x];
		return;
	}
	num[x]=100;
	for(int i=H[x]; i; i=nxt[i])
		dfs(to[i]), num[x]=std::min(num[x],num[to[i]]/need[i]), cost[x]+=need[i]*cost[to[i]];
	num[x]=std::min(num[x],m/cost[x]);
	for(int l=num[x]; ~l; --l)//当前要合成l个 
	{//g[]不需要再清空了吧，数量递减g[]一定是递增的。当然这么写本来也不需要。
		memset(g,-0x3f,sizeof g);//然而必须要清空。。之后的g[j]可能被之前本应非法-INF的g[j-k]给更新了。。
		g[0]=0;//necessary
		for(int i=H[x]; i; i=nxt[i])
			for(int j=m; ~j; --j)//这要更新到0！(DP g[]的初始值) 
			{
				int tmp=-INF;
				for(int k=0; k<=j; ++k)
					tmp=std::max(tmp,g[j-k]+f[to[i]][l*need[i]][k]);
				g[j]=tmp;
			}
		for(int i=0; i<=l; ++i)
			for(int j=0; j<=m; ++j)
				f[x][i][j]=std::max(f[x][i][j],g[j]+(l-i)*val[x]);//不需要再枚举k用g[k]更新f[j-k]，f只是由g[]转移来，且只能从当前g[]转移。
	}
}

int main()
{
	n=read(),m=read();
	char s[3];
	for(int x,v,i=1; i<=n; ++i)
	{
		val[i]=read(), scanf("%s",s);
		if(s[0]=='A'){
			x=read();
			while(x--) v=read(),AddEdge(i,v,read());
		}
		else cost[i]=read(),num[i]=read();
	}
	memset(f,-0x3f,sizeof f);//会有非法状态。
	for(int i=1; i<=n; ++i)
		if(!dgr[i])
		{
			dfs(i);
			for(int j=m; j; --j)
				for(int k=1; k<=j; ++k)
					Ans[j]=std::max(Ans[j],Ans[j-k]+f[i][0][k]);//根节点从f[i][0]转移就好了。
		}
	printf("%d",Ans[m]);
	return 0;
}
