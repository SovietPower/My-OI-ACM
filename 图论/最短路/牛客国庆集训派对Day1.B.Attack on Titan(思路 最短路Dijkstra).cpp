/*
90ms	10320KB
$Description$
����$n,m,C$����СΪ$(n+1)(m+1)$�ľ���$c[i][j]$��ƽ������$(n+1)(m+1)$���㣬��$(0,0)$��ŵ�$(n,m)$��
������ʱ�̣������ѡ���ڵ�ǰ��$(x,y)$��ȡ����ʵ������λ����������ȡÿһ��λ�軨��ʱ��$c[x][y]$��
Ҳ����ѡ���һ�����ƶ�����һ���㣬���ѵ��������ƶ�·�ߵ�ŷ����þ��루ֻ��������������ƽ�л���������н�$45^{\circ}$�ķ����ߣ���������ʱ�䡣
��ʼʱ��$0$������������ʱ�̵��������ܳ���$C$��������ʵ���������$(0,0)$�ߵ�$(n,m)$���������ʱ�䡣
$n,m\leq20,\ C\leq10000,\ c[i][j]\leq10^6$��
$Solution$
���·��������ô��ʾ������һ״̬�أ�
ע�⵽ÿ���ߵ�·�߳��ȣ�Ҳ�����������ѣ��Լ�������ȡ��һ�����Ա�ʾ��$x\cdot1+y\cdot\sqrt2,\ x,y\in\mathbb{Z}$���ȴ��ڻ���Ҳ���ڻ�ȡ������$x,y$����Ϊ��Ҳ����Ϊ������
ע�⵽ͼ��С�����׷���$x\in[-40,40],y\in[-20,20]$�͹��ˣ���$0\leq x\cdot1+y\cdot\sqrt2\leq C$��
Ҳ��������ʱ�̵�����ֻ��Ҫ��$x\cdot1+y\cdot\sqrt2$�Ϳ����ˡ������еĺϷ�$x\cdot1+y\cdot\sqrt2$ȫ���ֵ��������Щ��������״̬�Ϳ����ˣ���Ϊ$w[i]$��$C=10^4$�Ļ�״̬��ֻ�в���$1700$����

Ȼ�����ǾͿ�����$Dijkstra$�ˣ�
����״̬$(x,y,now)$����ʾ��ǰ��$(x,y)$������Ϊ$w[now]$��ֻ��Ҫ��������Χ$8$�������ƶ��ͺ��ˣ�ͬʱҲ����ѡ����ԭ�ز�����������$w[now]$�䵽��$w[now+1]$��
���и�������$w[now]$����$1$����$\sqrt2$����$w$���١����Ԥ����һ�¾ͺ��ˣ���ÿ��$now$�ҵ���$now-1$��$now-\sqrt2$�������ģ�ע�ⲻҪ�Ҵ�...= =����

ע�ⲻҪ����$C$�����ƣ���������״̬���������С= =��WA\*INF��
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
	for(int i=1; i<=cnt; ++i)//��1��λ����sqrt(2)��λ�����������ĵ����� 
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
