/*
1212kb	36ms
首先空格的移动等价于棋子在黑白格交替移动（设起点，即与白子交换的格子为黑色），且不会走到离起点距离为奇数的黑格、到起点距离为偶数的白格（删掉/当作障碍就行了），且不会重复走一个格子（回不去）。
（然后策略就同上题了，只不过第一步是走棋子）
还是考虑二分图最大匹配。如果起点不一定在最大匹配上，先手走到最大匹配点，后手沿最大匹配边走，先手要么无法走要么回到刚刚的情况，即先手必败（最大匹配是一条奇数长路径）。
反之，如果起点一定在最大匹配上，先手必胜。
判断一个点是否一定在最大匹配上可以先求一遍，再对非匹配点DFS。但是本题有多次移动，相当于删掉之前的点再求最大匹配。
如果删掉的点一定在最大匹配上，那么移动前该人必胜。
判断删的点是否一定在最大匹配中：首先当前在最大匹配中，其次删掉这个点x后，没有新的增广路（match[x]找不到新匹配）。
删点后记得清空连着的点的link啊。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1605,M=N<<2;

int n,m,mp[50][50],id[50][50],Enum,H[N],nxt[M],to[M],lk[N],Time,vis[N];
bool ban[N],ans[2005];
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
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
bool OK(int x)
{
	vis[x]=Time;
	for(int i=H[x],v; i; i=nxt[i])
		if(vis[v=to[i]]!=Time && !ban[v])
		{
			vis[v]=Time;
			if(!lk[v]||OK(lk[v])) return lk[v]=x,lk[x]=v,1;
		}
	return 0;
}

int main()
{
	n=read(),m=read(); int x=0,y=0;
	for(int i=1; i<=n; ++i)
	{
		register char c=gc();
		for(; c!='X'&&c!='O'&&c!='.'; c=gc());
		for(int j=1; j<=m; ++j,c=gc())
			if(c=='X') mp[i][j]=1;//black
			else if(c=='O') mp[i][j]=0;//white
			else x=i, y=j, mp[i][j]=1;
	}
	int f=(x+y)&1,tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(mp[i][j]^f^((i+j)&1))//f^is_black^(i+j)&1
				id[i][j]=++tot;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(!id[i][j]) continue;//!
			if(id[i+1][j]) AE(id[i][j],id[i+1][j]);
			if(id[i][j+1]) AE(id[i][j],id[i][j+1]);
		}
	for(int i=1; i<=tot; ++i) if(!lk[i]/*!*/) ++Time, OK(i);
	int K=read()<<1;
	for(int i=1,p; i<=K; ++i)
	{
		ban[p=id[x][y]]=1;
		if(lk[p]) ++Time, lk[lk[p]]=0/*清空！*/, ans[i]=!OK(lk[p]);//(x,y)是否是必胜态 
		x=read(), y=read();
	}
	int res=0;
	for(int i=1; i<=K; i+=2) if(ans[i]&&ans[i+1]) ++res;
	printf("%d\n",res);
	for(int i=1; i<=K; i+=2) if(ans[i]&&ans[i+1]) printf("%d\n",i+1>>1);

	return 0;
}
