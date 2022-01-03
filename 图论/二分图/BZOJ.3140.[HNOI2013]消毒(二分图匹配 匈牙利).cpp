/*
2120kb	9300ms
woc卡着时过去 那些2000ms怎么过的？？网上找不到快点的~~懒得找~~。
不难想到每次一定是切一片。
如果是平面，很容易想到直接做二分图匹配。对于3维的？
可以发现min(a,b,c)的最大值只有$\sqrt[3]{n}≈17$，我们暴力枚举这一最小值代表的是否选，对于剩下的两维二分图匹配(\approx) 
能用匈牙利用什么网络流啊。。那么麻烦。
在匈牙利求解的过程中记得剪枝！
因为实际点数应该远不如A*B*C多，所以不要用memset，直接枚举。

zz的我考场写的每次DFS完重建边+ISAP，成功都T掉(写的方式也很zz。。每次A*B*C枚举找点，3次讨论3个DFS)
感觉数据一点梯度没有全都5s过。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005,M=20005;

int A,B,C,Time,bit[1<<18],Enum,H[N],nxt[M],to[M],match[N],use[N]/*空间换时间，匈牙利常用套路？*/;
struct Node
{
	int x,y,z;
	Node() {}
	Node(int x,int y,int z):x(x),y(y),z(z) {}
}node[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
bool Can(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(use[to[i]]!=Time)
		{
			use[to[i]]=Time;
			if(!match[to[i]]||Can(match[to[i]]))
			{
				match[to[i]]=x; return 1;
			}
		}
	return 0;
}
void Work()
{
	A=read(),B=read(),C=read();
	int cnt=0, f=1, lim=1<<A, Max=B;
	if(B<A&&B<C) f=2,lim=1<<B,Max=A;
	else if(C<A&&C<B) f=3,lim=1<<C,Max=A;
	for(int v,i=1; i<=A; ++i)
		for(int j=1; j<=B; ++j)
			for(int k=1; k<=C; ++k)
				if(v=read()){
					if(f==1) node[++cnt]=Node(i,j,k);//直接交换顺序即可 
					else if(f==2) node[++cnt]=Node(j,i,k);
					else node[++cnt]=Node(k,i,j);
				}
	int Ans=10000;
	for(int res,s=0; s<lim; ++s)
	{
		Enum=0, res=bit[s];//Time并不需要清空 
//		memset(H,0,sizeof H), memset(match,0,sizeof match);
		for(int i=1; i<=Max; ++i) H[i]=match[i]=0;//here!
		for(int i=1; i<=cnt; ++i)
			if(!(s&(1<<node[i].x-1))) AddEdge(node[i].y,node[i].z);
		++Time;
		for(int i=1; i<=Max; ++i,++Time)
			if(Can(i)){
				if(++res>=Ans) break;//剪枝！
			}
		Ans=std::min(res,Ans);
	}
	printf("%d\n",Ans);
}

int main()
{
	for(int i=1; i<(1<<17); ++i) bit[i]=bit[i>>1]+(i&1);
	int T=read();
	while(T--) Work();
	return 0;
}
