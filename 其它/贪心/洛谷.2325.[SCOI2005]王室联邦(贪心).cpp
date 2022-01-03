/*
首先可以考虑DFS 每B个分一个块，但是这样链底不会和上边相连 
于是考虑从底下开始分，即在DFS完一个点时才将其加入栈中；当子树size==B时出栈 
最后在根节点可能会剩下一些未分配的点，这些点数当然<B(算上根节点<=B)，分给上块就好了 
感觉那么。。这才2B。。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=1005;

int n,B,Enum,H[N],to[N<<1],nxt[N<<1],sk[N],num,bel[N],cnt,capt[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	int cur=num;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f)
		{
			DFS(to[i],x);
			if(num>=B+cur)
			{
				capt[++cnt]=x;
				while(num>cur)
					bel[sk[num--]]=cnt;
			}
		}
	sk[++num]=x;
}

int main()
{
	n=read(),B=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	if(n<B) {putchar('0'); return 0;}
	DFS(1,1);
	while(num) bel[sk[num--]]=cnt;
	printf("%d\n",cnt);
	for(int i=1; i<n; ++i) printf("%d ",bel[i]);
	printf("%d\n",bel[n]);
	for(int i=1; i<=cnt; ++i) printf("%d ",capt[i]);

	return 0;
}
