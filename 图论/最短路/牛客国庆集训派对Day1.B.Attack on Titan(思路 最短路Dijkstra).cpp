/*
90ms	10320KB
$Description$
给定$n,m,C$及大小为$(n+1)(m+1)$的矩阵$c[i][j]$。平面上有$(n+1)(m+1)$个点，从$(0,0)$编号到$(n,m)$。
在任意时刻，你可以选择在当前点$(x,y)$获取任意实数个单位的能量，获取每一单位需花费时间$c[x][y]$；
也可以选择从一个点移动到另一个点，花费的能量是移动路线的欧几里得距离（只可以沿与坐标轴平行或与坐标轴夹角$45^{\circ}$的方向走），不花费时间。
初始时有$0$点能量，任意时刻的能量不能超过$C$（可以是实数）。求从$(0,0)$走到$(n,m)$所需的最少时间。
$n,m\leq20,\ C\leq10000,\ c[i][j]\leq10^6$。
$Solution$
最短路，但是怎么表示能量这一状态呢？
注意到每次走的路线长度，也就是能量花费，以及能量获取，一定可以表示成$x\cdot1+y\cdot\sqrt2,\ x,y\in\mathbb{Z}$（既存在花费也存在获取，所以$x,y$可能为正也可能为负）。
注意到图很小，容易发现$x\in[-40,40],y\in[-20,20]$就够了，且$0\leq x\cdot1+y\cdot\sqrt2\leq C$。
也就是任意时刻的能量只需要是$x\cdot1+y\cdot\sqrt2$就可以了。把所有的合法$x\cdot1+y\cdot\sqrt2$全算出值来，用这些做能量的状态就可以了，记为$w[i]$。$C=10^4$的话状态数只有不到$1700$个。

然后我们就可以跑$Dijkstra$了？
对于状态$(x,y,now)$，表示当前在$(x,y)$，能量为$w[now]$，只需要尝试向周围$8$个格子移动就好了，同时也可以选择在原地补充能量，由$w[now]$变到到$w[now+1]$。
还有个问题是$w[now]$花费$1$或者$\sqrt2$会变成$w$多少。这个预处理一下就好了，对每个$now$找到和$now-1$或$now-\sqrt2$相差最近的（注意不要找错...= =）。

注意不要忘了$C$的限制，拿样例的状态数做数组大小= =（WA\*INF）
*/
#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define eps 1e-7
#define eps2 1e-9
#define gc() getchar()
typedef long long LL;
const int N=23,M=1700,Way[5]={1,0,-1,0,1},Way2[5]={1,-1,-1,1,1};
const double sq2=sqrt(2),INF=(double)(1ll<<61);

int nxt1[M],nxt2[M];
bool vis[N][N][M];
double c[N][N],dis[N][N][M],w[M];
struct Node
{
	int x,y,now; double tm;
	bool operator <(const Node &x)const
	{
		return tm>x.tm;
	}
}e[M];
std::priority_queue<Node> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),C=read(),cnt=0;
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=m; ++j) c[i][j]=read();
	for(int i=-40; i<=40; ++i)
		for(int j=-20; j<=20; ++j)
		{
			double v=i+j*sq2;
			if(v>=0 && v<C+eps2) w[++cnt]=v;
		}
	std::sort(w+1,w+1+cnt);
	for(int i=1; i<=cnt; ++i)//走1单位或走sqrt(2)单位，能量会消耗到哪里 
	{
		for(int j=i-1; j; --j)
			if(fabs(w[i]-1-w[j])<eps) {nxt1[i]=j; break;}
//			if(w[i]-w[j]<1+eps) {nxt1[i]=j; break;}//wrong.
		for(int j=i-1; j; --j)
			if(fabs(w[i]-sq2-w[j])<eps) {nxt2[i]=j; break;}
	}
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=m; ++j)
			for(int k=1; k<=cnt; ++k) dis[i][j][k]=INF;
	dis[0][0][1]=0, q.push((Node){0,0,1,0});
	while(!q.empty())
	{
		Node tmp=q.top(); q.pop();
		int x=tmp.x,y=tmp.y,now=tmp.now;
		if(vis[x][y][now]) continue;
		if(x==n&&y==m) return printf("%.9lf\n",dis[x][y][now]),0;
		vis[x][y][now]=1;
		int t=0;
		if(w[now]+eps>1)
		{
			for(int i=0,xn,yn; i<4; ++i)
				if((xn=x+Way[i])<=n&&xn>=0&&(yn=y+Way[i+1])<=m&&yn>=0)
					e[++t]=(Node){xn,yn,nxt1[now],0};
		}
		if(w[now]+eps>sq2)
		{
			for(int i=0,xn,yn; i<4; ++i)
				if((xn=x+Way2[i])<=n&&xn>=0&&(yn=y+Way2[i+1])<=m&&yn>=0)
					e[++t]=(Node){xn,yn,nxt2[now],0};
		}
		if(now<cnt) e[++t]=(Node){x,y,now+1,(w[now+1]-w[now])*c[x][y]};
		#define v e[i]
		double ds=dis[x][y][now];
		for(int i=1; i<=t; ++i)
			if(dis[v.x][v.y][v.now]>ds+v.tm)
				v.tm=dis[v.x][v.y][v.now]=ds+v.tm, q.push(v);
	}

	return 0;
}
