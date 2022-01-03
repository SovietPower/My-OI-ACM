/*
434ms	15.43MB
对于一条链（只有两个儿子），我们可以每次取出两个链中的最大值，只取其中一个。
对于多个儿子，同样可以这样做若干次。每次启发式合并只保留需要算贡献的值，最后统计一遍即可。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int H[N],nxt[N],mem[N],id[N];
std::priority_queue<int> q[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
int Merge(int x,int y)//x->y
{
	static int A[N];
	if(q[x].size()>q[y].size()) std::swap(x,y);
	int t=0;
	while(!q[x].empty()) A[++t]=std::max(q[x].top(),q[y].top()), q[x].pop(), q[y].pop();
	while(t) q[y].push(A[t--]);
	return y;
}
void DFS(int x)
{
	static int Cnt=0;
	for(int v=H[x]; v; v=nxt[v])
		if(DFS(v),!id[x]) id[x]=id[v];
		else id[x]=Merge(id[x],id[v]);
	if(!id[x]) id[x]=++Cnt;
	q[id[x]].push(mem[x]);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) mem[i]=read();
	for(int i=2; i<=n; ++i) AE(read(),i);
	DFS(1);
	LL ans=0; std::priority_queue<int> &q=::q[id[1]];
	while(!q.empty()) ans+=q.top(), q.pop();
	printf("%lld\n",ans);

	return 0;
}
