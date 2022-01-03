/*
22156ms	31.88MB
$Description$
给定一棵边带权的树。求删掉K条边、再连上K条权为0的边后，新树的最大直径。
$n,K\leq3\times10^5$。
$Solution$
题目可以转化为，求树上不相交的$k+1$条链，使得它们的边权和最大(已不想再说什么了。。)。
选择链数越多，答案增长得越慢，减少的时候还会减少得越快，即形成了一个$K-Ans_K$的上凸包；而如果没有链数的限制，DP是很容易的(有链数得加一维$k$)。
带权二分。DP用$f[x][0/1/2]$表示点$x$度数为$0/1/2$时的最优解，记一下最优情况下的链数。

**DP细节：**
$f[x][1]$即度数为$1$时不加作为链的花费，而是合并时加上，更方便吧。
最后用$f[x][0]$ 与 以$f[x][1]$结束链或是$f[x][2]$取个$\max$，表示最终状态（不再向上更新的最优状态，即从这断开）。
结构体写虽然可能慢点但是太好写了。但常数竟然这么大的么...
注意是$K+1$→_→ 

**[Update] 19.2.11**
二分边界是，使得边界足够大能保证每一个物品都不会选，也就是每个物品的最大可能值就可以了。（比如[CF739E](https://www.cnblogs.com/SovietPower/p/9163792.html)，权值0~1就够）
然后...二分的时候只要保证恰好取到$k$个就可以了，斜率具体是多少无所谓...吧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int n,K,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
LL C,sum;
struct Node{
	LL v; int n;
	Node() {}
	Node(LL v,int n):v(v),n(n) {}
	bool operator <(const Node &x)const{
		return v==x.v?n>x.n:v<x.v;
	}
	Node operator +(const Node &x){
		return Node(v+x.v, n+x.n);
	}
	Node operator +(LL val){
		return Node(v+val, n);
	}
}f[N][3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	int w=read(); sum+=abs(w);
	to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;	
}
inline Node Update(Node t){//合并成一条整链 
	return Node(t.v-C, t.n+1);
}
void DFS(int x,int fa)
{
	f[x][0]=f[x][1]=Node(0,0), f[x][2]=Node(-C,1);
	//但是最初f[x][1/2]不应该没有值吗。。但是这样初始化没问题 因为如果只是这种情况也不会比f[x][0]更优吧。
	for(int v,val,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x), val=len[i];
			f[x][2]=std::max(f[x][2]+f[v][0],Update(f[x][1]+f[v][1]+val));
			f[x][1]=std::max(f[x][1]+f[v][0],f[x][0]+f[v][1]+val);
			f[x][0]=f[x][0]+f[v][0];
		}
	f[x][0]=std::max(f[x][0],std::max(Update(f[x][1]),f[x][2]));
}

int main()
{
	n=read(), K=read()+1;
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	LL l=-sum,r=sum;
	while(l<=r)
	{
		if(C=l+r>>1, DFS(1,1), f[1][0].n>K) l=C+1;
		else r=C-1;
	}
	C=l, DFS(1,1);//最后以l(r+1)为答案。
	printf("%lld",f[1][0].v+K*l);

	return 0;
}
