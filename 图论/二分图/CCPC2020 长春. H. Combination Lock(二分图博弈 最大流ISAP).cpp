/*
826ms	36000KB (做法1：2028ms	34200KB)
总结一下二分图匹配（原来真就只能出板子？），其它变型可以见[JSOI2019 游戏](https://www.cnblogs.com/SovietPower/p/9591108.html)、[NOI2011 兔兔与蛋蛋游戏](https://www.cnblogs.com/SovietPower/p/9592769.html)，还有一个[板子](https://www.cnblogs.com/SovietPower/p/9770464.html)。
**条件：**
操作可以视为在一个二分图上进行，每次从一部分走到另一部分，且不会走走过的点。
**做法：**
若某点（某状态）一定在最大匹配上，则处于该点时先手必胜；否则存在某种匹配使得该点不在最大匹配上，则处于该点时先手必败。（证明见[JSOI2019 游戏](https://www.cnblogs.com/SovietPower/p/9591108.html)）
**判断某点是否一定在最大匹配上：**
**做法1：** 保留该点求最大匹配，删掉该点再求最大匹配，看匹配数是否减少（做的时候反过来，先让该点不与$S/T$相连求匹配数，再加上该点到$S/T$的边求（其它边加上就行啊））。可以用网络流复杂度$O(能过)$。
**做法2：** 先求最大匹配，若该点未被匹配则肯定是。然后枚举所有未被匹配点$x$，记与$x$有边的点为$to$，所有已与$to$匹配的点$lk[to]$可以不在最大匹配上。可以直接匈牙利，复杂度$O(nm)$；或者网络流后再DFS，复杂度$O(能过+n+m)$。

因为方法1要两遍网络流，比方法2的一遍慢的多（甚至慢一倍多？）。

-----
$Description$
有一个有$m$位数字的锁（每位为$0$到$9$），初始状态给定。$Alice,Bob$轮流操作，每次操作可以更改一位数字（加一或减一），且改后状态不能和之前出现过的重复，且不能出现在给定的$n$种状态中。$Alice$先手，不能操作的人输，问谁能赢。
$m\leq5,n\lt 10^m,10组数据$。
$Solution$
每次操作后所有数位和的奇偶性都会改变，所以操作可以看做一个二分图。
然后判断起点是否一定在最大匹配上就ok了。
本地跑样例老RE，原来是把扩栈关了。。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e5+5,M=N*20,LIM=1e5;
const int pw10[]={1,10,100,1000,10000,100000,1000000};

int Enum,S,T,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],lk[N];
bool odd[N],vis[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	int T=::T;
	for(int i=S; i<T; ++i) lev[i]=T+1;
	int h=0,t=1; q[0]=T, lev[T]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==T+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[S]<=T;
}
inline int Augment()
{
	for(int i=T; i; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	static int cur[N],num[N];

	if(!BFS()) return 0;
	int S=::S,T=::T,res=0,x=S;
	memset(num,0,T+1<<2);
	for(int i=S; i<=T; ++i) cur[i]=H[i], ++num[lev[i]];
	while(lev[S]<=T)
	{
		if(x==T) res+=Augment(),x=S;
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=T;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=S) x=fr[pre[x]];
		}
	}
	return res;
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(/*lk[to[i]] && */!vis[lk[to[i]]]) DFS(lk[to[i]]);
}
void Solve()
{
	static int Ts=0; ++Ts;
	static int ban[N];

	int m=read(),n=read(),start=read();
	Enum=1, S=0, T=pw10[m]+1;
	while(n--) ban[read()]=Ts;

	for(int i=0; i+1<T; ++i)
		if(ban[i]!=Ts)
		{
			if(odd[i]) AE(i+1,T,1);
			else AE(S,i+1,1);
		}
	int tmp=Enum;
	for(int i=0; i+1<T; ++i)
		if(ban[i]!=Ts && !odd[i])
			for(int j=0; j<m; ++j)
			{
				int bit=i/pw10[j]%10,x;
				if(bit!=9) x=i+pw10[j];
				else x=i-9*pw10[j];
				if(ban[x]!=Ts) AE(i+1,x+1,1);

				if(bit) x=i-pw10[j];
				else x=i+9*pw10[j];
				if(ban[x]!=Ts) AE(i+1,x+1,1);
			}
	ISAP();
//--做法1：
//	if(odd[start]) AE(start+1,T,1);
//	else AE(S,start+1,1);
//	if(ISAP()) puts("Alice");
//	else puts("Bob");

//--做法2：
	for(int i=tmp+1; i<=Enum; i+=2)
		if(!cap[i]) assert(!lk[fr[i]]&&!lk[to[i]]),lk[fr[i]]=to[i], lk[to[i]]=fr[i];
	vis[0]=1;//! DFS别走0。
	for(int i=1; i<T; ++i) if(!lk[i] && !vis[i]) DFS(i);
	puts(vis[start+1]?"Bob":"Alice");//vis=0:一定在最大匹配中 

	memset(H,0,T+1<<2), memset(lk,0,T+1<<2), memset(vis,0,T+1);
}

int main()
{
	for(int i=0; i<LIM; ++i)
	{
		int x=i,t=0;
		while(x) t+=x%10,x/=10;
		odd[i]=t&1;
	}
	for(int T=read(); T--; Solve());

	return 0;
}
