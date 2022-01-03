/*
13948kb	5904ms
$Description$
n个点m条边的无向图，每个点有点权。对于任意一个三元环(i,j,k),i<j<k，其贡献为max{ai,aj,ak}。求所有三元环的贡献和。
$Solution$
一般的三元环计数问题：根据出度是否<=sqrt(m)将点分为两类。
对于dgr[x]<=sqrt(m)的点x，枚举x的任意两条出边，判断这两条出边的端点间是否有边（map/set/邻接表hash）。因为一条边最多被起点枚举sqrt(m)次，最多枚举m条边，所以复杂度不超过O(m*sqrt(m))（无向图的话计算过的点不再计算了）。
对于dgr[x]>sqrt(m)的点x，三个三个枚举这些点，暴力判断之间是否有边。因为最多只有sqrt(m)个这样的点，so复杂度是O(sqrt(m)^3)=O(m*sqrt(m))。
对于本题，我们消除取max的限制。对于原图中的一条边u<->v，若val[u]<val[v]，则连边v->u；否则连边u->v。（相等的话一样吧）
然后我们从val最大的点遍历新图（因为是有向图，so不会重复）。枚举当前点的出边x->v，若dgr[v]<=sqrt(m)，则枚举v的出边，判断是否与x相邻；否则枚举x的出边v'，判断是否与v相邻。
判断是判断v是否与v'有连边，而不是v'与v有边！因为若v'度数小会只枚举其出边，比如如果按后者判断，v->v'有边，枚举v时不算答案；而v'是枚举其出边，并不包括v。这个贡献就没了。so都统一计出边答案就行了。
（可以在此之前枚举x的出边x->v，对v打标记，就可以知道某个点是否与x相邻）
复杂度不知道。
???卡数组邻接表还行，T了三遍。
*/
#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=250005;

int n,m,/*Enum,H[N],nxt[M],to[M],*/Link[N],dgr[N];
std::set<int> s[N];
std::vector<int> vec[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node{
	int val,id;
	bool operator <(const Node &a)const{
		return val>a.val;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	++dgr[u], vec[u].push_back(v);
//	++dgr[u], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){read(),i};
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), A[u].val>A[v].val?(AddEdge(u,v),s[u].insert(v)):(AddEdge(v,u),s[v].insert(u));//set连双向/单向无所谓了，反正连通是单向的(不过这样快啊)
	std::sort(A+1,A+1+n);
	long long ans=0;
	for(int i=1,x,val,size=sqrt(m); i<=n; ++i)
	{
		x=A[i].id, val=A[i].val;
		const std::vector<int> &X=vec[x];
		int l=X.size();
		for(int j=0,l=X.size(); j<l; ++j) Link[X[j]]=x;
		for(int j=0,l=X.size(),v; j<l; ++j)
		{
			v=X[j];
			if(dgr[v]<=size){
				for(int k=0,l2=vec[v].size(); k<l2; ++k)
					if(Link[vec[v][k]]==x) ans+=val;
			}
			else{
				for(int k=0; k<l; ++k)
					if(s[v].count(X[k])) ans+=val;//not s[to[k]].count(v)!!!
			}
		}
//		for(int j=H[x]; j; j=nxt[j]) Link[to[j]]=x;
//		for(int j=H[x],v; j; j=nxt[j])
//		{
//			v=to[j];
//			if(dgr[v]<=size){
//				for(int k=H[v]; k; k=nxt[k])
//					if(Link[to[k]]==x) ans+=val;
//			}
//			else{
//				for(int k=H[x]; k; k=nxt[k])
//					if(s[v].count(to[k])) ans+=val;//if(s[to[k]].count(v)) ans+=val;//WA
//			}
//		}
	}
	printf("%lld",ans);

	return 0;
}
