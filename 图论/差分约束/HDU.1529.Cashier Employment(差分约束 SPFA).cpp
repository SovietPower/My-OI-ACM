/*
15MS	1580K
$Description$
给定一天24h 每小时需要的员工数量Ri，有n个员工，已知每个员工开始工作的时间ti(ti∈[0,23])，每个员工会连续工作8h。
问能否满足一天的需求。若能，输出最少需要多少员工。
$Solution$
既然给的是开始工作时间，那么就先根据开始时间做 
设Ai表示在i时开始工作的人数(未知)，Bi表示i时可工作人数的上限(已知) 
那么有:（注意可以跨天） 
A[i-7]+A[i-6]+...+A[i-1]+A[i] >= R[i] (7 <= i < 24)
A[17+i]+A[18+i]+...+A[23]+A[0]+A[1]+...+A[i] >= R[i] (0 <= i < 7)
0 <= A[i] <= B[i]

令S[i]=A[0]+A[1]+...+A[i]，规定S[-1]=0，将上边式子转化一下有: 
S[i]-S[i-8] >= R[i] (7 <= i < 24)
S[23]-S[16+i]+S[i] >= R[i] (0 <= i < 7)
0 <= S[i]-S[i-1] <= B[i]
观察不等式二，有三个未知数，S[23]是个未知条件，还无法转化为差分约束条件，但只有两个变量与i有关，于是我们对S[23]进行枚举，令S[23]=T 
S[i]-S[i-8] >= R[i] (7 <= i < 24)
S[i]-S[16+i] >= R[i]-T (0 <= i < 7)
S[i]-S[i-1] >= 0 
S[i-1]-S[i] >= -B[i]
这样就将原问题转化为了求-1 -> 23的最长路 
但是还有一个条件，我们令S[23]=T，我们也需要将其转化为不等式，因为S[-1]=0，所以S[23]-S[-1]=T，将其转化为两个不等式 
S[23]-S[-1] >= T
S[-1]-S[23] >= -T
若-1 -> 23的最长路=T，那么T就是满足条件的一个解。从小到大枚举 第一个可行的即为答案。
由于员工数量显然是单调的，所以可以二分T (满足条件仍是不存在负环) 
注: T(S[23]=A[0]+A[1]+...)的上界是n，not B[23] 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=50,M=1e4+5,T=24,INF=0x3f3f3f3f;

int n,B[N],R[N],Enum,H[N],nxt[M],to[M],val[M],dis[N],tm[N];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
bool SPFA()
{
	for(int i=1; i<=T; ++i) dis[i]=-INF,tm[i]=0;
	tm[0]=dis[0]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]<dis[x]+val[i])
			{
				dis[to[i]]=dis[x]+val[i];
				if(!inq[to[i]])
				{
					if(++tm[to[i]]>T) return 0;
					inq[to[i]]=1,q.push(to[i]);
				}
			}
	}
	return 1;
}
bool Check(int x)
{
	Enum=0, memset(H,0,sizeof H);
	for(int i=1; i<8; ++i) AddEdge(16+i,i,R[i]-x);
	for(int i=8; i<=T; ++i) AddEdge(i-8,i,R[i]);
	for(int i=1; i<=T; ++i) AddEdge(i,i-1,-B[i]),AddEdge(i-1,i,0);
	AddEdge(0,T,x), AddEdge(T,0,-x);
	return SPFA();
}

int main()
{
	int t=read();
	while(t--)
	{
		memset(B,0,sizeof B);
		for(int i=1; i<=T; ++i) R[i]=read();
		n=read();
		for(int i=1; i<=n; ++i) ++B[read()+1];
		int l=0,r=n+1,mid;
		while(l<r)
			if(Check(mid=l+r>>1)) r=mid;
			else l=mid+1;
		l>n ? puts("No Solution") : printf("%d\n",l);
	}
	return 0;
}
