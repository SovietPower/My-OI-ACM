/*
624K	63MS
$Description$
有一个大小为N的集合$S=\{x_1,x_2,....,x_n\}$，$x_i=0或1$，给出它们之间的一些逻辑运算的结果（如x1 and x2=1），逻辑运算有AND OR XOR三种，问是否存在一种满足所有条件的取值方案。
$Solution$
对于本题，我们逐个考虑每个逻辑运算：
1、A AND B=0.这要求A和B不同时为1。既然不同时为1，那么A取1时，B必须取0；B取1时，A必须取0.所以，连边A+n->B, B+n->A。
2、A AND B=1.这要求A和B同时为1。换句话说，A和B不能是0.那要怎么样体现在图中呢？我们知道，判断一个2-sat问题是否存在合法方案的方法是，缩点后判断有没有两个同组点属于同一个连通分量。
我们需要A和B都必须是1，那么我们就让A和B必须选0时无解即可。也就是说，连边A->A+n, B->B+n。这样的话，假如构图完成后，A必须取0，那么由于存在边A->A+n，所以A也必须取1，那么就不可能是一个合法方案。所以，这两条边能保证，有合法方案的话，一定是A取1（选A+n节点）的情况。
3、A OR B=0.这要求A和B同时为0.和2类似。
4、A XOR B=0.这要求A=B。所以，A为0/1时，B必须为0/1，同理B为0/1时，A必须为0/1.所以添加边：A->B,B->A,A+n->B+n,B+n->A+n。

连接某边是为了推出矛盾。x->y表示选x则必须选y.

注意数据下标是从0开始的 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2005,M=4e6+5;

int n,m,H[N],Enum,nxt[M],to[M];
int top,sk[N],dfn[N],low[N],id,bel[N],cnt;
bool ins[N];

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
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}

int main()
{
	n=read(),m=read();
	int a,b,c; char opt[6];
	for(int i=1; i<=m; ++i)
	{
		a=read()+1,b=read()+1,c=read(),scanf("%s",opt);
		if(opt[0]=='A')
			if(c) AddEdge(a,a+n),AddEdge(b,b+n);
			else AddEdge(a+n,b),AddEdge(b+n,a);
		else if(opt[0]=='O')
			if(c) AddEdge(a,b+n),AddEdge(b,a+n);
			else AddEdge(a+n,a),AddEdge(b+n,b);
		else//Xor
			if(c) AddEdge(a,b+n),AddEdge(b,a+n),AddEdge(a+n,b),AddEdge(b+n,a);
			else AddEdge(a,b),AddEdge(b,a),AddEdge(a+n,b+n),AddEdge(b+n,a+n);
	}
	for(int i=1; i<=n<<1; ++i)
		if(!dfn[i]) Tarjan(i);
	bool f=1;
	for(int i=1; i<=n; ++i)
		if(bel[i]==bel[i+n]) {f=0; break;}
	puts(f?"YES":"NO");

	return 0;
}
